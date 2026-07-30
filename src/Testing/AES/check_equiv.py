import re
import subprocess
import os

# 1. PASTE YOUR EXACT GOLDEN CODE HERE
GOLDEN_CODE = """

static int A2X[8] = {0x98, 0xF3, 0xF2, 0x48, 0x09, 0x81, 0xA9, 0xFF},
            X2A[8] = {0x64, 0x78, 0x6E, 0x8C, 0x68, 0x29, 0xDE, 0x60},
            X2S[8] = {0x58, 0x2D, 0x9E, 0x0B, 0xDC, 0x04, 0x03, 0x24},
            S2X[8] = {0x8C, 0x79, 0x05, 0xEB, 0x12, 0x04, 0x51, 0x53};
 
 
 int G4_mul(int x, int y) {
   int a, b, c, d, e, p, q;
 
   a = (x & 0x2) >> 1;
   b = (x & 0x1);
   c = (y & 0x2) >> 1;
   d = (y & 0x1);
   e = (a ^ b) & (c ^ d);
   p = (a & c) ^ e;
   q = (b & d) ^ e;
   return ((p << 1) | q);
 }
 
 
 int G4_scl_N(int x) {
   int a, b, p, q;
 
   a = (x & 0x2) >> 1;
   b = (x & 0x1);
   p = b;
   q = a ^ b;
   return ((p << 1) | q);
 }
 
 
 int G4_scl_N2(int x) {
   int a, b, p, q;
 
   a = (x & 0x2) >> 1;
   b = (x & 0x1);
   p = a ^ b;
   q = a;
   return ((p << 1) | q);
 }
 
 
 int G4_sq(int x) {
   int a, b;
 
   a = (x & 0x2) >> 1;
   b = (x & 0x1);
   return ((b << 1) | a);
 }
 

 int G16_mul(int x, int y) {
   int a, b, c, d, e, p, q;
 
   a = (x & 0xC) >> 2;
   b = (x & 0x3);
   c = (y & 0xC) >> 2;
   d = (y & 0x3);
   e = G4_mul(a ^ b, c ^ d);
   e = G4_scl_N(e);
   p = G4_mul(a, c) ^ e;
   q = G4_mul(b, d) ^ e;
   return ((p << 2) | q);
 }
 

 int G16_sq_scl(int x) {
   int a, b, p, q;
 
   a = (x & 0xC) >> 2;
   b = (x & 0x3);
   p = G4_sq(a ^ b);
   q = G4_scl_N2(G4_sq(b));
   return ((p << 2) | q);
 }
 
 
 int G16_inv(int x) {
   int a, b, c, d, e, p, q;
 
   a = (x & 0xC) >> 2;
   b = (x & 0x3);
   c = G4_scl_N(G4_sq(a ^ b));
   d = G4_mul(a, b);
   e = G4_sq(c ^ d);
   p = G4_mul(e, b);
   q = G4_mul(e, a);
   return ((p << 2) | q);
 }
 

 int G256_inv(int x) {
   int a, b, c, d, e, p, q;
 
   a = (x & 0xF0) >> 4;
   b = (x & 0x0F);
   c = G16_sq_scl(a ^ b);
   d = G16_mul(a, b);
   e = G16_inv(c ^ d);
   p = G16_mul(e, b);
   q = G16_mul(e, a);
   return ((p << 4) | q);
 }
 
 
 int G256_newbasis(int x, int b[]) {
   int i, y = 0;
 
   for (i = 7; i >= 0; i--) {
     if (x & 1)
       y ^= b[i];
     x >>= 1;
   }
   return (y);
 }
 
 int sbox(int n) {
   int t;
 
   t = G256_newbasis(n, A2X);
   t = G256_inv(t);
   t = G256_newbasis(t, X2S);
   return (t ^ 0x63);
 }

 
 
"""

