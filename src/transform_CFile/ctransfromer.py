# from pycparser import c_ast, c_generator, c_parser
# from copy import deepcopy
# import re

# class ShareTransformer:
#     def __init__(self, num_shares, gadget_expr_map, unique_gadget_def, arrival_depths=None):
#         self.num_shares = num_shares
#         self.gadget_expr_map = gadget_expr_map
#         self.unique_gadget_def = unique_gadget_def
#         self.arrival_depths = arrival_depths or {}  # NEW: arrival depth dict
#         self.generator = c_generator.CGenerator()
#         self.injected_random_decls = set()
#         self.rand_counter = 0
#         self.comar_rand_added = False
#         self.optimized_outputs = set()  # tracks AND outputs from hpc2o/hpc3o
#         self.variable_arrival_depths = {}  # Track depths of intermediate variables
        
#         # DEBUG: Print gadget map info
#         print("\n" + "="*80)
#         print("SHARETRANSFORMER INITIALIZATION")
#         print("="*80)
#         print(f"[INIT] Total gadgets in map: {len(gadget_expr_map)}")
#         print(f"[INIT] Unique definitions: {list(unique_gadget_def.keys())}")
        
#         # Count gadget types in map
#         gadget_counts = {}
#         for key, info in gadget_expr_map.items():
#             gname = info.get("gadget_name", "unknown")
#             gadget_counts[gname] = gadget_counts.get(gname, 0) + 1
        
#         print(f"\n[INIT] Gadget breakdown in map:")
#         for gname in sorted(gadget_counts.keys()):
#             count = gadget_counts[gname]
#             print(f"  {gname:8s}: {count:3d} gates")
#         print("="*80 + "\n")

#     def transform(self, node):
#         method = f"transform_{type(node).__name__}"
#         return getattr(self, method)(node)

#     def transform_FileAST(self, node):
#         """Only transform the main circuit — gadgets are inserted as raw text later."""
#         top_level_func = None
#         for item in node.ext:
#             if isinstance(item, c_ast.FuncDef):
#                 top_level_func = item
#                 break
#         assert top_level_func is not None, "Could not find any function definition in the file"

#         transformed_top_level = self.transform(top_level_func)

#         # Return ONLY the transformed main function (gadgets added in main script)
#         node.ext = [transformed_top_level]
        
#         # Print final summary
#         print("\n" + "="*80)
#         print("SHARETRANSFORMER TRANSFORMATION COMPLETE")
#         print("="*80)
        
#         return node

#     def _clean_gadget_code(self, code: str) -> str:
#         """Remove comments so pycparser doesn't crash on HPC3o/HPC2o."""
#         import re
#         # Remove /* */ comments
#         code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)
#         # Remove // comments
#         code = re.sub(r'//.*$', '', code, flags=re.MULTILINE)
#         # Clean empty lines
#         lines = [line.strip() for line in code.splitlines() if line.strip()]
#         return '\n'.join(lines)

#     def _get_arrival_depth(self, var_name):
#         """Get arrival depth of a variable (how many AND levels deep it is)."""
#         clean_name = var_name.replace('*', '').replace('&', '').strip()
#         return self.variable_arrival_depths.get(clean_name, 0)
    
#     def _update_arrival_depths(self, node_expr, output_name, depth_a, depth_b):
#         """Update arrival depths after an AND gate operation."""
#         # Output depth = max(input_depths) + 1 for AND operations
#         out_depth = max(depth_a, depth_b) + 1
#         clean_out = output_name.replace('*', '').replace('&', '').strip()
#         self.variable_arrival_depths[clean_out] = out_depth
#         return out_depth
    
#     def _should_swap_inputs(self, gadget_name, depth_a, depth_b):
#         """
#         Determine if inputs should be swapped for asymmetric gadgets.
        
#         HPC2/HPC2o have asymmetric latencies:
#         - Inputs A: latency 2 (slow path)
#         - Inputs B: latency 1 (fast path)
        
#         Strategy: place early-arriving input on slow path
#         """
#         if gadget_name not in ['hpc2', 'hpc2o']:
#             return False, None  # No swap for HPC3/HPC3o
        
#         depth_diff = abs(depth_a - depth_b)
        
#         # Only swap if arrival depths differ significantly
#         if depth_diff >= 1:
#             if depth_a < depth_b:
#                 # A arrives early → put A on slow path (swap to second position)
#                 return True, "swap"  # Swap A and B
#             else:
#                 # B arrives early → keep order (A on slow, B on fast)
#                 return False, "keep"
        
#         return False, None  # No difference worth swapping

#     def transform_FuncDef(self, node):
#         node.body = self.transform(node.body)

#         if not node.decl.type.args:
#             node.decl.type.args = c_ast.ParamList(params=[])

#         original_params = node.decl.type.args.params
#         new_params = []

#         for param in original_params:
#             if param.name.startswith("dec_"):
#                 new_params.append(param)
#             else:
#                 for i in range(self.num_shares):
#                     new_param = deepcopy(param)
#                     new_param.name = f"{param.name}_{i}"
#                     typ = new_param.type
#                     if isinstance(typ, c_ast.TypeDecl):
#                         typ.declname = new_param.name
#                     elif isinstance(typ, c_ast.PtrDecl) and isinstance(typ.type, c_ast.TypeDecl):
#                         typ.type.declname = new_param.name
#                     new_params.append(new_param)

