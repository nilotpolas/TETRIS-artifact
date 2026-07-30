#include <stdio.h>
#include <stdbool.h>
_Bool reg(_Bool a) {
  return a;
}

void hpc2o_same_shares_1_order(_Bool a_share, _Bool b_share, _Bool w0, _Bool *u_share)
{
  _Bool b_share_reg, temp;
  b_share_reg = reg(b_share);
  temp = a_share & b_share_reg;
  *u_share = reg(w0 ^ temp);
}
void hpc2_v_1_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand)
{
  _Bool temp;
  temp = reg(b_share ^ rand);
  *v_share = reg(temp & a_share);
}

void hpc2_w_1_order(_Bool a_share, _Bool rand, _Bool *w_share)
{
  _Bool rand_reg;
  rand_reg = reg(rand);
  _Bool a_neg;
  a_neg = !a_share;
  *w_share = reg(a_neg & rand_reg);
}

void hpc2_xor_vw_1_order(_Bool v_share, _Bool w_share, _Bool *u_share)
{
  *u_share = v_share ^ w_share;
}

void HPC2o(_Bool a0, _Bool a1, _Bool b0, _Bool b1, _Bool w0, _Bool w1, _Bool *c0, _Bool *c1, _Bool rand_01)
{
  _Bool u00;
  _Bool u01;
  _Bool u10;
  _Bool u11;
  _Bool v01;
  _Bool v10;
  _Bool w01;
  _Bool w10;
  hpc2o_same_shares_1_order(a0, b0, w0, &u00);
  hpc2_v_1_order(a0, b1, &v01, rand_01);
  hpc2_w_1_order(a0, rand_01, &w01);
  hpc2_xor_vw_1_order(v01, w01, &u01);
  hpc2_v_1_order(a1, b0, &v10, rand_01);
  hpc2_w_1_order(a1, rand_01, &w10);
  hpc2_xor_vw_1_order(v10, w10, &u10);
  hpc2o_same_shares_1_order(a1, b1, w1, &u11);
  *c0 = u00 ^ u01;
  *c1 = u10 ^ u11;
}