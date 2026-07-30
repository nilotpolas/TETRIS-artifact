# 1. convert the c file into tac. remove reassignmnet of varaibles
# 2. run script to inline the c file. 
# 3. run and_cloud generator to get the and tree.

# 4. generate the gadget defintion for the d order security.

# 5. get the area and latency of each gadget.
# 6. generate the dict for each gadget area latnecy and randomness

# 7. run mlrc and mrlc to get the optimisation gadget placement
# 8. replace the and operation with the gadgets

# 9. pass this file to maskedHLS

# import sys
# import os
# import glob # For finding directories

# # Get the directory of the current script (MTP_Tetris/)
# project_root = os.path.dirname(os.path.abspath(__file__))

# # Path to the MaskedHLS_LP/src/ directory
# masked_hls_src_dir = os.path.join(project_root, 'MaskedHLS_LP', 'src')

# # 1. Add the MaskedHLS_LP/src/ directory itself to sys.path
# # This allows your script.py to do imports like:
# # from Inliner.Visitors import ...
# # from TACGenerator.TAC import ...
# if masked_hls_src_dir not in sys.path:
#     sys.path.insert(0, masked_hls_src_dir)
#     print(f"Added to sys.path: {masked_hls_src_dir}") # For debugging

# # 2. Add all immediate subdirectories of MaskedHLS_LP/src/ to sys.path
# # This helps resolve absolute imports of sibling modules within those subdirectories.
# # For example, if Inliner/Visitors.py does 'from DiGraph import DiGraph'
# # and DiGraph.py is also in Inliner/, this will help.

# if os.path.isdir(masked_hls_src_dir):
#     # List all entries in masked_hls_src_dir
#     for entry_name in os.listdir(masked_hls_src_dir):
#         potential_subdir_path = os.path.join(masked_hls_src_dir, entry_name)
#         # Check if it's a directory and not a hidden directory (like .git, __pycache__)
#         if os.path.isdir(potential_subdir_path) and not entry_name.startswith('.') and not entry_name == '__pycache__':
#             if potential_subdir_path not in sys.path:
#                 sys.path.insert(0, potential_subdir_path)
#                 print(f"Added to sys.path: {potential_subdir_path}") # For debugging
# else:
#     print(f"Warning: Directory not found - {masked_hls_src_dir}", file=sys.stderr)

# # 3. Add specific deeper paths known to cause issues
# # For the current error: MaskedHLS_LP/src/RegBalancer/src/
# regbalancer_specific_path = os.path.join(masked_hls_src_dir, 'RegBalancer', 'src')
# if os.path.isdir(regbalancer_specific_path): # Check if it actually exists
#     paths_to_add.append(regbalancer_specific_path)
# else:
#     print(f"Warning: Specific RegBalancer path not found - {regbalancer_specific_path}", file=sys.stderr)

# # Add all collected paths to sys.path (prepending for priority)
# for path_to_add in reversed(paths_to_add): # Reversed to maintain insert(0) effective order
#     if path_to_add not in sys.path:
#         sys.path.insert(0, path_to_add)
#         print(f"Added to sys.path: {path_to_add}") # For debugging

import sys
import os
import re
import glob # For finding directories

# Get the directory of the current script (MTP_Tetris/)
project_root = os.path.dirname(os.path.abspath(__file__))

# Path to the MaskedHLS_LP/src/ directory
masked_hls_src_dir = os.path.join(project_root, 'MaskedHLS_LP', 'src')

# --- Paths to add to sys.path ---
paths_to_add = []

# 1. Add the MaskedHLS_LP/src/ directory itself
paths_to_add.append(masked_hls_src_dir)

# 2. Add all immediate subdirectories of MaskedHLS_LP/src/
if os.path.isdir(masked_hls_src_dir):
    for entry_name in os.listdir(masked_hls_src_dir):
        potential_subdir_path = os.path.join(masked_hls_src_dir, entry_name)
        if os.path.isdir(potential_subdir_path) and not entry_name.startswith('.') and not entry_name == '__pycache__':
            paths_to_add.append(potential_subdir_path)
else:
    print(f"Warning: Directory not found - {masked_hls_src_dir}", file=sys.stderr)

# 3. Add specific deeper paths known to cause issues
# For the current error: MaskedHLS_LP/src/RegBalancer/src/
regbalancer_specific_path = os.path.join(masked_hls_src_dir, 'RegBalancer', 'src')
if os.path.isdir(regbalancer_specific_path): # Check if it actually exists
    paths_to_add.append(regbalancer_specific_path)
