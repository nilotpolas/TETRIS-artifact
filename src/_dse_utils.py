"""
_dse_utils.py — Shared utilities for DSE-Framework CLI scripts (run_mrlc.py / run_mlrc.py).
Not meant to be invoked directly.
"""

import contextlib
import json
import os
import sqlite3
import subprocess
import sys
import time

# ── Real stdout/stderr saved at import time ───────────────────────────────────
# All display helpers write to these references so they always reach the
# terminal even when sys.stdout has been redirected to the log file.
_STDOUT = sys.stdout
_STDERR = sys.stderr

# ── ANSI colours ─────────────────────────────────────────────────────────────
_USE_COLOUR = _STDOUT.isatty()

def _c(text, code):
    return f"\033[{code}m{text}\033[0m" if _USE_COLOUR else text

def green(t):   return _c(t, "32")
def yellow(t):  return _c(t, "33")
def cyan(t):    return _c(t, "36")
def bold(t):    return _c(t, "1")
def red(t):     return _c(t, "31")
def dim(t):     return _c(t, "2")

# ── Paths (all relative to the script's own directory) ───────────────────────
FRAMEWORK_DIR = os.path.dirname(os.path.abspath(__file__))
C_FILES_DIR   = os.path.join(FRAMEWORK_DIR, "TestFiles", "C_files")
TAC_DIR       = os.path.join(FRAMEWORK_DIR, "TestFiles", "TAC_files")
INLINED_DIR   = os.path.join(FRAMEWORK_DIR, "TestFiles", "inlined_output")
SHARE_DIR     = os.path.join(FRAMEWORK_DIR, "TestFiles", "share_output")
GADGET_DB     = os.path.join(FRAMEWORK_DIR, "gadget_info.db")
SYNTH_TCL     = os.path.join(FRAMEWORK_DIR, "Design Synthesis", "synth_param.tcl")
LIB_FILE      = os.path.join(FRAMEWORK_DIR, "Design Synthesis", "nangate45-pdk", "stdcells.lib")
MASKEDHLS_SRC = os.path.join(FRAMEWORK_DIR, "MaskedHLS_LP", "src")
RESULTS_DIR   = os.path.join(FRAMEWORK_DIR, "Results")
LOG_FILE      = os.path.join(FRAMEWORK_DIR, "dse_run.log")


# ── Log file management ───────────────────────────────────────────────────────
def init_log(algorithm, design, constraint_label, constraint_val, d):
    """Truncate the log file and write a run header. Call once per script run."""
    with open(LOG_FILE, "w") as f:
        f.write("=" * 80 + "\n")
        f.write(f"DSE RUN LOG\n")
        f.write(f"Algorithm  : {algorithm}\n")
        f.write(f"Design     : {design}\n")
        f.write(f"Order      : d = {d}\n")
        f.write(f"{constraint_label}: {constraint_val}\n")
        f.write(f"Timestamp  : {time.strftime('%Y-%m-%d %H:%M:%S')}\n")
        f.write("=" * 80 + "\n\n")


def log(msg):
    """Append a plain message to the log file."""
    with open(LOG_FILE, "a") as f:
        f.write(msg + "\n")


@contextlib.contextmanager
def capture():
    """Redirect sys.stdout and sys.stderr to the log file for noisy calls."""
    with open(LOG_FILE, "a") as lf:
        old_out, old_err = sys.stdout, sys.stderr
        sys.stdout = lf
        sys.stderr = lf
        try:
            yield
        finally:
            sys.stdout = old_out
            sys.stderr = old_err


# ── Terminal display helpers (always use saved _STDOUT) ───────────────────────
def step(n, total, label):
    print(f"\n{dim(f'[{n}/{total}]')} {bold(label)}", file=_STDOUT)


def ok(msg):
    print(f"  {green('+')} {msg}", file=_STDOUT)


def warn(msg):
    print(f"  {yellow('!')} {msg}", file=_STDOUT)


def err(msg):
    print(f"  {red('x')} {msg}", file=_STDOUT)


# ── List available C designs ─────────────────────────────────────────────────
def list_designs():
    files = sorted(f for f in os.listdir(C_FILES_DIR) if f.endswith(".c"))
    print(bold("\nAvailable designs in TestFiles/C_files/\n"), file=_STDOUT)
    for f in files:
        path = os.path.join(C_FILES_DIR, f)
        size = os.path.getsize(path)
        print(f"  {cyan(f):<45} {dim(str(size) + ' bytes')}", file=_STDOUT)
    print(file=_STDOUT)


