"""
================================================================================
OPERAND SWAPPING OPTIMIZER FOR HPC2/HPC2o GADGETS
================================================================================

Optimizes critical path by intelligently swapping operand order in
HPC2 and HPC2o gadgets based on input depths and usage patterns.
"""

class OperandSwappingOptimizer:
    """
    Analyzes HPC2/HPC2o gadget operands and decides if swapping reduces latency.
    
    HPC2 Latency Paths:
      Input A: 1 cycle (faster)
      Input B: 2 cycles (slower - through XOR)
    
    Strategy:
      Put shallower/more-used input on slower path (B)
      Put deeper/less-used input on faster path (A)
      Reduces overall critical path
    """
    
    def __init__(self, mrlc_obj):
        """Initialize with MRLC object containing gadget definitions"""
        self.mrlc_obj = mrlc_obj
        self.gadget_definition = mrlc_obj.gadget_definition
        self.signal_depths = {}
        self.signal_usage_count = {}
        self.swaps_performed = 0
        self.operand_swaps = {}  # Maps gate → (op1, op2, should_swap, reason)
    
    def calculate_signal_depths(self):
        """Calculate depth of each signal from primary inputs"""
        depths = {}
        
        # Primary inputs have depth 0
        if hasattr(self.mrlc_obj, 'primary_inputs'):
            for pi in self.mrlc_obj.primary_inputs:
                depths[str(pi)] = 0
        
        # Process nodes level by level
        for lvl in sorted(self.mrlc_obj.nodes_by_level.keys()):
            for expr in self.mrlc_obj.nodes_by_level[lvl]:
                expr_str = str(expr)
                
                if self.mrlc_obj._is_and_node(expr_str):
                    operands = self._extract_operands(expr_str)
                    if operands:
                        op1, op2 = operands
                        depth1 = depths.get(op1, 0)
                        depth2 = depths.get(op2, 0)
                        depths[expr_str] = max(depth1, depth2) + 1
        
        self.signal_depths = depths
        return depths
    
    def count_signal_usage(self):
        """Count how many times each signal is used as input to gates"""
        usage = {}
        
        for expr, info in self.gadget_definition.items():
            operands = self._extract_operands(str(expr))
            if operands:
                op1, op2 = operands
                usage[op1] = usage.get(op1, 0) + 1
                usage[op2] = usage.get(op2, 0) + 1
        
        self.signal_usage_count = usage
        return usage
    
    def _extract_operands(self, expr_str):
        """Extract operand1 and operand2 from expression"""
        if '=' not in expr_str:
            return None
        
        _, rhs = expr_str.split('=', 1)
        rhs = rhs.strip()
        
        if '&' in rhs:
            parts = rhs.split('&')
        elif '^' in rhs:
            parts = rhs.split('^')
        else:
            return None
        
        if len(parts) >= 2:
            return (parts[0].strip(), parts[1].strip())
        
        return None
    
    def should_swap_operands(self, expr, operand1, operand2):
        """
        Decide if swapping operands reduces critical path latency
        
        Returns:
            (should_swap, reason)
        """
        depth1 = self.signal_depths.get(operand1, 0)
        depth2 = self.signal_depths.get(operand2, 0)
        usage1 = self.signal_usage_count.get(operand1, 0)
        usage2 = self.signal_usage_count.get(operand2, 0)
        
        # Strategy 1: If depths are different, put shallower on faster path (A)
        if depth1 != depth2:
            # A path: 1 cycle (faster)
            # B path: 2 cycles (slower)
            
            if depth2 > depth1:
                # operand2 is deeper → should be on slower path (B)
                # operand1 is shallower → should be on faster path (A)
                # Current: op1→A, op2→B (correct!)
                return (False, "Depths already optimized: deeper on B path")
            else:
                # operand1 is deeper → should be on slower path (B)
                # operand2 is shallower → should be on faster path (A)
                # Need to SWAP: op2→A, op1→B
                return (True, f"Swap: deeper({depth1}) to B, shallower({depth2}) to A")
        
        # Strategy 2: Depths equal, use usage patterns
        elif depth1 == depth2:
            if usage1 > usage2:
                # op1 used more → might benefit from faster path (A)
                # But currently on A, so keep it
                return (False, "Usage balanced, no swap needed")
            elif usage2 > usage1:
                # op2 used more → should be on faster path (A)
                # Currently on B, need to SWAP
                return (True, f"Swap: higher usage({usage2}) to A path")
            else:
                # Both equal, no optimization needed
                return (False, "Both depths and usage equal, no swap")
        
        return (False, "No optimization needed")
    
    def optimize_operand_order(self):
        """
        Analyze each gate and decide if operand swapping helps
        
        Updates gadget_definition with swap information
        """
        print("\n" + "="*70)
        print("OPERAND SWAPPING OPTIMIZATION")
        print("="*70 + "\n")
        
        # Calculate depths and usage
        self.calculate_signal_depths()
        self.count_signal_usage()
        
        print(f"[SWAP-OPT] Signal depths calculated: {len(self.signal_depths)} signals")
        print(f"[SWAP-OPT] Signal usage counted: {len(self.signal_usage_count)} signals\n")
        
        print(f"[SWAP-OPT] Analyzing {len(self.gadget_definition)} gates for operand swapping...\n")
        
        swaps = 0
        no_swaps = 0
        
        for expr, info in self.gadget_definition.items():
            gadget_name = info.get("gadget_name", "").lower()
            
            # Only optimize for HPC2 and HPC2o (have asymmetric paths)
            if gadget_name not in ['hpc2', 'hpc2o']:
                continue
            
            # Extract operands
            operands = self._extract_operands(str(expr))
            if not operands:
                continue
            
            op1, op2 = operands
            should_swap, reason = self.should_swap_operands(expr, op1, op2)
            
            # Store swap decision
            self.operand_swaps[str(expr)] = {
                'op1': op1,
                'op2': op2,
                'should_swap': should_swap,
                'reason': reason,
                'depth1': self.signal_depths.get(op1, 0),
                'depth2': self.signal_depths.get(op2, 0),
                'usage1': self.signal_usage_count.get(op1, 0),
                'usage2': self.signal_usage_count.get(op2, 0),
            }
            
            if should_swap:
                # Mark in gadget definition for code generation
                info['operands_swapped'] = True
                swaps += 1
                print(f"[SWAP] {str(expr)[:50]:50s}")
                print(f"       {reason}")
                print(f"       Depths: {op1}({self.signal_depths.get(op1, 0)}) ↔ "
                      f"{op2}({self.signal_depths.get(op2, 0)})")
                print(f"       Usage: {op1}({self.signal_usage_count.get(op1, 0)}) ↔ "
                      f"{op2}({self.signal_usage_count.get(op2, 0)})\n")
            else:
                no_swaps += 1
        
        self.swaps_performed = swaps
        
        print(f"\n[SWAP-OPT] OPTIMIZATION SUMMARY:")
        print(f"[SWAP-OPT]   Operands swapped: {swaps}")
        print(f"[SWAP-OPT]   No swap needed: {no_swaps}")
        print(f"[SWAP-OPT]   Total gates analyzed: {len(self.operand_swaps)}\n")
        
        return swaps
    
    def get_swap_info(self, expr):
        """Get swap information for a specific gate"""
        return self.operand_swaps.get(str(expr), None)
    
    def should_swap_for_gate(self, expr):
        """Check if operands should be swapped for this gate"""
        info = self.get_swap_info(expr)
        return info['should_swap'] if info else False
    
    def generate_report(self):
        """Generate detailed optimization report"""
        report = f"""
{'='*70}
OPERAND SWAPPING OPTIMIZATION REPORT
{'='*70}

SIGNAL ANALYSIS:
  Total signals: {len(self.signal_depths)}
  Max circuit depth: {max(self.signal_depths.values()) if self.signal_depths else 0}
  
USAGE ANALYSIS:
  Most used signals:
"""
        
        # Show top 5 most used signals
        sorted_usage = sorted(self.signal_usage_count.items(), 
                            key=lambda x: x[1], reverse=True)
        for signal, count in sorted_usage[:5]:
            depth = self.signal_depths.get(signal, 0)
            report += f"    {signal:20s}: used {count}x, depth {depth}\n"
        
        report += f"""
OPTIMIZATION DECISIONS:
  Operands swapped: {self.swaps_performed}
  
DEPTH DISTRIBUTION:
"""
        
        depth_counts = {}
        for signal, depth in self.signal_depths.items():
            depth_counts[depth] = depth_counts.get(depth, 0) + 1
        
        for depth in sorted(depth_counts.keys()):
            count = depth_counts[depth]
            report += f"    Depth {depth}: {count} signals\n"
        
        report += f"\n{'='*70}\n"
        return report


def integrate_operand_swapping(mrlc_obj):
    """
    Integration function: run operand swap optimization on completed MRLC result
    
    Usage in pipeline:
        # After MRLC completes
        from operand_swap_optimizer import integrate_operand_swapping
        integrate_operand_swapping(mrlc_obj)
    """
    print("\n" + "="*70)
    print("OPERAND SWAPPING OPTIMIZATION FOR HPC2/HPC2o")
    print("="*70)
    
    optimizer = OperandSwappingOptimizer(mrlc_obj)
    swaps = optimizer.optimize_operand_order()
    
    print(optimizer.generate_report())
    
    # Store optimizer in mrlc_obj for later use
    mrlc_obj.operand_swap_optimizer = optimizer
    
    return optimizer
