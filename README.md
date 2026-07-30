# TCHES 2026 Artifact Submission

This artifact accompanies the conditionally accepted paper:

**TETRIS: Automated Design Space Exploration of Randomness-Latency Trade-offs in Masked Hardware**
Nilotpola Sarma, Tapish Patidar, Nupur Brahamanya, Chandan Karfa
IACR Transactions on Cryptographic Hardware and Embedded Systems, Vol. 2026, Issue 4


## Scope

This artifact reproduces the MRLC (Minimize Randomness under Latency Constraint) and MLRC (Minimize Latency under Randomness Constraint) algorithms described in the paper.

The repository also contains a MARC algorithm (multi-constraint area minimization). MARC is ongoing work and **not** part of this artifact's evaluation, so it is disabled from the default reproduction flow.

## What the artifact contains

- Full implementation of the two DSE algorithms in the paper: MRLC (Algorithm 4/9) and MLRC (Algorithm 6/10).
- Complete gadget library: HPC1, HPC2, HPC3, HPC2o, HPC3o, COMAR, DOMAND.
- Implementation of the four asymmetric-gadget transforms (Algorithms 7/8 and Section 9).
- Benchmark designs used in the paper: Boyer-Peralta AES S-box, Canright AES S-box, SKINNY S-box.
- MaskedHLS integration for register balancing and Verilog RTL generation (in `src/MaskedHLS_LP/`).
- Reproduction scripts (`src/run_mrlc.py`, `src/run_mlrc.py`, `src/run_all_experiments.py`) plus a `src/Makefile`.
- Functional verification script (`run_verify.py`) that confirms C-level and RTL-level equivalence of generated designs against unmasked golden references (4096 test cases per design).
- Cached COMPRESS comparison data in `COMPRESS-results/compress_logs/` (89 stats.json files) plus the COMPRESS source code in `COMPRESS-results/compress/` for reviewers who wish to re-run the comparison from scratch.
- VERICA PINI verification logs in `verification/` for the paper's Table 9 first-order security proofs.

## Paper claims reproducible from this artifact

### Without COMPRESS comparision

| Paper element | Reproduction command | Notes |
|---|---|---|
| MRLC on Boyer-Peralta  | `make mrlc-synth` | Reports latency, randomness, area, runtime |
| MRLC on Canright  | `make mrlc-synth` | Included in same batch run |
| MRLC on SKINNY | `make mrlc-synth` | Included in same batch run |
| MLRC on Boyer-Peralta  | `make mlrc-synth` | Reports latency, randomness, area, runtime |
| MLRC on SKINNY  | `make mlrc-synth` | Included in same batch run |
| MLRC on Canright | `make mlrc-synth` | Included in same batch run |
| All MRLC + MLRC results | `make all-synth` | Runs everything; ~30-45 minutes with synthesis |
| DSE runtimes | See per-run output | Sub-second for S-box benchmarks |

## With COMPRESS comparision for MRLC (since COMPRESS is MRLC-only optimization)

Refer to COMPRESS-results/README.md and COMPRESS-results/PROVENANCE.md

## **VERICA PINI verification results (Table 9)** were produced with VERICA 3.1.0. Log files from our runs are included in `verification/`;

Our TETRIS DSE runtime numbers, area (via Yosys), latency (in cycles), and randomness (in bits) are all fully reproducible with the open-source tools listed below.

## Comparision with COMPRESS

- move to COMPRESS results : details inside COMPRESS-results/README.md
  ```
  cd COMPRESS-results
  ```

## Dependencies

### Required
- Ubuntu 22.04 LTS (tested) or macOS
- **Python 3.10 or later** (the code uses PEP 604 union syntax `X | None`)
- `pycparser`, `rustworkx`, `graphviz`, `tabulate`, `numpy`, `Pillow`, `ipython` (see `requirement.txt`)
- Graphviz (`dot`) system package
- Yosys 0.33 (for synthesis; `--skip-synth` bypasses this)
- NanGate45 open-source standard-cell library (bundled)
- GCC/CPP toolchain (for pycparser)

### Optional
- Icarus Verilog + `vvp` (for RTL simulation via `run_verify.py`)
- VERICA 3.1.0 (for PINI verification; only if reproducing Table 9)
- COMPRESS from `github.com/cassiersg/compress` (only if reproducing comparison columns)

## How to run

### Native install

