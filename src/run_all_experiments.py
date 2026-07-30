#!/usr/bin/env python3
"""
run_all_experiments.py
======================
Batch runner for MRLC, MLRC, and MARC algorithms across all three benchmark
S-box designs and all constraints from the thesis report tables.

Usage:
    python run_all_experiments.py              # run all (skip synthesis)
    python run_all_experiments.py --algo mrlc  # MRLC only
    python run_all_experiments.py --algo mlrc  # MLRC only
    python run_all_experiments.py --algo marc  # MARC only
    python run_all_experiments.py --tables-only  # only regenerate tables from cached JSON
    python run_all_experiments.py --with-synth   # enable Yosys synthesis (slow)
    python run_all_experiments.py --output tables/results.txt  # custom output file
"""

import argparse
import json
import os
import subprocess
import sys
import time
from pathlib import Path

try:
    from tabulate import tabulate
    HAS_TABULATE = True
except ImportError:
    HAS_TABULATE = False

# ── Paths ─────────────────────────────────────────────────────────────────────
ROOT       = os.path.dirname(os.path.abspath(__file__))
RESULTS    = os.path.join(ROOT, "Results")
PYTHON     = sys.executable

# ── Constraint Tables from Thesis Report ──────────────────────────────────────
# MRLC: (design, order d-1, target_latency)
MRLC_CONFIGS = [
    # Boyer-Peralta (34 AND gates, 4 levels)
    *[("Boyer_Peraltas_sbox", d, lat)
      for d in [1, 2, 3, 4] for lat in [4, 5, 6]],
    # Canright (36 AND gates, 4 levels)
    *[("Canright_sbox", d, lat)
      for d in [1, 2, 3, 4] for lat in [4, 5, 6]],
    # SKINNY (8 AND gates, 4 levels)
    *[("skinny_sbox_nor", d, lat)
      for d in [1, 2, 3, 4] for lat in [4, 5, 6]],
]

# MLRC: (design, order d-1, target_randomness)
# Taken from Tab. 5.3 and 5.5 of the thesis (one target_rand per latency level)
MLRC_CONFIGS = [
    # Boyer-Peralta
    ("Boyer_Peraltas_sbox", 1, 57),   # → lat 4
    ("Boyer_Peraltas_sbox", 1, 43),   # → lat 5
    ("Boyer_Peraltas_sbox", 1, 36),   # → lat 6
    ("Boyer_Peraltas_sbox", 1, 34),   # → lat 7
    ("Boyer_Peraltas_sbox", 2, 172),
    ("Boyer_Peraltas_sbox", 2, 130),
    ("Boyer_Peraltas_sbox", 2, 108),
    ("Boyer_Peraltas_sbox", 2, 102),
    ("Boyer_Peraltas_sbox", 3, 344),
    ("Boyer_Peraltas_sbox", 3, 260),
    ("Boyer_Peraltas_sbox", 3, 216),
    ("Boyer_Peraltas_sbox", 3, 204),
    ("Boyer_Peraltas_sbox", 4, 570),
    ("Boyer_Peraltas_sbox", 4, 430),
    ("Boyer_Peraltas_sbox", 4, 360),
    ("Boyer_Peraltas_sbox", 4, 340),
    # Canright
    ("Canright_sbox", 1, 57),
    ("Canright_sbox", 1, 43),
    ("Canright_sbox", 1, 36),
    ("Canright_sbox", 2, 172),
    ("Canright_sbox", 2, 130),
    ("Canright_sbox", 2, 108),
    ("Canright_sbox", 3, 344),
    ("Canright_sbox", 3, 260),
    ("Canright_sbox", 3, 216),
    ("Canright_sbox", 4, 570),
    ("Canright_sbox", 4, 432),
    ("Canright_sbox", 4, 360),
    # SKINNY (8 AND gates)
    ("skinny_sbox_nor", 1, 21),   # → lat 4
    ("skinny_sbox_nor", 1, 15),   # → lat 5
    ("skinny_sbox_nor", 1, 11),   # → lat 6
    ("skinny_sbox_nor", 1,  9),   # → lat 7
    ("skinny_sbox_nor", 1,  8),   # → lat 8
    ("skinny_sbox_nor", 2, 64),
    ("skinny_sbox_nor", 2, 46),
    ("skinny_sbox_nor", 2, 34),
    ("skinny_sbox_nor", 2, 28),
    ("skinny_sbox_nor", 2, 24),
    ("skinny_sbox_nor", 3, 126),
    ("skinny_sbox_nor", 3, 90),
    ("skinny_sbox_nor", 3, 66),
    ("skinny_sbox_nor", 3, 54),
    ("skinny_sbox_nor", 3, 48),
    ("skinny_sbox_nor", 4, 212),
    ("skinny_sbox_nor", 4, 152),
    ("skinny_sbox_nor", 4, 112),
    ("skinny_sbox_nor", 4, 92),
    ("skinny_sbox_nor", 4, 80),
]

