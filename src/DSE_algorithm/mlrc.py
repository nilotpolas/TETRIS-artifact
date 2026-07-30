# # ============================================================================
# # MLRC Post-Optimization Strategy (Generic, Order-Agnostic)
# # ============================================================================
# #
# # BEFORE (Hardcoded, AST-level, order-specific):
# #   1. Split AST into shares for d=1 (2 shares)
# #   2. Manually search for HPC3 calls in split code
# #   3. Try to swap HPC3 → HPC2 in AST
# #   4. Re-compile and hope latency is OK
# #   → Works only for d=1, fragile, requires AST manipulation
# #
# # AFTER (Generic, AND-tree level, works for any order):
# #   1. MLRC generates initial gadget mapping at AND-tree level
# #   2. Compute critical path latency (accounts for parallelism)
# #   3. Greedily replace high-cost gadgets with cheaper ones:
# #      - For each node, find a replacement with lower randomness/area
# #      - Same or better latency (checked via critical path)
# #   4. Split into shares ONCE with final optimized mapping
# #   → Works for any d, no AST manipulation, latency-aware
# #
# # KEY FUNCTIONS:
# #   - _get_replacement_gadget(current, target_latency)
# #     Find a cheaper alternative to 'current' gadget
# #   - optimize_gadget_mapping_for_cost(target_latency, max_iterations)
# #     Iteratively replace nodes; recompute critical path after each
# #   - _compute_critical_path_latency()
# #     Compute true latency as longest AND-dependency chain (not sum)
# #
# # USAGE IN NOTEBOOK:
# #   mlrc_obj = MLRC(d, and_tree, gadget_specs)
# #   mlrc_obj.mlrc(target_randomness)           # Initial MLRC
# #   stats = mlrc_obj.optimize_gadget_mapping_for_cost(target_latency)
# #   # Now split into shares once with final mapping
# # ============================================================================
# # ASYMMETRIC GADGET PROPERTY OPTIMIZATION
# # ============================================================================
# #
# # KEY INSIGHT: Different masking gadgets have different latency characteristics
# #
# # HPC2 (2-order masking):
# #   - Input A path latency: 2 cycles
# #   - Input B path latency: 1 cycle  (FAST PATH)
# #   - Asymmetric: different latencies for different inputs
# #   - Randomness: 3
# #
# # HPC3 (3-order masking):
# #   - Input A path latency: 1 cycle
# #   - Input B path latency: 1 cycle
# #   - Symmetric: same latency for both inputs
# #   - Randomness: 6
# #
# # OPTIMIZATION STRATEGY:
# #   1. Detect xor_and patterns:
# #      - AND node M = A & B
# #      - M is immediately consumed by XOR: Z = M ^ X
# #   
# #   2. For xor_and nodes, replace HPC3 → HPC2:
# #      - Place the fast input (latency 1) on the critical path
# #      - The slow input's extra latency is hidden by XOR buffering
# #      - Result: same critical path latency, but randomness 6 → 3
# #   
# #   3. For pure AND nodes:
# #      - Cannot safely replace (both inputs might be on critical path)
# #      - Keep as HPC3
# #
# # BENEFITS:
# #   - Reduces randomness by 50% (6 → 3) for xor_and nodes
# #   - No increase in latency (thanks to asymmetric properties)
# #   - Automatically applied to any order d
# #   - Works generically across all masking orders
# #
# # IMPLEMENTATION:
# #   - _can_swap_hpc3_to_hpc2_asymmetric(): Check if node is xor_and pattern
# #   - optimize_gadget_mapping_for_cost_asymmetric(): Greedily replace HPC3 → HPC2
# # ============================================================================
# # ARRIVAL DEPTH-BASED ASYMMETRIC GADGET OPTIMIZATION (matches find_swaps.py)
# # ============================================================================
# #
# # PROBLEM:
# #   After MLRC, all AND nodes are assigned gadgets (mostly HPC3 for d=1).
# #   But many HPC3 nodes have unbalanced input arrival times.
# #   → We can replace them with HPC2 (which is asymmetric) to save randomness.
# #
# # KEY INSIGHT FROM find_swaps.py:
# #   HPC2 has asymmetric input paths:
# #   - Input A: latency 2 (slow path)
# #   - Input B: latency 1 (fast path)
# #   
# #   HPC3 has symmetric paths (both latency 1).
# #   
# #   If inputs arrive at different times:
# #   - Early-arriving input → put on slow path (latency 2)
# #   - Late-arriving input → put on fast path (latency 1)
# #   → Total latency = max(early + 2, late + 1) = max(early, late) + 1
# #   → Same as HPC3 if inputs were balanced!
# #
# # ALGORITHM (_compute_arrival_depths):
# #   1. Process AND tree level by level (in order)
# #   2. For each variable, track its depth (how many AND ops deep)
# #   3. For AND nodes: depth = max(input_depths) + 1
# #   4. For XOR nodes: depth = max(input_depths)
# #   5. Result: {node_expr: (depth_A, depth_B)} for each AND node
# #
# # REPLACEMENT LOGIC (optimize_gadget_mapping_for_cost_asymmetric):
# #   For each HPC3/HPC3o node:
# #     1. Get input depths: depth_A, depth_B
# #     2. If |depth_A - depth_B| >= 1: inputs arrive at different times
# #     3. Replace HPC3 → HPC2 (or HPC3o → HPC2o)
# #     4. Reorder: early input → slow, late input → fast
# #     5. Save: randomness 6→3 (for d=1), area reduction, no latency increase!
# #
# # EXPECTED RESULTS (d=1, target_randomness=111):
# #   - Initial MLRC: ~34 HPC3 nodes (randomness: 34*6 = 204)
# #   - After arrival depth opt: ~22 nodes replaced → ~12 HPC3 + ~22 HPC2
# #   - Final randomness: 12*6 + 22*3 = 138 → saves ~66 randomness bits
# #   - Latency: unchanged (still critical path)
# #   - Area: reduced (HPC2 smaller than HPC3)
# #
# # COMPARISON WITH find_swaps.py:
# #   find_swaps.py: works on split C code, uses signal arrival depths
# #   Our MLRC version: works at AND-tree level BEFORE splitting
# #   Result: equivalent swaps, but applied earlier in pipeline
# # ============================================================================
# # COMPLETE MLRC OPTIMIZATION FLOW (WITH FINAL GADGET MAP PRINTING)
# # ============================================================================
# #
# # WORKFLOW:
# #
# # STEP 1: INITIAL MLRC (Minimize Latency Under Randomness Constraint)
# #   - All AND nodes assigned HPC2 initially (min randomness)
# #   - Use randomness budget (111) to upgrade to HPC3/HPC3o
# #   - Critical path latency: computed as longest AND dependency chain
# #   - Pattern analysis: detect xor_and nodes (AND → XOR)
# #   - Upgrade xor_and nodes to hpc3o/hpc2o (optimized variants)
# #   - Result: initial mapping with mixed gadgets, latency minimized
# #
# # STEP 2: ARRIVAL DEPTH OPTIMIZATION (Post-MLRC)
# #   - Compute arrival depth for each AND node (how deep in AND chain)
# #   - For each HPC3/HPC3o node:
# #     - If input depths differ by ≥1: swap to HPC2/HPC2o
# #     - Place early-arriving input on slow path (latency 2)
# #     - Place late-arriving input on fast path (latency 1)
# #     - Result: balanced timing, no latency increase, randomness saved!
# #   - Savings: randomness 2→1 per node, ~22 nodes → ~22 randomness saved
# #
# # STEP 3: FINAL GADGET MAPPING (printed after optimization)
# #   - Shows all 34 AND nodes with final gadget assignments
# #   - Columns: Gate No, Expression, Gadget, Randomness, Area
# #   - Gadget summary: count, total randomness, total area
# #   - Unique definitions: lists which gadgets are actually used
# #
# # STEP 4: SHARE SPLITTING
# #   - Transform AST: replace AND nodes with gadget function calls
# #   - ShareTransformer(d+1, gadget_map, unique_definitions)
# #   - Generates d+1 shares of the circuit
# #   - Includes all gadget definitions (HPC2, HPC3, HPC2o, HPC3o, etc.)
# #   - Output: C file with shared masking implementation
# #
# # KEY METRICS (Example for d=1, target_randomness=111):
# #   - Initial MLRC: 68 randomness, 3 latency, 156 area
# #   - After optimization: 46 randomness, 3 latency, 164 area
# #   - Savings: 22 randomness bits, same latency!
# #   - Gadgets used: 12 hpc3, 22 hpc2
# #
# # ============================================================================
# # MLRC Post-Optimization Strategy (Generic, Order-Agnostic)
# # ============================================================================
# #
# # BEFORE (Hardcoded, AST-level, order-specific):
# #   1. Split AST into shares for d=1 (2 shares)
# #   2. Manually search for HPC3 calls in split code
# #   3. Try to swap HPC3 → HPC2 in AST
# #   4. Re-compile and hope latency is OK
# #   → Works only for d=1, fragile, requires AST manipulation
# #
# # AFTER (Generic, AND-tree level, works for any order):
# #   1. MLRC generates initial gadget mapping at AND-tree level
# #   2. Compute critical path latency (accounts for parallelism)
# #   3. Greedily replace high-cost gadgets with cheaper ones:
# #      - For each node, find a replacement with lower randomness/area
# #      - Same or better latency (checked via critical path)
# #   4. Split into shares ONCE with final optimized mapping
# #   → Works for any d, no AST manipulation, latency-aware
# #
# # KEY FUNCTIONS:
# #   - _get_replacement_gadget(current, target_latency)
# #     Find a cheaper alternative to 'current' gadget
# #   - optimize_gadget_mapping_for_cost(target_latency, max_iterations)
# #     Iteratively replace nodes; recompute critical path after each
# #   - _compute_critical_path_latency()
# #     Compute true latency as longest AND-dependency chain (not sum)
# #
# # USAGE IN NOTEBOOK:
# #   mlrc_obj = MLRC(d, and_tree, gadget_specs)
# #   mlrc_obj.mlrc(target_randomness)           # Initial MLRC
# #   stats = mlrc_obj.optimize_gadget_mapping_for_cost(target_latency)
# #   # Now split into shares once with final mapping
# # ============================================================================
# # ASYMMETRIC GADGET PROPERTY OPTIMIZATION
# # ============================================================================
# #
# # KEY INSIGHT: Different masking gadgets have different latency characteristics
# #
# # HPC2 (2-order masking):
# #   - Input A path latency: 2 cycles
# #   - Input B path latency: 1 cycle  (FAST PATH)
# #   - Asymmetric: different latencies for different inputs
# #   - Randomness: 3
# #
# # HPC3 (3-order masking):
# #   - Input A path latency: 1 cycle
# #   - Input B path latency: 1 cycle
# #   - Symmetric: same latency for both inputs
# #   - Randomness: 6
# #
# # OPTIMIZATION STRATEGY:
# #   1. Detect xor_and patterns:
# #      - AND node M = A & B
# #      - M is immediately consumed by XOR: Z = M ^ X
# #   
# #   2. For xor_and nodes, replace HPC3 → HPC2:
# #      - Place the fast input (latency 1) on the critical path
# #      - The slow input's extra latency is hidden by XOR buffering
# #      - Result: same critical path latency, but randomness 6 → 3
# #   
# #   3. For pure AND nodes:
# #      - Cannot safely replace (both inputs might be on critical path)
# #      - Keep as HPC3
# #
# # BENEFITS:
# #   - Reduces randomness by 50% (6 → 3) for xor_and nodes
# #   - No increase in latency (thanks to asymmetric properties)
# #   - Automatically applied to any order d
# #   - Works generically across all masking orders
# #
# # IMPLEMENTATION:
# #   - _can_swap_hpc3_to_hpc2_asymmetric(): Check if node is xor_and pattern
# #   - optimize_gadget_mapping_for_cost_asymmetric(): Greedily replace HPC3 → HPC2
# # ============================================================================
# # ARRIVAL DEPTH-BASED ASYMMETRIC GADGET OPTIMIZATION (matches find_swaps.py)
# # ============================================================================
# #
# # PROBLEM:
# #   After MLRC, all AND nodes are assigned gadgets (mostly HPC3 for d=1).
# #   But many HPC3 nodes have unbalanced input arrival times.
# #   → We can replace them with HPC2 (which is asymmetric) to save randomness.
# #
# # KEY INSIGHT FROM find_swaps.py:
# #   HPC2 has asymmetric input paths:
# #   - Input A: latency 2 (slow path)
# #   - Input B: latency 1 (fast path)
# #   
# #   HPC3 has symmetric paths (both latency 1).
# #   
# #   If inputs arrive at different times:
# #   - Early-arriving input → put on slow path (latency 2)
# #   - Late-arriving input → put on fast path (latency 1)
# #   → Total latency = max(early + 2, late + 1) = max(early, late) + 1
# #   → Same as HPC3 if inputs were balanced!
# #
# # ALGORITHM (_compute_arrival_depths):
# #   1. Process AND tree level by level (in order)
# #   2. For each variable, track its depth (how many AND ops deep)
# #   3. For AND nodes: depth = max(input_depths) + 1
# #   4. For XOR nodes: depth = max(input_depths)
# #   5. Result: {node_expr: (depth_A, depth_B)} for each AND node
# #
# # REPLACEMENT LOGIC (optimize_gadget_mapping_for_cost_asymmetric):
# #   For each HPC3/HPC3o node:
# #     1. Get input depths: depth_A, depth_B
# #     2. If |depth_A - depth_B| >= 1: inputs arrive at different times
# #     3. Replace HPC3 → HPC2 (or HPC3o → HPC2o)
# #     4. Reorder: early input → slow, late input → fast
# #     5. Save: randomness 6→3 (for d=1), area reduction, no latency increase!
# #
# # EXPECTED RESULTS (d=1, target_randomness=111):
# #   - Initial MLRC: ~34 HPC3 nodes (randomness: 34*6 = 204)
# #   - After arrival depth opt: ~22 nodes replaced → ~12 HPC3 + ~22 HPC2
# #   - Final randomness: 12*6 + 22*3 = 138 → saves ~66 randomness bits
# #   - Latency: unchanged (still critical path)
# #   - Area: reduced (HPC2 smaller than HPC3)
# #
# # COMPARISON WITH find_swaps.py:
# #   find_swaps.py: works on split C code, uses signal arrival depths
# #   Our MLRC version: works at AND-tree level BEFORE splitting
# #   Result: equivalent swaps, but applied earlier in pipeline
# # ============================================================================
# # COMPLETE MLRC OPTIMIZATION FLOW (WITH FINAL GADGET MAP PRINTING)
# # ============================================================================
# #
# # WORKFLOW:
# #
# # STEP 1: INITIAL MLRC (Minimize Latency Under Randomness Constraint)
# #   - All AND nodes assigned HPC2 initially (min randomness)
# #   - Use randomness budget (111) to upgrade to HPC3/HPC3o
# #   - Critical path latency: computed as longest AND dependency chain
# #   - Pattern analysis: detect xor_and nodes (AND → XOR)
# #   - Upgrade xor_and nodes to hpc3o/hpc2o (optimized variants)
# #   - Result: initial mapping with mixed gadgets, latency minimized
# #
# # STEP 2: ARRIVAL DEPTH OPTIMIZATION (Post-MLRC)
# #   - Compute arrival depth for each AND node (how deep in AND chain)
# #   - For each HPC3/HPC3o node:
# #     - If input depths differ by ≥1: swap to HPC2/HPC2o
# #     - Place early-arriving input on slow path (latency 2)
# #     - Place late-arriving input on fast path (latency 1)
# #     - Result: balanced timing, no latency increase, randomness saved!
# #   - Savings: randomness 2→1 per node, ~22 nodes → ~22 randomness saved
# #
# # STEP 3: FINAL GADGET MAPPING (printed after optimization)
# #   - Shows all 34 AND nodes with final gadget assignments
# #   - Columns: Gate No, Expression, Gadget, Randomness, Area
# #   - Gadget summary: count, total randomness, total area
# #   - Unique definitions: lists which gadgets are actually used
# #
# # STEP 4: SHARE SPLITTING
# #   - Transform AST: replace AND nodes with gadget function calls
# #   - ShareTransformer(d+1, gadget_map, unique_definitions)
# #   - Generates d+1 shares of the circuit
# #   - Includes all gadget definitions (HPC2, HPC3, HPC2o, HPC3o, etc.)
# #   - Output: C file with shared masking implementation
# #
# # KEY METRICS (Example for d=1, target_randomness=111):
# #   - Initial MLRC: 68 randomness, 3 latency, 156 area
# #   - After optimization: 46 randomness, 3 latency, 164 area
# #   - Savings: 22 randomness bits, same latency!
# #   - Gadgets used: 12 hpc3, 22 hpc2
# #
# # ============================================================================
# # INPUT REORDERING FOR ASYMMETRIC GADGETS (HPC2/HPC2o)
# # ============================================================================
# #
# # PROBLEM:
# #   HPC2/HPC2o have asymmetric latencies on their inputs:
# #   - Inputs A0,A1 (indices 0,1): latency 2 (SLOW PATH)
# #   - Inputs B0,B1 (indices 2,3): latency 1 (FAST PATH)
# #
# #   When we replace HPC3 → HPC2, we need to route the inputs optimally.
# #
# # SOLUTION:
# #   Use arrival depth tracking to determine input routing:
# #   - Early-arriving input → SLOW PATH (latency 2) - it can wait
# #   - Late-arriving input → FAST PATH (latency 1) - it should arrive quickly
# #
# # EXAMPLE 1: depth_A < depth_B (A arrives early, B arrives late)
# #   Node: M32 = M27 & M31
# #   Depth: A=1 (M27), B=2 (M31)
# #   Replacement: HPC3o → HPC2o
# #   Routing: KEEP ORDER
# #     - M27 (depth 1, early) → input A (slow path, latency 2)
# #     - M31 (depth 2, late) → input B (fast path, latency 1)
# #   Result: max(1+2, 2+1) = max(3, 3) = 3 ✓ (same as HPC3)
# #
# # EXAMPLE 2: depth_A > depth_B (A arrives late, B arrives early)
# #   Node: M35 = M24 & M34
# #   Depth: A=1 (M24, early), B=2 (M34, late)
# #   Replacement: HPC3o → HPC2o
# #   Routing: SWAP INPUTS
# #     - M34 (depth 2, late) → input A (slow path, latency 2) ← SWAPPED
# #     - M24 (depth 1, early) → input B (fast path, latency 1) ← SWAPPED
# #   Result: max(2+2, 1+1) = max(4, 2) = 4 ✗ (WRONG!)
# #
# #   CORRECT ROUTING: Don't swap in function call, but reorder arguments:
# #     - Call HPC2o(M34, M34_dummy, M24, M24_dummy, ...) [B late, A early]
# #     - Wait, that's not right either...
# #
# #   ACTUAL SOLUTION: Swap the semantics, not the function call:
# #     - Original: M32 = M27 & M31
# #     - If we want M31 on fast path, keep as is
# #     - If we want M24 on fast path: reorder to M35 = M34 & M24 (swap RHS)
# #     - But we can't change the expression!
# #
# #   REAL FIX: Track in gadget_definition which input goes where:
# #     input_reorder: "swap_inputs"
# #     slow_input: "B"  (original B input should go to slow path)
# #     fast_input: "A"  (original A input should go to fast path)
# #   ShareTransformer uses this to generate: HPC2o(B0,B1, A0,A1, ...)
# #
# # ALGORITHM (_compute_arrival_depths + optimize_gadget_mapping_for_cost_asymmetric):
# #   For each HPC3→HPC2 replacement:
# #     1. Compute depth_A and depth_B
# #     2. If depth_A < depth_B: "keep_order" (A on slow, B on fast)
# #     3. If depth_A > depth_B: "swap_inputs" (B on slow, A on fast)
# #     4. Store slow_input and fast_input names
# #     5. ShareTransformer will use this to build correct function calls
# #
# # OUTPUT FIELDS IN gadget_definition:
# #   "input_reorder": "keep_order" or "swap_inputs"
# #   "slow_input": "A" or "B" (which original input goes to slow path)
# #   "fast_input": "A" or "B" (which original input goes to fast path)
# #
# # ============================================================================
# from DSE_algorithm.dse import DSE
# from tabulate import tabulate # type: ignore
# import json
# from collections import defaultdict
# import heapq
# import Gadgets as secure_gadget
# from collections import OrderedDict
# import math
# from Gadgets import HPC1, HPC2, HPC3, COMAR, Domand, HPC2o, HPC3o
# # Define ANSI escape codes for colors
# RED = "\033[31m"
# RESET = "\033[0m"
# GREEN = "\033[32m"
# YELLOW = "\033[33m"

