#!/usr/bin/env python3
"""
run_verify.py — Functional equivalence verification for DSE-Framework
======================================================================
Two-stage verification of a masked S-box design:

  Stage 1 (C-level) : compile masked share_output/output.c + unmasked golden C,
                      exhaustively check that XOR-of-shares == golden for all
                      256 inputs × NUM_TRIALS random share assignments.

  Stage 2 (RTL)     : simulate the Yosys-synthesized gate-level Verilog with
                      iverilog + vvp.  Uses the same lookup-table golden computed
                      from the C stage.

Supported designs  : Boyer_Peraltas_sbox  (AES S-box)
                     Canright_sbox         (AES S-box — no dec_1)
                     skinny_sbox_nor       (Skinny 8-bit S-box)

Usage examples:
  python run_verify.py --design Canright_sbox --order 1 --latency 4
  python run_verify.py --design Boyer_Peraltas_sbox --order 2 --latency 5 \\
      --rtl Results/Boyer_Peraltas_sbox/MRLC_d2_lat5/design_synth.v
  python run_verify.py --design skinny_sbox_nor --order 1 --latency 3 --skip-rtl
"""

import argparse
import os
import re
import subprocess
import sys
import tempfile
import time

_ROOT = os.path.dirname(os.path.abspath(__file__))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

import _dse_utils as U
from _dse_utils import bold, green, red, yellow, cyan, dim, _STDOUT, LOG_FILE

# ── constants ─────────────────────────────────────────────────────────────────
C_FILES_DIR   = U.C_FILES_DIR
SHARE_OUT_C   = os.path.join(U.SHARE_DIR, "output.c")
STDCELLS_V    = os.path.join(U.FRAMEWORK_DIR, "Design Synthesis",
                              "nangate45-pdk", "stdcells.v")
NUM_TRIALS    = 16          # random share trials per input byte

# Designs whose golden C does NOT have a dec_1 argument
DESIGNS_NO_DEC1 = {"canright_sbox"}


# ══════════════════════════════════════════════════════════════════════════════
#  Signature parsing
# ══════════════════════════════════════════════════════════════════════════════

def parse_golden_sig(c_text):
    """
    Parse unmasked sbox signature.
    Returns {'in_args', 'out_args', 'has_dec1'}.
    """
    m = re.search(r'void\s+sbox\s*\(([^)]+)\)', c_text, re.DOTALL)
    if not m:
        raise ValueError("Could not find 'void sbox(...)' in golden C")
    args = [a.strip() for a in m.group(1).split(',')]
    in_args, out_args, has_dec1 = [], [], False
    for a in args:
        name = a.split()[-1].lstrip('*')
        is_ptr = '*' in a
        if name == 'dec_1':
            has_dec1 = True
        elif is_ptr:
            out_args.append(name)
        else:
            in_args.append(name)
    return {'in_args': in_args, 'out_args': out_args, 'has_dec1': has_dec1}


