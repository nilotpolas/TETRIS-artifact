"""
@file test_register_hoisting.py
@brief Unit tests and examples for RegisterHoisting algorithm

Run with: python3 test_register_hoisting.py
"""

import sys
import os
sys.path.insert(0, os.path.abspath('.'))

import rustworkx as rx
from modules.GraphNode import ASTGraphNode, TextGraphNode
from modules.RegisterHoisting import RegisterHoisting


def create_simple_test_dfg():
    """Create a simple test DFG with known structure."""
    dfg = rx.PyDiGraph()
    
    # Create nodes: Source -> A -> {B, C, D} -> Sink
    source = dfg.add_node(TextGraphNode("Source"))
    a = dfg.add_node(TextGraphNode("A"))
    b = dfg.add_node(TextGraphNode("B"))
    c = dfg.add_node(TextGraphNode("C"))
    d = dfg.add_node(TextGraphNode("D"))
    sink = dfg.add_node(TextGraphNode("Sink"))
    
    # Edges with register counts
    dfg.add_edge(source, a, 0)      # Source -> A (0 regs)
    dfg.add_edge(a, b, 1)           # A -> B (1 reg)
    dfg.add_edge(a, c, 1)           # A -> C (1 reg)  
    dfg.add_edge(a, d, 1)           # A -> D (1 reg)
    dfg.add_edge(b, sink, 0)        # B -> Sink (0 regs)
    dfg.add_edge(c, sink, 0)        # C -> Sink (0 regs)
    dfg.add_edge(d, sink, 0)        # D -> Sink (0 regs)
    dfg.add_edge(sink, source, 0)   # Artificial back-edge (0 regs)
    
    return dfg, {'source': source, 'a': a, 'b': b, 'c': c, 'd': d, 'sink': sink}


def create_complex_test_dfg():
    """Create a more complex test with multiple hoisting opportunities."""
    dfg = rx.PyDiGraph()
    
    # Source -> A -> {B, C} -> D -> {E, F, G} -> Sink
    source = dfg.add_node(TextGraphNode("Source"))
    a = dfg.add_node(TextGraphNode("A"))
    b = dfg.add_node(TextGraphNode("B"))
    c = dfg.add_node(TextGraphNode("C"))
    d = dfg.add_node(TextGraphNode("D"))
    e = dfg.add_node(TextGraphNode("E"))
    f = dfg.add_node(TextGraphNode("F"))
    g = dfg.add_node(TextGraphNode("G"))
    sink = dfg.add_node(TextGraphNode("Sink"))
    
    # Build graph
    dfg.add_edge(source, a, 0)
    dfg.add_edge(a, b, 0)
    dfg.add_edge(a, c, 0)
    dfg.add_edge(b, d, 1)
    dfg.add_edge(c, d, 0)
    dfg.add_edge(d, e, 1)           # High fanout from D
    dfg.add_edge(d, f, 1)
    dfg.add_edge(d, g, 1)
    dfg.add_edge(e, sink, 0)
    dfg.add_edge(f, sink, 0)
    dfg.add_edge(g, sink, 0)
    dfg.add_edge(sink, source, 0)
    
    return dfg, {'source': source, 'a': a, 'b': b, 'c': c, 'd': d, 'e': e, 'f': f, 'g': g, 'sink': sink}


def test_simple_hoisting():
    """Test hoisting on a simple 1-in/3-out node."""
    print("\n" + "="*70)
    print("TEST 1: Simple High-Fanout Node (1 fanin, 3 fanout)")
    print("="*70)
    
    dfg, nodes = create_simple_test_dfg()
    hoisting = RegisterHoisting(dfg, debug=True)
    
    print("\nBefore Hoisting:")
    hoisting.print_dfg_stats()
    
    # Count initial regs
    regs_before = hoisting._count_total_registers()
    print(f"\nInitial registers: {regs_before}")
    
    # Apply hoisting
    stats = hoisting.apply_hoisting(threshold=1, max_iterations=5)
    
    # Check result
    print(f"\nExpected: 3 regs → 1 reg (2 saved)")
    print(f"Actual: {stats['total_registers_before']} → {stats['total_registers_after']} ({stats['registers_saved']} saved)")
    
    # Verify
    assert stats['total_registers_before'] == 3, "Initial count should be 3"
    assert stats['total_registers_after'] == 1, "Final count should be 1"
    assert stats['registers_saved'] == 2, "Should save 2 registers"
    
    print("✓ TEST 1 PASSED\n")