```bash
git clone https://github.com/nilotpolas/TETRIS-artifact.git
cd TETRIS-artifact
cd src
python3.10 -m venv myenv
source myenv/bin/activate
pip install -r requirement.txt

# System packages needed:
# sudo apt install graphviz iverilog build-essential
# Yosys 0.33 (build from source or install matching version)
```

### Smoke test (5 minutes, no synthesis)

```bash
make mrlc
```

Expected: MRLC runs on all three benchmarks at four masking orders and three latency budgets (36 configurations) and prints a summary table to the terminal.

### Full reproduction (30-45 minutes, with synthesis)

```bash
make all-synth
```

Expected: MRLC + MLRC run on all three benchmarks with Yosys synthesis, producing area numbers alongside latency and randomness. Results in `src/Results/all_results.txt`.

### Individual experiments

Refer to the main README for per-algorithm flags and examples. Key commands:

```bash
python run_mrlc.py --design Canright_sbox.c --latency 4 --order 1
python run_mlrc.py --design Boyer_Peraltas_sbox.c --randomness 168 --order 2
```

## Functional verification

Every generated masked design can be verified against its unmasked golden reference at both C and RTL levels:

```bash
cd src
python run_verify.py --design Canright_sbox.c --latency 4 --order 1 --results-dir Results/Canright_sbox/MRLC_d1_lat4 --rtl --rtl Results/Canright_sbox/MRLC_d1_lat4/design_synth.v 
```

Expected output (verified in our tests):

```
[1/2] C-level functional equivalence
  [PASS] C-level        4096/4096 tests passed
[2/2] RTL gate-level simulation  (iverilog)
  [PASS] RTL            4096/4096 tests passed
====================================================================
  Verdict: VERIFIED
====================================================================
```

The C-level check compiles the masked C code with gcc and verifies that the XOR of all output shares matches the unmasked golden output across all 4096 test cases (256 inputs × 16 random-share trials). The RTL check uses Icarus Verilog to simulate the Yosys-synthesized netlist against the same golden reference.

## Expected outputs

Each script writes:
- Summary table to the terminal (latency, randomness, area, DSE runtime)
- Detailed JSON results to `src/Results/<design>/<ALGO>_d<d>_<constraint>/results.json`
- Generated masked C code to the same directory
- If synthesis enabled: generated Verilog RTL and synthesis logs

## Directory organization

```
TETRIS/
├── LICENSE
├── README.md                  # Main documentation (user-facing)
├── ARTIFACT.md                # This file (reviewer-facing)
├── Dockerfile                 # Reproducible environment (Option A)
├── .dockerignore
├── requirement.txt            # Python dependencies
├── Makefile                   # Batch reproduction targets
│
├── run_mrlc.py                # MRLC entry point
├── run_mlrc.py                # MLRC entry point
├── run_marc.py                # MARC entry point (not part of TCHES 2026)
├── run_all_experiments.py     # Batch runner (default scope: MRLC + MLRC)
├── run_verify.py              # Optional VERICA verification wrapper
│
├── DSE_algorithm/             # DSE core: algorithms
│   ├── dse.py                 # Base DSE class
│   ├── mrlc.py                # MRLC (Algorithm 4/9)
│   ├── mlrc.py                # MLRC (Algorithm 6/10)
│   ├── marc.py                # MARC (not in TCHES 2026 paper)
│   └── utility.py
│
├── Gadgets/                   # Gadget library
│   ├── base.py                # Gadget base class
│   ├── hpc1.py, hpc2.py, hpc3.py, hpc2o.py, hpc3o.py
│   ├── comar.py, domand.py
│   └── hpc2_swapped.py, hpc2o_swapped.py   # Asymmetric transforms
│
├── ANDCloud/                  # AST → AND-tree conversion
├── MaskedHLS_LP/              # MaskedHLS integration (register balancing + RTL)
│
├── TestFiles/C_files/         # Benchmark designs
│   ├── Boyer_Peraltas_sbox.c
│   ├── Canright_sbox.c
│   └── skinny_sbox_nor.c
│
└── Results/                   # Generated at runtime (default output directory)
├── comparision                # Required to run for linking TETRIS library to COMPRESS
│   └── setup.sh
├── COMPRESS-results           # Required to generate COMPRESS results for tables 2 and 4
│   ├── compare_with_tetris.py          # Generates tables 2 and 4
│   ├── compress
│   ├── compress_logs
│   ├── Makefile_artifact_top_level
│   ├── parse_compress_logs.py          # Parse the compress logs for tables 2 and 4
│   ├── PROVENANCE.md
│   ├── README.md
│   ├── table2.csv
│   ├── table2_run.log
│   ├── table3.csv
│   ├── table4.csv
│   ├── table4_run.log
│   └── work                   # Directory containing actual compress rtl outputs 
├── src
│   ├── ANDCloud
│   ├── asymmetric_gadget_optimization.py
│   ├── asymmetric_latency_optimizer.py
│   ├── Canright_rand_reduction
│   ├── CircuitLevelAnalysis.json
│   ├── CircuitLevelAnalysis.txt
│   ├── Design Synthesis
│   ├── DSE_algorithm
│   ├── dse_explorer.py
│   ├── DSE.ipynb
│   ├── dse_pipeline.py
│   ├── dse_run.log
│   ├── _dse_utils.py
│   ├── find_swaps.py
│   ├── from DSE_algorithm.py
│   ├── gadget_info.db
│   ├── gadget_information.db
│   ├── Gadgets
│   ├── Genric_DSE.ipynb
│   ├── hpc2_input_swap_algorithm.py
│   ├── hpc2_optimizer.py
│   ├── logs
│   ├── Makefile
│   ├── MARC_ALGORITHM.md
│   ├── MaskedHLS_LP
│   ├── MLRC.ipynb
│   ├── MLRC_Sweep.ipynb
│   ├── MRLC.ipynb
│   ├── myenv
│   ├── __pycache__
│   ├── README.md
│   ├── regenerate_output.py
│   ├── requirement.txt
│   ├── Result_mlrc.ipynb
│   ├── Results
│   ├── run_all_experiments.py
│   ├── run_marc.py
│   ├── run_mlrc.py
│   ├── run_mrlc.py
│   ├── run_verify.py
│   ├── sbox.v
│   ├── synth_sweep.py
│   ├── systemArgs.json
│   ├── TACGenerator
│   ├── test_code.out
│   ├── TestFiles
│   ├── test_hpc2_optimizer.py
│   ├── Testing
│   └── transform_CFile
└── verification            # Verfication using verica annotations files, config files and DC Synthesis scripts for each design verified
    ├── AES_BP
    ├── AES_Canrights
    └── SKINNY_NOR
```