#         for rand_id in self.injected_random_decls:
#             param_decl = c_ast.Decl(
#                 name=rand_id.name, quals=[], storage=[], funcspec=[], align=None,
#                 type=c_ast.TypeDecl(
#                     declname=rand_id.name, quals=[], align=None,
#                     type=c_ast.IdentifierType(['int'])
#                 ),
#                 init=None, bitsize=None
#             )
#             new_params.append(param_decl)

#         node.decl.type.args.params = new_params
#         return node

#     def transform_Compound(self, node):
#         new_items = []
#         new_items.extend(self.injected_random_decls)
#         self.injected_random_decls.clear()

#         for stmt in node.block_items or []:
#             result = self.transform(stmt)
#             if isinstance(result, list):
#                 new_items.extend(result)
#             elif result:
#                 new_items.append(result)

#         return c_ast.Compound(block_items=new_items)

#     def transform_Decl(self, node):
#         if node.name.startswith("dec_"):
#             return node

#         decls = []
#         for i in range(self.num_shares):
#             new_decl = deepcopy(node)
#             new_decl.name = f"{node.name}_{i}"

#             if isinstance(new_decl.type, c_ast.TypeDecl):
#                 new_decl.type.declname = new_decl.name

#             if new_decl.init:
#                 new_decl.init = self.rename_ids(new_decl.init, i)

#             decls.append(new_decl)
#         return decls

#     def transform_Assignment(self, node):
#         # 1. Special NOT case (XOR with dec_1) – works for IDs and pointer lvalues
#         if isinstance(node.rvalue, c_ast.BinaryOp) and node.rvalue.op == '^':
#             left_dec = isinstance(node.rvalue.left, c_ast.ID) and node.rvalue.left.name == "dec_1"
#             right_dec = isinstance(node.rvalue.right, c_ast.ID) and node.rvalue.right.name == "dec_1"
#             if left_dec or right_dec:
#                 operand = node.rvalue.right if left_dec else node.rvalue.left
#                 not_expr = c_ast.UnaryOp(op='~', expr=operand)
#                 results = []
#                 for i in range(self.num_shares):
#                     new_assign = deepcopy(node)
#                     # scalar outputs
#                     if isinstance(new_assign.lvalue, c_ast.ID):
#                         new_assign.lvalue.name = f"{new_assign.lvalue.name}_{i}"
#                     # pointer outputs like *Yk
#                     elif isinstance(new_assign.lvalue, c_ast.UnaryOp) and new_assign.lvalue.op == '*':
#                         inner = new_assign.lvalue.expr
#                         if isinstance(inner, c_ast.ID):
#                             inner.name = f"{inner.name}_{i}"
#                     # RHS: share-wise NOT via rename_ids
#                     new_assign.rvalue = self.rename_ids(deepcopy(not_expr), i)
#                     results.append(new_assign)
#                 return results

#         # 2. Generate lookup key - TRY MULTIPLE MATCHING STRATEGIES
#         original_key = self.generator.visit(node).strip()
#         gadget = None
#         match_strategy = None
        
#         # Strategy 1: Try direct match with original key
#         gadget = self.gadget_expr_map.get(original_key)
#         if gadget:
#             match_strategy = "exact"
        
#         # Strategy 2: Try normalized key (remove spaces and parens)
#         if not gadget:
#             key = re.sub(r'\s+|\(|\)', '', original_key)
#             key = re.sub(r'_\d+', '', key)
#             gadget = self.gadget_expr_map.get(key)
#             if gadget:
#                 match_strategy = "normalized"
        
#         # Strategy 3: Try LHS lookup
#         if not gadget:
#             lhs = original_key.split('=')[0].strip()
#             gadget = self.gadget_expr_map.get(lhs)
#             if gadget:
#                 match_strategy = "lhs"
        
#         # Strategy 4: Search through all keys to find partial match
#         if not gadget:
#             for map_key, map_val in self.gadget_expr_map.items():
#                 # Check if this maps to the same LHS variable
#                 if '=' in str(map_key) and '=' in original_key:
#                     map_lhs = str(map_key).split('=')[0].strip()
#                     orig_lhs = original_key.split('=')[0].strip()
#                     if map_lhs == orig_lhs:
#                         gadget = map_val
#                         match_strategy = "search"
#                         break
        
#         if not gadget:
#             print(f"[NO MATCH] {original_key[:55]:55s} → NO GADGET FOUND - default assignment")

#         if gadget:
#             gadget_name = gadget["gadget_name"].lower()
#             func_name = gadget["func_name"]
#             rand_count = gadget.get("random_numbers", 0)
#             xor_consumer = gadget.get("xor_consumer")  # may be None
            
