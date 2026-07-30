# ============================================================================
# ASYMMETRIC GADGET OPTIMIZATION: HPC3 → HPC2 / HPC2_swapped
# ============================================================================
#
# STRATEGY:
# =========
# HPC2 has asymmetric input latency:
#   - Port A (1st param group): FAST path (1 cycle)
#   - Port B (2nd param group): SLOW path (2 cycles)
#
# HPC2_swapped has the ports flipped:
#   - Port A (1st param group): SLOW path (2 cycles)
#   - Port B (2nd param group): FAST path (1 cycle)
#
# OPTIMIZATION GOAL:
#   Route the DEEP (late-arriving) operand to the FAST port so the gate
#   finishes at the same cycle as HPC3 would.
#   Route the SHALLOW (early-arriving) operand to the SLOW port — it has
#   enough slack to absorb the extra cycle.
#
# GADGET SELECTION (for expression: result = op_A & op_B):
#   op_A is deep (large depth) → op_A already maps to Port A (fast) → use hpc2
#   op_B is deep (large depth) → op_B maps to Port B (slow in hpc2!)  → use hpc2_swapped
#                                 In hpc2_swapped, Port B is fast, so op_B gets the fast path.
#
# LATENCY VERIFICATION:
#   hpc3_latency = max(depth_A, depth_B) + 1  = deep_depth  + 1
#   hpc2_latency = max(deep_depth + 1, shallow_depth + 2)
#                = shallow_depth + 2   (when can_optimize is true)
#   can_optimize ⟺ shallow_depth + 2 ≤ deep_depth + 1
#                ⟺ depth_diff ≥ 1
#
# FLOW:
#   MRLC._mrlc_dp()
#     └─ nodes_gadget_assignment()        [Builds gadget_definition with HPC3]
#
#       ↓ THEN:
#
#   optimize_mrlc_with_asymmetric_gadgets()
#     └─ Replaces HPC3  → hpc2  or hpc2_swapped  where beneficial
#     └─ Replaces HPC3o → hpc2o or hpc2o_swapped where beneficial
#     └─ Updates gadget_definition in-place
#
#       ↓ THEN when generating C code:
#
#   ShareTransformer(gadget_definition)
#     └─ Reads gadget_name → emits correct function call (no arg-swap needed)
#     └─ Generates gadget definitions for all used gadgets
#
# ============================================================================
import os
from collections import defaultdict