## Mapping from paper to code

| Paper section / algorithm | Code location |
|---|---|
| Algorithm 1 (Linear Gadget) | `src/Gadgets/base.py`, linear gadget class |
| Algorithm 2 (Linear NOT Gadget) | `src/Gadgets/base.py`, NOT gadget class |
| Algorithm 3 (ReduceRandomnessWithBufferLatency) | `src/DSE_algorithm/mrlc.py::_reduce_randomness_with_buffer` |
| Algorithm 4 (MRLCWrapper) | `src/DSE_algorithm/mrlc.py::MRLC.run` |
| Algorithm 5 (referenced) | `src/DSE_algorithm/mrlc.py::MRLC._initial_assignment` |
| Algorithm 6 (MLRC) | `src/DSE_algorithm/mlrc.py::MLRC.run` |
| Algorithm 7 (Transform 1) | `src/Gadgets/hpc2_swapped.py`, integrated in `DSE_algorithm/mrlc.py` |
| Algorithm 8 (Transforms 2, 3, 4) | Same |
| Section 9 (Asymmetric Gadget Composition) | src/`asymmetric_gadget_optimization.py` |


## Runtime and hardware

Expected runtimes on Intel i7-8700 @ 3.20 GHz, 16 GB RAM (Ubuntu 22.04):

| Batch | Time | Notes |
|---|---|---|
| Single MRLC or MLRC run (no synth) | sub-second | DSE only |
| Single MRLC or MLRC run (with synth) | 1-3 minutes | Dominated by Yosys |
| `make mrlc` (36 configs, no synth) | ~15 minutes | |
| `make mlrc` (48 configs, no synth) | ~16 minutes | |
| `make all` (MRLC + MLRC, no synth) | ~30 minutes | |
| `make all-synth` (MRLC + MLRC, with synth) | ~45-60 minutes | Adds Yosys per-config |

## Contact

Any issues during evaluation, please contact:
- Nilotpola Sarma — `s.nilotpola@iitg.ac.in`
- Chandan Karfa — `ckarfa@iitg.ac.in`

We commit to responding within 24 hours during the evaluation period.

## License

MIT License. See `LICENSE` file.

Third-party components:
- MaskedHLS (in `MaskedHLS_LP/`): see `MaskedHLS_LP/LICENSE`
- NanGate45 open cell library: see the corresponding license file in the library directory
