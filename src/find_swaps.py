# filepath: /home/tapish08/Desktop/DSE-Framework/find_swaps.py
import re

HPC2_DEFINITIONS = """
void hpc2_same_shares_1_order(int a_share, int b_share, int *u_share)
{
  *u_share = a_share & b_share;
}

void hpc2_v_1_order(int a_share, int b_share, int *v_share, int rand)
{
  int temp;
  temp = reg(b_share ^ rand);
  *v_share = reg(temp & a_share);
}

void hpc2_w_1_order(int a_share, int rand, int *w_share)
{
  int a_neg;
  a_neg = ~a_share;
  *w_share = reg(a_neg & rand);
}

void hpc2_xor_vw_1_order(int v_share, int w_share, int *u_share)
{
  *u_share = v_share ^ w_share;
}

void HPC2(int a0, int a1, int b0, int b1, int *c0, int *c1, int rand_01)
{
  int u00; int u01; int u10; int u11;
  int v01; int v10; int w01; int w10;
  hpc2_same_shares_1_order(a0, b0, &u00);
  hpc2_v_1_order(a0, b1, &v01, rand_01);
  hpc2_w_1_order(a0, rand_01, &w01);
  hpc2_xor_vw_1_order(v01, w01, &u01);
  hpc2_v_1_order(a1, b0, &v10, rand_01);
  hpc2_w_1_order(a1, rand_01, &w10);
  hpc2_xor_vw_1_order(v10, w10, &u10);
  hpc2_same_shares_1_order(a1, b1, &u11);
  *c0 = u00 ^ u01;
  *c1 = u10 ^ u11;
}
"""

HPC2O_DEFINITIONS = """
void hpc2o_same_shares_1_order(int a_share, int b_share, int w0, int *u_share)
{
  int b_share_reg, temp;
  b_share_reg = reg(b_share);
  temp = a_share & b_share_reg;
  *u_share = reg(w0 ^ temp);
}
void hpc2o_v_1_order(int a_share, int b_share, int *v_share, int rand)
{
  int temp;
  temp = reg(b_share ^ rand);
  *v_share = reg(temp & a_share);
}

void hpc2o_w_1_order(int a_share, int rand, int *w_share)
{
  int rand_reg;
  rand_reg = reg(rand);
  int a_neg;
  a_neg = ~a_share;
  *w_share = reg(a_neg & rand_reg);
}

void hpc2o_xor_vw_1_order(int v_share, int w_share, int *u_share)
{
  *u_share = v_share ^ w_share;
}

void HPC2o(int a0, int a1, int b0, int b1, int w0, int w1, int *c0, int *c1, int rand_01)
{
  int u00;
  int u01;
  int u10;
  int u11;
  int v01;
  int v10;
  int w01;
  int w10;
  hpc2o_same_shares_1_order(a0, b0, w0, &u00);
  hpc2o_v_1_order(a0, b1, &v01, rand_01);
  hpc2o_w_1_order(a0, rand_01, &w01);
  hpc2o_xor_vw_1_order(v01, w01, &u01);
  hpc2o_v_1_order(a1, b0, &v10, rand_01);
  hpc2o_w_1_order(a1, rand_01, &w10);
  hpc2o_xor_vw_1_order(v10, w10, &u10);
  hpc2o_same_shares_1_order(a1, b1, w1, &u11);
  *c0 = u00 ^ u01;
  *c1 = u10 ^ u11;
}
"""

