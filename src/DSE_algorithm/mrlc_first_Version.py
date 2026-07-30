
from DSE_algorithm.dse import DSE
from tabulate import tabulate # type: ignore
import json
from collections import defaultdict
import heapq
import Gadgets as secure_gadget
class MRLC(DSE):
    """Minimise Randomness Under Latency Constraint (MRLC)"""



    
    """


        latency_initial 
        randomness_initial

        all the nodes in this table have low randomness than initial gadget randomness
        --------------------------------
        gadget | randomness | latency   |
        ---------------------------------
        g1     |    r1      |   l1      |
        g2     |    r2      |   l2      |
        g3     |    r3      |   l3      |
        g4     |    r4      |   l4      |

        - target_latency
        - bonus latency = target_latnecy - initial_latency.
        - H levels in tree
        - initial state : every node have initial state (initial gadget)
        - gadget table with m gadgets
        - cost of modification (required_extra_latency for modification) : extra latency required to change all the nodes in level with low randomness gadget.
            l_old = initial_latency
            extra_latency =  l_new - l_old
        - objective : choose for each level a gadget such that extra latency is not greater than bonous layency
    
                        
        as we want to reduce the reandomness we choose gadgets that have radnomness less current / initial gadget.
        
        level map -> a map of level corresponding to the gadget in each level
        min_randomness = number of nodes in the and tree * initial_randomness.

        DFS(bonus_latency, gadget_list, level, randomness, level_wise_gadget_Assignment map - m ){
            if bonus_latency == 0 || gadget_list is empty || level = none:
                if randomneess < min_randomness
                    min_Randomness = randomness
                    level map = m
                return 


            node = num of nodes in the level

            for each gadget, r_new, extra_latency in gadget_list:
                bonus_latency -= extra_latency
                randomness -= nodes * (initial_randomness -  r_new)
                m[level] = gadget
                
                # choose the next level to form maxheap
                gadget list = choose gadget form the table whose extra latency is less the latnecy bonous

                for gadget in gadget_specs_map
                    l_old = initial latency
                    l_new = gadget[latency]
                    extra_latency = l_new - l_old 
                    if extra_latency <= bounus larnecy
                        add the gadfget to the gadget_list 
                DFS(bonus_latency, gadget_list, level, ranomness, m)
                
                bonous_latncy += extra_latency
                ranomness += nodes * (initial_randomness -  r_new)
                m[level] = initial_gadget
            
        }



        The core idea is that if we have extra/bonus latency we can use it to decrease the randomness of the design 
        [INPUT] : 
            - target_latency: maximum allowed latency of the design 
            - AND-tree : 1. and-tree (A graph of AND gates preserving the dependency structure of computation). Nodes represent AND operations and edges represent dependencies. 
            - gadget_spec_map : map of gadget name to its corresponding specs.
                                e.g., 
                                {
                                
                                    'HPC1' : {"latency" : 2, "randomness" : 2, "area" : 200.67}
                                    'HPC3' : {"latency" : 1, "randomness" : 2, "area" : 908.67}
                                    ...
                                }

        [LOGIC]:

            Minimise Randomness Under Latency Constraint (MRLC)
            - `target_latency` => maximum latency that design can have.

            - We choose the gadget with minimum latency among all the gadgets present in `gadget_spec_map` and call it `initial_latency`.
            - assign each node in and tree the selected gadget and calculate the latency of the design.
              `total_latency` = number of node in and treee *  initial_latency

            - calculate the buffer latency => buffer_latency = target_latency - total_latency.

            - while buffer_latency > 0:

                - find the gadget with least randomness among the gadgets.
                                OR
                    (should we find gadgets with randomness < `initial_randomness)
                    let us say n gadget exist with randomness < initial_randomness.
                        we sort these n gadgets in ascending order of randomnness. (lowest randomness used comes first)
                        and then we iterate this list till we find a gadget with extra_letency <= buffer_latency 
                        thus we are able to reduce the randomness of design using the buffer latnecy.

                         o o o o o
                         
                        
                        if we are unable to find a gadget with randomness < initial_randomenss and extra_latnecy <= buffer_rnadomneess
                        then we try to reduce the area of the gadget.
                        
                        how to reduce the area:
                            - find the list of gadgets that have area less than current gadget.
                            - [g1, g2] hume do gaDget mile jinka area kam h

                            -   g1 -> randomness : 3, latency 2, area : 8
                                g2- > randomness  : 6 latency 2, area : 7
                                hum area to reduce kar skte hai na 
                                hum randomness bhi reduce kar de ge
                                humari need h rnaodmness reudnce karna 
                                g -> randomness : 9, latency 1, area :10
                                
                            

                    

                - calculate the extra latency required to change the gadget. `extra_latency`


                - if `extra_latency` <= buffer_latency:
                    - find the level with maximum number of nodes to replace the gadgets.
                    - buffer_latency = buffer_latency - extra_latency
                    - update gadget_definition map
                - else:
                    - randomness cannot be reduce..
                    - lets us try to reduce the area using the buffer_latency.
                    - 

        - humko randomness reduce krni h ... 
        - bonus latency calculate krege 
        - bonus latency ko use kar skate h ek level ke sare node ko hum jada latency de de to randomness reduce ho jaye gi
        - 
        
    
    """

    def __init__(self,d, and_tree):
        super().__init__(d, and_tree)


    def mrlc_algo(self, target_latency):
        """
            - Assuming initially all the gates are replaced with HPC3 gadget with latency 1
            - Therefore the latency of the circuit is number of levels in the and cloud tree
            - Target latency is the latency provided by the user it is the maximum latency that the user can tolerate
            - we are trying to use the bonus latency to reduce the randomness in the circuit 

            - As HPC3 uses 2 random numbers and HPC2 uses 1 random number per node 
            - comar uses 6 random numbers for any number of nodes

            - We will try to replace the HPC3 gadgets in a level with HPC2 or Comar gadgets to reduce the randomness in the circuit
            - We will start from the level with most number of gates to maximise the minimisation of reduction of random numbers used.
            - If the level have nodes more than 6 then we can use comar (latency 2)
                    why use comar -> because it uses 6 random numbers for all the nodes in the level
                    using HPC2 will use 1 random number for each node in the level 
                    thus reducing the randomness in the circuit by (HPc3[randomness] - HPC2[randomness]) * number of node in the level.
            
                    But if the level nodes are replaced by comar then the randomness used only be will be 6
                    Thus using comar will reduce the randomness in the circuit

            - If the level have nodes less than or equal to 6 then we can use HPC2 (latency 2)
                    When gate in a level is 6 we replace with HPC2, as the area of Comar is more 
                    Therefore, replacment with HPC2 gadget is prefered over Comar gadget as HPC2 
                    will incur same randomness with less area.
            Steps to implement the algorithm:

            1. get the level with most number of gates
            2. if the level have nodes more than 5 then replace all the nodes with comar
            3. else replace all the nodes with HPC2
            4. repeat the process until the target latency is met

                

            """
        # calculate the latency of design with initially all and operation assigend with hpc3
        latency_leastpossible = len(self.nodes_by_level) * DSE.GADGET_PARAM_MAP['HPC3']['latency']
        latency_bonus = target_latency - latency_leastpossible
        max_heap = self.construct_max_heap()

        
        if latency_bonus > 0:
            while(latency_bonus > 0):
                max_gate_level = self.find_max_gate_level(max_heap)
                if max_gate_level == None: # no more levels to replace
                    break
                if len(self.nodes_by_level[max_gate_level]) > 6:
                    self.replace_gates_with_optimisied_gadgets(max_gate_level, "COMAR")
                    self.level_latency[max_gate_level] = DSE.GADGET_PARAM_MAP['COMAR']['latency']
                else:
                    self.replace_gates_with_optimisied_gadgets(max_gate_level, "HPC2")
                    self.level_latency[max_gate_level] = DSE.GADGET_PARAM_MAP['HPC2']['latency']

                latency_bonus -= DSE.GADGET_PARAM_MAP['HPC3']['latency']
                
        elif latency_bonus < 0:
            print("Target Latency can't be met")
        
        for node in self.and_tree.graph.nodes():
            # print(f"node: {node}")
            if self.gadget_definition.get(node) is None:
                gadget_name = "HPC3"
                _ = self.replace_gadget(gadget_name, node)
        

    def construct_max_heap(self):
        max_heap = []
        for level, nodes in self.nodes_by_level.items():
            # intialising level_latency of each level in the and_tree
            # as every gate is HPC3, therefore latency of each level is 1
            self.level_latency[level] = 1
            heapq.heappush(max_heap, (-len(nodes), level))
        return max_heap
    
    def find_max_gate_level(self, max_heap):
        if max_heap:
            return heapq.heappop(max_heap)[1]

    def replace_gates_with_optimisied_gadgets(self, max_gate_level, gadget_name):
        
        for gate in self.nodes_by_level[max_gate_level]:
            # latency_sum += self.replace_gadget(gadget_name,gate, latency_sum, 1) # latency of hpc3 is 1
            self.replace_gadget(gadget_name,gate) # latency of hpc3 is 1
        #     print(latency_sum)
        # print(f"latency used {latency_sum//len(self.nodes_by_level[max_gate_level])}")
        # return latency_sum//len(self.nodes_by_level[max_gate_level]) - 1

  
    def replace_gadget(self,gadget_name, gate):
        # ------------------------------------------------------------------------------------------
        gadget_class = getattr(secure_gadget, gadget_name) # retrive gadget class
        if gadget_name == 'COMAR':
            gadget = gadget_class()
        else:
            gadget = gadget_class(self.d)
        # generate the function definition for this And Gadget
        gadget_def = gadget.generate_multiply_function()
        func_name = gadget.get_function_name()
        # ------------------------------------------------------------------------------------------
        # num_random_vars = gadget.get_random_count()
        # latency = gadget.get_latency()

        num_random_vars = DSE.GADGET_PARAM_MAP[gadget_name.upper()]['randomness']
        latency = DSE.GADGET_PARAM_MAP[gadget_name.upper()]['latency']
        
        if func_name not in self.unique_gadgets_definition:
            self.unique_gadgets_definition[func_name] = gadget_def

        if self.gadget_definition.get(gate) is None: # not replaced yet 
            self.gadget_definition[gate] = {
                # "gadget_definition": gadget_def,
                "gadget_name": gadget_name,
                "function_name":func_name,
                "random_numbers": num_random_vars,
                "gadget_latency": latency
            }
            
        # return latency
            
# how to calculate the latency of design after running mrlc:
# gagdet definition stores randomness of each gadget and latency of each gadget
# but latency depends on the levels of graph
# for randomness we need to add the randomness of each node if node is hpc3 or hpc2 but if it is commar then 
# we can resue the randomness so we will just add 6 if commar is present in the design
# for latency we can store latency of each level in a dictionary (map)
# latency of each level is defined as the maximum latency of any node in that level