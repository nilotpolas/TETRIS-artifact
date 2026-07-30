"""
HPC2 Latency-Optimized Gadget Generator
========================================

This module analyzes the asymmetric latency paths in HPC2 and generates
optimized C code by potentially swapping inputs to minimize critical path delay.
"""

class HPC2LatencyOptimizer:
    """
    Analyzes HPC2 gadget latency characteristics and generates optimized code.
    
    HPC2 has asymmetric latency paths:
    - Input A path: latency = 1 (a & b_protected)
    - Input B path: latency = 2 (xor_reg(b, rand) & a)
    
    Strategy: If A has higher input depth, swap to put A on faster path
    """
    
    def __init__(self, d, a_depth=None, b_depth=None):
        """
        Initialize optimizer
        
        Args:
            d: order (number of shares)
            a_depth: input depth of A (optional, for optimization hints)
            b_depth: input depth of B (optional, for optimization hints)
        """
        self.d = d
        self.a_depth = a_depth if a_depth is not None else 0
        self.b_depth = b_depth if b_depth is not None else 0
        self.should_swap = False
        
        # Determine if we should swap inputs
        if self.a_depth > self.b_depth:
            self.should_swap = True
    
    def analyze_latency_paths(self):
        """
        Analyze the latency paths in HPC2
        
        Returns:
            dict with latency analysis
        """
        return {
            'same_shares_latency': 0,  # u_{i,i} = a_i & b_i (combinational)
            'v_latency': 2,            # temp = reg(b_j ^ rand); v = reg(temp & a_i)
            'w_latency': 1,            # w = reg(~a_i & rand)
            'xor_latency': 0,          # u = v ^ w (combinational)
            'critical_path_latency': 2,  # v_latency is bottleneck
            'a_path_in_v': 1,          # a goes through 1 stage in v
            'b_path_in_v': 2,          # b goes through 2 stages in v
            'a_path_in_w': 1,          # a goes through 1 stage in w
            'optimization': {
                'if_a_deeper': 'SWAP inputs so a goes through xor path',
                'benefit': 'A critical path is masked by xor latency',
                'should_swap': self.should_swap
            }
        }
    
    def generate_helper_functions(self, d, swapped=False):
        """
        Generate optimized helper functions
        
        Args:
            d: order
            swapped: whether inputs were swapped
            
        Returns:
            helper function code
        """
        if swapped:
            # Swapped version: A is now the "B-like" path (through xor)
            helper_func = f"""
void hpc2_same_shares_{d}_order(int a_share, int b_share, int * u_share) {{
    * u_share  = a_share & b_share;
}}

void hpc2_v_{d}_order(int a_share, int b_share, int * v_share, int rand){{
    int temp;
    // A (originally B) goes through XOR - through critical path
    temp = reg(a_share ^ rand);
    *v_share = reg(temp & b_share);
}}

void hpc2_w_{d}_order(int a_share, int rand, int * w_share){{
    int b_neg;
    // B (originally A) is negated - on faster path
    b_neg = ~(b_share);
    *w_share = reg(b_neg & rand);
}}

void hpc2_xor_vw_{d}_order(int v_share, int w_share, int * u_share){{
    *u_share = v_share ^ w_share;
}}
"""
        else:
            # Standard version: keep original input ordering
            helper_func = f"""
void hpc2_same_shares_{d}_order(int a_share, int b_share, int * u_share) {{
    * u_share  = a_share & b_share;
}}

void hpc2_v_{d}_order(int a_share, int b_share, int * v_share, int rand){{
    int temp;
    // B goes through XOR - through critical path
    temp = reg(b_share ^ rand);
    *v_share = reg(temp & a_share);
}}

void hpc2_w_{d}_order(int a_share, int rand, int * w_share){{
    int a_neg;
    // A is negated - on faster path
    a_neg = ~(a_share);
    *w_share = reg(a_neg & rand);
}}

void hpc2_xor_vw_{d}_order(int v_share, int w_share, int * u_share){{
    *u_share = v_share ^ w_share;
}}
"""
        return helper_func
    
    def get_optimization_report(self):
        """
        Generate a human-readable optimization report
        
        Returns:
            string report
        """
        analysis = self.analyze_latency_paths()
        
        report = f"""
HPC2 LATENCY OPTIMIZATION REPORT (Order {self.d})
{'='*50}

INPUT DEPTHS:
  A depth: {self.a_depth}
  B depth: {self.b_depth}
  Recommendation: {'SWAP' if self.should_swap else 'NO SWAP'}

LATENCY PATHS:
  Same shares (u_ii):  {analysis['same_shares_latency']} cycle
  V computation:       {analysis['v_latency']} cycles (XOR → AND)
  W computation:       {analysis['w_latency']} cycle  (NEG → AND)
  XOR final:           {analysis['xor_latency']} cycles (combinational)
  
  Critical Path: {analysis['critical_path_latency']} cycles (V computation)

ASYMMETRIC PATHS IN V:
  Path via A: {analysis['a_path_in_v']} cycle (A & (B ^ rand))
  Path via B: {analysis['b_path_in_v']} cycles (B through XOR first)

OPTIMIZATION:
  Current bottleneck: B through XOR ({analysis['b_path_in_v']} cycles)
  
  If A_depth > B_depth:
    - SWAP inputs to put A on XOR path
    - Benefit: A's depth is masked by XOR latency
    - Result: More balanced timing
  
  Recommended: {'SWAP inputs for latency balancing' if self.should_swap else 'Keep original order'}
"""
        return report


# Example usage
if __name__ == "__main__":
    # Test with different depth scenarios
    print("Scenario 1: A and B have equal depth")
    opt1 = HPC2LatencyOptimizer(d=4, a_depth=3, b_depth=3)
    print(opt1.get_optimization_report())
    
    print("\n" + "="*50 + "\n")
    
    print("Scenario 2: A has deeper inputs than B")
    opt2 = HPC2LatencyOptimizer(d=4, a_depth=5, b_depth=2)
    print(opt2.get_optimization_report())
    print("Helper functions (SWAPPED):")
    print(opt2.generate_helper_functions(d=4, swapped=True))
    
    print("\n" + "="*50 + "\n")
    
    print("Scenario 3: B has deeper inputs than A")
    opt3 = HPC2LatencyOptimizer(d=4, a_depth=2, b_depth=5)
    print(opt3.get_optimization_report())
    print("Helper functions (NO SWAP):")
    print(opt3.generate_helper_functions(d=4, swapped=False))