def apply_hpc2_swaps(input_filepath, output_filepath):
    arrival_depth = {}

    def get_depth(var_name):
        clean_var = var_name.replace('*', '').strip()
        return arrival_depth.get(clean_var, 0)

    with open(input_filepath, 'r') as f:
        lines = f.readlines()

    optimized_lines = []
    hpc2_injected = False
    swap_count = 0

    sbox_sig_index = -1
    used_rands = set()
    inside_sbox = False

    # Precompute whole text for definition injection checks
    full_text = "".join(lines)

    for line in lines:
        stripped = line.strip()

        # === inject definitions before sbox ===
        if stripped.startswith("void sbox("):
            if not hpc2_injected:
                if "void HPC2(" not in full_text:
                    optimized_lines.append(HPC2_DEFINITIONS)
                if "void HPC2o(" not in full_text:
                    optimized_lines.append(HPC2O_DEFINITIONS)
                hpc2_injected = True

            sbox_sig_index = len(optimized_lines)
            optimized_lines.append(line)
            inside_sbox = True
            continue

        # === non-HPC lines: update depths and copy ===
        if not stripped.startswith("HPC"):
            m_xor = re.search(r"([A-Za-z0-9_*]+)\s*=\s*([A-Za-z0-9_]+)\s*\^\s*([A-Za-z0-9_]+);", stripped)
            m_not = re.search(r"([A-Za-z0-9_*]+)\s*=\s*~([A-Za-z0-9_]+);", stripped)
            m_assign = re.search(r"([A-Za-z0-9_*]+)\s*=\s*([A-Za-z0-9_]+);", stripped)

            if m_xor:
                out, in1, in2 = m_xor.groups()
                arrival_depth[out.replace('*', '')] = max(get_depth(in1), get_depth(in2))
            elif m_not:
                out, in1 = m_not.groups()
                arrival_depth[out.replace('*', '')] = get_depth(in1)
            elif m_assign and stripped.split()[0] != '_Bool':
                out, in1 = m_assign.groups()
                arrival_depth[out.replace('*', '')] = get_depth(in1)

            optimized_lines.append(line)
            if inside_sbox:
                used_rands.update(re.findall(r"rand_\d+", line))
            continue

        # === HPC3 / HPC3o swap handling (robust via splitting) ===
        if stripped.startswith("HPC3"):
            # keep indentation and call text
            indent = line[:len(line) - len(line.lstrip())]
            func_call = stripped  # e.g. "HPC3(...);" or "HPC3o(...);"

            m = re.match(r"(HPC3o|HPC3)\s*\((.*)\)\s*;", func_call)
            if not m:
                # unrecognized format, just copy
                optimized_lines.append(line)
                if inside_sbox:
                    used_rands.update(re.findall(r"rand_\d+", line))
                continue

            gname, arg_str = m.groups()
            args = [a.strip() for a in arg_str.split(',')]

            if gname == "HPC3":
                # Expect 8 args: a0,a1,b0,b1,&c0,&c1, rand1, rand2
                if len(args) != 8:
                    optimized_lines.append(line)
                    if inside_sbox:
                        used_rands.update(re.findall(r"rand_\d+", line))
                    continue
                a0, a1, b0, b1, c0, c1, rand1, rand2 = args
                is_opt = False
            else:
                # HPC3o: 10 args: a0,a1,b0,b1,w0,w1,&c0,&c1, rand1, rand2
                if len(args) != 10:
                    optimized_lines.append(line)
                    if inside_sbox:
                        used_rands.update(re.findall(r"rand_\d+", line))
                    continue
                a0, a1, b0, b1, w0, w1, c0, c1, rand1, rand2 = args
                is_opt = True

            # Compute arrival depths
            depth_A = max(get_depth(a0), get_depth(a1))
            depth_B = max(get_depth(b0), get_depth(b1))

            # Output depths (same for HPC3/HPC3o)
            out0_clean = c0.replace('&', '').strip()
            out1_clean = c1.replace('&', '').strip()
            out_depth = max(depth_A, depth_B) + 1
            arrival_depth[out0_clean] = out_depth
            arrival_depth[out1_clean] = out_depth

            # Decide target gadget and whether to swap A/B
            if abs(depth_A - depth_B) >= 1:
                swap_count += 1
                target = "HPC2o" if is_opt else "HPC2"

                # A is earlier → put A on slower pins (second pair)
                if depth_A < depth_B:
                    if not is_opt:
                        # HPC2(b0,b1,a0,a1,&c0,&c1, rand1)
                        new_args = [b0, b1, a0, a1, c0, c1, rand1]
                    else:
                        # HPC2o(b0,b1,a0,a1,w0,w1,&c0,&c1, rand1)
                        new_args = [b0, b1, a0, a1, w0, w1, c0, c1, rand1]
                else:
                    # B is earlier or equal → keep order
                    if not is_opt:
                        new_args = [a0, a1, b0, b1, c0, c1, rand1]
                    else:
                        new_args = [a0, a1, b0, b1, w0, w1, c0, c1, rand1]

                new_line = f"{indent}{target}(" + ", ".join(new_args) + ");\n"
                optimized_lines.append(new_line)
                if inside_sbox:
                    used_rands.update(re.findall(r"rand_\d+", new_line))
            else:
                # no swap, keep original
                optimized_lines.append(line)
                if inside_sbox:
                    used_rands.update(re.findall(r"rand_\d+", line))

            continue  # handled this line

        # other HPC lines: just copy
        optimized_lines.append(line)
        if inside_sbox:
            used_rands.update(re.findall(r"rand_\d+", line))

    # === clean up sbox signature (unchanged) ===
    if sbox_sig_index != -1:
        sig_line = optimized_lines[sbox_sig_index]
        match = re.search(r"(void\s+sbox\s*\()([^)]+)(\)(.*))", sig_line, flags=re.DOTALL)
        if match:
            prefix = match.group(1)
            params_str = match.group(2)
            suffix = match.group(3)
            new_params = []
            removed_rands = 0
            for p in params_str.split(','):
                p = p.strip()
                rand_match = re.search(r"(rand_\d+)", p)
                if rand_match:
                    if rand_match.group(1) in used_rands:
                        new_params.append(p)
                    else:
                        removed_rands += 1
                else:
                    new_params.append(p)
            optimized_lines[sbox_sig_index] = prefix + ", ".join(new_params) + suffix
            print(f"\n[CLEANUP] Dropped {removed_rands} unused random variables from the sbox signature.")

    with open(output_filepath, 'w') as f:
        f.writelines(optimized_lines)

    print(f"[SUCCESS] Successfully optimized {swap_count} gadgets.")

if __name__ == "__main__":
    # Adjust paths as needed
    input_path = "/home/tapish08/Desktop/DSE-Framework/TestFiles/share_output/output.c"
    output_path = "/home/tapish08/Desktop/DSE-Framework/TestFiles/share_output/output.c"

    print("[INFO] Running apply_hpc2_swaps...")
    apply_hpc2_swaps(input_path, output_path)
    print("[INFO] Done.")