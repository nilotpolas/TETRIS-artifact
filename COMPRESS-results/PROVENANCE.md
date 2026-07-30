# COMPRESS Comparison — Provenance

This document records the exact version, environment, and commands used to produce the cached COMPRESS results in `compress_logs/`. Following these steps against the code in `compress_source/` (plus a NanGate45 PDK) should reproduce the same numbers.

## Versions

| Component | Version / commit |
|---|---|
| COMPRESS tool | `github.com/cassiersg/compress` @ `8c0a6ae4a5ce4de25198c0bbcf93b8651f4a36e8` |
| COMPRESS artifact | `github.com/cassiersg/compress_artifact` @ `a2da3e50c4cfd01d77f0b696730a2cf3986ac8f1` |
| Python | 3.10 |
| Yosys | 0.33 |
| Icarus Verilog | 11.0 |
| Cell library | NanGate 45 nm open-source PDK |
| SAT solver  (bundled with COMPRESS's deps) |

Same versions as those used for the TETRIS numbers in the paper.

## Benchmarks

Three S-box benchmarks, matching those used for TETRIS:

| Benchmark | Input file | COMPRESS artifact dirs producing results |
|---|---|---|
| Boyer-Peralta AES S-box | `compress/circuits/aes_bp.txt` | `aes_base/`, `aes_sep/`, `aes_opt/` |
| Canright AES S-box | (Canright variant) | `canright_aes_sbox_opt/` |
| SKINNY S-box | `compress/circuits/skinny8.txt` | `skinny_base/`, `skinny_sep/`, `skinny_opt/` |

## COMPRESS modes

- **Base**: straightforward COMPRESS output using `gadget_library/gadgets_base.toml`
- **Sep**: with sep heuristics, `gadgets_sep.toml`
- **Opt**: fully optimized, `gadgets_opt.toml` — the strongest baseline TETRIS is compared against

The three `.toml` files that define each mode are in `compress/gadget_library/`.

## File naming in `compress_logs/`

Each `.json` file follows the pattern:

```
<mode>__<benchmark>_d<num_shares>_l<latency>.json
```

Examples:
- `aes_base__aes_bp_d2_l4.json` — Boyer-Peralta, 2 shares (d-1=1), latency 4, Base mode
- `aes_opt__aes_bp_d5_l6.json` — Boyer-Peralta, 5 shares (d-1=4), latency 6, Opt mode
- `canright_aes_sbox_opt__canright_d3_l5.json` — Canright, 3 shares, latency 5, Opt mode

**Note :** COMPRESS uses `d` for number of shares. TETRIS paper uses `d-1` for masking order. So COMPRESS's `d=2` = TETRIS's `d-1=1` (first order), COMPRESS's `d=5` = TETRIS's `d-1=4` (fourth order).

## Stats.json fields

Each JSON file has these fields (relevant subset):

| Field | Meaning |
|---|---|
| `Num Shares` | Number of shares (COMPRESS `d`) — TETRIS's `d-1` = this minus 1 |
| `Latency` | Cycles from primary inputs to primary outputs |
| `RNG Bits` | Total fresh randomness required (bits) |
| `Area Estimate (GE)` | Total area in Gate Equivalents, NanGate45 |
| `solve_time` | Wall-clock time COMPRESS's CP-SAT solver took (seconds) |
| `MSKand_hpc2`, `MSKand_hpc3`, ... | Gadget-instance counts (breakdown) |

## Commands used to generate these logs

The following sequence produced the cached results. Following these steps against `compress_source/` should reproduce the same numbers (modulo minor wall-clock timing variation).

```bash
# 1. Clone (or use the bundled compress/ directly)
git clone --recursive https://github.com/cassiersg/compress_artifact
cd compress_artifact
git checkout a2da3e50c4cfd01d77f0b696730a2cf3986ac8f1
```

# 2. Verify the submodule commit
```
git submodule status
#  8c0a6ae4a5ce4de25198c0bbcf93b8651f4a36e8 compress (8c0a6ae)
```

# 3. Set up dependencies
```
python3.10 -m venv venv
source venv/bin/activate
pip install -r compress/requirements.txt
```

# 3. Environment variables (adjust paths for your system)
```
export yosys=/usr/bin/yosys
export iverilog=/usr/bin/iverilog
```

# 4. Run the make targets
```
# The top-level Makefile at compress_artifact/Makefile drives everything.
# For the three modes on Boyer-Peralta AES:
make aes_base_all
make aes_sep_all
make aes_opt_all

# For Canright:
make canright_aes_sbox_opt_all

# For SKINNY:
make skinny_base_all
make skinny_sep_all
make skinny_opt_all
```

Results appear under `work/<mode>/circuits/<config>/stats.json`. These are the same files copied into `compress_logs/` (renamed to embed mode + benchmark + config in the filename).


## License

COMPRESS is Apache 2.0. See `compress_source/LICENSE.txt` for the full license text.

Both the cached JSON files in `compress_logs/` and the source code in `compress_source/` are redistributed under Apache 2.0.