# ── Gadget database ───────────────────────────────────────────────────────────
# HPC-family gadgets available at each security order (COMAR excluded here;
# added separately when the user explicitly requests it via --use-comar).
_HPC_GADGETS = {
    1: ["hpc1", "hpc2", "hpc3", "hpc2o", "hpc3o", "hpc2_swapped", "hpc2o_swapped"],
    2: ["hpc1", "hpc2", "hpc3", "hpc2o", "hpc3o", "hpc2_swapped", "hpc2o_swapped"],
    3: ["hpc1", "hpc2", "hpc3", "hpc2o", "hpc3o", "hpc2_swapped", "hpc2o_swapped"],
    4: ["hpc1", "hpc2", "hpc3", "hpc2o", "hpc3o", "hpc2_swapped", "hpc2o_swapped"],
    5: ["hpc1", "hpc2", "hpc3", "hpc2o", "hpc3o", "hpc2_swapped", "hpc2o_swapped"],
}
# COMAR is only present in the DB for d=1
_COMAR_MAX_ORDER = 1


def load_gadget_specs(d, use_comar=False):
    gadget_list = list(_HPC_GADGETS.get(d, []))
    if use_comar:
        if d <= _COMAR_MAX_ORDER:
            gadget_list.append("comar")
        else:
            warn(f"COMAR is only available for d <= {_COMAR_MAX_ORDER}; ignoring --use-comar for d={d}")

    conn = sqlite3.connect(GADGET_DB)
    cur  = conn.cursor()
    specs = {}
    for gadget in gadget_list:
        cur.execute(f"SELECT * FROM {gadget} WHERE d = ?", (d,))
        row = cur.fetchone()
        if row:
            specs[gadget] = {"latency": row[1], "randomness": row[2], "area": row[3]}
        else:
            warn(f"No DB entry for {gadget} at d={d}")
    conn.close()
    return specs


# ── Print gadget table ────────────────────────────────────────────────────────
def print_gadget_table(specs, d):
    from tabulate import tabulate
    rows = [[g, v["latency"], v["randomness"], v["area"]] for g, v in specs.items()]
    print(f"\n  {bold('Gadget specs for d=' + str(d))}", file=_STDOUT)
    table = tabulate(rows, headers=["Gadget", "Latency", "Randomness", "Area"], tablefmt="simple")
    print("  " + table.replace("\n", "\n  "), file=_STDOUT)


# ── TAC + Inliner + AND trees ─────────────────────────────────────────────────
def run_preprocessing(c_file_path, top_module="sbox"):
    """Run TAC conversion, inlining, and AND/AND-XOR tree generation."""
    import dse_pipeline
    from dse_pipeline import convert_to_TAC, run_inliner, generator_and_cloud, generator_and_xor_cloud

    t0 = time.time()
    with capture():
        convert_to_TAC(c_file_path)
    ok(f"TAC conversion  ({time.time()-t0:.2f}s)")

    t0 = time.time()
    tac_file = os.path.join(TAC_DIR, "output.c")
    with capture():
        run_inliner(tac_file, top_module)
    ok(f"Inlining        ({time.time()-t0:.2f}s)")

    inlined_file = os.path.join(INLINED_DIR, "output.c")

    t0 = time.time()
    with capture():
        and_tree = generator_and_cloud(inlined_file)
    ok(f"AND tree        ({time.time()-t0:.2f}s)  —  {and_tree.graph.num_nodes()} nodes")

    t0 = time.time()
    with capture():
        and_xor_tree = generator_and_xor_cloud(inlined_file)
    ok(f"AND-XOR tree    ({time.time()-t0:.2f}s)")

    return and_tree, and_xor_tree


# ── Circuit transformation + MaskedHLS ───────────────────────────────────────
def run_circuit_transform(dse_obj):
    """
    ShareTransformer → write share_output/output.c.
    Returns the path to the generated masked C file.
    This is the last step of DSE (before MaskedHLS).
    """
    from pycparser import parse_file, c_generator
    import transform_CFile.ctransfromer
    import importlib
    with capture():
        importlib.reload(transform_CFile.ctransfromer)
    from transform_CFile.ctransfromer import ShareTransformer

    d = dse_obj.d

    with capture():
        gadget_map     = dse_obj.get_gadget_definition()
        unique_def_map = dse_obj.get_unique_gadgets_definition()

    inlined_file = os.path.join(INLINED_DIR, "output.c")
    with capture():
        ast = parse_file(inlined_file)

    with capture():
        transformer     = ShareTransformer(d + 1, gadget_map, unique_def_map)
        transformed_ast = transformer.transform(ast)

    gen = c_generator.CGenerator()
    os.makedirs(SHARE_DIR, exist_ok=True)
    share_out = os.path.join(SHARE_DIR, "output.c")

    with open(share_out, "w") as f:
        f.write("// === GADGET DEFINITIONS ===\n")
        for name, code in unique_def_map.items():
            f.write(f"\n// --- {name} ---\n{code}\n\n")
        f.write("\n// === TRANSFORMED CIRCUIT ===\n")
        with capture():
            f.write(gen.visit(transformed_ast))

    ok("Share output written  →  TestFiles/share_output/output.c")
    return share_out


