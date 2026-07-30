# # import pycparser
# # import rustworkx as rx
# # from rustworkx.visualization import graphviz_draw  #  Import Graphviz rendering
# # import re
# # import graphviz
# # from pycparser import c_ast
# # import sys
# # import os
# # from pycparser import parse_file
# # sys.path.append(os.path.join(os.path.dirname(__file__), 'MaskedHLS_LP', 'src'))

# # from MaskedHLS_LP.src.Inliner.DiGraph import DiGraph
# # from MaskedHLS_LP.src.Inliner.Visitors import FunctionVisitor
# # from MaskedHLS_LP.src.RegBalancer.src.modules.utils import save_graph
# # from tabulate import tabulate


# # import heapq

# # def preprocess_c_code(code):
# #     code = re.sub(r'//.*', '', code)
# #     code = re.sub(r'^\s*#.*', '', code, flags=re.MULTILINE)
# #     return code
# # #  Function to visualize the AST



# # def generate_ast_graph(node, graph, parent=None, counter=[0]):
# #     """
# #     Recursively traverses the AST and adds nodes to Graphviz.

# #     Args:
# #         node (c_ast.Node): The current AST node being processed.
# #         graph (graphviz.Digraph): The Graphviz graph for visualization.
# #         parent (str): The parent node label for connecting edges.
# #         counter (list): A mutable counter to ensure unique node IDs.
# #     """
# #     node_id = f"node{counter[0]}"  # Unique ID for Graphviz
# #     counter[0] += 1

# #     #  Get the token or type for annotation
# #     label = node.__class__.__name__

# #     if isinstance(node, c_ast.ID):  #  Variable name
# #         label += f"\\nID: {node.name}"
# #     elif isinstance(node, c_ast.Constant):  #  Constant value
# #         label += f"\\nConst: {node.value}"
# #     elif isinstance(node, c_ast.BinaryOp):  #  Operator
# #         label += f"\\nOp: {node.op}"

# #     #  Add node to Graphviz with a rounded rectangle
# #     graph.node(node_id, label, shape="ellipse", style="filled", fillcolor="lightblue")

# #     if parent:
# #         graph.edge(parent, node_id)  #  Connect to parent

# #     #  Recursively add child nodes
# #     for child_name, child in node.children():
# #         generate_ast_graph(child, graph, node_id, counter)

# # def visualize_c_ast(code, output_file="ast_tree.png"):
# #     """
# #     Parses C code into an AST and visualizes it with token annotations.

# #     Args:
# #         code (str): The C code to parse.
# #         output_file (str): The output image filename.
# #     """
# #     parser = pycparser.CParser()
# #     ast = parser.parse(code)

# #     #  Create a Graphviz Digraph
# #     graph = graphviz.Digraph(format="png", comment="C AST Visualization")
# #     generate_ast_graph(ast, graph)

# #     #  Save and render the graph
# #     output_path = graph.render(filename=output_file, cleanup=True)
# #     print(f"AST visualization saved as: {output_path}")



# # class AndCloudGenerator(c_ast.NodeVisitor):
# #     def __init__(self):
# #         self.graph = rx.PyDiGraph()
# #         self.and_count = 0
# #         self.var_to_gate = {}
# #         self.node_map = {}
# #         self.level_nodes = {} # store node corresponding to a particular level
# #         self.max_level = 0 # keep track of node level

# #     def get_level_node(self):
# #         # return the 
# #         return self.level_nodes
    
    
# #     def construct_min_heap(self):
# #         node_level = self.get_level_node()
        
# #         min_heap = []

# #         for level, nodes in node_level.items():
# #             gate_count = len(nodes) # number of gate at this level
# #             heapq.heappush(min_heap, (gate_count, level, nodes))

# #         return min_heap


# #     def process_and_operation(self, var_name, rhs_node, and_operands):
# #         """Processes an AND operation and tracks dependencies correctly."""
# #         # and_operands = self.extract_and_operands(rhs_node)
# #         # print(f"extracted and operation : {and_operands}")

# #         # (2 <= len(and_operands) <= 3): is unnecessary as tac will contain atmost 3 input and
# #         # if and_operands and all(isinstance(op, str) for op in and_operands) and (2 <= len(and_operands) <= 3):
# #         expression_str = " & ".join(and_operands)
# #         expression_str = f"{var_name} = " + expression_str
# #         # gate_name = f"g{self.and_count} ({expression_str})"
# #         gate_name = f"{expression_str}"
# #         self.and_count += 1

# #         # print(f"Creating {gate_name} for AND operation: {and_operands}")

# #         gate_index = self.graph.add_node(gate_name)
# #         self.node_map[gate_name] = gate_index

# #         #  Track dependencies using only `var_to_gate`
        
# #         added_edges = set()
# #         max_parent_level = 0 # max level among the input operands
# #         for operand in and_operands:
# #             # print(f"added_edges : {added_edges}")
# #             operand = operand.lstrip("~*-+")
# #             if operand in self.var_to_gate:
# #                 prev_gates = self.var_to_gate[operand] 
# #                 # print(f"\tprevious gates : {prev_gates}")

# #                 # print(f"\tnode map : {self.node_map}")
# #                 # print(f"\tadded_edges : {added_edges}")
# #                 for prev_gate in prev_gates:  # 
# #                     assert prev_gate in self.node_map, f"Error: {prev_gate} not found in node_map"
# #                     if prev_gate not in added_edges:
# #                         # print(f"\t adding edge from {prev_gate} to {gate_name}")
# #                         self.graph.add_edge(self.node_map[prev_gate], gate_index, None)
# #                         added_edges.add(prev_gate)
# #                         max_parent_level = max(max_parent_level, self.get_node_level(prev_gate))
                    
# #         # assign level to new gate 
# #         node_level = max_parent_level + 1
# #         self.max_level = max(self.max_level, node_level) # update tree level


# #         if node_level not in self.level_nodes:
# #             self.level_nodes[node_level] = []
# #         self.level_nodes[node_level].append(gate_name)

# #         #  Store direct gadget dependency for future operations
# #         self.var_to_gate[var_name] = [gate_name]
# #         # print(f"\tvar to gate : {var_name} :{self.var_to_gate[var_name]}")

