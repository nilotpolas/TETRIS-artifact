
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// ==========================================
// 1. UTILITY FUNCTIONS
// ==========================================

int reg(int x) {
    return x;
}

// ==========================================
// 2. GOLDEN (UNMASKED) IMPLEMENTATION
// ==========================================

#include <stdint.h>

void sbox_golden(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int dec_1,
          int *o0, int *o1, int *o2, int *o3, int *o4, int *o5, int *o6, int *o7) {
    
    // Intermediate variables
    int n1, n2, n3, n6, n7;
    int t0, t1, t2, t3, t4, t5, t6, t7;
    int nt0, nt1, nt2, nt3, nt4, nt5;
    int o0_val, o1_val, o2_val, o3_val, o4_val, o5_val, o6_val, o7_val;

    // Layer 1: Input Inversions
    n1 = i1 ^ dec_1;
    n2 = i2 ^ dec_1;
    n3 = i3 ^ dec_1;
    n6 = i6 ^ dec_1;
    n7 = i7 ^ dec_1;

    // Layer 2: AND operations
    t0 = n6 & n7;
    t1 = n3 & n2;
    t2 = n2 & n1;

    // Layer 3: Inversions
    nt0 = t0 ^ dec_1;
    nt1 = t1 ^ dec_1;
    nt2 = t2 ^ dec_1;

    // Layer 4: AND operations
    t3 = nt0 & nt1;
    t4 = nt1 & n3;

    // Layer 5: Inversions
    nt3 = t3 ^ dec_1;
    
    // Layer 6: AND operations
    t5 = nt2 & nt3;
    
    // Layer 7: Inversions
    nt4 = t4 ^ dec_1;
    nt5 = t5 ^ dec_1;

    // Layer 8: Final AND operations
    t6 = nt3 & nt0;
    t7 = nt4 & nt5;

    // Layer 9: Final XOR with inputs - TAC COMPATIBLE FORMAT
    // First assign to temporary variables
    o6_val = t0 ^ i4;
    o5_val = t1 ^ i0;
    o2_val = t2 ^ i6;
    o7_val = t3 ^ i5;
    o0_val = t7 ^ i2;
    o4_val = t6 ^ i3;
    o1_val = t5 ^ i7;
    o3_val = t4 ^ i1;

    // Then assign temporaries to output pointers
    *o0 = o0_val;
    *o1 = o1_val;
    *o2 = o2_val;
    *o3 = o3_val;
    *o4 = o4_val;
    *o5 = o5_val;
    *o6 = o6_val;
    *o7 = o7_val;
}

// ==========================================
// 3. MASKED IMPLEMENTATION
// ==========================================

// === GADGET DEFINITIONS ===

// --- hpc3 ---

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
    a_share_neg = !(a_share);
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


// --- hpc3o ---

void hpc3o_first_half_1_order(int a_share, int b_share, int w_share, int rand, int rand_prime, int *out_share) {
    int xor_br;
    int and_ar;
    int xor_step1;
    int xor_step2;

    xor_br = b_share ^ rand;
    and_ar = a_share & xor_br;
    xor_step1 = w_share ^ and_ar;
    xor_step2 = xor_step1 ^ rand_prime;
    
    *out_share = reg(xor_step2);
}

void hpc3o_v_1_order(int a_share, int b_share, int *v_share, int rand) {
    int xor_br;
    int temp;
    int and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br); // This remains an R register in Algo 7
    
    and_ta = a_share & temp;
    *v_share = and_ta; // Notice: NO outer reg() here for HPC3o!
}

void hpc3o_w_1_order(int a_share, int rand, int rand_prime, int *w_share) {
    int and_ar;
    int xor_step1;

    // Notice: Algo 7 does not negate a_share in the else branch
    and_ar = a_share & rand;
    xor_step1 = and_ar ^ rand_prime;
    
    *w_share = reg(xor_step1);
}

void hpc3o_xor_vw_1_order(int v_share, int w_share, int *u_share) {
    *u_share = v_share ^ w_share;
}
void HPC3o(int a0, int a1, int b0, int b1, int w0, int w1, int * c0, int * c1, int rand_01, int rand_prime_01)
{
	int u01, u10;
	int v01, v10;
	int w01, w10;

	hpc3o_first_half_1_order(a0, b0, w0, rand_01, rand_prime_01, &w01);
	hpc3o_v_1_order(a0, b1, &v01, rand_01);
	hpc3o_xor_vw_1_order(v01, w01, &u01);

	hpc3o_first_half_1_order(a1, b1, w1, rand_01, rand_prime_01, &w10);
	hpc3o_v_1_order(a1, b0, &v10, rand_01);
	hpc3o_xor_vw_1_order(v10, w10, &u10);

	*c0 = u01;
	*c1 = u10;
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
    a_neg = !(a_share);
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


// --- hpc2o ---

void hpc2o_first_half_1_order(int a_share, int b_share, int w_share, int rand, int *out_share) {
    int temp_ab;
    int a_neg;
    int temp_ar;
    int xor_step1;
    int xor_step2;

    temp_ab = a_share & b_share;
    a_neg = !a_share;
    temp_ar = a_neg & rand;
    
    xor_step1 = w_share ^ temp_ab;
    xor_step2 = xor_step1 ^ temp_ar;
    
    *out_share = reg(xor_step2);
}

void hpc2o_v_1_order(int a_share, int b_share, int *v_share, int rand) {
    int xor_br;
    int temp;
    int and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br); // This remains an R register in Algo 6
    
    and_ta = temp & a_share;
    *v_share = reg(and_ta);
}

void hpc2o_w_1_order(int a_share, int rand, int *w_share) {
    int a_neg;
    int and_ar;

    a_neg = !a_share;
    
    and_ar = a_neg & rand;
    *w_share = reg(and_ar);
}

void hpc2o_xor_vw_1_order(int v_share, int w_share, int *u_share) {
    *u_share = v_share ^ w_share;
}

void hpc2o_or_vw_1_order(int v_share, int w_share, int *u_share) {
    *u_share = v_share | w_share;
}
void HPC2o(int a0, int a1, int b0, int b1, int w0, int w1, int * c0, int * c1, int rand_01)
{
	int u01, u10;
	int v01, v10;
	int w01, w10;

	hpc2o_first_half_1_order(a0, b0, w0, rand_01, &w01);
	hpc2o_v_1_order(a0, b1, &v01, rand_01);
	hpc2o_xor_vw_1_order(v01, w01, &u01);

	hpc2o_first_half_1_order(a1, b1, w1, rand_01, &w10);
	hpc2o_v_1_order(a1, b0, &v10, rand_01);
	hpc2o_xor_vw_1_order(v10, w10, &u10);

	*c0 = u01;
	*c1 = u10;
}


// --- hpc2_swapped ---

void hpc2sw_same_shares_1_order(int a_share, int b_share, int * u_share) {
    *u_share = a_share & b_share;
}

void hpc2sw_v_1_order(int a_share, int b_share, int * v_share, int rand) {
    int temp;
    temp = reg(b_share ^ rand);
    *v_share = reg(temp & a_share);
}

void hpc2sw_w_1_order(int a_share, int rand, int * w_share) {
    int a_neg;
    a_neg = !(a_share);
    *w_share = reg(a_neg & rand);
}

void hpc2sw_xor_vw_1_order(int v_share, int w_share, int * u_share) {
    *u_share = v_share ^ w_share;
}

void HPC2_swapped(int a0, int a1, int b0, int b1, int * c0, int * c1, int rand_01)
{
	int u00, u01, u10, u11;
	int v01, v10;

	int w01, w10;

	hpc2sw_same_shares_1_order(a0, b0, &u00);
	hpc2sw_v_1_order(b0, a1, &v01, rand_01);
	hpc2sw_w_1_order(b0, rand_01, &w01);
	hpc2sw_xor_vw_1_order(v01, w01, &u01);

	hpc2sw_v_1_order(b1, a0, &v10, rand_01);
	hpc2sw_w_1_order(b1, rand_01, &w10);
	hpc2sw_xor_vw_1_order(v10, w10, &u10);

	hpc2sw_same_shares_1_order(a1, b1, &u11);
	*c0 = u00 ^ u01;
	*c1 = u10 ^ u11;
}


// --- hpc2o_swapped ---

void hpc2osw_first_half_1_order(int a_share, int b_share, int w_share, int rand, int *out_share) {
    int temp_ab;
    int a_neg;
    int temp_ar;
    int xor_step1;
    int xor_step2;

    temp_ab = a_share & b_share;
    a_neg = !a_share;
    temp_ar = a_neg & rand;

    xor_step1 = w_share ^ temp_ab;
    xor_step2 = xor_step1 ^ temp_ar;

    *out_share = reg(xor_step2);
}

void hpc2osw_v_1_order(int a_share, int b_share, int *v_share, int rand) {
    int xor_br;
    int temp;
    int and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br);

    and_ta = temp & a_share;
    *v_share = reg(and_ta);
}

void hpc2osw_w_1_order(int a_share, int rand, int *w_share) {
    int a_neg;
    int and_ar;

    a_neg = !a_share;

    and_ar = a_neg & rand;
    *w_share = reg(and_ar);
}

void hpc2osw_xor_vw_1_order(int v_share, int w_share, int *u_share) {
    *u_share = v_share ^ w_share;
}

void hpc2osw_or_vw_1_order(int v_share, int w_share, int *u_share) {
    *u_share = v_share | w_share;
}
void HPC2o_swapped(int a0, int a1, int b0, int b1, int w0, int w1, int * c0, int * c1, int rand_01)
{
	int u01, u10;
	int v01, v10;
	int w01, w10;

	hpc2osw_first_half_1_order(b0, a0, w0, rand_01, &w01);
	hpc2osw_v_1_order(b0, a1, &v01, rand_01);
	hpc2osw_xor_vw_1_order(v01, w01, &u01);

	hpc2osw_first_half_1_order(b1, a1, w1, rand_01, &w10);
	hpc2osw_v_1_order(b1, a0, &v10, rand_01);
	hpc2osw_xor_vw_1_order(v10, w10, &u10);

	*c0 = u01;
	*c1 = u10;
}

