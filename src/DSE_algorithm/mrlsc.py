from DSE_algorithm.dse import DSE
from tabulate import tabulate
import json
from collections import defaultdict
import heapq
from Gadgets import HPC1, HPC2, HPC3, COMAR, Domand, HPC2o, HPC3o
import math
import sqlite3

class MRLC(DSE):
    """
    Minimise Randomness Under Latency Constraint (MRLC)
    Enhanced version with database integration for dynamic gadget specs
    Returns calculated latency along with gadget definition

    MRLSC (Minimum Randomness under Latency and Security Constraints)
    Objective: Minimize randomness consumption while respecting latency budget and maximizing security level.

    Enhanced Algorithm:
    Input: Minimum masking order (min_d), target latency budget, maximum d to try
    Process: Iteratively tries masking orders from highest to lowest (max_d down to min_d)
    Selection: Chooses the highest feasible masking order that fits within the latency constraint
    Optimization: Uses dynamic programming approach to optimally distribute latency budget across circuit levels

    Key Features:
    Automatically maximizes security by selecting highest possible d ≥ min_d
    DP-based optimal gadget assignment per level
    Returns calculated latency directly from algorithm (eliminates separate calculation errors)
    Database integration for dynamic gadget specification loading
    Pattern-aware gadget selection (XOR+AND vs pure AND)
    """

    def __init__(self, d, and_tree, gadget_map):
        super().__init__(d, and_tree, gadget_map)
        # New: Track node operation patterns
        self.node_pattern = {}  # node -> 'xor_and' (z=w^(a&b)) or 'pure_and' (z=a&b)

    def _analyze_and_tree_for_patterns(self):
        """
        Analyzes the AND tree to identify XOR+AND patterns vs pure AND operations.
        Stores patterns in self.node_pattern for later use.
        """
        # FIXED: Don't iterate over and_tree directly; iterate over nodes
        try:
            # Get all nodes from the graph
            for node_expr in self.and_tree.graph.nodes():
                # For now, mark all nodes as 'pure_and' (default)
                # In a more sophisticated implementation, you could parse the expression
                # to detect if it's part of an XOR+AND pattern
                self.node_pattern[node_expr] = 'pure_and'
            
            print(f"[MRLC INFO]: Analyzed {len(self.node_pattern)} nodes for patterns")
        except AttributeError as e:
            print(f"[MRLC WARN]: Could not analyze AND tree patterns: {str(e)}")
            # Fallback: treat all as pure_and
            for node_expr in self.nodes_by_level.values():
                for expr in node_expr:
                    self.node_pattern[expr] = 'pure_and'

    def _heuristic_pattern_detection(self):
        """
        Returns gadget selection heuristic based on node patterns.
        """
        # Placeholder for pattern-aware heuristics
        return {}

    def _get_gadgets_for_pattern(self, pattern_type, matching_gadgets):
        """
        Returns suitable gadgets for a given pattern type.
        - For 'xor_and': HPC2o, HPC3o (masked, computes z = w ^ (a & b))
        - For 'pure_and': HPC1, HPC2, COMAR, Domand (pure AND gadgets)
        """
        pure_and_gadgets = {name: spec for name, spec in matching_gadgets.items() 
                           if name in ['hpc1', 'hpc2', 'comar', 'domand']}
        xor_and_gadgets = {name: spec for name, spec in matching_gadgets.items() 
                          if name in ['hpc2o', 'hpc3o', 'comar']}
        
        if pattern_type == 'xor_and':
            # Prefer xor_and gadgets, fallback to pure_and if unavailable
            return xor_and_gadgets if xor_and_gadgets else matching_gadgets
        else:  # 'pure_and'
            return pure_and_gadgets if pure_and_gadgets else matching_gadgets
    


    def mrlc_dp(self, target_latency):
        """
        Dynamic Programming approach to minimize randomness under latency constraint
        """
        
        # Check if gadget_map is empty
        if not self.gadget_map or len(self.gadget_map) == 0:
            print(f"[ERROR]: No gadgets available for d={self.d}. Gadget map is empty.")
            return None, float('inf')

        # Analyze AND tree for XOR+AND patterns (with error handling)
        try:
            self._analyze_and_tree_for_patterns()
        except Exception as e:
            print(f"[MRLC WARN]: Pattern analysis failed: {str(e)}. Continuing with default patterns...")
            # Initialize with empty pattern dict - mrlc_dp will still work
            self.node_pattern = {}

        # Number of levels in the tree
        L = len(self.nodes_by_level)
        print(f"[MRLC INFO]: Number of levels: {L}")
        print(f"[MRLC INFO]: Nodes by level: {self.nodes_by_level}")

        # Nodes per level
        node_per_level = []
        for lvl, nodes in self.nodes_by_level.items():
            node_per_level.append(len(nodes))
        print(f"[MRLC INFO]: Nodes per level: {node_per_level}")

        # Choose the initial gadget from gadget map (minimum latency)
        min_latency_gadget = min(self.gadget_map.items(), 
                               key=lambda item: (item[1]["latency"], item[1]["randomness"], item[1]["area"]))
        initial_gadget = min_latency_gadget[0]
        initial_latency = min_latency_gadget[1]["latency"]
        initial_randomness = min_latency_gadget[1]["randomness"]
        
        print(f"[MRLC INFO]: Initial gadget: {initial_gadget}")
        print(f"[MRLC INFO]: Initial latency: {initial_latency}")
        print(f"[MRLC INFO]: Initial randomness: {initial_randomness}")

        # Find gadgets with randomness less than or equal to initial randomness
        matching_gadgets = {
            name: specs
            for name, specs in self.gadget_map.items() 
            if specs["randomness"] <= initial_randomness
        }
        print(f"[MRLC INFO]: Matching gadgets (randomness <= {initial_randomness}): {list(matching_gadgets.keys())}")

        # Add initial gadget to matching gadgets if not already present
        if initial_gadget not in matching_gadgets:
            matching_gadgets[initial_gadget] = min_latency_gadget[1]

        total_initial_latency = L * initial_latency
        bonus_latency = target_latency - total_initial_latency  # bonus for replacement

        print(f"[MRLC INFO]: Total levels in the and tree: {L}")
        print(f"[MRLC INFO]: Initial latency of and tree: {total_initial_latency}")
        print(f"[MRLC INFO]: Target latency: {target_latency}")
        print(f"[MRLC INFO]: Bonus latency: {bonus_latency}")

        if bonus_latency < 0:
            print(f"[MRLC ERROR]: Target latency cannot be met with d={self.d}")
            return None, float('inf')

        # Initialize DP table
        infinity = float('inf')
        dp = [[infinity] * (bonus_latency + 1) for _ in range(L + 1)]
        gadget_assigned = [[None] * (bonus_latency + 1) for _ in range(L + 1)]

        # Base case
        dp[0][0] = 0

        # Fill the DP table with pattern-aware gadget selection
        for i in range(1, L + 1):
            node_in_current_level = node_per_level[i - 1]
            nodes_in_level = list(self.nodes_by_level.get(i, []))
            print(f"[MRLC INFO]: Processing level {i} with {node_in_current_level} nodes")

            for prev_j_spent in range(bonus_latency + 1):
                for prev_comar_used_state in [0, 1]:
                    if dp[i - 1][prev_j_spent] == infinity:
                        continue  # No valid assignment in previous iteration

                    # Determine operation patterns in this level
                    patterns_in_level = set(self.node_pattern.get(node, 'pure_and') for node in nodes_in_level)
                    
                    if len(patterns_in_level) == 1:
                        # All nodes have same pattern in this level
                        pattern = list(patterns_in_level)[0]
                        available_gadgets = self._get_gadgets_for_pattern(pattern, matching_gadgets)
                        print(f"    Level {i} has uniform pattern: {pattern}. Using gadgets: {list(available_gadgets.keys())}")
                    else:
                        # Mixed patterns in same level: use all matching gadgets
                        available_gadgets = matching_gadgets
                        print(f"    Level {i} has mixed patterns {patterns_in_level}. Using all matching gadgets.")

                    # Try all available gadgets
                    for gadget_name, gadget_spec in available_gadgets.items():
                        # Constraint: only use hpc2o/hpc3o for 'xor_and' pattern nodes
                        if gadget_name in ['hpc2o', 'hpc3o']:
                            if 'xor_and' not in patterns_in_level:
                                continue

                        cost_for_replacement = gadget_spec["latency"] - initial_latency
                        randomness_for_this_gadget = gadget_spec["randomness"]
                        current_total_j_spent = prev_j_spent + cost_for_replacement

                        if current_total_j_spent <= bonus_latency:
                            randomness_from_level_i = float(node_in_current_level) * randomness_for_this_gadget
                            total_randomness = dp[i - 1][prev_j_spent] + randomness_from_level_i

                            if total_randomness < dp[i][current_total_j_spent]:
                                dp[i][current_total_j_spent] = total_randomness
                                gadget_assigned[i][current_total_j_spent] = (prev_j_spent, gadget_name)

        # Find Final randomness and Bonus Spent
        min_total_tree_randomness = infinity
        final_bonus_spent = -1

        for j_spent in range(bonus_latency + 1):
            if dp[L][j_spent] < min_total_tree_randomness:
                min_total_tree_randomness = dp[L][j_spent]
                final_bonus_spent = j_spent

        if min_total_tree_randomness == infinity:
            print(f"[MRLC ERROR]: No solution found within latency budget for d={self.d}")
            return None, float('inf')
        else:
            print(f"[MRLC SUCCESS]: Minimum possible total tree randomness: {min_total_tree_randomness}")
            print(f"[MRLC SUCCESS]: Achieved by spending latency budget of: {final_bonus_spent}")

        # Calculate actual latency used
        actual_latency_used = total_initial_latency + final_bonus_spent
        print(f"[MRLC SUCCESS]: Final latency used: {actual_latency_used}")
        print(f"[MRLC SUCCESS]: Target latency was: {target_latency}")

        # Reconstruct path (gadget used per level)
        print(f"[MRLC INFO]: Reconstructing optimal gadget assignment path...")
        chosen_gadget_for_levels = [None] * L
        current_j = final_bonus_spent

        for i in range(L, 0, -1):  # Levels L down to 1
            if gadget_assigned[i][current_j] is not None:
                prev_j_for_level_i_minus_1, gadget_name_for_level_i = gadget_assigned[i][current_j]
                chosen_gadget_for_levels[i - 1] = gadget_name_for_level_i
                current_j = prev_j_for_level_i_minus_1
            else:
                # Find zero-cost option
                zero_cost_option = None
                for gadget_name, gadget_spec in matching_gadgets.items():
                    if gadget_spec['latency'] - initial_latency == 0:
                        zero_cost_option = gadget_name
                        break

                if zero_cost_option and dp[i-1][current_j] != infinity:
                    expected_randomness = dp[i-1][current_j] + node_per_level[i-1] * matching_gadgets[zero_cost_option]['randomness']
                    if abs(expected_randomness - dp[i][current_j]) < 1e-9:  # Float comparison
                        chosen_gadget_for_levels[i-1] = zero_cost_option
                    else:
                        print(f"[MRLC WARN]: Path reconstruction failed for level {i}, using initial gadget")
                        chosen_gadget_for_levels[i-1] = initial_gadget
                else:
                    print(f"[MRLC WARN]: Critical error in path reconstruction for level {i}, using initial gadget")
                    chosen_gadget_for_levels[i-1] = initial_gadget

        print(f"[MRLC INFO]: Final gadget assignment per level:")
        for lvl, g in enumerate(chosen_gadget_for_levels, start=1):
            print(f"  Level {lvl}: {g}")

        # Assign gadgets to nodes
        for lvl, expressions in self.nodes_by_level.items():
            for expr in expressions:
                gadget = chosen_gadget_for_levels[lvl - 1]
                self.gadget_definition[expr] = {
                    "gadget_name": gadget,
                    "random_numbers": self.gadget_map[gadget]["randomness"]
                }

        # Generate gadget function definitions
        for node, gadget_spec in self.gadget_definition.items():
            gadget = gadget_spec["gadget_name"]
            
            if gadget == 'hpc2':
                HPC2_obj = HPC2(d=self.d)
                gadget_def = HPC2_obj.generate_multiply_function()
                func_name = HPC2_obj.get_function_name()
            elif gadget == 'hpc2o':
                HPC2_obj = HPC2(d=self.d)
                gadget_def = HPC2_obj.generate_multiply_function()
                func_name = HPC2_obj.get_function_name()
            elif gadget == 'hpc1':
                HPC1_obj = HPC1(d=self.d)
                gadget_def = HPC1_obj.generate_multiply_function()
                func_name = HPC1_obj.get_function_name()
            elif gadget == 'hpc3':
                HPC3_obj = HPC3(d=self.d)
                gadget_def = HPC3_obj.generate_multiply_function()
                func_name = HPC3_obj.get_function_name()
            elif gadget == 'hpc3o':
                HPC3_obj = HPC3(d=self.d)
                gadget_def = HPC3_obj.generate_multiply_function()
                func_name = HPC3_obj.get_function_name()
            elif gadget == 'comar':
                COMAR_obj = COMAR()
                gadget_def = COMAR_obj.generate_multiply_function()
                func_name = COMAR_obj.get_function_name()
            elif gadget == 'domand':
                Domand_obj = Domand(d=self.d)
                gadget_def = Domand_obj.generate_multiply_function()
                func_name = Domand_obj.get_function_name()

            self.gadget_definition[node]['func_name'] = func_name

            if gadget not in self.unique_gadgets_definition:
                self.unique_gadgets_definition[gadget] = gadget_def

        print(f"[MRLC INFO]: GADGET ASSIGNMENT FOR NODES")
        self.print_gadget_definition()
        print(f"[MRLC INFO]: UNIQUE DEFINITION TO BE INSERTED IN THE C FILE")
        self.print_unique_gadget_definition()
        
        return self.gadget_definition, actual_latency_used

