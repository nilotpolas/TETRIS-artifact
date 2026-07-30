#!/usr/bin/env python3
"""
verify_masked_sbox.py — Correctness check for a masked Boyer-Peralta AES S-box.

Usage:
    python3 verify_masked_sbox.py <d> <num_rand> [--file PATH]

Arguments:
    d         Masking order  (number of shares = d + 1)
    num_rand  Number of random inputs expected by the masked sbox
    --file    Path to the masked C file
              (default: share_output/output.c, relative to this script)

Example:
    python3 verify_masked_sbox.py 1 46
    python3 verify_masked_sbox.py 2 90 --file share_output/output.c

How it works:
    For each of the 256 possible input bytes:
      1. Split every input bit into (d+1) random boolean shares whose XOR
         equals the original bit.
      2. Call the masked sbox with those shares.
         All 'rand_k' gadget randomness inputs are set to 0 — this does not
         affect correctness (only security), so it is fine for this test.
      3. XOR all output shares for each output bit to recover the plaintext
         output byte.
      4. Compare against the reference AES forward S-box (FIPS-197).
"""

import re
import sys
import os
import subprocess
import tempfile
import argparse

# ---------------------------------------------------------------------------
# AES forward S-box (FIPS-197, Table 4)
# ---------------------------------------------------------------------------
AES_SBOX = [
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
    0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
    0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
    0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
    0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
    0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
    0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
    0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
    0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
    0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
    0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
    0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16,
]


# ---------------------------------------------------------------------------
# Parse the sbox() signature from the C file
# ---------------------------------------------------------------------------
def parse_signature(content):
    """Return ordered list of parameter dicts from the top-level sbox() signature."""
    m = re.search(r'void\s+sbox\s*\(([^)]+)\)', content)
    if not m:
        sys.exit("[ERROR] Could not find 'void sbox(...)' in the file.")

    raw = m.group(1)
    params = []
    for token in (t.strip() for t in raw.split(',') if t.strip()):
        parts = token.split()
        name = parts[-1].lstrip('*')       # strip leading '*' for pointers
        is_ptr = '*' in token
        is_bool = '_Bool' in token or 'bool' in token
        is_int  = 'int' in token and not is_bool
        params.append({'name': name, 'is_ptr': is_ptr,
                       'is_bool': is_bool, 'is_int': is_int})
    return params


def classify_param(name, d):
    """Return one of: 'input_share', 'output_share', 'dec1', 'rand'."""
    # input share: i{bit}_{share}  e.g. i0_0, i7_2
    if re.fullmatch(r'i[0-7]_\d+', name):
        return 'input_share'
    # output share: y{bit}_{share}
    if re.fullmatch(r'y[0-7]_\d+', name):
        return 'output_share'
    if name == 'dec_1':
        return 'dec1'
    if re.fullmatch(r'rand_\d+', name):
        return 'rand'
    return 'unknown'


