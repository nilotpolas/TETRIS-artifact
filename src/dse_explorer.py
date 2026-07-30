#!/usr/bin/env python3

import sys
import os
import re
import glob
import subprocess
import json
import time
import sqlite3
import argparse
import random
import csv
from tabulate import tabulate
from scipy.interpolate import griddata 
# --- Matplotlib for Plotting ---
try:
    import matplotlib.pyplot as plt
    from mpl_toolkits.mplot3d import Axes3D
    import pandas as pd
    import numpy as np
except ImportError:
    print(" plotting libraries (matplotlib, pandas, numpy) are not installed.", file=sys.stderr)
    print("Please install them using: pip install matplotlib pandas numpy", file=sys.stderr)
    sys.exit(1)

# --- Path Setup ---
project_root = os.path.dirname(os.path.abspath(__file__))
masked_hls_src_dir = os.path.join(project_root, 'MaskedHLS_LP', 'src')

paths_to_add = []
paths_to_add.append(masked_hls_src_dir)

if os.path.isdir(masked_hls_src_dir):
    for entry_name in os.listdir(masked_hls_src_dir):
        potential_subdir_path = os.path.join(masked_hls_src_dir, entry_name)
        if os.path.isdir(potential_subdir_path) and not entry_name.startswith('.') and not entry_name == '__pycache__':
            paths_to_add.append(potential_subdir_path)
else:
    print(f"Warning: Directory not found - {masked_hls_src_dir}", file=sys.stderr)

regbalancer_specific_path = os.path.join(masked_hls_src_dir, 'RegBalancer', 'src')
if os.path.isdir(regbalancer_specific_path):
    paths_to_add.append(regbalancer_specific_path)
else:
    print(f"Warning: Specific RegBalancer path not found - {regbalancer_specific_path}", file=sys.stderr)

for path_to_add in reversed(paths_to_add):
    if path_to_add not in sys.path:
        sys.path.insert(0, path_to_add)

# --- Import Core Modules ---
try:
    from pycparser import parse_file, c_ast, c_generator
    from TACGenerator.TAC import TACStyleASTBuilder
    from ANDCloud.and_cloud import AndCloudGenerator
    from Gadgets import base, HPC2, HPC1, HPC3
    from DSE_algorithm.mrlc import MRLC
    from DSE_algorithm.mlrc import MLRC
    from transform_CFile.ctransfromer import ShareTransformer
except ImportError as e:
    print(f" Failed to import a required module: {e}", file=sys.stderr)
    print("Please ensure the MaskedHLS_LP submodule is correctly initialized and paths are set up.", file=sys.stderr)
    sys.exit(1)

# --- Core Pipeline Functions ---

def convert_to_TAC(CFile_path):
    """Parses C code and writes corresponding TAC."""
    print("[INFO] : Transforming input file to TAC...")
    ast = parse_file(CFile_path, use_cpp=True)
    tac_gen = TACStyleASTBuilder()
    for i, ext in enumerate(ast.ext):
        if isinstance(ext, c_ast.FuncDef):
            ast.ext[i] = tac_gen.transform(ext)
    gen = c_generator.CGenerator()
    output_path = os.path.abspath(r"./TestFiles/TAC_files/output.c")
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    with open(output_path, 'w') as f:
        f.write(gen.visit(ast))
    print(f"[INFO] : TAC output written to {output_path}\n")
    return output_path

def run_inliner(input_file, top_module, script_path="./MaskedHLS_LP/src"):
    """Writes systemArgs.json and runs the inliner script."""
    script_abs_path = os.path.abspath(script_path)
    print("[INFO] : Inlining the TAC file...")
    relative_inliner_output_path = os.path.join("TestFiles", "inlined_output", "output.c")
    inlined_file_path = os.path.abspath(relative_inliner_output_path)
    args = {
        "inputFile": input_file,
        "inlinerOutput": inlined_file_path,
        "topModule": top_module,
        "turn": 1
    }
    with open('./MaskedHLS_LP/src/systemArgs.json', "w") as f:
        json.dump(args, f, indent=4)
    print(f"[INFO] : systemArgs.json written.\n")
    try:
        result = subprocess.run(
            ["python3", './Inliner/inliner.py'],
            check=True, text=True, cwd=script_abs_path, capture_output=True
        )
        print(f"[INFO] : Inlined file written to {inlined_file_path}\n")
    except subprocess.CalledProcessError as e:
        print(" Inliner script failed:\n", e.stderr)
        # Capture and print stdout from the failed process for more context
        print(" Inliner script stdout:\n", e.stdout)
        raise
    return inlined_file_path

def generator_and_cloud(filename):
    """Generates the AND-tree from a C file."""
    print("[INFO] : Generating the AND tree...")
    and_cloud = AndCloudGenerator()
    ast = parse_file(filename, use_cpp=True)
    and_cloud.visit(ast)
    print(f"[INFO] : Number of nodes in the tree: {and_cloud.graph.num_nodes()}")
    and_cloud.save_and_tree(filename=filename)
    return and_cloud