# #     def visit_Decl(self, node):
# #         if node.init:
# #         # Create a fake Assignment node
# #             assignment_node = c_ast.Assignment(op="=", lvalue=c_ast.ID(node.name), rvalue=node.init)

# #         # Manually call visit_Assignment() to processs dependencies
# #             self.visit_Assignment(assignment_node)

# #         self.generic_visit(node)
        

# #     def get_node_level(self, node):
# #         """find the level of a given node in the AND tree"""
# #         for level, nodes in self.level_nodes.items():
# #             if node in nodes:
# #                 return level
# #         return 0 
    

# #     def visit_Assignment(self, node):
# #         """Tracks assignments and propagates dependencies correctly."""
# #         # print(f"processing assignment node : \n {node}")
# #         if isinstance(node.lvalue, c_ast.ID):
# #             lhs = node.lvalue.name  # Normal variable assignment
# #         elif isinstance(node.lvalue, c_ast.UnaryOp) and node.lvalue.op == '*':
# #             lhs = "*"+node.lvalue.expr.name  # pointer dereference
        
# #         rhs = node.rvalue

# #          #  Case 1: If rhs is an AND operation (2 or 3 operands), process it
# #         and_operands = self.extract_and_operands(rhs)
# #         # print(f"extracted and operands : {and_operands}")
# #         # if and_operands and all(isinstance(op, str) for op in and_operands) and (2 <= len(and_operands) <= 3):
# #         CONST_PATTERN = re.compile(r"^(?:0x[0-9a-fA-F]+|0b[01]+|\d+)$")

# #         # if (and_operands and (2 <= len(and_operands) <= 3) and all(not CONST_PATTERN.match(op) for op in and_operands) ):
# #         if (and_operands and (2 <= len(and_operands) <= 3) and all(not op.startswith("dec_") for op in and_operands)):
# #             self.process_and_operation(lhs, rhs, and_operands)

# #         else:
# #             #  Case 2: Track dependencies if rhs is a variable or complex expression
# #             dependencies = set()

# #             if isinstance(rhs, c_ast.ID) and rhs.name in self.var_to_gate:
# #                 stored_dependency = self.var_to_gate[rhs.name]
# #                 if not isinstance(stored_dependency, list):
# #                     stored_dependency = [stored_dependency]  #  Convert single dependency to list
# #                 dependencies.update(stored_dependency)

# #             elif isinstance(rhs, c_ast.BinaryOp):
# #                 for var in self.get_used_variables(rhs):
# #                     if var in self.var_to_gate:
# #                         stored_dependency = self.var_to_gate[var]
# #                         if not isinstance(stored_dependency, list):
# #                             stored_dependency = [stored_dependency]  #  Convert single dependency to list
# #                         dependencies.update(stored_dependency)

# #             #  Store dependencies in `var_to_gate`
# #             if dependencies:
# #                 if lhs in self.var_to_gate:
# #                     if not isinstance(self.var_to_gate[lhs], list):
# #                         self.var_to_gate[lhs] = [self.var_to_gate[lhs]]  #  Convert to list if needed
# #                     self.var_to_gate[lhs] = list(set(self.var_to_gate[lhs]) | dependencies)  # Enure unique entries
# #                 else:
# #                     self.var_to_gate[lhs] = list(dependencies)

# #         self.generic_visit(node)
    
# #     def get_tree_level(self):
# #         """return the level of the ando cloud tree"""
# #         return self.max_level + 1
    
# #     def get_used_variables(self, node):
# #         """Extracts all variables used in an expression."""
# #         variables = set()
# #         if isinstance(node, c_ast.ID):
# #             variables.add(node.name)
# #         elif isinstance(node, c_ast.BinaryOp):
# #             variables |= self.get_used_variables(node.left)
# #             variables |= self.get_used_variables(node.right)
# #         return variables

# #     def extract_and_operands(self, node):
# #         if isinstance(node, c_ast.BinaryOp) and node.op == '&':
# #             operands = []

# #             left_operands = self.extract_and_operands(node.left) if isinstance(node.left, c_ast.BinaryOp) else [self.get_var_name(node.left)]
# #             # print(f"left operand : {left_operands}")
# #             right_operands = self.extract_and_operands(node.right) if isinstance(node.right, c_ast.BinaryOp) else [self.get_var_name(node.right)]
# #             # print(f"right operand : {right_operands}")
# #             if left_operands and right_operands:
# #                 operands = left_operands + right_operands  

# #             if 2 <= len(operands) <= 3 and all(isinstance(op, str) for op in operands):
# #                 return operands
# #         return None

# #     def get_var_name(self, node):
# #         if isinstance(node, c_ast.ID):
# #             return node.name
# #         elif isinstance(node, c_ast.UnaryOp):
# #             return f"{node.op}{self.get_var_name(node.expr)}"
# #         return None

# #     def visit_FuncDef(self, node):
# #         # print("\n=== Processing Function ===")
# #         self.visit(node.body)

# #     def print_data(self):
# #         for var, gates in self.var_to_gate.items():
# #             print(f"{var} -> {gates}")

# #         if isinstance(self.node_map, dict):
# #             print("[NODE MAP]")
# #             table_data = [(key, value) for key, value in self.node_map.items()]
# #             print(tabulate(table_data, headers=["Key", "Value"], tablefmt="grid"))
# #         # print(f"Node map {self.node_map}")

# #         # print(f"ode level : {self.level_nodes}")
# #         if isinstance(self.level_nodes, dict):
# #             print("[NODE IN EACH LEVEL {LEVEL MAP}]")
# #             table_data = [(key, value) for key, value in self.level_nodes.items()]
# #             print(tabulate(table_data, headers=["Key", "Value"], tablefmt="grid"))


# #         # heap =self.construct_max_heap()
# #         # while (heap):
# #         #     print(heapq.heappop(heap))

# #     def save_and_tree(self, filename):
# #         output_folder = './ANDCloud/AND_tree'
# #         sys.path.append(output_folder)
        
# #         image_path = os.path.join(output_folder, f"and_cloud.png")
        
# #         save_graph(self.graph, image_path)

# # #  Function to Extract Graph and Save It
# # def extract_and_draw_graph(filename, output_file="and_cloud.png"):
# #     # Parse the C file into an AST
# #     ast = parse_file(filename, use_cpp=True)

