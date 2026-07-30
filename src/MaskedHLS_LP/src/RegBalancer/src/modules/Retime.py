# import rustworkx as rx
# import re
# from modules.GraphNode import ASTGraphNode, TextGraphNode
# from rustworkx.visualization import graphviz_draw
# from collections import deque
# from pycparser import c_ast
# from modules.Visitor import AddRegs
# from modules.utils import get_source_index as utils_get_source_index, get_sink_index as utils_get_sink_index

# # Helper to build a FuncCall AST node for a single-argument call (used for reg/regPR)
# def get_func_call_ast(func_name, expr):
#     """
#     Create a pycparser FuncCall node that represents: func_name(expr)
#     If expr is None, returns a FuncCall with no args.
#     """
#     name = c_ast.ID(func_name)
#     args = None if expr is None else c_ast.ExprList([expr])
#     return c_ast.FuncCall(name, args)


# class RetimeDFG():
#     """
#     @class RetimeDFG
#     @brief A class for retiming a data flow graph (DFG) to optimize its performance.

#     This class handles the retiming of a data flow graph represented using the `rustworkx` library. It performs various
#     operations including setting source and sink weights, updating retiming labels, adding register calls, and solving
#     constraint graphs.

#     @details
#         The `RetimeDFG` class includes methods for calculating retimed designs, creating constraint graphs, and updating
#         edge weights. It also supports debugging outputs to trace the computation steps.
#     """

#     def __init__(self, dfg: rx.PyDiGraph, debug: bool = False) -> None:
#         """
#         @brief Initializes the RetimeDFG instance.

#         @param dfg (rx.PyDiGraph): The data flow graph to be retimed.
#         @param debug (bool, optional): Whether to enable debugging output. Defaults to False.
#         """
#         self.dfg = dfg
#         self.w_matrix = None
#         self.m_matrix = None
#         # Create constraint graph and add N+1 nodes to it
#         self.constraint_graph = rx.PyDiGraph()
#         num_nodes = self.dfg.num_nodes()
#         self.constraint_graph.add_nodes_from(range(num_nodes+1))
#         self.target_period = 1
#         self.solution = {}
#         self.retimed_design = None
#         self.debug = debug
#         self.feasibilityConstraints = 0
#         self.criticalPathConstraints = 0
#         self.maxPathWeight = 0

#     @staticmethod
#     def get_sink_index(dfg: rx.PyDiGraph) -> int:
#         """
#         @brief Retrieves the index of the sink node in the DFG using the utils helper.

#         @param dfg (rx.PyDiGraph): The data flow graph.

#         @return int: The index of the sink node. Raises RuntimeError if not found.
#         """
#         # Delegate to the utils implementation which is already used elsewhere
#         try:
#             sink_idx = utils_get_sink_index(dfg)
#         except Exception as e:
#             raise RuntimeError(f"[RetimeDFG] failed to find sink node: {e}")
#         return sink_idx

#     @staticmethod
#     def get_source_index(dfg: rx.PyDiGraph) -> int:
#         """
#         @brief Retrieves the index of the source node in the DFG using the utils helper.

#         @param dfg (rx.PyDiGraph): The data flow graph.

#         @return int: The index of the source node. Raises RuntimeError if not found.
#         """
#         try:
#             src_idx = utils_get_source_index(dfg)
#         except Exception as e:
#             raise RuntimeError(f"[RetimeDFG] failed to find source node: {e}")
#         return src_idx

#     def isSourceNode(self,node):
#         """
#         @brief Checks if the given node is a source node.

#         @param node: The node to check.

#         @return bool: True if the node is a source node, False otherwise.
#         """
#         return isinstance(node,TextGraphNode) and node.label() == "Source"
    
#     def isSinkNode(self,node):
#         """
#         @brief Checks if the given node is a sink node.

#         @param node: The node to check.

#         @return bool: True if the node is a sink node, False otherwise.
#         """
#         return isinstance(node,TextGraphNode) and node.label() == "Sink"
    
#     def printRetimedLabels(self):
#         """
#         @brief Prints the retimed labels of the nodes in the DFG.
#         """
#         print(self.solution)
#         # for key in self.solution:
#         #     print(str(self.dfg[key].label())+ " ----> " + str(self.solution[key]))

#     def is_dummy_node(self, node_index):
#         """
#         @brief Checks if the node at the given index is a dummy node.

#         @param node_index (int): The index of the node.

#         @return bool: True if the node is a dummy node, False otherwise.
#         """
#         node = self.dfg[node_index]
#         return isinstance(node, TextGraphNode) and node.node_text == 'Dummy'

#     def set_source_sink_weight(self,useLinearAlgorithm):
#         """
#         @brief Sets the weight of the edge between the source and sink nodes.

#         @param useLinearAlgorithm (str): Whether to use linear algorithm for setting the weight ("true" or "false").
#         """
#         num_nodes = self.dfg.num_nodes()
#         source_index = RetimeDFG.get_source_index(self.dfg)
#         sink_index = RetimeDFG.get_sink_index(self.dfg)
        
#         # remove the artificial edge only if present to avoid unexpected exceptions / state
#         try:
#             self.dfg.remove_edge(sink_index, source_index)
#         except Exception:
#             # edge may not exist; ignore
#             pass

#         max_path_weights = [0 for index in range(num_nodes)]
#         sortedNodeList = rx.topological_sort(self.dfg)
#         for nodeIndex in sortedNodeList:
#             inEdges = self.dfg.in_edges(nodeIndex)
#             maxWeightTillNode = 0
#             for inEdge in inEdges:
#                 maxWeightTillNode = max(max_path_weights[inEdge[0]],maxWeightTillNode)
#             if self.is_dummy_node(nodeIndex):
#                 maxWeightTillNode += 1
#             max_path_weights[nodeIndex] = maxWeightTillNode
#         max_path_weight = max(max_path_weights)
#         print("Max path weight " + str(max_path_weight))
#         self.maxPathWeight = max_path_weight
#         if useLinearAlgorithm == "false":
#             self.dfg.add_edge(sink_index,source_index,max_path_weight)
#             self.dfg.update_edge(sink_index, source_index, max_path_weight)
#         if useLinearAlgorithm == "true":
#             print("useLineAlgo from set_source_sink_weight")
#             self.solution[source_index] = -max_path_weight
#             self.solution[sink_index] = 0
#             # self.dfg.remove_edge(sink_index,source_index)
#     # def set_source_sink_weight(self,useLinearAlgorithm):
#     #     num_nodes = self.dfg.num_nodes()
#     #     source_index = RetimeDFG.get_source_index(self.dfg)
#     #     sink_index = RetimeDFG.get_sink_index(self.dfg)
#     #     all_paths_source_sink = rx.all_simple_paths(
#     #         self.dfg, source_index, sink_index)
#     #     max_path_weight = 0
#     #     for path in all_paths_source_sink:
#     #         path_weight_sum = sum(
#     #             self.dfg[node_index].node_weight
#     #             # if not self.is_dummy_node(node_index)
#     #             # else 0
#     #             for node_index in path
#     #         )
#     #         max_path_weight = max(max_path_weight, path_weight_sum)
#     #     self.dfg.update_edge(sink_index, source_index, max_path_weight)
#     #     print("Max path weight : " + str(max_path_weight))
#     #     if useLinearAlgorithm == "true":
#     #         print("useLineAlgo from set_source_sink_weight")
#     #         self.solution[source_index] = -max_path_weight
#     #         self.solution[sink_index] = 0
#     #         self.dfg.remove_edge(sink_index,source_index)

#     def update_retiming_labels(self):
#         """
#         @brief Updates the retiming labels for all nodes in the DFG based on the sorted node list.
#         """
#         sourceIndex = self.get_source_index(self.dfg)
#         #--------Level Order Here---------------
        
#         #----------Topological sort here--------------
#         sortedNodeList = rx.topological_sort(self.dfg)
#         for nodeIndex in sortedNodeList:
#             if(nodeIndex != sourceIndex):
#                 inEdges = self.dfg.in_edges(nodeIndex)
                
#                 if(len(inEdges) > 1):
#                     mn = 1e8
#                     for edge in inEdges:
#                         mn = min(mn,abs(self.solution[edge[0]]))
#                     self.solution[nodeIndex] = -mn
#                 else:
#                     edge = inEdges[0]
#                     if self.is_dummy_node(nodeIndex):
#                         self.solution[nodeIndex] = -(abs(self.solution[edge[0]]) - 1)
#                     else:
#                         self.solution[nodeIndex] = self.solution[edge[0]]

#     def printEdgeWeights(self):
#         """
#         @brief Prints the weights of all edges in the DFG.
#         """
#         edges = self.dfg.weighted_edge_list()
#         for edge in edges:
#             print(self.dfg[edge[0]].label() + "------->" + self.dfg[edge[1]].label() + " : " + str(edge[2]))
            
