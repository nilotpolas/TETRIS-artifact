# MARC — Minimize Area under Randomness and latency Constraints

## Overview

MARC is the third DSE algorithm in this framework, complementing MRLC and MLRC.
Where MRLC minimises randomness given a latency budget and MLRC minimises latency given
a randomness budget, **MARC minimises silicon area while satisfying both a latency ceiling
and a randomness ceiling simultaneously**.

```
Inputs : design (C), security order d, max_latency L*, max_randomness R*
Output : optimal gadget assignment (min area), Pareto frontier across the feasible space
```

---

## Motivation

Choosing gadgets for masked hardware involves three conflicting objectives:

| Gadget | Latency | Randomness | Area |
|--------|---------|------------|------|
| HPC3   |   low   |    high    |  low |
| HPC2   |  high   |    low     | high |
| HPC1   | higher  |    higher  |  low |

MRLC and MLRC each optimise one objective while constraining the other.
MARC enables area-optimal design when both latency **and** randomness are bounded — the
typical constraint regime for hardware implementations that must fit within an area budget
(e.g., IoT chips) while meeting a given throughput and key-refresh rate.

---

## Algorithm

### Formal problem statement

```
minimise   ∑_{v ∈ AND-nodes} area(gadget(v))
subject to total_latency(assignment)    ≤ L*
           total_randomness(assignment) ≤ R*
```

### High-level steps

```
1. Pattern analysis   — detect AND→XOR fan-out patterns for hpc2o/hpc3o eligibility
2. Gadget setup       — select minimum-latency baseline gadget; compute bonus budget B
3. 4-D DP             — explore all (latency, randomness, area) combinations in the box
4. Pareto extraction  — collect all non-dominated (latency, randomness, area) triples
5. Best design        — pick the minimum-area feasible point
6. Reconstruction     — backtrack to recover per-level gadget choice, then assign per node
7. HLS + Synthesis    — generate Verilog RTL and gate-level netlist
```

---

## Dynamic Programming

### State

```
dp[i][j][r][k]  =  minimum area (liberty units)
                   achieved for the first i AND-only levels
                   having spent j bonus-latency units
                   having consumed r total randomness bits
                   with COMAR-used flag k ∈ {0, 1}
```

Dimensions:
- `i` ∈ `{0, …, L}` — AND-only level index (L = number of AND levels in the circuit)
- `j` ∈ `{0, …, B}` — bonus latency spent; B = max(0, L* − L·lat_min)
- `r` ∈ `{0, …, R*}` — cumulative randomness consumed
- `k` ∈ `{0, 1}` — COMAR has been used at least once

### Transition

For level `i` with `n_i` AND nodes, choosing gadget `g`:

```
j_new = j + (latency(g) − latency_min)     # per-level cost
r_new = r + n_i × randomness(g)            # per-node cost  (COMAR: +6 first time, 0 thereafter)
a_new = dp[i−1][j][r][k] + n_i × area(g)  # per-node cost

if j_new ≤ B  and  r_new ≤ R*:
    dp[i][j_new][r_new][k_new] = min(dp[i][j_new][r_new][k_new], a_new)
```