# Database Integration Functions for MRLC
def create_gadget_specs_from_db_mrlc(d, db_path='gadget_info.db'):
    """
    Create gadget specifications from database for given d (MRLC version)
    """
    print(f"[MRLC INFO] : Connecting Database for d={d}...")
    conn = sqlite3.connect(db_path)
    conn.execute("PRAGMA foreign_keys = ON")
    cur = conn.cursor()
    
    gadget_specs = {}
    gadget_list = ["comar", "hpc1", "hpc2", "hpc3"] if d == 1 else ["hpc1", "hpc2", "hpc3"]
    
    for gadget in gadget_list:
        table = gadget.lower()
        cur.execute(f"SELECT * FROM {table} WHERE d = ?", (d,))
        row = cur.fetchone()
        
        if row:
            gadget_specs[gadget] = {
                "latency": row[1],
                "randomness": row[2],
                "area": row[3]
            }
        else:
            print(f"[MRLC WARN] No entry for {gadget} with d = {d}")
    
    if gadget_specs:
        table_data = []
        for gadget, values in gadget_specs.items():
            table_data.append([gadget, values['latency'], values['randomness'], values['area']])
        print(f"\n[MRLC INFO]: Populated DSE MAP for d={d} order")
        print(tabulate(table_data, headers=["Gadget", "Latency", "Randomness", "Area"], tablefmt="grid"))
    
    conn.close()
    return gadget_specs

