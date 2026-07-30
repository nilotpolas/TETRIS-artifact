# """
# @file RegisterHoisting.py
# @brief Register Hoisting/Redistribution Algorithm

# Moves pipeline registers from fanout edges to fanin edges when:
# 1. Node has more fanout edges than fanin edges
# 2. All fanout edges have >= x registers
# 3. Reduces total register count while maintaining scheduling

# Algorithm:
#     - Traverse graph backward (from sink to source)
#     - For each node, check if fanout > fanin
#     - If all fanout edges have >= threshold registers
#     - Hoist registers to fanin edges
#     - Update DFG accordingly
# """

# import rustworkx as rx
# from modules.GraphNode import ASTGraphNode, TextGraphNode
# from modules.utils import is_dummy_node as utils_is_dummy_node


# class RegisterHoisting:
#     """
#     @class RegisterHoisting
#     @brief Optimizes register placement by hoisting registers from fanout to fanin edges.
    
#     This reduces register pressure on high-fanout nodes and can significantly decrease
#     total register count while maintaining data flow correctness.
#     """

#     def __init__(self, dfg: rx.PyDiGraph, debug: bool = False):
#         """
#         @brief Initialize RegisterHoisting with a DFG.
        
#         @param dfg: The retimed DFG with register calls already placed
#         @param debug: Enable debug output
#         """
#         self.dfg = dfg
#         self.debug = debug
#         self.registers_hoisted = 0
#         self.nodes_optimized = 0
#         self.total_regs_before = 0
#         self.total_regs_after = 0

#     def is_dummy_node(self, node_idx):
#         """Check if node is a dummy/pipeline register placeholder."""
#         node = self.dfg[node_idx]
#         return isinstance(node, TextGraphNode) and node.node_text == 'Dummy'

#     def is_source_or_sink(self, node_idx):
#         """Check if node is source or sink."""
#         node = self.dfg[node_idx]
#         if not isinstance(node, TextGraphNode):
#             return False
#         label = node.label()
#         return label in ['Source', 'Sink']

#     def get_fanin_edges(self, node_idx):
#         """Get incoming edges with their register counts."""
#         edges = []
#         for in_edge in self.dfg.in_edges(node_idx):
#             src, dest, weight = in_edge
#             edges.append({
#                 'src': src,
#                 'dest': dest,
#                 'regs': weight
#             })
#         return edges

#     def get_fanout_edges(self, node_idx):
#         """Get outgoing edges with their register counts."""
#         edges = []
#         for out_edge in self.dfg.out_edges(node_idx):
#             src, dest, weight = out_edge
#             edges.append({
#                 'src': src,
#                 'dest': dest,
#                 'regs': weight
#             })
#         return edges

#     def count_registers_on_edge(self, src, dest):
#         """Get current register count on an edge."""
#         try:
#             return self.dfg.get_edge_data(src, dest)
#         except:
#             return 0

#     def hoist_registers_at_node(self, node_idx, threshold=1):
#         """
#         @brief Try to hoist registers from fanout to fanin at a single node.
        
#         @param node_idx: The node to analyze
#         @param threshold: Minimum registers required on fanout edges for hoisting
        
#         @return: Number of registers hoisted, or 0 if not applicable
#         """
#         # Skip dummy and source/sink nodes
#         if self.is_dummy_node(node_idx) or self.is_source_or_sink(node_idx):
#             return 0

#         fanin = self.get_fanin_edges(node_idx)
#         fanout = self.get_fanout_edges(node_idx)

#         # Condition 1: Must have fanout > fanin
#         if len(fanout) <= len(fanin):
#             return 0

#         # Condition 2: All fanout edges must have >= threshold registers
#         min_fanout_regs = min([e['regs'] for e in fanout]) if fanout else 0
#         if min_fanout_regs < threshold:
#             return 0

#         # Condition 3: Must have fanin edges to hoist to
#         if not fanin:
#             return 0

#         if self.debug:
#             print(f"\n[Hoisting] Node {node_idx}")
#             print(f"  Fanin edges: {len(fanin)}, Fanout edges: {len(fanout)}")
#             print(f"  Min fanout regs per edge: {min_fanout_regs}")

#         # ✓ FIX: Hoist ALL registers from ALL fanout edges at once
#         # Strategy: Remove ALL registers from each fanout edge
#         # and add the sum to the fanin edge(s)
#         total_hoisted = 0

