from DSE_algorithm.dse import DSE
from tabulate import tabulate # type: ignore
import json
from collections import defaultdict
import heapq
from Gadgets import HPC1, HPC2, HPC3, COMAR, Domand, HPC2o, HPC3o, HPC2Swapped, HPC2oSwapped
import math

class MRLC(DSE):
    
    def __init__(self, d, and_tree, gadget_map, and_xor_tree=None):
        super().__init__(d, and_tree, gadget_map)
        self.and_xor_tree = and_xor_tree  # Optional: AND-XOR tree for pattern detection
        self.node_pattern = {}
        self.debug = True
        self.total_latency_after_mrlc = 0
        self.total_randomness_after_mrlc = 0.0
        self.initial_latency = 0
        # map: level -> list of AND expressions at that level, used by nodes_gadget_assignment
        self.level_nodes = {}

    def _display_3d_dp_table(self, dp_table, L, bonus_latency, title="DP Table"):
        print(f"\n--- {title} ---")

        # COMAR NOT USED (k=0)
        print("\n--- COMAR NOT USED (k=0) ---")
        formatted_dp_0 = [
            [f"{dp_table[l][b][0]:.2f}" if dp_table[l][b][0] != math.inf else 'inf'
            for b in range(bonus_latency + 1)]
            for l in range(L + 1)
        ]
        print(tabulate(formatted_dp_0,
                    headers=[f"B={i}" for i in range(bonus_latency + 1)],
                    showindex=[f"L={i}" for i in range(L + 1)],
                    tablefmt="fancy_grid"))

        # COMAR USED (k=1)
        print("\n--- COMAR USED (k=1) ---")
        formatted_dp_1 = [
            [f"{dp_table[l][b][1]:.2f}" if dp_table[l][b][1] != math.inf else 'inf'
            for b in range(bonus_latency + 1)]
            for l in range(L + 1)
        ]
        print(tabulate(formatted_dp_1,
                    headers=[f"B={i}" for i in range(bonus_latency + 1)],
                    showindex=[f"L={i}" for i in range(L + 1)],
                    tablefmt="grid"))


    
    def _mrlc_dp(self, target_latency):
        print(f"[DEBUG] gadget_map keys: {list(self.gadget_map.keys())}")
        print(f"[DEBUG] hpc2o present? {'hpc2o' in self.gadget_map}")
        print(f"[DEBUG] hpc3o present? {'hpc3o' in self.gadget_map}")
        print(f"[DEBUG] and_xor_tree available? {self.and_xor_tree is not None}")
        """
        Main MRLC DP method - wrapper that calls the setup and DP iteration
        
        CRITICAL ORDERING:
        1. Pattern analysis (identify XOR_AND vs pure_and)
        2. Initialize gadgets and bonus latency
        3. PRE-DP Asymmetric optimization (mark HPC2-feasible nodes)
        4. DP algorithm (uses marked nodes + bonus latency)
        5. Gadget assignment (applies XOR_AND optimizations)
        """
        print(f"\n[MRLC INFO] Starting MRLC-DP with target_latency={target_latency}")
        
        # Step 1: Analyze patterns using and_xor_tree if available
        if self.and_xor_tree is not None:
            self._analyze_and_xor_tree_for_patterns()
        else:
            self._analyze_and_tree_for_patterns()
        
        # Step 2: Initialize gadget selection and bonus latency
        bonus_latency = self.initial_gadget_and_list_possible_replacement(target_latency)
        
        # ===== CRITICAL: Step 2.4 - Pre-initialize all nodes as HPC3 =====
        # This is REQUIRED for pre-DP optimization to work!
        # Pre-DP optimization looks for existing HPC3 nodes to mark as HPC2-feasible
        # If no gadget assignments exist, it finds nothing!
        print("\n[MRLC] Step 2.4: Pre-initializing all AND nodes with baseline gadget...")
        self.gadget_definition = {}
        for lvl in sorted(self.nodes_by_level.keys()):
            for expr in self.nodes_by_level[lvl]:
                if self._is_and_node(str(expr)):
                    # Initialize all nodes as HPC3 (minimum latency, baseline randomness)
                    self.gadget_definition[expr] = {
                        "gadget_name": "hpc3",
                        "random_numbers": self.gadget_map["hpc3"]["randomness"],
                        "xor_consumer": None,
                    }
        print(f"[MRLC] Pre-initialized {len(self.gadget_definition)} nodes as HPC3")
        print(f"[MRLC] Baseline randomness: {len(self.gadget_definition) * self.gadget_map['hpc3']['randomness']} bits")
        print(f"[MRLC] Now pre-DP optimization can identify HPC2-feasible candidates...\n")
        
        # ===== CRITICAL: Step 2.5 - PRE-DP Asymmetric Optimization =====
        # This MUST run BEFORE DP to identify HPC2-feasible candidates
        # DP will then use bonus latency to convert these candidates + others
        print("="*80)
        print("[MRLC] Step 2.5: Pre-DP Asymmetric Gadget Optimization")
        print("[MRLC] Analyzing HPC3 nodes: which CAN be converted to HPC2/HPC2o?")
        print("[MRLC] DP will then decide which ones SHOULD be converted using bonus budget")
        print("="*80)
        if self.and_xor_tree is not None:
            try:
                from asymmetric_gadget_optimization import optimize_mrlc_with_asymmetric_gadgets
                print("[MRLC] Running asymmetric gadget optimization BEFORE DP...")
                print("[MRLC] This identifies structural constraints (which nodes CAN be HPC2)")
                print("[MRLC] Operating on pre-initialized HPC3 nodes...\n")
                self = optimize_mrlc_with_asymmetric_gadgets(self, self.and_xor_tree, debug=True)
                print("\n[MRLC] Pre-DP asymmetric optimization completed")
                
                # Check how many nodes were marked
                hpc2_count = sum(1 for info in self.gadget_definition.values()
                                if info.get("gadget_name") in ['hpc2', 'hpc2o', 'hpc2_swapped', 'hpc2o_swapped'])
                hpc3_count = sum(1 for info in self.gadget_definition.values()
                                if info.get("gadget_name") in ['hpc3', 'hpc3o'])
                print(f"[MRLC] Result: {hpc2_count} nodes marked as HPC2-feasible, {hpc3_count} remain as HPC3")
                print(f"[MRLC] These marks will guide DP's bonus budget allocation")
            except ImportError as e:
                print(f"[MRLC WARN] Could not import asymmetric_gadget_optimization: {e}")
                print(f"[MRLC INFO] Continuing without pre-DP optimization")
            except Exception as e:
                print(f"[MRLC WARN] Pre-DP optimization failed: {e}")
                print(f"[MRLC INFO] Continuing with all nodes as HPC3")
        else:
            print("[MRLC INFO] Skipping pre-DP optimization (and_xor_tree not available)")
            print("[MRLC INFO] Continuing with all nodes as HPC3")
        print("="*80 + "\n")
        
        # ===== CRITICAL: Step 2.75 - Store pre-DP optimization results =====
        # Save which nodes were marked as HPC2-feasible by pre-DP optimization
        # DP will use this information to guide its decisions
        print("[MRLC] Step 2.75: Storing pre-DP optimization marks...")
        self.hpc2_feasible_nodes = set()
        hpc2_count_after_preopt = 0
        for expr, info in self.gadget_definition.items():
            if info.get("gadget_name") in ['hpc2', 'hpc2o', 'hpc2_swapped', 'hpc2o_swapped']:
                self.hpc2_feasible_nodes.add(expr)
                hpc2_count_after_preopt += 1
        
        hpc3_count_after_preopt = len(self.gadget_definition) - hpc2_count_after_preopt
        
        # ===== CRITICAL: Track which LEVELS have pre-DP conversions =====
        # This is essential for reconstruction - levels with ALL nodes converted
        # by pre-DP should STAY as HPC2 in the final output
        self.levels_with_preopt_hpc2 = set()
        for lvl in sorted(self.nodes_by_level.keys()):
            nodes_in_level = [n for n in self.nodes_by_level[lvl] if self._is_and_node(str(n))]
            if not nodes_in_level:
                continue
            
            hpc2_in_level = sum(1 for n in nodes_in_level if n in self.hpc2_feasible_nodes)
            
            # If ALL nodes in this level are HPC2 by pre-DP, mark the level
            if hpc2_in_level == len(nodes_in_level) and hpc2_in_level > 0:
                self.levels_with_preopt_hpc2.add(lvl)
        
        print(f"[MRLC] After Pre-DP optimization:")
        print(f"[MRLC]   HPC2/HPC2o nodes: {hpc2_count_after_preopt} (ALREADY CONVERTED!)")
        print(f"[MRLC]   HPC3/HPC3o nodes: {hpc3_count_after_preopt} (REMAINING for DP)")
        print(f"[MRLC]   Levels with ALL nodes as HPC2: {sorted(self.levels_with_preopt_hpc2)}")
        print(f"[MRLC]   Total randomness after pre-opt: {hpc2_count_after_preopt * 1 + hpc3_count_after_preopt * 2} bits")
        print(f"[MRLC] DP will now convert REMAINING HPC3 nodes using bonus latency\n")
        
        # Step 3: Initialize 3D DP table
        self.initialise_dp(node_per_level=None, gadget_assigned=None)
        
        # Step 4: Run DP iterations
        self.dp_iteration()
        
        # Step 5: Reconstruct and assign gadgets
        self.choose_gadgets_for_each_level()
        
        # Step 6: Generate gadget definitions
        self.nodes_gadget_assignment()
        print(f"[MRLC RESULT] Total randomness: {self.total_randomness_after_mrlc}")
        print(f"[MRLC RESULT] Total latency   : {self.total_latency_after_mrlc}")
        print(f"\n[MRLC SUCCESS] MRLC-DP completed successfully")
        return self.gadget_definition, self.total_latency_after_mrlc

    def _filter_to_and_only_levels(self):
        """
        Filter nodes_by_level to only include AND nodes.
        This is critical because:
        - AND nodes need gadgets (consume latency/randomness)
        - XOR nodes are free (no gadgets, no cost)
        - DP algorithm works on AND-only levels
        
        Converts from mixed levels to AND-only levels:
        Input:  {1: [XOR], 2: [XOR], 3: [AND], 4: [XOR], 5: [AND]}
        Output: {1: [AND], 2: [AND]}
        """
        print(f"\n[MRLC INFO] Filtering to AND-only levels...")
        print(f"[DEBUG] Initial levels (mixed XOR+AND): {len(self.nodes_by_level)} levels")
        
        and_only_levels = {}
        and_level_counter = 0
        total_and_nodes = 0
        
        for level in sorted(self.nodes_by_level.keys()):
            nodes_in_level = self.nodes_by_level[level]
            
            # Check if this level has any AND nodes
            and_nodes = [n for n in nodes_in_level if self._is_and_node(str(n))]
            
            if and_nodes:
                and_level_counter += 1
                and_only_levels[and_level_counter] = nodes_in_level  # Keep all nodes for now
                total_and_nodes += len(and_nodes)
                
                if self.debug:
                    print(f"  Level {level} → AND-Level {and_level_counter}: {len(and_nodes)} AND nodes, {len(nodes_in_level) - len(and_nodes)} XOR nodes")
        
        # Update nodes_by_level to AND-only mapping
        self.nodes_by_level = and_only_levels
        self.DAG_levels = len(and_only_levels)
        
        print(f"[MRLC INFO] Filtered result:")
        print(f"  Original levels: {len(self.nodes_by_level)} (before filter)")
        print(f"  AND-only levels: {self.DAG_levels}")
        print(f"  Total AND nodes: {total_and_nodes}")

    def initialise_dp(self, node_per_level, gadget_assigned):
        """
        Initialize the 3D DP table:
        dp[i][j][k] = minimum randomness for levels 0..i, using j bonus latency, with comar state k
        
        i: 0 to L (number of levels)
        j: 0 to bonus_latency (latency budget spent)
        k: 0 or 1 (comar_used state)
        """
        infinity = float('inf')
        L = self.DAG_levels
        
        print(f"\n[MRLC INFO] Initializing 3D DP Table:")
        print(f"  Dimensions: dp[{L + 1}][{self.bonus_latency + 1}][2]")
        print(f"  Total size: {(L + 1) * (self.bonus_latency + 1) * 2} entries")
        
        # Create 3D DP table: dp[level][bonus_spent][comar_state]
        self.dp = [
            [
                [infinity for _ in range(2)]  # comar_state: 0 or 1
                for _ in range(self.bonus_latency + 1)  # bonus_spent: 0 to bonus_latency
            ]
            for _ in range(L + 1)  # levels: 0 to L
        ]
        
        # Create 3D gadget assignment tracking table
        self.gadget_assigned = [
            [
                [None for _ in range(2)]  # comar_state: 0 or 1
                for _ in range(self.bonus_latency + 1)  # bonus_spent: 0 to bonus_latency
            ]
            for _ in range(L + 1)  # levels: 0 to L
        ]
        
        # Base case: 0 levels, 0 bonus spent, comar NOT used, 0 randomness
        self.dp[0][0][0] = 0.0
        
        print(f"[MRLC INFO] DP table initialized successfully")
        self._display_3d_dp_table(self.dp, L, self.bonus_latency, "Initial DP Table (3D)")

    def dp_iteration(self):
        """
        Fill the 3D DP table with pattern-aware gadget selection
        Only AND nodes consume gadgets / randomness / latency.
        XOR-only levels are treated as 0-cost (no bonus spending).
        
        CRITICAL: Uses pre-DP optimization marks to guide decisions!
        - hpc2_feasible_nodes: Set of nodes marked as HPC2-feasible by pre-DP opt
        - DP prioritizes these nodes for HPC2 conversion
        - Ensures pre-DP structural analysis is used by DP!
        """
        initial_latency = self.min_latency_gadget[1]["latency"]
        L = self.DAG_levels
        
        # Get HPC2-feasible nodes from pre-DP optimization
        hpc2_feasible = getattr(self, 'hpc2_feasible_nodes', set())
        print(f"\n[MRLC DP] Pre-DP optimization already converted {len(hpc2_feasible)} nodes to HPC2")
        print(f"[MRLC DP] Now DP will convert REMAINING HPC3 nodes using bonus latency\n")
        
        if self.debug:
            print(f"\n--- Starting 3D DP Table Filling Iterations ---")
        
        for i in range(1, L + 1):
            nodes_in_level = list(self.nodes_by_level.get(i, []))
            and_nodes_in_level = [n for n in nodes_in_level if self._is_and_node(n)]
            and_count = len(and_nodes_in_level)
            
            # ===== CRITICAL: Check which nodes are STILL HPC3 (not converted by pre-DP) =====
            hpc3_nodes_in_level = [n for n in and_nodes_in_level if n not in hpc2_feasible]
            hpc3_count = len(hpc3_nodes_in_level)
            
            # ===== CRITICAL: Calculate pre-DP baseline for this level =====
            # Nodes already converted by pre-DP contribute fixed randomness
            hpc2_by_preopt_count = and_count - hpc3_count
            preopt_baseline = hpc2_by_preopt_count * 1.0  # HPC2 nodes: 1 bit each
            
            if self.debug:
                print(f"\n======== Processing Level {i} ========")
                print(f"  Total nodes: {len(nodes_in_level)}, AND nodes: {and_count}")
                print(f"  HPC3 remaining: {hpc3_count}, HPC2 already converted: {hpc2_by_preopt_count}")
                print(f"  Pre-DP baseline for this level: {preopt_baseline}")

            if and_count == 0:
                # carry-over for XOR-only levels (unchanged)
                for prev_j_spent in range(self.bonus_latency + 1):
                    for prev_comar_used_state in [0, 1]:
                        self.dp[i][prev_j_spent][prev_comar_used_state] = \
                            self.dp[i-1][prev_j_spent][prev_comar_used_state]
                        self.gadget_assigned[i][prev_j_spent][prev_comar_used_state] = \
                            self.gadget_assigned[i-1][prev_j_spent][prev_comar_used_state]
                continue

            # ===== CRITICAL: Check if this level has marked nodes =====
            marked_in_level = [n for n in and_nodes_in_level if n in hpc2_feasible]
            if marked_in_level and self.debug:
                print(f"  [PRE-DP MARK] {len(marked_in_level)}/{and_count} nodes marked as HPC2-feasible")
                print(f"  [PRE-DP MARK] This level is a CANDIDATE for HPC2 replacement (saves {len(marked_in_level)} randomness)")

            for prev_j_spent in range(self.bonus_latency + 1):
                for prev_comar_used_state in [0, 1]:
                    if self.dp[i-1][prev_j_spent][prev_comar_used_state] == float('inf'):
                        continue

                    if self.debug:
                        print(f"  Considering: dp[{i-1}][{prev_j_spent}][{prev_comar_used_state}] = "
                              f"{self.dp[i-1][prev_j_spent][prev_comar_used_state]:.2f}")

                    patterns_in_level = {self.node_pattern.get(node, 'pure_and')
                                 for node in and_nodes_in_level}
                    
                    if self.debug:
                        print(f"  Level {i}: AND count={and_count}, Patterns detected={patterns_in_level}")

                    if len(patterns_in_level) == 1:
                        pattern = list(patterns_in_level)[0]
                        available_gadgets = self._get_gadgets_for_pattern(pattern, self.matching_gadgets)
                    else:
                        available_gadgets = self.matching_gadgets  # mixed level → safest choice

                    # ===== CRITICAL: DP chooses gadgets to minimize randomness =====
                    # HPC2: randomness=1, latency cost (uses bonus budget)
                    # HPC3: randomness=2, no latency cost (free)
                    # 
                    # Strategy: DP will pick HPC2 when bonus latency available
                    # Because: HPC2 saves randomness (2-1=1 bit per node)
                    #
                    # Pre-DP marks tell us WHICH levels CAN be HPC2
                    # DP decides WHETHER to use bonus budget on those levels
                    
                    for gadget_name, gadget_spec in available_gadgets.items():
                        # Skip optimized gadgets unless the level is purely xor_and
                        if gadget_name in ['hpc2o', 'hpc3o'] and 'xor_and' not in patterns_in_level:
                            continue
                        if self.debug and gadget_name in ['hpc2o', 'hpc3o']:
                            print(f"      >>> Optimized gadget '{gadget_name}' is available for level {i} "
                                  f"(xor_and pattern detected)")

                        cost = gadget_spec["latency"] - initial_latency
                        randomness_base = gadget_spec["randomness"]
                        j_spent = prev_j_spent + cost

                        if j_spent > self.bonus_latency:
                            continue

                        new_comar_state = prev_comar_used_state
                        if gadget_name == 'comar' and prev_comar_used_state == 0:
                            randomness_added = 6.0
                            new_comar_state = 1
                        else:
                            # ===== CRITICAL FIX: Only HPC3 nodes need randomness! =====
                            # Pre-DP already converted some nodes to HPC2 (randomness=1 each)
                            # Those are ALREADY accounted for and WON'T change
                            # DP only evaluates the REMAINING HPC3 nodes
                            # 
                            # If gadget_name is HPC2:
                            #   We're choosing to convert all REMAINING HPC3 nodes to HPC2
                            #   Randomness = hpc3_count × 1 (each remaining HPC3 becomes HPC2)
                            #
                            # If gadget_name is HPC3:
                            #   We're keeping all REMAINING HPC3 nodes as HPC3
                            #   Randomness = hpc3_count × 2 (each stays as HPC3)
                            
                            if gadget_name == 'hpc2':
                                # Converting remaining HPC3 to HPC2
                                randomness_added = float(hpc3_count) * randomness_base
                            else:
                                # Keeping remaining HPC3 as HPC3 (or choosing other gadgets)
                                randomness_added = float(hpc3_count) * randomness_base

                        total_randomness = self.dp[i-1][prev_j_spent][prev_comar_used_state] + randomness_added
                        
                        # ===== CRITICAL: Add pre-DP baseline to show TOTAL randomness =====
                        # Pre-DP already converted some nodes to HPC2 (fixed cost)
                        # Add this to the DP's decision to get the TRUE total randomness
                        #
                        # KEY INSIGHT: DP needs to see the FULL picture!
                        # Example Level 4: Pre-DP converted 18→HPC2 (18 bits fixed)
                        #           If DP chooses HPC3 for 0 remaining nodes: 0 + 18 = 18 bits
                        #           If DP chooses HPC2 for 0 remaining nodes: 0 + 18 = 18 bits
                        #           Both equal! DP will pick first option (HPC3 has no cost)
                        #
                        # But for Level 1: Pre-DP converted 0 nodes (0 bits fixed)
                        #           If DP chooses HPC3 for 9 remaining: 9×2 + 0 = 18 bits
                        #           If DP chooses HPC2 for 9 remaining: 9×1 + 0 = 9 bits
                        #           HPC2 wins! (9 < 18, saves 9 bits)
                        #
                        # This ensures DP picks the level with most HPC3 nodes!
                        total_randomness += preopt_baseline

                        # ===== DP EVALUATION: Simple cost-benefit =====
                        # HPC2: costs 1 bonus latency, saves 1 randomness (2→1 per node)
                        # HPC3: costs 0 bonus latency, but uses 2 randomness per node
                        # DP will choose HPC2 when bonus latency is available (saves randomness!)
                        # Pre-DP marked nodes guide DP to pick HPC2 for those levels

                        if total_randomness < self.dp[i][j_spent][new_comar_state]:
                            self.dp[i][j_spent][new_comar_state] = total_randomness
                            self.gadget_assigned[i][j_spent][new_comar_state] = \
                                (prev_j_spent, gadget_name, prev_comar_used_state)
                            
                            if self.debug and gadget_name == 'hpc2' and len(marked_in_level) > 0:
                                print(f"      [CHOICE] Level {i}: Choosing HPC2 (saves {len(marked_in_level)} randomness with {len(marked_in_level)} marked nodes)")

        if self.debug:
            print(f"\n--- DP Table Filling Complete ---")

    def choose_gadgets_for_each_level(self):
        """
        Backtrack through the DP table to determine which gadget was selected for each level.
        Sets self.chosen_gadget_for_levels list.
        
        CRITICAL FIX: Use FULL budget (bonus_latency), not the minimum across all budgets!
        """
        L = self.DAG_levels
        
        # Initialize the list to store the chosen gadget for each level
        # Index 0 is unused (levels are 1-based), or adjust accordingly
        self.chosen_gadget_for_levels = [None] * L
        
        # Calculate final state to start backtracking
        min_randomness = float('inf')
        final_bonus_spent = -1
        final_comar_state = -1 # 0 or 1
        
        # === BUG FIX: Find the best randomness using the FULL budget ===
        # Search at j = bonus_latency (use all available budget to minimize randomness)
        # Try both comar states at the maximum budget level
        for k in [0, 1]:
            if self.dp[L][self.bonus_latency][k] < min_randomness:
                min_randomness = self.dp[L][self.bonus_latency][k]
                final_bonus_spent = self.bonus_latency
                final_comar_state = k
        
        # If no solution at full budget, search backwards for any valid state
        if min_randomness == float('inf'):
            print("[MRLC WARN] No solution found at full budget. Searching for any valid solution...")
            for j in range(self.bonus_latency, -1, -1):
                for k in [0, 1]:
                    if self.dp[L][j][k] < min_randomness:
                        min_randomness = self.dp[L][j][k]
                        final_bonus_spent = j
                        final_comar_state = k
                if min_randomness < float('inf'):
                    break

        if min_randomness == float('inf'):
            print("[MRLC ERROR] No valid path found in DP table.")
            # Fallback: assign initial gadget to all levels
            default_gadget = self.min_latency_gadget[0]
            self.chosen_gadget_for_levels = [default_gadget] * L
            return

        print(f"[MRLC INFO] Optimal randomness: {min_randomness} with bonus spent: {final_bonus_spent}/{self.bonus_latency}")

        # Backtrack
        current_j = final_bonus_spent
        current_k = final_comar_state
        
        for i in range(L, 0, -1):
            # Retrieve assignment decision
            assignment = self.gadget_assigned[i][current_j][current_k]
            
            if assignment is not None:
                prev_j, gadget_name, prev_k = assignment
                self.chosen_gadget_for_levels[i-1] = gadget_name
                current_j = prev_j
                current_k = prev_k
            else:
                 # Should not happen if DP path is valid
                print(f"[MRLC WARN] No assignment record for Level {i}. Using heuristic.")
                # Basic fallback: try to infer zero-cost transition
                self.chosen_gadget_for_levels[i-1] = self.min_latency_gadget[0]

        print(f"[MRLC INFO] Reconstructed gadget path: {self.chosen_gadget_for_levels}")

    def nodes_gadget_assignment(self):
        print("\n=== GADGET ASSIGNMENT WITH OPTIMIZATION PRESERVATION ===")
        if not hasattr(self, 'chosen_gadget_for_levels') or self.chosen_gadget_for_levels is None:
            self.chosen_gadget_for_levels = ['hpc3'] * self.DAG_levels

        # Normalize node_pattern: str(expr) -> (pattern, xor_consumer)
        normalized_pattern = {str(k).strip(): v for k, v in self.node_pattern.items()}
        
        # ===== CRITICAL FIX: Preserve optimized gadgets from HPC2 optimization pass =====
        # If gadget_definition already has entries (from optimization), keep them!
        # Only fill in missing nodes.
        preserved_optimizations = getattr(self, 'gadget_definition', {})
        print(f"[PRESERVE] Found {len(preserved_optimizations)} existing gadget assignments")
        
        # Count optimized gadgets BEFORE clearing
        hpc2_count_before = sum(1 for info in preserved_optimizations.values()
                                if info.get("gadget_name") in ['hpc2', 'hpc2o', 'hpc2_swapped', 'hpc2o_swapped'])
        print(f"[PRESERVE] HPC2/HPC2o count before clearing: {hpc2_count_before}")
        
        self.gadget_definition = {}
        upgraded = 0

        for lvl, nodes in self.nodes_by_level.items():
            base = self.chosen_gadget_for_levels[lvl-1] if lvl-1 < len(self.chosen_gadget_for_levels) else 'hpc3'
            
            # ===== CRITICAL: Preserve pre-DP level conversions =====
            # If Pre-DP marked ALL nodes in this level as HPC2, keep it as HPC2
            # regardless of what DP chose!
            # This ensures we don't lose pre-DP optimization
            levels_with_preopt = getattr(self, 'levels_with_preopt_hpc2', set())
            if lvl in levels_with_preopt:
                # All nodes in this level were converted by pre-DP, keep as HPC2
                base = 'hpc2'
                if self.debug:
                    print(f"[PREOPT-LEVEL] Level {lvl}: Preserving pre-DP conversion to HPC2")
            
            for expr in nodes:
                if not self._is_and_node(str(expr)):
                    continue

                key = str(expr).strip()
                
                # ===== CRITICAL: DP DECISION OVERRIDES PRE-DP! =====
                # Pre-DP marked nodes as HPC2-feasible, but DP made the FINAL decision
                # about which gadget to assign to each LEVEL
                # We apply DP's level-wise decision to ALL nodes in that level
                # regardless of pre-DP markings
                #
                # Example:
                #   Pre-DP: Level 3 has all 4 nodes marked as HPC2-feasible
                #   DP decision: Level 3 should be HPC3 (no bonus left)
                #   Result: Override pre-DP, assign all Level 3 nodes as HPC3
                
                pattern_info = normalized_pattern.get(key, ("pure_and", None, None))
                if isinstance(pattern_info, tuple) and len(pattern_info) == 3:
                    pattern, xor_consumer, xor_other_operand = pattern_info
                elif isinstance(pattern_info, tuple):
                    pattern, xor_consumer = pattern_info
                    xor_other_operand = None
                else:
                    pattern, xor_consumer, xor_other_operand = pattern_info, None, None

                # Start with DP's choice for this level
                gadget = base

                # ===== PRESERVE PRE-DP SWAPPED VARIANT =====
                # The pre-DP asymmetric optimizer may have assigned hpc2_swapped to this
                # specific node (based on its operand depths).  nodes_gadget_assignment()
                # only tracks the level-wise decision (hpc2 vs hpc3); the per-node
                # swap direction must be recovered from preserved_optimizations.
                preopt_gadget = preserved_optimizations.get(expr, {}).get("gadget_name", "")
                if preopt_gadget in ('hpc2_swapped', 'hpc2o_swapped') and base == 'hpc2':
                    gadget = 'hpc2_swapped'

                # ===== SMART OPTIMIZATION: Apply optimized variants if cost-neutral =====
                # Key insight: HPC2o and HPC3o have SAME cost (latency/randomness) as HPC2/HPC3
                # But are optimized for XOR_AND patterns
                # So we can safely upgrade without violating DP's budget!

                if pattern == 'xor_and':
                    # Try to find cost-neutral upgrade
                    optimized_variant = None

                    if gadget == 'hpc3' and 'hpc3o' in self.gadget_map:
                        # HPC3 → HPC3o upgrade
                        if self.gadget_map['hpc3o']['randomness'] <= self.gadget_map['hpc3']['randomness']:
                            optimized_variant = 'hpc3o'
                            if self.debug:
                                print(f"[UPGRADE] {key[:50]:50s} HPC3→HPC3o (cost-neutral)")

                    elif gadget == 'hpc2' and 'hpc2o' in self.gadget_map:
                        # HPC2 → HPC2o upgrade
                        if self.gadget_map['hpc2o']['randomness'] <= self.gadget_map['hpc2']['randomness']:
                            optimized_variant = 'hpc2o'
                            if self.debug:
                                print(f"[UPGRADE] {key[:50]:50s} HPC2→HPC2o (cost-neutral)")

                    elif gadget == 'hpc2_swapped' and 'hpc2o_swapped' in self.gadget_map:
                        # HPC2_swapped → HPC2o_swapped upgrade (same swap direction, xor-optimised)
                        if self.gadget_map['hpc2o_swapped']['randomness'] <= self.gadget_map['hpc2_swapped']['randomness']:
                            optimized_variant = 'hpc2o_swapped'
                            if self.debug:
                                print(f"[UPGRADE] {key[:50]:50s} HPC2_swapped→HPC2o_swapped (cost-neutral)")

                    if optimized_variant:
                        gadget = optimized_variant
                        upgraded += 1

                self.gadget_definition[expr] = {
                    "gadget_name": gadget,
                    "random_numbers": self.gadget_map[gadget]["randomness"],
                    "xor_consumer": xor_consumer,
                    "xor_other_operand": xor_other_operand,
                }
        
        print(f"[PRESERVE] Total upgraded to xor_and optimized: {upgraded}")
        
        # Verify HPC2 count AFTER
        hpc2_count_after = sum(1 for info in self.gadget_definition.values()
                               if info.get("gadget_name") in ['hpc2', 'hpc2o', 'hpc2_swapped', 'hpc2o_swapped'])
        print(f"[PRESERVE] HPC2/HPC2o count after assignment: {hpc2_count_after}")
        
        # ===== BUILD GADGET DEFINITIONS =====
        # This MUST happen AFTER we assign gadgets, and it MUST include all gadgets used!
        print(f"\n[DEFINITIONS] Building unique gadget definitions...")
        print(f"[DEFINITIONS] Analyzing {len(self.gadget_definition)} gadget assignments...")
        
        # Count what gadgets are actually used
        used_gadgets = {}
        for expr, info in self.gadget_definition.items():
            gname = info.get("gadget_name", "unknown").lower()
            used_gadgets[gname] = used_gadgets.get(gname, 0) + 1
        
        print(f"[DEFINITIONS] Gadgets used in assignments: {used_gadgets}")

        print(f"[SUMMARY] Upgraded {upgraded} nodes to xor_and optimized variants (should match xor_and count)")

        # Build definitions
        self.unique_gadgets_definition = {}
        gadget_classes = {'hpc1': HPC1, 'hpc2': HPC2, 'hpc3': HPC3,
                          'hpc2o': HPC2o, 'hpc3o': HPC3o, 'comar': COMAR, 'domand': Domand,
                          'hpc2_swapped': HPC2Swapped, 'hpc2o_swapped': HPC2oSwapped}

        for expr, info in self.gadget_definition.items():
            gname = info["gadget_name"].lower()
            
            # Skip if already has func_name (from optimization pass)
            if "func_name" in info and info["func_name"]:
                if gname not in self.unique_gadgets_definition and gname in gadget_classes:
                    obj = gadget_classes[gname](d=self.d) if gname != 'comar' else COMAR()
                    self.unique_gadgets_definition[gname] = obj.generate_multiply_function()
                continue
            
            if gname not in self.unique_gadgets_definition and gname in gadget_classes:
                obj = gadget_classes[gname](d=self.d) if gname != 'comar' else COMAR()
                self.unique_gadgets_definition[gname] = obj.generate_multiply_function()
                func_name = obj.get_function_name()
                for e, spec in self.gadget_definition.items():
                    if spec["gadget_name"].lower() == gname:
                        spec["func_name"] = func_name

        # COMAR randomness is shared across all instances — count it only once.
        comar_used = any(
            info["gadget_name"].lower() == "comar"
            for info in self.gadget_definition.values()
        )
        self.total_randomness_after_mrlc = sum(
            info["random_numbers"]
            for info in self.gadget_definition.values()
            if info["gadget_name"].lower() != "comar"
        ) + (self.gadget_map["comar"]["randomness"] if comar_used and "comar" in self.gadget_map else 0)
        self.total_latency_after_mrlc = self.total_initial_latency + getattr(self, 'bonus_latency', 0)
        self.total_area_after_mrlc = sum(self.gadget_map[info["gadget_name"]]["area"] for info in self.gadget_definition.values())

        table = [(getattr(self.and_tree, 'node_map', {}).get(e, '?'), str(e)[:50], info["gadget_name"])
                 for e, info in self.gadget_definition.items()]
        print(tabulate(table, headers=["Gate", "Expression", "Gadget"], tablefmt="grid"))        
        print(f"\n[MRLC RESULT] Randomness: {self.total_randomness_after_mrlc} | Latency: {self.total_latency_after_mrlc}")
    
    def get_gadget_definition(self):
        """Return gadget_definition dict for use by ShareTransformer
        
        Converts expression object keys to strings for reliable matching in ShareTransformer
        """
        print(f"\n" + "="*80)
        print("MRLC: GET_GADGET_DEFINITION()")
        print("="*80)
        print(f"[INFO] Preparing gadget_definition with {len(self.gadget_definition)} entries")
        
        gadget_counts = {}
        hpc2_gates = []
        
        # Convert keys from expression objects to strings for ShareTransformer
        string_key_gadget_def = {}
        for expr, info in self.gadget_definition.items():
            gname = info.get("gadget_name", "unknown")
            gadget_counts[gname] = gadget_counts.get(gname, 0) + 1
            
            # Track HPC2/HPC2o gates (including swapped variants)
            if gname in ['hpc2', 'hpc2o', 'hpc2_swapped', 'hpc2o_swapped']:
                hpc2_gates.append((str(expr).strip(), gname))
            
            # Key can be an expression object or string
            key_str = str(expr).strip() if not isinstance(expr, str) else expr
            string_key_gadget_def[key_str] = info
        
        print(f"\n[GADGET BREAKDOWN]")
        for gname in sorted(gadget_counts.keys()):
            count = gadget_counts[gname]
            print(f"  {gname:8s}: {count:3d} gates")
        
        if hpc2_gates:
            print(f"\n[HPC2/HPC2o OPTIMIZED GATES] ({len(hpc2_gates)} gates)")
            for gate_expr, gate_type in hpc2_gates[:5]:  # Print first 5
                print(f"  {gate_expr[:60]:60s} → {gate_type}")
            if len(hpc2_gates) > 5:
                print(f"  ... and {len(hpc2_gates) - 5} more")
        
        print("="*80 + "\n")
        
        return string_key_gadget_def
    
    def get_unique_gadgets_definition(self):
        """
        Return unique_gadgets_definition for all gadgets used in gadget_definition,
        plus the full standard gadget set so the output C file is always complete.

        Fills in any gadget whose definition is absent — whether it was added by
        the asymmetric optimisation pass AFTER nodes_gadget_assignment() ran, or
        was simply never assigned to a node in this particular circuit.
        """
        print("[MRLC] get_unique_gadgets_definition() called")

        # Collect gadgets actually used in this circuit
        gadget_counts = {}
        for info in self.gadget_definition.values():
            gadget_name = info.get("gadget_name")
            if gadget_name:
                gadget_counts[gadget_name] = gadget_counts.get(gadget_name, 0) + 1

        print(f"[MRLC] Gadgets actually used in gadget_definition: {gadget_counts}")
        print(f"[MRLC] Currently in unique_gadgets_definition: {list(self.unique_gadgets_definition.keys())}")

        # Always ensure the full standard set is available (used + unused)
        standard_gadgets = {
            'hpc2', 'hpc2o', 'hpc3', 'hpc3o',
            'hpc2_swapped', 'hpc2o_swapped',
        }
        needed = (set(gadget_counts.keys()) | standard_gadgets) - set(self.unique_gadgets_definition.keys())

        if needed:
            print(f"\n[MRLC] Generating definitions for: {sorted(needed)}")
            for gadget_name in sorted(needed):
                func_def = self._generate_gadget_definition(gadget_name)
                if func_def:
                    self.unique_gadgets_definition[gadget_name] = func_def
                    print(f"  [OK] {gadget_name}")
                else:
                    print(f"  [FAILED] {gadget_name}")

        print(f"\n[MRLC] Final unique_gadgets_definition: {sorted(self.unique_gadgets_definition.keys())}")
        return self.unique_gadgets_definition
    
    def _generate_gadget_definition(self, gadget_name):
        """
        Generate C function definition for a gadget by name.
        """
        print(f"    [_generate_gadget_definition] Generating for: {gadget_name}")
        
        # Map gadget names to gadget classes
        gadget_class_map = {
            'hpc1': HPC1,
            'hpc2': HPC2,
            'hpc3': HPC3,
            'hpc2o': HPC2o,
            'hpc3o': HPC3o,
            'hpc2_swapped': HPC2Swapped,
            'hpc2o_swapped': HPC2oSwapped,
        }
        
        if gadget_name not in gadget_class_map:
            print(f"    [ERROR] Unknown gadget: {gadget_name}")
            return None
        
        GadgetClass = gadget_class_map[gadget_name]
        
        try:
            gadget_obj = GadgetClass(d=self.d)
            print(f"    [_generate_gadget_definition] Instantiated {gadget_name} with d={self.d}")
            
            # Get the C code definition using generate_multiply_function
            func_def = gadget_obj.generate_multiply_function()
            if not func_def or len(func_def.strip()) == 0:
                print(f"    [ERROR] generate_multiply_function() returned empty for {gadget_name}")
                return None
                
            print(f"    [SUCCESS] Generated C code for {gadget_name}, length: {len(func_def)} chars")
            return func_def
        except AttributeError as e:
            print(f"    [ERROR] AttributeError: {e}")
            print(f"    [RETRY] Trying alternative method...")
            try:
                gadget_obj = GadgetClass(d=self.d)
                # Try get_c_code if it exists
                if hasattr(gadget_obj, 'get_c_code'):
                    func_def = gadget_obj.get_c_code()
                    print(f"    [SUCCESS] Generated C code using get_c_code(), length: {len(func_def)} chars")
                    return func_def
            except Exception as e2:
                print(f"    [ERROR] Alternative method also failed: {e2}")
            return None
        except Exception as e:
            print(f"    [ERROR] Exception generating {gadget_name}: {e}")
            import traceback
            traceback.print_exc()
            return None
        

    def _analyze_and_xor_tree_for_patterns(self):
        """
        Detect AND-XOR patterns using precomputed fanin/fanout from and_xor_tree.

        STRATEGY:
        - and_xor_tree contains both AND and XOR nodes with full circuit structure
        - Use the real graph (not string search) for exact fan-out detection
        - Rule 1: fanout count == 1
        - Rule 2: the single fanout node is a XOR node
        - Rule 3: the XOR has not been claimed by any previous AND
                  (we keep a claimed_xor flag per XOR — first AND wins)
        """
        print("\n--- Analyzing AND-XOR Tree for Patterns (Fan-out based) ---")
        self.node_pattern = {}

        # Fallback if and_xor_tree is not available
        if self.and_xor_tree is None or not hasattr(self.and_xor_tree, 'graph'):
            print("[WARN] and_xor_tree or its graph not available — falling back to old level-based analysis")
            self._analyze_and_tree_for_patterns()  # old method (if you still keep it)
            return

        and_count = 0
        xor_and_count = 0
        multi_fanout_count = 0
        non_xor_consumer_count = 0

        graph = self.and_xor_tree.graph

        # ── Step 1: Precompute exact fanout and fanin for every node ──
        fanout = {}   # node_str → [successor_str, ...]
        fanin  = {}   # node_str → [predecessor_str, ...]

        for node_idx in graph.node_indices():
            node_str = str(graph[node_idx])
            fanout[node_str] = [str(s) for s in graph.successors(node_idx)]
            fanin[node_str]  = [str(p) for p in graph.predecessors(node_idx)]

        # ── Build var → effective AND level map ──────────────────────────────
        # For each variable, compute the maximum AND-tree level in its transitive
        # fanin. Used in Rule 4 to detect when xor_other_operand (w) is at the
        # same level as the AND gate — using hpc*o then serializes parallel work.
        and_output_to_level = {}
        for lvl, nodes in self.nodes_by_level.items():
            for n in nodes:
                out_var = self._extract_lhs_var(str(n))
                if out_var:
                    and_output_to_level[out_var] = lvl

        var_effective_level = {}

        def _effective_level(var_name):
            if var_name in var_effective_level:
                return var_effective_level[var_name]
            if var_name in and_output_to_level:
                lv = and_output_to_level[var_name]
                var_effective_level[var_name] = lv
                return lv
            best = 0
            for node_idx in graph.node_indices():
                expr_str = str(graph[node_idx])
                if '=' in expr_str:
                    lhs = expr_str.split('=')[0].strip()
                    if lhs == var_name:
                        preds = [str(p) for p in graph.predecessors(node_idx)]
                        for pred in preds:
                            pred_lhs = pred.split('=')[0].strip() if '=' in pred else pred.strip()
                            best = max(best, _effective_level(pred_lhs))
                        break
            var_effective_level[var_name] = best
            return best

        # ── Rule 3 tracking: which XORs have already been claimed by an AND ──
        claimed_xor = set()   # stores consumer_str of XORs already marked

        # ── Step 2: Classify each AND node from the and_tree ──
        for lvl in sorted(self.nodes_by_level.keys()):
            for node_expr in self.nodes_by_level[lvl]:
                node_str = str(node_expr)
                if not self._is_and_node(node_str):
                    continue

                and_count += 1
                output_var = self._extract_lhs_var(node_expr)

                if not output_var or node_str not in fanout:
                    self.node_pattern[node_expr] = ("pure_and", None)
                    if getattr(self, 'debug', True):
                        print(f"  [NO CONSUMER] {node_expr} has NO consumers")
                    continue

                successors = fanout[node_str]

                # Rule 1: exactly one fanout
                if len(successors) == 0:
                    self.node_pattern[node_expr] = ("pure_and", None)
                    if getattr(self, 'debug', True):
                        print(f"  [NO CONSUMER] {node_expr} has NO consumers")
                    continue

                elif len(successors) > 1:
                    self.node_pattern[node_expr] = ("pure_and", None)
                    multi_fanout_count += 1
                    if getattr(self, 'debug', True):
                        consumers_str = ", ".join(successors)
                        print(f"  [MULTI-FANOUT] {node_expr}")
                        print(f"               has {len(successors)} consumers: {consumers_str}")
                        print(f"               → CANNOT use HPC2o/HPC3o (needs exclusive XOR consumer)")
                    continue

                # Exactly one consumer
                consumer_str = successors[0]

                # Rule 2: that fanout must be a XOR node
                if not self._is_xor_node(consumer_str):
                    self.node_pattern[node_expr] = ("pure_and", None)
                    non_xor_consumer_count += 1
                    if getattr(self, 'debug', True):
                        print(f"  [SINGLE NON-XOR] {node_expr}")
                        print(f"                 → single consumer is NOT XOR: {consumer_str}")
                        print(f"                 → CANNOT use HPC2o/HPC3o (requires XOR consumer)")
                    continue

                # === Rule 3: XOR not already claimed by another AND ===
                if consumer_str in claimed_xor:
                    self.node_pattern[node_expr] = ("pure_and", None)
                    multi_fanout_count += 1
                    if getattr(self, 'debug', True):
                        print(f"  [XOR ALREADY CLAIMED] {node_expr} → {consumer_str}")
                        print(f"                        → XOR was already marked by another AND")
                        print(f"                        → This AND treated as pure_and")
                    continue

                # All rules passed so far → compute xor_other_operand
                consumer_lhs      = self._extract_lhs_var(consumer_str)
                xor_other_operand = self._extract_xor_other_operand(consumer_str, output_var)

                # === Rule 4: w must arrive before this AND gate level ===
                # If w's effective level >= current level, the two gates that
                # were computed in parallel would now run serially → latency grows.
                if xor_other_operand:
                    w_level = _effective_level(xor_other_operand)
                    if w_level >= lvl:
                        self.node_pattern[node_expr] = ("pure_and", None)
                        if getattr(self, 'debug', True):
                            print(f"  [W-LATE] {node_expr}")
                            print(f"           xor_other_operand='{xor_other_operand}' effective level {w_level} >= current level {lvl}")
                            print(f"           → using hpc*o would serialize parallel AND gates → keep pure_and")
                        continue

                # All rules passed → mark as xor_and and claim the XOR
                claimed_xor.add(consumer_str)
                self.node_pattern[node_expr] = ("xor_and", consumer_lhs, xor_other_operand)
                xor_and_count += 1
                if getattr(self, 'debug', True):
                    print(f"  [XOR PATTERN] {node_expr}")
                    print(f"               → XOR output: {consumer_lhs}, XOR other operand: {xor_other_operand} (level {_effective_level(xor_other_operand) if xor_other_operand else 'N/A'} < {lvl}) ✓")
                    print(f"               → ELIGIBLE for HPC2o/HPC3o (XOR claimed)")

        print(f"\n[MLRC INFO] Pattern analysis complete (using and_xor_tree graph):")
        print(f"  Total AND nodes                          : {and_count}")
        print(f"  ✅ XOR_AND patterns (HPC2o/HPC3o eligible): {xor_and_count}")
        print(f"  ❌ Pure AND (multiple fan-outs)         : {multi_fanout_count}")
        print(f"  ❌ Pure AND (single non-XOR consumer)   : {non_xor_consumer_count}")
        print(f"  ❌ Pure AND (other)                     : {and_count - xor_and_count - multi_fanout_count - non_xor_consumer_count}")
        
    def _analyze_and_tree_for_patterns(self):
        """Detect XOR+AND patterns and record their XOR consumers for hpc2o/hpc3o."""
        print("\n--- Analyzing AND Tree for XOR+AND Patterns (Level-based) ---")
        self.node_pattern = {}

        and_count = 0
        xor_and_count = 0

        for lvl in sorted(self.nodes_by_level.keys()):
            for node_expr in self.nodes_by_level[lvl]:
                node_str = str(node_expr)
                if not self._is_and_node(node_str):
                    continue

                and_count += 1
                # default: pure AND, no XOR consumer
                self.node_pattern[node_expr] = ("pure_and", None)

                # intra-node pattern (not used in this circuit, but keep for completeness)
                if " ^ " in node_str and " & " in node_str:
                    self.node_pattern[node_expr] = ("xor_and", None)
                    xor_and_count += 1
                    if self.debug:
                        print(f"  [INTRA] {node_expr} -> 'xor_and' (no explicit XOR consumer)")
                    continue

                # cross-level pattern with single fan-out into XOR
                if lvl + 1 not in self.nodes_by_level:
                    continue

                output_var = self._extract_lhs_var(node_expr)
                if not output_var:
                    continue

                fanout_count = 0
                xor_consumer = None
                max_lvl = max(self.nodes_by_level.keys())

                for next_lvl in range(lvl + 1, max_lvl + 1):
                    if next_lvl not in self.nodes_by_level:
                        continue
                    for next_expr in self.nodes_by_level[next_lvl]:
                        next_str = str(next_expr)
                        if '=' in next_str:
                            lhs, rhs = next_str.split('=', 1)
                            lhs = lhs.strip()
                            rhs = rhs.strip()
                        else:
                            lhs = ""
                            rhs = next_str

                        if output_var in rhs:
                            fanout_count += 1
                            if next_lvl == lvl + 1 and self._is_xor_node(next_str):
                                xor_consumer = lhs
                        if fanout_count > 1:
                            break
                    if fanout_count > 1:
                        break

                if fanout_count == 1 and xor_consumer is not None:
                    self.node_pattern[node_expr] = ("xor_and", xor_consumer)
                    xor_and_count += 1
                    if self.debug:
                        print(f"  [CROSS-LEVEL] {node_expr} -> xor_and, XOR consumer={xor_consumer}")

        print(f"[MRLC INFO] Pattern analysis complete:")
        print(f"             Total AND nodes : {and_count}")
        print(f"             'xor_and' (hpc2o/hpc3o eligible): {xor_and_count}")
        print(f"             'pure_and'                        : {and_count - xor_and_count}")

    def _heuristic_pattern_detection(self):
        """
        Fallback pattern detection based on node names/levels when graph analysis fails.
        """
        for lvl, nodes in self.nodes_by_level.items():
            for node in nodes:
                # Heuristic: simple check
                self.node_pattern[node] = 'pure_and' # Default

    def _get_gadgets_for_pattern(self, pattern_type, matching_gadgets):
        """Return gadgets legal for the detected pattern.
        
        CRITICAL FIX: Patterns are PREFERENCES, not hard constraints.
        DP algorithm will choose the best option based on actual costs.
        
        For XOR_AND patterns: Try optimized gadgets (HPC2o/HPC3o) AND standard gadgets
        For pure_and: Try standard gadgets (but include HPC2 if beneficial)
        Mixed: Use all available gadgets
        
        Previous problem: Too restrictive pattern enforcement prevented optimal choices
        New approach: Allow flexibility, let DP make final decision
        """
        if pattern_type == 'xor_and':
            # XOR_AND patterns: Prefer optimized but allow all
            # Exclude only inefficient gadgets like HPC1
            return {name: spec for name, spec in matching_gadgets.items()
                    if name not in ['hpc1']}
        else:
            # Pure AND: Use standard gadgets, but allow HPC2 for mixed patterns
            # Can still use HPC2 if DP determines it's optimal
            # Only exclude purely optimized variants (hpc2o, hpc3o) for pure_and
            return {name: spec for name, spec in matching_gadgets.items()
                    if name not in ['hpc2o', 'hpc3o']}
        
    def initial_gadget_and_list_possible_replacement(self, target_latency):
        self.min_latency_gadget = min(
            self.gadget_map.items(),
            key=lambda item: (item[1]["latency"], item[1]["randomness"], item[1]["area"])
        )

        initial_gadget_name = self.min_latency_gadget[0]
        initial_latency = self.min_latency_gadget[1]["latency"]
        initial_randomness = self.min_latency_gadget[1]["randomness"]

        print(f"[MRLC INFO]: Initial gadget selected: {initial_gadget_name}")
        print(f"             Latency: {initial_latency}, Randomness: {initial_randomness}")

        # Base matching gadgets
        self.matching_gadgets = {
            name: specs for name, specs in self.gadget_map.items()
            if specs["randomness"] <= initial_randomness or name == 'comar'
        }

        # === CRITICAL FIX: Force include optimized gadgets ===
        for opt in ['hpc2o', 'hpc3o']:
            if opt in self.gadget_map:
                if opt not in self.matching_gadgets:
                    self.matching_gadgets[opt] = self.gadget_map[opt]
                    print(f"[MRLC INFO] Force-included optimized gadget → {opt} "
                          f"(randomness={self.gadget_map[opt]['randomness']}, "
                          f"latency={self.gadget_map[opt]['latency']})")
                else:
                    print(f"[MRLC INFO] {opt} already present")
            else:
                print(f"[MRLC WARN] {opt} NOT FOUND in gadget_map! (add it)")

        if initial_gadget_name not in self.matching_gadgets:
            self.matching_gadgets[initial_gadget_name] = self.min_latency_gadget[1]

        print(f"[MRLC INFO]: Final matching gadgets: {list(self.matching_gadgets.keys())}")

        # Rest of the method (effective AND levels calculation) stays exactly the same
        self.DAG_levels = len(self.nodes_by_level)
        effective_levels = sum(1 for nodes in self.nodes_by_level.values()
                               if any(self._is_and_node(n) for n in nodes))
        self.total_initial_latency = effective_levels * initial_latency
        self.bonus_latency = max(0, target_latency - self.total_initial_latency)
        self.initial_latency_bonus = self.bonus_latency

        print(f"[MRLC INFO]: Effective AND levels: {effective_levels} | Bonus: {self.bonus_latency}")
        return self.bonus_latency
    
    def _is_and_node(self, expr: str) -> bool:
        """
        Return True if this TAC expression corresponds to an AND operation
        of the form:  LHS = RHS1 & RHS2
        (very simple heuristic: check for '&' on the RHS)
        """
        if '=' not in expr:
            return False
        lhs, rhs = expr.split('=', 1)
        rhs = rhs.strip()
        return '&' in rhs

    def _is_xor_node(self, expr: str) -> bool:
        """
        Return True if this TAC expression is a pure XOR operation
        (contains '^' but no '&' on the RHS).
        """
        if '=' not in expr:
            return False
        _, rhs = expr.split('=', 1)
        rhs = rhs.strip()
        return '^' in rhs and '&' not in rhs

    def _extract_lhs_var(self, expr):
        """Extract the LHS variable from an assignment like 'T1 = A ^ B'."""
        s = str(expr)
        if '=' not in s:
            return ""
        lhs = s.split('=', 1)[0].strip()
        return lhs

    def _extract_xor_other_operand(self, xor_expr_str, and_output_var):
        """From 'xor_out = and_out ^ w_in', given and_output_var, return the other XOR operand."""
        if '=' not in xor_expr_str:
            return None
        _, rhs = xor_expr_str.split('=', 1)
        rhs = rhs.strip()
        parts = [p.strip() for p in rhs.split('^')]
        for p in parts:
            if p != and_output_var:
                return p
        return None


