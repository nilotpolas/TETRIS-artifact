// === GADGET DEFINITIONS (hpc3o, hpc2o, etc.) ===

// --- hpc3 ---

void hpc3_same_shares_2_order(int a_share, int b_share, int * u_share) {
    * u_share  = a_share & b_share;
}

void hpc3_v_2_order(int a_share, int b_share, int * v_share, int rand){
    int temp;
    temp = reg(b_share ^ rand);
    *v_share = temp & a_share;
}

void hpc3_w_2_order(int a_share, int rand, int prand, int * w_share){
    int temp;
    int a_share_neg;
    a_share_neg = ~(a_share);
    temp = a_share_neg & rand;
    *w_share = reg(temp ^ prand);
}

void hpc3_xor_vw_2_order(int v_share, int w_share, int * u_share){
    *u_share = v_share ^ w_share;
}

void HPC3(int a0, int a1, int a2, int b0, int b1, int b2, int* c0, int* c1, int* c2, int r01, int r02, int r12, int p01, int p02, int p12)
{
	int u00, u01, u02, u10, u11, u12, u20, u21, u22;
	int v01, v02, v10, v12, v20, v21;
	int w01, w02, w10, w12, w20, w21;

	hpc3_same_shares_2_order(a0, b0, &u00);

	hpc3_v_2_order(a0, b1, &v01 , r01);
	hpc3_w_2_order(a0, r01, p01, &w01);
	hpc3_xor_vw_2_order(v01, w01, &u01);

	hpc3_v_2_order(a0, b2, &v02 , r02);
	hpc3_w_2_order(a0, r02, p02, &w02);
	hpc3_xor_vw_2_order(v02, w02, &u02);

	hpc3_v_2_order(a1, b0, &v10 , r01);
	hpc3_w_2_order(a1, r01, p01, &w10);
	hpc3_xor_vw_2_order(v10, w10, &u10);

	hpc3_same_shares_2_order(a1, b1, &u11);

	hpc3_v_2_order(a1, b2, &v12 , r12);
	hpc3_w_2_order(a1, r12, p12, &w12);
	hpc3_xor_vw_2_order(v12, w12, &u12);

	hpc3_v_2_order(a2, b0, &v20 , r02);
	hpc3_w_2_order(a2, r02, p02, &w20);
	hpc3_xor_vw_2_order(v20, w20, &u20);

	hpc3_v_2_order(a2, b1, &v21 , r12);
	hpc3_w_2_order(a2, r12, p12, &w21);
	hpc3_xor_vw_2_order(v21, w21, &u21);

	hpc3_same_shares_2_order(a2, b2, &u22);

	int t1, t2, t3;
	t1 = u00 ^ u01;
	*c0 = t1 ^ u02;

	t2 = u10 ^ u11;
	*c1 = t2 ^ u12;

	t3 = u20 ^ u21;
	*c2 = t3 ^ u22;

}


// --- hpc3o ---

void hpc3o_first_half_2_order(int a_share, int b_share, int w_share, int rand, int rand_prime, int *out_share) {
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

void hpc3o_v_2_order(int a_share, int b_share, int *v_share, int rand) {
    int xor_br;
    int temp;
    int and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br); // This remains an R register in Algo 7
    
    and_ta = a_share & temp;
    *v_share = and_ta; // Notice: NO outer reg() here for HPC3o!
}

void hpc3o_w_2_order(int a_share, int rand, int rand_prime, int *w_share) {
    int and_ar;
    int xor_step1;

    // Notice: Algo 7 does not negate a_share in the else branch
    and_ar = a_share & rand;
    xor_step1 = and_ar ^ rand_prime;
    
    *w_share = reg(xor_step1);
}

