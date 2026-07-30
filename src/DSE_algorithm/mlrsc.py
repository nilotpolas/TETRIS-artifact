from DSE_algorithm.dse import DSE
from tabulate import tabulate
import json
from collections import defaultdict
import heapq
import Gadgets as secure_gadget
from collections import OrderedDict
import math
from Gadgets import HPC1, HPC2, HPC3, COMAR, Domand
import sqlite3

class MLRC(DSE):
    """
    Minimise Latency Under Randomness Constraint (MLRC)
    Enhanced version with database integration for dynamic gadget specs
    
    MLRSC (Minimum Latency under Randomness and Security Constraints)

    Objective: Minimize circuit latency while respecting randomness budget and maximizing security level.
    Enhanced Algorithm:
    Input: Minimum masking order (min_d), target randomness budget, maximum d to try
    Process: Iteratively tries masking orders from highest to lowest (max_d down to min_d)
    Selection: Chooses the highest feasible masking order that fits within the randomness constraint
    Optimization: Uses greedy approach with level-wise gadget assignment, prioritizing low-latency gadgets while staying within randomness budget

    Key Features:
    Automatically maximizes security by selecting highest possible d ≥ min_d
    Database-driven gadget specification loading for each masking order
    Handles area reduction when latency constraints are tight
    Returns both optimal gadget mapping and achieved security level

    """

    def __init__(self, d, and_tree, gadget_map):
        super().__init__(d, and_tree, gadget_map)
        self.processed_node = 0

    def construct_min_heap(self):
        """
        Constructs the min heap
        where each node is the level number
        @return minheap of levels created on the basis of number of node in a level
        """
        min_heap = []
        for level, nodes in self.nodes_by_level.items():
            gate_count = len(nodes)  # number of gate at this level
            self.level_latency[level] = 2
            heapq.heappush(min_heap, (gate_count, -level, nodes))
        return min_heap

    def find_min_gate_level(self, min_heap):
        """
        Extract the level with the minimum number of nodes
        @param min_heap: The min heap storing (gate_count, level, nodes)
        @return: the level with least gate.
        """
        if not min_heap:
            return None
        _, level, _ = heapq.heappop(min_heap)
        return abs(level)

    def print_gadget_specs(self, gadget_specs):
        table_data = []
        for gadget, values in gadget_specs.items():
            table_data.append([gadget, values['latency'], values['randomness'], values['area']])
        print(f"\n[INFO]: Populated DSE MAP for order")
        print(tabulate(table_data, headers=["Gadget", "Latency", "randomness", "area"], tablefmt="grid"))

    def mlrc(self, target_randomness):
        # Check if gadget_map is empty
        if not self.gadget_map or len(self.gadget_map) == 0:
            print(f"[ERROR]: No gadgets available for d={self.d}. Gadget map is empty.")
            return None
        
        # 1. Build a min-heap where each level is ordered by number of nodes
        min_heap = self.construct_min_heap()
        print(f"[INFO] : Constructed min heap\n{min_heap}")

        # 2. find the gadget with least randomness
        min_randomness_gadget = min(self.gadget_map.items(), key=lambda item: (item[1]["randomness"], item[1]["latency"], item[1]["area"]))
        initial_gadget_name = min_randomness_gadget[0]
        print(f"[INFO]: initial gadget selected is {initial_gadget_name}")
        gadget_specs = min_randomness_gadget[1]

        initial_randomness = gadget_specs['randomness']
        print(f"[INFO]: Initial_random : {initial_randomness}")
        initial_latency = gadget_specs['latency']
        print(f"[INFO]: Initial_latency: {initial_latency}")
        initial_area = gadget_specs['area']
        print(f"[INFO]: Initial area : {initial_area}")

        # compute the bonus or buffer randomness
        randomness_bonus = target_randomness - initial_randomness * self.and_tree.graph.num_nodes()
        print(f"[INFO]: Target randomness : {target_randomness}")
        print(f"[INFO]: Total initial randomness : {initial_randomness * self.and_tree.graph.num_nodes()}")

        if randomness_bonus < 0:
            print(f"[INFO]: Target randomness cannot be met")
            return None
        elif randomness_bonus >= 0:
            print(f"[INFO]: Unsorted gadgets")
            self.print_gadget_specs(self.gadget_map)
            self.gadget_map = OrderedDict(sorted(
                self.gadget_map.items(),
                key=lambda item: (item[1]["latency"], item[1]["randomness"], item[1]["area"])
            ))
            print(f"[INFO]: sorted gadgets on basis of their Latency")
            self.print_gadget_specs(self.gadget_map)

            # [Rest of your existing MLRC algorithm logic continues here...]
            # [I'm keeping the complete implementation from your original code]
            
            while(randomness_bonus > 0):
                print(f"[INFO]: Bonus Randomness : {randomness_bonus}")
                min_level = self.find_min_gate_level(min_heap)
                
                if min_level == None:
                    break
                
                top_gadget = next(iter(self.gadget_map))
                print(f"[INFO]: gadget replacement gadget: {top_gadget}")
                top_gadget_specs = self.gadget_map[top_gadget]
                
                replacement_randomness = top_gadget_specs["randomness"]
                replacement_latency = top_gadget_specs["latency"]
                replacement_area = top_gadget_specs["area"]
                print(f"[INFO]: replacement randomness : {replacement_randomness}")
                
                required_randomness = replacement_randomness - initial_randomness
                print(f"[INFO]: Relative randomness required {required_randomness}")
                
                nodes_in_level = self.nodes_by_level[min_level]
                print(f"[INFO]: Number of node in level : {nodes_in_level}")
                
                total_replacement_randomness = required_randomness * len(nodes_in_level)
                print(f"[INFO]: total randomness required : {total_replacement_randomness}")
                
                if total_replacement_randomness <= randomness_bonus:
                    self.processed_node += len(nodes_in_level)
                    randomness_bonus -= total_replacement_randomness
                    for node_expr in nodes_in_level:
                        self.gadget_definition[node_expr] = {
                            "gadget_name": top_gadget,
                            "random_numbers": self.gadget_map[top_gadget]["randomness"]
                        }
                else:
                    # Area reduction logic
                    matching_gadgets = {
                        name: specs
                        for name, specs in self.gadget_map.items()
                        if specs["latency"] == initial_latency and specs["area"] < initial_area
                    }
                    
                    print(f"****************** Reducing the area!!!! **********************")
                    print(f"matching gadget : {matching_gadgets}")
                    
                    node_count = self.and_tree.graph.num_nodes() - self.processed_node
                    print(f"[INFO]: number of unprocessed nodes : {node_count}")
                    print(f"[INFO]: initial area : {initial_area}")
                    min_area = initial_area * node_count
                    print(f"[INFO]: min area of unprocessed nodes : {min_area}")
                    
                    gadget_name = None
                    gadget_replacement_randomness = 0
                    replaceable_node_count = 0
                    
                    for gadget, gadget_spec in matching_gadgets.items():
                        extra_randomness = gadget_spec['randomness'] - initial_randomness
                        print(f"[INFO] : Relative randomness needed for gadget replacement {extra_randomness}")
                        print(f"randomness_bonus : {randomness_bonus}")
                        replaceable_node_count = randomness_bonus // extra_randomness
                        print(f"[INFO] : nodes that can be replaced {replaceable_node_count}")
                        
                        if replaceable_node_count >= node_count:
                            replaceable_node_count = node_count
                        
                        curr_area = replaceable_node_count * initial_area
                        print(f"[INFO]: current area of {replaceable_node_count} is {curr_area}")
                        area = replaceable_node_count * gadget_spec['area']
                        print(f"[INFO]: replaced area of {replaceable_node_count} is {area}")
                        
                        if curr_area > area and area < min_area:
                            gadget_name = gadget
                            min_area = area
                            gadget_replacement_randomness = extra_randomness
                    
                    if replaceable_node_count > 0:
                        print(f"[Replacement INFO]: randomness required for replacement is {extra_randomness}")
                        print(f"[Replacement INFO] : current gadget will be replaced by {gadget_name}")
                        self.processed_node += replaceable_node_count
                        
                        while(replaceable_node_count > 0):
                            if nodes_in_level:
                                for node_expr in nodes_in_level:
                                    self.gadget_definition[node_expr] = {
                                        "gadget_name": gadget_name,
                                        "random_numbers": self.gadget_map[gadget_name]["randomness"]
                                    }
                                    replaceable_node_count -= 1
                                    if(replaceable_node_count == 0):
                                        break
                                level = self.find_min_gate_level(min_heap)
                                if level == None:
                                    break
                                nodes_in_level = self.nodes_by_level[level]
                            else:
                                break
                        
                        randomness_bonus -= gadget_replacement_randomness * replaceable_node_count
                        print("---------------------------------------------------------------------")

            # Fill remaining nodes with initial gadget
            for node in self.and_tree.graph.nodes():
                if self.gadget_definition.get(node) is None:
                    self.gadget_definition[node] = {
                        "gadget_name": initial_gadget_name,
                        "random_numbers": self.gadget_map[initial_gadget_name]["randomness"]
                    }

            # Add gadget definitions
            for node, gadget_spec in self.gadget_definition.items():
                gadget = gadget_spec["gadget_name"]
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

            print(f"GADGET ASSIGNMENT FOR NODES")
            self.print_gadget_definition()
            print(f"UNIQUE DEFINITION TO BE INSERTED IN THE C FILE")
            self.print_unique_gadget_definition()
            
            return self.gadget_definition