def parse_masked_sig(c_text):
    """
    Parse masked sbox signature (the last 'void sbox(...)' in the file).
    Returns {'num_bits', 'num_shares', 'in_shares', 'out_shares',
             'rand_args', 'has_dec1', 'arg_order', 'dec1_hardcoded_val'}.
    in_shares / out_shares: {(bit, share): arg_name}
    dec1_hardcoded_val: 1 if the ShareTransformer hardcoded dec_1=1 in the body
                        (dec_1 in signature but not referenced in body), else 0.
    """
    matches = list(re.finditer(r'void\s+sbox\s*\(([^)]+)\)', c_text, re.DOTALL))
    if not matches:
        raise ValueError("Could not find masked sbox signature")

    # extract the sbox function body (text after last match)
    last_match = matches[-1]
    sbox_body = c_text[last_match.end():]

    args_raw = last_match.group(1)
    args = [a.strip() for a in args_raw.split(',')]

    # Generic share-port pattern: any name ending in _{bit}_{share}
    _SHARE_PAT = re.compile(r'^.+?(\d+)_(\d+)$')

    in_sh, out_sh, rand_args, has_dec1 = {}, {}, [], False
    arg_order = []
    for a in args:
        name = a.split()[-1].lstrip('*')
        is_ptr = '*' in a
        arg_order.append(name)
        if name == 'dec_1':
            has_dec1 = True
        elif re.match(r'rand_\d+$', name):
            rand_args.append(name)
        else:
            g = _SHARE_PAT.match(name)
            if g:
                b, s = int(g.group(1)), int(g.group(2))
                if is_ptr:
                    out_sh[(b, s)] = name
                else:
                    in_sh[(b, s)] = name

    if not in_sh:
        raise ValueError("No masked input shares found in signature")
    nb = max(b for b, _ in in_sh) + 1
    ns = max(s for _, s in in_sh) + 1

    # detect whether dec_1 is actually used in the body or was hardcoded by the
    # ShareTransformer.  When hardcoded to 1, the body has !share inversions
    # instead of share ^ dec_1 expressions.
    dec1_hardcoded_val = 0
    if has_dec1:
        # if 'dec_1' doesn't appear anywhere in the body, the transformer fixed it
        if not re.search(r'\bdec_1\b', sbox_body):
            dec1_hardcoded_val = 1

    return dict(num_bits=nb, num_shares=ns, in_sh=in_sh, out_sh=out_sh,
                rand_args=rand_args, has_dec1=has_dec1, arg_order=arg_order,
                dec1_hardcoded_val=dec1_hardcoded_val)


# ══════════════════════════════════════════════════════════════════════════════
#  Stage 1 — C-level equivalence test
# ══════════════════════════════════════════════════════════════════════════════

