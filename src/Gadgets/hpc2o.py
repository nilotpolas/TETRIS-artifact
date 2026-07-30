from Gadgets import Gadget

# class HPC2o(Gadget):
#     def __init__(self, d):
#         super().__init__(d=d, random_required=0, latency=2, function_name="HPC2o")

    
#     def generate_multiply_function(self, var_a="a", var_b="b", var_w="w", var_c="c"):
#         """
#         input:  [a0, a1, ..., ad]
#                 [b0, b1, ..., bd]
#                 [w0, w1, ..., wd]
#         output: [c0, c1, ..., cd]
#         """
#         d = self.d
#         param_a = ", ".join([f"_Bool {var_a}{i}" for i in range(d + 1)])
#         param_b = ", ".join([f"_Bool {var_b}{i}" for i in range(d + 1)])
#         param_w = ", ".join([f"_Bool {var_w}{i}" for i in range(d + 1)])
#         param_c = ", ".join([f"_Bool * {var_c}{i}" for i in range(d + 1)])

#         param_rand_list = []
#         for i in range(d):
#             for j in range(i + 1, d + 1):
#                 param_rand_list.append(f"_Bool rand_{i}{j}")
#                 self.random_required += 1  # Increment the counter

#         param_rand = ", ".join(param_rand_list)  # Convert list to string

#         # Combine parameters into the function signature
#         if param_rand:
#             param_str = f"{param_a}, {param_b}, {param_w}, {param_c}, {param_rand}" 
#         else:
#             param_str = f"{param_a}, {param_b}, {param_w}, {param_c}"

#         self.latency = 2  # Set the latency for the HPC2o gadget
        
#         # Updated helper functions with hpc2o_same_shares logic
#         helper_func = f"""
# void hpc2o_same_shares_{d}_order(_Bool a_share, _Bool b_share, _Bool w_share, _Bool *u_share) {{
#     _Bool b_share_reg, temp;
#     b_share_reg = reg(b_share);
#     temp = a_share & b_share_reg;
#     *u_share = reg(w_share ^ temp);
# }}

# void hpc2_v_{d}_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand) {{
#     _Bool temp; 
#     temp = reg(b_share ^ rand);
#     *v_share = reg(temp & a_share);
# }}

# void hpc2_w_{d}_order(_Bool a_share, _Bool rand, _Bool *w_share) {{
#     _Bool rand_reg;
#     rand_reg = reg(rand);
#     _Bool a_neg;
#     a_neg = !a_share;
#     *w_share = reg(a_neg & rand_reg);
# }}

# void hpc2_xor_vw_{d}_order(_Bool v_share, _Bool w_share, _Bool *u_share) {{
#     *u_share = v_share ^ w_share;
# }}
# """
#         function_signature = f"void HPC2o({param_str})"
#         print(f"function signature for HPC2o \n {function_signature}")

#         # Store the function body lines
#         body_lines = []

#         # Generating declarations for u_ij, v_ij, and w_ij
#         body_lines.append(f"\t_Bool {', '.join([f'u{i}{j}' for i in range(d + 1) for j in range(d+1)])};\n") 
#         if d > 0: # Prevent empty declaration lines if d=0
#             body_lines.append(f"\t_Bool {', '.join([f'v{i}{j}' for i in range(d + 1) for j in range(d+1) if i != j])};\n")
#             body_lines.append(f"\t_Bool {', '.join([f'w{i}{j}' for i in range(d + 1) for j in range(d+1) if i != j])};\n\n")

#         # Generate core logic
#         for i in range(d + 1):
#             for j in range(d+1):
#                 if i == j:
#                     # Added w variable into the same shares function call
#                     body_lines.append(f"\thpc2o_same_shares_{d}_order({var_a}{i}, {var_b}{i}, {var_w}{i}, &u{i}{i});\n")
#                 if i != j:
#                     r_param = f"rand_{min(i, j)}{max(i, j)}"
#                     body_lines.append(f"\thpc2_v_{d}_order({var_a}{i}, {var_b}{j}, &v{i}{j}, {r_param});\n")
#                     body_lines.append(f"\thpc2_w_{d}_order({var_a}{i}, {r_param}, &w{i}{j});\n")
#                     body_lines.append(f"\thpc2_xor_vw_{d}_order(v{i}{j}, w{i}{j}, &u{i}{j});\n\n")

