from Gadgets import Gadget

class HPC2oSwapped(Gadget):
    """
    HPC2o with swapped input latency profile.

    Original HPC2o: a (first param group)  = fast path (1 cycle)
                    b (second param group) = slow path (2 cycles)

    HPC2o_swapped:  a (first param group)  = slow path (2 cycles)
                    b (second param group) = fast path (1 cycle)

    Like HPC2_swapped, the swap is applied at the call site in the main body:
      - first_half(...) is called as  first_half(b_i, a_i, w_i, rand, &out)
        so that b_i occupies the fast "a_share" port and a_i the slow "b_share" port.
        The !a_share correction inside first_half then becomes !b_i, which
        correctly cancels the b_i & rand term that appears in the swapped v helper.
      - v(...)  is called as  v(b_i, a_j, &vij, rand)   (b_i fast, a_j slow)
      - w(...)  is called as  w(b_i, rand, &wij)          (b_i fast)

    Mathematical verification (d = 1, share i = 0, j_i = 1):
        first_half_sw(b0, a0, w0, r, &out):
            out = reg(w0 ^ b0&a0 ^ !b0 & r)
        v_sw(b0, a1, &v01, r):
            v01 = b0 & (a1 ^ r)   [= b0&a1 ^ b0&r, ignoring registers]
        u01 = v01 ^ out
             = b0&a1 ^ b0&r ^ w0 ^ b0&a0 ^ !b0&r
             = b0&(a0^a1) ^ r ^ w0          (since b0&r ^ !b0&r = r)
        XOR_i u_{i} = (b0^b1)&(a0^a1) ^ (w0^w1) = b & a ^ w  ✓

    Helper functions use the "hpc2osw_" prefix to avoid redefinition errors
    when both HPC2o and HPC2o_swapped appear in the same compilation unit.
    Their bodies are identical to the original HPC2o helpers.
    """

    def __init__(self, d):
        super().__init__(d=d, random_required=0, latency=2, function_name="HPC2o_swapped")

    def generate_multiply_function(self, var_a="a", var_b="b", var_w="w", var_c="c"):
        """
        input:  [a0, ..., ad]   ← slow path (2 cycles)
                [b0, ..., bd]   ← fast path (1 cycle)
                [w0, ..., wd]   ← XOR consumer pre-computed shares
        output: [c0, ..., cd]
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

        # ---------------------------------------------------------------
        # Helper functions – bodies identical to HPC2o; prefix "hpc2osw_"
        # avoids linker conflicts when both gadgets are compiled together.
        #
        # Timing inside each helper (unchanged):
        #   first param  (a_share) → fast port (1 cycle)
        #   second param (b_share) → slow port (2 cycles)
        #
        # HPC2o_swapped's main body inverts the call-site mapping so that
        # the outer "b" input occupies the fast port and the outer "a" input
        # occupies the slow port.
        # ---------------------------------------------------------------
        helper_func = f"""
void hpc2osw_first_half_{d}_order(_Bool a_share, _Bool b_share, _Bool w_share, _Bool rand, _Bool *out_share) {{
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

void hpc2osw_v_{d}_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand) {{
    _Bool xor_br;
    _Bool temp;
    _Bool and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br);

    and_ta = temp & a_share;
    *v_share = reg(and_ta);
}}

void hpc2osw_w_{d}_order(_Bool a_share, _Bool rand, _Bool *w_share) {{
    _Bool a_neg;
    _Bool and_ar;

    a_neg = !a_share;

    and_ar = a_neg & rand;
    *w_share = reg(and_ar);
}}

void hpc2osw_xor_vw_{d}_order(_Bool v_share, _Bool w_share, _Bool *u_share) {{
    *u_share = v_share ^ w_share;
}}

void hpc2osw_or_vw_{d}_order(_Bool v_share, _Bool w_share, _Bool *u_share) {{
    *u_share = v_share | w_share;
}}
"""

        function_signature = f"void HPC2o_swapped({param_str})"
        print(f"function signature for HPC2o_swapped\n {function_signature}")

        body_lines = []

        if d == 0:
            body_lines.append(f"\t_Bool w00;\n")
            body_lines.append(
                f"\thpc2osw_first_half_0_order({var_b}0, {var_a}0, {var_w}0, 0, &w00);\n"
            )
            body_lines.append(f"\t*{var_c}0 = w00;\n")
            body_lines.append("}")
            return helper_func + function_signature + "\n{\n" + "".join(body_lines)

        u_vars = [f"u{i}{j}" for i in range(shares) for j in range(shares) if i != j]
        v_vars = [f"v{i}{j}" for i in range(shares) for j in range(shares) if i != j]
        w_vars = [f"w{i}{j}" for i in range(shares) for j in range(shares) if i != j]

        body_lines.append(f"\t_Bool {', '.join(u_vars)};\n")
        body_lines.append(f"\t_Bool {', '.join(v_vars)};\n")
        body_lines.append(f"\t_Bool {', '.join(w_vars)};\n")

        temp_vars = []
        if shares > 2:
            total_temps = (shares - 2) * shares
            temp_vars = [f"t{k + 1}" for k in range(total_temps)]
            if temp_vars:
                body_lines.append("\t_Bool " + ", ".join(temp_vars) + ";\n")

        body_lines.append("\n")

        for i in range(shares):
            # j_i: the one j≠i that uses first_half (handles same-share correction)
            j_i = 1 if i == 0 else 0

            for j in range(shares):
                if i == j:
                    continue

                r_param = f"rand_{min(i, j)}{max(i, j)}"

                if j == j_i:
                    # SWAPPED call site:
                    #   first_half(b_i, a_i, w_i, rand):
                    #       b_i → a_share port (fast, 1 cycle)
                    #       a_i → b_share port (slow, 2 cycles)
                    #     correction = !b_i & rand, which cancels b_i&rand from v_sw
                    #
                    #   v(b_i, a_j, rand):
                    #       b_i → a_share port (fast, 1 cycle)
                    #       a_j → b_share port (slow, 2 cycles)
                    body_lines.append(
                        f"\thpc2osw_first_half_{d}_order("
                        f"{var_b}{i}, {var_a}{i}, {var_w}{i}, {r_param}, &w{i}{j});\n"
                    )
                    body_lines.append(
                        f"\thpc2osw_v_{d}_order({var_b}{i}, {var_a}{j}, &v{i}{j}, {r_param});\n"
                    )
                    body_lines.append(
                        f"\thpc2osw_xor_vw_{d}_order(v{i}{j}, w{i}{j}, &u{i}{j});\n\n"
                    )
                else:
                    # Additional cross-share terms for d > 1 (or_vw path)
                    body_lines.append(
                        f"\thpc2osw_w_{d}_order({var_b}{i}, {r_param}, &w{i}{j});\n"
                    )
                    body_lines.append(
                        f"\thpc2osw_v_{d}_order({var_b}{i}, {var_a}{j}, &v{i}{j}, {r_param});\n"
                    )
                    body_lines.append(
                        f"\thpc2osw_or_vw_{d}_order(v{i}{j}, w{i}{j}, &u{i}{j});\n\n"
                    )

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
                    body_lines.append(
                        f"\t{temp_vars[temp_index + 1]} = {temp_vars[temp_index]} ^ {u_list[k]};\n"
                    )
                    temp_index += 1
                body_lines.append(
                    f"\t*{var_c}{i} = {temp_vars[temp_index]} ^ {u_list[-1]};\n\n"
                )
                temp_index += 1

        body_lines.append("}")
        function_body = "{\n" + "".join(body_lines)
        return helper_func + function_signature + "\n" + function_body