def _build_c_testbench(golden_c, masked_c, gsig, msig):
    """Generate a self-contained C equivalence test file."""
    nb, ns = msig['num_bits'], msig['num_shares']

    # ── rename sbox → sbox_golden in golden code ──────────────────────────
    golden_renamed = re.sub(r'void\s+sbox\s*\(',
                            'void sbox_golden(', golden_c, count=1)

    # ── rename sbox → sbox_masked in masked code (only the sbox def) ──────
    masked_renamed = re.sub(r'((?:^|\n))void\s+sbox\s*\(',
                             r'\1void sbox_masked(', masked_c)

    # ── build golden call ──────────────────────────────────────────────────
    # If the ShareTransformer hardcoded dec_1=1 (body never references dec_1),
    # we must call the golden with dec_1=1 to match hardware behaviour.
    dec1_val = msig.get('dec1_hardcoded_val', 0)
    golden_in_call  = ', '.join(f'(bool)bits[{i}]' for i in range(nb))
    golden_dec_call = f', {dec1_val}' if gsig['has_dec1'] else ''
    golden_out_decl = '    bool ' + ', '.join(f'go{i}' for i in range(nb)) + ';\n'
    golden_out_ptrs = ', '.join(f'&go{i}' for i in range(nb))
    golden_out_byte = ' | '.join(f'((int)go{i}<<{i})' for i in range(nb))

    # ── build masked call following exact arg_order in signature ──────────
    _SHARE_RE = re.compile(r'^.+?(\d+)_(\d+)$')
    masked_call_parts = []
    # track output var declarations
    out_var_decls = []
    for nm in msig['arg_order']:
        if nm == 'dec_1':
            masked_call_parts.append(str(dec1_val))
        elif re.match(r'rand_\d+$', nm):
            masked_call_parts.append('rand() & 1')
        else:
            g = _SHARE_RE.match(nm)
            if g:
                b, s = int(g.group(1)), int(g.group(2))
                # Use name-exact match to distinguish in vs out (keys may collide)
                if msig['out_sh'].get((b, s)) == nm:
                    var = f'mo_{b}_{s}'
                    out_var_decls.append(f'    _Bool {var};')
                    masked_call_parts.append(f'&{var}')
                elif msig['in_sh'].get((b, s)) == nm:
                    masked_call_parts.append(f'(bool)in_sh[{b}][{s}]')
                else:
                    masked_call_parts.append('0')  # unknown — skip gracefully
    masked_call = ', '.join(masked_call_parts)

    # output recovery
    out_recovery_lines = []
    for b in range(nb):
        xor_terms = ' ^ '.join(
            f'(int)mo_{b}_{s}' for s in range(ns)
        )
        out_recovery_lines.append(
            f'        masked_out |= (({xor_terms}) << {b});'
        )

    return f"""\
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* reg() is a hardware pipeline register — identity at C-simulation level */
static inline _Bool reg(_Bool x) {{ return x; }}

/* ===== GOLDEN REFERENCE ===== */
{golden_renamed}

/* ===== MASKED IMPLEMENTATION ===== */
{masked_renamed}

#define NUM_BITS    {nb}
#define NUM_SHARES  {ns}
#define NUM_TRIALS  {NUM_TRIALS}

int main(void) {{
    int pass = 0, fail = 0;
    srand(0x1234ABCD);   /* fixed seed for reproducibility */

    for (int x = 0; x < 256; x++) {{
        for (int t = 0; t < NUM_TRIALS; t++) {{
            /* -- extract bits -- */
            int bits[NUM_BITS];
            for (int b = 0; b < NUM_BITS; b++) bits[b] = (x >> b) & 1;

            /* -- golden output -- */
{golden_out_decl}
            sbox_golden({golden_in_call}{golden_dec_call}, {golden_out_ptrs});
            int golden_out = {golden_out_byte};

            /* -- generate input shares -- */
            int in_sh[NUM_BITS][NUM_SHARES];
            for (int b = 0; b < NUM_BITS; b++) {{
                int xorsum = bits[b];
                for (int s = 0; s < NUM_SHARES - 1; s++) {{
                    in_sh[b][s] = rand() & 1;
                    xorsum ^= in_sh[b][s];
                }}
                in_sh[b][NUM_SHARES - 1] = xorsum;
            }}

            /* -- masked output variables -- */
{chr(10).join(out_var_decls)}

            /* -- call masked sbox -- */
            sbox_masked({masked_call});

            /* -- recover output by XOR-ing shares -- */
            int masked_out = 0;
{chr(10).join(out_recovery_lines)}

            /* -- compare -- */
            if (masked_out == golden_out) {{
                pass++;
            }} else {{
                fail++;
                if (fail <= 10)
                    printf("FAIL  input=0x%02x trial=%d  expected=0x%02x  got=0x%02x\\n",
                           x, t, golden_out, masked_out);
            }}
        }}
    }}

    int total = pass + fail;
    printf("\\nC-LEVEL RESULT: %d / %d passed\\n", pass, total);
    if (fail == 0) {{ printf("ALL TESTS PASSED\\n"); return 0; }}
    else            {{ printf("FAILED: %d test(s)\\n", fail); return 1; }}
}}
"""


def run_c_verification(golden_c_path, masked_c_path):
    """
    Build and run the C equivalence test.
    Returns (pass_count, fail_count, total).
    """
    golden_c = open(golden_c_path).read()
    masked_c = open(masked_c_path).read()

    gsig = parse_golden_sig(golden_c)
    msig = parse_masked_sig(masked_c)

    tb_src = _build_c_testbench(golden_c, masked_c, gsig, msig)

    with tempfile.TemporaryDirectory() as tmp:
        src_path = os.path.join(tmp, "equiv_test.c")
        bin_path = os.path.join(tmp, "equiv_test")
        with open(src_path, 'w') as f:
            f.write(tb_src)

        # compile
        comp = subprocess.run(
            ['gcc', '-O2', '-o', bin_path, src_path, '-lm'],
            capture_output=True, text=True
        )
        if comp.returncode != 0:
            U.log("=== C COMPILE ERRORS ===\n" + comp.stderr)
            raise RuntimeError(f"C compilation failed — see {LOG_FILE}")

        # run
        run = subprocess.run([bin_path], capture_output=True, text=True, timeout=120)
        U.log("=== C TESTBENCH OUTPUT ===\n" + run.stdout + run.stderr)

        # parse result
        m = re.search(r'C-LEVEL RESULT:\s+(\d+)\s*/\s*(\d+)', run.stdout)
        if m:
            p, total = int(m.group(1)), int(m.group(2))
            return p, total - p, total
        return 0, 1, 1     # unexpected output → treat as failure