#     def update_edge_weights(self):
#         """
#         @brief Updates the weights of all edges in the DFG based on the computed solution.
#         """
#         edges = self.dfg.edge_list()
#         for edge in edges:
#             edgeWeight = abs(self.solution[edge[0]] - self.solution[edge[1]])
#             self.dfg.update_edge(edge[0],edge[1],edgeWeight)

#     def get_path_edge_sum(self, path: rx.NodeIndices) -> int:
#         """
#         @brief Computes the sum of edge weights along a given path.

#         @param path (rx.NodeIndices): The path as a list of node indices.

#         @return int: The sum of edge weights along the path.
#         """
#         path_len = len(path)
#         sum = 0
#         for i in range(path_len-1):
#             sum += self.dfg.get_edge_data(path[i], path[i+1])
#         return sum

#     def print_matrix(self, mat):
#         """
#         @brief Prints a matrix.

#         @param mat: The matrix to print.
#         """
#         rows = len(mat)
#         for i in range(rows):
#             print(mat[i])
#         print()

#     # def add_feasibility_constraint(self, edge):
#     #     """
#     #     @brief Adds a feasibility constraint to the constraint graph.

#     #     @param edge (tuple): The edge to add as a constraint.
#     #     """
#     #     self.feasibilityConstraints += 1
#     #     source = edge[0]
#     #     dest = edge[1]
#     #     edge_weight = self.dfg.get_edge_data(source, dest)
#     #     if (self.debug):
#     #         print(
#     #             f"Adding feasibility constraint from {dest} and {source} with weight {edge_weight}")
#     #     self.constraint_graph.add_edge(dest, source, edge_weight)
#     def add_feasibility_constraint(self, edge):
#         """
#         @brief Adds a feasibility constraint to the constraint graph.
#         Locks internal gadget edges so the solver treats the gadget as an atomic block.
#         """
#         self.feasibilityConstraints += 1
#         source = edge[0]
#         dest = edge[1]
#         edge_weight = self.dfg.get_edge_data(source, dest)
        
#         if self.is_internal_gadget_edge(source, dest):
#             # THE FIX: Lock the internal gadget edge mathematically.
#             # Enforcing r(source) = r(dest) ensures no extra registers are placed here.
#             # print(f"🔒 SUCCESS: Locking internal gadget edge {source} -> {dest}")
#             self.constraint_graph.add_edge(dest, source, 0)
#             self.constraint_graph.add_edge(source, dest, 0)
#         else:
#             # Normal feasibility constraint for external wires
#             if self.debug:
#                 print(f"Adding feasibility constraint from {dest} and {source} with weight {edge_weight}")
#             self.constraint_graph.add_edge(dest, source, edge_weight)


#     def add_critical_path_constraint(self, source, dest):
#         """
#         @brief Adds a critical path constraint to the constraint graph.

#         @param source (int): The source node index.
#         @param dest (int): The destination node index.
#         """
#         self.criticalPathConstraints += 1
#         inequality_rhs = self.w_matrix[source][dest] - 1
#         if (self.debug):
#             print(
#                 f"Adding critical path constraint from {dest} and {source} with weight {inequality_rhs}")
#         self.constraint_graph.add_edge(dest, source, inequality_rhs)

#     def save_constraint_graph(self):
#         """
#         @brief Saves the constraint graph and the original DFG as images.
#         """
#         fig = graphviz_draw(self.constraint_graph, method="sfdp")
#         fig.save("constraint.png")
#         fig = graphviz_draw(self.dfg, method="sfdp")
#         fig.save("graph2.png")

#     def solve_constraint_graph(self):
#         """
#         @brief Solves the constraint graph to find the retiming solution.
#         """
#         has_no_solution = rx.negative_edge_cycle(
#             self.constraint_graph, lambda e: e)
#         if (has_no_solution):
#             print("Constraint graph has negative edge cycle")
#             neg_cycle = rx.find_negative_cycle(
#                 self.constraint_graph, lambda e: e)
#             if (self.debug):
#                 print(neg_cycle)
#             return
#         else:
#             num_nodes = self.dfg.num_nodes()
#             solution = rx.bellman_ford_shortest_path_lengths(
#                 self.constraint_graph, num_nodes, lambda e: e)
#             print('Solved constraint graph')
#             # if (self.debug):
#             #     print(solution)
#             self.solution = solution

#     def calculate_retimed_design(self):
#         """
#         @brief Calculates the retimed design based on the solution.
#         """
#         retimed_dfg = self.dfg.copy()
#         original_edges = self.dfg.weighted_edge_list()
#         for original_edge in original_edges:
#             source = original_edge[0]
#             dest = original_edge[1]
#             original_weight = original_edge[2]
#             new_weight = self.solution[dest] - \
#                 self.solution[source] + original_weight
#             assert (int(new_weight) == new_weight)
#             retimed_dfg.update_edge(source, dest, int(new_weight))
#         self.retimed_design = retimed_dfg
    
#     def insertRegCallsInAssignment(self,node,count):
#         """
#         @brief Inserts register calls into the assignment expression.

#         @param node: The node whose assignment expression is to be modified.
#         @param count (int): The number of register calls to insert.

#         @return: The modified node with inserted register calls.
#         """
#         currNode = node
#         for _ in range(count):
#             currNode = get_func_call_ast('regPR',currNode)
#         return currNode
    
#     def getNodeToAddRegCalls(self,idToFind,currNode):
#         """
#         @brief Recursively searches for the node to add register calls to.

#         @param idToFind (str): The ID of the node to find.
#         @param currNode: The current node in the search.

#         @return: The node to add register calls to, or None if not found.
#         """
#         if isinstance(currNode,c_ast.ID):
#             if idToFind == currNode.name:
#                 return currNode
#             else:
#                 return None
#         if isinstance(currNode,c_ast.FuncCall):
#             return self.getNodeToAddRegCalls(idToFind,currNode.args.exprs[0])
#         if isinstance(currNode,c_ast.BinaryOp):
#             left = self.getNodeToAddRegCalls(idToFind,currNode.left)
#             right = self.getNodeToAddRegCalls(idToFind,currNode.right)
#             if left is not None:
#                 return left
#             if right is not None:
#                 return right
    
#     def add_reg_calls(self,useLinearAlgorithm):
#         """
#         @brief Adds register calls to the retimed DFG based on the algorithm used.

#         @param useLinearAlgorithm (str): Whether to use linear algorithm ("true" or "false").
#         """
#         # dfgToUse : rx.PyDiGraph
#         # if(useLinearAlgorithm == "false"):
#         #     self.dfg.remove_edge(RetimeDFG.get_sink_index(self.dfg),RetimeDFG.get_source_index(self.dfg))
#         #     dfgToUse = self.retimed_design
#         #     dfgToUse.remove_edge(self.get_sink_index(dfgToUse),self.get_source_index(dfgToUse))
#         # else:
#         #     dfgToUse = self.dfg
#         # sortedNodeList = rx.topological_sort(dfgToUse)



#         dfgToUse : rx.PyDiGraph
#         if(useLinearAlgorithm == "false"):
#             # SAFE EDGE REMOVAL
#             sink_idx = self.get_sink_index(self.dfg)
#             src_idx = self.get_source_index(self.dfg)
#             try:
#                 self.dfg.remove_edge(sink_idx, src_idx)
#             except Exception:
#                 pass # Edge already removed, perfectly fine
                
#             dfgToUse = self.retimed_design
            
#             try:
#                 dfgToUse.remove_edge(self.get_sink_index(dfgToUse), self.get_source_index(dfgToUse))
#             except Exception:
#                 pass # Edge already removed, perfectly fine
#         else:
#             dfgToUse = self.dfg
            
#         sortedNodeList = rx.topological_sort(dfgToUse)
        
#         for node in sortedNodeList:
#             label = dfgToUse[node].label()
#             inEdges = dfgToUse.in_edges(node)
            
#             if self.is_dummy_node(node) or self.isSourceNode(dfgToUse[node]):
#                 continue
#             if self.isSinkNode(dfgToUse[node]):
#                 for edge in inEdges:
#                     src = None
#                     weight = 0
#                     if self.is_dummy_node(edge[0]):
#                         inEdge = dfgToUse.in_edges(edge[0])[0]
#                         src = dfgToUse[inEdge[0]].ast
#                         weight = edge[2] + inEdge[2] - 1
#                     else:
#                         src = dfgToUse[edge[0]].ast
#                         weight = edge[2]

#                     src.rvalue = self.insertRegCallsInAssignment(src.rvalue,edge[2])
#                 continue