# 2. PASTE YOUR EXACT MASKED CODE HERE
MASKED_CODE = """
// === GADGET DEFINITIONS ===



void hpc3_same_shares_1_order(int a_share, int b_share, int * u_share) {
    * u_share  = a_share & b_share;
}

void hpc3_v_1_order(int a_share, int b_share, int * v_share, int rand){
    int temp;
    temp = reg(b_share ^ rand);
    *v_share = temp & a_share;
}

void hpc3_w_1_order(int a_share, int rand, int prand, int * w_share){
    int temp;
    int a_share_neg;
    a_share_neg = ~(a_share);
    temp = a_share_neg & rand;
    *w_share = reg(temp ^ prand);
}

void hpc3_xor_vw_1_order(int v_share, int w_share, int * u_share){
    *u_share = v_share ^ w_share;
}

void HPC3(int a0, int a1, int b0, int b1, int* c0, int* c1, int r01, int p01)
{
	int u00, u01, u10, u11;
	int v01, v10;
	int w01, w10;

	hpc3_same_shares_1_order(a0, b0, &u00);

	hpc3_v_1_order(a0, b1, &v01 , r01);
	hpc3_w_1_order(a0, r01, p01, &w01);
	hpc3_xor_vw_1_order(v01, w01, &u01);

	hpc3_v_1_order(a1, b0, &v10 , r01);
	hpc3_w_1_order(a1, r01, p01, &w10);
	hpc3_xor_vw_1_order(v10, w10, &u10);

	hpc3_same_shares_1_order(a1, b1, &u11);

	*c0 = u00 ^ u01;
	*c1 = u10 ^ u11;
}


// --- hpc2 ---

void hpc2_same_shares_1_order(int a_share, int b_share, int * u_share) {
    * u_share  = a_share & b_share;
}

void hpc2_v_1_order(int a_share, int b_share, int * v_share, int rand){
    int temp; 
    temp = reg(b_share ^ rand);
    *v_share = reg(temp & a_share);
}

void hpc2_w_1_order(int a_share, int rand, int * w_share){
    int a_neg;
    a_neg = ~(a_share);
    *w_share = reg(a_neg & rand);
}

void hpc2_xor_vw_1_order(int v_share, int w_share, int * u_share){
    *u_share = v_share ^ w_share;
}

void HPC2(int a0, int a1, int b0, int b1, int * c0, int * c1, int rand_01)
{
	int u00, u01, u10, u11;
	int v01, v10;

	int w01, w10;

	hpc2_same_shares_1_order(a0, b0, &u00);
	hpc2_v_1_order(a0, b1, &v01 , rand_01);
	hpc2_w_1_order(a0, rand_01, &w01);
	hpc2_xor_vw_1_order(v01, w01, &u01);

	hpc2_v_1_order(a1, b0, &v10 , rand_01);
	hpc2_w_1_order(a1, rand_01, &w10);
	hpc2_xor_vw_1_order(v10, w10, &u10);

	hpc2_same_shares_1_order(a1, b1, &u11);
	*c0 = u00 ^ u01;
	*c1 = u10 ^ u11;
}

void sbox(int n_0, int n_1, int *__return_value_0, int *__return_value_1, int dec_0, int dec_1, int dec_255, int dec_169, int dec_129, int dec_9, int dec_72, int dec_242, int dec_243, int dec_152, int dec_240, int dec_4, int dec_15, int dec_12, int dec_2, int dec_3, int dec_36, int dec_220, int dec_11, int dec_158, int dec_45, int dec_88, int dec_99, int rand_9, int rand_25, int rand_42, int rand_10, int rand_26, int rand_40, int rand_11, int rand_27, int rand_43, int rand_12, int rand_28, int rand_45, int rand_14, int rand_30, int rand_44, int rand_15, int rand_29, int rand_47, int rand_13, int rand_31, int rand_48, int rand_41, int rand_1, int rand_16, int rand_33, int rand_46, int rand_3, int rand_17, int rand_32, int rand_2, int rand_18, int rand_34, int rand_4, int rand_20, int rand_36, int rand_5, int rand_21, int rand_35, int rand_6, int rand_19, int rand_38, int rand_7, int rand_22, int rand_39, int rand_8, int rand_23, int rand_37, int rand_24)
{
  int t_0;
  int t_1;
  int i_G256_newbasis0_0;
  int i_G256_newbasis0_1;
  int y_G256_newbasis0_0;
  int y_G256_newbasis0_1;
  int _7_y_G256_newbasis0_0;
  int _7_y_G256_newbasis0_1;
  int _7_x_G256_newbasis0_0;
  int _7_x_G256_newbasis0_1;
  int _if_cond_0_G256_newbasis0_0;
  int _if_cond_0_G256_newbasis0_1;
  int _if_neg_cond_0_G256_newbasis0_0;
  int _if_neg_cond_0_G256_newbasis0_1;
  int temp_var_1_G256_newbasis0_0;
  int temp_var_1_G256_newbasis0_1;
  int temp_var_2_G256_newbasis0_0;
  int temp_var_2_G256_newbasis0_1;
  int temp_var_3_G256_newbasis0_0;
  int temp_var_3_G256_newbasis0_1;
  int _1_version__7_y_G256_newbasis0_0;
  int _1_version__7_y_G256_newbasis0_1;
  int _1_version__7_x_G256_newbasis0_0;
  int _1_version__7_x_G256_newbasis0_1;
  int _6_x_G256_newbasis0_0;
  int _6_x_G256_newbasis0_1;
  int _6_y_G256_newbasis0_0;
  int _6_y_G256_newbasis0_1;
  int _if_cond_4_G256_newbasis0_0;
  int _if_cond_4_G256_newbasis0_1;
  int _if_neg_cond_4_G256_newbasis0_0;
  int _if_neg_cond_4_G256_newbasis0_1;
  int temp_var_5_G256_newbasis0_0;
  int temp_var_5_G256_newbasis0_1;
  int temp_var_6_G256_newbasis0_0;
  int temp_var_6_G256_newbasis0_1;
  int temp_var_7_G256_newbasis0_0;
  int temp_var_7_G256_newbasis0_1;
  int _1_version__6_y_G256_newbasis0_0;
  int _1_version__6_y_G256_newbasis0_1;
  int _1_version__6_x_G256_newbasis0_0;
  int _1_version__6_x_G256_newbasis0_1;
  int _5_x_G256_newbasis0_0;
  int _5_x_G256_newbasis0_1;
  int _5_y_G256_newbasis0_0;
  int _5_y_G256_newbasis0_1;
  int _if_cond_8_G256_newbasis0_0;
  int _if_cond_8_G256_newbasis0_1;
  int _if_neg_cond_8_G256_newbasis0_0;
  int _if_neg_cond_8_G256_newbasis0_1;
  int temp_var_9_G256_newbasis0_0;
  int temp_var_9_G256_newbasis0_1;
  int temp_var_10_G256_newbasis0_0;
  int temp_var_10_G256_newbasis0_1;
  int temp_var_11_G256_newbasis0_0;
  int temp_var_11_G256_newbasis0_1;
  int _1_version__5_y_G256_newbasis0_0;
  int _1_version__5_y_G256_newbasis0_1;
  int _1_version__5_x_G256_newbasis0_0;
  int _1_version__5_x_G256_newbasis0_1;
  int _4_y_G256_newbasis0_0;
  int _4_y_G256_newbasis0_1;
  int _4_x_G256_newbasis0_0;
  int _4_x_G256_newbasis0_1;
  int _if_cond_12_G256_newbasis0_0;
  int _if_cond_12_G256_newbasis0_1;
  int _if_neg_cond_12_G256_newbasis0_0;
  int _if_neg_cond_12_G256_newbasis0_1;
  int temp_var_13_G256_newbasis0_0;
  int temp_var_13_G256_newbasis0_1;
  int temp_var_14_G256_newbasis0_0;
  int temp_var_14_G256_newbasis0_1;
  int temp_var_15_G256_newbasis0_0;
  int temp_var_15_G256_newbasis0_1;
  int _1_version__4_y_G256_newbasis0_0;
  int _1_version__4_y_G256_newbasis0_1;
  int _1_version__4_x_G256_newbasis0_0;
  int _1_version__4_x_G256_newbasis0_1;
  int _3_x_G256_newbasis0_0;
  int _3_x_G256_newbasis0_1;
  int _3_y_G256_newbasis0_0;
  int _3_y_G256_newbasis0_1;
  int _if_cond_16_G256_newbasis0_0;
  int _if_cond_16_G256_newbasis0_1;
  int _if_neg_cond_16_G256_newbasis0_0;
  int _if_neg_cond_16_G256_newbasis0_1;
  int temp_var_17_G256_newbasis0_0;
  int temp_var_17_G256_newbasis0_1;
  int temp_var_18_G256_newbasis0_0;
  int temp_var_18_G256_newbasis0_1;
  int temp_var_19_G256_newbasis0_0;
  int temp_var_19_G256_newbasis0_1;
  int _1_version__3_y_G256_newbasis0_0;
  int _1_version__3_y_G256_newbasis0_1;
  int _1_version__3_x_G256_newbasis0_0;
  int _1_version__3_x_G256_newbasis0_1;
  int _2_y_G256_newbasis0_0;
  int _2_y_G256_newbasis0_1;
  int _2_x_G256_newbasis0_0;
  int _2_x_G256_newbasis0_1;
  int _if_cond_20_G256_newbasis0_0;
  int _if_cond_20_G256_newbasis0_1;
  int _if_neg_cond_20_G256_newbasis0_0;
  int _if_neg_cond_20_G256_newbasis0_1;
  int temp_var_21_G256_newbasis0_0;
  int temp_var_21_G256_newbasis0_1;
  int temp_var_22_G256_newbasis0_0;
  int temp_var_22_G256_newbasis0_1;
  int temp_var_23_G256_newbasis0_0;
  int temp_var_23_G256_newbasis0_1;
  int _1_version__2_y_G256_newbasis0_0;
  int _1_version__2_y_G256_newbasis0_1;
  int _1_version__2_x_G256_newbasis0_0;
  int _1_version__2_x_G256_newbasis0_1;
  int _1_y_G256_newbasis0_0;
  int _1_y_G256_newbasis0_1;
  int _1_x_G256_newbasis0_0;
  int _1_x_G256_newbasis0_1;
  int _if_cond_24_G256_newbasis0_0;
  int _if_cond_24_G256_newbasis0_1;
  int _if_neg_cond_24_G256_newbasis0_0;
  int _if_neg_cond_24_G256_newbasis0_1;
  int temp_var_25_G256_newbasis0_0;
  int temp_var_25_G256_newbasis0_1;
  int temp_var_26_G256_newbasis0_0;
  int temp_var_26_G256_newbasis0_1;
  int temp_var_27_G256_newbasis0_0;
  int temp_var_27_G256_newbasis0_1;
  int _1_version__1_y_G256_newbasis0_0;
  int _1_version__1_y_G256_newbasis0_1;
  int _1_version__1_x_G256_newbasis0_0;
  int _1_version__1_x_G256_newbasis0_1;
  int _0_x_G256_newbasis0_0;
  int _0_x_G256_newbasis0_1;
  int _0_y_G256_newbasis0_0;
  int _0_y_G256_newbasis0_1;
  int _if_cond_28_G256_newbasis0_0;
  int _if_cond_28_G256_newbasis0_1;
  int _if_neg_cond_28_G256_newbasis0_0;
  int _if_neg_cond_28_G256_newbasis0_1;
  int temp_var_29_G256_newbasis0_0;
  int temp_var_29_G256_newbasis0_1;
  int temp_var_30_G256_newbasis0_0;
  int temp_var_30_G256_newbasis0_1;
  int temp_var_31_G256_newbasis0_0;
  int temp_var_31_G256_newbasis0_1;
  int _1_version__0_y_G256_newbasis0_0;
  int _1_version__0_y_G256_newbasis0_1;
  int _1_version__0_x_G256_newbasis0_0;
  int _1_version__0_x_G256_newbasis0_1;
  y_G256_newbasis0_0 = dec_0;
  y_G256_newbasis0_1 = dec_0;
  _7_y_G256_newbasis0_0 = y_G256_newbasis0_0;
  _7_y_G256_newbasis0_1 = y_G256_newbasis0_1;
  _7_x_G256_newbasis0_0 = n_0;
  _7_x_G256_newbasis0_1 = n_1;
  _if_cond_0_G256_newbasis0_0 = _7_x_G256_newbasis0_0 & dec_1;
  _if_cond_0_G256_newbasis0_1 = _7_x_G256_newbasis0_1 & dec_1;
  _if_neg_cond_0_G256_newbasis0_0 = !_if_cond_0_G256_newbasis0_0;
  _if_neg_cond_0_G256_newbasis0_1 = _if_cond_0_G256_newbasis0_1;
  temp_var_1_G256_newbasis0_0 = _7_y_G256_newbasis0_0 ^ dec_255;
  temp_var_1_G256_newbasis0_1 = _7_y_G256_newbasis0_1;
  temp_var_2_G256_newbasis0_0 = temp_var_1_G256_newbasis0_0 * _if_cond_0_G256_newbasis0_0;
  temp_var_2_G256_newbasis0_1 = temp_var_1_G256_newbasis0_1 * _if_cond_0_G256_newbasis0_1;
  temp_var_3_G256_newbasis0_0 = _7_y_G256_newbasis0_0 * _if_neg_cond_0_G256_newbasis0_0;
  temp_var_3_G256_newbasis0_1 = _7_y_G256_newbasis0_1 * _if_neg_cond_0_G256_newbasis0_1;
  _1_version__7_y_G256_newbasis0_0 = temp_var_2_G256_newbasis0_0 + temp_var_3_G256_newbasis0_0;
  _1_version__7_y_G256_newbasis0_1 = temp_var_2_G256_newbasis0_1 + temp_var_3_G256_newbasis0_1;
  _1_version__7_x_G256_newbasis0_0 = _7_x_G256_newbasis0_0 >> dec_1;
  _1_version__7_x_G256_newbasis0_1 = _7_x_G256_newbasis0_1 >> dec_1;
  _6_x_G256_newbasis0_0 = _1_version__7_x_G256_newbasis0_0;
  _6_x_G256_newbasis0_1 = _1_version__7_x_G256_newbasis0_1;
  _6_y_G256_newbasis0_0 = _1_version__7_y_G256_newbasis0_0;
  _6_y_G256_newbasis0_1 = _1_version__7_y_G256_newbasis0_1;
  _if_cond_4_G256_newbasis0_0 = _6_x_G256_newbasis0_0 & dec_1;
  _if_cond_4_G256_newbasis0_1 = _6_x_G256_newbasis0_1 & dec_1;
  _if_neg_cond_4_G256_newbasis0_0 = !_if_cond_4_G256_newbasis0_0;
  _if_neg_cond_4_G256_newbasis0_1 = _if_cond_4_G256_newbasis0_1;
  temp_var_5_G256_newbasis0_0 = _6_y_G256_newbasis0_0 ^ dec_169;
  temp_var_5_G256_newbasis0_1 = _6_y_G256_newbasis0_1 ;
  temp_var_6_G256_newbasis0_0 = temp_var_5_G256_newbasis0_0 * _if_cond_4_G256_newbasis0_0;
  temp_var_6_G256_newbasis0_1 = temp_var_5_G256_newbasis0_1 * _if_cond_4_G256_newbasis0_1;
  temp_var_7_G256_newbasis0_0 = _6_y_G256_newbasis0_0 * _if_neg_cond_4_G256_newbasis0_0;
  temp_var_7_G256_newbasis0_1 = _6_y_G256_newbasis0_1 * _if_neg_cond_4_G256_newbasis0_1;
  _1_version__6_y_G256_newbasis0_0 = temp_var_6_G256_newbasis0_0 + temp_var_7_G256_newbasis0_0;
  _1_version__6_y_G256_newbasis0_1 = temp_var_6_G256_newbasis0_1 + temp_var_7_G256_newbasis0_1;
  _1_version__6_x_G256_newbasis0_0 = _6_x_G256_newbasis0_0 >> dec_1;
  _1_version__6_x_G256_newbasis0_1 = _6_x_G256_newbasis0_1 >> dec_1;
  _5_x_G256_newbasis0_0 = _1_version__6_x_G256_newbasis0_0;
  _5_x_G256_newbasis0_1 = _1_version__6_x_G256_newbasis0_1;
  _5_y_G256_newbasis0_0 = _1_version__6_y_G256_newbasis0_0;
  _5_y_G256_newbasis0_1 = _1_version__6_y_G256_newbasis0_1;
  _if_cond_8_G256_newbasis0_0 = _5_x_G256_newbasis0_0 & dec_1;
  _if_cond_8_G256_newbasis0_1 = _5_x_G256_newbasis0_1 & dec_1;
  _if_neg_cond_8_G256_newbasis0_0 = !_if_cond_8_G256_newbasis0_0;
  _if_neg_cond_8_G256_newbasis0_1 = _if_cond_8_G256_newbasis0_1;
  temp_var_9_G256_newbasis0_0 = _5_y_G256_newbasis0_0 ^ dec_129;
  temp_var_9_G256_newbasis0_1 = _5_y_G256_newbasis0_1;
  temp_var_10_G256_newbasis0_0 = temp_var_9_G256_newbasis0_0 * _if_cond_8_G256_newbasis0_0;
  temp_var_10_G256_newbasis0_1 = temp_var_9_G256_newbasis0_1 * _if_cond_8_G256_newbasis0_1;
  temp_var_11_G256_newbasis0_0 = _5_y_G256_newbasis0_0 * _if_neg_cond_8_G256_newbasis0_0;
  temp_var_11_G256_newbasis0_1 = _5_y_G256_newbasis0_1 * _if_neg_cond_8_G256_newbasis0_1;
  _1_version__5_y_G256_newbasis0_0 = temp_var_10_G256_newbasis0_0 + temp_var_11_G256_newbasis0_0;
  _1_version__5_y_G256_newbasis0_1 = temp_var_10_G256_newbasis0_1 + temp_var_11_G256_newbasis0_1;
  _1_version__5_x_G256_newbasis0_0 = _5_x_G256_newbasis0_0 >> dec_1;
  _1_version__5_x_G256_newbasis0_1 = _5_x_G256_newbasis0_1 >> dec_1;
  _4_y_G256_newbasis0_0 = _1_version__5_y_G256_newbasis0_0;
  _4_y_G256_newbasis0_1 = _1_version__5_y_G256_newbasis0_1;
  _4_x_G256_newbasis0_0 = _1_version__5_x_G256_newbasis0_0;
  _4_x_G256_newbasis0_1 = _1_version__5_x_G256_newbasis0_1;
  _if_cond_12_G256_newbasis0_0 = _4_x_G256_newbasis0_0 & dec_1;
  _if_cond_12_G256_newbasis0_1 = _4_x_G256_newbasis0_1 & dec_1;
  _if_neg_cond_12_G256_newbasis0_0 = !_if_cond_12_G256_newbasis0_0;
  _if_neg_cond_12_G256_newbasis0_1 = _if_cond_12_G256_newbasis0_1;
  temp_var_13_G256_newbasis0_0 = _4_y_G256_newbasis0_0 ^ dec_9;
  temp_var_13_G256_newbasis0_1 = _4_y_G256_newbasis0_1 ;
  temp_var_14_G256_newbasis0_0 = temp_var_13_G256_newbasis0_0 * _if_cond_12_G256_newbasis0_0;
  temp_var_14_G256_newbasis0_1 = temp_var_13_G256_newbasis0_1 * _if_cond_12_G256_newbasis0_1;
  temp_var_15_G256_newbasis0_0 = _4_y_G256_newbasis0_0 * _if_neg_cond_12_G256_newbasis0_0;
  temp_var_15_G256_newbasis0_1 = _4_y_G256_newbasis0_1 * _if_neg_cond_12_G256_newbasis0_1;
  _1_version__4_y_G256_newbasis0_0 = temp_var_14_G256_newbasis0_0 + temp_var_15_G256_newbasis0_0;
  _1_version__4_y_G256_newbasis0_1 = temp_var_14_G256_newbasis0_1 + temp_var_15_G256_newbasis0_1;
  _1_version__4_x_G256_newbasis0_0 = _4_x_G256_newbasis0_0 >> dec_1;
  _1_version__4_x_G256_newbasis0_1 = _4_x_G256_newbasis0_1 >> dec_1;
  _3_x_G256_newbasis0_0 = _1_version__4_x_G256_newbasis0_0;
  _3_x_G256_newbasis0_1 = _1_version__4_x_G256_newbasis0_1;
  _3_y_G256_newbasis0_0 = _1_version__4_y_G256_newbasis0_0;
  _3_y_G256_newbasis0_1 = _1_version__4_y_G256_newbasis0_1;
  _if_cond_16_G256_newbasis0_0 = _3_x_G256_newbasis0_0 & dec_1;
  _if_cond_16_G256_newbasis0_1 = _3_x_G256_newbasis0_1 & dec_1;
  _if_neg_cond_16_G256_newbasis0_0 = !_if_cond_16_G256_newbasis0_0;
  _if_neg_cond_16_G256_newbasis0_1 = _if_cond_16_G256_newbasis0_1;
  temp_var_17_G256_newbasis0_0 = _3_y_G256_newbasis0_0 ^ dec_72;
  temp_var_17_G256_newbasis0_1 = _3_y_G256_newbasis0_1 ;
  temp_var_18_G256_newbasis0_0 = temp_var_17_G256_newbasis0_0 * _if_cond_16_G256_newbasis0_0;
  temp_var_18_G256_newbasis0_1 = temp_var_17_G256_newbasis0_1 * _if_cond_16_G256_newbasis0_1;
  temp_var_19_G256_newbasis0_0 = _3_y_G256_newbasis0_0 * _if_neg_cond_16_G256_newbasis0_0;
  temp_var_19_G256_newbasis0_1 = _3_y_G256_newbasis0_1 * _if_neg_cond_16_G256_newbasis0_1;
  _1_version__3_y_G256_newbasis0_0 = temp_var_18_G256_newbasis0_0 + temp_var_19_G256_newbasis0_0;
  _1_version__3_y_G256_newbasis0_1 = temp_var_18_G256_newbasis0_1 + temp_var_19_G256_newbasis0_1;
  _1_version__3_x_G256_newbasis0_0 = _3_x_G256_newbasis0_0 >> dec_1;
  _1_version__3_x_G256_newbasis0_1 = _3_x_G256_newbasis0_1 >> dec_1;
  _2_y_G256_newbasis0_0 = _1_version__3_y_G256_newbasis0_0;
  _2_y_G256_newbasis0_1 = _1_version__3_y_G256_newbasis0_1;
  _2_x_G256_newbasis0_0 = _1_version__3_x_G256_newbasis0_0;
  _2_x_G256_newbasis0_1 = _1_version__3_x_G256_newbasis0_1;
  _if_cond_20_G256_newbasis0_0 = _2_x_G256_newbasis0_0 & dec_1;
  _if_cond_20_G256_newbasis0_1 = _2_x_G256_newbasis0_1 & dec_1;
  _if_neg_cond_20_G256_newbasis0_0 = !_if_cond_20_G256_newbasis0_0;
  _if_neg_cond_20_G256_newbasis0_1 = _if_cond_20_G256_newbasis0_1;
  temp_var_21_G256_newbasis0_0 = _2_y_G256_newbasis0_0 ^ dec_242;
  temp_var_21_G256_newbasis0_1 = _2_y_G256_newbasis0_1 ;
  temp_var_22_G256_newbasis0_0 = temp_var_21_G256_newbasis0_0 * _if_cond_20_G256_newbasis0_0;
  temp_var_22_G256_newbasis0_1 = temp_var_21_G256_newbasis0_1 * _if_cond_20_G256_newbasis0_1;
  temp_var_23_G256_newbasis0_0 = _2_y_G256_newbasis0_0 * _if_neg_cond_20_G256_newbasis0_0;
  temp_var_23_G256_newbasis0_1 = _2_y_G256_newbasis0_1 * _if_neg_cond_20_G256_newbasis0_1;
  _1_version__2_y_G256_newbasis0_0 = temp_var_22_G256_newbasis0_0 + temp_var_23_G256_newbasis0_0;
  _1_version__2_y_G256_newbasis0_1 = temp_var_22_G256_newbasis0_1 + temp_var_23_G256_newbasis0_1;
  _1_version__2_x_G256_newbasis0_0 = _2_x_G256_newbasis0_0 >> dec_1;
  _1_version__2_x_G256_newbasis0_1 = _2_x_G256_newbasis0_1 >> dec_1;
  _1_y_G256_newbasis0_0 = _1_version__2_y_G256_newbasis0_0;
  _1_y_G256_newbasis0_1 = _1_version__2_y_G256_newbasis0_1;
  _1_x_G256_newbasis0_0 = _1_version__2_x_G256_newbasis0_0;
  _1_x_G256_newbasis0_1 = _1_version__2_x_G256_newbasis0_1;
  _if_cond_24_G256_newbasis0_0 = _1_x_G256_newbasis0_0 & dec_1;
  _if_cond_24_G256_newbasis0_1 = _1_x_G256_newbasis0_1 & dec_1;
  _if_neg_cond_24_G256_newbasis0_0 = !_if_cond_24_G256_newbasis0_0;
  _if_neg_cond_24_G256_newbasis0_1 = _if_cond_24_G256_newbasis0_1;
  temp_var_25_G256_newbasis0_0 = _1_y_G256_newbasis0_0 ^ dec_243;
  temp_var_25_G256_newbasis0_1 = _1_y_G256_newbasis0_1 ;
  temp_var_26_G256_newbasis0_0 = temp_var_25_G256_newbasis0_0 * _if_cond_24_G256_newbasis0_0;
  temp_var_26_G256_newbasis0_1 = temp_var_25_G256_newbasis0_1 * _if_cond_24_G256_newbasis0_1;
  temp_var_27_G256_newbasis0_0 = _1_y_G256_newbasis0_0 * _if_neg_cond_24_G256_newbasis0_0;
  temp_var_27_G256_newbasis0_1 = _1_y_G256_newbasis0_1 * _if_neg_cond_24_G256_newbasis0_1;
  _1_version__1_y_G256_newbasis0_0 = temp_var_26_G256_newbasis0_0 + temp_var_27_G256_newbasis0_0;
  _1_version__1_y_G256_newbasis0_1 = temp_var_26_G256_newbasis0_1 + temp_var_27_G256_newbasis0_1;
  _1_version__1_x_G256_newbasis0_0 = _1_x_G256_newbasis0_0 >> dec_1;
  _1_version__1_x_G256_newbasis0_1 = _1_x_G256_newbasis0_1 >> dec_1;
  _0_x_G256_newbasis0_0 = _1_version__1_x_G256_newbasis0_0;
  _0_x_G256_newbasis0_1 = _1_version__1_x_G256_newbasis0_1;
  _0_y_G256_newbasis0_0 = _1_version__1_y_G256_newbasis0_0;
  _0_y_G256_newbasis0_1 = _1_version__1_y_G256_newbasis0_1;
  _if_cond_28_G256_newbasis0_0 = _0_x_G256_newbasis0_0 & dec_1;
  _if_cond_28_G256_newbasis0_1 = _0_x_G256_newbasis0_1 & dec_1;
  _if_neg_cond_28_G256_newbasis0_0 = !_if_cond_28_G256_newbasis0_0;
  _if_neg_cond_28_G256_newbasis0_1 = _if_cond_28_G256_newbasis0_1;
  temp_var_29_G256_newbasis0_0 = _0_y_G256_newbasis0_0 ^ dec_152;
  temp_var_29_G256_newbasis0_1 = _0_y_G256_newbasis0_1 ;
  temp_var_30_G256_newbasis0_0 = temp_var_29_G256_newbasis0_0 * _if_cond_28_G256_newbasis0_0;
  temp_var_30_G256_newbasis0_1 = temp_var_29_G256_newbasis0_1 * _if_cond_28_G256_newbasis0_1;
  temp_var_31_G256_newbasis0_0 = _0_y_G256_newbasis0_0 * _if_neg_cond_28_G256_newbasis0_0;
  temp_var_31_G256_newbasis0_1 = _0_y_G256_newbasis0_1 * _if_neg_cond_28_G256_newbasis0_1;
  _1_version__0_y_G256_newbasis0_0 = temp_var_30_G256_newbasis0_0 + temp_var_31_G256_newbasis0_0;
  _1_version__0_y_G256_newbasis0_1 = temp_var_30_G256_newbasis0_1 + temp_var_31_G256_newbasis0_1;
  _1_version__0_x_G256_newbasis0_0 = _0_x_G256_newbasis0_0 >> dec_1;
  _1_version__0_x_G256_newbasis0_1 = _0_x_G256_newbasis0_1 >> dec_1;
  t_0 = _1_version__0_y_G256_newbasis0_0;
  t_1 = _1_version__0_y_G256_newbasis0_1;
  int _1_version_t_0;
  int _1_version_t_1;
  int a_G256_inv0_0;
  int a_G256_inv0_1;
  int b_G256_inv0_0;
  int b_G256_inv0_1;
  int c_G256_inv0_0;
  int c_G256_inv0_1;
  int d_G256_inv0_0;
  int d_G256_inv0_1;
  int e_G256_inv0_0;
  int e_G256_inv0_1;
  int p_G256_inv0_0;
  int p_G256_inv0_1;
  int q_G256_inv0_0;
  int q_G256_inv0_1;
  int temp_var_0_G256_inv0_0;
  int temp_var_0_G256_inv0_1;
  int temp_var_1_G256_inv0_0;
  int temp_var_1_G256_inv0_1;
  int a_G16_sq_scl0_G256_inv0_0;
  int a_G16_sq_scl0_G256_inv0_1;
  int b_G16_sq_scl0_G256_inv0_0;
  int b_G16_sq_scl0_G256_inv0_1;
  int p_G16_sq_scl0_G256_inv0_0;
  int p_G16_sq_scl0_G256_inv0_1;
  int q_G16_sq_scl0_G256_inv0_0;
  int q_G16_sq_scl0_G256_inv0_1;
  int temp_var_0_G16_sq_scl0_G256_inv0_0;
  int temp_var_0_G16_sq_scl0_G256_inv0_1;
  int temp_var_1_G16_sq_scl0_G256_inv0_0;
  int temp_var_1_G16_sq_scl0_G256_inv0_1;
  int a_G4_sq0_G16_sq_scl0_G256_inv0_0;
  int a_G4_sq0_G16_sq_scl0_G256_inv0_1;
  int b_G4_sq0_G16_sq_scl0_G256_inv0_0;
  int b_G4_sq0_G16_sq_scl0_G256_inv0_1;
  int temp_var_0_G4_sq0_G16_sq_scl0_G256_inv0_0;
  int temp_var_0_G4_sq0_G16_sq_scl0_G256_inv0_1;
  int temp_var_1_G4_sq0_G16_sq_scl0_G256_inv0_0;
  int temp_var_1_G4_sq0_G16_sq_scl0_G256_inv0_1;
  int temp_var_2_G16_sq_scl0_G256_inv0_0;
  int temp_var_2_G16_sq_scl0_G256_inv0_1;
  int a_G4_sq1_G16_sq_scl0_G256_inv0_0;
  int a_G4_sq1_G16_sq_scl0_G256_inv0_1;
  int b_G4_sq1_G16_sq_scl0_G256_inv0_0;
  int b_G4_sq1_G16_sq_scl0_G256_inv0_1;
  int temp_var_0_G4_sq1_G16_sq_scl0_G256_inv0_0;
  int temp_var_0_G4_sq1_G16_sq_scl0_G256_inv0_1;
  int temp_var_1_G4_sq1_G16_sq_scl0_G256_inv0_0;
  int temp_var_1_G4_sq1_G16_sq_scl0_G256_inv0_1;
  int a_G4_scl_N20_G16_sq_scl0_G256_inv0_0;
  int a_G4_scl_N20_G16_sq_scl0_G256_inv0_1;
  int b_G4_scl_N20_G16_sq_scl0_G256_inv0_0;
  int b_G4_scl_N20_G16_sq_scl0_G256_inv0_1;
  int p_G4_scl_N20_G16_sq_scl0_G256_inv0_0;
  int p_G4_scl_N20_G16_sq_scl0_G256_inv0_1;
  int q_G4_scl_N20_G16_sq_scl0_G256_inv0_0;
  int q_G4_scl_N20_G16_sq_scl0_G256_inv0_1;
  int temp_var_0_G4_scl_N20_G16_sq_scl0_G256_inv0_0;
  int temp_var_0_G4_scl_N20_G16_sq_scl0_G256_inv0_1;
  int temp_var_1_G4_scl_N20_G16_sq_scl0_G256_inv0_0;
  int temp_var_1_G4_scl_N20_G16_sq_scl0_G256_inv0_1;
  int temp_var_3_G16_sq_scl0_G256_inv0_0;
  int temp_var_3_G16_sq_scl0_G256_inv0_1;
  int a_G16_mul0_G256_inv0_0;
  int a_G16_mul0_G256_inv0_1;
  int b_G16_mul0_G256_inv0_0;
  int b_G16_mul0_G256_inv0_1;
  int c_G16_mul0_G256_inv0_0;
  int c_G16_mul0_G256_inv0_1;
  int d_G16_mul0_G256_inv0_0;
  int d_G16_mul0_G256_inv0_1;
  int e_G16_mul0_G256_inv0_0;
  int e_G16_mul0_G256_inv0_1;
  int p_G16_mul0_G256_inv0_0;
  int p_G16_mul0_G256_inv0_1;
  int q_G16_mul0_G256_inv0_0;
  int q_G16_mul0_G256_inv0_1;
  int temp_var_0_G16_mul0_G256_inv0_0;
  int temp_var_0_G16_mul0_G256_inv0_1;
  int temp_var_1_G16_mul0_G256_inv0_0;
  int temp_var_1_G16_mul0_G256_inv0_1;
  int temp_var_2_G16_mul0_G256_inv0_0;
  int temp_var_2_G16_mul0_G256_inv0_1;
  int temp_var_3_G16_mul0_G256_inv0_0;
  int temp_var_3_G16_mul0_G256_inv0_1;
  int a_G4_mul0_G16_mul0_G256_inv0_0;
  int a_G4_mul0_G16_mul0_G256_inv0_1;
  int b_G4_mul0_G16_mul0_G256_inv0_0;
  int b_G4_mul0_G16_mul0_G256_inv0_1;
  int c_G4_mul0_G16_mul0_G256_inv0_0;
  int c_G4_mul0_G16_mul0_G256_inv0_1;
  int d_G4_mul0_G16_mul0_G256_inv0_0;
  int d_G4_mul0_G16_mul0_G256_inv0_1;
  int e_G4_mul0_G16_mul0_G256_inv0_0;
  int e_G4_mul0_G16_mul0_G256_inv0_1;
  int p_G4_mul0_G16_mul0_G256_inv0_0;
  int p_G4_mul0_G16_mul0_G256_inv0_1;
  int q_G4_mul0_G16_mul0_G256_inv0_0;
  int q_G4_mul0_G16_mul0_G256_inv0_1;
  int temp_var_0_G4_mul0_G16_mul0_G256_inv0_0;
  int temp_var_0_G4_mul0_G16_mul0_G256_inv0_1;
  int temp_var_1_G4_mul0_G16_mul0_G256_inv0_0;
  int temp_var_1_G4_mul0_G16_mul0_G256_inv0_1;
  int temp_var_2_G4_mul0_G16_mul0_G256_inv0_0;
  int temp_var_2_G4_mul0_G16_mul0_G256_inv0_1;
  int temp_var_3_G4_mul0_G16_mul0_G256_inv0_0;
  int temp_var_3_G4_mul0_G16_mul0_G256_inv0_1;
  int temp_var_4_G4_mul0_G16_mul0_G256_inv0_0;
  int temp_var_4_G4_mul0_G16_mul0_G256_inv0_1;
  int temp_var_5_G4_mul0_G16_mul0_G256_inv0_0;
  int temp_var_5_G4_mul0_G16_mul0_G256_inv0_1;
  int temp_var_6_G4_mul0_G16_mul0_G256_inv0_0;
  int temp_var_6_G4_mul0_G16_mul0_G256_inv0_1;
  int _1_version_e_G16_mul0_G256_inv0_0;
  int _1_version_e_G16_mul0_G256_inv0_1;
  int a_G4_scl_N0_G16_mul0_G256_inv0_0;
  int a_G4_scl_N0_G16_mul0_G256_inv0_1;
  int b_G4_scl_N0_G16_mul0_G256_inv0_0;
  int b_G4_scl_N0_G16_mul0_G256_inv0_1;
  int p_G4_scl_N0_G16_mul0_G256_inv0_0;
  int p_G4_scl_N0_G16_mul0_G256_inv0_1;
  int q_G4_scl_N0_G16_mul0_G256_inv0_0;
  int q_G4_scl_N0_G16_mul0_G256_inv0_1;
  int temp_var_0_G4_scl_N0_G16_mul0_G256_inv0_0;
  int temp_var_0_G4_scl_N0_G16_mul0_G256_inv0_1;
  int temp_var_1_G4_scl_N0_G16_mul0_G256_inv0_0;
  int temp_var_1_G4_scl_N0_G16_mul0_G256_inv0_1;
  int temp_var_4_G16_mul0_G256_inv0_0;
  int temp_var_4_G16_mul0_G256_inv0_1;
  int a_G4_mul1_G16_mul0_G256_inv0_0;
  int a_G4_mul1_G16_mul0_G256_inv0_1;
  int b_G4_mul1_G16_mul0_G256_inv0_0;
  int b_G4_mul1_G16_mul0_G256_inv0_1;
  int c_G4_mul1_G16_mul0_G256_inv0_0;
  int c_G4_mul1_G16_mul0_G256_inv0_1;
  int d_G4_mul1_G16_mul0_G256_inv0_0;
  int d_G4_mul1_G16_mul0_G256_inv0_1;
  int e_G4_mul1_G16_mul0_G256_inv0_0;
  int e_G4_mul1_G16_mul0_G256_inv0_1;
  int p_G4_mul1_G16_mul0_G256_inv0_0;
  int p_G4_mul1_G16_mul0_G256_inv0_1;
  int q_G4_mul1_G16_mul0_G256_inv0_0;
  int q_G4_mul1_G16_mul0_G256_inv0_1;
  int temp_var_0_G4_mul1_G16_mul0_G256_inv0_0;
  int temp_var_0_G4_mul1_G16_mul0_G256_inv0_1;
  int temp_var_1_G4_mul1_G16_mul0_G256_inv0_0;
  int temp_var_1_G4_mul1_G16_mul0_G256_inv0_1;
  int temp_var_2_G4_mul1_G16_mul0_G256_inv0_0;
  int temp_var_2_G4_mul1_G16_mul0_G256_inv0_1;
  int temp_var_3_G4_mul1_G16_mul0_G256_inv0_0;
  int temp_var_3_G4_mul1_G16_mul0_G256_inv0_1;
  int temp_var_4_G4_mul1_G16_mul0_G256_inv0_0;
  int temp_var_4_G4_mul1_G16_mul0_G256_inv0_1;
  int temp_var_5_G4_mul1_G16_mul0_G256_inv0_0;
  int temp_var_5_G4_mul1_G16_mul0_G256_inv0_1;
  int temp_var_6_G4_mul1_G16_mul0_G256_inv0_0;
  int temp_var_6_G4_mul1_G16_mul0_G256_inv0_1;
  int temp_var_5_G16_mul0_G256_inv0_0;
  int temp_var_5_G16_mul0_G256_inv0_1;
  int a_G4_mul2_G16_mul0_G256_inv0_0;
  int a_G4_mul2_G16_mul0_G256_inv0_1;
  int b_G4_mul2_G16_mul0_G256_inv0_0;
  int b_G4_mul2_G16_mul0_G256_inv0_1;
  int c_G4_mul2_G16_mul0_G256_inv0_0;
  int c_G4_mul2_G16_mul0_G256_inv0_1;
  int d_G4_mul2_G16_mul0_G256_inv0_0;
  int d_G4_mul2_G16_mul0_G256_inv0_1;
  int e_G4_mul2_G16_mul0_G256_inv0_0;
  int e_G4_mul2_G16_mul0_G256_inv0_1;
  int p_G4_mul2_G16_mul0_G256_inv0_0;
  int p_G4_mul2_G16_mul0_G256_inv0_1;
  int q_G4_mul2_G16_mul0_G256_inv0_0;
  int q_G4_mul2_G16_mul0_G256_inv0_1;
  int temp_var_0_G4_mul2_G16_mul0_G256_inv0_0;
  int temp_var_0_G4_mul2_G16_mul0_G256_inv0_1;
  int temp_var_1_G4_mul2_G16_mul0_G256_inv0_0;
  int temp_var_1_G4_mul2_G16_mul0_G256_inv0_1;
  int temp_var_2_G4_mul2_G16_mul0_G256_inv0_0;
  int temp_var_2_G4_mul2_G16_mul0_G256_inv0_1;
  int temp_var_3_G4_mul2_G16_mul0_G256_inv0_0;
  int temp_var_3_G4_mul2_G16_mul0_G256_inv0_1;
  int temp_var_4_G4_mul2_G16_mul0_G256_inv0_0;
  int temp_var_4_G4_mul2_G16_mul0_G256_inv0_1;
  int temp_var_5_G4_mul2_G16_mul0_G256_inv0_0;
  int temp_var_5_G4_mul2_G16_mul0_G256_inv0_1;
  int temp_var_6_G4_mul2_G16_mul0_G256_inv0_0;
  int temp_var_6_G4_mul2_G16_mul0_G256_inv0_1;
  int temp_var_6_G16_mul0_G256_inv0_0;
  int temp_var_6_G16_mul0_G256_inv0_1;
  int temp_var_2_G256_inv0_0;
  int temp_var_2_G256_inv0_1;
  int a_G16_inv0_G256_inv0_0;
  int a_G16_inv0_G256_inv0_1;
  int b_G16_inv0_G256_inv0_0;
  int b_G16_inv0_G256_inv0_1;
  int c_G16_inv0_G256_inv0_0;
  int c_G16_inv0_G256_inv0_1;
  int d_G16_inv0_G256_inv0_0;
  int d_G16_inv0_G256_inv0_1;
  int e_G16_inv0_G256_inv0_0;
  int e_G16_inv0_G256_inv0_1;
  int p_G16_inv0_G256_inv0_0;
  int p_G16_inv0_G256_inv0_1;
  int q_G16_inv0_G256_inv0_0;
  int q_G16_inv0_G256_inv0_1;
  int temp_var_0_G16_inv0_G256_inv0_0;
  int temp_var_0_G16_inv0_G256_inv0_1;
  int temp_var_1_G16_inv0_G256_inv0_0;
  int temp_var_1_G16_inv0_G256_inv0_1;
  int temp_var_2_G16_inv0_G256_inv0_0;
  int temp_var_2_G16_inv0_G256_inv0_1;
  int a_G4_sq2_G16_inv0_G256_inv0_0;
  int a_G4_sq2_G16_inv0_G256_inv0_1;
  int b_G4_sq2_G16_inv0_G256_inv0_0;
  int b_G4_sq2_G16_inv0_G256_inv0_1;
  int temp_var_0_G4_sq2_G16_inv0_G256_inv0_0;
  int temp_var_0_G4_sq2_G16_inv0_G256_inv0_1;
  int temp_var_1_G4_sq2_G16_inv0_G256_inv0_0;
  int temp_var_1_G4_sq2_G16_inv0_G256_inv0_1;
  int a_G4_scl_N1_G16_inv0_G256_inv0_0;
  int a_G4_scl_N1_G16_inv0_G256_inv0_1;
  int b_G4_scl_N1_G16_inv0_G256_inv0_0;
  int b_G4_scl_N1_G16_inv0_G256_inv0_1;
  int p_G4_scl_N1_G16_inv0_G256_inv0_0;
  int p_G4_scl_N1_G16_inv0_G256_inv0_1;
  int q_G4_scl_N1_G16_inv0_G256_inv0_0;
  int q_G4_scl_N1_G16_inv0_G256_inv0_1;
  int temp_var_0_G4_scl_N1_G16_inv0_G256_inv0_0;
  int temp_var_0_G4_scl_N1_G16_inv0_G256_inv0_1;
  int temp_var_1_G4_scl_N1_G16_inv0_G256_inv0_0;
  int temp_var_1_G4_scl_N1_G16_inv0_G256_inv0_1;
  int a_G4_mul3_G16_inv0_G256_inv0_0;
  int a_G4_mul3_G16_inv0_G256_inv0_1;
  int b_G4_mul3_G16_inv0_G256_inv0_0;
  int b_G4_mul3_G16_inv0_G256_inv0_1;
  int c_G4_mul3_G16_inv0_G256_inv0_0;
  int c_G4_mul3_G16_inv0_G256_inv0_1;
  int d_G4_mul3_G16_inv0_G256_inv0_0;
  int d_G4_mul3_G16_inv0_G256_inv0_1;
  int e_G4_mul3_G16_inv0_G256_inv0_0;
  int e_G4_mul3_G16_inv0_G256_inv0_1;
  int p_G4_mul3_G16_inv0_G256_inv0_0;
  int p_G4_mul3_G16_inv0_G256_inv0_1;
  int q_G4_mul3_G16_inv0_G256_inv0_0;
  int q_G4_mul3_G16_inv0_G256_inv0_1;
  int temp_var_0_G4_mul3_G16_inv0_G256_inv0_0;
  int temp_var_0_G4_mul3_G16_inv0_G256_inv0_1;
  int temp_var_1_G4_mul3_G16_inv0_G256_inv0_0;
  int temp_var_1_G4_mul3_G16_inv0_G256_inv0_1;
  int temp_var_2_G4_mul3_G16_inv0_G256_inv0_0;
  int temp_var_2_G4_mul3_G16_inv0_G256_inv0_1;
  int temp_var_3_G4_mul3_G16_inv0_G256_inv0_0;
  int temp_var_3_G4_mul3_G16_inv0_G256_inv0_1;
  int temp_var_4_G4_mul3_G16_inv0_G256_inv0_0;
  int temp_var_4_G4_mul3_G16_inv0_G256_inv0_1;
  int temp_var_5_G4_mul3_G16_inv0_G256_inv0_0;
  int temp_var_5_G4_mul3_G16_inv0_G256_inv0_1;
  int temp_var_6_G4_mul3_G16_inv0_G256_inv0_0;
  int temp_var_6_G4_mul3_G16_inv0_G256_inv0_1;
  int temp_var_3_G16_inv0_G256_inv0_0;
  int temp_var_3_G16_inv0_G256_inv0_1;
  int a_G4_sq3_G16_inv0_G256_inv0_0;
  int a_G4_sq3_G16_inv0_G256_inv0_1;
  int b_G4_sq3_G16_inv0_G256_inv0_0;
  int b_G4_sq3_G16_inv0_G256_inv0_1;
  int temp_var_0_G4_sq3_G16_inv0_G256_inv0_0;
  int temp_var_0_G4_sq3_G16_inv0_G256_inv0_1;
  int temp_var_1_G4_sq3_G16_inv0_G256_inv0_0;
  int temp_var_1_G4_sq3_G16_inv0_G256_inv0_1;
  int a_G4_mul4_G16_inv0_G256_inv0_0;
  int a_G4_mul4_G16_inv0_G256_inv0_1;
  int b_G4_mul4_G16_inv0_G256_inv0_0;
  int b_G4_mul4_G16_inv0_G256_inv0_1;
  int c_G4_mul4_G16_inv0_G256_inv0_0;
  int c_G4_mul4_G16_inv0_G256_inv0_1;
  int d_G4_mul4_G16_inv0_G256_inv0_0;
  int d_G4_mul4_G16_inv0_G256_inv0_1;
  int e_G4_mul4_G16_inv0_G256_inv0_0;
  int e_G4_mul4_G16_inv0_G256_inv0_1;
  int p_G4_mul4_G16_inv0_G256_inv0_0;
  int p_G4_mul4_G16_inv0_G256_inv0_1;
  int q_G4_mul4_G16_inv0_G256_inv0_0;
  int q_G4_mul4_G16_inv0_G256_inv0_1;
  int temp_var_0_G4_mul4_G16_inv0_G256_inv0_0;
  int temp_var_0_G4_mul4_G16_inv0_G256_inv0_1;
  int temp_var_1_G4_mul4_G16_inv0_G256_inv0_0;
  int temp_var_1_G4_mul4_G16_inv0_G256_inv0_1;
  int temp_var_2_G4_mul4_G16_inv0_G256_inv0_0;
  int temp_var_2_G4_mul4_G16_inv0_G256_inv0_1;
  int temp_var_3_G4_mul4_G16_inv0_G256_inv0_0;
  int temp_var_3_G4_mul4_G16_inv0_G256_inv0_1;
  int temp_var_4_G4_mul4_G16_inv0_G256_inv0_0;
  int temp_var_4_G4_mul4_G16_inv0_G256_inv0_1;
  int temp_var_5_G4_mul4_G16_inv0_G256_inv0_0;
  int temp_var_5_G4_mul4_G16_inv0_G256_inv0_1;
  int temp_var_6_G4_mul4_G16_inv0_G256_inv0_0;
  int temp_var_6_G4_mul4_G16_inv0_G256_inv0_1;
  int a_G4_mul5_G16_inv0_G256_inv0_0;
  int a_G4_mul5_G16_inv0_G256_inv0_1;
  int b_G4_mul5_G16_inv0_G256_inv0_0;
  int b_G4_mul5_G16_inv0_G256_inv0_1;
  int c_G4_mul5_G16_inv0_G256_inv0_0;
  int c_G4_mul5_G16_inv0_G256_inv0_1;
  int d_G4_mul5_G16_inv0_G256_inv0_0;
  int d_G4_mul5_G16_inv0_G256_inv0_1;
  int e_G4_mul5_G16_inv0_G256_inv0_0;
  int e_G4_mul5_G16_inv0_G256_inv0_1;
  int p_G4_mul5_G16_inv0_G256_inv0_0;
  int p_G4_mul5_G16_inv0_G256_inv0_1;
  int q_G4_mul5_G16_inv0_G256_inv0_0;
  int q_G4_mul5_G16_inv0_G256_inv0_1;
  int temp_var_0_G4_mul5_G16_inv0_G256_inv0_0;
  int temp_var_0_G4_mul5_G16_inv0_G256_inv0_1;
  int temp_var_1_G4_mul5_G16_inv0_G256_inv0_0;
  int temp_var_1_G4_mul5_G16_inv0_G256_inv0_1;
  int temp_var_2_G4_mul5_G16_inv0_G256_inv0_0;
  int temp_var_2_G4_mul5_G16_inv0_G256_inv0_1;
  int temp_var_3_G4_mul5_G16_inv0_G256_inv0_0;
  int temp_var_3_G4_mul5_G16_inv0_G256_inv0_1;
  int temp_var_4_G4_mul5_G16_inv0_G256_inv0_0;
  int temp_var_4_G4_mul5_G16_inv0_G256_inv0_1;
  int temp_var_5_G4_mul5_G16_inv0_G256_inv0_0;
  int temp_var_5_G4_mul5_G16_inv0_G256_inv0_1;
  int temp_var_6_G4_mul5_G16_inv0_G256_inv0_0;
  int temp_var_6_G4_mul5_G16_inv0_G256_inv0_1;
  int temp_var_4_G16_inv0_G256_inv0_0;
  int temp_var_4_G16_inv0_G256_inv0_1;
  int a_G16_mul1_G256_inv0_0;
  int a_G16_mul1_G256_inv0_1;
  int b_G16_mul1_G256_inv0_0;
  int b_G16_mul1_G256_inv0_1;
  int c_G16_mul1_G256_inv0_0;
  int c_G16_mul1_G256_inv0_1;
  int d_G16_mul1_G256_inv0_0;
  int d_G16_mul1_G256_inv0_1;
  int e_G16_mul1_G256_inv0_0;
  int e_G16_mul1_G256_inv0_1;
  int p_G16_mul1_G256_inv0_0;
  int p_G16_mul1_G256_inv0_1;
  int q_G16_mul1_G256_inv0_0;
  int q_G16_mul1_G256_inv0_1;
  int temp_var_0_G16_mul1_G256_inv0_0;
  int temp_var_0_G16_mul1_G256_inv0_1;
  int temp_var_1_G16_mul1_G256_inv0_0;
  int temp_var_1_G16_mul1_G256_inv0_1;
  int temp_var_2_G16_mul1_G256_inv0_0;
  int temp_var_2_G16_mul1_G256_inv0_1;
  int temp_var_3_G16_mul1_G256_inv0_0;
  int temp_var_3_G16_mul1_G256_inv0_1;
  int a_G4_mul0_G16_mul1_G256_inv0_0;
  int a_G4_mul0_G16_mul1_G256_inv0_1;
  int b_G4_mul0_G16_mul1_G256_inv0_0;
  int b_G4_mul0_G16_mul1_G256_inv0_1;
  int c_G4_mul0_G16_mul1_G256_inv0_0;
  int c_G4_mul0_G16_mul1_G256_inv0_1;
  int d_G4_mul0_G16_mul1_G256_inv0_0;
  int d_G4_mul0_G16_mul1_G256_inv0_1;
  int e_G4_mul0_G16_mul1_G256_inv0_0;
  int e_G4_mul0_G16_mul1_G256_inv0_1;
  int p_G4_mul0_G16_mul1_G256_inv0_0;
  int p_G4_mul0_G16_mul1_G256_inv0_1;
  int q_G4_mul0_G16_mul1_G256_inv0_0;
  int q_G4_mul0_G16_mul1_G256_inv0_1;
  int temp_var_0_G4_mul0_G16_mul1_G256_inv0_0;
  int temp_var_0_G4_mul0_G16_mul1_G256_inv0_1;
  int temp_var_1_G4_mul0_G16_mul1_G256_inv0_0;
  int temp_var_1_G4_mul0_G16_mul1_G256_inv0_1;
  int temp_var_2_G4_mul0_G16_mul1_G256_inv0_0;
  int temp_var_2_G4_mul0_G16_mul1_G256_inv0_1;
  int temp_var_3_G4_mul0_G16_mul1_G256_inv0_0;
  int temp_var_3_G4_mul0_G16_mul1_G256_inv0_1;
  int temp_var_4_G4_mul0_G16_mul1_G256_inv0_0;
  int temp_var_4_G4_mul0_G16_mul1_G256_inv0_1;
  int temp_var_5_G4_mul0_G16_mul1_G256_inv0_0;
  int temp_var_5_G4_mul0_G16_mul1_G256_inv0_1;
  int temp_var_6_G4_mul0_G16_mul1_G256_inv0_0;
  int temp_var_6_G4_mul0_G16_mul1_G256_inv0_1;
  int _1_version_e_G16_mul1_G256_inv0_0;
  int _1_version_e_G16_mul1_G256_inv0_1;
  int a_G4_scl_N0_G16_mul1_G256_inv0_0;
  int a_G4_scl_N0_G16_mul1_G256_inv0_1;
  int b_G4_scl_N0_G16_mul1_G256_inv0_0;
  int b_G4_scl_N0_G16_mul1_G256_inv0_1;
  int p_G4_scl_N0_G16_mul1_G256_inv0_0;
  int p_G4_scl_N0_G16_mul1_G256_inv0_1;
  int q_G4_scl_N0_G16_mul1_G256_inv0_0;
  int q_G4_scl_N0_G16_mul1_G256_inv0_1;
  int temp_var_0_G4_scl_N0_G16_mul1_G256_inv0_0;
  int temp_var_0_G4_scl_N0_G16_mul1_G256_inv0_1;
  int temp_var_1_G4_scl_N0_G16_mul1_G256_inv0_0;
  int temp_var_1_G4_scl_N0_G16_mul1_G256_inv0_1;
  int temp_var_4_G16_mul1_G256_inv0_0;
  int temp_var_4_G16_mul1_G256_inv0_1;
  int a_G4_mul1_G16_mul1_G256_inv0_0;
  int a_G4_mul1_G16_mul1_G256_inv0_1;
  int b_G4_mul1_G16_mul1_G256_inv0_0;
  int b_G4_mul1_G16_mul1_G256_inv0_1;
  int c_G4_mul1_G16_mul1_G256_inv0_0;
  int c_G4_mul1_G16_mul1_G256_inv0_1;
  int d_G4_mul1_G16_mul1_G256_inv0_0;
  int d_G4_mul1_G16_mul1_G256_inv0_1;
  int e_G4_mul1_G16_mul1_G256_inv0_0;
  int e_G4_mul1_G16_mul1_G256_inv0_1;
  int p_G4_mul1_G16_mul1_G256_inv0_0;
  int p_G4_mul1_G16_mul1_G256_inv0_1;
  int q_G4_mul1_G16_mul1_G256_inv0_0;
  int q_G4_mul1_G16_mul1_G256_inv0_1;
  int temp_var_0_G4_mul1_G16_mul1_G256_inv0_0;
  int temp_var_0_G4_mul1_G16_mul1_G256_inv0_1;
  int temp_var_1_G4_mul1_G16_mul1_G256_inv0_0;
  int temp_var_1_G4_mul1_G16_mul1_G256_inv0_1;
  int temp_var_2_G4_mul1_G16_mul1_G256_inv0_0;
  int temp_var_2_G4_mul1_G16_mul1_G256_inv0_1;
  int temp_var_3_G4_mul1_G16_mul1_G256_inv0_0;
  int temp_var_3_G4_mul1_G16_mul1_G256_inv0_1;
  int temp_var_4_G4_mul1_G16_mul1_G256_inv0_0;
  int temp_var_4_G4_mul1_G16_mul1_G256_inv0_1;
  int temp_var_5_G4_mul1_G16_mul1_G256_inv0_0;
  int temp_var_5_G4_mul1_G16_mul1_G256_inv0_1;
  int temp_var_6_G4_mul1_G16_mul1_G256_inv0_0;
  int temp_var_6_G4_mul1_G16_mul1_G256_inv0_1;
  int temp_var_5_G16_mul1_G256_inv0_0;
  int temp_var_5_G16_mul1_G256_inv0_1;
  int a_G4_mul2_G16_mul1_G256_inv0_0;
  int a_G4_mul2_G16_mul1_G256_inv0_1;
  int b_G4_mul2_G16_mul1_G256_inv0_0;
  int b_G4_mul2_G16_mul1_G256_inv0_1;
  int c_G4_mul2_G16_mul1_G256_inv0_0;
  int c_G4_mul2_G16_mul1_G256_inv0_1;
  int d_G4_mul2_G16_mul1_G256_inv0_0;
  int d_G4_mul2_G16_mul1_G256_inv0_1;
  int e_G4_mul2_G16_mul1_G256_inv0_0;
  int e_G4_mul2_G16_mul1_G256_inv0_1;
  int p_G4_mul2_G16_mul1_G256_inv0_0;
  int p_G4_mul2_G16_mul1_G256_inv0_1;
  int q_G4_mul2_G16_mul1_G256_inv0_0;
  int q_G4_mul2_G16_mul1_G256_inv0_1;
  int temp_var_0_G4_mul2_G16_mul1_G256_inv0_0;
  int temp_var_0_G4_mul2_G16_mul1_G256_inv0_1;
  int temp_var_1_G4_mul2_G16_mul1_G256_inv0_0;
  int temp_var_1_G4_mul2_G16_mul1_G256_inv0_1;
  int temp_var_2_G4_mul2_G16_mul1_G256_inv0_0;
  int temp_var_2_G4_mul2_G16_mul1_G256_inv0_1;
  int temp_var_3_G4_mul2_G16_mul1_G256_inv0_0;
  int temp_var_3_G4_mul2_G16_mul1_G256_inv0_1;
  int temp_var_4_G4_mul2_G16_mul1_G256_inv0_0;
  int temp_var_4_G4_mul2_G16_mul1_G256_inv0_1;
  int temp_var_5_G4_mul2_G16_mul1_G256_inv0_0;
  int temp_var_5_G4_mul2_G16_mul1_G256_inv0_1;
  int temp_var_6_G4_mul2_G16_mul1_G256_inv0_0;
  int temp_var_6_G4_mul2_G16_mul1_G256_inv0_1;
  int temp_var_6_G16_mul1_G256_inv0_0;
  int temp_var_6_G16_mul1_G256_inv0_1;
  int a_G16_mul2_G256_inv0_0;
  int a_G16_mul2_G256_inv0_1;
  int b_G16_mul2_G256_inv0_0;
  int b_G16_mul2_G256_inv0_1;
  int c_G16_mul2_G256_inv0_0;
  int c_G16_mul2_G256_inv0_1;
  int d_G16_mul2_G256_inv0_0;
  int d_G16_mul2_G256_inv0_1;
  int e_G16_mul2_G256_inv0_0;
  int e_G16_mul2_G256_inv0_1;
  int p_G16_mul2_G256_inv0_0;
  int p_G16_mul2_G256_inv0_1;
  int q_G16_mul2_G256_inv0_0;
  int q_G16_mul2_G256_inv0_1;
  int temp_var_0_G16_mul2_G256_inv0_0;
  int temp_var_0_G16_mul2_G256_inv0_1;
  int temp_var_1_G16_mul2_G256_inv0_0;
  int temp_var_1_G16_mul2_G256_inv0_1;
  int temp_var_2_G16_mul2_G256_inv0_0;
  int temp_var_2_G16_mul2_G256_inv0_1;
  int temp_var_3_G16_mul2_G256_inv0_0;
  int temp_var_3_G16_mul2_G256_inv0_1;
  int a_G4_mul0_G16_mul2_G256_inv0_0;
  int a_G4_mul0_G16_mul2_G256_inv0_1;
  int b_G4_mul0_G16_mul2_G256_inv0_0;
  int b_G4_mul0_G16_mul2_G256_inv0_1;
  int c_G4_mul0_G16_mul2_G256_inv0_0;
  int c_G4_mul0_G16_mul2_G256_inv0_1;
  int d_G4_mul0_G16_mul2_G256_inv0_0;
  int d_G4_mul0_G16_mul2_G256_inv0_1;
  int e_G4_mul0_G16_mul2_G256_inv0_0;
  int e_G4_mul0_G16_mul2_G256_inv0_1;
  int p_G4_mul0_G16_mul2_G256_inv0_0;
  int p_G4_mul0_G16_mul2_G256_inv0_1;
  int q_G4_mul0_G16_mul2_G256_inv0_0;
  int q_G4_mul0_G16_mul2_G256_inv0_1;
  int temp_var_0_G4_mul0_G16_mul2_G256_inv0_0;
  int temp_var_0_G4_mul0_G16_mul2_G256_inv0_1;
  int temp_var_1_G4_mul0_G16_mul2_G256_inv0_0;
  int temp_var_1_G4_mul0_G16_mul2_G256_inv0_1;
  int temp_var_2_G4_mul0_G16_mul2_G256_inv0_0;
  int temp_var_2_G4_mul0_G16_mul2_G256_inv0_1;
  int temp_var_3_G4_mul0_G16_mul2_G256_inv0_0;
  int temp_var_3_G4_mul0_G16_mul2_G256_inv0_1;
  int temp_var_4_G4_mul0_G16_mul2_G256_inv0_0;
  int temp_var_4_G4_mul0_G16_mul2_G256_inv0_1;
  int temp_var_5_G4_mul0_G16_mul2_G256_inv0_0;
  int temp_var_5_G4_mul0_G16_mul2_G256_inv0_1;
  int temp_var_6_G4_mul0_G16_mul2_G256_inv0_0;
  int temp_var_6_G4_mul0_G16_mul2_G256_inv0_1;
  int _1_version_e_G16_mul2_G256_inv0_0;
  int _1_version_e_G16_mul2_G256_inv0_1;
  int a_G4_scl_N0_G16_mul2_G256_inv0_0;
  int a_G4_scl_N0_G16_mul2_G256_inv0_1;
  int b_G4_scl_N0_G16_mul2_G256_inv0_0;
  int b_G4_scl_N0_G16_mul2_G256_inv0_1;
  int p_G4_scl_N0_G16_mul2_G256_inv0_0;
  int p_G4_scl_N0_G16_mul2_G256_inv0_1;
  int q_G4_scl_N0_G16_mul2_G256_inv0_0;
  int q_G4_scl_N0_G16_mul2_G256_inv0_1;
  int temp_var_0_G4_scl_N0_G16_mul2_G256_inv0_0;
  int temp_var_0_G4_scl_N0_G16_mul2_G256_inv0_1;
  int temp_var_1_G4_scl_N0_G16_mul2_G256_inv0_0;
  int temp_var_1_G4_scl_N0_G16_mul2_G256_inv0_1;
  int temp_var_4_G16_mul2_G256_inv0_0;
  int temp_var_4_G16_mul2_G256_inv0_1;
  int a_G4_mul1_G16_mul2_G256_inv0_0;
  int a_G4_mul1_G16_mul2_G256_inv0_1;
  int b_G4_mul1_G16_mul2_G256_inv0_0;
  int b_G4_mul1_G16_mul2_G256_inv0_1;
  int c_G4_mul1_G16_mul2_G256_inv0_0;
  int c_G4_mul1_G16_mul2_G256_inv0_1;
  int d_G4_mul1_G16_mul2_G256_inv0_0;
  int d_G4_mul1_G16_mul2_G256_inv0_1;
  int e_G4_mul1_G16_mul2_G256_inv0_0;
  int e_G4_mul1_G16_mul2_G256_inv0_1;
  int p_G4_mul1_G16_mul2_G256_inv0_0;
  int p_G4_mul1_G16_mul2_G256_inv0_1;
  int q_G4_mul1_G16_mul2_G256_inv0_0;
  int q_G4_mul1_G16_mul2_G256_inv0_1;
  int temp_var_0_G4_mul1_G16_mul2_G256_inv0_0;
  int temp_var_0_G4_mul1_G16_mul2_G256_inv0_1;
  int temp_var_1_G4_mul1_G16_mul2_G256_inv0_0;
  int temp_var_1_G4_mul1_G16_mul2_G256_inv0_1;
  int temp_var_2_G4_mul1_G16_mul2_G256_inv0_0;
  int temp_var_2_G4_mul1_G16_mul2_G256_inv0_1;
  int temp_var_3_G4_mul1_G16_mul2_G256_inv0_0;
  int temp_var_3_G4_mul1_G16_mul2_G256_inv0_1;
  int temp_var_4_G4_mul1_G16_mul2_G256_inv0_0;
  int temp_var_4_G4_mul1_G16_mul2_G256_inv0_1;
  int temp_var_5_G4_mul1_G16_mul2_G256_inv0_0;
  int temp_var_5_G4_mul1_G16_mul2_G256_inv0_1;
  int temp_var_6_G4_mul1_G16_mul2_G256_inv0_0;
  int temp_var_6_G4_mul1_G16_mul2_G256_inv0_1;
  int temp_var_5_G16_mul2_G256_inv0_0;
  int temp_var_5_G16_mul2_G256_inv0_1;
  int a_G4_mul2_G16_mul2_G256_inv0_0;
  int a_G4_mul2_G16_mul2_G256_inv0_1;
  int b_G4_mul2_G16_mul2_G256_inv0_0;
  int b_G4_mul2_G16_mul2_G256_inv0_1;
  int c_G4_mul2_G16_mul2_G256_inv0_0;
  int c_G4_mul2_G16_mul2_G256_inv0_1;
  int d_G4_mul2_G16_mul2_G256_inv0_0;
  int d_G4_mul2_G16_mul2_G256_inv0_1;
  int e_G4_mul2_G16_mul2_G256_inv0_0;
  int e_G4_mul2_G16_mul2_G256_inv0_1;
  int p_G4_mul2_G16_mul2_G256_inv0_0;
  int p_G4_mul2_G16_mul2_G256_inv0_1;
  int q_G4_mul2_G16_mul2_G256_inv0_0;
  int q_G4_mul2_G16_mul2_G256_inv0_1;
  int temp_var_0_G4_mul2_G16_mul2_G256_inv0_0;
  int temp_var_0_G4_mul2_G16_mul2_G256_inv0_1;
  int temp_var_1_G4_mul2_G16_mul2_G256_inv0_0;
  int temp_var_1_G4_mul2_G16_mul2_G256_inv0_1;
  int temp_var_2_G4_mul2_G16_mul2_G256_inv0_0;
  int temp_var_2_G4_mul2_G16_mul2_G256_inv0_1;
  int temp_var_3_G4_mul2_G16_mul2_G256_inv0_0;
  int temp_var_3_G4_mul2_G16_mul2_G256_inv0_1;
  int temp_var_4_G4_mul2_G16_mul2_G256_inv0_0;
  int temp_var_4_G4_mul2_G16_mul2_G256_inv0_1;
  int temp_var_5_G4_mul2_G16_mul2_G256_inv0_0;
  int temp_var_5_G4_mul2_G16_mul2_G256_inv0_1;
  int temp_var_6_G4_mul2_G16_mul2_G256_inv0_0;
  int temp_var_6_G4_mul2_G16_mul2_G256_inv0_1;
  int temp_var_6_G16_mul2_G256_inv0_0;
  int temp_var_6_G16_mul2_G256_inv0_1;
  int temp_var_3_G256_inv0_0;
  int temp_var_3_G256_inv0_1;
  temp_var_0_G256_inv0_0 = t_0 & dec_240;
  temp_var_0_G256_inv0_1 = t_1 & dec_240;
  a_G256_inv0_0 = temp_var_0_G256_inv0_0 >> dec_4;
  a_G256_inv0_1 = temp_var_0_G256_inv0_1 >> dec_4;
  b_G256_inv0_0 = t_0 & dec_15;
  b_G256_inv0_1 = t_1 & dec_15;
  temp_var_1_G256_inv0_0 = a_G256_inv0_0 ^ b_G256_inv0_0;
  temp_var_1_G256_inv0_1 = a_G256_inv0_1 ^ b_G256_inv0_1;
  temp_var_0_G16_sq_scl0_G256_inv0_0 = temp_var_1_G256_inv0_0 & dec_12;
  temp_var_0_G16_sq_scl0_G256_inv0_1 = temp_var_1_G256_inv0_1 & dec_12;
  a_G16_sq_scl0_G256_inv0_0 = temp_var_0_G16_sq_scl0_G256_inv0_0 >> dec_2;
  a_G16_sq_scl0_G256_inv0_1 = temp_var_0_G16_sq_scl0_G256_inv0_1 >> dec_2;
  b_G16_sq_scl0_G256_inv0_0 = temp_var_1_G256_inv0_0 & dec_3;
  b_G16_sq_scl0_G256_inv0_1 = temp_var_1_G256_inv0_1 & dec_3;
  temp_var_1_G16_sq_scl0_G256_inv0_0 = a_G16_sq_scl0_G256_inv0_0 ^ b_G16_sq_scl0_G256_inv0_0;
  temp_var_1_G16_sq_scl0_G256_inv0_1 = a_G16_sq_scl0_G256_inv0_1 ^ b_G16_sq_scl0_G256_inv0_1;
  temp_var_0_G4_sq0_G16_sq_scl0_G256_inv0_0 = temp_var_1_G16_sq_scl0_G256_inv0_0 & dec_2;
  temp_var_0_G4_sq0_G16_sq_scl0_G256_inv0_1 = temp_var_1_G16_sq_scl0_G256_inv0_1 & dec_2;
  a_G4_sq0_G16_sq_scl0_G256_inv0_0 = temp_var_0_G4_sq0_G16_sq_scl0_G256_inv0_0 >> dec_1;
  a_G4_sq0_G16_sq_scl0_G256_inv0_1 = temp_var_0_G4_sq0_G16_sq_scl0_G256_inv0_1 >> dec_1;
  b_G4_sq0_G16_sq_scl0_G256_inv0_0 = temp_var_1_G16_sq_scl0_G256_inv0_0 & dec_1;
  b_G4_sq0_G16_sq_scl0_G256_inv0_1 = temp_var_1_G16_sq_scl0_G256_inv0_1 & dec_1;
  temp_var_1_G4_sq0_G16_sq_scl0_G256_inv0_0 = b_G4_sq0_G16_sq_scl0_G256_inv0_0 << dec_1;
  temp_var_1_G4_sq0_G16_sq_scl0_G256_inv0_1 = b_G4_sq0_G16_sq_scl0_G256_inv0_1 << dec_1;
  p_G16_sq_scl0_G256_inv0_0 = temp_var_1_G4_sq0_G16_sq_scl0_G256_inv0_0 | a_G4_sq0_G16_sq_scl0_G256_inv0_0;
  p_G16_sq_scl0_G256_inv0_1 = temp_var_1_G4_sq0_G16_sq_scl0_G256_inv0_1 | a_G4_sq0_G16_sq_scl0_G256_inv0_1;
  temp_var_0_G4_sq1_G16_sq_scl0_G256_inv0_0 = b_G16_sq_scl0_G256_inv0_0 & dec_2;
  temp_var_0_G4_sq1_G16_sq_scl0_G256_inv0_1 = b_G16_sq_scl0_G256_inv0_1 & dec_2;
  a_G4_sq1_G16_sq_scl0_G256_inv0_0 = temp_var_0_G4_sq1_G16_sq_scl0_G256_inv0_0 >> dec_1;
  a_G4_sq1_G16_sq_scl0_G256_inv0_1 = temp_var_0_G4_sq1_G16_sq_scl0_G256_inv0_1 >> dec_1;
  b_G4_sq1_G16_sq_scl0_G256_inv0_0 = b_G16_sq_scl0_G256_inv0_0 & dec_1;
  b_G4_sq1_G16_sq_scl0_G256_inv0_1 = b_G16_sq_scl0_G256_inv0_1 & dec_1;
  temp_var_1_G4_sq1_G16_sq_scl0_G256_inv0_0 = b_G4_sq1_G16_sq_scl0_G256_inv0_0 << dec_1;
  temp_var_1_G4_sq1_G16_sq_scl0_G256_inv0_1 = b_G4_sq1_G16_sq_scl0_G256_inv0_1 << dec_1;
  temp_var_2_G16_sq_scl0_G256_inv0_0 = temp_var_1_G4_sq1_G16_sq_scl0_G256_inv0_0 | a_G4_sq1_G16_sq_scl0_G256_inv0_0;
  temp_var_2_G16_sq_scl0_G256_inv0_1 = temp_var_1_G4_sq1_G16_sq_scl0_G256_inv0_1 | a_G4_sq1_G16_sq_scl0_G256_inv0_1;
  temp_var_0_G4_scl_N20_G16_sq_scl0_G256_inv0_0 = temp_var_2_G16_sq_scl0_G256_inv0_0 & dec_2;
  temp_var_0_G4_scl_N20_G16_sq_scl0_G256_inv0_1 = temp_var_2_G16_sq_scl0_G256_inv0_1 & dec_2;
  a_G4_scl_N20_G16_sq_scl0_G256_inv0_0 = temp_var_0_G4_scl_N20_G16_sq_scl0_G256_inv0_0 >> dec_1;
  a_G4_scl_N20_G16_sq_scl0_G256_inv0_1 = temp_var_0_G4_scl_N20_G16_sq_scl0_G256_inv0_1 >> dec_1;
  b_G4_scl_N20_G16_sq_scl0_G256_inv0_0 = temp_var_2_G16_sq_scl0_G256_inv0_0 & dec_1;
  b_G4_scl_N20_G16_sq_scl0_G256_inv0_1 = temp_var_2_G16_sq_scl0_G256_inv0_1 & dec_1;
  p_G4_scl_N20_G16_sq_scl0_G256_inv0_0 = a_G4_scl_N20_G16_sq_scl0_G256_inv0_0 ^ b_G4_scl_N20_G16_sq_scl0_G256_inv0_0;
  p_G4_scl_N20_G16_sq_scl0_G256_inv0_1 = a_G4_scl_N20_G16_sq_scl0_G256_inv0_1 ^ b_G4_scl_N20_G16_sq_scl0_G256_inv0_1;
  q_G4_scl_N20_G16_sq_scl0_G256_inv0_0 = a_G4_scl_N20_G16_sq_scl0_G256_inv0_0;
  q_G4_scl_N20_G16_sq_scl0_G256_inv0_1 = a_G4_scl_N20_G16_sq_scl0_G256_inv0_1;
  temp_var_1_G4_scl_N20_G16_sq_scl0_G256_inv0_0 = p_G4_scl_N20_G16_sq_scl0_G256_inv0_0 << dec_1;
  temp_var_1_G4_scl_N20_G16_sq_scl0_G256_inv0_1 = p_G4_scl_N20_G16_sq_scl0_G256_inv0_1 << dec_1;
  q_G16_sq_scl0_G256_inv0_0 = temp_var_1_G4_scl_N20_G16_sq_scl0_G256_inv0_0 | q_G4_scl_N20_G16_sq_scl0_G256_inv0_0;
  q_G16_sq_scl0_G256_inv0_1 = temp_var_1_G4_scl_N20_G16_sq_scl0_G256_inv0_1 | q_G4_scl_N20_G16_sq_scl0_G256_inv0_1;
  temp_var_3_G16_sq_scl0_G256_inv0_0 = p_G16_sq_scl0_G256_inv0_0 << dec_2;
  temp_var_3_G16_sq_scl0_G256_inv0_1 = p_G16_sq_scl0_G256_inv0_1 << dec_2;
  c_G256_inv0_0 = temp_var_3_G16_sq_scl0_G256_inv0_0 | q_G16_sq_scl0_G256_inv0_0;
  c_G256_inv0_1 = temp_var_3_G16_sq_scl0_G256_inv0_1 | q_G16_sq_scl0_G256_inv0_1;
  temp_var_0_G16_mul0_G256_inv0_0 = a_G256_inv0_0 & dec_12;
  temp_var_0_G16_mul0_G256_inv0_1 = a_G256_inv0_1 & dec_12;
  a_G16_mul0_G256_inv0_0 = temp_var_0_G16_mul0_G256_inv0_0 >> dec_2;
  a_G16_mul0_G256_inv0_1 = temp_var_0_G16_mul0_G256_inv0_1 >> dec_2;
  b_G16_mul0_G256_inv0_0 = a_G256_inv0_0 & dec_3;
  b_G16_mul0_G256_inv0_1 = a_G256_inv0_1 & dec_3;
  temp_var_1_G16_mul0_G256_inv0_0 = b_G256_inv0_0 & dec_12;
  temp_var_1_G16_mul0_G256_inv0_1 = b_G256_inv0_1 & dec_12;
  c_G16_mul0_G256_inv0_0 = temp_var_1_G16_mul0_G256_inv0_0 >> dec_2;
  c_G16_mul0_G256_inv0_1 = temp_var_1_G16_mul0_G256_inv0_1 >> dec_2;
  d_G16_mul0_G256_inv0_0 = b_G256_inv0_0 & dec_3;
  d_G16_mul0_G256_inv0_1 = b_G256_inv0_1 & dec_3;
  temp_var_2_G16_mul0_G256_inv0_0 = a_G16_mul0_G256_inv0_0 ^ b_G16_mul0_G256_inv0_0;
  temp_var_2_G16_mul0_G256_inv0_1 = a_G16_mul0_G256_inv0_1 ^ b_G16_mul0_G256_inv0_1;
  temp_var_3_G16_mul0_G256_inv0_0 = c_G16_mul0_G256_inv0_0 ^ d_G16_mul0_G256_inv0_0;
  temp_var_3_G16_mul0_G256_inv0_1 = c_G16_mul0_G256_inv0_1 ^ d_G16_mul0_G256_inv0_1;
  temp_var_0_G4_mul0_G16_mul0_G256_inv0_0 = temp_var_2_G16_mul0_G256_inv0_0 & dec_2;
  temp_var_0_G4_mul0_G16_mul0_G256_inv0_1 = temp_var_2_G16_mul0_G256_inv0_1 & dec_2;
  a_G4_mul0_G16_mul0_G256_inv0_0 = temp_var_0_G4_mul0_G16_mul0_G256_inv0_0 >> dec_1;
  a_G4_mul0_G16_mul0_G256_inv0_1 = temp_var_0_G4_mul0_G16_mul0_G256_inv0_1 >> dec_1;
  b_G4_mul0_G16_mul0_G256_inv0_0 = temp_var_2_G16_mul0_G256_inv0_0 & dec_1;
  b_G4_mul0_G16_mul0_G256_inv0_1 = temp_var_2_G16_mul0_G256_inv0_1 & dec_1;
  temp_var_1_G4_mul0_G16_mul0_G256_inv0_0 = temp_var_3_G16_mul0_G256_inv0_0 & dec_2;
  temp_var_1_G4_mul0_G16_mul0_G256_inv0_1 = temp_var_3_G16_mul0_G256_inv0_1 & dec_2;
  c_G4_mul0_G16_mul0_G256_inv0_0 = temp_var_1_G4_mul0_G16_mul0_G256_inv0_0 >> dec_1;
  c_G4_mul0_G16_mul0_G256_inv0_1 = temp_var_1_G4_mul0_G16_mul0_G256_inv0_1 >> dec_1;
  d_G4_mul0_G16_mul0_G256_inv0_0 = temp_var_3_G16_mul0_G256_inv0_0 & dec_1;
  d_G4_mul0_G16_mul0_G256_inv0_1 = temp_var_3_G16_mul0_G256_inv0_1 & dec_1;
  temp_var_2_G4_mul0_G16_mul0_G256_inv0_0 = a_G4_mul0_G16_mul0_G256_inv0_0 ^ b_G4_mul0_G16_mul0_G256_inv0_0;
  temp_var_2_G4_mul0_G16_mul0_G256_inv0_1 = a_G4_mul0_G16_mul0_G256_inv0_1 ^ b_G4_mul0_G16_mul0_G256_inv0_1;
  temp_var_3_G4_mul0_G16_mul0_G256_inv0_0 = c_G4_mul0_G16_mul0_G256_inv0_0 ^ d_G4_mul0_G16_mul0_G256_inv0_0;
  temp_var_3_G4_mul0_G16_mul0_G256_inv0_1 = c_G4_mul0_G16_mul0_G256_inv0_1 ^ d_G4_mul0_G16_mul0_G256_inv0_1;
  HPC3(temp_var_3_G4_mul0_G16_mul0_G256_inv0_0, temp_var_3_G4_mul0_G16_mul0_G256_inv0_1, temp_var_2_G4_mul0_G16_mul0_G256_inv0_0, temp_var_2_G4_mul0_G16_mul0_G256_inv0_1, &e_G4_mul0_G16_mul0_G256_inv0_0, &e_G4_mul0_G16_mul0_G256_inv0_1, rand_1, rand_2);
  HPC3(c_G4_mul0_G16_mul0_G256_inv0_0, c_G4_mul0_G16_mul0_G256_inv0_1, a_G4_mul0_G16_mul0_G256_inv0_0, a_G4_mul0_G16_mul0_G256_inv0_1, &temp_var_4_G4_mul0_G16_mul0_G256_inv0_0, &temp_var_4_G4_mul0_G16_mul0_G256_inv0_1, rand_3, rand_4);
  p_G4_mul0_G16_mul0_G256_inv0_0 = temp_var_4_G4_mul0_G16_mul0_G256_inv0_0 ^ e_G4_mul0_G16_mul0_G256_inv0_0;
  p_G4_mul0_G16_mul0_G256_inv0_1 = temp_var_4_G4_mul0_G16_mul0_G256_inv0_1 ^ e_G4_mul0_G16_mul0_G256_inv0_1;
  HPC3(d_G4_mul0_G16_mul0_G256_inv0_0, d_G4_mul0_G16_mul0_G256_inv0_1, b_G4_mul0_G16_mul0_G256_inv0_0, b_G4_mul0_G16_mul0_G256_inv0_1, &temp_var_5_G4_mul0_G16_mul0_G256_inv0_0, &temp_var_5_G4_mul0_G16_mul0_G256_inv0_1, rand_5, rand_6);
  q_G4_mul0_G16_mul0_G256_inv0_0 = temp_var_5_G4_mul0_G16_mul0_G256_inv0_0 ^ e_G4_mul0_G16_mul0_G256_inv0_0;
  q_G4_mul0_G16_mul0_G256_inv0_1 = temp_var_5_G4_mul0_G16_mul0_G256_inv0_1 ^ e_G4_mul0_G16_mul0_G256_inv0_1;
  temp_var_6_G4_mul0_G16_mul0_G256_inv0_0 = p_G4_mul0_G16_mul0_G256_inv0_0 << dec_1;
  temp_var_6_G4_mul0_G16_mul0_G256_inv0_1 = p_G4_mul0_G16_mul0_G256_inv0_1 << dec_1;
  e_G16_mul0_G256_inv0_0 = temp_var_6_G4_mul0_G16_mul0_G256_inv0_0 | q_G4_mul0_G16_mul0_G256_inv0_0;
  e_G16_mul0_G256_inv0_1 = temp_var_6_G4_mul0_G16_mul0_G256_inv0_1 | q_G4_mul0_G16_mul0_G256_inv0_1;
  temp_var_0_G4_scl_N0_G16_mul0_G256_inv0_0 = e_G16_mul0_G256_inv0_0 & dec_2;
  temp_var_0_G4_scl_N0_G16_mul0_G256_inv0_1 = e_G16_mul0_G256_inv0_1 & dec_2;
  a_G4_scl_N0_G16_mul0_G256_inv0_0 = temp_var_0_G4_scl_N0_G16_mul0_G256_inv0_0 >> dec_1;
  a_G4_scl_N0_G16_mul0_G256_inv0_1 = temp_var_0_G4_scl_N0_G16_mul0_G256_inv0_1 >> dec_1;
  b_G4_scl_N0_G16_mul0_G256_inv0_0 = e_G16_mul0_G256_inv0_0 & dec_1;
  b_G4_scl_N0_G16_mul0_G256_inv0_1 = e_G16_mul0_G256_inv0_1 & dec_1;
  p_G4_scl_N0_G16_mul0_G256_inv0_0 = b_G4_scl_N0_G16_mul0_G256_inv0_0;
  p_G4_scl_N0_G16_mul0_G256_inv0_1 = b_G4_scl_N0_G16_mul0_G256_inv0_1;
  q_G4_scl_N0_G16_mul0_G256_inv0_0 = a_G4_scl_N0_G16_mul0_G256_inv0_0 ^ b_G4_scl_N0_G16_mul0_G256_inv0_0;
  q_G4_scl_N0_G16_mul0_G256_inv0_1 = a_G4_scl_N0_G16_mul0_G256_inv0_1 ^ b_G4_scl_N0_G16_mul0_G256_inv0_1;
  temp_var_1_G4_scl_N0_G16_mul0_G256_inv0_0 = p_G4_scl_N0_G16_mul0_G256_inv0_0 << dec_1;
  temp_var_1_G4_scl_N0_G16_mul0_G256_inv0_1 = p_G4_scl_N0_G16_mul0_G256_inv0_1 << dec_1;
  _1_version_e_G16_mul0_G256_inv0_0 = temp_var_1_G4_scl_N0_G16_mul0_G256_inv0_0 | q_G4_scl_N0_G16_mul0_G256_inv0_0;
  _1_version_e_G16_mul0_G256_inv0_1 = temp_var_1_G4_scl_N0_G16_mul0_G256_inv0_1 | q_G4_scl_N0_G16_mul0_G256_inv0_1;
  temp_var_0_G4_mul1_G16_mul0_G256_inv0_0 = a_G16_mul0_G256_inv0_0 & dec_2;
  temp_var_0_G4_mul1_G16_mul0_G256_inv0_1 = a_G16_mul0_G256_inv0_1 & dec_2;
  a_G4_mul1_G16_mul0_G256_inv0_0 = temp_var_0_G4_mul1_G16_mul0_G256_inv0_0 >> dec_1;
  a_G4_mul1_G16_mul0_G256_inv0_1 = temp_var_0_G4_mul1_G16_mul0_G256_inv0_1 >> dec_1;
  b_G4_mul1_G16_mul0_G256_inv0_0 = a_G16_mul0_G256_inv0_0 & dec_1;
  b_G4_mul1_G16_mul0_G256_inv0_1 = a_G16_mul0_G256_inv0_1 & dec_1;
  temp_var_1_G4_mul1_G16_mul0_G256_inv0_0 = c_G16_mul0_G256_inv0_0 & dec_2;
  temp_var_1_G4_mul1_G16_mul0_G256_inv0_1 = c_G16_mul0_G256_inv0_1 & dec_2;
  c_G4_mul1_G16_mul0_G256_inv0_0 = temp_var_1_G4_mul1_G16_mul0_G256_inv0_0 >> dec_1;
  c_G4_mul1_G16_mul0_G256_inv0_1 = temp_var_1_G4_mul1_G16_mul0_G256_inv0_1 >> dec_1;
  d_G4_mul1_G16_mul0_G256_inv0_0 = c_G16_mul0_G256_inv0_0 & dec_1;
  d_G4_mul1_G16_mul0_G256_inv0_1 = c_G16_mul0_G256_inv0_1 & dec_1;
  temp_var_2_G4_mul1_G16_mul0_G256_inv0_0 = a_G4_mul1_G16_mul0_G256_inv0_0 ^ b_G4_mul1_G16_mul0_G256_inv0_0;
  temp_var_2_G4_mul1_G16_mul0_G256_inv0_1 = a_G4_mul1_G16_mul0_G256_inv0_1 ^ b_G4_mul1_G16_mul0_G256_inv0_1;
  temp_var_3_G4_mul1_G16_mul0_G256_inv0_0 = c_G4_mul1_G16_mul0_G256_inv0_0 ^ d_G4_mul1_G16_mul0_G256_inv0_0;
  temp_var_3_G4_mul1_G16_mul0_G256_inv0_1 = c_G4_mul1_G16_mul0_G256_inv0_1 ^ d_G4_mul1_G16_mul0_G256_inv0_1;
  HPC3(temp_var_3_G4_mul1_G16_mul0_G256_inv0_0, temp_var_3_G4_mul1_G16_mul0_G256_inv0_1, temp_var_2_G4_mul1_G16_mul0_G256_inv0_0, temp_var_2_G4_mul1_G16_mul0_G256_inv0_1, &e_G4_mul1_G16_mul0_G256_inv0_0, &e_G4_mul1_G16_mul0_G256_inv0_1, rand_7, rand_8);
  HPC3(c_G4_mul1_G16_mul0_G256_inv0_0, c_G4_mul1_G16_mul0_G256_inv0_1, a_G4_mul1_G16_mul0_G256_inv0_0, a_G4_mul1_G16_mul0_G256_inv0_1, &temp_var_4_G4_mul1_G16_mul0_G256_inv0_0, &temp_var_4_G4_mul1_G16_mul0_G256_inv0_1, rand_9, rand_10);
  p_G4_mul1_G16_mul0_G256_inv0_0 = temp_var_4_G4_mul1_G16_mul0_G256_inv0_0 ^ e_G4_mul1_G16_mul0_G256_inv0_0;
  p_G4_mul1_G16_mul0_G256_inv0_1 = temp_var_4_G4_mul1_G16_mul0_G256_inv0_1 ^ e_G4_mul1_G16_mul0_G256_inv0_1;
  HPC3(d_G4_mul1_G16_mul0_G256_inv0_0, d_G4_mul1_G16_mul0_G256_inv0_1, b_G4_mul1_G16_mul0_G256_inv0_0, b_G4_mul1_G16_mul0_G256_inv0_1, &temp_var_5_G4_mul1_G16_mul0_G256_inv0_0, &temp_var_5_G4_mul1_G16_mul0_G256_inv0_1, rand_11, rand_12);
  q_G4_mul1_G16_mul0_G256_inv0_0 = temp_var_5_G4_mul1_G16_mul0_G256_inv0_0 ^ e_G4_mul1_G16_mul0_G256_inv0_0;
  q_G4_mul1_G16_mul0_G256_inv0_1 = temp_var_5_G4_mul1_G16_mul0_G256_inv0_1 ^ e_G4_mul1_G16_mul0_G256_inv0_1;
  temp_var_6_G4_mul1_G16_mul0_G256_inv0_0 = p_G4_mul1_G16_mul0_G256_inv0_0 << dec_1;
  temp_var_6_G4_mul1_G16_mul0_G256_inv0_1 = p_G4_mul1_G16_mul0_G256_inv0_1 << dec_1;
  temp_var_4_G16_mul0_G256_inv0_0 = temp_var_6_G4_mul1_G16_mul0_G256_inv0_0 | q_G4_mul1_G16_mul0_G256_inv0_0;
  temp_var_4_G16_mul0_G256_inv0_1 = temp_var_6_G4_mul1_G16_mul0_G256_inv0_1 | q_G4_mul1_G16_mul0_G256_inv0_1;
  p_G16_mul0_G256_inv0_0 = temp_var_4_G16_mul0_G256_inv0_0 ^ _1_version_e_G16_mul0_G256_inv0_0;
  p_G16_mul0_G256_inv0_1 = temp_var_4_G16_mul0_G256_inv0_1 ^ _1_version_e_G16_mul0_G256_inv0_1;
  temp_var_0_G4_mul2_G16_mul0_G256_inv0_0 = b_G16_mul0_G256_inv0_0 & dec_2;
  temp_var_0_G4_mul2_G16_mul0_G256_inv0_1 = b_G16_mul0_G256_inv0_1 & dec_2;
  a_G4_mul2_G16_mul0_G256_inv0_0 = temp_var_0_G4_mul2_G16_mul0_G256_inv0_0 >> dec_1;
  a_G4_mul2_G16_mul0_G256_inv0_1 = temp_var_0_G4_mul2_G16_mul0_G256_inv0_1 >> dec_1;
  b_G4_mul2_G16_mul0_G256_inv0_0 = b_G16_mul0_G256_inv0_0 & dec_1;
  b_G4_mul2_G16_mul0_G256_inv0_1 = b_G16_mul0_G256_inv0_1 & dec_1;
  temp_var_1_G4_mul2_G16_mul0_G256_inv0_0 = d_G16_mul0_G256_inv0_0 & dec_2;
  temp_var_1_G4_mul2_G16_mul0_G256_inv0_1 = d_G16_mul0_G256_inv0_1 & dec_2;
  c_G4_mul2_G16_mul0_G256_inv0_0 = temp_var_1_G4_mul2_G16_mul0_G256_inv0_0 >> dec_1;
  c_G4_mul2_G16_mul0_G256_inv0_1 = temp_var_1_G4_mul2_G16_mul0_G256_inv0_1 >> dec_1;
  d_G4_mul2_G16_mul0_G256_inv0_0 = d_G16_mul0_G256_inv0_0 & dec_1;
  d_G4_mul2_G16_mul0_G256_inv0_1 = d_G16_mul0_G256_inv0_1 & dec_1;
  temp_var_2_G4_mul2_G16_mul0_G256_inv0_0 = a_G4_mul2_G16_mul0_G256_inv0_0 ^ b_G4_mul2_G16_mul0_G256_inv0_0;
  temp_var_2_G4_mul2_G16_mul0_G256_inv0_1 = a_G4_mul2_G16_mul0_G256_inv0_1 ^ b_G4_mul2_G16_mul0_G256_inv0_1;
  temp_var_3_G4_mul2_G16_mul0_G256_inv0_0 = c_G4_mul2_G16_mul0_G256_inv0_0 ^ d_G4_mul2_G16_mul0_G256_inv0_0;
  temp_var_3_G4_mul2_G16_mul0_G256_inv0_1 = c_G4_mul2_G16_mul0_G256_inv0_1 ^ d_G4_mul2_G16_mul0_G256_inv0_1;
  HPC3(temp_var_3_G4_mul2_G16_mul0_G256_inv0_0, temp_var_3_G4_mul2_G16_mul0_G256_inv0_1, temp_var_2_G4_mul2_G16_mul0_G256_inv0_0, temp_var_2_G4_mul2_G16_mul0_G256_inv0_1, &e_G4_mul2_G16_mul0_G256_inv0_0, &e_G4_mul2_G16_mul0_G256_inv0_1, rand_13, rand_14);
  HPC3(c_G4_mul2_G16_mul0_G256_inv0_0, c_G4_mul2_G16_mul0_G256_inv0_1, a_G4_mul2_G16_mul0_G256_inv0_0, a_G4_mul2_G16_mul0_G256_inv0_1, &temp_var_4_G4_mul2_G16_mul0_G256_inv0_0, &temp_var_4_G4_mul2_G16_mul0_G256_inv0_1, rand_15, rand_16);
  p_G4_mul2_G16_mul0_G256_inv0_0 = temp_var_4_G4_mul2_G16_mul0_G256_inv0_0 ^ e_G4_mul2_G16_mul0_G256_inv0_0;
  p_G4_mul2_G16_mul0_G256_inv0_1 = temp_var_4_G4_mul2_G16_mul0_G256_inv0_1 ^ e_G4_mul2_G16_mul0_G256_inv0_1;
  HPC3(d_G4_mul2_G16_mul0_G256_inv0_0, d_G4_mul2_G16_mul0_G256_inv0_1, b_G4_mul2_G16_mul0_G256_inv0_0, b_G4_mul2_G16_mul0_G256_inv0_1, &temp_var_5_G4_mul2_G16_mul0_G256_inv0_0, &temp_var_5_G4_mul2_G16_mul0_G256_inv0_1, rand_17, rand_18);
  q_G4_mul2_G16_mul0_G256_inv0_0 = temp_var_5_G4_mul2_G16_mul0_G256_inv0_0 ^ e_G4_mul2_G16_mul0_G256_inv0_0;
  q_G4_mul2_G16_mul0_G256_inv0_1 = temp_var_5_G4_mul2_G16_mul0_G256_inv0_1 ^ e_G4_mul2_G16_mul0_G256_inv0_1;
  temp_var_6_G4_mul2_G16_mul0_G256_inv0_0 = p_G4_mul2_G16_mul0_G256_inv0_0 << dec_1;
  temp_var_6_G4_mul2_G16_mul0_G256_inv0_1 = p_G4_mul2_G16_mul0_G256_inv0_1 << dec_1;
  temp_var_5_G16_mul0_G256_inv0_0 = temp_var_6_G4_mul2_G16_mul0_G256_inv0_0 | q_G4_mul2_G16_mul0_G256_inv0_0;
  temp_var_5_G16_mul0_G256_inv0_1 = temp_var_6_G4_mul2_G16_mul0_G256_inv0_1 | q_G4_mul2_G16_mul0_G256_inv0_1;
  q_G16_mul0_G256_inv0_0 = temp_var_5_G16_mul0_G256_inv0_0 ^ _1_version_e_G16_mul0_G256_inv0_0;
  q_G16_mul0_G256_inv0_1 = temp_var_5_G16_mul0_G256_inv0_1 ^ _1_version_e_G16_mul0_G256_inv0_1;
  temp_var_6_G16_mul0_G256_inv0_0 = p_G16_mul0_G256_inv0_0 << dec_2;
  temp_var_6_G16_mul0_G256_inv0_1 = p_G16_mul0_G256_inv0_1 << dec_2;
  d_G256_inv0_0 = temp_var_6_G16_mul0_G256_inv0_0 | q_G16_mul0_G256_inv0_0;
  d_G256_inv0_1 = temp_var_6_G16_mul0_G256_inv0_1 | q_G16_mul0_G256_inv0_1;
  temp_var_2_G256_inv0_0 = c_G256_inv0_0 ^ d_G256_inv0_0;
  temp_var_2_G256_inv0_1 = c_G256_inv0_1 ^ d_G256_inv0_1;
  temp_var_0_G16_inv0_G256_inv0_0 = temp_var_2_G256_inv0_0 & dec_12;
  temp_var_0_G16_inv0_G256_inv0_1 = temp_var_2_G256_inv0_1 & dec_12;
  a_G16_inv0_G256_inv0_0 = temp_var_0_G16_inv0_G256_inv0_0 >> dec_2;
  a_G16_inv0_G256_inv0_1 = temp_var_0_G16_inv0_G256_inv0_1 >> dec_2;
  b_G16_inv0_G256_inv0_0 = temp_var_2_G256_inv0_0 & dec_3;
  b_G16_inv0_G256_inv0_1 = temp_var_2_G256_inv0_1 & dec_3;
  temp_var_2_G16_inv0_G256_inv0_0 = a_G16_inv0_G256_inv0_0 ^ b_G16_inv0_G256_inv0_0;
  temp_var_2_G16_inv0_G256_inv0_1 = a_G16_inv0_G256_inv0_1 ^ b_G16_inv0_G256_inv0_1;
  temp_var_0_G4_sq2_G16_inv0_G256_inv0_0 = temp_var_2_G16_inv0_G256_inv0_0 & dec_2;
  temp_var_0_G4_sq2_G16_inv0_G256_inv0_1 = temp_var_2_G16_inv0_G256_inv0_1 & dec_2;
  a_G4_sq2_G16_inv0_G256_inv0_0 = temp_var_0_G4_sq2_G16_inv0_G256_inv0_0 >> dec_1;
  a_G4_sq2_G16_inv0_G256_inv0_1 = temp_var_0_G4_sq2_G16_inv0_G256_inv0_1 >> dec_1;
  b_G4_sq2_G16_inv0_G256_inv0_0 = temp_var_2_G16_inv0_G256_inv0_0 & dec_1;
  b_G4_sq2_G16_inv0_G256_inv0_1 = temp_var_2_G16_inv0_G256_inv0_1 & dec_1;
  temp_var_1_G4_sq2_G16_inv0_G256_inv0_0 = b_G4_sq2_G16_inv0_G256_inv0_0 << dec_1;
  temp_var_1_G4_sq2_G16_inv0_G256_inv0_1 = b_G4_sq2_G16_inv0_G256_inv0_1 << dec_1;
  temp_var_1_G16_inv0_G256_inv0_0 = temp_var_1_G4_sq2_G16_inv0_G256_inv0_0 | a_G4_sq2_G16_inv0_G256_inv0_0;
  temp_var_1_G16_inv0_G256_inv0_1 = temp_var_1_G4_sq2_G16_inv0_G256_inv0_1 | a_G4_sq2_G16_inv0_G256_inv0_1;
  temp_var_0_G4_scl_N1_G16_inv0_G256_inv0_0 = temp_var_1_G16_inv0_G256_inv0_0 & dec_2;
  temp_var_0_G4_scl_N1_G16_inv0_G256_inv0_1 = temp_var_1_G16_inv0_G256_inv0_1 & dec_2;
  a_G4_scl_N1_G16_inv0_G256_inv0_0 = temp_var_0_G4_scl_N1_G16_inv0_G256_inv0_0 >> dec_1;
  a_G4_scl_N1_G16_inv0_G256_inv0_1 = temp_var_0_G4_scl_N1_G16_inv0_G256_inv0_1 >> dec_1;
  b_G4_scl_N1_G16_inv0_G256_inv0_0 = temp_var_1_G16_inv0_G256_inv0_0 & dec_1;
  b_G4_scl_N1_G16_inv0_G256_inv0_1 = temp_var_1_G16_inv0_G256_inv0_1 & dec_1;
  p_G4_scl_N1_G16_inv0_G256_inv0_0 = b_G4_scl_N1_G16_inv0_G256_inv0_0;
  p_G4_scl_N1_G16_inv0_G256_inv0_1 = b_G4_scl_N1_G16_inv0_G256_inv0_1;
  q_G4_scl_N1_G16_inv0_G256_inv0_0 = a_G4_scl_N1_G16_inv0_G256_inv0_0 ^ b_G4_scl_N1_G16_inv0_G256_inv0_0;
  q_G4_scl_N1_G16_inv0_G256_inv0_1 = a_G4_scl_N1_G16_inv0_G256_inv0_1 ^ b_G4_scl_N1_G16_inv0_G256_inv0_1;
  temp_var_1_G4_scl_N1_G16_inv0_G256_inv0_0 = p_G4_scl_N1_G16_inv0_G256_inv0_0 << dec_1;
  temp_var_1_G4_scl_N1_G16_inv0_G256_inv0_1 = p_G4_scl_N1_G16_inv0_G256_inv0_1 << dec_1;
  c_G16_inv0_G256_inv0_0 = temp_var_1_G4_scl_N1_G16_inv0_G256_inv0_0 | q_G4_scl_N1_G16_inv0_G256_inv0_0;
  c_G16_inv0_G256_inv0_1 = temp_var_1_G4_scl_N1_G16_inv0_G256_inv0_1 | q_G4_scl_N1_G16_inv0_G256_inv0_1;
  temp_var_0_G4_mul3_G16_inv0_G256_inv0_0 = a_G16_inv0_G256_inv0_0 & dec_2;
  temp_var_0_G4_mul3_G16_inv0_G256_inv0_1 = a_G16_inv0_G256_inv0_1 & dec_2;
  a_G4_mul3_G16_inv0_G256_inv0_0 = temp_var_0_G4_mul3_G16_inv0_G256_inv0_0 >> dec_1;
  a_G4_mul3_G16_inv0_G256_inv0_1 = temp_var_0_G4_mul3_G16_inv0_G256_inv0_1 >> dec_1;
  b_G4_mul3_G16_inv0_G256_inv0_0 = a_G16_inv0_G256_inv0_0 & dec_1;
  b_G4_mul3_G16_inv0_G256_inv0_1 = a_G16_inv0_G256_inv0_1 & dec_1;
  temp_var_1_G4_mul3_G16_inv0_G256_inv0_0 = b_G16_inv0_G256_inv0_0 & dec_2;
  temp_var_1_G4_mul3_G16_inv0_G256_inv0_1 = b_G16_inv0_G256_inv0_1 & dec_2;
  c_G4_mul3_G16_inv0_G256_inv0_0 = temp_var_1_G4_mul3_G16_inv0_G256_inv0_0 >> dec_1;
  c_G4_mul3_G16_inv0_G256_inv0_1 = temp_var_1_G4_mul3_G16_inv0_G256_inv0_1 >> dec_1;
  d_G4_mul3_G16_inv0_G256_inv0_0 = b_G16_inv0_G256_inv0_0 & dec_1;
  d_G4_mul3_G16_inv0_G256_inv0_1 = b_G16_inv0_G256_inv0_1 & dec_1;
  temp_var_2_G4_mul3_G16_inv0_G256_inv0_0 = a_G4_mul3_G16_inv0_G256_inv0_0 ^ b_G4_mul3_G16_inv0_G256_inv0_0;
  temp_var_2_G4_mul3_G16_inv0_G256_inv0_1 = a_G4_mul3_G16_inv0_G256_inv0_1 ^ b_G4_mul3_G16_inv0_G256_inv0_1;
  temp_var_3_G4_mul3_G16_inv0_G256_inv0_0 = c_G4_mul3_G16_inv0_G256_inv0_0 ^ d_G4_mul3_G16_inv0_G256_inv0_0;
  temp_var_3_G4_mul3_G16_inv0_G256_inv0_1 = c_G4_mul3_G16_inv0_G256_inv0_1 ^ d_G4_mul3_G16_inv0_G256_inv0_1;
  HPC3(temp_var_3_G4_mul3_G16_inv0_G256_inv0_0, temp_var_3_G4_mul3_G16_inv0_G256_inv0_1, temp_var_2_G4_mul3_G16_inv0_G256_inv0_0, temp_var_2_G4_mul3_G16_inv0_G256_inv0_1, &e_G4_mul3_G16_inv0_G256_inv0_0, &e_G4_mul3_G16_inv0_G256_inv0_1, rand_19, rand_20);
  HPC3(c_G4_mul3_G16_inv0_G256_inv0_0, c_G4_mul3_G16_inv0_G256_inv0_1, a_G4_mul3_G16_inv0_G256_inv0_0, a_G4_mul3_G16_inv0_G256_inv0_1, &temp_var_4_G4_mul3_G16_inv0_G256_inv0_0, &temp_var_4_G4_mul3_G16_inv0_G256_inv0_1, rand_21, rand_22);
  p_G4_mul3_G16_inv0_G256_inv0_0 = temp_var_4_G4_mul3_G16_inv0_G256_inv0_0 ^ e_G4_mul3_G16_inv0_G256_inv0_0;
  p_G4_mul3_G16_inv0_G256_inv0_1 = temp_var_4_G4_mul3_G16_inv0_G256_inv0_1 ^ e_G4_mul3_G16_inv0_G256_inv0_1;
  HPC3(d_G4_mul3_G16_inv0_G256_inv0_0, d_G4_mul3_G16_inv0_G256_inv0_1, b_G4_mul3_G16_inv0_G256_inv0_0, b_G4_mul3_G16_inv0_G256_inv0_1, &temp_var_5_G4_mul3_G16_inv0_G256_inv0_0, &temp_var_5_G4_mul3_G16_inv0_G256_inv0_1, rand_23, rand_24);
  q_G4_mul3_G16_inv0_G256_inv0_0 = temp_var_5_G4_mul3_G16_inv0_G256_inv0_0 ^ e_G4_mul3_G16_inv0_G256_inv0_0;
  q_G4_mul3_G16_inv0_G256_inv0_1 = temp_var_5_G4_mul3_G16_inv0_G256_inv0_1 ^ e_G4_mul3_G16_inv0_G256_inv0_1;
  temp_var_6_G4_mul3_G16_inv0_G256_inv0_0 = p_G4_mul3_G16_inv0_G256_inv0_0 << dec_1;
  temp_var_6_G4_mul3_G16_inv0_G256_inv0_1 = p_G4_mul3_G16_inv0_G256_inv0_1 << dec_1;
  d_G16_inv0_G256_inv0_0 = temp_var_6_G4_mul3_G16_inv0_G256_inv0_0 | q_G4_mul3_G16_inv0_G256_inv0_0;
  d_G16_inv0_G256_inv0_1 = temp_var_6_G4_mul3_G16_inv0_G256_inv0_1 | q_G4_mul3_G16_inv0_G256_inv0_1;
  temp_var_3_G16_inv0_G256_inv0_0 = c_G16_inv0_G256_inv0_0 ^ d_G16_inv0_G256_inv0_0;
  temp_var_3_G16_inv0_G256_inv0_1 = c_G16_inv0_G256_inv0_1 ^ d_G16_inv0_G256_inv0_1;
  temp_var_0_G4_sq3_G16_inv0_G256_inv0_0 = temp_var_3_G16_inv0_G256_inv0_0 & dec_2;
  temp_var_0_G4_sq3_G16_inv0_G256_inv0_1 = temp_var_3_G16_inv0_G256_inv0_1 & dec_2;
  a_G4_sq3_G16_inv0_G256_inv0_0 = temp_var_0_G4_sq3_G16_inv0_G256_inv0_0 >> dec_1;
  a_G4_sq3_G16_inv0_G256_inv0_1 = temp_var_0_G4_sq3_G16_inv0_G256_inv0_1 >> dec_1;
  b_G4_sq3_G16_inv0_G256_inv0_0 = temp_var_3_G16_inv0_G256_inv0_0 & dec_1;
  b_G4_sq3_G16_inv0_G256_inv0_1 = temp_var_3_G16_inv0_G256_inv0_1 & dec_1;
  temp_var_1_G4_sq3_G16_inv0_G256_inv0_0 = b_G4_sq3_G16_inv0_G256_inv0_0 << dec_1;
  temp_var_1_G4_sq3_G16_inv0_G256_inv0_1 = b_G4_sq3_G16_inv0_G256_inv0_1 << dec_1;
  e_G16_inv0_G256_inv0_0 = temp_var_1_G4_sq3_G16_inv0_G256_inv0_0 | a_G4_sq3_G16_inv0_G256_inv0_0;
  e_G16_inv0_G256_inv0_1 = temp_var_1_G4_sq3_G16_inv0_G256_inv0_1 | a_G4_sq3_G16_inv0_G256_inv0_1;
  temp_var_0_G4_mul4_G16_inv0_G256_inv0_0 = e_G16_inv0_G256_inv0_0 & dec_2;
  temp_var_0_G4_mul4_G16_inv0_G256_inv0_1 = e_G16_inv0_G256_inv0_1 & dec_2;
  a_G4_mul4_G16_inv0_G256_inv0_0 = temp_var_0_G4_mul4_G16_inv0_G256_inv0_0 >> dec_1;
  a_G4_mul4_G16_inv0_G256_inv0_1 = temp_var_0_G4_mul4_G16_inv0_G256_inv0_1 >> dec_1;
  b_G4_mul4_G16_inv0_G256_inv0_0 = e_G16_inv0_G256_inv0_0 & dec_1;
  b_G4_mul4_G16_inv0_G256_inv0_1 = e_G16_inv0_G256_inv0_1 & dec_1;
  temp_var_1_G4_mul4_G16_inv0_G256_inv0_0 = b_G16_inv0_G256_inv0_0 & dec_2;
  temp_var_1_G4_mul4_G16_inv0_G256_inv0_1 = b_G16_inv0_G256_inv0_1 & dec_2;
  c_G4_mul4_G16_inv0_G256_inv0_0 = temp_var_1_G4_mul4_G16_inv0_G256_inv0_0 >> dec_1;
  c_G4_mul4_G16_inv0_G256_inv0_1 = temp_var_1_G4_mul4_G16_inv0_G256_inv0_1 >> dec_1;
  d_G4_mul4_G16_inv0_G256_inv0_0 = b_G16_inv0_G256_inv0_0 & dec_1;
  d_G4_mul4_G16_inv0_G256_inv0_1 = b_G16_inv0_G256_inv0_1 & dec_1;
  temp_var_2_G4_mul4_G16_inv0_G256_inv0_0 = a_G4_mul4_G16_inv0_G256_inv0_0 ^ b_G4_mul4_G16_inv0_G256_inv0_0;
  temp_var_2_G4_mul4_G16_inv0_G256_inv0_1 = a_G4_mul4_G16_inv0_G256_inv0_1 ^ b_G4_mul4_G16_inv0_G256_inv0_1;
  temp_var_3_G4_mul4_G16_inv0_G256_inv0_0 = c_G4_mul4_G16_inv0_G256_inv0_0 ^ d_G4_mul4_G16_inv0_G256_inv0_0;
  temp_var_3_G4_mul4_G16_inv0_G256_inv0_1 = c_G4_mul4_G16_inv0_G256_inv0_1 ^ d_G4_mul4_G16_inv0_G256_inv0_1;
  HPC2(temp_var_2_G4_mul4_G16_inv0_G256_inv0_0, temp_var_2_G4_mul4_G16_inv0_G256_inv0_1, temp_var_3_G4_mul4_G16_inv0_G256_inv0_0, temp_var_3_G4_mul4_G16_inv0_G256_inv0_1, &e_G4_mul4_G16_inv0_G256_inv0_0, &e_G4_mul4_G16_inv0_G256_inv0_1, rand_25);
  HPC2(a_G4_mul4_G16_inv0_G256_inv0_0, a_G4_mul4_G16_inv0_G256_inv0_1, c_G4_mul4_G16_inv0_G256_inv0_0, c_G4_mul4_G16_inv0_G256_inv0_1, &temp_var_4_G4_mul4_G16_inv0_G256_inv0_0, &temp_var_4_G4_mul4_G16_inv0_G256_inv0_1, rand_26);
  p_G4_mul4_G16_inv0_G256_inv0_0 = temp_var_4_G4_mul4_G16_inv0_G256_inv0_0 ^ e_G4_mul4_G16_inv0_G256_inv0_0;
  p_G4_mul4_G16_inv0_G256_inv0_1 = temp_var_4_G4_mul4_G16_inv0_G256_inv0_1 ^ e_G4_mul4_G16_inv0_G256_inv0_1;
  HPC2(b_G4_mul4_G16_inv0_G256_inv0_0, b_G4_mul4_G16_inv0_G256_inv0_1, d_G4_mul4_G16_inv0_G256_inv0_0, d_G4_mul4_G16_inv0_G256_inv0_1, &temp_var_5_G4_mul4_G16_inv0_G256_inv0_0, &temp_var_5_G4_mul4_G16_inv0_G256_inv0_1, rand_27);
  q_G4_mul4_G16_inv0_G256_inv0_0 = temp_var_5_G4_mul4_G16_inv0_G256_inv0_0 ^ e_G4_mul4_G16_inv0_G256_inv0_0;
  q_G4_mul4_G16_inv0_G256_inv0_1 = temp_var_5_G4_mul4_G16_inv0_G256_inv0_1 ^ e_G4_mul4_G16_inv0_G256_inv0_1;
  temp_var_6_G4_mul4_G16_inv0_G256_inv0_0 = p_G4_mul4_G16_inv0_G256_inv0_0 << dec_1;
  temp_var_6_G4_mul4_G16_inv0_G256_inv0_1 = p_G4_mul4_G16_inv0_G256_inv0_1 << dec_1;
  p_G16_inv0_G256_inv0_0 = temp_var_6_G4_mul4_G16_inv0_G256_inv0_0 | q_G4_mul4_G16_inv0_G256_inv0_0;
  p_G16_inv0_G256_inv0_1 = temp_var_6_G4_mul4_G16_inv0_G256_inv0_1 | q_G4_mul4_G16_inv0_G256_inv0_1;
  temp_var_0_G4_mul5_G16_inv0_G256_inv0_0 = e_G16_inv0_G256_inv0_0 & dec_2;
  temp_var_0_G4_mul5_G16_inv0_G256_inv0_1 = e_G16_inv0_G256_inv0_1 & dec_2;
  a_G4_mul5_G16_inv0_G256_inv0_0 = temp_var_0_G4_mul5_G16_inv0_G256_inv0_0 >> dec_1;
  a_G4_mul5_G16_inv0_G256_inv0_1 = temp_var_0_G4_mul5_G16_inv0_G256_inv0_1 >> dec_1;
  b_G4_mul5_G16_inv0_G256_inv0_0 = e_G16_inv0_G256_inv0_0 & dec_1;
  b_G4_mul5_G16_inv0_G256_inv0_1 = e_G16_inv0_G256_inv0_1 & dec_1;
  temp_var_1_G4_mul5_G16_inv0_G256_inv0_0 = a_G16_inv0_G256_inv0_0 & dec_2;
  temp_var_1_G4_mul5_G16_inv0_G256_inv0_1 = a_G16_inv0_G256_inv0_1 & dec_2;
  c_G4_mul5_G16_inv0_G256_inv0_0 = temp_var_1_G4_mul5_G16_inv0_G256_inv0_0 >> dec_1;
  c_G4_mul5_G16_inv0_G256_inv0_1 = temp_var_1_G4_mul5_G16_inv0_G256_inv0_1 >> dec_1;
  d_G4_mul5_G16_inv0_G256_inv0_0 = a_G16_inv0_G256_inv0_0 & dec_1;
  d_G4_mul5_G16_inv0_G256_inv0_1 = a_G16_inv0_G256_inv0_1 & dec_1;
  temp_var_2_G4_mul5_G16_inv0_G256_inv0_0 = a_G4_mul5_G16_inv0_G256_inv0_0 ^ b_G4_mul5_G16_inv0_G256_inv0_0;
  temp_var_2_G4_mul5_G16_inv0_G256_inv0_1 = a_G4_mul5_G16_inv0_G256_inv0_1 ^ b_G4_mul5_G16_inv0_G256_inv0_1;
  temp_var_3_G4_mul5_G16_inv0_G256_inv0_0 = c_G4_mul5_G16_inv0_G256_inv0_0 ^ d_G4_mul5_G16_inv0_G256_inv0_0;
  temp_var_3_G4_mul5_G16_inv0_G256_inv0_1 = c_G4_mul5_G16_inv0_G256_inv0_1 ^ d_G4_mul5_G16_inv0_G256_inv0_1;
  HPC2(temp_var_2_G4_mul5_G16_inv0_G256_inv0_0, temp_var_2_G4_mul5_G16_inv0_G256_inv0_1, temp_var_3_G4_mul5_G16_inv0_G256_inv0_0, temp_var_3_G4_mul5_G16_inv0_G256_inv0_1, &e_G4_mul5_G16_inv0_G256_inv0_0, &e_G4_mul5_G16_inv0_G256_inv0_1, rand_28);
  HPC2(a_G4_mul5_G16_inv0_G256_inv0_0, a_G4_mul5_G16_inv0_G256_inv0_1, c_G4_mul5_G16_inv0_G256_inv0_0, c_G4_mul5_G16_inv0_G256_inv0_1, &temp_var_4_G4_mul5_G16_inv0_G256_inv0_0, &temp_var_4_G4_mul5_G16_inv0_G256_inv0_1, rand_29);
  p_G4_mul5_G16_inv0_G256_inv0_0 = temp_var_4_G4_mul5_G16_inv0_G256_inv0_0 ^ e_G4_mul5_G16_inv0_G256_inv0_0;
  p_G4_mul5_G16_inv0_G256_inv0_1 = temp_var_4_G4_mul5_G16_inv0_G256_inv0_1 ^ e_G4_mul5_G16_inv0_G256_inv0_1;
  HPC2(b_G4_mul5_G16_inv0_G256_inv0_0, b_G4_mul5_G16_inv0_G256_inv0_1, d_G4_mul5_G16_inv0_G256_inv0_0, d_G4_mul5_G16_inv0_G256_inv0_1, &temp_var_5_G4_mul5_G16_inv0_G256_inv0_0, &temp_var_5_G4_mul5_G16_inv0_G256_inv0_1, rand_30);
  q_G4_mul5_G16_inv0_G256_inv0_0 = temp_var_5_G4_mul5_G16_inv0_G256_inv0_0 ^ e_G4_mul5_G16_inv0_G256_inv0_0;
  q_G4_mul5_G16_inv0_G256_inv0_1 = temp_var_5_G4_mul5_G16_inv0_G256_inv0_1 ^ e_G4_mul5_G16_inv0_G256_inv0_1;
  temp_var_6_G4_mul5_G16_inv0_G256_inv0_0 = p_G4_mul5_G16_inv0_G256_inv0_0 << dec_1;
  temp_var_6_G4_mul5_G16_inv0_G256_inv0_1 = p_G4_mul5_G16_inv0_G256_inv0_1 << dec_1;
  q_G16_inv0_G256_inv0_0 = temp_var_6_G4_mul5_G16_inv0_G256_inv0_0 | q_G4_mul5_G16_inv0_G256_inv0_0;
  q_G16_inv0_G256_inv0_1 = temp_var_6_G4_mul5_G16_inv0_G256_inv0_1 | q_G4_mul5_G16_inv0_G256_inv0_1;
  temp_var_4_G16_inv0_G256_inv0_0 = p_G16_inv0_G256_inv0_0 << dec_2;
  temp_var_4_G16_inv0_G256_inv0_1 = p_G16_inv0_G256_inv0_1 << dec_2;
  e_G256_inv0_0 = temp_var_4_G16_inv0_G256_inv0_0 | q_G16_inv0_G256_inv0_0;
  e_G256_inv0_1 = temp_var_4_G16_inv0_G256_inv0_1 | q_G16_inv0_G256_inv0_1;
  temp_var_0_G16_mul1_G256_inv0_0 = e_G256_inv0_0 & dec_12;
  temp_var_0_G16_mul1_G256_inv0_1 = e_G256_inv0_1 & dec_12;
  a_G16_mul1_G256_inv0_0 = temp_var_0_G16_mul1_G256_inv0_0 >> dec_2;
  a_G16_mul1_G256_inv0_1 = temp_var_0_G16_mul1_G256_inv0_1 >> dec_2;
  b_G16_mul1_G256_inv0_0 = e_G256_inv0_0 & dec_3;
  b_G16_mul1_G256_inv0_1 = e_G256_inv0_1 & dec_3;
  temp_var_1_G16_mul1_G256_inv0_0 = b_G256_inv0_0 & dec_12;
  temp_var_1_G16_mul1_G256_inv0_1 = b_G256_inv0_1 & dec_12;
  c_G16_mul1_G256_inv0_0 = temp_var_1_G16_mul1_G256_inv0_0 >> dec_2;
  c_G16_mul1_G256_inv0_1 = temp_var_1_G16_mul1_G256_inv0_1 >> dec_2;
  d_G16_mul1_G256_inv0_0 = b_G256_inv0_0 & dec_3;
  d_G16_mul1_G256_inv0_1 = b_G256_inv0_1 & dec_3;
  temp_var_2_G16_mul1_G256_inv0_0 = a_G16_mul1_G256_inv0_0 ^ b_G16_mul1_G256_inv0_0;
  temp_var_2_G16_mul1_G256_inv0_1 = a_G16_mul1_G256_inv0_1 ^ b_G16_mul1_G256_inv0_1;
  temp_var_3_G16_mul1_G256_inv0_0 = c_G16_mul1_G256_inv0_0 ^ d_G16_mul1_G256_inv0_0;
  temp_var_3_G16_mul1_G256_inv0_1 = c_G16_mul1_G256_inv0_1 ^ d_G16_mul1_G256_inv0_1;
  temp_var_0_G4_mul0_G16_mul1_G256_inv0_0 = temp_var_2_G16_mul1_G256_inv0_0 & dec_2;
  temp_var_0_G4_mul0_G16_mul1_G256_inv0_1 = temp_var_2_G16_mul1_G256_inv0_1 & dec_2;
  a_G4_mul0_G16_mul1_G256_inv0_0 = temp_var_0_G4_mul0_G16_mul1_G256_inv0_0 >> dec_1;
  a_G4_mul0_G16_mul1_G256_inv0_1 = temp_var_0_G4_mul0_G16_mul1_G256_inv0_1 >> dec_1;
  b_G4_mul0_G16_mul1_G256_inv0_0 = temp_var_2_G16_mul1_G256_inv0_0 & dec_1;
  b_G4_mul0_G16_mul1_G256_inv0_1 = temp_var_2_G16_mul1_G256_inv0_1 & dec_1;
  temp_var_1_G4_mul0_G16_mul1_G256_inv0_0 = temp_var_3_G16_mul1_G256_inv0_0 & dec_2;
  temp_var_1_G4_mul0_G16_mul1_G256_inv0_1 = temp_var_3_G16_mul1_G256_inv0_1 & dec_2;
  c_G4_mul0_G16_mul1_G256_inv0_0 = temp_var_1_G4_mul0_G16_mul1_G256_inv0_0 >> dec_1;
  c_G4_mul0_G16_mul1_G256_inv0_1 = temp_var_1_G4_mul0_G16_mul1_G256_inv0_1 >> dec_1;
  d_G4_mul0_G16_mul1_G256_inv0_0 = temp_var_3_G16_mul1_G256_inv0_0 & dec_1;
  d_G4_mul0_G16_mul1_G256_inv0_1 = temp_var_3_G16_mul1_G256_inv0_1 & dec_1;
  temp_var_2_G4_mul0_G16_mul1_G256_inv0_0 = a_G4_mul0_G16_mul1_G256_inv0_0 ^ b_G4_mul0_G16_mul1_G256_inv0_0;
  temp_var_2_G4_mul0_G16_mul1_G256_inv0_1 = a_G4_mul0_G16_mul1_G256_inv0_1 ^ b_G4_mul0_G16_mul1_G256_inv0_1;
  temp_var_3_G4_mul0_G16_mul1_G256_inv0_0 = c_G4_mul0_G16_mul1_G256_inv0_0 ^ d_G4_mul0_G16_mul1_G256_inv0_0;
  temp_var_3_G4_mul0_G16_mul1_G256_inv0_1 = c_G4_mul0_G16_mul1_G256_inv0_1 ^ d_G4_mul0_G16_mul1_G256_inv0_1;
  HPC2(temp_var_2_G4_mul0_G16_mul1_G256_inv0_0, temp_var_2_G4_mul0_G16_mul1_G256_inv0_1, temp_var_3_G4_mul0_G16_mul1_G256_inv0_0, temp_var_3_G4_mul0_G16_mul1_G256_inv0_1, &e_G4_mul0_G16_mul1_G256_inv0_0, &e_G4_mul0_G16_mul1_G256_inv0_1, rand_31);
  HPC2(a_G4_mul0_G16_mul1_G256_inv0_0, a_G4_mul0_G16_mul1_G256_inv0_1, c_G4_mul0_G16_mul1_G256_inv0_0, c_G4_mul0_G16_mul1_G256_inv0_1, &temp_var_4_G4_mul0_G16_mul1_G256_inv0_0, &temp_var_4_G4_mul0_G16_mul1_G256_inv0_1, rand_32);
  p_G4_mul0_G16_mul1_G256_inv0_0 = temp_var_4_G4_mul0_G16_mul1_G256_inv0_0 ^ e_G4_mul0_G16_mul1_G256_inv0_0;
  p_G4_mul0_G16_mul1_G256_inv0_1 = temp_var_4_G4_mul0_G16_mul1_G256_inv0_1 ^ e_G4_mul0_G16_mul1_G256_inv0_1;
  HPC2(b_G4_mul0_G16_mul1_G256_inv0_0, b_G4_mul0_G16_mul1_G256_inv0_1, d_G4_mul0_G16_mul1_G256_inv0_0, d_G4_mul0_G16_mul1_G256_inv0_1, &temp_var_5_G4_mul0_G16_mul1_G256_inv0_0, &temp_var_5_G4_mul0_G16_mul1_G256_inv0_1, rand_33);
  q_G4_mul0_G16_mul1_G256_inv0_0 = temp_var_5_G4_mul0_G16_mul1_G256_inv0_0 ^ e_G4_mul0_G16_mul1_G256_inv0_0;
  q_G4_mul0_G16_mul1_G256_inv0_1 = temp_var_5_G4_mul0_G16_mul1_G256_inv0_1 ^ e_G4_mul0_G16_mul1_G256_inv0_1;
  temp_var_6_G4_mul0_G16_mul1_G256_inv0_0 = p_G4_mul0_G16_mul1_G256_inv0_0 << dec_1;
  temp_var_6_G4_mul0_G16_mul1_G256_inv0_1 = p_G4_mul0_G16_mul1_G256_inv0_1 << dec_1;
  e_G16_mul1_G256_inv0_0 = temp_var_6_G4_mul0_G16_mul1_G256_inv0_0 | q_G4_mul0_G16_mul1_G256_inv0_0;
  e_G16_mul1_G256_inv0_1 = temp_var_6_G4_mul0_G16_mul1_G256_inv0_1 | q_G4_mul0_G16_mul1_G256_inv0_1;
  temp_var_0_G4_scl_N0_G16_mul1_G256_inv0_0 = e_G16_mul1_G256_inv0_0 & dec_2;
  temp_var_0_G4_scl_N0_G16_mul1_G256_inv0_1 = e_G16_mul1_G256_inv0_1 & dec_2;
  a_G4_scl_N0_G16_mul1_G256_inv0_0 = temp_var_0_G4_scl_N0_G16_mul1_G256_inv0_0 >> dec_1;
  a_G4_scl_N0_G16_mul1_G256_inv0_1 = temp_var_0_G4_scl_N0_G16_mul1_G256_inv0_1 >> dec_1;
  b_G4_scl_N0_G16_mul1_G256_inv0_0 = e_G16_mul1_G256_inv0_0 & dec_1;
  b_G4_scl_N0_G16_mul1_G256_inv0_1 = e_G16_mul1_G256_inv0_1 & dec_1;
  p_G4_scl_N0_G16_mul1_G256_inv0_0 = b_G4_scl_N0_G16_mul1_G256_inv0_0;
  p_G4_scl_N0_G16_mul1_G256_inv0_1 = b_G4_scl_N0_G16_mul1_G256_inv0_1;
  q_G4_scl_N0_G16_mul1_G256_inv0_0 = a_G4_scl_N0_G16_mul1_G256_inv0_0 ^ b_G4_scl_N0_G16_mul1_G256_inv0_0;
  q_G4_scl_N0_G16_mul1_G256_inv0_1 = a_G4_scl_N0_G16_mul1_G256_inv0_1 ^ b_G4_scl_N0_G16_mul1_G256_inv0_1;
  temp_var_1_G4_scl_N0_G16_mul1_G256_inv0_0 = p_G4_scl_N0_G16_mul1_G256_inv0_0 << dec_1;
  temp_var_1_G4_scl_N0_G16_mul1_G256_inv0_1 = p_G4_scl_N0_G16_mul1_G256_inv0_1 << dec_1;
  _1_version_e_G16_mul1_G256_inv0_0 = temp_var_1_G4_scl_N0_G16_mul1_G256_inv0_0 | q_G4_scl_N0_G16_mul1_G256_inv0_0;
  _1_version_e_G16_mul1_G256_inv0_1 = temp_var_1_G4_scl_N0_G16_mul1_G256_inv0_1 | q_G4_scl_N0_G16_mul1_G256_inv0_1;
  temp_var_0_G4_mul1_G16_mul1_G256_inv0_0 = a_G16_mul1_G256_inv0_0 & dec_2;
  temp_var_0_G4_mul1_G16_mul1_G256_inv0_1 = a_G16_mul1_G256_inv0_1 & dec_2;
  a_G4_mul1_G16_mul1_G256_inv0_0 = temp_var_0_G4_mul1_G16_mul1_G256_inv0_0 >> dec_1;
  a_G4_mul1_G16_mul1_G256_inv0_1 = temp_var_0_G4_mul1_G16_mul1_G256_inv0_1 >> dec_1;
  b_G4_mul1_G16_mul1_G256_inv0_0 = a_G16_mul1_G256_inv0_0 & dec_1;
  b_G4_mul1_G16_mul1_G256_inv0_1 = a_G16_mul1_G256_inv0_1 & dec_1;
  temp_var_1_G4_mul1_G16_mul1_G256_inv0_0 = c_G16_mul1_G256_inv0_0 & dec_2;
  temp_var_1_G4_mul1_G16_mul1_G256_inv0_1 = c_G16_mul1_G256_inv0_1 & dec_2;
  c_G4_mul1_G16_mul1_G256_inv0_0 = temp_var_1_G4_mul1_G16_mul1_G256_inv0_0 >> dec_1;
  c_G4_mul1_G16_mul1_G256_inv0_1 = temp_var_1_G4_mul1_G16_mul1_G256_inv0_1 >> dec_1;
  d_G4_mul1_G16_mul1_G256_inv0_0 = c_G16_mul1_G256_inv0_0 & dec_1;
  d_G4_mul1_G16_mul1_G256_inv0_1 = c_G16_mul1_G256_inv0_1 & dec_1;
  temp_var_2_G4_mul1_G16_mul1_G256_inv0_0 = a_G4_mul1_G16_mul1_G256_inv0_0 ^ b_G4_mul1_G16_mul1_G256_inv0_0;
  temp_var_2_G4_mul1_G16_mul1_G256_inv0_1 = a_G4_mul1_G16_mul1_G256_inv0_1 ^ b_G4_mul1_G16_mul1_G256_inv0_1;
  temp_var_3_G4_mul1_G16_mul1_G256_inv0_0 = c_G4_mul1_G16_mul1_G256_inv0_0 ^ d_G4_mul1_G16_mul1_G256_inv0_0;
  temp_var_3_G4_mul1_G16_mul1_G256_inv0_1 = c_G4_mul1_G16_mul1_G256_inv0_1 ^ d_G4_mul1_G16_mul1_G256_inv0_1;
  HPC2(temp_var_2_G4_mul1_G16_mul1_G256_inv0_0, temp_var_2_G4_mul1_G16_mul1_G256_inv0_1, temp_var_3_G4_mul1_G16_mul1_G256_inv0_0, temp_var_3_G4_mul1_G16_mul1_G256_inv0_1, &e_G4_mul1_G16_mul1_G256_inv0_0, &e_G4_mul1_G16_mul1_G256_inv0_1, rand_34);
  HPC2(a_G4_mul1_G16_mul1_G256_inv0_0, a_G4_mul1_G16_mul1_G256_inv0_1, c_G4_mul1_G16_mul1_G256_inv0_0, c_G4_mul1_G16_mul1_G256_inv0_1, &temp_var_4_G4_mul1_G16_mul1_G256_inv0_0, &temp_var_4_G4_mul1_G16_mul1_G256_inv0_1, rand_35);
  p_G4_mul1_G16_mul1_G256_inv0_0 = temp_var_4_G4_mul1_G16_mul1_G256_inv0_0 ^ e_G4_mul1_G16_mul1_G256_inv0_0;
  p_G4_mul1_G16_mul1_G256_inv0_1 = temp_var_4_G4_mul1_G16_mul1_G256_inv0_1 ^ e_G4_mul1_G16_mul1_G256_inv0_1;
  HPC2(b_G4_mul1_G16_mul1_G256_inv0_0, b_G4_mul1_G16_mul1_G256_inv0_1, d_G4_mul1_G16_mul1_G256_inv0_0, d_G4_mul1_G16_mul1_G256_inv0_1, &temp_var_5_G4_mul1_G16_mul1_G256_inv0_0, &temp_var_5_G4_mul1_G16_mul1_G256_inv0_1, rand_36);
  q_G4_mul1_G16_mul1_G256_inv0_0 = temp_var_5_G4_mul1_G16_mul1_G256_inv0_0 ^ e_G4_mul1_G16_mul1_G256_inv0_0;
  q_G4_mul1_G16_mul1_G256_inv0_1 = temp_var_5_G4_mul1_G16_mul1_G256_inv0_1 ^ e_G4_mul1_G16_mul1_G256_inv0_1;
  temp_var_6_G4_mul1_G16_mul1_G256_inv0_0 = p_G4_mul1_G16_mul1_G256_inv0_0 << dec_1;
  temp_var_6_G4_mul1_G16_mul1_G256_inv0_1 = p_G4_mul1_G16_mul1_G256_inv0_1 << dec_1;
  temp_var_4_G16_mul1_G256_inv0_0 = temp_var_6_G4_mul1_G16_mul1_G256_inv0_0 | q_G4_mul1_G16_mul1_G256_inv0_0;
  temp_var_4_G16_mul1_G256_inv0_1 = temp_var_6_G4_mul1_G16_mul1_G256_inv0_1 | q_G4_mul1_G16_mul1_G256_inv0_1;
  p_G16_mul1_G256_inv0_0 = temp_var_4_G16_mul1_G256_inv0_0 ^ _1_version_e_G16_mul1_G256_inv0_0;
  p_G16_mul1_G256_inv0_1 = temp_var_4_G16_mul1_G256_inv0_1 ^ _1_version_e_G16_mul1_G256_inv0_1;
  temp_var_0_G4_mul2_G16_mul1_G256_inv0_0 = b_G16_mul1_G256_inv0_0 & dec_2;
  temp_var_0_G4_mul2_G16_mul1_G256_inv0_1 = b_G16_mul1_G256_inv0_1 & dec_2;
  a_G4_mul2_G16_mul1_G256_inv0_0 = temp_var_0_G4_mul2_G16_mul1_G256_inv0_0 >> dec_1;
  a_G4_mul2_G16_mul1_G256_inv0_1 = temp_var_0_G4_mul2_G16_mul1_G256_inv0_1 >> dec_1;
  b_G4_mul2_G16_mul1_G256_inv0_0 = b_G16_mul1_G256_inv0_0 & dec_1;
  b_G4_mul2_G16_mul1_G256_inv0_1 = b_G16_mul1_G256_inv0_1 & dec_1;
  temp_var_1_G4_mul2_G16_mul1_G256_inv0_0 = d_G16_mul1_G256_inv0_0 & dec_2;
  temp_var_1_G4_mul2_G16_mul1_G256_inv0_1 = d_G16_mul1_G256_inv0_1 & dec_2;
  c_G4_mul2_G16_mul1_G256_inv0_0 = temp_var_1_G4_mul2_G16_mul1_G256_inv0_0 >> dec_1;
  c_G4_mul2_G16_mul1_G256_inv0_1 = temp_var_1_G4_mul2_G16_mul1_G256_inv0_1 >> dec_1;
  d_G4_mul2_G16_mul1_G256_inv0_0 = d_G16_mul1_G256_inv0_0 & dec_1;
  d_G4_mul2_G16_mul1_G256_inv0_1 = d_G16_mul1_G256_inv0_1 & dec_1;
  temp_var_2_G4_mul2_G16_mul1_G256_inv0_0 = a_G4_mul2_G16_mul1_G256_inv0_0 ^ b_G4_mul2_G16_mul1_G256_inv0_0;
  temp_var_2_G4_mul2_G16_mul1_G256_inv0_1 = a_G4_mul2_G16_mul1_G256_inv0_1 ^ b_G4_mul2_G16_mul1_G256_inv0_1;
  temp_var_3_G4_mul2_G16_mul1_G256_inv0_0 = c_G4_mul2_G16_mul1_G256_inv0_0 ^ d_G4_mul2_G16_mul1_G256_inv0_0;
  temp_var_3_G4_mul2_G16_mul1_G256_inv0_1 = c_G4_mul2_G16_mul1_G256_inv0_1 ^ d_G4_mul2_G16_mul1_G256_inv0_1;
  HPC2(temp_var_2_G4_mul2_G16_mul1_G256_inv0_0, temp_var_2_G4_mul2_G16_mul1_G256_inv0_1, temp_var_3_G4_mul2_G16_mul1_G256_inv0_0, temp_var_3_G4_mul2_G16_mul1_G256_inv0_1, &e_G4_mul2_G16_mul1_G256_inv0_0, &e_G4_mul2_G16_mul1_G256_inv0_1, rand_37);
  HPC2(a_G4_mul2_G16_mul1_G256_inv0_0, a_G4_mul2_G16_mul1_G256_inv0_1, c_G4_mul2_G16_mul1_G256_inv0_0, c_G4_mul2_G16_mul1_G256_inv0_1, &temp_var_4_G4_mul2_G16_mul1_G256_inv0_0, &temp_var_4_G4_mul2_G16_mul1_G256_inv0_1, rand_38);
  p_G4_mul2_G16_mul1_G256_inv0_0 = temp_var_4_G4_mul2_G16_mul1_G256_inv0_0 ^ e_G4_mul2_G16_mul1_G256_inv0_0;
  p_G4_mul2_G16_mul1_G256_inv0_1 = temp_var_4_G4_mul2_G16_mul1_G256_inv0_1 ^ e_G4_mul2_G16_mul1_G256_inv0_1;
  HPC2(b_G4_mul2_G16_mul1_G256_inv0_0, b_G4_mul2_G16_mul1_G256_inv0_1, d_G4_mul2_G16_mul1_G256_inv0_0, d_G4_mul2_G16_mul1_G256_inv0_1, &temp_var_5_G4_mul2_G16_mul1_G256_inv0_0, &temp_var_5_G4_mul2_G16_mul1_G256_inv0_1, rand_39);
  q_G4_mul2_G16_mul1_G256_inv0_0 = temp_var_5_G4_mul2_G16_mul1_G256_inv0_0 ^ e_G4_mul2_G16_mul1_G256_inv0_0;
  q_G4_mul2_G16_mul1_G256_inv0_1 = temp_var_5_G4_mul2_G16_mul1_G256_inv0_1 ^ e_G4_mul2_G16_mul1_G256_inv0_1;
  temp_var_6_G4_mul2_G16_mul1_G256_inv0_0 = p_G4_mul2_G16_mul1_G256_inv0_0 << dec_1;
  temp_var_6_G4_mul2_G16_mul1_G256_inv0_1 = p_G4_mul2_G16_mul1_G256_inv0_1 << dec_1;
  temp_var_5_G16_mul1_G256_inv0_0 = temp_var_6_G4_mul2_G16_mul1_G256_inv0_0 | q_G4_mul2_G16_mul1_G256_inv0_0;
  temp_var_5_G16_mul1_G256_inv0_1 = temp_var_6_G4_mul2_G16_mul1_G256_inv0_1 | q_G4_mul2_G16_mul1_G256_inv0_1;
  q_G16_mul1_G256_inv0_0 = temp_var_5_G16_mul1_G256_inv0_0 ^ _1_version_e_G16_mul1_G256_inv0_0;
  q_G16_mul1_G256_inv0_1 = temp_var_5_G16_mul1_G256_inv0_1 ^ _1_version_e_G16_mul1_G256_inv0_1;
  temp_var_6_G16_mul1_G256_inv0_0 = p_G16_mul1_G256_inv0_0 << dec_2;
  temp_var_6_G16_mul1_G256_inv0_1 = p_G16_mul1_G256_inv0_1 << dec_2;
  p_G256_inv0_0 = temp_var_6_G16_mul1_G256_inv0_0 | q_G16_mul1_G256_inv0_0;
  p_G256_inv0_1 = temp_var_6_G16_mul1_G256_inv0_1 | q_G16_mul1_G256_inv0_1;
  temp_var_0_G16_mul2_G256_inv0_0 = e_G256_inv0_0 & dec_12;
  temp_var_0_G16_mul2_G256_inv0_1 = e_G256_inv0_1 & dec_12;
  a_G16_mul2_G256_inv0_0 = temp_var_0_G16_mul2_G256_inv0_0 >> dec_2;
  a_G16_mul2_G256_inv0_1 = temp_var_0_G16_mul2_G256_inv0_1 >> dec_2;
  b_G16_mul2_G256_inv0_0 = e_G256_inv0_0 & dec_3;
  b_G16_mul2_G256_inv0_1 = e_G256_inv0_1 & dec_3;
  temp_var_1_G16_mul2_G256_inv0_0 = a_G256_inv0_0 & dec_12;
  temp_var_1_G16_mul2_G256_inv0_1 = a_G256_inv0_1 & dec_12;
  c_G16_mul2_G256_inv0_0 = temp_var_1_G16_mul2_G256_inv0_0 >> dec_2;
  c_G16_mul2_G256_inv0_1 = temp_var_1_G16_mul2_G256_inv0_1 >> dec_2;
  d_G16_mul2_G256_inv0_0 = a_G256_inv0_0 & dec_3;
  d_G16_mul2_G256_inv0_1 = a_G256_inv0_1 & dec_3;
  temp_var_2_G16_mul2_G256_inv0_0 = a_G16_mul2_G256_inv0_0 ^ b_G16_mul2_G256_inv0_0;
  temp_var_2_G16_mul2_G256_inv0_1 = a_G16_mul2_G256_inv0_1 ^ b_G16_mul2_G256_inv0_1;
  temp_var_3_G16_mul2_G256_inv0_0 = c_G16_mul2_G256_inv0_0 ^ d_G16_mul2_G256_inv0_0;
  temp_var_3_G16_mul2_G256_inv0_1 = c_G16_mul2_G256_inv0_1 ^ d_G16_mul2_G256_inv0_1;
  temp_var_0_G4_mul0_G16_mul2_G256_inv0_0 = temp_var_2_G16_mul2_G256_inv0_0 & dec_2;
  temp_var_0_G4_mul0_G16_mul2_G256_inv0_1 = temp_var_2_G16_mul2_G256_inv0_1 & dec_2;
  a_G4_mul0_G16_mul2_G256_inv0_0 = temp_var_0_G4_mul0_G16_mul2_G256_inv0_0 >> dec_1;
  a_G4_mul0_G16_mul2_G256_inv0_1 = temp_var_0_G4_mul0_G16_mul2_G256_inv0_1 >> dec_1;
  b_G4_mul0_G16_mul2_G256_inv0_0 = temp_var_2_G16_mul2_G256_inv0_0 & dec_1;
  b_G4_mul0_G16_mul2_G256_inv0_1 = temp_var_2_G16_mul2_G256_inv0_1 & dec_1;
  temp_var_1_G4_mul0_G16_mul2_G256_inv0_0 = temp_var_3_G16_mul2_G256_inv0_0 & dec_2;
  temp_var_1_G4_mul0_G16_mul2_G256_inv0_1 = temp_var_3_G16_mul2_G256_inv0_1 & dec_2;
  c_G4_mul0_G16_mul2_G256_inv0_0 = temp_var_1_G4_mul0_G16_mul2_G256_inv0_0 >> dec_1;
  c_G4_mul0_G16_mul2_G256_inv0_1 = temp_var_1_G4_mul0_G16_mul2_G256_inv0_1 >> dec_1;
  d_G4_mul0_G16_mul2_G256_inv0_0 = temp_var_3_G16_mul2_G256_inv0_0 & dec_1;
  d_G4_mul0_G16_mul2_G256_inv0_1 = temp_var_3_G16_mul2_G256_inv0_1 & dec_1;
  temp_var_2_G4_mul0_G16_mul2_G256_inv0_0 = a_G4_mul0_G16_mul2_G256_inv0_0 ^ b_G4_mul0_G16_mul2_G256_inv0_0;
  temp_var_2_G4_mul0_G16_mul2_G256_inv0_1 = a_G4_mul0_G16_mul2_G256_inv0_1 ^ b_G4_mul0_G16_mul2_G256_inv0_1;
  temp_var_3_G4_mul0_G16_mul2_G256_inv0_0 = c_G4_mul0_G16_mul2_G256_inv0_0 ^ d_G4_mul0_G16_mul2_G256_inv0_0;
  temp_var_3_G4_mul0_G16_mul2_G256_inv0_1 = c_G4_mul0_G16_mul2_G256_inv0_1 ^ d_G4_mul0_G16_mul2_G256_inv0_1;
  HPC2(temp_var_2_G4_mul0_G16_mul2_G256_inv0_0, temp_var_2_G4_mul0_G16_mul2_G256_inv0_1, temp_var_3_G4_mul0_G16_mul2_G256_inv0_0, temp_var_3_G4_mul0_G16_mul2_G256_inv0_1, &e_G4_mul0_G16_mul2_G256_inv0_0, &e_G4_mul0_G16_mul2_G256_inv0_1, rand_40);
  HPC2(a_G4_mul0_G16_mul2_G256_inv0_0, a_G4_mul0_G16_mul2_G256_inv0_1, c_G4_mul0_G16_mul2_G256_inv0_0, c_G4_mul0_G16_mul2_G256_inv0_1, &temp_var_4_G4_mul0_G16_mul2_G256_inv0_0, &temp_var_4_G4_mul0_G16_mul2_G256_inv0_1, rand_41);
  p_G4_mul0_G16_mul2_G256_inv0_0 = temp_var_4_G4_mul0_G16_mul2_G256_inv0_0 ^ e_G4_mul0_G16_mul2_G256_inv0_0;
  p_G4_mul0_G16_mul2_G256_inv0_1 = temp_var_4_G4_mul0_G16_mul2_G256_inv0_1 ^ e_G4_mul0_G16_mul2_G256_inv0_1;
  HPC2(b_G4_mul0_G16_mul2_G256_inv0_0, b_G4_mul0_G16_mul2_G256_inv0_1, d_G4_mul0_G16_mul2_G256_inv0_0, d_G4_mul0_G16_mul2_G256_inv0_1, &temp_var_5_G4_mul0_G16_mul2_G256_inv0_0, &temp_var_5_G4_mul0_G16_mul2_G256_inv0_1, rand_42);
  q_G4_mul0_G16_mul2_G256_inv0_0 = temp_var_5_G4_mul0_G16_mul2_G256_inv0_0 ^ e_G4_mul0_G16_mul2_G256_inv0_0;
  q_G4_mul0_G16_mul2_G256_inv0_1 = temp_var_5_G4_mul0_G16_mul2_G256_inv0_1 ^ e_G4_mul0_G16_mul2_G256_inv0_1;
  temp_var_6_G4_mul0_G16_mul2_G256_inv0_0 = p_G4_mul0_G16_mul2_G256_inv0_0 << dec_1;
  temp_var_6_G4_mul0_G16_mul2_G256_inv0_1 = p_G4_mul0_G16_mul2_G256_inv0_1 << dec_1;
  e_G16_mul2_G256_inv0_0 = temp_var_6_G4_mul0_G16_mul2_G256_inv0_0 | q_G4_mul0_G16_mul2_G256_inv0_0;
  e_G16_mul2_G256_inv0_1 = temp_var_6_G4_mul0_G16_mul2_G256_inv0_1 | q_G4_mul0_G16_mul2_G256_inv0_1;
  temp_var_0_G4_scl_N0_G16_mul2_G256_inv0_0 = e_G16_mul2_G256_inv0_0 & dec_2;
  temp_var_0_G4_scl_N0_G16_mul2_G256_inv0_1 = e_G16_mul2_G256_inv0_1 & dec_2;
  a_G4_scl_N0_G16_mul2_G256_inv0_0 = temp_var_0_G4_scl_N0_G16_mul2_G256_inv0_0 >> dec_1;
  a_G4_scl_N0_G16_mul2_G256_inv0_1 = temp_var_0_G4_scl_N0_G16_mul2_G256_inv0_1 >> dec_1;
  b_G4_scl_N0_G16_mul2_G256_inv0_0 = e_G16_mul2_G256_inv0_0 & dec_1;
  b_G4_scl_N0_G16_mul2_G256_inv0_1 = e_G16_mul2_G256_inv0_1 & dec_1;
  p_G4_scl_N0_G16_mul2_G256_inv0_0 = b_G4_scl_N0_G16_mul2_G256_inv0_0;
  p_G4_scl_N0_G16_mul2_G256_inv0_1 = b_G4_scl_N0_G16_mul2_G256_inv0_1;
  q_G4_scl_N0_G16_mul2_G256_inv0_0 = a_G4_scl_N0_G16_mul2_G256_inv0_0 ^ b_G4_scl_N0_G16_mul2_G256_inv0_0;
  q_G4_scl_N0_G16_mul2_G256_inv0_1 = a_G4_scl_N0_G16_mul2_G256_inv0_1 ^ b_G4_scl_N0_G16_mul2_G256_inv0_1;
  temp_var_1_G4_scl_N0_G16_mul2_G256_inv0_0 = p_G4_scl_N0_G16_mul2_G256_inv0_0 << dec_1;
  temp_var_1_G4_scl_N0_G16_mul2_G256_inv0_1 = p_G4_scl_N0_G16_mul2_G256_inv0_1 << dec_1;
  _1_version_e_G16_mul2_G256_inv0_0 = temp_var_1_G4_scl_N0_G16_mul2_G256_inv0_0 | q_G4_scl_N0_G16_mul2_G256_inv0_0;
  _1_version_e_G16_mul2_G256_inv0_1 = temp_var_1_G4_scl_N0_G16_mul2_G256_inv0_1 | q_G4_scl_N0_G16_mul2_G256_inv0_1;
  temp_var_0_G4_mul1_G16_mul2_G256_inv0_0 = a_G16_mul2_G256_inv0_0 & dec_2;
  temp_var_0_G4_mul1_G16_mul2_G256_inv0_1 = a_G16_mul2_G256_inv0_1 & dec_2;
  a_G4_mul1_G16_mul2_G256_inv0_0 = temp_var_0_G4_mul1_G16_mul2_G256_inv0_0 >> dec_1;
  a_G4_mul1_G16_mul2_G256_inv0_1 = temp_var_0_G4_mul1_G16_mul2_G256_inv0_1 >> dec_1;
  b_G4_mul1_G16_mul2_G256_inv0_0 = a_G16_mul2_G256_inv0_0 & dec_1;
  b_G4_mul1_G16_mul2_G256_inv0_1 = a_G16_mul2_G256_inv0_1 & dec_1;
  temp_var_1_G4_mul1_G16_mul2_G256_inv0_0 = c_G16_mul2_G256_inv0_0 & dec_2;
  temp_var_1_G4_mul1_G16_mul2_G256_inv0_1 = c_G16_mul2_G256_inv0_1 & dec_2;
  c_G4_mul1_G16_mul2_G256_inv0_0 = temp_var_1_G4_mul1_G16_mul2_G256_inv0_0 >> dec_1;
  c_G4_mul1_G16_mul2_G256_inv0_1 = temp_var_1_G4_mul1_G16_mul2_G256_inv0_1 >> dec_1;
  d_G4_mul1_G16_mul2_G256_inv0_0 = c_G16_mul2_G256_inv0_0 & dec_1;
  d_G4_mul1_G16_mul2_G256_inv0_1 = c_G16_mul2_G256_inv0_1 & dec_1;
  temp_var_2_G4_mul1_G16_mul2_G256_inv0_0 = a_G4_mul1_G16_mul2_G256_inv0_0 ^ b_G4_mul1_G16_mul2_G256_inv0_0;
  temp_var_2_G4_mul1_G16_mul2_G256_inv0_1 = a_G4_mul1_G16_mul2_G256_inv0_1 ^ b_G4_mul1_G16_mul2_G256_inv0_1;
  temp_var_3_G4_mul1_G16_mul2_G256_inv0_0 = c_G4_mul1_G16_mul2_G256_inv0_0 ^ d_G4_mul1_G16_mul2_G256_inv0_0;
  temp_var_3_G4_mul1_G16_mul2_G256_inv0_1 = c_G4_mul1_G16_mul2_G256_inv0_1 ^ d_G4_mul1_G16_mul2_G256_inv0_1;
  HPC2(temp_var_2_G4_mul1_G16_mul2_G256_inv0_0, temp_var_2_G4_mul1_G16_mul2_G256_inv0_1, temp_var_3_G4_mul1_G16_mul2_G256_inv0_0, temp_var_3_G4_mul1_G16_mul2_G256_inv0_1, &e_G4_mul1_G16_mul2_G256_inv0_0, &e_G4_mul1_G16_mul2_G256_inv0_1, rand_43);
  HPC2(a_G4_mul1_G16_mul2_G256_inv0_0, a_G4_mul1_G16_mul2_G256_inv0_1, c_G4_mul1_G16_mul2_G256_inv0_0, c_G4_mul1_G16_mul2_G256_inv0_1, &temp_var_4_G4_mul1_G16_mul2_G256_inv0_0, &temp_var_4_G4_mul1_G16_mul2_G256_inv0_1, rand_44);
  p_G4_mul1_G16_mul2_G256_inv0_0 = temp_var_4_G4_mul1_G16_mul2_G256_inv0_0 ^ e_G4_mul1_G16_mul2_G256_inv0_0;
  p_G4_mul1_G16_mul2_G256_inv0_1 = temp_var_4_G4_mul1_G16_mul2_G256_inv0_1 ^ e_G4_mul1_G16_mul2_G256_inv0_1;
  HPC2(b_G4_mul1_G16_mul2_G256_inv0_0, b_G4_mul1_G16_mul2_G256_inv0_1, d_G4_mul1_G16_mul2_G256_inv0_0, d_G4_mul1_G16_mul2_G256_inv0_1, &temp_var_5_G4_mul1_G16_mul2_G256_inv0_0, &temp_var_5_G4_mul1_G16_mul2_G256_inv0_1, rand_45);
  q_G4_mul1_G16_mul2_G256_inv0_0 = temp_var_5_G4_mul1_G16_mul2_G256_inv0_0 ^ e_G4_mul1_G16_mul2_G256_inv0_0;
  q_G4_mul1_G16_mul2_G256_inv0_1 = temp_var_5_G4_mul1_G16_mul2_G256_inv0_1 ^ e_G4_mul1_G16_mul2_G256_inv0_1;
  temp_var_6_G4_mul1_G16_mul2_G256_inv0_0 = p_G4_mul1_G16_mul2_G256_inv0_0 << dec_1;
  temp_var_6_G4_mul1_G16_mul2_G256_inv0_1 = p_G4_mul1_G16_mul2_G256_inv0_1 << dec_1;
  temp_var_4_G16_mul2_G256_inv0_0 = temp_var_6_G4_mul1_G16_mul2_G256_inv0_0 | q_G4_mul1_G16_mul2_G256_inv0_0;
  temp_var_4_G16_mul2_G256_inv0_1 = temp_var_6_G4_mul1_G16_mul2_G256_inv0_1 | q_G4_mul1_G16_mul2_G256_inv0_1;
  p_G16_mul2_G256_inv0_0 = temp_var_4_G16_mul2_G256_inv0_0 ^ _1_version_e_G16_mul2_G256_inv0_0;
  p_G16_mul2_G256_inv0_1 = temp_var_4_G16_mul2_G256_inv0_1 ^ _1_version_e_G16_mul2_G256_inv0_1;
  temp_var_0_G4_mul2_G16_mul2_G256_inv0_0 = b_G16_mul2_G256_inv0_0 & dec_2;
  temp_var_0_G4_mul2_G16_mul2_G256_inv0_1 = b_G16_mul2_G256_inv0_1 & dec_2;
  a_G4_mul2_G16_mul2_G256_inv0_0 = temp_var_0_G4_mul2_G16_mul2_G256_inv0_0 >> dec_1;
  a_G4_mul2_G16_mul2_G256_inv0_1 = temp_var_0_G4_mul2_G16_mul2_G256_inv0_1 >> dec_1;
  b_G4_mul2_G16_mul2_G256_inv0_0 = b_G16_mul2_G256_inv0_0 & dec_1;
  b_G4_mul2_G16_mul2_G256_inv0_1 = b_G16_mul2_G256_inv0_1 & dec_1;
  temp_var_1_G4_mul2_G16_mul2_G256_inv0_0 = d_G16_mul2_G256_inv0_0 & dec_2;
  temp_var_1_G4_mul2_G16_mul2_G256_inv0_1 = d_G16_mul2_G256_inv0_1 & dec_2;
  c_G4_mul2_G16_mul2_G256_inv0_0 = temp_var_1_G4_mul2_G16_mul2_G256_inv0_0 >> dec_1;
  c_G4_mul2_G16_mul2_G256_inv0_1 = temp_var_1_G4_mul2_G16_mul2_G256_inv0_1 >> dec_1;
  d_G4_mul2_G16_mul2_G256_inv0_0 = d_G16_mul2_G256_inv0_0 & dec_1;
  d_G4_mul2_G16_mul2_G256_inv0_1 = d_G16_mul2_G256_inv0_1 & dec_1;
  temp_var_2_G4_mul2_G16_mul2_G256_inv0_0 = a_G4_mul2_G16_mul2_G256_inv0_0 ^ b_G4_mul2_G16_mul2_G256_inv0_0;
  temp_var_2_G4_mul2_G16_mul2_G256_inv0_1 = a_G4_mul2_G16_mul2_G256_inv0_1 ^ b_G4_mul2_G16_mul2_G256_inv0_1;
  temp_var_3_G4_mul2_G16_mul2_G256_inv0_0 = c_G4_mul2_G16_mul2_G256_inv0_0 ^ d_G4_mul2_G16_mul2_G256_inv0_0;
  temp_var_3_G4_mul2_G16_mul2_G256_inv0_1 = c_G4_mul2_G16_mul2_G256_inv0_1 ^ d_G4_mul2_G16_mul2_G256_inv0_1;
  HPC2(temp_var_2_G4_mul2_G16_mul2_G256_inv0_0, temp_var_2_G4_mul2_G16_mul2_G256_inv0_1, temp_var_3_G4_mul2_G16_mul2_G256_inv0_0, temp_var_3_G4_mul2_G16_mul2_G256_inv0_1, &e_G4_mul2_G16_mul2_G256_inv0_0, &e_G4_mul2_G16_mul2_G256_inv0_1, rand_46);
  HPC2(a_G4_mul2_G16_mul2_G256_inv0_0, a_G4_mul2_G16_mul2_G256_inv0_1, c_G4_mul2_G16_mul2_G256_inv0_0, c_G4_mul2_G16_mul2_G256_inv0_1, &temp_var_4_G4_mul2_G16_mul2_G256_inv0_0, &temp_var_4_G4_mul2_G16_mul2_G256_inv0_1, rand_47);
  p_G4_mul2_G16_mul2_G256_inv0_0 = temp_var_4_G4_mul2_G16_mul2_G256_inv0_0 ^ e_G4_mul2_G16_mul2_G256_inv0_0;
  p_G4_mul2_G16_mul2_G256_inv0_1 = temp_var_4_G4_mul2_G16_mul2_G256_inv0_1 ^ e_G4_mul2_G16_mul2_G256_inv0_1;
  HPC2(b_G4_mul2_G16_mul2_G256_inv0_0, b_G4_mul2_G16_mul2_G256_inv0_1, d_G4_mul2_G16_mul2_G256_inv0_0, d_G4_mul2_G16_mul2_G256_inv0_1, &temp_var_5_G4_mul2_G16_mul2_G256_inv0_0, &temp_var_5_G4_mul2_G16_mul2_G256_inv0_1, rand_48);
  q_G4_mul2_G16_mul2_G256_inv0_0 = temp_var_5_G4_mul2_G16_mul2_G256_inv0_0 ^ e_G4_mul2_G16_mul2_G256_inv0_0;
  q_G4_mul2_G16_mul2_G256_inv0_1 = temp_var_5_G4_mul2_G16_mul2_G256_inv0_1 ^ e_G4_mul2_G16_mul2_G256_inv0_1;
  temp_var_6_G4_mul2_G16_mul2_G256_inv0_0 = p_G4_mul2_G16_mul2_G256_inv0_0 << dec_1;
  temp_var_6_G4_mul2_G16_mul2_G256_inv0_1 = p_G4_mul2_G16_mul2_G256_inv0_1 << dec_1;
  temp_var_5_G16_mul2_G256_inv0_0 = temp_var_6_G4_mul2_G16_mul2_G256_inv0_0 | q_G4_mul2_G16_mul2_G256_inv0_0;
  temp_var_5_G16_mul2_G256_inv0_1 = temp_var_6_G4_mul2_G16_mul2_G256_inv0_1 | q_G4_mul2_G16_mul2_G256_inv0_1;
  q_G16_mul2_G256_inv0_0 = temp_var_5_G16_mul2_G256_inv0_0 ^ _1_version_e_G16_mul2_G256_inv0_0;
  q_G16_mul2_G256_inv0_1 = temp_var_5_G16_mul2_G256_inv0_1 ^ _1_version_e_G16_mul2_G256_inv0_1;
  temp_var_6_G16_mul2_G256_inv0_0 = p_G16_mul2_G256_inv0_0 << dec_2;
  temp_var_6_G16_mul2_G256_inv0_1 = p_G16_mul2_G256_inv0_1 << dec_2;
  q_G256_inv0_0 = temp_var_6_G16_mul2_G256_inv0_0 | q_G16_mul2_G256_inv0_0;
  q_G256_inv0_1 = temp_var_6_G16_mul2_G256_inv0_1 | q_G16_mul2_G256_inv0_1;
  temp_var_3_G256_inv0_0 = p_G256_inv0_0 << dec_4;
  temp_var_3_G256_inv0_1 = p_G256_inv0_1 << dec_4;
  _1_version_t_0 = temp_var_3_G256_inv0_0 | q_G256_inv0_0;
  _1_version_t_1 = temp_var_3_G256_inv0_1 | q_G256_inv0_1;
  int _2_version_t_0;
  int _2_version_t_1;
  int i_G256_newbasis1_0;
  int i_G256_newbasis1_1;
  int y_G256_newbasis1_0;
  int y_G256_newbasis1_1;
  int _7_y_G256_newbasis1_0;
  int _7_y_G256_newbasis1_1;
  int _7_x_G256_newbasis1_0;
  int _7_x_G256_newbasis1_1;
  int _if_cond_0_G256_newbasis1_0;
  int _if_cond_0_G256_newbasis1_1;
  int _if_neg_cond_0_G256_newbasis1_0;
  int _if_neg_cond_0_G256_newbasis1_1;
  int temp_var_1_G256_newbasis1_0;
  int temp_var_1_G256_newbasis1_1;
  int temp_var_2_G256_newbasis1_0;
  int temp_var_2_G256_newbasis1_1;
  int temp_var_3_G256_newbasis1_0;
  int temp_var_3_G256_newbasis1_1;
  int _1_version__7_y_G256_newbasis1_0;
  int _1_version__7_y_G256_newbasis1_1;
  int _1_version__7_x_G256_newbasis1_0;
  int _1_version__7_x_G256_newbasis1_1;
  int _6_x_G256_newbasis1_0;
  int _6_x_G256_newbasis1_1;
  int _6_y_G256_newbasis1_0;
  int _6_y_G256_newbasis1_1;
  int _if_cond_4_G256_newbasis1_0;
  int _if_cond_4_G256_newbasis1_1;
  int _if_neg_cond_4_G256_newbasis1_0;
  int _if_neg_cond_4_G256_newbasis1_1;
  int temp_var_5_G256_newbasis1_0;
  int temp_var_5_G256_newbasis1_1;
  int temp_var_6_G256_newbasis1_0;
  int temp_var_6_G256_newbasis1_1;
  int temp_var_7_G256_newbasis1_0;
  int temp_var_7_G256_newbasis1_1;
  int _1_version__6_y_G256_newbasis1_0;
  int _1_version__6_y_G256_newbasis1_1;
  int _1_version__6_x_G256_newbasis1_0;
  int _1_version__6_x_G256_newbasis1_1;
  int _5_x_G256_newbasis1_0;
  int _5_x_G256_newbasis1_1;
  int _5_y_G256_newbasis1_0;
  int _5_y_G256_newbasis1_1;
  int _if_cond_8_G256_newbasis1_0;
  int _if_cond_8_G256_newbasis1_1;
  int _if_neg_cond_8_G256_newbasis1_0;
  int _if_neg_cond_8_G256_newbasis1_1;
  int temp_var_9_G256_newbasis1_0;
  int temp_var_9_G256_newbasis1_1;
  int temp_var_10_G256_newbasis1_0;
  int temp_var_10_G256_newbasis1_1;
  int temp_var_11_G256_newbasis1_0;
  int temp_var_11_G256_newbasis1_1;
  int _1_version__5_y_G256_newbasis1_0;
  int _1_version__5_y_G256_newbasis1_1;
  int _1_version__5_x_G256_newbasis1_0;
  int _1_version__5_x_G256_newbasis1_1;
  int _4_y_G256_newbasis1_0;
  int _4_y_G256_newbasis1_1;
  int _4_x_G256_newbasis1_0;
  int _4_x_G256_newbasis1_1;
  int _if_cond_12_G256_newbasis1_0;
  int _if_cond_12_G256_newbasis1_1;
  int _if_neg_cond_12_G256_newbasis1_0;
  int _if_neg_cond_12_G256_newbasis1_1;
  int temp_var_13_G256_newbasis1_0;
  int temp_var_13_G256_newbasis1_1;
  int temp_var_14_G256_newbasis1_0;
  int temp_var_14_G256_newbasis1_1;
  int temp_var_15_G256_newbasis1_0;
  int temp_var_15_G256_newbasis1_1;
  int _1_version__4_y_G256_newbasis1_0;
  int _1_version__4_y_G256_newbasis1_1;
  int _1_version__4_x_G256_newbasis1_0;
  int _1_version__4_x_G256_newbasis1_1;
  int _3_x_G256_newbasis1_0;
  int _3_x_G256_newbasis1_1;
  int _3_y_G256_newbasis1_0;
  int _3_y_G256_newbasis1_1;
  int _if_cond_16_G256_newbasis1_0;
  int _if_cond_16_G256_newbasis1_1;
  int _if_neg_cond_16_G256_newbasis1_0;
  int _if_neg_cond_16_G256_newbasis1_1;
  int temp_var_17_G256_newbasis1_0;
  int temp_var_17_G256_newbasis1_1;
  int temp_var_18_G256_newbasis1_0;
  int temp_var_18_G256_newbasis1_1;
  int temp_var_19_G256_newbasis1_0;
  int temp_var_19_G256_newbasis1_1;
  int _1_version__3_y_G256_newbasis1_0;
  int _1_version__3_y_G256_newbasis1_1;
  int _1_version__3_x_G256_newbasis1_0;
  int _1_version__3_x_G256_newbasis1_1;
  int _2_y_G256_newbasis1_0;
  int _2_y_G256_newbasis1_1;
  int _2_x_G256_newbasis1_0;
  int _2_x_G256_newbasis1_1;
  int _if_cond_20_G256_newbasis1_0;
  int _if_cond_20_G256_newbasis1_1;
  int _if_neg_cond_20_G256_newbasis1_0;
  int _if_neg_cond_20_G256_newbasis1_1;
  int temp_var_21_G256_newbasis1_0;
  int temp_var_21_G256_newbasis1_1;
  int temp_var_22_G256_newbasis1_0;
  int temp_var_22_G256_newbasis1_1;
  int temp_var_23_G256_newbasis1_0;
  int temp_var_23_G256_newbasis1_1;
  int _1_version__2_y_G256_newbasis1_0;
  int _1_version__2_y_G256_newbasis1_1;
  int _1_version__2_x_G256_newbasis1_0;
  int _1_version__2_x_G256_newbasis1_1;
  int _1_y_G256_newbasis1_0;
  int _1_y_G256_newbasis1_1;
  int _1_x_G256_newbasis1_0;
  int _1_x_G256_newbasis1_1;
  int _if_cond_24_G256_newbasis1_0;
  int _if_cond_24_G256_newbasis1_1;
  int _if_neg_cond_24_G256_newbasis1_0;
  int _if_neg_cond_24_G256_newbasis1_1;
  int temp_var_25_G256_newbasis1_0;
  int temp_var_25_G256_newbasis1_1;
  int temp_var_26_G256_newbasis1_0;
  int temp_var_26_G256_newbasis1_1;
  int temp_var_27_G256_newbasis1_0;
  int temp_var_27_G256_newbasis1_1;
  int _1_version__1_y_G256_newbasis1_0;
  int _1_version__1_y_G256_newbasis1_1;
  int _1_version__1_x_G256_newbasis1_0;
  int _1_version__1_x_G256_newbasis1_1;
  int _0_x_G256_newbasis1_0;
  int _0_x_G256_newbasis1_1;
  int _0_y_G256_newbasis1_0;
  int _0_y_G256_newbasis1_1;
  int _if_cond_28_G256_newbasis1_0;
  int _if_cond_28_G256_newbasis1_1;
  int _if_neg_cond_28_G256_newbasis1_0;
  int _if_neg_cond_28_G256_newbasis1_1;
  int temp_var_29_G256_newbasis1_0;
  int temp_var_29_G256_newbasis1_1;
  int temp_var_30_G256_newbasis1_0;
  int temp_var_30_G256_newbasis1_1;
  int temp_var_31_G256_newbasis1_0;
  int temp_var_31_G256_newbasis1_1;
  int _1_version__0_y_G256_newbasis1_0;
  int _1_version__0_y_G256_newbasis1_1;
  int _1_version__0_x_G256_newbasis1_0;
  int _1_version__0_x_G256_newbasis1_1;
  y_G256_newbasis1_0 = dec_0;
  y_G256_newbasis1_1 = dec_0;
  _7_y_G256_newbasis1_0 = y_G256_newbasis1_0;
  _7_y_G256_newbasis1_1 = y_G256_newbasis1_1;
  _7_x_G256_newbasis1_0 = _1_version_t_0;
  _7_x_G256_newbasis1_1 = _1_version_t_1;
  _if_cond_0_G256_newbasis1_0 = _7_x_G256_newbasis1_0 & dec_1;
  _if_cond_0_G256_newbasis1_1 = _7_x_G256_newbasis1_1 & dec_1;
  _if_neg_cond_0_G256_newbasis1_0 = !_if_cond_0_G256_newbasis1_0;
  _if_neg_cond_0_G256_newbasis1_1 = _if_cond_0_G256_newbasis1_1;
  temp_var_1_G256_newbasis1_0 = _7_y_G256_newbasis1_0 ^ dec_36;
  temp_var_1_G256_newbasis1_1 = _7_y_G256_newbasis1_1 ;
  temp_var_2_G256_newbasis1_0 = temp_var_1_G256_newbasis1_0 * _if_cond_0_G256_newbasis1_0;
  temp_var_2_G256_newbasis1_1 = temp_var_1_G256_newbasis1_1 * _if_cond_0_G256_newbasis1_1;
  temp_var_3_G256_newbasis1_0 = _7_y_G256_newbasis1_0 * _if_neg_cond_0_G256_newbasis1_0;
  temp_var_3_G256_newbasis1_1 = _7_y_G256_newbasis1_1 * _if_neg_cond_0_G256_newbasis1_1;
  _1_version__7_y_G256_newbasis1_0 = temp_var_2_G256_newbasis1_0 + temp_var_3_G256_newbasis1_0;
  _1_version__7_y_G256_newbasis1_1 = temp_var_2_G256_newbasis1_1 + temp_var_3_G256_newbasis1_1;
  _1_version__7_x_G256_newbasis1_0 = _7_x_G256_newbasis1_0 >> dec_1;
  _1_version__7_x_G256_newbasis1_1 = _7_x_G256_newbasis1_1 >> dec_1;
  _6_x_G256_newbasis1_0 = _1_version__7_x_G256_newbasis1_0;
  _6_x_G256_newbasis1_1 = _1_version__7_x_G256_newbasis1_1;
  _6_y_G256_newbasis1_0 = _1_version__7_y_G256_newbasis1_0;
  _6_y_G256_newbasis1_1 = _1_version__7_y_G256_newbasis1_1;
  _if_cond_4_G256_newbasis1_0 = _6_x_G256_newbasis1_0 & dec_1;
  _if_cond_4_G256_newbasis1_1 = _6_x_G256_newbasis1_1 & dec_1;
  _if_neg_cond_4_G256_newbasis1_0 = !_if_cond_4_G256_newbasis1_0;
  _if_neg_cond_4_G256_newbasis1_1 = _if_cond_4_G256_newbasis1_1;
  temp_var_5_G256_newbasis1_0 = _6_y_G256_newbasis1_0 ^ dec_3;
  temp_var_5_G256_newbasis1_1 = _6_y_G256_newbasis1_1 ;
  temp_var_6_G256_newbasis1_0 = temp_var_5_G256_newbasis1_0 * _if_cond_4_G256_newbasis1_0;
  temp_var_6_G256_newbasis1_1 = temp_var_5_G256_newbasis1_1 * _if_cond_4_G256_newbasis1_1;
  temp_var_7_G256_newbasis1_0 = _6_y_G256_newbasis1_0 * _if_neg_cond_4_G256_newbasis1_0;
  temp_var_7_G256_newbasis1_1 = _6_y_G256_newbasis1_1 * _if_neg_cond_4_G256_newbasis1_1;
  _1_version__6_y_G256_newbasis1_0 = temp_var_6_G256_newbasis1_0 + temp_var_7_G256_newbasis1_0;
  _1_version__6_y_G256_newbasis1_1 = temp_var_6_G256_newbasis1_1 + temp_var_7_G256_newbasis1_1;
  _1_version__6_x_G256_newbasis1_0 = _6_x_G256_newbasis1_0 >> dec_1;
  _1_version__6_x_G256_newbasis1_1 = _6_x_G256_newbasis1_1 >> dec_1;
  _5_x_G256_newbasis1_0 = _1_version__6_x_G256_newbasis1_0;
  _5_x_G256_newbasis1_1 = _1_version__6_x_G256_newbasis1_1;
  _5_y_G256_newbasis1_0 = _1_version__6_y_G256_newbasis1_0;
  _5_y_G256_newbasis1_1 = _1_version__6_y_G256_newbasis1_1;
  _if_cond_8_G256_newbasis1_0 = _5_x_G256_newbasis1_0 & dec_1;
  _if_cond_8_G256_newbasis1_1 = _5_x_G256_newbasis1_1 & dec_1;
  _if_neg_cond_8_G256_newbasis1_0 = !_if_cond_8_G256_newbasis1_0;
  _if_neg_cond_8_G256_newbasis1_1 = _if_cond_8_G256_newbasis1_1;
  temp_var_9_G256_newbasis1_0 = _5_y_G256_newbasis1_0 ^ dec_4;
  temp_var_9_G256_newbasis1_1 = _5_y_G256_newbasis1_1;
  temp_var_10_G256_newbasis1_0 = temp_var_9_G256_newbasis1_0 * _if_cond_8_G256_newbasis1_0;
  temp_var_10_G256_newbasis1_1 = temp_var_9_G256_newbasis1_1 * _if_cond_8_G256_newbasis1_1;
  temp_var_11_G256_newbasis1_0 = _5_y_G256_newbasis1_0 * _if_neg_cond_8_G256_newbasis1_0;
  temp_var_11_G256_newbasis1_1 = _5_y_G256_newbasis1_1 * _if_neg_cond_8_G256_newbasis1_1;
  _1_version__5_y_G256_newbasis1_0 = temp_var_10_G256_newbasis1_0 + temp_var_11_G256_newbasis1_0;
  _1_version__5_y_G256_newbasis1_1 = temp_var_10_G256_newbasis1_1 + temp_var_11_G256_newbasis1_1;
  _1_version__5_x_G256_newbasis1_0 = _5_x_G256_newbasis1_0 >> dec_1;
  _1_version__5_x_G256_newbasis1_1 = _5_x_G256_newbasis1_1 >> dec_1;
  _4_y_G256_newbasis1_0 = _1_version__5_y_G256_newbasis1_0;
  _4_y_G256_newbasis1_1 = _1_version__5_y_G256_newbasis1_1;
  _4_x_G256_newbasis1_0 = _1_version__5_x_G256_newbasis1_0;
  _4_x_G256_newbasis1_1 = _1_version__5_x_G256_newbasis1_1;
  _if_cond_12_G256_newbasis1_0 = _4_x_G256_newbasis1_0 & dec_1;
  _if_cond_12_G256_newbasis1_1 = _4_x_G256_newbasis1_1 & dec_1;
  _if_neg_cond_12_G256_newbasis1_0 = !_if_cond_12_G256_newbasis1_0;
  _if_neg_cond_12_G256_newbasis1_1 = _if_cond_12_G256_newbasis1_1;
  temp_var_13_G256_newbasis1_0 = _4_y_G256_newbasis1_0 ^ dec_220;
  temp_var_13_G256_newbasis1_1 = _4_y_G256_newbasis1_1;
  temp_var_14_G256_newbasis1_0 = temp_var_13_G256_newbasis1_0 * _if_cond_12_G256_newbasis1_0;
  temp_var_14_G256_newbasis1_1 = temp_var_13_G256_newbasis1_1 * _if_cond_12_G256_newbasis1_1;
  temp_var_15_G256_newbasis1_0 = _4_y_G256_newbasis1_0 * _if_neg_cond_12_G256_newbasis1_0;
  temp_var_15_G256_newbasis1_1 = _4_y_G256_newbasis1_1 * _if_neg_cond_12_G256_newbasis1_1;
  _1_version__4_y_G256_newbasis1_0 = temp_var_14_G256_newbasis1_0 + temp_var_15_G256_newbasis1_0;
  _1_version__4_y_G256_newbasis1_1 = temp_var_14_G256_newbasis1_1 + temp_var_15_G256_newbasis1_1;
  _1_version__4_x_G256_newbasis1_0 = _4_x_G256_newbasis1_0 >> dec_1;
  _1_version__4_x_G256_newbasis1_1 = _4_x_G256_newbasis1_1 >> dec_1;
  _3_x_G256_newbasis1_0 = _1_version__4_x_G256_newbasis1_0;
  _3_x_G256_newbasis1_1 = _1_version__4_x_G256_newbasis1_1;
  _3_y_G256_newbasis1_0 = _1_version__4_y_G256_newbasis1_0;
  _3_y_G256_newbasis1_1 = _1_version__4_y_G256_newbasis1_1;
  _if_cond_16_G256_newbasis1_0 = _3_x_G256_newbasis1_0 & dec_1;
  _if_cond_16_G256_newbasis1_1 = _3_x_G256_newbasis1_1 & dec_1;
  _if_neg_cond_16_G256_newbasis1_0 = !_if_cond_16_G256_newbasis1_0;
  _if_neg_cond_16_G256_newbasis1_1 = _if_cond_16_G256_newbasis1_1;
  temp_var_17_G256_newbasis1_0 = _3_y_G256_newbasis1_0 ^ dec_11;
  temp_var_17_G256_newbasis1_1 = _3_y_G256_newbasis1_1;
  temp_var_18_G256_newbasis1_0 = temp_var_17_G256_newbasis1_0 * _if_cond_16_G256_newbasis1_0;
  temp_var_18_G256_newbasis1_1 = temp_var_17_G256_newbasis1_1 * _if_cond_16_G256_newbasis1_1;
  temp_var_19_G256_newbasis1_0 = _3_y_G256_newbasis1_0 * _if_neg_cond_16_G256_newbasis1_0;
  temp_var_19_G256_newbasis1_1 = _3_y_G256_newbasis1_1 * _if_neg_cond_16_G256_newbasis1_1;
  _1_version__3_y_G256_newbasis1_0 = temp_var_18_G256_newbasis1_0 + temp_var_19_G256_newbasis1_0;
  _1_version__3_y_G256_newbasis1_1 = temp_var_18_G256_newbasis1_1 + temp_var_19_G256_newbasis1_1;
  _1_version__3_x_G256_newbasis1_0 = _3_x_G256_newbasis1_0 >> dec_1;
  _1_version__3_x_G256_newbasis1_1 = _3_x_G256_newbasis1_1 >> dec_1;
  _2_y_G256_newbasis1_0 = _1_version__3_y_G256_newbasis1_0;
  _2_y_G256_newbasis1_1 = _1_version__3_y_G256_newbasis1_1;
  _2_x_G256_newbasis1_0 = _1_version__3_x_G256_newbasis1_0;
  _2_x_G256_newbasis1_1 = _1_version__3_x_G256_newbasis1_1;
  _if_cond_20_G256_newbasis1_0 = _2_x_G256_newbasis1_0 & dec_1;
  _if_cond_20_G256_newbasis1_1 = _2_x_G256_newbasis1_1 & dec_1;
  _if_neg_cond_20_G256_newbasis1_0 = !_if_cond_20_G256_newbasis1_0;
  _if_neg_cond_20_G256_newbasis1_1 = !_if_cond_20_G256_newbasis1_1;
  temp_var_21_G256_newbasis1_0 = _2_y_G256_newbasis1_0 ^ dec_158;
  temp_var_21_G256_newbasis1_1 = _2_y_G256_newbasis1_1;
  temp_var_22_G256_newbasis1_0 = temp_var_21_G256_newbasis1_0 * _if_cond_20_G256_newbasis1_0;
  temp_var_22_G256_newbasis1_1 = temp_var_21_G256_newbasis1_1 * _if_cond_20_G256_newbasis1_1;
  temp_var_23_G256_newbasis1_0 = _2_y_G256_newbasis1_0 * _if_neg_cond_20_G256_newbasis1_0;
  temp_var_23_G256_newbasis1_1 = _2_y_G256_newbasis1_1 * _if_neg_cond_20_G256_newbasis1_1;
  _1_version__2_y_G256_newbasis1_0 = temp_var_22_G256_newbasis1_0 + temp_var_23_G256_newbasis1_0;
  _1_version__2_y_G256_newbasis1_1 = temp_var_22_G256_newbasis1_1 + temp_var_23_G256_newbasis1_1;
  _1_version__2_x_G256_newbasis1_0 = _2_x_G256_newbasis1_0 >> dec_1;
  _1_version__2_x_G256_newbasis1_1 = _2_x_G256_newbasis1_1 >> dec_1;
  _1_y_G256_newbasis1_0 = _1_version__2_y_G256_newbasis1_0;
  _1_y_G256_newbasis1_1 = _1_version__2_y_G256_newbasis1_1;
  _1_x_G256_newbasis1_0 = _1_version__2_x_G256_newbasis1_0;
  _1_x_G256_newbasis1_1 = _1_version__2_x_G256_newbasis1_1;
  _if_cond_24_G256_newbasis1_0 = _1_x_G256_newbasis1_0 & dec_1;
  _if_cond_24_G256_newbasis1_1 = _1_x_G256_newbasis1_1 & dec_1;
  _if_neg_cond_24_G256_newbasis1_0 = !_if_cond_24_G256_newbasis1_0;
  _if_neg_cond_24_G256_newbasis1_1 = _if_cond_24_G256_newbasis1_1;
  temp_var_25_G256_newbasis1_0 = _1_y_G256_newbasis1_0 ^ dec_45;
  temp_var_25_G256_newbasis1_1 = _1_y_G256_newbasis1_1 ^ dec_45;
  temp_var_26_G256_newbasis1_0 = temp_var_25_G256_newbasis1_0 * _if_cond_24_G256_newbasis1_0;
  temp_var_26_G256_newbasis1_1 = temp_var_25_G256_newbasis1_1 * _if_cond_24_G256_newbasis1_1;
  temp_var_27_G256_newbasis1_0 = _1_y_G256_newbasis1_0 * _if_neg_cond_24_G256_newbasis1_0;
  temp_var_27_G256_newbasis1_1 = _1_y_G256_newbasis1_1 * _if_neg_cond_24_G256_newbasis1_1;
  _1_version__1_y_G256_newbasis1_0 = temp_var_26_G256_newbasis1_0 + temp_var_27_G256_newbasis1_0;
  _1_version__1_y_G256_newbasis1_1 = temp_var_26_G256_newbasis1_1 + temp_var_27_G256_newbasis1_1;
  _1_version__1_x_G256_newbasis1_0 = _1_x_G256_newbasis1_0 >> dec_1;
  _1_version__1_x_G256_newbasis1_1 = _1_x_G256_newbasis1_1 >> dec_1;
  _0_x_G256_newbasis1_0 = _1_version__1_x_G256_newbasis1_0;
  _0_x_G256_newbasis1_1 = _1_version__1_x_G256_newbasis1_1;
  _0_y_G256_newbasis1_0 = _1_version__1_y_G256_newbasis1_0;
  _0_y_G256_newbasis1_1 = _1_version__1_y_G256_newbasis1_1;
  _if_cond_28_G256_newbasis1_0 = _0_x_G256_newbasis1_0 & dec_1;
  _if_cond_28_G256_newbasis1_1 = _0_x_G256_newbasis1_1 & dec_1;
  _if_neg_cond_28_G256_newbasis1_0 = !_if_cond_28_G256_newbasis1_0;
  _if_neg_cond_28_G256_newbasis1_1 = !_if_cond_28_G256_newbasis1_1;
  temp_var_29_G256_newbasis1_0 = _0_y_G256_newbasis1_0 ^ dec_88;
  temp_var_29_G256_newbasis1_1 = _0_y_G256_newbasis1_1;
  temp_var_30_G256_newbasis1_0 = temp_var_29_G256_newbasis1_0 * _if_cond_28_G256_newbasis1_0;
  temp_var_30_G256_newbasis1_1 = temp_var_29_G256_newbasis1_1 * _if_cond_28_G256_newbasis1_1;
  temp_var_31_G256_newbasis1_0 = _0_y_G256_newbasis1_0 * _if_neg_cond_28_G256_newbasis1_0;
  temp_var_31_G256_newbasis1_1 = _0_y_G256_newbasis1_1 * _if_neg_cond_28_G256_newbasis1_1;
  _1_version__0_y_G256_newbasis1_0 = temp_var_30_G256_newbasis1_0 + temp_var_31_G256_newbasis1_0;
  _1_version__0_y_G256_newbasis1_1 = temp_var_30_G256_newbasis1_1 + temp_var_31_G256_newbasis1_1;
  _1_version__0_x_G256_newbasis1_0 = _0_x_G256_newbasis1_0 >> dec_1;
  _1_version__0_x_G256_newbasis1_1 = _0_x_G256_newbasis1_1 >> dec_1;
  _2_version_t_0 = _1_version__0_y_G256_newbasis1_0;
  _2_version_t_1 = _1_version__0_y_G256_newbasis1_1;
  *__return_value_0 = _2_version_t_0 ^ dec_99;
  *__return_value_1 = _2_version_t_1 ;
}


"""

