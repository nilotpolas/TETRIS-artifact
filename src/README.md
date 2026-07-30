# DSE-Framework

**Automated Design Space Exploration for Masked Cryptographic Hardware**

This is the TETRIS DSE-Framework, it takes an unmasked S-box written in C, applies Boolean masking at a chosen security order, and produces a synthesised, verified Verilog gate-level netlist — all in a single command.

Three algorithms cover the main design trade-offs:

| Algorithm | Constraint(s) | Objective |
|-----------|--------------|-----------|
| **MRLC** | Maximum latency (cycles) | Minimise randomness (bits) |
| **MLRC** | Maximum randomness (bits) | Minimise latency (cycles) |


---

## Table of Contents

1. [How it works](#how-it-works)
2. [Prerequisites](#prerequisites)
3. [Installation](#installation)
4. [Quick start](#quick-start)
5. [Algorithm reference](#algorithm-reference)
   - [MRLC](#mrlc--minimize-randomness-under-latency-constraint)
   - [MLRC](#mlrc--minimize-latency-under-randomness-constraint)

6. [Verification](#verification)
7. [Adding your own design](#adding-your-own-design)
8. [Gadget system](#gadget-system)
9. [Output files](#output-files)
10. [Troubleshooting](#troubleshooting)

---

## How it works

```
┌─────────────────────────────────────────────────────────────────────┐
│  Input: unmasked C S-box  +  constraints  +  security order d       │
└──────────────────────────────┬──────────────────────────────────────┘
                               │
              ┌────────────────▼────────────────┐
              │  1. Preprocessing               │
              │     TAC conversion              │
              │     Function inlining           │
              │     AND-tree / AND-XOR-tree     │
              └────────────────┬────────────────┘
                               │
              ┌────────────────▼────────────────┐
              │  2. DSE algorithm               │
              │     MRLC / MLRC                │
              │     Assigns HPC gadgets to      │
              │     every AND gate              │
              └────────────────┬────────────────┘
                               │
              ┌────────────────▼────────────────┐
              │  3. Share transformation        │
              │     ShareTransformer → masked C │
              │     MaskedHLS → Verilog RTL     │
              └────────────────┬────────────────┘
                               │
              ┌────────────────▼────────────────┐
              │  4. Synthesis  (Yosys/NanGate)  │
              │     Gate-level netlist          │
              │     Area / cell / DFF counts    │
              └────────────────┬────────────────┘
                               │
              ┌────────────────▼────────────────┐
              │  5. Verification (optional)     │
              │     C-level functional check    │
              │     RTL simulation (iverilog)   │
              └─────────────────────────────────┘
```

---

## Prerequisites

### System tools

| Tool | Purpose | Install (Ubuntu/Debian) |
|------|---------|------------------------|
| Python 3.10 | Runtime | `sudo apt install python3` |
| Graphviz (`dot`) | AND-tree processing | `sudo apt install graphviz` |
| Yosys | Gate-level synthesis | `sudo apt install yosys` |
| iverilog + vvp | RTL simulation (verification) | `sudo apt install iverilog` |
| gcc / cpp | Compile C testbenches, pycparser | `sudo apt install build-essential` |

**macOS equivalents (using Homebrew):**
```bash
brew install python graphviz yosys icarus-verilog gcc
```

Verify each tool is on your PATH:
```bash
python3 --version
dot -V
yosys --version
iverilog -V
gcc --version
```

---

## Installation

```bash
# 1. Clone / download the repository
git clone <repo-url>
cd TETRIS-artifact/src

# 2. (Recommended) Create a virtual environment
python3 -m venv myenv
source myenv/bin/activate        # Linux / macOS
# myenv\Scripts\activate         # Windows

# 3. Install Python dependencies
pip install -r requirement.txt
```

No further build steps are needed — all scripts run from the repository root.

---

## Quick start

```bash
# See all available designs
python src/run_mrlc.py --list-designs

# MRLC: minimise randomness, Canright S-box, latency ≤ 4 cycles, order d=1
python src/run_mrlc.py --design Canright_sbox.c --latency 4 --order 1

# MLRC: minimise latency, Boyer-Peralta S-box, randomness ≤ 168 bits, order d=2
python src/run_mlrc.py --design Boyer_Peraltas_sbox.c --randomness 168 --order 2

```

Each command prints a summary table to the terminal and writes detailed results to
`src/Results/<design>/<ALGO>_d<d>_<constraint>/`.

---

## Batch experiments (Makefile)

`run_all_experiments.py` runs all three algorithms across all three benchmark S-boxes
(Boyer-Peralta AES, Canright AES, SKINNY) for every constraint in the thesis report tables.
Results are printed to the terminal and saved to `Results/all_results.txt`.

### Run everything

```bash
cd src            # Only inside the TETRIS source
make all          # MRLC + MLRC + MARC for all designs (synthesis skipped)
make all-synth    # same, with Yosys synthesis — adds area (kGE) to tables (slow, 30+ min)
```

### Run a single algorithm

```bash
cd src            # Only inside the TETRIS source
make mrlc         # MRLC only  (no synthesis)
make mlrc         # MLRC only  (no synthesis)

make mrlc-synth   # MRLC with Yosys synthesis
make mlrc-synth   # MLRC with synthesis
```

Or equivalently via the script directly:

```bash
python3 src/run_all_experiments.py --algo mrlc
python3 src/run_all_experiments.py --algo mlrc
```

### Regenerate tables without re-running

If results are already cached in `src/Results/`, rebuild the summary table instantly:

```bash
make tables
# or:
python3 src/run_all_experiments.py --tables-only
```

### Other targets

```bash
make src/clean-results    # delete all results.json files (keeps directory structure)
make src/help             # print target list
```

The combined summary table (`src/Results/all_results.txt`) always shows `—` for any
algorithm that has not been run yet, so you can run algorithms incrementally.

---

## Algorithm reference

### Common flags

All three scripts share these flags:

| Flag | Description | Default |
|------|-------------|---------|
| `--design FILE.c` | C source file name (from `TestFiles/C_files/`) | required |
| `--order d` | Masking security order d, 1–5 | 1 |
| `--top-module NAME` | Top C function / Verilog module name | `sbox` |
| `--use-comar` | Include COMAR gadget (d = 1 only) | off |
| `--skip-synth` | Skip Yosys gate-level synthesis | off |
| `--debug` | Verbose internal debug output to log | off |
| `--output-dir DIR` | Custom output directory | auto |
| `--list-designs` | Print available C files and exit | — |

---

### MRLC — Minimize Randomness under Latency Constraint

Given a latency budget, MRLC finds the gadget assignment that uses the fewest random bits while staying within the latency limit.

**Use when** you have a fixed clock budget (throughput requirement) and want to minimise the key-refresh rate or the size of the random number generator.

```bash
python src/run_mrlc.py --design <design>.c --latency <cycles> --order <d> [options]
```

**MRLC-specific flag:**

| Flag | Description | Default |
|------|-------------|---------|
| `--latency N` | Maximum latency in clock cycles | required |
| `--no-asym-opt` | Skip asymmetric gadget optimisation pass | off |

**Examples:**

```bash
# Canright S-box, order d=1, latency ≤ 4 cycles
python src/run_mrlc.py --design Canright_sbox.c --latency 4 --order 1

# Boyer-Peralta S-box, order d=2, latency ≤ 5 cycles
python src/run_mrlc.py --design Boyer_Peraltas_sbox.c --latency 5 --order 2

# Skinny S-box, order d=1, skip synthesis for a quick estimate
python src/run_mrlc.py --design skinny_sbox_nor.c --latency 3 --order 1 --skip-synth

# Include COMAR gadget (order d=1 only)
python src/run_mrlc.py --design Canright_sbox.c --latency 4 --order 1 --use-comar

# Save results to a custom directory
python src/run_mrlc.py --design Canright_sbox.c --latency 4 --order 1 \
    --output-dir ./my_results/canright_lat4
```

**Algorithm — 3-D Dynamic Programming:**

```
State:  dp[level][bonus_latency_spent][comar_used]  →  minimum randomness
Bonus:  B = max(0, target_latency − L × latency_HPC3)
Choice: HPC3 (free, 2 bits/node)  vs  HPC2 (costs 1 bonus cycle, 1 bit/node)
Goal:   spend bonus cycles converting HPC3 → HPC2 to save the most randomness
```

---

### MLRC — Minimize Latency under Randomness Constraint 

Given a randomness budget, MLRC finds the gadget assignment with the shortest critical path.

**Use when** fresh randomness is scarce or expensive and you want the fastest design within a fixed randomness limit.

```bash
python src/run_mlrc.py --design <design>.c --randomness <bits> --order <d> [options]
```

**MLRC-specific flag:**

| Flag | Description | Default |
|------|-------------|---------|
| `--randomness N` | Maximum randomness in bits | required |

**Examples:**

```bash
# Boyer-Peralta S-box, order d=2, randomness ≤ 168 bits
python src/run_mlrc.py --design Boyer_Peraltas_sbox.c --randomness 168 --order 2

# Canright S-box, order d=1, randomness ≤ 102 bits
python src/run_mlrc.py --design Canright_sbox.c --randomness 102 --order 1

# Skinny S-box, order d=1, skip synthesis
python src/run_mlrc.py --design skinny_sbox_nor.c --randomness 80 --order 1 --skip-synth
```

---

## Generate Tables 6,7,8
```bash
make mlrc-synth
```

---

## Verification

After running any algorithm, verify the generated design in two stages:

```bash
python src/run_verify.py [options]
```

**Option 1 — point directly to the files:**

```bash
python src/run_verify.py \
    --design Canright_sbox.c \
    --masked-c src/Results/Canright_sbox/MRLC_d1_lat4/masked_output.c \
    --rtl      src/Results/Canright_sbox/MRLC_d1_lat4/design_synth.v \
    --order 1
```

**Option 2 — use the results directory shortcut:**

```bash
# Verifies MRLC result
python run_verify.py \
    --design Canright_sbox.c \
    --order 1 \
    --results-dir Results/Canright_sbox/MRLC_d1_lat4

# Verifies MARC result
python run_verify.py \
    --design Boyer_Peraltas_sbox.c \
    --order 1 \
    --results-dir Results/Boyer_Peraltas_sbox/MARC_d1_lat6_rand120
```

**Verification flags:**

| Flag | Description |
|------|-------------|
| `--design FILE.c` | Original (golden) C source |
| `--masked-c FILE` | Masked C output from DSE run |
| `--rtl FILE` | Yosys gate-level Verilog netlist |
| `--results-dir DIR` | Auto-locate `masked_output.c` and `design_synth.v` |
| `--order d` | Security order used during DSE |
| `--dec1 0\|1` | Override `dec_1` parameter (auto-detected by default) |

**What gets checked:**

| Stage | Tool | Test |
|-------|------|------|
| C-level | gcc | 256 × 16 = 4 096 input cases; XOR of all output shares == golden output |
| RTL-level | iverilog/vvp | Gate-level simulation for every input; output bits match golden LUT |

---

## Adding your own design

1. **Write your S-box in C** — use only bitwise operators:

   ```c
   // File: src/TestFiles/C_files/my_sbox.c
   // Function name must match --top-module (default: sbox)
   unsigned char sbox(unsigned char x) {
       unsigned char a = (x >> 7) & 1;
       unsigned char b = (x >> 6) & 1;
       // ... combinational logic with & ^ ~ ! only ...
       return result;
   }
   ```

2. **Copy it into the designs directory:**

   ```bash
   cp my_sbox.c TestFiles/C_files/
   ```

3. **Run an algorithm:**

   ```bash
   python run_mrlc.py --design my_sbox.c --latency 5 --order 1
   ```

**C source requirements:**
- Single top-level function matching `--top-module`
- Only bitwise operations: `&`, `^`, `~`, `!`
- Scalar `unsigned char` / `_Bool` inputs and outputs
- No arrays, no loops, no stdlib calls, no external functions

*Important* If your function has a `dec_1` parameter, the framework detects and handles it automatically.

---

## Gadgets Library

Masked AND gadgets from the HPC family are stored in `gadget_info.db` (SQLite).  Each gadget has a `(latency, randomness, area)` triple for every security order.

### Properties at security order d = 1

| Gadget | Latency | Randomness | Area (GE) | Notes |
|--------|---------|------------|-----------|-------|
| HPC3 | 1 cycle | 2 bits/gate | 4.0 | Baseline — minimum latency |
| HPC1 | 2 cycles | 2 bits/gate | 3.0 | Lower area, higher latency |
| HPC2 | 2 cycles | 1 bit/gate | 5.0 | Saves 1 bit vs HPC3, costs 1 cycle |
| HPC2o | 2 cycles | 1 bit/gate | 5.0 | HPC2 optimised for AND→XOR fan-out |
| HPC3o | 1 cycle | 2 bits/gate | 6.0 | HPC3 optimised for AND→XOR fan-out |
| HPC2\_swapped | 2 cycles | 1 bit/gate | 5.0 | HPC2 with operand swap (asymmetric depths) |
| HPC2o\_swapped | 2 cycles | 1 bit/gate | 5.0 | HPC2o with operand swap |
| COMAR | 2 cycles | 6 bits\* | 7.0 | Shared randomness; d = 1 only |

\* COMAR's 6 random bits are **shared** across all COMAR instances in the design — counted only once regardless of how many AND gates use it.

### COMAR

COMAR is a special gadget available only at d = 1.  Enable it with `--use-comar`:

```bash
python run_mrlc.py --design Canright_sbox.c --latency 4 --order 1 --use-comar
```

### Security orders

All HPC-family gadgets scale to orders d = 1–5.  Randomness and area increase with d.

```bash
# 2 shares (d=1)
python run_mrlc.py --design Canright_sbox.c --latency 4 --order 1

# 3 shares (d=2)
python run_mrlc.py --design Canright_sbox.c --latency 4 --order 2

# 4 shares (d=3)
python run_mrlc.py --design Canright_sbox.c --latency 4 --order 3
```

---

## Output files

Every run writes its results to:

```
src/Results/<design_name>/<ALGO>_d<d>_<constraint>/
```

For example:
```
src/Results/Canright_sbox/MRLC_d1_lat4/
    masked_output.c     ← masked C (used by run_verify.py)
    design_synth.v      ← Yosys gate-level Verilog netlist
    area.json           ← raw synthesis area breakdown
    results.json        ← complete run summary
```

### results.json structure

```json
{
  "algorithm":            "MRLC",
  "design":               "Canright_sbox",
  "security_order_d":     1,
  "latency_budget":       4,
  "achieved_randomness":  34,
  "achieved_latency":     4,
  "hls_verified_latency": 4,
  "synthesis": {
    "area_ge":    142.3,
    "cell_count": 210,
    "dff_count":  34
  },
  "gadget_distribution": {
    "hpc3": 12,
    "hpc2": 6
  },
  "wall_time_sec": 8.4
}
```



**Log file:** `dse_run.log` in the repository root contains all verbose algorithm output.  Only the final summary table is shown in the terminal.

---

## Troubleshooting

**`ModuleNotFoundError: No module named 'pycparser'` (or similar)**
```bash
pip install -r requirement.txt
```

**`Design file not found`**
```bash
python run_mrlc.py --list-designs    # see all available file names
```

**Yosys synthesis fails**
Check `dse_run.log` for the full Yosys output.  Confirm Yosys is installed and on PATH:
```bash
yosys --version
```

**RTL verification fails** — ensure iverilog is installed:
```bash
iverilog -V
vvp -V
```

**`COMAR is only available for d <= 1`**
Remove `--use-comar` or set `--order 1`.


**Custom top-level function name**
If your function is not named `sbox`, pass `--top-module`:
```bash
python run_mrlc.py --design present.c --top-module present --latency 5 --order 1
```

**Design produces wrong verification results**
The `dec_1` parameter is auto-detected from the masked C body.  If detection fails, override it manually:
```bash
python run_verify.py --design Canright_sbox.c --order 1 \
    --results-dir Results/Canright_sbox/MRLC_d1_lat4 --dec1 1
```