def run_maskedHLS(top_module, input_file, rtl_file, bit_width, script_path="./MaskedHLS_LP/src/script.py"):
    """Runs the MaskedHLS tool to generate Verilog and extract latency."""
    script_abs_path = os.path.abspath(script_path)
    script_dir = os.path.dirname(script_abs_path)
    command = [
        "python3",
        "script.py",
        f"--topModule={top_module}",
        f"--inputFile={input_file}",
        f"--rtlFile={rtl_file}",
        f"--bitWidth={bit_width}"
    ]
    print("[INFO] : Running MaskedHLS Command:", " ".join(command))
    latency = None
    try:
        result = subprocess.run(
            command, check=True, capture_output=True, text=True, cwd=script_dir
        )
        stdout = result.stdout
        print("[INFO] MaskedHLS Script output:\n", stdout)
        if result.stderr.strip():
            print(" MaskedHLS Script stderr:\n", result.stderr)
        match = re.search(r"Max path weight\s*(\d+)", stdout)
        if match:
            latency = int(match.group(1))
            print(f"[INFO] : Final design latency from MaskedHLS: {latency}")
        else:
            print(" : Latency not found in MaskedHLS output.")
    except subprocess.CalledProcessError as e:
        print(" : MaskedHLS script failed with exit code", e.returncode)
        print(" : stdout:\n", e.stdout)
        print(" : stderr:\n", e.stderr)
    return latency

# --- Hardcoded Gadget Data and Database Management ---

def setup_hardcoded_gadget_db(conn):
    """Create and populate the gadget table with only hardcoded data."""
    cur = conn.cursor()
    cur.execute('CREATE TABLE IF NOT EXISTS gadget(d INTEGER PRIMARY KEY)')
    for table in ["hpc1", "hpc2", "hpc3"]:
        cur.execute(f'''
            CREATE TABLE IF NOT EXISTS {table}(
                d INTEGER PRIMARY KEY,
                latency INTEGER,
                randomness INTEGER,
                area REAL,
                FOREIGN KEY (d) REFERENCES gadget(d) ON DELETE CASCADE
            )
        ''')
    # Insert hardcoded values exactly matching your script 1
    hardcoded_data = {
        'hpc1': [(1,2,2,3),(2,2,5,6),(3,2,9,10),(4,2,14,15),(5,2,20,21)],
        'hpc2': [(1,2,1,5),(2,2,3,12),(3,2,6,22),(4,2,10,35),(5,2,15,50)],
        'hpc3': [(1,1,2,4),(2,1,6,9),(3,1,12,16),(4,1,20,25),(5,1,30,36)],
    }
    for table, rows in hardcoded_data.items():
        for d, latency, randomness, area in rows:
            cur.execute("INSERT OR IGNORE INTO gadget (d) VALUES (?)", (d,))
            cur.execute(f"""
                INSERT INTO {table} (d, latency, randomness, area)
                VALUES (?, ?, ?, ?)
                ON CONFLICT(d) DO UPDATE SET
                    latency = excluded.latency,
                    randomness = excluded.randomness,
                    area = excluded.area
            """, (d, latency, randomness, area))
    conn.commit()

def get_gadget_specs_for_d(d, cur):
    """Fetch only from hardcoded DB, never generate dynamically."""
    gadget_specs = {}
    gadget_list = ["hpc1", "hpc2", "hpc3", "hpc2o", "hpc3o", "hpc2_swapped", "hpc2o_swapped"]
    for gadget in gadget_list:
        table = gadget.lower()
        cur.execute(f"SELECT latency, randomness, area FROM {table} WHERE d = ?", (d,))
        row = cur.fetchone()
        if row:
            gadget_specs[gadget] = {"latency": row[0], "randomness": row[1], "area": row[2]}
        else:
            print(f"[WARN] No entry for {gadget} with d = {d}")
    return gadget_specs

# --- DSE Algorithm Wrappers ---

def run_mrlc(latency_target, d, and_cloud, gadget_map):
    print(f"\n[INFO] : Running MRLC for security order d={d} and latency_target={latency_target}...")
    mrlc_runner = MRLC(d=d, and_tree=and_cloud, gadget_map=gadget_map)
    start_time = time.perf_counter()
    mrlc_runner.mrlc_dp(latency_target)
    end_time = time.perf_counter()
    print(f"[INFO] : MRLC finished in {end_time - start_time:.4f}s.")
    gadget_mapping = mrlc_runner.get_gadget_definition()
    unique_defs = mrlc_runner.get_unique_gadgets_definition()
    total_randomness = 0
    total_area = 0
    for node_id, gadget_details in gadget_mapping.items():
        g_name = gadget_details['gadget_name']
        total_randomness += gadget_map[g_name]['randomness']
        total_area += gadget_map[g_name]['area']
    
    actual_latency = 0
    for level in range(1, and_cloud.max_level + 1):
        max_level_latency = 0
        if level in and_cloud.level_nodes and and_cloud.level_nodes[level]:
            for node_id in and_cloud.level_nodes[level]:
                gadget_details = gadget_mapping.get(node_id)
                if not gadget_details: continue
                g_name = gadget_details['gadget_name']
                max_level_latency = max(max_level_latency, gadget_map[g_name]['latency'])
        actual_latency += max_level_latency
    
    return total_randomness, total_area, actual_latency, unique_defs, gadget_mapping

