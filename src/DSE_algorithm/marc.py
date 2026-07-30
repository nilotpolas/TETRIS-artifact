"""
DSE_algorithm/marc.py — MARC: Minimize Area under Randomness and latency Constraints
=====================================================================================

MARC solves the joint optimization problem:

    Given : max_latency L*, max_randomness R*, security order d
    Find  : gadget assignment that minimises silicon area (GE)
            subject to:  total_latency   ≤ L*
                         total_randomness ≤ R*

Algorithm summary
-----------------
1. Pattern analysis — detect AND-XOR fan-out patterns for hpc2o/hpc3o eligibility.
2. Gadget setup     — choose the minimum-latency baseline gadget; compute bonus budget.
3. 4-D DP           — dp[level][bonus_spent][rand_spent][comar_used] → min area.
                      Explores every (latency, randomness) operating point within the
                      constraint box and records the minimum area achievable at each.
4. Pareto extraction— collect all non-dominated (latency, randomness, area) triples from
                      the final DP states.
5. Best selection   — identify the global min-area point within both constraints.
6. Reconstruction   — backtrack through bt_marc to recover the per-level gadget choice,
                      then call nodes_gadget_assignment() (inherited from MRLC) to produce
                      the per-node gadget_definition used by MaskedHLS.

Relationship to MRLC / MLRC
----------------------------
* MRLC : 3-D DP  —  minimise randomness subject to a latency constraint.
* MLRC : greedy  —  minimise latency subject to a randomness constraint.
* MARC : 4-D DP  —  minimise area subject to BOTH constraints simultaneously,
                    with full Pareto-front reporting across the feasible design space.

MARC inherits pattern-analysis helpers, gadget-setup, node-assignment and
gadget-definition generation from MRLC.  Only the DP, Pareto extraction, and
best-design selection are new.
"""

import math
from DSE_algorithm.mrlc import MRLC
from Gadgets import HPC1, HPC2, HPC3, COMAR, Domand, HPC2o, HPC3o, HPC2Swapped, HPC2oSwapped