#             for edge in inEdges:
#                 weight = 0
#                 inNode = None
#                 if self.is_dummy_node(edge[0]):
#                     inEdgeDummy = dfgToUse.in_edges(edge[0])[0]
#                     weight = inEdgeDummy[2] + edge[2] - 1
#                     inNode = dfgToUse[inEdgeDummy[0]].ast.lvalue
#                 elif self.isSourceNode(dfgToUse[edge[0]]):
#                     dfgToUse[node].ast.rvalue = self.insertRegCallsInAssignment(dfgToUse[node].ast.rvalue,edge[2])
#                     continue
#                 else:
#                     weight = edge[2]
#                     inNode = dfgToUse[edge[0]].ast.lvalue
#                 idToFind = inNode.name if isinstance(inNode,c_ast.ID) else inNode.expr.name
#                 currNode = dfgToUse[node].ast
#                 nodeToAddRegCalls = self.getNodeToAddRegCalls(idToFind,currNode.rvalue)
#                 changedNode = self.insertRegCallsInAssignment(nodeToAddRegCalls,weight)
#                 visitor = AddRegs(changedNode,idToFind)
#                 visitor.visit(dfgToUse[node].ast)
#                 if isinstance(currNode.rvalue,c_ast.ID):
#                     currNode.rvalue = changedNode

#         # for edge in retimed_weights:
#         #     source = self.dfg[edge[0]]
#         #     dest = self.dfg[edge[1]]
#         #     weight = edge[2]
#         #     if (weight >= 1):
#         #         if self.is_dummy_node(edge[0]) or self.is_dummy_node(edge[1]):
#         #             weight -= 1
#         #         for index in range(weight):
#         #             if (isinstance(source, ASTGraphNode)):
#         #                 source.ast.rvalue = get_func_call_ast(
#         #                     'reg', source.ast.rvalue)
#         #             elif (isinstance(dest, ASTGraphNode)):
#         #                 dest.ast.rvalue = get_func_call_ast('reg', dest.ast.rvalue)

#     def create_constraint_graph(self):
#         """
#         @brief Creates the constraint graph based on the DFG and the computed matrices.
#         """
#         edge_list = self.dfg.edge_list()
#         for edge in edge_list:
#             self.add_feasibility_constraint(edge)
#         num_nodes = self.dfg.num_nodes()
#         for i in range(num_nodes):
#             for j in range(num_nodes):
#                 d_u_v = self.d_matrix[i][j]
#                 w_u_v = self.w_matrix[i][j]
#                 if (d_u_v > self.target_period):
#                     self.add_critical_path_constraint(i, j)
#         for i in range(num_nodes):
#             self.constraint_graph.add_edge(num_nodes, i, 0)

#     # def set_w_d_matrix(self):
#     #     num_nodes = self.dfg.num_nodes()
#     #     self.w_matrix = [[0 for i in range(num_nodes)]
#     #                      for j in range(num_nodes)]
#     #     self.d_matrix = [[0 for i in range(num_nodes)]
#     #                      for j in range(num_nodes)]
#     #     all_pair_paths = rx.all_pairs_all_simple_paths(self.dfg)
#     #     for source in all_pair_paths:
#     #         for dest in all_pair_paths[source]:
#     #             all_path_w = []
#     #             all_path_d = []
#     #             for path in all_pair_paths[source][dest]:
#     #                 all_path_w.append(self.get_path_edge_sum(path))
#     #                 path_d = sum(
#     #                     self.dfg[node_index].node_weight for node_index in path)
#     #                 all_path_d.append(path_d)
#     #             self.w_matrix[source][dest] = min(all_path_w)
#     #             d_max = 0
#     #             for i in range(len(all_path_d)):
#     #                 if (all_path_w[i] == self.w_matrix[source][dest]):
#     #                     d_max = max(d_max, all_path_d[i])
#     #             self.d_matrix[source][dest] = d_max
#     #     for node_index in range(num_nodes):
#     #         self.d_matrix[node_index][node_index] = self.dfg[node_index].node_weight

#     #     if (self.debug):
#     #         self.print_matrix(self.d_matrix)
#     #         self.print_matrix(self.w_matrix)
            
#     def set_w_d_matrix(self):
#         """
#         @brief Sets the weight and delay matrices using O(V*E) dynamic programming.
#         This prevents exponential memory blowups (OOM crashes) on large benchmarks like AES.
#         """
#         num_nodes = self.dfg.num_nodes()

#         # ---------------------------------------------------------
#         # CYCLE FIX: Temporarily remove the artificial sink->source edge 
#         # so topological sort doesn't crash!
#         # ---------------------------------------------------------
#         source_index = self.get_source_index(self.dfg)
#         sink_index = self.get_sink_index(self.dfg)
#         edge_removed = False
#         edge_data = None
        
#         try:
#             # Check if the artificial edge exists and remove it
#             if self.dfg.has_edge(sink_index, source_index):
#                 edge_data = self.dfg.get_edge_data(sink_index, source_index)
#                 self.dfg.remove_edge(sink_index, source_index)
#                 edge_removed = True
#         except Exception:
#             pass

#         # Initialize W (min registers) to infinity, D (max delay) to 0
#         self.w_matrix = [[float('inf') for _ in range(num_nodes)] for _ in range(num_nodes)]
#         self.d_matrix = [[0 for _ in range(num_nodes)] for _ in range(num_nodes)]
        
#         # We only need to traverse the graph going forward
#         sorted_nodes = list(rx.topological_sort(self.dfg))
        
#         for source in range(num_nodes):
#             # Distance to itself
#             self.w_matrix[source][source] = 0
#             self.d_matrix[source][source] = self.dfg[source].node_weight
            
#             try:
#                 start_idx = sorted_nodes.index(source)
#             except ValueError:
#                 continue
                
#             # Sweep forward through the topological sort
#             for i in range(start_idx, len(sorted_nodes)):
#                 u = sorted_nodes[i]
                
#                 # If 'u' is unreachable from 'source', skip it
#                 if self.w_matrix[source][u] == float('inf'):
#                     continue
                    
#                 # Check all outgoing wires from 'u' to 'v'
#                 for out_edge in self.dfg.out_edges(u):
#                     v = out_edge[1]
#                     edge_weight = out_edge[2]
                    
#                     new_w = self.w_matrix[source][u] + edge_weight
#                     new_d = self.d_matrix[source][u] + self.dfg[v].node_weight
                    
#                     # Update if we found a path with fewer registers
#                     if new_w < self.w_matrix[source][v]:
#                         self.w_matrix[source][v] = new_w
#                         self.d_matrix[source][v] = new_d
#                     # If same number of registers, keep the path with the worst-case delay
#                     elif new_w == self.w_matrix[source][v]:
#                         if new_d > self.d_matrix[source][v]:
#                             self.d_matrix[source][v] = new_d

#         # Replace 'inf' with 0 for unreachable nodes to match original code behavior
#         for i in range(num_nodes):
#             for j in range(num_nodes):
#                 if self.w_matrix[i][j] == float('inf'):
#                     self.w_matrix[i][j] = 0

#         # ---------------------------------------------------------
#         # RESTORE THE EDGE IF WE REMOVED IT
#         # ---------------------------------------------------------
#         if edge_removed:
#             self.dfg.add_edge(sink_index, source_index, edge_data)

#         # print(f"✅ W and D matrices computed safely for {num_nodes} nodes!")
#         # if self.debug:  # Commenting this out so it doesn't flood your console for 980 nodes!
#         #     self.print_matrix(self.d_matrix)
#         #     self.print_matrix(self.w_matrix)

#     # def get_hpc3_to_hpc2_candidates(self):
#     #     """
#     #     @brief Scans the retimed graph to find HPC3 gadgets that can be optimized to HPC2.
        
#     #     It looks for HPC3 gadget 'entry nodes' where the inputs are mismatched 
#     #     (one path has a pipeline register, the other does not).
        
#     #     @return: A set of unique Gadget IDs (integers) that should be converted to HPC2.
#     #     """
#     #     candidates = set()
        
#     #     # Regex to find variables belonging to HPC3 gadgets and extract their ID.
#     #     # Matches strings like "u00_HPC30", "temp_..._HPC35"
#     #     # Group 1 will be the ID (e.g., '0', '5')
#     #     gadget_pattern = re.compile(r".*HPC3(\d+)$")

#     #     existing_nodes = self.dfg.node_indices()
        
#     #     for node_idx in existing_nodes:
#     #         node = self.dfg[node_idx]
            
#     #         # 1. We only care about AST Assignment nodes
#     #         if not isinstance(node, ASTGraphNode):
#     #             continue
                
