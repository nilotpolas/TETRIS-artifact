#!/usr/bin/env python3
"""
compare_with_tetris.py
======================

Produce the TETRIS vs COMPRESS comparison table matching the format of
Tables 2, 4, and 8 in the TETRIS TCHES 2026 paper.

Reads:
    - Results/<design>/MRLC_d<d>_lat<l>/results.json   (TETRIS results)
    - comparison/compress_logs/*.json                    (COMPRESS stats)

Produces a per-row comparison of:
    d-1, latency, RNG (TETRIS), RNG (COMPRESS:Base/Sep/Opt),
    Area (TETRIS), Area (COMPRESS:Opt),
    Speedup (COMPRESS:Opt / TETRIS)

NOTE ON AREA COMPARABILITY:
    COMPRESS's "Area Estimate (GE)" field bakes in the cost of randomness
    distribution:

        Area Estimate (GE) == base_gadget_area + RNG Bits * RNG Cost Per Bit

    TETRIS's area (from Yosys synthesis) treats random bits as free
    primary inputs, with no distribution cost charged. To make an
    apples-to-apples comparison, we back out COMPRESS's RNG contribution:

        area_no_rng = Area Estimate (GE) - (RNG Bits * RNG Cost Per Bit)

    The original COMPRESS total is preserved as area_ge_total in every
    record and surfaced as extra columns in the table/CSV for
    transparency, so reviewers can see both the RNG-free area we compare
    against TETRIS and COMPRESS's original reported total.

Usage:
    python compare_with_tetris.py --benchmark aes_bp
    python compare_with_tetris.py --benchmark aes_bp --csv table2.csv
"""

import argparse
import csv
import json
import os
import re
import sys
from pathlib import Path

SCRIPT_DIR   = Path(__file__).resolve().parent
COMPRESS_DIR = SCRIPT_DIR / "compress_logs"
REPO_ROOT    = SCRIPT_DIR.parent
RESULTS_DIR  = REPO_ROOT / "src/Results"

# TETRIS design-name → compression-mode mapping
BENCHMARK_MAP = {
    "aes_bp":   {"tetris_design": "Boyer_Peraltas_sbox", "compress_prefix": "aes"},
    "canright": {"tetris_design": "Canright_sbox",       "compress_prefix": "canright_aes_sbox"},
    "skinny":   {"tetris_design": "skinny_sbox_nor",     "compress_prefix": "skinny"},
}

FILENAME_RE = re.compile(
    r"^(?P<mode_prefix>.+?)__"
    r"(?P<circuit>.+?)_"
    r"d(?P<num_shares>\d+)_"
    r"l(?P<latency>\d+)"
    r"\.json$"
)

MODE_MAP = {
    "aes_base":               ("aes_bp",   "base"),
    "aes_sep":                ("aes_bp",   "sep"),
    "aes_opt":                ("aes_bp",   "opt"),
    "canright_aes_sbox_opt":  ("canright", "opt"),
    "skinny_base":            ("skinny",   "base"),
    "skinny_sep":             ("skinny",   "sep"),
    "skinny_opt":             ("skinny",   "opt"),
}


def load_compress_records():
    """Load all COMPRESS stats files into a dict keyed by (bench, mode, d-1, latency).

    See module docstring for why area_ge is derived (RNG-free) rather than
    read directly from "Area Estimate (GE)".
    """
    records = {}
    if not COMPRESS_DIR.exists():
        return records
    for fname in os.listdir(COMPRESS_DIR):
        if not fname.endswith(".json"):
            continue
        m = FILENAME_RE.match(fname)
        if not m or m.group("mode_prefix") not in MODE_MAP:
            continue
        benchmark, mode = MODE_MAP[m.group("mode_prefix")]
        num_shares = int(m.group("num_shares"))
        d_minus_1  = num_shares - 1
        latency    = int(m.group("latency"))
        try:
            with open(COMPRESS_DIR / fname) as f:
                data = json.load(f)
        except Exception:
            continue

        rng_bits         = data.get("RNG Bits")
        rng_cost_per_bit = data.get("RNG Cost Per Bit")
        area_total       = data.get("Area Estimate (GE)")

        area_no_rng = None
        if area_total is not None and rng_bits is not None and rng_cost_per_bit is not None:
            try:
                area_no_rng = area_total - (rng_bits * rng_cost_per_bit)
            except (TypeError, ValueError):
                area_no_rng = None

        records[(benchmark, mode, d_minus_1, latency)] = {
            "rng_bits":         rng_bits,
            "area_ge":          area_no_rng,   # RNG-free, comparable to TETRIS
            "area_ge_total":    area_total,    # original COMPRESS value, for reference
            "rng_cost_per_bit": rng_cost_per_bit,
            "solve_time":       data.get("solve_time"),
        }
    return records


def load_tetris_record(design: str, d: int, lat: int):
    """Load the corresponding TETRIS MRLC result.json (if present)."""
    path = RESULTS_DIR / design / f"MRLC_d{d}_lat{lat}" / "results.json"
    if not path.exists():
        return None
    try:
        with open(path) as f:
            data = json.load(f)
    except Exception:
        return None
    synth = data.get("synthesis", {}) or {}
    return {
        "rng_bits":   data.get("achieved_randomness"),
        "latency":    data.get("achieved_latency"),
        "area_ge":    synth.get("area_ge"),
        "dse_time":   data.get("dse_time_sec", data.get("wall_time_sec")),
    }