All nodes within a level are assigned the same gadget type (they execute in parallel,
so the level latency equals the chosen gadget's latency).

### Base case

```
dp[0][0][0][0] = 0
all other dp[0][*][*][*] = ∞
```

### Complexity

| Dimension | Size   |
|-----------|--------|
| Levels L  | ~5–20  |
| Bonus B   | ~0–10  |
| Randomness R* | user-defined (typically 50–300) |
| COMAR k   | 2      |

Total DP states: O(L · B · R* · 2) — typically 10,000–100,000 entries.
Time: O(L · B · R* · |gadgets|) — sub-second for all practical circuits.

---

## Pareto Frontier

After the DP, MARC scans all final states `dp[L][j][r][k]` and collects every finite
(total\_latency, randomness, area) triple.  It then computes the **Pareto-optimal subset**:
a point is Pareto-optimal if no other feasible point is better in all three objectives.

This frontier is useful for design trade-off analysis:
- A designer who prioritises area picks the leftmost Pareto point.
- A designer who prioritises randomness picks the topmost point.
- The `--show-pareto` flag in `run_marc.py` displays the full table.

---

## Relationship to MRLC and MLRC

| Property              | MRLC                       | MLRC                       | MARC                            |
|-----------------------|----------------------------|----------------------------|---------------------------------|
| Constraint            | latency budget             | randomness budget          | latency **and** randomness      |
| Objective             | minimise randomness        | minimise latency           | minimise area                   |
| DP dimensionality     | 3-D (level × bonus × COMAR)| N/A (greedy)               | 4-D (level × bonus × rand × COMAR) |
| Pareto frontier       | no                         | no                         | yes                             |
| File                  | `DSE_algorithm/mrlc.py`    | `DSE_algorithm/mlrc.py`    | `DSE_algorithm/marc.py`         |
| CLI                   | `run_mrlc.py`              | `run_mlrc.py`              | `run_marc.py`                   |

MARC inherits the pattern-analysis helpers, gadget-setup, node-assignment, and
gadget-definition-generation code from MRLC.  Only the DP, Pareto extraction, and
best-design selection are new.

---

## CLI Usage

```bash
# Minimum-area design with both constraints
python run_marc.py \
    --design Boyer_Peraltas_sbox.c \
    --max-latency 6 \
    --max-randomness 120 \
    --order 1

# Include COMAR gadget, display Pareto frontier, skip synthesis
python run_marc.py \
    --design Canright_sbox.c \
    --max-latency 5 \
    --max-randomness 80 \
    --order 1 \
    --use-comar \
    --show-pareto \
    --skip-synth

# List available designs
python run_marc.py --list-designs
```

### Options

| Flag              | Description                                        | Default  |
|-------------------|----------------------------------------------------|----------|
| `--design`        | C source file (name only, from `TestFiles/C_files/`) | required |
| `--max-latency`   | Latency ceiling in clock cycles                    | required |
| `--max-randomness`| Randomness ceiling in bits                         | required |
| `--order`         | Security order d (1–5)                             | 1        |
| `--top-module`    | Top C function / Verilog module name               | `sbox`   |
| `--use-comar`     | Include COMAR gadget (d=1 only)                    | off      |
| `--skip-synth`    | Skip Yosys gate-level synthesis                    | off      |
| `--show-pareto`   | Display full Pareto frontier table                 | off      |
| `--debug`         | Verbose DP output to log                           | off      |
| `--output-dir`    | Custom directory for result files                  | auto     |

### Output files

```
Results/<design>/MARC_d<d>_lat<L>_rand<R>/
    masked_output.c    — masked C code (input to run_verify.py)
    design_synth.v     — Yosys gate-level netlist
    area.json          — synthesis area breakdown
    results.json       — complete JSON summary including Pareto frontier
```

---

## Gadget Database

Gadget properties are stored in `gadget_info.db` (SQLite).  For each security order `d`,
every gadget has a `(latency, randomness, area)` triple.  Example values for d=1:

| Gadget       | Latency | Randomness | Area (lib) |
|--------------|---------|------------|------------|
| HPC1         |    2    |     2      |    3.0     |
| HPC2         |    2    |     1      |    5.0     |
| HPC3         |    1    |     2      |    4.0     |
| HPC2o        |    2    |     1      |    5.0     |
| HPC3o        |    1    |     2      |    6.0     |
| COMAR        |    2    |     6*     |    7.0     |

\* COMAR's 6 random bits are shared across all instances; counted only once per design.

---

## Implementation Notes

### COMAR handling
COMAR uses 6 bits of shared randomness.  The DP tracks a binary COMAR-used flag `k`.
The first time a level is assigned COMAR, `r` increases by 6; subsequent COMAR levels
add 0 randomness.  This correctly models the shared-randomness property.

### Pattern-aware gadget selection
AND nodes whose single fan-out is a XOR node (the "xor\_and" pattern) are eligible for
the `hpc2o` / `hpc3o` optimised gadgets.  MARC detects these patterns from the AND-XOR
dependency graph (same as MRLC) and restricts the DP to legal gadgets per level.

### Post-DP asymmetric optimisation pass
After the 4-D DP selects the minimum-area gadget assignment, MARC runs the same four
asymmetric gadget transforms (T1–T4) that MRLC uses as a post-processing step.  The
transforms operate on the already-chosen assignment and can reduce achieved latency and/or
randomness by eliminating redundant balancing registers.  This directly lowers the total
effective area (fewer registers, and — if the `GC + R × rand_cost` metric is used — also
fewer random bits).  The transforms do not re-run the DP; they refine the result after the
fact, which is correct because the transforms are structural and independent of the DP
objective.