# MARC: (design, order d-1, max_latency, max_randomness)
# Chosen at the "elbow" of the MRLC trade-off curve:
#   max_rand = MRLC rand at min latency + small slack
#   max_lat  = min_latency + 1  (gives 1 extra cycle to trade for less randomness)
MARC_CONFIGS = [
    # Boyer-Peralta (MRLC lat=4: rand=46,138,276,460)
    ("Boyer_Peraltas_sbox", 1,  4,  68),
    ("Boyer_Peraltas_sbox", 1,  5,  65),   # lat4-5, rand~46
    ("Boyer_Peraltas_sbox", 1,  6,  60),   # lat4-6, rand=46 (tight)
    ("Boyer_Peraltas_sbox", 2,  4,  204),
    ("Boyer_Peraltas_sbox", 2,  5, 200),
    ("Boyer_Peraltas_sbox", 2,  6, 190),
    ("Boyer_Peraltas_sbox", 3,  4, 408),
    ("Boyer_Peraltas_sbox", 3,  5, 380),
    ("Boyer_Peraltas_sbox", 3,  6, 340),
    ("Boyer_Peraltas_sbox", 4,  4, 680),
    ("Boyer_Peraltas_sbox", 4,  5, 640),
    ("Boyer_Peraltas_sbox", 4,  6, 570),
    # Canright (MRLC lat=4: rand≈48,130,276,460)
    ("Canright_sbox", 1,  4,  72),
    ("Canright_sbox", 1,  5,  68),
    ("Canright_sbox", 1,  6,  60),
    ("Canright_sbox", 2,  4, 216),
    ("Canright_sbox", 2,  5, 200),
    ("Canright_sbox", 2,  6, 180),
    ("Canright_sbox", 3,  4, 482),
    ("Canright_sbox", 3,  5, 400),
    ("Canright_sbox", 3,  6, 380),
    ("Canright_sbox", 4,  4, 720),
    ("Canright_sbox", 4,  5, 690),
    ("Canright_sbox", 4,  6, 500),
    # SKINNY (MRLC lat=4: rand=12,36,72,120)
    ("skinny_sbox_nor", 1,  4, 21),
    ("skinny_sbox_nor", 1,  5, 15),
    ("skinny_sbox_nor", 1,  6, 13),
    ("skinny_sbox_nor", 2,  4, 64),
    ("skinny_sbox_nor", 2,  5, 50),
    ("skinny_sbox_nor", 2,  6, 40),
    ("skinny_sbox_nor", 3,  4, 126),
    ("skinny_sbox_nor", 3,  5, 110),
    ("skinny_sbox_nor", 3,  6, 90),
    ("skinny_sbox_nor", 4,  4, 190),
    ("skinny_sbox_nor", 4,  5, 160),
    ("skinny_sbox_nor", 4,  6, 130),
]

