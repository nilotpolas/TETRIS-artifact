"""
================================================================================
HPC2 Asymmetric Latency Analysis and Optimization
================================================================================

ANALYSIS:
---------

HPC2 helper functions latency paths:

1. hpc2_same_shares: latency = 0 (no reg calls)
   u_{i,i} = a_i & b_i

2. hpc2_v: latency = 2 (two reg calls in sequence)
   temp = reg(b_j ^ rand)      [latency = 1]
   v_{i,j} = reg(temp & a_i)   [latency = 1]
   Total: 2 cycles
   
   Path: b_j is critical path (goes through 2 stages)

3. hpc2_w: latency = 2 (two reg calls in sequence)
   a_neg = ~(a_i)              [latency = 0]
   w_{i,j} = reg(a_neg & rand) [latency = 1]
   Total: 1 cycle (but with neg operation)
   
   Path: a_i is critical path (goes through 1 stage)

4. hpc2_xor_vw: latency = 0 (no reg calls)
   u_{i,j} = v_{i,j} ^ w_{i,j}

CRITICAL INSIGHT:
-----------------

The bottleneck is in hpc2_v_order:
  - Input B goes through: XOR(latency 1) → AND(latency 1) = 2 stages
  - Input A goes through: AND(latency 1) = 1 stage

This means:
  • If B has longer input depth: use current implementation (B is "free")
  • If A has longer input depth: SWAP inputs (make A go through XOR path)

OPTIMIZATION STRATEGY:
----------------------

1. Analyze input depth of A and B
2. If depth(A) > depth(B): SWAP A and B, then adjust helper functions
3. This ensures the critical path input goes through XOR (cheaper in terms of latency balancing)

IMPLEMENTATION:
---------------

We need to:
1. Track which input (A or B) has higher depth
2. Generate optimized helper functions that swap or don't swap
3. Adjust variable ordering in main function

================================================================================
"""