# #     # Visualize AST (optional)
# #     # print("\n=== Parsed AST ===")
# #     # ast.show()
    
# #     extractor = AndCloudGenerator()
# #     extractor.visit(ast)
# #     extractor.print_data()

# #     # print("\n=== Extracted Graph Data ===")
# #     # print("Nodes:", [extractor.graph[i] for i in range(len(extractor.graph.nodes()))])
# #     # print("Edges:", extractor.graph.edge_list())
# #     if len(extractor.graph.nodes()) == 0:
# #         print("No valid AND operations found in the given C code.")
# #         return

# #     #  Save the Graph as an Image
# #     save_graph(extractor.graph, output_file)

# # # #  Sample C Code Input
# # # c_code = """
# # # void f2(int a, int d, int *z)
# # # {
# # #   int a_inp;
# # #   int d_inp;
# # #   a_inp = a;
# # #   d_inp = d;
# # #   int y;
# # #   int x;
# # #   int p;
# # #   y = a_inp & d_inp;
# # #   p = y & d_inp;
# # #   *z = (y & p) & a_inp;
# # # }

# # # """



# # # test_file_dir = r"C:\Users\nupur\Desktop\mtp_phase2\MTP\LatencyRandomnessMaskedHLS\test_files"
# # # filename = "ex2.c"
# # # output_folder = r"C:\Users\nupur\Desktop\mtp_phase2\MTP\LatencyRandomnessMaskedHLS\and_tree_images"
# # # sys.path.append(test_file_dir)
# # # sys.path.append(output_folder)


# # # # if len(sys.argv) < 2:
# # # #     print("Usage: python script.py <filename>")
# # # #     sys.exit(1)

# # # # filename = sys.argv[1]  # Take filename from the command line
# # # # print(f"Processing file: {filename}")

# # # test_file_path = os.path.join(test_file_dir, filename)
# # # image_path = os.path.join(output_folder, f"and_cloud_{filename}.png")

# # # extract_and_draw_graph(test_file_path, image_path)


# import pycparser
# import rustworkx as rx
# from rustworkx.visualization import graphviz_draw
# import re
# import graphviz
# from pycparser import c_ast
# import sys
# import os
# from pycparser import parse_file
# sys.path.append(os.path.join(os.path.dirname(__file__), 'MaskedHLS_LP', 'src'))

# from MaskedHLS_LP.src.Inliner.DiGraph import DiGraph
# from MaskedHLS_LP.src.Inliner.Visitors import FunctionVisitor
# from MaskedHLS_LP.src.RegBalancer.src.modules.utils import save_graph
# from tabulate import tabulate


# import heapq

# def preprocess_c_code(code):
#     code = re.sub(r'//.*', '', code)
#     code = re.sub(r'^\s*#.*', '', code, flags=re.MULTILINE)
#     return code
# #  Function to visualize the AST



# def generate_ast_graph(node, graph, parent=None, counter=[0]):
#     """
#     Recursively traverses the AST and adds nodes to Graphviz.

#     Args:
#         node (c_ast.Node): The current AST node being processed.
#         graph (graphviz.Digraph): The Graphviz graph for visualization.
#         parent (str): The parent node label for connecting edges.
#         counter (list): A mutable counter to ensure unique node IDs.
#     """
#     node_id = f"node{counter[0]}"  # Unique ID for Graphviz
#     counter[0] += 1

#     #  Get the token or type for annotation
#     label = node.__class__.__name__

#     if isinstance(node, c_ast.ID):  #  Variable name
#         label += f"\\nID: {node.name}"
#     elif isinstance(node, c_ast.Constant):  #  Constant value
#         label += f"\\nConst: {node.value}"
#     elif isinstance(node, c_ast.BinaryOp):  #  Operator
#         label += f"\\nOp: {node.op}"

#     #  Add node to Graphviz with a rounded rectangle
#     graph.node(node_id, label, shape="ellipse", style="filled", fillcolor="lightblue")

#     if parent:
#         graph.edge(parent, node_id)  #  Connect to parent

#     #  Recursively add child nodes
#     for child_name, child in node.children():
#         generate_ast_graph(child, graph, node_id, counter)

# def visualize_c_ast(code, output_file="ast_tree.png"):
#     """
#     Parses C code into an AST and visualizes it with token annotations.

#     Args:
#         code (str): The C code to parse.
#         output_file (str): The output image filename.
#     """
#     parser = pycparser.CParser()
#     ast = parser.parse(code)

#     #  Create a Graphviz Digraph
#     graph = graphviz.Digraph(format="png", comment="C AST Visualization")
#     generate_ast_graph(ast, graph)

#     #  Save and render the graph
#     output_path = graph.render(filename=output_file, cleanup=True)
#     print(f"AST visualization saved as: {output_path}")





# # #  Sample C Code Input
# # c_code = """
# # void f2(int a, int d, int *z)
# # {
# #   int a_inp;
# #   int d_inp;
# #   a_inp = a;
# #   d_inp = d;
# #   int y;
# #   int x;
# #   int p;
# #   y = a_inp & d_inp;
# #   p = y & d_inp;
# #   *z = (y & p) & a_inp;
# # }

# # """



# # test_file_dir = r"C:\Users\nupur\Desktop\mtp_phase2\MTP\LatencyRandomnessMaskedHLS\test_files"
# # filename = "ex2.c"
# # output_folder = r"C:\Users\nupur\Desktop\mtp_phase2\MTP\LatencyRandomnessMaskedHLS\and_tree_images"
# # sys.path.append(test_file_dir)
# # sys.path.append(output_folder)


# # # if len(sys.argv) < 2:
# # #     print("Usage: python script.py <filename>")
# # #     sys.exit(1)

# # # filename = sys.argv[1]  # Take filename from the command line
# # # print(f"Processing file: {filename}")

# # test_file_path = os.path.join(test_file_dir, filename)
# # image_path = os.path.join(output_folder, f"and_cloud_{filename}.png")

# # extract_and_draw_graph(test_file_path, image_path)