def run_mlrc(randomness_target, d, and_cloud, gadget_map):
    print(f"\n[INFO] : Running MLRC for security order d={d} and randomness_target={randomness_target}...")
    mlrc_runner = MLRC(d=d, and_tree=and_cloud, gadget_map=gadget_map)
    start_time = time.perf_counter()
    mlrc_runner.mlrc(randomness_target)
    end_time = time.perf_counter()
    print(f"[INFO] : MLRC finished in {end_time - start_time:.4f}s.")
    gadget_mapping = mlrc_runner.get_gadget_definition()
    unique_defs = mlrc_runner.get_unique_gadgets_definition()
    
    # --- FIX 2: Correctly calculate total area, randomness, and latency ---
    # The original implementation had a bug where area/randomness were summed incorrectly.
    # This new logic calculates each metric separately and correctly.
    total_randomness = 0
    total_area = 0
    # First, calculate total area and randomness from the final gadget mapping
    for node_id, gadget_details in gadget_mapping.items():
        if not gadget_details: continue
        g_name = gadget_details['gadget_name']
        total_randomness += gadget_map[g_name]['randomness']
        total_area += gadget_map[g_name]['area']
    
    # Second, calculate total latency by iterating through levels
    total_latency = 0
    for level in range(1, and_cloud.max_level + 1):
        max_level_latency = 0
        if level in and_cloud.level_nodes and and_cloud.level_nodes[level]:
            for node_id in and_cloud.level_nodes[level]:
                gadget_details = gadget_mapping.get(node_id)
                if not gadget_details: continue
                g_name = gadget_details['gadget_name']
                max_level_latency = max(max_level_latency, gadget_map[g_name]['latency'])
        total_latency += max_level_latency

    return total_latency, total_area, total_randomness, unique_defs, gadget_mapping

def run_msrlc(latency_target, randomness_target, security_range, and_cloud, conn, preference):
    print(f"\n[INFO] : Running MSRLC with latency_target <= {latency_target} and randomness_target <= {randomness_target}...")
    best_result = None
    for d in sorted(security_range, reverse=True):
        print(f"\n--- Checking Security Order d={d} ---")
        gadget_map = get_gadget_specs_for_d(d, conn.cursor())
        if not gadget_map:
            print(f" : No gadgets defined for security order {d}. Skipping.")
            continue
        
        if preference == 'randomness' :
            # Strategy: Find the most randomness-efficient design that meets the latency target.
            # Then, check if its randomness cost is within our budget.
            min_randomness, area, actual_latency, unique_defs, gadget_mapping = run_mrlc(latency_target, d, and_cloud, gadget_map)
            print(f"[INFO] : For d={d}, min randomness required for latency <= {latency_target} is {min_randomness} (actual latency: {actual_latency}).")
            
            if min_randomness <= randomness_target:
                print(f" : Found a valid design at security order d={d}!")
                best_result = {
                    "security_order": d,
                    "latency": actual_latency, # Store the actual latency achieved
                    "randomness": min_randomness,
                    "area": area,
                    "unique_defs": unique_defs,
                    "gadget_mapping": gadget_mapping
                }
                break
            else:
                print(f"[INFO] : Design at d={d} is not feasible (requires {min_randomness} randomness > {randomness_target}).")

        elif preference == 'latency':
            min_latency, area, actual_randomness, unique_defs, gadget_mapping = run_mlrc(randomness_target, d, and_cloud, gadget_map)
        
            print(f"[INFO] : For d={d}, with randomness <= {randomness_target}, the minimum achievable latency is {min_latency}.")

            # Now, check if this best-case latency is within our latency budget.
            if min_latency <= latency_target:
                print(f" : Found a valid design at security order d={d}!")
                best_result = {
                    "security_order": d,
                    "latency": min_latency,         # Store the actual best latency found
                    "randomness": actual_randomness,# Store the actual randomness used
                    "area": area,
                    "unique_defs": unique_defs,
                    "gadget_mapping": gadget_mapping
                }
                # Since we iterate d from high to low, the first solution found is the best one.
                break 
            else:
                print(f"[INFO] : Design at d={d} is not feasible (requires {min_latency} latency > {latency_target}).")

    return best_result


def _calculate_metrics(mapping, d, and_cloud, gadget_map):
    """A helper function to calculate the metrics for a given gadget mapping."""
    # 1. Calculate Total Latency (by level)
    total_latency = 0
    for level in range(1, and_cloud.max_level + 1):
        max_level_latency = 0
        if level in and_cloud.level_nodes and and_cloud.level_nodes[level]:
            for node_id in and_cloud.level_nodes[level]:
                g_name = mapping.get(node_id)
                if g_name:
                    max_level_latency = max(max_level_latency, gadget_map[g_name]['latency'])
        total_latency += max_level_latency

    # 2. Calculate Total Randomness and Area (over all nodes)
    total_randomness = 0
    total_area = 0
    for node_id, g_name in mapping.items():
        total_area += gadget_map[g_name]['area']
        total_randomness += gadget_map[g_name]['randomness']
        
    return (total_latency, total_randomness, d, total_area)