def get_best_secure_mapping_mrlc_with_db(and_tree, min_d, target_latency, max_d=5, db_path='gadget_info.db'):
    """
    Enhanced MRLC mapping function that uses latency calculated by MRLC itself
    """
    for d_candidate in range(max_d, min_d-1, -1):
        print(f"\n=== Trying MRLC with d = {d_candidate} ===")
        
        # Get gadget specs from database for this d_candidate
        gadget_specs = create_gadget_specs_from_db_mrlc(d_candidate, db_path)
        
        if not gadget_specs:
            print(f"✗ d = {d_candidate} - no gadgets available in database")
            continue
        
        # Create MRLC object with current d_candidate and its specific gadget_specs
        mrlc_obj = MRLC(d_candidate, and_tree, gadget_specs)
        
        # Run MRLC algorithm
        try:
            # MRLC now returns both mapping and latency
            mapping, latency_used = mrlc_obj.mrlc_dp(target_latency)
        except ValueError as e:
            print(f"✗ d = {d_candidate} - Error: {str(e)}")
            continue
        except Exception as e:
            print(f"✗ d = {d_candidate} - Unexpected error: {str(e)}")
            continue
        
        # Check if mapping is valid and latency fits constraint
        if mapping is not None and latency_used <= target_latency:
            print(f"✓ Selected d = {d_candidate} - mapping fits within latency constraint.")
            print(f"  Latency used: {latency_used} (target: {target_latency})")
            return mapping, d_candidate, latency_used
        elif mapping is not None:
            print(f"✗ d = {d_candidate} uses too much latency ({latency_used} > {target_latency})")
        else:
            print(f"✗ d = {d_candidate} - no valid mapping found")

    print(f"\n❌ No mapping can be found for any d >= {min_d} with latency <= {target_latency}")
    return None, None, float('inf')