void hpc3o_xor_vw_2_order(int v_share, int w_share, int *u_share) {
    *u_share = v_share ^ w_share;
}
void HPC3o(int a0, int a1, int a2, int b0, int b1, int b2, int w0, int w1, int w2, int * c0, int * c1, int * c2, int rand_01, int rand_02, int rand_12, int rand_prime_01, int rand_prime_02, int rand_prime_12)
{
	int u01, u02, u10, u12, u20, u21;
	int v01, v02, v10, v12, v20, v21;
	int w01, w02, w10, w12, w20, w21;
	int t1, t2, t3;

	hpc3o_first_half_2_order(a0, b0, w0, rand_01, rand_prime_01, &w01);
	hpc3o_v_2_order(a0, b1, &v01, rand_01);
	hpc3o_xor_vw_2_order(v01, w01, &u01);

	hpc3o_w_2_order(a0, rand_02, rand_prime_02, &w02);
	hpc3o_v_2_order(a0, b2, &v02, rand_02);
	hpc3o_xor_vw_2_order(v02, w02, &u02);

	hpc3o_first_half_2_order(a1, b1, w1, rand_01, rand_prime_01, &w10);
	hpc3o_v_2_order(a1, b0, &v10, rand_01);
	hpc3o_xor_vw_2_order(v10, w10, &u10);

	hpc3o_w_2_order(a1, rand_12, rand_prime_12, &w12);
	hpc3o_v_2_order(a1, b2, &v12, rand_12);
	hpc3o_xor_vw_2_order(v12, w12, &u12);

	hpc3o_first_half_2_order(a2, b2, w2, rand_02, rand_prime_02, &w20);
	hpc3o_v_2_order(a2, b0, &v20, rand_02);
	hpc3o_xor_vw_2_order(v20, w20, &u20);

	hpc3o_w_2_order(a2, rand_12, rand_prime_12, &w21);
	hpc3o_v_2_order(a2, b1, &v21, rand_12);
	hpc3o_xor_vw_2_order(v21, w21, &u21);

	*c0 = u01 ^ u02;
	*c1 = u10 ^ u12;
	*c2 = u20 ^ u21;
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
void sbox(_Bool X0_0, _Bool X0_1, _Bool X0_2, _Bool X1_0, _Bool X1_1, _Bool X1_2, _Bool X2_0, _Bool X2_1, _Bool X2_2, _Bool X3_0, _Bool X3_1, _Bool X3_2, _Bool X4_0, _Bool X4_1, _Bool X4_2, _Bool X5_0, _Bool X5_1, _Bool X5_2, _Bool X6_0, _Bool X6_1, _Bool X6_2, _Bool X7_0, _Bool X7_1, _Bool X7_2, _Bool *Y0_0, _Bool *Y0_1, _Bool *Y0_2, _Bool *Y1_0, _Bool *Y1_1, _Bool *Y1_2, _Bool *Y2_0, _Bool *Y2_1, _Bool *Y2_2, _Bool *Y3_0, _Bool *Y3_1, _Bool *Y3_2, _Bool *Y4_0, _Bool *Y4_1, _Bool *Y4_2, _Bool *Y5_0, _Bool *Y5_1, _Bool *Y5_2, _Bool *Y6_0, _Bool *Y6_1, _Bool *Y6_2, _Bool *Y7_0, _Bool *Y7_1, _Bool *Y7_2, _Bool dec_1, int rand_5, int rand_43, int rand_68, int rand_102, int rand_44, int rand_69, int rand_168, int rand_70, int rand_6, int rand_45, int rand_46, int rand_71, int rand_47, int rand_103, int rand_169, int rand_72, int rand_7, int rand_48, int rand_104, int rand_170, int rand_8, int rand_105, int rand_171, int rand_9, int rand_106, int rand_172, int rand_10, int rand_107, int rand_173, int rand_11, int rand_108, int rand_174, int rand_12, int rand_109, int rand_181, int rand_13, int rand_110, int rand_182, int rand_14, int rand_111, int rand_183, int rand_15, int rand_112, int rand_184, int rand_16, int rand_113, int rand_185, int rand_17, int rand_114, int rand_186, int rand_18, int rand_101, int rand_49, int rand_121, int rand_187, int rand_50, int rand_91, int rand_19, int rand_51, int rand_92, int rand_122, int rand_52, int rand_93, int rand_188, int rand_20, int rand_53, int rand_94, int rand_123, int rand_95, int rand_189, int rand_21, int rand_54, int rand_124, int rand_190, int rand_96, int rand_22, int rand_125, int rand_191, int rand_31, int rand_23, int rand_32, int rand_126, int rand_192, int rand_33, int rand_24, int rand_34, int rand_35, int rand_127, int rand_193, int rand_36, int rand_25, int rand_128, int rand_194, int rand_26, int rand_129, int rand_195, int rand_27, int rand_130, int rand_196, int rand_28, int rand_131, int rand_197, int rand_29, int rand_132, int rand_198, int rand_30, int rand_133, int rand_199, int rand_37, int rand_134, int rand_200, int rand_38, int rand_135, int rand_201, int rand_39, int rand_136, int rand_202, int rand_40, int rand_137, int rand_203, int rand_41, int rand_138, int rand_204, int rand_115, int rand_42, int rand_116, int rand_79, int rand_139, int rand_80, int rand_117, int rand_55, int rand_81, int rand_140, int rand_82, int rand_118, int rand_56, int rand_83, int rand_141, int rand_119, int rand_57, int rand_84, int rand_142, int rand_58, int rand_120, int rand_143, int rand_59, int rand_144, int rand_60, int rand_145, int rand_151, int rand_146, int rand_73, int rand_152, int rand_147, int rand_74, int rand_153, int rand_148, int rand_75, int rand_154, int rand_149, int rand_76, int rand_155, int rand_77, int rand_150, int rand_156, int rand_78, int rand_157, int rand_175, int rand_85, int rand_158, int rand_176, int rand_61, int rand_62, int rand_86, int rand_159, int rand_177, int rand_63, int rand_64, int rand_87, int rand_160, int rand_178, int rand_65, int rand_88, int rand_161, int rand_179, int rand_66, int rand_89, int rand_162, int rand_180, int rand_90, int rand_163, int rand_1, int rand_97, int rand_164, int rand_2, int rand_98, int rand_165, int rand_3, int rand_99, int rand_166, int rand_4, int rand_100, int rand_167, int rand_67)
{
  _Bool T1_0;
  _Bool T1_1;
  _Bool T1_2;
  _Bool T2_0;
  _Bool T2_1;
  _Bool T2_2;
  _Bool T3_0;
  _Bool T3_1;
  _Bool T3_2;
  _Bool T4_0;
  _Bool T4_1;
  _Bool T4_2;
  _Bool T5_0;
  _Bool T5_1;
  _Bool T5_2;
  _Bool T6_0;
  _Bool T6_1;
  _Bool T6_2;
  _Bool T7_0;
  _Bool T7_1;
  _Bool T7_2;
  _Bool T8_0;
  _Bool T8_1;
  _Bool T8_2;
  _Bool T9_0;
  _Bool T9_1;
  _Bool T9_2;
  _Bool T10_0;
  _Bool T10_1;
  _Bool T10_2;
  _Bool T11_0;
  _Bool T11_1;
  _Bool T11_2;
  _Bool T12_0;
  _Bool T12_1;
  _Bool T12_2;
  _Bool T13_0;
  _Bool T13_1;
  _Bool T13_2;
  _Bool T14_0;
  _Bool T14_1;
  _Bool T14_2;
  _Bool T15_0;
  _Bool T15_1;
  _Bool T15_2;
  _Bool T16_0;
  _Bool T16_1;
  _Bool T16_2;
  _Bool T17_0;
  _Bool T17_1;
  _Bool T17_2;
  _Bool T18_0;
  _Bool T18_1;
  _Bool T18_2;
  _Bool T19_0;
  _Bool T19_1;
  _Bool T19_2;
  _Bool T20_0;
  _Bool T20_1;
  _Bool T20_2;
  _Bool T21_0;
  _Bool T21_1;
  _Bool T21_2;
  _Bool T22_0;
  _Bool T22_1;
  _Bool T22_2;
  _Bool T23_0;
  _Bool T23_1;
  _Bool T23_2;
  _Bool T24_0;
  _Bool T24_1;
  _Bool T24_2;
  _Bool T25_0;
  _Bool T25_1;
  _Bool T25_2;
  _Bool T26_0;
  _Bool T26_1;
  _Bool T26_2;
  _Bool T27_0;
  _Bool T27_1;
  _Bool T27_2;
  _Bool M1_0;
  _Bool M1_1;
  _Bool M1_2;
  _Bool M2_0;
  _Bool M2_1;
  _Bool M2_2;
  _Bool M3_0;
  _Bool M3_1;
  _Bool M3_2;
  _Bool M4_0;
  _Bool M4_1;
  _Bool M4_2;
  _Bool M5_0;
  _Bool M5_1;
  _Bool M5_2;
  _Bool M6_0;
  _Bool M6_1;
  _Bool M6_2;
  _Bool M7_0;
  _Bool M7_1;
  _Bool M7_2;
  _Bool M8_0;
  _Bool M8_1;
  _Bool M8_2;
  _Bool M9_0;
  _Bool M9_1;
  _Bool M9_2;
  _Bool M10_0;
  _Bool M10_1;
  _Bool M10_2;
  _Bool M11_0;
  _Bool M11_1;
  _Bool M11_2;
  _Bool M12_0;
  _Bool M12_1;
  _Bool M12_2;
  _Bool M13_0;
  _Bool M13_1;
  _Bool M13_2;
  _Bool M14_0;
  _Bool M14_1;
  _Bool M14_2;
  _Bool M15_0;
  _Bool M15_1;
  _Bool M15_2;
  _Bool M16_0;
  _Bool M16_1;
  _Bool M16_2;
  _Bool M17_0;
  _Bool M17_1;
  _Bool M17_2;
  _Bool M18_0;
  _Bool M18_1;
  _Bool M18_2;
  _Bool M19_0;
  _Bool M19_1;
  _Bool M19_2;
  _Bool M20_0;
  _Bool M20_1;
  _Bool M20_2;
  _Bool M21_0;
  _Bool M21_1;
  _Bool M21_2;
  _Bool M22_0;
  _Bool M22_1;
  _Bool M22_2;
  _Bool M23_0;
  _Bool M23_1;
  _Bool M23_2;
  _Bool M24_0;
  _Bool M24_1;
  _Bool M24_2;
  _Bool M25_0;
  _Bool M25_1;
  _Bool M25_2;
  _Bool M26_0;
  _Bool M26_1;
  _Bool M26_2;
  _Bool M27_0;
  _Bool M27_1;
  _Bool M27_2;
  _Bool M28_0;
  _Bool M28_1;
  _Bool M28_2;
  _Bool M29_0;
  _Bool M29_1;
  _Bool M29_2;
  _Bool M30_0;
  _Bool M30_1;
  _Bool M30_2;
  _Bool M31_0;
  _Bool M31_1;
  _Bool M31_2;
  _Bool M32_0;
  _Bool M32_1;
  _Bool M32_2;
  _Bool M33_0;
  _Bool M33_1;
  _Bool M33_2;
  _Bool M34_0;
  _Bool M34_1;
  _Bool M34_2;
  _Bool M35_0;
  _Bool M35_1;
  _Bool M35_2;
  _Bool M36_0;
  _Bool M36_1;
  _Bool M36_2;
  _Bool M37_0;
  _Bool M37_1;
  _Bool M37_2;
  _Bool M38_0;
  _Bool M38_1;
  _Bool M38_2;
  _Bool M39_0;
  _Bool M39_1;
  _Bool M39_2;
  _Bool M40_0;
  _Bool M40_1;
  _Bool M40_2;
  _Bool M41_0;
  _Bool M41_1;
  _Bool M41_2;
  _Bool M42_0;
  _Bool M42_1;
  _Bool M42_2;
  _Bool M43_0;
  _Bool M43_1;
  _Bool M43_2;
  _Bool M44_0;
  _Bool M44_1;
  _Bool M44_2;
  _Bool M45_0;
  _Bool M45_1;
  _Bool M45_2;
  _Bool M46_0;
  _Bool M46_1;
  _Bool M46_2;
  _Bool M47_0;
  _Bool M47_1;
  _Bool M47_2;
  _Bool M48_0;
  _Bool M48_1;
  _Bool M48_2;
  _Bool M49_0;
  _Bool M49_1;
  _Bool M49_2;
  _Bool M50_0;
  _Bool M50_1;
  _Bool M50_2;
  _Bool M51_0;
  _Bool M51_1;
  _Bool M51_2;
  _Bool M52_0;
  _Bool M52_1;
  _Bool M52_2;
  _Bool M53_0;
  _Bool M53_1;
  _Bool M53_2;
  _Bool M54_0;
  _Bool M54_1;
  _Bool M54_2;
  _Bool M55_0;
  _Bool M55_1;
  _Bool M55_2;
  _Bool M56_0;
  _Bool M56_1;
  _Bool M56_2;
  _Bool M57_0;
  _Bool M57_1;
  _Bool M57_2;
  _Bool M58_0;
  _Bool M58_1;
  _Bool M58_2;
  _Bool M59_0;
  _Bool M59_1;
  _Bool M59_2;
  _Bool M60_0;
  _Bool M60_1;
  _Bool M60_2;
  _Bool M61_0;
  _Bool M61_1;
  _Bool M61_2;
  _Bool M62_0;
  _Bool M62_1;
  _Bool M62_2;
  _Bool M63_0;
  _Bool M63_1;
  _Bool M63_2;
  _Bool L0_0;
  _Bool L0_1;
  _Bool L0_2;
  _Bool L1_0;
  _Bool L1_1;
  _Bool L1_2;
  _Bool L2_0;
  _Bool L2_1;
  _Bool L2_2;
  _Bool L3_0;
  _Bool L3_1;
  _Bool L3_2;
  _Bool L4_0;
  _Bool L4_1;
  _Bool L4_2;
  _Bool L5_0;
  _Bool L5_1;
  _Bool L5_2;
  _Bool L6_0;
  _Bool L6_1;
  _Bool L6_2;
  _Bool L7_0;
  _Bool L7_1;
  _Bool L7_2;
  _Bool L8_0;
  _Bool L8_1;
  _Bool L8_2;
  _Bool L9_0;
  _Bool L9_1;
  _Bool L9_2;
  _Bool L10_0;
  _Bool L10_1;
  _Bool L10_2;
  _Bool L11_0;
  _Bool L11_1;
  _Bool L11_2;
  _Bool L12_0;
  _Bool L12_1;
  _Bool L12_2;
  _Bool L13_0;
  _Bool L13_1;
  _Bool L13_2;
  _Bool L14_0;
  _Bool L14_1;
  _Bool L14_2;
  _Bool L15_0;
  _Bool L15_1;
  _Bool L15_2;
  _Bool L16_0;
  _Bool L16_1;
  _Bool L16_2;
  _Bool L17_0;
  _Bool L17_1;
  _Bool L17_2;
  _Bool L18_0;
  _Bool L18_1;
  _Bool L18_2;
  _Bool L19_0;
  _Bool L19_1;
  _Bool L19_2;
  _Bool L20_0;
  _Bool L20_1;
  _Bool L20_2;
  _Bool L21_0;
  _Bool L21_1;
  _Bool L21_2;
  _Bool L22_0;
  _Bool L22_1;
  _Bool L22_2;
  _Bool L23_0;
  _Bool L23_1;
  _Bool L23_2;
  _Bool L24_0;
  _Bool L24_1;
  _Bool L24_2;
  _Bool L25_0;
  _Bool L25_1;
  _Bool L25_2;
  _Bool L26_0;
  _Bool L26_1;
  _Bool L26_2;
  _Bool L27_0;
  _Bool L27_1;
  _Bool L27_2;
  _Bool L28_0;
  _Bool L28_1;
  _Bool L28_2;
  _Bool L29_0;
  _Bool L29_1;
  _Bool L29_2;
  T1_0 = X0_0 ^ X3_0;
  T1_1 = X0_1 ^ X3_1;
  T1_2 = X0_2 ^ X3_2;
  T2_0 = X0_0 ^ X5_0;
  T2_1 = X0_1 ^ X5_1;
  T2_2 = X0_2 ^ X5_2;
  T3_0 = X0_0 ^ X6_0;
  T3_1 = X0_1 ^ X6_1;
  T3_2 = X0_2 ^ X6_2;
  T4_0 = X3_0 ^ X5_0;
  T4_1 = X3_1 ^ X5_1;
  T4_2 = X3_2 ^ X5_2;
  T5_0 = X4_0 ^ X6_0;
  T5_1 = X4_1 ^ X6_1;
  T5_2 = X4_2 ^ X6_2;
  T6_0 = T1_0 ^ T5_0;
  T6_1 = T1_1 ^ T5_1;
  T6_2 = T1_2 ^ T5_2;
  T7_0 = X1_0 ^ X2_0;
  T7_1 = X1_1 ^ X2_1;
  T7_2 = X1_2 ^ X2_2;
  T8_0 = X7_0 ^ T6_0;
  T8_1 = X7_1 ^ T6_1;
  T8_2 = X7_2 ^ T6_2;
  T9_0 = X7_0 ^ T7_0;
  T9_1 = X7_1 ^ T7_1;
  T9_2 = X7_2 ^ T7_2;
  T10_0 = T6_0 ^ T7_0;
  T10_1 = T6_1 ^ T7_1;
  T10_2 = T6_2 ^ T7_2;
  T11_0 = X1_0 ^ X5_0;
  T11_1 = X1_1 ^ X5_1;
  T11_2 = X1_2 ^ X5_2;
  T12_0 = X2_0 ^ X5_0;
  T12_1 = X2_1 ^ X5_1;
  T12_2 = X2_2 ^ X5_2;
  T13_0 = T3_0 ^ T4_0;
  T13_1 = T3_1 ^ T4_1;
  T13_2 = T3_2 ^ T4_2;
  T14_0 = T6_0 ^ T11_0;
  T14_1 = T6_1 ^ T11_1;
  T14_2 = T6_2 ^ T11_2;
  T15_0 = T5_0 ^ T11_0;
  T15_1 = T5_1 ^ T11_1;
  T15_2 = T5_2 ^ T11_2;
  T16_0 = T5_0 ^ T12_0;
  T16_1 = T5_1 ^ T12_1;
  T16_2 = T5_2 ^ T12_2;
  T17_0 = T9_0 ^ T16_0;
  T17_1 = T9_1 ^ T16_1;
  T17_2 = T9_2 ^ T16_2;
  T18_0 = X3_0 ^ X7_0;
  T18_1 = X3_1 ^ X7_1;
  T18_2 = X3_2 ^ X7_2;
  T19_0 = T7_0 ^ T18_0;
  T19_1 = T7_1 ^ T18_1;
  T19_2 = T7_2 ^ T18_2;
  T20_0 = T1_0 ^ T19_0;
  T20_1 = T1_1 ^ T19_1;
  T20_2 = T1_2 ^ T19_2;
  T21_0 = X6_0 ^ X7_0;
  T21_1 = X6_1 ^ X7_1;
  T21_2 = X6_2 ^ X7_2;
  T22_0 = T7_0 ^ T21_0;
  T22_1 = T7_1 ^ T21_1;
  T22_2 = T7_2 ^ T21_2;
  T23_0 = T2_0 ^ T22_0;
  T23_1 = T2_1 ^ T22_1;
  T23_2 = T2_2 ^ T22_2;
  T24_0 = T2_0 ^ T10_0;
  T24_1 = T2_1 ^ T10_1;
  T24_2 = T2_2 ^ T10_2;
  T25_0 = T20_0 ^ T17_0;
  T25_1 = T20_1 ^ T17_1;
  T25_2 = T20_2 ^ T17_2;
  T26_0 = T3_0 ^ T16_0;
  T26_1 = T3_1 ^ T16_1;
  T26_2 = T3_2 ^ T16_2;
  T27_0 = T1_0 ^ T12_0;
  T27_1 = T1_1 ^ T12_1;
  T27_2 = T1_2 ^ T12_2;
  HPC3(T13_0, T13_1, T13_2, T6_0, T6_1, T6_2, &M1_0, &M1_1, &M1_2, rand_1, rand_2, rand_3, rand_4, rand_5, rand_6);
  HPC3(T23_0, T23_1, T23_2, T8_0, T8_1, T8_2, &M2_0, &M2_1, &M2_2, rand_7, rand_8, rand_9, rand_10, rand_11, rand_12);
  M3_0 = T14_0 ^ M1_0;
  M3_1 = T14_1 ^ M1_1;
  M3_2 = T14_2 ^ M1_2;
  HPC3(T19_0, T19_1, T19_2, X7_0, X7_1, X7_2, &M4_0, &M4_1, &M4_2, rand_13, rand_14, rand_15, rand_16, rand_17, rand_18);
  M5_0 = M4_0 ^ M1_0;
  M5_1 = M4_1 ^ M1_1;
  M5_2 = M4_2 ^ M1_2;
  HPC3(T3_0, T3_1, T3_2, T16_0, T16_1, T16_2, &M6_0, &M6_1, &M6_2, rand_19, rand_20, rand_21, rand_22, rand_23, rand_24);
  HPC3(T22_0, T22_1, T22_2, T9_0, T9_1, T9_2, &M7_0, &M7_1, &M7_2, rand_25, rand_26, rand_27, rand_28, rand_29, rand_30);
  M8_0 = T26_0 ^ M6_0;
  M8_1 = T26_1 ^ M6_1;
  M8_2 = T26_2 ^ M6_2;
  HPC3o(T20_0, T20_1, T20_2, T17_0, T17_1, T17_2, M10_0, M10_1, M10_2, &M9_0, &M9_1, &M9_2, rand_31, rand_32, rand_33, rand_34, rand_35, rand_36);
  M10_0 = M9_0 ^ M6_0;
  M10_1 = M9_1 ^ M6_1;
  M10_2 = M9_2 ^ M6_2;
  HPC3(T1_0, T1_1, T1_2, T15_0, T15_1, T15_2, &M11_0, &M11_1, &M11_2, rand_37, rand_38, rand_39, rand_40, rand_41, rand_42);
  HPC3o(T4_0, T4_1, T4_2, T27_0, T27_1, T27_2, M13_0, M13_1, M13_2, &M12_0, &M12_1, &M12_2, rand_43, rand_44, rand_45, rand_46, rand_47, rand_48);
  M13_0 = M12_0 ^ M11_0;
  M13_1 = M12_1 ^ M11_1;
  M13_2 = M12_2 ^ M11_2;
  HPC3o(T2_0, T2_1, T2_2, T10_0, T10_1, T10_2, M15_0, M15_1, M15_2, &M14_0, &M14_1, &M14_2, rand_49, rand_50, rand_51, rand_52, rand_53, rand_54);
  M15_0 = M14_0 ^ M11_0;
  M15_1 = M14_1 ^ M11_1;
  M15_2 = M14_2 ^ M11_2;
  M16_0 = M3_0 ^ M2_0;
  M16_1 = M3_1 ^ M2_1;
  M16_2 = M3_2 ^ M2_2;
  M17_0 = M5_0 ^ T24_0;
  M17_1 = M5_1 ^ T24_1;
  M17_2 = M5_2 ^ T24_2;
  M18_0 = M8_0 ^ M7_0;
  M18_1 = M8_1 ^ M7_1;
  M18_2 = M8_2 ^ M7_2;
  M19_0 = M10_0 ^ M15_0;
  M19_1 = M10_1 ^ M15_1;
  M19_2 = M10_2 ^ M15_2;
  M20_0 = M16_0 ^ M13_0;
  M20_1 = M16_1 ^ M13_1;
  M20_2 = M16_2 ^ M13_2;
  M21_0 = M17_0 ^ M15_0;
  M21_1 = M17_1 ^ M15_1;
  M21_2 = M17_2 ^ M15_2;
  M22_0 = M18_0 ^ M13_0;
  M22_1 = M18_1 ^ M13_1;
  M22_2 = M18_2 ^ M13_2;
  M23_0 = M19_0 ^ T25_0;
  M23_1 = M19_1 ^ T25_1;
  M23_2 = M19_2 ^ T25_2;
  M24_0 = M22_0 ^ M23_0;
  M24_1 = M22_1 ^ M23_1;
  M24_2 = M22_2 ^ M23_2;
  HPC3(M22_0, M22_1, M22_2, M20_0, M20_1, M20_2, &M25_0, &M25_1, &M25_2, rand_55, rand_56, rand_57, rand_58, rand_59, rand_60);
  M26_0 = M21_0 ^ M25_0;
  M26_1 = M21_1 ^ M25_1;
  M26_2 = M21_2 ^ M25_2;
  M27_0 = M20_0 ^ M21_0;
  M27_1 = M20_1 ^ M21_1;
  M27_2 = M20_2 ^ M21_2;
  M28_0 = M23_0 ^ M25_0;
  M28_1 = M23_1 ^ M25_1;
  M28_2 = M23_2 ^ M25_2;
  HPC3o(M28_0, M28_1, M28_2, M27_0, M27_1, M27_2, M37_0, M37_1, M37_2, &M29_0, &M29_1, &M29_2, rand_61, rand_62, rand_63, rand_64, rand_65, rand_66);
  HPC3o(M26_0, M26_1, M26_2, M24_0, M24_1, M24_2, M39_0, M39_1, M39_2, &M30_0, &M30_1, &M30_2, rand_67, rand_68, rand_69, rand_70, rand_71, rand_72);
  HPC3(M20_0, M20_1, M20_2, M23_0, M23_1, M23_2, &M31_0, &M31_1, &M31_2, rand_73, rand_74, rand_75, rand_76, rand_77, rand_78);
  HPC3o(M27_0, M27_1, M27_2, M31_0, M31_1, M31_2, M38_0, M38_1, M38_2, &M32_0, &M32_1, &M32_2, rand_79, rand_80, rand_81, rand_82, rand_83, rand_84);
  M33_0 = M27_0 ^ M25_0;
  M33_1 = M27_1 ^ M25_1;
  M33_2 = M27_2 ^ M25_2;
  HPC3(M21_0, M21_1, M21_2, M22_0, M22_1, M22_2, &M34_0, &M34_1, &M34_2, rand_85, rand_86, rand_87, rand_88, rand_89, rand_90);
  HPC3o(M24_0, M24_1, M24_2, M34_0, M34_1, M34_2, M40_0, M40_1, M40_2, &M35_0, &M35_1, &M35_2, rand_91, rand_92, rand_93, rand_94, rand_95, rand_96);
  M36_0 = M24_0 ^ M25_0;
  M36_1 = M24_1 ^ M25_1;
  M36_2 = M24_2 ^ M25_2;
  M37_0 = M21_0 ^ M29_0;
  M37_1 = M21_1 ^ M29_1;
  M37_2 = M21_2 ^ M29_2;
  M38_0 = M32_0 ^ M33_0;
  M38_1 = M32_1 ^ M33_1;
  M38_2 = M32_2 ^ M33_2;
  M39_0 = M23_0 ^ M30_0;
  M39_1 = M23_1 ^ M30_1;
  M39_2 = M23_2 ^ M30_2;
  M40_0 = M35_0 ^ M36_0;
  M40_1 = M35_1 ^ M36_1;
  M40_2 = M35_2 ^ M36_2;
  M41_0 = M38_0 ^ M40_0;
  M41_1 = M38_1 ^ M40_1;
  M41_2 = M38_2 ^ M40_2;
  M42_0 = M37_0 ^ M39_0;
  M42_1 = M37_1 ^ M39_1;
  M42_2 = M37_2 ^ M39_2;
  M43_0 = M37_0 ^ M38_0;
  M43_1 = M37_1 ^ M38_1;
  M43_2 = M37_2 ^ M38_2;
  M44_0 = M39_0 ^ M40_0;
  M44_1 = M39_1 ^ M40_1;
  M44_2 = M39_2 ^ M40_2;
  M45_0 = M42_0 ^ M41_0;
  M45_1 = M42_1 ^ M41_1;
  M45_2 = M42_2 ^ M41_2;
  HPC3(M44_0, M44_1, M44_2, T6_0, T6_1, T6_2, &M46_0, &M46_1, &M46_2, rand_97, rand_98, rand_99, rand_100, rand_101, rand_102);
  HPC3(M40_0, M40_1, M40_2, T8_0, T8_1, T8_2, &M47_0, &M47_1, &M47_2, rand_103, rand_104, rand_105, rand_106, rand_107, rand_108);
  HPC3(M39_0, M39_1, M39_2, X7_0, X7_1, X7_2, &M48_0, &M48_1, &M48_2, rand_109, rand_110, rand_111, rand_112, rand_113, rand_114);
  HPC3o(M43_0, M43_1, M43_2, T16_0, T16_1, T16_2, L5_0, L5_1, L5_2, &M49_0, &M49_1, &M49_2, rand_115, rand_116, rand_117, rand_118, rand_119, rand_120);
  HPC3(M38_0, M38_1, M38_2, T9_0, T9_1, T9_2, &M50_0, &M50_1, &M50_2, rand_121, rand_122, rand_123, rand_124, rand_125, rand_126);
  HPC3(M37_0, M37_1, M37_2, T17_0, T17_1, T17_2, &M51_0, &M51_1, &M51_2, rand_127, rand_128, rand_129, rand_130, rand_131, rand_132);
  HPC3(M42_0, M42_1, M42_2, T15_0, T15_1, T15_2, &M52_0, &M52_1, &M52_2, rand_133, rand_134, rand_135, rand_136, rand_137, rand_138);
  HPC3(M45_0, M45_1, M45_2, T27_0, T27_1, T27_2, &M53_0, &M53_1, &M53_2, rand_139, rand_140, rand_141, rand_142, rand_143, rand_144);
  HPC3o(M41_0, M41_1, M41_2, T10_0, T10_1, T10_2, L4_0, L4_1, L4_2, &M54_0, &M54_1, &M54_2, rand_145, rand_146, rand_147, rand_148, rand_149, rand_150);
  HPC3(M44_0, M44_1, M44_2, T13_0, T13_1, T13_2, &M55_0, &M55_1, &M55_2, rand_151, rand_152, rand_153, rand_154, rand_155, rand_156);
  HPC3(M40_0, M40_1, M40_2, T23_0, T23_1, T23_2, &M56_0, &M56_1, &M56_2, rand_157, rand_158, rand_159, rand_160, rand_161, rand_162);
  HPC3(M39_0, M39_1, M39_2, T19_0, T19_1, T19_2, &M57_0, &M57_1, &M57_2, rand_163, rand_164, rand_165, rand_166, rand_167, rand_168);
  HPC3(M43_0, M43_1, M43_2, T3_0, T3_1, T3_2, &M58_0, &M58_1, &M58_2, rand_169, rand_170, rand_171, rand_172, rand_173, rand_174);
  HPC3o(M38_0, M38_1, M38_2, T22_0, T22_1, T22_2, L8_0, L8_1, L8_2, &M59_0, &M59_1, &M59_2, rand_175, rand_176, rand_177, rand_178, rand_179, rand_180);
  HPC3(M37_0, M37_1, M37_2, T20_0, T20_1, T20_2, &M60_0, &M60_1, &M60_2, rand_181, rand_182, rand_183, rand_184, rand_185, rand_186);
  HPC3(M42_0, M42_1, M42_2, T1_0, T1_1, T1_2, &M61_0, &M61_1, &M61_2, rand_187, rand_188, rand_189, rand_190, rand_191, rand_192);
  HPC3(M45_0, M45_1, M45_2, T4_0, T4_1, T4_2, &M62_0, &M62_1, &M62_2, rand_193, rand_194, rand_195, rand_196, rand_197, rand_198);
  HPC3(M41_0, M41_1, M41_2, T2_0, T2_1, T2_2, &M63_0, &M63_1, &M63_2, rand_199, rand_200, rand_201, rand_202, rand_203, rand_204);
  L0_0 = M61_0 ^ M62_0;
  L0_1 = M61_1 ^ M62_1;
  L0_2 = M61_2 ^ M62_2;
  L1_0 = M50_0 ^ M56_0;
  L1_1 = M50_1 ^ M56_1;
  L1_2 = M50_2 ^ M56_2;
  L2_0 = M46_0 ^ M48_0;
  L2_1 = M46_1 ^ M48_1;
  L2_2 = M46_2 ^ M48_2;
  L3_0 = M47_0 ^ M55_0;
  L3_1 = M47_1 ^ M55_1;
  L3_2 = M47_2 ^ M55_2;
  L4_0 = M54_0 ^ M58_0;
  L4_1 = M54_1 ^ M58_1;
  L4_2 = M54_2 ^ M58_2;
  L5_0 = M49_0 ^ M61_0;
  L5_1 = M49_1 ^ M61_1;
  L5_2 = M49_2 ^ M61_2;
  L6_0 = M62_0 ^ L5_0;
  L6_1 = M62_1 ^ L5_1;
  L6_2 = M62_2 ^ L5_2;
  L7_0 = M46_0 ^ L3_0;
  L7_1 = M46_1 ^ L3_1;
  L7_2 = M46_2 ^ L3_2;
  L8_0 = M51_0 ^ M59_0;
  L8_1 = M51_1 ^ M59_1;
  L8_2 = M51_2 ^ M59_2;
  L9_0 = M52_0 ^ M53_0;
  L9_1 = M52_1 ^ M53_1;
  L9_2 = M52_2 ^ M53_2;
  L10_0 = M53_0 ^ L4_0;
  L10_1 = M53_1 ^ L4_1;
  L10_2 = M53_2 ^ L4_2;
  L11_0 = M60_0 ^ L2_0;
  L11_1 = M60_1 ^ L2_1;
  L11_2 = M60_2 ^ L2_2;
  L12_0 = M48_0 ^ M51_0;
  L12_1 = M48_1 ^ M51_1;
  L12_2 = M48_2 ^ M51_2;
  L13_0 = M50_0 ^ L0_0;
  L13_1 = M50_1 ^ L0_1;
  L13_2 = M50_2 ^ L0_2;
  L14_0 = M52_0 ^ M61_0;
  L14_1 = M52_1 ^ M61_1;
  L14_2 = M52_2 ^ M61_2;
  L15_0 = M55_0 ^ L1_0;
  L15_1 = M55_1 ^ L1_1;
  L15_2 = M55_2 ^ L1_2;
  L16_0 = M56_0 ^ L0_0;
  L16_1 = M56_1 ^ L0_1;
  L16_2 = M56_2 ^ L0_2;
  L17_0 = M57_0 ^ L1_0;
  L17_1 = M57_1 ^ L1_1;
  L17_2 = M57_2 ^ L1_2;
  L18_0 = M58_0 ^ L8_0;
  L18_1 = M58_1 ^ L8_1;
  L18_2 = M58_2 ^ L8_2;
  L19_0 = M63_0 ^ L4_0;
  L19_1 = M63_1 ^ L4_1;
  L19_2 = M63_2 ^ L4_2;
  L20_0 = L0_0 ^ L1_0;
  L20_1 = L0_1 ^ L1_1;
  L20_2 = L0_2 ^ L1_2;
  L21_0 = L1_0 ^ L7_0;
  L21_1 = L1_1 ^ L7_1;
  L21_2 = L1_2 ^ L7_2;
  L22_0 = L3_0 ^ L12_0;
  L22_1 = L3_1 ^ L12_1;
  L22_2 = L3_2 ^ L12_2;
  L23_0 = L18_0 ^ L2_0;
  L23_1 = L18_1 ^ L2_1;
  L23_2 = L18_2 ^ L2_2;
  L24_0 = L15_0 ^ L9_0;
  L24_1 = L15_1 ^ L9_1;
  L24_2 = L15_2 ^ L9_2;
  L25_0 = L6_0 ^ L10_0;
  L25_1 = L6_1 ^ L10_1;
  L25_2 = L6_2 ^ L10_2;
  L26_0 = L7_0 ^ L9_0;
  L26_1 = L7_1 ^ L9_1;
  L26_2 = L7_2 ^ L9_2;
  L27_0 = L8_0 ^ L10_0;
  L27_1 = L8_1 ^ L10_1;
  L27_2 = L8_2 ^ L10_2;
  L28_0 = L11_0 ^ L14_0;
  L28_1 = L11_1 ^ L14_1;
  L28_2 = L11_2 ^ L14_2;
  L29_0 = L11_0 ^ L17_0;
  L29_1 = L11_1 ^ L17_1;
  L29_2 = L11_2 ^ L17_2;
  *Y0_0 = L6_0 ^ L24_0;
  *Y0_1 = L6_1 ^ L24_1;
  *Y0_2 = L6_2 ^ L24_2;
  _Bool temp1_0;
  _Bool temp1_1;
  _Bool temp1_2;
  temp1_0 = L16_0 ^ L26_0;
  temp1_1 = L16_1 ^ L26_1;
  temp1_2 = L16_2 ^ L26_2;
  *Y1_0 = temp1_0;
  *Y1_1 = temp1_1;
  *Y1_2 = ~temp1_2;
  _Bool temp2_0;
  _Bool temp2_1;
  _Bool temp2_2;
  temp2_0 = L19_0 ^ L28_0;
  temp2_1 = L19_1 ^ L28_1;
  temp2_2 = L19_2 ^ L28_2;
  *Y2_0 = temp2_0;
  *Y2_1 = temp2_1;
  *Y2_2 = ~temp2_2;
  *Y3_0 = L6_0 ^ L21_0;
  *Y3_1 = L6_1 ^ L21_1;
  *Y3_2 = L6_2 ^ L21_2;
  *Y4_0 = L20_0 ^ L22_0;
  *Y4_1 = L20_1 ^ L22_1;
  *Y4_2 = L20_2 ^ L22_2;
  *Y5_0 = L25_0 ^ L29_0;
  *Y5_1 = L25_1 ^ L29_1;
  *Y5_2 = L25_2 ^ L29_2;
  _Bool temp3_0;
  _Bool temp3_1;
  _Bool temp3_2;
  temp3_0 = L13_0 ^ L27_0;
  temp3_1 = L13_1 ^ L27_1;
  temp3_2 = L13_2 ^ L27_2;
  *Y6_0 = temp3_0;
  *Y6_1 = temp3_1;
  *Y6_2 = ~temp3_2;
  _Bool temp4_0;
  _Bool temp4_1;
  _Bool temp4_2;
  temp4_0 = L6_0 ^ L23_0;
  temp4_1 = L6_1 ^ L23_1;
  temp4_2 = L6_2 ^ L23_2;
  *Y7_0 = temp4_0;
  *Y7_1 = temp4_1;
  *Y7_2 = ~temp4_2;
}