import pycparser
import rustworkx as rx
from rustworkx.visualization import graphviz_draw  #  Import Graphviz rendering
import re
import graphviz
from pycparser import c_ast
import sys
import os
from pycparser import parse_file
sys.path.append(os.path.join(os.path.dirname(__file__), 'MaskedHLS_LP', 'src'))

from MaskedHLS_LP.src.Inliner.DiGraph import DiGraph
from MaskedHLS_LP.src.Inliner.Visitors import FunctionVisitor
from MaskedHLS_LP.src.RegBalancer.src.modules.utils import save_graph
from tabulate import tabulate


import heapq

def preprocess_c_code(code):
    code = re.sub(r'//.*', '', code)
    code = re.sub(r'^\s*#.*', '', code, flags=re.MULTILINE)
    return code
#  Function to visualize the AST



def generate_ast_graph(node, graph, parent=None, counter=[0]):
    """
    Recursively traverses the AST and adds nodes to Graphviz.

    Args:
        node (c_ast.Node): The current AST node being processed.
        graph (graphviz.Digraph): The Graphviz graph for visualization.
        parent (str): The parent node label for connecting edges.
        counter (list): A mutable counter to ensure unique node IDs.
    """
    node_id = f"node{counter[0]}"  # Unique ID for Graphviz
    counter[0] += 1

    #  Get the token or type for annotation
    label = node.__class__.__name__

    if isinstance(node, c_ast.ID):  #  Variable name
        label += f"\\nID: {node.name}"
    elif isinstance(node, c_ast.Constant):  #  Constant value
        label += f"\\nConst: {node.value}"
    elif isinstance(node, c_ast.BinaryOp):  #  Operator
        label += f"\\nOp: {node.op}"

    #  Add node to Graphviz with a rounded rectangle
    graph.node(node_id, label, shape="ellipse", style="filled", fillcolor="lightblue")

    if parent:
        graph.edge(parent, node_id)  #  Connect to parent

    #  Recursively add child nodes
    for child_name, child in node.children():
        generate_ast_graph(child, graph, node_id, counter)

def visualize_c_ast(code, output_file="ast_tree.png"):
    """
    Parses C code into an AST and visualizes it with token annotations.

    Args:
        code (str): The C code to parse.
        output_file (str): The output image filename.
    """
    parser = pycparser.CParser()
    ast = parser.parse(code)

    #  Create a Graphviz Digraph
    graph = graphviz.Digraph(format="png", comment="C AST Visualization")
    generate_ast_graph(ast, graph)

    #  Save and render the graph
    output_path = graph.render(filename=output_file, cleanup=True)
    print(f"AST visualization saved as: {output_path}")



