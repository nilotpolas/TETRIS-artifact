#!/usr/bin/env python3
"""
run_marc.py — Minimize Area under Randomness and latency Constraints (MARC)
============================================================================
Full DSE pipeline from C source to synthesized area metrics.

Usage examples:
    python run_marc.py --design Boyer_Peraltas_sbox.c --max-latency 6 --max-randomness 120 --order 1
    python run_marc.py --design Canright_sbox.c --max-latency 5 --max-randomness 80 --order 1 --show-pareto
    python run_marc.py --design skinny_sbox_nor.c --max-latency 4 --max-randomness 60 --order 1 --skip-synth
    python run_marc.py --list-designs
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
    area_to_kge, area_wo_rand_kge,
)

TOTAL_STEPS = 8   # preprocessing(1), gadgets(2), MARC(3), asym-opt(4), HLS(5), synth(6), pareto(7), report(8)


def parse_args():
    p = argparse.ArgumentParser(
        prog="run_marc.py",
        description="MARC — Minimize Area under Randomness and latency Constraints",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python run_marc.py --design Boyer_Peraltas_sbox.c --max-latency 6 --max-randomness 120 --order 1
  python run_marc.py --design Canright_sbox.c --max-latency 5 --max-randomness 80 --order 1 --show-pareto
  python run_marc.py --list-designs
        """,
    )
    p.add_argument("--design",          metavar="FILE.c",  help="Input C design file (name only, from TestFiles/C_files/)")
    p.add_argument("--max-latency",     type=int,          help="Maximum allowed latency (clock cycles)")
    p.add_argument("--max-randomness",  type=int,          help="Maximum allowed randomness (bits)")
    p.add_argument("--order",           type=int, default=1, choices=[1,2,3,4,5], help="Masking security order d, 1–5 (default: 1)")
    p.add_argument("--top-module",      default="sbox",    help="Top C function / Verilog module name (default: sbox)")
    p.add_argument("--use-comar",       action="store_true", help="Include COMAR gadget (only available for d=1)")
    p.add_argument("--skip-synth",      action="store_true", help="Skip Yosys gate-level synthesis")
    p.add_argument("--show-pareto",     action="store_true", help="Display full Pareto frontier table")
    p.add_argument("--debug",           action="store_true", help="Enable verbose DP debug output")
    p.add_argument("--output-dir",      metavar="DIR",     help="Custom directory for result files")
    p.add_argument("--list-designs",    action="store_true", help="List available C design files and exit")
    return p.parse_args()


def print_pareto_table(pareto_front, label="Pareto Frontier"):
    """Display the Pareto-optimal (latency, randomness, area) triples."""
    from tabulate import tabulate

    _NAND2 = 0.798
    rows = []
    for lat, rand, area_raw in pareto_front:
        kge     = area_raw / _NAND2 / 1000.0
        rows.append([lat, rand, f"{area_raw:.1f}", f"{kge:.3f}"])

    print(f"\n  {bold('── ' + label + ' ──')}", file=_STDOUT)
    tbl = tabulate(
        rows,
        headers=["Latency (cycles)", "Randomness (bits)", "Area (lib-units)", "Area (kGE)"],
        tablefmt="simple",
        numalign="right",
    )
    print("  " + tbl.replace("\n", "\n  "), file=_STDOUT)
    print(file=_STDOUT)