#             # DEBUG: Log which gadget was selected with detailed info
#             print(f"[GADGET] Node: {original_key[:55]:55s} → {gadget_name:6s} | Rands: {rand_count} | Func: {func_name} | Strategy: {match_strategy}")
#             print(f"[DEBUG] gadget_name={gadget_name}, func_name={func_name}, rand_count={rand_count}")

#             a_all = [self.rename_ids(deepcopy(node.rvalue.left), i) for i in range(self.num_shares)]
#             b_all = [self.rename_ids(deepcopy(node.rvalue.right), i) for i in range(self.num_shares)]
            
#             # CHECK: Should we swap inputs for HPC2/HPC2o?
#             should_swap = False
#             if gadget_name in ['hpc2', 'hpc2o']:
#                 should_swap = gadget.get("swap_needed", False)
#                 if should_swap:
#                     print(f"[SWAP] {original_key[:60]}")
#                     a_all, b_all = b_all, a_all
#                 else:
#                     print(f"[KEEP] {original_key[:60]}")
            
#             # If swap needed for HPC2/HPC2o, swap the inputs
#             if should_swap:
#                 a_all, b_all = b_all, a_all
#                 print(f"       ✓ Inputs swapped for correct HPC2/HPC2o operation")

#             # Compute arrival depths for this AND gate
#             depth_a = self._get_arrival_depth(self.generator.visit(node.rvalue.left).strip())
#             depth_b = self._get_arrival_depth(self.generator.visit(node.rvalue.right).strip())
            
#             # Check if we should swap inputs (for HPC2/HPC2o asymmetry)
#             should_swap, swap_action = self._should_swap_inputs(gadget_name, depth_a, depth_b)
            
#             # Apply swap if needed


#             # === HPC3o / HPC2o: use XOR consumer as third input ===
#             if gadget_name in ['hpc2o', 'hpc3o']:
#                 if xor_consumer is None:
#                     # Fallback: behave like non-optimized wiring, but this indicates a bug in pattern propagation
#                     w_all = b_all[:]
#                 else:
#                     # w_all is the XOR node that consumes this AND output, per share
#                     w_all = [c_ast.ID(f"{xor_consumer}_{i}") for i in range(self.num_shares)]

#                 rand_args = [c_ast.ID(f"rand_{j+1}") for j in range(self.rand_counter, self.rand_counter + rand_count)]
#                 self.rand_counter += rand_count
#                 self.injected_random_decls.update(rand_args)

#                 # Build output arguments: &c0, &c1, ... for all shares
#                 if isinstance(node.lvalue, c_ast.ID):
#                     out_all = [c_ast.UnaryOp(op='&', expr=c_ast.ID(f"{node.lvalue.name}_{i}")) for i in range(self.num_shares)]
#                     # HPC3o/HPC2o args: a_all + b_all + w_all + out_all + rand_args
#                     args = a_all + b_all + w_all + out_all + rand_args
#                 else:
#                     # Pointer output - not typical but handle it
#                     args = a_all + b_all + w_all + rand_args

#                 return [c_ast.FuncCall(name=c_ast.ID(func_name), args=c_ast.ExprList(args))]

#             # === Normal gadgets (unchanged) ===
#             if gadget_name == 'comar':
#                 rand_args = [c_ast.ID(f"comar_r{j+1}") for j in range(rand_count)]
#                 if not self.comar_rand_added:
#                     self.injected_random_decls.update(rand_args)
#                     self.comar_rand_added = True
#             else:
#                 # FIXED: Generate only the required number of random variables
#                 # For HPC3/HPC2: need 1-2 random variables
#                 # For HPC3o/HPC2o: need 2 random variables
#                 rand_args = []
#                 for j in range(rand_count):
#                     rand_name = f"rand_{self.rand_counter + j + 1}"
#                     rand_id = c_ast.ID(rand_name)
#                     rand_args.append(rand_id)
#                     # Create a Decl node for the random variable
#                     rand_decl = c_ast.Decl(
#                         name=rand_name, quals=[], storage=[], funcspec=[], align=None,
#                         type=c_ast.TypeDecl(
#                             declname=rand_name, quals=[], align=None,
#                             type=c_ast.IdentifierType(['int'])
#                         ),
#                         init=None, bitsize=None
#                     )
#                     self.injected_random_decls.add(rand_decl)
#                 self.rand_counter += rand_count

#             if isinstance(node.lvalue, c_ast.ID):
#                 out_all = [c_ast.UnaryOp(op='&', expr=c_ast.ID(f"{node.lvalue.name}_{i}")) for i in range(self.num_shares)]
#                 args = a_all + b_all + out_all + rand_args
#             else:
#                 args = a_all + b_all + rand_args

#             return [c_ast.FuncCall(name=c_ast.ID(func_name), args=c_ast.ExprList(args))]
#         if isinstance(node.rvalue, c_ast.BinaryOp) and node.rvalue.op == '^':
#             left_name = getattr(node.rvalue.left, 'name', None)
#             right_name = getattr(node.rvalue.right, 'name', None)
#             if left_name in self.optimized_outputs or right_name in self.optimized_outputs:
#                 final_side = node.rvalue.right if left_name in self.optimized_outputs else node.rvalue.left
#                 results = []
#                 for i in range(self.num_shares):
#                     new_assign = deepcopy(node)
#                     if isinstance(new_assign.lvalue, c_ast.ID):
#                         new_assign.lvalue.name = f"{new_assign.lvalue.name}_{i}"
#                     new_assign.rvalue = self.rename_ids(deepcopy(final_side), i)
#                     results.append(new_assign)
#                 return results