# ══════════════════════════════════════════════════════════════════════════════
#  Compute S-box lookup table (for Verilog testbench)
# ══════════════════════════════════════════════════════════════════════════════

def compute_sbox_lut(golden_c_path, dec1_val=0):
    """
    Compile the golden C to a standalone lookup-table generator and run it.
    dec1_val: value to pass for the dec_1 parameter (0 or 1).
    Returns list[256] of ints.
    """
    golden_c = open(golden_c_path).read()
    gsig = parse_golden_sig(golden_c)
    nb = len(gsig['in_args'])

    golden_renamed = re.sub(r'void\s+sbox\s*\(',
                            'void sbox_golden(', golden_c, count=1)

    in_call  = ', '.join(f'(bool)((x>>{i})&1)' for i in range(nb))
    dec_call = f', {dec1_val}' if gsig['has_dec1'] else ''
    out_decl = ', '.join(f'go{i}' for i in range(nb))
    out_ptrs = ', '.join(f'&go{i}' for i in range(nb))
    out_byte = ' | '.join(f'((int)go{i}<<{i})' for i in range(nb))

    lut_src = f"""\
#include <stdio.h>
#include <stdbool.h>
{golden_renamed}
int main(void) {{
    for (int x = 0; x < 256; x++) {{
        bool {out_decl};
        sbox_golden({in_call}{dec_call}, {out_ptrs});
        int r = {out_byte};
        printf("%02x\\n", r);
    }}
    return 0;
}}
"""
    with tempfile.TemporaryDirectory() as tmp:
        src = os.path.join(tmp, "lut.c")
        exe = os.path.join(tmp, "lut")
        open(src, 'w').write(lut_src)
        r = subprocess.run(['gcc', '-O2', '-o', exe, src], capture_output=True, text=True)
        if r.returncode != 0:
            raise RuntimeError("LUT compiler failed:\n" + r.stderr)
        out = subprocess.run([exe], capture_output=True, text=True, timeout=10)
        values = [int(line.strip(), 16) for line in out.stdout.splitlines() if line.strip()]
        if len(values) != 256:
            raise RuntimeError(f"LUT generator produced {len(values)} values, expected 256")
        return values


# ══════════════════════════════════════════════════════════════════════════════
#  Stage 2 — RTL (Verilog) simulation
# ══════════════════════════════════════════════════════════════════════════════

