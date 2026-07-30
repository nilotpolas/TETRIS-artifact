# ============================================================================
# asymmetric_latency_optimizer.py
# Standalone Post-MLRC Latency Optimizer (Asymmetric Gadget Flipping)
# ============================================================================

from collections import defaultdict
import copy

class AsymmetricLatencyOptimizer:
    """
    Post-MLRC latency optimizer using asymmetric gadget flipping.
    Works on HPC2 / HPC2o gadgets only.
    Completely independent of the MLRC class.
    """

    def __init__(self, gadget_definition: dict, nodes_by_level: dict):
        """
        Parameters:
            gadget_definition : dict (same as mlrc_obj.gadget_definition)
                Will be modified in-place with new "input_reorder" values.
            nodes_by_level    : dict (same as mlrc_obj.nodes_by_level)
        """
        self.gadget_definition = gadget_definition
        self.nodes_by_level = nodes_by_level

    def _get_port_latencies(self, gadget_name: str) -> dict:
        """Return per-port latencies for asymmetric gadgets.

        HPC2 / HPC2o:
            a-param (first)  = fast port  (1 cycle)
            b-param (second) = slow port  (2 cycles)
        HPC2_swapped / HPC2o_swapped:
            a-param (first)  = slow port  (2 cycles)
            b-param (second) = fast port  (1 cycle)
        """
        g = gadget_name.lower()
        if g in {'hpc2', 'hpc2o'}:
            return {'A': 1, 'B': 2}
        if g in {'hpc2_swapped', 'hpc2o_swapped'}:
            return {'A': 2, 'B': 1}
        # Symmetric gadgets: both ports add 1 cycle
        return {'A': 1, 'B': 1}

    def _compute_accurate_critical_path_latency(self) -> int:
        """
        Accurate timing simulation that respects gadget asymmetry + input_reorder.
        Returns the true critical-path latency.
        """
        arrival = {}  # variable -> earliest arrival time (cycles)

        for lvl in sorted(self.nodes_by_level.keys()):
            for node_expr in self.nodes_by_level[lvl]:
                node_str = str(node_expr)
                if '=' not in node_str:
                    continue

                lhs, rhs = node_str.split('=', 1)
                lhs = lhs.strip()
                rhs = rhs.strip()

                if '&' in rhs:  # AND gadget
                    input_a, input_b = [x.strip().replace('*', '') for x in rhs.split('&')]
                    info      = self.gadget_definition.get(node_expr, {})
                    gname     = info.get("gadget_name", "hpc2").lower()
                    port_lats = self._get_port_latencies(gname)

                    # A-port receives input_a (left of &), B-port receives input_b (right of &).
                    # The gadget name encodes which port is fast/slow.
                    arr_a = arrival.get(input_a, 0)
                    arr_b = arrival.get(input_b, 0)

                    out_arr = max(
                        arr_a + port_lats['A'],
                        arr_b + port_lats['B'],
                    )
                    arrival[lhs] = out_arr

                elif '^' in rhs:  # XOR = no added latency
                    inputs = [x.strip().replace('*', '') for x in rhs.split('^')]
                    max_in = max(arrival.get(inp, 0) for inp in inputs)
                    arrival[lhs] = max_in
                else:  # simple assignment
                    input_var = rhs.replace('*', '').strip()
                    arrival[lhs] = arrival.get(input_var, 0)

        return max(arrival.values()) if arrival else 0

    def optimize(self, max_iterations: int = 30) -> dict:
        """
        Iteratively toggle each HPC2/HPC2o node between its base and swapped
        variant.  A toggle is kept only when it strictly reduces the accurate
        critical-path latency.

        Base ↔ swapped pairs:
            hpc2        ↔  hpc2_swapped
            hpc2o       ↔  hpc2o_swapped

        The gadget name itself encodes which port is fast/slow, so no
        input_reorder flag is needed.
        """
        print("\n[AsymmetricLatencyOptimizer] === Starting Asymmetric Gadget Flipping ===")

        # Pairs: toggling between a gadget and its swapped counterpart
        _toggle = {
            'hpc2'         : 'hpc2_swapped',
            'hpc2_swapped' : 'hpc2',
            'hpc2o'        : 'hpc2o_swapped',
            'hpc2o_swapped': 'hpc2o',
        }

        initial_latency = self._compute_accurate_critical_path_latency()
        current_latency = initial_latency
        print(f"Initial accurate critical-path latency : {current_latency} cycles")

        iteration   = 0
        total_flips = 0
        improved    = True

        while improved and iteration < max_iterations:
            improved        = False
            iteration      += 1
            flips_this_iter = 0

            for node_expr in list(self.gadget_definition.keys()):
                info  = self.gadget_definition[node_expr]
                gname = info.get("gadget_name", "").lower()

                if gname not in _toggle:
                    continue

                toggled = _toggle[gname]

                # Temporarily apply toggle
                info["gadget_name"] = toggled
                new_latency = self._compute_accurate_critical_path_latency()

                if new_latency < current_latency:
                    # Accept
                    current_latency  = new_latency
                    improved         = True
                    flips_this_iter += 1
                    total_flips     += 1
                    print(f"  ✓ Toggled {node_expr}: {gname} → {toggled}  |  latency now = {current_latency}")
                else:
                    # Revert
                    info["gadget_name"] = gname

            if improved:
                print(f"  Iteration {iteration}: {flips_this_iter} successful flips")

        print(f"\n[AsymmetricLatencyOptimizer] Optimization finished after {iteration} iterations.")
        print(f"   Total flips performed     : {total_flips}")
        print(f"   Initial critical-path     : {initial_latency} cycles")
        print(f"   Final critical-path       : {current_latency} cycles")
        print(f"   Latency reduction         : {initial_latency - current_latency} cycles")

        return {
            "final_latency":   current_latency,
            "initial_latency": initial_latency,
            "iterations":      iteration,
            "total_flips":     total_flips,
        }