def run_structured_exploration(d, and_cloud, gadget_map, partial_samples_per_level=100):
    """
    Generates design points using a structured exploration strategy.
    1. Uniform Assignment: All nodes get the same gadget.
    2. Full-Level Swap: Swap one entire level (row) to a different gadget.
    3. Partial-Level Swap: Swap a random subset of nodes in a level.
    """
    print(f"[INFO] : Starting structured exploration for d={d}...")
    points = set() # Use a set to automatically handle duplicate designs
    gadget_names = list(gadget_map.keys())
    all_node_ids = list(and_cloud.graph.nodes())

    if not all_node_ids:
        print("[WARN] : The AND-cloud graph has no nodes. Exploration will yield no results.")
        return []

    # --- Strategy 1: Uniform Gadget Assignments ---
    print("[INFO] :   Phase 1: Generating uniform baseline designs...")
    base_mappings = []
    for g_name in gadget_names:
        # Assign the same gadget to all nodes
        uniform_mapping = {node_id: g_name for node_id in all_node_ids}
        points.add(_calculate_metrics(uniform_mapping, d, and_cloud, gadget_map))
        base_mappings.append(uniform_mapping)
        
    # We will use the first uniform design as a baseline for the next strategies
    base_mapping = base_mappings[0]

    # --- Strategy 2: Full Level-by-Level Replacement ---
    print("[INFO] :   Phase 2: Sweeping full level replacements...")
    for level in range(1, and_cloud.max_level + 1):
        if level not in and_cloud.level_nodes: continue
        nodes_in_level = and_cloud.level_nodes[level]
        
        # Try replacing this entire level with every other possible gadget
        for g_name_replacement in gadget_names:
            new_mapping = base_mapping.copy()
            for node_id in nodes_in_level:
                new_mapping[node_id] = g_name_replacement
            points.add(_calculate_metrics(new_mapping, d, and_cloud, gadget_map))

    # --- Strategy 3: Partial Level Replacement ---
    print(f"[INFO] :   Phase 3: Generating {partial_samples_per_level} partial samples per level...")
    for level in range(1, and_cloud.max_level + 1):
        if level not in and_cloud.level_nodes: continue
        nodes_in_level = and_cloud.level_nodes[level]
        if not nodes_in_level: continue

        for _ in range(partial_samples_per_level):
            new_mapping = base_mapping.copy()
            
            # Choose a random number of nodes to replace in the level
            num_to_replace = random.randint(1, len(nodes_in_level))
            nodes_to_replace = random.sample(nodes_in_level, num_to_replace)
            
            # Choose a random gadget to assign to them
            g_name_replacement = random.choice(gadget_names)
            
            for node_id in nodes_to_replace:
                new_mapping[node_id] = g_name_replacement
            points.add(_calculate_metrics(new_mapping, d, and_cloud, gadget_map))
    
    print(f"[INFO] : Generated {len(points)} unique design points for d={d}.")
    return list(points)


# --- Random Exploration ---
def run_random_exploration(num_samples, d, and_cloud, gadget_map):
    """Generates a number of random gadget assignments and calculates their cost."""
    print(f"[INFO] : Generating {num_samples} random design points...")
    points = []
    gadget_names = list(gadget_map.keys())
    
    all_node_ids = list(and_cloud.graph.nodes())
    
    if not all_node_ids:
        print("[WARN] : The AND-cloud graph has no nodes. Random exploration will yield no results.")
        return []

    for _ in range(num_samples):
        random_mapping = {node_id: random.choice(gadget_names) for node_id in all_node_ids}

        # 1. Calculate Total Latency (by level)
        total_latency = 0
        for level in range(1, and_cloud.max_level + 1):
            max_level_latency = 0
            if level in and_cloud.level_nodes and and_cloud.level_nodes[level]:
                for node_id in and_cloud.level_nodes[level]:
                    g_name = random_mapping.get(node_id)
                    if g_name:
                        max_level_latency = max(max_level_latency, gadget_map[g_name]['latency'])
            total_latency += max_level_latency

        # 2. Calculate Total Randomness and Area (over all nodes)
        total_randomness = 0
        total_area = 0
        for node_id in all_node_ids:
            g_name = random_mapping.get(node_id)
            if not g_name: continue
            total_area += gadget_map[g_name]['area']
            total_randomness += gadget_map[g_name]['randomness']

        points.append((total_latency, total_randomness, d, total_area))
    
    return points