# ── Helpers ────────────────────────────────────────────────────────────────────

def _nice(design: str) -> str:
    """Short display name for a design."""
    return {
        "Boyer_Peraltas_sbox": "BoyerPeralta",
        "Canright_sbox":       "Canright",
        "skinny_sbox_nor":     "SKINNY",
    }.get(design, design)


def _run(cmd: list[str], label: str) -> int:
    """Run a subprocess and stream its output. Returns returncode."""
    print(f"\n{'─'*70}")
    print(f"  RUN: {label}")
    print(f"  CMD: {' '.join(cmd)}")
    print(f"{'─'*70}")
    t0 = time.time()
    proc = subprocess.run(cmd, cwd=ROOT)
    elapsed = time.time() - t0
    status = "OK" if proc.returncode == 0 else "FAILED"
    print(f"  [{status}]  wall-clock: {elapsed:.2f}s")
    return proc.returncode


def _load_json(path: str) -> dict | None:
    try:
        with open(path) as f:
            return json.load(f)
    except Exception:
        return None


def _mrlc_result_path(design: str, d: int, lat: int) -> str:
    return os.path.join(RESULTS, design, f"MRLC_d{d}_lat{lat}", "results.json")


def _mlrc_result_path(design: str, d: int, rand: int) -> str:
    return os.path.join(RESULTS, design, f"MLRC_d{d}_rand{rand}", "results.json")


def _marc_result_path(design: str, d: int, max_lat: int, max_rand: int) -> str:
    return os.path.join(RESULTS, design, f"MARC_d{d}_lat{max_lat}_rand{max_rand}", "results.json")


# ── Runners ────────────────────────────────────────────────────────────────────

def run_mrlc_all(skip_synth: bool, failed: list):
    print(f"\n{'═'*70}")
    print("  MRLC — Running {n} configurations".format(n=len(MRLC_CONFIGS)))
    print(f"{'═'*70}")
    for design, d, lat in MRLC_CONFIGS:
        out_dir = os.path.join(RESULTS, design, f"MRLC_d{d}_lat{lat}")
        cmd = [PYTHON, "run_mrlc.py",
               "--design", f"{design}.c",
               "--latency", str(lat),
               "--order", str(d),
               "--output-dir", out_dir]
        if skip_synth:
            cmd.append("--skip-synth")
        label = f"MRLC  {_nice(design)}  d-1={d}  lat={lat}"
        rc = _run(cmd, label)
        if rc != 0:
            failed.append(label)


def run_mlrc_all(skip_synth: bool, failed: list):
    print(f"\n{'═'*70}")
    print("  MLRC — Running {n} configurations".format(n=len(MLRC_CONFIGS)))
    print(f"{'═'*70}")
    for design, d, rand in MLRC_CONFIGS:
        out_dir = os.path.join(RESULTS, design, f"MLRC_d{d}_rand{rand}")
        cmd = [PYTHON, "run_mlrc.py",
               "--design", f"{design}.c",
               "--randomness", str(rand),
               "--order", str(d),
               "--output-dir", out_dir]
        if skip_synth:
            cmd.append("--skip-synth")
        label = f"MLRC  {_nice(design)}  d-1={d}  rand={rand}"
        rc = _run(cmd, label)
        if rc != 0:
            failed.append(label)


def run_marc_all(skip_synth: bool, failed: list):
    print(f"\n{'═'*70}")
    print("  MARC — Running {n} configurations".format(n=len(MARC_CONFIGS)))
    print(f"{'═'*70}")
    for design, d, max_lat, max_rand in MARC_CONFIGS:
        out_dir = os.path.join(RESULTS, design, f"MARC_d{d}_lat{max_lat}_rand{max_rand}")
        cmd = [PYTHON, "run_marc.py",
               "--design", f"{design}.c",
               "--max-latency", str(max_lat),
               "--max-randomness", str(max_rand),
               "--order", str(d),
               "--output-dir", out_dir]
        if skip_synth:
            cmd.append("--skip-synth")
        label = f"MARC  {_nice(design)}  d-1={d}  lat≤{max_lat}  rand≤{max_rand}"
        rc = _run(cmd, label)
        if rc != 0:
            failed.append(label)