#         temp_var_counter = 1  
#         temp_vars = []  

#         # Allocate (d - 1) * (d + 1) temp variables for XORing
#         if d > 1:
#             total_temps = (d - 1) * (d + 1)
#             for _ in range(total_temps):
#                 temp_vars.append(f"t{temp_var_counter}")
#                 temp_var_counter += 1

#             # Declare all temp variables at once
#             body_lines.append("\t_Bool " + ", ".join(temp_vars) + ";\n\n")

#         temp_index = 0  

#         # Assign final values to c pointer shares
#         for i in range(d + 1):
#             if d == 1:
#                 body_lines.append(f"\t*{var_c}{i} = u{i}{0} ^ u{i}{1};\n")
#             elif d == 0:
#                 body_lines.append(f"\t*{var_c}{i} = u{i}{0};\n")
#             else:
#                 body_lines.append(f"\t{temp_vars[temp_index]} = u{i}{0} ^ u{i}{1};\n")

#                 for j in range(2, d):
#                     body_lines.append(f"\t{temp_vars[temp_index + 1]} = {temp_vars[temp_index]} ^ u{i}{j};\n")
#                     temp_index += 1  

#                 # Final XOR step directly assigns to *c{i}
#                 body_lines.append(f"\t*{var_c}{i} = {temp_vars[temp_index]} ^ u{i}{d};\n\n")
#                 temp_index += 1  

#         body_lines.append("}")
#         function_body = "{\n" + "".join(body_lines)
#         return helper_func + function_signature + "\n" + function_body