def explore_and_plot(security_range, steps, random_samples, and_cloud, conn):
    print("\n[INFO] : Starting full Design Space Exploration...")
    all_heuristic_points, all_random_points = [], []
    all_best_points = []
    for d in security_range:
        print(f"\n--- Exploring Security Order d={d} ---")
        gadget_map = get_gadget_specs_for_d(d, conn.cursor())
        if not gadget_map: continue
        
        heuristic_points_for_d = []
        # 1. MLRC Sweep
        min_rand = and_cloud.graph.num_nodes() * min(g['randomness'] for g in gadget_map.values())
        max_rand = and_cloud.graph.num_nodes() * max(g['randomness'] for g in gadget_map.values())


        print(f"[INFO] : Sweeping randomness from ~{min_rand} to {max_rand} (MLRC).")
        for r_target in np.linspace(min_rand, max_rand, steps):
            latency, area, randomness, _, _ = run_mlrc(int(r_target), d, and_cloud, gadget_map)
            if latency is not None: 
                heuristic_points_for_d.append((latency, randomness, d, area))
                all_random_points.append((latency, randomness, d, area))


        # 2. MRLC Sweep
        min_lat = and_cloud.max_level * min(g['latency'] for g in gadget_map.values())
        max_lat = and_cloud.max_level * max(g['latency'] for g in gadget_map.values())
        print(f"[INFO] : Sweeping latency from ~{min_lat} to {max_lat} (MRLC).")
        for l_target in np.linspace(min_lat, max_lat, steps):
            randomness, area, actual_latency, _, _ = run_mrlc(int(np.ceil(l_target)), d, and_cloud, gadget_map)
            if randomness is not None: 
                heuristic_points_for_d.append((actual_latency, randomness, d, area))
                all_random_points.append((actual_latency, randomness, d, area))

        if heuristic_points_for_d:
            # Define the filename. It's good practice to include the security order in the name.
            csv_filename = f'heuristic_points_d_{d}.csv'
            print(f"[INFO] : Writing heuristic points to {csv_filename}...")
            
            # Define the header for your CSV file
            header = ['latency', 'randomness', 'd', 'area']
            
            # Open the file in write mode
            with open(csv_filename, 'w', newline='') as csvfile:
                # Create a CSV writer object
                writer = csv.writer(csvfile)
                
                # Write the header row
                writer.writerow(header)
                
                # Write all the data rows
                writer.writerows(heuristic_points_for_d)
                
            print(f"[INFO] : Successfully saved {len(heuristic_points_for_d)} points.")


        # 3. Random Sampling
        if random_samples > 0:
            all_random_points.extend(run_random_exploration(random_samples, d, and_cloud, gadget_map))
            all_random_points.extend(run_structured_exploration(d, and_cloud, gadget_map))


        if all_random_points:
            # Define the filename. It's good practice to include the security order in the name.
            csv_filename = f'random_points_d_{d}.csv'
            print(f"[INFO] : Writing random points to {csv_filename}...")
            
            # Define the header for your CSV file
            header = ['latency', 'randomness', 'd', 'area']
            
            # Open the file in write mode
            with open(csv_filename, 'w', newline='') as csvfile:
                # Create a CSV writer object
                writer = csv.writer(csvfile)
                
                # Write the header row
                writer.writerow(header)
                
                # Write all the data rows
                writer.writerows(all_random_points)
                
            print(f"[INFO] : Successfully saved {len(all_random_points)} points.")


        # 4. Filter for Heuristic Pareto Front
        if heuristic_points_for_d:
            df_heuristic = pd.DataFrame(heuristic_points_for_d, columns=['latency', 'randomness', 'd', 'area']).drop_duplicates()
            for _, row in df_heuristic.iterrows():
                all_heuristic_points.append(tuple(row))
                is_dominated = ((df_heuristic['latency'] <= row['latency']) & (df_heuristic['randomness'] <= row['randomness']) &
                                ((df_heuristic['latency'] < row['latency']) | (df_heuristic['randomness'] < row['randomness']))).any()
                if not is_dominated: all_best_points.append(tuple(row))

    if not all_heuristic_points and not all_random_points:
        print(" : No valid design points found during exploration.")
        return

    print("\n[INFO] : Generating plots from DSE results...")
    df_heuristic_results = pd.DataFrame(list(set(all_heuristic_points)), columns=['latency', 'randomness', 'd', 'area'])
    df_heuristic_best_result = pd.DataFrame(list(set(all_best_points)), columns=['latency', 'randomness', 'd', 'area'])
    df_random_results = pd.DataFrame(all_random_points, columns=['latency', 'randomness', 'd', 'area'])


    # --- Plotting for HEURISTIC Results ---
    if not df_heuristic_results.empty:
        print("\n[INFO] : Generating plots for HEURISTIC Algorithms...")
        # 3D Scatter Plot (Heuristic)
        fig = plt.figure(figsize=(12, 9))
        ax = fig.add_subplot(111, projection='3d')
        scatter = ax.scatter(df_heuristic_results['latency'], df_heuristic_results['randomness'], df_heuristic_results['d'], 
                             c=df_heuristic_results['area'], cmap='viridis', s=60, alpha=0.8)
        
        # if not df_heuristic_best_result.empty:
        #     ax.scatter(df_heuristic_best_result['latency'], df_heuristic_best_result['randomness'], df_heuristic_best_result['d'], 
        #             c='red',                 # Set the color to red
        #             s=100,                   # Make the points larger to stand out
        #             edgecolors='black',      # Add a black border for better visibility
        #             depthshade=False,        # Ensure the red color is bright
        #             label='Best Points per Layer') # Add a label for the legend
            
        ax.set_xlabel('Latency (cycles)'); 
        ax.set_ylabel('Randomness (bits)'); 
        ax.set_zlabel('Security Order (d)')
        ax.set_title('DSE: Latency vs. Randomness vs. Security')
        fig.colorbar(scatter, label='Area (GE)')
        plt.savefig('dse_heuristic_3d_pareto_front.png')
        print("[INFO] : Saved Heuristic 3D Pareto front plot to 'dse_heuristic_3d_pareto_front.png'")
        plt.close(fig)

        # 2D Projections (Heuristic)
        fig, ax = plt.subplots(figsize=(12, 8))
        for d_val in sorted(df_heuristic_results['d'].unique()):
            subset = df_heuristic_results[df_heuristic_results['d'] == d_val].sort_values(by='latency')
            ax.plot(subset['latency'], subset['randomness'], marker='o', linestyle='-', label=f'Security Order d={d_val}')
        ax.set_xlabel('Latency (cycles)'); ax.set_ylabel('Randomness (bits)')
        ax.set_title('DSE: Latency vs. Randomness Projections')
        ax.legend(); ax.grid(True)
        plt.savefig('dse_heuristic_2d_projections.png')
        print("[INFO] : Saved Heuristic 2D projections plot to 'dse_heuristic_2d_projections.png'")
        plt.close(fig)

        # 2D Scatter Plots (Heuristic)
        for d_val in sorted(df_heuristic_results['d'].unique()):
            subset = df_heuristic_results[df_heuristic_results['d'] == d_val]
            if len(subset) < 1:
                print(f" : Skipping heuristic 2D plot for d={d_val}, not enough data points.")
                continue

            # --- CHANGED: Create a 2D plot instead of 3D ---
            fig, ax = plt.subplots(figsize=(12, 8))
            
            # 1. Plot the main heuristic points in 2D
            # X = latency, Y = randomness, Color = area
            scatter = ax.scatter(
                subset['latency'],
                subset['randomness'],
                c=subset['area'],
                cmap='plasma',
                s=80,  # size of points
                alpha=0.75,
                label='Heuristic Points'
            )
            
            # 2. Filter and highlight the 'best_result' points
            best_points_for_d = df_heuristic_best_result[df_heuristic_best_result['d'] == d_val]
            
            if not best_points_for_d.empty:
                ax.scatter(
                    best_points_for_d['latency'],
                    best_points_for_d['randomness'],
                    c='red',
                    s=150,  # Make the best points larger
                    edgecolors='black',
                    linewidths=1.5,
                    label='Best Point'
                )

            # --- UPDATED: Set labels and title for 2D plot ---
            ax.set_xlabel('Latency (cycles)')
            ax.set_ylabel('Randomness (bits)')
            ax.set_title(f'DSE: Latency vs. Randomness for d={d_val}')
            
            # Add a grid for easier reading
            ax.grid(True, linestyle='--', alpha=0.6)
            
            # Add a legend
            ax.legend()
            
            # Add a colorbar to show what the colors represent (Area)
            fig.colorbar(scatter, label='Area (GE)')
            
            # --- UPDATED: New filename for the 2D plot ---
            plot_filename = f'dse_heuristic_2d_scatter_d_{int(d_val)}.png'
            plt.savefig(plot_filename)
            print(f"[INFO] : Saved Heuristic 2D scatter plot to '{plot_filename}'")
            plt.close(fig)

        # # 3D Scatter Plots (Heuristic)
        # for d_val in sorted(df_heuristic_results['d'].unique()):
        #     subset = df_heuristic_results[df_heuristic_results['d'] == d_val]
        #     if len(subset) < 1: # A scatter plot can be made with even one point
        #         print(f" : Skipping heuristic scatter plot for d={d_val}, not enough data points.")
        #         continue
            
        #     # This check is less critical for a scatter plot but good to keep
        #     if subset['latency'].nunique() == 1 or subset['randomness'].nunique() == 1:
        #         print(f" : Note: For d={d_val}, data points are co-linear.")

        #     fig = plt.figure(figsize=(12, 9))
        #     ax = fig.add_subplot(111, projection='3d')
            
        #     # 1. Plot the main heuristic points from the subset
        #     scatter = ax.scatter(
        #         subset['latency'],      # X-axis
        #         subset['randomness'],   # Y-axis
        #         subset['area'],         # Z-axis
        #         c=subset['area'],       # Color points by area
        #         cmap='plasma',          # Colormap
        #         s=60,                   # Marker size
        #         alpha=0.8               # Transparency
        #     )
            

        #     # 2. Filter the 'best_result' dataframe for the current d_val
        #     best_points_for_d = df_heuristic_best_result[df_heuristic_best_result['d'] == d_val]
            
        #     # 3. If best points exist for this 'd', plot them on top
        #     if not best_points_for_d.empty:
        #         ax.scatter(
        #             best_points_for_d['latency'],
        #             best_points_for_d['randomness'],
        #             best_points_for_d['area'],
        #             c=best_points_for_d['area'],                # Set color to red
        #             cmap='plasma', 
        #             s=120,                  # Make points larger to stand out
        #             # edgecolors='black',     # Add a black border for visibility
        #             # depthshade=False,       # Ensure the red color is bright
        #             label='Best Point'      # Label for the legend
        #         )

        #     # Define a padding factor to give a little space around the data
        #     padding_factor = 0.1 

        #     # Calculate limits for Latency (X-axis)
        #     x_min, x_max = subset['latency'].min(), subset['latency'].max()
        #     x_range = x_max - x_min if x_max > x_min else 1.0 # Avoid division by zero if all points are same
        #     x_padding = x_range * padding_factor
        #     ax.set_xlim(x_min - x_padding, x_max + x_padding)

        #     # Calculate limits for Randomness (Y-axis)
        #     y_min, y_max = subset['randomness'].min(), subset['randomness'].max()
        #     y_range = y_max - y_min if y_max > y_min else 1.0
        #     y_padding = y_range * padding_factor
        #     ax.set_ylim(y_min - y_padding, y_max + y_padding)

        #     # Calculate limits for Area (Z-axis)
        #     z_min, z_max = subset['area'].min(), subset['area'].max()
        #     z_range = z_max - z_min if z_max > z_min else 1.0
        #     z_padding = z_range * padding_factor
        #     ax.set_zlim(z_min - z_padding, z_max + z_padding)

        #     ax.set_xlabel('Latency (cycles)')
        #     ax.set_ylabel('Randomness (bits)')
        #     ax.set_zlabel('Area (GE)')
        #     ax.set_title(f'Heuristic DSE: Latency vs. Randomness vs. Area for d={d_val}')
            
        #     # Update colorbar to use the 'scatter' object
        #     fig.colorbar(scatter, shrink=0.5, aspect=5, label='Area (GE)')
            
        #     plot_filename = f'dse_heuristic_scatter_d_{int(d_val)}.png'
        #     plt.savefig(plot_filename)
        #     print(f"[INFO] : Saved Heuristic 3D scatter plot to '{plot_filename}'")
        #     plt.close(fig)

    # --- Plotting for RANDOM Sampling Results ---
    if not df_random_results.empty:
        print("\n[INFO] : Generating plots for RANDOM Sampling...")
        from scipy.ndimage import gaussian_filter
        # 3D Scatter Plot (Random)
        fig = plt.figure(figsize=(12, 9))
        ax = fig.add_subplot(111, projection='3d')
        scatter = ax.scatter(df_random_results['latency'], df_random_results['randomness'], df_random_results['d'], 
                             c=df_random_results['area'], cmap='plasma', s=30, alpha=0.6) # Using a different cmap for distinction
        ax.set_xlabel('Latency (cycles)'); ax.set_ylabel('Randomness (bits)'); ax.set_zlabel('Security Order (d)')
        ax.set_title('Random Sampling DSE: Latency vs. Randomness vs. Security')
        fig.colorbar(scatter, label='Area (GE)')
        plt.savefig('dse_random_3d_scatter.png')
        print("[INFO] : Saved Random 3D scatter plot to 'dse_random_3d_scatter.png'")
        plt.close(fig)

        # 2D Projections (Random)
        fig, ax = plt.subplots(figsize=(12, 8))
        for d_val in sorted(df_random_results['d'].unique()):
            subset = df_random_results[df_random_results['d'] == d_val]
            ax.scatter(subset['latency'], subset['randomness'], s=20, alpha=0.7, label=f'Security Order d={d_val}')
        ax.set_xlabel('Latency (cycles)'); ax.set_ylabel('Randomness (bits)')
        ax.set_title('Random Sampling DSE: Latency vs. Randomness Projections')
        ax.legend(); ax.grid(True)
        plt.savefig('dse_random_2d_projections.png')
        print("[INFO] : Saved Random 2D projections plot to 'dse_random_2d_projections.png'")
        plt.close(fig)

        # 3D Surface Plots (Random)
        for d_val in sorted(df_random_results['d'].unique()):
            subset = df_random_results[df_random_results['d'] == d_val]
            if len(subset) < 4:
                print(f" : Skipping random surface plot for d={d_val}, not enough data points (need at least 4).")
                continue
            
            # Add a check to prevent QhullError if all points are on a line
            if subset['latency'].nunique() == 1 or subset['randomness'].nunique() == 1:
                print(f" : Skipping random surface plot for d={d_val}, data points are co-linear.")
                continue
            
            grid_x, grid_y = np.mgrid[subset['latency'].min():subset['latency'].max():100j, 
                                      subset['randomness'].min():subset['randomness'].max():100j]
            grid_z = griddata(subset[['latency', 'randomness']], subset['area'], (grid_x, grid_y), method='cubic')
            grid_z_smooth = gaussian_filter(grid_z, sigma=3)
            fig = plt.figure(figsize=(12, 9))
            ax = fig.add_subplot(111, projection='3d')
            surf = ax.plot_surface(grid_x, grid_y, grid_z_smooth, cmap='plasma', edgecolor='none', alpha=0.5)
            ax.set_xlabel('Latency (cycles)'); 
            ax.set_ylabel('Randomness (bits)'); 
            ax.set_zlabel('Area (GE)')
            ax.set_title(f'Random DSE: Latency vs. Randomness vs. Area for d={d_val}')

            # ax.view_init(elev=10, azim=-60) # We can change these angles!

            fig.colorbar(surf, shrink=0.5, aspect=5, label='Area (GE)')
            plot_filename = f'dse_random_surface_d_{int(d_val)}.png'
            plt.savefig(plot_filename)
            print(f"[INFO] : Saved Random 3D surface plot to '{plot_filename}'")
            plt.close(fig)

            # --- 2. ADDED: Generate the Top-Down 2D View (Heatmap) ---
            fig_top, ax_top = plt.subplots(figsize=(10, 8))
            
            # Use pcolormesh to create a 2D heatmap from the data
            c = ax_top.pcolormesh(grid_x, grid_y, grid_z_smooth, cmap='plasma', shading='auto')
            
            # Overlay the original data points to see where the samples came from
            ax_top.scatter(subset['latency'], subset['randomness'], c='white', edgecolors='black', s=30, label='Original Data Points')
            
            ax_top.set_xlabel('Latency (cycles)')
            ax_top.set_ylabel('Randomness (bits)')
            ax_top.set_title(f'Random DSE: Top-Down View for d={d_val}')
            fig_top.colorbar(c, label='Area (GE)')
            ax_top.legend()
            ax_top.grid(True, alpha=0.3)
            
            top_view_filename = f'dse_random_surface_top_view_d_{int(d_val)}.png'
            plt.savefig(top_view_filename)
            print(f"[INFO] : Saved Top-Down view to '{top_view_filename}'")
            plt.close(fig_top)

    # --- Plotting for COMBINED Comparison (Heuristic vs. Random) ---
    if not df_heuristic_results.empty and not df_random_results.empty:
        print("\n[INFO] : Generating COMBINED comparison plots...")
        fig, ax = plt.subplots(figsize=(12, 8))
        all_d_values = sorted(pd.concat([df_heuristic_results['d'], df_random_results['d']]).unique())

        for d_val in all_d_values:
            # Plot random points as a background cloud
            random_subset = df_random_results[df_random_results['d'] == d_val]
            if not random_subset.empty:
                # Use a single label for all random points for a cleaner legend
                label = 'Random Samples' if d_val == all_d_values[0] else None
                ax.scatter(random_subset['latency'], random_subset['randomness'],
                           color='gray', s=15, alpha=0.8, label=label)

            # Plot heuristic pareto front on top
            heuristic_subset = df_heuristic_results[df_heuristic_results['d'] == d_val].sort_values(by='latency')
            if not heuristic_subset.empty:
                ax.plot(heuristic_subset['latency'], heuristic_subset['randomness'], marker='o', linestyle='-',
                        label=f'Pareto Front (d={d_val})')

        ax.set_xlabel('Latency (cycles)')
        ax.set_ylabel('Randomness (bits)')
        ax.set_title('DSE Comparison: Our Algorithms vs. Random Sampling')
        ax.legend()
        ax.grid(True)
        plt.savefig('dse_comparison_2d_projections.png')
        print("[INFO] : Saved comparison 2D plot to 'dse_comparison_2d_projections.png'")
        plt.close(fig)