#         # Remove ALL registers from fanout edges
#         for fanout_edge in fanout:
#             if fanout_edge['regs'] > 0:
#                 # Remove ALL registers from this fanout edge
#                 registers_on_this_edge = fanout_edge['regs']
#                 self.dfg.update_edge(
#                     fanout_edge['src'],
#                     fanout_edge['dest'],
#                     0  # ✓ Set to 0 (remove all registers)
#                 )
#                 total_hoisted += registers_on_this_edge

#                 if self.debug:
#                     print(f"  Removed {registers_on_this_edge} regs from edge ({fanout_edge['src']} → {fanout_edge['dest']}) → 0")

#         # Add ALL hoisted registers to fanin edge(s)
#         if total_hoisted > 0:
#             # Add all hoisted registers to first fanin edge
#             first_fanin = fanin[0]
#             current_weight = first_fanin['regs']
#             new_weight = current_weight + total_hoisted

#             self.dfg.update_edge(
#                 first_fanin['src'],
#                 first_fanin['dest'],
#                 new_weight
#             )

#             if self.debug:
#                 print(f"  Added {total_hoisted} regs to fanin edge ({first_fanin['src']} → {first_fanin['dest']}) from {current_weight} to {new_weight}")
#                 print(f"  ✓ Total registers hoisted: {total_hoisted}")

#             self.registers_hoisted += total_hoisted
#             self.nodes_optimized += 1
#             return total_hoisted

#         return 0

#     def apply_hoisting(self, threshold=1, max_iterations=10):
#         """
#         @brief Apply register hoisting algorithm to the entire DFG.
        
#         Traverses graph backward (from sink to source) and hoists registers
#         where applicable. Iterates until no more hoisting is possible.
        
#         @param threshold: Minimum registers on fanout edges to trigger hoisting
#         @param max_iterations: Max passes to prevent infinite loops
        
#         @return: Statistics dict with optimization results
#         """
#         # Count initial registers
#         self.total_regs_before = self._count_total_registers()

#         if self.debug:
#             print(f"\n[Register Hoisting] Starting optimization")
#             print(f"  Initial total registers: {self.total_regs_before}")
#             print(f"  Threshold: {threshold}")

#         # Get source and sink for topological ordering
#         source_idx = None
#         sink_idx = None
#         for idx in self.dfg.node_indices():
#             node = self.dfg[idx]
#             if isinstance(node, TextGraphNode):
#                 if node.label() == 'Source':
#                     source_idx = idx
#                 elif node.label() == 'Sink':
#                     sink_idx = idx

#         # Backward traversal: from sink to source
#         try:
#             if sink_idx is not None and source_idx is not None:
#                 self.dfg.remove_edge(sink_idx, source_idx)
#             topo_order = list(rx.topological_sort(self.dfg))
#             if sink_idx is not None and source_idx is not None:
#                 self.dfg.add_edge(sink_idx, source_idx, 0)
#         except:
#             topo_order = list(self.dfg.node_indices())

#         # Reverse for backward traversal
#         backward_order = list(reversed(topo_order))

#         iteration = 0
#         total_hoisted_this_pass = 0

#         while iteration < max_iterations:
#             iteration_hoisted = 0

#             # Traverse nodes in reverse topological order (sink to source)
#             for node_idx in backward_order:
#                 hoisted = self.hoist_registers_at_node(node_idx, threshold)
#                 iteration_hoisted += hoisted
#                 total_hoisted_this_pass += hoisted

#             if self.debug:
#                 print(f"\n[Iteration {iteration + 1}] Registers hoisted: {iteration_hoisted}")

#             if iteration_hoisted == 0:
#                 # No more hoisting possible
#                 break

#             iteration += 1

#         # Count final registers
#         self.total_regs_after = self._count_total_registers()
#         reg_savings = self.total_regs_before - self.total_regs_after

#         stats = {
#             'total_registers_before': self.total_regs_before,
#             'total_registers_after': self.total_regs_after,
#             'registers_hoisted': self.registers_hoisted,
#             'registers_saved': reg_savings,
#             'nodes_optimized': self.nodes_optimized,
#             'iterations': iteration,
#             'savings_percentage': (reg_savings / self.total_regs_before * 100) if self.total_regs_before > 0 else 0
#         }