class AndCloudGenerator(c_ast.NodeVisitor):
    def __init__(self):
        self.graph = rx.PyDiGraph()
        self.and_count = 0
        self.var_to_gate = {}
        self.node_map = {}
        self.level_nodes = {} # store node corresponding to a particular level
        self.max_level = 0 # keep track of node level

    def get_level_node(self):
        # return the 
        return self.level_nodes
    
    
    def construct_min_heap(self):
        node_level = self.get_level_node()
        
        min_heap = []

        for level, nodes in node_level.items():
            gate_count = len(nodes) # number of gate at this level
            heapq.heappush(min_heap, (gate_count, level, nodes))

        return min_heap


    def process_and_operation(self, var_name, rhs_node, and_operands):
        """Processes an AND operation and tracks dependencies correctly."""
        # and_operands = self.extract_and_operands(rhs_node)
        # print(f"extracted and operation : {and_operands}")

        # (2 <= len(and_operands) <= 3): is unnecessary as tac will contain atmost 3 input and
        # if and_operands and all(isinstance(op, str) for op in and_operands) and (2 <= len(and_operands) <= 3):
        expression_str = " & ".join(and_operands)
        expression_str = f"{var_name} = " + expression_str
        # gate_name = f"g{self.and_count} ({expression_str})"
        gate_name = f"{expression_str}"
        self.and_count += 1

        # print(f"Creating {gate_name} for AND operation: {and_operands}")

        gate_index = self.graph.add_node(gate_name)
        self.node_map[gate_name] = gate_index

        #  Track dependencies using only `var_to_gate`
        
        added_edges = set()
        max_parent_level = 0 # max level among the input operands
        for operand in and_operands:
            # print(f"added_edges : {added_edges}")
            operand = operand.lstrip("~*-+")
            if operand in self.var_to_gate:
                prev_gates = self.var_to_gate[operand] 
                # print(f"\tprevious gates : {prev_gates}")

                # print(f"\tnode map : {self.node_map}")
                # print(f"\tadded_edges : {added_edges}")
                for prev_gate in prev_gates:  # 
                    assert prev_gate in self.node_map, f"Error: {prev_gate} not found in node_map"
                    if prev_gate not in added_edges:
                        # print(f"\t adding edge from {prev_gate} to {gate_name}")
                        self.graph.add_edge(self.node_map[prev_gate], gate_index, None)
                        added_edges.add(prev_gate)
                        max_parent_level = max(max_parent_level, self.get_node_level(prev_gate))
                    
        # assign level to new gate 
        node_level = max_parent_level + 1
        self.max_level = max(self.max_level, node_level) # update tree level


        if node_level not in self.level_nodes:
            self.level_nodes[node_level] = []
        self.level_nodes[node_level].append(gate_name)

        #  Store direct gadget dependency for future operations
        self.var_to_gate[var_name] = [gate_name]
        # print(f"\tvar to gate : {var_name} :{self.var_to_gate[var_name]}")

    def visit_Decl(self, node):
        if node.init:
        # Create a fake Assignment node
            assignment_node = c_ast.Assignment(op="=", lvalue=c_ast.ID(node.name), rvalue=node.init)

        # Manually call visit_Assignment() to processs dependencies
            self.visit_Assignment(assignment_node)

        self.generic_visit(node)
        

    def get_node_level(self, node):
        """find the level of a given node in the AND tree"""
        for level, nodes in self.level_nodes.items():
            if node in nodes:
                return level
        return 0 
    

    def visit_Assignment(self, node):
        """Tracks assignments and propagates dependencies correctly."""
        if isinstance(node.lvalue, c_ast.ID):
            lhs = node.lvalue.name  # Normal variable assignment
        elif isinstance(node.lvalue, c_ast.UnaryOp) and node.lvalue.op == '*':
            lhs = "*"+node.lvalue.expr.name  # pointer dereference
        
        rhs = node.rvalue

        # Case 1: If rhs is an AND operation (2 or 3 operands), process it as a graph node
        and_operands = self.extract_and_operands(rhs)
        CONST_PATTERN = re.compile(r"^(?:0x[0-9a-fA-F]+|0b[01]+|\d+)$")

        if (and_operands and (2 <= len(and_operands) <= 3) and all(not op.startswith("dec_") for op in and_operands)):
            self.process_and_operation(lhs, rhs, and_operands)

        else:
            # Case 2: Track dependencies for ANY other expression (NOT, XOR, assignments)
            # This bridges the dependencies without creating physical nodes in the graph.
            dependencies = set()

            # Extract ALL variables from the right-hand side, regardless of operators used
            for var in self.get_used_variables(rhs):
                if var in self.var_to_gate:
                    stored_dependency = self.var_to_gate[var]
                    if not isinstance(stored_dependency, list):
                        stored_dependency = [stored_dependency]  # Convert single dependency to list
                    dependencies.update(stored_dependency)

            # Store dependencies in `var_to_gate` so downstream AND gates can find them
            if dependencies:
                if lhs in self.var_to_gate:
                    if not isinstance(self.var_to_gate[lhs], list):
                        self.var_to_gate[lhs] = [self.var_to_gate[lhs]]  # Convert to list if needed
                    self.var_to_gate[lhs] = list(set(self.var_to_gate[lhs]) | dependencies)  # Ensure unique entries
                else:
                    self.var_to_gate[lhs] = list(dependencies)

        self.generic_visit(node)
    
    def get_tree_level(self):
        """return the level of the ando cloud tree"""
        return self.max_level + 1
    
    def get_used_variables(self, node):
        """Extracts all variables used in an expression."""
        variables = set()
        if isinstance(node, c_ast.ID):
            variables.add(node.name)
        elif isinstance(node, c_ast.BinaryOp):
            variables |= self.get_used_variables(node.left)
            variables |= self.get_used_variables(node.right)
        elif isinstance(node, c_ast.UnaryOp):               # <-- ADDED THIS
            variables |= self.get_used_variables(node.expr) # <-- ADDED THIS
        return variables

    def extract_and_operands(self, node):
        if isinstance(node, c_ast.BinaryOp) and node.op == '&':
            operands = []

            left_operands = self.extract_and_operands(node.left) if isinstance(node.left, c_ast.BinaryOp) else [self.get_var_name(node.left)]
            # print(f"left operand : {left_operands}")
            right_operands = self.extract_and_operands(node.right) if isinstance(node.right, c_ast.BinaryOp) else [self.get_var_name(node.right)]
            # print(f"right operand : {right_operands}")
            if left_operands and right_operands:
                operands = left_operands + right_operands  

            if 2 <= len(operands) <= 3 and all(isinstance(op, str) for op in operands):
                return operands
        return None

    def get_var_name(self, node):
        if isinstance(node, c_ast.ID):
            return node.name
        elif isinstance(node, c_ast.UnaryOp):
            return f"{node.op}{self.get_var_name(node.expr)}"
        return None

    def visit_FuncDef(self, node):
        # print("\n=== Processing Function ===")
        self.visit(node.body)

    def print_data(self):
        for var, gates in self.var_to_gate.items():
            print(f"{var} -> {gates}")

        if isinstance(self.node_map, dict):
            print("[NODE MAP]")
            table_data = [(key, value) for key, value in self.node_map.items()]
            print(tabulate(table_data, headers=["Key", "Value"], tablefmt="grid"))
        # print(f"Node map {self.node_map}")

        # print(f"ode level : {self.level_nodes}")
        if isinstance(self.level_nodes, dict):
            print("[NODE IN EACH LEVEL {LEVEL MAP}]")
            table_data = [(key, value) for key, value in self.level_nodes.items()]
            print(tabulate(table_data, headers=["Key", "Value"], tablefmt="grid"))


        # heap =self.construct_max_heap()
        # while (heap):
        #     print(heapq.heappop(heap))

    def save_and_tree(self, filename):
        output_folder = './ANDCloud/AND_tree'
        sys.path.append(output_folder)
        
        image_path = os.path.join(output_folder, f"and_cloud.png")
        
        save_graph(self.graph, image_path)