# Database Integration Functions
def create_gadget_specs_from_db(d, db_path='gadget_info.db'):
    """
    Create gadget specifications from database for given d
    """
    print(f"[INFO] : Connecting Database for d={d}...")
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
            print(f"[WARN] No entry for {gadget} with d = {d}")
    
    if gadget_specs:
        table_data = []
        for gadget, values in gadget_specs.items():
            table_data.append([gadget, values['latency'], values['randomness'], values['area']])
        print(f"\n[INFO]: Populated DSE MAP for d={d} order")
        print(tabulate(table_data, headers=["Gadget", "Latency", "Randomness", "Area"], tablefmt="grid"))
    
    conn.close()
    return gadget_specs

def compute_total_randomness(gadget_definition):
    """
    Calculates total randomness used for mapping
    """
    if not gadget_definition:
        return float('inf')
    total = sum([spec.get("random_numbers", 0) for spec in gadget_definition.values()])
    return total

def get_best_secure_mapping_with_db(and_tree, min_d, target_randomness, max_d=5, db_path='gadget_info.db'):
    """
    Enhanced mapping function that uses database for gadget specs
    """
    for d_candidate in range(max_d, min_d-1, -1):
        print(f"\n=== Trying d = {d_candidate} ===")
        
        # Get gadget specs from database for this d_candidate
        gadget_specs = create_gadget_specs_from_db(d_candidate, db_path)
        
        if not gadget_specs:
            print(f"✗ d = {d_candidate} - no gadgets available in database")
            continue
        
        # Create MLRC object with current d_candidate and its specific gadget_specs
        mlrc_obj = MLRC(d_candidate, and_tree, gadget_specs)
        
        # Run MLRC algorithm
        try:
            result = mlrc_obj.mlrc(target_randomness)
        except ValueError as e:
            print(f"✗ d = {d_candidate} - Error: {str(e)}")
            continue
        except Exception as e:
            print(f"✗ d = {d_candidate} - Unexpected error: {str(e)}")
            continue
        
        # Get the mapping and check if it's valid
        mapping = getattr(mlrc_obj, "gadget_definition", None)
        
        if mapping is not None and result is not None:
            randomness_used = compute_total_randomness(mapping)
            print(f"  Randomness used: {randomness_used}")
            
            if randomness_used <= target_randomness:
                print(f"✓ Selected d = {d_candidate} - mapping fits within randomness constraint.")
                return mapping, d_candidate
            else:
                print(f"✗ d = {d_candidate} uses too much randomness ({randomness_used} > {target_randomness})")
        else:
            print(f"✗ d = {d_candidate} - no valid mapping found")

    print(f"\n❌ No mapping can be found for any d >= {min_d} with randomness <= {target_randomness}")
    return None, None