else:
    print(f"Warning: Specific RegBalancer path not found - {regbalancer_specific_path}", file=sys.stderr)

# Add all collected paths to sys.path (prepending for priority)
for path_to_add in reversed(paths_to_add): # Reversed to maintain insert(0) effective order
    if path_to_add not in sys.path:
        sys.path.insert(0, path_to_add)
        # print(f"Added to sys.path: {path_to_add}") # For debugging


from pycparser import parse_file, c_ast, c_generator
from TACGenerator.TAC import TACStyleASTBuilder
from ANDCloud.and_cloud import AndCloudGenerator, AndXorCloudGenerator
from PIL import Image
from IPython.display import display
import subprocess
import json

from Gadgets import base, HPC2, HPC1, HPC3, COMAR, Domand, HPC2o, HPC3o

# 1. Convert the file into TAC
def convert_to_TAC(CFile_path):
    """
    Parses C code and writes corresponding TAC.
    """
    print(f"[INFO] : Transforming input file to TAC ...")

    ast = parse_file(CFile_path, use_cpp=True)  # Enable C preprocessor for better handling of complex C code

    tac_gen = TACStyleASTBuilder()
    for i, ext in enumerate(ast.ext):
        if isinstance(ext, c_ast.FuncDef):
            ast.ext[i] = tac_gen.transform(ext)

    gen = c_generator.CGenerator()

    # output_path = r"./TestFiles/TAC_files"
    # output_path = os.path.join(output_path, "output.c")
    output_path = os.path.abspath(r"./TestFiles/TAC_files/output.c")
    
    os.makedirs(os.path.dirname(output_path), exist_ok=True)

    with open(output_path, 'w') as f:
        code = gen.visit(ast)
        f.write(code)

    print(f"[INFO] : TAC output written to {output_path}\n")

# # 2. Inline C-file
def run_inliner(input_file, top_module, script_path="./MaskedHLS_LP/src"):

    """
    Writes systemArgs.json and runs the inliner script.
    
    Parameters:
    - input_file: path to the input C file
    - top_module: the top-level function to inline
    - script_path: the Python script that runs mainInline (default: 'inliner.py')
    """
    script_abs_path = os.path.abspath(script_path)
    # script_dir = os.path.dirname(script_abs_path) # 
    
    
    print(f"[INFO] : Inlining the TAC file ...")
    relative_inliner_output_path = os.path.join("TestFiles", "inlined_output", "output.c")
    args = {
        "inputFile": input_file,
        "inlinerOutput": os.path.abspath(relative_inliner_output_path),
        "topModule": top_module,
        "turn":1
    }

    # Write systemArgs.json
    with open('./MaskedHLS_LP/src/systemArgs.json', "w") as f:
        json.dump(args, f, indent=4)

    print(f"[INFO] : systemArgs.json written:")
    print(json.dumps(args, indent=4))
    print()

    # Run the inliner script
    print(f"[INFO] : Subprocess CWD will be: {script_abs_path}")
    try:
        result = subprocess.run(
            ["python", './Inliner/inliner.py'],
            check=True,
            # capture_output=True,
            text=True,
            cwd=script_abs_path
        )
        print(f"[INFO] : Inlined file written to {os.path.abspath('./TestFiles/inlined_output/output.c')}\n")
        # print("[INFO] Inliner Output:\n", result.stdout)
    except subprocess.CalledProcessError as e:
        print("[ERROR] Inliner script failed:\n", e.stderr)



# def run_maskedHLS(top_module, input_file, rtl_file, bit_width,script_path="./MaskedHLS_LP/src/script.py"):
#     """
#         @param top_module: top function of the file 
#         @param input_file: input_file is the for which verilog need to be generated
#         @param rltFile: name of the file where verilog need to be saved
#         @param bit_width: sepicfy the bit width of the design 
#     """
#     script_abs_path = os.path.abspath(script_path)
#     # resolve script path to absolute path
#     script_dir = os.path.dirname(script_abs_path)
#     # print(f"script path : {script_dir}")

#     # input_file_abs = os.path.abspath(input_file)
#     # print(f"input_file :{input_file}")


#     # rtl_file_abs = os.path.abspath(f"./Gadgets/gadget_verilog/{rtl_file}")
#     # print(f"rtl_file : {rtl_file_abs}")

#     command =[
#         "python3",
#         "script.py",
#         f"--topModule={top_module}",
#         f"--inputFile={input_file}",
#         f"--rtlFile={rtl_file}",
#         f"--bitWidth={bit_width}"
#     ]