class AndXorCloudGenerator(c_ast.NodeVisitor):
    def __init__(self):
        self.graph = rx.PyDiGraph()
        self.node_count = 0
        self.var_to_gate = {}
        self.node_map = {}
        self.level_nodes = {} # store node corresponding to a particular level
        self.max_level = 0 # keep track of node level

    def get_level_node(self):
        # return the 
        print(f"node level : {self.level_nodes}")
        return self.level_nodes
    
    def get_and_only_levels(self):
        """
        Extract ONLY AND nodes, grouped by their dependency depth.
        Returns a dict mapping depth → list of AND nodes at that depth.
        
        This is the correct critical path computation:
        - AND nodes with only XOR inputs → depth 1
        - AND nodes with depth-1 inputs → depth 2
        - etc.
        """
        print(f"\n[AND_CLOUD] Computing AND-only levels by dependency depth...")
        
        # Step 1: Extract all AND nodes and compute their depths
        and_node_depth = {}
        var_depth = {}
        
        # Initialize: all non-AND variables have depth 0
        for level in sorted(self.level_nodes.keys()):
            for node_expr in self.level_nodes[level]:
                node_str = str(node_expr)
                if '=' not in node_str:
                    continue
                
                lhs = node_str.split('=')[0].strip()
                
                # XOR and other non-AND operations have depth 0
                if '&' not in node_str:
                    var_depth[lhs] = 0
        
        # Step 2: Iteratively compute AND node depths
        max_iterations = 100
        iteration = 0
        
        while iteration < max_iterations:
            iteration += 1
            newly_computed = 0
            
            for level in sorted(self.level_nodes.keys()):
                for node_expr in self.level_nodes[level]:
                    node_str = str(node_expr)
                    
                    if '=' not in node_str or '&' not in node_str:
                        continue  # Not an AND node
                    
                    if node_str in and_node_depth:
                        continue  # Already computed
                    
                    lhs, rhs = node_str.split('=')
                    lhs = lhs.strip()
                    rhs = rhs.strip()
                    
                    # Extract operands from "a & b"
                    match = re.search(r'(\w+)\s*&\s*(\w+)', rhs)
                    if not match:
                        and_node_depth[node_str] = 1
                        var_depth[lhs] = 1
                        newly_computed += 1
                        continue
                    
                    op_a, op_b = match.groups()
                    
                    # Check if both operands have known depths
                    if op_a in var_depth and op_b in var_depth:
                        depth = max(var_depth[op_a], var_depth[op_b]) + 1
                        and_node_depth[node_str] = depth
                        var_depth[lhs] = depth
                        newly_computed += 1
            
            if newly_computed == 0:
                break  # No more updates
        
        # Step 3: Group AND nodes by depth
        depth_to_nodes = {}
        for level in sorted(self.level_nodes.keys()):
            for node_expr in self.level_nodes[level]:
                node_str = str(node_expr)
                
                if node_str in and_node_depth:
                    depth = and_node_depth[node_str]
                    if depth not in depth_to_nodes:
                        depth_to_nodes[depth] = []
                    depth_to_nodes[depth].append(node_expr)
        
        # Step 4: Print results
        total_and = len(and_node_depth)
        print(f"[AND_CLOUD] ✅ AND-only levels by dependency depth:")
        print(f"  Total AND nodes: {total_and}")
        print(f"  Depth levels: {len(depth_to_nodes)}")
        for depth in sorted(depth_to_nodes.keys()):
            print(f"    Depth {depth}: {len(depth_to_nodes[depth])} AND nodes")
        
        return depth_to_nodes
      
    def construct_min_heap(self):
        node_level = self.get_level_node()
        
        min_heap = []

        for level, nodes in node_level.items():
            gate_count = len(nodes) # number of gate at this level
            heapq.heappush(min_heap, (gate_count, level, nodes))

        return min_heap
    def process_operation(self, var_name, rhs_node, operands, operator):
        """Processes either an AND or XOR operation."""
        expression_str = f" {operator} ".join(operands)
        expression_str = f"{var_name} = " + expression_str
        gate_name = f"{expression_str}"

        self.node_count += 1

        # print(f"Creating {gate_name} for AND operation: {and_operands}")

        gate_index = self.graph.add_node(gate_name)
        self.node_map[gate_name] = gate_index

        #  Track dependencies using only `var_to_gate`
        
        added_edges = set()
        max_parent_level = 0 # max level among the input operands
        for operand in operands:
            # print(f"added_edges : {added_edges}")
            operand = operand.lstrip("~*-+")
            if operand in self.var_to_gate:
                prev_gates = self.var_to_gate[operand] 
                # print(f"\tprevious gates : {prev_gates}")

                # print(f"\tnode map : {self.node_map}")
                # print(f"\tadded_edges : {added_edges}")
                for prev_gate in prev_gates:  # 
                    assert prev_gate in self.node_map, f"Error: {prev_gate} not found in node_map"
                    if prev_gate not in added_edges:
                        # print(f"\t adding edge from {prev_gate} to {gate_name}")
                        self.graph.add_edge(self.node_map[prev_gate], gate_index, None)
                        added_edges.add(prev_gate)
                        max_parent_level = max(max_parent_level, self.get_node_level(prev_gate))
                    
        # assign level to new gate 
        node_level = max_parent_level + 1
        self.max_level = max(self.max_level, node_level) # update tree level


        if node_level not in self.level_nodes:
            self.level_nodes[node_level] = []
        self.level_nodes[node_level].append(gate_name)

        #  Store direct gadget dependency for future operations
        self.var_to_gate[var_name] = [gate_name]
        # print(f"\tvar to gate : {var_name} :{self.var_to_gate[var_name]}")

    def visit_Decl(self, node):
        if node.init:
        # Create a fake Assignment node
            assignment_node = c_ast.Assignment(op="=", lvalue=c_ast.ID(node.name), rvalue=node.init)

        # Manually call visit_Assignment() to processs dependencies
            self.visit_Assignment(assignment_node)

        self.generic_visit(node)
        
    def get_node_level(self, node):
        """find the ACTUAL AND-only level of a given node in the AND tree"""
        for level, nodes in self.level_nodes.items():
            if node in nodes:
                return level
        return 0
    
    def get_and_only_levels(self):
        """
        Extract ONLY AND nodes, grouped by their dependency depth.
        Properly passes depth transparently through XOR/NOT nodes.
        """
        print(f"\n[AND_CLOUD] Computing AND-only levels by dependency depth...")
        
        and_node_depth = {}
        var_depth = {}  # Tracks the max AND-depth for EVERY variable
        
        # Process in topological order (provided by level_nodes keys)
        for level in sorted(self.level_nodes.keys()):
            for node_expr in self.level_nodes[level]:
                node_str = str(node_expr)
                if '=' not in node_str:
                    continue
                
                lhs, rhs = node_str.split('=', 1)
                lhs = lhs.strip()
                rhs = rhs.strip()
                
                # Extract variables from RHS, ignoring all operators
                operands = re.findall(r'[a-zA-Z_]\w*', rhs)
                
                max_input_depth = 0
                for op in operands:
                    if op in var_depth:
                        max_input_depth = max(max_input_depth, var_depth[op])
                
                if '&' in rhs:
                    # AND node increases the depth
                    depth = max_input_depth + 1
                    and_node_depth[node_str] = depth
                    var_depth[lhs] = depth
                else:
                    # XOR/NOT nodes inherit the max depth transparently
                    var_depth[lhs] = max_input_depth

        # Group AND nodes by depth
        depth_to_nodes = {}
        for node_str, depth in and_node_depth.items():
            if depth not in depth_to_nodes:
                depth_to_nodes[depth] = []
            depth_to_nodes[depth].append(node_str)
        
        total_and = len(and_node_depth)
        print(f"[AND_CLOUD] ✅ AND-only levels by dependency depth:")
        print(f"  Total AND nodes: {total_and}")
        print(f"  Depth levels: {len(depth_to_nodes)}")
        for depth in sorted(depth_to_nodes.keys()):
            print(f"    Depth {depth}: {len(depth_to_nodes[depth])} AND nodes")
        
        return depth_to_nodes
    
    def visit_Assignment(self, node):
        """Tracks assignments and propagates dependencies correctly."""
        if isinstance(node.lvalue, c_ast.ID):
            lhs = node.lvalue.name  # Normal variable assignment
        elif isinstance(node.lvalue, c_ast.UnaryOp) and node.lvalue.op == '*':
            lhs = "*"+node.lvalue.expr.name  # pointer dereference
        
        rhs = node.rvalue

         #  Case 1: If rhs is an AND or XOR operation (2 or 3 operands), process it
        operands, operators = self.extract_binary_operands(rhs)
        # print(f"extracted and operands : {operands}")
        # if operands and all(isinstance(op, str) for op in operands) and (2 <= len(operands) <= 3):
        CONST_PATTERN = re.compile(r"^(?:0x[0-9a-fA-F]+|0b[01]+|\d+)$")

        # if (operands and (2 <= len(operands) <= 3) and all(not CONST_PATTERN.match(op) for op in operands) ):
        if (operands and (2 <= len(operands) <= 3) and all(not op.startswith("dec_") for op in operands)):
            self.process_operation(lhs, rhs, operands, operators)
        
        #  Case 2: If rhs is a NOT operation, create a gate node for it
        elif isinstance(rhs, c_ast.UnaryOp) and rhs.op == '!':
            operand_name = self.get_var_name(rhs.expr)
            operand_name = operand_name.lstrip("~*-+") if operand_name else None
            
            if operand_name:
                # Create a NOT gate node
                gate_name = f"{lhs} = !{operand_name}"
                gate_index = self.graph.add_node(gate_name)
                self.node_map[gate_name] = gate_index
                
                added_edges = set()
                max_parent_level = 0
                
                # Connect to parent if it exists in var_to_gate
                if operand_name in self.var_to_gate:
                    prev_gates = self.var_to_gate[operand_name]
                    for prev_gate in prev_gates:
                        if prev_gate in self.node_map and prev_gate not in added_edges:
                            self.graph.add_edge(self.node_map[prev_gate], gate_index, None)
                            added_edges.add(prev_gate)
                            max_parent_level = max(max_parent_level, self.get_node_level(prev_gate))
                
                # Assign level
                node_level = max_parent_level + 1
                self.max_level = max(self.max_level, node_level)
                
                if node_level not in self.level_nodes:
                    self.level_nodes[node_level] = []
                self.level_nodes[node_level].append(gate_name)
                
                # Store dependency
                self.var_to_gate[lhs] = [gate_name]

        else:
            #  Case 3: Track dependencies if rhs is a variable or other expression
            dependencies = set()

            if isinstance(rhs, c_ast.ID) and rhs.name in self.var_to_gate:
                stored_dependency = self.var_to_gate[rhs.name]
                if not isinstance(stored_dependency, list):
                    stored_dependency = [stored_dependency]  #  Convert single dependency to list
                dependencies.update(stored_dependency)

            elif isinstance(rhs, c_ast.BinaryOp):
                for var in self.get_used_variables(rhs):
                    if var in self.var_to_gate:
                        stored_dependency = self.var_to_gate[var]
                        if not isinstance(stored_dependency, list):
                            stored_dependency = [stored_dependency]  #  Convert single dependency to list
                        dependencies.update(stored_dependency)

            #  Store dependencies in `var_to_gate`
            if dependencies:
                if lhs in self.var_to_gate:
                    if not isinstance(self.var_to_gate[lhs], list):
                        self.var_to_gate[lhs] = [self.var_to_gate[lhs]]  #  Convert to list if needed
                    self.var_to_gate[lhs] = list(set(self.var_to_gate[lhs]) | dependencies)  # Enure unique entries
                else:
                    self.var_to_gate[lhs] = list(dependencies)

        self.generic_visit(node)
    
    def get_tree_level(self):
        """return the level of the ando cloud tree"""
        return self.max_level + 1
    
    def get_used_variables(self, node):
        """Extracts all variables used in an expression."""
        variables = set()
        if isinstance(node, c_ast.ID):
            variables.add(node.name)
        elif isinstance(node, c_ast.BinaryOp):
            variables |= self.get_used_variables(node.left)
            variables |= self.get_used_variables(node.right)
        elif isinstance(node, c_ast.UnaryOp):               # <-- ADDED THIS
            variables |= self.get_used_variables(node.expr) # <-- ADDED THIS
        return variables

    def extract_binary_operands(self, node):
        # Check for both AND (&) and XOR (^) operators
        if isinstance(node, c_ast.BinaryOp) and node.op in ['&', '^']:
            operands = []
            # Recursively extract operands for nested operations
            left_operands = self.extract_binary_operands(node.left) if isinstance(node.left, c_ast.BinaryOp) else [self.get_var_name(node.left)]
            right_operands = self.extract_binary_operands(node.right) if isinstance(node.right, c_ast.BinaryOp) else [self.get_var_name(node.right)]
            
            if left_operands and right_operands:
                operands = left_operands + right_operands
                # Maintain the 2-3 operand constraint from the original source [2]
                if 2 <= len(operands) <= 3 and all(isinstance(op, str) for op in operands):
                    return operands, node.op # Return operands and the operator used
        return None, None
    
    def extract_and_operands(self, node):
        if isinstance(node, c_ast.BinaryOp) and node.op == '&':
            operands = []

            left_operands = self.extract_and_operands(node.left) if isinstance(node.left, c_ast.BinaryOp) else [self.get_var_name(node.left)]
            # print(f"left operand : {left_operands}")
            right_operands = self.extract_and_operands(node.right) if isinstance(node.right, c_ast.BinaryOp) else [self.get_var_name(node.right)]
            # print(f"right operand : {right_operands}")
            if left_operands and right_operands:
                operands = left_operands + right_operands  

            if 2 <= len(operands) <= 3 and all(isinstance(op, str) for op in operands):
                return operands
        return None

    def get_var_name(self, node):
        if isinstance(node, c_ast.ID):
            return node.name
        elif isinstance(node, c_ast.UnaryOp):
            return f"{node.op}{self.get_var_name(node.expr)}"
        return None

    def visit_FuncDef(self, node):
        # print("\n=== Processing Function ===")
        self.visit(node.body)

    def print_data(self):
        for var, gates in self.var_to_gate.items():
            print(f"{var} -> {gates}")

        if isinstance(self.node_map, dict):
            print("[NODE MAP]")
            table_data = [(key, value) for key, value in self.node_map.items()]
            print(tabulate(table_data, headers=["Key", "Value"], tablefmt="grid"))
        # print(f"Node map {self.node_map}")

        # print(f"ode level : {self.level_nodes}")
        if isinstance(self.level_nodes, dict):
            print("[NODE IN EACH LEVEL {LEVEL MAP}]")
            table_data = [(key, value) for key, value in self.level_nodes.items()]
            print(tabulate(table_data, headers=["Key", "Value"], tablefmt="grid"))


        # heap =self.construct_max_heap()
        # while (heap):
        #     print(heapq.heappop(heap))
    
    def save_and_xor_graph(self, filename):
        def node_attr(node):
            if '&' in node:
                return {
                    "label": node,
                    "fillcolor": "lightgreen",
                    "style": "filled",
                }
            elif '^' in node:
                return {
                    "label": node,
                    "fillcolor": "mediumpurple1",
                    "style": "filled",
                }
            
            # 3. CRITICAL: Always return a string for 'label' 
            # Never return the 'node' object itself or a dictionary without 'label'
            return {}
        
        # Define the output path
        output_folder = './ANDCloud/AND_Xor_tree'
        os.makedirs(output_folder, exist_ok=True)
        image_path = os.path.join(output_folder, filename)
        
        # Let rustworkx handle the file output directly
        # This is more stable than manually saving the figure object
        graphviz_draw(
            self.graph, 
            node_attr_fn=node_attr, 
            edge_attr_fn=lambda e: {"label": str(e)} if e else {}, 
            method="dot",
            filename=image_path
        )
        print(f"[INFO] XOR graph successfully saved to: {image_path}")
        # save the file using the provided filename
        # output_folder = './ANDCloud/AND_tree'
        # sys.path.append(output_folder)
        
        # image_path = os.path.join(output_folder, filename)
        # print(f"[INFO]:Saving XOR graph to: {image_path}")

        # fig.save(image_path)
        # print(f"[INFO] XOR graph saved as: {image_path}")

    def save_and_tree(self, filename):
        output_folder = './ANDCloud/AND_Xor_tree'
        sys.path.append(output_folder)
        
        image_path = os.path.join(output_folder, filename)
        print(f"[INFO]:Saving AND_Xor tree graph to: {image_path}")
        
        save_graph(self.graph, image_path)

    # def save_and_tree(self, filename):
    #     output_folder = './ANDCloud/AND_tree'
    #     # Ensure the directory exists just in case
    #     os.makedirs(output_folder, exist_ok=True) 
        
    #     # 1. Extract 'output.c' from '/home/.../output.c'
    #     base_name = os.path.basename(filename) 
        
    #     # 2. Split 'output' and '.c', then create 'output.png'
    #     name_only, _ = os.path.splitext(base_name)
    #     image_filename = f"{name_only}.png"
        
    #     # 3. Join securely. This will result in: ./ANDCloud/AND_tree/output.png
    #     image_path = os.path.join(output_folder, image_filename)
        
    #     print(f"[INFO]: Saving AND tree graph to: {image_path}")
        
    #     save_graph(self.graph, image_path)