# --- Main Execution Logic ---

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run DSE for gadget-based masked hardware.")
    parser.add_argument("--input_file", required=True, help="Path to input C file")
    parser.add_argument("--top_module", required=True, help="Top-level function name")
    parser.add_argument("--mode", required=True, choices=['mlrc', 'mrlc', 'msrlc', 'explore'], help="DSE algorithm to run")
    parser.add_argument("--latency", type=int, help="Latency constraint (for mrlc and msrlc)")
    parser.add_argument("--randomness", type=int, help="Randomness constraint (for mlrc and msrlc)")
    parser.add_argument("--security_order", type=int, default=1, help="Security order 'd' (for mlrc and mrlc)")
    parser.add_argument("--max_security_order", type=int, default=3, help="Maximum security order to explore (for msrlc and explore)")
    parser.add_argument("--steps", type=int, default=20, help="Number of randomness points to sweep per security order (for explore mode)")
    parser.add_argument("--random_samples", type=int, default=10000, help="Number of random designs to sample for comparison")
    parser.add_argument("--preference", choices=['latency', 'randomness'], default='randomness', 
                        help="For msrlc mode: prioritize minimizing latency or randomness after security (default: randomness)")
    args = parser.parse_args()

    # Step 1-3: C -> TAC -> Inline -> AND-Tree
    tac_file = convert_to_TAC(args.input_file)
    inlined_file = run_inliner(tac_file, args.top_module)
    and_tree = generator_and_cloud(inlined_file)
    print()

    # Step 4: Database and Gadget Cost Setup (hardcoded only)
    conn = sqlite3.connect(':memory:') # Use in-memory DB for simplicity
    setup_hardcoded_gadget_db(conn)

    # Step 5: Run selected DSE mode
    unique_defs, gadget_mapping, d_final = None, None, None
    if args.mode in ['mlrc', 'mrlc', 'msrlc']:
        if args.mode == 'mlrc':
            if args.randomness is None: parser.error("--randomness is required for mlrc mode.")
            gadget_map = get_gadget_specs_for_d(args.security_order, conn.cursor())
            if not gadget_map:
                print(f"[ERROR] No gadgets found for security order d={args.security_order}. Exiting.")
                sys.exit(1)
            _, _, _, unique_defs, gadget_mapping = run_mlrc(args.randomness, args.security_order, and_tree, gadget_map)
            d_final = args.security_order

        elif args.mode == 'mrlc':
            if args.latency is None: parser.error("--latency is required for mrlc mode.")
            gadget_map = get_gadget_specs_for_d(args.security_order, conn.cursor())
            if not gadget_map:
                print(f"[ERROR] No gadgets found for security order d={args.security_order}. Exiting.")
                sys.exit(1)
            _, _, _, unique_defs, gadget_mapping = run_mrlc(args.latency, args.security_order, and_tree, gadget_map)
            d_final = args.security_order

        elif args.mode == 'msrlc':
            if args.latency is None or args.randomness is None: parser.error("--latency and --randomness are required for msrlc mode.")
            security_range = range(1, args.max_security_order + 1)
            result = run_msrlc(args.latency, args.randomness, security_range, and_tree, conn, args.preference)
            if result:
                print("\n : MSRLC found optimal solution:")
                print(f"  - Max Security Order (d): {result['security_order']}")
                print(f"  - Latency: <= {result['latency']}")
                print(f"  - Randomness: {result['randomness']}")
                print(f"  - Area: {result['area']} GE")
                unique_defs = result['unique_defs']
                gadget_mapping = result['gadget_mapping']
                d_final = result['security_order']
            else:
                print("\n : MSRLC could not find a feasible design for the given constraints.")
                sys.exit(0)

        # Step 6-9: Transform C file and run MaskedHLS
        if unique_defs and gadget_mapping and d_final is not None:
            print("\n[INFO] : Transforming C file with optimal gadget placement...")
            ast = parse_file(inlined_file, use_cpp=True)
            shareTransformer = ShareTransformer(d_final + 1, gadget_mapping, unique_defs)
            transformed_ast = shareTransformer.transform(ast)
            gen = c_generator.CGenerator()
            output_path = os.path.abspath(r"./TestFiles/share_output/output.c")
            os.makedirs(os.path.dirname(output_path), exist_ok=True)
            with open(output_path, 'w') as f:
                f.write(gen.visit(transformed_ast))
            print(f"[INFO] : Final masked C code written to {output_path}\n")
            run_maskedHLS(top_module=args.top_module, input_file=output_path, rtl_file='final_design.v', bit_width=8)

    elif args.mode == 'explore':
        security_range = range(1, args.max_security_order + 1)
        explore_and_plot(security_range, args.steps, args.random_samples, and_tree, conn)
        print("\n[INFO] : Exploration and plotting complete.")

    conn.close()