def run_maskedhls(share_out, top_module="sbox", rtl_filename="output.v"):
    """
    Run MaskedHLS on the already-generated masked C file.
    Returns (hls_latency, rtl_abs_path).
    """
    from dse_pipeline import run_maskedHLS

    t0 = time.time()
    with capture():
        hls_result = run_maskedHLS(
            top_module=top_module, input_file=share_out,
            rtl_file=rtl_filename, bit_width=1
        )
    hls_latency, _ = hls_result if isinstance(hls_result, tuple) else (hls_result, "")
    ok(f"MaskedHLS               ({time.time()-t0:.2f}s)  —  latency = {hls_latency} cycles")

    rtl_abs = os.path.join(MASKEDHLS_SRC, rtl_filename)
    return hls_latency, rtl_abs


def run_circuit_transform_and_hls(dse_obj, top_module="sbox", rtl_filename="output.v"):
    """
    Convenience wrapper: ShareTransformer → masked C → MaskedHLS.
    Returns (hls_latency, rtl_abs_path).
    """
    share_out = run_circuit_transform(dse_obj)
    return run_maskedhls(share_out, top_module=top_module, rtl_filename=rtl_filename)


# ── Yosys synthesis ───────────────────────────────────────────────────────────
def run_yosys_synthesis(rtl_path, top_module, out_dir):
    """
    Run Yosys using synth_param.tcl.
    Returns (area_float, cell_count, dff_count) or (None, None, None) on failure.
    """
    if not os.path.isfile(rtl_path):
        err(f"RTL file not found: {rtl_path}")
        return None, None, None
    if not os.path.isfile(SYNTH_TCL):
        err(f"synth_param.tcl not found: {SYNTH_TCL}")
        return None, None, None
    if not os.path.isfile(LIB_FILE):
        err(f"Liberty file not found: {LIB_FILE}")
        return None, None, None

    os.makedirs(out_dir, exist_ok=True)
    env = os.environ.copy()
    env["SYNTH_SRC"]    = rtl_path
    env["SYNTH_TOP"]    = top_module
    env["SYNTH_RESDIR"] = out_dir
    env["SYNTH_LIB"]    = LIB_FILE

    t0 = time.time()
    result = subprocess.run(
        ["yosys", "-c", SYNTH_TCL],
        capture_output=True, text=True, env=env
    )
    elapsed = time.time() - t0

    # always dump yosys output to the log
    log("\n--- Yosys stdout ---\n" + result.stdout)
    if result.stderr.strip():
        log("\n--- Yosys stderr ---\n" + result.stderr)

    if result.returncode != 0:
        err(f"Yosys failed (exit {result.returncode})  —  see {LOG_FILE}")
        return None, None, None

    area_json = os.path.join(out_dir, "area.json")
    if not os.path.exists(area_json):
        err("area.json not produced by Yosys")
        return None, None, None

    with open(area_json) as f:
        data = json.load(f)

    module_key = f"\\{top_module}"
    stats       = data.get("modules", {}).get(module_key) or data.get("design", {})
    area        = stats.get("area")
    cell_count  = stats.get("num_cells")
    dff_count   = stats.get("num_cells_by_type", {}).get("DFF_X1", 0)

    ok(f"Yosys synthesis  ({elapsed:.1f}s)  —  area = {area:.2f} GE,  cells = {cell_count},  DFFs = {dff_count}")
    return area, cell_count, dff_count


# ── Nangate 45nm area constants (from stdcells.lib) ──────────────────────────
_NAND2_AREA = 0.798   # um^2  →  1 GE reference
_DFF_AREA   = 4.522   # um^2 per DFF_X1


def area_to_kge(yosys_area):
    """Convert Yosys GE area to kGE."""
    if yosys_area is None:
        return None
    return yosys_area / 1000.0


def area_wo_rand_kge(yosys_area, randomness_bits):
    """
    kGE after subtracting the registers used to store fresh random bits.
    Each random bit occupies one DFF_X1.
    """
    if yosys_area is None:
        return None
    rand_area   = randomness_bits * _DFF_AREA
    net_area    = max(0.0, yosys_area - rand_area)
    return (net_area / _NAND2_AREA) / 1000.0