#         # 5. Normal share-wise assignment (unchanged except for pointer LHS support)
#         results = []
#         for i in range(self.num_shares):
#             new_assign = deepcopy(node)
#             if isinstance(new_assign.lvalue, c_ast.ID):
#                 new_assign.lvalue.name = f"{new_assign.lvalue.name}_{i}"
#             elif isinstance(new_assign.lvalue, c_ast.UnaryOp) and new_assign.lvalue.op == '*':
#                 inner = new_assign.lvalue.expr
#                 if isinstance(inner, c_ast.ID):
#                     inner.name = f"{inner.name}_{i}"
#             new_assign.rvalue = self.rename_ids(new_assign.rvalue, i)
#             results.append(new_assign)
#         return results

#     def rename_ids(self, node, i):
#         if node is None:
#             return None

#         # Generalized NOT handling for higher order: put the '~' only on one chosen share
#         if isinstance(node, c_ast.UnaryOp) and node.op == '~':
#             processed_child = self.rename_ids(deepcopy(node.expr), i)
#             # choose the highest-index share as the negated share
#             if i == self.num_shares - 1:
#                 return c_ast.UnaryOp(op='~', expr=processed_child)
#             else:
#                 return processed_child

#         elif isinstance(node, c_ast.ID):
#             if node.name.startswith("dec_"):
#                 return node
#             node.name = f"{node.name}_{i}"
#             return node
#         else:
#             for attr_name, child in node.children():
#                 if isinstance(child, c_ast.Node):
#                     setattr(node, attr_name, self.rename_ids(child, i))
#                 elif isinstance(child, list):
#                     new_list = [self.rename_ids(elem, i) if isinstance(elem, c_ast.Node) else elem for elem in child]
#                     setattr(node, attr_name, new_list)
#             return node

