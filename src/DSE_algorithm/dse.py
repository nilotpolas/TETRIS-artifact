from tabulate import tabulate
from ANDCloud.and_cloud import AndCloudGenerator
import re

class DSE:

    GADGET_PARAM_MAP = {}

    """Design space Exploration class"""
    def __init__(self, d, and_tree: AndCloudGenerator, gadget_map):
        self.gadget_definition = {}  # store AND expression mapped to {gadget name mapped to gadget function call}
        self.and_tree = and_tree
        self.nodes_by_level = and_tree.get_level_node() #sore nodes by the level 
        self.gadget_map = gadget_map 
        #   map of gadgets: A dictionary mapping gadget names to latency, randomness and area of that gadget.
        #     e.g., 
        #     {
            
        #         'HPC1' : {"latency" : 2, "randomness" : 2, "area" : 200.67}
        #         'HPC3' : {"latency" : 1, "randomness" : 2, "area" : 908.67}
        #         ...
        #     }


        self.d = d
        self.unique_gadgets_definition = {}
        self.level_latency = {}

    @classmethod
    def set_param_map(cls, param_map):
        if not cls.GADGET_PARAM_MAP:
            cls.GADGET_PARAM_MAP = param_map
            print("[INFO] GADGET_PARAM_MAP initialized.")
        else:
            print("[INFO] GADGET_PARAM_MAP already set. Skipping.")

    @classmethod
    def get_params_for(cls, gadget_name):
        return cls.GADGET_PARAM_MAP.get(gadget_name)
    
    def get_unique_gadgets_definition(self):
        # print("ye kya bakchodi h")
        return self.unique_gadgets_definition

    def get_gadget_definition(self):
        return self.gadget_definition
    
    def get_total_latency(self):
        """
            return the sum of latency of each level in the and tree
        """
        return sum(self.level_latency.values())
    
    def get_total_randomness_and_area(self):
        
        """
        Logic: 

            - For randomness we need to add the randomness of each node in the and_tree if node is hpc3 or hpc2 
            - but if it is commar then we can resue the randomness so we will just add 6 if commar is present in 
            - the design
        
        """
        
        design_randomness = 0
        design_area = 0

        comar_counted = False

        for gadget_info in self.gadget_definition.values():
            # print(f"gadget_info: {gadget_info}")
            gadget_type = gadget_info.get("gadget_name", "")
            # print(f"gadget_Type : {gadget_type}")
            rand = gadget_info.get("radom_numbers", 0)
            # print(f"random used : {rand}")
            if gadget_type == "COMAR":
                if not comar_counted:
                    design_randomness += rand
                    comar_counted = True # counting only once for comar
            else:
                design_randomness += rand
            design_area += self.GADGET_AREA_MAP[gadget_type]

        # print(f"Design randomness: {design_randomness}")
        # print(f"Design area: {design_area}")
        
        return design_randomness, design_area

    def print_gadget_definition(self):
        if isinstance(self.gadget_definition, dict):
            table_data = []
            for expr, gadget_call in self.gadget_definition.items():
                node_no = self.and_tree.node_map.get(expr, "N/A")  # Use "N/A" if expr not in node_map
                # print(f"[DEBUG]: gadget call : {gadget_call}")
                table_data.append((node_no, expr, gadget_call))
            print(tabulate(table_data, headers=["Gate No", "Expression", "Gadget Name", ], tablefmt="grid"))


    def print_unique_gadget_definition(self):
        if isinstance(self.unique_gadgets_definition, dict):
            table_data = []
            for gadget_name, gadget_call in self.unique_gadgets_definition.items():
                table_data.append((gadget_name, gadget_call))
            print(tabulate(table_data, headers=["Gadget", "Gadget Def"], tablefmt="grid"))

    def _filter_to_and_only_levels(self):
        """
        Get AND-only levels from the AND tree (which already computes critical path depth correctly).
        
        The and_cloud.py already has the correct logic to build an AND-only tree.
        We just need to extract it and use it.
        """
        print(f"\n[DSE INFO] Extracting AND-only levels from circuit...")
        
        # Get AND-only levels from and_tree if available
        if hasattr(self.and_tree, 'get_and_only_levels'):
            and_only_levels_map = self.and_tree.get_and_only_levels()
            self.nodes_by_level = and_only_levels_map
            self.DAG_levels = len(and_only_levels_map)
            
            total_and_nodes = sum(len(nodes) for nodes in and_only_levels_map.values())
            
            print(f"[DSE INFO] ✅ AND-only levels extracted from AND tree:")
            print(f"  Critical path depth: {self.DAG_levels}")
            print(f"  Total AND nodes: {total_and_nodes}")
            print(f"  Nodes per level:")
            for level in sorted(and_only_levels_map.keys()):
                print(f"    Level {level}: {len(and_only_levels_map[level])} AND nodes")
        else:
            print(f"[WARN] AND tree does not have get_and_only_levels() method")
            print(f"[WARN] Falling back to filtering by AND-containing levels")
            
            # Fallback: just filter to levels that have AND nodes
            and_only_levels = {}
            level_counter = 0
            
            for level in sorted(self.nodes_by_level.keys()):
                nodes_in_level = self.nodes_by_level[level]
                and_nodes = [n for n in nodes_in_level if self._is_and_node(str(n))]
                
                if and_nodes:
                    level_counter += 1
                    and_only_levels[level_counter] = nodes_in_level
            
            self.nodes_by_level = and_only_levels
            self.DAG_levels = len(and_only_levels)
            
            print(f"[DSE INFO] Filtered to {self.DAG_levels} AND-containing levels")
