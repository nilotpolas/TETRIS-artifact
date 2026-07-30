from Gadgets import Gadget

class HPC1(Gadget):
    """
    Implementation from Algorithm 1: https://tches.iacr.org/index.php/TCHES/article/view/11942/11802
    
    This script is corrected to properly generate the C code for d > 1
    by calculating and using the final intermediate random value r_d.
    """
    def __init__(self, d):
        """
        Initialise HPC1 with security order d (number of shares = d + 1)
        """
        # Note: The 'Gadgets' import might need to be 'base' depending on your file structure
        # (e.g., from base import Gadget)
        super().__init__(d=d, random_required=0, latency=2, function_name=f"HPC1")

    def generate_multiply_function(self, var_a="a", var_b="b", var_c="c"):
        """
        input:  [a0, a1, ..., ad]
                [b0, b1, ..., bd]
        output: [c0, c1, ..., cd]
        """
        d = self.d
        param_a = ", ".join([f"_Bool {var_a}{i}" for i in range(d + 1)])
        param_b = ", ".join([f"_Bool {var_b}{i}" for i in range(d + 1)])
        param_c = ", ".join([f"int* {var_c}{i}" for i in range(d + 1)])

        param_rand_list = [f"_Bool rand_{i}" for i in range(d)]
        param_prand_list = [f"_Bool prand_{i}{j}" for i in range(d) for j in range(i + 1, d + 1)]

        param_rand = ", ".join(param_rand_list)
        param_prand = ", ".join(param_prand_list)

        num_rand_vars = len(param_rand_list)
        num_prand_vars = len(param_prand_list)
        self.random_required = num_rand_vars + num_prand_vars
        self.latency = 2

        param_str = f"{param_a}, {param_b}, {param_c}"
        if param_rand:
            param_str += f", {param_rand}"
        if param_prand:
            param_str += f", {param_prand}"
        
        helper_func = f"""
void hpc1_same_shares_{d}_order(_Bool a_share, _Bool b_share, _Bool rand, _Bool * v_share) {{
    _Bool b_share_;
    b_share_ = reg(b_share ^ rand);
    *v_share  = a_share & b_share_;
}}

void hpc1_cross_domain_{d}_order(_Bool a_share, _Bool b_share, _Bool * v_share, _Bool rand, _Bool prand){{
    _Bool b_share_;
    b_share_ = reg(b_share ^ rand);
    _Bool a_and_b;
    a_and_b = a_share & b_share_;
    *v_share = a_and_b ^ prand;
}}
"""
        function_signature = f"void HPC1({param_str})"
        body_lines = []

        # Declare the v_ij variables
        body_lines.append(f"\t\t_Bool {', '.join([f'v{i}{j}' for i in range(d + 1) for j in range(d + 1)])};\n")

        # --- START OF FIX ---
        
        # Calculate the final intermediate random value, r_d = rand_0 ^ ... ^ rand_{d-1}
        # This is the crucial step that was missing.
        if d > 0:
            r_xor_terms = [f"rand_{i}" for i in range(d)]
            # Let the C compiler handle the chained XOR
            body_lines.append(f"\t\t_Bool r{d} = {' ^ '.join(r_xor_terms)};\n")

        # This loop generates the calls to hpc1_same_shares and hpc1_cross_domain
        for i in range(d + 1):
            for j in range(d + 1):
                
                # Determine which random parameter to use for b_j
                rand_parameter = ""
                if d == 0:
                    # d=0 is an edge case, has no rand inputs.
                    # The C helper still expects a 'rand' param, so we pass 0.
                    rand_parameter = "0" 
                elif j < d:
                    # For b_0 to b_{d-1}, use r_j (which is just rand_j)
                    rand_parameter = f"rand_{j}"
                else: # j == d
                    # For b_d, use r_d (which we calculated above)
                    rand_parameter = f"r{d}"

                if i == j:
                    body_lines.append(f"\t\thpc1_same_shares_{d}_order({var_a}{i}, {var_b}{i}, {rand_parameter}, &v{i}{i});\n")
                else:
                    prand_parameter = f"prand_{min(i, j)}{max(i, j)}"
                    body_lines.append(f"\t\thpc1_cross_domain_{d}_order({var_a}{i}, {var_b}{j}, &v{i}{j}, {rand_parameter}, {prand_parameter});\n")
        
        # --- END OF FIX ---


        # --- START OF MODIFICATION (Logic from Code 2) ---
        # This is your existing logic for chained-XOR outputs, which is correct.
        
        temp_vars_to_declare = []
        if d > 1:
            total_temps = (d + 1) * (d - 1)
            for i in range(total_temps):
                temp_vars_to_declare.append(f"t{i}")
            
            if temp_vars_to_declare:
                 body_lines.append(f"\n\t\t_Bool {', '.join(temp_vars_to_declare)};\n\n")

        temp_index = 0 

        for i in range(d + 1):
            if d == 0:
                body_lines.append(f"\t\t*{var_c}{i} = reg(v{i}{0});\n")
            elif d == 1:
                body_lines.append(f"\t\t*{var_c}{i} = reg(v{i}{0} ^ v{i}{1});\n")
            else:
                current_temp_var = temp_vars_to_declare[temp_index]
                body_lines.append(f"\t\t{current_temp_var} = v{i}{0} ^ v{i}{1};\n")
                temp_index += 1

                for j in range(2, d): # Loops from v{i}{2} up to v{i}{d-1}
                    next_temp_var = temp_vars_to_declare[temp_index]
                    body_lines.append(f"\t\t{next_temp_var} = {current_temp_var} ^ v{i}{j};\n")
                    current_temp_var = next_temp_var 
                    temp_index += 1

                body_lines.append(f"\t\t*{var_c}{i} = reg({current_temp_var} ^ v{i}{d});\n\n")

        # --- END OF MODIFICATION ---

        body_lines.append("}")
        full_body = "".join(body_lines)
        return f"{helper_func}\n{function_signature}{{\n{full_body}"

# Example of how to run this script (as a 'test_runner.py' file)
if __name__ == "__main__":
    
    # This check is needed because the Gadget class is abstract
    # We need to provide a dummy implementation for this file to be runnable
    # In your real code, you'd import from 'base.py'
    try:
        from Gadgets import Gadget
    except ImportError:
        print("Warning: 'Gadgets' module not found. Using dummy class for testing.")
        from abc import ABC, abstractmethod
        class Gadget(ABC):
            def __init__(self, d, random_required, latency, function_name):
                self.d = d
            @abstractmethod
            def generate_multiply_function(self): pass

    print("--- Generating HPC1 for d=5 ---")
    hpc_d5_generator = HPC1(d=5)
    generated_c_code = hpc_d5_generator.generate_multiply_function()
    print(generated_c_code)
    
    print("\n--- Generating HPC1 for d=1 ---")
    hpc_d1_generator = HPC1(d=1)
    print(hpc_d1_generator.generate_multiply_function())