#     print("[INFO] : Running Commnad: ", " ".join(command))
#     # print(f"[INFO] : Suprocess CWD will be : {script_dir}")
#     try:
#         result = subprocess.run(command, check=True, capture_output=True, text=True, cwd=script_dir)
#         print("[INFO] Script output:\n", result.stdout)

#         # extracting the latency of the design 
#         import re
#         match = re.search(r"Max path weight\s*(\d+)", result.stdout)
#         if match:
#             latency = int(match.group(1))
#             # print(f"[INFO] : Latency of the design: {latency}")
            
#         else:
#             print("[WARNING] : Latency not found in script output.")


#     except subprocess.CalledProcessError as e:
#         print("[ERROR] : Script failed:\n", e.stderr)
#         print("[ERROR] : stdout (if any):\n", e.stdout) # Print stdout too, it might have clues
#     except FileNotFoundError:
#         print(f"[ERROR] : Python interpreter or script '{script_abs_path}' not found. Check paths.")

#     return latency if latency else None

# ----------------------------------------------------------------------------------------------#
def run_hpc2optimization(top_module, input_file, rtl_file, bit_width, mode, script_path="./MaskedHLS_LP/src/script.py"):
    """
        @param top_module: top function of the file 
        @param input_file: input_file is the for which verilog need to be generated
        @param rtl_file: name of the file where verilog need to be saved
        @param bit_width: specify the bit width of the design 
    """
    script_abs_path = os.path.abspath(script_path)
    script_dir = os.path.dirname(script_abs_path)

    command = [
        "python3",               # Use python3 explicitly
        "script.py",
        f"--topModule={top_module}",
        f"--inputFile={input_file}",
        f"--rtlFile={rtl_file}",
        f"--bitWidth={bit_width}",
        f"--mode={mode}"
    ]

    latency = None  # Ensure it's defined
    print("[INFO] : Running Command:", " ".join(command))

    try:
        result = subprocess.run(
            command,
            check=True,
            capture_output=True,
            text=True,
            cwd=script_dir
        )
        stdout = result.stdout
        stderr = result.stderr

        print("[INFO] Script output:\n", stdout)
        if stderr.strip():
            print("[WARNING] Script stderr:\n", stderr)

        # Extract latency
        match = re.search(r"Max path weight\s*(\d+)", stdout)
        if match:
            latency = int(match.group(1))
            print(f"[INFO] : Latency of the design: {latency}")
        else:
            print("[WARNING] : Latency not found in script output.")

    except subprocess.CalledProcessError as e:
        print("[ERROR] : Script failed with exit code", e.returncode)
        print("[ERROR] : stdout:\n", e.stdout)
        print("[ERROR] : stderr:\n", e.stderr)
        stdout = e.stdout
        latency = None
    except FileNotFoundError:
        print(f"[ERROR] : Python interpreter or script '{script_abs_path}' not found. Check paths.")
        stdout = ""
        latency = None

    return latency, stdout
# ----------------------------------------------------------------------------------------#


##########################################################################################################################################################################
def run_maskedHLS(top_module, input_file, rtl_file, bit_width, script_path="./MaskedHLS_LP/src/script.py"):
    """
        @param top_module: top function of the file 
        @param input_file: input_file is the for which verilog need to be generated
        @param rtl_file: name of the file where verilog need to be saved
        @param bit_width: specify the bit width of the design 
    """
    script_abs_path = os.path.abspath(script_path)
    script_dir = os.path.dirname(script_abs_path)

    command = [
        "python3",               # Use python3 explicitly
        "script.py",
        f"--topModule={top_module}",
        f"--inputFile={input_file}",
        f"--rtlFile={rtl_file}",
        f"--bitWidth={bit_width}"
    ]

    latency = None  # Ensure it's defined
    print("[INFO] : Running Command:", " ".join(command))

    try:
        result = subprocess.run(
            command,
            check=True,
            capture_output=True,
            text=True,
            cwd=script_dir
        )
        stdout = result.stdout
        stderr = result.stderr

        print("[INFO] Script output:\n", stdout)
        if stderr.strip():
            print("[WARNING] Script stderr:\n", stderr)

        # Extract latency
        match = re.search(r"Max path weight\s*(\d+)", stdout)
        if match:
            latency = int(match.group(1))
            print(f"[INFO] : Latency of the design: {latency}")
        else:
            print("[WARNING] : Latency not found in script output.")

    except subprocess.CalledProcessError as e:
        print("[ERROR] : Script failed with exit code", e.returncode)
        print("[ERROR] : stdout:\n", e.stdout)
        print("[ERROR] : stderr:\n", e.stderr)
        stdout = e.stdout
        latency = None
    except FileNotFoundError:
        print(f"[ERROR] : Python interpreter or script '{script_abs_path}' not found. Check paths.")
        stdout = ""
        latency = None

    return latency, stdout
