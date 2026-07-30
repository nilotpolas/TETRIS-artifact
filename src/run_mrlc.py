#!/usr/bin/env python3
"""
run_mrlc.py — Minimize Randomness under Latency Constraint (MRLC)
==================================================================
Full DSE pipeline from C source to synthesized area metrics.

Usage examples:
    python run_mrlc.py --design Canright_sbox.c --latency 4 --order 1
    python run_mrlc.py --design Boyer_Peraltas_sbox.c --latency 5 --order 2
    python run_mrlc.py --design skinny_sbox.c --latency 3 --order 1 --skip-synth
    python run_mrlc.py --list-designs
"""

import argparse
import os
import shutil
import sys
import time

# ── Make sure the framework root is in the path ───────────────────────────────
_ROOT = os.path.dirname(os.path.abspath(__file__))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

import _dse_utils as U
from _dse_utils import (
    step, ok, warn, err,
    bold, green, yellow, cyan, red, dim,
    FRAMEWORK_DIR, C_FILES_DIR, RESULTS_DIR,
    load_gadget_specs, print_gadget_table,
    run_preprocessing, run_circuit_transform, run_maskedhls,
    run_yosys_synthesis, gadget_distribution,
    print_results, save_json_results,
    init_log, capture, LOG_FILE,
    MASKEDHLS_SRC, _STDOUT,
)

TOTAL_STEPS = 7  # preprocessing(1), gadgets(2), MRLC(3), asym-opt(4), HLS(5), synth(6), report(7)


