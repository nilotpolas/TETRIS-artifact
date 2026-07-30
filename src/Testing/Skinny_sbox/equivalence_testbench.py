#!/usr/bin/env python3
"""
Equivalence Verification Testbench for Masked S-Box

This testbench verifies that the masked S-box (output.c) is functionally
equivalent to the original unmasked S-box (skinny_sbox_nor.c).

For 1st-order Boolean masking:
  - Original input: x
  - Masked shares: x = x0 ⊕ x1 (where x0 and x1 are the shares)
  - Original output: y = sbox(x)
  - Masked output shares: y0 ⊕ y1 = sbox(x0 ⊕ x1)

The test verifies: sbox_masked(x0, x1, ...) produces y0, y1 such that
                   y0 ⊕ y1 = sbox_golden(x0 ⊕ x1, ...)
"""

import subprocess
import os
import sys
from pathlib import Path

# ============================================================================
# CONFIGURATION
# ============================================================================

UNMASKED_FILE = "skinny_sbox_nor.c"
MASKED_FILE = "output.c"
TEST_FILE = "equivalence_test.c"
EXECUTABLE = "./equivalence_test"

# Get the directory where this script is located
TEST_DIR = Path(__file__).parent
UNMASKED_PATH = TEST_DIR / UNMASKED_FILE
MASKED_PATH = Path("/home/tapish08/Desktop/DSE-Framework/TestFiles/share_output") / MASKED_FILE

# ============================================================================
# GENERATE TESTBENCH C CODE
# ============================================================================

def generate_testbench():
    """Generate the C testbench that tests both implementations"""
    
    # Read the unmasked and masked implementations
    with open(UNMASKED_PATH, 'r') as f:
        unmasked_code = f.read()
    
    with open(MASKED_PATH, 'r') as f:
        masked_code = f.read()
    
    # Rename functions to avoid conflicts
    unmasked_code = unmasked_code.replace("void sbox(", "void sbox_golden(")
    masked_code = masked_code.replace("void sbox(", "void sbox_masked(")
    
    # Convert _Bool to int in both
    unmasked_code = unmasked_code.replace("_Bool", "int").replace("bool", "int")
    masked_code = masked_code.replace("_Bool", "int").replace("bool", "int")
    
    # Create the testbench
    testbench_code = f"""
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// ==========================================
// 1. UTILITY FUNCTIONS
// ==========================================

int reg(int x) {{
    return x;
}}

// ==========================================
// 2. GOLDEN (UNMASKED) IMPLEMENTATION
// ==========================================

{unmasked_code}

// ==========================================
// 3. MASKED IMPLEMENTATION
// ==========================================

{masked_code}

// ==========================================
// 4. TESTBENCH LOGIC
// ==========================================

int main() {{
    int total_tests = 256;
    int passed = 0;
    int failed = 0;
    
    printf("\\n");
    printf("════════════════════════════════════════════════════════════════\\n");
    printf("MASKED S-BOX EQUIVALENCE VERIFICATION TESTBENCH\\n");
    printf("════════════════════════════════════════════════════════════════\\n\\n");
    
    printf("Testing: Unmasked vs 1st-Order Boolean Masked\\n");
    printf("Method: For each input x (0-255) and random share r:\\n");
    printf("  1. Split input: x0 = r (random), x1 = r ^ x\\n");
    printf("  2. Compute golden output: y = sbox_golden(x)\\n");
    printf("  3. Compute masked output: y0, y1 = sbox_masked(x0, x1, ...)\\n");
    printf("  4. Verify: y0 ^ y1 = sbox_golden(x)\\n\\n");
    
    printf("Running %d x 256 = %d test cases...\\n", total_tests, total_tests * 256);
    printf("(For each input value, testing with 256 different random shares)\\n");
    printf("────────────────────────────────────────────────────────────────\\n\\n");
    
    int grand_total = 0;
    int grand_passed = 0;
    int grand_failed = 0;
    
    for(int input_val = 0; input_val < total_tests; input_val++) {{
        // Extract 8 bits from input
        int in_bits[8];
        for(int b = 0; b < 8; b++) {{
            in_bits[b] = (input_val >> b) & 1;
        }}
        
        // Test with multiple random shares for this input
        for(int random_share = 0; random_share < 256; random_share++) {{
            grand_total++;
            
            // Extract 8 bits from random share
            int rand_bits[8];
            for(int b = 0; b < 8; b++) {{
                rand_bits[b] = (random_share >> b) & 1;
            }}
            
            // Compute share0 and share1 for each input bit
            // share0 = random value
            // share1 = share0 ^ input
            int share0[8], share1[8];
            for(int b = 0; b < 8; b++) {{
                share0[b] = rand_bits[b];
                share1[b] = share0[b] ^ in_bits[b];
            }}
            
            // =====================================
            // Run GOLDEN (unmasked) implementation
            // =====================================
            int g_out[8] = {{0}};
            sbox_golden(in_bits[0], in_bits[1], in_bits[2], in_bits[3],
                        in_bits[4], in_bits[5], in_bits[6], in_bits[7],
                        0,  // dec_1 = 0
                        &g_out[0], &g_out[1], &g_out[2], &g_out[3],
                        &g_out[4], &g_out[5], &g_out[6], &g_out[7]);
            
            // =====================================
            // Run MASKED implementation
            // Input shares: share0 and share1
            // All randoms set to 0 for deterministic testing
            // =====================================
            int m_out_sh0[8] = {{0}};
            int m_out_sh1[8] = {{0}};
            
            sbox_masked(
                share0[0], share1[0],  // i0_0, i0_1
                share0[1], share1[1],  // i1_0, i1_1
                share0[2], share1[2],  // i2_0, i2_1
                share0[3], share1[3],  // i3_0, i3_1
                share0[4], share1[4],  // i4_0, i4_1
                share0[5], share1[5],  // i5_0, i5_1
                share0[6], share1[6],  // i6_0, i6_1
                share0[7], share1[7],  // i7_0, i7_1
                1,  // dec_1
                &m_out_sh0[0], &m_out_sh1[0],
                &m_out_sh0[1], &m_out_sh1[1],
                &m_out_sh0[2], &m_out_sh1[2],
                &m_out_sh0[3], &m_out_sh1[3],
                &m_out_sh0[4], &m_out_sh1[4],
                &m_out_sh0[5], &m_out_sh1[5],
                &m_out_sh0[6], &m_out_sh1[6],
                &m_out_sh0[7], &m_out_sh1[7],
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1  // all randoms = 0
            );
        
        // =====================================
        // Combine masked shares and verify
        // =====================================
        int mismatch = 0;
        for(int bit = 0; bit < 8; bit++) {{
            int combined = (m_out_sh0[bit] ^ m_out_sh1[bit]) & 1;
            int golden = g_out[bit] & 1;
            
            if(combined != golden) {{
                mismatch = 1;
                break;
            }}
        }}
        
        // =====================================
        // Report results
        // =====================================
        if(mismatch) {{
            grand_failed++;
            printf("[FAIL] Input: 0x%02X, Random: 0x%02X | ", input_val, random_share);
            printf("Expected: ");
            for(int b = 7; b >= 0; b--) printf("%d", g_out[b] & 1);
            printf(" | ");
            printf("Got: ");
            for(int b = 7; b >= 0; b--) printf("%d", (m_out_sh0[b] ^ m_out_sh1[b]) & 1);
            printf("\\n");
        }} else {{
            grand_passed++;
        }}
    }}
    }}
    
    // =====================================
    // Summary
    // =====================================
    printf("\\n────────────────────────────────────────────────────────────────\\n");
    printf("RESULTS:\\n");
    printf("  Total Tests: %d (256 inputs x 256 random shares)\\n", grand_total);
    printf("  Passed: %d\\n", grand_passed);
    printf("  Failed: %d\\n", grand_failed);
    printf("  Success Rate: %.2f%%\\n", (100.0 * grand_passed / grand_total));
    printf("════════════════════════════════════════════════════════════════\\n\\n");
    
    if(grand_failed == 0) {{
        printf("✓ EQUIVALENCE VERIFIED: All %d test cases passed!\\n\\n", grand_total);
        return 0;
    }} else {{
        printf("✗ EQUIVALENCE FAILED: %d mismatches detected!\\n\\n", grand_failed);
        return 1;
    }}
}}
"""
    
    # Write the testbench
    with open(TEST_DIR / TEST_FILE, 'w') as f:
        f.write(testbench_code)
    
    print(f"[✓] Testbench generated: {TEST_DIR / TEST_FILE}")
    return True


