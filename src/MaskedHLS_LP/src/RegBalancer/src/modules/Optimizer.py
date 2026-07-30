import rustworkx as rx
from modules.GraphNode import ASTGraphNode, TextGraphNode
import pycparser.c_ast as cast
import re
import json

class GadgetAnalyzer:
    """
    Pass 1 Analysis:
    Identifies HPC3 gadgets that have balancing registers (Dummy nodes) 
    on strictly ONE operand. These are candidates for HPC2 optimization.
    """
    
    def __init__(self, dfg: rx.PyDiGraph):
        self.dfg = dfg

    def get_gadget_id(self, node_index):
        """Extracts the unique Gadget ID from the variable name (e.g. _HPC35 -> 5)"""
        node = self.dfg[node_index]
        if not isinstance(node, ASTGraphNode): return None
        
        ast = node.ast
        name = ""
        if isinstance(ast, cast.Assignment) and isinstance(ast.lvalue, cast.ID):
            name = ast.lvalue.name
        elif isinstance(ast, cast.Decl):
            name = ast.name
            
        # Regex to capture the number after _HPC3
        match = re.search(r'_HPC3(\d+)$', name)
        if match:
            return int(match.group(1)) # Return ID as integer
        return None

    def is_dummy_reg(self, node_index):
        node = self.dfg[node_index]
        return isinstance(node, TextGraphNode) and node.node_text == "Dummy"
    
    def is_randomness(self, node_index):
        # ... (Same randomness check as before) ...
        node = self.dfg[node_index]
        name = ""
        if isinstance(node, ASTGraphNode):
             if isinstance(node.ast, cast.Assignment): name = node.ast.lvalue.name
             elif isinstance(node.ast, cast.Decl): name = node.ast.name
             elif isinstance(node.ast, cast.ID): name = node.name
        elif isinstance(node, TextGraphNode): name = node.node_text
        return "rand" in name.lower()

    def analyze(self, output_file="hpc2_candidates.json"):
        print("[Analyzer] Scanning for HPC2 optimization candidates...")
        
        # 1. Group nodes by ID
        gadget_groups = {}
        for node_idx in self.dfg.node_indices():
            gid = self.get_gadget_id(node_idx)
            if gid is not None:
                if gid not in gadget_groups: gadget_groups[gid] = []
                gadget_groups[gid].append(node_idx)

        candidates = []

        # 2. Check each group
        for gid, members in gadget_groups.items():
            member_indices = set(members)
            delayed_inputs = 0
            direct_inputs = 0
            
            for node_idx in members:
                for src, _, _ in self.dfg.in_edges(node_idx):
                    if src in member_indices or self.is_randomness(src): continue
                    
                    if self.is_dummy_reg(src):
                        delayed_inputs += 1
                    else:
                        direct_inputs += 1
            
            # 3. If mixed (some inputs delayed, some direct), it's a candidate
            if delayed_inputs > 0 and direct_inputs > 0:
                print(f"  [Analyzer] Gadget ID {gid} can be optimized to HPC2.")
                candidates.append(gid)

        # 4. Save to file
        with open(output_file, 'w') as f:
            json.dump(candidates, f)
        print(f"[Analyzer] Saved {len(candidates)} candidates to {output_file}")