class HPC2OptimizationPass:
    """
    Optimize HPC3/HPC3o nodes to HPC2/HPC2o (or their _swapped variants)
    using asymmetric input latency.

    This pass:
    1. Analyzes each AND node's input depths through the full AND-XOR logic tree.
    2. Determines if HPC2/HPC2o can be used without increasing total pipeline latency.
    3. Selects hpc2 when op_A is the deep operand (op_A → fast Port A).
       Selects hpc2_swapped when op_B is the deep operand (op_B → fast Port B).
    4. Returns the updated MRLC object with reduced randomness.
    """

    def __init__(self, mrlc_obj, and_xor_tree, debug=True):
        """
        Args:
            mrlc_obj:     MRLC object after DP algorithm.
            and_xor_tree: Complete combinational tree (AND + XOR nodes) with depth info.
            debug:        Enable debug output.
        """
        self.mrlc_obj = mrlc_obj
        self.and_xor_tree = and_xor_tree
        self.optimizations = {}
        self.depth_cache = {}
        self.debug = debug

    # ------------------------------------------------------------------
    # Helpers
    # ------------------------------------------------------------------

    def clean_var_name(self, var_name):
        """Strip brackets, negations, and pointers for perfect matching."""
        for char in ['*', '&', '~', '!', '(', ')', '[', ']']:
            var_name = var_name.replace(char, '')
        return var_name.strip()

    def _extract_operands(self, expr_str):
        """Robustly extract operands from any expression (AND, XOR, OR, assignment)."""
        if '=' not in expr_str:
            return []

        _, rhs = expr_str.split('=', 1)
        rhs = rhs.split('//')[0].strip()

        for char in ['&', '^', '|', '+', '-', '*', '~', '!', '(', ')']:
            rhs = rhs.replace(char, ' ')

        operands = [op.strip() for op in rhs.split()
                    if op.strip() and not op.strip().isdigit()]
        return operands

    # ------------------------------------------------------------------
    # Depth computation
    # ------------------------------------------------------------------

    def compute_node_depth(self, var_name, trace=False, indent=0):
        """
        Compute critical-path pipeline depth through the complete AND/XOR tree.
        XOR gates = +0 latency.  AND gates = +1 latency.
        """
        prefix = "  " * indent
        clean_var = self.clean_var_name(var_name)

        if clean_var in self.depth_cache:
            if trace:
                print(f"{prefix}[CACHE] {clean_var} → Depth: {self.depth_cache[clean_var]}")
            return self.depth_cache[clean_var]

        # Base case: primary inputs
        import re
        if (clean_var.startswith('T') or clean_var.startswith('X') or
                clean_var.startswith('in_') or clean_var.startswith('dec_') or
                re.match(r'^i\d+$', clean_var)):
            self.depth_cache[clean_var] = 0
            if trace:
                print(f"{prefix}[INPUT] {clean_var} → Depth: 0")
            return 0

        found_expr_str = None

        # 1. Search the and_xor_tree (leveled nodes)
        if hasattr(self.and_xor_tree, 'level_nodes'):
            for level, nodes in self.and_xor_tree.level_nodes.items():
                for node_expr in nodes:
                    node_str = str(node_expr)
                    if '=' in node_str:
                        lhs = node_str.split('=')[0]
                        if self.clean_var_name(lhs) == clean_var:
                            found_expr_str = node_str
                            break
                if found_expr_str:
                    break

        # 2. Bridge missing nodes via var_to_gate
        if not found_expr_str and hasattr(self.and_xor_tree, 'var_to_gate'):
            if clean_var in self.and_xor_tree.var_to_gate:
                parent_gates = self.and_xor_tree.var_to_gate[clean_var]
                if parent_gates:
                    if trace:
                        print(f"{prefix}[BRIDGE] {clean_var} is aliased to upstream gates")
                    depths = []
                    for p_gate in parent_gates:
                        p_gate_str = str(p_gate)
                        if '=' in p_gate_str:
                            p_lhs = p_gate_str.split('=')[0]
                            depths.append(
                                self.compute_node_depth(p_lhs, trace=trace, indent=indent + 1)
                            )
                    if depths:
                        bridged_depth = max(depths)
                        self.depth_cache[clean_var] = bridged_depth
                        if trace:
                            print(f"{prefix}  → {clean_var} bridged depth = {bridged_depth}")
                        return bridged_depth

        # 3. Fallback: search gadget_definition
        if not found_expr_str and hasattr(self.mrlc_obj, 'gadget_definition'):
            for expr in self.mrlc_obj.gadget_definition.keys():
                expr_str = str(expr)
                if '=' in expr_str:
                    lhs = expr_str.split('=')[0]
                    if self.clean_var_name(lhs) == clean_var:
                        found_expr_str = expr_str
                        break

        # 4. Process found expression
        if found_expr_str:
            rhs = found_expr_str.split('=', 1)[1].strip()
            if trace:
                print(f"{prefix}[FOUND] {clean_var} = {rhs}")

            operands = self._extract_operands(found_expr_str)
            if operands:
                depths = [
                    self.compute_node_depth(op, trace=trace, indent=indent + 1)
                    for op in operands
                ]
                max_input_depth = max(depths)
                depth = max_input_depth + (1 if '&' in rhs else 0)
                if trace:
                    print(f"{prefix}  Operands: {operands}")
                    print(f"{prefix}  Operand depths: {depths}")
                    print(f"{prefix}  → {clean_var} depth = {depth}")
            else:
                depth = 0
                if trace:
                    print(f"{prefix}  No operands extracted, depth = 0")

            self.depth_cache[clean_var] = depth
            return depth

        # 5. Truly not found — treat as primary input
        if trace:
            print(f"{prefix}[NOT FOUND] {clean_var} — treating as input (depth=0)")
        self.depth_cache[clean_var] = 0
        return 0

    def compute_node_depth_with_trace(self, var_name, indent=0):
        """Debug trace wrapper."""
        return self.compute_node_depth(var_name, trace=True, indent=indent)

    # ------------------------------------------------------------------
    # Gadget classification helpers
    # ------------------------------------------------------------------

    def _is_hpc3_node(self, gadget_name):
        return gadget_name.lower() in ['hpc3', 'hpc3o']

    def _is_hpc2_node(self, gadget_name):
        return gadget_name.lower() in ['hpc2', 'hpc2o', 'hpc2_swapped', 'hpc2o_swapped']

    def _get_hpc2_base(self, gadget_name):
        """Return the base HPC2 variant for the given HPC3 gadget (without swap suffix)."""
        if gadget_name.lower() == 'hpc3':
            return 'hpc2'
        elif gadget_name.lower() == 'hpc3o':
            return 'hpc2o'
        return None

    # ------------------------------------------------------------------
    # Optimization feasibility check
    # ------------------------------------------------------------------

    def can_optimize_to_hpc2(self, and_node_expr, current_gadget):
        """
        Check if an AND node can be replaced by HPC2 (or HPC2_swapped) without
        increasing pipeline latency.

        Returns
        -------
        (can_optimize, deep_operand, shallow_operand, depth_diff)
            deep_operand    — name of the operand with the LARGER depth (arrives later)
            shallow_operand — name of the operand with the SMALLER depth (arrives earlier)
        """
        if not self._is_hpc3_node(current_gadget):
            if self.debug:
                print(f"  [SKIP] Not HPC3/HPC3o: {current_gadget}")
            return False, None, None, 0

        operands = self._extract_operands(str(and_node_expr))
        if len(operands) != 2:
            if self.debug:
                print(f"  [SKIP] Unexpected operand count ({len(operands)}) in: "
                      f"{str(and_node_expr)[:60]}...")
            return False, None, None, 0

        op_A, op_B = operands[0], operands[1]
        op_A_clean = self.clean_var_name(op_A)
        op_B_clean = self.clean_var_name(op_B)

        depth_A = self.compute_node_depth(op_A_clean)
        depth_B = self.compute_node_depth(op_B_clean)
        depth_diff = abs(depth_A - depth_B)

        # deep = larger depth (arrives later), shallow = smaller depth (arrives earlier)
        if depth_A >= depth_B:
            deep_operand    = op_A_clean
            shallow_operand = op_B_clean
            deep_depth      = depth_A
            shallow_depth   = depth_B
        else:
            deep_operand    = op_B_clean
            shallow_operand = op_A_clean
            deep_depth      = depth_B
            shallow_depth   = depth_A

        # Latency check:
        #   HPC3: both inputs through 1 cycle                   → deep_depth + 1
        #   HPC2: deep → fast port (+1), shallow → slow port (+2) → shallow_depth + 2
        hpc3_latency = deep_depth + 1
        hpc2_latency = shallow_depth + 2   # = min(depth_A, depth_B) + 2

        can_optimize = hpc2_latency <= hpc3_latency

        if self.debug:
            print(f"  [DEPTH DEBUG] {str(and_node_expr)[:60]}")
            print(f"    op_A: {op_A_clean} (depth: {depth_A})")
            print(f"    op_B: {op_B_clean} (depth: {depth_B})")
            print(f"    diff: {depth_diff}")
            print(f"    HPC3 latency: {hpc3_latency}, HPC2 latency: {hpc2_latency}")
            print(f"    Can optimize: {can_optimize}")

        return can_optimize, deep_operand, shallow_operand, depth_diff

    # ------------------------------------------------------------------
    # Main optimization pass
    # ------------------------------------------------------------------

    def apply_optimization(self):
        """
        Iterate over all HPC3/HPC3o nodes and replace eligible ones with
        hpc2 / hpc2_swapped (or hpc2o / hpc2o_swapped for OR-masked nodes).
        """
        print("\n" + "=" * 80)
        print("ASYMMETRIC GADGET OPTIMIZATION PASS (HPC3 → HPC2 / HPC2_swapped)")
        print("=" * 80)

        optimized_count     = 0
        total_hpc3_nodes    = 0
        randomness_reduction = 0
        no_depth_diff       = 0
        latency_exceeded    = 0
        not_hpc3            = 0
        optimized_nodes_list = []

        # --- sanity checks -------------------------------------------
        print(f"\n[DEBUG] gadget_definition type: {type(self.mrlc_obj.gadget_definition)}")
        print(f"[DEBUG] gadget_definition size: "
              f"{len(self.mrlc_obj.gadget_definition) if self.mrlc_obj.gadget_definition else 0}")

        if not self.mrlc_obj.gadget_definition:
            print("[ERROR] gadget_definition is EMPTY — run MRLC first.")
            return self.mrlc_obj

        gadget_types = {}
        for info in self.mrlc_obj.gadget_definition.values():
            g = info.get("gadget_name", "UNKNOWN")
            gadget_types[g] = gadget_types.get(g, 0) + 1

        print("\n[DEBUG] Gadget distribution:")
        for g, cnt in sorted(gadget_types.items()):
            print(f"  {g:15s}: {cnt:3d} gates")

        hpc3_count = sum(1 for info in self.mrlc_obj.gadget_definition.values()
                         if self._is_hpc3_node(info.get("gadget_name", "")))
        print(f"\n[DEBUG] HPC3/HPC3o gates found: {hpc3_count}")

        if hpc3_count == 0:
            print("[WARNING] No HPC3/HPC3o gates found — nothing to optimize.")
            return self.mrlc_obj

        # --- function-name map ---------------------------------------
        func_name_map = {
            'hpc2':          'HPC2',
            'hpc2o':         'HPC2o',
            'hpc2_swapped':  'HPC2_swapped',
            'hpc2o_swapped': 'HPC2o_swapped',
            'hpc3':          'HPC3',
            'hpc3o':         'HPC3o',
            'hpc1':          'HPC1',
            'comar':         'COMAR',
            'domand':        'Domand',
        }

        # --- main loop -----------------------------------------------
        for and_node_expr, gadget_info in self.mrlc_obj.gadget_definition.items():
            current_gadget = gadget_info.get("gadget_name", "")

            if not self._is_hpc3_node(current_gadget):
                if self.debug:
                    print(f"  [SKIP] Not HPC3/HPC3o: {current_gadget}")
                not_hpc3 += 1
                continue

            total_hpc3_nodes += 1
            node_str = str(and_node_expr)

            can_opt, deep_op, shallow_op, depth_diff = self.can_optimize_to_hpc2(
                and_node_expr, current_gadget
            )

            # Track failure reasons for the summary
            if not can_opt:
                operands = self._extract_operands(node_str)
                if len(operands) == 2:
                    d_A = self.compute_node_depth(self.clean_var_name(operands[0]))
                    d_B = self.compute_node_depth(self.clean_var_name(operands[1]))
                    if abs(d_A - d_B) < 1:
                        no_depth_diff += 1
                    else:
                        latency_exceeded += 1
                continue

            if not (deep_op and shallow_op):
                continue

            hpc2_base = self._get_hpc2_base(current_gadget)   # 'hpc2' or 'hpc2o'
            if hpc2_base is None:
                continue

            # ----------------------------------------------------------
            # Gadget variant selection
            # ----------------------------------------------------------
            # Expression in the netlist: result = op_A & op_B
            #   op_A → Port A    op_B → Port B
            #
            # We want the DEEP operand on the FAST port:
            #   hpc2          : Port A = fast (1 cyc), Port B = slow (2 cyc)
            #   hpc2_swapped  : Port A = slow (2 cyc), Port B = fast (1 cyc)
            #
            #   op_A is deep → op_A on Port A (fast in hpc2)     → use hpc2
            #   op_B is deep → op_B on Port B (fast in hpc2_swapped) → use hpc2_swapped
            operands = self._extract_operands(node_str)
            if len(operands) == 2:
                op_A_clean = self.clean_var_name(operands[0])
                if op_A_clean == deep_op:
                    # op_A is deep → Port A (fast in hpc2) → no swap needed
                    hpc2_gadget = hpc2_base
                else:
                    # op_B is deep → Port B (fast only in hpc2_swapped) → use _swapped
                    hpc2_gadget = hpc2_base + '_swapped'
            else:
                hpc2_gadget = hpc2_base   # fallback

            if self.debug:
                print(f"    [GADGET VARIANT] deep={deep_op}, shallow={shallow_op}")
                print(f"      op_A={self.clean_var_name(operands[0]) if len(operands)==2 else '?'}, "
                      f"op_B={self.clean_var_name(operands[1]) if len(operands)==2 else '?'}")
                print(f"      → selected gadget: {hpc2_gadget}")

            # Check the chosen gadget exists in gadget_map; fall back to base if not
            if hasattr(self.mrlc_obj, 'gadget_map') and hpc2_gadget not in self.mrlc_obj.gadget_map:
                print(f"[WARN] {hpc2_gadget} not in gadget_map — falling back to {hpc2_base}")
                hpc2_gadget = hpc2_base

            if not hasattr(self.mrlc_obj, 'gadget_map'):
                print(f"[WARN] mrlc_obj has no gadget_map — skipping {node_str[:60]}")
                continue

            if and_node_expr not in self.mrlc_obj.gadget_definition:
                print(f"[ERROR] Expression not in gadget_definition: {and_node_expr}")
                continue

            old_gadget     = current_gadget
            old_randomness = gadget_info.get("random_numbers", 0)
            new_randomness = self.mrlc_obj.gadget_map[hpc2_gadget].get("randomness", old_randomness)

            # Update gadget_definition in-place
            entry = self.mrlc_obj.gadget_definition[and_node_expr]
            entry["gadget_name"]    = hpc2_gadget
            entry["random_numbers"] = new_randomness
            entry["func_name"]      = func_name_map.get(hpc2_gadget, hpc2_gadget.upper())
            entry["depth_diff"]     = depth_diff

            # Verify
            if entry["gadget_name"] != hpc2_gadget:
                print(f"[ERROR] Failed to update gadget_name! "
                      f"Expected {hpc2_gadget}, got {entry['gadget_name']}")

            randomness_reduction += old_randomness - new_randomness
            optimized_count += 1
            optimized_nodes_list.append({
                'expr':    node_str[:60],
                'old':     old_gadget,
                'new':     hpc2_gadget,
                'func':    entry["func_name"],
                'shallow': shallow_op,
                'deep':    deep_op,
            })

        # --- update total randomness (COMAR is shared — count once) --
        old_total_randomness = getattr(self.mrlc_obj, 'total_randomness_after_mrlc', 0)
        gdef = self.mrlc_obj.gadget_definition
        comar_used = any(
            info.get("gadget_name", "").lower() == "comar"
            for info in gdef.values()
        )
        self.mrlc_obj.total_randomness_after_mrlc = sum(
            info.get("random_numbers", 0)
            for info in gdef.values()
            if info.get("gadget_name", "").lower() != "comar"
        ) + (self.mrlc_obj.gadget_map["comar"]["randomness"]
             if comar_used and "comar" in self.mrlc_obj.gadget_map else 0)

        # --- summary -------------------------------------------------
        print("\n" + "=" * 80)
        print(f"OPTIMIZATION RESULTS: {optimized_count} gates optimized")
        print("=" * 80)

        if optimized_nodes_list:
            print(f"\n[OPTIMIZED GATES] ({len(optimized_nodes_list)} total)")
            for i, n in enumerate(optimized_nodes_list, 1):
                print(f"  {i:2d}. {n['expr']:60s} | {n['old']} → {n['new']}")
                print(f"      Shallow: {n['shallow']:10s} | Deep: {n['deep']}")

        print(f"\n[OPTIMIZATION SUMMARY]")
        print(f"  Total HPC3/HPC3o nodes analyzed : {total_hpc3_nodes}")
        print(f"  Nodes optimized to HPC2(o)      : {optimized_count}")
        print(f"  Optimization rate               : "
              f"{optimized_count}/{total_hpc3_nodes} = "
              f"{100 * optimized_count / max(1, total_hpc3_nodes):.1f}%")
        print(f"\n  Failures:")
        print(f"    Insufficient depth difference (< 1) : {no_depth_diff}")
        print(f"    Latency would increase              : {latency_exceeded}")
        print(f"    Not HPC3 gadget                     : {not_hpc3}")
        print(f"\n  Randomness:")
        print(f"    Before : {old_total_randomness}")
        print(f"    After  : {self.mrlc_obj.total_randomness_after_mrlc}")
        if old_total_randomness > 0:
            saved = randomness_reduction
            pct   = 100 * saved / old_total_randomness
            print(f"    Saved  : {saved} ({pct:.1f}%)")
        print(f"    Latency: {getattr(self.mrlc_obj, 'total_latency_after_mrlc', 'Unknown')} (unchanged)")
        print("=" * 80 + "\n")

        return self.mrlc_obj


def optimize_mrlc_with_asymmetric_gadgets(mrlc_obj, and_xor_tree, debug=True):
    """
    Main entry point for asymmetric gadget optimization.

    Args:
        mrlc_obj:     MRLC object containing gadget assignments.
        and_xor_tree: Complete tree containing both AND and XOR nodes.
        debug:        Print tracing details.

    Returns:
        Updated mrlc_obj with HPC3/HPC3o replaced by hpc2/hpc2_swapped
        (and hpc2o/hpc2o_swapped) wherever it reduces randomness without
        increasing pipeline latency.
    """
    optimizer = HPC2OptimizationPass(mrlc_obj, and_xor_tree, debug=debug)
    return optimizer.apply_optimization()