# ── Table Builders ─────────────────────────────────────────────────────────────

def build_mrlc_table() -> list[list]:
    """Return rows for the MRLC summary table."""
    rows = []
    for design, d, lat in MRLC_CONFIGS:
        data = _load_json(_mrlc_result_path(design, d, lat))
        if data is None:
            rows.append([_nice(design), d, lat, "—", "—", "—", "—"])
            continue
        rand  = data.get("achieved_randomness", "—")
        a_lat = data.get("achieved_latency",    "—")
        area  = data.get("synthesis", {}).get("area_ge")
        area_s = f"{area/1000:.2f}" if area else "—"
        t     = data.get("dse_time_sec", data.get("wall_time_sec", "—"))
        rows.append([_nice(design), d, lat, rand, a_lat, area_s, t])
    return rows


def build_mlrc_table() -> list[list]:
    """Return rows for the MLRC summary table."""
    rows = []
    for design, d, rand in MLRC_CONFIGS:
        data = _load_json(_mlrc_result_path(design, d, rand))
        if data is None:
            rows.append([_nice(design), d, rand, "—", "—", "—", "—"])
            continue
        r_used = data.get("achieved_randomness", "—")
        a_lat  = data.get("achieved_latency",    "—")
        area   = data.get("synthesis", {}).get("area_ge")
        area_s = f"{area/1000:.2f}" if area else "—"
        t      = data.get("dse_time_sec", data.get("wall_time_sec", "—"))
        rows.append([_nice(design), d, rand, r_used, a_lat, area_s, t])
    return rows


def build_marc_table() -> list[list]:
    """Return rows for the MARC summary table."""
    rows = []
    for design, d, max_lat, max_rand in MARC_CONFIGS:
        data = _load_json(_marc_result_path(design, d, max_lat, max_rand))
        if data is None:
            rows.append([_nice(design), d, max_lat, max_rand, "—", "—", "—", "—"])
            continue
        a_lat  = data.get("achieved_latency",    "—")
        a_rand = data.get("achieved_randomness",  "—")
        area   = data.get("synthesis", {}).get("area_ge")
        area_s = f"{area/1000:.2f}" if area else "—"
        pareto = data.get("pareto_front", [])
        n_pf   = len(pareto)
        t      = data.get("dse_time_sec", data.get("wall_time_sec", "—"))
        rows.append([_nice(design), d, max_lat, max_rand, a_lat, a_rand, area_s, n_pf, t])
    return rows


def _fmt(headers, rows, fmt="simple") -> str:
    if HAS_TABULATE:
        return tabulate(rows, headers=headers, tablefmt=fmt)
    # fallback: plain text
    col_w = [max(len(str(h)), max((len(str(r[i])) for r in rows), default=0))
             for i, h in enumerate(headers)]
    sep   = "  ".join("-" * w for w in col_w)
    hdr   = "  ".join(str(h).ljust(w) for h, w in zip(headers, col_w))
    lines = [hdr, sep]
    for r in rows:
        lines.append("  ".join(str(c).ljust(w) for c, w in zip(r, col_w)))
    return "\n".join(lines)