class MARC(MRLC):
    """
    MARC — Minimize Area under Randomness and latency Constraints.

    Inherits infrastructure from MRLC (pattern analysis, gadget helpers,
    node assignment) but replaces the 3-D DP with a 4-D DP whose fourth
    dimension tracks cumulative randomness and whose objective is area.
    """

    def __init__(self, d, and_tree, gadget_map, and_xor_tree=None):
        super().__init__(d, and_tree, gadget_map, and_xor_tree)
        self.max_latency                 = None
        self.max_randomness              = None
        self.total_latency_after_marc    = 0
        self.total_randomness_after_marc = 0
        self.total_area_after_marc       = 0.0
        self.pareto_front                = []   # list of (latency, randomness, area)
        self._all_feasible_points        = []   # all feasible (lat, rand, area, j, r, k)
        # Backtrack coordinates for the best design
        self.best_j = 0   # bonus latency spent at the optimal point
        self.best_r = 0   # randomness consumed at the optimal point
        self.best_k = 0   # COMAR state at the optimal point
        # Pre-DP marks: empty — MARC skips the pre-DP optimisation pass
        self.hpc2_feasible_nodes     = set()
        self.levels_with_preopt_hpc2 = set()

    # ──────────────────────────────────────────────────────────────────────────
    # Public entry point
    # ──────────────────────────────────────────────────────────────────────────

    def marc(self, max_latency: int, max_randomness: int):
        """
        Main MARC algorithm.

        Parameters
        ----------
        max_latency    : maximum allowed total latency (clock cycles)
        max_randomness : maximum allowed total randomness (bits)

        After this call the following attributes are populated:
            gadget_definition          — per-node gadget assignment (for MaskedHLS)
            total_latency_after_marc   — achieved latency of the best design
            total_randomness_after_marc— achieved randomness of the best design
            total_area_after_marc      — achieved area of the best design
            pareto_front               — Pareto-optimal (lat, rand, area) triples
        """
        self.max_latency    = max_latency
        self.max_randomness = max_randomness

        print(f"\n[MARC] Starting MARC: max_latency={max_latency}, max_randomness={max_randomness}")

        # Step 1 — Pattern analysis
        if self.and_xor_tree is not None:
            self._analyze_and_xor_tree_for_patterns()
        else:
            self._analyze_and_tree_for_patterns()

        # Step 2 — Gadget setup and bonus-latency budget
        bonus_latency = self.initial_gadget_and_list_possible_replacement(max_latency)
        print(f"[MARC] Bonus latency available: {bonus_latency} cycles")

        # Step 3 — 4-D DP
        self._marc_dp(bonus_latency, max_randomness)

        # Step 4 — Pareto-front extraction
        self._extract_pareto_front(bonus_latency, max_randomness)
        print(f"[MARC] Pareto front: {len(self.pareto_front)} non-dominated design points")

        # Step 5 — Select the minimum-area feasible design
        self._select_best_design(bonus_latency, max_randomness)
        print(f"[MARC] Best design: latency={self.total_latency_after_marc}, "
              f"randomness={self.total_randomness_after_marc}, "
              f"area={self.total_area_after_marc:.2f}")

        # Step 6 — Reconstruct the gadget assignment for the best design
        self.choose_gadgets_for_each_level()
        self.nodes_gadget_assignment()

        # Sync MARC attributes (nodes_gadget_assignment also sets MRLC's attrs)
        self.total_latency_after_marc    = self.total_initial_latency + self.best_j
        self.total_randomness_after_marc = getattr(self, 'total_randomness_after_mrlc',
                                                   self.best_r)
        self.total_area_after_marc       = getattr(self, 'total_area_after_mrlc',
                                                   self.total_area_after_marc)

        print(f"[MARC RESULT] Latency   : {self.total_latency_after_marc}")
        print(f"[MARC RESULT] Randomness: {self.total_randomness_after_marc}")
        print(f"[MARC RESULT] Area      : {self.total_area_after_marc:.2f}")

        return self.gadget_definition, self.total_latency_after_marc

    # ──────────────────────────────────────────────────────────────────────────
    # 4-D Dynamic Programming
    # ──────────────────────────────────────────────────────────────────────────

    def _marc_dp(self, bonus_latency: int, max_randomness: int):
        """
        Fill the 4-D DP table.

        State  : dp_marc[i][j][r][k]
            i  — AND-only level index (1 … L)
            j  — bonus latency spent  (0 … bonus_latency)
            r  — cumulative randomness consumed (0 … max_randomness)
            k  — COMAR used flag (0 = not yet, 1 = already used)
        Value  : minimum achievable area (in liberty units / GE raw)

        Backtrack table bt_marc[i][j][r][k] = (prev_j, prev_r, gadget_name, prev_k)
        """
        L               = self.DAG_levels
        R               = max_randomness
        inf             = float('inf')
        initial_latency = self.min_latency_gadget[1]["latency"]

        total_entries = (L + 1) * (bonus_latency + 1) * (R + 1) * 2
        print(f"[MARC DP] Table size: dp[{L+1}][{bonus_latency+1}][{R+1}][2] "
              f"= {total_entries:,} entries")

        # Allocate tables
        self.dp_marc = [[[[inf] * 2 for _ in range(R + 1)]
                          for _ in range(bonus_latency + 1)]
                         for _ in range(L + 1)]

        self.bt_marc = [[[[None] * 2 for _ in range(R + 1)]
                          for _ in range(bonus_latency + 1)]
                         for _ in range(L + 1)]

        # Base case: 0 levels, 0 bonus spent, 0 randomness, COMAR unused → 0 area
        self.dp_marc[0][0][0][0] = 0.0

        for i in range(1, L + 1):
            nodes_in_level = list(self.nodes_by_level.get(i, []))
            and_nodes      = [n for n in nodes_in_level if self._is_and_node(str(n))]
            n_and          = len(and_nodes)

            # XOR-only level — propagate unchanged
            if n_and == 0:
                for j in range(bonus_latency + 1):
                    for r in range(R + 1):
                        for k in range(2):
                            self.dp_marc[i][j][r][k] = self.dp_marc[i-1][j][r][k]
                            self.bt_marc[i][j][r][k] = self.bt_marc[i-1][j][r][k]
                continue

            # Determine which gadgets are legal for this level's pattern
            patterns = set()
            for n in and_nodes:
                pat = self.node_pattern.get(n, ('pure_and', None))
                patterns.add(pat[0] if isinstance(pat, tuple) else pat)

            if len(patterns) == 1:
                avail = self._get_gadgets_for_pattern(list(patterns)[0],
                                                       self.matching_gadgets)
            else:
                avail = self.matching_gadgets   # mixed level — allow all

            # DP transitions
            for j_prev in range(bonus_latency + 1):
                for r_prev in range(R + 1):
                    for k_prev in range(2):
                        prev_area = self.dp_marc[i-1][j_prev][r_prev][k_prev]
                        if prev_area == inf:
                            continue

                        for gadget_name, gspec in avail.items():
                            # Restrict *o variants to levels with the xor_and pattern
                            if gadget_name in ('hpc2o', 'hpc3o', 'hpc2o_swapped') \
                                    and 'xor_and' not in patterns:
                                continue

                            # — Latency cost (per level, not per node) —
                            j_cost = gspec["latency"] - initial_latency
                            j_new  = j_prev + j_cost
                            if j_new > bonus_latency:
                                continue

                            # — Randomness cost —
                            # COMAR shares its 6 random bits across all instances;
                            # count the 6 bits only on the first use.
                            if gadget_name == 'comar':
                                r_added = 6 if k_prev == 0 else 0
                                k_new   = 1
                            else:
                                r_added = n_and * gspec["randomness"]
                                k_new   = k_prev

                            r_new = r_prev + r_added
                            if r_new > R:
                                continue

                            # — Area cost (per node) —
                            a_new = prev_area + n_and * gspec["area"]

                            if a_new < self.dp_marc[i][j_new][r_new][k_new]:
                                self.dp_marc[i][j_new][r_new][k_new] = a_new
                                self.bt_marc[i][j_new][r_new][k_new] = \
                                    (j_prev, r_prev, gadget_name, k_prev)

        print(f"[MARC DP] DP iteration complete.")

    # ──────────────────────────────────────────────────────────────────────────
    # Pareto-front extraction
    # ──────────────────────────────────────────────────────────────────────────

    def _extract_pareto_front(self, bonus_latency: int, max_randomness: int):
        """
        Scan dp_marc[L][*][*][*] for all finite entries, deduplicate by
        (total_latency, randomness) keeping the minimum area, then compute
        the Pareto-optimal subset in the three-objective space
        (minimise latency, minimise randomness, minimise area).
        """
        L   = self.DAG_levels
        inf = float('inf')

        # Deduplicate: for each (achieved_latency, randomness) → minimum area
        best: dict = {}
        for j in range(bonus_latency + 1):
            lat = self.total_initial_latency + j
            for r in range(max_randomness + 1):
                for k in range(2):
                    area = self.dp_marc[L][j][r][k]
                    if area < inf:
                        key = (lat, r)
                        if key not in best or area < best[key][0]:
                            best[key] = (area, j, r, k)

        all_points = [
            (lat, rand, v[0], v[1], v[2], v[3])   # lat, rand, area, j, r, k
            for (lat, rand), v in best.items()
        ]
        self._all_feasible_points = all_points

        # Pareto dominance: p dominates q iff p ≤ q in all three and < in at least one
        pareto = []
        for i, pi in enumerate(all_points):
            dominated = False
            for j2, pj in enumerate(all_points):
                if i == j2:
                    continue
                if (pj[0] <= pi[0] and pj[1] <= pi[1] and pj[2] <= pi[2] and
                        (pj[0] < pi[0] or pj[1] < pi[1] or pj[2] < pi[2])):
                    dominated = True
                    break
            if not dominated:
                pareto.append((pi[0], pi[1], pi[2]))   # (latency, randomness, area)

        pareto.sort(key=lambda x: x[2])   # sort by area (ascending)
        self.pareto_front = pareto

    # ──────────────────────────────────────────────────────────────────────────
    # Best-design selection
    # ──────────────────────────────────────────────────────────────────────────

    def _select_best_design(self, bonus_latency: int, max_randomness: int):
        """
        Find the minimum-area state among all dp_marc[L][j][r][k]
        that satisfy both constraints, and record its backtrack coordinates.
        """
        L   = self.DAG_levels
        inf = float('inf')

        best_area = inf
        best_j = best_r = best_k = 0

        for j in range(bonus_latency + 1):
            for r in range(max_randomness + 1):
                for k in range(2):
                    a = self.dp_marc[L][j][r][k]
                    if a < best_area:
                        best_area = a
                        best_j, best_r, best_k = j, r, k

        if best_area == inf:
            raise ValueError(
                "[MARC] No feasible design found within the given constraints.\n"
                "       Try increasing --max-latency or --max-randomness."
            )

        self.best_j = best_j
        self.best_r = best_r
        self.best_k = best_k
        self.total_latency_after_marc    = self.total_initial_latency + best_j
        self.total_randomness_after_marc = best_r
        self.total_area_after_marc       = best_area

    # ──────────────────────────────────────────────────────────────────────────
    # Gadget reconstruction  (overrides MRLC's choose_gadgets_for_each_level)
    # ──────────────────────────────────────────────────────────────────────────

    def choose_gadgets_for_each_level(self):
        """
        Backtrack through bt_marc from (best_j, best_r, best_k) to recover
        the per-level gadget name, then store it in self.chosen_gadget_for_levels.
        The inherited nodes_gadget_assignment() reads this list to populate
        gadget_definition with per-node entries.
        """
        L = self.DAG_levels
        self.chosen_gadget_for_levels = [None] * L

        j, r, k = self.best_j, self.best_r, self.best_k

        for i in range(L, 0, -1):
            entry = self.bt_marc[i][j][r][k]
            if entry is None:
                # XOR-only level or unreachable — fall back to baseline
                self.chosen_gadget_for_levels[i - 1] = self.min_latency_gadget[0]
            else:
                j_prev, r_prev, gadget_name, k_prev = entry
                self.chosen_gadget_for_levels[i - 1] = gadget_name
                j, r, k = j_prev, r_prev, k_prev

        print(f"[MARC] Reconstructed gadget path: {self.chosen_gadget_for_levels}")

    # ──────────────────────────────────────────────────────────────────────────
    # Public accessors
    # ──────────────────────────────────────────────────────────────────────────

    def get_pareto_front(self):
        """Return Pareto-optimal (latency, randomness, area) triples, sorted by area."""
        return list(self.pareto_front)

    def get_all_feasible_points(self):
        """Return all feasible (latency, randomness, area, j, r, k) points."""
        return list(self._all_feasible_points)