void sbox_masked(int sb_n0_0, int sb_n0_1, int sb_n1_0, int sb_n1_1, int sb_n2_0, int sb_n2_1, int sb_n3_0, int sb_n3_1, int sb_n4_0, int sb_n4_1, int sb_n5_0, int sb_n5_1, int sb_n6_0, int sb_n6_1, int sb_n7_0, int sb_n7_1, int *sb_o0_0, int *sb_o0_1, int *sb_o1_0, int *sb_o1_1, int *sb_o2_0, int *sb_o2_1, int *sb_o3_0, int *sb_o3_1, int *sb_o4_0, int *sb_o4_1, int *sb_o5_0, int *sb_o5_1, int *sb_o6_0, int *sb_o6_1, int *sb_o7_0, int *sb_o7_1, int dec_1, int dec_0, int rand_15, int rand_30, int rand_16, int rand_32, int rand_48, int rand_1, int rand_17, int rand_33, int rand_18, int rand_2, int rand_35, int rand_3, int rand_19, int rand_34, int rand_4, int rand_26, int rand_36, int rand_5, int rand_20, int rand_37, int rand_6, int rand_21, int rand_29, int rand_38, int rand_8, int rand_22, int rand_39, int rand_40, int rand_44, int rand_7, int rand_23, int rand_9, int rand_24, int rand_45, int rand_10, int rand_31, int rand_41, int rand_11, int rand_25, int rand_43, int rand_47, int rand_42, int rand_12, int rand_27, int rand_46, int rand_13, int rand_28, int rand_14)
{
  int sb_y0_0;
  int sb_y0_1;
  int sb_y1_0;
  int sb_y1_1;
  int sb_y2_0;
  int sb_y2_1;
  int sb_y3_0;
  int sb_y3_1;
  int sb_y4_0;
  int sb_y4_1;
  int sb_y5_0;
  int sb_y5_1;
  int sb_y6_0;
  int sb_y6_1;
  int sb_y7_0;
  int sb_y7_1;
  int sb_i0_0;
  int sb_i0_1;
  int sb_i1_0;
  int sb_i1_1;
  int sb_i2_0;
  int sb_i2_1;
  int sb_i3_0;
  int sb_i3_1;
  int sb_i4_0;
  int sb_i4_1;
  int sb_i5_0;
  int sb_i5_1;
  int sb_i6_0;
  int sb_i6_1;
  int sb_i7_0;
  int sb_i7_1;
  int fy0_0;
  int fy0_1;
  int fy1_0;
  int fy1_1;
  int fy2_0;
  int fy2_1;
  int fy3_0;
  int fy3_1;
  int fy4_0;
  int fy4_1;
  int fy5_0;
  int fy5_1;
  int fy6_0;
  int fy6_1;
  int fy7_0;
  int fy7_1;
  int temp_var_0_0;
  int temp_var_0_1;
  temp_var_0_0 = sb_n0_0 ^ sb_n1_0;
  temp_var_0_1 = sb_n0_1 ^ sb_n1_1;
  int temp_var_1_0;
  int temp_var_1_1;
  temp_var_1_0 = temp_var_0_0 ^ sb_n2_0;
  temp_var_1_1 = temp_var_0_1 ^ sb_n2_1;
  int temp_var_2_0;
  int temp_var_2_1;
  temp_var_2_0 = temp_var_1_0 ^ sb_n3_0;
  temp_var_2_1 = temp_var_1_1 ^ sb_n3_1;
  sb_y0_0 = temp_var_2_0 ^ sb_n6_0;
  sb_y0_1 = temp_var_2_1 ^ sb_n6_1;
  int temp_var_3_0;
  int temp_var_3_1;
  temp_var_3_0 = sb_n0_0 ^ sb_n5_0;
  temp_var_3_1 = sb_n0_1 ^ sb_n5_1;
  sb_y1_0 = temp_var_3_0 ^ sb_n6_0;
  sb_y1_1 = temp_var_3_1 ^ sb_n6_1;
  sb_y2_0 = sb_n0_0;
  sb_y2_1 = sb_n0_1;
  int temp_var_4_0;
  int temp_var_4_1;
  temp_var_4_0 = sb_n0_0 ^ sb_n1_0;
  temp_var_4_1 = sb_n0_1 ^ sb_n1_1;
  int temp_var_5_0;
  int temp_var_5_1;
  temp_var_5_0 = temp_var_4_0 ^ sb_n3_0;
  temp_var_5_1 = temp_var_4_1 ^ sb_n3_1;
  int temp_var_6_0;
  int temp_var_6_1;
  temp_var_6_0 = temp_var_5_0 ^ sb_n4_0;
  temp_var_6_1 = temp_var_5_1 ^ sb_n4_1;
  sb_y3_0 = temp_var_6_0 ^ sb_n7_0;
  sb_y3_1 = temp_var_6_1 ^ sb_n7_1;
  int temp_var_7_0;
  int temp_var_7_1;
  temp_var_7_0 = sb_n0_0 ^ sb_n5_0;
  temp_var_7_1 = sb_n0_1 ^ sb_n5_1;
  int temp_var_8_0;
  int temp_var_8_1;
  temp_var_8_0 = temp_var_7_0 ^ sb_n6_0;
  temp_var_8_1 = temp_var_7_1 ^ sb_n6_1;
  sb_y4_0 = temp_var_8_0 ^ sb_n7_0;
  sb_y4_1 = temp_var_8_1 ^ sb_n7_1;
  int temp_var_9_0;
  int temp_var_9_1;
  temp_var_9_0 = sb_n0_0 ^ sb_n1_0;
  temp_var_9_1 = sb_n0_1 ^ sb_n1_1;
  int temp_var_10_0;
  int temp_var_10_1;
  temp_var_10_0 = temp_var_9_0 ^ sb_n5_0;
  temp_var_10_1 = temp_var_9_1 ^ sb_n5_1;
  sb_y5_0 = temp_var_10_0 ^ sb_n6_0;
  sb_y5_1 = temp_var_10_1 ^ sb_n6_1;
  int temp_var_11_0;
  int temp_var_11_1;
  temp_var_11_0 = sb_n0_0 ^ sb_n4_0;
  temp_var_11_1 = sb_n0_1 ^ sb_n4_1;
  int temp_var_12_0;
  int temp_var_12_1;
  temp_var_12_0 = temp_var_11_0 ^ sb_n5_0;
  temp_var_12_1 = temp_var_11_1 ^ sb_n5_1;
  sb_y6_0 = temp_var_12_0 ^ sb_n6_0;
  sb_y6_1 = temp_var_12_1 ^ sb_n6_1;
  int temp_var_13_0;
  int temp_var_13_1;
  temp_var_13_0 = sb_n0_0 ^ sb_n1_0;
  temp_var_13_1 = sb_n0_1 ^ sb_n1_1;
  int temp_var_14_0;
  int temp_var_14_1;
  temp_var_14_0 = temp_var_13_0 ^ sb_n2_0;
  temp_var_14_1 = temp_var_13_1 ^ sb_n2_1;
  int temp_var_15_0;
  int temp_var_15_1;
  temp_var_15_0 = temp_var_14_0 ^ sb_n5_0;
  temp_var_15_1 = temp_var_14_1 ^ sb_n5_1;
  int temp_var_16_0;
  int temp_var_16_1;
  temp_var_16_0 = temp_var_15_0 ^ sb_n6_0;
  temp_var_16_1 = temp_var_15_1 ^ sb_n6_1;
  sb_y7_0 = temp_var_16_0 ^ sb_n7_0;
  sb_y7_1 = temp_var_16_1 ^ sb_n7_1;
  int i256_tx0_G256_inv0_0;
  int i256_tx0_G256_inv0_1;
  int i256_tx1_G256_inv0_0;
  int i256_tx1_G256_inv0_1;
  int i256_tx2_G256_inv0_0;
  int i256_tx2_G256_inv0_1;
  int i256_tx3_G256_inv0_0;
  int i256_tx3_G256_inv0_1;
  int i256_c0_G256_inv0_0;
  int i256_c0_G256_inv0_1;
  int i256_c1_G256_inv0_0;
  int i256_c1_G256_inv0_1;
  int i256_c2_G256_inv0_0;
  int i256_c2_G256_inv0_1;
  int i256_c3_G256_inv0_0;
  int i256_c3_G256_inv0_1;
  int i256_d0_G256_inv0_0;
  int i256_d0_G256_inv0_1;
  int i256_d1_G256_inv0_0;
  int i256_d1_G256_inv0_1;
  int i256_d2_G256_inv0_0;
  int i256_d2_G256_inv0_1;
  int i256_d3_G256_inv0_0;
  int i256_d3_G256_inv0_1;
  int i256_te0_G256_inv0_0;
  int i256_te0_G256_inv0_1;
  int i256_te1_G256_inv0_0;
  int i256_te1_G256_inv0_1;
  int i256_te2_G256_inv0_0;
  int i256_te2_G256_inv0_1;
  int i256_te3_G256_inv0_0;
  int i256_te3_G256_inv0_1;
  int i256_e0_G256_inv0_0;
  int i256_e0_G256_inv0_1;
  int i256_e1_G256_inv0_0;
  int i256_e1_G256_inv0_1;
  int i256_e2_G256_inv0_0;
  int i256_e2_G256_inv0_1;
  int i256_e3_G256_inv0_0;
  int i256_e3_G256_inv0_1;
  int i256_ph0_G256_inv0_0;
  int i256_ph0_G256_inv0_1;
  int i256_ph1_G256_inv0_0;
  int i256_ph1_G256_inv0_1;
  int i256_ph2_G256_inv0_0;
  int i256_ph2_G256_inv0_1;
  int i256_ph3_G256_inv0_0;
  int i256_ph3_G256_inv0_1;
  int i256_ql0_G256_inv0_0;
  int i256_ql0_G256_inv0_1;
  int i256_ql1_G256_inv0_0;
  int i256_ql1_G256_inv0_1;
  int i256_ql2_G256_inv0_0;
  int i256_ql2_G256_inv0_1;
  int i256_ql3_G256_inv0_0;
  int i256_ql3_G256_inv0_1;
  int ss16_tx0_G16_sq_scl0_G256_inv0_0;
  int ss16_tx0_G16_sq_scl0_G256_inv0_1;
  int ss16_tx1_G16_sq_scl0_G256_inv0_0;
  int ss16_tx1_G16_sq_scl0_G256_inv0_1;
  int ss16_ph0_G16_sq_scl0_G256_inv0_0;
  int ss16_ph0_G16_sq_scl0_G256_inv0_1;
  int ss16_ph1_G16_sq_scl0_G256_inv0_0;
  int ss16_ph1_G16_sq_scl0_G256_inv0_1;
  int ss16_ql0_s1_G16_sq_scl0_G256_inv0_0;
  int ss16_ql0_s1_G16_sq_scl0_G256_inv0_1;
  int ss16_ql1_s1_G16_sq_scl0_G256_inv0_0;
  int ss16_ql1_s1_G16_sq_scl0_G256_inv0_1;
  int ss16_ql0_s2_G16_sq_scl0_G256_inv0_0;
  int ss16_ql0_s2_G16_sq_scl0_G256_inv0_1;
  int ss16_ql1_s2_G16_sq_scl0_G256_inv0_0;
  int ss16_ql1_s2_G16_sq_scl0_G256_inv0_1;
  int m16_tx0_G16_mul0_G256_inv0_0;
  int m16_tx0_G16_mul0_G256_inv0_1;
  int m16_tx1_G16_mul0_G256_inv0_0;
  int m16_tx1_G16_mul0_G256_inv0_1;
  int m16_ty0_G16_mul0_G256_inv0_0;
  int m16_ty0_G16_mul0_G256_inv0_1;
  int m16_ty1_G16_mul0_G256_inv0_0;
  int m16_ty1_G16_mul0_G256_inv0_1;
  int m16_e0_s1_G16_mul0_G256_inv0_0;
  int m16_e0_s1_G16_mul0_G256_inv0_1;
  int m16_e1_s1_G16_mul0_G256_inv0_0;
  int m16_e1_s1_G16_mul0_G256_inv0_1;
  int m16_e0_s2_G16_mul0_G256_inv0_0;
  int m16_e0_s2_G16_mul0_G256_inv0_1;
  int m16_e1_s2_G16_mul0_G256_inv0_0;
  int m16_e1_s2_G16_mul0_G256_inv0_1;
  int m16_ph0_G16_mul0_G256_inv0_0;
  int m16_ph0_G16_mul0_G256_inv0_1;
  int m16_ph1_G16_mul0_G256_inv0_0;
  int m16_ph1_G16_mul0_G256_inv0_1;
  int m16_ql0_G16_mul0_G256_inv0_0;
  int m16_ql0_G16_mul0_G256_inv0_1;
  int m16_ql1_G16_mul0_G256_inv0_0;
  int m16_ql1_G16_mul0_G256_inv0_1;
  int m4_ab_G4_mul0_G16_mul0_G256_inv0_0;
  int m4_ab_G4_mul0_G16_mul0_G256_inv0_1;
  int m4_cd_G4_mul0_G16_mul0_G256_inv0_0;
  int m4_cd_G4_mul0_G16_mul0_G256_inv0_1;
  int m4_e_G4_mul0_G16_mul0_G256_inv0_0;
  int m4_e_G4_mul0_G16_mul0_G256_inv0_1;
  int temp_var_0_G4_mul0_G16_mul0_G256_inv0_0;
  int temp_var_0_G4_mul0_G16_mul0_G256_inv0_1;
  int temp_var_1_G4_mul0_G16_mul0_G256_inv0_0;
  int temp_var_1_G4_mul0_G16_mul0_G256_inv0_1;
  int m4_ab_G4_mul1_G16_mul0_G256_inv0_0;
  int m4_ab_G4_mul1_G16_mul0_G256_inv0_1;
  int m4_cd_G4_mul1_G16_mul0_G256_inv0_0;
  int m4_cd_G4_mul1_G16_mul0_G256_inv0_1;
  int m4_e_G4_mul1_G16_mul0_G256_inv0_0;
  int m4_e_G4_mul1_G16_mul0_G256_inv0_1;
  int temp_var_0_G4_mul1_G16_mul0_G256_inv0_0;
  int temp_var_0_G4_mul1_G16_mul0_G256_inv0_1;
  int temp_var_1_G4_mul1_G16_mul0_G256_inv0_0;
  int temp_var_1_G4_mul1_G16_mul0_G256_inv0_1;
  int m4_ab_G4_mul2_G16_mul0_G256_inv0_0;
  int m4_ab_G4_mul2_G16_mul0_G256_inv0_1;
  int m4_cd_G4_mul2_G16_mul0_G256_inv0_0;
  int m4_cd_G4_mul2_G16_mul0_G256_inv0_1;
  int m4_e_G4_mul2_G16_mul0_G256_inv0_0;
  int m4_e_G4_mul2_G16_mul0_G256_inv0_1;
  int temp_var_0_G4_mul2_G16_mul0_G256_inv0_0;
  int temp_var_0_G4_mul2_G16_mul0_G256_inv0_1;
  int temp_var_1_G4_mul2_G16_mul0_G256_inv0_0;
  int temp_var_1_G4_mul2_G16_mul0_G256_inv0_1;
  int i16_tx0_G16_inv0_G256_inv0_0;
  int i16_tx0_G16_inv0_G256_inv0_1;
  int i16_tx1_G16_inv0_G256_inv0_0;
  int i16_tx1_G16_inv0_G256_inv0_1;
  int i16_c0_s1_G16_inv0_G256_inv0_0;
  int i16_c0_s1_G16_inv0_G256_inv0_1;
  int i16_c1_s1_G16_inv0_G256_inv0_0;
  int i16_c1_s1_G16_inv0_G256_inv0_1;
  int i16_c0_s2_G16_inv0_G256_inv0_0;
  int i16_c0_s2_G16_inv0_G256_inv0_1;
  int i16_c1_s2_G16_inv0_G256_inv0_0;
  int i16_c1_s2_G16_inv0_G256_inv0_1;
  int i16_d0_G16_inv0_G256_inv0_0;
  int i16_d0_G16_inv0_G256_inv0_1;
  int i16_d1_G16_inv0_G256_inv0_0;
  int i16_d1_G16_inv0_G256_inv0_1;
  int i16_te0_G16_inv0_G256_inv0_0;
  int i16_te0_G16_inv0_G256_inv0_1;
  int i16_te1_G16_inv0_G256_inv0_0;
  int i16_te1_G16_inv0_G256_inv0_1;
  int i16_e0_G16_inv0_G256_inv0_0;
  int i16_e0_G16_inv0_G256_inv0_1;
  int i16_e1_G16_inv0_G256_inv0_0;
  int i16_e1_G16_inv0_G256_inv0_1;
  int i16_ph0_G16_inv0_G256_inv0_0;
  int i16_ph0_G16_inv0_G256_inv0_1;
  int i16_ph1_G16_inv0_G256_inv0_0;
  int i16_ph1_G16_inv0_G256_inv0_1;
  int i16_ql0_G16_inv0_G256_inv0_0;
  int i16_ql0_G16_inv0_G256_inv0_1;
  int i16_ql1_G16_inv0_G256_inv0_0;
  int i16_ql1_G16_inv0_G256_inv0_1;
  int m4_ab_G4_mul3_G16_inv0_G256_inv0_0;
  int m4_ab_G4_mul3_G16_inv0_G256_inv0_1;
  int m4_cd_G4_mul3_G16_inv0_G256_inv0_0;
  int m4_cd_G4_mul3_G16_inv0_G256_inv0_1;
  int m4_e_G4_mul3_G16_inv0_G256_inv0_0;
  int m4_e_G4_mul3_G16_inv0_G256_inv0_1;
  int temp_var_0_G4_mul3_G16_inv0_G256_inv0_0;
  int temp_var_0_G4_mul3_G16_inv0_G256_inv0_1;
  int temp_var_1_G4_mul3_G16_inv0_G256_inv0_0;
  int temp_var_1_G4_mul3_G16_inv0_G256_inv0_1;
  int m4_ab_G4_mul4_G16_inv0_G256_inv0_0;
  int m4_ab_G4_mul4_G16_inv0_G256_inv0_1;
  int m4_cd_G4_mul4_G16_inv0_G256_inv0_0;
  int m4_cd_G4_mul4_G16_inv0_G256_inv0_1;
  int m4_e_G4_mul4_G16_inv0_G256_inv0_0;
  int m4_e_G4_mul4_G16_inv0_G256_inv0_1;
  int temp_var_0_G4_mul4_G16_inv0_G256_inv0_0;
  int temp_var_0_G4_mul4_G16_inv0_G256_inv0_1;
  int temp_var_1_G4_mul4_G16_inv0_G256_inv0_0;
  int temp_var_1_G4_mul4_G16_inv0_G256_inv0_1;
  int m4_ab_G4_mul5_G16_inv0_G256_inv0_0;
  int m4_ab_G4_mul5_G16_inv0_G256_inv0_1;
  int m4_cd_G4_mul5_G16_inv0_G256_inv0_0;
  int m4_cd_G4_mul5_G16_inv0_G256_inv0_1;
  int m4_e_G4_mul5_G16_inv0_G256_inv0_0;
  int m4_e_G4_mul5_G16_inv0_G256_inv0_1;
  int temp_var_0_G4_mul5_G16_inv0_G256_inv0_0;
  int temp_var_0_G4_mul5_G16_inv0_G256_inv0_1;
  int temp_var_1_G4_mul5_G16_inv0_G256_inv0_0;
  int temp_var_1_G4_mul5_G16_inv0_G256_inv0_1;
  int m16_tx0_G16_mul1_G256_inv0_0;
  int m16_tx0_G16_mul1_G256_inv0_1;
  int m16_tx1_G16_mul1_G256_inv0_0;
  int m16_tx1_G16_mul1_G256_inv0_1;
  int m16_ty0_G16_mul1_G256_inv0_0;
  int m16_ty0_G16_mul1_G256_inv0_1;
  int m16_ty1_G16_mul1_G256_inv0_0;
  int m16_ty1_G16_mul1_G256_inv0_1;
  int m16_e0_s1_G16_mul1_G256_inv0_0;
  int m16_e0_s1_G16_mul1_G256_inv0_1;
  int m16_e1_s1_G16_mul1_G256_inv0_0;
  int m16_e1_s1_G16_mul1_G256_inv0_1;
  int m16_e0_s2_G16_mul1_G256_inv0_0;
  int m16_e0_s2_G16_mul1_G256_inv0_1;
  int m16_e1_s2_G16_mul1_G256_inv0_0;
  int m16_e1_s2_G16_mul1_G256_inv0_1;
  int m16_ph0_G16_mul1_G256_inv0_0;
  int m16_ph0_G16_mul1_G256_inv0_1;
  int m16_ph1_G16_mul1_G256_inv0_0;
  int m16_ph1_G16_mul1_G256_inv0_1;
  int m16_ql0_G16_mul1_G256_inv0_0;
  int m16_ql0_G16_mul1_G256_inv0_1;
  int m16_ql1_G16_mul1_G256_inv0_0;
  int m16_ql1_G16_mul1_G256_inv0_1;
  int m4_ab_G4_mul0_G16_mul1_G256_inv0_0;
  int m4_ab_G4_mul0_G16_mul1_G256_inv0_1;
  int m4_cd_G4_mul0_G16_mul1_G256_inv0_0;
  int m4_cd_G4_mul0_G16_mul1_G256_inv0_1;
  int m4_e_G4_mul0_G16_mul1_G256_inv0_0;
  int m4_e_G4_mul0_G16_mul1_G256_inv0_1;
  int temp_var_0_G4_mul0_G16_mul1_G256_inv0_0;
  int temp_var_0_G4_mul0_G16_mul1_G256_inv0_1;
  int temp_var_1_G4_mul0_G16_mul1_G256_inv0_0;
  int temp_var_1_G4_mul0_G16_mul1_G256_inv0_1;
  int m4_ab_G4_mul1_G16_mul1_G256_inv0_0;
  int m4_ab_G4_mul1_G16_mul1_G256_inv0_1;
  int m4_cd_G4_mul1_G16_mul1_G256_inv0_0;
  int m4_cd_G4_mul1_G16_mul1_G256_inv0_1;
  int m4_e_G4_mul1_G16_mul1_G256_inv0_0;
  int m4_e_G4_mul1_G16_mul1_G256_inv0_1;
  int temp_var_0_G4_mul1_G16_mul1_G256_inv0_0;
  int temp_var_0_G4_mul1_G16_mul1_G256_inv0_1;
  int temp_var_1_G4_mul1_G16_mul1_G256_inv0_0;
  int temp_var_1_G4_mul1_G16_mul1_G256_inv0_1;
  int m4_ab_G4_mul2_G16_mul1_G256_inv0_0;
  int m4_ab_G4_mul2_G16_mul1_G256_inv0_1;
  int m4_cd_G4_mul2_G16_mul1_G256_inv0_0;
  int m4_cd_G4_mul2_G16_mul1_G256_inv0_1;
  int m4_e_G4_mul2_G16_mul1_G256_inv0_0;
  int m4_e_G4_mul2_G16_mul1_G256_inv0_1;
  int temp_var_0_G4_mul2_G16_mul1_G256_inv0_0;
  int temp_var_0_G4_mul2_G16_mul1_G256_inv0_1;
  int temp_var_1_G4_mul2_G16_mul1_G256_inv0_0;
  int temp_var_1_G4_mul2_G16_mul1_G256_inv0_1;
  int m16_tx0_G16_mul2_G256_inv0_0;
  int m16_tx0_G16_mul2_G256_inv0_1;
  int m16_tx1_G16_mul2_G256_inv0_0;
  int m16_tx1_G16_mul2_G256_inv0_1;
  int m16_ty0_G16_mul2_G256_inv0_0;
  int m16_ty0_G16_mul2_G256_inv0_1;
  int m16_ty1_G16_mul2_G256_inv0_0;
  int m16_ty1_G16_mul2_G256_inv0_1;
  int m16_e0_s1_G16_mul2_G256_inv0_0;
  int m16_e0_s1_G16_mul2_G256_inv0_1;
  int m16_e1_s1_G16_mul2_G256_inv0_0;
  int m16_e1_s1_G16_mul2_G256_inv0_1;
  int m16_e0_s2_G16_mul2_G256_inv0_0;
  int m16_e0_s2_G16_mul2_G256_inv0_1;
  int m16_e1_s2_G16_mul2_G256_inv0_0;
  int m16_e1_s2_G16_mul2_G256_inv0_1;
  int m16_ph0_G16_mul2_G256_inv0_0;
  int m16_ph0_G16_mul2_G256_inv0_1;
  int m16_ph1_G16_mul2_G256_inv0_0;
  int m16_ph1_G16_mul2_G256_inv0_1;
  int m16_ql0_G16_mul2_G256_inv0_0;
  int m16_ql0_G16_mul2_G256_inv0_1;
  int m16_ql1_G16_mul2_G256_inv0_0;
  int m16_ql1_G16_mul2_G256_inv0_1;
  int m4_ab_G4_mul0_G16_mul2_G256_inv0_0;
  int m4_ab_G4_mul0_G16_mul2_G256_inv0_1;
  int m4_cd_G4_mul0_G16_mul2_G256_inv0_0;
  int m4_cd_G4_mul0_G16_mul2_G256_inv0_1;
  int m4_e_G4_mul0_G16_mul2_G256_inv0_0;
  int m4_e_G4_mul0_G16_mul2_G256_inv0_1;
  int temp_var_0_G4_mul0_G16_mul2_G256_inv0_0;
  int temp_var_0_G4_mul0_G16_mul2_G256_inv0_1;
  int temp_var_1_G4_mul0_G16_mul2_G256_inv0_0;
  int temp_var_1_G4_mul0_G16_mul2_G256_inv0_1;
  int m4_ab_G4_mul1_G16_mul2_G256_inv0_0;
  int m4_ab_G4_mul1_G16_mul2_G256_inv0_1;
  int m4_cd_G4_mul1_G16_mul2_G256_inv0_0;
  int m4_cd_G4_mul1_G16_mul2_G256_inv0_1;
  int m4_e_G4_mul1_G16_mul2_G256_inv0_0;
  int m4_e_G4_mul1_G16_mul2_G256_inv0_1;
  int temp_var_0_G4_mul1_G16_mul2_G256_inv0_0;
  int temp_var_0_G4_mul1_G16_mul2_G256_inv0_1;
  int temp_var_1_G4_mul1_G16_mul2_G256_inv0_0;
  int temp_var_1_G4_mul1_G16_mul2_G256_inv0_1;
  int m4_ab_G4_mul2_G16_mul2_G256_inv0_0;
  int m4_ab_G4_mul2_G16_mul2_G256_inv0_1;
  int m4_cd_G4_mul2_G16_mul2_G256_inv0_0;
  int m4_cd_G4_mul2_G16_mul2_G256_inv0_1;
  int m4_e_G4_mul2_G16_mul2_G256_inv0_0;
  int m4_e_G4_mul2_G16_mul2_G256_inv0_1;
  int temp_var_0_G4_mul2_G16_mul2_G256_inv0_0;
  int temp_var_0_G4_mul2_G16_mul2_G256_inv0_1;
  int temp_var_1_G4_mul2_G16_mul2_G256_inv0_0;
  int temp_var_1_G4_mul2_G16_mul2_G256_inv0_1;
  i256_tx0_G256_inv0_0 = sb_y4_0 ^ sb_y0_0;
  i256_tx0_G256_inv0_1 = sb_y4_1 ^ sb_y0_1;
  i256_tx1_G256_inv0_0 = sb_y5_0 ^ sb_y1_0;
  i256_tx1_G256_inv0_1 = sb_y5_1 ^ sb_y1_1;
  i256_tx2_G256_inv0_0 = sb_y6_0 ^ sb_y2_0;
  i256_tx2_G256_inv0_1 = sb_y6_1 ^ sb_y2_1;
  i256_tx3_G256_inv0_0 = sb_y7_0 ^ sb_y3_0;
  i256_tx3_G256_inv0_1 = sb_y7_1 ^ sb_y3_1;
  ss16_tx0_G16_sq_scl0_G256_inv0_0 = i256_tx2_G256_inv0_0 ^ i256_tx0_G256_inv0_0;
  ss16_tx0_G16_sq_scl0_G256_inv0_1 = i256_tx2_G256_inv0_1 ^ i256_tx0_G256_inv0_1;
  ss16_tx1_G16_sq_scl0_G256_inv0_0 = i256_tx3_G256_inv0_0 ^ i256_tx1_G256_inv0_0;
  ss16_tx1_G16_sq_scl0_G256_inv0_1 = i256_tx3_G256_inv0_1 ^ i256_tx1_G256_inv0_1;
  ss16_ph1_G16_sq_scl0_G256_inv0_0 = ss16_tx0_G16_sq_scl0_G256_inv0_0;
  ss16_ph1_G16_sq_scl0_G256_inv0_1 = ss16_tx0_G16_sq_scl0_G256_inv0_1;
  ss16_ph0_G16_sq_scl0_G256_inv0_0 = ss16_tx1_G16_sq_scl0_G256_inv0_0;
  ss16_ph0_G16_sq_scl0_G256_inv0_1 = ss16_tx1_G16_sq_scl0_G256_inv0_1;
  ss16_ql1_s1_G16_sq_scl0_G256_inv0_0 = i256_tx0_G256_inv0_0;
  ss16_ql1_s1_G16_sq_scl0_G256_inv0_1 = i256_tx0_G256_inv0_1;
  ss16_ql0_s1_G16_sq_scl0_G256_inv0_0 = i256_tx1_G256_inv0_0;
  ss16_ql0_s1_G16_sq_scl0_G256_inv0_1 = i256_tx1_G256_inv0_1;
  ss16_ql1_s2_G16_sq_scl0_G256_inv0_0 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_0 ^ ss16_ql0_s1_G16_sq_scl0_G256_inv0_0;
  ss16_ql1_s2_G16_sq_scl0_G256_inv0_1 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_1 ^ ss16_ql0_s1_G16_sq_scl0_G256_inv0_1;
  ss16_ql0_s2_G16_sq_scl0_G256_inv0_0 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_0;
  ss16_ql0_s2_G16_sq_scl0_G256_inv0_1 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_1;
  i256_c3_G256_inv0_0 = ss16_ph1_G16_sq_scl0_G256_inv0_0;
  i256_c3_G256_inv0_1 = ss16_ph1_G16_sq_scl0_G256_inv0_1;
  i256_c2_G256_inv0_0 = ss16_ph0_G16_sq_scl0_G256_inv0_0;
  i256_c2_G256_inv0_1 = ss16_ph0_G16_sq_scl0_G256_inv0_1;
  i256_c1_G256_inv0_0 = ss16_ql1_s2_G16_sq_scl0_G256_inv0_0;
  i256_c1_G256_inv0_1 = ss16_ql1_s2_G16_sq_scl0_G256_inv0_1;
  i256_c0_G256_inv0_0 = ss16_ql0_s2_G16_sq_scl0_G256_inv0_0;
  i256_c0_G256_inv0_1 = ss16_ql0_s2_G16_sq_scl0_G256_inv0_1;
  m16_tx0_G16_mul0_G256_inv0_0 = sb_y6_0 ^ sb_y4_0;
  m16_tx0_G16_mul0_G256_inv0_1 = sb_y6_1 ^ sb_y4_1;
  m16_tx1_G16_mul0_G256_inv0_0 = sb_y7_0 ^ sb_y5_0;
  m16_tx1_G16_mul0_G256_inv0_1 = sb_y7_1 ^ sb_y5_1;
  m16_ty0_G16_mul0_G256_inv0_0 = sb_y2_0 ^ sb_y0_0;
  m16_ty0_G16_mul0_G256_inv0_1 = sb_y2_1 ^ sb_y0_1;
  m16_ty1_G16_mul0_G256_inv0_0 = sb_y3_0 ^ sb_y1_0;
  m16_ty1_G16_mul0_G256_inv0_1 = sb_y3_1 ^ sb_y1_1;
  m4_ab_G4_mul0_G16_mul0_G256_inv0_0 = m16_tx1_G16_mul0_G256_inv0_0 ^ m16_tx0_G16_mul0_G256_inv0_0;
  m4_ab_G4_mul0_G16_mul0_G256_inv0_1 = m16_tx1_G16_mul0_G256_inv0_1 ^ m16_tx0_G16_mul0_G256_inv0_1;
  m4_cd_G4_mul0_G16_mul0_G256_inv0_0 = m16_ty1_G16_mul0_G256_inv0_0 ^ m16_ty0_G16_mul0_G256_inv0_0;
  m4_cd_G4_mul0_G16_mul0_G256_inv0_1 = m16_ty1_G16_mul0_G256_inv0_1 ^ m16_ty0_G16_mul0_G256_inv0_1;
  HPC3(m4_ab_G4_mul0_G16_mul0_G256_inv0_0, m4_ab_G4_mul0_G16_mul0_G256_inv0_1, m4_cd_G4_mul0_G16_mul0_G256_inv0_0, m4_cd_G4_mul0_G16_mul0_G256_inv0_1, &m4_e_G4_mul0_G16_mul0_G256_inv0_0, &m4_e_G4_mul0_G16_mul0_G256_inv0_1, rand_1, rand_2);
  HPC3o(m16_tx1_G16_mul0_G256_inv0_0, m16_tx1_G16_mul0_G256_inv0_1, m16_ty1_G16_mul0_G256_inv0_0, m16_ty1_G16_mul0_G256_inv0_1, m16_e1_s1_G16_mul0_G256_inv0_0, m16_e1_s1_G16_mul0_G256_inv0_1, &temp_var_0_G4_mul0_G16_mul0_G256_inv0_0, &temp_var_0_G4_mul0_G16_mul0_G256_inv0_1, rand_3, rand_4);
  m16_e1_s1_G16_mul0_G256_inv0_0 = temp_var_0_G4_mul0_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_0;
  m16_e1_s1_G16_mul0_G256_inv0_1 = temp_var_0_G4_mul0_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_1;
  HPC3o(m16_tx0_G16_mul0_G256_inv0_0, m16_tx0_G16_mul0_G256_inv0_1, m16_ty0_G16_mul0_G256_inv0_0, m16_ty0_G16_mul0_G256_inv0_1, m16_e0_s1_G16_mul0_G256_inv0_0, m16_e0_s1_G16_mul0_G256_inv0_1, &temp_var_1_G4_mul0_G16_mul0_G256_inv0_0, &temp_var_1_G4_mul0_G16_mul0_G256_inv0_1, rand_5, rand_6);
  m16_e0_s1_G16_mul0_G256_inv0_0 = temp_var_1_G4_mul0_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_0;
  m16_e0_s1_G16_mul0_G256_inv0_1 = temp_var_1_G4_mul0_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_1;
  m16_e1_s2_G16_mul0_G256_inv0_0 = m16_e0_s1_G16_mul0_G256_inv0_0;
  m16_e1_s2_G16_mul0_G256_inv0_1 = m16_e0_s1_G16_mul0_G256_inv0_1;
  m16_e0_s2_G16_mul0_G256_inv0_0 = m16_e1_s1_G16_mul0_G256_inv0_0 ^ m16_e0_s1_G16_mul0_G256_inv0_0;
  m16_e0_s2_G16_mul0_G256_inv0_1 = m16_e1_s1_G16_mul0_G256_inv0_1 ^ m16_e0_s1_G16_mul0_G256_inv0_1;
  m4_ab_G4_mul1_G16_mul0_G256_inv0_0 = sb_y7_0 ^ sb_y6_0;
  m4_ab_G4_mul1_G16_mul0_G256_inv0_1 = sb_y7_1 ^ sb_y6_1;
  m4_cd_G4_mul1_G16_mul0_G256_inv0_0 = sb_y3_0 ^ sb_y2_0;
  m4_cd_G4_mul1_G16_mul0_G256_inv0_1 = sb_y3_1 ^ sb_y2_1;
  HPC3(m4_ab_G4_mul1_G16_mul0_G256_inv0_0, m4_ab_G4_mul1_G16_mul0_G256_inv0_1, m4_cd_G4_mul1_G16_mul0_G256_inv0_0, m4_cd_G4_mul1_G16_mul0_G256_inv0_1, &m4_e_G4_mul1_G16_mul0_G256_inv0_0, &m4_e_G4_mul1_G16_mul0_G256_inv0_1, rand_7, rand_8);
  HPC3o(sb_y7_0, sb_y7_1, sb_y3_0, sb_y3_1, m16_ph1_G16_mul0_G256_inv0_0, m16_ph1_G16_mul0_G256_inv0_1, &temp_var_0_G4_mul1_G16_mul0_G256_inv0_0, &temp_var_0_G4_mul1_G16_mul0_G256_inv0_1, rand_9, rand_10);
  m16_ph1_G16_mul0_G256_inv0_0 = temp_var_0_G4_mul1_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_0;
  m16_ph1_G16_mul0_G256_inv0_1 = temp_var_0_G4_mul1_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_1;
  HPC3o(sb_y6_0, sb_y6_1, sb_y2_0, sb_y2_1, m16_ph0_G16_mul0_G256_inv0_0, m16_ph0_G16_mul0_G256_inv0_1, &temp_var_1_G4_mul1_G16_mul0_G256_inv0_0, &temp_var_1_G4_mul1_G16_mul0_G256_inv0_1, rand_11, rand_12);
  m16_ph0_G16_mul0_G256_inv0_0 = temp_var_1_G4_mul1_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_0;
  m16_ph0_G16_mul0_G256_inv0_1 = temp_var_1_G4_mul1_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_1;
  m4_ab_G4_mul2_G16_mul0_G256_inv0_0 = sb_y5_0 ^ sb_y4_0;
  m4_ab_G4_mul2_G16_mul0_G256_inv0_1 = sb_y5_1 ^ sb_y4_1;
  m4_cd_G4_mul2_G16_mul0_G256_inv0_0 = sb_y1_0 ^ sb_y0_0;
  m4_cd_G4_mul2_G16_mul0_G256_inv0_1 = sb_y1_1 ^ sb_y0_1;
  HPC3(m4_ab_G4_mul2_G16_mul0_G256_inv0_0, m4_ab_G4_mul2_G16_mul0_G256_inv0_1, m4_cd_G4_mul2_G16_mul0_G256_inv0_0, m4_cd_G4_mul2_G16_mul0_G256_inv0_1, &m4_e_G4_mul2_G16_mul0_G256_inv0_0, &m4_e_G4_mul2_G16_mul0_G256_inv0_1, rand_13, rand_14);
  HPC3o(sb_y5_0, sb_y5_1, sb_y1_0, sb_y1_1, m16_ql1_G16_mul0_G256_inv0_0, m16_ql1_G16_mul0_G256_inv0_1, &temp_var_0_G4_mul2_G16_mul0_G256_inv0_0, &temp_var_0_G4_mul2_G16_mul0_G256_inv0_1, rand_15, rand_16);
  m16_ql1_G16_mul0_G256_inv0_0 = temp_var_0_G4_mul2_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_0;
  m16_ql1_G16_mul0_G256_inv0_1 = temp_var_0_G4_mul2_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_1;
  HPC3o(sb_y4_0, sb_y4_1, sb_y0_0, sb_y0_1, m16_ql0_G16_mul0_G256_inv0_0, m16_ql0_G16_mul0_G256_inv0_1, &temp_var_1_G4_mul2_G16_mul0_G256_inv0_0, &temp_var_1_G4_mul2_G16_mul0_G256_inv0_1, rand_17, rand_18);
  m16_ql0_G16_mul0_G256_inv0_0 = temp_var_1_G4_mul2_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_0;
  m16_ql0_G16_mul0_G256_inv0_1 = temp_var_1_G4_mul2_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_1;
  i256_d3_G256_inv0_0 = m16_ph1_G16_mul0_G256_inv0_0 ^ m16_e1_s2_G16_mul0_G256_inv0_0;
  i256_d3_G256_inv0_1 = m16_ph1_G16_mul0_G256_inv0_1 ^ m16_e1_s2_G16_mul0_G256_inv0_1;
  i256_d2_G256_inv0_0 = m16_ph0_G16_mul0_G256_inv0_0 ^ m16_e0_s2_G16_mul0_G256_inv0_0;
  i256_d2_G256_inv0_1 = m16_ph0_G16_mul0_G256_inv0_1 ^ m16_e0_s2_G16_mul0_G256_inv0_1;
  i256_d1_G256_inv0_0 = m16_ql1_G16_mul0_G256_inv0_0 ^ m16_e1_s2_G16_mul0_G256_inv0_0;
  i256_d1_G256_inv0_1 = m16_ql1_G16_mul0_G256_inv0_1 ^ m16_e1_s2_G16_mul0_G256_inv0_1;
  i256_d0_G256_inv0_0 = m16_ql0_G16_mul0_G256_inv0_0 ^ m16_e0_s2_G16_mul0_G256_inv0_0;
  i256_d0_G256_inv0_1 = m16_ql0_G16_mul0_G256_inv0_1 ^ m16_e0_s2_G16_mul0_G256_inv0_1;
  i256_te0_G256_inv0_0 = i256_c0_G256_inv0_0 ^ i256_d0_G256_inv0_0;
  i256_te0_G256_inv0_1 = i256_c0_G256_inv0_1 ^ i256_d0_G256_inv0_1;
  i256_te1_G256_inv0_0 = i256_c1_G256_inv0_0 ^ i256_d1_G256_inv0_0;
  i256_te1_G256_inv0_1 = i256_c1_G256_inv0_1 ^ i256_d1_G256_inv0_1;
  i256_te2_G256_inv0_0 = i256_c2_G256_inv0_0 ^ i256_d2_G256_inv0_0;
  i256_te2_G256_inv0_1 = i256_c2_G256_inv0_1 ^ i256_d2_G256_inv0_1;
  i256_te3_G256_inv0_0 = i256_c3_G256_inv0_0 ^ i256_d3_G256_inv0_0;
  i256_te3_G256_inv0_1 = i256_c3_G256_inv0_1 ^ i256_d3_G256_inv0_1;
  i16_tx0_G16_inv0_G256_inv0_0 = i256_te2_G256_inv0_0 ^ i256_te0_G256_inv0_0;
  i16_tx0_G16_inv0_G256_inv0_1 = i256_te2_G256_inv0_1 ^ i256_te0_G256_inv0_1;
  i16_tx1_G16_inv0_G256_inv0_0 = i256_te3_G256_inv0_0 ^ i256_te1_G256_inv0_0;
  i16_tx1_G16_inv0_G256_inv0_1 = i256_te3_G256_inv0_1 ^ i256_te1_G256_inv0_1;
  i16_c1_s1_G16_inv0_G256_inv0_0 = i16_tx0_G16_inv0_G256_inv0_0;
  i16_c1_s1_G16_inv0_G256_inv0_1 = i16_tx0_G16_inv0_G256_inv0_1;
  i16_c0_s1_G16_inv0_G256_inv0_0 = i16_tx1_G16_inv0_G256_inv0_0;
  i16_c0_s1_G16_inv0_G256_inv0_1 = i16_tx1_G16_inv0_G256_inv0_1;
  i16_c1_s2_G16_inv0_G256_inv0_0 = i16_c0_s1_G16_inv0_G256_inv0_0;
  i16_c1_s2_G16_inv0_G256_inv0_1 = i16_c0_s1_G16_inv0_G256_inv0_1;
  i16_c0_s2_G16_inv0_G256_inv0_0 = i16_c1_s1_G16_inv0_G256_inv0_0 ^ i16_c0_s1_G16_inv0_G256_inv0_0;
  i16_c0_s2_G16_inv0_G256_inv0_1 = i16_c1_s1_G16_inv0_G256_inv0_1 ^ i16_c0_s1_G16_inv0_G256_inv0_1;
  m4_ab_G4_mul3_G16_inv0_G256_inv0_0 = i256_te3_G256_inv0_0 ^ i256_te2_G256_inv0_0;
  m4_ab_G4_mul3_G16_inv0_G256_inv0_1 = i256_te3_G256_inv0_1 ^ i256_te2_G256_inv0_1;
  m4_cd_G4_mul3_G16_inv0_G256_inv0_0 = i256_te1_G256_inv0_0 ^ i256_te0_G256_inv0_0;
  m4_cd_G4_mul3_G16_inv0_G256_inv0_1 = i256_te1_G256_inv0_1 ^ i256_te0_G256_inv0_1;
  HPC3(m4_ab_G4_mul3_G16_inv0_G256_inv0_0, m4_ab_G4_mul3_G16_inv0_G256_inv0_1, m4_cd_G4_mul3_G16_inv0_G256_inv0_0, m4_cd_G4_mul3_G16_inv0_G256_inv0_1, &m4_e_G4_mul3_G16_inv0_G256_inv0_0, &m4_e_G4_mul3_G16_inv0_G256_inv0_1, rand_19, rand_20);
  HPC3o(i256_te3_G256_inv0_0, i256_te3_G256_inv0_1, i256_te1_G256_inv0_0, i256_te1_G256_inv0_1, i16_d1_G16_inv0_G256_inv0_0, i16_d1_G16_inv0_G256_inv0_1, &temp_var_0_G4_mul3_G16_inv0_G256_inv0_0, &temp_var_0_G4_mul3_G16_inv0_G256_inv0_1, rand_21, rand_22);
  i16_d1_G16_inv0_G256_inv0_0 = temp_var_0_G4_mul3_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_0;
  i16_d1_G16_inv0_G256_inv0_1 = temp_var_0_G4_mul3_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_1;
  HPC3o(i256_te2_G256_inv0_0, i256_te2_G256_inv0_1, i256_te0_G256_inv0_0, i256_te0_G256_inv0_1, i16_d0_G16_inv0_G256_inv0_0, i16_d0_G16_inv0_G256_inv0_1, &temp_var_1_G4_mul3_G16_inv0_G256_inv0_0, &temp_var_1_G4_mul3_G16_inv0_G256_inv0_1, rand_23, rand_24);
  i16_d0_G16_inv0_G256_inv0_0 = temp_var_1_G4_mul3_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_0;
  i16_d0_G16_inv0_G256_inv0_1 = temp_var_1_G4_mul3_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_1;
  i16_te0_G16_inv0_G256_inv0_0 = i16_c0_s2_G16_inv0_G256_inv0_0 ^ i16_d0_G16_inv0_G256_inv0_0;
  i16_te0_G16_inv0_G256_inv0_1 = i16_c0_s2_G16_inv0_G256_inv0_1 ^ i16_d0_G16_inv0_G256_inv0_1;
  i16_te1_G16_inv0_G256_inv0_0 = i16_c1_s2_G16_inv0_G256_inv0_0 ^ i16_d1_G16_inv0_G256_inv0_0;
  i16_te1_G16_inv0_G256_inv0_1 = i16_c1_s2_G16_inv0_G256_inv0_1 ^ i16_d1_G16_inv0_G256_inv0_1;
  i16_e1_G16_inv0_G256_inv0_0 = i16_te0_G16_inv0_G256_inv0_0;
  i16_e1_G16_inv0_G256_inv0_1 = i16_te0_G16_inv0_G256_inv0_1;
  i16_e0_G16_inv0_G256_inv0_0 = i16_te1_G16_inv0_G256_inv0_0;
  i16_e0_G16_inv0_G256_inv0_1 = i16_te1_G16_inv0_G256_inv0_1;
  m4_ab_G4_mul4_G16_inv0_G256_inv0_0 = i16_e1_G16_inv0_G256_inv0_0 ^ i16_e0_G16_inv0_G256_inv0_0;
  m4_ab_G4_mul4_G16_inv0_G256_inv0_1 = i16_e1_G16_inv0_G256_inv0_1 ^ i16_e0_G16_inv0_G256_inv0_1;
  m4_cd_G4_mul4_G16_inv0_G256_inv0_0 = i256_te1_G256_inv0_0 ^ i256_te0_G256_inv0_0;
  m4_cd_G4_mul4_G16_inv0_G256_inv0_1 = i256_te1_G256_inv0_1 ^ i256_te0_G256_inv0_1;
  HPC2(m4_ab_G4_mul4_G16_inv0_G256_inv0_0, m4_ab_G4_mul4_G16_inv0_G256_inv0_1, m4_cd_G4_mul4_G16_inv0_G256_inv0_0, m4_cd_G4_mul4_G16_inv0_G256_inv0_1, &m4_e_G4_mul4_G16_inv0_G256_inv0_0, &m4_e_G4_mul4_G16_inv0_G256_inv0_1, rand_25);
  HPC2o(i16_e1_G16_inv0_G256_inv0_0, i16_e1_G16_inv0_G256_inv0_1, i256_te1_G256_inv0_0, i256_te1_G256_inv0_1, i16_ph1_G16_inv0_G256_inv0_0, i16_ph1_G16_inv0_G256_inv0_1, &temp_var_0_G4_mul4_G16_inv0_G256_inv0_0, &temp_var_0_G4_mul4_G16_inv0_G256_inv0_1, rand_26);
  i16_ph1_G16_inv0_G256_inv0_0 = temp_var_0_G4_mul4_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_0;
  i16_ph1_G16_inv0_G256_inv0_1 = temp_var_0_G4_mul4_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_1;
  HPC2o(i16_e0_G16_inv0_G256_inv0_0, i16_e0_G16_inv0_G256_inv0_1, i256_te0_G256_inv0_0, i256_te0_G256_inv0_1, i16_ph0_G16_inv0_G256_inv0_0, i16_ph0_G16_inv0_G256_inv0_1, &temp_var_1_G4_mul4_G16_inv0_G256_inv0_0, &temp_var_1_G4_mul4_G16_inv0_G256_inv0_1, rand_27);
  i16_ph0_G16_inv0_G256_inv0_0 = temp_var_1_G4_mul4_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_0;
  i16_ph0_G16_inv0_G256_inv0_1 = temp_var_1_G4_mul4_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_1;
  m4_ab_G4_mul5_G16_inv0_G256_inv0_0 = i16_e1_G16_inv0_G256_inv0_0 ^ i16_e0_G16_inv0_G256_inv0_0;
  m4_ab_G4_mul5_G16_inv0_G256_inv0_1 = i16_e1_G16_inv0_G256_inv0_1 ^ i16_e0_G16_inv0_G256_inv0_1;
  m4_cd_G4_mul5_G16_inv0_G256_inv0_0 = i256_te3_G256_inv0_0 ^ i256_te2_G256_inv0_0;
  m4_cd_G4_mul5_G16_inv0_G256_inv0_1 = i256_te3_G256_inv0_1 ^ i256_te2_G256_inv0_1;
  HPC2(m4_ab_G4_mul5_G16_inv0_G256_inv0_0, m4_ab_G4_mul5_G16_inv0_G256_inv0_1, m4_cd_G4_mul5_G16_inv0_G256_inv0_0, m4_cd_G4_mul5_G16_inv0_G256_inv0_1, &m4_e_G4_mul5_G16_inv0_G256_inv0_0, &m4_e_G4_mul5_G16_inv0_G256_inv0_1, rand_28);
  HPC2o(i16_e1_G16_inv0_G256_inv0_0, i16_e1_G16_inv0_G256_inv0_1, i256_te3_G256_inv0_0, i256_te3_G256_inv0_1, i16_ql1_G16_inv0_G256_inv0_0, i16_ql1_G16_inv0_G256_inv0_1, &temp_var_0_G4_mul5_G16_inv0_G256_inv0_0, &temp_var_0_G4_mul5_G16_inv0_G256_inv0_1, rand_29);
  i16_ql1_G16_inv0_G256_inv0_0 = temp_var_0_G4_mul5_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_0;
  i16_ql1_G16_inv0_G256_inv0_1 = temp_var_0_G4_mul5_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_1;
  HPC2o(i16_e0_G16_inv0_G256_inv0_0, i16_e0_G16_inv0_G256_inv0_1, i256_te2_G256_inv0_0, i256_te2_G256_inv0_1, i16_ql0_G16_inv0_G256_inv0_0, i16_ql0_G16_inv0_G256_inv0_1, &temp_var_1_G4_mul5_G16_inv0_G256_inv0_0, &temp_var_1_G4_mul5_G16_inv0_G256_inv0_1, rand_30);
  i16_ql0_G16_inv0_G256_inv0_0 = temp_var_1_G4_mul5_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_0;
  i16_ql0_G16_inv0_G256_inv0_1 = temp_var_1_G4_mul5_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_1;
  i256_e3_G256_inv0_0 = i16_ph1_G16_inv0_G256_inv0_0;
  i256_e3_G256_inv0_1 = i16_ph1_G16_inv0_G256_inv0_1;
  i256_e2_G256_inv0_0 = i16_ph0_G16_inv0_G256_inv0_0;
  i256_e2_G256_inv0_1 = i16_ph0_G16_inv0_G256_inv0_1;
  i256_e1_G256_inv0_0 = i16_ql1_G16_inv0_G256_inv0_0;
  i256_e1_G256_inv0_1 = i16_ql1_G16_inv0_G256_inv0_1;
  i256_e0_G256_inv0_0 = i16_ql0_G16_inv0_G256_inv0_0;
  i256_e0_G256_inv0_1 = i16_ql0_G16_inv0_G256_inv0_1;
  m16_tx0_G16_mul1_G256_inv0_0 = i256_e2_G256_inv0_0 ^ i256_e0_G256_inv0_0;
  m16_tx0_G16_mul1_G256_inv0_1 = i256_e2_G256_inv0_1 ^ i256_e0_G256_inv0_1;
  m16_tx1_G16_mul1_G256_inv0_0 = i256_e3_G256_inv0_0 ^ i256_e1_G256_inv0_0;
  m16_tx1_G16_mul1_G256_inv0_1 = i256_e3_G256_inv0_1 ^ i256_e1_G256_inv0_1;
  m16_ty0_G16_mul1_G256_inv0_0 = sb_y2_0 ^ sb_y0_0;
  m16_ty0_G16_mul1_G256_inv0_1 = sb_y2_1 ^ sb_y0_1;
  m16_ty1_G16_mul1_G256_inv0_0 = sb_y3_0 ^ sb_y1_0;
  m16_ty1_G16_mul1_G256_inv0_1 = sb_y3_1 ^ sb_y1_1;
  m4_ab_G4_mul0_G16_mul1_G256_inv0_0 = m16_tx1_G16_mul1_G256_inv0_0 ^ m16_tx0_G16_mul1_G256_inv0_0;
  m4_ab_G4_mul0_G16_mul1_G256_inv0_1 = m16_tx1_G16_mul1_G256_inv0_1 ^ m16_tx0_G16_mul1_G256_inv0_1;
  m4_cd_G4_mul0_G16_mul1_G256_inv0_0 = m16_ty1_G16_mul1_G256_inv0_0 ^ m16_ty0_G16_mul1_G256_inv0_0;
  m4_cd_G4_mul0_G16_mul1_G256_inv0_1 = m16_ty1_G16_mul1_G256_inv0_1 ^ m16_ty0_G16_mul1_G256_inv0_1;
  HPC2(m4_ab_G4_mul0_G16_mul1_G256_inv0_0, m4_ab_G4_mul0_G16_mul1_G256_inv0_1, m4_cd_G4_mul0_G16_mul1_G256_inv0_0, m4_cd_G4_mul0_G16_mul1_G256_inv0_1, &m4_e_G4_mul0_G16_mul1_G256_inv0_0, &m4_e_G4_mul0_G16_mul1_G256_inv0_1, rand_31);
  HPC2o(m16_tx1_G16_mul1_G256_inv0_0, m16_tx1_G16_mul1_G256_inv0_1, m16_ty1_G16_mul1_G256_inv0_0, m16_ty1_G16_mul1_G256_inv0_1, m16_e1_s1_G16_mul1_G256_inv0_0, m16_e1_s1_G16_mul1_G256_inv0_1, &temp_var_0_G4_mul0_G16_mul1_G256_inv0_0, &temp_var_0_G4_mul0_G16_mul1_G256_inv0_1, rand_32);
  m16_e1_s1_G16_mul1_G256_inv0_0 = temp_var_0_G4_mul0_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_0;
  m16_e1_s1_G16_mul1_G256_inv0_1 = temp_var_0_G4_mul0_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_1;
  HPC2o(m16_tx0_G16_mul1_G256_inv0_0, m16_tx0_G16_mul1_G256_inv0_1, m16_ty0_G16_mul1_G256_inv0_0, m16_ty0_G16_mul1_G256_inv0_1, m16_e0_s1_G16_mul1_G256_inv0_0, m16_e0_s1_G16_mul1_G256_inv0_1, &temp_var_1_G4_mul0_G16_mul1_G256_inv0_0, &temp_var_1_G4_mul0_G16_mul1_G256_inv0_1, rand_33);
  m16_e0_s1_G16_mul1_G256_inv0_0 = temp_var_1_G4_mul0_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_0;
  m16_e0_s1_G16_mul1_G256_inv0_1 = temp_var_1_G4_mul0_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_1;
  m16_e1_s2_G16_mul1_G256_inv0_0 = m16_e0_s1_G16_mul1_G256_inv0_0;
  m16_e1_s2_G16_mul1_G256_inv0_1 = m16_e0_s1_G16_mul1_G256_inv0_1;
  m16_e0_s2_G16_mul1_G256_inv0_0 = m16_e1_s1_G16_mul1_G256_inv0_0 ^ m16_e0_s1_G16_mul1_G256_inv0_0;
  m16_e0_s2_G16_mul1_G256_inv0_1 = m16_e1_s1_G16_mul1_G256_inv0_1 ^ m16_e0_s1_G16_mul1_G256_inv0_1;
  m4_ab_G4_mul1_G16_mul1_G256_inv0_0 = i256_e3_G256_inv0_0 ^ i256_e2_G256_inv0_0;
  m4_ab_G4_mul1_G16_mul1_G256_inv0_1 = i256_e3_G256_inv0_1 ^ i256_e2_G256_inv0_1;
  m4_cd_G4_mul1_G16_mul1_G256_inv0_0 = sb_y3_0 ^ sb_y2_0;
  m4_cd_G4_mul1_G16_mul1_G256_inv0_1 = sb_y3_1 ^ sb_y2_1;
  HPC2(m4_ab_G4_mul1_G16_mul1_G256_inv0_0, m4_ab_G4_mul1_G16_mul1_G256_inv0_1, m4_cd_G4_mul1_G16_mul1_G256_inv0_0, m4_cd_G4_mul1_G16_mul1_G256_inv0_1, &m4_e_G4_mul1_G16_mul1_G256_inv0_0, &m4_e_G4_mul1_G16_mul1_G256_inv0_1, rand_34);
  HPC2o(i256_e3_G256_inv0_0, i256_e3_G256_inv0_1, sb_y3_0, sb_y3_1, m16_ph1_G16_mul1_G256_inv0_0, m16_ph1_G16_mul1_G256_inv0_1, &temp_var_0_G4_mul1_G16_mul1_G256_inv0_0, &temp_var_0_G4_mul1_G16_mul1_G256_inv0_1, rand_35);
  m16_ph1_G16_mul1_G256_inv0_0 = temp_var_0_G4_mul1_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_0;
  m16_ph1_G16_mul1_G256_inv0_1 = temp_var_0_G4_mul1_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_1;
  HPC2o(i256_e2_G256_inv0_0, i256_e2_G256_inv0_1, sb_y2_0, sb_y2_1, m16_ph0_G16_mul1_G256_inv0_0, m16_ph0_G16_mul1_G256_inv0_1, &temp_var_1_G4_mul1_G16_mul1_G256_inv0_0, &temp_var_1_G4_mul1_G16_mul1_G256_inv0_1, rand_36);
  m16_ph0_G16_mul1_G256_inv0_0 = temp_var_1_G4_mul1_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_0;
  m16_ph0_G16_mul1_G256_inv0_1 = temp_var_1_G4_mul1_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_1;
  m4_ab_G4_mul2_G16_mul1_G256_inv0_0 = i256_e1_G256_inv0_0 ^ i256_e0_G256_inv0_0;
  m4_ab_G4_mul2_G16_mul1_G256_inv0_1 = i256_e1_G256_inv0_1 ^ i256_e0_G256_inv0_1;
  m4_cd_G4_mul2_G16_mul1_G256_inv0_0 = sb_y1_0 ^ sb_y0_0;
  m4_cd_G4_mul2_G16_mul1_G256_inv0_1 = sb_y1_1 ^ sb_y0_1;
  HPC2(m4_ab_G4_mul2_G16_mul1_G256_inv0_0, m4_ab_G4_mul2_G16_mul1_G256_inv0_1, m4_cd_G4_mul2_G16_mul1_G256_inv0_0, m4_cd_G4_mul2_G16_mul1_G256_inv0_1, &m4_e_G4_mul2_G16_mul1_G256_inv0_0, &m4_e_G4_mul2_G16_mul1_G256_inv0_1, rand_37);
  HPC2o(i256_e1_G256_inv0_0, i256_e1_G256_inv0_1, sb_y1_0, sb_y1_1, m16_ql1_G16_mul1_G256_inv0_0, m16_ql1_G16_mul1_G256_inv0_1, &temp_var_0_G4_mul2_G16_mul1_G256_inv0_0, &temp_var_0_G4_mul2_G16_mul1_G256_inv0_1, rand_38);
  m16_ql1_G16_mul1_G256_inv0_0 = temp_var_0_G4_mul2_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_0;
  m16_ql1_G16_mul1_G256_inv0_1 = temp_var_0_G4_mul2_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_1;
  HPC2o(i256_e0_G256_inv0_0, i256_e0_G256_inv0_1, sb_y0_0, sb_y0_1, m16_ql0_G16_mul1_G256_inv0_0, m16_ql0_G16_mul1_G256_inv0_1, &temp_var_1_G4_mul2_G16_mul1_G256_inv0_0, &temp_var_1_G4_mul2_G16_mul1_G256_inv0_1, rand_39);
  m16_ql0_G16_mul1_G256_inv0_0 = temp_var_1_G4_mul2_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_0;
  m16_ql0_G16_mul1_G256_inv0_1 = temp_var_1_G4_mul2_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_1;
  i256_ph3_G256_inv0_0 = m16_ph1_G16_mul1_G256_inv0_0 ^ m16_e1_s2_G16_mul1_G256_inv0_0;
  i256_ph3_G256_inv0_1 = m16_ph1_G16_mul1_G256_inv0_1 ^ m16_e1_s2_G16_mul1_G256_inv0_1;
  i256_ph2_G256_inv0_0 = m16_ph0_G16_mul1_G256_inv0_0 ^ m16_e0_s2_G16_mul1_G256_inv0_0;
  i256_ph2_G256_inv0_1 = m16_ph0_G16_mul1_G256_inv0_1 ^ m16_e0_s2_G16_mul1_G256_inv0_1;
  i256_ph1_G256_inv0_0 = m16_ql1_G16_mul1_G256_inv0_0 ^ m16_e1_s2_G16_mul1_G256_inv0_0;
  i256_ph1_G256_inv0_1 = m16_ql1_G16_mul1_G256_inv0_1 ^ m16_e1_s2_G16_mul1_G256_inv0_1;
  i256_ph0_G256_inv0_0 = m16_ql0_G16_mul1_G256_inv0_0 ^ m16_e0_s2_G16_mul1_G256_inv0_0;
  i256_ph0_G256_inv0_1 = m16_ql0_G16_mul1_G256_inv0_1 ^ m16_e0_s2_G16_mul1_G256_inv0_1;
  m16_tx0_G16_mul2_G256_inv0_0 = i256_e2_G256_inv0_0 ^ i256_e0_G256_inv0_0;
  m16_tx0_G16_mul2_G256_inv0_1 = i256_e2_G256_inv0_1 ^ i256_e0_G256_inv0_1;
  m16_tx1_G16_mul2_G256_inv0_0 = i256_e3_G256_inv0_0 ^ i256_e1_G256_inv0_0;
  m16_tx1_G16_mul2_G256_inv0_1 = i256_e3_G256_inv0_1 ^ i256_e1_G256_inv0_1;
  m16_ty0_G16_mul2_G256_inv0_0 = sb_y6_0 ^ sb_y4_0;
  m16_ty0_G16_mul2_G256_inv0_1 = sb_y6_1 ^ sb_y4_1;
  m16_ty1_G16_mul2_G256_inv0_0 = sb_y7_0 ^ sb_y5_0;
  m16_ty1_G16_mul2_G256_inv0_1 = sb_y7_1 ^ sb_y5_1;
  m4_ab_G4_mul0_G16_mul2_G256_inv0_0 = m16_tx1_G16_mul2_G256_inv0_0 ^ m16_tx0_G16_mul2_G256_inv0_0;
  m4_ab_G4_mul0_G16_mul2_G256_inv0_1 = m16_tx1_G16_mul2_G256_inv0_1 ^ m16_tx0_G16_mul2_G256_inv0_1;
  m4_cd_G4_mul0_G16_mul2_G256_inv0_0 = m16_ty1_G16_mul2_G256_inv0_0 ^ m16_ty0_G16_mul2_G256_inv0_0;
  m4_cd_G4_mul0_G16_mul2_G256_inv0_1 = m16_ty1_G16_mul2_G256_inv0_1 ^ m16_ty0_G16_mul2_G256_inv0_1;
  HPC2(m4_ab_G4_mul0_G16_mul2_G256_inv0_0, m4_ab_G4_mul0_G16_mul2_G256_inv0_1, m4_cd_G4_mul0_G16_mul2_G256_inv0_0, m4_cd_G4_mul0_G16_mul2_G256_inv0_1, &m4_e_G4_mul0_G16_mul2_G256_inv0_0, &m4_e_G4_mul0_G16_mul2_G256_inv0_1, rand_40);
  HPC2o(m16_tx1_G16_mul2_G256_inv0_0, m16_tx1_G16_mul2_G256_inv0_1, m16_ty1_G16_mul2_G256_inv0_0, m16_ty1_G16_mul2_G256_inv0_1, m16_e1_s1_G16_mul2_G256_inv0_0, m16_e1_s1_G16_mul2_G256_inv0_1, &temp_var_0_G4_mul0_G16_mul2_G256_inv0_0, &temp_var_0_G4_mul0_G16_mul2_G256_inv0_1, rand_41);
  m16_e1_s1_G16_mul2_G256_inv0_0 = temp_var_0_G4_mul0_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_0;
  m16_e1_s1_G16_mul2_G256_inv0_1 = temp_var_0_G4_mul0_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_1;
  HPC2o(m16_tx0_G16_mul2_G256_inv0_0, m16_tx0_G16_mul2_G256_inv0_1, m16_ty0_G16_mul2_G256_inv0_0, m16_ty0_G16_mul2_G256_inv0_1, m16_e0_s1_G16_mul2_G256_inv0_0, m16_e0_s1_G16_mul2_G256_inv0_1, &temp_var_1_G4_mul0_G16_mul2_G256_inv0_0, &temp_var_1_G4_mul0_G16_mul2_G256_inv0_1, rand_42);
  m16_e0_s1_G16_mul2_G256_inv0_0 = temp_var_1_G4_mul0_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_0;
  m16_e0_s1_G16_mul2_G256_inv0_1 = temp_var_1_G4_mul0_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_1;
  m16_e1_s2_G16_mul2_G256_inv0_0 = m16_e0_s1_G16_mul2_G256_inv0_0;
  m16_e1_s2_G16_mul2_G256_inv0_1 = m16_e0_s1_G16_mul2_G256_inv0_1;
  m16_e0_s2_G16_mul2_G256_inv0_0 = m16_e1_s1_G16_mul2_G256_inv0_0 ^ m16_e0_s1_G16_mul2_G256_inv0_0;
  m16_e0_s2_G16_mul2_G256_inv0_1 = m16_e1_s1_G16_mul2_G256_inv0_1 ^ m16_e0_s1_G16_mul2_G256_inv0_1;
  m4_ab_G4_mul1_G16_mul2_G256_inv0_0 = i256_e3_G256_inv0_0 ^ i256_e2_G256_inv0_0;
  m4_ab_G4_mul1_G16_mul2_G256_inv0_1 = i256_e3_G256_inv0_1 ^ i256_e2_G256_inv0_1;
  m4_cd_G4_mul1_G16_mul2_G256_inv0_0 = sb_y7_0 ^ sb_y6_0;
  m4_cd_G4_mul1_G16_mul2_G256_inv0_1 = sb_y7_1 ^ sb_y6_1;
  HPC2(m4_ab_G4_mul1_G16_mul2_G256_inv0_0, m4_ab_G4_mul1_G16_mul2_G256_inv0_1, m4_cd_G4_mul1_G16_mul2_G256_inv0_0, m4_cd_G4_mul1_G16_mul2_G256_inv0_1, &m4_e_G4_mul1_G16_mul2_G256_inv0_0, &m4_e_G4_mul1_G16_mul2_G256_inv0_1, rand_43);
  HPC2o(i256_e3_G256_inv0_0, i256_e3_G256_inv0_1, sb_y7_0, sb_y7_1, m16_ph1_G16_mul2_G256_inv0_0, m16_ph1_G16_mul2_G256_inv0_1, &temp_var_0_G4_mul1_G16_mul2_G256_inv0_0, &temp_var_0_G4_mul1_G16_mul2_G256_inv0_1, rand_44);
  m16_ph1_G16_mul2_G256_inv0_0 = temp_var_0_G4_mul1_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_0;
  m16_ph1_G16_mul2_G256_inv0_1 = temp_var_0_G4_mul1_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_1;
  HPC2o(i256_e2_G256_inv0_0, i256_e2_G256_inv0_1, sb_y6_0, sb_y6_1, m16_ph0_G16_mul2_G256_inv0_0, m16_ph0_G16_mul2_G256_inv0_1, &temp_var_1_G4_mul1_G16_mul2_G256_inv0_0, &temp_var_1_G4_mul1_G16_mul2_G256_inv0_1, rand_45);
  m16_ph0_G16_mul2_G256_inv0_0 = temp_var_1_G4_mul1_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_0;
  m16_ph0_G16_mul2_G256_inv0_1 = temp_var_1_G4_mul1_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_1;
  m4_ab_G4_mul2_G16_mul2_G256_inv0_0 = i256_e1_G256_inv0_0 ^ i256_e0_G256_inv0_0;
  m4_ab_G4_mul2_G16_mul2_G256_inv0_1 = i256_e1_G256_inv0_1 ^ i256_e0_G256_inv0_1;
  m4_cd_G4_mul2_G16_mul2_G256_inv0_0 = sb_y5_0 ^ sb_y4_0;
  m4_cd_G4_mul2_G16_mul2_G256_inv0_1 = sb_y5_1 ^ sb_y4_1;
  HPC2(m4_ab_G4_mul2_G16_mul2_G256_inv0_0, m4_ab_G4_mul2_G16_mul2_G256_inv0_1, m4_cd_G4_mul2_G16_mul2_G256_inv0_0, m4_cd_G4_mul2_G16_mul2_G256_inv0_1, &m4_e_G4_mul2_G16_mul2_G256_inv0_0, &m4_e_G4_mul2_G16_mul2_G256_inv0_1, rand_46);
  HPC2o(i256_e1_G256_inv0_0, i256_e1_G256_inv0_1, sb_y5_0, sb_y5_1, m16_ql1_G16_mul2_G256_inv0_0, m16_ql1_G16_mul2_G256_inv0_1, &temp_var_0_G4_mul2_G16_mul2_G256_inv0_0, &temp_var_0_G4_mul2_G16_mul2_G256_inv0_1, rand_47);
  m16_ql1_G16_mul2_G256_inv0_0 = temp_var_0_G4_mul2_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_0;
  m16_ql1_G16_mul2_G256_inv0_1 = temp_var_0_G4_mul2_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_1;
  HPC2o(i256_e0_G256_inv0_0, i256_e0_G256_inv0_1, sb_y4_0, sb_y4_1, m16_ql0_G16_mul2_G256_inv0_0, m16_ql0_G16_mul2_G256_inv0_1, &temp_var_1_G4_mul2_G16_mul2_G256_inv0_0, &temp_var_1_G4_mul2_G16_mul2_G256_inv0_1, rand_48);
  m16_ql0_G16_mul2_G256_inv0_0 = temp_var_1_G4_mul2_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_0;
  m16_ql0_G16_mul2_G256_inv0_1 = temp_var_1_G4_mul2_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_1;
  i256_ql3_G256_inv0_0 = m16_ph1_G16_mul2_G256_inv0_0 ^ m16_e1_s2_G16_mul2_G256_inv0_0;
  i256_ql3_G256_inv0_1 = m16_ph1_G16_mul2_G256_inv0_1 ^ m16_e1_s2_G16_mul2_G256_inv0_1;
  i256_ql2_G256_inv0_0 = m16_ph0_G16_mul2_G256_inv0_0 ^ m16_e0_s2_G16_mul2_G256_inv0_0;
  i256_ql2_G256_inv0_1 = m16_ph0_G16_mul2_G256_inv0_1 ^ m16_e0_s2_G16_mul2_G256_inv0_1;
  i256_ql1_G256_inv0_0 = m16_ql1_G16_mul2_G256_inv0_0 ^ m16_e1_s2_G16_mul2_G256_inv0_0;
  i256_ql1_G256_inv0_1 = m16_ql1_G16_mul2_G256_inv0_1 ^ m16_e1_s2_G16_mul2_G256_inv0_1;
  i256_ql0_G256_inv0_0 = m16_ql0_G16_mul2_G256_inv0_0 ^ m16_e0_s2_G16_mul2_G256_inv0_0;
  i256_ql0_G256_inv0_1 = m16_ql0_G16_mul2_G256_inv0_1 ^ m16_e0_s2_G16_mul2_G256_inv0_1;
  sb_i7_0 = i256_ph3_G256_inv0_0;
  sb_i7_1 = i256_ph3_G256_inv0_1;
  sb_i6_0 = i256_ph2_G256_inv0_0;
  sb_i6_1 = i256_ph2_G256_inv0_1;
  sb_i5_0 = i256_ph1_G256_inv0_0;
  sb_i5_1 = i256_ph1_G256_inv0_1;
  sb_i4_0 = i256_ph0_G256_inv0_0;
  sb_i4_1 = i256_ph0_G256_inv0_1;
  sb_i3_0 = i256_ql3_G256_inv0_0;
  sb_i3_1 = i256_ql3_G256_inv0_1;
  sb_i2_0 = i256_ql2_G256_inv0_0;
  sb_i2_1 = i256_ql2_G256_inv0_1;
  sb_i1_0 = i256_ql1_G256_inv0_0;
  sb_i1_1 = i256_ql1_G256_inv0_1;
  sb_i0_0 = i256_ql0_G256_inv0_0;
  sb_i0_1 = i256_ql0_G256_inv0_1;
  int temp_var_17_0;
  int temp_var_17_1;
  temp_var_17_0 = sb_i1_0 ^ sb_i4_0;
  temp_var_17_1 = sb_i1_1 ^ sb_i4_1;
  fy0_0 = temp_var_17_0 ^ sb_i6_0;
  fy0_1 = temp_var_17_1 ^ sb_i6_1;
  int temp_var_18_0;
  int temp_var_18_1;
  temp_var_18_0 = sb_i1_0 ^ sb_i4_0;
  temp_var_18_1 = sb_i1_1 ^ sb_i4_1;
  fy1_0 = temp_var_18_0 ^ sb_i5_0;
  fy1_1 = temp_var_18_1 ^ sb_i5_1;
  int temp_var_19_0;
  int temp_var_19_1;
  temp_var_19_0 = sb_i0_0 ^ sb_i2_0;
  temp_var_19_1 = sb_i0_1 ^ sb_i2_1;
  int temp_var_20_0;
  int temp_var_20_1;
  temp_var_20_0 = temp_var_19_0 ^ sb_i3_0;
  temp_var_20_1 = temp_var_19_1 ^ sb_i3_1;
  int temp_var_21_0;
  int temp_var_21_1;
  temp_var_21_0 = temp_var_20_0 ^ sb_i5_0;
  temp_var_21_1 = temp_var_20_1 ^ sb_i5_1;
  fy2_0 = temp_var_21_0 ^ sb_i6_0;
  fy2_1 = temp_var_21_1 ^ sb_i6_1;
  int temp_var_22_0;
  int temp_var_22_1;
  temp_var_22_0 = sb_i3_0 ^ sb_i4_0;
  temp_var_22_1 = sb_i3_1 ^ sb_i4_1;
  int temp_var_23_0;
  int temp_var_23_1;
  temp_var_23_0 = temp_var_22_0 ^ sb_i5_0;
  temp_var_23_1 = temp_var_22_1 ^ sb_i5_1;
  int temp_var_24_0;
  int temp_var_24_1;
  temp_var_24_0 = temp_var_23_0 ^ sb_i6_0;
  temp_var_24_1 = temp_var_23_1 ^ sb_i6_1;
  fy3_0 = temp_var_24_0 ^ sb_i7_0;
  fy3_1 = temp_var_24_1 ^ sb_i7_1;
  int temp_var_25_0;
  int temp_var_25_1;
  temp_var_25_0 = sb_i3_0 ^ sb_i5_0;
  temp_var_25_1 = sb_i3_1 ^ sb_i5_1;
  fy4_0 = temp_var_25_0 ^ sb_i7_0;
  fy4_1 = temp_var_25_1 ^ sb_i7_1;
  fy5_0 = sb_i0_0 ^ sb_i6_0;
  fy5_1 = sb_i0_1 ^ sb_i6_1;
  fy6_0 = sb_i3_0 ^ sb_i7_0;
  fy6_1 = sb_i3_1 ^ sb_i7_1;
  fy7_0 = sb_i3_0 ^ sb_i5_0;
  fy7_1 = sb_i3_1 ^ sb_i5_1;
  *sb_o0_0 = fy0_0;
  *sb_o0_1 = !fy0_1;
  *sb_o1_0 = fy1_0;
  *sb_o1_1 = !fy1_1;
  *sb_o2_0 = fy2_0 ^ dec_0;
  *sb_o2_1 = fy2_1 ^ dec_0;
  *sb_o3_0 = fy3_0 ^ dec_0;
  *sb_o3_1 = fy3_1 ^ dec_0;
  *sb_o4_0 = fy4_0 ^ dec_0;
  *sb_o4_1 = fy4_1 ^ dec_0;
  *sb_o5_0 = fy5_0;
  *sb_o5_1 = !fy5_1;
  *sb_o6_0 = fy6_0;
  *sb_o6_1 = !fy6_1;
  *sb_o7_0 = fy7_0 ^ dec_0;
  *sb_o7_1 = fy7_1 ^ dec_0;
}