def run_enhanced_mlrc_with_db(and_tree, min_d, target_randomness, max_d=5, db_path='gadget_info.db'):
    """
    Main function to run the enhanced MLRC with database integration
    
    Parameters:
      and_tree: your existing AND-tree
      min_d: minimum masking order specified by user
      target_randomness: maximum randomness budget
      max_d: maximum d to try (default 5)
      db_path: path to gadget database
    
    Returns:
      mapping, used_d, success_flag
    """
    print(f"🚀 Starting Enhanced MLRC with Database Integration")
    print(f"   Min d: {min_d}")
    print(f"   Target randomness: {target_randomness}")
    print(f"   Max d to try: {max_d}")
    print(f"   Database: {db_path}")
    
    mapping, used_d = get_best_secure_mapping_with_db(
        and_tree=and_tree,
        min_d=min_d,
        target_randomness=target_randomness,
        max_d=max_d,
        db_path=db_path
    )
    
    if mapping is not None:
        print(f"\n🎯 SUCCESS!")
        print(f"   Final d used: {used_d}")
        print(f"   Total randomness: {compute_total_randomness(mapping)}")
        print(f"   Security level: {used_d}-order masking")
        return mapping, used_d, True
    else:
        print(f"\n❌ FAILED - No feasible solution found")
        return None, None, False

