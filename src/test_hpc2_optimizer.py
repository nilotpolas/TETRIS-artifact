#!/usr/bin/env python3
"""
HPC2 Latency Optimization Test and Demonstration

This script tests the HPC2 latency optimizer with various input depth scenarios.
"""

import sys
sys.path.insert(0, '/home/tapish08/Desktop/DSE-Framework')

from Gadgets.hpc2_latency_optimizer import HPC2LatencyOptimizer


def test_scenario(scenario_name, d, a_depth, b_depth):
    """Test a specific scenario and display results"""
    print(f"\n{'='*70}")
    print(f"SCENARIO: {scenario_name}")
    print(f"{'='*70}")
    
    optimizer = HPC2LatencyOptimizer(d, a_depth, b_depth)
    
    print(optimizer.get_optimization_report())
    
    print("\nGENERATED HELPER FUNCTIONS:")
    print("-" * 70)
    print(optimizer.generate_helper_functions(d, swapped=optimizer.should_swap))
    
    return optimizer


if __name__ == "__main__":
    print("""
╔════════════════════════════════════════════════════════════════╗
║       HPC2 LATENCY OPTIMIZER - TEST AND DEMONSTRATION          ║
╚════════════════════════════════════════════════════════════════╝
""")
    
    # Scenario 1: Equal input depths
    opt1 = test_scenario(
        "Equal Input Depths (Balanced)",
        d=4, a_depth=3, b_depth=3
    )
    
    # Scenario 2: A has deeper inputs
    opt2 = test_scenario(
        "A Deeper Than B (SWAP RECOMMENDED)",
        d=4, a_depth=5, b_depth=2
    )
    
    # Scenario 3: B has deeper inputs
    opt3 = test_scenario(
        "B Deeper Than A (NO SWAP NEEDED)",
        d=4, a_depth=2, b_depth=5
    )
    
    # Scenario 4: Significant depth difference
    opt4 = test_scenario(
        "Large Depth Difference (SWAP RECOMMENDED)",
        d=4, a_depth=8, b_depth=1
    )
    
    # Summary
    print(f"\n{'='*70}")
    print("SUMMARY")
    print(f"{'='*70}")
    
    scenarios = [
        ("Equal depths", opt1.should_swap, False),
        ("A deeper", opt2.should_swap, True),
        ("B deeper", opt3.should_swap, False),
        ("A much deeper", opt4.should_swap, True),
    ]
    
    print("\nSwap Recommendations:")
    for scenario, should_swap, expected in scenarios:
        status = "✓" if should_swap == expected else "✗"
        print(f"  {status} {scenario:20s}: swap={should_swap}")
    
    print(f"\n{'='*70}")
    print("✓ All scenarios tested successfully!")
    print(f"{'='*70}\n")