def build_table(benchmark: str, compress_records: dict):
    """Assemble one comparison table for a single benchmark."""
    bench_info = BENCHMARK_MAP[benchmark]
    tetris_design = bench_info["tetris_design"]

    # Find all (d-1, latency) pairs where any COMPRESS mode has data
    keys = [(b, m, d, l) for (b, m, d, l) in compress_records.keys() if b == benchmark]
    dl_pairs = sorted(set((d, l) for (_, _, d, l) in keys))

    rows = []
    for (d, lat) in dl_pairs:
        tetris  = load_tetris_record(tetris_design, d, lat)
        c_base  = compress_records.get((benchmark, "base", d, lat))
        c_sep   = compress_records.get((benchmark, "sep",  d, lat))
        c_opt   = compress_records.get((benchmark, "opt",  d, lat))

        speedup = None
        if tetris and tetris.get("dse_time") and c_opt and c_opt.get("solve_time"):
            try:
                speedup = c_opt["solve_time"] / float(tetris["dse_time"])
            except (TypeError, ValueError, ZeroDivisionError):
                pass

        rows.append({
            "d_minus_1":       d,
            "latency":         lat,
            "t_rng":           tetris["rng_bits"] if tetris else None,
            "t_area":          tetris["area_ge"] if tetris else None,
            "t_dse":           tetris["dse_time"] if tetris else None,
            "c_base_rng":         c_base["rng_bits"]      if c_base else None,
            "c_base_area":        c_base["area_ge"]        if c_base else None,
            "c_base_area_total":  c_base["area_ge_total"]  if c_base else None,
            "c_base_solve":       c_base["solve_time"]     if c_base else None,
            "c_sep_rng":          c_sep["rng_bits"]        if c_sep else None,
            "c_sep_area":         c_sep["area_ge"]         if c_sep else None,
            "c_sep_area_total":   c_sep["area_ge_total"]   if c_sep else None,
            "c_sep_solve":        c_sep["solve_time"]      if c_sep else None,
            "c_opt_rng":          c_opt["rng_bits"]        if c_opt else None,
            "c_opt_area":         c_opt["area_ge"]         if c_opt else None,
            "c_opt_area_total":   c_opt["area_ge_total"]   if c_opt else None,
            "c_opt_solve":        c_opt["solve_time"]      if c_opt else None,
            "speedup_vs_opt":  speedup,
        })
    return rows


def fmt(x, spec=".2f", none="—"):
    if x is None:
        return none
    try:
        return format(x, spec)
    except (TypeError, ValueError):
        return str(x)


def print_table(benchmark: str, rows: list):
    print(f"\n{'='*160}")
    print(f"  TETRIS vs COMPRESS — {benchmark}")
    print(f"  (Area columns are RNG-free; '*Total' columns include COMPRESS's baked-in RNG cost)")
    print(f"{'='*160}")
    headers = ["d-1", "Lat",
               "T:RNG", "T:Area(GE)", "T:DSE(s)",
               "C:Base RNG", "C:Base Area", "C:Base Total", "C:Base Solve",
               "C:Sep RNG",  "C:Sep Area",  "C:Sep Total",  "C:Sep Solve",
               "C:Opt RNG",  "C:Opt Area",  "C:Opt Total",  "C:Opt Solve",
               "Speedup vs Opt"]
    print("  ".join(headers))
    print("-" * 160)
    for r in rows:
        print("  ".join([
            fmt(r["d_minus_1"], "d"),
            fmt(r["latency"], "d"),
            fmt(r["t_rng"], "d"),
            fmt(r["t_area"], ".0f"),
            fmt(r["t_dse"], ".3f"),
            fmt(r["c_base_rng"], "d"),
            fmt(r["c_base_area"], ".0f"),
            fmt(r["c_base_area_total"], ".0f"),
            fmt(r["c_base_solve"], ".2f"),
            fmt(r["c_sep_rng"], "d"),
            fmt(r["c_sep_area"], ".0f"),
            fmt(r["c_sep_area_total"], ".0f"),
            fmt(r["c_sep_solve"], ".2f"),
            fmt(r["c_opt_rng"], "d"),
            fmt(r["c_opt_area"], ".0f"),
            fmt(r["c_opt_area_total"], ".0f"),
            fmt(r["c_opt_solve"], ".2f"),
            fmt(r["speedup_vs_opt"], ".1f") + "×" if r["speedup_vs_opt"] else "—",
        ]))


def save_csv(rows: list, path: str):
    with open(path, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=rows[0].keys())
        writer.writeheader()
        writer.writerows(rows)
    print(f"[SAVED] {path}")


def main():
    p = argparse.ArgumentParser(
        description="TETRIS vs COMPRESS comparison table (paper-format)"
    )
    p.add_argument("--benchmark", choices=list(BENCHMARK_MAP.keys()),
                   default="aes_bp",
                   help="Benchmark to compare (default: aes_bp = Boyer-Peralta)")
    p.add_argument("--csv", metavar="PATH", help="Save comparison table as CSV")
    args = p.parse_args()

    compress_records = load_compress_records()
    if not compress_records:
        sys.exit(f"ERROR: no COMPRESS records found in {COMPRESS_DIR}")

    rows = build_table(args.benchmark, compress_records)
    print_table(args.benchmark, rows)

    if args.csv:
        save_csv(rows, args.csv)


if __name__ == "__main__":
    main()
