"""
HPC2 Input Argument Swapping Algorithm

Goal: Reduce latency by optimally routing signals to HPC2 input paths

HPC2/HPC2o Asymmetry:
  Input A (indices 0,1): latency 2 (SLOW)
  Input B (indices 2,3): latency 1 (FAST)

Strategy:
  1. Compute signal arrival times at each HPC2 input
  2. If fast signal arrives at slow input → SWAP arguments
  3. Route early-arriving signals to fast path
  4. Iteratively improve until convergence
"""