# ---------------------------------------------------------------------------
# Generate the C testbench source
# ---------------------------------------------------------------------------
def generate_testbench(d, num_rand, sbox_abs_path, params):
    shares = d + 1
    sbox_hex = ', '.join(f'0x{v:02x}' for v in AES_SBOX)

    # Validate param counts against the given d / num_rand
    input_params  = [p for p in params if classify_param(p['name'], d) == 'input_share']
    output_params = [p for p in params if classify_param(p['name'], d) == 'output_share']
    rand_params   = [p for p in params if classify_param(p['name'], d) == 'rand']

    expected_inputs  = 8 * shares
    expected_outputs = 8 * shares

    if len(input_params) != expected_inputs:
        print(f"[WARN] Expected {expected_inputs} input shares for d={d}, "
              f"found {len(input_params)} in signature.")
    if len(output_params) != expected_outputs:
        print(f"[WARN] Expected {expected_outputs} output shares for d={d}, "
              f"found {len(output_params)} in signature.")
    if len(rand_params) != num_rand:
        print(f"[WARN] Expected {num_rand} random params, "
              f"found {len(rand_params)} in signature.")

    # ── Build the argument list for the sbox() call ──────────────────────────
    call_args = []
    for p in params:
        kind = classify_param(p['name'], d)
        if kind == 'input_share':
            call_args.append(p['name'])          # declared as local variable
        elif kind == 'output_share':
            call_args.append(f'&{p["name"]}')   # pass address
        elif kind == 'dec1':
            call_args.append('1')
        elif kind == 'rand':
            call_args.append('0')                # 0 is correct for any rand
        else:
            call_args.append('0')

    call_str = ', '.join(call_args)

    # ── Declarations for input / output share variables ─────────────────────
    input_decls = '\n'.join(
        f'        _Bool {p["name"]};' for p in input_params
    )
    output_decls = '\n'.join(
        f'        _Bool {p["name"]};' for p in output_params
    )

    # ── Sharing logic: for each input bit, create d+1 random shares ─────────
    sharing_lines = []
    for bit in range(8):
        sharing_lines.append(f'        /* --- input bit {bit} --- */')
        sharing_lines.append(f'        int actual_i{bit} = (inp >> {bit}) & 1;')
        sharing_lines.append(f'        int xor_acc_i{bit} = 0;')
        for s in range(shares - 1):
            sharing_lines.append(f'        i{bit}_{s} = rand() & 1;')
            sharing_lines.append(f'        xor_acc_i{bit} ^= i{bit}_{s};')
        # last share = XOR of all previous XOR actual bit
        sharing_lines.append(
            f'        i{bit}_{shares-1} = (xor_acc_i{bit} ^ actual_i{bit}) & 1;'
        )
    sharing_code = '\n'.join(sharing_lines)

    # ── Output reconstruction: XOR all shares for each output bit ───────────
    recon_lines = []
    recon_lines.append('        uint8_t out = 0;')
    for bit in range(8):
        xor_expr = ' ^ '.join(f'y{bit}_{s}' for s in range(shares))
        recon_lines.append(f'        out |= (({xor_expr}) & 1u) << {bit};')
    recon_code = '\n'.join(recon_lines)

    # ── Escape the absolute path for use in #include ─────────────────────────
    escaped_path = sbox_abs_path.replace('\\', '\\\\')

    src = f"""\
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/* ── AES forward S-box (FIPS-197) ──────────────────────────────────── */
static const uint8_t AES_SBOX[256] = {{ {sbox_hex} }};

/* ── reg() models a hardware register; identity for simulation ──────── */
#define reg(x) (x)

/* ── Masked Boyer-Peralta S-box (order d={d}, shares={shares}) ──────── */
#include "{escaped_path}"

/* ── Exhaustive correctness test ────────────────────────────────────── */
int main(void) {{
    int errors = 0;
    srand(12345);   /* fixed seed for reproducibility */

    for (int inp = 0; inp < 256; inp++) {{

        /* ---- declare input share variables ---- */
{input_decls}

        /* ---- declare output share variables ---- */
{output_decls}

        /* ---- create random boolean sharing of each input bit ---- */
{sharing_code}

        /* ---- call the masked sbox (all rand_k = 0) ---- */
        sbox({call_str});

        /* ---- reconstruct output by XOR-ing all shares ---- */
{recon_code}

        /* ---- compare with reference ---- */
        uint8_t ref = AES_SBOX[inp];
        if (out != ref) {{
            printf("[FAIL] inp=0x%02X  got=0x%02X  expected=0x%02X\\n",
                   (unsigned)inp, (unsigned)out, (unsigned)ref);
            errors++;
        }}
    }}

    if (errors == 0)
        printf("[PASS] All 256 inputs matched the AES S-box reference.\\n");
    else
        printf("[FAIL] %d / 256 mismatches found.\\n", errors);

    return errors ? 1 : 0;
}}
"""
    return src


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------
def main():
    parser = argparse.ArgumentParser(
        description='Verify correctness of a masked Boyer-Peralta AES S-box.')
    parser.add_argument('d', type=int,
                        help='Masking order (shares = d + 1)')
    parser.add_argument('num_rand', type=int,
                        help='Number of random inputs in the masked sbox signature')
    parser.add_argument('--file', default=None,
                        help='Path to the masked C file '
                             '(default: share_output/output.c next to this script)')
    args = parser.parse_args()

    # Resolve the masked sbox file path
    script_dir = os.path.dirname(os.path.abspath(__file__))
    if args.file:
        sbox_path = os.path.abspath(args.file)
    else:
        sbox_path = os.path.join(script_dir, 'share_output', 'output.c')

    if not os.path.isfile(sbox_path):
        sys.exit(f"[ERROR] Masked sbox file not found: {sbox_path}")

    print(f"[INFO] Masked sbox file : {sbox_path}")
    print(f"[INFO] Masking order d  : {args.d}  (shares = {args.d + 1})")
    print(f"[INFO] Random inputs    : {args.num_rand}")

    with open(sbox_path) as f:
        content = f.read()

    params = parse_signature(content)
    print(f"[INFO] Parsed {len(params)} parameters from sbox() signature.")

    src = generate_testbench(args.d, args.num_rand, sbox_path, params)

    # Write testbench to a temp file and compile
    with tempfile.NamedTemporaryFile(suffix='.c', mode='w',
                                     delete=False, dir='/tmp') as tf:
        tf.write(src)
        tb_path = tf.name

    exe_path = tb_path.replace('.c', '')
    print(f"[INFO] Compiling testbench ...")
    compile_cmd = ['gcc', tb_path, '-o', exe_path, '-w', '-O2']
    result = subprocess.run(compile_cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print("[ERROR] Compilation failed:")
        print(result.stderr)
        os.unlink(tb_path)
        sys.exit(1)

    print(f"[INFO] Running verification ...")
    run_result = subprocess.run([exe_path], capture_output=True, text=True)
    print(run_result.stdout.strip())
    if run_result.stderr.strip():
        print(run_result.stderr.strip())

    # Clean up
    os.unlink(tb_path)
    os.unlink(exe_path)

    sys.exit(run_result.returncode)


if __name__ == '__main__':
    main()