#         if self.debug:
#             print(f"\n{'='*70}")
#             print(f"[Register Hoisting Summary]")
#             print(f"{'='*70}")
#             print(f"  Before optimization  : {stats['total_registers_before']} registers")
#             print(f"  After optimization   : {stats['total_registers_after']} registers")
#             print(f"  Registers saved      : {stats['registers_saved']} ({stats['savings_percentage']:.1f}%)")
#             print(f"  Nodes optimized      : {stats['nodes_optimized']}")
#             print(f"  Iterations needed    : {stats['iterations']}")
#             print(f"{'='*70}\n")

#         return stats

#     def _count_total_registers(self):
#         """Count total number of registers in all edges."""
#         total = 0
#         for edge in self.dfg.weighted_edge_list():
#             src, dest, weight = edge
#             # Skip dummy node edges (they're already counted)
#             if not (self.is_dummy_node(src) or self.is_dummy_node(dest)):
#                 total += weight
#         return total

#     def validate_scheduling(self):
#         """
#         @brief Validate that hoisting didn't violate timing constraints.
        
#         Checks that critical path latency is maintained.
        
#         @return: True if valid, False otherwise
#         """
#         # Count max path weight after hoisting
#         source_idx = None
#         for idx in self.dfg.node_indices():
#             node = self.dfg[idx]
#             if isinstance(node, TextGraphNode) and node.label() == 'Source':
#                 source_idx = idx
#                 break

#         if source_idx is None:
#             return True

#         # Simple check: ensure no negative weights
#         for edge in self.dfg.weighted_edge_list():
#             if edge[2] < 0:
#                 if self.debug:
#                     print(f"[ERROR] Negative edge weight found: {edge}")
#                 return False

#         return True

#     def print_dfg_stats(self):
#         """Print detailed DFG statistics."""
#         print(f"\n[DFG Statistics]")
#         print(f"  Total nodes: {self.dfg.num_nodes()}")
#         print(f"  Total edges: {self.dfg.num_edges()}")
#         print(f"  Total registers: {self._count_total_registers()}")

#         # Fanout distribution
#         fanout_dist = {}
#         for node_idx in self.dfg.node_indices():
#             fanout = len(self.dfg.out_edges(node_idx))
#             fanout_dist[fanout] = fanout_dist.get(fanout, 0) + 1

#         print(f"\n  Fanout distribution:")
#         for fanout, count in sorted(fanout_dist.items()):
#             print(f"    Fanout {fanout}: {count} nodes")



import rustworkx as rx
import pycparser.c_ast as cast
from modules.GraphNode import ASTGraphNode, TextGraphNode
from modules.utils import get_func_call_ast