// ==========================================
// 4. TESTBENCH LOGIC
// ==========================================

int main() {
    int total_tests = 256;
    int passed = 0;
    int failed = 0;
    
    printf("\n");
    printf("════════════════════════════════════════════════════════════════\n");
    printf("MASKED S-BOX EQUIVALENCE VERIFICATION TESTBENCH\n");
    printf("════════════════════════════════════════════════════════════════\n\n");
    
    printf("Testing: Unmasked vs 1st-Order Boolean Masked\n");
    printf("Method: For each input x (0-255) and random share r:\n");
    printf("  1. Split input: x0 = r (random), x1 = r ^ x\n");
    printf("  2. Compute golden output: y = sbox_golden(x)\n");
    printf("  3. Compute masked output: y0, y1 = sbox_masked(x0, x1, ...)\n");
    printf("  4. Verify: y0 ^ y1 = sbox_golden(x)\n\n");
    
    printf("Running %d x 256 = %d test cases...\n", total_tests, total_tests * 256);
    printf("(For each input value, testing with 256 different random shares)\n");
    printf("────────────────────────────────────────────────────────────────\n\n");
    
    int grand_total = 0;
    int grand_passed = 0;
    int grand_failed = 0;
    
    for(int input_val = 0; input_val < total_tests; input_val++) {
        // Extract 8 bits from input
        int in_bits[8];
        for(int b = 0; b < 8; b++) {
            in_bits[b] = (input_val >> b) & 1;
        }
        
        // Test with multiple random shares for this input
        for(int random_share = 0; random_share < 256; random_share++) {
            grand_total++;
            
            // Extract 8 bits from random share
            int rand_bits[8];
            for(int b = 0; b < 8; b++) {
                rand_bits[b] = (random_share >> b) & 1;
            }
            
            // Compute share0 and share1 for each input bit
            // share0 = random value
            // share1 = share0 ^ input
            int share0[8], share1[8];
            for(int b = 0; b < 8; b++) {
                share0[b] = rand_bits[b];
                share1[b] = share0[b] ^ in_bits[b];
            }
            
            // =====================================
            // Run GOLDEN (unmasked) implementation
            // =====================================
            int g_out[8] = {0};
            sbox_golden(in_bits[0], in_bits[1], in_bits[2], in_bits[3],
                        in_bits[4], in_bits[5], in_bits[6], in_bits[7],
                        0,  // dec_1 = 0
                        &g_out[0], &g_out[1], &g_out[2], &g_out[3],
                        &g_out[4], &g_out[5], &g_out[6], &g_out[7]);
            
            // =====================================
            // Run MASKED implementation
            // Input shares: share0 and share1
            // All randoms set to 0 for deterministic testing
            // =====================================
            int m_out_sh0[8] = {0};
            int m_out_sh1[8] = {0};
            
            sbox_masked(
                share0[0], share1[0],  // i0_0, i0_1
                share0[1], share1[1],  // i1_0, i1_1
                share0[2], share1[2],  // i2_0, i2_1
                share0[3], share1[3],  // i3_0, i3_1
                share0[4], share1[4],  // i4_0, i4_1
                share0[5], share1[5],  // i5_0, i5_1
                share0[6], share1[6],  // i6_0, i6_1
                share0[7], share1[7],  // i7_0, i7_1
                1,  // dec_1
                &m_out_sh0[0], &m_out_sh1[0],
                &m_out_sh0[1], &m_out_sh1[1],
                &m_out_sh0[2], &m_out_sh1[2],
                &m_out_sh0[3], &m_out_sh1[3],
                &m_out_sh0[4], &m_out_sh1[4],
                &m_out_sh0[5], &m_out_sh1[5],
                &m_out_sh0[6], &m_out_sh1[6],
                &m_out_sh0[7], &m_out_sh1[7],
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1  // all randoms = 0
            );
        
        // =====================================
        // Combine masked shares and verify
        // =====================================
        int mismatch = 0;
        for(int bit = 0; bit < 8; bit++) {
            int combined = (m_out_sh0[bit] ^ m_out_sh1[bit]) & 1;
            int golden = g_out[bit] & 1;
            
            if(combined != golden) {
                mismatch = 1;
                break;
            }
        }
        
        // =====================================
        // Report results
        // =====================================
        if(mismatch) {
            grand_failed++;
            printf("[FAIL] Input: 0x%02X, Random: 0x%02X | ", input_val, random_share);
            printf("Expected: ");
            for(int b = 7; b >= 0; b--) printf("%d", g_out[b] & 1);
            printf(" | ");
            printf("Got: ");
            for(int b = 7; b >= 0; b--) printf("%d", (m_out_sh0[b] ^ m_out_sh1[b]) & 1);
            printf("\n");
        } else {
            grand_passed++;
        }
    }
    }
    
    // =====================================
    // Summary
    // =====================================
    printf("\n────────────────────────────────────────────────────────────────\n");
    printf("RESULTS:\n");
    printf("  Total Tests: %d (256 inputs x 256 random shares)\n", grand_total);
    printf("  Passed: %d\n", grand_passed);
    printf("  Failed: %d\n", grand_failed);
    printf("  Success Rate: %.2f%%\n", (100.0 * grand_passed / grand_total));
    printf("════════════════════════════════════════════════════════════════\n\n");
    
    if(grand_failed == 0) {
        printf("✓ EQUIVALENCE VERIFIED: All %d test cases passed!\n\n", grand_total);
        return 0;
    } else {
        printf("✗ EQUIVALENCE FAILED: %d mismatches detected!\n\n", grand_failed);
        return 1;
    }
}