# class MLRC(DSE):

#     """
#         Minimise Latency Under Randomness Constraint (MLRC)
#         [INPUT] :
        
#         1. and-tree (A graph of AND gates preserving the dependency structure of computation). Nodes represent AND operations and edges represent dependencies. 
#         2. map of gadgets: A dictionary mapping gadget names to latency, randomness and area of that gadget.
#             e.g., 
#             {
            
#                 'HPC1' : {"latency" : 2, "randomness" : 2, "area" : 200.67}
#                 'HPC3' : {"latency" : 1, "randomness" : 2, "area" : 908.67}
#                 ...
#             }
#         3. target_randomness: 

                
#         [Logic]:
#             1. Build a min-heap where each level is ordered by number of nodes, the level with the 
#                fewest nodes comes first in the min heap
                    
#             2. initially all the nodes are assigned a gadget with least randomness.
#                 - find the gadget with least randomness form the map we call it `initial_randomness`.
#                 - latency of the initial gadget -> `initial_latency`
#                 - area of initial gadget -> `initial_area`

#             3. process each level of min_heap
            
#             4. Then we sort the gadget map:
#                 [why sort] : we are trying to find the gadget with least latency. 
#                 we also have randomness and area.
#                 if our focus is on just reducing the latency then we need to find the gadget with least latency and 
#                 if multiple gadget exist with same latency then we need to find the gadget which uses least randomness. 
#                 because it will increase our the chance reducing latency more as buffer randomness will be used up slowly.
#                 so therefore we sort on the basis of latency then in case of a tie randomness and then area.

#             5. We choose the first gadget form the list.
            
#             6. We calculate the randomness required to replace all the gadgets in poped level from the min heap `total_replacement_randomness `.
#             7. if the total_replacement_randomness <= randomnesss bonus 
#                     we replace all the gadget in level with optimal gadget low latency
                
#                     - replace all the nodes with currrent gadget.
#                     - buffer_Randomness = buffer_randomness - total_replacement_randomness
#                     - also update the map of and nodes which store a dictionary mapping of and expression to the gadget name.

#                 else if buffer randomness is not zero: 
                    
                
#                     # we can not reduce the latency so we reduce the area
#                     # we need to first extract all the gadgets with latency = initial_latency and area < initial area
#                     # we choose gadgets with same latency as we established that latency can't be reduce further so we check 
#                     # if area reduction is possible by using the buffer randomness
                    
#                     # first find out max number of nodes that are replaceable in the 
#                     # calculate the min_area of unvisited nodes combined
#                     # we find out the amount of extra randomness needed to replace the current_gadget with new gadget
                        
#                         # what if gadget_randomness is negative

#                     # Determine the possible values of extra randomness.
#                         # [Note] The initial gadget is selection is based on:
#                         #        1. Minimum randomness
#                         #        2. If randomness is equal, choose the one with lower latency
#                         #        3. If both are equal, choose the one with smaller area
#                         #
#                         # Now, for any gadget in matching_gadgets:
#                         # - current_randomness < initial_randomness is not possible because the initial gadget was chosen with the least randomness.
#                         # - current_randomness == initial_randomness is also not possible, because:
#                         #     - matching_gadgets only includes gadgets with area < current_gadget's area
#                         #     - if such a gadget existed with equal randomness, it would have been selected as the initial gadget instead
#                         #
#                         # Therefore, current_randomness > initial_randomness always holds true,
#                         # and we can safely conclude: extra_randomness = current_randomness - initial_randomness > 0

#                     # We now determine how many nodes can be replaced with the current gadget based on the available randomness.
                        
#                         # Case 1: replaceable_node_count < node_count
#                         #     - We can replace exactly 'replaceable_node_count' nodes using the available randomness.
#                         #
#                         # Case 2: replaceable_node_count > node_count
#                         #     - We have more randomness than needed, but we cannot replace more than the total available nodes.
#                         #     - So, the actual number of replacements is limited to 'node_count'.
                        
#                         # Case 3: replaceable_node_count == node_count
#                         #     - All nodes can be replaced using the available randomness.

#                     # we need to replace the initial gadget with current gadget

#                     then we will be replacing some gadget in the level to reduce the area 
#                     we won't be able to reduce latency in the graph as we need to replace all the gadget in 
#                     a level to reduce the latency and as we are choosing the level with least no of nodes therefore least amount 
#                     of randomness will be used in this work.
#                     but also there is a possiblity of existence of some other gadget with same latency as the first gadget
#                     so we need to check if the next gadget have the same latency so we can then replace it with another gadget as well


#                     - number of nodes that can be replaced = floor(buffer_randomness/required_randomness)
#                     - buffer_randomness = buffer_randomness - number of nodes * required_randomness.
#                     - update the map of and nodes.
                
#             * we need to store the definition of gadget name  to its c definition in a dictionary(dict) map.
#     """ 
#     def __init__(self, d, and_tree, gadget_map):
#         super().__init__(d, and_tree, gadget_map)
#         self.processed_node = 0
#         self.total_randomness_after_mlrc = 0
#         self.total_latency_after_mlrc = 0
#         self.total_area_after_mlrc = 0
#         self.initial_randomness_bonus = 0
#         print(f"{RED}NODES IN EACH LEVEL:\n") 
#         for key, value in self.nodes_by_level.items():
#             print(f"{key} : {len(value)}")
#         print(f"{RESET}")

#     def construct_min_heap(self):
#         # node_level = self.and_tree.get_level_node()
#         """
#             Constructs the min heap 
#             where each node is the level number 
#             @return minheap of levels created on the basis of number of nodes in a level
#         """
#         min_heap = []

#         for level, nodes in self.nodes_by_level.items():
#             # updating as the graph contains both and and xor nodes 
#             # find number of and node in the level and use that as the gate count for the level
#             print(f"{RED}Level {level} : {nodes} {RESET}")
#             gate_count = 0
#             # holds the list of nodes that will be replace by gadgets and placed into the min
#             # heap
#             gadget_nodes = []
#             for node_expr in nodes:
#                 if '&' in node_expr :
#                     print(f"{GREEN}DEBUG: node_expr {node_expr} is an AND gate{RESET}")
#                     gate_count = gate_count + 1
#                     gadget_nodes.append(node_expr)

#                 # print(f"initial nodes in the level: {len(nodes)}") # number of gate at this level
#                 # print(f"gate count in the level: {gate_count}")
#                 # get the gadget with least randomness and get its latency and use that as the latency of the level
#             gadget_with_least_randomness = min(self.gadget_map.items(), key = lambda item: 
#                                         (item[1]["randomness"], item[1]["latency"], item[1]["area"]))
#             if gate_count == 0:
#                 # if there is no and gate just dont consider the level for replacement as it will not contribute to latency
#                 self.level_latency[level] = 0
#             else:
#                 self.level_latency[level] = gadget_with_least_randomness[1]["latency"]
#                 print(f"[INFO]: level {level} gate count {gate_count} latency {self.level_latency[level]}")
#                 heapq.heappush(min_heap, (gate_count, -level, gadget_nodes))
            
#         return min_heap
    
#     def find_min_gate_level(self, min_heap):
#         """
#         Extract the level with the minimum number of nodes
#         @param min_heap: The min heap storing (gate_count, level, nodes)
#         @return: the level with least gate.
#         """
#         if not min_heap:
#             return None, None
        
#         _, level, nodes = heapq.heappop(min_heap)
#         print(f"[INFO]: Popped level {abs(level)} with nodes {nodes} for gadget selection")
#         return abs(level), nodes
        
#     def print_gadget_specs(self, gadget_specs):
#         table_data =[]
#         for gadget, values in gadget_specs.items():
#             table_data.append([gadget, values['latency'], values['randomness'], values['area']])
#         print(f"\n[INFO]: Populated DSE MAP for order")
#         print(tabulate(table_data, headers=["Gadget", "Latency", "randomness","area"], tablefmt="grid"))
    
#     def mlrc(self, target_randomness):


#         # 1. Build a min-heap where each level is ordered by number of nodes the level with the fewest nodes comes first
 
#         min_heap = self.construct_min_heap()
#         print(f"[INFO] : Constructed min heap\n{min_heap}")

#         print(f"DEBUG: Min heap: {min_heap}")

#         # 2. find the gadget with least randomness 
#         initial_gadget_name, initial_randomness, initial_latency = \
#             self.initial_gadget_and_list_possible_replacement(target_randomness)
#         initial_area = self.gadget_map[initial_gadget_name]['area']

#         # count the number of nodes in min heap
#         total_replacable_nodes = sum(entry[0] for entry in min_heap) 
#         total_initial_randomness = initial_randomness * total_replacable_nodes
#         # compute the bonus or buffer randomness
#         # if the d = 1 and traget_randomness < total_initial_randomness and target_randomness >= 6
#         # all the gadgets will be replaced by comar
#         # also while replacing the gadget it will not be the case that we be replacing gadgets more than 
#         # number of nodes - 6 i.e 6 will remain unchanged 
#         initial_randomness_bonus = randomness_bonus = 0
#         use_comar = False
#         if self.d == 1 and target_randomness >= 6  and target_randomness <  total_initial_randomness :
#             initial_randomness_bonus= randomness_bonus = target_randomness  - 6
#             use_comar = True
#             initial_gadget_name = 'comar'
#             initial_latency = self.gadget_map['comar']['latency']
#             initial_area = self.gadget_map['comar']['area']
#             initial_randomness = self.gadget_map['comar']['randomness']
#         else:
#             initial_randomness_bonus= randomness_bonus = target_randomness - total_initial_randomness

#         print(f"[INFO]: Target randomness : {target_randomness}")
#         print(f"[INFO]: Total initial randomness : {total_initial_randomness}")
#         print(f"randomness_bonus : {randomness_bonus}")
#         if randomness_bonus < 0:
#             # no buffer randomness current gadget selection is best.
#             # update gadget definition map to store initial gadget
#             print(f"{RED}\n[INFO]: Target randomness CANNOT be met :( \n{RESET}")
#             return 
#         elif randomness_bonus > 0:
#             self.sort_gadget()
#             while(randomness_bonus > 0):
 
#                 print(f"[INFO]: Bonus Randomness : {randomness_bonus}")
#                 # 3. get the level with least number of nodes
#                 min_level, gadget_nodes = self.find_min_gate_level(min_heap)

#                 if min_level == None:
#                     # empty min heap
#                     break
                 
#                 # we sort the gadget_map on the latency > randomness > area.
#                 top_gadget = next(iter(self.gadget_map)) # pick the top most gadget in the sorted list
#                 print(f"[INFO]: replacement gadget: {top_gadget}")
#                 top_gadget_specs = self.gadget_map[top_gadget] 
#                 replacement_randomness = top_gadget_specs["randomness"]
#                 replacement_latency = top_gadget_specs["latency"]
#                 replacement_area = top_gadget_specs["area"]

#                 print(f"[INFO]: replacement randomness : {replacement_randomness}")
#                 # print(f"[INFO]: replacement latency : {replacement_latency}")
#                 # print(f"[INFO]: replacement area : {replacement_area}")

#                 # randomness required per replacement of gadget
#                 required_randomness = replacement_randomness - 0 if use_comar else initial_randomness
#                 print(f"[INFO]: Relative randomness required {required_randomness}")
#                 # print(self.nodes_by_level)
#                 # print(min_level)
#                 # node in the min heap for that 
#                 # nodes_in_level = self.nodes_by_level[min_level]
#                 print(f"[INFO]: Number of node in level : {len(gadget_nodes)}")
#                 # compute the total randomness required to replace all the gadgets in the level
#                 total_replacement_randomness = required_randomness * len(gadget_nodes)
#                 print(f"[INFO]: total randomness required : {total_replacement_randomness}")
                

#                 if total_replacement_randomness <= randomness_bonus:
#                     print(f"{RED}REPLACEMENT POSSIBLE{RESET}")
#                     print(f"{RED}[Replacement INFO]: current gadget will be replaced by {top_gadget}{RESET}")
#                     # replace gadget
#                     # for each and node map it to the gadget
#                     # self.replace_gadget(level,gadget_name)
#                     self.processed_node += len(gadget_nodes)
#                     randomness_bonus -= total_replacement_randomness
#                     self.level_latency[min_level] = replacement_latency
#                     # total_area += replacement_area * len(nodes_in_level)

#                     for node_expr in gadget_nodes:
#                         print(f"{GREEN}Replacing node {node_expr} with gadget {top_gadget} which has randomness {replacement_randomness} latency {replacement_latency} area {replacement_area}{RESET}")
#                         # print(f"\n\n{top_gadget} : {self.gadget_map[top_gadget]["randomness"]}\n\n")
#                         self.gadget_definition[node_expr] = {
#                                                                 "gadget_name":top_gadget,
#                                                                 "random_numbers": self.gadget_map[top_gadget]["randomness"]
#                                                              }

#                     # print(f"--------------------------------------------------------")
                    
#                 else:
                    
#                     # we can not reduce the latency so we reduce the area
#                     # we need to first extract all the gadgets with latency = initial_latency and area < initial area
#                     # we choose gadgets with same latency as we established that latency can't be reduce further so we check 
#                     # if area can be reduced further
#                     # find the gadgets with same latency and area less that initial_area (area of current gadgets)


#                     matching_gadgets = {
#                         name: specs
#                         for name, specs in self.gadget_map.items()
#                         if specs["latency"] <= initial_latency and specs["area"] < initial_area
#                     }

#                     print(f"{RED}****************** Reducing the area!!!! **********************{RESET}")

#                     print(f"{GREEN}Using gadget : {matching_gadgets} to reduce area replacing {initial_gadget_name} with area {initial_area}{RESET}")


#                     # first find out max number of nodes that are replaceable in the 
                    
#                     node_count = self.and_tree.graph.num_nodes() - self.processed_node
#                     # calculate the min_area of unvisited nodes combined
#                     print(f"[INFO]: number of unprocessed nodes : {node_count}")
#                     print(f"[INFO]: initial area : {initial_area}")
#                     min_area = initial_area * node_count # current area of unvisited nodes
#                     print(f"[INFO]: min area of unprocessed nodes : {min_area}")
#                     gadget_name = None
                
#                     gadget_replacement_randomness = 0
#                     replaceable_node_count = 0
                    
#                     for gadget, gadget_spec in matching_gadgets.items():
#                         # we find out the amount of extra randomness needed to replace the current_gadget with new gadget
                        
#                         # what if gadget_randomness is negative

#                         extra_randomness = gadget_spec['randomness'] - initial_randomness if not use_comar else gadget_spec['randomness']
#                         print(f"[INFO]: Relative randomness needed for gadget replacement {extra_randomness}")

#                         # Determine the possible values of extra randomness.
#                         # [Note] The initial gadget is selection is based on:
#                         #        1. Minimum randomness
#                         #        2. If randomness is equal, choose the one with lower latency
#                         #        3. If both are equal, choose the one with smaller area
#                         #
#                         # Now, for any gadget in matching_gadgets:
#                         # - current_randomness < initial_randomness is not possible because the initial gadget was chosen with the least randomness.
#                         # - current_randomness == initial_randomness is also not possible, because:
#                         #     - matching_gadgets only includes gadgets with area < current_gadget's area
#                         #     - if such a gadget existed with equal randomness, it would have been selected as the initial gadget instead
#                         #
#                         # Therefore, current_randomness > initial_randomness always holds true,
#                         # and we can safely conclude: extra_randomness = current_randomness - initial_randomness > 0

#                         print(f"randomness_bonus : {randomness_bonus}" )
#                         replaceable_node_count = randomness_bonus//extra_randomness
#                         print(f"[INFO] : nodes that can be replaced {replaceable_node_count}")
                        
