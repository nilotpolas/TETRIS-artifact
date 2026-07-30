from DSE_algorithm.dse import DSE
from tabulate import tabulate # type: ignore
import json
from collections import defaultdict
import heapq
from Gadgets import HPC1, HPC2, HPC3, COMAR, Domand, HPC2o, HPC3o
import math

class MRLC(DSE):
    
    def __init__(self, d, and_tree, gadget_map):
        super().__init__(d, and_tree, gadget_map)
        self.node_pattern = {}
        self.debug = False
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

    def mrlc_dp(self, target_latency):

        """
        Goal : make total randomness as low as possible.

            - we can update a lvl by any gadget  


            --------------------------------
            gadget | randomness | latency   |
            ---------------------------------
            g1     |    r1      |   l1      |
            g2     |    r2      |   l2      |
            g3     |    r3      |   l3      |
            g4     |    r4      |   l4      |

            - We only have certain amount of latency to spend from.
            - bonus = total latency - initial_latency

            Greedy won't work (choosing gadget with least randomness for each level)

            What if the lowest ranomdomess gadget is very expensive in terms of latency, 
            then we might spend all our bonus on the few levels
            and have no bonus left for later lvls what if a slightly less effective but 
            cheaper gadget(in terms of latency), would have been better.

            using dp:

            "Let's figure out the best way for the first level with differnt amount of latency spent. 
            Then, using that knowledge, we figure out the best way for the first two levels with 
            different amounts of latency spent, and so on."

            kya memoize karna h
            - level - ith level.
            - how much money we spent up to i-1 level. j bonous spent

            dp table dp[i][j] = minimium randomness possible from lvl 1 to L, if we spend j bonous.
            i - > 0 to L
            j -> 0 to B

            base case :

            No Level 0:
                If we consider 0 levels and spend 0 latency, the total randomness is 0.
                dp[0][0] = 0
                If we consider 0 level but somehow spent bonus > 0, that is impossible. So, the randomness is "infinity" (meaning, "this situation can't happen).
                dp[0][1] = infinity, dp[0][2] = infinity, ...

        

            FILLING DP TABLE:
                - Iterate through each level `i` (from 1 to L).
                - For each level, iterate through all possible amounts of bonus latency spent `j` (from 0 to B).
                - For each combination of level `i` and bonus latency `j`:
                    - Consider all gadgets available at level `i`.
                    - For each gadget, calculate the total randomness as:
                        dp[i][j] = min(dp[i][j], dp[i-1][j-k] + randomness_of_gadget)
                    where `k` is the latency cost of the gadget, and `randomness_of_gadget` is the randomness contributed by the gadget.
                    logic behind this:
                    - If we choose a gadget with latency cost `k` at level `i`, we must have spent `j-k` latency up to level `i-1`.
                    
                    - Update dp[i][j] with the minimum randomness achievable.
                - Ensure that the base case is respected:
                    - dp[0][0] = 0 (no levels, no latency spent, randomness is 0).
                    - dp[0][j] = infinity for all j > 0 (impossible to spend latency without levels).
"""
        

        
        L = len(self.nodes_by_level)
        print(f"\n--- MRLC DP Initialization ---")
        print(f"Number of levels (L): {L}")
        print(f"Nodes by level: {self.nodes_by_level}")

        node_per_level = []
        for lvl, nodes in self.nodes_by_level.items():
            node_per_level.append(len(nodes))
        
        print(f"Nodes per level list: {node_per_level}")

        # Find the gadget with minimum latency
        # If multiple gadgets have the same latency, choose the one with the lowest randomness
        # If still tie, choose the one with the lowest area
        min_latency_gadget = min(self.gadget_map.items(), key = lambda item: (item[1]["latency"], item[1]["randomness"], item[1]["area"]))
        # store initial gadget info
        initial_gadget = min_latency_gadget[0] 
        initial_latency = min_latency_gadget[1]["latency"]
        initial_randomness = min_latency_gadget[1]["randomness"]
        print(f"\n--- Initial Gadget Selection ---\n{min_latency_gadget}")
        print(f"Initial gadget (min latency): {initial_gadget} (Latency: {initial_latency}, Randomness: {initial_randomness})")
        # Filter gadgets with randomness less than initial_randomness or is 'comar'
        matching_gadgets = {
            name: specs
            for name, specs in self.gadget_map.items() if specs["randomness"] < initial_randomness or name == 'comar'
            }
        # Adds initial_gadget if not already present
        matching_gadgets[initial_gadget] = min_latency_gadget[1] 
        print(f"Matching gadgets (randomness < {initial_randomness} or comar, plus initial): {matching_gadgets}")
        
        # Calculate bonus latency   
        total_initial_latency = L * initial_latency
        bonus_latency = target_latency - total_initial_latency
        self.initial_latency_bonus = bonus_latency

        print(f"[MRLC INFO]: Initial Latency per gadget: {initial_latency}") 
        print(f"[MRLC INFO]: Initial randomness per gadget: {initial_randomness}") 
        print(f"[MRLC INFO]: Total levels in the tree: {L}") 
        print(f"[MRLC INFO]: Total initial latency (L * initial_latency): {total_initial_latency}")
        print(f"[MRLC INFO]: Target latency: {target_latency}")
        print(f"[MRLC INFO]: Bonus latency available: {bonus_latency}")

        infinity = math.inf # Use math.inf
        
        # dp[level][bonus_spent][comar_used_flag]
        dp  = [[[infinity, infinity] for _ in range(bonus_latency + 1)] for _ in range (L + 1)]
        
        # gadget_assigned[level][bonus_spent][comar_used_flag] = (prev_bonus_spent, gadget_name, prev_comar_used_flag)
        gadget_assigned = [[[None, None] for _ in range(bonus_latency + 1)] for _ in range(L + 1)]

        self._display_3d_dp_table(dp, L, bonus_latency, "Initial DP Table (3D)")

        # Base case: 0 levels, 0 bonus spent, comar NOT used, 0 randomness
        dp[0][0][0] = 0.0 # It's a float
        self._display_3d_dp_table(dp, L, bonus_latency, "DP Table after Base Case: dp[0][0][0] = 0")


        print("\n--- Starting 3D DP Table Filling Iterations ---")
        for i in range(1, L+1): # i is the current level (1-indexed)
            current_level_idx = i - 1 # 0-indexed for node_per_level list
            node_in_current_level = node_per_level[current_level_idx]
            print(f"\n======== Processing Level {i} (Nodes: {node_in_current_level}) ========")

            for prev_j_spent in range(bonus_latency + 1): # Bonus spent up to level i-1
                # Iterate through previous comar_used states
                for prev_comar_used_state in [0, 1]: # 0: comar not used, 1: comar used

                    if dp[i-1][prev_j_spent][prev_comar_used_state] == infinity:
                        continue # This previous state is unreachable

                    print(f"\n  -- Considering previous state: dp[{i-1}][{prev_j_spent}][{prev_comar_used_state}] = {dp[i-1][prev_j_spent][prev_comar_used_state]:.2f} (randomness up to level {i-1}, comar_used={prev_comar_used_state}) --")

                    for gadget_name , gadget_spec in matching_gadgets.items():
                        print(f"    Trying gadget '{gadget_name}' for Level {i} (Randomness: {gadget_spec['randomness']:.2f}, Latency: {gadget_spec['latency']})")
                        cost_for_replacement =  gadget_spec["latency"] - initial_latency
                        randomness_for_this_gadget_base = gadget_spec["randomness"] 

                        current_total_j_spent = prev_j_spent + cost_for_replacement

                        if current_total_j_spent <= bonus_latency:
                            randomness_added_for_current_level = 0.0
                            new_comar_used_state = prev_comar_used_state # Inherit state by default

                            if gadget_name == 'comar':
                                if prev_comar_used_state == 0:
                                    randomness_added_for_current_level = 6.0 # Initial cost of comar
                                    print(f"      [{gadget_name}] selected for Level {i}. Comar was NOT used before. Adding initial randomness = {randomness_added_for_current_level:.2f}")
                                else: # prev_comar_used_state == 1
                                    randomness_added_for_current_level = 0.0 # Comar already used, no additional randomness for subsequent uses
                                    print(f"      [{gadget_name}] selected for Level {i}. Comar WAS used before. Adding 0 randomness (reuse).")
                                new_comar_used_state = 1 # Comar is now definitely used

                            else: # Not comar gadget
                                randomness_added_for_current_level = float(node_in_current_level) * randomness_for_this_gadget_base
                                print(f"      [{gadget_name}] selected for Level {i}. Randomness for this level = {node_in_current_level} nodes * {randomness_for_this_gadget_base:.2f} = {randomness_added_for_current_level:.2f}")
                            
                            total_randomness_if_chosen = dp[i - 1][prev_j_spent][prev_comar_used_state] + randomness_added_for_current_level
                            
                            print(f"      Latency Cost for replacement: {cost_for_replacement}. Total bonus spent up to Level {i}: {current_total_j_spent}")
                            print(f"      Potential total randomness: {dp[i-1][prev_j_spent][prev_comar_used_state]:.2f} (prev) + {randomness_added_for_current_level:.2f} (current level) = {total_randomness_if_chosen:.2f}")
                            print(f"      New Comar State: {new_comar_used_state}")

                            if total_randomness_if_chosen < dp[i][current_total_j_spent][new_comar_used_state]:
                                print(f"      >>> UPDATE: dp[{i}][{current_total_j_spent}][{new_comar_used_state}] updated from {dp[i][current_total_j_spent][new_comar_used_state]:.2f} to {total_randomness_if_chosen:.2f} using '{gadget_name}'")
                                dp[i][current_total_j_spent][new_comar_used_state] = total_randomness_if_chosen
                                gadget_assigned[i][current_total_j_spent][new_comar_used_state] = (prev_j_spent, gadget_name, prev_comar_used_state)
                                # Display DP table after each successful update
                                self._display_3d_dp_table(dp, L, bonus_latency, f"DP after update L{i} B{current_total_j_spent} C{new_comar_used_state} with {gadget_name}")
                            else:
                                print(f"      No update: {total_randomness_if_chosen:.2f} is not better than current dp[{i}][{current_total_j_spent}][{new_comar_used_state}] ({dp[i][current_total_j_spent][new_comar_used_state]:.2f})")
                        else:
                            print(f"      Cannot use '{gadget_name}': Latency bonus {current_total_j_spent} exceeds budget {bonus_latency}")
            
            print(f"\n======== End of Processing Level {i} ========")
            self._display_3d_dp_table(dp, L, bonus_latency, f"Final DP Table after all considerations for Level {i}")


        print("\n--- 3D DP Table Filling Complete ---")

        # Find Final randomness and Bonus Spent
        min_total_tree_randomness = infinity
        final_bonus_spent = -1
        final_comar_used_state = -1

        # Check both possible final comar states
        for k_state in [0, 1]:
            for j_spent in range(bonus_latency + 1):
                if dp[L][j_spent][k_state] < min_total_tree_randomness:
                    min_total_tree_randomness = dp[L][j_spent][k_state]
                    final_bonus_spent = j_spent
                    final_comar_used_state = k_state

        if min_total_tree_randomness == infinity:
            print("\nNo solution found within budget.")
        else:
            print(f"\nMinimum possible total tree randomness: {min_total_tree_randomness:.2f}")
            print(f"Achieved by spending a total modification cost of: {final_bonus_spent}")
            print(f"Comar final state (0=not used, 1=used): {final_comar_used_state}")
            
            self.total_randomness_after_mrlc = int(min_total_tree_randomness)
            self.total_latency_after_mrlc = total_initial_latency + final_bonus_spent
            
            # gadget used per level
            print("\n--- Path Reconstruction (3D) ---")
            chosen_gadget_for_levels = [None] * L
            current_j = final_bonus_spent
            current_k = final_comar_used_state # Start with the final comar state

            for i in range(L, 0, -1): # Levels L down to 1
                print(f"  Reconstructing Level {i} with current_j = {current_j}, current_k = {current_k}")
                
                if gadget_assigned[i][current_j][current_k] is not None:
                    prev_j_for_level_i_minus_1, gadget_name_for_level_i, prev_k_for_level_i_minus_1 = gadget_assigned[i][current_j][current_k]
                    chosen_gadget_for_levels[i - 1] = gadget_name_for_level_i
                    current_j = prev_j_for_level_i_minus_1
                    current_k = prev_k_for_level_i_minus_1 # Update comar state for previous level
                    print(f"    Chosen gadget: {gadget_name_for_level_i}. Previous J for Level {i-1}: {current_j}, Previous K: {current_k}")
                else:
                    # This fallback logic becomes more complex with 3D DP and might indicate an issue 
                    # if reached frequently.
                    # It assumes that a path SHOULD always be reconstructible if a finite value exists.
                    print(f"Critical Error: Path reconstruction failed for level {i} at budget {current_j} and comar_state {current_k}. This should ideally not happen.")
                    chosen_gadget_for_levels[i-1] = initial_gadget # Fallback
        
            print("\n[INFO] Final gadget assignment per level:")
            for lvl, g in enumerate(chosen_gadget_for_levels, start=1):
                print(f"Level {lvl}: {g}")

            for lvl, exp in self.nodes_by_level.items():
                for e in exp:
                    gadget = chosen_gadget_for_levels[lvl-1]
                    self.gadget_definition[e] = {
                                                "gadget_name":gadget,
                                                "random_numbers": self.gadget_map[gadget]["randomness"]
                                                }

            for node, gadget_spec in self.gadget_definition.items():
                gadget = gadget_spec["gadget_name"]
                gadget_def = ""
                func_name = ""
                
                if gadget == 'hpc2':
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

            self.total_area_after_mrlc =  sum([self.gadget_map[info['gadget_name']]['area'] for info in self.gadget_definition.values()])  
            
            self.print_gadget_definition()
            self.print_unique_gadget_definition()
    
    def _mrlc_dp(self, target_latency):
        """
        Main MRLC DP method - wrapper that calls the setup and DP iteration
        """
        print(f"\n[MRLC INFO] Starting MRLC-DP with target_latency={target_latency}")
        
        # Step 1: Analyze patterns
        self._analyze_and_tree_for_patterns()
        
        # Step 2: Initialize gadget selection and bonus latency
        bonus_latency = self.initial_gadget_and_list_possible_replacement(target_latency)
        
        # Step 3: Initialize 3D DP table (FIXED: pass None values, method creates it internally)
        self.initialise_dp(node_per_level=None, gadget_assigned=None)
        
        # Step 4: Run DP iterations
        self.dp_iteration()
        
        # Step 5: Reconstruct and assign gadgets
        self.choose_gadgets_for_each_level()
        
        # Step 6: Generate gadget definitions
        self.nodes_gadget_assignment()
        
        print(f"\n[MRLC SUCCESS] MRLC-DP completed successfully")
        return self.gadget_definition, self.total_latency_after_mrlc

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
        """
        initial_latency = self.min_latency_gadget[1]["latency"]
        L = self.DAG_levels
        if self.debug:
            print(f"\n--- Starting 3D DP Table Filling Iterations ---")
        
        for i in range(1, L + 1):
            nodes_in_level = list(self.nodes_by_level.get(i, []))
            and_nodes_in_level = [n for n in nodes_in_level if self._is_and_node(n)]
            and_count = len(and_nodes_in_level)
            if self.debug:
                print(f"\n======== Processing Level {i} ========")
                print(f"  Total nodes: {len(nodes_in_level)}, AND nodes: {and_count}")

            if and_count == 0:
                # carry-over for XOR-only levels (unchanged)
                for prev_j_spent in range(self.bonus_latency + 1):
                    for prev_comar_used_state in [0, 1]:
                        self.dp[i][prev_j_spent][prev_comar_used_state] = \
                            self.dp[i-1][prev_j_spent][prev_comar_used_state]
                        self.gadget_assigned[i][prev_j_spent][prev_comar_used_state] = \
                            self.gadget_assigned[i-1][prev_j_spent][prev_comar_used_state]
                continue

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

                    for gadget_name, gadget_spec in available_gadgets.items():
                        # Skip optimized gadgets unless the level is purely xor_and
                        if gadget_name in ['hpc2o', 'hpc3o'] and 'xor_and' not in patterns_in_level:
                            continue

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
                            randomness_added = float(and_count) * randomness_base

                        total_randomness = self.dp[i-1][prev_j_spent][prev_comar_used_state] + randomness_added

                        if total_randomness < self.dp[i][j_spent][new_comar_state]:
                            self.dp[i][j_spent][new_comar_state] = total_randomness
                            self.gadget_assigned[i][j_spent][new_comar_state] = \
                                (prev_j_spent, gadget_name, prev_comar_used_state)

        if self.debug:
            print(f"\n--- DP Table Filling Complete ---")

    def choose_gadgets_for_each_level(self):
        """
        Backtrack through the DP table to determine which gadget was selected for each level.
        Sets self.chosen_gadget_for_levels list.
        """
        L = self.DAG_levels
        
        # Initialize the list to store the chosen gadget for each level
        # Index 0 is unused (levels are 1-based), or adjust accordingly
        self.chosen_gadget_for_levels = [None] * L
        
        # Calculate final state to start backtracking
        min_randomness = float('inf')
        final_bonus_spent = -1
        final_comar_state = -1 # 0 or 1
        
        # Find the best end state at level L
        for j in range(self.bonus_latency + 1):
             # Try both comar states
            for k in [0, 1]: 
                if self.dp[L][j][k] < min_randomness:
                    min_randomness = self.dp[L][j][k]
                    final_bonus_spent = j
                    final_comar_state = k

        if min_randomness == float('inf'):
            print("[MRLC ERROR] No valid path found in DP table.")
            # Fallback: assign initial gadget to all levels
            default_gadget = self.min_latency_gadget[0]
            self.chosen_gadget_for_levels = [default_gadget] * L
            return

        print(f"[MRLC INFO] Optimal randomness: {min_randomness} with bonus spent: {final_bonus_spent}")

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
        """Assign chosen gadgets to AND nodes, build definitions, and compute area."""
        # Ensure chosen_gadget_for_levels exists
        if not hasattr(self, 'chosen_gadget_for_levels') or self.chosen_gadget_for_levels is None:
            default = self.min_latency_gadget[0]
            self.chosen_gadget_for_levels = [default] * len(self.nodes_by_level)

        # Map expression -> gadget info
        self.gadget_definition = {}

        # 1) Assign gadgets to AND nodes per level
        for lvl, nodes in self.nodes_by_level.items():
            level_index = lvl - 1
            if level_index < 0 or level_index >= len(self.chosen_gadget_for_levels):
                continue

            gadget = self.chosen_gadget_for_levels[level_index]
            if gadget is None or gadget not in self.gadget_map:
                continue

            for expr in nodes:
                if not self._is_and_node(expr):
                    continue
                self.gadget_definition[expr] = {
                    "gadget_name": gadget,
                    "random_numbers": self.gadget_map[gadget]["randomness"],
                }

        # 2) Build unique_gadgets_definition using existing gadget generator classes
        self.unique_gadgets_definition = {}
        from Gadgets import HPC2, HPC1, HPC3, COMAR, Domand

        for _, gadget_spec in self.gadget_definition.items():
            gadget = gadget_spec["gadget_name"].lower()
            if gadget in self.unique_gadgets_definition:
                continue

            if gadget == 'hpc2':
                obj = HPC2(d=self.d)
            elif gadget == 'hpc1':
                obj = HPC1(d=self.d)
            elif gadget == 'hpc3':
                obj = HPC3(d=self.d)
            elif gadget == 'comar':
                obj = COMAR()
            elif gadget == 'domand':
                obj = Domand(d=self.d)
            else:
                continue

            gadget_def = obj.generate_multiply_function()
            func_name = obj.get_function_name()

            # add func_name to all entries of this gadget type
            for expr, info in self.gadget_definition.items():
                if info["gadget_name"].lower() == gadget:
                    info["func_name"] = func_name

            self.unique_gadgets_definition[gadget] = gadget_def

        # 3) Compute total area
        self.total_area_after_mrlc = sum(
            self.gadget_map[info["gadget_name"]]["area"]
            for info in self.gadget_definition.values()
        )

        # 4) Optional debug printing
        if self.debug:
            from tabulate import tabulate
            print("[INFO] Final gadget assignment per level:")
            table_data = []
            for expr, info in self.gadget_definition.items():
                node_no = self.and_tree.node_map.get(expr, None)
                table_data.append((node_no, expr, info["gadget_name"]))
            print(tabulate(table_data, headers=["Gate No", "Expression", "Gadget Name"], tablefmt="grid"))

            print("\n[INFO] Unique gadget definitions:")
            for gname, gdef in self.unique_gadgets_definition.items():
                print(f"\n== {gname} ==\n{gdef}")

    def _analyze_and_tree_for_patterns(self):
        """
        Detect XOR+AND patterns WITHOUT using the graph (avoids TypeError).
        - Intra-node:  t = a ^ (b & c)
        - Cross-level: AND output used by XOR in next level  ← this enables hpc2o/hpc3o
        """
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
                self.node_pattern[node_expr] = 'pure_and'   # default

                # === INTRA-NODE PATTERN ===
                if " ^ " in node_str and " & " in node_str:
                    self.node_pattern[node_expr] = 'xor_and'
                    xor_and_count += 1
                    if self.debug:
                        print(f"  [INTRA] {node_expr} → 'xor_and'")
                    continue

                # === CROSS-LEVEL PATTERN (your requested case) ===
                if lvl + 1 not in self.nodes_by_level:
                    continue
                output_var = self._extract_lhs_var(node_expr)
                if not output_var:
                    continue

                for next_expr in self.nodes_by_level[lvl + 1]:
                    next_str = str(next_expr)
                    if (self._is_xor_node(next_str) and output_var in next_str):
                        self.node_pattern[node_expr] = 'xor_and'
                        xor_and_count += 1
                        if self.debug:
                            print(f"  [CROSS-LEVEL] {node_expr} → output '{output_var}' used in XOR at level {lvl+1} → 'xor_and'")
                        break

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
        """Return only the gadgets legal for the detected pattern."""
        if pattern_type == 'xor_and':
            # hpc2o / hpc3o are only for AND→XOR patterns
            return {name: spec for name, spec in matching_gadgets.items()
                    if name in ['hpc2o', 'hpc3o', 'comar']}
        else:
            # normal gadgets only
            return {name: spec for name, spec in matching_gadgets.items()
                    if name not in ['hpc2o', 'hpc3o']}
        
    def initial_gadget_and_list_possible_replacement(self, target_latency):
        """
        Selects the initial gadget (minimum latency) and identifies potential replacements.
        Calculates the initial latency of the entire circuit and the bonus latency budget.
        Now the initial latency is computed only over levels that actually contain AND nodes.
        """
        # Find gadget with minimum latency (tie‑break by randomness then area)
        self.min_latency_gadget = min(
            self.gadget_map.items(),
            key=lambda item: (item[1]["latency"], item[1]["randomness"], item[1]["area"])
        )

        initial_gadget_name = self.min_latency_gadget[0]
        initial_latency = self.min_latency_gadget[1]["latency"]
        initial_randomness = self.min_latency_gadget[1]["randomness"]

        print(f"[MRLC INFO]: Initial gadget selected: {initial_gadget_name}")
        print(f"             Latency: {initial_latency}, Randomness: {initial_randomness}")

        # Filter gadgets that have randomness <= initial gadget's randomness
        # and always include 'comar' if present
        self.matching_gadgets = {
            name: specs
            for name, specs in self.gadget_map.items()
            if specs["randomness"] <= initial_randomness or name == 'comar'
        }

        # Ensure initial gadget is in matching_gadgets
        if initial_gadget_name not in self.matching_gadgets:
            self.matching_gadgets[initial_gadget_name] = self.min_latency_gadget[1]

        print(f"[MRLC INFO]: Matching gadgets for optimization: {list(self.matching_gadgets.keys())}")

        # Total number of levels in the DAG (for DP indices)
        self.DAG_levels = len(self.nodes_by_level)

        # Count only levels that actually have AND nodes: these are the ones that
        # will contribute latency and can be optimized by gadget replacement.
        effective_levels = 0
        for lvl, nodes in self.nodes_by_level.items():
            and_nodes_in_level = [n for n in nodes if self._is_and_node(n)]
            if and_nodes_in_level:
                effective_levels += 1

        # Initial latency is computed only over effective AND levels
        self.total_initial_latency = effective_levels * initial_latency

        # Compute bonus latency w.r.t. target_latency
        self.bonus_latency = target_latency - self.total_initial_latency
        self.initial_latency_bonus = self.bonus_latency

        print(f"[MRLC INFO]: Circuit Analysis:")
        print(f"  - Total DAG levels (incl. XOR-only): {self.DAG_levels}")
        print(f"  - Effective AND levels: {effective_levels}")
        print(f"  - Initial circuit latency (AND levels only): {self.total_initial_latency}")
        print(f"  - Target latency: {target_latency}")
        print(f"  - Bonus latency available: {self.bonus_latency}")

        if self.bonus_latency < 0:
            print(f"[MRLC WARN]: Target latency ({target_latency}) is less than "
                f"minimum possible latency based on AND levels ({self.total_initial_latency})!")
            # Allow algorithm to run but with zero bonus
            self.bonus_latency = 0

        return self.bonus_latency

    def _is_and_node(self, expr: str) -> bool:
        """
        Return True if this TAC expression corresponds to an AND operation
        of the form:  LHS = RHS1 & RHS2
        (very simple heuristic: check for '&' on RHS)
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
    