#     #         # 2. Check if this node writes to an HPC3 variable (LHS Analysis)
#     #         lvalue_name = ""
#     #         if isinstance(node.ast.lvalue, c_ast.ID):
#     #             lvalue_name = node.ast.lvalue.name
#     #         elif isinstance(node.ast.lvalue, c_ast.UnaryOp): # Handle pointer/dereference if needed
#     #             if isinstance(node.ast.lvalue.expr, c_ast.ID):
#     #                 lvalue_name = node.ast.lvalue.expr.name
            
#     #         match = gadget_pattern.match(lvalue_name)
#     #         if not match:
#     #             continue  # This node is not part of an HPC3 gadget
                
#     #         gadget_id = int(match.group(1))
            
#     #         # 3. Analyze Input Edges (The "Entry" Check)
#     #         # We need to see if this node takes inputs from OUTSIDE this gadget.
#     #         # If both inputs are from inside the same gadget, it's an internal node (skip it).
            
#     #         in_edges = self.dfg.in_edges(node_idx)
#     #         if len(in_edges) < 2:
#     #             continue # Gadget entry points (like AND/XOR) usually take 2 inputs

#     #         # Get the source nodes for these edges
#     #         src_node_1 = self.dfg[in_edges[0][0]]
#     #         src_node_2 = self.dfg[in_edges[1][0]]
            
#     #         weight_1 = in_edges[0][2]
#     #         weight_2 = in_edges[1][2]
            
#     #         # Helper to check if a source node belongs to the SAME gadget
#     #         def is_same_gadget(src_node, current_id):
#     #             if not isinstance(src_node, ASTGraphNode): return False
#     #             src_name = src_node.ast.lvalue.name if isinstance(src_node.ast.lvalue, c_ast.ID) else ""
#     #             src_match = gadget_pattern.match(src_name)
#     #             if src_match and int(src_match.group(1)) == current_id:
#     #                 return True
#     #             return False

#     #         # If inputs come from the *same* gadget, this is an internal step (e.g., y_0 calculation).
#     #         # We only care about the first layer where external data enters the gadget.
#     #         if is_same_gadget(src_node_1, gadget_id) or is_same_gadget(src_node_2, gadget_id):
#     #             continue

#     #         # 4. The Pattern Match: Mismatched Register Latency
#     #         # Case: (Reg, Direct) or (Direct, Reg)
#     #         has_mismatch = (weight_1 >= 1 and weight_2 == 0) or (weight_1 == 0 and weight_2 >= 1)
            
#     #         if has_mismatch:
#     #             if self.debug:
#     #                 print(f"[Optimization] Found Candidate! Gadget {gadget_id}")
#     #                 print(f"    Node: {lvalue_name}")
#     #                 print(f"    Inputs: Weight {weight_1} vs Weight {weight_2}")
                
#     #             candidates.add(gadget_id)

#     #     return candidates

#     # def get_hpc3_to_hpc2_candidates(self):
#     #     """
#     #     @brief Scans the retimed graph to find HPC3 gadgets that can be optimized to HPC2.

#     #     For each candidate gadget, also records whether the pipeline register
#     #     is on the left or right input of the gadget entry node.

#     #     @return:
#     #         dict:
#     #             key   -> Gadget ID (int)
#     #             value -> "left" or "right"
#     #     """

#     #     candidates = dict()

#     #     gadget_pattern = re.compile(r".*HPC3(\d+)$")
#     #     existing_nodes = self.dfg.node_indices()

#     #     for node_idx in existing_nodes:
#     #         node = self.dfg[node_idx]

#     #         # 1. Only AST assignment nodes
#     #         if not isinstance(node, ASTGraphNode):
#     #             continue

#     #         # 2. Extract LHS variable name
#     #         lvalue_name = ""
#     #         if isinstance(node.ast.lvalue, c_ast.ID):
#     #             lvalue_name = node.ast.lvalue.name
#     #         elif isinstance(node.ast.lvalue, c_ast.UnaryOp):
#     #             if isinstance(node.ast.lvalue.expr, c_ast.ID):
#     #                 lvalue_name = node.ast.lvalue.expr.name

#     #         match = gadget_pattern.match(lvalue_name)
#     #         if not match:
#     #             continue

#     #         gadget_id = int(match.group(1))

#     #         # 3. Entry-node check
#     #         in_edges = self.dfg.in_edges(node_idx)
#     #         if len(in_edges) < 2:
#     #             continue

#     #         src_node_1 = self.dfg[in_edges[0][0]]
#     #         src_node_2 = self.dfg[in_edges[1][0]]

#     #         weight_1 = in_edges[0][2]
#     #         weight_2 = in_edges[1][2]

#     #         # Helper: same gadget check
#     #         def is_same_gadget(src_node, current_id):
#     #             if not isinstance(src_node, ASTGraphNode):
#     #                 return False
#     #             if isinstance(src_node.ast.lvalue, c_ast.ID):
#     #                 src_name = src_node.ast.lvalue.name
#     #             else:
#     #                 return False
#     #             src_match = gadget_pattern.match(src_name)
#     #             return src_match and int(src_match.group(1)) == current_id

#     #         # Skip internal gadget nodes
#     #         if is_same_gadget(src_node_1, gadget_id) or is_same_gadget(src_node_2, gadget_id):
#     #             continue

#     #         # 4. Detect mismatch and side
#     #         if weight_1 >= 1 and weight_2 == 0:
#     #             reg_side = "left"
#     #         elif weight_1 == 0 and weight_2 >= 1:
#     #             reg_side = "right"
#     #         else:
#     #             continue  # balanced → not a candidate

#     #         # Store result
#     #         candidates[gadget_id] = reg_side

#     #         if self.debug:
#     #             print(f"[Optimization] HPC3 → HPC2 candidate")
#     #             print(f"    Gadget ID : {gadget_id}")
#     #             print(f"    Entry Var : {lvalue_name}")
#     #             print(f"    Reg Side  : {reg_side}")
#     #             print(f"    Weights   : left={weight_1}, right={weight_2}")

#     #     return candidates
#     def get_hpc3_to_hpc2_candidates(self):
#         """
#         @brief Scans the retimed graph to find HPC3 gadgets that can be optimized to HPC2.
#         Only returns candidates that have a slack >= 1 to prevent violating the critical path latency.
#         """
#         candidates = dict()
#         num_nodes = self.dfg.num_nodes()
#         # sortedNodeList = rx.topological_sort(self.dfg)


#         source_index = self.get_source_index(self.dfg)
#         sink_index = self.get_sink_index(self.dfg)
#         try:
#             self.dfg.remove_edge(sink_index, source_index)
#             if self.debug:
#                 print("[RegBalancer] Removed artificial Sink->Source edge for topological sort.")
#         except Exception:
#             pass # Edge might already be removed, which is fine.

#         sortedNodeList = rx.topological_sort(self.dfg)

#         # ---------------------------------------------------------
#         # STEP 1: Calculate ASAP (Forward Pass)
#         # Matches logic from set_source_sink_weight
#         # ---------------------------------------------------------
#         asap_weights = [0 for _ in range(num_nodes)]
#         for nodeIndex in sortedNodeList:
#             maxWeightTillNode = 0
#             for inEdge in self.dfg.in_edges(nodeIndex):
#                 maxWeightTillNode = max(asap_weights[inEdge[0]], maxWeightTillNode)
#             if self.is_dummy_node(nodeIndex):
#                 maxWeightTillNode += 1
#             asap_weights[nodeIndex] = maxWeightTillNode

#         # ---------------------------------------------------------
#         # STEP 2: Calculate ALAP (Backward Pass)
#         # ---------------------------------------------------------
#         alap_weights = [0 for _ in range(num_nodes)]
#         for nodeIndex in reversed(sortedNodeList):
#             maxWeightFromNode = 0
#             for outEdge in self.dfg.out_edges(nodeIndex):
#                 # outEdge is (src, dest, weight) -> outEdge[1] is dest
#                 maxWeightFromNode = max(alap_weights[outEdge[1]], maxWeightFromNode)
#             if self.is_dummy_node(nodeIndex):
#                 maxWeightFromNode += 1
#             alap_weights[nodeIndex] = maxWeightFromNode

#         # The global critical path latency (already calculated in set_source_sink_weight)
#         max_graph_weight = self.maxPathWeight 



#         # # ---------------------------------------------------------
#         # # STEP 1: Calculate ASAP (Forward Pass)
#         # # ---------------------------------------------------------
#         # asap_weights = [0 for _ in range(num_nodes)]
#         # for nodeIndex in sortedNodeList:
#         #     maxWeightTillNode = 0
#         #     for inEdge in self.dfg.in_edges(nodeIndex):
#         #         # FIX: Add the actual retimed edge weight (inEdge[2])
#         #         weight_with_edge = asap_weights[inEdge[0]] + inEdge[2]
#         #         maxWeightTillNode = max(weight_with_edge, maxWeightTillNode)
                