def parse_rtl_ports(v_path):
    """
    Parse the port list of the synthesized Verilog.
    Supports two port-naming conventions produced by MaskedHLS + Yosys:
      - i{bit}_{share} / o{bit}_{share}  (direct from masked C)
      - X{bit}_{share} / Y{bit}_{share}  (alternative convention)
    Returns {module_name, num_bits, num_shares, rand_ports, has_dec1,
             in_sh_ports, out_sh_ports}.
    """
    text = open(v_path).read()

    # module name
    m = re.search(r'module\s+(\w+)\s*\(', text)
    if not m:
        raise ValueError(f"No 'module' declaration in {v_path}")
    module = m.group(1)

    # all input / output port names
    inputs  = re.findall(r'\binput\b[^;]*?\b(\w+)\s*;', text)
    outputs = re.findall(r'\boutput\b[^;]*?\b(\w+)\s*;', text)

    rand_ports = sorted([p for p in inputs if re.match(r'rand_\d+$', p)],
                        key=lambda x: int(x.split('_')[1]))
    has_dec1 = 'dec_1' in inputs

    # Generic share-port pattern: name ending in _{bit}_{share}
    _SHARE_RE = re.compile(r'^.+?(\d+)_(\d+)$')
    in_sh_ports  = [p for p in inputs  if _SHARE_RE.match(p)
                    and not re.match(r'rand_\d+$', p) and p != 'dec_1']
    out_sh_ports = [p for p in outputs if _SHARE_RE.match(p)
                    and not re.match(r'rand_\d+$', p) and p != 'dec_1']
    in_pat  = r'^.+?(\d+)_(\d+)$'
    out_pat = r'^.+?(\d+)_(\d+)$'

    if not in_sh_ports:
        raise ValueError("No masked input ports ({prefix}{bit}_{share}) found")

    nb = max(int(re.match(in_pat, p).group(1)) for p in in_sh_ports) + 1
    ns = max(int(re.match(in_pat, p).group(2)) for p in in_sh_ports) + 1

    return dict(module=module, num_bits=nb, num_shares=ns,
                rand_ports=rand_ports, has_dec1=has_dec1,
                in_sh_ports=sorted(in_sh_ports),
                out_sh_ports=sorted(out_sh_ports),
                in_pat=in_pat, out_pat=out_pat)


