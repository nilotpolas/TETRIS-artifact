# test_runner.py

# Import the HPC1 class from your hpc_generator.py file
from hpc2o_swapped import HPC2oSwapped

# --- Now we can actually use the class ---

# 1. Create an instance of the HPC1 generator.
#    Let's ask it to generate code for security order d=2 (which means d+1 = 3 shares).
print("--- Generating HPC1 for d=5 ---")
hpc_d2_generator = HPC2oSwapped(d=1)

# 2. Call the function to get the C code as a string
#    This is the main purpose of your class.
generated_c_code = hpc_d2_generator.generate_multiply_function()

# 3. Print the resulting C code to your terminal
print(generated_c_code)


# # You can even try another order, like d=1
# print("\n--- Generating HPC1 for d=5 ---")
# hpc_d1_generator = HPC1(d=1)
# print(hpc_d1_generator.generate_multiply_function())