def test_complex_hoisting():
    """Test hoisting on a more complex structure with multiple candidates."""
    print("\n" + "="*70)
    print("TEST 2: Complex Multi-Level Hoisting")
    print("="*70)
    
    dfg, nodes = create_complex_test_dfg()
    hoisting = RegisterHoisting(dfg, debug=True)
    
    print("\nBefore Hoisting:")
    hoisting.print_dfg_stats()
    
    regs_before = hoisting._count_total_registers()
    print(f"\nInitial registers: {regs_before}")
    
    # Apply hoisting
    stats = hoisting.apply_hoisting(threshold=1, max_iterations=5)
    
    print(f"\nExpected: 4 regs → ? (D's 3 fanout regs hoist to B-C path)")
    print(f"Actual: {stats['total_registers_before']} → {stats['total_registers_after']} ({stats['registers_saved']} saved)")
    
    # Verify validation
    is_valid = hoisting.validate_scheduling()
    assert is_valid, "Scheduling should remain valid"
    
    print("✓ TEST 2 PASSED\n")


def test_no_hoisting_same_fanin_fanout():
    """Test that nodes with equal fanin/fanout don't get hoisted."""
    print("\n" + "="*70)
    print("TEST 3: No Hoisting When Fanin == Fanout")
    print("="*70)
    
    dfg = rx.PyDiGraph()
    
    # Linear chain: Source -> A -> B -> C -> Sink
    source = dfg.add_node(TextGraphNode("Source"))
    a = dfg.add_node(TextGraphNode("A"))
    b = dfg.add_node(TextGraphNode("B"))
    c = dfg.add_node(TextGraphNode("C"))
    sink = dfg.add_node(TextGraphNode("Sink"))
    
    dfg.add_edge(source, a, 1)
    dfg.add_edge(a, b, 1)
    dfg.add_edge(b, c, 1)
    dfg.add_edge(c, sink, 0)
    dfg.add_edge(sink, source, 0)
    
    hoisting = RegisterHoisting(dfg, debug=True)
    
    regs_before = hoisting._count_total_registers()
    stats = hoisting.apply_hoisting(threshold=1, max_iterations=5)
    
    print(f"\nLinear chain (1-in, 1-out): {regs_before} → {stats['total_registers_after']}")
    assert stats['registers_saved'] == 0, "Linear chain should not be hoisted"
    
    print("✓ TEST 3 PASSED\n")


def test_scheduling_validity():
    """Test that hoisting doesn't create negative weights."""
    print("\n" + "="*70)
    print("TEST 4: Scheduling Validity Check")
    print("="*70)
    
    dfg, nodes = create_simple_test_dfg()
    hoisting = RegisterHoisting(dfg, debug=False)
    
    stats = hoisting.apply_hoisting(threshold=1, max_iterations=5)
    
    is_valid = hoisting.validate_scheduling()
    assert is_valid, "Scheduling must remain valid after hoisting"
    
    # Check for negative weights manually
    for edge in dfg.weighted_edge_list():
        assert edge[2] >= 0, f"Negative weight on edge {edge[0]} -> {edge[1]}"
    
    print("✓ TEST 4 PASSED: All edge weights remain non-negative\n")


def test_multi_iteration_convergence():
    """Test that algorithm converges in multiple iterations."""
    print("\n" + "="*70)
    print("TEST 5: Multi-Iteration Convergence")
    print("="*70)
    
    dfg, nodes = create_complex_test_dfg()
    hoisting = RegisterHoisting(dfg, debug=True)
    
    stats = hoisting.apply_hoisting(threshold=1, max_iterations=10)
    
    print(f"\nConverged in {stats['iterations']} iterations")
    assert stats['iterations'] > 0, "Should run at least 1 iteration"
    assert stats['iterations'] <= 10, "Should converge within max_iterations"
    
    print("✓ TEST 5 PASSED\n")


def run_all_tests():
    """Run all test cases."""
    print("\n" + "="*70)
    print("REGISTER HOISTING TEST SUITE")
    print("="*70)
    
    try:
        test_simple_hoisting()
        test_complex_hoisting()
        test_no_hoisting_same_fanin_fanout()
        test_scheduling_validity()
        test_multi_iteration_convergence()
        
        print("\n" + "="*70)
        print("ALL TESTS PASSED ✓")
        print("="*70 + "\n")
        
    except AssertionError as e:
        print(f"\n✗ TEST FAILED: {e}\n")
        return False
    except Exception as e:
        print(f"\n✗ ERROR: {e}\n")
        import traceback
        traceback.print_exc()
        return False
    
    return True


if __name__ == "__main__":
    success = run_all_tests()
    sys.exit(0 if success else 1)
