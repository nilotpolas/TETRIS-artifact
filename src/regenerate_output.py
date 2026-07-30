"""
Script to regenerate output.c with HPC2/HPC2O definitions
Run this after MRLC optimization to ensure all gadget definitions are included
"""

import os
import sys

def regenerate_output_with_definitions(mrlc_obj, d, output_path):
    """
    Regenerate output.c with proper HPC2/HPC2O definitions
    
    Parameters:
    -----------
    mrlc_obj : MRLC object
        The MRLC object after optimization
    d : int
        Masking order
    output_path : str
        Path to output.c file
    """
    from pycparser import parse_file, c_generator
    from transform_CFile.ctransfromer import ShareTransformer
    from Gadgets import HPC2, HPC2o
    
    print(f"\n{'='*80}")
    print("REGENERATING OUTPUT.C WITH GADGET DEFINITIONS")
    print('='*80)
    
    # Parse the inlined file
    inlined_file = os.path.abspath(r"./TestFiles/inlined_output/output.c")
    ast = parse_file(inlined_file)
    
    # Get gadget map and unique definitions
    gadget_map = mrlc_obj.get_gadget_definition()
    unique_definition_map = mrlc_obj.get_unique_gadgets_definition()
    
    print(f"\n[DEBUG] Initial unique definitions: {list(unique_definition_map.keys())}")
    
    # Check what gadgets are actually used
    all_gadgets_used = set()
    for entry in gadget_map.values():
        if isinstance(entry, dict):
            gadget = entry.get('gadget_name', '').lower()
        else:
            gadget = str(entry).lower()
        all_gadgets_used.add(gadget)
    
    print(f"[DEBUG] Gadgets used in circuit: {all_gadgets_used}")
    
    # Generate HPC2 if needed
    if 'hpc2' in all_gadgets_used and 'HPC2' not in unique_definition_map:
        print(f"[INFO] Generating HPC2 definition for order {d}...")
        try:
            hpc2_obj = HPC2(d)
            hpc2_def = str(hpc2_obj)
            if hpc2_def and not hpc2_def.startswith('<'):
                unique_definition_map['HPC2'] = hpc2_def
                print(f"[SUCCESS] HPC2 definition added")
            else:
                print(f"[WARNING] HPC2 generated invalid code, skipping")
        except Exception as e:
            print(f"[WARNING] Could not generate HPC2: {e}")
    
    # Generate HPC2o if needed
    if 'hpc2o' in all_gadgets_used and 'HPC2o' not in unique_definition_map:
        print(f"[INFO] Generating HPC2o definition for order {d}...")
        try:
            hpc2o_obj = HPC2o(d)
            hpc2o_def = str(hpc2o_obj)
            if hpc2o_def and not hpc2o_def.startswith('<'):
                unique_definition_map['HPC2o'] = hpc2o_def
                print(f"[SUCCESS] HPC2o definition added")
            else:
                print(f"[WARNING] HPC2o generated invalid code, skipping")
        except Exception as e:
            print(f"[WARNING] Could not generate HPC2o: {e}")
    
    print(f"\n[DEBUG] Final unique definitions: {list(unique_definition_map.keys())}")
    
    # Transform AST
    shareTransformer = ShareTransformer(d+1, gadget_map, unique_definition_map)
    transformed_ast = shareTransformer.transform(ast)
    
    gen = c_generator.CGenerator()
    
    # Write output
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    
    with open(output_path, 'w') as f:
        # Write all gadget definitions
        f.write("// === GADGET DEFINITIONS (hpc3o, hpc2o, etc.) ===\n")
        for gadget_name, func_str in unique_definition_map.items():
            f.write(f"\n// --- {gadget_name} ---\n")
            f.write(func_str)
            f.write("\n\n")
        
        # Write transformed code
        code = gen.visit(transformed_ast)
        f.write(code)
    
    print(f"\n[SUCCESS] Output written to {output_path}")
    print(f"[INFO] Included definitions: {list(unique_definition_map.keys())}")
    
    return unique_definition_map
