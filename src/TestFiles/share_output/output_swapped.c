// === GADGET DEFINITIONS (hpc3o, hpc2o, etc.) ===

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
void sbox(_Bool X0_0, _Bool X0_1, _Bool X1_0, _Bool X1_1, _Bool X2_0, _Bool X2_1, _Bool X3_0, _Bool X3_1, _Bool X4_0, _Bool X4_1, _Bool X5_0, _Bool X5_1, _Bool X6_0, _Bool X6_1, _Bool X7_0, _Bool X7_1, _Bool *Y0_0, _Bool *Y0_1, _Bool *Y1_0, _Bool *Y1_1, _Bool *Y2_0, _Bool *Y2_1, _Bool *Y3_0, _Bool *Y3_1, _Bool *Y4_0, _Bool *Y4_1, _Bool *Y5_0, _Bool *Y5_1, _Bool *Y6_0, _Bool *Y6_1, _Bool *Y7_0, _Bool *Y7_1, _Bool dec_1, int rand_18, int rand_19, int rand_30, int rand_59, int rand_39, int rand_47, int rand_2, int rand_12, int rand_1, int rand_20, int rand_29, int rand_49, int rand_14, int rand_27, int rand_33, int rand_67, int rand_31, int rand_43, int rand_9, int rand_16, int rand_3, int rand_6, int rand_13, int rand_5, int rand_10, int rand_15, int rand_7, int rand_55, int rand_4, int rand_41, int rand_45, int rand_61, int rand_63, int rand_8, int rand_35, int rand_57, int rand_23, int rand_21, int rand_51, int rand_17, int rand_26, int rand_37, int rand_25, int rand_65, int rand_11, int rand_53)
{
  _Bool T1_0;
  _Bool T1_1;
  _Bool T2_0;
  _Bool T2_1;
  _Bool T3_0;
  _Bool T3_1;
  _Bool T4_0;
  _Bool T4_1;
  _Bool T5_0;
  _Bool T5_1;
  _Bool T6_0;
  _Bool T6_1;
  _Bool T7_0;
  _Bool T7_1;
  _Bool T8_0;
  _Bool T8_1;
  _Bool T9_0;
  _Bool T9_1;
  _Bool T10_0;
  _Bool T10_1;
  _Bool T11_0;
  _Bool T11_1;
  _Bool T12_0;
  _Bool T12_1;
  _Bool T13_0;
  _Bool T13_1;
  _Bool T14_0;
  _Bool T14_1;
  _Bool T15_0;
  _Bool T15_1;
  _Bool T16_0;
  _Bool T16_1;
  _Bool T17_0;
  _Bool T17_1;
  _Bool T18_0;
  _Bool T18_1;
  _Bool T19_0;
  _Bool T19_1;
  _Bool T20_0;
  _Bool T20_1;
  _Bool T21_0;
  _Bool T21_1;
  _Bool T22_0;
  _Bool T22_1;
  _Bool T23_0;
  _Bool T23_1;
  _Bool T24_0;
  _Bool T24_1;
  _Bool T25_0;
  _Bool T25_1;
  _Bool T26_0;
  _Bool T26_1;
  _Bool T27_0;
  _Bool T27_1;
  _Bool M1_0;
  _Bool M1_1;
  _Bool M2_0;
  _Bool M2_1;
  _Bool M3_0;
  _Bool M3_1;
  _Bool M4_0;
  _Bool M4_1;
  _Bool M5_0;
  _Bool M5_1;
  _Bool M6_0;
  _Bool M6_1;
  _Bool M7_0;
  _Bool M7_1;
  _Bool M8_0;
  _Bool M8_1;
  _Bool M9_0;
  _Bool M9_1;
  _Bool M10_0;
  _Bool M10_1;
  _Bool M11_0;
  _Bool M11_1;
  _Bool M12_0;
  _Bool M12_1;
  _Bool M13_0;
  _Bool M13_1;
  _Bool M14_0;
  _Bool M14_1;
  _Bool M15_0;
  _Bool M15_1;
  _Bool M16_0;
  _Bool M16_1;
  _Bool M17_0;
  _Bool M17_1;
  _Bool M18_0;
  _Bool M18_1;
  _Bool M19_0;
  _Bool M19_1;
  _Bool M20_0;
  _Bool M20_1;
  _Bool M21_0;
  _Bool M21_1;
  _Bool M22_0;
  _Bool M22_1;
  _Bool M23_0;
  _Bool M23_1;
  _Bool M24_0;
  _Bool M24_1;
  _Bool M25_0;
  _Bool M25_1;
  _Bool M26_0;
  _Bool M26_1;
  _Bool M27_0;
  _Bool M27_1;
  _Bool M28_0;
  _Bool M28_1;
  _Bool M29_0;
  _Bool M29_1;
  _Bool M30_0;
  _Bool M30_1;
  _Bool M31_0;
  _Bool M31_1;
  _Bool M32_0;
  _Bool M32_1;
  _Bool M33_0;
  _Bool M33_1;
  _Bool M34_0;
  _Bool M34_1;
  _Bool M35_0;
  _Bool M35_1;
  _Bool M36_0;
  _Bool M36_1;
  _Bool M37_0;
  _Bool M37_1;
  _Bool M38_0;
  _Bool M38_1;
  _Bool M39_0;
  _Bool M39_1;
  _Bool M40_0;
  _Bool M40_1;
  _Bool M41_0;
  _Bool M41_1;
  _Bool M42_0;
  _Bool M42_1;
  _Bool M43_0;
  _Bool M43_1;
  _Bool M44_0;
  _Bool M44_1;
  _Bool M45_0;
  _Bool M45_1;
  _Bool M46_0;
  _Bool M46_1;
  _Bool M47_0;
  _Bool M47_1;
  _Bool M48_0;
  _Bool M48_1;
  _Bool M49_0;
  _Bool M49_1;
  _Bool M50_0;
  _Bool M50_1;
  _Bool M51_0;
  _Bool M51_1;
  _Bool M52_0;
  _Bool M52_1;
  _Bool M53_0;
  _Bool M53_1;
  _Bool M54_0;
  _Bool M54_1;
  _Bool M55_0;
  _Bool M55_1;
  _Bool M56_0;
  _Bool M56_1;
  _Bool M57_0;
  _Bool M57_1;
  _Bool M58_0;
  _Bool M58_1;
  _Bool M59_0;
  _Bool M59_1;
  _Bool M60_0;
  _Bool M60_1;
  _Bool M61_0;
  _Bool M61_1;
  _Bool M62_0;
  _Bool M62_1;
  _Bool M63_0;
  _Bool M63_1;
  _Bool L0_0;
  _Bool L0_1;
  _Bool L1_0;
  _Bool L1_1;
  _Bool L2_0;
  _Bool L2_1;
  _Bool L3_0;
  _Bool L3_1;
  _Bool L4_0;
  _Bool L4_1;
  _Bool L5_0;
  _Bool L5_1;
  _Bool L6_0;
  _Bool L6_1;
  _Bool L7_0;
  _Bool L7_1;
  _Bool L8_0;
  _Bool L8_1;
  _Bool L9_0;
  _Bool L9_1;
  _Bool L10_0;
  _Bool L10_1;
  _Bool L11_0;
  _Bool L11_1;
  _Bool L12_0;
  _Bool L12_1;
  _Bool L13_0;
  _Bool L13_1;
  _Bool L14_0;
  _Bool L14_1;
  _Bool L15_0;
  _Bool L15_1;
  _Bool L16_0;
  _Bool L16_1;
  _Bool L17_0;
  _Bool L17_1;
  _Bool L18_0;
  _Bool L18_1;
  _Bool L19_0;
  _Bool L19_1;
  _Bool L20_0;
  _Bool L20_1;
  _Bool L21_0;
  _Bool L21_1;
  _Bool L22_0;
  _Bool L22_1;
  _Bool L23_0;
  _Bool L23_1;
  _Bool L24_0;
  _Bool L24_1;
  _Bool L25_0;
  _Bool L25_1;
  _Bool L26_0;
  _Bool L26_1;
  _Bool L27_0;
  _Bool L27_1;
  _Bool L28_0;
  _Bool L28_1;
  _Bool L29_0;
  _Bool L29_1;
  T1_0 = X0_0 ^ X3_0;
  T1_1 = X0_1 ^ X3_1;
  T2_0 = X0_0 ^ X5_0;
  T2_1 = X0_1 ^ X5_1;
  T3_0 = X0_0 ^ X6_0;
  T3_1 = X0_1 ^ X6_1;
  T4_0 = X3_0 ^ X5_0;
  T4_1 = X3_1 ^ X5_1;
  T5_0 = X4_0 ^ X6_0;
  T5_1 = X4_1 ^ X6_1;
  T6_0 = T1_0 ^ T5_0;
  T6_1 = T1_1 ^ T5_1;
  T7_0 = X1_0 ^ X2_0;
  T7_1 = X1_1 ^ X2_1;
  T8_0 = X7_0 ^ T6_0;
  T8_1 = X7_1 ^ T6_1;
  T9_0 = X7_0 ^ T7_0;
  T9_1 = X7_1 ^ T7_1;
  T10_0 = T6_0 ^ T7_0;
  T10_1 = T6_1 ^ T7_1;
  T11_0 = X1_0 ^ X5_0;
  T11_1 = X1_1 ^ X5_1;
  T12_0 = X2_0 ^ X5_0;
  T12_1 = X2_1 ^ X5_1;
  T13_0 = T3_0 ^ T4_0;
  T13_1 = T3_1 ^ T4_1;
  T14_0 = T6_0 ^ T11_0;
  T14_1 = T6_1 ^ T11_1;
  T15_0 = T5_0 ^ T11_0;
  T15_1 = T5_1 ^ T11_1;
  T16_0 = T5_0 ^ T12_0;
  T16_1 = T5_1 ^ T12_1;
  T17_0 = T9_0 ^ T16_0;
  T17_1 = T9_1 ^ T16_1;
  T18_0 = X3_0 ^ X7_0;
  T18_1 = X3_1 ^ X7_1;
  T19_0 = T7_0 ^ T18_0;
  T19_1 = T7_1 ^ T18_1;
  T20_0 = T1_0 ^ T19_0;
  T20_1 = T1_1 ^ T19_1;
  T21_0 = X6_0 ^ X7_0;
  T21_1 = X6_1 ^ X7_1;
  T22_0 = T7_0 ^ T21_0;
  T22_1 = T7_1 ^ T21_1;
  T23_0 = T2_0 ^ T22_0;
  T23_1 = T2_1 ^ T22_1;
  T24_0 = T2_0 ^ T10_0;
  T24_1 = T2_1 ^ T10_1;
  T25_0 = T20_0 ^ T17_0;
  T25_1 = T20_1 ^ T17_1;
  T26_0 = T3_0 ^ T16_0;
  T26_1 = T3_1 ^ T16_1;
  T27_0 = T1_0 ^ T12_0;
  T27_1 = T1_1 ^ T12_1;
  HPC3(T13_0, T13_1, T6_0, T6_1, &M1_0, &M1_1, rand_1, rand_2);
  HPC3(T23_0, T23_1, T8_0, T8_1, &M2_0, &M2_1, rand_3, rand_4);
  M3_0 = T14_0 ^ M1_0;
  M3_1 = T14_1 ^ M1_1;
  HPC3(T19_0, T19_1, X7_0, X7_1, &M4_0, &M4_1, rand_5, rand_6);
  M5_0 = M4_0 ^ M1_0;
  M5_1 = M4_1 ^ M1_1;
  HPC3(T3_0, T3_1, T16_0, T16_1, &M6_0, &M6_1, rand_7, rand_8);
  HPC3(T22_0, T22_1, T9_0, T9_1, &M7_0, &M7_1, rand_9, rand_10);
  M8_0 = T26_0 ^ M6_0;
  M8_1 = T26_1 ^ M6_1;
  HPC3o(T20_0, T20_1, T17_0, T17_1, M10_0, M10_1, &M9_0, &M9_1, rand_11, rand_12);
  M10_0 = M9_0 ^ M6_0;
  M10_1 = M9_1 ^ M6_1;
  HPC3(T1_0, T1_1, T15_0, T15_1, &M11_0, &M11_1, rand_13, rand_14);
  HPC3o(T4_0, T4_1, T27_0, T27_1, M13_0, M13_1, &M12_0, &M12_1, rand_15, rand_16);
  M13_0 = M12_0 ^ M11_0;
  M13_1 = M12_1 ^ M11_1;
  HPC3o(T2_0, T2_1, T10_0, T10_1, M15_0, M15_1, &M14_0, &M14_1, rand_17, rand_18);
  M15_0 = M14_0 ^ M11_0;
  M15_1 = M14_1 ^ M11_1;
  M16_0 = M3_0 ^ M2_0;
  M16_1 = M3_1 ^ M2_1;
  M17_0 = M5_0 ^ T24_0;
  M17_1 = M5_1 ^ T24_1;
  M18_0 = M8_0 ^ M7_0;
  M18_1 = M8_1 ^ M7_1;
  M19_0 = M10_0 ^ M15_0;
  M19_1 = M10_1 ^ M15_1;
  M20_0 = M16_0 ^ M13_0;
  M20_1 = M16_1 ^ M13_1;
  M21_0 = M17_0 ^ M15_0;
  M21_1 = M17_1 ^ M15_1;
  M22_0 = M18_0 ^ M13_0;
  M22_1 = M18_1 ^ M13_1;
  M23_0 = M19_0 ^ T25_0;
  M23_1 = M19_1 ^ T25_1;
  M24_0 = M22_0 ^ M23_0;
  M24_1 = M22_1 ^ M23_1;
  HPC3(M22_0, M22_1, M20_0, M20_1, &M25_0, &M25_1, rand_19, rand_20);
  M26_0 = M21_0 ^ M25_0;
  M26_1 = M21_1 ^ M25_1;
  M27_0 = M20_0 ^ M21_0;
  M27_1 = M20_1 ^ M21_1;
  M28_0 = M23_0 ^ M25_0;
  M28_1 = M23_1 ^ M25_1;
  HPC2o(M28_0, M28_1, M27_0, M27_1, M37_0, M37_1, &M29_0, &M29_1, rand_21);
  HPC2o(M26_0, M26_1, M24_0, M24_1, M39_0, M39_1, &M30_0, &M30_1, rand_23);
  HPC3(M20_0, M20_1, M23_0, M23_1, &M31_0, &M31_1, rand_25, rand_26);
  HPC2o(M31_0, M31_1, M27_0, M27_1, M38_0, M38_1, &M32_0, &M32_1, rand_27);
  M33_0 = M27_0 ^ M25_0;
  M33_1 = M27_1 ^ M25_1;
  HPC3(M21_0, M21_1, M22_0, M22_1, &M34_0, &M34_1, rand_29, rand_30);
  HPC2o(M34_0, M34_1, M24_0, M24_1, M40_0, M40_1, &M35_0, &M35_1, rand_31);
  M36_0 = M24_0 ^ M25_0;
  M36_1 = M24_1 ^ M25_1;
  M37_0 = M21_0 ^ M29_0;
  M37_1 = M21_1 ^ M29_1;
  M38_0 = M32_0 ^ M33_0;
  M38_1 = M32_1 ^ M33_1;
  M39_0 = M23_0 ^ M30_0;
  M39_1 = M23_1 ^ M30_1;
  M40_0 = M35_0 ^ M36_0;
  M40_1 = M35_1 ^ M36_1;
  M41_0 = M38_0 ^ M40_0;
  M41_1 = M38_1 ^ M40_1;
  M42_0 = M37_0 ^ M39_0;
  M42_1 = M37_1 ^ M39_1;
  M43_0 = M37_0 ^ M38_0;
  M43_1 = M37_1 ^ M38_1;
  M44_0 = M39_0 ^ M40_0;
  M44_1 = M39_1 ^ M40_1;
  M45_0 = M42_0 ^ M41_0;
  M45_1 = M42_1 ^ M41_1;
  HPC2(M44_0, M44_1, T6_0, T6_1, &M46_0, &M46_1, rand_33);
  HPC2(M40_0, M40_1, T8_0, T8_1, &M47_0, &M47_1, rand_35);
  HPC2(M39_0, M39_1, X7_0, X7_1, &M48_0, &M48_1, rand_37);
  HPC2o(M43_0, M43_1, T16_0, T16_1, L5_0, L5_1, &M49_0, &M49_1, rand_39);
  HPC2(M38_0, M38_1, T9_0, T9_1, &M50_0, &M50_1, rand_41);
  HPC2(M37_0, M37_1, T17_0, T17_1, &M51_0, &M51_1, rand_43);
  HPC2(M42_0, M42_1, T15_0, T15_1, &M52_0, &M52_1, rand_45);
  HPC2(M45_0, M45_1, T27_0, T27_1, &M53_0, &M53_1, rand_47);
  HPC2o(M41_0, M41_1, T10_0, T10_1, L4_0, L4_1, &M54_0, &M54_1, rand_49);
  HPC2(M44_0, M44_1, T13_0, T13_1, &M55_0, &M55_1, rand_51);
  HPC2(M40_0, M40_1, T23_0, T23_1, &M56_0, &M56_1, rand_53);
  HPC2(M39_0, M39_1, T19_0, T19_1, &M57_0, &M57_1, rand_55);
  HPC2(M43_0, M43_1, T3_0, T3_1, &M58_0, &M58_1, rand_57);
  HPC2o(M38_0, M38_1, T22_0, T22_1, L8_0, L8_1, &M59_0, &M59_1, rand_59);
  HPC2(M37_0, M37_1, T20_0, T20_1, &M60_0, &M60_1, rand_61);
  HPC2(M42_0, M42_1, T1_0, T1_1, &M61_0, &M61_1, rand_63);
  HPC2(M45_0, M45_1, T4_0, T4_1, &M62_0, &M62_1, rand_65);
  HPC2(M41_0, M41_1, T2_0, T2_1, &M63_0, &M63_1, rand_67);
  L0_0 = M61_0 ^ M62_0;
  L0_1 = M61_1 ^ M62_1;
  L1_0 = M50_0 ^ M56_0;
  L1_1 = M50_1 ^ M56_1;
  L2_0 = M46_0 ^ M48_0;
  L2_1 = M46_1 ^ M48_1;
  L3_0 = M47_0 ^ M55_0;
  L3_1 = M47_1 ^ M55_1;
  L4_0 = M54_0 ^ M58_0;
  L4_1 = M54_1 ^ M58_1;
  L5_0 = M49_0 ^ M61_0;
  L5_1 = M49_1 ^ M61_1;
  L6_0 = M62_0 ^ L5_0;
  L6_1 = M62_1 ^ L5_1;
  L7_0 = M46_0 ^ L3_0;
  L7_1 = M46_1 ^ L3_1;
  L8_0 = M51_0 ^ M59_0;
  L8_1 = M51_1 ^ M59_1;
  L9_0 = M52_0 ^ M53_0;
  L9_1 = M52_1 ^ M53_1;
  L10_0 = M53_0 ^ L4_0;
  L10_1 = M53_1 ^ L4_1;
  L11_0 = M60_0 ^ L2_0;
  L11_1 = M60_1 ^ L2_1;
  L12_0 = M48_0 ^ M51_0;
  L12_1 = M48_1 ^ M51_1;
  L13_0 = M50_0 ^ L0_0;
  L13_1 = M50_1 ^ L0_1;
  L14_0 = M52_0 ^ M61_0;
  L14_1 = M52_1 ^ M61_1;
  L15_0 = M55_0 ^ L1_0;
  L15_1 = M55_1 ^ L1_1;
  L16_0 = M56_0 ^ L0_0;
  L16_1 = M56_1 ^ L0_1;
  L17_0 = M57_0 ^ L1_0;
  L17_1 = M57_1 ^ L1_1;
  L18_0 = M58_0 ^ L8_0;
  L18_1 = M58_1 ^ L8_1;
  L19_0 = M63_0 ^ L4_0;
  L19_1 = M63_1 ^ L4_1;
  L20_0 = L0_0 ^ L1_0;
  L20_1 = L0_1 ^ L1_1;
  L21_0 = L1_0 ^ L7_0;
  L21_1 = L1_1 ^ L7_1;
  L22_0 = L3_0 ^ L12_0;
  L22_1 = L3_1 ^ L12_1;
  L23_0 = L18_0 ^ L2_0;
  L23_1 = L18_1 ^ L2_1;
  L24_0 = L15_0 ^ L9_0;
  L24_1 = L15_1 ^ L9_1;
  L25_0 = L6_0 ^ L10_0;
  L25_1 = L6_1 ^ L10_1;
  L26_0 = L7_0 ^ L9_0;
  L26_1 = L7_1 ^ L9_1;
  L27_0 = L8_0 ^ L10_0;
  L27_1 = L8_1 ^ L10_1;
  L28_0 = L11_0 ^ L14_0;
  L28_1 = L11_1 ^ L14_1;
  L29_0 = L11_0 ^ L17_0;
  L29_1 = L11_1 ^ L17_1;
  *Y0_0 = L6_0 ^ L24_0;
  *Y0_1 = L6_1 ^ L24_1;
  _Bool temp1_0;
  _Bool temp1_1;
  temp1_0 = L16_0 ^ L26_0;
  temp1_1 = L16_1 ^ L26_1;
  *Y1_0 = temp1_0;
  *Y1_1 = ~temp1_1;
  _Bool temp2_0;
  _Bool temp2_1;
  temp2_0 = L19_0 ^ L28_0;
  temp2_1 = L19_1 ^ L28_1;
  *Y2_0 = temp2_0;
  *Y2_1 = ~temp2_1;
  *Y3_0 = L6_0 ^ L21_0;
  *Y3_1 = L6_1 ^ L21_1;
  *Y4_0 = L20_0 ^ L22_0;
  *Y4_1 = L20_1 ^ L22_1;
  *Y5_0 = L25_0 ^ L29_0;
  *Y5_1 = L25_1 ^ L29_1;
  _Bool temp3_0;
  _Bool temp3_1;
  temp3_0 = L13_0 ^ L27_0;
  temp3_1 = L13_1 ^ L27_1;
  *Y6_0 = temp3_0;
  *Y6_1 = ~temp3_1;
  _Bool temp4_0;
  _Bool temp4_1;
  temp4_0 = L6_0 ^ L23_0;
  temp4_1 = L6_1 ^ L23_1;
  *Y7_0 = temp4_0;
  *Y7_1 = ~temp4_1;
}