#  Function to Extract Graph and Save It
def extract_and_xor_draw_graph(filename, output_file="and_xor_cloud.png"):
    # Parse the C file into an AST
    ast = parse_file(filename, use_cpp=True)

    # Visualize AST (optional)
    print("\n=== Parsed AST ===")
    ast.show()
    
    extractor = AndXorCloudGenerator()
    extractor.visit(ast)
    extractor.print_data()

    # print("\n=== Extracted Graph Data ===")
    # print("Nodes:", [extractor.graph[i] for i in range(len(extractor.graph.nodes()))])
    # print("Edges:", extractor.graph.edge_list())
    if len(extractor.graph.nodes()) == 0:
        print("No valid AND operations found in the given C code.")
        return

    #  Save the Graph as an Image
    save_graph(extractor.graph, output_file)

#  Function to Extract Graph and Save It
def extract_and_draw_graph(filename, output_file="and_cloud.png"):
    # Parse the C file into an AST
    ast = parse_file(filename, use_cpp=True)

    # Visualize AST (optional)
    # print("\n=== Parsed AST ===")
    # ast.show()
    
    extractor = AndCloudGenerator()
    extractor.visit(ast)
    extractor.print_data()

    # print("\n=== Extracted Graph Data ===")
    # print("Nodes:", [extractor.graph[i] for i in range(len(extractor.graph.nodes()))])
    # print("Edges:", extractor.graph.edge_list())
    if len(extractor.graph.nodes()) == 0:
        print("No valid AND operations found in the given C code.")
        return

    #  Save the Graph as an Image
    save_graph(extractor.graph, output_file)

# #  Sample C Code Input
# c_code = """
# void f2(int a, int d, int *z)
# {
#   int a_inp;
#   int d_inp;
#   a_inp = a;
#   d_inp = d;
#   int y;
#   int x;
#   int p;
#   y = a_inp & d_inp;
#   p = y & d_inp;
#   *z = (y & p) & a_inp;
# }

# """



# test_file_dir = r"C:\Users\nupur\Desktop\mtp_phase2\MTP\LatencyRandomnessMaskedHLS\test_files"
# filename = "ex2.c"
# output_folder = r"C:\Users\nupur\Desktop\mtp_phase2\MTP\LatencyRandomnessMaskedHLS\and_tree_images"
# sys.path.append(test_file_dir)
# sys.path.append(output_folder)


# # if len(sys.argv) < 2:
# #     print("Usage: python script.py <filename>")
# #     sys.exit(1)

# # filename = sys.argv[1]  # Take filename from the command line
# # print(f"Processing file: {filename}")

# test_file_path = os.path.join(test_file_dir, filename)
# image_path = os.path.join(output_folder, f"and_cloud_{filename}.png")

# extract_and_draw_graph(test_file_path, image_path)