# Backward compatibility functions
def get_best_secure_mapping(and_tree, gadget_map, min_d, target_randomness, max_d=5):
    """
    Original function for backward compatibility (without database)
    """
    for d_candidate in range(max_d, min_d-1, -1):
        print(f"\n=== Trying d = {d_candidate} ===")
        
        mlrc_obj = MLRC(d_candidate, and_tree, gadget_map)
        
        try:
            result = mlrc_obj.mlrc(target_randomness)
        except ValueError as e:
            print(f"✗ d = {d_candidate} - Error: {str(e)}")
            continue
        
        mapping = getattr(mlrc_obj, "gadget_definition", None)
        
        if mapping is not None and result is not None:
            randomness_used = compute_total_randomness(mapping)
            print(f"  Randomness used: {randomness_used}")
            
            if randomness_used <= target_randomness:
                print(f"✓ Selected d = {d_candidate} - mapping fits within randomness constraint.")
                return mapping, d_candidate
            else:
                print(f"✗ d = {d_candidate} uses too much randomness ({randomness_used} > {target_randomness})")
        else:
            print(f"✗ d = {d_candidate} - no valid mapping found")

    print(f"\n❌ No mapping can be found for any d >= {min_d} with randomness <= {target_randomness}")
    return None, None

def run_enhanced_mlrc(and_tree, gadget_map, min_d, target_randomness, max_d=5):
    """
    Original function for backward compatibility (without database)
    """
    print(f"🚀 Starting Enhanced MLRC")
    print(f"   Min d: {min_d}")
    print(f"   Target randomness: {target_randomness}")
    print(f"   Max d to try: {max_d}")
    
    mapping, used_d = get_best_secure_mapping(
        and_tree=and_tree,
        gadget_map=gadget_map,
        min_d=min_d,
        target_randomness=target_randomness,
        max_d=max_d
    )
    
    if mapping is not None:
        print(f"\n🎯 SUCCESS!")
        print(f"   Final d used: {used_d}")
        print(f"   Total randomness: {compute_total_randomness(mapping)}")
        print(f"   Security level: {used_d}-order masking")
        return mapping, used_d, True
    else:
        print(f"\n❌ FAILED - No feasible solution found")
        return None, None, False
