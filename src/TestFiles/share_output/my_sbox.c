void hpc3_same_shares_1_order(int a_share, int b_share, int *u_share)
{
  *u_share = reg(a_share & b_share);
}

void hpc3_v_1_order(int a_share, int b_share, int *v_share, int rand)
{
  int temp;
  temp = reg(b_share ^ rand);
  int a_share_reg;
  a_share_reg = reg(a_share);
  *v_share = temp & a_share_reg;
}

void hpc3_w_1_order(int a_share, int rand, int prand, int *w_share)
{
  int temp;
  int a_share_neg;
  a_share_neg = ~a_share;
  temp = a_share_neg & rand;
  *w_share = reg(temp ^ prand);
}

void hpc3_xor_vw_1_order(int v_share, int w_share, int *u_share)
{
  *u_share = v_share ^ w_share;
}

void HPC3(int a0, int a1, int b0, int b1, int *c0, int *c1, int r01, int p01)
{
  int u00;
  int u01;
  int u10;
  int u11;
  int v01;
  int v10;
  int w01;
  int w10;
  hpc3_same_shares_1_order(a0, b0, &u00);
  hpc3_v_1_order(a0, b1, &v01, r01);
  hpc3_w_1_order(a0, r01, p01, &w01);
  hpc3_xor_vw_1_order(v01, w01, &u01);
  hpc3_v_1_order(a1, b0, &v10, r01);
  hpc3_w_1_order(a1, r01, p01, &w10);
  hpc3_xor_vw_1_order(v10, w10, &u10);
  hpc3_same_shares_1_order(a1, b1, &u11);
  *c0 = u00 ^ u01;
  *c1 = u10 ^ u11;
}

void hpc2_same_shares_1_order(int a_share, int b_share, int *u_share)
{
  int b_share_reg;
  b_share_reg = reg(b_share);
  *u_share = reg(a_share & b_share_reg);
}

void hpc2_v_1_order(int a_share, int b_share, int *v_share, int rand)
{
  int temp;
  temp = reg(b_share ^ rand);
  *v_share = reg(temp & a_share);
}

void hpc2_w_1_order(int a_share, int rand, int *w_share)
{
  int rand_reg;
  rand_reg = reg(rand);
  int a_neg;
  a_neg = ~a_share;
  *w_share = reg(a_neg & rand_reg);
}

void hpc2_xor_vw_1_order(int v_share, int w_share, int *u_share)
{
  *u_share = v_share ^ w_share;
}

void HPC2(int a0, int a1, int b0, int b1, int *c0, int *c1, int rand_01)
{
  int u00;
  int u01;
  int u10;
  int u11;
  int v01;
  int v10;
  int w01;
  int w10;
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

void fun(int a_0, int a_1, int b_0, int b_1, int c_0, int c_1, int d_0, int d_1, int *r_0, int *r_1, int rand_1, int rand_4, int rand_5, int rand_6, int rand_3, int rand_7, int rand_8, int rand_2)
{
  int a_inp_0;
  int a_inp_1;
  int b_inp_0;
  int b_inp_1;
  int c_inp_0;
  int c_inp_1;
  int d_inp_0;
  int d_inp_1;
  a_inp_0 = a_0;
  a_inp_1 = a_1;
  b_inp_0 = b_0;
  b_inp_1 = b_1;
  c_inp_0 = c_0;
  c_inp_1 = c_1;
  d_inp_0 = d_0;
  d_inp_1 = d_1;
  int y_0;
  int y_1;
  int z_0;
  int z_1;
  int x_0;
  int x_1;
  int t_0;
  int t_1;
  int p_0;
  int p_1;
  int q_0;
  int q_1;
  int e_0;
  int e_1;
  HPC3(a_inp_0, a_inp_1, b_inp_0, b_inp_1, &y_0, &y_1, rand_1, rand_2);
  HPC2(y_0, y_1, b_inp_0, b_inp_1, &z_0, &z_1, rand_3);
  HPC2(y_0, y_1, c_inp_0, c_inp_1, &x_0, &x_1, rand_4);
  HPC2(y_0, y_1, d_inp_0, d_inp_1, &t_0, &t_1, rand_5);
  HPC2(z_0, z_1, x_0, x_1, &p_0, &p_1, rand_6);
  HPC2(t_0, t_1, d_inp_0, d_inp_1, &q_0, &q_1, rand_7);
  HPC2(p_0, p_1, q_0, q_1, &e_0, &e_1, rand_8);
  *r_0 = e_0 ^ q_0;
  *r_1 = e_1 ^ q_1;
}