# # ============================================================================
# # FIX: ShareTransformer Gadget Function Call Arguments
# # ============================================================================
# #
# # PROBLEM:
# #   After recent changes, ShareTransformer was generating function calls with
# #   too many arguments. For example:
# #   
# #   WRONG (too many args):
# #   HPC3(T13_0, T13_1, T13_2, T6_0, T6_1, T6_2, &M1_0, &M1_1, &M1_2, 
# #        rand_1, rand_2, rand_3, rand_4, rand_5, rand_6)
# #   
# #   CORRECT (7-8 args):
# #   HPC3(T13_0, T13_1, T6_0, T6_1, &M1_0, &M1_1, rand_01, rand_p01)
# #
# # ROOT CAUSE:
# #   1. Random variable generation was creating Decl nodes instead of ID nodes
# #   2. Decl nodes were being added directly to argument list
# #   3. This caused extra random variable IDs in function calls
# #
# # SOLUTION:
# #   Fixed random variable handling in transform_Assignment():
# #   
# #   BEFORE:
# #   ```python
# #   rand_args = [c_ast.ID(f"rand_{j+1}") for j in range(...)]
# #   self.injected_random_decls.update(rand_args)  # Adding IDs to set!
# #   ```
# #   
# #   AFTER:
# #   ```python
# #   rand_args = []
# #   for j in range(rand_count):
# #       rand_id = c_ast.ID(rand_name)
# #       rand_args.append(rand_id)
# #       # Create separate Decl for tracking
# #       rand_decl = c_ast.Decl(...)
# #       self.injected_random_decls.add(rand_decl)
# #   ```
# #
# # GADGET FUNCTION SIGNATURES (d=1, 2 shares):
# #   HPC2:  HPC2(a0, a1, b0, b1, &c0, &c1, r01)                    [7 args]
# #   HPC2o: HPC2o(a0, a1, b0, b1, w0, w1, &c0, &c1, r01)           [9 args]
# #   HPC3:  HPC3(a0, a1, b0, b1, &c0, &c1, r01, p01)               [8 args]
# #   HPC3o: HPC3o(a0, a1, b0, b1, w0, w1, &c0, &c1, r01, p01)      [10 args]
# #
# # VERIFICATION:
# #   Run the verification cell to check all function calls have correct arg counts
# #
# # ============================================================================
# # INTEGRATED HPC2/HPC2o SWAP LOGIC IN SHARETRANSFORMER
# # ============================================================================
# #
# # OVERVIEW:
# #   Instead of post-processing the generated C code with find_swaps.py,
# #   we now integrate the swap logic directly into ShareTransformer.
# #   This makes it generic for any order d and keeps the logic in one place.
# #
# # FLOW:
# #
# #   MLRC (mlrc.py)
# #   ├─ Computes arrival depths
# #   ├─ Identifies HPC3→HPC2 replacements
# #   ├─ Stores: input_reorder, slow_input, fast_input
# #   └─ Returns gadget_map with metadata
# #              │
# #              ▼
# #   ShareTransformer (ctransfromer.py) [NEW]
# #   ├─ Receives gadget_map + input_reordering metadata
# #   ├─ For each AND gate:
# #   │  ├─ Check if input_reorder == "swap_inputs"
# #   │  ├─ Compute local arrival depths (optional for verification)
# #   │  ├─ Swap input arguments if needed
# #   │  └─ Generate HPC2(b0,b1,a0,a1,...) or HPC2(a0,a1,b0,b1,...)
# #   └─ Returns: Correctly ordered function calls
# #              │
# #              ▼
# #   output.c [CORRECT]
# #   ├─ HPC2 calls with 7 arguments
# #   ├─ HPC2o calls with 9 arguments
# #   ├─ Inputs pre-swapped based on arrival depths
# #   └─ NO post-processing needed!
# #
# # KEY DATA STRUCTURES:
# #
# # 1. gadget_map (from MLRC):
# #    {
# #      "M32 = M27 & M31": {
# #        "gadget_name": "hpc2o",
# #        "func_name": "HPC2o",
# #        "random_numbers": 1,
# #        "input_reorder": "keep_order",   # NEW
# #        "slow_input": "A",                # NEW
# #        "fast_input": "B"                 # NEW
# #      },
# #      "M51 = M37 & T17": {
# #        "gadget_name": "hpc2",
# #        "func_name": "HPC2",
# #        "random_numbers": 1,
# #        "input_reorder": "swap_inputs",   # NEW
# #        "slow_input": "B",                # NEW
# #        "fast_input": "A"                 # NEW
# #      }
# #    }
# #
# # 2. ShareTransformer init:
# #    ShareTransformer(
# #      num_shares=2,
# #      gadget_expr_map=gadget_map,
# #      unique_gadget_def=unique_definitions,
# #      arrival_depths=swap_info  # NEW parameter
# #    )
# #
# # EXAMPLE TRANSFORMATION:
# #
# # Input (gadget_map):
# #   M32 = M27 & M31  →  hpc2o, input_reorder="keep_order"
# #   M51 = M37 & T17  →  hpc2, input_reorder="swap_inputs"
# #
# # Generated code (before):
# #   HPC2o(M27_0, M27_1, M31_0, M31_1, M37_0, M37_1, &M32_0, &M32_1, rand_1)
# #   HPC2(M37_0, M37_1, T17_0, T17_1, &M51_0, &M51_1, rand_2)
# #
# # Generated code (after swap integration):
# #   HPC2o(M27_0, M27_1, M31_0, M31_1, M37_0, M37_1, &M32_0, &M32_1, rand_1)
# #   HPC2(T17_0, T17_1, M37_0, M37_1, &M51_0, &M51_1, rand_2)  ← SWAPPED
# #                ▲                ▲
# #                └────────┬────────┘
# #                    Arguments swapped!
# #
# # BENEFITS:
# #   ✅ Integrated: No external post-processing needed
# #   ✅ Generic: Works for any order d and any gadget mapping
# #   ✅ Correct: Swaps done at AST level, not text parsing
# #   ✅ Traceable: Can add debugging directly in transform_Assignment
# #   ✅ Single flow: All optimization in MLRC → all swaps in ShareTransformer
# #
# # METHODS ADDED TO SHARETRANSFORMER:
# #
# #   _get_arrival_depth(var_name)
# #     → Get arrival depth of a variable from tracking dict
# #
# #   _update_arrival_depths(node_expr, output_name, depth_a, depth_b)
# #     → Update depth tracking after AND operation
# #     → output_depth = max(depth_a, depth_b) + 1
# #
# #   _should_swap_inputs(gadget_name, depth_a, depth_b)
# #     → Check if inputs should be swapped for HPC2/HPC2o
# #     → Only swap if: |depth_a - depth_b| >= 1
# #     → Return: (should_swap, action) where action is "swap" or "keep"
# #
# # ============================================================================




from pycparser import c_ast, c_generator, c_parser
from copy import deepcopy
import re