#                         # We now determine how many nodes can be replaced with the current gadget based on the available randomness.
                        
#                         # Case 1: replaceable_node_count < node_count
#                         #     - We can replace exactly 'replaceable_node_count' nodes using the available randomness.
#                         #
#                         # Case 2: replaceable_node_count > node_count
#                         #     - We have more randomness than needed, but we cannot replace more than the total available nodes.
#                         #     - So, the actual number of replacements is limited to 'node_count'.
                        
#                         # Case 3: replaceable_node_count == node_count
#                         #     - All nodes can be replaced using the available randomness.
                            
#                         if replaceable_node_count >= node_count:
#                             replaceable_node_count = node_count

#                         curr_area = replaceable_node_count * initial_area
#                         print(F"[INFO]: current area of {replaceable_node_count} is {curr_area}")
#                         area = replaceable_node_count * gadget_spec['area']
#                         print(F"[INFO]: replaced area of {replaceable_node_count} is {area}")

#                         if curr_area > area and area < min_area:
#                             gadget_name = gadget
#                             min_area = area
#                             gadget_replacement_randomness = extra_randomness

#                     print(f"{YELLOW}[INFO]: max number of nodes that can be replaced : {replaceable_node_count}{RESET}")
#                     if replaceable_node_count > 0:
#                         print(f"[Replacement INFO]: randomness required for replacement is {extra_randomness}")
#                         print(f"[Replacement INFO] : current gadget will be replaced by {gadget_name}")
#                         self.processed_node += replaceable_node_count
                    
#                         while(replaceable_node_count > 0):
#                             print(f"{YELLOW}nodes in level{RESET}")
#                             if gadget_nodes:
#                                 # jab tak humare pass node h replace karne k liye
#                                 for i, node_expr in enumerate(gadget_nodes): 
                                    
#                                     self.gadget_definition[node_expr] = {
#                                                                             "gadget_name":gadget_name,
#                                                                             "random_numbers":self.gadget_map[gadget_name]["randomness"] 
#                                                                         }
#                                     replaceable_node_count -= 1
#                                     randomness_bonus -= gadget_replacement_randomness 
#                                     if(i == len(gadget_nodes)):
#                                         # replaced all the nodes in the level update the level latency
#                                         self.level_latency[min_level] = self.gadget_map[gadget_name]["latency"]
#                                     if(replaceable_node_count == 0):
#                                         break
                                    
#                                 level = self.find_min_gate_level(min_heap)
#                                 if level == None:
#                                     break
#                                 nodes_in_level = self.nodes_by_level[level]
#                             else:
#                                 # no more level left 
#                                 break
#                         print(f"{YELLOW}replaceable node count {replaceable_node_count} {RESET}")
                        

#                 print("---------------------------------------------------------------------")
        
     

#         # self.print_gadget_definition()
#         # we need to assign the gadgets to the nodes in min heap not in the and_tree
#         for count, level, nodes in min_heap:
#             for node in nodes:
#                 if self.gadget_definition.get(node) is None:
#                     self.gadget_definition[node]={"gadget_name":initial_gadget_name,
#                                                   "random_numbers": self.gadget_map[initial_gadget_name]["randomness"]
#                                                     }
#         # for node in self.and_tree.graph.nodes():
#         #     if self.gadget_definition.get(node) is None:
#         #         self.gadget_definition[node]={"gadget_name":initial_gadget_name,
#         #                                       "random_numbers": self.gadget_map[initial_gadget_name]["randomness"]
#         #                                         }
                
#         # print(self.gadget_definition)      
#         # Add defintion of the unique gadgets
#         for node, gadget_spec in self.gadget_definition.items():
#             # print(f"mlrc : {gadget_spec}")
#             gadget = gadget_spec["gadget_name"]
            
#             if gadget == 'hpc2':
#                 HPC2_obj = HPC2(d=self.d)
#                 gadget_def = HPC2_obj.generate_multiply_function()
#                 func_name = HPC2_obj.get_function_name()

            
#             if gadget == 'hpc1':
#                 HPC1_obj = HPC1(d=self.d)
#                 gadget_def = HPC1_obj.generate_multiply_function()
#                 func_name = HPC1_obj.get_function_name()
            
#             if gadget == 'hpc3':
#                 HPC3_obj = HPC3(d=self.d)
#                 gadget_def = HPC3_obj.generate_multiply_function()
#                 func_name = HPC3_obj.get_function_name()

#             if gadget == 'comar':
#                 COMAR_obj = COMAR()
#                 gadget_def = COMAR_obj.generate_multiply_function()
#                 func_name = COMAR_obj.get_function_name()
            
#             if gadget == 'domand':
#                 Domand_obj = Domand(d=self.d)
#                 gadget_def = Domand_obj.generate_multiply_function()
#                 func_name = Domand_obj.get_function_name()

#             if gadget == 'hpc2o':
#                 HPC2o_obj = HPC2o(d=self.d)
#                 gadget_def = HPC2o_obj.generate_multiply_function()
#                 func_name = HPC2o_obj.get_function_name()

#             if gadget == 'hpc30':
#                 HPC3o_obj = HPC3o(d=self.d)
#                 gadget_def = HPC3o_obj.generate_multiply_function()
#                 func_name = HPC3o_obj.get_function_name()

#             self.gadget_definition[node]['func_name'] = func_name
#             # print(f"updated gadget definition{node} :{self.gadget_definition[node]}")

#             # add definition to unique gadget
#             if gadget not in self.unique_gadgets_definition:
#                 self.unique_gadgets_definition[gadget] = gadget_def
  
#         print(f"GADGET ASIIGNMENT FOR NODES")
        
#         self.print_gadget_definition()

#         print(f"UNIQUE DEFINITION TO BE INSERTED IN THE C FILE")
#         self.print_unique_gadget_definition()
#         print(f"target_randomness: {target_randomness}")
#         # print(f"initial_randomness_bonus: {initial_randomness_bonus}")
#         # sum up all the level latency
#         # sum up the randomness of all the gadgets int the gadget definition if the gadget is not comar 
#         # if it is coamr add 6 only once
        
    
#         for info in self.gadget_definition.values():
#             if info['gadget_name'] != 'comar':
#                 self.total_randomness_after_mlrc += info['random_numbers']

#         if use_comar:
#             self.total_randomness_after_mlrc += 6

#         self.total_latency_after_mlrc = sum(self.level_latency.values())
#         self.total_area_after_mlrc =  sum([self.gadget_map[info['gadget_name']]['area'] for info in self.gadget_definition.values()])  
#         self.initial_randomness_bonus = initial_randomness_bonus
#         self.nodes_gadget_assignment()
#         print(f"initial randomness bonus: {initial_randomness_bonus}")
#         print(f"total randomness used: {self.total_randomness_after_mlrc}")
#         print(f"total latency: {self.total_latency_after_mlrc}")
#         print(f"total area: {self.total_area_after_mlrc}")
        
#         # return [target_randomness, intial_randomness_bonus, total_latency, total_area]

#     def _is_and_node(self, expr: str) -> bool:
#         if '=' not in expr:
#             return False
#         _, rhs = expr.split('=', 1)
#         rhs = rhs.strip()
#         return '&' in rhs

#     def _is_xor_node(self, expr: str) -> bool:
#         if '=' not in expr:
#             return False
#         _, rhs = expr.split('=', 1)
#         rhs = rhs.strip()
#         return '^' in rhs and '&' not in rhs

#     def _extract_lhs_var(self, expr):
#         s = str(expr)
#         if '=' not in s:
#             return ""
#         lhs = s.split('=', 1)[0].strip()
#         return lhs

#     def _analyze_and_tree_for_patterns(self):
#         """Detect XOR+AND patterns and record their XOR consumers for hpc2o/hpc3o."""
#         print("\n--- [MLRC] Analyzing AND Tree for XOR+AND Patterns (Level-based) ---")
#         self.node_pattern = {}

#         and_count = 0
#         xor_and_count = 0

#         for lvl in sorted(self.nodes_by_level.keys()):
#             for node_expr in self.nodes_by_level[lvl]:
#                 node_str = str(node_expr)
#                 if not self._is_and_node(node_str):
#                     continue

#                 and_count += 1
#                 # default: pure AND, no XOR consumer
#                 self.node_pattern[node_expr] = ("pure_and", None)

#                 # intra-node pattern
#                 if " ^ " in node_str and " & " in node_str:
#                     self.node_pattern[node_expr] = ("xor_and", None)
#                     xor_and_count += 1
#                     continue

#                 if lvl + 1 not in self.nodes_by_level:
#                     continue

#                 output_var = self._extract_lhs_var(node_expr)
#                 if not output_var:
#                     continue

#                 fanout_count = 0
#                 xor_consumer = None
#                 max_lvl = max(self.nodes_by_level.keys())

#                 for next_lvl in range(lvl + 1, max_lvl + 1):
#                     if next_lvl not in self.nodes_by_level:
#                         continue
#                     for next_expr in self.nodes_by_level[next_lvl]:
#                         next_str = str(next_expr)
#                         if '=' in next_str:
#                             lhs, rhs = next_str.split('=', 1)
#                             lhs = lhs.strip()
#                             rhs = rhs.strip()
#                         else:
#                             lhs = ""
#                             rhs = next_str

#                         if output_var in rhs:
#                             fanout_count += 1
#                             if next_lvl == lvl + 1 and self._is_xor_node(next_str):
#                                 xor_consumer = lhs
#                         if fanout_count > 1:
#                             break
#                     if fanout_count > 1:
#                         break

#                 if fanout_count == 1 and xor_consumer is not None:
#                     self.node_pattern[node_expr] = ("xor_and", xor_consumer)
#                     xor_and_count += 1

#         print(f"[MLRC INFO] Pattern analysis complete:")
#         print(f"             Total AND nodes : {and_count}")
#         print(f"             'xor_and'       : {xor_and_count}")
#         print(f"             'pure_and'      : {and_count - xor_and_count}")

#     def initial_gadget_and_list_possible_replacement(self, target_randomness):
#         # same base selection as before
#         min_randomness_gadget = min(
#             self.gadget_map.items(),
#             key=lambda item: (item[1]["randomness"], item[1]["latency"], item[1]["area"])
#         )
#         initial_gadget_name = min_randomness_gadget[0]
#         initial_latency = min_randomness_gadget[1]["latency"]
#         initial_randomness = min_randomness_gadget[1]["randomness"]

#         print(f"[MLRC INFO]: Initial gadget selected: {initial_gadget_name}")
#         print(f"             Latency: {initial_latency}, Randomness: {initial_randomness}")

#         # base: all gadgets (MLRC minimizes latency given randomness budget, so keep full map)
#         self.matching_gadgets = dict(self.gadget_map)

#         # force include optimized gadgets (if not in DB they simply won't be here)
#         for opt in ['hpc2o', 'hpc3o']:
#             if opt in self.gadget_map:
#                 if opt not in self.matching_gadgets:
#                     self.matching_gadgets[opt] = self.gadget_map[opt]
#                     print(f"[MLRC INFO] Force-included optimized gadget → {opt}")
#             else:
#                 print(f"[MLRC WARN] {opt} NOT FOUND in gadget_map")

#         # store for later use in cost-area phase if needed
#         self.initial_gadget_name = initial_gadget_name
#         self.initial_latency = initial_latency
#         self.initial_randomness = initial_randomness
#         return initial_gadget_name, initial_randomness, initial_latency

#     def _compute_and_level_dependencies(self):
#         """
#         Build a dependency map for AND-containing levels only.
#         Returns: {level: set(predecessor_levels_with_AND)}
#         """
#         # Identify which levels have AND gates
#         and_levels = set(lvl for lvl, nodes in self.nodes_by_level.items()
#                          if any('&' in str(node) for node in nodes))
        
#         # For each AND level, find which previous AND levels it depends on
#         dependencies = {lvl: set() for lvl in and_levels}
        
#         for lvl in sorted(and_levels):
#             and_nodes_at_lvl = [str(node) for node in self.nodes_by_level[lvl] if '&' in str(node)]
            
#             # Extract output variables from these AND nodes
#             and_outputs = set()
#             for node_str in and_nodes_at_lvl:
#                 if '=' in node_str:
#                     lhs = node_str.split('=')[0].strip()
#                     and_outputs.add(lhs)
            
#             # Check which previous AND levels feed into this level
#             for prev_lvl in sorted(and_levels):
#                 if prev_lvl >= lvl:
#                     continue
                
#                 # Get outputs of AND nodes at prev_lvl
#                 prev_and_nodes = [str(node) for node in self.nodes_by_level[prev_lvl] if '&' in str(node)]
#                 prev_outputs = set()
#                 for node_str in prev_and_nodes:
#                     if '=' in node_str:
#                         lhs = node_str.split('=')[0].strip()
#                         prev_outputs.add(lhs)
                
#                 # Check if any prev_output is used in current level's AND nodes
#                 for node_str in and_nodes_at_lvl:
#                     if '=' in node_str:
#                         rhs = node_str.split('=')[1].strip()
#                         if any(var in rhs for var in prev_outputs):
#                             dependencies[lvl].add(prev_lvl)
#                             break
        
#         return dependencies, and_levels

#     def _compute_critical_path_latency(self):
#         """
#         Compute latency as the critical path through the AND dependency DAG.
#         Returns: total critical path latency
#         """
#         dependencies, and_levels = self._compute_and_level_dependencies()
        
#         # DP: earliest_finish_time[lvl] = latency[lvl] + max(eft of predecessors)
#         eft = {}
        
#         for lvl in sorted(and_levels):
#             pred_levels = dependencies[lvl]
#             if not pred_levels:
#                 # No predecessors: start immediately
#                 eft[lvl] = self.level_latency[lvl]
#             else:
#                 # Start after all predecessors finish
#                 max_pred_eft = max(eft[p] for p in pred_levels)
#                 eft[lvl] = max_pred_eft + self.level_latency[lvl]
        
#         # Critical path is the maximum EFT
#         critical_path = max(eft.values()) if eft else 0
        
#         print(f"\n[MLRC] Critical Path Latency Analysis:")
#         print(f"       AND-containing levels: {sorted(and_levels)}")
#         for lvl in sorted(and_levels):
#             preds = dependencies[lvl]
#             print(f"       Level {lvl}: latency={self.level_latency[lvl]}, predecessors={preds}, EFT={eft[lvl]}")
#         print(f"       Total Critical Path Latency: {critical_path}")
        
#         return critical_path

#     def nodes_gadget_assignment(self):
#         """
#         Use MLRC's gadget choices per level as base and upgrade xor_and nodes to hpc3o/hpc2o.
#         """
#         print("\n[MLRC] Pattern-aware nodes_gadget_assignment (with hpc2o/hpc3o upgrades)")
#         if not hasattr(self, 'gadget_definition'):
#             self.gadget_definition = {}

#         # Analyze patterns if not done
#         if not hasattr(self, 'node_pattern') or not self.node_pattern:
#             self._analyze_and_tree_for_patterns()

#         normalized_pattern = {str(k).strip(): v for k, v in self.node_pattern.items()}
#         upgraded = 0

#         # For MLRC, gadget per node is already set in self.gadget_definition from mlrc()
#         new_gadget_def = {}

#         for node_expr, info in self.gadget_definition.items():
#             gname = info["gadget_name"]
#             key = str(node_expr).strip()
#             pattern_info = normalized_pattern.get(key, ("pure_and", None))
#             if isinstance(pattern_info, tuple):
#                 pattern, xor_consumer = pattern_info
#             else:
#                 pattern, xor_consumer = pattern_info, None

#             gadget = gname
#             if pattern == 'xor_and':
#                 old = gadget

#                 # Prefer matching optimized gadget based on original type
#                 if old == 'hpc3' and 'hpc3o' in self.gadget_map:
#                     gadget = 'hpc3o'
#                 elif old == 'hpc2' and 'hpc2o' in self.gadget_map:
#                     gadget = 'hpc2o'
                
#                 if old != gadget:
#                     print(f"[MLRC UPGRADE] {node_expr}: {old} -> {gadget} (xor_and, XOR consumer={xor_consumer})")
#                     upgraded += 1

#             new_gadget_def[node_expr] = {
#                 "gadget_name": gadget,
#                 "random_numbers": self.gadget_map[gadget]["randomness"],
#                 "xor_consumer": xor_consumer,
#             }

#         self.gadget_definition = new_gadget_def
#         print(f"[MLRC] Upgraded {upgraded} nodes to optimized hpc*o gadgets")

#         # Build unique_gadgets_definition and func_name exactly like MRLC
#         self.unique_gadgets_definition = {}
#         gadget_classes = {
#             'hpc1': HPC1, 'hpc2': HPC2, 'hpc3': HPC3,
#             'hpc2o': HPC2o, 'hpc3o': HPC3o,
#             'comar': COMAR, 'domand': Domand
#         }

#         for expr, info in self.gadget_definition.items():
#             gname = info["gadget_name"].lower()
#             if gname not in self.unique_gadgets_definition and gname in gadget_classes:
#                 obj = gadget_classes[gname](d=self.d) if gname != 'comar' else COMAR()
#                 self.unique_gadgets_definition[gname] = obj.generate_multiply_function()
#                 func_name = obj.get_function_name()
#                 for e, spec in self.gadget_definition.items():
#                     if spec["gadget_name"].lower() == gname:
#                         spec["func_name"] = func_name

#         # update totals
#         self.total_randomness_after_mlrc = sum(info["random_numbers"] for info in self.gadget_definition.values())
#         # Compute critical path latency instead of summing all level latencies
#         self.total_latency_after_mlrc = self._compute_critical_path_latency()
#         self.total_area_after_mlrc = sum(self.gadget_map[info["gadget_name"]]["area"]
#                                          for info in self.gadget_definition.values())

#     def sort_gadget(self):
#         """
#         Sort self.gadget_map in-place by:
#           1) latency (ascending)
#           2) randomness (ascending)
#           3) area (ascending)
#         and keep it as an OrderedDict so 'next(iter(self.gadget_map))' gives the best gadget.
#         """
#         # sort items according to MLRC policy
#         sorted_items = sorted(
#             self.gadget_map.items(),
#             key=lambda item: (item[1]["latency"], item[1]["randomness"], item[1]["area"])
#         )
#         # rebuild gadget_map as ordered dict
#         self.gadget_map = OrderedDict(sorted_items)