# ── Randomness calculation (COMAR-aware) ─────────────────────────────────────
def compute_total_randomness(gadget_definition, gadget_specs):
    """
    Sum randomness across all gadget instances, but count COMAR only once
    because all COMAR instances in a design share the same 6 random bits.
    """
    comar_used = any(
        info["gadget_name"].lower() == "comar"
        for info in gadget_definition.values()
        if isinstance(info, dict) and "gadget_name" in info
    )
    total = sum(
        gadget_specs.get(info["gadget_name"], {}).get("randomness", 0)
        for info in gadget_definition.values()
        if isinstance(info, dict) and "gadget_name" in info
        and info["gadget_name"].lower() != "comar"
    )
    if comar_used:
        total += gadget_specs.get("comar", {}).get("randomness", 6)
    return total


# ── Gadget distribution summary ───────────────────────────────────────────────
def gadget_distribution(dse_obj):
    gdef = dse_obj.get_gadget_definition()
    counts = {}
    for info in gdef.values():
        g = info["gadget_name"]
        counts[g] = counts.get(g, 0) + 1
    return counts


# ── Print final results ───────────────────────────────────────────────────────
def print_results(
    algorithm, design_name, d, constraint_label, constraint_val,
    achieved_randomness, achieved_latency, hls_latency,
    area, cell_count, dff_count, gadget_counts, gadget_specs,
    elapsed_total, out_dir
):
    from tabulate import tabulate

    # ── verbose detail → log file only ───────────────────────────────────────
    detail_lines = [
        "\n" + "=" * 70,
        f"FULL RESULTS — {algorithm}",
        "=" * 70,
        f"Design          : {design_name}",
        f"Security order  : d = {d}  ({d+1} shares)",
        f"{constraint_label}: {constraint_val}",
        f"Achieved randomness : {achieved_randomness} bits",
        f"Achieved latency    : {achieved_latency} cycles",
        f"HLS verified latency: {hls_latency} cycles",
        f"Synthesis area      : {area} liberty-units",
        f"Cell count          : {cell_count}",
        f"DFF count           : {dff_count}",
        f"DSE time            : {elapsed_total:.2f}s",
        "",
        "Gadget distribution:",
    ]
    for g, cnt in sorted(gadget_counts.items()):
        rp = gadget_specs.get(g, {}).get("randomness", "?")
        lp = gadget_specs.get(g, {}).get("latency",    "?")
        detail_lines.append(f"  {g:<18} count={cnt}  lat/gadget={lp}  rand/gadget={rp}")
    log("\n".join(detail_lines))

    # ── compute area metrics ──────────────────────────────────────────────────
    a_kge          = area_to_kge(area)
    a_wo_rand_kge  = area_wo_rand_kge(area, achieved_randomness)

    area_str        = f"{a_kge:.3f}"        if a_kge         is not None else "n/a"
    area_wo_str     = f"{a_wo_rand_kge:.3f}" if a_wo_rand_kge is not None else "n/a"

    # ── clean terminal table ──────────────────────────────────────────────────
    sep = "=" * 68
    print(f"\n{bold(sep)}", file=_STDOUT)
    print(bold(f"  DSE RESULTS — {algorithm}"), file=_STDOUT)
    print(bold(sep), file=_STDOUT)

    row = [[
        d,
        achieved_latency if achieved_latency is not None else hls_latency,
        design_name,
        achieved_randomness,
        area_str,
    ]]
    print(tabulate(row,
                   headers=["Security order", "Latency", "Design",
                             "Randomness", "Area (kGE)"],
                   tablefmt="grid"), file=_STDOUT)

    print(f"\n  {dim('Full details')} → {LOG_FILE}", file=_STDOUT)
    print(bold(sep) + "\n", file=_STDOUT)


# ── Save JSON summary ─────────────────────────────────────────────────────────
def save_json_results(path, payload):
    # enrich synthesis block with kGE values if raw area is present
    synth = payload.get("synthesis", {})
    raw   = synth.get("area_ge")          # named area_ge but it's liberty units
    rand  = payload.get("achieved_randomness", 0)
    if raw is not None:
        synth["area_kge"]         = round(area_to_kge(raw), 4)
        synth["area_kge_wo_rand"] = round(area_wo_rand_kge(raw, rand), 4)
        payload["synthesis"]      = synth

    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as f:
        json.dump(payload, f, indent=2)
    ok(f"Results saved  →  {path}")