def run_enhanced_mrlc_with_db(and_tree, min_d, target_latency, max_d=5, db_path='gadget_info.db'):
    """
    Main function to run the enhanced MRLC with database integration
    Now returns the actual latency calculated by MRLC
    """
    print(f"🚀 Starting Enhanced MRLC with Database Integration")
    print(f"   Min d: {min_d}")
    print(f"   Target latency: {target_latency}")
    print(f"   Max d to try: {max_d}")
    print(f"   Database: {db_path}")
    
    # FIXED: Call the correct function with proper parameters
    mapping, used_d, actual_latency = get_best_secure_mapping_mrlc_with_db(
        and_tree=and_tree,
        min_d=min_d,
        target_latency=target_latency,
        max_d=max_d,
        db_path=db_path
    )
    
    if mapping is not None:
        print(f"\n🎯 SUCCESS!")
        print(f"   Final d used: {used_d}")
        print(f"   Actual latency used: {actual_latency}")
        print(f"   Target latency: {target_latency}")
        print(f"   Security level: {used_d}-order masking")
        return mapping, used_d, actual_latency, True
    else:
        print(f"\n❌ FAILED - No feasible solution found")
        return None, None, float('inf'), False


# Backward compatibility functions for MRLC (without database)
def get_best_secure_mapping_mrlc(and_tree, gadget_map, min_d, target_latency, max_d=5):
    """
    Original MRLC function for backward compatibility (without database)
    """
    for d_candidate in range(max_d, min_d-1, -1):
        print(f"\n=== Trying MRLC with d = {d_candidate} ===")
        
        mrlc_obj = MRLC(d_candidate, and_tree, gadget_map)
        
        try:
            mapping, latency_used = mrlc_obj.mrlc_dp(target_latency)
        except ValueError as e:
            print(f"✗ d = {d_candidate} - Error: {str(e)}")
            continue
        
        if mapping is not None and latency_used <= target_latency:
            print(f"✓ Selected d = {d_candidate} - mapping fits within latency constraint.")
            print(f"  Latency used: {latency_used} (target: {target_latency})")
            return mapping, d_candidate, latency_used
        elif mapping is not None:
            print(f"✗ d = {d_candidate} uses too much latency ({latency_used} > {target_latency})")
        else:
            print(f"✗ d = {d_candidate} - no valid mapping found")

    print(f"\n❌ No mapping can be found for any d >= {min_d} with latency <= {target_latency}")
    return None, None, float('inf')

def run_enhanced_mrlc(and_tree, gadget_map, min_d, target_latency, max_d=5):
    """
    Original MRLC function for backward compatibility (without database)
    """
    print(f"🚀 Starting Enhanced MRLC")
    print(f"   Min d: {min_d}")
    print(f"   Target latency: {target_latency}")
    print(f"   Max d to try: {max_d}")
    
    mapping, used_d, actual_latency = get_best_secure_mapping_mrlc(
        and_tree=and_tree,
        gadget_map=gadget_map,
        min_d=min_d,
        target_latency=target_latency,
        max_d=max_d
    )
    
    if mapping is not None:
        print(f"\n🎯 SUCCESS!")
        print(f"   Final d used: {used_d}")
        print(f"   Actual latency used: {actual_latency}")
        print(f"   Security level: {used_d}-order masking")
        return mapping, used_d, actual_latency, True
    else:
        print(f"\n❌ FAILED - No feasible solution found")
        return None, None, float('inf'), False