def main():
    args = parse_args()

    # ── list-designs shortcut ──────────────────────────────────────────────────
    if args.list_designs:
        U.list_designs()
        sys.exit(0)

    # ── validate required args ─────────────────────────────────────────────────
    if not args.design or args.max_latency is None or args.max_randomness is None:
        err("--design, --max-latency and --max-randomness are all required.  "
            "Use --list-designs to see available files.")
        sys.exit(1)

    design_file = args.design if args.design.endswith(".c") else args.design + ".c"
    c_path      = os.path.join(C_FILES_DIR, design_file)
    if not os.path.isfile(c_path):
        err(f"Design file not found: {c_path}")
        U.list_designs()
        sys.exit(1)

    design_name    = design_file.replace(".c", "")
    d              = args.order
    top_module     = args.top_module
    max_latency    = args.max_latency
    max_randomness = args.max_randomness

    rtl_filename = f"{design_name}_d{d}_marc_lat{max_latency}_rand{max_randomness}.v"

    out_dir = args.output_dir or os.path.join(
        RESULTS_DIR, design_name,
        f"MARC_d{d}_lat{max_latency}_rand{max_randomness}"
    )

    # ── initialise log ────────────────────────────────────────────────────────
    init_log("MARC", design_name, "max_latency / max_randomness",
             f"{max_latency} / {max_randomness}", d)

    # ── header ─────────────────────────────────────────────────────────────────
    print(file=_STDOUT)
    print(bold("=" * 68), file=_STDOUT)
    print(bold("  DSE-Framework — MARC (Minimize Area under R and L Constraints)"), file=_STDOUT)
    print(bold("=" * 68), file=_STDOUT)
    print(f"  Design            : {cyan(design_name)}", file=_STDOUT)
    print(f"  Security order    : d = {d}  ({d+1} shares)", file=_STDOUT)
    print(f"  Max latency       : {bold(str(max_latency))} cycles", file=_STDOUT)
    print(f"  Max randomness    : {bold(str(max_randomness))} bits", file=_STDOUT)
    print(f"  Top module        : {top_module}", file=_STDOUT)
    print(f"  Debug log         : {LOG_FILE}", file=_STDOUT)
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

    # ── STEP 3: MARC algorithm ────────────────────────────────────────────────
    step(3, TOTAL_STEPS,
         f"Running MARC  (lat ≤ {max_latency}, rand ≤ {max_randomness})")

    import importlib
    import DSE_algorithm.marc, DSE_algorithm.mrlc, DSE_algorithm.dse
    import Gadgets, Gadgets.hpc2_swapped, Gadgets.hpc2o_swapped
    with capture():
        importlib.reload(Gadgets.hpc2_swapped)
        importlib.reload(Gadgets.hpc2o_swapped)
        importlib.reload(Gadgets)
        importlib.reload(DSE_algorithm.dse)
        importlib.reload(DSE_algorithm.mrlc)
        importlib.reload(DSE_algorithm.marc)
    from DSE_algorithm.marc import MARC

    marc_obj = MARC(d=d, and_tree=and_tree, gadget_map=gadget_specs,
                    and_xor_tree=and_xor_tree)
    marc_obj.debug = args.debug

    t0 = time.time()
    with capture():
        marc_obj.marc(max_latency=max_latency, max_randomness=max_randomness)
    marc_elapsed = time.time() - t0
    ok(f"MARC completed  ({marc_elapsed:.3f}s)")

    gadget_def          = marc_obj.get_gadget_definition()
    achieved_randomness = compute_total_randomness(gadget_def, gadget_specs)
    achieved_latency    = marc_obj.total_latency_after_marc
    pareto_front        = marc_obj.get_pareto_front()

    ok(f"Achieved latency    : {bold(str(achieved_latency))} cycles")
    ok(f"Achieved randomness : {bold(str(achieved_randomness))} bits")
    ok(f"Pareto-front points : {len(pareto_front)}")

    # ── STEP 4: Asymmetric gadget optimisation ─────────────────────────────────
    step(4, TOTAL_STEPS, "Asymmetric gadget optimisation  (post-MARC transform pass)")
    try:
        from asymmetric_gadget_optimization import optimize_mrlc_with_asymmetric_gadgets
        t0 = time.time()
        with capture():
            marc_obj = optimize_mrlc_with_asymmetric_gadgets(marc_obj, and_xor_tree, debug=False)
        ok(f"Optimisation pass completed  ({time.time()-t0:.3f}s)")
        achieved_randomness = compute_total_randomness(
            marc_obj.get_gadget_definition(), gadget_specs)
        achieved_latency = getattr(marc_obj, 'total_latency_after_mrlc',
                                   getattr(marc_obj, 'total_latency_after_marc', achieved_latency))
        ok(f"Randomness after opt : {bold(str(achieved_randomness))} bits")
        ok(f"Latency after opt    : {bold(str(achieved_latency))} cycles")
    except Exception as e:
        warn(f"Asymmetric optimisation skipped: {e}")

    gcounts = gadget_distribution(marc_obj)

    # ── STEP 5: Circuit transformation + MaskedHLS ────────────────────────────
    step(5, TOTAL_STEPS, "Circuit transformation + MaskedHLS → Verilog RTL")
    share_out = run_circuit_transform(marc_obj)
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

    # ── STEP 7: Pareto frontier ───────────────────────────────────────────────
    step(7, TOTAL_STEPS, "Pareto frontier")
    if args.show_pareto:
        print_pareto_table(pareto_front, "Pareto Frontier (all non-dominated designs)")
    else:
        ok(f"{len(pareto_front)} non-dominated design points found  "
           f"(use --show-pareto to display them)")

    # ── STEP 8: Results ───────────────────────────────────────────────────────
    step(8, TOTAL_STEPS, "Results")
    print_results(
        algorithm           = "MARC",
        design_name         = design_name,
        d                   = d,
        constraint_label    = "Max latency / Max randomness",
        constraint_val      = f"{max_latency} / {max_randomness}",
        achieved_randomness = achieved_randomness,
        achieved_latency    = achieved_latency,
        hls_latency         = hls_latency,
        area                = area,
        cell_count          = cell_count,
        dff_count           = dff_count,
        gadget_counts       = gcounts,
        gadget_specs        = gadget_specs,
        elapsed_total       = dse_elapsed,
        out_dir             = out_dir,
    )

    # save JSON summary
    payload = {
        "algorithm":            "MARC",
        "design":               design_name,
        "security_order_d":     d,
        "max_latency":          max_latency,
        "max_randomness":       max_randomness,
        "achieved_latency":     achieved_latency,
        "achieved_randomness":  achieved_randomness,
        "hls_verified_latency": hls_latency,
        "synthesis": {
            "area_ge":    area,
            "cell_count": cell_count,
            "dff_count":  dff_count,
        },
        "gadget_distribution":  gcounts,
        "pareto_front": [
            {"latency": lat, "randomness": rand, "area_lib": ar}
            for lat, rand, ar in pareto_front
        ],
        "dse_time_sec":         round(dse_elapsed, 3),
    }
    json_path = os.path.join(out_dir, "results.json")
    save_json_results(json_path, payload)


if __name__ == "__main__":
    main()