#         #     if self.is_dummy_node(nodeIndex):
#         #         maxWeightTillNode += 1
#         #     asap_weights[nodeIndex] = maxWeightTillNode

#         # # ---------------------------------------------------------
#         # # STEP 2: Calculate ALAP (Backward Pass)
#         # # ---------------------------------------------------------
#         # alap_weights = [0 for _ in range(num_nodes)]
#         # for nodeIndex in reversed(sortedNodeList):
#         #     maxWeightFromNode = 0
#         #     for outEdge in self.dfg.out_edges(nodeIndex):
#         #         # FIX: Add the actual retimed edge weight (outEdge[2])
#         #         weight_with_edge = alap_weights[outEdge[1]] + outEdge[2]
#         #         maxWeightFromNode = max(weight_with_edge, maxWeightFromNode)
                
#         #     if self.is_dummy_node(nodeIndex):
#         #         maxWeightFromNode += 1
#         #     alap_weights[nodeIndex] = maxWeightFromNode



#         # ---------------------------------------------------------
#         # STEP 3: Find Candidates with Slack
#         # ---------------------------------------------------------
#         gadget_pattern = re.compile(r".*HPC3(\d+)$")
#         existing_nodes = self.dfg.node_indices()

#         for node_idx in existing_nodes:
#             node = self.dfg[node_idx]

#             # 1. Only AST assignment nodes
#             if not isinstance(node, ASTGraphNode):
#                 continue

#             # 2. Extract LHS variable name
#             lvalue_name = ""
#             if isinstance(node.ast.lvalue, c_ast.ID):
#                 lvalue_name = node.ast.lvalue.name
#             elif isinstance(node.ast.lvalue, c_ast.UnaryOp):
#                 if isinstance(node.ast.lvalue.expr, c_ast.ID):
#                     lvalue_name = node.ast.lvalue.expr.name

#             match = gadget_pattern.match(lvalue_name)
#             if not match:
#                 continue

#             gadget_id = int(match.group(1))

#             # 3. Entry-node check
#             in_edges = self.dfg.in_edges(node_idx)
#             if len(in_edges) < 2:
#                 continue

#             src_node_1 = self.dfg[in_edges[0][0]]
#             src_node_2 = self.dfg[in_edges[1][0]]

#             weight_1 = in_edges[0][2]
#             weight_2 = in_edges[1][2]

#             def is_same_gadget(src_node, current_id):
#                 if not isinstance(src_node, ASTGraphNode):
#                     return False
#                 if isinstance(src_node.ast.lvalue, c_ast.ID):
#                     src_name = src_node.ast.lvalue.name
#                 else:
#                     return False
#                 src_match = gadget_pattern.match(src_name)
#                 return src_match and int(src_match.group(1)) == current_id

#             # Skip internal gadget nodes
#             if is_same_gadget(src_node_1, gadget_id) or is_same_gadget(src_node_2, gadget_id):
#                 continue

#             # 4. Detect mismatch and side
#             if weight_1 >= 1 and weight_2 == 0:
#                 reg_side = "left"
#             elif weight_1 == 0 and weight_2 >= 1:
#                 reg_side = "right"
#             else:
#                 continue  # balanced → not a candidate

#             # 5. THE CRITICAL FIX: SLACK CHECK
#             # Total path weight passing through this specific node
#             node_dummy_val = 1 if self.is_dummy_node(node_idx) else 0
#             path_through_node = asap_weights[node_idx] + alap_weights[node_idx] - node_dummy_val
#             max_graph_weight = self.maxPathWeight
#             slack = max_graph_weight - path_through_node

#             if slack >= 1:
#                 # Safe to swap! It won't increase the total max path weight
#                 candidates[gadget_id] = reg_side

#                 if self.debug:
#                     print(f"[Optimization] HPC3 → HPC2 candidate ACCEPTED")
#                     print(f"    Gadget ID : {gadget_id} (Slack: {slack})")
#                     print(f"    Entry Var : {lvalue_name}")
#             else:
#                 if self.debug:
#                     print(f"[Optimization] HPC3 → HPC2 candidate REJECTED (On Critical Path)")
#                     print(f"    Gadget ID : {gadget_id} (Slack: {slack})")

#         return candidates
    
#     def get_gadget_suffix(self, node_idx):
#         """Extracts the gadget suffix (e.g., '_HPC30') from a node's variable name."""
#         node = self.dfg[node_idx]
#         if not isinstance(node, ASTGraphNode):
#             return None
            
#         lvalue_name = ""
#         if isinstance(node.ast.lvalue, c_ast.ID):
#             lvalue_name = node.ast.lvalue.name
#         elif isinstance(node.ast.lvalue, c_ast.UnaryOp):
#             if isinstance(node.ast.lvalue.expr, c_ast.ID):
#                 lvalue_name = node.ast.lvalue.expr.name
                
#         # Match standard gadget variable suffixes
#         match = re.search(r"_(HPC[123]|COMAR|DOMAND)(\d+)$", lvalue_name, re.IGNORECASE)
#         if match:
#             return match.group(0)
#         return None

#     def is_internal_gadget_edge(self, source, dest):
#         """Checks if an edge connects two nodes inside the EXACT SAME gadget."""
#         src_suffix = self.get_gadget_suffix(source)
#         dest_suffix = self.get_gadget_suffix(dest)
        
#         if src_suffix and dest_suffix and (src_suffix == dest_suffix):
#             return True
#         return False
    
    

import rustworkx as rx
from modules.GraphNode import ASTGraphNode, TextGraphNode
from rustworkx.visualization import graphviz_draw
from collections import deque
from pycparser import c_ast
from modules.Visitor import AddRegs
from modules.utils import get_func_call_ast
import re