class ShareTransformer:
    def __init__(self, num_shares, gadget_expr_map, unique_gadget_def):
        self.num_shares = num_shares
        self.gadget_expr_map = gadget_expr_map
        self.unique_gadget_def = unique_gadget_def
        self.generator = c_generator.CGenerator()
        self.injected_random_decls = set()
        self.rand_counter = 0
        self.comar_rand_added = False
        self.optimized_outputs = set()   # AND outputs consumed by deferred hpc*o gadgets
        self.deferred_gadgets  = {}      # and_var_name → (and_node, gadget_dict)

        # Pre-scan: for each xor_and gadget, the XOR consumer variable (e.g. m18) is
        # eliminated because the gadget writes directly into the AND output variable (m7).
        # m7 ends up holding the combined AND+XOR result, so every reference to m18
        # must be redirected to m7.
        #
        #   var_substitution : { "m18" → "m7" }   (rename m18 → m7 everywhere)
        #   suppressed_vars  : { "m18" }           (suppress m18's declaration)
        self.var_substitution = {}   # xor_consumer_lhs → and_lhs
        self.suppressed_vars  = set()
        for key, info in gadget_expr_map.items():
            gname = info.get("gadget_name", "").lower()
            if gname in ['hpc2o', 'hpc2o_swapped', 'hpc3o'] and info.get("xor_consumer"):
                key_str = str(key)
                if '=' in key_str:
                    and_lhs      = key_str.split('=')[0].strip()
                    xor_consumer = info["xor_consumer"]
                    self.var_substitution[xor_consumer] = and_lhs
                    self.suppressed_vars.add(xor_consumer)

        # DEBUG: Print gadget map info
        print("\n" + "="*80)
        print("SHARETRANSFORMER INITIALIZATION")
        print("="*80)
        print(f"[INIT] Total gadgets in map: {len(gadget_expr_map)}")
        
        # Count gadget types in map
        gadget_counts = {}
        for key, info in gadget_expr_map.items():
            gname = info.get("gadget_name", "unknown")
            gadget_counts[gname] = gadget_counts.get(gname, 0) + 1
        
        print(f"\n[INIT] Gadget breakdown in map:")
        for gname in sorted(gadget_counts.keys()):
            count = gadget_counts[gname]
            print(f"  {gname:8s}: {count:3d} gates")
        print("="*80 + "\n")

    def transform(self, node):
        method = f"transform_{type(node).__name__}"
        return getattr(self, method)(node)

    def transform_FileAST(self, node):
        """Only transform the main circuit — gadgets are inserted as raw text later."""
        top_level_func = None
        for item in node.ext:
            if isinstance(item, c_ast.FuncDef):
                top_level_func = item
                break
        assert top_level_func is not None, "Could not find any function definition in the file"

        transformed_top_level = self.transform(top_level_func)
        node.ext = [transformed_top_level]
        
        print("\n" + "="*80)
        print("SHARETRANSFORMER TRANSFORMATION COMPLETE")
        print("="*80)
        return node

    def transform_FuncDef(self, node):
        node.body = self.transform(node.body)

        if not node.decl.type.args:
            node.decl.type.args = c_ast.ParamList(params=[])

        original_params = node.decl.type.args.params
        new_params = []

        for param in original_params:
            if param.name.startswith("dec_"):
                new_params.append(param)
            else:
                for i in range(self.num_shares):
                    new_param = deepcopy(param)
                    new_param.name = f"{param.name}_{i}"
                    typ = new_param.type
                    if isinstance(typ, c_ast.TypeDecl):
                        typ.declname = new_param.name
                    elif isinstance(typ, c_ast.PtrDecl) and isinstance(typ.type, c_ast.TypeDecl):
                        typ.type.declname = new_param.name
                    new_params.append(new_param)

        for rand_id in self.injected_random_decls:
            param_decl = c_ast.Decl(
                name=rand_id.name, quals=[], storage=[], funcspec=[], align=None,
                type=c_ast.TypeDecl(
                    declname=rand_id.name, quals=[], align=None,
                    type=c_ast.IdentifierType(['int'])
                ),
                init=None, bitsize=None
            )
            new_params.append(param_decl)

        node.decl.type.args.params = new_params
        return node

    def transform_Compound(self, node):
        new_items = []
        new_items.extend(self.injected_random_decls)
        self.injected_random_decls.clear()

        for stmt in node.block_items or []:
            result = self.transform(stmt)
            if isinstance(result, list):
                new_items.extend(result)
            elif result:
                new_items.append(result)

        return c_ast.Compound(block_items=new_items)

    def transform_Decl(self, node):
        if node.name.startswith("dec_"):
            return node

        # Suppress declarations for XOR consumer variables (e.g. m18) that have been
        # absorbed into an hpc*o gadget. Their value is now carried by the AND output
        # variable (e.g. m7), so m18 no longer exists in the transformed code.
        if node.name in self.suppressed_vars:
            return []

        decls = []
        for i in range(self.num_shares):
            new_decl = deepcopy(node)
            new_decl.name = f"{node.name}_{i}"

            if isinstance(new_decl.type, c_ast.TypeDecl):
                new_decl.type.declname = new_decl.name

            if new_decl.init:
                new_decl.init = self.rename_ids(new_decl.init, i)

            decls.append(new_decl)
        return decls

    def transform_Assignment(self, node):
        # 1. Special NOT case (XOR with dec_1)
        if isinstance(node.rvalue, c_ast.BinaryOp) and node.rvalue.op == '^':
            left_dec = isinstance(node.rvalue.left, c_ast.ID) and node.rvalue.left.name == "dec_1"
            right_dec = isinstance(node.rvalue.right, c_ast.ID) and node.rvalue.right.name == "dec_1"
            if left_dec or right_dec:
                operand = node.rvalue.right if left_dec else node.rvalue.left
                not_expr = c_ast.UnaryOp(op='!', expr=operand)
                results = []
                for i in range(self.num_shares):
                    new_assign = deepcopy(node)
                    if isinstance(new_assign.lvalue, c_ast.ID):
                        new_assign.lvalue.name = f"{new_assign.lvalue.name}_{i}"
                    elif isinstance(new_assign.lvalue, c_ast.UnaryOp) and new_assign.lvalue.op == '*':
                        inner = new_assign.lvalue.expr
                        if isinstance(inner, c_ast.ID):
                            inner.name = f"{inner.name}_{i}"
                    new_assign.rvalue = self.rename_ids(deepcopy(not_expr), i)
                    results.append(new_assign)
                return results
            
        if isinstance(node.rvalue, c_ast.UnaryOp) and node.rvalue.op == '!':
            results = []
            for i in range(self.num_shares):
                new_assign = deepcopy(node)
                # Rename LHS: y -> y_i
                if isinstance(new_assign.lvalue, c_ast.ID):
                    new_assign.lvalue.name = f"{new_assign.lvalue.name}_{i}"
                
                # If it's the last share, keep the '!' operator
                if i == self.num_shares - 1:
                    new_assign.rvalue = self.rename_ids(deepcopy(node.rvalue), i)
                else:
                    # Otherwise, strip the '!' and just rename the inner variable: !x -> x_i
                    new_assign.rvalue = self.rename_ids(deepcopy(node.rvalue.expr), i)
                
                results.append(new_assign)
            return results
        # 2. Generate lookup key
        original_key = self.generator.visit(node).strip()
        gadget = None
        
        # Lookups
        gadget = self.gadget_expr_map.get(original_key)
        if not gadget:
            key = re.sub(r'\s+|\(|\)', '', original_key)
            key = re.sub(r'_\d+', '', key)
            gadget = self.gadget_expr_map.get(key)
        if not gadget:
            lhs = original_key.split('=')[0].strip()
            gadget = self.gadget_expr_map.get(lhs)
        if not gadget:
            for map_key, map_val in self.gadget_expr_map.items():
                if '=' in str(map_key) and '=' in original_key:
                    if str(map_key).split('=')[0].strip() == original_key.split('=')[0].strip():
                        gadget = map_val
                        break

        if gadget:
            gadget_name       = gadget["gadget_name"].lower()
            func_name         = gadget["func_name"]
            rand_count        = gadget.get("random_numbers", 0)
            xor_consumer      = gadget.get("xor_consumer")
            xor_other_operand = gadget.get("xor_other_operand")

            # Arguments are passed in natural order: left operand first, right operand second.
            # The gadget name itself encodes which port is fast/slow, so no argument
            # swapping is needed here.  hpc2_swapped / hpc2o_swapped were chosen by
            # optimize_gadget_mapping_for_cost_asymmetric() based on arrival depths.
            a_all = [self.rename_ids(deepcopy(node.rvalue.left),  i) for i in range(self.num_shares)]
            b_all = [self.rename_ids(deepcopy(node.rvalue.right), i) for i in range(self.num_shares)]

            # === HPC2o-family (xor_and gadgets) — DEFERRED emission ===
            # These gadgets compute  out = a AND b XOR w  securely.
            # Problem: the 'w' operand (the other XOR input) is often defined AFTER
            # the AND gate in the sequential C code, making it unavailable here.
            # Solution: defer the gadget call to the position of the consuming XOR
            # assignment, where all three inputs (a, b, w) are guaranteed to exist.
            if gadget_name in ['hpc2o', 'hpc2o_swapped', 'hpc3o']:
                if isinstance(node.lvalue, c_ast.ID) and xor_consumer:
                    and_var = node.lvalue.name
                    # Store AND node + gadget info; emit at the XOR assignment position.
                    self.deferred_gadgets[and_var] = (deepcopy(node), gadget)
                    self.optimized_outputs.add(and_var)
                    return []   # nothing emitted here; gadget fires at the XOR site

                # Fallback (xor_consumer missing): emit immediately with b as w
                w_all = b_all[:]
                rand_args = [c_ast.ID(f"rand_{j+1}") for j in range(self.rand_counter, self.rand_counter + rand_count)]
                for r_arg in rand_args:
                    self.injected_random_decls.add(c_ast.Decl(
                        name=r_arg.name, quals=[], storage=[], funcspec=[], align=None,
                        type=c_ast.TypeDecl(declname=r_arg.name, quals=[], align=None,
                                            type=c_ast.IdentifierType(['int'])),
                        init=None, bitsize=None,
                    ))
                self.rand_counter += rand_count
                if isinstance(node.lvalue, c_ast.ID):
                    out_all = [c_ast.UnaryOp(op='&', expr=c_ast.ID(f"{node.lvalue.name}_{i}"))
                               for i in range(self.num_shares)]
                    args = a_all + b_all + w_all + out_all + rand_args
                else:
                    args = a_all + b_all + w_all + rand_args
                return [c_ast.FuncCall(name=c_ast.ID(func_name), args=c_ast.ExprList(args))]

            # === Normal gadgets (HPC3, HPC2, HPC2_swapped, …) ===
            rand_args = []
            for j in range(rand_count):
                rand_name = f"rand_{self.rand_counter + j + 1}"
                rand_id   = c_ast.ID(rand_name)
                rand_args.append(rand_id)
                rand_decl = c_ast.Decl(
                    name=rand_name, quals=[], storage=[], funcspec=[], align=None,
                    type=c_ast.TypeDecl(declname=rand_name, quals=[], align=None,
                                        type=c_ast.IdentifierType(['int'])),
                    init=None, bitsize=None,
                )
                self.injected_random_decls.add(rand_decl)
            self.rand_counter += rand_count

            if isinstance(node.lvalue, c_ast.ID):
                out_all = [c_ast.UnaryOp(op='&', expr=c_ast.ID(f"{node.lvalue.name}_{i}"))
                           for i in range(self.num_shares)]
                args = a_all + b_all + out_all + rand_args
            else:
                args = a_all + b_all + rand_args

            return [c_ast.FuncCall(name=c_ast.ID(func_name), args=c_ast.ExprList(args))]

        # === Deferred hpc*o gadget emission ===
        # When we reach a XOR "xor_out = a ^ b" and one of the operands is a deferred
        # AND output, we now have all inputs available: emit the gadget here.
        # The gadget computes  xor_out = AND(a_ops) XOR other_operand  securely.
        if isinstance(node.rvalue, c_ast.BinaryOp) and node.rvalue.op == '^':
            left_name  = getattr(node.rvalue.left,  'name', None)
            right_name = getattr(node.rvalue.right, 'name', None)

            and_var        = None
            xor_other_node = None
            if left_name in self.deferred_gadgets:
                and_var        = left_name
                xor_other_node = node.rvalue.right
            elif right_name in self.deferred_gadgets:
                and_var        = right_name
                xor_other_node = node.rvalue.left

            if and_var is not None:
                and_node, dgadget = self.deferred_gadgets.pop(and_var)
                dfunc_name  = dgadget["func_name"]
                drand_count = dgadget.get("random_numbers", 0)

                da_all = [self.rename_ids(deepcopy(and_node.rvalue.left),  i) for i in range(self.num_shares)]
                db_all = [self.rename_ids(deepcopy(and_node.rvalue.right), i) for i in range(self.num_shares)]

                if isinstance(xor_other_node, c_ast.ID):
                    dw_all = [c_ast.ID(f"{xor_other_node.name}_{i}") for i in range(self.num_shares)]
                else:
                    dw_all = [self.rename_ids(deepcopy(xor_other_node), i) for i in range(self.num_shares)]

                drand_args = [c_ast.ID(f"rand_{j+1}") for j in range(self.rand_counter, self.rand_counter + drand_count)]
                for r_arg in drand_args:
                    self.injected_random_decls.add(c_ast.Decl(
                        name=r_arg.name, quals=[], storage=[], funcspec=[], align=None,
                        type=c_ast.TypeDecl(declname=r_arg.name, quals=[], align=None,
                                            type=c_ast.IdentifierType(['int'])),
                        init=None, bitsize=None,
                    ))
                self.rand_counter += drand_count

                # Output to the AND variable (e.g. m7), not the XOR consumer (e.g. m18).
                # m7 now holds the combined AND+XOR result; all m18 references have
                # already been redirected to m7 via var_substitution / rename_ids.
                and_var_name = and_node.lvalue.name   # "m7"
                dout_all = [c_ast.UnaryOp(op='&', expr=c_ast.ID(f"{and_var_name}_{i}"))
                            for i in range(self.num_shares)]
                dargs = da_all + db_all + dw_all + dout_all + drand_args

                return [c_ast.FuncCall(name=c_ast.ID(dfunc_name), args=c_ast.ExprList(dargs))]

        # Normal assignments
        results = []
        for i in range(self.num_shares):
            new_assign = deepcopy(node)
            if isinstance(new_assign.lvalue, c_ast.ID):
                new_assign.lvalue.name = f"{new_assign.lvalue.name}_{i}"
            elif isinstance(new_assign.lvalue, c_ast.UnaryOp) and new_assign.lvalue.op == '*':
                inner = new_assign.lvalue.expr
                if isinstance(inner, c_ast.ID):
                    inner.name = f"{inner.name}_{i}"
            new_assign.rvalue = self.rename_ids(new_assign.rvalue, i)
            results.append(new_assign)
        return results

    def rename_ids(self, node, i):
        if node is None:
            return None
        if isinstance(node, c_ast.UnaryOp) and node.op in ['!', '~']:
            processed_child = self.rename_ids(deepcopy(node.expr), i)
            if i == self.num_shares - 1:
                return c_ast.UnaryOp(op=node.op, expr=processed_child)
            else:
                return processed_child
        elif isinstance(node, c_ast.ID):
            if node.name.startswith("dec_"):
                return node
            # Apply xor_and substitution: m18 → m7 (m7 now holds the combined result)
            actual_name = self.var_substitution.get(node.name, node.name)
            node.name = f"{actual_name}_{i}"
            return node
        else:
            for attr_name, child in node.children():
                if isinstance(child, c_ast.Node):
                    setattr(node, attr_name, self.rename_ids(child, i))
                elif isinstance(child, list):
                    new_list = [self.rename_ids(elem, i) if isinstance(elem, c_ast.Node) else elem for elem in child]
                    setattr(node, attr_name, new_list)
            return node