###############################################################################################################################################################


# 3. generate and_tree 
def generator_and_xor_cloud(filename):
    print(f"[INFO] : Generating the AND_Xor tree ...")
    and_xor_cloud = AndXorCloudGenerator()
    ast = parse_file(filename, use_cpp=True)
    and_xor_cloud.visit(ast)
    # and_xor_cloud.print_data()

    print(f"[INFO] : Number of node in the tree :{and_xor_cloud.graph.num_nodes()}")
    and_xor_cloud.save_and_tree(filename="and_xor_cloud.png")
    and_xor_cloud.save_and_xor_graph(filename="and_xor_graph.png")

    # Load and display image
    # output_folder = r".\ANDCloud\AND_tree"
    # sys.path.append(output_folder)
            
    # image_path = os.path.join(output_folder, f"and_xor_cloud.png")
    # image = Image.open(image_path)  # Change to your image path
    # display(image)
    return and_xor_cloud

def generator_and_cloud(filename):
    print(f"[INFO] : Generating the AND tree ...")
    and_cloud = AndCloudGenerator()
    ast = parse_file(filename, use_cpp=True)
    and_cloud.visit(ast)
    # and_cloud.print_data()

    print(f"[INFO] : Number of node in the tree :{and_cloud.graph.num_nodes()}")
    and_cloud.save_and_tree(filename=filename)

    # Load and display image
    # output_folder = r".\ANDCloud\AND_tree"
    # sys.path.append(output_folder)
            
    # image_path = os.path.join(output_folder, f"and_cloud.png")
    # image = Image.open(image_path)  # Change to your image path
    # display(image)
    return and_cloud
# 4. generate the gadget definition for nth order security 

# 5. run mlrc & mrlc to get the optimal gadget placement 
import time
from DSE_algorithm.dse import DSE
from DSE_algorithm.mrlc import MRLC
from DSE_algorithm.mlrc import MLRC

def run_mrlc_test(latency_target, d, and_cloud, gadget_map):
    run_mrlc = MRLC(d=d, and_tree=and_cloud, gadget_map=gadget_map)
    
    start_time = time.perf_counter()
    run_mrlc.mrlc_dp(latency_target)
    end_time = time.perf_counter()

    execution_time = end_time - start_time
    gadget_mapping = run_mrlc.get_gadget_definition()
# 
    # run_mrlc.print_gadget_definition()
    # print(run_mrlc.get_unique_gadgets_definition())

    print(f"[INFO] : MRLC FINISH PROCESSING in {execution_time}s.")
    
    return run_mrlc.get_unique_gadgets_definition(), gadget_mapping

def run_mlrc_test(randomess_target, d, and_cloud, gadget_map):
    run_mlrc = MLRC(d=d, and_tree=and_cloud, gadget_map=gadget_map)
    
    start_time = time.perf_counter()
    run_mlrc.mlrc(randomess_target)
    end_time = time.perf_counter()

    execution_time = end_time - start_time
    gadget_mapping = run_mlrc.get_gadget_definition()
# 
    # run_mlrc.print_gadget_definition()
    # print(run_mlrc.get_unique_gadgets_definition())

    print(f"[INFO] : MLRC FINISH PROCESSING in {execution_time}s.")
    
    return run_mlrc.get_unique_gadgets_definition(), gadget_mapping



