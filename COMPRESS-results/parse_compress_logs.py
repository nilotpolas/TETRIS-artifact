#!/usr/bin/env python3
"""
parse_compress_logs.py
======================

Parse the cached COMPRESS stats.json files in compress_logs/ and produce
a structured summary matching the columns of the TETRIS paper's
comparison tables (Tables 2, 3, 4, 6, 7, 8).

Usage:
    python parse_compress_logs.py                    # Print summary table
    python parse_compress_logs.py --csv out.csv      # Save as CSV
    python parse_compress_logs.py --benchmark aes_bp # Filter by benchmark
    python parse_compress_logs.py --mode opt         # Filter by mode

Output columns:
    Benchmark, Mode, d-1, Latency, RNG Bits, Area (GE), Solve Time (s)

Where:
    - Benchmark:   aes_bp | canright | skinny
    - Mode:        base | sep | opt
    - d-1:         TETRIS-paper masking order (COMPRESS Num Shares - 1)
    - Latency:     Cycles
    - RNG Bits:    Fresh randomness bits required
    - Area (GE):   Area estimate in Gate Equivalents (NanGate45)
    - Solve Time:  Wall-clock time for COMPRESS's SAT solver
"""

import argparse
import csv
import json
import os
import re
import sys
from pathlib import Path

# ── Paths ─────────────────────────────────────────────────────────────────────
SCRIPT_DIR = Path(__file__).resolve().parent
LOGS_DIR   = SCRIPT_DIR / "compress_logs"


# ── Filename parsing ──────────────────────────────────────────────────────────
# Filenames follow: <mode>__<circuit_name>_d<num_shares>_l<latency>.json
# Examples:
#   aes_base__aes_bp_d2_l4.json
#   aes_opt__aes_bp_d5_l6.json
#   canright_aes_sbox_opt__aes_sbox_d3_l5.json
#   skinny_base__skinny_sbox_d2_l4.json

FILENAME_RE = re.compile(
    r"^(?P<mode_prefix>.+?)__"
    r"(?P<circuit>.+?)_"
    r"d(?P<num_shares>\d+)_"
    r"l(?P<latency>\d+)"
    r"\.json$"
)

# Map file prefix to (benchmark, mode)
MODE_MAP = {
    "aes_base":               ("aes_bp",   "base"),
    "aes_sep":                ("aes_bp",   "sep"),
    "aes_opt":                ("aes_bp",   "opt"),
    "canright_aes_sbox_opt":  ("canright", "opt"),
    "skinny_base":            ("skinny",   "base"),
    "skinny_sep":             ("skinny",   "sep"),
    "skinny_opt":             ("skinny",   "opt"),
}


def parse_filename(fname: str):
    """Extract (benchmark, mode, d_minus_1, latency) from a stats filename.
    Returns None if the filename doesn't match the expected pattern.
    """
    m = FILENAME_RE.match(fname)
    if not m:
        return None
    mode_prefix = m.group("mode_prefix")
    if mode_prefix not in MODE_MAP:
        return None
    benchmark, mode = MODE_MAP[mode_prefix]
    num_shares = int(m.group("num_shares"))
    latency    = int(m.group("latency"))
    return benchmark, mode, num_shares - 1, latency


def load_stats(path: Path):
    """Load a single stats.json file and return a dict of relevant fields."""
    with open(path) as f:
        data = json.load(f)
    return {
        "num_shares":       data.get("Num Shares"),
        "latency":          data.get("Latency"),
        "rng_bits":         data.get("RNG Bits"),
        "area_ge":          data.get("Area Estimate (GE)"),
        "area_ge_with_rng": data.get("Area Estimate (GE) with RNG"),
        "solve_time":       data.get("solve_time"),
    }