def parse_args():
    p = argparse.ArgumentParser(
        prog="run_mrlc.py",
        description="MRLC — Minimize Randomness under Latency Constraint",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python run_mrlc.py --design Canright_sbox.c --latency 4 --order 1
  python run_mrlc.py --design Boyer_Peraltas_sbox.c --latency 5 --order 2
  python run_mrlc.py --list-designs
        """,
    )
    p.add_argument("--design",        metavar="FILE.c",   help="Input C design file (name only, from TestFiles/C_files/)")
    p.add_argument("--latency",       type=int,           help="Latency budget (in clock cycles)")
    p.add_argument("--order",         type=int, default=1, choices=[1,2,3,4,5], help="Masking security order d, 1–5 (default: 1)")
    p.add_argument("--top-module",    default="sbox",     help="Top C function / Verilog module name (default: sbox)")
    p.add_argument("--use-comar",     action="store_true", help="Include COMAR gadget (only available for d=1)")
    p.add_argument("--skip-synth",    action="store_true", help="Skip Yosys gate-level synthesis")
    p.add_argument("--no-asym-opt",   action="store_true", help="Skip asymmetric gadget optimization pass")
    p.add_argument("--debug",         action="store_true", help="Enable verbose DP debug output")
    p.add_argument("--output-dir",    metavar="DIR",       help="Custom directory for result files")
    p.add_argument("--list-designs",  action="store_true", help="List available C design files and exit")
    return p.parse_args()


def main():
    args = parse_args()

    # ── list-designs shortcut ──────────────────────────────────────────────────
    if args.list_designs:
        U.list_designs()
        sys.exit(0)

    # ── validate required args ─────────────────────────────────────────────────
    if not args.design or args.latency is None:
        err("--design and --latency are required.  Use --list-designs to see available files.")
        sys.exit(1)

    design_file = args.design if args.design.endswith(".c") else args.design + ".c"
    c_path      = os.path.join(C_FILES_DIR, design_file)
    if not os.path.isfile(c_path):
        err(f"Design file not found: {c_path}")
        U.list_designs()
        sys.exit(1)

    design_name = design_file.replace(".c", "")
    d           = args.order
    top_module  = args.top_module
    latency_budget = args.latency

    rtl_filename = f"{design_name}_d{d}_lat{latency_budget}.v"

    out_dir = args.output_dir or os.path.join(
        RESULTS_DIR, design_name, f"MRLC_d{d}_lat{latency_budget}"
    )

    # ── initialise log (truncates previous run) ───────────────────────────────
    init_log("MRLC", design_name, "Latency budget", latency_budget, d)

    # ── header ─────────────────────────────────────────────────────────────────
    print(file=_STDOUT)
    print(bold("=" * 68), file=_STDOUT)
    print(bold("  DSE-Framework — MRLC (Minimize Randomness under Latency Constraint)"), file=_STDOUT)
    print(bold("=" * 68), file=_STDOUT)
    print(f"  Design        : {cyan(design_name)}", file=_STDOUT)
    print(f"  Security order: d = {d}  ({d+1} shares)", file=_STDOUT)
    print(f"  Latency budget: {bold(str(latency_budget))} cycles", file=_STDOUT)
    print(f"  Top module    : {top_module}", file=_STDOUT)
    print(f"  Debug log     : {LOG_FILE}", file=_STDOUT)
    print(file=_STDOUT)

    wall_start = time.time()

    # ── STEP 1: Preprocessing ─────────────────────────────────────────────────
    step(1, TOTAL_STEPS, "Preprocessing  (TAC → Inline → AND trees)")
    and_tree, and_xor_tree = run_preprocessing(c_path, top_module)
    dse_start = time.time()   # DSE timer starts here (after preprocessing)

    # ── STEP 2: Gadget database ────────────────────────────────────────────────
    step(2, TOTAL_STEPS, "Loading gadget specs from database")
    gadget_specs = load_gadget_specs(d, use_comar=args.use_comar)
    print_gadget_table(gadget_specs, d)

    # ── STEP 3: MRLC DP algorithm ─────────────────────────────────────────────
    step(3, TOTAL_STEPS, f"Running MRLC DP  (target latency = {latency_budget} cycles)")

    import importlib
    import DSE_algorithm.mrlc, DSE_algorithm.dse
    import Gadgets
    with capture():
        importlib.reload(DSE_algorithm.mrlc)
        importlib.reload(DSE_algorithm.dse)
        importlib.reload(Gadgets)
    from DSE_algorithm.mrlc import MRLC

    mrlc_obj = MRLC(d=d, and_tree=and_tree, gadget_map=gadget_specs, and_xor_tree=and_xor_tree)
    mrlc_obj.debug = args.debug

    t0 = time.time()
    with capture():
        mrlc_obj._mrlc_dp(latency_budget)
    mrlc_elapsed = time.time() - t0

    ok(f"MRLC DP completed  ({mrlc_elapsed:.3f}s)")
    ok(f"Randomness : {bold(str(mrlc_obj.total_randomness_after_mrlc))} bits")
    ok(f"Latency    : {bold(str(mrlc_obj.total_latency_after_mrlc))} cycles")

    # ── STEP 4: Asymmetric gadget optimisation ─────────────────────────────────
    step(4, TOTAL_STEPS, "Asymmetric gadget optimisation  (HPC3 → HPC2 where beneficial)")
    if args.no_asym_opt:
        warn("Skipped (--no-asym-opt flag set)")
    else:
        from asymmetric_gadget_optimization import optimize_mrlc_with_asymmetric_gadgets
        t0 = time.time()
        with capture():
            mrlc_obj = optimize_mrlc_with_asymmetric_gadgets(mrlc_obj, and_xor_tree, debug=False)
        ok(f"Optimisation pass completed  ({time.time()-t0:.3f}s)")
        ok(f"Randomness after opt : {bold(str(mrlc_obj.total_randomness_after_mrlc))} bits")
        ok(f"Latency after opt    : {bold(str(mrlc_obj.total_latency_after_mrlc))} cycles")

    achieved_randomness = mrlc_obj.total_randomness_after_mrlc
    achieved_latency    = mrlc_obj.total_latency_after_mrlc

    gcounts = gadget_distribution(mrlc_obj)

    # ── STEP 5: Circuit transformation + MaskedHLS ────────────────────────────
    step(5, TOTAL_STEPS, "Circuit transformation + MaskedHLS → Verilog RTL")
    share_out = run_circuit_transform(mrlc_obj)
    dse_elapsed = time.time() - dse_start   # DSE timer ends here (masked C written, MaskedHLS not yet started)
    hls_latency, rtl_abs = run_maskedhls(
        share_out, top_module=top_module, rtl_filename=rtl_filename
    )

    # save masked C alongside results (used by run_verify.py)
    os.makedirs(out_dir, exist_ok=True)
    shutil.copy(U.SHARE_DIR + "/output.c", os.path.join(out_dir, "masked_output.c"))

    # ── STEP 6: Yosys synthesis ───────────────────────────────────────────────
    area = cell_count = dff_count = None
    step(6, TOTAL_STEPS, "Yosys gate-level synthesis  (Nangate 45nm)")
    if args.skip_synth:
        warn("Skipped (--skip-synth flag set)")
    else:
        area, cell_count, dff_count = run_yosys_synthesis(rtl_abs, top_module, out_dir)

    # ── STEP 7: Results ───────────────────────────────────────────────────────
    step(7, TOTAL_STEPS, "Results")
    print_results(
        algorithm        = "MRLC",
        design_name      = design_name,
        d                = d,
        constraint_label = "Latency budget",
        constraint_val   = latency_budget,
        achieved_randomness = achieved_randomness,
        achieved_latency    = achieved_latency,
        hls_latency         = hls_latency,
        area             = area,
        cell_count       = cell_count,
        dff_count        = dff_count,
        gadget_counts    = gcounts,
        gadget_specs     = gadget_specs,
        elapsed_total    = dse_elapsed,
        out_dir          = out_dir,
    )

    # save JSON summary
    payload = {
        "algorithm":            "MRLC",
        "design":               design_name,
        "security_order_d":     d,
        "latency_budget":       latency_budget,
        "achieved_randomness":  achieved_randomness,
        "achieved_latency":     achieved_latency,
        "hls_verified_latency": hls_latency,
        "synthesis": {
            "area_ge":    area,
            "cell_count": cell_count,
            "dff_count":  dff_count,
        },
        "gadget_distribution":  gcounts,
        "dse_time_sec":         round(dse_elapsed, 3),
    }
    json_path = os.path.join(out_dir, "results.json")
    save_json_results(json_path, payload)


if __name__ == "__main__":
    main()
