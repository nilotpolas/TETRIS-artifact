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

void sbox(int x0_0, int x0_1, int x1_0, int x1_1, int x2_0, int x2_1, int x3_0, int x3_1, int *output_0, int *output_1, int dec_1, int dec_0, int dec_2, int dec_3, int rand_2, int rand_3, int rand_1, int rand_4)
{



  int x0_inp_0;
  int x0_inp_1;
  int x1_inp_0;
  int x1_inp_1;
  int x2_inp_0;
  int x2_inp_1;
  int x3_inp_0;
  int x3_inp_1;
  x0_inp_0 = x0_0;
  x0_inp_1 = x0_1;
  x1_inp_0 = x1_0;
  x1_inp_1 = x1_1;
  x2_inp_0 = x2_0;
  x2_inp_1 = x2_1;
  x3_inp_0 = x3_0;
  x3_inp_1 = x3_1;
  int X0_0;
  int X0_1;
  X0_0 = x1_inp_0 & dec_1;
  X0_1 = x1_inp_1 & dec_1;
  int temp_var_0_0;
  int temp_var_0_1;
  temp_var_0_0 = x0_inp_0 ^ x2_inp_0;
  temp_var_0_1 = x0_inp_1 ^ x2_inp_1;
  int X1_0;
  int X1_1;
  X1_0 = temp_var_0_0 & dec_1;
  X1_1 = temp_var_0_1 & dec_1;
  int temp_var_1_0;
  int temp_var_1_1;
  temp_var_1_0 = x2_inp_0 ^ x3_inp_0;
  temp_var_1_1 = x2_inp_1 ^ x3_inp_1;
  int X2_0;
  int X2_1;
  X2_0 = temp_var_1_0 & dec_1;
  X2_1 = temp_var_1_1 & dec_1;
  int X3_0;
  int X3_1;
  X3_0 = (~x2_inp_0) & dec_1;
  X3_1 = x2_inp_1 & dec_1;
  int temp_var_2_0;
  int temp_var_2_1;
  temp_var_2_0 = X0_0 ^ X1_0;
  temp_var_2_1 = X0_1 ^ X1_1;
  int Q0_0;
  int Q0_1;
  Q0_0 = temp_var_2_0 & dec_1;
  Q0_1 = temp_var_2_1 & dec_1;
  int temp_var_3_0;
  int temp_var_3_1;
  temp_var_3_0 = X0_0 ^ X2_0;
  temp_var_3_1 = X0_1 ^ X2_1;
  int Q1_0;
  int Q1_1;
  Q1_0 = temp_var_3_0 & dec_1;
  Q1_1 = temp_var_3_1 & dec_1;
  int T0_0;
  int T0_1;
  HPC2(X3_0, X3_1, Q1_0, Q1_1, &T0_0, &T0_1, rand_1);
  int temp_var_4_0;
  int temp_var_4_1;
  temp_var_4_0 = Q0_0 ^ T0_0;
  temp_var_4_1 = Q0_1 ^ T0_1;
  int Q2_0;
  int Q2_1;
  Q2_0 = temp_var_4_0 & dec_1;
  Q2_1 = temp_var_4_1 & dec_1;
  int T1_0;
  int T1_1;
  HPC2(X0_0, X0_1, Q2_0, Q2_1, &T1_0, &T1_1, rand_2);
  int Q3_0;
  int Q3_1;
  Q3_0 = X0_0 ^ X3_0;
  Q3_1 = X0_1 ^ X3_1;
  int neg_Q3_0 = ~Q3;
  int neg_Q3_1 = ~Q3;
  int Q4_0;
  int Q4_1;
  Q4_0 = neg_Q3_0 & dec_1;
  Q4_1 = neg_Q3_1 & dec_1;
  int T2_0;
  int T2_1;
  HPC2(X3_0, X3_1, Q4_0, Q4_1, &T2_0, &T2_1, rand_3);
  int L0_0;
  int L0_1;
  L0_0 = T1_0 ^ T2_0;
  L0_1 = T1_1 ^ T2_1;
  int Q6_0;
  int Q6_1;
  Q6_0 = X1_0 ^ X3_0;
  Q6_1 = X1_1 ^ X3_1;
  int L4_0;
  int L4_1;
  L4_0 = Q1_0 ^ Q6_0;
  L4_1 = Q1_1 ^ Q6_1;
  int neg_L3_0 = ~L4;
  int neg_L3_1 = ~L4;
  int L1_0;
  int L1_1;
  L1_0 = neg_L3_0 & dec_1;
  L1_1 = neg_L3_1 & dec_1;
  int Q7_0;
  int Q7_1;
  Q7_0 = L1_0 ^ T2_0;
  Q7_1 = L1_1 ^ T2_1;
  int T3_0;
  int T3_1;
  HPC2(Q6_0, Q6_1, Q7_0, Q7_1, &T3_0, &T3_1, rand_4);
  int L2_0;
  int L2_1;
  L2_0 = X0_0 ^ X3_0;
  L2_1 = X0_1 ^ X3_1;
  int Y0_0;
  int Y0_1;
  Y0_0 = L0_0 ^ L2_0;
  Y0_1 = L0_1 ^ L2_1;
  int Y1_0;
  int Y1_1;
  Y1_0 = L0_0 ^ T3_0;
  Y1_1 = L0_1 ^ T3_1;
  int L3_0;
  int L3_1;
  L3_0 = X1_0 ^ T0_0;
  L3_1 = X1_1 ^ T0_1;
  int Y2_0;
  int Y2_1;
  Y2_0 = L3_0 ^ T2_0;
  Y2_1 = L3_1 ^ T2_1;
  int Y3_0;
  int Y3_1;
  Y3_0 = X2_0 ^ T2_0;
  Y3_1 = X2_1 ^ T2_1;
  int O0_0;
  int O0_1;
  O0_0 = Y1_0 & dec_1;
  O0_1 = Y1_1 & dec_1;
  int O_temp_0;
  int O_temp_1;
  O_temp_0 = Y2_0 ^ Y0_0;
  O_temp_1 = Y2_1 ^ Y0_1;
  int neg_O_temp_0 = ~O_temp;
  int neg_O_temp_1 = ~O_temp;
  int O1_0;
  int O1_1;
  O1_0 = neg_O_temp_0 & dec_1;
  O1_1 = neg_O_temp_1 & dec_1;
  int O2_0;
  int O2_1;
  O2_0 = (~Y3_0) & dec_1;
  O2_1 = Y3_1 & dec_1;
  int O3_0;
  int O3_1;
  O3_0 = (~Y2_0) & dec_1;
  O3_1 = Y2_1 & dec_1;
  int temp_var_5_0;
  int temp_var_5_1;
  temp_var_5_0 = O0_0 << dec_0;
  temp_var_5_1 = O0_1 << dec_0;
  int temp_var_6_0;
  int temp_var_6_1;
  temp_var_6_0 = O1_0 << dec_1;
  temp_var_6_1 = O1_1 << dec_1;
  int temp_var_7_0;
  int temp_var_7_1;
  temp_var_7_0 = temp_var_5_0 | temp_var_6_0;
  temp_var_7_1 = temp_var_5_1 | temp_var_6_1;
  int temp_var_8_0;
  int temp_var_8_1;
  temp_var_8_0 = O2_0 << dec_2;
  temp_var_8_1 = O2_1 << dec_2;
  int temp_var_9_0;
  int temp_var_9_1;
  temp_var_9_0 = temp_var_7_0 | temp_var_8_0;
  temp_var_9_1 = temp_var_7_1 | temp_var_8_1;
  int temp_var_10_0;
  int temp_var_10_1;
  temp_var_10_0 = O3_0 << dec_3;
  temp_var_10_1 = O3_1 << dec_3;
  *output_0 = temp_var_9_0 | temp_var_10_0;
  *output_1 = temp_var_9_1 | temp_var_10_1;
}