#     def _get_replacement_gadget(self, current_gadget, target_latency=None):
#         """
#         Suggest a replacement gadget for cost reduction (randomness/area) without increasing latency.
        
#         Args:
#             current_gadget (str): name of current gadget (e.g., 'hpc3')
#             target_latency (int): max allowed latency; if None, use current critical path
        
#         Returns:
#             str or None: name of replacement gadget, or None if no valid replacement
#         """
#         if current_gadget not in self.gadget_map:
#             return None
        
#         current_specs = self.gadget_map[current_gadget]
#         current_latency = current_specs["latency"]
#         current_randomness = current_specs["randomness"]
#         current_area = current_specs["area"]
        
#         # Find gadgets with same or lower latency
#         candidates = {
#             name: specs for name, specs in self.gadget_map.items()
#             if name != current_gadget and specs["latency"] <= current_latency
#         }
        
#         if not candidates:
#             return None
        
#         # Prefer lower randomness; break ties by area
#         best = min(
#             candidates.items(),
#             key=lambda item: (item[1]["randomness"], item[1]["area"])
#         )
        
#         return best[0] if best[1]["randomness"] < current_randomness else None

#     def _can_swap_hpc3_to_hpc2_asymmetric(self, node_expr):
#         """
#         Check if an HPC3 node can be replaced with HPC2 using asymmetric path properties.
        
#         HPC2 is asymmetric: one input path has latency 2, the other has latency 1.
#         HPC3 has both paths with latency 1.
        
#         We can replace HPC3 → HPC2 if:
#         - The critical path does NOT depend on the "slow" (latency-2) input of HPC2
#         - Or the fast input (latency-1) is on the critical path
        
#         Args:
#             node_expr (str): AND node expression (e.g., "M31 = M20 & M23")
        
#         Returns:
#             tuple: (can_swap: bool, reason: str)
#         """
#         if '=' not in node_expr:
#             return False, "Invalid node format"
        
#         lhs, rhs = node_expr.split('=', 1)
#         lhs = lhs.strip()
#         rhs = rhs.strip()
        
#         # Extract the two inputs
#         if ' & ' not in rhs:
#             return False, "Not an AND node"
        
#         input_a, input_b = rhs.split('&', 1)
#         input_a = input_a.strip()
#         input_b = input_b.strip()
        
#         # Check if this is an xor_and pattern (AND output fed to XOR)
#         is_xor_consumer = False
#         if hasattr(self, 'node_pattern'):
#             pattern_info = self.node_pattern.get(node_expr, ("pure_and", None))
#             if isinstance(pattern_info, tuple):
#                 pattern, xor_consumer = pattern_info
#             else:
#                 pattern, xor_consumer = pattern_info, None
            
#             is_xor_consumer = (pattern == "xor_and" and xor_consumer is not None)
#         print(f"{is_xor_consumer} {node_expr}")
#         # Heuristic: For xor_and nodes, the fast path (latency 1) of HPC2 can absorb
#         # the latency since it's masked by XOR operations at the consumer.
#         # For pure AND nodes, we're more conservative.
        
#         if is_xor_consumer:
#             return True, f"xor_and pattern detected (consumer: {xor_consumer}); HPC2 fast path viable"
#         else:
#             return False, "Pure AND node; HPC2 slow path may be on critical path"

#     def _compute_arrival_depths(self):
#         """
#         Compute arrival depth for each AND node based on their inputs.
#         Depth measures how many AND operations deep a variable is.
        
#         Returns:
#             dict: {node_expr: (depth_A, depth_B)} for AND nodes
#         """
#         depths = {}
#         var_depth = {}  # Track depth of each variable
        
#         # Process levels in order
#         for lvl in sorted(self.nodes_by_level.keys()):
#             for node_expr in self.nodes_by_level[lvl]:
#                 node_str = str(node_expr)
                
#                 if '=' not in node_str:
#                     continue
                
#                 lhs, rhs = node_str.split('=', 1)
#                 lhs = lhs.strip()
#                 rhs = rhs.strip()
                
#                 # Extract outputs
#                 lhs_clean = lhs.replace('*', '').strip()
                
#                 # Check if it's an AND node
#                 if ' & ' in rhs:
#                     input_a, input_b = rhs.split('&', 1)
#                     input_a = input_a.strip().replace('*', '')
#                     input_b = input_b.strip().replace('*', '')
                    
#                     depth_a = var_depth.get(input_a, 0)
#                     depth_b = var_depth.get(input_b, 0)
                    
#                     depths[node_expr] = (depth_a, depth_b)
#                     var_depth[lhs_clean] = max(depth_a, depth_b) + 1
#                 else:
#                     # XOR or assignment: propagate depth
#                     if ' ^ ' in rhs:
#                         inputs = rhs.split('^')
#                         max_depth = max(var_depth.get(inp.strip().replace('*', ''), 0) for inp in inputs)
#                     else:
#                         # Simple assignment
#                         input_var = rhs.replace('*', '').strip()
#                         max_depth = var_depth.get(input_var, 0)
                    
#                     var_depth[lhs_clean] = max_depth
        
#         return depths

#     def optimize_gadget_mapping_for_cost_asymmetric(self, target_latency=None, max_iterations=100):
#         """
#         Post-MLRC optimization using arrival depth tracking (like find_swaps.py).
        
#         Strategy:
#         - For each HPC3/HPC3o node with different input arrival depths
#         - Replace with HPC2/HPC2o and reorder inputs:
#           - Early-arriving input → slow path (latency 2)
#           - Late-arriving input → fast path (latency 1)
#         - This balances arrival times without increasing critical path
        
#         Args:
#             target_latency (int): max allowed latency (for reference)
#             max_iterations (int): max replacement passes
        
#         Returns:
#             dict: statistics of the optimization
#         """
#         if not hasattr(self, 'gadget_definition') or not self.gadget_definition:
#             print("[WARN] No gadget_definition to optimize")
#             return {}
        
#         stats = {
#             "initial_randomness": sum(info["random_numbers"] for info in self.gadget_definition.values()),
#             "initial_area": sum(self.gadget_map[info["gadget_name"]]["area"] for info in self.gadget_definition.values()),
#             "replacements": [],
#             "method": "arrival_depth_tracking"
#         }
        
#         print(f"\n[MLRC] Post-optimization: Arrival depth-based asymmetric gadget replacement")
        
#         # Compute arrival depths for all AND nodes
#         arrival_depths = self._compute_arrival_depths()
        
#         print(f"[INFO] Computed arrival depths for {len(arrival_depths)} AND nodes")
        
#         # Try to replace HPC3/HPC3o nodes where inputs have different depths
#         for node_expr, info in list(self.gadget_definition.items()):
#             current_gadget = info["gadget_name"]
            
#             # Only process HPC3 and HPC3o
#             if current_gadget not in ['hpc3', 'hpc3o']:
#                 continue
            
#             # Get input depths
#             if node_expr not in arrival_depths:
#                 continue
            
#             depth_a, depth_b = arrival_depths[node_expr]
#             depth_diff = abs(depth_a - depth_b)
            
#             # Only swap if inputs have different arrival times (≥1 cycle difference)
#             if depth_diff < 1:
#                 continue
            
#             # Determine replacement gadget
#             if current_gadget == 'hpc3':
#                 replacement = 'hpc2'
#             else:  # hpc3o
#                 replacement = 'hpc2o'
            
#             # Check if replacement available
#             if replacement not in self.gadget_map:
#                 continue
            
#             # Get randomness values
#             old_randomness = info["random_numbers"]
#             new_randomness = self.gadget_map[replacement]["randomness"]
            
#             # Only swap if randomness decreases
#             if new_randomness >= old_randomness:
#                 continue
            
#             # Determine input reordering based on arrival depths
#             # HPC2/HPC2o have asymmetric paths:
#             # - Path 0,1 (A inputs): latency 2 (slow path)
#             # - Path 2,3 (B inputs): latency 1 (fast path)
#             # Strategy: put early-arriving input on slow path, late-arriving on fast path
#             if depth_a < depth_b:
#                 # A arrives early, B arrives late → keep order (A on slow, B on fast)
#                 input_reorder = "keep_order"
#                 slow_input = "A"
#                 fast_input = "B"
#             else:
#                 # B arrives early, A arrives late → swap order (B on slow, A on fast)
#                 input_reorder = "swap_inputs"
#                 slow_input = "B"
#                 fast_input = "A"
            
#             # Perform replacement
#             info["gadget_name"] = replacement
#             info["random_numbers"] = new_randomness
#             info["input_reorder"] = input_reorder
#             info["slow_input"] = slow_input
#             info["fast_input"] = fast_input
            
#             old_area = self.gadget_map[current_gadget]["area"]
#             new_area = self.gadget_map[replacement]["area"]
            
#             stats["replacements"].append({
#                 "node": node_expr,
#                 "from": current_gadget,
#                 "to": replacement,
#                 "depth_a": depth_a,
#                 "depth_b": depth_b,
#                 "depth_diff": depth_diff,
#                 "input_reorder": input_reorder,
#                 "slow_input": slow_input,
#                 "fast_input": fast_input,
#                 "randomness_saved": old_randomness - new_randomness,
#                 "area_change": new_area - old_area
#             })
            
#             print(f"   ✓ {node_expr}: {current_gadget} → {replacement}")
#             print(f"     Depth: A={depth_a}, B={depth_b}, diff={depth_diff}")
#             print(f"     Reorder: {input_reorder} ({slow_input} on slow path, {fast_input} on fast path)")
#             print(f"     Randomness: {old_randomness} → {new_randomness} (saved: {old_randomness - new_randomness})")
#             print(f"     Area: {old_area:.1f} → {new_area:.1f}")
        
#         stats["final_randomness"] = sum(info["random_numbers"] for info in self.gadget_definition.values())
#         stats["final_area"] = sum(self.gadget_map[info["gadget_name"]]["area"] for info in self.gadget_definition.values())
#         stats["total_randomness_saved"] = stats["initial_randomness"] - stats["final_randomness"]
#         stats["final_critical_path"] = self._compute_critical_path_latency()
        
#         print(f"\n[MLRC] Arrival depth optimization complete:")
#         print(f"       Total replacements: {len(stats['replacements'])}")
#         print(f"       Randomness: {stats['initial_randomness']} → {stats['final_randomness']} (saved: {stats['total_randomness_saved']})")
#         print(f"       Area: {stats['initial_area']:.1f} → {stats['final_area']:.1f}")
#         print(f"       Final critical path latency: {stats['final_critical_path']}")
        
#         # IMPORTANT: Regenerate unique gadget definitions with hpc2/hpc2o
#         print(f"\n[MLRC] Regenerating gadget definitions (including hpc2/hpc2o)...")
#         self.unique_gadgets_definition = {}
#         gadget_classes = {
#             'hpc1': HPC1, 'hpc2': HPC2, 'hpc3': HPC3,
#             'hpc2o': HPC2o, 'hpc3o': HPC3o,
#             'comar': COMAR, 'domand': Domand
#         }

#         for expr, info in self.gadget_definition.items():
#             gname = info["gadget_name"].lower()
#             if gname not in self.unique_gadgets_definition and gname in gadget_classes:
#                 obj = gadget_classes[gname](d=self.d) if gname != 'comar' else COMAR()
#                 self.unique_gadgets_definition[gname] = obj.generate_multiply_function()
#                 func_name = obj.get_function_name()
#                 # Update func_name for all nodes using this gadget
#                 for e, spec in self.gadget_definition.items():
#                     if spec["gadget_name"].lower() == gname:
#                         spec["func_name"] = func_name
        
#         print(f"[MLRC] Generated {len(self.unique_gadgets_definition)} unique gadget definitions: {list(self.unique_gadgets_definition.keys())}")
        
#         return stats

#     def optimize_gadget_mapping_for_cost(self, target_latency=None, max_iterations=10):
#         """
#         Post-MLRC optimization: greedily replace high-cost gadgets with cheaper alternatives
#         while respecting the latency constraint (via critical path).
        
#         Args:
#             target_latency (int): max allowed latency; if None, computed from current critical path
#             max_iterations (int): max replacement iterations
        
#         Returns:
#             dict: statistics of the optimization
#         """
#         if not hasattr(self, 'gadget_definition') or not self.gadget_definition:
#             print("[WARN] No gadget_definition to optimize")
#             return {}
        
#         if target_latency is None:
#             target_latency = self._compute_critical_path_latency()
#             print(f"[INFO] Using current critical path latency as target: {target_latency}")
        
#         stats = {
#             "initial_randomness": sum(info["random_numbers"] for info in self.gadget_definition.values()),
#             "initial_area": sum(self.gadget_map[info["gadget_name"]]["area"] for info in self.gadget_definition.values()),
#             "replacements": [],
#             "iterations": 0
#         }
        
#         print(f"\n[MLRC] Post-optimization: Cost reduction with latency constraint ≤ {target_latency}")
        
#         # Repeatedly try to replace nodes
#         for iteration in range(max_iterations):
#             replaced_this_iter = False
            
#             # Find nodes that might benefit from replacement
#             for node_expr, info in list(self.gadget_definition.items()):
#                 current_gadget = info["gadget_name"]
#                 replacement = self._get_replacement_gadget(current_gadget, target_latency)
                
#                 if replacement is None:
#                     continue
                
#                 # Tentatively replace
#                 old_gadget = info["gadget_name"]
#                 old_randomness = info["random_numbers"]
#                 old_area = self.gadget_map[old_gadget]["area"]
                
#                 info["gadget_name"] = replacement
#                 info["random_numbers"] = self.gadget_map[replacement]["randomness"]
#                 new_area = self.gadget_map[replacement]["area"]
                
#                 # Check if latency constraint is still satisfied
#                 new_critical_path = self._compute_critical_path_latency()
                
#                 if new_critical_path <= target_latency:
#                     # Replacement accepted
#                     stats["replacements"].append({
#                         "node": node_expr,
#                         "from": old_gadget,
#                         "to": replacement,
#                         "randomness_saved": old_randomness - self.gadget_map[replacement]["randomness"],
#                         "area_change": new_area - old_area
#                     })
#                     replaced_this_iter = True
#                     print(f"   ✓ {node_expr}: {old_gadget} → {replacement} "
#                           f"(rand: {old_randomness}→{info['random_numbers']}, area: {old_area:.1f}→{new_area:.1f})")
#                     break  # Re-scan from beginning
#                 else:
#                     # Revert
#                     info["gadget_name"] = old_gadget
#                     info["random_numbers"] = old_randomness
            
#             if not replaced_this_iter:
#                 break
            
#             stats["iterations"] += 1
        
#         stats["final_randomness"] = sum(info["random_numbers"] for info in self.gadget_definition.values())
#         stats["final_area"] = sum(self.gadget_map[info["gadget_name"]]["area"] for info in self.gadget_definition.values())
#         stats["total_randomness_saved"] = stats["initial_randomness"] - stats["final_randomness"]
#         stats["final_critical_path"] = self._compute_critical_path_latency()
        
#         print(f"\n[MLRC] Optimization complete:")
#         print(f"       Iterations: {stats['iterations']}")
#         print(f"       Total replacements: {len(stats['replacements'])}")
#         print(f"       Randomness: {stats['initial_randomness']} → {stats['final_randomness']} (saved: {stats['total_randomness_saved']})")
#         print(f"       Area: {stats['initial_area']:.1f} → {stats['final_area']:.1f}")
#         print(f"       Final critical path latency: {stats['final_critical_path']}")
        
#         return stats