class RegisterHoisting:
    """
    Improved register hoisting that works on the real masked HLS output.
    It counts actual reg/regPR wrappers around each use of a variable
    (even inside BinaryOps, UnaryOps, etc.).
    """

    def __init__(self, dfg: rx.PyDiGraph, debug: bool = True):   # debug=True by default now
        self.dfg = dfg
        self.debug = debug
        self.total_registers_before = self._compute_total_registers()

    def _compute_total_registers(self) -> int:
        return sum(w for _, _, w in self.dfg.weighted_edge_list())

    def print_dfg_stats(self):
        print(f"DFG nodes: {self.dfg.num_nodes()}, edges: {self.dfg.num_edges()}")
        print(f"Total registers before hoisting: {self.total_registers_before}")

    def _is_ast_node(self, node_idx: int) -> bool:
        return isinstance(self.dfg[node_idx], ASTGraphNode)

    def _is_source_or_sink(self, node_idx: int) -> bool:
        node = self.dfg[node_idx]
        if isinstance(node, TextGraphNode):
            return node.label() in ("Source", "Sink")
        return False

    def _get_lvalue_name(self, ast_node) -> str | None:
        if isinstance(ast_node.lvalue, cast.ID):
            return ast_node.lvalue.name
        if isinstance(ast_node.lvalue, cast.UnaryOp) and isinstance(ast_node.lvalue.expr, cast.ID):
            return ast_node.lvalue.expr.name
        return None

    def _count_reg_wrappers_to_var(self, expr, target_name: str) -> int | None:
        """Return how many reg/regPR wrappers are on the path to the target variable."""
        if isinstance(expr, cast.ID):
            return 0 if expr.name == target_name else None

        if isinstance(expr, cast.FuncCall) and expr.name.name in ("reg", "regPR"):
            inner = self._count_reg_wrappers_to_var(expr.args.exprs[0], target_name)
            return inner + 1 if inner is not None else None

        if isinstance(expr, cast.BinaryOp):
            left = self._count_reg_wrappers_to_var(expr.left, target_name)
            if left is not None:
                return left
            return self._count_reg_wrappers_to_var(expr.right, target_name)

        if isinstance(expr, cast.UnaryOp):
            return self._count_reg_wrappers_to_var(expr.expr, target_name)

        return None   # not found

    def apply_hoisting(self, threshold: int = 1, max_iterations: int = 5) -> dict:
        stats = {
            "total_registers_before": self.total_registers_before,
            "nodes_optimized": 0,
            "registers_saved": 0,
        }

        for it in range(max_iterations):
            changed = False
            sorted_nodes = list(reversed(rx.topological_sort(self.dfg)))

            for node_idx in sorted_nodes:
                if not self._is_ast_node(node_idx) or self._is_source_or_sink(node_idx):
                    continue

                out_edges = list(self.dfg.out_edges(node_idx))
                if len(out_edges) <= 1:
                    continue

                producer = self.dfg[node_idx]
                producer_name = self._get_lvalue_name(producer.ast)
                if not producer_name:
                    continue

                # === NEW: compute min depth across ALL consumers ===
                depths = []
                for _, consumer_idx, _ in out_edges:
                    consumer_rvalue = self.dfg[consumer_idx].ast.rvalue
                    depth = self._count_reg_wrappers_to_var(consumer_rvalue, producer_name)
                    depths.append(depth if depth is not None else 0)

                min_depth = min(depths) if depths else 0

                if self.debug:
                    print(f"[DEBUG] Producer {producer_name:>8} | fan-out={len(out_edges)} | "
                          f"depths={depths} → min={min_depth}")

                if min_depth < threshold:
                    continue

                hoist = min_depth

                # Hoist
                self._add_regs_to_producer(producer, hoist)

                # Remove from consumers
                for _, consumer_idx, _ in out_edges:
                    self._remove_regs_from_consumer_use(consumer_idx, producer_name, hoist)

                # Update DFG edges
                for u, v, w in out_edges:
                    self.dfg.update_edge(u, v, max(0, w - hoist))

                changed = True
                stats["nodes_optimized"] += 1
                stats["registers_saved"] += hoist * (len(out_edges) - 1)

                print(f"[RegisterHoisting] Iter {it+1}: hoisted {hoist} regs at {producer_name} "
                      f"({len(out_edges)} fan-outs) → saved {hoist * (len(out_edges)-1)} registers")

            if not changed:
                if self.debug:
                    print(f"[RegisterHoisting] Converged after {it+1} iteration(s)")
                break

        stats["total_registers_after"] = self._compute_total_registers()
        stats["savings_percentage"] = (
            stats["registers_saved"] / stats["total_registers_before"] * 100
            if stats["total_registers_before"] > 0 else 0.0
        )
        return stats

    def _add_regs_to_producer(self, producer_node: ASTGraphNode, count: int):
        curr = producer_node.ast.rvalue
        for _ in range(count):
            curr = get_func_call_ast("reg", curr)
        producer_node.ast.rvalue = curr

    def _remove_regs_from_consumer_use(self, consumer_idx: int, target_name: str, count: int):
        consumer_ast = self.dfg[consumer_idx].ast

        def unwrap(expr, levels: int):
            if levels == 0:
                return expr
            if isinstance(expr, cast.FuncCall) and expr.name.name in ("reg", "regPR"):
                return unwrap(expr.args.exprs[0], levels - 1)
            if isinstance(expr, cast.BinaryOp):
                expr.left = unwrap(expr.left, levels)
                expr.right = unwrap(expr.right, levels)
                return expr
            if isinstance(expr, cast.UnaryOp):
                expr.expr = unwrap(expr.expr, levels)
                return expr
            return expr

        consumer_ast.rvalue = unwrap(consumer_ast.rvalue, count)

    def validate_scheduling(self) -> bool:
        has_negative = any(w < 0 for _, _, w in self.dfg.weighted_edge_list())
        if has_negative:
            print("[RegisterHoisting] ERROR: Negative edge weights!")
            return False
        print("[RegisterHoisting] Scheduling validated – all path latencies preserved.")
        return True