from DSE_algorithm.dse import DSE
from tabulate import tabulate # type: ignore
import json
from collections import defaultdict
import heapq
from Gadgets import HPC1, HPC2, HPC3, COMAR, Domand, HPC2o, HPC3o
import math

class MRLC(DSE):
    
    def __init__(self, d, and_tree, gadget_map):
        super().__init__(d, and_tree, gadget_map)
        self.node_pattern = {}
        self.debug = False
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

    def mrlc_dp(self, target_latency):

        """
        Goal : make total randomness as low as possible.

            - we can update a lvl by any gadget  


            --------------------------------
            gadget | randomness | latency   |
            ---------------------------------
            g1     |    r1      |   l1      |
            g2     |    r2      |   l2      |
            g3     |    r3      |   l3      |
            g4     |    r4      |   l4      |

            - We only have certain amount of latency to spend from.
            - bonus = total latency - initial_latency

            Greedy won't work (choosing gadget with least randomness for each level)

            What if the lowest ranomdomess gadget is very expensive in terms of latency, 
            then we might spend all our bonus on the few levels
            and have no bonus left for later lvls what if a slightly less effective but 
            cheaper gadget(in terms of latency), would have been better.

            using dp:

            "Let's figure out the best way for the first level with differnt amount of latency spent. 
            Then, using that knowledge, we figure out the best way for the first two levels with 
            different amounts of latency spent, and so on."

            kya memoize karna h
            - level - ith level.
            - how much money we spent up to i-1 level. j bonous spent

            dp table dp[i][j] = minimium randomness possible from lvl 1 to L, if we spend j bonous.
            i - > 0 to L
            j -> 0 to B

            base case :

            No Level 0:
                If we consider 0 levels and spend 0 latency, the total randomness is 0.
                dp[0][0] = 0
                If we consider 0 level but somehow spent bonus > 0, that is impossible. So, the randomness is "infinity" (meaning, "this situation can't happen).
                dp[0][1] = infinity, dp[0][2] = infinity, ...

        

            FILLING DP TABLE:
                - Iterate through each level `i` (from 1 to L).
                - For each level, iterate through all possible amounts of bonus latency spent `j` (from 0 to B).
                - For each combination of level `i` and bonus latency `j`:
                    - Consider all gadgets available at level `i`.
                    - For each gadget, calculate the total randomness as:
                        dp[i][j] = min(dp[i][j], dp[i-1][j-k] + randomness_of_gadget)
                    where `k` is the latency cost of the gadget, and `randomness_of_gadget` is the randomness contributed by the gadget.
                    logic behind this:
                    - If we choose a gadget with latency cost `k` at level `i`, we must have spent `j-k` latency up to level `i-1`.
                    
                    - Update dp[i][j] with the minimum randomness achievable.
                - Ensure that the base case is respected:
                    - dp[0][0] = 0 (no levels, no latency spent, randomness is 0).
                    - dp[0][j] = infinity for all j > 0 (impossible to spend latency without levels).
"""
        

        
        L = len(self.nodes_by_level)
        print(f"\n--- MRLC DP Initialization ---")
        print(f"Number of levels (L): {L}")
        print(f"Nodes by level: {self.nodes_by_level}")

        node_per_level = []
        for lvl, nodes in self.nodes_by_level.items():
            node_per_level.append(len(nodes))
        
        print(f"Nodes per level list: {node_per_level}")

        # Find the gadget with minimum latency
        # If multiple gadgets have the same latency, choose the one with the lowest randomness
        # If still tie, choose the one with the lowest area
        min_latency_gadget = min(self.gadget_map.items(), key = lambda item: (item[1]["latency"], item[1]["randomness"], item[1]["area"]))
        # store initial gadget info
        initial_gadget = min_latency_gadget[0] 
        initial_latency = min_latency_gadget[1]["latency"]
        initial_randomness = min_latency_gadget[1]["randomness"]
        print(f"\n--- Initial Gadget Selection ---\n{min_latency_gadget}")
        print(f"Initial gadget (min latency): {initial_gadget} (Latency: {initial_latency}, Randomness: {initial_randomness})")
        # Filter gadgets with randomness less than initial_randomness or is 'comar'
        matching_gadgets = {
            name: specs
            for name, specs in self.gadget_map.items() if specs["randomness"] < initial_randomness or name == 'comar'
            }
        # Adds initial_gadget if not already present
        matching_gadgets[initial_gadget] = min_latency_gadget[1] 
        print(f"Matching gadgets (randomness < {initial_randomness} or comar, plus initial): {matching_gadgets}")
        
        # Calculate bonus latency   
        total_initial_latency = L * initial_latency
        bonus_latency = target_latency - total_initial_latency
        self.initial_latency_bonus = bonus_latency

        print(f"[MRLC INFO]: Initial Latency per gadget: {initial_latency}") 
        print(f"[MRLC INFO]: Initial randomness per gadget: {initial_randomness}") 
        print(f"[MRLC INFO]: Total levels in the tree: {L}") 
        print(f"[MRLC INFO]: Total initial latency (L * initial_latency): {total_initial_latency}")
        print(f"[MRLC INFO]: Target latency: {target_latency}")
        print(f"[MRLC INFO]: Bonus latency available: {bonus_latency}")

        infinity = math.inf # Use math.inf
        
        # dp[level][bonus_spent][comar_used_flag]
        dp  = [[[infinity, infinity] for _ in range(bonus_latency + 1)] for _ in range (L + 1)]
        
        # gadget_assigned[level][bonus_spent][comar_used_flag] = (prev_bonus_spent, gadget_name, prev_comar_used_flag)
        gadget_assigned = [[[None, None] for _ in range(bonus_latency + 1)] for _ in range(L + 1)]

        self._display_3d_dp_table(dp, L, bonus_latency, "Initial DP Table (3D)")

        # Base case: 0 levels, 0 bonus spent, comar NOT used, 0 randomness
        dp[0][0][0] = 0.0 # It's a float
        self._display_3d_dp_table(dp, L, bonus_latency, "DP Table after Base Case: dp[0][0][0] = 0")


        print("\n--- Starting 3D DP Table Filling Iterations ---")
        for i in range(1, L+1): # i is the current level (1-indexed)
            current_level_idx = i - 1 # 0-indexed for node_per_level list
            node_in_current_level = node_per_level[current_level_idx]
            print(f"\n======== Processing Level {i} (Nodes: {node_in_current_level}) ========")

            for prev_j_spent in range(bonus_latency + 1): # Bonus spent up to level i-1
                # Iterate through previous comar_used states
                for prev_comar_used_state in [0, 1]: # 0: comar not used, 1: comar used

                    if dp[i-1][prev_j_spent][prev_comar_used_state] == infinity:
                        continue # This previous state is unreachable

                    print(f"\n  -- Considering previous state: dp[{i-1}][{prev_j_spent}][{prev_comar_used_state}] = {dp[i-1][prev_j_spent][prev_comar_used_state]:.2f} (randomness up to level {i-1}, comar_used={prev_comar_used_state}) --")

                    for gadget_name , gadget_spec in matching_gadgets.items():
                        print(f"    Trying gadget '{gadget_name}' for Level {i} (Randomness: {gadget_spec['randomness']:.2f}, Latency: {gadget_spec['latency']})")
                        cost_for_replacement =  gadget_spec["latency"] - initial_latency
                        randomness_for_this_gadget_base = gadget_spec["randomness"] 

                        current_total_j_spent = prev_j_spent + cost_for_replacement

                        if current_total_j_spent <= bonus_latency:
                            randomness_added_for_current_level = 0.0
                            new_comar_used_state = prev_comar_used_state # Inherit state by default

                            if gadget_name == 'comar':
                                if prev_comar_used_state == 0:
                                    randomness_added_for_current_level = 6.0 # Initial cost of comar
                                    print(f"      [{gadget_name}] selected for Level {i}. Comar was NOT used before. Adding initial randomness = {randomness_added_for_current_level:.2f}")
                                else: # prev_comar_used_state == 1
                                    randomness_added_for_current_level = 0.0 # Comar already used, no additional randomness for subsequent uses
                                    print(f"      [{gadget_name}] selected for Level {i}. Comar WAS used before. Adding 0 randomness (reuse).")
                                new_comar_used_state = 1 # Comar is now definitely used

                            else: # Not comar gadget
                                randomness_added_for_current_level = float(node_in_current_level) * randomness_for_this_gadget_base
                                print(f"      [{gadget_name}] selected for Level {i}. Randomness for this level = {node_in_current_level} nodes * {randomness_for_this_gadget_base:.2f} = {randomness_added_for_current_level:.2f}")
                            
                            total_randomness_if_chosen = dp[i - 1][prev_j_spent][prev_comar_used_state] + randomness_added_for_current_level
                            
                            print(f"      Latency Cost for replacement: {cost_for_replacement}. Total bonus spent up to Level {i}: {current_total_j_spent}")
                            print(f"      Potential total randomness: {dp[i-1][prev_j_spent][prev_comar_used_state]:.2f} (prev) + {randomness_added_for_current_level:.2f} (current level) = {total_randomness_if_chosen:.2f}")
                            print(f"      New Comar State: {new_comar_used_state}")

                            if total_randomness_if_chosen < dp[i][current_total_j_spent][new_comar_used_state]:
                                print(f"      >>> UPDATE: dp[{i}][{current_total_j_spent}][{new_comar_used_state}] updated from {dp[i][current_total_j_spent][new_comar_used_state]:.2f} to {total_randomness_if_chosen:.2f} using '{gadget_name}'")
                                dp[i][current_total_j_spent][new_comar_used_state] = total_randomness_if_chosen
                                gadget_assigned[i][current_total_j_spent][new_comar_used_state] = (prev_j_spent, gadget_name, prev_comar_used_state)
                                # Display DP table after each successful update
                                self._display_3d_dp_table(dp, L, bonus_latency, f"DP after update L{i} B{current_total_j_spent} C{new_comar_used_state} with {gadget_name}")
                            else:
                                print(f"      No update: {total_randomness_if_chosen:.2f} is not better than current dp[{i}][{current_total_j_spent}][{new_comar_used_state}] ({dp[i][current_total_j_spent][new_comar_used_state]:.2f})")
                        else:
                            print(f"      Cannot use '{gadget_name}': Latency bonus {current_total_j_spent} exceeds budget {bonus_latency}")
            
            print(f"\n======== End of Processing Level {i} ========")
            self._display_3d_dp_table(dp, L, bonus_latency, f"Final DP Table after all considerations for Level {i}")


        print("\n--- 3D DP Table Filling Complete ---")

        # Find Final randomness and Bonus Spent
        min_total_tree_randomness = infinity
        final_bonus_spent = -1
        final_comar_used_state = -1

        # Check both possible final comar states
        for k_state in [0, 1]:
            for j_spent in range(bonus_latency + 1):
                if dp[L][j_spent][k_state] < min_total_tree_randomness:
                    min_total_tree_randomness = dp[L][j_spent][k_state]
                    final_bonus_spent = j_spent
                    final_comar_used_state = k_state

        if min_total_tree_randomness == infinity:
            print("\nNo solution found within budget.")
        else:
            print(f"\nMinimum possible total tree randomness: {min_total_tree_randomness:.2f}")
            print(f"Achieved by spending a total modification cost of: {final_bonus_spent}")
            print(f"Comar final state (0=not used, 1=used): {final_comar_used_state}")
            
            self.total_randomness_after_mrlc = int(min_total_tree_randomness)
            self.total_latency_after_mrlc = total_initial_latency + final_bonus_spent
            
            # gadget used per level
            print("\n--- Path Reconstruction (3D) ---")
            chosen_gadget_for_levels = [None] * L
            current_j = final_bonus_spent
            current_k = final_comar_used_state # Start with the final comar state

            for i in range(L, 0, -1): # Levels L down to 1
                print(f"  Reconstructing Level {i} with current_j = {current_j}, current_k = {current_k}")
                
                if gadget_assigned[i][current_j][current_k] is not None:
                    prev_j_for_level_i_minus_1, gadget_name_for_level_i, prev_k_for_level_i_minus_1 = gadget_assigned[i][current_j][current_k]
                    chosen_gadget_for_levels[i - 1] = gadget_name_for_level_i
                    current_j = prev_j_for_level_i_minus_1
                    current_k = prev_k_for_level_i_minus_1 # Update comar state for previous level
                    print(f"    Chosen gadget: {gadget_name_for_level_i}. Previous J for Level {i-1}: {current_j}, Previous K: {current_k}")
                else:
                    # This fallback logic becomes more complex with 3D DP and might indicate an issue 
                    # if reached frequently.
                    # It assumes that a path SHOULD always be reconstructible if a finite value exists.
                    print(f"Critical Error: Path reconstruction failed for level {i} at budget {current_j} and comar_state {current_k}. This should ideally not happen.")
                    chosen_gadget_for_levels[i-1] = initial_gadget # Fallback
        
            print("\n[INFO] Final gadget assignment per level:")
            for lvl, g in enumerate(chosen_gadget_for_levels, start=1):
                print(f"Level {lvl}: {g}")

            for lvl, exp in self.nodes_by_level.items():
                for e in exp:
                    gadget = chosen_gadget_for_levels[lvl-1]
                    self.gadget_definition[e] = {
                                                "gadget_name":gadget,
                                                "random_numbers": self.gadget_map[gadget]["randomness"]
                                                }

            for node, gadget_spec in self.gadget_definition.items():
                gadget = gadget_spec["gadget_name"]
                gadget_def = ""
                func_name = ""
                
                if gadget == 'hpc2':
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

            self.total_area_after_mrlc =  sum([self.gadget_map[info['gadget_name']]['area'] for info in self.gadget_definition.values()])  
            
            self.print_gadget_definition()
            self.print_unique_gadget_definition()
    
    def _mrlc_dp(self, target_latency):
        """
        Main MRLC DP method - wrapper that calls the setup and DP iteration
        """
        print(f"\n[MRLC INFO] Starting MRLC-DP with target_latency={target_latency}")
        
        # Step 1: Analyze patterns
        self._analyze_and_tree_for_patterns()
        
        # Step 2: Initialize gadget selection and bonus latency
        bonus_latency = self.initial_gadget_and_list_possible_replacement(target_latency)
        
        # Step 3: Initialize 3D DP table (FIXED: pass None values, method creates it internally)
        self.initialise_dp(node_per_level=None, gadget_assigned=None)
        
        # Step 4: Run DP iterations
        self.dp_iteration()
        
        # Step 5: Reconstruct and assign gadgets
        self.choose_gadgets_for_each_level()
        
        # Step 6: Generate gadget definitions
        self.nodes_gadget_assignment()
        
        print(f"\n[MRLC SUCCESS] MRLC-DP completed successfully")
        return self.gadget_definition, self.total_latency_after_mrlc

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
        """
        initial_latency = self.min_latency_gadget[1]["latency"]
        L = self.DAG_levels
        if self.debug:
            print(f"\n--- Starting 3D DP Table Filling Iterations ---")
        
        for i in range(1, L + 1):
            nodes_in_level = list(self.nodes_by_level.get(i, []))
            and_nodes_in_level = [n for n in nodes_in_level if self._is_and_node(n)]
            and_count = len(and_nodes_in_level)
            if self.debug:
                print(f"\n======== Processing Level {i} ========")
                print(f"  Total nodes: {len(nodes_in_level)}, AND nodes: {and_count}")

            if and_count == 0:
                # carry-over for XOR-only levels (unchanged)
                for prev_j_spent in range(self.bonus_latency + 1):
                    for prev_comar_used_state in [0, 1]:
                        self.dp[i][prev_j_spent][prev_comar_used_state] = \
                            self.dp[i-1][prev_j_spent][prev_comar_used_state]
                        self.gadget_assigned[i][prev_j_spent][prev_comar_used_state] = \
                            self.gadget_assigned[i-1][prev_j_spent][prev_comar_used_state]
                continue

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

                    for gadget_name, gadget_spec in available_gadgets.items():
                        # Skip optimized gadgets unless the level is purely xor_and
                        if gadget_name in ['hpc2o', 'hpc3o'] and 'xor_and' not in patterns_in_level:
                            continue

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
                            randomness_added = float(and_count) * randomness_base

                        total_randomness = self.dp[i-1][prev_j_spent][prev_comar_used_state] + randomness_added

                        if total_randomness < self.dp[i][j_spent][new_comar_state]:
                            self.dp[i][j_spent][new_comar_state] = total_randomness
                            self.gadget_assigned[i][j_spent][new_comar_state] = \
                                (prev_j_spent, gadget_name, prev_comar_used_state)

        if self.debug:
            print(f"\n--- DP Table Filling Complete ---")

    def choose_gadgets_for_each_level(self):
        """
        Backtrack through the DP table to determine which gadget was selected for each level.
        Sets self.chosen_gadget_for_levels list.
        """
        L = self.DAG_levels
        
        # Initialize the list to store the chosen gadget for each level
        # Index 0 is unused (levels are 1-based), or adjust accordingly
        self.chosen_gadget_for_levels = [None] * L
        
        # Calculate final state to start backtracking
        min_randomness = float('inf')
        final_bonus_spent = -1
        final_comar_state = -1 # 0 or 1
        
        # Find the best end state at level L
        for j in range(self.bonus_latency + 1):
             # Try both comar states
            for k in [0, 1]: 
                if self.dp[L][j][k] < min_randomness:
                    min_randomness = self.dp[L][j][k]
                    final_bonus_spent = j
                    final_comar_state = k

        if min_randomness == float('inf'):
            print("[MRLC ERROR] No valid path found in DP table.")
            # Fallback: assign initial gadget to all levels
            default_gadget = self.min_latency_gadget[0]
            self.chosen_gadget_for_levels = [default_gadget] * L
            return

        print(f"[MRLC INFO] Optimal randomness: {min_randomness} with bonus spent: {final_bonus_spent}")

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
        """Assign chosen gadgets to AND nodes, build definitions, and compute area."""
        # Ensure chosen_gadget_for_levels exists
        if not hasattr(self, 'chosen_gadget_for_levels') or self.chosen_gadget_for_levels is None:
            default = self.min_latency_gadget[0]
            self.chosen_gadget_for_levels = [default] * len(self.nodes_by_level)

        # Map expression -> gadget info
        self.gadget_definition = {}

        # 1) Assign gadgets to AND nodes per level
        for lvl, nodes in self.nodes_by_level.items():
            level_index = lvl - 1
            if level_index < 0 or level_index >= len(self.chosen_gadget_for_levels):
                continue

            gadget = self.chosen_gadget_for_levels[level_index]
            if gadget is None or gadget not in self.gadget_map:
                continue

            for expr in nodes:
                if not self._is_and_node(expr):
                    continue
                self.gadget_definition[expr] = {
                    "gadget_name": gadget,
                    "random_numbers": self.gadget_map[gadget]["randomness"],
                }

        # 2) Build unique_gadgets_definition using existing gadget generator classes
        self.unique_gadgets_definition = {}
        from Gadgets import HPC2, HPC1, HPC3, COMAR, Domand

        for _, gadget_spec in self.gadget_definition.items():
            gadget = gadget_spec["gadget_name"].lower()
            if gadget in self.unique_gadgets_definition:
                continue

            if gadget == 'hpc2':
                obj = HPC2(d=self.d)
            elif gadget == 'hpc1':
                obj = HPC1(d=self.d)
            elif gadget == 'hpc3':
                obj = HPC3(d=self.d)
            elif gadget == 'comar':
                obj = COMAR()
            elif gadget == 'domand':
                obj = Domand(d=self.d)
            else:
                continue

            gadget_def = obj.generate_multiply_function()
            func_name = obj.get_function_name()

            # add func_name to all entries of this gadget type
            for expr, info in self.gadget_definition.items():
                if info["gadget_name"].lower() == gadget:
                    info["func_name"] = func_name

            self.unique_gadgets_definition[gadget] = gadget_def

        # 3) Compute total area
        self.total_area_after_mrlc = sum(
            self.gadget_map[info["gadget_name"]]["area"]
            for info in self.gadget_definition.values()
        )

        # 4) Optional debug printing
        if self.debug:
            from tabulate import tabulate
            print("[INFO] Final gadget assignment per level:")
            table_data = []
            for expr, info in self.gadget_definition.items():
                node_no = self.and_tree.node_map.get(expr, None)
                table_data.append((node_no, expr, info["gadget_name"]))
            print(tabulate(table_data, headers=["Gate No", "Expression", "Gadget Name"], tablefmt="grid"))

            print("\n[INFO] Unique gadget definitions:")
            for gname, gdef in self.unique_gadgets_definition.items():
                print(f"\n== {gname} ==\n{gdef}")

    def _analyze_and_tree_for_patterns(self):
        """
        Detect XOR+AND patterns WITHOUT using the graph (avoids TypeError).
        - Intra-node:  t = a ^ (b & c)
        - Cross-level: AND output used by XOR in next level  ← this enables hpc2o/hpc3o
        """
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
                self.node_pattern[node_expr] = 'pure_and'   # default

                # === INTRA-NODE PATTERN ===
                if " ^ " in node_str and " & " in node_str:
                    self.node_pattern[node_expr] = 'xor_and'
                    xor_and_count += 1
                    if self.debug:
                        print(f"  [INTRA] {node_expr} → 'xor_and'")
                    continue

                # === CROSS-LEVEL PATTERN with single-fanout constraint ===
                if lvl + 1 not in self.nodes_by_level:
                    continue
                output_var = self._extract_lhs_var(node_expr)
                if not output_var:
                    continue

                # 1) Count fan-out in later levels and track if we have an XOR use at lvl+1
                fanout_count = 0
                xor_level_match = False

                max_lvl = max(self.nodes_by_level.keys())
                for next_lvl in range(lvl + 1, max_lvl + 1):
                    if next_lvl not in self.nodes_by_level:
                        continue
                    for next_expr in self.nodes_by_level[next_lvl]:
                        next_str = str(next_expr)
                        # ignore LHS, look only in RHS
                        if '=' in next_str:
                            _, rhs = next_str.split('=', 1)
                            rhs = rhs.strip()
                        else:
                            rhs = next_str

                        if output_var in rhs:
                            fanout_count += 1
                            # only count as XOR match if it's at the immediate next level
                            if next_lvl == lvl + 1 and self._is_xor_node(next_str):
                                xor_level_match = True

                        # early stop if more than 1 fan-out
                        if fanout_count > 1:
                            break
                    if fanout_count > 1:
                        break

                # 2) Require exactly one fan-out and that use is XOR at next level
                if fanout_count == 1 and xor_level_match:
                    self.node_pattern[node_expr] = 'xor_and'
                    xor_and_count += 1
                    if self.debug:
                        print(f"  [CROSS-LEVEL] {node_expr} → output '{output_var}' "
                              f"has single fan-out in XOR at level {lvl+1} → 'xor_and'")

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
        """Return only the gadgets legal for the detected pattern."""
        if pattern_type == 'xor_and':
            # hpc2o / hpc3o are only for AND→XOR patterns
            return {name: spec for name, spec in matching_gadgets.items()
                    if name in ['hpc2o', 'hpc3o', 'comar']}
        else:
            # normal gadgets only
            return {name: spec for name, spec in matching_gadgets.items()
                    if name not in ['hpc2o', 'hpc3o']}
        
    def initial_gadget_and_list_possible_replacement(self, target_latency):
        """
        Selects the initial gadget (minimum latency) and identifies potential replacements.
        Calculates the initial latency of the entire circuit and the bonus latency budget.
        Now the initial latency is computed only over levels that actually contain AND nodes.
        """
        # Find gadget with minimum latency (tie‑break by randomness then area)
        self.min_latency_gadget = min(
            self.gadget_map.items(),
            key=lambda item: (item[1]["latency"], item[1]["randomness"], item[1]["area"])
        )

        initial_gadget_name = self.min_latency_gadget[0]
        initial_latency = self.min_latency_gadget[1]["latency"]
        initial_randomness = self.min_latency_gadget[1]["randomness"]

        print(f"[MRLC INFO]: Initial gadget selected: {initial_gadget_name}")
        print(f"             Latency: {initial_latency}, Randomness: {initial_randomness}")

        # Filter gadgets that have randomness <= initial gadget's randomness
        # and always include 'comar' if present
        self.matching_gadgets = {
            name: specs
            for name, specs in self.gadget_map.items()
            if specs["randomness"] <= initial_randomness or name == 'comar'
        }

        # Ensure initial gadget is in matching_gadgets
        if initial_gadget_name not in self.matching_gadgets:
            self.matching_gadgets[initial_gadget_name] = self.min_latency_gadget[1]

        print(f"[MRLC INFO]: Matching gadgets for optimization: {list(self.matching_gadgets.keys())}")

        # Total number of levels in the DAG (for DP indices)
        self.DAG_levels = len(self.nodes_by_level)

        # Count only levels that actually have AND nodes: these are the ones that
        # will contribute latency and can be optimized by gadget replacement.
        effective_levels = 0
        for lvl, nodes in self.nodes_by_level.items():
            and_nodes_in_level = [n for n in nodes if self._is_and_node(n)]
            if and_nodes_in_level:
                effective_levels += 1

        # Initial latency is computed only over effective AND levels
        self.total_initial_latency = effective_levels * initial_latency

        # Compute bonus latency w.r.t. target_latency
        self.bonus_latency = target_latency - self.total_initial_latency
        self.initial_latency_bonus = self.bonus_latency

        print(f"[MRLC INFO]: Circuit Analysis:")
        print(f"  - Total DAG levels (incl. XOR-only): {self.DAG_levels}")
        print(f"  - Effective AND levels: {effective_levels}")
        print(f"  - Initial circuit latency (AND levels only): {self.total_initial_latency}")
        print(f"  - Target latency: {target_latency}")
        print(f"  - Bonus latency available: {self.bonus_latency}")

        if self.bonus_latency < 0:
            print(f"[MRLC WARN]: Target latency ({target_latency}) is less than "
                f"minimum possible latency based on AND levels ({self.total_initial_latency})!")
            # Allow algorithm to run but with zero bonus
            self.bonus_latency = 0

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