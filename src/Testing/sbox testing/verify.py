import re
import os
import subprocess
import sys

# --- Configuration ---
MASKED_FILE = "output.c"       
GOLDEN_FILE = "golden_sbox.c"  # Note: Ensure this file contains your 8-bit golden code
TEST_FILE   = "tb_verify.c"    
EXECUTABLE  = "./verify_sbox"  

def parse_signature(content, filename):
    match = re.search(r'void\s+sbox\s*\((.*?)\)', content, re.DOTALL)
    if not match:
        print(f"[Error] Could not find 'void sbox(...)' in {filename}")
        sys.exit(1)

    args_str = match.group(1)
    raw_args_list = [x.strip() for x in args_str.split(',') if x.strip()]
    
    parsed_args = []
    for arg in raw_args_list:
        parts = arg.split()
        var_name = parts[-1].replace('*', '') 
        full_type = " ".join(parts[:-1])
        if '*' in parts[-1]: full_type += "*" 
        
        parsed_args.append({
            'full_decl': arg,
            'name': var_name,
            'is_ptr': '*' in arg or '*' in full_type
        })
    return parsed_args

def generate_testbench():
    # 1. Read files
    with open(MASKED_FILE, 'r') as f:
        masked_code = f.read()
    with open(GOLDEN_FILE, 'r') as f:
        golden_code = f.read()

    # 2. Parse signatures BEFORE renaming them
    masked_args = parse_signature(masked_code, MASKED_FILE)
    golden_args = parse_signature(golden_code, GOLDEN_FILE)

    # 3. Prevent Memory Corruption: Upgrade booleans to standard 32-bit ints
    masked_code = masked_code.replace("void sbox", "void sbox_masked")
    masked_code = masked_code.replace("_Bool", "int").replace("bool", "int")
    
    golden_code = golden_code.replace("void sbox", "void sbox_golden")
    golden_code = golden_code.replace("_Bool", "int").replace("bool", "int")

    # 4. Auto-Detect S-Box Bit Size (4-bit vs 8-bit)
    num_bits = 0
    for arg in golden_args:
        name_lower = arg['name'].lower()
        if name_lower.startswith('x'):
            idx_match = re.search(r'\d+', name_lower)
            if idx_match:
                num_bits = max(num_bits, int(idx_match.group()) + 1)
    
    if num_bits == 0:
        print("[Error] Could not detect input bit size. Defaulting to 4.")
        num_bits = 4

    num_iterations = 1 << num_bits # 2^4 = 16, 2^8 = 256

    # 5. Dynamically construct Golden Call Arguments
    golden_call_args = []
    for arg in golden_args:
        name = arg['name'].lower()
        if "dec" in name:
            golden_call_args.append("1") # True
        elif name.startswith("x"):
            idx = re.search(r'\d+', name).group()
            golden_call_args.append(f"x[{idx}]")
        elif name.startswith("y"):
            idx = re.search(r'\d+', name).group()
            golden_call_args.append(f"&y_gold[{idx}]")
        else:
            golden_call_args.append("0")
    golden_call_string = ", ".join(golden_call_args)

    # 6. Dynamically construct Masked Call Arguments
    masked_call_args = []
    for arg in masked_args:
        name = arg['name'].lower()
        if "rand" in name:
            masked_call_args.append("0")
        elif "dec" in name:
            masked_call_args.append("1")
        elif name.startswith("x"):
            idx = re.search(r'\d+', name).group()
            share_idx = name.split('_')[-1]
            if share_idx == '0':
                masked_call_args.append(f"x_sh0[{idx}]")
            else:
                masked_call_args.append(f"x_sh1[{idx}]")
        elif name.startswith("y"):
            idx = re.search(r'\d+', name).group()
            share_idx = name.split('_')[-1]
            if share_idx == '0':
                masked_call_args.append(f"&y_masked_sh0[{idx}]")
            else:
                masked_call_args.append(f"&y_masked_sh1[{idx}]")
        else:
            masked_call_args.append("0")
    masked_call_string = ", ".join(masked_call_args)

    # 7. Upgrade Prototype
    prototype_args = [x['full_decl'].replace("_Bool", "int").replace("bool", "int") for x in masked_args]
    prototype_string = ", ".join(prototype_args)

    c_code = f"""
#include <stdio.h>
#include <stdlib.h>

// --- 1. Golden Model (Unmasked) ---
{golden_code}

// --- 2. Masked Model (Generated) ---
void sbox_masked({prototype_string});

{masked_code}

// --- 3. Verification Logic ---
int main() {{
    int error_count = 0;

    printf("Starting verification for {num_iterations} inputs ({num_bits}-bit S-Box)...\\n");

    for(int i = 0; i < {num_iterations}; i++) {{
        int x[{num_bits}];
        for(int b=0; b<{num_bits}; b++) x[b] = (i >> b) & 1;

        int y_gold[{num_bits}] = {{0}};
        sbox_golden({golden_call_string});

        int x_sh0[{num_bits}];
        int x_sh1[{num_bits}];
        for(int b=0; b<{num_bits}; b++) {{
            x_sh0[b] = x[b];
            x_sh1[b] = 0; 
        }}

        int y_masked_sh0[{num_bits}] = {{0}};
        int y_masked_sh1[{num_bits}] = {{0}};
        
        sbox_masked({masked_call_string});

        int y_final[{num_bits}];
        int mismatch = 0;
        for(int b=0; b<{num_bits}; b++) {{
            // Mask with & 1 to safely truncate integers back to 1/0
            y_final[b] = (y_masked_sh0[b] ^ y_masked_sh1[b]) & 1;
            y_gold[b] = y_gold[b] & 1;
            
            if(y_final[b] != y_gold[b]) mismatch = 1;
        }}

        if(mismatch) {{
            printf("[FAILED] Input: %d (0x%0X) | Expected: ", i, i);
            for(int b={num_bits}-1; b>=0; b--) printf("%d", y_gold[b]);
            printf(" | Got: ");
            for(int b={num_bits}-1; b>=0; b--) printf("%d", y_final[b]);
            printf("\\n");
            error_count++;
        }}
    }}

    if(error_count == 0) {{
        printf("\\n[SUCCESS] All {num_iterations} inputs matched perfectly! Ground Truth verified.\\n");
    }} else {{
        printf("\\n[FAILURE] Total errors: %d\\n", error_count);
    }}

    return error_count > 0 ? 1 : 0;
}}
    """

    with open(TEST_FILE, 'w') as f:
        f.write(c_code)
    
    print(f"[Info] Testbench generated: {TEST_FILE}")

def compile_and_run():
    print(f"[Info] Compiling {TEST_FILE}...")
    cmd = ["gcc", TEST_FILE, "-o", EXECUTABLE, "-w", "-O2"] 
    try:
        subprocess.run(cmd, check=True)
        print(f"[Info] Compilation successful. Running {EXECUTABLE}...")
        subprocess.run([EXECUTABLE], check=True)
    except subprocess.CalledProcessError as e:
        print(f"[Error] Failed during compilation or execution.")

if __name__ == "__main__":
    if not os.path.exists(MASKED_FILE):
        print(f"[Error] {MASKED_FILE} not found.")
        sys.exit(1)
    if not os.path.exists(GOLDEN_FILE):
        print(f"[Error] {GOLDEN_FILE} not found.")
        sys.exit(1)

    print(f"Parsing {MASKED_FILE} and {GOLDEN_FILE}...")
    generate_testbench()
    compile_and_run()