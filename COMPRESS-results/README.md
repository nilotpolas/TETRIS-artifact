# TETRIS vs COMPRESS — Comparison Data

This directory contains everything needed to verify the "TETRIS vs COMPRESS" comparison in the TETRIS TCHES 2026 paper (Tables 2, 3, 4, 6, 7, 8):

1. **Cached COMPRESS results** (`compress_logs/`) — the exact per-configuration stats from the runs used to populate the paper tables.
2. **COMPRESS source code** (`compress-results/`) — the version of COMPRESS used to generate those results, minus the NanGate45 PDK (which TETRIS ships elsewhere).
3. **Provenance** (`PROVENANCE.md`) — exact commit hashes, environment, and commands.
4. **Analysis scripts** (`parse_compress_logs.py`, `compare_with_tetris.py`) — reproduce the paper's comparison tables from the cached data.

Reviewers can either work directly with the cached data (fastest path) or re-run COMPRESS from the included source (slower but fully reproducible from scratch).

## Contents

```
comparison/
├── README.md                    # This file
├── PROVENANCE.md                # COMPRESS version, commands, env details
│
├── compress_logs/               # 89 cached stats.json files + 7 summary CSVs
│   ├── aes_base__aes_bp_d2_l4.json
│   ├── aes_opt__aes_bp_d2_l6.json
│   ├── ... (89 JSON files + 7 CSVs, ~400 KB)
│
├── compress-results/             # COMPRESS source code, our version (~700 KB)
│   ├── README.md                # Upstream COMPRESS README
│   ├── LICENSE.txt              # Apache 2.0
│   ├── circuits/                # Benchmark descriptions (aes_bp.txt, skinny8.txt, etc.)
│   ├── gadget_library/          # Masked gadget Verilog + toml specs
│   ├── scripts/                 # compress.py and helpers
│   ├── synthesis/               # synth.tcl + PDK placeholder
│   ├── Makefile                 # COMPRESS's own Makefile
│   └── Makefile_artifact_top_level   # The top-level artifact Makefile
│
├── parse_compress_logs.py       # Parse cached logs into a table
└── compare_with_tetris.py       # Produce paper-format TETRIS vs COMPRESS
```

## Quick usage

### Look at COMPRESS numbers directly

```bash
python3 parse_compress_logs.py                          # everything
python3 parse_compress_logs.py --benchmark aes_bp       # only Boyer-Peralta
python3 parse_compress_logs.py --mode opt --order 1     # Opt mode, first-order
python3 parse_compress_logs.py --csv all_compress.csv   # export as CSV
```

### Compare TETRIS vs COMPRESS

Requires TETRIS results to exist under `../src/Results/`. Run TETRIS first:

```bash
cd ../src
make mrlc-synth   # or make all-synth
cd ../COMPRESS-results
```

Then:

```bash
python3 compare_with_tetris.py --benchmark aes_bp
/TETRIS-artefact/COMPRESS-results$ python compare_with_tetris.py --benchmark canright --csv table3.csv
```

Output is a table like the paper's Table 2:

```
d-1  Lat  T:RNG  T:Area  T:DSE(s)  C:Base RNG/Solve  C:Sep RNG/Solve  C:Opt RNG/Solve  Speedup vs Opt
1    4    46     -       0.063     68/    1.02      46/    1.63      46/    2.35      37.3×
1    5    37     -       0.062     37/    1.53      37/    3.99      37/    5.83      94.0×
1    6    34     -       0.063     34/    2.54      34/    8.69      34/   17.43      316.9×
...
```

The last column is the speedup TETRIS achieves over COMPRESS:Opt at the same randomness budget.

### Re-run COMPRESS from scratch (optional)

If you want to verify the cached numbers by re-running COMPRESS itself:

```bash
cd comparision
bash setup.sh # link the NanGate45 library from TETRIS
cd ..
cd compress
# 1. Set up Python 3.10 environment
python3.10 -m venv venv
source venv/bin/activate
pip install -r requirements.txt

# 2. Install / point to NanGate45 PDK
# See synthesis/README_pdk.md — TETRIS ships this same library
ln -s ../../../<path-to-tetris-nangate45> synthesis/nangate45-pdk

# 3. Set up environment variables (from PROVENANCE.md)
export yosys=/usr/bin/yosys
export iverilog=/usr/bin/iverilog

# 4. Run the make target for the mode you want
# NOTE: The top-level artifact Makefile that drives these is
# Makefile_artifact_top_level. See PROVENANCE.md for the exact
# commands used to produce the cached logs.
```

Full instructions are in `PROVENANCE.md`.

## Field mapping

COMPRESS uses `Num Shares` (2, 3, 4, 5). The TETRIS paper uses `d-1` (1, 2, 3, 4).

- COMPRESS `Num Shares` = 2 → TETRIS paper's `d-1` = 1 (first-order masking)
- COMPRESS `Num Shares` = 3 → TETRIS paper's `d-1` = 2
- etc.

This mapping is applied automatically by both scripts.

## License

COMPRESS is licensed under Apache 2.0 (see `compress_source/LICENSE.txt`).

Both the derived `stats.json` files in `compress_logs/` and the source code in `compress_source/` are redistributed here under the same terms.
