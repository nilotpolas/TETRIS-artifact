#!/usr/bin/env python3
"""
run_mlrc.py — Minimize Latency under Randomness Constraint (MLRC)
=================================================================
Full DSE pipeline from C source to synthesized area metrics.

Usage examples:
    python run_mlrc.py --design Boyer_Peraltas_sbox.c --randomness 168 --order 2
    python run_mlrc.py --design Canright_sbox.c --randomness 102 --order 1
    python run_mlrc.py --design skinny_sbox.c --randomness 80 --order 1 --skip-synth
    python run_mlrc.py --list-designs
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
    compute_total_randomness,
    print_results, save_json_results,
    init_log, capture, LOG_FILE,
    MASKEDHLS_SRC, _STDOUT,
)

TOTAL_STEPS = 6   # preprocessing(1), gadgets(2), MLRC(3), HLS(4), synth(5), report(6)


def parse_args():
    p = argparse.ArgumentParser(
        prog="run_mlrc.py",
        description="MLRC — Minimize Latency under Randomness Constraint",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python run_mlrc.py --design Boyer_Peraltas_sbox.c --randomness 168 --order 2
  python run_mlrc.py --design Canright_sbox.c --randomness 102 --order 1
  python run_mlrc.py --list-designs
        """,
    )
    p.add_argument("--design",        metavar="FILE.c",    help="Input C design file (name only, from TestFiles/C_files/)")
    p.add_argument("--randomness",    type=int,            help="Randomness budget (in bits)")
    p.add_argument("--order",         type=int, default=2, choices=[1,2,3,4,5], help="Masking security order d, 1–5 (default: 2)")
    p.add_argument("--top-module",    default="sbox",      help="Top C function / Verilog module name (default: sbox)")
    p.add_argument("--use-comar",     action="store_true", help="Include COMAR gadget (only available for d=1)")
    p.add_argument("--skip-synth",    action="store_true", help="Skip Yosys gate-level synthesis")
    p.add_argument("--debug",         action="store_true", help="Enable verbose algorithm debug output")
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
    if not args.design or args.randomness is None:
        err("--design and --randomness are required.  Use --list-designs to see available files.")
        sys.exit(1)

    design_file = args.design if args.design.endswith(".c") else args.design + ".c"
    c_path      = os.path.join(C_FILES_DIR, design_file)
    if not os.path.isfile(c_path):
        err(f"Design file not found: {c_path}")
        U.list_designs()
        sys.exit(1)

    design_name      = design_file.replace(".c", "")
    d                = args.order
    top_module       = args.top_module
    randomness_budget = args.randomness

    rtl_filename = f"{design_name}_d{d}_rand{randomness_budget}.v"

    out_dir = args.output_dir or os.path.join(
        RESULTS_DIR, design_name, f"MLRC_d{d}_rand{randomness_budget}"
    )

    # ── initialise log (truncates previous run) ───────────────────────────────
    init_log("MLRC", design_name, "Randomness budget", randomness_budget, d)

    # ── header ─────────────────────────────────────────────────────────────────
    print(file=_STDOUT)
    print(bold("=" * 68), file=_STDOUT)
    print(bold("  DSE-Framework — MLRC (Minimize Latency under Randomness Constraint)"), file=_STDOUT)
    print(bold("=" * 68), file=_STDOUT)
    print(f"  Design          : {cyan(design_name)}", file=_STDOUT)
    print(f"  Security order  : d = {d}  ({d+1} shares)", file=_STDOUT)
    print(f"  Randomness budget: {bold(str(randomness_budget))} bits", file=_STDOUT)
    print(f"  Top module      : {top_module}", file=_STDOUT)
    print(f"  Debug log       : {LOG_FILE}", file=_STDOUT)
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

    # ── STEP 3: MLRC algorithm ────────────────────────────────────────────────
    step(3, TOTAL_STEPS, f"Running MLRC  (target randomness = {randomness_budget} bits)")

    import importlib
    import DSE_algorithm.mlrc, DSE_algorithm.dse
    import Gadgets, Gadgets.hpc2_swapped, Gadgets.hpc2o_swapped
    with capture():
        importlib.reload(Gadgets.hpc2_swapped)
        importlib.reload(Gadgets.hpc2o_swapped)
        importlib.reload(Gadgets)
        importlib.reload(DSE_algorithm.mlrc)
        importlib.reload(DSE_algorithm.dse)
    from DSE_algorithm.mlrc import MLRC

    mlrc_obj = MLRC(d=d, and_tree=and_tree, gadget_map=gadget_specs, and_xor_tree=and_xor_tree)

    t0 = time.time()
    with capture():
        mlrc_obj.mlrc(target_randomness=randomness_budget)
    mlrc_elapsed = time.time() - t0
    ok(f"MLRC completed  ({mlrc_elapsed:.3f}s)")

    gadget_def = mlrc_obj.get_gadget_definition()
    achieved_randomness = compute_total_randomness(gadget_def, gadget_specs)
    achieved_latency = getattr(mlrc_obj, "total_latency_after_mlrc",
                        getattr(mlrc_obj, "DAG_levels", None))

    ok(f"Randomness achieved   : {bold(str(achieved_randomness))} bits")
    if achieved_latency:
        ok(f"Critical-path latency : {bold(str(achieved_latency))} cycles")

    gcounts = gadget_distribution(mlrc_obj)

    # ── STEP 4: Circuit transformation + MaskedHLS ────────────────────────────
    step(4, TOTAL_STEPS, "Circuit transformation + MaskedHLS → Verilog RTL")
    share_out = run_circuit_transform(mlrc_obj)
    dse_elapsed = time.time() - dse_start   # DSE timer ends here (masked C written, MaskedHLS not yet started)
    hls_latency, rtl_abs = run_maskedhls(
        share_out, top_module=top_module, rtl_filename=rtl_filename
    )

    # save masked C alongside results (used by run_verify.py)
    os.makedirs(out_dir, exist_ok=True)
    shutil.copy(U.SHARE_DIR + "/output.c", os.path.join(out_dir, "masked_output.c"))

    # ── STEP 5: Yosys synthesis ───────────────────────────────────────────────
    area = cell_count = dff_count = None
    step(5, TOTAL_STEPS, "Yosys gate-level synthesis  (Nangate 45nm)")
    if args.skip_synth:
        warn("Skipped (--skip-synth flag set)")
    else:
        area, cell_count, dff_count = run_yosys_synthesis(rtl_abs, top_module, out_dir)

    # ── STEP 6: Results ───────────────────────────────────────────────────────
    step(6, TOTAL_STEPS, "Results")
    print_results(
        algorithm        = "MLRC",
        design_name      = design_name,
        d                = d,
        constraint_label = "Randomness budget",
        constraint_val   = randomness_budget,
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
        "algorithm":            "MLRC",
        "design":               design_name,
        "security_order_d":     d,
        "randomness_budget":    randomness_budget,
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
