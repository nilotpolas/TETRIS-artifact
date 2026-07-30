"""
HPC Gadget Optimization Module - Simplified Version
Optimizes gadget selection by swapping HPC3/HPC3o with HPC2/HPC2o when arrival depths differ.
"""

import re
from typing import Dict, Tuple, Set

class HPC2OptimizationPass:
    """
    Optimizes gadget selection in MLRC objects by replacing
    HPC3/HPC3o with HPC2/HPC2o when inputs have unbalanced arrival depths.
    """
    
    def __init__(self, mlrc_obj, order):
        """Initialize optimizer with MLRC object."""
        self.mlrc_obj = mlrc_obj
        self.order = order
        
        # The actual gadget definitions are stored differently
        # gadget_definition maps: expression (like "M1 = T13 & T6") -> dict with gadget info
        self.gadget_map = mlrc_obj.gadget_definition
        
        self.swap_count = 0
        self.swapped_gates = {}
        
        print(f"[INFO] HPC2 Optimization Pass initialized for order {order}")
        print(f"[INFO] Found {len(self.gadget_map)} gadget assignments")
    
    def analyze_gadget_inputs(self, and_expression: str) -> Tuple[str, str, str, bool]:
        """Extract input operands from AND expression."""
        # Parse expressions like "M1 = T13 & T6" or just "T13 & T6"
        match = re.search(r'(\w+)\s*&\s*(\w+)', and_expression)
        if not match:
            return None, None, None, False
        
        a, b = match.groups()
        current_gadget_dict = self.gadget_map.get(and_expression, {})
        
        # Extract gadget name from dict structure
        if isinstance(current_gadget_dict, dict):
            gadget_name = current_gadget_dict.get('gadget_name', 'unknown').lower()
        else:
            gadget_name = str(current_gadget_dict).lower()
        
        is_hpc3o = 'hpc3o' in gadget_name
        
        return a, b, gadget_name, is_hpc3o
    
    def should_swap(self, input_a: str, input_b: str, current_gadget: str) -> Tuple[bool, str, str]:
        """
        Determine if swapping HPC3/HPC3o to HPC2/HPC2o is beneficial.
        """
        if current_gadget is None or 'hpc3' not in current_gadget.lower():
            return False, current_gadget, "not HPC3/HPC3o"
        
        # Use heuristic based on input variable types and numbers
        type_a = 'input' if input_a[0] in ['T', 'X'] else 'intermediate'
        type_b = 'input' if input_b[0] in ['T', 'X'] else 'intermediate'
        
        # Extract numeric parts for comparison
        try:
            num_a = int(''.join(filter(str.isdigit, input_a.split('_')[0])))
            num_b = int(''.join(filter(str.isdigit, input_b.split('_')[0])))
            num_diff = abs(num_a - num_b)
        except:
            num_diff = 0
        
        # Swap if types differ OR numbers are significantly different
        if type_a != type_b or num_diff >= 5:
            is_hpc3o = 'hpc3o' in current_gadget.lower()
            new_gadget = 'hpc2o' if is_hpc3o else 'hpc2'
            reason = f"{input_a}({type_a}) & {input_b}({type_b}), num_diff={num_diff}"
            return True, new_gadget, reason
        
        return False, current_gadget, f"{input_a} & {input_b} (balanced)"
    
    def optimize(self) -> Dict[str, Tuple[str, str]]:
        """Run optimization pass on all gadgets."""
        swapped = {}
        
        print(f"\n[OPTIMIZATION] Starting gadget optimization pass...")
        print(f"[OPTIMIZATION] Analyzing {len(self.gadget_map)} gadget assignments...\n")
        
        for expr_key, gadget_dict in list(self.gadget_map.items()):
            # Extract gadget name from dict structure
            if isinstance(gadget_dict, dict):
                gadget_name = gadget_dict.get('gadget_name', 'unknown').lower()
            else:
                gadget_name = str(gadget_dict).lower()
            
            # Only process HPC3/HPC3o gadgets
            if 'hpc3' not in gadget_name:
                continue
            
            # Analyze inputs from expression
            a, b, current_gad, is_opt = self.analyze_gadget_inputs(expr_key)
            if a is None:
                continue
            
            # Check if swap is beneficial
            should_swap_result, new_gadget, reason = self.should_swap(a, b, current_gad)
            
            if should_swap_result:
                self.swap_count += 1
                old_gadget = gadget_name
                
                # Update gadget map with new gadget name
                if isinstance(gadget_dict, dict):
                    # Update the 'gadget_name' key
                    self.gadget_map[expr_key]['gadget_name'] = new_gadget
                    # Also update func_name to match
                    if 'func_name' in self.gadget_map[expr_key]:
                        self.gadget_map[expr_key]['func_name'] = new_gadget.upper()
                else:
                    self.gadget_map[expr_key] = new_gadget
                
                self.swapped_gates[expr_key] = (old_gadget, new_gadget)
                
                print(f"[SWAP {self.swap_count}] {expr_key}")
                print(f"       Old: {old_gadget}")
                print(f"       New: {new_gadget}")
                print(f"       Reason: {reason}\n")
                
                swapped[expr_key] = (old_gadget, new_gadget)
        
        print(f"[SUCCESS] Optimization complete. Swapped {self.swap_count} gadgets.")
        return swapped
    
    def get_statistics(self) -> Dict:
        """Get optimization statistics."""
        hpc3_count = 0
        hpc2_count = 0
        
        for g_dict in self.gadget_map.values():
            if isinstance(g_dict, dict):
                gadget_name = g_dict.get('gadget_name', '').lower()
            else:
                gadget_name = str(g_dict).lower()
            
            if 'hpc3' in gadget_name:
                hpc3_count += 1
            elif 'hpc2' in gadget_name:
                hpc2_count += 1
        
        return {
            'swaps': self.swap_count,
            'swapped_gates': self.swapped_gates,
            'total_hpc3_gates': hpc3_count,
            'total_hpc2_gates': hpc2_count,
        }


def optimize_mlrc_gadgets(mlrc_obj, order: int) -> Dict:
    """
    High-level function to optimize MLRC gadget selection.
    
    This should be called AFTER MLRC._mrlc_dp() but BEFORE code generation.
    
    Parameters:
    -----------
    mlrc_obj : DSE_algorithm.mrlc.MLRC
        The MLRC object from the DSE pipeline
    order : int
        Masking order (1, 2, 3, etc.)
    
    Returns:
    --------
    Dict : Optimization results and statistics
    """
    optimizer = HPC2OptimizationPass(mlrc_obj, order)
    swapped = optimizer.optimize()
    stats = optimizer.get_statistics()
    
    print(f"\n[STATISTICS]")
    print(f"  Total HPC3/HPC3o gates: {stats['total_hpc3_gates']}")
    print(f"  Total HPC2/HPC2o gates: {stats['total_hpc2_gates']}")
    print(f"  Gadgets swapped: {stats['swaps']}")
    
    return {
        'swapped': swapped,
        'statistics': stats,
        'optimizer': optimizer
    }