# # ============================================================================
# # COMPLETE MLRC PIPELINE WITH INPUT REORDERING (FINAL)
# # ============================================================================
# #
# # STEP 1: Initial MLRC
# #   - Assign all AND nodes to HPC2 (minimum randomness)
# #   - Use randomness budget to upgrade to HPC3/HPC3o
# #   - Result: initial mapping, latency minimized
# #
# # STEP 2: Pattern Analysis (xor_and detection)
# #   - Detect AND nodes feeding directly to XOR
# #   - Upgrade xor_and nodes: HPC3 → HPC3o, HPC2 → HPC2o
# #   - Benefit: ~10% area reduction
# #
# # STEP 3: Arrival Depth Optimization (NEW!)
# #   - Compute arrival depth for each AND node
# #   - For HPC3/HPC3o with depth_diff ≥ 1:
# #     - Replace HPC3 → HPC2 (or HPC3o → HPC2o)
# #     - Determine input routing based on depths
# #     - Store reordering info (keep_order or swap_inputs)
# #   - Result: ~22 nodes replaced, ~22 randomness saved
# #
# # STEP 4: Input Reordering Decision
# #   For each replaced node:
# #     if depth_A < depth_B:
# #       input_reorder = "keep_order"
# #       slow_input = "A" (depth_A on slow path 2)
# #       fast_input = "B" (depth_B on fast path 1)
# #     else:
# #       input_reorder = "swap_inputs"
# #       slow_input = "B" (depth_B on slow path 2)
# #       fast_input = "A" (depth_A on fast path 1)
# #
# # STEP 5: Share Splitting
# #   - ShareTransformer uses gadget_map + input_reorder info
# #   - For "keep_order" nodes: HPC2(a0, a1, b0, b1, ...)
# #   - For "swap_inputs" nodes: HPC2(b0, b1, a0, a1, ...) ← SWAPPED
# #   - Result: correct C code with proper input routing
# #
# # FINAL METRICS (d=1, target_randomness=111):
# #   Initial MLRC: 68 randomness, 3 latency, 156 area
# #   After optimization: 46 randomness, 3 latency, 164 area
# #   Savings: 22 randomness bits, 0 latency increase
# #   Gadgets: 9 hpc3, 3 hpc3o, 15 hpc2, 7 hpc2o
# #   Swaps: 16 nodes with input swaps, 6 nodes keeping order
# #
# # ============================================================================
# ============================================================================
# MLRC Post-Optimization Strategy (Generic, Order-Agnostic)
# ============================================================================
#
# BEFORE (Hardcoded, AST-level, order-specific):
#   1. Split AST into shares for d=1 (2 shares)
#   2. Manually search for HPC3 calls in split code
#   3. Try to swap HPC3 → HPC2 in AST
#   4. Re-compile and hope latency is OK
#   → Works only for d=1, fragile, requires AST manipulation
#
# AFTER (Generic, AND-tree level, works for any order):
#   1. MLRC generates initial gadget mapping at AND-tree level
#   2. Compute critical path latency (accounts for parallelism)
#   3. Greedily replace high-cost gadgets with cheaper ones:
#      - For each node, find a replacement with lower randomness/area
#      - Same or better latency (checked via critical path)
#   4. Split into shares ONCE with final optimized mapping
#   → Works for any d, no AST manipulation, latency-aware
#
# KEY FUNCTIONS:
#   - _get_replacement_gadget(current, target_latency)
#     Find a cheaper alternative to 'current' gadget
#   - optimize_gadget_mapping_for_cost(target_latency, max_iterations)
#     Iteratively replace nodes; recompute critical path after each
#   - _compute_critical_path_latency()
#     Compute true latency as longest AND-dependency chain (not sum)
#
# USAGE IN NOTEBOOK:
#   mlrc_obj = MLRC(d, and_tree, gadget_specs)
#   mlrc_obj.mlrc(target_randomness)           # Initial MLRC
#   stats = mlrc_obj.optimize_gadget_mapping_for_cost(target_latency)
#   # Now split into shares once with final mapping
# ============================================================================
# ASYMMETRIC GADGET PROPERTY OPTIMIZATION
# ============================================================================
#
# KEY INSIGHT: Different masking gadgets have different latency characteristics
#
# HPC2 (2-order masking):
#   - Input A path latency: 2 cycles
#   - Input B path latency: 1 cycle  (FAST PATH)
#   - Asymmetric: different latencies for different inputs
#   - Randomness: 3
#
# HPC3 (3-order masking):
#   - Input A path latency: 1 cycle
#   - Input B path latency: 1 cycle
#   - Symmetric: same latency for both inputs
#   - Randomness: 6
#
# OPTIMIZATION STRATEGY:
#   1. Detect xor_and patterns:
#      - AND node M = A & B
#      - M is immediately consumed by XOR: Z = M ^ X
#   
#   2. For xor_and nodes, replace HPC3 → HPC2:
#      - Place the fast input (latency 1) on the critical path
#      - The slow input's extra latency is hidden by XOR buffering
#      - Result: same critical path latency, but randomness 6 → 3
#   
#   3. For pure AND nodes:
#      - Cannot safely replace (both inputs might be on critical path)
#      - Keep as HPC3
#
# BENEFITS:
#   - Reduces randomness by 50% (6 → 3) for xor_and nodes
#   - No increase in latency (thanks to asymmetric properties)
#   - Automatically applied to any order d
#   - Works generically across all masking orders
#
# IMPLEMENTATION:
#   - _can_swap_hpc3_to_hpc2_asymmetric(): Check if node is xor_and pattern
#   - optimize_gadget_mapping_for_cost_asymmetric(): Greedily replace HPC3 → HPC2
# ============================================================================
# ARRIVAL DEPTH-BASED ASYMMETRIC GADGET OPTIMIZATION (matches find_swaps.py)
# ============================================================================
#
# PROBLEM:
#   After MLRC, all AND nodes are assigned gadgets (mostly HPC3 for d=1).
#   But many HPC3 nodes have unbalanced input arrival times.
#   → We can replace them with HPC2 (which is asymmetric) to save randomness.
#
# KEY INSIGHT FROM find_swaps.py:
#   HPC2 has asymmetric input paths:
#   - Input A: latency 2 (slow path)
#   - Input B: latency 1 (fast path)
#   
#   HPC3 has symmetric paths (both latency 1).
#   
#   If inputs arrive at different times:
#   - Early-arriving input → put on slow path (latency 2)
#   - Late-arriving input → put on fast path (latency 1)
#   → Total latency = max(early + 2, late + 1) = max(early, late) + 1
#   → Same as HPC3 if inputs were balanced!
#
# ALGORITHM (_compute_arrival_depths):
#   1. Process AND tree level by level (in order)
#   2. For each variable, track its depth (how many AND ops deep)
#   3. For AND nodes: depth = max(input_depths) + 1
#   4. For XOR nodes: depth = max(input_depths)
#   5. Result: {node_expr: (depth_A, depth_B)} for each AND node
#
# REPLACEMENT LOGIC (optimize_gadget_mapping_for_cost_asymmetric):
#   For each HPC3/HPC3o node:
#     1. Get input depths: depth_A, depth_B
#     2. If |depth_A - depth_B| >= 1: inputs arrive at different times
#     3. Replace HPC3 → HPC2 (or HPC3o → HPC2o)
#     4. Reorder: early input → slow, late input → fast
#     5. Save: randomness 6→3 (for d=1), area reduction, no latency increase!
#
# EXPECTED RESULTS (d=1, target_randomness=111):
#   - Initial MLRC: ~34 HPC3 nodes (randomness: 34*6 = 204)
#   - After arrival depth opt: ~22 nodes replaced → ~12 HPC3 + ~22 HPC2
#   - Final randomness: 12*6 + 22*3 = 138 → saves ~66 randomness bits
#   - Latency: unchanged (still critical path)
#   - Area: reduced (HPC2 smaller than HPC3)
#
# COMPARISON WITH find_swaps.py:
#   find_swaps.py: works on split C code, uses signal arrival depths
#   Our MLRC version: works at AND-tree level BEFORE splitting
#   Result: equivalent swaps, but applied earlier in pipeline
# ============================================================================
# COMPLETE MLRC OPTIMIZATION FLOW (WITH FINAL GADGET MAP PRINTING)
# ============================================================================
#
# WORKFLOW:
#
# STEP 1: INITIAL MLRC (Minimize Latency Under Randomness Constraint)
#   - All AND nodes assigned HPC2 initially (min randomness)
#   - Use randomness budget (111) to upgrade to HPC3/HPC3o
#   - Critical path latency: computed as longest AND dependency chain
#   - Pattern analysis: detect xor_and nodes (AND → XOR)
#   - Upgrade xor_and nodes to hpc3o/hpc2o (optimized variants)
#   - Result: initial mapping with mixed gadgets, latency minimized
#
# STEP 2: ARRIVAL DEPTH OPTIMIZATION (Post-MLRC)
#   - Compute arrival depth for each AND node (how deep in AND chain)
#   - For each HPC3/HPC3o node:
#     - If input depths differ by ≥1: swap to HPC2/HPC2o
#     - Place early-arriving input on slow path (latency 2)
#     - Place late-arriving input on fast path (latency 1)
#     - Result: balanced timing, no latency increase, randomness saved!
#   - Savings: randomness 2→1 per node, ~22 nodes → ~22 randomness saved
#
# STEP 3: FINAL GADGET MAPPING (printed after optimization)
#   - Shows all 34 AND nodes with final gadget assignments
#   - Columns: Gate No, Expression, Gadget, Randomness, Area
#   - Gadget summary: count, total randomness, total area
#   - Unique definitions: lists which gadgets are actually used
#
# STEP 4: SHARE SPLITTING
#   - Transform AST: replace AND nodes with gadget function calls
#   - ShareTransformer(d+1, gadget_map, unique_definitions)
#   - Generates d+1 shares of the circuit
#   - Includes all gadget definitions (HPC2, HPC3, HPC2o, HPC3o, etc.)
#   - Output: C file with shared masking implementation
#
# KEY METRICS (Example for d=1, target_randomness=111):
#   - Initial MLRC: 68 randomness, 3 latency, 156 area
#   - After optimization: 46 randomness, 3 latency, 164 area
#   - Savings: 22 randomness bits, same latency!
#   - Gadgets used: 12 hpc3, 22 hpc2
#
# ============================================================================
# MLRC Post-Optimization Strategy (Generic, Order-Agnostic)
# ============================================================================
#
# BEFORE (Hardcoded, AST-level, order-specific):
#   1. Split AST into shares for d=1 (2 shares)
#   2. Manually search for HPC3 calls in split code
#   3. Try to swap HPC3 → HPC2 in AST
#   4. Re-compile and hope latency is OK
#   → Works only for d=1, fragile, requires AST manipulation
#
# AFTER (Generic, AND-tree level, works for any order):
#   1. MLRC generates initial gadget mapping at AND-tree level
#   2. Compute critical path latency (accounts for parallelism)
#   3. Greedily replace high-cost gadgets with cheaper ones:
#      - For each node, find a replacement with lower randomness/area
#      - Same or better latency (checked via critical path)
#   4. Split into shares ONCE with final optimized mapping
#   → Works for any d, no AST manipulation, latency-aware
#
# KEY FUNCTIONS:
#   - _get_replacement_gadget(current, target_latency)
#     Find a cheaper alternative to 'current' gadget
#   - optimize_gadget_mapping_for_cost(target_latency, max_iterations)
#     Iteratively replace nodes; recompute critical path after each
#   - _compute_critical_path_latency()
#     Compute true latency as longest AND-dependency chain (not sum)
#
# USAGE IN NOTEBOOK:
#   mlrc_obj = MLRC(d, and_tree, gadget_specs)
#   mlrc_obj.mlrc(target_randomness)           # Initial MLRC
#   stats = mlrc_obj.optimize_gadget_mapping_for_cost(target_latency)
#   # Now split into shares once with final mapping
# ============================================================================
# ASYMMETRIC GADGET PROPERTY OPTIMIZATION
# ============================================================================
#
# KEY INSIGHT: Different masking gadgets have different latency characteristics
#
# HPC2 (2-order masking):
#   - Input A path latency: 2 cycles
#   - Input B path latency: 1 cycle  (FAST PATH)
#   - Asymmetric: different latencies for different inputs
#   - Randomness: 3
#
# HPC3 (3-order masking):
#   - Input A path latency: 1 cycle
#   - Input B path latency: 1 cycle
#   - Symmetric: same latency for both inputs
#   - Randomness: 6
#
# OPTIMIZATION STRATEGY:
#   1. Detect xor_and patterns:
#      - AND node M = A & B
#      - M is immediately consumed by XOR: Z = M ^ X
#   
#   2. For xor_and nodes, replace HPC3 → HPC2:
#      - Place the fast input (latency 1) on the critical path
#      - The slow input's extra latency is hidden by XOR buffering
#      - Result: same critical path latency, but randomness 6 → 3
#   
#   3. For pure AND nodes:
#      - Cannot safely replace (both inputs might be on critical path)
#      - Keep as HPC3
#
# BENEFITS:
#   - Reduces randomness by 50% (6 → 3) for xor_and nodes
#   - No increase in latency (thanks to asymmetric properties)
#   - Automatically applied to any order d
#   - Works generically across all masking orders
#
# IMPLEMENTATION:
#   - _can_swap_hpc3_to_hpc2_asymmetric(): Check if node is xor_and pattern
#   - optimize_gadget_mapping_for_cost_asymmetric(): Greedily replace HPC3 → HPC2
# ============================================================================
# ARRIVAL DEPTH-BASED ASYMMETRIC GADGET OPTIMIZATION (matches find_swaps.py)
# ============================================================================
#
# PROBLEM:
#   After MLRC, all AND nodes are assigned gadgets (mostly HPC3 for d=1).
#   But many HPC3 nodes have unbalanced input arrival times.
#   → We can replace them with HPC2 (which is asymmetric) to save randomness.
#
# KEY INSIGHT FROM find_swaps.py:
#   HPC2 has asymmetric input paths:
#   - Input A: latency 2 (slow path)
#   - Input B: latency 1 (fast path)
#   
#   HPC3 has symmetric paths (both latency 1).
#   
#   If inputs arrive at different times:
#   - Early-arriving input → put on slow path (latency 2)
#   - Late-arriving input → put on fast path (latency 1)
#   → Total latency = max(early + 2, late + 1) = max(early, late) + 1
#   → Same as HPC3 if inputs were balanced!
#
# ALGORITHM (_compute_arrival_depths):
#   1. Process AND tree level by level (in order)
#   2. For each variable, track its depth (how many AND ops deep)
#   3. For AND nodes: depth = max(input_depths) + 1
#   4. For XOR nodes: depth = max(input_depths)
#   5. Result: {node_expr: (depth_A, depth_B)} for each AND node
#
# REPLACEMENT LOGIC (optimize_gadget_mapping_for_cost_asymmetric):
#   For each HPC3/HPC3o node:
#     1. Get input depths: depth_A, depth_B
#     2. If |depth_A - depth_B| >= 1: inputs arrive at different times
#     3. Replace HPC3 → HPC2 (or HPC3o → HPC2o)
#     4. Reorder: early input → slow, late input → fast
#     5. Save: randomness 6→3 (for d=1), area reduction, no latency increase!
#
# EXPECTED RESULTS (d=1, target_randomness=111):
#   - Initial MLRC: ~34 HPC3 nodes (randomness: 34*6 = 204)
#   - After arrival depth opt: ~22 nodes replaced → ~12 HPC3 + ~22 HPC2
#   - Final randomness: 12*6 + 22*3 = 138 → saves ~66 randomness bits
#   - Latency: unchanged (still critical path)
#   - Area: reduced (HPC2 smaller than HPC3)
#
# COMPARISON WITH find_swaps.py:
#   find_swaps.py: works on split C code, uses signal arrival depths
#   Our MLRC version: works at AND-tree level BEFORE splitting
#   Result: equivalent swaps, but applied earlier in pipeline
# ============================================================================
# COMPLETE MLRC OPTIMIZATION FLOW (WITH FINAL GADGET MAP PRINTING)
# ============================================================================
#
# WORKFLOW:
#
# STEP 1: INITIAL MLRC (Minimize Latency Under Randomness Constraint)
#   - All AND nodes assigned HPC2 initially (min randomness)
#   - Use randomness budget (111) to upgrade to HPC3/HPC3o
#   - Critical path latency: computed as longest AND dependency chain
#   - Pattern analysis: detect xor_and nodes (AND → XOR)
#   - Upgrade xor_and nodes to hpc3o/hpc2o (optimized variants)
#   - Result: initial mapping with mixed gadgets, latency minimized
#
# STEP 2: ARRIVAL DEPTH OPTIMIZATION (Post-MLRC)
#   - Compute arrival depth for each AND node (how deep in AND chain)
#   - For each HPC3/HPC3o node:
#     - If input depths differ by ≥1: swap to HPC2/HPC2o
#     - Place early-arriving input on slow path (latency 2)
#     - Place late-arriving input on fast path (latency 1)
#     - Result: balanced timing, no latency increase, randomness saved!
#   - Savings: randomness 2→1 per node, ~22 nodes → ~22 randomness saved
#
# STEP 3: FINAL GADGET MAPPING (printed after optimization)
#   - Shows all 34 AND nodes with final gadget assignments
#   - Columns: Gate No, Expression, Gadget, Randomness, Area
#   - Gadget summary: count, total randomness, total area
#   - Unique definitions: lists which gadgets are actually used
#
# STEP 4: SHARE SPLITTING
#   - Transform AST: replace AND nodes with gadget function calls
#   - ShareTransformer(d+1, gadget_map, unique_definitions)
#   - Generates d+1 shares of the circuit
#   - Includes all gadget definitions (HPC2, HPC3, HPC2o, HPC3o, etc.)
#   - Output: C file with shared masking implementation
#
# KEY METRICS (Example for d=1, target_randomness=111):
#   - Initial MLRC: 68 randomness, 3 latency, 156 area
#   - After optimization: 46 randomness, 3 latency, 164 area
#   - Savings: 22 randomness bits, same latency!
#   - Gadgets used: 12 hpc3, 22 hpc2
#
# ============================================================================
# INPUT REORDERING FOR ASYMMETRIC GADGETS (HPC2/HPC2o)
# ============================================================================
#
# PROBLEM:
#   HPC2/HPC2o have asymmetric latencies on their inputs:
#   - Inputs A0,A1 (indices 0,1): latency 2 (SLOW PATH)
#   - Inputs B0,B1 (indices 2,3): latency 1 (FAST PATH)
#
#   When we replace HPC3 → HPC2, we need to route the inputs optimally.
#
# SOLUTION:
#   Use arrival depth tracking to determine input routing:
#   - Early-arriving input → SLOW PATH (latency 2) - it can wait
#   - Late-arriving input → FAST PATH (latency 1) - it should arrive quickly
#
# EXAMPLE 1: depth_A < depth_B (A arrives early, B arrives late)
#   Node: M32 = M27 & M31
#   Depth: A=1 (M27), B=2 (M31)
#   Replacement: HPC3o → HPC2o
#   Routing: KEEP ORDER
#     - M27 (depth 1, early) → input A (slow path, latency 2)
#     - M31 (depth 2, late) → input B (fast path, latency 1)
#   Result: max(1+2, 2+1) = max(3, 3) = 3 ✓ (same as HPC3)
#
# EXAMPLE 2: depth_A > depth_B (A arrives late, B arrives early)
#   Node: M35 = M24 & M34
#   Depth: A=1 (M24, early), B=2 (M34, late)
#   Replacement: HPC3o → HPC2o
#   Routing: SWAP INPUTS
#     - M34 (depth 2, late) → input A (slow path, latency 2) ← SWAPPED
#     - M24 (depth 1, early) → input B (fast path, latency 1) ← SWAPPED
#   Result: max(2+2, 1+1) = max(4, 2) = 4 ✗ (WRONG!)
#
#   CORRECT ROUTING: Don't swap in function call, but reorder arguments:
#     - Call HPC2o(M34, M34_dummy, M24, M24_dummy, ...) [B late, A early]
#     - Wait, that's not right either...
#
#   ACTUAL SOLUTION: Swap the semantics, not the function call:
#     - Original: M32 = M27 & M31
#     - If we want M31 on fast path, keep as is
#     - If we want M24 on fast path: reorder to M35 = M34 & M24 (swap RHS)
#     - But we can't change the expression!
#
#   REAL FIX: Track in gadget_definition which input goes where:
#     input_reorder: "swap_inputs"
#     slow_input: "B"  (original B input should go to slow path)
#     fast_input: "A"  (original A input should go to fast path)
#   ShareTransformer uses this to generate: HPC2o(B0,B1, A0,A1, ...)
#
# ALGORITHM (_compute_arrival_depths + optimize_gadget_mapping_for_cost_asymmetric):
#   For each HPC3→HPC2 replacement:
#     1. Compute depth_A and depth_B
#     2. If depth_A < depth_B: "keep_order" (A on slow, B on fast)
#     3. If depth_A > depth_B: "swap_inputs" (B on slow, A on fast)
#     4. Store slow_input and fast_input names
#     5. ShareTransformer will use this to build correct function calls
#
# OUTPUT FIELDS IN gadget_definition:
#   "input_reorder": "keep_order" or "swap_inputs"
#   "slow_input": "A" or "B" (which original input goes to slow path)
#   "fast_input": "A" or "B" (which original input goes to fast path)
#
# ============================================================================
from DSE_algorithm.dse import DSE
from tabulate import tabulate # type: ignore
import json
from collections import defaultdict
import heapq
import Gadgets as secure_gadget
from collections import OrderedDict
import math
from Gadgets import HPC1, HPC2, HPC3, COMAR, Domand, HPC2o, HPC3o, HPC2Swapped, HPC2oSwapped
from asymmetric_latency_optimizer import AsymmetricLatencyOptimizer
# Define ANSI escape codes for colors
RED = "\033[31m"
RESET = "\033[0m"
GREEN = "\033[32m"
YELLOW = "\033[33m"