class RetimeDFG():
    """
    @class RetimeDFG
    @brief A class for retiming a data flow graph (DFG) to optimize its performance.

    This class handles the retiming of a data flow graph represented using the `rustworkx` library. It performs various
    operations including setting source and sink weights, updating retiming labels, adding register calls, and solving
    constraint graphs.

    @details
        The `RetimeDFG` class includes methods for calculating retimed designs, creating constraint graphs, and updating
        edge weights. It also supports debugging outputs to trace the computation steps.
    """

    def __init__(self, dfg: rx.PyDiGraph, debug: bool = False) -> None:
        """
        @brief Initializes the RetimeDFG instance.

        @param dfg (rx.PyDiGraph): The data flow graph to be retimed.
        @param debug (bool, optional): Whether to enable debugging output. Defaults to False.
        """
        self.dfg = dfg
        self.w_matrix = None
        self.m_matrix = None
        # Create constraint graph and add N+1 nodes to it
        self.constraint_graph = rx.PyDiGraph()
        num_nodes = self.dfg.num_nodes()
        self.constraint_graph.add_nodes_from(range(num_nodes+1))
        self.target_period = 1
        self.solution = {}
        self.retimed_design = None
        self.debug = debug
        self.feasibilityConstraints = 0
        self.criticalPathConstraints = 0
        self.maxPathWeight = 0

    @staticmethod
    def get_source_index(dfg: rx.PyDiGraph) -> int:
        """
        @brief Retrieves the index of the source node in the DFG.

        @param dfg (rx.PyDiGraph): The data flow graph.

        @return int: The index of the source node.
        """
        # print(dfg.node_indices())
        for node_idx in dfg.node_indices():
            node = dfg[node_idx]
            
            if (isinstance(node, TextGraphNode) and node.label() == 'Source'):
                source_index = node_idx
        return source_index
    
    
    def isSourceNode(self,node):
        """
        @brief Checks if the given node is a source node.

        @param node: The node to check.

        @return bool: True if the node is a source node, False otherwise.
        """
        return isinstance(node,TextGraphNode) and node.label() == "Source"
    
    def isSinkNode(self,node):
        """
        @brief Checks if the given node is a sink node.

        @param node: The node to check.

        @return bool: True if the node is a sink node, False otherwise.
        """
        return isinstance(node,TextGraphNode) and node.label() == "Sink"
    
    @staticmethod
    def get_sink_index(dfg: rx.PyDiGraph) -> int:
        """
        @brief Retrieves the index of the sink node in the DFG.

        @param dfg (rx.PyDiGraph): The data flow graph.

        @return int: The index of the sink node.
        """
        for node_idx in dfg.node_indices():
            node = dfg[node_idx]
            if (isinstance(node, TextGraphNode) and node.label() == 'Sink'):
                sink_index = node_idx
        return sink_index
    
    def printRetimedLabels(self):
        """
        @brief Prints the retimed labels of the nodes in the DFG.
        """
        print(self.solution)
        # for key in self.solution:
        #     print(str(self.dfg[key].label())+ " ----> " + str(self.solution[key]))

    def is_dummy_node(self, node_index):
        """
        @brief Checks if the node at the given index is a dummy node.

        @param node_index (int): The index of the node.

        @return bool: True if the node is a dummy node, False otherwise.
        """
        node = self.dfg[node_index]
        return isinstance(node, TextGraphNode) and node.node_text == 'Dummy'

    def set_source_sink_weight(self,useLinearAlgorithm):
        """
        @brief Sets the weight of the edge between the source and sink nodes.

        @param useLinearAlgorithm (str): Whether to use linear algorithm for setting the weight ("true" or "false").
        """
        num_nodes = self.dfg.num_nodes()
        source_index = RetimeDFG.get_source_index(self.dfg)
        sink_index = RetimeDFG.get_sink_index(self.dfg)
        
        self.dfg.remove_edge(sink_index,source_index)
        max_path_weights = [0 for index in range(num_nodes)]
        sortedNodeList = rx.topological_sort(self.dfg)
        for nodeIndex in sortedNodeList:
            inEdges = self.dfg.in_edges(nodeIndex)
            maxWeightTillNode = 0
            for inEdge in inEdges:
                maxWeightTillNode = max(max_path_weights[inEdge[0]],maxWeightTillNode)
            if self.is_dummy_node(nodeIndex):
                maxWeightTillNode += 1
            max_path_weights[nodeIndex] = maxWeightTillNode
        max_path_weight = max(max_path_weights)
        print("Max path weight " + str(max_path_weight))
        self.maxPathWeight = max_path_weight
        if useLinearAlgorithm == "false":
            self.dfg.add_edge(sink_index,source_index,max_path_weight)
            self.dfg.update_edge(sink_index, source_index, max_path_weight)
        if useLinearAlgorithm == "true":
            print("useLineAlgo from set_source_sink_weight")
            self.solution[source_index] = -max_path_weight
            self.solution[sink_index] = 0
            # self.dfg.remove_edge(sink_index,source_index)
    # def set_source_sink_weight(self,useLinearAlgorithm):
    #     num_nodes = self.dfg.num_nodes()
    #     source_index = RetimeDFG.get_source_index(self.dfg)
    #     sink_index = RetimeDFG.get_sink_index(self.dfg)
    #     all_paths_source_sink = rx.all_simple_paths(
    #         self.dfg, source_index, sink_index)
    #     max_path_weight = 0
    #     for path in all_paths_source_sink:
    #         path_weight_sum = sum(
    #             self.dfg[node_index].node_weight
    #             # if not self.is_dummy_node(node_index)
    #             # else 0
    #             for node_index in path
    #         )
    #         max_path_weight = max(max_path_weight, path_weight_sum)
    #     self.dfg.update_edge(sink_index, source_index, max_path_weight)
    #     print("Max path weight : " + str(max_path_weight))
    #     if useLinearAlgorithm == "true":
    #         print("useLineAlgo from set_source_sink_weight")
    #         self.solution[source_index] = -max_path_weight
    #         self.solution[sink_index] = 0
    #         self.dfg.remove_edge(sink_index,source_index)

    def update_retiming_labels(self):
        """
        @brief Updates the retiming labels for all nodes in the DFG based on the sorted node list.
        """
        sourceIndex = self.get_source_index(self.dfg)
        #--------Level Order Here---------------
        
        #----------Topological sort here--------------
        sortedNodeList = rx.topological_sort(self.dfg)
        for nodeIndex in sortedNodeList:
            if(nodeIndex != sourceIndex):
                inEdges = self.dfg.in_edges(nodeIndex)
                
                if(len(inEdges) > 1):
                    mn = 1e8
                    for edge in inEdges:
                        mn = min(mn,abs(self.solution[edge[0]]))
                    self.solution[nodeIndex] = -mn
                else:
                    edge = inEdges[0]
                    if self.is_dummy_node(nodeIndex):
                        self.solution[nodeIndex] = -(abs(self.solution[edge[0]]) - 1)
                    else:
                        self.solution[nodeIndex] = self.solution[edge[0]]

    def printEdgeWeights(self):
        """
        @brief Prints the weights of all edges in the DFG.
        """
        edges = self.dfg.weighted_edge_list()
        for edge in edges:
            print(self.dfg[edge[0]].label() + "------->" + self.dfg[edge[1]].label() + " : " + str(edge[2]))
            
    def update_edge_weights(self):
        """
        @brief Updates the weights of all edges in the DFG based on the computed solution.
        """
        edges = self.dfg.edge_list()
        for edge in edges:
            edgeWeight = abs(self.solution[edge[0]] - self.solution[edge[1]])
            self.dfg.update_edge(edge[0],edge[1],edgeWeight)

    def get_path_edge_sum(self, path: rx.NodeIndices) -> int:
        """
        @brief Computes the sum of edge weights along a given path.

        @param path (rx.NodeIndices): The path as a list of node indices.

        @return int: The sum of edge weights along the path.
        """
        path_len = len(path)
        sum = 0
        for i in range(path_len-1):
            sum += self.dfg.get_edge_data(path[i], path[i+1])
        return sum

    def print_matrix(self, mat):
        """
        @brief Prints a matrix.

        @param mat: The matrix to print.
        """
        rows = len(mat)
        for i in range(rows):
            print(mat[i])
        print()

    def add_feasibility_constraint(self, edge):
        """
        @brief Adds a feasibility constraint to the constraint graph.

        @param edge (tuple): The edge to add as a constraint.
        """
        self.feasibilityConstraints += 1
        source = edge[0]
        dest = edge[1]
        edge_weight = self.dfg.get_edge_data(source, dest)
        if (self.debug):
            print(
                f"Adding feasibility constraint from {dest} and {source} with weight {edge_weight}")
        self.constraint_graph.add_edge(dest, source, edge_weight)

    def add_critical_path_constraint(self, source, dest):
        """
        @brief Adds a critical path constraint to the constraint graph.

        @param source (int): The source node index.
        @param dest (int): The destination node index.
        """
        self.criticalPathConstraints += 1
        inequality_rhs = self.w_matrix[source][dest] - 1
        if (self.debug):
            print(
                f"Adding critical path constraint from {dest} and {source} with weight {inequality_rhs}")
        self.constraint_graph.add_edge(dest, source, inequality_rhs)

    def save_constraint_graph(self):
        """
        @brief Saves the constraint graph and the original DFG as images.
        """
        fig = graphviz_draw(self.constraint_graph, method="sfdp")
        fig.save("constraint.png")
        fig = graphviz_draw(self.dfg, method="sfdp")
        fig.save("graph2.png")


    # def solve_constraint_graph(self):
    #     """
    #     @brief Solves the constraint graph using Linear Programming (Minimum-Area Retiming).
    #     This replaces Bellman-Ford to ensure registers are evenly distributed and 
    #     the total number of registers in the generated code is minimized.
    #     """
    #     import numpy as np
    #     from scipy.optimize import linprog

    #     num_nodes = self.dfg.num_nodes()
    #     total_vars = num_nodes + 1  # Include the N+1 dummy node

    #     # 1. Objective Function: Minimize Sum( r(v) * (in_degree(v) - out_degree(v)) )
    #     c = np.zeros(total_vars)
    #     for i in range(num_nodes):
    #         # In retiming, the coefficient for a node's retiming value is (in_degree - out_degree)
    #         in_deg = len(self.dfg.in_edges(i))
    #         out_deg = len(self.dfg.out_edges(i))
    #         c[i] = in_deg - out_deg
        
    #     # The dummy node doesn't affect the objective score
    #     c[num_nodes] = 0

    #     # 2. Setup the inequality matrix (A_ub * r <= b_ub)
    #     A_ub = []
    #     b_ub = []

    #     # Parse every constraint edge into a linear equation
    #     # An edge u -> v with weight W means: r(v) - r(u) <= W
    #     for u, v, W in self.constraint_graph.weighted_edge_list():
    #         row = np.zeros(total_vars)
    #         row[v] = 1
    #         row[u] = -1
    #         A_ub.append(row)
    #         b_ub.append(W)

    #     # 3. Setup equality constraint: anchor the dummy node to 0
    #     A_eq = np.zeros((1, total_vars))
    #     A_eq[0, num_nodes] = 1
    #     b_eq = np.array([0])

    #     # Convert constraints to numpy arrays
    #     if A_ub:
    #         A_ub = np.array(A_ub)
    #         b_ub = np.array(b_ub)
    #     else:
    #         A_ub = np.zeros((1, total_vars))
    #         b_ub = np.zeros(1)

    #     # 4. Solve the Linear Program
    #     # Retiming values can mathematically be negative, so we leave bounds open (None, None)
    #     bounds = [(None, None) for _ in range(total_vars)]

    #     print("Solving Minimum-Area Retiming using LP...")
    #     res = linprog(c, A_ub=A_ub, b_ub=b_ub, A_eq=A_eq, b_eq=b_eq, bounds=bounds)

    #     # 5. Extract and apply the solution
    #     if res.success:
    #         print('Successfully solved constraint graph using LP (Min-Area Retiming)')
    #         # Due to the unimodular property of the constraint matrix, LP relaxation 
    #         # naturally yields integer solutions. We round to handle minor float precision.
    #         self.solution = {i: int(round(res.x[i])) for i in range(num_nodes)}
            
    #         if self.debug:
    #             print("Retiming Array:", self.solution)
    #     else:
    #         print("Constraint graph has no valid retiming solution (Infeasible).")
    #         if self.debug:
    #             print("LP Solver Error:", res.message)
    def solve_constraint_graph(self):
        """
        @brief Solves the constraint graph to find the retiming solution.
        """
        has_no_solution = rx.negative_edge_cycle(
            self.constraint_graph, lambda e: e)
        if (has_no_solution):
            print("Constraint graph has negative edge cycle")
            neg_cycle = rx.find_negative_cycle(
                self.constraint_graph, lambda e: e)
            if (self.debug):
                print(neg_cycle)
            return
        else:
            num_nodes = self.dfg.num_nodes()
            solution = rx.bellman_ford_shortest_path_lengths(
                self.constraint_graph, num_nodes, lambda e: e)
            print('Solved constraint graph')
            if (self.debug):
                print(solution)
            self.solution = solution

    def calculate_retimed_design(self):
        """
        @brief Calculates the retimed design based on the solution.
        """
        retimed_dfg = self.dfg.copy()
        original_edges = self.dfg.weighted_edge_list()
        for original_edge in original_edges:
            source = original_edge[0]
            dest = original_edge[1]
            original_weight = original_edge[2]
            new_weight = self.solution[dest] - \
                self.solution[source] + original_weight
            assert (int(new_weight) == new_weight)
            retimed_dfg.update_edge(source, dest, int(new_weight))
        self.retimed_design = retimed_dfg
    
    def insertRegCallsInAssignment(self,node,count):
        """
        @brief Inserts register calls into the assignment expression.

        @param node: The node whose assignment expression is to be modified.
        @param count (int): The number of register calls to insert.

        @return: The modified node with inserted register calls.
        """
        currNode = node
        for _ in range(count):
            currNode = get_func_call_ast('reg',currNode)
        return currNode
    
    def getNodeToAddRegCalls(self,idToFind,currNode):
        """
        @brief Recursively searches for the node to add register calls to.

        @param idToFind (str): The ID of the node to find.
        @param currNode: The current node in the search.

        @return: The node to add register calls to, or None if not found.
        """
        if isinstance(currNode,c_ast.ID):
            if idToFind == currNode.name:
                return currNode
            else:
                return None
        if isinstance(currNode,c_ast.FuncCall):
            return self.getNodeToAddRegCalls(idToFind,currNode.args.exprs[0])
        if isinstance(currNode,c_ast.BinaryOp):
            left = self.getNodeToAddRegCalls(idToFind,currNode.left)
            right = self.getNodeToAddRegCalls(idToFind,currNode.right)
            if left is not None:
                return left
            if right is not None:
                return right
    
    def add_reg_calls(self,useLinearAlgorithm):
        """
        @brief Adds register calls to the retimed DFG based on the algorithm used.

        @param useLinearAlgorithm (str): Whether to use linear algorithm ("true" or "false").
        """
        dfgToUse : rx.PyDiGraph
        if(useLinearAlgorithm == "false"):
            self.dfg.remove_edge(RetimeDFG.get_sink_index(self.dfg),RetimeDFG.get_source_index(self.dfg))
            dfgToUse = self.retimed_design
            dfgToUse.remove_edge(self.get_sink_index(dfgToUse),self.get_source_index(dfgToUse))
        else:
            dfgToUse = self.dfg
        sortedNodeList = rx.topological_sort(dfgToUse)
        
        for node in sortedNodeList:
            label = dfgToUse[node].label()
            inEdges = dfgToUse.in_edges(node)
            
            if self.is_dummy_node(node) or self.isSourceNode(dfgToUse[node]):
                continue
            if self.isSinkNode(dfgToUse[node]):
                for edge in inEdges:
                    src = None
                    weight = 0
                    if self.is_dummy_node(edge[0]):
                        inEdge = dfgToUse.in_edges(edge[0])[0]
                        src = dfgToUse[inEdge[0]].ast
                        weight = edge[2] + inEdge[2] - 1
                    else:
                        src = dfgToUse[edge[0]].ast
                        weight = edge[2]

                    src.rvalue = self.insertRegCallsInAssignment(src.rvalue,edge[2])
                continue

            for edge in inEdges:
                weight = 0
                inNode = None
                if self.is_dummy_node(edge[0]):
                    inEdgeDummy = dfgToUse.in_edges(edge[0])[0]
                    weight = inEdgeDummy[2] + edge[2] - 1
                    inNode = dfgToUse[inEdgeDummy[0]].ast.lvalue
                elif self.isSourceNode(dfgToUse[edge[0]]):
                    dfgToUse[node].ast.rvalue = self.insertRegCallsInAssignment(dfgToUse[node].ast.rvalue,edge[2])
                    continue
                else:
                    weight = edge[2]
                    inNode = dfgToUse[edge[0]].ast.lvalue
                idToFind = inNode.name if isinstance(inNode,c_ast.ID) else inNode.expr.name
                currNode = dfgToUse[node].ast
                nodeToAddRegCalls = self.getNodeToAddRegCalls(idToFind,currNode.rvalue)
                changedNode = self.insertRegCallsInAssignment(nodeToAddRegCalls,weight)
                visitor = AddRegs(changedNode,idToFind)
                visitor.visit(dfgToUse[node].ast)
                if isinstance(currNode.rvalue,c_ast.ID):
                    currNode.rvalue = changedNode


    def create_constraint_graph(self):
        """
        @brief Creates the constraint graph based on the DFG and the computed matrices.
        """
        edge_list = self.dfg.edge_list()
        for edge in edge_list:
            self.add_feasibility_constraint(edge)
        num_nodes = self.dfg.num_nodes()
        for i in range(num_nodes):
            for j in range(num_nodes):
                d_u_v = self.d_matrix[i][j]
                w_u_v = self.w_matrix[i][j]
                if (d_u_v > self.target_period):
                    self.add_critical_path_constraint(i, j)
        for i in range(num_nodes):
            self.constraint_graph.add_edge(num_nodes, i, 0)
            
    # def set_w_d_matrix(self):
    #     """
    #     @brief Sets the weight and delay matrices based on all-pairs shortest paths in the DFG.
    #     """
    #     num_nodes = self.dfg.num_nodes()
    #     num_paths = 0
    #     self.w_matrix = [[0 for i in range(num_nodes)]
    #                      for j in range(num_nodes)]
    #     self.d_matrix = [[0 for i in range(num_nodes)]
    #                      for j in range(num_nodes)]
    #     all_pair_paths = rx.all_pairs_all_simple_paths(self.dfg)
    #     for source in all_pair_paths:
    #         for dest in all_pair_paths[source]:
    #             all_path_w = []
    #             all_path_d = []
    #             num_paths += len(all_pair_paths[source][dest])
                
    #             for path in all_pair_paths[source][dest]:
    #                 all_path_w.append(self.get_path_edge_sum(path))
    #                 path_d = sum(self.dfg[node_index].node_weight for node_index in path)
    #                 all_path_d.append(path_d)
    #             self.w_matrix[source][dest] = min(all_path_w)
    #             d_max = 0
    #             for i in range(len(all_path_d)):
    #                 if (all_path_w[i] == self.w_matrix[source][dest]):
    #                     d_max = max(d_max, all_path_d[i])
    #             self.d_matrix[source][dest] = d_max
    #     for node_index in range(num_nodes):
    #         self.d_matrix[node_index][node_index] = self.dfg[node_index].node_weight
    #     print("########## paths ###########")
    #     print(num_paths)
    #     if (self.debug):
    #         self.print_matrix(self.d_matrix)
    #         self.print_matrix(self.w_matrix)
    def set_w_d_matrix(self):
        """
        @brief Sets the weight (W) and delay (D) matrices using the Floyd-Warshall algorithm.
        This calculates the minimum registers (W) and maximum delay (D) between all pairs
        without suffering from combinatorial path explosion.
        """
        import math
        num_nodes = self.dfg.num_nodes()
        
        # Initialize matrices with infinity
        self.w_matrix = [[math.inf] * num_nodes for _ in range(num_nodes)]
        self.d_matrix = [[-math.inf] * num_nodes for _ in range(num_nodes)]

        # Base case: The path from a node to itself has 0 edge weight, 
        # and a delay equal to its own node weight.
        for i in range(num_nodes):
            self.w_matrix[i][i] = 0
            self.d_matrix[i][i] = self.dfg[i].node_weight

        # Base case: Direct edges
        for edge in self.dfg.edge_indices():
            u, v = self.dfg.get_edge_endpoints_by_index(edge)
            weight = self.dfg.get_edge_data_by_index(edge)
            
            # If multiple edges exist between u and v, take the minimum weight
            if weight < self.w_matrix[u][v]:
                self.w_matrix[u][v] = weight
                self.d_matrix[u][v] = self.dfg[u].node_weight + self.dfg[v].node_weight
            elif weight == self.w_matrix[u][v]:
                # If weights are equal, maximize the delay
                self.d_matrix[u][v] = max(self.d_matrix[u][v], self.dfg[u].node_weight + self.dfg[v].node_weight)

        print(f"Computing W and D matrices for {num_nodes} nodes (Floyd-Warshall)...")
        
        # Floyd-Warshall DP step
        for k in range(num_nodes):
            for i in range(num_nodes):
                for j in range(num_nodes):
                    # If a path exists from i->k and k->j
                    if self.w_matrix[i][k] != math.inf and self.w_matrix[k][j] != math.inf:
                        w_ikj = self.w_matrix[i][k] + self.w_matrix[k][j]
                        
                        # Subtract node_weight[k] because it gets counted twice (once in i->k, once in k->j)
                        d_ikj = self.d_matrix[i][k] + self.d_matrix[k][j] - self.dfg[k].node_weight
                        
                        # We want the path with the minimum registers (W)
                        if w_ikj < self.w_matrix[i][j]:
                            self.w_matrix[i][j] = w_ikj
                            self.d_matrix[i][j] = d_ikj
                        # If registers are equal, we track the worst-case (maximum) delay (D)
                        elif w_ikj == self.w_matrix[i][j]:
                            if d_ikj > self.d_matrix[i][j]:
                                self.d_matrix[i][j] = d_ikj

        # Clean up infinity values to match the behavior of your original script
        for i in range(num_nodes):
            for j in range(num_nodes):
                if self.w_matrix[i][j] == math.inf:
                    self.w_matrix[i][j] = 0
                    self.d_matrix[i][j] = 0

        print("Finished generating W and D matrices.")
        
        if self.debug:
            self.print_matrix(self.d_matrix)
            self.print_matrix(self.w_matrix)
    # def get_hpc3_to_hpc2_candidates(self):
    #         """
    #         @brief Scans the retimed graph to find HPC3 gadgets that can be optimized to HPC2.
    #         Dynamically tracks cumulative latency added by multiple swaps to prevent cascading violations.
    #         """
    #         import re
    #         candidates = dict()
    #         num_nodes = self.dfg.num_nodes()

    #         source_index = self.get_source_index(self.dfg)
    #         sink_index = self.get_sink_index(self.dfg)
    #         try:
    #             self.dfg.remove_edge(sink_index, source_index)
    #             if self.debug:
    #                 print("[RegBalancer] Removed artificial Sink->Source edge for topological sort.")
    #         except Exception:
    #             pass 

    #         sortedNodeList = rx.topological_sort(self.dfg)
    #         gadget_pattern = re.compile(r".*HPC3(\d+)$")
    #         existing_nodes = self.dfg.node_indices()
    #         max_graph_weight = self.maxPathWeight

    #         # Dictionary to track virtual latency added to specific edges by our accepted swaps
    #         virtual_edge_delays = {}

    #         for node_idx in sortedNodeList:
    #             node = self.dfg[node_idx]

    #             # 1. Only AST assignment nodes
    #             if not isinstance(node, ASTGraphNode):
    #                 continue

    #             # 2. Extract LHS variable name
    #             lvalue_name = ""
    #             if isinstance(node.ast.lvalue, c_ast.ID):
    #                 lvalue_name = node.ast.lvalue.name
    #             elif isinstance(node.ast.lvalue, c_ast.UnaryOp):
    #                 if isinstance(node.ast.lvalue.expr, c_ast.ID):
    #                     lvalue_name = node.ast.lvalue.expr.name

    #             match = gadget_pattern.match(lvalue_name)
    #             if not match:
    #                 continue

    #             gadget_id = int(match.group(1))

    #             # 3. Entry-node check
    #             in_edges = self.dfg.in_edges(node_idx)
    #             if len(in_edges) < 2:
    #                 continue

    #             src_node_1 = in_edges[0][0]
    #             src_node_2 = in_edges[1][0]
    #             weight_1 = in_edges[0][2]
    #             weight_2 = in_edges[1][2]

    #             def is_same_gadget(src_node_idx, current_id):
    #                 src_node = self.dfg[src_node_idx]
    #                 if not isinstance(src_node, ASTGraphNode):
    #                     return False
    #                 if isinstance(src_node.ast.lvalue, c_ast.ID):
    #                     src_name = src_node.ast.lvalue.name
    #                 else:
    #                     return False
    #                 src_match = gadget_pattern.match(src_name)
    #                 return src_match and int(src_match.group(1)) == current_id

    #             # Skip internal gadget nodes
    #             if is_same_gadget(src_node_1, gadget_id) or is_same_gadget(src_node_2, gadget_id):
    #                 continue

    #             # 4. Detect mismatch and determine which edge would receive the +1 slow path delay
    #             if weight_1 >= 1 and weight_2 == 0:
    #                 reg_side = "left"
    #                 slow_edge = (src_node_1, node_idx)
    #             elif weight_1 == 0 and weight_2 >= 1:
    #                 reg_side = "right"
    #                 slow_edge = (src_node_2, node_idx)
    #             else:
    #                 continue  # balanced → not a candidate

    #             # ---------------------------------------------------------
    #             # STEP 5: DYNAMIC ASAP & ALAP CALCULATION
    #             # Recalculates structural depth using the virtual delays 
    #             # added by any previously accepted gadgets.
    #             # ---------------------------------------------------------
    #             asap_weights = [0 for _ in range(num_nodes)]
    #             for n_idx in sortedNodeList:
    #                 maxWeightTillNode = 0
    #                 for inEdge in self.dfg.in_edges(n_idx):
    #                     u, v, _ = inEdge
    #                     # Add virtual delay if this edge was made a slow path earlier
    #                     extra_delay = virtual_edge_delays.get((u, v), 0)
    #                     weight_with_edge = asap_weights[u] + extra_delay
    #                     maxWeightTillNode = max(weight_with_edge, maxWeightTillNode)
    #                 if self.is_dummy_node(n_idx):
    #                     maxWeightTillNode += 1
    #                 asap_weights[n_idx] = maxWeightTillNode

    #             alap_weights = [0 for _ in range(num_nodes)]
    #             for n_idx in reversed(sortedNodeList):
    #                 maxWeightFromNode = 0
    #                 for outEdge in self.dfg.out_edges(n_idx):
    #                     u, v, _ = outEdge
    #                     # Add virtual delay if this edge was made a slow path earlier
    #                     extra_delay = virtual_edge_delays.get((u, v), 0)
    #                     weight_with_edge = alap_weights[v] + extra_delay
    #                     maxWeightFromNode = max(weight_with_edge, maxWeightFromNode)
    #                 if self.is_dummy_node(n_idx):
    #                     maxWeightFromNode += 1
    #                 alap_weights[n_idx] = maxWeightFromNode

    #             # ---------------------------------------------------------
    #             # STEP 6: SLACK CHECK & CONSUMPTION
    #             # ---------------------------------------------------------
    #             node_dummy_val = 1 if self.is_dummy_node(node_idx) else 0
    #             path_through_node = asap_weights[node_idx] + alap_weights[node_idx] - node_dummy_val
    #             slack = max_graph_weight - path_through_node

    #             if slack >= 1:
    #                 # Safe to swap!
    #                 candidates[gadget_id] = reg_side
                    
    #                 # CRITICAL: Consume the slack so downstream gadgets don't double-dip!
    #                 virtual_edge_delays[slow_edge] = virtual_edge_delays.get(slow_edge, 0) + 1

    #                 if self.debug:
    #                     print(f"[Optimization] HPC3 → HPC2 ACCEPTED")
    #                     print(f"    Gadget ID : {gadget_id} (Remaining Slack: {slack})")
    #             else:
    #                 if self.debug:
    #                     print(f"[Optimization] HPC3 → HPC2 REJECTED (Cascading Critical Path)")
    #                     print(f"    Gadget ID : {gadget_id} (Remaining Slack: {slack})")

    #         return candidates