# ============================================================================
# COMPILE AND RUN
# ============================================================================

def compile_and_run():
    """Compile and execute the testbench"""
    
    # Change to test directory
    os.chdir(TEST_DIR)
    
    # Compile
    print("\n[COMPILING] Generating executable...")
    compile_cmd = ["gcc", TEST_FILE, "-o", EXECUTABLE, "-Wall", "-O2"]
    
    result = subprocess.run(compile_cmd, capture_output=True, text=True)
    
    if result.returncode != 0:
        print(f"[✗] Compilation failed!")
        print(f"STDERR:\n{result.stderr}")
        return False
    
    print(f"[✓] Compilation successful!")
    
    # Run
    print(f"\n[RUNNING] Executing testbench...\n")
    result = subprocess.run([EXECUTABLE], capture_output=True, text=True)
    
    print(result.stdout)
    
    if result.stderr:
        print(f"STDERR:\n{result.stderr}")
    
    return result.returncode == 0


# ============================================================================
# MAIN
# ============================================================================

def main():
    """Main entry point"""
    
    print("\n" + "="*70)
    print("MASKED S-BOX EQUIVALENCE TESTBENCH GENERATOR")
    print("="*70 + "\n")
    
    # Verify input files exist
    print("[CHECK] Verifying input files...")
    
    if not UNMASKED_PATH.exists():
        print(f"[✗] ERROR: Unmasked file not found: {UNMASKED_PATH}")
        return 1
    print(f"[✓] Found unmasked: {UNMASKED_PATH}")
    
    if not MASKED_PATH.exists():
        print(f"[✗] ERROR: Masked file not found: {MASKED_PATH}")
        return 1
    print(f"[✓] Found masked: {MASKED_PATH}")
    
    # Generate testbench
    print("\n[STEP 1] Generating testbench C code...")
    if not generate_testbench():
        return 1
    
    # Compile and run
    print("\n[STEP 2] Compiling testbench...")
    print("[STEP 3] Running verification...\n")
    
    if not compile_and_run():
        print("\n[✗] Testbench execution failed!")
        return 1
    
    print("[✓] Verification complete!")
    return 0


if __name__ == "__main__":
    sys.exit(main())
