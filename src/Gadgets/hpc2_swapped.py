from Gadgets import Gadget

class HPC2Swapped(Gadget):
    """
    HPC2 with swapped input latency profile.

    Original HPC2:  a (first param group)  = fast path (1 cycle)
                    b (second param group) = slow path (2 cycles)

    HPC2_swapped:   a (first param group)  = slow path (2 cycles)
                    b (second param group) = fast path (1 cycle)

    Achieved by calling the same helper functions but passing (b_i, a_j) to v/w
    instead of (a_i, b_j).  The helper bodies are identical to HPC2 helpers;
    they are given a unique "hpc2sw_" prefix to avoid redefinition errors when
    both HPC2 and HPC2_swapped appear in the same compilation unit.

    Mathematical correctness:
        u_ij = b_i & (a_j ^ r) ^ !b_i & r = b_i & a_j ^ r
        XOR_j u_ij still reconstructs share i of (a AND b).
    """

    def __init__(self, d):
        super().__init__(d=d, random_required=0, latency=2, function_name="HPC2_swapped")

    def generate_multiply_function(self, var_a="a", var_b="b", var_c="c"):
        """
        input:  [a0, a1, ..., ad]   ← slow path (2 cycles)
                [b0, b1, ..., bd]   ← fast path (1 cycle)
        output: [c0, c1, ..., cd]
        """
        d = self.d
        param_a = ", ".join([f"_Bool {var_a}{i}" for i in range(d + 1)])
        param_b = ", ".join([f"_Bool {var_b}{i}" for i in range(d + 1)])
        param_c = ", ".join([f"_Bool * {var_c}{i}" for i in range(d + 1)])

        param_rand_list = []
        for i in range(d):
            for j in range(i + 1, d + 1):
                param_rand_list.append(f"_Bool rand_{i}{j}")
                self.random_required += 1

        param_rand = ", ".join(param_rand_list)
        param_str = f"{param_a}, {param_b}, {param_c}, {param_rand}"

        self.latency = 2

        # ---------------------------------------------------------------
        # Helper functions (bodies identical to HPC2; prefix "hpc2sw_"
        # avoids linker conflicts when both gadgets appear together).
        #
        # Timing (unchanged from HPC2 helpers):
        #   first param  (named a_share) → 1 cycle  (fast port)
        #   second param (named b_share) → 2 cycles (slow port)
        #
        # In HPC2_swapped's main body we SWAP the call-site arguments so
        # that b_i (from the outer "b" input) goes to the fast port and
        # a_j (from the outer "a" input) goes to the slow port.
        # ---------------------------------------------------------------
        helper_func = f"""
void hpc2sw_same_shares_{d}_order(_Bool a_share, _Bool b_share, _Bool * u_share) {{
    *u_share = a_share & b_share;
}}

void hpc2sw_v_{d}_order(_Bool a_share, _Bool b_share, _Bool * v_share, _Bool rand) {{
    _Bool temp;
    temp = reg(b_share ^ rand);
    *v_share = reg(temp & a_share);
}}

void hpc2sw_w_{d}_order(_Bool a_share, _Bool rand, _Bool * w_share) {{
    _Bool a_neg;
    a_neg = !(a_share);
    *w_share = reg(a_neg & rand);
}}

void hpc2sw_xor_vw_{d}_order(_Bool v_share, _Bool w_share, _Bool * u_share) {{
    *u_share = v_share ^ w_share;
}}
"""

        function_signature = f"void HPC2_swapped({param_str})"
        print(f"function signature for HPC2_swapped\n {function_signature}")

        body_lines = []

        # Declare intermediate variables
        body_lines.append(
            f"\t_Bool {', '.join([f'u{i}{j}' for i in range(d + 1) for j in range(d + 1)])};\n"
        )
        body_lines.append(
            f"\t_Bool {', '.join([f'v{i}{j}' for i in range(d + 1) for j in range(d + 1) if i != j])};\n\n"
        )
        body_lines.append(
            f"\t_Bool {', '.join([f'w{i}{j}' for i in range(d + 1) for j in range(d + 1) if i != j])};\n\n"
        )

        for i in range(d + 1):
            for j in range(d + 1):
                if i == j:
                    # Same-share: AND is commutative, no change needed.
                    body_lines.append(
                        f"\thpc2sw_same_shares_{d}_order({var_a}{i}, {var_b}{i}, &u{i}{i});\n"
                    )
                else:
                    r_param = f"rand_{min(i, j)}{max(i, j)}"
                    # SWAPPED call site:
                    #   b_i → first arg (a_share in helper) = fast path (1 cycle)
                    #   a_j → second arg (b_share in helper) = slow path (2 cycles)
                    # This makes the outer "a" input (a_j) travel through 2 pipeline
                    # stages and the outer "b" input (b_i) through only 1.
                    body_lines.append(
                        f"\thpc2sw_v_{d}_order({var_b}{i}, {var_a}{j}, &v{i}{j}, {r_param});\n"
                    )
                    body_lines.append(
                        f"\thpc2sw_w_{d}_order({var_b}{i}, {r_param}, &w{i}{j});\n"
                    )
                    body_lines.append(
                        f"\thpc2sw_xor_vw_{d}_order(v{i}{j}, w{i}{j}, &u{i}{j});\n\n"
                    )

        # Temp variables for XOR reduction (d > 1)
        temp_var_counter = 1
        temp_vars = []
        if d > 1:
            total_temps = (d - 1) * (d + 1)
            for _ in range(total_temps):
                temp_vars.append(f"t{temp_var_counter}")
                temp_var_counter += 1
            body_lines.append("\t_Bool " + ", ".join(temp_vars) + ";\n\n")

        temp_index = 0
        for i in range(d + 1):
            if d == 1:
                body_lines.append(f"\t*{var_c}{i} = u{i}{0} ^ u{i}{1};\n")
            else:
                body_lines.append(f"\t{temp_vars[temp_index]} = u{i}{0} ^ u{i}{1};\n")
                for j in range(2, d):
                    body_lines.append(
                        f"\t{temp_vars[temp_index + 1]} = {temp_vars[temp_index]} ^ u{i}{j};\n"
                    )
                    temp_index += 1
                body_lines.append(f"\t*{var_c}{i} = {temp_vars[temp_index]} ^ u{i}{d};\n\n")
                temp_index += 1

        body_lines.append("}")
        function_body = "{\n" + "".join(body_lines)
        return helper_func + "\n" + function_signature + "\n" + function_body
