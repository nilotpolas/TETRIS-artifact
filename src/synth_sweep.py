"""
Synthesis Sweep
===============
For every .v file in TestFiles/rtl_output/:
  1. Parses filename  →  design_name, d, target_randomness
  2. Creates output dir  Synth_result/<design_name>/d_<d>/rand_<rand>/
  3. Runs Yosys with the parameterised TCL
  4. Reads area from the resulting area.json
  5. Updates the matching row in Results/<design_name>.csv  (adds/updates 'synth_area' column)

Usage:
    python synth_sweep.py                     # synthesise everything in rtl_output/
    python synth_sweep.py --design Boyer_Peraltas_sbox        # one design only
    python synth_sweep.py --design Boyer_Peraltas_sbox --d 1  # one design, one order
"""

import argparse
import csv
import json
import os
import re
import subprocess
import sys
import tempfile

# ── paths (all relative to this script's directory) ─────────────────────────
SCRIPT_DIR   = os.path.dirname(os.path.abspath(__file__))
RTL_DIR      = os.path.join(SCRIPT_DIR, 'TestFiles', 'rtl_output')
CSV_DIR      = os.path.join(SCRIPT_DIR, 'Results')
SYNTH_DIR    = os.path.join(SCRIPT_DIR, 'Design Synthesis')
TCL_FILE     = os.path.join(SYNTH_DIR,  'synth_param.tcl')
LIB_FILE     = os.path.join(SYNTH_DIR,  'nangate45-pdk', 'stdcells.lib')
OUT_BASE_DIR = os.path.join(SCRIPT_DIR, 'Synth_result')


# ── helpers ──────────────────────────────────────────────────────────────────

def parse_rtl_filename(fname):
    """
    'Boyer_Peraltas_sbox_1_34.v'  →  ('Boyer_Peraltas_sbox', 1, 34)
    Returns None if the name does not match the expected pattern.
    """
    m = re.match(r'^(.+)_(\d+)_(\d+)\.v$', fname)
    if not m:
        return None
    return m.group(1), int(m.group(2)), int(m.group(3))


def get_top_module(v_file):
    """Extract the first module name found in the Verilog file."""
    with open(v_file) as fh:
        for line in fh:
            m = re.match(r'\s*module\s+(\w+)', line)
            if m:
                return m.group(1)
    raise ValueError(f"No 'module' declaration found in {v_file}")


def run_yosys(src_v, top_module, out_dir):
    """
    Run Yosys with synth_param.tcl.
    Returns the synthesised area (float) or None on failure.
    """
    env = os.environ.copy()
    env['SYNTH_SRC']    = src_v
    env['SYNTH_TOP']    = top_module
    env['SYNTH_RESDIR'] = out_dir
    env['SYNTH_LIB']    = LIB_FILE

    try:
        result = subprocess.run(
            ['yosys', '-c', TCL_FILE],
            capture_output=True,
            text=True,
            env=env,
        )
        if result.returncode != 0:
            print(f'    [ERROR] Yosys failed (exit {result.returncode})')
            print(result.stderr[-2000:])   # last 2 KB of stderr
            return None
    except FileNotFoundError:
        print('    [ERROR] yosys not found in PATH')
        return None

    area_json = os.path.join(out_dir, 'area.json')
    if not os.path.exists(area_json):
        print(f'    [ERROR] area.json not created at {area_json}')
        return None

    with open(area_json) as fh:
        data = json.load(fh)

    # Try module-level area first, fall back to design-level
    area = None
    modules = data.get('modules', {})
    for key, val in modules.items():
        if key.lstrip('\\') == top_module:
            area = val.get('area')
            break
    if area is None:
        area = data.get('design', {}).get('area')

    return area


def update_csv(csv_path, d, target_randomness, synth_area):
    """
    Find the row matching (d, target_randomness) in csv_path and set/update
    the 'synth_area' column.  Rewrites the file in place.
    Returns True if a matching row was found and updated.
    """
    if not os.path.exists(csv_path):
        print(f'    [WARN] CSV not found: {csv_path}')
        return False

    with open(csv_path, newline='') as fh:
        reader = csv.DictReader(fh)
        rows   = list(reader)
        fields = reader.fieldnames or []

    if 'synth_area' not in fields:
        fields = list(fields) + ['synth_area']

    updated = False
    for row in rows:
        try:
            row_d   = int(row['d'])
            row_rand = int(row['target_randomness'])
        except (KeyError, ValueError):
            continue
        if row_d == d and row_rand == target_randomness:
            row['synth_area'] = synth_area
            updated = True

    if not updated:
        print(f'    [WARN] No matching row for d={d}, target_randomness={target_randomness} in {csv_path}')
        return False

    with open(csv_path, 'w', newline='') as fh:
        writer = csv.DictWriter(fh, fieldnames=fields)
        writer.writeheader()
        writer.writerows(rows)

    return True


# ── main ─────────────────────────────────────────────────────────────────────

def main():
    parser = argparse.ArgumentParser(description='Run Yosys synthesis sweep and update CSVs.')
    parser.add_argument('--design', default=None, help='Only process this design name')
    parser.add_argument('--d',      default=None, type=int, help='Only process this masking order')
    args = parser.parse_args()

    if not os.path.isfile(TCL_FILE):
        sys.exit(f'[FATAL] TCL file not found: {TCL_FILE}')
    if not os.path.isfile(LIB_FILE):
        sys.exit(f'[FATAL] Liberty file not found: {LIB_FILE}')

    v_files = sorted(f for f in os.listdir(RTL_DIR) if f.endswith('.v'))
    if not v_files:
        sys.exit(f'[FATAL] No .v files found in {RTL_DIR}')

    os.makedirs(OUT_BASE_DIR, exist_ok=True)

    total = skipped = success = failed = 0

    for fname in v_files:
        parsed = parse_rtl_filename(fname)
        if parsed is None:
            print(f'[SKIP] Cannot parse filename: {fname}')
            skipped += 1
            continue

        design_name, d, target_randomness = parsed

        # Optional filters
        if args.design and design_name != args.design:
            skipped += 1
            continue
        if args.d is not None and d != args.d:
            skipped += 1
            continue

        total += 1
        src_v = os.path.join(RTL_DIR, fname)

        # Build output directory
        out_dir = os.path.join(OUT_BASE_DIR, design_name, f'd_{d}', f'rand_{target_randomness}')
        os.makedirs(out_dir, exist_ok=True)

        # Extract top module from the .v file
        try:
            top_module = get_top_module(src_v)
        except ValueError as e:
            print(f'[ERROR] {e}')
            failed += 1
            continue

        print(f'[SYNTH] {design_name}  d={d}  rand={target_randomness}  top={top_module}')
        print(f'        src : {src_v}')
        print(f'        out : {out_dir}')

        # Run Yosys
        area = run_yosys(src_v, top_module, out_dir)
        if area is None:
            failed += 1
            continue

        print(f'        area: {area:.4f}')

        # Update CSV  – named {design_name}_{d}.csv
        csv_path = os.path.join(CSV_DIR, f'{design_name}_{d}.csv')
        updated  = update_csv(csv_path, d, target_randomness, area)
        if updated:
            print(f'        csv : updated {csv_path}')
        success += 1

    print()
    print('=' * 60)
    print(f'Done.  total={total}  success={success}  failed={failed}  skipped={skipped}')
    print(f'Synthesis results : {OUT_BASE_DIR}')
    print(f'Updated CSVs      : {CSV_DIR}')


if __name__ == '__main__':
    main()
