from Gadgets import Gadget
class HPC3o(Gadget):
    def __init__(self, d):
        super().__init__(d=d, random_required=0, latency=2, function_name="HPC3o")

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
        param_rand_prime_list = []
        
        # HPC3o requires two independent random bits per share pair (r_ij and r'_ij)
        for i in range(shares):
            for j in range(i + 1, shares):
                param_rand_list.append(f"_Bool rand_{i}{j}")
                param_rand_prime_list.append(f"_Bool rand_prime_{i}{j}")
                self.random_required += 2

        param_rand = ", ".join(param_rand_list + param_rand_prime_list)

        if param_rand:
            param_str = f"{param_a}, {param_b}, {param_w}, {param_c}, {param_rand}" 
        else:
            param_str = f"{param_a}, {param_b}, {param_w}, {param_c}"

        self.latency = 2  
        
        # Helper functions mapping EXACTLY to Algorithm 7
        # Note: No PR registers, no outer reg() on v_share, strict 2-operand formatting
        helper_func = f"""
void hpc3o_first_half_{d}_order(_Bool a_share, _Bool b_share, _Bool w_share, _Bool rand, _Bool rand_prime, _Bool *out_share) {{
    _Bool xor_br;
    _Bool and_ar;
    _Bool xor_step1;
    _Bool xor_step2;

    xor_br = b_share ^ rand;
    and_ar = a_share & xor_br;
    xor_step1 = w_share ^ and_ar;
    xor_step2 = xor_step1 ^ rand_prime;
    
    *out_share = reg(xor_step2);
}}

void hpc3o_v_{d}_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand) {{
    _Bool xor_br;
    _Bool temp;
    _Bool and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br); // This remains an R register in Algo 7
    
    and_ta = a_share & temp;
    *v_share = and_ta; // Notice: NO outer reg() here for HPC3o!
}}

void hpc3o_w_{d}_order(_Bool a_share, _Bool rand, _Bool rand_prime, _Bool *w_share) {{
    _Bool and_ar;
    _Bool xor_step1;

    // Notice: Algo 7 does not negate a_share in the else branch
    and_ar = a_share & rand;
    xor_step1 = and_ar ^ rand_prime;
    
    *w_share = reg(xor_step1);
}}

void hpc3o_xor_vw_{d}_order(_Bool v_share, _Bool w_share, _Bool *u_share) {{
    *u_share = v_share ^ w_share;
}}
"""
        function_signature = f"void HPC3o({param_str})"
        print(f"function signature for HPC3o \n {function_signature}")

        body_lines = []

        # Unmasked fallback
        if d == 0:
            body_lines.append(f"\t_Bool and_ab;\n")
            body_lines.append(f"\tand_ab = {var_a}0 & {var_b}0;\n")
            body_lines.append(f"\t*{var_c}0 = {var_w}0 ^ and_ab;\n")
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
                
                # Fetch symmetric random variables
                r_param = f"rand_{min(i, j)}{max(i, j)}"
                r_prime_param = f"rand_prime_{min(i, j)}{max(i, j)}"
                
                # Routing logic explicitly matches Algo 7 if/else
                if j == j_i:
                    body_lines.append(f"\thpc3o_first_half_{d}_order({var_a}{i}, {var_b}{i}, {var_w}{i}, {r_param}, {r_prime_param}, &w{i}{j});\n")
                else:
                    body_lines.append(f"\thpc3o_w_{d}_order({var_a}{i}, {r_param}, {r_prime_param}, &w{i}{j});\n")
                
                # Both branches use the exact same v calculation and XOR combination
                body_lines.append(f"\thpc3o_v_{d}_order({var_a}{i}, {var_b}{j}, &v{i}{j}, {r_param});\n")
                body_lines.append(f"\thpc3o_xor_vw_{d}_order(v{i}{j}, w{i}{j}, &u{i}{j});\n\n")

        temp_index = 0  

        # Assign final values using strictly two-input XOR reductions
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