# 6. replace the AND operation with gadget definition and save it into the file 
# 7. pass this file into maskedHLS
# from DSE_algorithm.mrlc import MRLC
from tabulate import tabulate
import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run TAC conversion and inliner.")
    parser.add_argument("--input_file", help="Path to input C file")
    parser.add_argument("--top_module", help="Top-level function name for inliner")
    parser.add_argument("--security_order",type=int,  help="Security order of the design")
    parser.add_argument("--latency", type=int, help="Maximum possible latency of the design")
    parser.add_argument("--randomness", type=int, help="Maximum possible randomness of the design")

    args = parser.parse_args()

    convert_to_TAC(args.input_file)
    file = os.path.abspath('./TestFiles/TAC_files/output.c')

    
    # # inline the tac 
    run_inliner(file, args.top_module)
    # print(f"[INFO] Inlining TAC file")
    # print(f"[IN]")

    # # use the inlined file to generate and cloud
    file = os.path.abspath('./TestFiles/inlined_output/output.c')

    # # get the and tree this will be use to find the optimal gadget placement 
    and_tree = generator_and_cloud(file)
    print()
    # # generate Gadget definition 
    # # if the table does not have entry for dth order
    
    # declare the DSE
    d = args.security_order

    # use sql lite for the table
    import sqlite3
    # create db if does not exist
    print(f"[INFO] : Connecting Database ... ")
    conn = sqlite3.connect('gadget_info.db')
    conn.execute("PRAGMA foregin_keys = ON")

    # cursor to query the database
    cur = conn.cursor()

    """
        gadget
        +----------------+
        | security order |
        +----------------+

        HPC1
        +--+---------+-----------+------+
        |d | latency | randomness| area |
        +--+---------+-----------+------+

        HPC2
        +--+---------+-----------+------+
        |d | latency | randomness| area |
        +--+---------+-----------+------+

        HPC3
        +--+---------+-----------+------+
        |d | latency | randomness| area |
        +--+---------+-----------+------+

        Comar
        +--+---------+-----------+------+
        |d | latency | randomness| area |
        +--+---------+-----------+------+
        
    """
    # create central gadget tabel
    cur.execute('''
        CREATE TABLE IF NOT EXISTS gadget(
            d INTEGER PRIMARY KEY
                )
    ''')
    for table in ["hpc1", "hpc2", "hpc2_swapped", "hpc3", "hpc3_swapped", "comar", "domand", "hpc2o", "hpc2o_swapped", "hpc3o", "hpc3o_swapped"]:
        cur.execute(f'''
            CREATE TABLE IF NOT EXISTS {table}(
                d INTEGER PRIMARY KEY,
                latency INTEGER,
                randomness INTEGER,
                area REAL,
                FOREIGN KEY (d) REFERENCES gadget(d) ON DELETE CASCADE
            )
        ''')

    # cur.execute(f"DELETE FROM gadget WHERE d = ?",(1,))
    # cur.execute(f"SELECT * FROM gadget WHERE d = ?", (1,))
    # if cur.fetchone() is None:
        
    #     cur.execute("INSERT INTO gadget (d) VALUES (?)", (1,))
        
    #     cur.execute("INSERT INTO hpc1 (d, latency, randomness, area) VALUES (?, ?, ?, ?)", (1, 2, 2, 1))

    #     cur.execute("INSERT INTO hpc2 (d, latency, randomness, area) VALUES (?, ?, ?, ?)",(1, 2, 1, 2))

    #     cur.execute("INSERT INTO hpc3 (d, latency, randomness, area) VALUES (?, ?, ?, ?)",(1, 1, 2, 3))

    #     cur.execute("INSERT INTO comar (d, latency, randomness, area) VALUES (?, ?, ?, ?)",(1, 2, 6, 4))

    cur.execute(f"SELECT * FROM gadget WHERE d = {d}")
    row = cur.fetchone()
    print(f"[INFO] : row {row}")


    # check the contents of the tabes in the database
    print("[INFO] : Gadget Table Contents:")

    tables = ["gadget", "hpc1", "hpc2", "hpc2_swapped", "hpc3", "hpc3_swapped", "comar", "domand", "hpc2o", "hpc2o_swapped", "hpc3o", "hpc3o_swapped"]

    for x in [1, 2, 3]:
        cur.execute(f"INSERT OR IGNORE INTO gadget (d) VALUES (?)", (x,))
    
    # data = {
    #     'hpc1' : [(1,2,2,329.839989),(2,2,5,606.479980),(3,2,9,1021.439966)],
    #     'hpc2' :[(1,2,1,589.987981),(2,2,3,1279.991959),(3,2,6,2233.335929)],
    #     'hpc3' : [(1,1,2,452.465985),(2,1,6,971.165968),(3,1,12,1682.715945 )],
    #     'comar' : [(1,2,6,746.927975)],
    #     'domand' : [(1,1,1,253.231992),(2,1,3,651.167979),(3,1,6,868.223972)],
    # }


    # data = {
    #     'hpc1' : [(1,2,2,3),(2,2,5,6),(3,2,9,10),(4,2,14,15),(5,2,20,21)],
    #     'hpc2' :[(1,2,1,5),(2,2,3,12),(3,2,6,22),(4,2,10,35),(5,2,15,50)],
    #     'hpc3' : [(1,1,2,4),(2,1,6,9),(3,1,12,16),(4,1,20,25),(5,1,30,36)],
    #     'comar' : [(1,2,6,7)],
    #     'domand' : [(1,1,1,2),(2,1,3,6),(3,1,6,8)],
    #     'hpc2o' : [(1,2,1,5),(2,2,3,12),(3,2,6,22),(4,2,10,30),(5,2,15,45)],   # same latency as hpc2, lower randomness
    #     'hpc3o' : [(1,1,2,6),(2,1,6,14),(3,1,12,25),(4,1,20,20),(5,1,30,30)]  # you can tune these values later
    # }

    data = {
    'hpc1' : [(1, 2, 2, 50.7), (2, 2, 5, 127), (3, 2, 9, 217.3), (4, 2, 14, 325), (5, 2, 20, 21)],
    'hpc2' : [(1, 2, 1, 79.26), (2, 2, 3, 193.9), (3, 2, 6, 358.56), (4, 2, 10, 573.23), (5, 2, 15, 50)],
    'hpc2_swapped' : [(1, 2, 1, 79.26), (2, 2, 3, 193.9), (3, 2, 6, 358.56), (4, 2, 10, 573.23), (5, 2, 15, 50)],
    'hpc3' : [(1, 1, 2, 55.32), (2, 1, 6, 134.06), (3, 1, 12, 246.84), (4, 1, 20, 393.68), (5, 1, 30, 36)],
    'hpc3_swapped' : [(1, 1, 2, 55.32), (2, 1, 6, 134.06), (3, 1, 12, 246.84), (4, 1, 20, 393.68), (5, 1, 30, 36)],
    'comar' : [(1, 2, 6, 7)],
    'domand' : [(1, 1, 1, 2), (2, 1, 3, 6), (3, 1, 6, 8)],
    'hpc2o' : [(1, 2, 1, 60.64), (2, 2, 3, 163.85), (3, 2, 6, 315.47), (4, 2, 10, 515.50), (5, 2, 15, 45)],
    'hpc2o_swapped' : [(1, 2, 1, 60.64), (2, 2, 3, 163.85), (3, 2, 6, 315.47), (4, 2, 10, 515.50), (5, 2, 15, 45)],
    'hpc3o' : [(1, 1, 2, 43.09), (2, 1, 6, 115.71), (3, 1, 12, 222.37), (4, 1, 20, 363.09), (5, 1, 30, 30)],
    'hpc3o_swapped' : [(1, 1, 2, 43.09), (2, 1, 6, 115.71), (3, 1, 12, 222.37), (4, 1, 20, 363.09), (5, 1, 30, 30)]
    }


    for current_table_name, entries in data.items():
        for entry_d, entry_latency, entry_randomness, entry_area in entries:
            # print(f"[DEBUG] Processing {current_table_name}: d={entry_d}") # Uncomment for very verbose
            try:
                cur.execute(f"""
                    INSERT INTO {current_table_name} (d, latency, randomness, area)
                    VALUES (?, ?, ?, ?)
                    ON CONFLICT(d) DO UPDATE SET
                        latency = excluded.latency,
                        randomness = excluded.randomness,
                        area = excluded.area
                """, (entry_d, entry_latency, entry_randomness, entry_area))
            except sqlite3.Error as e: # Catch generic sqlite3.Error
                print(f"SQLite error while processing {current_table_name} for d={entry_d}: {e}")
                # If it's an operational error about ON CONFLICT again, print schema
                if "ON CONFLICT clause does not match" in str(e):
                    print(f"Schema for {current_table_name} (from PRAGMA table_info):")
                    cur.execute(f"PRAGMA table_info({current_table_name});")
                    for row_info in cur.fetchall():
                        print(row_info)
                raise # Re-raise to stop execution if there's an issue
    conn.commit() # Commit all data inserts/updates
            

    print(f"\n\n[INFO] : Displaying the contents of Tables...")
    for table in tables:
        print(f"\nTable: {table}")
        # cur.execute(f"DELETE FROM {table}")
        cur.execute(f"SELECT * FROM {table}")

        column_names = [description[0] for description in cur.description]
 
        rows = cur.fetchall()
        if rows:
            print(tabulate(rows, headers=column_names, tablefmt="grid"))
        else:
            print("[INFO] : NO data in this table")
        
    conn.commit()
    # conn.close()
    
    # if row is not none fetch the values form table
    # if row is none call the gadget definition and populate the row of table

 
    if row is None:
        print("[INFO] : Generating gadget definition..")
        
        # generate gadget definition 
        HPC2_obj = HPC2(d=d)
        HPC2_obj.generate_and_write_function(HPC2_obj, filename_prefix="HPC2")
        # create object of HPC2 and get randomness.
        randomness_HPC2 = HPC2_obj.get_random_count()
        print(f"[INFO] : Randomness of HPC2: {randomness_HPC2}")
        
        HPC1_obj = HPC1(d=d)
        HPC1_obj.generate_and_write_function(HPC1_obj, filename_prefix="HPC1")
        randomness_HPC1 = HPC1_obj.get_random_count()
        print(f"[INFO] : Randomness of HPC1: {randomness_HPC1}")
        
        HPC3_obj = HPC3(d=d)
        HPC3_obj.generate_and_write_function(HPC3_obj, filename_prefix="HPC3")
        randomness_HPC3 = HPC3_obj.get_random_count()
        print(f"[INFO] : Randomness of HPC3: {randomness_HPC3}")

        COMAR_obj = COMAR()
        COMAR_obj.generate_and_write_function(COMAR_obj, filename_prefix="Comar")
        randomness_COMAR = COMAR_obj.get_random_count()
        print(f"[INFO] : Randomness of COMAR: {randomness_COMAR}")
        
        Domand_obj = Domand(d=d)
        Domand_obj.generate_and_write_function(Domand_obj, filename_prefix="Domand")
        randomness_Domand = Domand_obj.get_random_count()
        print(f"[INFO] : Randomness of Domand: {randomness_Domand}")

        HPC2o_obj = HPC2o(d=d)
        HPC2o_obj.generate_and_write_function(HPC2o_obj, filename_prefix="HPC2o")
        randomness_HPC2o = HPC2o_obj.get_random_count()
        print(f"[INFO] : Randomness of HPC2o: {randomness_HPC2o}")

        HPC3o_obj = HPC3o(d=d)
        HPC3o_obj.generate_and_write_function(HPC3o_obj, filename_prefix="HPC3o")
        randomness_HPC3o = HPC3o_obj.get_random_count()
        print(f"[INFO] : Randomness of HPC3o: {randomness_HPC3o}")

        print(f"[INFO] : Gadget Definition written to {os.path.abspath('./Gadgets/gadget_output')}\n")
        # # pass the generated c files into the masked HLS to get verilog 
        folder_path = os.path.abspath(r"./Gadgets/gadget_output")

        for filename in os.listdir(folder_path):
            print()
            print(f"[INFO] : filename : {filename}")
            top_module = filename.replace("_generated.c","") 

            rtl_file = filename.replace(".c", ".v")
            filename= os.path.abspath(f"./Gadgets/gadget_output/{filename}")
            #print(f"filename {filename}")
            latnecy = run_maskedHLS(top_module=top_module,input_file=filename, rtl_file=rtl_file,bit_width=8)
            if latnecy is not None:
                print(f"[INFO] : Latency of the design: {latnecy}")
            # call design compiler to get the area and latency of the design
            # latnecy and rnadomness is already with us just need area
            # add to the tabel
            
    
    
    # # populate the dse map 
    
    gadget_specs = {}
    # gadget_list = ["comar", "hpc1", "hpc2", "hpc3", "domand" ] if d == 1 else ["hpc1", "hpc2", "hpc3", "domand"]
    # gadget_list = ["comar", "hpc1", "hpc2", "hpc3" ] if d == 1 else ["hpc1", "hpc2", "hpc3"]
    gadget_list = ["comar", "hpc1", "hpc2", "hpc3", "hpc2o", "hpc3o",
                   "hpc2_swapped", "hpc2o_swapped"]
    for gadget in gadget_list:
        table = gadget.lower()
        # print(f"[INFO] : d value while populating the map : {d}")
        cur.execute(f"SELECT * FROM {table} WHERE d = ?", (d,))
        row = cur.fetchone()

        if row:
            gadget_specs[gadget] = {
                "latency": row[1],
                "randomness": row[2],
                "area": row[3]
            }
        else:
            print(f"[WARN] No entry for {gadget} with d = {d}")
    if gadget_specs:
        table_data =[]
        for gadget, values in gadget_specs.items():
            table_data.append([gadget, values['latency'], values['randomness'], values['area']])
        print(f"\n[INFO]: Populated DSE MAP for {d} order")
    
        from tabulate import tabulate
        print(tabulate(table_data, headers=["Gadget", "Latency", "randomness","area"], tablefmt="grid"))

    # DSE.set_gadget_specs(gadget_specs)
    # print(f"DSE.GADGET_gadget_specs :\n {DSE.GADGET_gadget_specs}")
    conn.commit()


    # # create table ..

    
    # # pass these verilog file to design compiler 
    # # get the area latency 
    # # get the randomness 
    # # store these values into the table

    if args.latency is None and args.randomness is None:
        parser.error("[ERROR] : At least one of --latency or --randomness must be provided.")
    from transform_CFile.ctransfromer import ShareTransformer

    if args.latency is not None:
        # run mrlc
    
        print("[INFO] : Running MRLC for optimal gadget placement.")
        unique_def, gadget_mapping = run_mrlc_test(latency_target=args.latency, d=d, and_cloud=and_tree, gadget_map=gadget_specs)
        print("[INFO] : printing the unique definitions")
        # print(unique_def)
        
        inlined_file = r"./TestFiles/inlined_output/output.c"
        ast = parse_file(inlined_file, use_cpp=True)

        shareTransformer = ShareTransformer(d+1, gadget_mapping, unique_def)
        transformed_ast = shareTransformer.transform(ast)

        gen = c_generator.CGenerator()

        # output_path = r"./TestFiles/TAC_files"
        # output_path = os.path.join(output_path, "output.c")
        output_path = os.path.abspath(r"./TestFiles/share_output/output.c")
        
        os.makedirs(os.path.dirname(output_path), exist_ok=True)

        with open(output_path, 'w') as f:
            code = gen.visit(ast)
            f.write(code)

        print(f"[INFO] : shared output written to {output_path}\n")

        # pass the shared output to maskedHLS
        input_file = os.path.abspath("./TestFiles/share_output/output.c")
        print(f"input file for maskedHLS : {input_file}")

        latency = run_maskedHLS(top_module=args.top_module, input_file=input_file, rtl_file='nupur.v', bit_width=8)

        

    else:
        print("[INFO] : Running MLRC for optimal gadget placement.")
        
        unique_def, gadget_mapping = run_mlrc_test(randomess_target=args.randomness, d=d, and_cloud=and_tree,gadget_map=gadget_specs)
        print("[INFO] : printing the unique definitions")
        # print(unique_def)
        
        inlined_file = r"./TestFiles/inlined_output/output.c"
        ast = parse_file(inlined_file, use_cpp=True)

        shareTransformer = ShareTransformer(d+1, gadget_mapping, unique_def)
        transformed_ast = shareTransformer.transform(ast)

        gen = c_generator.CGenerator()

        # output_path = r"./TestFiles/TAC_files"
        # output_path = os.path.join(output_path, "output.c")
        output_path = os.path.abspath(r"./TestFiles/share_output/output.c")
        
        os.makedirs(os.path.dirname(output_path), exist_ok=True)

        with open(output_path, 'w') as f:
            code = gen.visit(ast)
            f.write(code)

        print(f"[INFO] : shared output written to {output_path}\n")

        input_file = os.path.abspath("./TestFiles/share_output/output.c")
        print(f"input file for maskedHLS : {input_file}")

        latency = run_maskedHLS(top_module=args.top_module, input_file=input_file, rtl_file='test.v', bit_width=8)


    # # use the unique definition to replace the expression with gadget definition 
    
    # # run maskedHLS on the design

from find_swaps import apply_hpc2_swaps

def run_dse_pipeline(input_file, output_file, optimize_hpc=True):
    """
    Run the complete DSE pipeline with optional HPC2 gadget optimization.
    
    Parameters:
    -----------
    input_file : str
        Path to input C file
    output_file : str
        Path to output C file
    optimize_hpc : bool
        If True, apply HPC2 gadget optimization after main processing
    """
    # Your existing DSE pipeline code here
    pass


def optimize_gadgets_after_dse(c_file_path):
    """
    Apply HPC2/HPC2o gadget optimization to a C file.
    Converts HPC3/HPC3o calls to HPC2/HPC2o when arrival depths differ by >= 1.
    
    Parameters:
    -----------
    c_file_path : str
        Path to the C file to optimize (modified in-place)
    """
    print(f"\n[GADGET_OPT] Starting HPC gadget optimization on {c_file_path}")
    apply_hpc2_swaps(c_file_path, c_file_path)
    print("[GADGET_OPT] Gadget optimization complete.")

# Quick usage from main:
# if __name__ == "__main__":
#     # Run your normal DSE pipeline
#     # ... existing code ...
#     
#     # Then optimize gadgets
#     optimize_gadgets_after_dse("path/to/output.c")
