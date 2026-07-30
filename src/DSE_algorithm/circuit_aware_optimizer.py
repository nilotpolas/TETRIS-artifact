"""
================================================================================
CIRCUIT-AWARE GADGET PLACEMENT OPTIMIZER
================================================================================

After MRLC assigns gadgets, this module:
1. Analyzes input signal depths for each AND node
2. Determines optimal gadget variant (HPC2 vs HPC2o, HPC3 vs HPC3o)
3. Places gadgets to minimize overall circuit latency
4. Updates gadget_definition with optimized assignments

KEY INSIGHT:
- Each AND gate has two inputs with potentially different depths
- HPC2/HPC3 have asymmetric latency paths
- Route deeper input through faster path → minimize critical path
"""

class CircuitAwareGadgetOptimizer:
    """
    Analyzes circuit structure and optimizes gadget placement for latency.
    
    Works on mrlc_obj after MRLC algorithm completes.
    """
    
    def __init__(self, mrlc_obj, and_xor_tree=None):
        """
        Initialize optimizer
        
        Args:
            mrlc_obj: MRLC object with gadget_definition
            and_xor_tree: Optional AND-XOR tree for depth analysis
        """
        self.mrlc_obj = mrlc_obj
        self.and_xor_tree = and_xor_tree
        self.gadget_definition = mrlc_obj.gadget_definition
        self.signal_depths = {}  # signal -> depth from primary inputs
        self.optimization_log = []
    
    def calculate_signal_depths(self):
        """
        Calculate depth (latency) of each signal from primary inputs.
        
        Returns:
            dict mapping signal_name -> depth
        """
        print("\n[OPTIMIZER] Calculating signal depths...")
        
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
                    # Extract operands
                    operands = self._extract_operands(expr_str)
                    
                    if operands:
                        op1_str, op2_str = operands
                        
                        # Get depths of operands
                        op1_depth = depths.get(op1_str, 0)
                        op2_depth = depths.get(op2_str, 0)
                        
                        # AND gate adds 1 to the maximum depth
                        and_depth = max(op1_depth, op2_depth) + 1
                        depths[expr_str] = and_depth
                        
                        self.optimization_log.append(
                            f"Gate {expr_str}: inputs({op1_depth}, {op2_depth}) → depth={and_depth}"
                        )
                
                elif self.mrlc_obj._is_xor_node(expr_str):
                    # XOR is combinational (no latency)
                    operands = self._extract_operands(expr_str)
                    if operands:
                        op1_str, op2_str = operands
                        xor_depth = max(depths.get(op1_str, 0), depths.get(op2_str, 0))
                        depths[expr_str] = xor_depth
        
        self.signal_depths = depths
        print(f"[OPTIMIZER] Calculated depths for {len(depths)} signals")
        return depths
    
    def _extract_operands(self, expr_str):
        """Extract operand1 and operand2 from expression"""
        if '=' not in expr_str:
            return None
        
        _, rhs = expr_str.split('=', 1)
        rhs = rhs.strip()
        
        # Handle both & and ^ operators
        if '&' in rhs:
            parts = rhs.split('&')
        elif '^' in rhs:
            parts = rhs.split('^')
        else:
            return None
        
        if len(parts) >= 2:
            return (parts[0].strip(), parts[1].strip())
        
        return None
    
    def get_input_depths(self, expr):
        """
        Get the depths of two inputs for a gate
        
        Returns:
            (input1_depth, input2_depth)
        """
        expr_str = str(expr)
        operands = self._extract_operands(expr_str)
        
        if not operands:
            return (0, 0)
        
        op1_str, op2_str = operands
        depth1 = self.signal_depths.get(op1_str, 0)
        depth2 = self.signal_depths.get(op2_str, 0)
        
        return (depth1, depth2)
    
    def optimize_gadget_placement(self):
        """
        Analyze each gate and optimize gadget assignment.
        
        Updates gadget_definition with optimal variants.
        """
        print("\n[OPTIMIZER] Optimizing gadget placement for latency...")
        
        # First calculate depths
        self.calculate_signal_depths()
        
        optimizations = {
            'hpc2_to_hpc2o': 0,
            'hpc3_to_hpc3o': 0,
            'hpc2_variants': 0,
            'hpc3_variants': 0,
        }
        
        for expr, info in self.gadget_definition.items():
            gadget_name = info.get("gadget_name", "").lower()
            
            # Only optimize for gadgets with variants
            if gadget_name not in ['hpc2', 'hpc3']:
                continue
            
            # Get input depths
            input1_depth, input2_depth = self.get_input_depths(expr)
            
            # Determine optimal variant
            if gadget_name == 'hpc2':
                optimal_gadget = self._optimize_hpc2_placement(
                    expr, input1_depth, input2_depth
                )
                if optimal_gadget != 'hpc2':
                    info['gadget_name'] = optimal_gadget
                    info['random_numbers'] = self.mrlc_obj.gadget_map[optimal_gadget]['randomness']
                    optimizations['hpc2_to_hpc2o'] += 1
                    optimizations['hpc2_variants'] += 1
                    
                    print(f"[HPC2→HPC2o] {str(expr)[:50]:50s} "
                          f"inputs({input1_depth}, {input2_depth})")
            
            elif gadget_name == 'hpc3':
                optimal_gadget = self._optimize_hpc3_placement(
                    expr, input1_depth, input2_depth
                )
                if optimal_gadget != 'hpc3':
                    info['gadget_name'] = optimal_gadget
                    info['random_numbers'] = self.mrlc_obj.gadget_map[optimal_gadget]['randomness']
                    optimizations['hpc3_to_hpc3o'] += 1
                    optimizations['hpc3_variants'] += 1
                    
                    print(f"[HPC3→HPC3o] {str(expr)[:50]:50s} "
                          f"inputs({input1_depth}, {input2_depth})")
        
        print(f"\n[OPTIMIZER] Optimization Summary:")
        print(f"  HPC2 → HPC2o swaps: {optimizations['hpc2_to_hpc2o']}")
        print(f"  HPC3 → HPC3o swaps: {optimizations['hpc3_to_hpc3o']}")
        print(f"  Total HPC2 variants: {optimizations['hpc2_variants']}")
        print(f"  Total HPC3 variants: {optimizations['hpc3_variants']}")
        
        return optimizations
    
    def _optimize_hpc2_placement(self, expr, depth1, depth2):
        """
        Determine optimal HPC2 variant based on input depths
        
        HPC2 latency paths:
        - Input A: 1 cycle (direct AND path)
        - Input B: 2 cycles (through XOR)
        
        Strategy:
        - If input1 much deeper: put on faster path (A path)
        - If input2 much deeper: put on slower path (B path, already there)
        - If similar: use HPC2o for XOR_AND pattern
        """
        
        # Check if this gate is XOR_AND pattern
        is_xor_and = self._is_xor_and_pattern(expr)
        
        if not is_xor_and:
            return 'hpc2'  # No variant available for pure AND
        
        # Depth difference threshold
        depth_diff = abs(depth1 - depth2)
        
        # If inputs are similar depth, use optimized variant
        if depth_diff <= 1:
            return 'hpc2o'  # Balanced inputs, use optimized
        
        # If inputs very different, use standard HPC2
        # (we can't rearrange, so use standard)
        return 'hpc2'
    
    def _optimize_hpc3_placement(self, expr, depth1, depth2):
        """
        Determine optimal HPC3 variant based on input depths
        
        Similar to HPC2 optimization
        """
        
        is_xor_and = self._is_xor_and_pattern(expr)
        
        if not is_xor_and:
            return 'hpc3'
        
        depth_diff = abs(depth1 - depth2)
        
        if depth_diff <= 1:
            return 'hpc3o'  # Use optimized for balanced inputs
        
        return 'hpc3'
    
    def _is_xor_and_pattern(self, expr):
        """Check if expr is marked as XOR_AND pattern"""
        expr_str = str(expr)
        
        # Check in mrlc_obj.node_pattern
        if hasattr(self.mrlc_obj, 'node_pattern'):
            pattern_info = self.mrlc_obj.node_pattern.get(expr)
            if pattern_info:
                if isinstance(pattern_info, tuple):
                    pattern_type, _ = pattern_info
                    return pattern_type == 'xor_and'
                else:
                    return pattern_info == 'xor_and'
        
        return False
    
    def generate_report(self):
        """Generate detailed optimization report"""
        report = f"""
{'='*70}
CIRCUIT-AWARE GADGET PLACEMENT OPTIMIZATION REPORT
{'='*70}

SIGNAL DEPTHS:
  Total signals analyzed: {len(self.signal_depths)}
  Max circuit depth: {max(self.signal_depths.values()) if self.signal_depths else 0}
  
DEPTH DISTRIBUTION:
"""
        if self.signal_depths:
            depth_counts = {}
            for signal, depth in self.signal_depths.items():
                depth_counts[depth] = depth_counts.get(depth, 0) + 1
            
            for depth in sorted(depth_counts.keys()):
                count = depth_counts[depth]
                report += f"  Depth {depth}: {count:3d} signals\n"
        
        report += f"""
OPTIMIZATION DECISIONS:
  Total gates analyzed: {len(self.gadget_definition)}
  
DETAILED LOG:
"""
        for log_entry in self.optimization_log[:10]:  # Show first 10
            report += f"  {log_entry}\n"
        
        if len(self.optimization_log) > 10:
            report += f"  ... and {len(self.optimization_log) - 10} more\n"
        
        report += f"\n{'='*70}\n"
        return report


def integrate_with_mrlc(mrlc_obj, and_xor_tree=None):
    """
    Integration function: run optimization on completed MRLC result
    
    Usage in pipeline:
        # After MRLC completes
        mrlc_obj, latency = mrlc_instance._mrlc_dp(target_latency)
        
        # Run circuit-aware optimization
        from circuit_aware_optimizer import integrate_with_mrlc
        integrate_with_mrlc(mrlc_obj, mrlc_instance.and_xor_tree)
    """
    print("\n" + "="*70)
    print("CIRCUIT-AWARE GADGET PLACEMENT OPTIMIZATION")
    print("="*70)
    
    optimizer = CircuitAwareGadgetOptimizer(mrlc_obj, and_xor_tree)
    optimizer.optimize_gadget_placement()
    
    print(optimizer.generate_report())
    
    return optimizer