def print_and_save_tables(output_file: str):
    """Build all tables, print to stdout, and write to output_file."""

    mrlc_rows = build_mrlc_table()
    mlrc_rows = build_mlrc_table()
    marc_rows = build_marc_table()

    mrlc_hdrs = ["Design", "d-1", "Target Lat", "Rand Used", "Achieved Lat", "Area (kGE)", "DSE Time (s)"]
    mlrc_hdrs = ["Design", "d-1", "Target Rand", "Rand Used", "Achieved Lat", "Area (kGE)", "DSE Time (s)"]
    marc_hdrs = ["Design", "d-1", "Max Lat", "Max Rand", "Best Lat", "Best Rand", "Min Area (kGE)", "Pareto Pts", "DSE Time (s)"]

    sep = "\n" + "═" * 90 + "\n"

    lines = []
    lines.append("=" * 90)
    lines.append("  DSE EXPERIMENT RESULTS — MRLC / MLRC / MARC")
    lines.append("  Designs: Boyer-Peralta AES S-box  |  Canright AES S-box  |  SKINNY S-box")
    lines.append("  Note: Area (kGE) shown only when --with-synth was used; '—' otherwise.")
    lines.append("=" * 90)

    lines.append(sep + "  TABLE 1: MRLC  (Minimize Randomness under Latency Constraint)" + "\n")
    lines.append(_fmt(mrlc_hdrs, mrlc_rows))

    lines.append(sep + "  TABLE 2: MLRC  (Minimize Latency under Randomness Constraint)" + "\n")
    lines.append(_fmt(mlrc_hdrs, mlrc_rows))

    lines.append(sep + "  TABLE 3: MARC  (Minimize Area under Randomness and Latency Constraints)" + "\n")
    lines.append(_fmt(marc_hdrs, marc_rows))

    lines.append(sep.rstrip())

    # count coverage
    mrlc_ok = sum(1 for r in mrlc_rows if r[3] != "—")
    mlrc_ok = sum(1 for r in mlrc_rows if r[3] != "—")
    marc_ok = sum(1 for r in marc_rows if r[4] != "—")
    lines.append(f"\n  Coverage: MRLC {mrlc_ok}/{len(mrlc_rows)}  "
                 f"MLRC {mlrc_ok}/{len(mlrc_rows)}  MARC {marc_ok}/{len(marc_rows)}")

    output = "\n".join(lines)

    print(output)

    os.makedirs(os.path.dirname(os.path.abspath(output_file)), exist_ok=True)
    with open(output_file, "w") as f:
        f.write(output)
    print(f"\n  [SAVED] Tables written to: {output_file}")


# ── Main ───────────────────────────────────────────────────────────────────────

def parse_args():
    p = argparse.ArgumentParser(
        prog="run_all_experiments.py",
        description="Batch DSE runner: MRLC, MLRC, MARC on all three S-box benchmarks",
    )
    p.add_argument("--algo", choices=["mrlc", "mlrc", "marc", "all"], default="all",
                   help="Which algorithm(s) to run (default: all)")
    p.add_argument("--tables-only", action="store_true",
                   help="Skip running; only regenerate tables from cached JSON results")
    p.add_argument("--with-synth", action="store_true",
                   help="Enable Yosys synthesis (slow; required for area in kGE)")
    p.add_argument("--output", default="Results/all_results.txt",
                   metavar="FILE",
                   help="Path for the saved results table (default: Results/all_results.txt)")
    return p.parse_args()


def main():
    args  = parse_args()
    skip  = not args.with_synth
    failed: list[str] = []

    if not args.tables_only:
        t_start = time.time()
        if args.algo in ("mrlc", "all"):
            run_mrlc_all(skip, failed)
        if args.algo in ("mlrc", "all"):
            run_mlrc_all(skip, failed)
        if args.algo in ("marc", "all"):
            run_marc_all(skip, failed)
        elapsed = time.time() - t_start
        print(f"\n{'═'*70}")
        print(f"  All runs finished in {elapsed:.1f}s")
        if failed:
            print(f"  FAILED ({len(failed)}):")
            for f_ in failed:
                print(f"    ✗  {f_}")
        else:
            print("  All runs succeeded.")
        print(f"{'═'*70}")

    print("\n  Generating summary tables …")
    print_and_save_tables(args.output)


if __name__ == "__main__":
    main()