def _build_verilog_testbench(ports, sbox_lut, latency, dec1_val=0):
    """Generate a Verilog testbench for the synthesized gate-level netlist."""
    nb  = ports['num_bits']
    ns  = ports['num_shares']
    nrand = len(ports['rand_ports'])
    module = ports['module']
    in_pat  = ports.get('in_pat',  r'i(\d+)_(\d+)$')
    out_pat = ports.get('out_pat', r'o(\d+)_(\d+)$')

    # build ordered lists of (bit, share, port_name)
    def _parse_port(p, pat):
        g = re.match(pat, p)
        return int(g.group(1)), int(g.group(2))

    in_ports  = sorted(ports['in_sh_ports'],  key=lambda p: _parse_port(p, in_pat))
    out_ports = sorted(ports['out_sh_ports'], key=lambda p: _parse_port(p, out_pat))

    # Golden S-box as a 256-entry case statement (assign task output g, not module reg)
    cases = '\n'.join(
        f'            8\'h{i:02x}: g = 8\'h{sbox_lut[i]:02x};'
        for i in range(256)
    )

    # Flat signal declarations (use tb_in_ / tb_out_ prefix to avoid name clashes)
    in_decls = '\n'.join(
        f'    reg  tb_in_{p};' for p in in_ports
    )
    out_decls = '\n'.join(
        f'    wire tb_out_{p};' for p in out_ports
    )

    # DUT port map
    in_connections = '\n'.join(
        f'    .{p}(tb_in_{p}),' for p in in_ports
    )
    rand_decl = f'    reg  [{max(1,nrand)}-1:0] rand_bits;'
    rand_connections = '\n'.join(
        f'    .{p}(rand_bits[{i}]),' for i, p in enumerate(ports['rand_ports'])
    )
    dec1_lit = f"1'b{dec1_val}"
    dec1_conn = f'    .dec_1({dec1_lit}),' if ports['has_dec1'] else ''
    last_out = out_ports[-1]
    out_connections = '\n'.join(
        f'    .{p}(tb_out_{p}){"," if p != last_out else ""}'
        for p in out_ports
    )

    # Input share assignment block
    share_assign_lines = []
    for b in range(nb):
        for s in range(ns - 1):
            port = next(p for p in in_ports if _parse_port(p, in_pat) == (b, s))
            share_assign_lines.append(
                f'            tb_in_{port} = mask_bits[{b * (ns-1) + s}];'
            )
        # last share = bit ^ XOR of other shares
        xor_masks = ' ^ '.join(f'mask_bits[{b*(ns-1)+s}]' for s in range(ns-1))
        port_last = next(p for p in in_ports if _parse_port(p, in_pat) == (b, ns-1))
        share_assign_lines.append(
            f'            tb_in_{port_last} = input_byte[{b}] ^ ({xor_masks});'
        )
    share_assign = '\n'.join(share_assign_lines)

    # Output XOR recovery
    recover_lines = []
    for b in range(nb):
        xor_terms = ' ^ '.join(
            f'tb_out_{next(p for p in out_ports if _parse_port(p, out_pat) == (b, s))}'
            for s in range(ns)
        )
        recover_lines.append(f'        output_byte[{b}] = {xor_terms};')
    recover = '\n'.join(recover_lines)

    total_tests = 256 * NUM_TRIALS

    return f"""\
`timescale 1ns/1ps

module verify_tb;

    // ── clock ──────────────────────────────────────────────────────────────
    reg clk = 0;
    always #5 clk = ~clk;

    // ── DUT signals ────────────────────────────────────────────────────────
{in_decls}
{out_decls}
{rand_decl}

    // ── DUT instantiation ──────────────────────────────────────────────────
    {module} dut (
    .clk(clk),
{in_connections}
{rand_connections}
{dec1_conn}
{out_connections}
    );

    // ── test variables ─────────────────────────────────────────────────────
    integer       x_val, trial, b, pass_cnt, fail_cnt;
    reg [7:0]     input_byte, golden, output_byte;
    reg [{nb*(ns-1)}-1:0] mask_bits;

    // Golden S-box (combinational LUT)
    task golden_sbox;
        input  [7:0] in;
        output [7:0] g;
        case (in)
{cases}
            default: g = 8'hxx;
        endcase
    endtask

    initial begin
        pass_cnt  = 0;
        fail_cnt  = 0;
        rand_bits = 0;
        {'; '.join(f'tb_in_{p} = 0' for p in in_ports)};

        // flush pipeline before first valid output
        repeat ({latency} + 2) @(posedge clk);

        for (x_val = 0; x_val < 256; x_val = x_val + 1) begin
            input_byte = x_val[7:0];
            golden_sbox(input_byte, golden);

            for (trial = 0; trial < {NUM_TRIALS}; trial = trial + 1) begin
                // fresh randomness each trial
                mask_bits = $urandom;
                rand_bits = $urandom;

                // apply masked inputs
{share_assign}

                // clock in and wait for pipeline output.
                // MaskedHLS latency excludes the final output register, so
                // the output is valid after latency+1 rising edges.
                @(posedge clk);
                repeat ({latency}) @(posedge clk);
                #1;   // small settle after last rising edge

                // recover output
{recover}

                if (output_byte === golden) begin
                    pass_cnt = pass_cnt + 1;
                end else begin
                    fail_cnt = fail_cnt + 1;
                    if (fail_cnt <= 10)
                        $display("FAIL  input=0x%02x trial=%0d  expected=0x%02x  got=0x%02x",
                                 x_val, trial, golden, output_byte);
                end
            end
        end

        $display("\\nRTL RESULT: %0d / {total_tests} passed", pass_cnt);
        if (fail_cnt == 0)
            $display("ALL TESTS PASSED");
        else
            $display("FAILED: %0d test(s)", fail_cnt);

        $finish;
    end
endmodule
"""