class HPC2o(Gadget):
    def __init__(self, d):
        super().__init__(d=d, random_required=0, latency=2, function_name="HPC2o")

    def generate_multiply_function(self, var_a="a", var_b="b", var_w="w", var_c="c"):
        """
        input:  [a0, a1, ..., ad]
                [b0, b1, ..., bd]
                [w0, w1, ..., wd]
        output: [c0, c1, ..., cd]
        """
        d = self.d
        shares = d + 1
        
        param_a = ", ".join([f"_Bool {var_a}{i}" for i in range(shares)])
        param_b = ", ".join([f"_Bool {var_b}{i}" for i in range(shares)])
        param_w = ", ".join([f"_Bool {var_w}{i}" for i in range(shares)])
        param_c = ", ".join([f"_Bool * {var_c}{i}" for i in range(shares)])

        param_rand_list = []
        for i in range(d):
            for j in range(i + 1, shares):
                param_rand_list.append(f"_Bool rand_{i}{j}")
                self.random_required += 1

        param_rand = ", ".join(param_rand_list)

        if param_rand:
            param_str = f"{param_a}, {param_b}, {param_w}, {param_c}, {param_rand}" 
        else:
            param_str = f"{param_a}, {param_b}, {param_w}, {param_c}"

        self.latency = 2  
        
        # Helper functions with PR registers removed, strict formatting, and new OR function
        helper_func = f"""
void hpc2o_first_half_{d}_order(_Bool a_share, _Bool b_share, _Bool w_share, _Bool rand, _Bool *out_share) {{
    _Bool temp_ab;
    _Bool a_neg;
    _Bool temp_ar;
    _Bool xor_step1;
    _Bool xor_step2;

    temp_ab = a_share & b_share;
    a_neg = !a_share;
    temp_ar = a_neg & rand;
    
    xor_step1 = w_share ^ temp_ab;
    xor_step2 = xor_step1 ^ temp_ar;
    
    *out_share = reg(xor_step2);
}}

void hpc2o_v_{d}_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand) {{
    _Bool xor_br;
    _Bool temp;
    _Bool and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br); // This remains an R register in Algo 6
    
    and_ta = temp & a_share;
    *v_share = reg(and_ta);
}}

void hpc2o_w_{d}_order(_Bool a_share, _Bool rand, _Bool *w_share) {{
    _Bool a_neg;
    _Bool and_ar;

    a_neg = !a_share;
    
    and_ar = a_neg & rand;
    *w_share = reg(and_ar);
}}

void hpc2o_xor_vw_{d}_order(_Bool v_share, _Bool w_share, _Bool *u_share) {{
    *u_share = v_share ^ w_share;
}}

void hpc2o_or_vw_{d}_order(_Bool v_share, _Bool w_share, _Bool *u_share) {{
    *u_share = v_share | w_share;
}}
"""
        function_signature = f"void HPC2o({param_str})"
        print(f"function signature for HPC2o \n {function_signature}")

        body_lines = []

        if d == 0:
            body_lines.append(f"\t_Bool w00;\n")
            body_lines.append(f"\thpc2o_first_half_0_order({var_a}0, {var_b}0, {var_w}0, 0, &w00);\n")
            body_lines.append(f"\t*{var_c}0 = w00;\n")
            body_lines.append("}")
            return helper_func + function_signature + "\n{\n" + "".join(body_lines)

        u_vars = [f'u{i}{j}' for i in range(shares) for j in range(shares) if i != j]
        v_vars = [f'v{i}{j}' for i in range(shares) for j in range(shares) if i != j]
        w_vars = [f'w{i}{j}' for i in range(shares) for j in range(shares) if i != j]
        
        body_lines.append(f"\t_Bool {', '.join(u_vars)};\n")
        body_lines.append(f"\t_Bool {', '.join(v_vars)};\n")
        body_lines.append(f"\t_Bool {', '.join(w_vars)};\n")

        temp_vars = []
        if shares > 2:
            total_temps = (shares - 2) * shares
            temp_vars = [f"t{k+1}" for k in range(total_temps)]
            if temp_vars:
                body_lines.append("\t_Bool " + ", ".join(temp_vars) + ";\n")
        
        body_lines.append("\n")

        for i in range(shares):
            j_i = 1 if i == 0 else 0 
            
            for j in range(shares):
                if i == j:
                    continue  
                
                r_param = f"rand_{min(i, j)}{max(i, j)}"
                
                if j == j_i:
                    body_lines.append(f"\thpc2o_first_half_{d}_order({var_a}{i}, {var_b}{i}, {var_w}{i}, {r_param}, &w{i}{j});\n")
                    body_lines.append(f"\thpc2o_v_{d}_order({var_a}{i}, {var_b}{j}, &v{i}{j}, {r_param});\n")
                    body_lines.append(f"\thpc2o_xor_vw_{d}_order(v{i}{j}, w{i}{j}, &u{i}{j});\n\n")
                else:
                    body_lines.append(f"\thpc2o_w_{d}_order({var_a}{i}, {r_param}, &w{i}{j});\n")
                    body_lines.append(f"\thpc2o_v_{d}_order({var_a}{i}, {var_b}{j}, &v{i}{j}, {r_param});\n")
                    body_lines.append(f"\thpc2o_or_vw_{d}_order(v{i}{j}, w{i}{j}, &u{i}{j});\n\n")

        temp_index = 0  

        for i in range(shares):
            u_list = [f"u{i}{j}" for j in range(shares) if i != j]
            
            if len(u_list) == 1:
                body_lines.append(f"\t*{var_c}{i} = {u_list[0]};\n")
            elif len(u_list) == 2:
                body_lines.append(f"\t*{var_c}{i} = {u_list[0]} ^ {u_list[1]};\n")
            else:
                body_lines.append(f"\t{temp_vars[temp_index]} = {u_list[0]} ^ {u_list[1]};\n")
                for k in range(2, len(u_list) - 1):
                    body_lines.append(f"\t{temp_vars[temp_index + 1]} = {temp_vars[temp_index]} ^ {u_list[k]};\n")
                    temp_index += 1  
                body_lines.append(f"\t*{var_c}{i} = {temp_vars[temp_index]} ^ {u_list[-1]};\n\n")
                temp_index += 1  

        body_lines.append("}")
        function_body = "{\n" + "".join(body_lines)
        return helper_func + function_signature + "\n" + function_body