def build_testbench():
    # Use Regex to parse the gigantic signature and auto-map variables
    sig_match = re.search(r'void sbox\((.*?)\)', MASKED_CODE, re.DOTALL)
    if not sig_match:
        raise ValueError("Could not find the masked 'void sbox(...)' signature!")
    
    params = sig_match.group(1).split(',')
    c_args = []
    
    # Auto-generate the C argument list
    for p in params:
        name = p.strip().split()[-1].replace('*', '')
        if name == 'n_0': c_args.append('n_0')
        elif name == 'n_1': c_args.append('n_1')
        elif name == '__return_value_0': c_args.append('&ret_0')
        elif name == '__return_value_1': c_args.append('&ret_1')
        elif name.startswith('dec_'):
            c_args.append(name.split('_')[1]) # Extract the integer
        elif name.startswith('rand_'):
            c_args.append('rand() % 256') # Give it fresh randomness
        else:
            c_args.append('0')

    args_str = ",\n        ".join(c_args)

    # Generate the complete C file string
    c_source = f"""
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>

    // --- GOLDEN CODE (Renamed safely) ---
    #define sbox golden_sbox
    {GOLDEN_CODE}
    #undef sbox

    // --- SOFTWARE MOCKS FOR HARDWARE GADGETS ---
    // Simulate a hardware register passing data through
    int reg(int x) {{ return x; }}

    // --- MASKED CODE (Renamed safely) ---
    #define sbox masked_sbox
    {MASKED_CODE}
    #undef sbox

    int main() {{
        srand(time(NULL));
        int mismatches = 0;

        printf("--------------------------------------------------\\n");
        printf("Starting Equivalence Check for all 256 inputs...\\n");
        printf("--------------------------------------------------\\n");

        for (int n = 0; n < 256; n++) {{
            // 1. Get true expected value
            int expected = golden_sbox(n);

            // 2. Generate random masks for input
            int n_0 = rand() % 256;
            int n_1 = n ^ n_0; 
            
            int ret_0 = 0, ret_1 = 0;

            // 3. Fire the Masked Hardware function
            masked_sbox(
                {args_str}
            );

            // 4. Recombine shares and check
            int actual = ret_0 ^ ret_1;

            if (expected != actual) {{
                if (mismatches < 5) {{ // Only print first 5 to avoid spam
                    printf("Mismatch at n=%d (0x%02X)! Expected: 0x%02X | Actual: 0x%02X (Share0: 0x%02X, Share1: 0x%02X)\\n", 
                            n, n, expected, actual, ret_0, ret_1);
                }}
                mismatches++;
            }}
        }}

        printf("--------------------------------------------------\\n");
        if (mismatches == 0) {{
            printf("✅ SUCCESS: The masked code is perfectly equivalent to the golden code!\\n");
        }} else {{
            printf("❌ FAILED: Found %d mismatches.\\n", mismatches);
            printf("Hint: Check the final XOR addition of dec_99 (0x63). You are XORing it to BOTH shares!\\n");
        }}
        printf("--------------------------------------------------\\n");

        return 0;
    }}
    """
    
    with open("sbox_verification.c", "w") as f:
        f.write(c_source)

def compile_and_run():
    print("⚙️ Compiling sbox_verification.c with GCC...")
    compile_cmd = ["gcc", "sbox_verification.c", "-o", "sbox_verify"]
    
    try:
        subprocess.run(compile_cmd, check=True)
    except subprocess.CalledProcessError:
        print("❌ Compilation failed! Check C code syntax.")
        return

    print("🚀 Running verification...\n")
    # Run the executable
    os_exec = "./sbox_verify" if os.name != 'nt' else "sbox_verify.exe"
    subprocess.run([os_exec])

if __name__ == "__main__":
    build_testbench()
    compile_and_run()