def run_rtl_verification(rtl_path, golden_c_path, latency, work_dir, dec1_val=0):
    """
    Generate testbench, compile with iverilog, run with vvp.
    Returns (pass_count, fail_count, total, elapsed_sec).
    """
    ports    = parse_rtl_ports(rtl_path)
    sbox_lut = compute_sbox_lut(golden_c_path, dec1_val=dec1_val)

    tb_src  = _build_verilog_testbench(ports, sbox_lut, latency, dec1_val=dec1_val)

    os.makedirs(work_dir, exist_ok=True)
    tb_path  = os.path.join(work_dir, "verify_tb.v")
    sim_path = os.path.join(work_dir, "verify_sim")
    open(tb_path, 'w').write(tb_src)
    U.log("=== VERILOG TESTBENCH ===\n" + tb_src)

    # compile
    comp = subprocess.run(
        ['iverilog', '-g2001', '-o', sim_path, tb_path, rtl_path, STDCELLS_V],
        capture_output=True, text=True
    )
    U.log("=== IVERILOG COMPILE ===\n" + comp.stdout + comp.stderr)
    if comp.returncode != 0:
        raise RuntimeError(f"iverilog compilation failed — see {LOG_FILE}")

    # simulate
    t0 = time.time()
    sim = subprocess.run(['vvp', sim_path], capture_output=True, text=True, timeout=300)
    U.log("=== VVP SIMULATION ===\n" + sim.stdout + sim.stderr)
    elapsed = time.time() - t0

    total = 256 * NUM_TRIALS
    m = re.search(r'RTL RESULT:\s+(\d+)\s*/\s*\d+', sim.stdout)
    if m:
        p = int(m.group(1))
        return p, total - p, total, elapsed
    return 0, 1, total, elapsed


# ══════════════════════════════════════════════════════════════════════════════
#  Reporting
# ══════════════════════════════════════════════════════════════════════════════

def _pass_line(stage, p, f, total, elapsed=None):
    status  = green("PASS") if f == 0 else red("FAIL")
    t_str   = f"  ({elapsed:.1f}s)" if elapsed is not None else ""
    rate    = f"{p}/{total}"
    print(f"  [{status}] {stage:<14} {rate} tests passed{t_str}", file=_STDOUT)


# ══════════════════════════════════════════════════════════════════════════════
#  CLI
# ══════════════════════════════════════════════════════════════════════════════

