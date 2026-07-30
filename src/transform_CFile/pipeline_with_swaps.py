"""
================================================================================
COMPLETE PIPELINE INTEGRATION: MRLC + OPERAND SWAP + SHARETRANSFORMER
================================================================================

This script shows the complete flow from MRLC to code generation with
operand swapping integrated.
"""

import os
import sys
import importlib
from pycparser import parse_file, c_ast, c_generator
from io import StringIO

def run_complete_pipeline(d, inlined_file_path, output_c_path, mrlc_obj):
    """
    Complete pipeline:
    1. MRLC gadget assignment
    2. Operand swap optimization
    3. ShareTransformer with swap info
    4. Code generation
    
    Args:
        d: Order (number of shares - 1)
        inlined_file_path: Path to inlined C code
        output_c_path: Output path for generated C code
        mrlc_obj: MRLC object with gadget definitions
    """
    
    print("\n" + "="*80)
    print("COMPLETE PIPELINE: MRLC → OPERAND SWAP → CODE GENERATION")
    print("="*80 + "\n")
    
    # ======= STEP 1: Parse input file =======
    print("[PIPELINE] Step 1: Parse inlined C file")
    ast = parse_file(inlined_file_path)
    print(f"[SUCCESS] Parsed: {inlined_file_path}\n")
    
    # ======= STEP 2: Get gadget definitions from MRLC =======
    print("[PIPELINE] Step 2: Get gadget definitions from MRLC")
    gadget_map = mrlc_obj.gadget_definition
    print(f"[SUCCESS] Got {len(gadget_map)} gadget definitions\n")
    
    # ======= STEP 3: Get unique gadget definitions =======
    print("[PIPELINE] Step 3: Get unique gadget definitions from MRLC")
    unique_definition_map = mrlc_obj.get_unique_gadgets_definition()
    print(f"[SUCCESS] Unique gadget definitions:")
    for gadget_name in sorted(unique_definition_map.keys()):
        func_code = unique_definition_map[gadget_name]
        lines = len(func_code.split('\n'))
        print(f"  ✓ {gadget_name:8s}: {lines:3d} lines")
    print()
    
    # ======= STEP 4: Run operand swap optimization =======
    print("[PIPELINE] Step 4: Run operand swap optimization")
    if not hasattr(mrlc_obj, 'operand_swap_optimizer'):
        print("[ERROR] MRLC object doesn't have operand_swap_optimizer!")
        print("[INFO] Make sure MRLC Step 6.5 was executed")
        print("[INFO] Try: from DSE_algorithm.operand_swap_optimizer import integrate_operand_swapping")
        print("[INFO]      integrate_operand_swapping(mrlc_obj)")
        operand_swap_optimizer = None
    else:
        operand_swap_optimizer = mrlc_obj.operand_swap_optimizer
        print(f"[SUCCESS] Operand swap optimizer available")
        print(f"          Total swaps identified: {operand_swap_optimizer.swaps_performed}\n")
    
    # ======= STEP 5: Create ShareTransformer with swap info =======
    print("[PIPELINE] Step 5: Create ShareTransformer with operand swap info")
    
    # Import after we know we have the files
    from transform_CFile.ctransfromer import ShareTransformer
    
    # Pass the operand swap optimizer to ShareTransformer!
    share_transformer = ShareTransformer(
        d + 1,  # num_shares
        gadget_map,
        unique_definition_map,
        operand_swap_optimizer=operand_swap_optimizer  # NEW PARAMETER!
    )
    print("[SUCCESS] ShareTransformer created with operand swap optimizer\n")
    
    # ======= STEP 6: Transform circuit =======
    print("[PIPELINE] Step 6: Transform circuit (applying operand swaps during code gen)")
    
    # Suppress verbose output during transformation
    old_stdout = sys.stdout
    sys.stdout = StringIO()
    
    try:
        transformed_ast = share_transformer.transform(ast)
    finally:
        sys.stdout = old_stdout
    
    print("[SUCCESS] Circuit transformation complete\n")
    
    # ======= STEP 7: Generate C code =======
    print("[PIPELINE] Step 7: Generate C code from transformed AST")
    gen = c_generator.CGenerator()
    print("[SUCCESS] C generator created\n")
    
    # ======= STEP 8: Write output file =======
    print("[PIPELINE] Step 8: Write output to file")
    os.makedirs(os.path.dirname(output_c_path), exist_ok=True)
    
    with open(output_c_path, 'w') as f:
        f.write("// === GADGET DEFINITIONS ===\n")
        for gadget_name, func_str in unique_definition_map.items():
            f.write(f"\n// --- {gadget_name} ---\n")
            f.write(func_str)
            f.write("\n\n")
        
        code = gen.visit(transformed_ast)
        f.write(code)
    
    print(f"[SUCCESS] Output written to {output_c_path}\n")
    
    # ======= STEP 9: Print summary =======
    print("[PIPELINE] Step 9: Summary")
    print("="*80)
    print(f"[SUMMARY] Operand swaps applied: {share_transformer.swap_count}")
    if operand_swap_optimizer:
        print(f"[SUMMARY] Operand swaps identified: {operand_swap_optimizer.swaps_performed}")
    print("[SUMMARY] Code generation complete!")
    print("="*80 + "\n")
    
    return transformed_ast, output_c_path


# ============================================================================
# USAGE EXAMPLE
# ============================================================================

if __name__ == "__main__":
    """
    Example usage:
    
    # Setup paths
    inlined_file = os.path.abspath(r"./TestFiles/inlined_output/output.c")
    output_c = os.path.abspath(r"./TestFiles/share_output/output.c")
    
    # Assume mrlc_obj is your MRLC result with optimization already done
    # (from: mrlc = MRLC(...); gadget_def, latency = mrlc._mrlc_dp(...))
    
    # Run complete pipeline
    transformed_ast, output_path = run_complete_pipeline(
        d=1,  # Order (2 shares)
        inlined_file_path=inlined_file,
        output_c_path=output_c,
        mrlc_obj=mrlc_obj
    )
    
    print(f"\n✓ Generated file: {output_path}")
    """
    pass