# ── Main gathering ────────────────────────────────────────────────────────────
def gather_all():
    """Walk compress_logs/ and return a list of records."""
    if not LOGS_DIR.exists():
        sys.exit(f"ERROR: compress_logs/ directory not found at {LOGS_DIR}")

    records = []
    skipped = []
    for fname in sorted(os.listdir(LOGS_DIR)):
        if not fname.endswith(".json"):
            continue
        parsed = parse_filename(fname)
        if parsed is None:
            skipped.append(fname)
            continue
        benchmark, mode, d_minus_1, latency_from_name = parsed
        try:
            stats = load_stats(LOGS_DIR / fname)
        except Exception as e:
            skipped.append(f"{fname} (load error: {e})")
            continue
        records.append({
            "file":       fname,
            "benchmark":  benchmark,
            "mode":       mode,
            "d_minus_1":  d_minus_1,
            "latency":    stats["latency"] or latency_from_name,
            "rng_bits":   stats["rng_bits"],
            "area_ge":    stats["area_ge"],
            "solve_time": stats["solve_time"],
        })
    return records, skipped


# ── Output formatting ─────────────────────────────────────────────────────────
def print_table(records, headers=("Benchmark", "Mode", "d-1", "Latency",
                                    "RNG Bits", "Area (GE)", "Solve Time (s)")):
    """Print records as a fixed-width text table."""
    if not records:
        print("(no records)")
        return

    # Build rows for display
    rows = []
    for r in records:
        rows.append((
            r["benchmark"],
            r["mode"],
            r["d_minus_1"],
            r["latency"],
            r["rng_bits"],
            f"{r['area_ge']:.1f}" if r["area_ge"] is not None else "—",
            f"{r['solve_time']:.3f}" if r["solve_time"] is not None else "—",
        ))

    widths = [max(len(str(h)), max(len(str(row[i])) for row in rows))
              for i, h in enumerate(headers)]
    hdr    = "  ".join(str(h).ljust(w) for h, w in zip(headers, widths))
    sep    = "  ".join("-" * w for w in widths)
    print(hdr)
    print(sep)
    for row in rows:
        print("  ".join(str(c).ljust(w) for c, w in zip(row, widths)))


def save_csv(records, path):
    fields = ["benchmark", "mode", "d_minus_1", "latency",
              "rng_bits", "area_ge", "solve_time", "file"]
    with open(path, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=fields)
        w.writeheader()
        for r in records:
            w.writerow({k: r.get(k, "") for k in fields})
    print(f"[SAVED] {path}")


# ── Main ──────────────────────────────────────────────────────────────────────
def main():
    p = argparse.ArgumentParser(
        description="Parse cached COMPRESS stats.json files into a summary table."
    )
    p.add_argument("--csv", metavar="PATH", default=None,
                   help="Save results to CSV file")
    p.add_argument("--benchmark", choices=["aes_bp", "canright", "skinny"],
                   help="Filter to a single benchmark")
    p.add_argument("--mode", choices=["base", "sep", "opt"],
                   help="Filter to a single mode")
    p.add_argument("--order", type=int, metavar="D",
                   help="Filter to a single TETRIS masking order (d-1)")
    p.add_argument("--sort", choices=["benchmark", "mode", "d", "latency", "file"],
                   default="benchmark",
                   help="Sort output by field (default: benchmark)")
    args = p.parse_args()

    records, skipped = gather_all()

    if skipped:
        print(f"# {len(skipped)} file(s) skipped (bad format or load errors)", file=sys.stderr)

    # Filter
    if args.benchmark:
        records = [r for r in records if r["benchmark"] == args.benchmark]
    if args.mode:
        records = [r for r in records if r["mode"] == args.mode]
    if args.order is not None:
        records = [r for r in records if r["d_minus_1"] == args.order]

    # Sort
    sort_key_map = {
        "benchmark": lambda r: (r["benchmark"], r["mode"], r["d_minus_1"], r["latency"]),
        "mode":      lambda r: (r["mode"], r["benchmark"], r["d_minus_1"], r["latency"]),
        "d":         lambda r: (r["d_minus_1"], r["benchmark"], r["mode"], r["latency"]),
        "latency":   lambda r: (r["latency"], r["benchmark"], r["mode"], r["d_minus_1"]),
        "file":      lambda r: r["file"],
    }
    records.sort(key=sort_key_map[args.sort])

    # Print
    print(f"# Total records: {len(records)}")
    print_table(records)

    if args.csv:
        save_csv(records, args.csv)


if __name__ == "__main__":
    main()