def parse_args():
    p = argparse.ArgumentParser(
        prog="run_verify.py",
        description="Functional equivalence verification (C-level + RTL simulation)",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python run_verify.py --design Canright_sbox --order 1 --latency 4
  python run_verify.py --design Boyer_Peraltas_sbox --order 2 --latency 5 \\
      --rtl Results/Boyer_Peraltas_sbox/MRLC_d2_lat5/design_synth.v
  python run_verify.py --design skinny_sbox_nor --order 1 --latency 3 --skip-rtl
        """,
    )
    p.add_argument("--design",    required=True,
                   help="Design name: Boyer_Peraltas_sbox | Canright_sbox | skinny_sbox_nor")
    p.add_argument("--order",     type=int, required=True, choices=range(1,6),
                   help="Security order d (1–5)")
    p.add_argument("--latency",   type=int, required=True,
                   help="Pipeline depth in clock cycles (from MaskedHLS)")
    p.add_argument("--masked-c",    default=None,
                   help="Path to masked C file (default: <results-dir>/masked_output.c or share_output/output.c)")
    p.add_argument("--rtl",         default=None,
                   help="Path to Yosys-synthesized Verilog (design_synth.v)")
    p.add_argument("--results-dir", default=None, metavar="DIR",
                   help="Results directory from run_mrlc/run_mlrc; auto-sets --masked-c and --rtl")
    p.add_argument("--skip-rtl",    action="store_true",
                   help="Skip Verilog RTL simulation")
    p.add_argument("--work-dir",    default=None,
                   help="Directory for generated testbench files")
    return p.parse_args()


def main():
    args = parse_args()

    design_name = args.design
    design_key  = design_name.lower().replace("-", "_")
    c_name      = design_name if design_name.endswith(".c") else design_name + ".c"
    golden_c    = os.path.join(C_FILES_DIR, c_name)

    # resolve --results-dir shortcut
    masked_c = args.masked_c
    rtl_path = args.rtl
    if args.results_dir:
        rdir = os.path.abspath(args.results_dir)
        if masked_c is None:
            candidate = os.path.join(rdir, "masked_output.c")
            if os.path.isfile(candidate):
                masked_c = candidate
        if rtl_path is None:
            candidate = os.path.join(rdir, "design_synth.v")
            if os.path.isfile(candidate):
                rtl_path = candidate

    # fall back to shared output.c
    if masked_c is None:
        masked_c = SHARE_OUT_C

    if not os.path.isfile(golden_c):
        U.err(f"Golden C not found: {golden_c}")
        sys.exit(1)
    if not os.path.isfile(masked_c):
        U.err(f"Masked C not found: {masked_c}")
        sys.exit(1)

    work_dir = args.work_dir or os.path.join(
        U.RESULTS_DIR, design_name, f"verify_d{args.order}_lat{args.latency}"
    )

    # header
    print(file=_STDOUT)
    print(bold("=" * 68), file=_STDOUT)
    print(bold("  DSE-Framework — Functional Equivalence Verification"), file=_STDOUT)
    print(bold("=" * 68), file=_STDOUT)
    print(f"  Design        : {cyan(design_name)}", file=_STDOUT)
    print(f"  Security order: d = {args.order}  ({args.order+1} shares)", file=_STDOUT)
    print(f"  Pipeline depth: {args.latency} cycles", file=_STDOUT)
    print(f"  Test cases    : 256 inputs × {NUM_TRIALS} trials = {256*NUM_TRIALS}", file=_STDOUT)
    print(file=_STDOUT)

    U.init_log("VERIFY", design_name, "Latency", args.latency, args.order)
    overall_pass = True

    # detect dec1 hardcoded value from masked C (needed by both stages)
    try:
        _msig = parse_masked_sig(open(masked_c).read())
        dec1_val = _msig.get('dec1_hardcoded_val', 0)
    except Exception:
        dec1_val = 0

    # ── Stage 1: C-level ──────────────────────────────────────────────────
    print(f"{dim('[1/2]')} {bold('C-level functional equivalence')}", file=_STDOUT)
    t0 = time.time()
    try:
        p, f, total = run_c_verification(golden_c, masked_c)
        elapsed = time.time() - t0
        _pass_line("C-level", p, f, total, elapsed)
        if f > 0:
            overall_pass = False
    except Exception as e:
        U.err(f"C verification error: {e}")
        overall_pass = False

    # ── Stage 2: RTL simulation ───────────────────────────────────────────
    print(f"\n{dim('[2/2]')} {bold('RTL gate-level simulation  (iverilog)')}", file=_STDOUT)
    if args.skip_rtl:
        U.warn("Skipped (--skip-rtl)")
    elif not rtl_path:
        U.warn("No --rtl path given; skipping RTL simulation")
        print(f"         Run again with: {cyan('--rtl <path/to/design_synth.v>')}",
              file=_STDOUT)
    elif not os.path.isfile(rtl_path):
        U.err(f"RTL file not found: {rtl_path}")
        overall_pass = False
    else:
        t0 = time.time()
        try:
            p, f, total, elapsed = run_rtl_verification(
                rtl_path, golden_c, args.latency, work_dir, dec1_val=dec1_val
            )
            _pass_line("RTL", p, f, total, elapsed)
            if f > 0:
                overall_pass = False
        except Exception as e:
            U.err(f"RTL verification error: {e}")
            overall_pass = False

    # ── Summary ──────────────────────────────────────────────────────────
    print(file=_STDOUT)
    sep = "=" * 68
    print(bold(sep), file=_STDOUT)
    verdict = green("VERIFIED") if overall_pass else red("FAILED")
    print(f"  Verdict: {verdict}", file=_STDOUT)
    print(f"  Debug log: {LOG_FILE}", file=_STDOUT)
    print(bold(sep), file=_STDOUT)


if __name__ == "__main__":
    main()