class MLRC(DSE):

    """
        Minimise Latency Under Randomness Constraint (MLRC)
        [INPUT] :
        
        1. and-tree (A graph of AND gates preserving the dependency structure of computation). Nodes represent AND operations and edges represent dependencies. 
        2. map of gadgets: A dictionary mapping gadget names to latency, randomness and area of that gadget.
            e.g., 
            {
            
                'HPC1' : {"latency" : 2, "randomness" : 2, "area" : 200.67}
                'HPC3' : {"latency" : 1, "randomness" : 2, "area" : 908.67}
                ...
            }
        3. target_randomness: 

                
        [Logic]:
            1. Build a min-heap where each level is ordered by number of nodes, the level with the 
               fewest nodes comes first in the min heap
                    
            2. initially all the nodes are assigned a gadget with least randomness.
                - find the gadget with least randomness form the map we call it `initial_randomness`.
                - latency of the initial gadget -> `initial_latency`
                - area of initial gadget -> `initial_area`

            3. process each level of min_heap
            
            4. Then we sort the gadget map:
                [why sort] : we are trying to find the gadget with least latency. 
                we also have randomness and area.
                if our focus is on just reducing the latency then we need to find the gadget with least latency and 
                if multiple gadget exist with same latency then we need to find the gadget which uses least randomness. 
                because it will increase our the chance reducing latency more as buffer randomness will be used up slowly.
                so therefore we sort on the basis of latency then in case of a tie randomness and then area.

            5. We choose the first gadget form the list.
            
            6. We calculate the randomness required to replace all the gadgets in poped level from the min heap `total_replacement_randomness `.
            7. if the total_replacement_randomness <= randomnesss bonus 
                    we replace all the gadget in level with optimal gadget low latency
                
                    - replace all the nodes with currrent gadget.
                    - buffer_Randomness = buffer_randomness - total_replacement_randomness
                    - also update the map of and nodes which store a dictionary mapping of and expression to the gadget name.

                else if buffer randomness is not zero: 
                    
                
                    # we can not reduce the latency so we reduce the area
                    # we need to first extract all the gadgets with latency = initial_latency and area < initial area
                    # we choose gadgets with same latency as we established that latency can't be reduce further so we check 
                    # if area reduction is possible by using the buffer randomness
                    
                    # first find out max number of nodes that are replaceable in the 
                    # calculate the min_area of unvisited nodes combined
                    # we find out the amount of extra randomness needed to replace the current_gadget with new gadget
                        
                        # what if gadget_randomness is negative

                    # Determine the possible values of extra randomness.
                        # [Note] The initial gadget is selection is based on:
                        #        1. Minimum randomness
                        #        2. If randomness is equal, choose the one with lower latency
                        #        3. If both are equal, choose the one with smaller area
                        #
                        # Now, for any gadget in matching_gadgets:
                        # - current_randomness < initial_randomness is not possible because the initial gadget was chosen with the least randomness.
                        # - current_randomness == initial_randomness is also not possible, because:
                        #     - matching_gadgets only includes gadgets with area < current_gadget's area
                        #     - if such a gadget existed with equal randomness, it would have been selected as the initial gadget instead
                        #
                        # Therefore, current_randomness > initial_randomness always holds true,
                        # and we can safely conclude: extra_randomness = current_randomness - initial_randomness > 0

                    # We now determine how many nodes can be replaced with the current gadget based on the available randomness.
                        
                        # Case 1: replaceable_node_count < node_count
                        #     - We can replace exactly 'replaceable_node_count' nodes using the available randomness.
                        #
                        # Case 2: replaceable_node_count > node_count
                        #     - We have more randomness than needed, but we cannot replace more than the total available nodes.
                        #     - So, the actual number of replacements is limited to 'node_count'.
                        
                        # Case 3: replaceable_node_count == node_count
                        #     - All nodes can be replaced using the available randomness.

                    # we need to replace the initial gadget with current gadget

                    then we will be replacing some gadget in the level to reduce the area 
                    we won't be able to reduce latency in the graph as we need to replace all the gadget in 
                    a level to reduce the latency and as we are choosing the level with least no of nodes therefore least amount 
                    of randomness will be used in this work.
                    but also there is a possiblity of existence of some other gadget with same latency as the first gadget
                    so we need to check if the next gadget have the same latency so we can then replace it with another gadget as well


                    - number of nodes that can be replaced = floor(buffer_randomness/required_randomness)
                    - buffer_randomness = buffer_randomness - number of nodes * required_randomness.
                    - update the map of and nodes.
                
            * we need to store the definition of gadget name  to its c definition in a dictionary(dict) map.
    """ 
    def __init__(self, d, and_tree, gadget_map, and_xor_tree=None):
        super().__init__(d, and_tree, gadget_map)
        self.and_xor_tree = and_xor_tree # Optional: AND-XOR tree pattern detection
        self.processed_node = 0
        self.total_randomness_after_mlrc = 0
        self.total_latency_after_mlrc = 0
        self.total_area_after_mlrc = 0
        self.initial_randomness_bonus = 0
        print(f"{RED}NODES IN EACH LEVEL:\n") 
        for key, value in self.nodes_by_level.items():
            print(f"{key} : {len(value)}")
        print(f"{RESET}")

    def construct_min_heap(self):
        # node_level = self.and_tree.get_level_node()
        """
            Constructs the min heap 
            where each node is the level number 
            @return minheap of levels created on the basis of number of nodes in a level
        """
        min_heap = []

        for level, nodes in self.nodes_by_level.items():
            # updating as the graph contains both and and xor nodes 
            # find number of and node in the level and use that as the gate count for the level
            print(f"{RED}Level {level} : {nodes} {RESET}")
            gate_count = 0
            # holds the list of nodes that will be replace by gadgets and placed into the min
            # heap
            gadget_nodes = []
            for node_expr in nodes:
                if '&' in node_expr :
                    print(f"{GREEN}DEBUG: node_expr {node_expr} is an AND gate{RESET}")
                    gate_count = gate_count + 1
                    gadget_nodes.append(node_expr)

                # print(f"initial nodes in the level: {len(nodes)}") # number of gate at this level
                # print(f"gate count in the level: {gate_count}")
                # get the gadget with least randomness and get its latency and use that as the latency of the level
            gadget_with_least_randomness = min(self.gadget_map.items(), key = lambda item: 
                                        (item[1]["randomness"], item[1]["latency"], item[1]["area"]))
            if gate_count == 0:
                # if there is no and gate just dont consider the level for replacement as it will not contribute to latency
                self.level_latency[level] = 0
            else:
                self.level_latency[level] = gadget_with_least_randomness[1]["latency"]
                print(f"[INFO]: level {level} gate count {gate_count} latency {self.level_latency[level]}")
                heapq.heappush(min_heap, (gate_count, -level, gadget_nodes))
            
        return min_heap
    
    def find_min_gate_level(self, min_heap):
        """
        Extract the level with the minimum number of nodes
        @param min_heap: The min heap storing (gate_count, level, nodes)
        @return: the level with least gate.
        """
        if not min_heap:
            return None, None
        
        _, level, nodes = heapq.heappop(min_heap)
        print(f"[INFO]: Popped level {abs(level)} with nodes {nodes} for gadget selection")
        return abs(level), nodes
        
    def print_gadget_specs(self, gadget_specs):
        table_data =[]
        for gadget, values in gadget_specs.items():
            table_data.append([gadget, values['latency'], values['randomness'], values['area']])
        print(f"\n[INFO]: Populated DSE MAP for order")
        print(tabulate(table_data, headers=["Gadget", "Latency", "randomness","area"], tablefmt="grid"))
    
    def _is_and_node(self, expr: str) -> bool:
        if '=' not in expr:
            return False
        _, rhs = expr.split('=', 1)
        rhs = rhs.strip()
        return '&' in rhs

    def _is_xor_node(self, expr: str) -> bool:
        if '=' not in expr:
            return False
        _, rhs = expr.split('=', 1)
        rhs = rhs.strip()
        return '^' in rhs and '&' not in rhs

    def _extract_lhs_var(self, expr):
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
        # For each variable (AND or XOR output), compute the maximum AND-tree
        # level in its transitive fanin.  This tells us how "late" a variable
        # arrives relative to the AND-gate pipeline.
        #
        # AND gate at level L  →  effective_level = L
        # XOR gate             →  effective_level = max(effective_level of its inputs)
        # Primary input        →  effective_level = 0
        #
        # This is used in Rule 4 below: if xor_other_operand's effective level
        # equals the current AND gate's level, using hpc*o would force the two
        # computations to run serially instead of in parallel, increasing latency.

        # Build AND-output → level lookup first
        and_output_to_level = {}
        for lvl, nodes in self.nodes_by_level.items():
            for n in nodes:
                out_var = self._extract_lhs_var(str(n))
                if out_var:
                    and_output_to_level[out_var] = lvl

        # Compute effective level for every node via topological traversal
        var_effective_level = {}   # variable name → effective AND level

        def _effective_level(var_name):
            if var_name in var_effective_level:
                return var_effective_level[var_name]
            if var_name in and_output_to_level:
                lv = and_output_to_level[var_name]
                var_effective_level[var_name] = lv
                return lv
            # Search the graph for the expression whose LHS is var_name
            best = 0
            for node_idx in graph.node_indices():
                expr_str = str(graph[node_idx])
                if '=' in expr_str:
                    lhs = expr_str.split('=')[0].strip()
                    if lhs == var_name:
                        # Recurse on RHS operands' effective levels
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
                consumer_lhs    = self._extract_lhs_var(consumer_str)
                xor_other_operand = self._extract_xor_other_operand(consumer_str, output_var)

                # === Rule 4: xor_other_operand must arrive BEFORE this AND gate ===
                # If w is at the same (or later) AND level as the current gate,
                # using hpc*o forces serial execution of two gates that were
                # otherwise computed in parallel, adding latency.
                if xor_other_operand:
                    w_level = _effective_level(xor_other_operand)
                    if w_level >= lvl:
                        self.node_pattern[node_expr] = ("pure_and", None)
                        if getattr(self, 'debug', True):
                            print(f"  [W-LATE] {node_expr}")
                            print(f"           xor_other_operand='{xor_other_operand}' has effective level {w_level} >= current level {lvl}")
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
        """Detect XOR+AND patterns using precomputed fanin/fanout from and_xor_tree.

        Step 1 — Build fanout and fanin dicts for every node in and_xor_tree:
            fanout[node_str]  = [successor_str, ...]
            fanin[node_str]   = [predecessor_str, ...]

        Step 2 — For each AND node in and_tree (nodes_by_level):
            Rule 1: fanout count == 1
            Rule 2: the single fanout node is a XOR node
            Rule 3: that XOR node's fanin has no other AND node
        """
        print("\n--- [MLRC] Analyzing AND-XOR Graph for Patterns (Graph-based) ---")
        self.node_pattern = {}

        if self.and_xor_tree is None:
            print("[WARN] and_xor_tree not available — all nodes marked pure_and")
            for lvl_nodes in self.nodes_by_level.values():
                for node_expr in lvl_nodes:
                    self.node_pattern[node_expr] = ("pure_and", None)
            return

        graph = self.and_xor_tree.graph

        # ── Step 1: precompute fanout and fanin for every node in and_xor_tree ──
        fanout = {}   # node_str → [successor_str, ...]
        fanin  = {}   # node_str → [predecessor_str, ...]

        for node_idx in graph.node_indices():
            node_str = str(graph[node_idx])
            fanout[node_str] = [str(s) for s in graph.successors(node_idx)]
            fanin[node_str]  = [str(p) for p in graph.predecessors(node_idx)]
        # print(f"[DEBUG] Fanout: {fanout}")
        # print(f"[DEBUG] Fanin: {fanin}")

        # ── Step 2: classify each AND node from the and_tree ──
        and_count     = 0
        xor_and_count = 0

        for lvl in sorted(self.nodes_by_level.keys()):
            for node_expr in self.nodes_by_level[lvl]:
                node_str = str(node_expr)
                and_count += 1
                self.node_pattern[node_expr] = ("pure_and", None)  # default

                if node_str not in fanout:
                    print(f"  [WARN] '{node_str}' not in and_xor_tree — pure_and")
                    continue

                successors = fanout[node_str]

                # Rule 1: exactly one fanout
                if len(successors) != 1:
                    print(f"  [FANOUT={len(successors)}] {node_str} → pure_and")
                    continue

                consumer_str = successors[0]

                # Rule 2: that fanout must be a XOR node
                if not self._is_xor_node(consumer_str):
                    print(f"  [NON-XOR] {node_str} → {consumer_str} → pure_and")
                    continue

                # Rule 3: the XOR node's fanin must have no other AND node
                xor_fanin = fanin.get(consumer_str, [])
                other_and = [p for p in xor_fanin
                             if p != node_str and self._is_and_node(p)]
                if other_and:
                    print(f"  [OTHER AND] {node_str} → {consumer_str} also fed by {other_and} → pure_and")
                    continue

                # All 3 rules pass → xor_and
                consumer_lhs = self._extract_lhs_var(consumer_str)
                self.node_pattern[node_expr] = ("xor_and", consumer_lhs)
                xor_and_count += 1
                print(f"  [XOR_AND] {node_str} → {consumer_str} ✓")

        print(f"\n[MLRC INFO] Pattern analysis complete:")
        print(f"             Total AND nodes : {and_count}")
        print(f"             'xor_and'       : {xor_and_count}")
        print(f"             'pure_and'      : {and_count - xor_and_count}")

    def initial_gadget_and_list_possible_replacement(self, target_randomness):
        # same base selection as before
        min_randomness_gadget = min(
            self.gadget_map.items(),
            key=lambda item: (item[1]["randomness"], item[1]["latency"], item[1]["area"])
        )
        initial_gadget_name = min_randomness_gadget[0]
        initial_latency = min_randomness_gadget[1]["latency"]
        initial_randomness = min_randomness_gadget[1]["randomness"]

        print(f"[MLRC INFO]: Initial gadget selected: {initial_gadget_name}")
        print(f"             Latency: {initial_latency}, Randomness: {initial_randomness}")

        # base: all gadgets (MLRC minimizes latency given randomness budget, so keep full map)
        self.matching_gadgets = dict(self.gadget_map)

        # force include optimized gadgets (if not in DB they simply won't be here)
        for opt in ['hpc2o', 'hpc3o']:
            if opt in self.gadget_map:
                if opt not in self.matching_gadgets:
                    self.matching_gadgets[opt] = self.gadget_map[opt]
                    print(f"[MLRC INFO] Force-included optimized gadget → {opt}")
            else:
                print(f"[MLRC WARN] {opt} NOT FOUND in gadget_map")

        # store for later use in cost-area phase if needed
        self.initial_gadget_name = initial_gadget_name
        self.initial_latency = initial_latency
        self.initial_randomness = initial_randomness
        return initial_gadget_name, initial_randomness, initial_latency

    def _compute_and_level_dependencies(self):
        """
        Build a dependency map for AND-containing levels only.
        Returns: {level: set(predecessor_levels_with_AND)}
        """
        # Identify which levels have AND gates
        and_levels = set(lvl for lvl, nodes in self.nodes_by_level.items()
                         if any('&' in str(node) for node in nodes))
        
        # For each AND level, find which previous AND levels it depends on
        dependencies = {lvl: set() for lvl in and_levels}
        
        for lvl in sorted(and_levels):
            and_nodes_at_lvl = [str(node) for node in self.nodes_by_level[lvl] if '&' in str(node)]
            
            # Extract output variables from these AND nodes
            and_outputs = set()
            for node_str in and_nodes_at_lvl:
                if '=' in node_str:
                    lhs = node_str.split('=')[0].strip()
                    and_outputs.add(lhs)
            
            # Check which previous AND levels feed into this level
            for prev_lvl in sorted(and_levels):
                if prev_lvl >= lvl:
                    continue
                
                # Get outputs of AND nodes at prev_lvl
                prev_and_nodes = [str(node) for node in self.nodes_by_level[prev_lvl] if '&' in str(node)]
                prev_outputs = set()
                for node_str in prev_and_nodes:
                    if '=' in node_str:
                        lhs = node_str.split('=')[0].strip()
                        prev_outputs.add(lhs)
                
                # Check if any prev_output is used in current level's AND nodes
                for node_str in and_nodes_at_lvl:
                    if '=' in node_str:
                        rhs = node_str.split('=')[1].strip()
                        if any(var in rhs for var in prev_outputs):
                            dependencies[lvl].add(prev_lvl)
                            break
        
        return dependencies, and_levels

    def _compute_critical_path_latency(self):
        """
        Compute latency as the critical path through the AND dependency DAG.
        Returns: total critical path latency
        """
        dependencies, and_levels = self._compute_and_level_dependencies()
        
        # DP: earliest_finish_time[lvl] = latency[lvl] + max(eft of predecessors)
        eft = {}
        
        for lvl in sorted(and_levels):
            pred_levels = dependencies[lvl]
            if not pred_levels:
                # No predecessors: start immediately
                eft[lvl] = self.level_latency[lvl]
            else:
                # Start after all predecessors finish
                max_pred_eft = max(eft[p] for p in pred_levels)
                eft[lvl] = max_pred_eft + self.level_latency[lvl]
        
        # Critical path is the maximum EFT
        critical_path = max(eft.values()) if eft else 0
        
        print(f"\n[MLRC] Critical Path Latency Analysis:")
        print(f"       AND-containing levels: {sorted(and_levels)}")
        for lvl in sorted(and_levels):
            preds = dependencies[lvl]
            print(f"       Level {lvl}: latency={self.level_latency[lvl]}, predecessors={preds}, EFT={eft[lvl]}")
        print(f"       Total Critical Path Latency: {critical_path}")
        
        return critical_path

    def _compute_randomness_budget(self, target_randomness, initial_gadget_name,
                                   initial_randomness, initial_latency, initial_area,
                                   total_replacable_nodes):
        """
        Compute the randomness bonus and decide whether COMAR mode applies.

        Returns a dict with budget parameters, or None if target cannot be met.

        COMAR mode triggers when d==1 and 6 <= target < total_initial_randomness:
          - all remaining nodes start as 'comar' (costs 6 total, not per-node)
          - bonus = target - 6  (can be spent upgrading some nodes further)

        Normal mode:
          - bonus = target - (initial_randomness * total_nodes)
          - negative bonus → infeasible
        """
        use_comar = False
        total_initial_randomness = initial_randomness * total_replacable_nodes

        if self.d == 1 and target_randomness >= 6 and target_randomness < total_initial_randomness:
            randomness_bonus = target_randomness - 6
            use_comar = True
            initial_gadget_name = 'comar'
            initial_latency     = self.gadget_map['comar']['latency']
            initial_area        = self.gadget_map['comar']['area']
            initial_randomness  = self.gadget_map['comar']['randomness']
        else:
            randomness_bonus = target_randomness - total_initial_randomness

        print(f"[INFO]: Target randomness     : {target_randomness}")
        print(f"[INFO]: Total initial random  : {total_initial_randomness}")
        print(f"[INFO]: Randomness bonus       : {randomness_bonus}")

        if randomness_bonus < 0:
            print(f"{RED}\n[INFO]: Target randomness CANNOT be met :(\n{RESET}")
            return None

        return {
            'randomness_bonus'    : randomness_bonus,
            'use_comar'           : use_comar,
            'initial_gadget_name' : initial_gadget_name,
            'initial_randomness'  : initial_randomness,
            'initial_latency'     : initial_latency,
            'initial_area'        : initial_area,
        }

    def _replace_full_level(self, gadget_nodes, top_gadget, min_level):
        """
        Upgrade ALL nodes in a level to top_gadget (budget covers the whole level).

        Updates gadget_definition and level_latency.
        Returns: randomness spent (= randomness_per_node * len(gadget_nodes)).
        """
        specs = self.gadget_map[top_gadget]
        self.processed_node      += len(gadget_nodes)
        self.level_latency[min_level] = specs["latency"]

        for node_expr in gadget_nodes:
            print(f"{GREEN}Replacing {node_expr} → {top_gadget} "
                  f"(rand={specs['randomness']}, lat={specs['latency']}, "
                  f"area={specs['area']}){RESET}")
            self.gadget_definition[node_expr] = {
                "gadget_name"    : top_gadget,
                "random_numbers" : specs["randomness"],
            }

        return specs["randomness"] * len(gadget_nodes)

    def _find_best_area_gadget(self, initial_gadget_name, initial_randomness, initial_area,
                                randomness_bonus, use_comar, node_count):
        """
        When the full-level replacement is unaffordable, find the gadget that gives
        the best area reduction for the remaining budget.

        Candidates: gadgets with latency <= initial and area < initial_area.
        Selection criteria: minimise total area of replaceable nodes.

        Returns: (gadget_name, replaceable_node_count, cost_per_node)
                 (None, 0, 0) if no beneficial replacement exists.
        """
        initial_lat = self.gadget_map[initial_gadget_name]["latency"]
        matching_gadgets = {
            name: specs
            for name, specs in self.gadget_map.items()
            if specs["latency"] <= initial_lat and specs["area"] < initial_area
        }
        print(f"{RED}*** Area reduction — candidates: {list(matching_gadgets)}{RESET}")

        best_gadget = None
        best_count  = 0
        best_cost   = 0
        min_area    = initial_area * node_count   # current total area (upper bound)

        for gadget, spec in matching_gadgets.items():
            cost = spec['randomness'] if use_comar else (spec['randomness'] - initial_randomness)
            if cost <= 0:
                continue
            count = min(randomness_bonus // cost, node_count)
            if count == 0:
                continue
            area      = count * spec['area']
            curr_area = count * initial_area
            if curr_area > area and area < min_area:
                best_gadget = gadget
                best_count  = count
                best_cost   = cost
                min_area    = area

        print(f"[INFO]: Best area gadget: {best_gadget}, "
              f"replaceable={best_count}, cost/node={best_cost}")
        return best_gadget, best_count, best_cost

    def _replace_partial_level(self, gadget_nodes, gadget_name, cost_per_node,
                                replaceable_node_count, initial_gadget_name,
                                min_heap, min_level):
        """
        Replace up to replaceable_node_count nodes with gadget_name, spreading
        across multiple levels if needed.

        Bug fixes vs original mlrc():
          FIX-1: Don't pop the next level after budget is exhausted — the original
                 code always called find_min_gate_level after the inner for-loop,
                 even when replaceable_node_count hit 0, causing those nodes to
                 disappear from both gadget_definition and min_heap.
          FIX-2: Assign initial_gadget to the tail of the current level when the
                 budget runs out mid-level — the original left those nodes unassigned.
          FIX-3: off-by-one in `i == len(gadget_nodes)` (was always False).

        Returns: total randomness spent.
        """
        randomness_spent = 0
        self.processed_node += replaceable_node_count

        while replaceable_node_count > 0:
            if not gadget_nodes:
                break

            for i, node_expr in enumerate(gadget_nodes):
                self.gadget_definition[node_expr] = {
                    "gadget_name"    : gadget_name,
                    "random_numbers" : self.gadget_map[gadget_name]["randomness"],
                }
                replaceable_node_count -= 1
                randomness_spent       += cost_per_node

                if replaceable_node_count == 0:
                    # FIX-2: assign fallback to the rest of this level
                    for remaining in gadget_nodes[i + 1:]:
                        if self.gadget_definition.get(remaining) is None:
                            self.gadget_definition[remaining] = {
                                "gadget_name"    : initial_gadget_name,
                                "random_numbers" : self.gadget_map[initial_gadget_name]["randomness"],
                            }
                    # FIX-3: update level latency when the level is finished
                    self.level_latency[min_level] = self.gadget_map[gadget_name]["latency"]
                    break

            # FIX-1: only pop the next level when budget still remains
            if replaceable_node_count > 0:
                min_level, gadget_nodes = self.find_min_gate_level(min_heap)
                if min_level is None:
                    break
            else:
                break

        print(f"[INFO]: Partial replacement done — randomness spent: {randomness_spent}")
        return randomness_spent

    def _assign_fallback_gadgets(self, min_heap, initial_gadget_name):
        """
        Assign initial_gadget_name to every AND node still sitting in the heap
        (i.e. nodes that were never popped during the replacement loop).
        """
        for _count, _level, nodes in min_heap:
            for node in nodes:
                if self.gadget_definition.get(node) is None:
                    self.gadget_definition[node] = {
                        "gadget_name"    : initial_gadget_name,
                        "random_numbers" : self.gadget_map[initial_gadget_name]["randomness"],
                    }

    def _build_gadget_definitions(self):
        """
        For every node in gadget_definition, generate the gadget's C function
        (func_name) and add it to unique_gadgets_definition if not already present.
        Replaces the long if/elif chain in the original mlrc().
        """
        gadget_classes = {
            'hpc1'         : HPC1,
            'hpc2'         : HPC2,
            'hpc3'         : HPC3,
            'hpc2o'        : HPC2o,
            'hpc3o'        : HPC3o,
            'comar'        : COMAR,
            'domand'       : Domand,
            'hpc2_swapped' : HPC2Swapped,
            'hpc2o_swapped': HPC2oSwapped,
        }
        for node, spec in self.gadget_definition.items():
            gname = spec["gadget_name"].lower()
            if gname not in gadget_classes:
                continue
            obj        = gadget_classes[gname](d=self.d) if gname != 'comar' else COMAR()
            gadget_def = obj.generate_multiply_function()
            func_name  = obj.get_function_name()
            spec["func_name"] = func_name
            if gname not in self.unique_gadgets_definition:
                self.unique_gadgets_definition[gname] = gadget_def

    def _compute_mlrc_totals(self, use_comar):
        """
        Recompute total randomness (COMAR counted once), critical-path latency,
        and total area after all gadget assignments are finalised.
        """
        self.total_randomness_after_mlrc = sum(
            info["random_numbers"]
            for info in self.gadget_definition.values()
            if info["gadget_name"] != "comar"
        )
        if use_comar:
            self.total_randomness_after_mlrc += 6

        self.total_latency_after_mlrc = self._compute_critical_path_latency()
        self.total_area_after_mlrc    = sum(
            self.gadget_map[info["gadget_name"]]["area"]
            for info in self.gadget_definition.values()
        )

    def mlrc(self, target_randomness):
        """
        Minimize latency under the given randomness constraint.
        Use Greedy approch
        steps:
        1. Build min-heap (levels ordered by node count, fewest first)
        2. Choose initial gadget & compute randomness budget
        3. Greedy replacement loop
           a. Full-level upgrade  → _replace_full_level()
           b. Partial/area upgrade → _find_best_area_gadget() + _replace_partial_level()
        4. assign initial gadget to unvisited heap nodes (when budget runs out)
        5. Generate gadget C-function definitions
        6. Compute cost totals (randomness, latency, area)
        7. Pattern-aware hpc*o upgrade (nodes_gadget_assignment)
        """
        # step 1: Build min-heap of levels ordered by node count (fewest first)
        min_heap = self.construct_min_heap()
        print(f"[INFO]: Constructed min heap\n{min_heap}")

        # step 2: Initial gadget & randomness budget calculation
        initial_gadget_name, initial_randomness, initial_latency = \
            self.initial_gadget_and_list_possible_replacement(target_randomness)
        initial_area          = self.gadget_map[initial_gadget_name]['area']
        total_replacable_nodes = sum(entry[0] for entry in min_heap)

        budget = self._compute_randomness_budget(
            target_randomness,
            initial_gadget_name, initial_randomness,
            initial_latency, initial_area,
            total_replacable_nodes,
        )
        if budget is None:
            return  # target cannot be met

        initial_randomness_bonus = budget['randomness_bonus']
        randomness_bonus         = budget['randomness_bonus']
        use_comar                = budget['use_comar']
        initial_gadget_name      = budget['initial_gadget_name']
        initial_randomness       = budget['initial_randomness']
        initial_area             = budget['initial_area']

        # step 3: Greedy replacement loop 
        if randomness_bonus > 0:
            self.sort_gadget()

            while randomness_bonus > 0:
                print(f"[INFO]: Bonus randomness: {randomness_bonus}")

                min_level, gadget_nodes = self.find_min_gate_level(min_heap)
                if min_level is None:
                    break

                top_gadget    = next(iter(self.gadget_map))
                top_specs     = self.gadget_map[top_gadget]
                required_rand = (top_specs["randomness"]
                                 if use_comar
                                 else top_specs["randomness"] - initial_randomness)
                total_needed  = required_rand * len(gadget_nodes)

                print(f"[INFO]: Level {min_level} — {len(gadget_nodes)} nodes, "
                      f"top gadget={top_gadget}, needed={total_needed}")

                if total_needed <= randomness_bonus:
                    # Whole level fits in budget
                    spent = self._replace_full_level(gadget_nodes, top_gadget, min_level)
                    randomness_bonus -= spent
                else:
                    # Partial upgrade: find best area-reduction gadget
                    node_count = self.and_tree.graph.num_nodes() - self.processed_node
                    gadget_name, replaceable_count, cost_per_node = \
                        self._find_best_area_gadget(
                            initial_gadget_name, initial_randomness, initial_area,
                            randomness_bonus, use_comar, node_count,
                        )

                    if replaceable_count > 0 and gadget_name:
                        spent = self._replace_partial_level(
                            gadget_nodes, gadget_name, cost_per_node,
                            replaceable_count, initial_gadget_name,
                            min_heap, min_level,
                        )
                        randomness_bonus -= spent
                    else:
                        # No beneficial replacement — give this level the initial gadget
                        for node in gadget_nodes:
                            if self.gadget_definition.get(node) is None:
                                self.gadget_definition[node] = {
                                    "gadget_name"    : initial_gadget_name,
                                    "random_numbers" : self.gadget_map[initial_gadget_name]["randomness"],
                                }
                        break

                print("-------------------------------------------------------------------")

        # step 4: Fallback for nodes still in heap 
        self._assign_fallback_gadgets(min_heap, initial_gadget_name)

        # step 5: Generate gadget C-function definitions 
        self._build_gadget_definitions()

        print("GADGET ASSIGNMENT FOR NODES")
        self.print_gadget_definition()
        print(f"target_randomness: {target_randomness}")

        # step 6: Cost totals 
        self._compute_mlrc_totals(use_comar)
        self.initial_randomness_bonus = initial_randomness_bonus

        # step 7: Pattern-aware hpc*o upgrade
        self.nodes_gadget_assignment()
        # # step 8: Arrival depth-based asymmetric gadget optimization (HPC3 → HPC2 where safe)
        # print("\n" + "=" * 80)
        # print("STEP 8: ARRIVAL DEPTH-BASED OPTIMIZATION (initial pass)")
        # print("=" * 80)
        # self.optimize_gadget_mapping_for_cost_asymmetric()
        # # step 9: Asymmetric input-order flipping (HPC2/HPC2o input swapping)
        # print("\n" + "=" * 80)
        # print("STEP 9: ASYMMETRIC LATENCY OPTIMIZER (input-order flipping)")
        # print("=" * 80)
        # flip_optimizer = AsymmetricLatencyOptimizer(
        #     gadget_definition=self.gadget_definition,
        #     nodes_by_level=self.nodes_by_level,
        # )
        # flip_optimizer.optimize(max_iterations=30)


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
        

        # step 9: Asymmetric input-order flipping (HPC2/HPC2o input swapping)
        print("\n" + "=" * 80)
        print("STEP 9: ASYMMETRIC LATENCY OPTIMIZER (input-order flipping)")
        print("=" * 80)
        flip_optimizer = AsymmetricLatencyOptimizer(
            gadget_definition=self.gadget_definition,
            nodes_by_level=self.nodes_by_level,
        )
        flip_optimizer.optimize(max_iterations=30)
        # step 8: Arrival depth-based asymmetric gadget optimization (HPC3 → HPC2 where safe)
        print("\n" + "=" * 80)
        print("STEP 8: ARRIVAL DEPTH-BASED OPTIMIZATION (initial pass)")
        print("=" * 80)
        self.optimize_gadget_mapping_for_cost_asymmetric()



        

        # step 10: Arrival depth-based optimization (second pass, latency-constrained)
        print("\n" + "=" * 80)
        print("STEP 10: ARRIVAL DEPTH-BASED OPTIMIZATION (latency-constrained pass)")
        print("=" * 80)
        opt_stats = self.optimize_gadget_mapping_for_cost_asymmetric(
            target_latency=self.total_latency_after_mlrc,
        )
        self.total_randomness_after_mlrc = opt_stats["final_randomness"]
        self.total_area_after_mlrc       = opt_stats["final_area"]
        self.total_latency_after_mlrc    = opt_stats["final_critical_path"]

        self.print_gadget_definition()

        print(f"initial randomness bonus : {initial_randomness_bonus}")
        print(f"total randomness used    : {self.total_randomness_after_mlrc}")
        print(f"total latency            : {self.total_latency_after_mlrc}")
        print(f"total area               : {self.total_area_after_mlrc}")

    def nodes_gadget_assignment(self):
        """
        Use MLRC's gadget choices per level as base and upgrade xor_and nodes to hpc3o/hpc2o.

        - updates the self.node_pattern and self.gadget_definition to reflect 
        the final gadget assignment after MLRC, including pattern-aware upgrades.
        """
        print("\n[MLRC] Pattern-aware nodes_gadget_assignment (with hpc2o/hpc3o upgrades)")
        if not hasattr(self, 'gadget_definition'):
            self.gadget_definition = {}

        # Analyze patterns if not done
        if not hasattr(self, 'node_pattern') or not self.node_pattern:
            self._analyze_and_xor_tree_for_patterns()

        normalized_pattern = {str(k).strip(): v for k, v in self.node_pattern.items()}
        upgraded = 0

        # For MLRC, gadget per node is already set in self.gadget_definition from mlrc()
        new_gadget_def = {}

        for node_expr, info in self.gadget_definition.items():
            gname = info["gadget_name"]
            key = str(node_expr).strip()
            pattern_info = normalized_pattern.get(key, ("pure_and", None, None))
            if isinstance(pattern_info, tuple) and len(pattern_info) == 3:
                pattern, xor_consumer, xor_other_operand = pattern_info
            elif isinstance(pattern_info, tuple):
                pattern, xor_consumer = pattern_info
                xor_other_operand = None
            else:
                pattern, xor_consumer, xor_other_operand = pattern_info, None, None

            gadget = gname
            if pattern == 'xor_and':
                old = gadget

                # Prefer matching optimized gadget based on original type
                if old == 'hpc3' and 'hpc3o' in self.gadget_map:
                    gadget = 'hpc3o'
                elif old == 'hpc2' and 'hpc2o' in self.gadget_map:
                    gadget = 'hpc2o'
                elif old == 'hpc2_swapped' and 'hpc2o_swapped' in self.gadget_map:
                    gadget = 'hpc2o_swapped'
                
                if old != gadget:
                    print(f"[MLRC UPGRADE] {node_expr}: {old} -> {gadget} (xor_and, XOR consumer={xor_consumer})")
                    upgraded += 1

            new_gadget_def[node_expr] = {
                "gadget_name": gadget,
                "random_numbers": self.gadget_map[gadget]["randomness"],
                "xor_consumer": xor_consumer,
                "xor_other_operand": xor_other_operand,
            }

        self.gadget_definition = new_gadget_def
        print(f"[MLRC] Upgraded {upgraded} nodes to optimized hpc*o gadgets")

        # Build unique_gadgets_definition and func_name exactly like MRLC
        self.unique_gadgets_definition = {}
        gadget_classes = {
            'hpc1': HPC1, 'hpc2': HPC2, 'hpc3': HPC3,
            'hpc2o': HPC2o, 'hpc3o': HPC3o,
            'comar': COMAR, 'domand': Domand
        }

        for expr, info in self.gadget_definition.items():
            gname = info["gadget_name"].lower()
            if gname not in self.unique_gadgets_definition and gname in gadget_classes:
                obj = gadget_classes[gname](d=self.d) if gname != 'comar' else COMAR()
                self.unique_gadgets_definition[gname] = obj.generate_multiply_function()
                func_name = obj.get_function_name()
                for e, spec in self.gadget_definition.items():
                    if spec["gadget_name"].lower() == gname:
                        spec["func_name"] = func_name

        # update totals
        self.total_randomness_after_mlrc = sum(info["random_numbers"] for info in self.gadget_definition.values())
        # Compute critical path latency instead of summing all level latencies
        # self.total_latency_after_mlrc = self._compute_critical_path_latency()
        self.total_area_after_mlrc = sum(self.gadget_map[info["gadget_name"]]["area"]
                                         for info in self.gadget_definition.values())

    def sort_gadget(self):
        """
        Sort self.gadget_map in-place by:
          1) latency (ascending)
          2) randomness (ascending)
          3) area (ascending)
        and keep it as an OrderedDict to get the best gadget.
        """
        # sort items according to MLRC policy
        sorted_items = sorted(
            self.gadget_map.items(),
            key=lambda item: (item[1]["latency"], item[1]["randomness"], item[1]["area"])
        )
        # rebuild gadget_map as ordered dict
        self.gadget_map = OrderedDict(sorted_items)

    def _get_replacement_gadget(self, current_gadget, target_latency=None):
        """
        Suggest a replacement gadget for cost reduction (randomness/area) without increasing latency.
        
        Args:
            current_gadget (str): name of current gadget (e.g., 'hpc3')
            target_latency (int): max allowed latency; if None, use current critical path
        
        Returns:
            str or None: name of replacement gadget, or None if no valid replacement
        """
        if current_gadget not in self.gadget_map:
            return None
        
        current_specs = self.gadget_map[current_gadget]
        current_latency = current_specs["latency"]
        current_randomness = current_specs["randomness"]
        current_area = current_specs["area"]
        
        # Find gadgets with same or lower latency
        candidates = {
            name: specs for name, specs in self.gadget_map.items()
            if name != current_gadget and specs["latency"] <= current_latency
        }
        
        if not candidates:
            return None
        
        # Prefer lower randomness; break ties by area
        best = min(
            candidates.items(),
            key=lambda item: (item[1]["randomness"], item[1]["area"])
        )
        
        return best[0] if best[1]["randomness"] < current_randomness else None

    def _can_swap_hpc3_to_hpc2_asymmetric(self, node_expr):
        """
        Check if an HPC3 node can be replaced with HPC2 using asymmetric path properties.
        
        HPC2 is asymmetric: one input path has latency 2, the other has latency 1.
        HPC3 has both paths with latency 1.
        
        We can replace HPC3 → HPC2 if:
        - The critical path does NOT depend on the "slow" (latency-2) input of HPC2
        - Or the fast input (latency-1) is on the critical path
        
        Args:
            node_expr (str): AND node expression (e.g., "M31 = M20 & M23")
        
        Returns:
            tuple: (can_swap: bool, reason: str)
        """
        if '=' not in node_expr:
            return False, "Invalid node format"
        
        lhs, rhs = node_expr.split('=', 1)
        lhs = lhs.strip()
        rhs = rhs.strip()
        
        # Extract the two inputs
        if ' & ' not in rhs:
            return False, "Not an AND node"
        
        input_a, input_b = rhs.split('&', 1)
        input_a = input_a.strip()
        input_b = input_b.strip()
        
        # Check if this is an xor_and pattern (AND output fed to XOR)
        is_xor_consumer = False
        if hasattr(self, 'node_pattern'):
            pattern_info = self.node_pattern.get(node_expr, ("pure_and", None, None))
            if isinstance(pattern_info, tuple) and len(pattern_info) >= 2:
                pattern, xor_consumer = pattern_info[0], pattern_info[1]
            else:
                pattern, xor_consumer = pattern_info, None

            is_xor_consumer = (pattern == "xor_and" and xor_consumer is not None)
        print(f"{is_xor_consumer} {node_expr}")
        # Heuristic: For xor_and nodes, the fast path (latency 1) of HPC2 can absorb
        # the latency since it's masked by XOR operations at the consumer.
        # For pure AND nodes, we're more conservative.
        
        if is_xor_consumer:
            return True, f"xor_and pattern detected (consumer: {xor_consumer}); HPC2 fast path viable"
        else:
            return False, "Pure AND node; HPC2 slow path may be on critical path"

    def _compute_arrival_depths(self):
        """
        Compute arrival depth for each AND node based on their inputs.
        Depth measures how many AND operations deep a variable is.
        
        Returns:
            dict: {node_expr: (depth_A, depth_B)} for AND nodes
        """
        depths = {}
        var_depth = {}  # Track depth of each variable
        
        # Process levels in order
        for lvl in sorted(self.nodes_by_level.keys()):
            for node_expr in self.nodes_by_level[lvl]:
                node_str = str(node_expr)
                
                if '=' not in node_str:
                    continue
                
                lhs, rhs = node_str.split('=', 1)
                lhs = lhs.strip()
                rhs = rhs.strip()
                
                # Extract outputs
                lhs_clean = lhs.replace('*', '').strip()
                
                # Check if it's an AND node
                if ' & ' in rhs:
                    input_a, input_b = rhs.split('&', 1)
                    input_a = input_a.strip().replace('*', '')
                    input_b = input_b.strip().replace('*', '')
                    
                    depth_a = var_depth.get(input_a, 0)
                    depth_b = var_depth.get(input_b, 0)
                    
                    depths[node_expr] = (depth_a, depth_b)
                    var_depth[lhs_clean] = max(depth_a, depth_b) + 1
                else:
                    # XOR or assignment: propagate depth
                    if ' ^ ' in rhs:
                        inputs = rhs.split('^')
                        max_depth = max(var_depth.get(inp.strip().replace('*', ''), 0) for inp in inputs)
                    else:
                        # Simple assignment
                        input_var = rhs.replace('*', '').strip()
                        max_depth = var_depth.get(input_var, 0)
                    
                    var_depth[lhs_clean] = max_depth
        
        return depths

    def optimize_gadget_mapping_for_cost_asymmetric(self, target_latency=None, max_iterations=100):
        """
        Post-MLRC optimization using arrival depth tracking.

        Strategy:
        - For each HPC3/HPC3o node whose two inputs arrive at different depths,
          replace with HPC2/HPC2o (half the randomness, same latency).
        - Choose the gadget variant based on which input arrives later:
            depth_a > depth_b  →  A is late  →  use hpc2         (a-port = fast, 1 cycle)
            depth_a < depth_b  →  B is late  →  use hpc2_swapped (a-port = slow, b-port = fast)
          This routes the late-arriving signal through the fast 1-cycle port so the
          critical path is unchanged while randomness is halved.
        - No input_reorder flag needed; the gadget name encodes the routing.

        Args:
            target_latency: max allowed latency (unused; kept for API compatibility)
            max_iterations: unused; kept for API compatibility

        Returns:
            dict: statistics of the optimization
        """
        if not hasattr(self, 'gadget_definition') or not self.gadget_definition:
            print("[WARN] No gadget_definition to optimize")
            return {}

        # Base gadget → swapped variant lookup
        _swapped = {'hpc2': 'hpc2_swapped', 'hpc2o': 'hpc2o_swapped'}

        stats = {
            "initial_randomness": sum(info["random_numbers"] for info in self.gadget_definition.values()),
            "initial_area": sum(self.gadget_map[info["gadget_name"]]["area"] for info in self.gadget_definition.values()),
            "replacements": [],
            "method": "arrival_depth_tracking",
        }

        print(f"\n[MLRC] Post-optimization: Arrival depth-based asymmetric gadget replacement")

        arrival_depths = self._compute_arrival_depths()
        print(f"[INFO] Computed arrival depths for {len(arrival_depths)} AND nodes")

        for node_expr, info in list(self.gadget_definition.items()):
            current_gadget = info["gadget_name"]

            if current_gadget not in ['hpc3', 'hpc3o']:
                continue

            if node_expr not in arrival_depths:
                continue

            depth_a, depth_b = arrival_depths[node_expr]
            depth_diff = abs(depth_a - depth_b)

            if depth_diff < 1:
                continue

            # Base replacement (hpc3→hpc2, hpc3o→hpc2o)
            base_replacement = 'hpc2' if current_gadget == 'hpc3' else 'hpc2o'

            if base_replacement not in self.gadget_map:
                continue

            old_randomness = info["random_numbers"]
            new_randomness = self.gadget_map[base_replacement]["randomness"]

            if new_randomness >= old_randomness:
                continue

            # Choose variant based on which input arrives LATER:
            #   depth_a > depth_b → A is late → put A on the fast 1-cycle port
            #     → use base hpc2  (a-port = fast)
            #   depth_a < depth_b → B is late → put B on the fast 1-cycle port
            #     → use hpc2_swapped (b-port = fast, a-port = slow)
            if depth_a < depth_b:
                replacement = base_replacement            # a-port = fast (1 cycle)
            else:
                replacement = _swapped[base_replacement]  # b-port = fast (1 cycle)

            # hpc2_swapped/hpc2o_swapped share the same specs as hpc2/hpc2o
            actual_key = base_replacement
            old_area = self.gadget_map[current_gadget]["area"]
            new_area = self.gadget_map[actual_key]["area"]

            info["gadget_name"]    = replacement
            info["random_numbers"] = new_randomness

            stats["replacements"].append({
                "node":             node_expr,
                "from":             current_gadget,
                "to":               replacement,
                "depth_a":          depth_a,
                "depth_b":          depth_b,
                "depth_diff":       depth_diff,
                "randomness_saved": old_randomness - new_randomness,
                "area_change":      new_area - old_area,
            })

            late_input = "A" if depth_a >= depth_b else "B"
            print(f"   ✓ {node_expr}: {current_gadget} → {replacement}")
            print(f"     Depth: A={depth_a}, B={depth_b}  |  late input = {late_input} → fast port")
            print(f"     Randomness: {old_randomness} → {new_randomness} (saved: {old_randomness - new_randomness})")
            print(f"     Area: {old_area:.1f} → {new_area:.1f}")

        stats["final_randomness"]      = sum(info["random_numbers"] for info in self.gadget_definition.values())
        stats["final_area"]            = sum(self.gadget_map[info["gadget_name"].replace('_swapped', '')]["area"]
                                             for info in self.gadget_definition.values())
        stats["total_randomness_saved"] = stats["initial_randomness"] - stats["final_randomness"]
        stats["final_critical_path"]   = self._compute_critical_path_latency()

        print(f"\n[MLRC] Arrival depth optimization complete:")
        print(f"       Total replacements: {len(stats['replacements'])}")
        print(f"       Randomness: {stats['initial_randomness']} → {stats['final_randomness']} (saved: {stats['total_randomness_saved']})")
        print(f"       Area: {stats['initial_area']:.1f} → {stats['final_area']:.1f}")
        print(f"       Final critical path latency: {stats['final_critical_path']}")

        # Regenerate unique gadget definitions (now includes swapped variants)
        print(f"\n[MLRC] Regenerating gadget definitions (including swapped variants)...")
        self._build_gadget_definitions()
        print(f"[MLRC] Generated {len(self.unique_gadgets_definition)} unique gadget definitions: "
              f"{list(self.unique_gadgets_definition.keys())}")

        return stats

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



    def optimize_gadget_mapping_for_cost(self, target_latency=None, max_iterations=10):
        """
        Post-MLRC optimization: greedily replace high-cost gadgets with cheaper alternatives
        while respecting the latency constraint (via critical path).
        
        Args:
            target_latency (int): max allowed latency; if None, computed from current critical path
            max_iterations (int): max replacement iterations
        
        Returns:
            dict: statistics of the optimization
        """
        if not hasattr(self, 'gadget_definition') or not self.gadget_definition:
            print("[WARN] No gadget_definition to optimize")
            return {}
        
        if target_latency is None:
            target_latency = self._compute_critical_path_latency()
            print(f"[INFO] Using current critical path latency as target: {target_latency}")
        
        stats = {
            "initial_randomness": sum(info["random_numbers"] for info in self.gadget_definition.values()),
            "initial_area": sum(self.gadget_map[info["gadget_name"]]["area"] for info in self.gadget_definition.values()),
            "replacements": [],
            "iterations": 0
        }
        
        print(f"\n[MLRC] Post-optimization: Cost reduction with latency constraint ≤ {target_latency}")
        
        # Repeatedly try to replace nodes
        for iteration in range(max_iterations):
            replaced_this_iter = False
            
            # Find nodes that might benefit from replacement
            for node_expr, info in list(self.gadget_definition.items()):
                current_gadget = info["gadget_name"]
                replacement = self._get_replacement_gadget(current_gadget, target_latency)
                
                if replacement is None:
                    continue
                
                # Tentatively replace
                old_gadget = info["gadget_name"]
                old_randomness = info["random_numbers"]
                old_area = self.gadget_map[old_gadget]["area"]
                
                info["gadget_name"] = replacement
                info["random_numbers"] = self.gadget_map[replacement]["randomness"]
                new_area = self.gadget_map[replacement]["area"]
                
                # Check if latency constraint is still satisfied
                new_critical_path = self._compute_critical_path_latency()
                
                if new_critical_path <= target_latency:
                    # Replacement accepted
                    stats["replacements"].append({
                        "node": node_expr,
                        "from": old_gadget,
                        "to": replacement,
                        "randomness_saved": old_randomness - self.gadget_map[replacement]["randomness"],
                        "area_change": new_area - old_area
                    })
                    replaced_this_iter = True
                    print(f"   ✓ {node_expr}: {old_gadget} → {replacement} "
                          f"(rand: {old_randomness}→{info['random_numbers']}, area: {old_area:.1f}→{new_area:.1f})")
                    break  # Re-scan from beginning
                else:
                    # Revert
                    info["gadget_name"] = old_gadget
                    info["random_numbers"] = old_randomness
            
            if not replaced_this_iter:
                break
            
            stats["iterations"] += 1
        
        stats["final_randomness"] = sum(info["random_numbers"] for info in self.gadget_definition.values())
        stats["final_area"] = sum(self.gadget_map[info["gadget_name"]]["area"] for info in self.gadget_definition.values())
        stats["total_randomness_saved"] = stats["initial_randomness"] - stats["final_randomness"]
        stats["final_critical_path"] = self._compute_critical_path_latency()
        
        print(f"\n[MLRC] Optimization complete:")
        print(f"       Iterations: {stats['iterations']}")
        print(f"       Total replacements: {len(stats['replacements'])}")
        print(f"       Randomness: {stats['initial_randomness']} → {stats['final_randomness']} (saved: {stats['total_randomness_saved']})")
        print(f"       Area: {stats['initial_area']:.1f} → {stats['final_area']:.1f}")
        print(f"       Final critical path latency: {stats['final_critical_path']}")
        
        return stats

# ============================================================================
# COMPLETE MLRC PIPELINE WITH INPUT REORDERING (FINAL)
# ============================================================================
#
# STEP 1: Initial MLRC
#   - Assign all AND nodes to HPC2 (minimum randomness)
#   - Use randomness budget to upgrade to HPC3/HPC3o
#   - Result: initial mapping, latency minimized
#
# STEP 2: Pattern Analysis (xor_and detection)
#   - Detect AND nodes feeding directly to XOR
#   - Upgrade xor_and nodes: HPC3 → HPC3o, HPC2 → HPC2o
#   - Benefit: ~10% area reduction
#
# STEP 3: Arrival Depth Optimization (NEW!)
#   - Compute arrival depth for each AND node
#   - For HPC3/HPC3o with depth_diff ≥ 1:
#     - Replace HPC3 → HPC2 (or HPC3o → HPC2o)
#     - Determine input routing based on depths
#     - Store reordering info (keep_order or swap_inputs)
#   - Result: ~22 nodes replaced, ~22 randomness saved
#
# STEP 4: Input Reordering Decision
#   For each replaced node:
#     if depth_A < depth_B:
#       input_reorder = "keep_order"
#       slow_input = "A" (depth_A on slow path 2)
#       fast_input = "B" (depth_B on fast path 1)
#     else:
#       input_reorder = "swap_inputs"
#       slow_input = "B" (depth_B on slow path 2)
#       fast_input = "A" (depth_A on fast path 1)
#
# STEP 5: Share Splitting
#   - ShareTransformer uses gadget_map + input_reorder info
#   - For "keep_order" nodes: HPC2(a0, a1, b0, b1, ...)
#   - For "swap_inputs" nodes: HPC2(b0, b1, a0, a1, ...) ← SWAPPED
#   - Result: correct C code with proper input routing
#
# FINAL METRICS (d=1, target_randomness=111):
#   Initial MLRC: 68 randomness, 3 latency, 156 area
#   After optimization: 46 randomness, 3 latency, 164 area
#   Savings: 22 randomness bits, 0 latency increase
#   Gadgets: 9 hpc3, 3 hpc3o, 15 hpc2, 7 hpc2o
#   Swaps: 16 nodes with input swaps, 6 nodes keeping order
#
# ============================================================================
