// === GADGET DEFINITIONS ===

// --- hpc3 ---

void hpc3_same_shares_2_order(_Bool a_share, _Bool b_share, _Bool * u_share) {
    * u_share  = a_share & b_share;
}

void hpc3_v_2_order(_Bool a_share, _Bool b_share, _Bool * v_share, _Bool rand){
    _Bool temp;
    temp = reg(b_share ^ rand);
    *v_share = temp & a_share;
}

void hpc3_w_2_order(_Bool a_share, _Bool rand, _Bool prand, _Bool * w_share){
    _Bool temp;
    _Bool a_share_neg;
    a_share_neg = !(a_share);
    temp = a_share_neg & rand;
    *w_share = reg(temp ^ prand);
}

void hpc3_xor_vw_2_order(_Bool v_share, _Bool w_share, _Bool * u_share){
    *u_share = v_share ^ w_share;
}

void HPC3(_Bool a0, _Bool a1, _Bool a2, _Bool b0, _Bool b1, _Bool b2, _Bool* c0, _Bool* c1, _Bool* c2, _Bool r01, _Bool r02, _Bool r12, _Bool p01, _Bool p02, _Bool p12)
{
	_Bool u00, u01, u02, u10, u11, u12, u20, u21, u22;
	_Bool v01, v02, v10, v12, v20, v21;
	_Bool w01, w02, w10, w12, w20, w21;

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

	_Bool t1, t2, t3;
	t1 = u00 ^ u01;
	*c0 = t1 ^ u02;

	t2 = u10 ^ u11;
	*c1 = t2 ^ u12;

	t3 = u20 ^ u21;
	*c2 = t3 ^ u22;

}


// --- hpc2 ---

void hpc2_same_shares_2_order(_Bool a_share, _Bool b_share, _Bool * u_share) {
    * u_share  = a_share & b_share;
}

void hpc2_v_2_order(_Bool a_share, _Bool b_share, _Bool * v_share, _Bool rand){
    _Bool temp; 
    temp = reg(b_share ^ rand);
    *v_share = reg(temp & a_share);
}

void hpc2_w_2_order(_Bool a_share, _Bool rand, _Bool * w_share){
    _Bool a_neg;
    a_neg = !(a_share);
    *w_share = reg(a_neg & rand);
}

void hpc2_xor_vw_2_order(_Bool v_share, _Bool w_share, _Bool * u_share){
    *u_share = v_share ^ w_share;
}

void HPC2(_Bool a0, _Bool a1, _Bool a2, _Bool b0, _Bool b1, _Bool b2, _Bool * c0, _Bool * c1, _Bool * c2, _Bool rand_01, _Bool rand_02, _Bool rand_12)
{
	_Bool u00, u01, u02, u10, u11, u12, u20, u21, u22;
	_Bool v01, v02, v10, v12, v20, v21;

	_Bool w01, w02, w10, w12, w20, w21;

	hpc2_same_shares_2_order(a0, b0, &u00);
	hpc2_v_2_order(a0, b1, &v01 , rand_01);
	hpc2_w_2_order(a0, rand_01, &w01);
	hpc2_xor_vw_2_order(v01, w01, &u01);

	hpc2_v_2_order(a0, b2, &v02 , rand_02);
	hpc2_w_2_order(a0, rand_02, &w02);
	hpc2_xor_vw_2_order(v02, w02, &u02);

	hpc2_v_2_order(a1, b0, &v10 , rand_01);
	hpc2_w_2_order(a1, rand_01, &w10);
	hpc2_xor_vw_2_order(v10, w10, &u10);

	hpc2_same_shares_2_order(a1, b1, &u11);
	hpc2_v_2_order(a1, b2, &v12 , rand_12);
	hpc2_w_2_order(a1, rand_12, &w12);
	hpc2_xor_vw_2_order(v12, w12, &u12);

	hpc2_v_2_order(a2, b0, &v20 , rand_02);
	hpc2_w_2_order(a2, rand_02, &w20);
	hpc2_xor_vw_2_order(v20, w20, &u20);

	hpc2_v_2_order(a2, b1, &v21 , rand_12);
	hpc2_w_2_order(a2, rand_12, &w21);
	hpc2_xor_vw_2_order(v21, w21, &u21);

	hpc2_same_shares_2_order(a2, b2, &u22);
	_Bool t1, t2, t3;

	t1 = u00 ^ u01;
	*c0 = t1 ^ u02;

	t2 = u10 ^ u11;
	*c1 = t2 ^ u12;

	t3 = u20 ^ u21;
	*c2 = t3 ^ u22;

}


// --- hpc2_swapped ---

void hpc2sw_same_shares_2_order(_Bool a_share, _Bool b_share, _Bool * u_share) {
    *u_share = a_share & b_share;
}

void hpc2sw_v_2_order(_Bool a_share, _Bool b_share, _Bool * v_share, _Bool rand) {
    _Bool temp;
    temp = reg(b_share ^ rand);
    *v_share = reg(temp & a_share);
}

void hpc2sw_w_2_order(_Bool a_share, _Bool rand, _Bool * w_share) {
    _Bool a_neg;
    a_neg = !(a_share);
    *w_share = reg(a_neg & rand);
}

void hpc2sw_xor_vw_2_order(_Bool v_share, _Bool w_share, _Bool * u_share) {
    *u_share = v_share ^ w_share;
}

void HPC2_swapped(_Bool a0, _Bool a1, _Bool a2, _Bool b0, _Bool b1, _Bool b2, _Bool * c0, _Bool * c1, _Bool * c2, _Bool rand_01, _Bool rand_02, _Bool rand_12)
{
	_Bool u00, u01, u02, u10, u11, u12, u20, u21, u22;
	_Bool v01, v02, v10, v12, v20, v21;

	_Bool w01, w02, w10, w12, w20, w21;

	hpc2sw_same_shares_2_order(a0, b0, &u00);
	hpc2sw_v_2_order(b0, a1, &v01, rand_01);
	hpc2sw_w_2_order(b0, rand_01, &w01);
	hpc2sw_xor_vw_2_order(v01, w01, &u01);

	hpc2sw_v_2_order(b0, a2, &v02, rand_02);
	hpc2sw_w_2_order(b0, rand_02, &w02);
	hpc2sw_xor_vw_2_order(v02, w02, &u02);

	hpc2sw_v_2_order(b1, a0, &v10, rand_01);
	hpc2sw_w_2_order(b1, rand_01, &w10);
	hpc2sw_xor_vw_2_order(v10, w10, &u10);

	hpc2sw_same_shares_2_order(a1, b1, &u11);
	hpc2sw_v_2_order(b1, a2, &v12, rand_12);
	hpc2sw_w_2_order(b1, rand_12, &w12);
	hpc2sw_xor_vw_2_order(v12, w12, &u12);

	hpc2sw_v_2_order(b2, a0, &v20, rand_02);
	hpc2sw_w_2_order(b2, rand_02, &w20);
	hpc2sw_xor_vw_2_order(v20, w20, &u20);

	hpc2sw_v_2_order(b2, a1, &v21, rand_12);
	hpc2sw_w_2_order(b2, rand_12, &w21);
	hpc2sw_xor_vw_2_order(v21, w21, &u21);

	hpc2sw_same_shares_2_order(a2, b2, &u22);
	_Bool t1, t2, t3;

	t1 = u00 ^ u01;
	*c0 = t1 ^ u02;

	t2 = u10 ^ u11;
	*c1 = t2 ^ u12;

	t3 = u20 ^ u21;
	*c2 = t3 ^ u22;

}


// --- hpc2o ---

void hpc2o_first_half_2_order(_Bool a_share, _Bool b_share, _Bool w_share, _Bool rand, _Bool *out_share) {
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
}

void hpc2o_v_2_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand) {
    _Bool xor_br;
    _Bool temp;
    _Bool and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br); // This remains an R register in Algo 6
    
    and_ta = temp & a_share;
    *v_share = reg(and_ta);
}

void hpc2o_w_2_order(_Bool a_share, _Bool rand, _Bool *w_share) {
    _Bool a_neg;
    _Bool and_ar;

    a_neg = !a_share;
    
    and_ar = a_neg & rand;
    *w_share = reg(and_ar);
}

void hpc2o_xor_vw_2_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share ^ w_share;
}

void hpc2o_or_vw_2_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share | w_share;
}
void HPC2o(_Bool a0, _Bool a1, _Bool a2, _Bool b0, _Bool b1, _Bool b2, _Bool w0, _Bool w1, _Bool w2, _Bool * c0, _Bool * c1, _Bool * c2, _Bool rand_01, _Bool rand_02, _Bool rand_12)
{
	_Bool u01, u02, u10, u12, u20, u21;
	_Bool v01, v02, v10, v12, v20, v21;
	_Bool w01, w02, w10, w12, w20, w21;
	_Bool t1, t2, t3;

	hpc2o_first_half_2_order(a0, b0, w0, rand_01, &w01);
	hpc2o_v_2_order(a0, b1, &v01, rand_01);
	hpc2o_xor_vw_2_order(v01, w01, &u01);

	hpc2o_w_2_order(a0, rand_02, &w02);
	hpc2o_v_2_order(a0, b2, &v02, rand_02);
	hpc2o_or_vw_2_order(v02, w02, &u02);

	hpc2o_first_half_2_order(a1, b1, w1, rand_01, &w10);
	hpc2o_v_2_order(a1, b0, &v10, rand_01);
	hpc2o_xor_vw_2_order(v10, w10, &u10);

	hpc2o_w_2_order(a1, rand_12, &w12);
	hpc2o_v_2_order(a1, b2, &v12, rand_12);
	hpc2o_or_vw_2_order(v12, w12, &u12);

	hpc2o_first_half_2_order(a2, b2, w2, rand_02, &w20);
	hpc2o_v_2_order(a2, b0, &v20, rand_02);
	hpc2o_xor_vw_2_order(v20, w20, &u20);

	hpc2o_w_2_order(a2, rand_12, &w21);
	hpc2o_v_2_order(a2, b1, &v21, rand_12);
	hpc2o_or_vw_2_order(v21, w21, &u21);

	*c0 = u01 ^ u02;
	*c1 = u10 ^ u12;
	*c2 = u20 ^ u21;
}


// --- hpc2o_swapped ---

void hpc2osw_first_half_2_order(_Bool a_share, _Bool b_share, _Bool w_share, _Bool rand, _Bool *out_share) {
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
}

void hpc2osw_v_2_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand) {
    _Bool xor_br;
    _Bool temp;
    _Bool and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br);

    and_ta = temp & a_share;
    *v_share = reg(and_ta);
}

void hpc2osw_w_2_order(_Bool a_share, _Bool rand, _Bool *w_share) {
    _Bool a_neg;
    _Bool and_ar;

    a_neg = !a_share;

    and_ar = a_neg & rand;
    *w_share = reg(and_ar);
}

void hpc2osw_xor_vw_2_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share ^ w_share;
}

void hpc2osw_or_vw_2_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share | w_share;
}
void HPC2o_swapped(_Bool a0, _Bool a1, _Bool a2, _Bool b0, _Bool b1, _Bool b2, _Bool w0, _Bool w1, _Bool w2, _Bool * c0, _Bool * c1, _Bool * c2, _Bool rand_01, _Bool rand_02, _Bool rand_12)
{
	_Bool u01, u02, u10, u12, u20, u21;
	_Bool v01, v02, v10, v12, v20, v21;
	_Bool w01, w02, w10, w12, w20, w21;
	_Bool t1, t2, t3;

	hpc2osw_first_half_2_order(b0, a0, w0, rand_01, &w01);
	hpc2osw_v_2_order(b0, a1, &v01, rand_01);
	hpc2osw_xor_vw_2_order(v01, w01, &u01);

	hpc2osw_w_2_order(b0, rand_02, &w02);
	hpc2osw_v_2_order(b0, a2, &v02, rand_02);
	hpc2osw_or_vw_2_order(v02, w02, &u02);

	hpc2osw_first_half_2_order(b1, a1, w1, rand_01, &w10);
	hpc2osw_v_2_order(b1, a0, &v10, rand_01);
	hpc2osw_xor_vw_2_order(v10, w10, &u10);

	hpc2osw_w_2_order(b1, rand_12, &w12);
	hpc2osw_v_2_order(b1, a2, &v12, rand_12);
	hpc2osw_or_vw_2_order(v12, w12, &u12);

	hpc2osw_first_half_2_order(b2, a2, w2, rand_02, &w20);
	hpc2osw_v_2_order(b2, a0, &v20, rand_02);
	hpc2osw_xor_vw_2_order(v20, w20, &u20);

	hpc2osw_w_2_order(b2, rand_12, &w21);
	hpc2osw_v_2_order(b2, a1, &v21, rand_12);
	hpc2osw_or_vw_2_order(v21, w21, &u21);

	*c0 = u01 ^ u02;
	*c1 = u10 ^ u12;
	*c2 = u20 ^ u21;
}


// --- hpc3o ---

void hpc3o_first_half_2_order(_Bool a_share, _Bool b_share, _Bool w_share, _Bool rand, _Bool rand_prime, _Bool *out_share) {
    _Bool xor_br;
    _Bool and_ar;
    _Bool xor_step1;
    _Bool xor_step2;

    xor_br = b_share ^ rand;
    and_ar = a_share & xor_br;
    xor_step1 = w_share ^ and_ar;
    xor_step2 = xor_step1 ^ rand_prime;
    
    *out_share = reg(xor_step2);
}

void hpc3o_v_2_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand) {
    _Bool xor_br;
    _Bool temp;
    _Bool and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br); // This remains an R register in Algo 7
    
    and_ta = a_share & temp;
    *v_share = and_ta; // Notice: NO outer reg() here for HPC3o!
}

void hpc3o_w_2_order(_Bool a_share, _Bool rand, _Bool rand_prime, _Bool *w_share) {
    _Bool and_ar;
    _Bool xor_step1;

    // Notice: Algo 7 does not negate a_share in the else branch
    and_ar = a_share & rand;
    xor_step1 = and_ar ^ rand_prime;
    
    *w_share = reg(xor_step1);
}

void hpc3o_xor_vw_2_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share ^ w_share;
}
void HPC3o(_Bool a0, _Bool a1, _Bool a2, _Bool b0, _Bool b1, _Bool b2, _Bool w0, _Bool w1, _Bool w2, _Bool * c0, _Bool * c1, _Bool * c2, _Bool rand_01, _Bool rand_02, _Bool rand_12, _Bool rand_prime_01, _Bool rand_prime_02, _Bool rand_prime_12)
{
	_Bool u01, u02, u10, u12, u20, u21;
	_Bool v01, v02, v10, v12, v20, v21;
	_Bool w01, w02, w10, w12, w20, w21;
	_Bool t1, t2, t3;

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


// === TRANSFORMED CIRCUIT ===
void sbox(_Bool sb_n0_0, _Bool sb_n0_1, _Bool sb_n0_2, _Bool sb_n1_0, _Bool sb_n1_1, _Bool sb_n1_2, _Bool sb_n2_0, _Bool sb_n2_1, _Bool sb_n2_2, _Bool sb_n3_0, _Bool sb_n3_1, _Bool sb_n3_2, _Bool sb_n4_0, _Bool sb_n4_1, _Bool sb_n4_2, _Bool sb_n5_0, _Bool sb_n5_1, _Bool sb_n5_2, _Bool sb_n6_0, _Bool sb_n6_1, _Bool sb_n6_2, _Bool sb_n7_0, _Bool sb_n7_1, _Bool sb_n7_2, _Bool *sb_o0_0, _Bool *sb_o0_1, _Bool *sb_o0_2, _Bool *sb_o1_0, _Bool *sb_o1_1, _Bool *sb_o1_2, _Bool *sb_o2_0, _Bool *sb_o2_1, _Bool *sb_o2_2, _Bool *sb_o3_0, _Bool *sb_o3_1, _Bool *sb_o3_2, _Bool *sb_o4_0, _Bool *sb_o4_1, _Bool *sb_o4_2, _Bool *sb_o5_0, _Bool *sb_o5_1, _Bool *sb_o5_2, _Bool *sb_o6_0, _Bool *sb_o6_1, _Bool *sb_o6_2, _Bool *sb_o7_0, _Bool *sb_o7_1, _Bool *sb_o7_2, int dec_1, int rand_49, int rand_122, int rand_50, int rand_123, int rand_51, int rand_124, int rand_52, int rand_125, int rand_53, int rand_126, int rand_54, int rand_128, int rand_55, int rand_127, int rand_57, int rand_129, int rand_58, int rand_130, int rand_59, int rand_131, int rand_60, int rand_132, int rand_61, int rand_133, int rand_62, int rand_134, int rand_63, int rand_135, int rand_64, int rand_136, int rand_65, int rand_137, int rand_66, int rand_138, int rand_67, int rand_139, int rand_68, int rand_140, int rand_69, int rand_141, int rand_70, int rand_142, int rand_71, int rand_143, int rand_72, int rand_144, int rand_73, int rand_74, int rand_75, int rand_2, int rand_76, int rand_3, int rand_77, int rand_4, int rand_78, int rand_5, int rand_79, int rand_6, int rand_80, int rand_7, int rand_81, int rand_8, int rand_82, int rand_9, int rand_83, int rand_10, int rand_84, int rand_11, int rand_85, int rand_12, int rand_86, int rand_13, int rand_87, int rand_1, int rand_14, int rand_88, int rand_15, int rand_89, int rand_16, int rand_90, int rand_17, int rand_91, int rand_18, int rand_92, int rand_20, int rand_93, int rand_19, int rand_94, int rand_21, int rand_95, int rand_22, int rand_96, int rand_23, int rand_97, int rand_24, int rand_98, int rand_37, int rand_99, int rand_25, int rand_101, int rand_26, int rand_100, int rand_27, int rand_102, int rand_28, int rand_103, int rand_29, int rand_104, int rand_30, int rand_105, int rand_31, int rand_106, int rand_32, int rand_107, int rand_33, int rand_108, int rand_34, int rand_109, int rand_35, int rand_110, int rand_36, int rand_111, int rand_38, int rand_112, int rand_39, int rand_113, int rand_40, int rand_114, int rand_41, int rand_115, int rand_42, int rand_116, int rand_56, int rand_117, int rand_43, int rand_118, int rand_44, int rand_119, int rand_45, int rand_120, int rand_46, int rand_121, int rand_47, int rand_48)
{
  _Bool sb_y0_0;
  _Bool sb_y0_1;
  _Bool sb_y0_2;
  _Bool sb_y1_0;
  _Bool sb_y1_1;
  _Bool sb_y1_2;
  _Bool sb_y2_0;
  _Bool sb_y2_1;
  _Bool sb_y2_2;
  _Bool sb_y3_0;
  _Bool sb_y3_1;
  _Bool sb_y3_2;
  _Bool sb_y4_0;
  _Bool sb_y4_1;
  _Bool sb_y4_2;
  _Bool sb_y5_0;
  _Bool sb_y5_1;
  _Bool sb_y5_2;
  _Bool sb_y6_0;
  _Bool sb_y6_1;
  _Bool sb_y6_2;
  _Bool sb_y7_0;
  _Bool sb_y7_1;
  _Bool sb_y7_2;
  _Bool sb_i0_0;
  _Bool sb_i0_1;
  _Bool sb_i0_2;
  _Bool sb_i1_0;
  _Bool sb_i1_1;
  _Bool sb_i1_2;
  _Bool sb_i2_0;
  _Bool sb_i2_1;
  _Bool sb_i2_2;
  _Bool sb_i3_0;
  _Bool sb_i3_1;
  _Bool sb_i3_2;
  _Bool sb_i4_0;
  _Bool sb_i4_1;
  _Bool sb_i4_2;
  _Bool sb_i5_0;
  _Bool sb_i5_1;
  _Bool sb_i5_2;
  _Bool sb_i6_0;
  _Bool sb_i6_1;
  _Bool sb_i6_2;
  _Bool sb_i7_0;
  _Bool sb_i7_1;
  _Bool sb_i7_2;
  _Bool fy0_0;
  _Bool fy0_1;
  _Bool fy0_2;
  _Bool fy1_0;
  _Bool fy1_1;
  _Bool fy1_2;
  _Bool fy2_0;
  _Bool fy2_1;
  _Bool fy2_2;
  _Bool fy3_0;
  _Bool fy3_1;
  _Bool fy3_2;
  _Bool fy4_0;
  _Bool fy4_1;
  _Bool fy4_2;
  _Bool fy5_0;
  _Bool fy5_1;
  _Bool fy5_2;
  _Bool fy6_0;
  _Bool fy6_1;
  _Bool fy6_2;
  _Bool fy7_0;
  _Bool fy7_1;
  _Bool fy7_2;
  _Bool temp_var_0_0;
  _Bool temp_var_0_1;
  _Bool temp_var_0_2;
  temp_var_0_0 = sb_n0_0 ^ sb_n1_0;
  temp_var_0_1 = sb_n0_1 ^ sb_n1_1;
  temp_var_0_2 = sb_n0_2 ^ sb_n1_2;
  _Bool temp_var_1_0;
  _Bool temp_var_1_1;
  _Bool temp_var_1_2;
  temp_var_1_0 = temp_var_0_0 ^ sb_n2_0;
  temp_var_1_1 = temp_var_0_1 ^ sb_n2_1;
  temp_var_1_2 = temp_var_0_2 ^ sb_n2_2;
  _Bool temp_var_2_0;
  _Bool temp_var_2_1;
  _Bool temp_var_2_2;
  temp_var_2_0 = temp_var_1_0 ^ sb_n3_0;
  temp_var_2_1 = temp_var_1_1 ^ sb_n3_1;
  temp_var_2_2 = temp_var_1_2 ^ sb_n3_2;
  sb_y0_0 = temp_var_2_0 ^ sb_n6_0;
  sb_y0_1 = temp_var_2_1 ^ sb_n6_1;
  sb_y0_2 = temp_var_2_2 ^ sb_n6_2;
  _Bool temp_var_3_0;
  _Bool temp_var_3_1;
  _Bool temp_var_3_2;
  temp_var_3_0 = sb_n0_0 ^ sb_n5_0;
  temp_var_3_1 = sb_n0_1 ^ sb_n5_1;
  temp_var_3_2 = sb_n0_2 ^ sb_n5_2;
  sb_y1_0 = temp_var_3_0 ^ sb_n6_0;
  sb_y1_1 = temp_var_3_1 ^ sb_n6_1;
  sb_y1_2 = temp_var_3_2 ^ sb_n6_2;
  sb_y2_0 = sb_n0_0;
  sb_y2_1 = sb_n0_1;
  sb_y2_2 = sb_n0_2;
  _Bool temp_var_4_0;
  _Bool temp_var_4_1;
  _Bool temp_var_4_2;
  temp_var_4_0 = sb_n0_0 ^ sb_n1_0;
  temp_var_4_1 = sb_n0_1 ^ sb_n1_1;
  temp_var_4_2 = sb_n0_2 ^ sb_n1_2;
  _Bool temp_var_5_0;
  _Bool temp_var_5_1;
  _Bool temp_var_5_2;
  temp_var_5_0 = temp_var_4_0 ^ sb_n3_0;
  temp_var_5_1 = temp_var_4_1 ^ sb_n3_1;
  temp_var_5_2 = temp_var_4_2 ^ sb_n3_2;
  _Bool temp_var_6_0;
  _Bool temp_var_6_1;
  _Bool temp_var_6_2;
  temp_var_6_0 = temp_var_5_0 ^ sb_n4_0;
  temp_var_6_1 = temp_var_5_1 ^ sb_n4_1;
  temp_var_6_2 = temp_var_5_2 ^ sb_n4_2;
  sb_y3_0 = temp_var_6_0 ^ sb_n7_0;
  sb_y3_1 = temp_var_6_1 ^ sb_n7_1;
  sb_y3_2 = temp_var_6_2 ^ sb_n7_2;
  _Bool temp_var_7_0;
  _Bool temp_var_7_1;
  _Bool temp_var_7_2;
  temp_var_7_0 = sb_n0_0 ^ sb_n5_0;
  temp_var_7_1 = sb_n0_1 ^ sb_n5_1;
  temp_var_7_2 = sb_n0_2 ^ sb_n5_2;
  _Bool temp_var_8_0;
  _Bool temp_var_8_1;
  _Bool temp_var_8_2;
  temp_var_8_0 = temp_var_7_0 ^ sb_n6_0;
  temp_var_8_1 = temp_var_7_1 ^ sb_n6_1;
  temp_var_8_2 = temp_var_7_2 ^ sb_n6_2;
  sb_y4_0 = temp_var_8_0 ^ sb_n7_0;
  sb_y4_1 = temp_var_8_1 ^ sb_n7_1;
  sb_y4_2 = temp_var_8_2 ^ sb_n7_2;
  _Bool temp_var_9_0;
  _Bool temp_var_9_1;
  _Bool temp_var_9_2;
  temp_var_9_0 = sb_n0_0 ^ sb_n1_0;
  temp_var_9_1 = sb_n0_1 ^ sb_n1_1;
  temp_var_9_2 = sb_n0_2 ^ sb_n1_2;
  _Bool temp_var_10_0;
  _Bool temp_var_10_1;
  _Bool temp_var_10_2;
  temp_var_10_0 = temp_var_9_0 ^ sb_n5_0;
  temp_var_10_1 = temp_var_9_1 ^ sb_n5_1;
  temp_var_10_2 = temp_var_9_2 ^ sb_n5_2;
  sb_y5_0 = temp_var_10_0 ^ sb_n6_0;
  sb_y5_1 = temp_var_10_1 ^ sb_n6_1;
  sb_y5_2 = temp_var_10_2 ^ sb_n6_2;
  _Bool temp_var_11_0;
  _Bool temp_var_11_1;
  _Bool temp_var_11_2;
  temp_var_11_0 = sb_n0_0 ^ sb_n4_0;
  temp_var_11_1 = sb_n0_1 ^ sb_n4_1;
  temp_var_11_2 = sb_n0_2 ^ sb_n4_2;
  _Bool temp_var_12_0;
  _Bool temp_var_12_1;
  _Bool temp_var_12_2;
  temp_var_12_0 = temp_var_11_0 ^ sb_n5_0;
  temp_var_12_1 = temp_var_11_1 ^ sb_n5_1;
  temp_var_12_2 = temp_var_11_2 ^ sb_n5_2;
  sb_y6_0 = temp_var_12_0 ^ sb_n6_0;
  sb_y6_1 = temp_var_12_1 ^ sb_n6_1;
  sb_y6_2 = temp_var_12_2 ^ sb_n6_2;
  _Bool temp_var_13_0;
  _Bool temp_var_13_1;
  _Bool temp_var_13_2;
  temp_var_13_0 = sb_n0_0 ^ sb_n1_0;
  temp_var_13_1 = sb_n0_1 ^ sb_n1_1;
  temp_var_13_2 = sb_n0_2 ^ sb_n1_2;
  _Bool temp_var_14_0;
  _Bool temp_var_14_1;
  _Bool temp_var_14_2;
  temp_var_14_0 = temp_var_13_0 ^ sb_n2_0;
  temp_var_14_1 = temp_var_13_1 ^ sb_n2_1;
  temp_var_14_2 = temp_var_13_2 ^ sb_n2_2;
  _Bool temp_var_15_0;
  _Bool temp_var_15_1;
  _Bool temp_var_15_2;
  temp_var_15_0 = temp_var_14_0 ^ sb_n5_0;
  temp_var_15_1 = temp_var_14_1 ^ sb_n5_1;
  temp_var_15_2 = temp_var_14_2 ^ sb_n5_2;
  _Bool temp_var_16_0;
  _Bool temp_var_16_1;
  _Bool temp_var_16_2;
  temp_var_16_0 = temp_var_15_0 ^ sb_n6_0;
  temp_var_16_1 = temp_var_15_1 ^ sb_n6_1;
  temp_var_16_2 = temp_var_15_2 ^ sb_n6_2;
  sb_y7_0 = temp_var_16_0 ^ sb_n7_0;
  sb_y7_1 = temp_var_16_1 ^ sb_n7_1;
  sb_y7_2 = temp_var_16_2 ^ sb_n7_2;
  _Bool i256_tx0_G256_inv0_0;
  _Bool i256_tx0_G256_inv0_1;
  _Bool i256_tx0_G256_inv0_2;
  _Bool i256_tx1_G256_inv0_0;
  _Bool i256_tx1_G256_inv0_1;
  _Bool i256_tx1_G256_inv0_2;
  _Bool i256_tx2_G256_inv0_0;
  _Bool i256_tx2_G256_inv0_1;
  _Bool i256_tx2_G256_inv0_2;
  _Bool i256_tx3_G256_inv0_0;
  _Bool i256_tx3_G256_inv0_1;
  _Bool i256_tx3_G256_inv0_2;
  _Bool i256_c0_G256_inv0_0;
  _Bool i256_c0_G256_inv0_1;
  _Bool i256_c0_G256_inv0_2;
  _Bool i256_c1_G256_inv0_0;
  _Bool i256_c1_G256_inv0_1;
  _Bool i256_c1_G256_inv0_2;
  _Bool i256_c2_G256_inv0_0;
  _Bool i256_c2_G256_inv0_1;
  _Bool i256_c2_G256_inv0_2;
  _Bool i256_c3_G256_inv0_0;
  _Bool i256_c3_G256_inv0_1;
  _Bool i256_c3_G256_inv0_2;
  _Bool i256_d0_G256_inv0_0;
  _Bool i256_d0_G256_inv0_1;
  _Bool i256_d0_G256_inv0_2;
  _Bool i256_d1_G256_inv0_0;
  _Bool i256_d1_G256_inv0_1;
  _Bool i256_d1_G256_inv0_2;
  _Bool i256_d2_G256_inv0_0;
  _Bool i256_d2_G256_inv0_1;
  _Bool i256_d2_G256_inv0_2;
  _Bool i256_d3_G256_inv0_0;
  _Bool i256_d3_G256_inv0_1;
  _Bool i256_d3_G256_inv0_2;
  _Bool i256_te0_G256_inv0_0;
  _Bool i256_te0_G256_inv0_1;
  _Bool i256_te0_G256_inv0_2;
  _Bool i256_te1_G256_inv0_0;
  _Bool i256_te1_G256_inv0_1;
  _Bool i256_te1_G256_inv0_2;
  _Bool i256_te2_G256_inv0_0;
  _Bool i256_te2_G256_inv0_1;
  _Bool i256_te2_G256_inv0_2;
  _Bool i256_te3_G256_inv0_0;
  _Bool i256_te3_G256_inv0_1;
  _Bool i256_te3_G256_inv0_2;
  _Bool i256_e0_G256_inv0_0;
  _Bool i256_e0_G256_inv0_1;
  _Bool i256_e0_G256_inv0_2;
  _Bool i256_e1_G256_inv0_0;
  _Bool i256_e1_G256_inv0_1;
  _Bool i256_e1_G256_inv0_2;
  _Bool i256_e2_G256_inv0_0;
  _Bool i256_e2_G256_inv0_1;
  _Bool i256_e2_G256_inv0_2;
  _Bool i256_e3_G256_inv0_0;
  _Bool i256_e3_G256_inv0_1;
  _Bool i256_e3_G256_inv0_2;
  _Bool i256_ph0_G256_inv0_0;
  _Bool i256_ph0_G256_inv0_1;
  _Bool i256_ph0_G256_inv0_2;
  _Bool i256_ph1_G256_inv0_0;
  _Bool i256_ph1_G256_inv0_1;
  _Bool i256_ph1_G256_inv0_2;
  _Bool i256_ph2_G256_inv0_0;
  _Bool i256_ph2_G256_inv0_1;
  _Bool i256_ph2_G256_inv0_2;
  _Bool i256_ph3_G256_inv0_0;
  _Bool i256_ph3_G256_inv0_1;
  _Bool i256_ph3_G256_inv0_2;
  _Bool i256_ql0_G256_inv0_0;
  _Bool i256_ql0_G256_inv0_1;
  _Bool i256_ql0_G256_inv0_2;
  _Bool i256_ql1_G256_inv0_0;
  _Bool i256_ql1_G256_inv0_1;
  _Bool i256_ql1_G256_inv0_2;
  _Bool i256_ql2_G256_inv0_0;
  _Bool i256_ql2_G256_inv0_1;
  _Bool i256_ql2_G256_inv0_2;
  _Bool i256_ql3_G256_inv0_0;
  _Bool i256_ql3_G256_inv0_1;
  _Bool i256_ql3_G256_inv0_2;
  _Bool ss16_tx0_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_tx0_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_tx0_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_tx1_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_tx1_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_tx1_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_ph0_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_ph0_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_ph0_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_ph1_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_ph1_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_ph1_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_ql0_s1_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_ql0_s1_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_ql0_s1_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_ql1_s1_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_ql1_s1_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_ql1_s1_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_ql0_s2_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_ql0_s2_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_ql0_s2_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_ql1_s2_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_ql1_s2_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_ql1_s2_G16_sq_scl0_G256_inv0_2;
  _Bool m16_tx0_G16_mul0_G256_inv0_0;
  _Bool m16_tx0_G16_mul0_G256_inv0_1;
  _Bool m16_tx0_G16_mul0_G256_inv0_2;
  _Bool m16_tx1_G16_mul0_G256_inv0_0;
  _Bool m16_tx1_G16_mul0_G256_inv0_1;
  _Bool m16_tx1_G16_mul0_G256_inv0_2;
  _Bool m16_ty0_G16_mul0_G256_inv0_0;
  _Bool m16_ty0_G16_mul0_G256_inv0_1;
  _Bool m16_ty0_G16_mul0_G256_inv0_2;
  _Bool m16_ty1_G16_mul0_G256_inv0_0;
  _Bool m16_ty1_G16_mul0_G256_inv0_1;
  _Bool m16_ty1_G16_mul0_G256_inv0_2;
  _Bool m16_e0_s1_G16_mul0_G256_inv0_0;
  _Bool m16_e0_s1_G16_mul0_G256_inv0_1;
  _Bool m16_e0_s1_G16_mul0_G256_inv0_2;
  _Bool m16_e1_s1_G16_mul0_G256_inv0_0;
  _Bool m16_e1_s1_G16_mul0_G256_inv0_1;
  _Bool m16_e1_s1_G16_mul0_G256_inv0_2;
  _Bool m16_e0_s2_G16_mul0_G256_inv0_0;
  _Bool m16_e0_s2_G16_mul0_G256_inv0_1;
  _Bool m16_e0_s2_G16_mul0_G256_inv0_2;
  _Bool m16_e1_s2_G16_mul0_G256_inv0_0;
  _Bool m16_e1_s2_G16_mul0_G256_inv0_1;
  _Bool m16_e1_s2_G16_mul0_G256_inv0_2;
  _Bool m16_ph0_G16_mul0_G256_inv0_0;
  _Bool m16_ph0_G16_mul0_G256_inv0_1;
  _Bool m16_ph0_G16_mul0_G256_inv0_2;
  _Bool m16_ph1_G16_mul0_G256_inv0_0;
  _Bool m16_ph1_G16_mul0_G256_inv0_1;
  _Bool m16_ph1_G16_mul0_G256_inv0_2;
  _Bool m16_ql0_G16_mul0_G256_inv0_0;
  _Bool m16_ql0_G16_mul0_G256_inv0_1;
  _Bool m16_ql0_G16_mul0_G256_inv0_2;
  _Bool m16_ql1_G16_mul0_G256_inv0_0;
  _Bool m16_ql1_G16_mul0_G256_inv0_1;
  _Bool m16_ql1_G16_mul0_G256_inv0_2;
  _Bool m4_ab_G4_mul0_G16_mul0_G256_inv0_0;
  _Bool m4_ab_G4_mul0_G16_mul0_G256_inv0_1;
  _Bool m4_ab_G4_mul0_G16_mul0_G256_inv0_2;
  _Bool m4_cd_G4_mul0_G16_mul0_G256_inv0_0;
  _Bool m4_cd_G4_mul0_G16_mul0_G256_inv0_1;
  _Bool m4_cd_G4_mul0_G16_mul0_G256_inv0_2;
  _Bool m4_e_G4_mul0_G16_mul0_G256_inv0_0;
  _Bool m4_e_G4_mul0_G16_mul0_G256_inv0_1;
  _Bool m4_e_G4_mul0_G16_mul0_G256_inv0_2;
  _Bool temp_var_0_G4_mul0_G16_mul0_G256_inv0_0;
  _Bool temp_var_0_G4_mul0_G16_mul0_G256_inv0_1;
  _Bool temp_var_0_G4_mul0_G16_mul0_G256_inv0_2;
  _Bool temp_var_1_G4_mul0_G16_mul0_G256_inv0_0;
  _Bool temp_var_1_G4_mul0_G16_mul0_G256_inv0_1;
  _Bool temp_var_1_G4_mul0_G16_mul0_G256_inv0_2;
  _Bool m4_ab_G4_mul1_G16_mul0_G256_inv0_0;
  _Bool m4_ab_G4_mul1_G16_mul0_G256_inv0_1;
  _Bool m4_ab_G4_mul1_G16_mul0_G256_inv0_2;
  _Bool m4_cd_G4_mul1_G16_mul0_G256_inv0_0;
  _Bool m4_cd_G4_mul1_G16_mul0_G256_inv0_1;
  _Bool m4_cd_G4_mul1_G16_mul0_G256_inv0_2;
  _Bool m4_e_G4_mul1_G16_mul0_G256_inv0_0;
  _Bool m4_e_G4_mul1_G16_mul0_G256_inv0_1;
  _Bool m4_e_G4_mul1_G16_mul0_G256_inv0_2;
  _Bool temp_var_0_G4_mul1_G16_mul0_G256_inv0_0;
  _Bool temp_var_0_G4_mul1_G16_mul0_G256_inv0_1;
  _Bool temp_var_0_G4_mul1_G16_mul0_G256_inv0_2;
  _Bool temp_var_1_G4_mul1_G16_mul0_G256_inv0_0;
  _Bool temp_var_1_G4_mul1_G16_mul0_G256_inv0_1;
  _Bool temp_var_1_G4_mul1_G16_mul0_G256_inv0_2;
  _Bool m4_ab_G4_mul2_G16_mul0_G256_inv0_0;
  _Bool m4_ab_G4_mul2_G16_mul0_G256_inv0_1;
  _Bool m4_ab_G4_mul2_G16_mul0_G256_inv0_2;
  _Bool m4_cd_G4_mul2_G16_mul0_G256_inv0_0;
  _Bool m4_cd_G4_mul2_G16_mul0_G256_inv0_1;
  _Bool m4_cd_G4_mul2_G16_mul0_G256_inv0_2;
  _Bool m4_e_G4_mul2_G16_mul0_G256_inv0_0;
  _Bool m4_e_G4_mul2_G16_mul0_G256_inv0_1;
  _Bool m4_e_G4_mul2_G16_mul0_G256_inv0_2;
  _Bool temp_var_0_G4_mul2_G16_mul0_G256_inv0_0;
  _Bool temp_var_0_G4_mul2_G16_mul0_G256_inv0_1;
  _Bool temp_var_0_G4_mul2_G16_mul0_G256_inv0_2;
  _Bool temp_var_1_G4_mul2_G16_mul0_G256_inv0_0;
  _Bool temp_var_1_G4_mul2_G16_mul0_G256_inv0_1;
  _Bool temp_var_1_G4_mul2_G16_mul0_G256_inv0_2;
  _Bool i16_tx0_G16_inv0_G256_inv0_0;
  _Bool i16_tx0_G16_inv0_G256_inv0_1;
  _Bool i16_tx0_G16_inv0_G256_inv0_2;
  _Bool i16_tx1_G16_inv0_G256_inv0_0;
  _Bool i16_tx1_G16_inv0_G256_inv0_1;
  _Bool i16_tx1_G16_inv0_G256_inv0_2;
  _Bool i16_c0_s1_G16_inv0_G256_inv0_0;
  _Bool i16_c0_s1_G16_inv0_G256_inv0_1;
  _Bool i16_c0_s1_G16_inv0_G256_inv0_2;
  _Bool i16_c1_s1_G16_inv0_G256_inv0_0;
  _Bool i16_c1_s1_G16_inv0_G256_inv0_1;
  _Bool i16_c1_s1_G16_inv0_G256_inv0_2;
  _Bool i16_c0_s2_G16_inv0_G256_inv0_0;
  _Bool i16_c0_s2_G16_inv0_G256_inv0_1;
  _Bool i16_c0_s2_G16_inv0_G256_inv0_2;
  _Bool i16_c1_s2_G16_inv0_G256_inv0_0;
  _Bool i16_c1_s2_G16_inv0_G256_inv0_1;
  _Bool i16_c1_s2_G16_inv0_G256_inv0_2;
  _Bool i16_d0_G16_inv0_G256_inv0_0;
  _Bool i16_d0_G16_inv0_G256_inv0_1;
  _Bool i16_d0_G16_inv0_G256_inv0_2;
  _Bool i16_d1_G16_inv0_G256_inv0_0;
  _Bool i16_d1_G16_inv0_G256_inv0_1;
  _Bool i16_d1_G16_inv0_G256_inv0_2;
  _Bool i16_te0_G16_inv0_G256_inv0_0;
  _Bool i16_te0_G16_inv0_G256_inv0_1;
  _Bool i16_te0_G16_inv0_G256_inv0_2;
  _Bool i16_te1_G16_inv0_G256_inv0_0;
  _Bool i16_te1_G16_inv0_G256_inv0_1;
  _Bool i16_te1_G16_inv0_G256_inv0_2;
  _Bool i16_e0_G16_inv0_G256_inv0_0;
  _Bool i16_e0_G16_inv0_G256_inv0_1;
  _Bool i16_e0_G16_inv0_G256_inv0_2;
  _Bool i16_e1_G16_inv0_G256_inv0_0;
  _Bool i16_e1_G16_inv0_G256_inv0_1;
  _Bool i16_e1_G16_inv0_G256_inv0_2;
  _Bool i16_ph0_G16_inv0_G256_inv0_0;
  _Bool i16_ph0_G16_inv0_G256_inv0_1;
  _Bool i16_ph0_G16_inv0_G256_inv0_2;
  _Bool i16_ph1_G16_inv0_G256_inv0_0;
  _Bool i16_ph1_G16_inv0_G256_inv0_1;
  _Bool i16_ph1_G16_inv0_G256_inv0_2;
  _Bool i16_ql0_G16_inv0_G256_inv0_0;
  _Bool i16_ql0_G16_inv0_G256_inv0_1;
  _Bool i16_ql0_G16_inv0_G256_inv0_2;
  _Bool i16_ql1_G16_inv0_G256_inv0_0;
  _Bool i16_ql1_G16_inv0_G256_inv0_1;
  _Bool i16_ql1_G16_inv0_G256_inv0_2;
  _Bool m4_ab_G4_mul3_G16_inv0_G256_inv0_0;
  _Bool m4_ab_G4_mul3_G16_inv0_G256_inv0_1;
  _Bool m4_ab_G4_mul3_G16_inv0_G256_inv0_2;
  _Bool m4_cd_G4_mul3_G16_inv0_G256_inv0_0;
  _Bool m4_cd_G4_mul3_G16_inv0_G256_inv0_1;
  _Bool m4_cd_G4_mul3_G16_inv0_G256_inv0_2;
  _Bool m4_e_G4_mul3_G16_inv0_G256_inv0_0;
  _Bool m4_e_G4_mul3_G16_inv0_G256_inv0_1;
  _Bool m4_e_G4_mul3_G16_inv0_G256_inv0_2;
  _Bool temp_var_0_G4_mul3_G16_inv0_G256_inv0_0;
  _Bool temp_var_0_G4_mul3_G16_inv0_G256_inv0_1;
  _Bool temp_var_0_G4_mul3_G16_inv0_G256_inv0_2;
  _Bool temp_var_1_G4_mul3_G16_inv0_G256_inv0_0;
  _Bool temp_var_1_G4_mul3_G16_inv0_G256_inv0_1;
  _Bool temp_var_1_G4_mul3_G16_inv0_G256_inv0_2;
  _Bool m4_ab_G4_mul4_G16_inv0_G256_inv0_0;
  _Bool m4_ab_G4_mul4_G16_inv0_G256_inv0_1;
  _Bool m4_ab_G4_mul4_G16_inv0_G256_inv0_2;
  _Bool m4_cd_G4_mul4_G16_inv0_G256_inv0_0;
  _Bool m4_cd_G4_mul4_G16_inv0_G256_inv0_1;
  _Bool m4_cd_G4_mul4_G16_inv0_G256_inv0_2;
  _Bool m4_e_G4_mul4_G16_inv0_G256_inv0_0;
  _Bool m4_e_G4_mul4_G16_inv0_G256_inv0_1;
  _Bool m4_e_G4_mul4_G16_inv0_G256_inv0_2;
  _Bool temp_var_0_G4_mul4_G16_inv0_G256_inv0_0;
  _Bool temp_var_0_G4_mul4_G16_inv0_G256_inv0_1;
  _Bool temp_var_0_G4_mul4_G16_inv0_G256_inv0_2;
  _Bool temp_var_1_G4_mul4_G16_inv0_G256_inv0_0;
  _Bool temp_var_1_G4_mul4_G16_inv0_G256_inv0_1;
  _Bool temp_var_1_G4_mul4_G16_inv0_G256_inv0_2;
  _Bool m4_ab_G4_mul5_G16_inv0_G256_inv0_0;
  _Bool m4_ab_G4_mul5_G16_inv0_G256_inv0_1;
  _Bool m4_ab_G4_mul5_G16_inv0_G256_inv0_2;
  _Bool m4_cd_G4_mul5_G16_inv0_G256_inv0_0;
  _Bool m4_cd_G4_mul5_G16_inv0_G256_inv0_1;
  _Bool m4_cd_G4_mul5_G16_inv0_G256_inv0_2;
  _Bool m4_e_G4_mul5_G16_inv0_G256_inv0_0;
  _Bool m4_e_G4_mul5_G16_inv0_G256_inv0_1;
  _Bool m4_e_G4_mul5_G16_inv0_G256_inv0_2;
  _Bool temp_var_0_G4_mul5_G16_inv0_G256_inv0_0;
  _Bool temp_var_0_G4_mul5_G16_inv0_G256_inv0_1;
  _Bool temp_var_0_G4_mul5_G16_inv0_G256_inv0_2;
  _Bool temp_var_1_G4_mul5_G16_inv0_G256_inv0_0;
  _Bool temp_var_1_G4_mul5_G16_inv0_G256_inv0_1;
  _Bool temp_var_1_G4_mul5_G16_inv0_G256_inv0_2;
  _Bool m16_tx0_G16_mul1_G256_inv0_0;
  _Bool m16_tx0_G16_mul1_G256_inv0_1;
  _Bool m16_tx0_G16_mul1_G256_inv0_2;
  _Bool m16_tx1_G16_mul1_G256_inv0_0;
  _Bool m16_tx1_G16_mul1_G256_inv0_1;
  _Bool m16_tx1_G16_mul1_G256_inv0_2;
  _Bool m16_ty0_G16_mul1_G256_inv0_0;
  _Bool m16_ty0_G16_mul1_G256_inv0_1;
  _Bool m16_ty0_G16_mul1_G256_inv0_2;
  _Bool m16_ty1_G16_mul1_G256_inv0_0;
  _Bool m16_ty1_G16_mul1_G256_inv0_1;
  _Bool m16_ty1_G16_mul1_G256_inv0_2;
  _Bool m16_e0_s1_G16_mul1_G256_inv0_0;
  _Bool m16_e0_s1_G16_mul1_G256_inv0_1;
  _Bool m16_e0_s1_G16_mul1_G256_inv0_2;
  _Bool m16_e1_s1_G16_mul1_G256_inv0_0;
  _Bool m16_e1_s1_G16_mul1_G256_inv0_1;
  _Bool m16_e1_s1_G16_mul1_G256_inv0_2;
  _Bool m16_e0_s2_G16_mul1_G256_inv0_0;
  _Bool m16_e0_s2_G16_mul1_G256_inv0_1;
  _Bool m16_e0_s2_G16_mul1_G256_inv0_2;
  _Bool m16_e1_s2_G16_mul1_G256_inv0_0;
  _Bool m16_e1_s2_G16_mul1_G256_inv0_1;
  _Bool m16_e1_s2_G16_mul1_G256_inv0_2;
  _Bool m16_ph0_G16_mul1_G256_inv0_0;
  _Bool m16_ph0_G16_mul1_G256_inv0_1;
  _Bool m16_ph0_G16_mul1_G256_inv0_2;
  _Bool m16_ph1_G16_mul1_G256_inv0_0;
  _Bool m16_ph1_G16_mul1_G256_inv0_1;
  _Bool m16_ph1_G16_mul1_G256_inv0_2;
  _Bool m16_ql0_G16_mul1_G256_inv0_0;
  _Bool m16_ql0_G16_mul1_G256_inv0_1;
  _Bool m16_ql0_G16_mul1_G256_inv0_2;
  _Bool m16_ql1_G16_mul1_G256_inv0_0;
  _Bool m16_ql1_G16_mul1_G256_inv0_1;
  _Bool m16_ql1_G16_mul1_G256_inv0_2;
  _Bool m4_ab_G4_mul0_G16_mul1_G256_inv0_0;
  _Bool m4_ab_G4_mul0_G16_mul1_G256_inv0_1;
  _Bool m4_ab_G4_mul0_G16_mul1_G256_inv0_2;
  _Bool m4_cd_G4_mul0_G16_mul1_G256_inv0_0;
  _Bool m4_cd_G4_mul0_G16_mul1_G256_inv0_1;
  _Bool m4_cd_G4_mul0_G16_mul1_G256_inv0_2;
  _Bool m4_e_G4_mul0_G16_mul1_G256_inv0_0;
  _Bool m4_e_G4_mul0_G16_mul1_G256_inv0_1;
  _Bool m4_e_G4_mul0_G16_mul1_G256_inv0_2;
  _Bool temp_var_0_G4_mul0_G16_mul1_G256_inv0_0;
  _Bool temp_var_0_G4_mul0_G16_mul1_G256_inv0_1;
  _Bool temp_var_0_G4_mul0_G16_mul1_G256_inv0_2;
  _Bool temp_var_1_G4_mul0_G16_mul1_G256_inv0_0;
  _Bool temp_var_1_G4_mul0_G16_mul1_G256_inv0_1;
  _Bool temp_var_1_G4_mul0_G16_mul1_G256_inv0_2;
  _Bool m4_ab_G4_mul1_G16_mul1_G256_inv0_0;
  _Bool m4_ab_G4_mul1_G16_mul1_G256_inv0_1;
  _Bool m4_ab_G4_mul1_G16_mul1_G256_inv0_2;
  _Bool m4_cd_G4_mul1_G16_mul1_G256_inv0_0;
  _Bool m4_cd_G4_mul1_G16_mul1_G256_inv0_1;
  _Bool m4_cd_G4_mul1_G16_mul1_G256_inv0_2;
  _Bool m4_e_G4_mul1_G16_mul1_G256_inv0_0;
  _Bool m4_e_G4_mul1_G16_mul1_G256_inv0_1;
  _Bool m4_e_G4_mul1_G16_mul1_G256_inv0_2;
  _Bool temp_var_0_G4_mul1_G16_mul1_G256_inv0_0;
  _Bool temp_var_0_G4_mul1_G16_mul1_G256_inv0_1;
  _Bool temp_var_0_G4_mul1_G16_mul1_G256_inv0_2;
  _Bool temp_var_1_G4_mul1_G16_mul1_G256_inv0_0;
  _Bool temp_var_1_G4_mul1_G16_mul1_G256_inv0_1;
  _Bool temp_var_1_G4_mul1_G16_mul1_G256_inv0_2;
  _Bool m4_ab_G4_mul2_G16_mul1_G256_inv0_0;
  _Bool m4_ab_G4_mul2_G16_mul1_G256_inv0_1;
  _Bool m4_ab_G4_mul2_G16_mul1_G256_inv0_2;
  _Bool m4_cd_G4_mul2_G16_mul1_G256_inv0_0;
  _Bool m4_cd_G4_mul2_G16_mul1_G256_inv0_1;
  _Bool m4_cd_G4_mul2_G16_mul1_G256_inv0_2;
  _Bool m4_e_G4_mul2_G16_mul1_G256_inv0_0;
  _Bool m4_e_G4_mul2_G16_mul1_G256_inv0_1;
  _Bool m4_e_G4_mul2_G16_mul1_G256_inv0_2;
  _Bool temp_var_0_G4_mul2_G16_mul1_G256_inv0_0;
  _Bool temp_var_0_G4_mul2_G16_mul1_G256_inv0_1;
  _Bool temp_var_0_G4_mul2_G16_mul1_G256_inv0_2;
  _Bool temp_var_1_G4_mul2_G16_mul1_G256_inv0_0;
  _Bool temp_var_1_G4_mul2_G16_mul1_G256_inv0_1;
  _Bool temp_var_1_G4_mul2_G16_mul1_G256_inv0_2;
  _Bool m16_tx0_G16_mul2_G256_inv0_0;
  _Bool m16_tx0_G16_mul2_G256_inv0_1;
  _Bool m16_tx0_G16_mul2_G256_inv0_2;
  _Bool m16_tx1_G16_mul2_G256_inv0_0;
  _Bool m16_tx1_G16_mul2_G256_inv0_1;
  _Bool m16_tx1_G16_mul2_G256_inv0_2;
  _Bool m16_ty0_G16_mul2_G256_inv0_0;
  _Bool m16_ty0_G16_mul2_G256_inv0_1;
  _Bool m16_ty0_G16_mul2_G256_inv0_2;
  _Bool m16_ty1_G16_mul2_G256_inv0_0;
  _Bool m16_ty1_G16_mul2_G256_inv0_1;
  _Bool m16_ty1_G16_mul2_G256_inv0_2;
  _Bool m16_e0_s1_G16_mul2_G256_inv0_0;
  _Bool m16_e0_s1_G16_mul2_G256_inv0_1;
  _Bool m16_e0_s1_G16_mul2_G256_inv0_2;
  _Bool m16_e1_s1_G16_mul2_G256_inv0_0;
  _Bool m16_e1_s1_G16_mul2_G256_inv0_1;
  _Bool m16_e1_s1_G16_mul2_G256_inv0_2;
  _Bool m16_e0_s2_G16_mul2_G256_inv0_0;
  _Bool m16_e0_s2_G16_mul2_G256_inv0_1;
  _Bool m16_e0_s2_G16_mul2_G256_inv0_2;
  _Bool m16_e1_s2_G16_mul2_G256_inv0_0;
  _Bool m16_e1_s2_G16_mul2_G256_inv0_1;
  _Bool m16_e1_s2_G16_mul2_G256_inv0_2;
  _Bool m16_ph0_G16_mul2_G256_inv0_0;
  _Bool m16_ph0_G16_mul2_G256_inv0_1;
  _Bool m16_ph0_G16_mul2_G256_inv0_2;
  _Bool m16_ph1_G16_mul2_G256_inv0_0;
  _Bool m16_ph1_G16_mul2_G256_inv0_1;
  _Bool m16_ph1_G16_mul2_G256_inv0_2;
  _Bool m16_ql0_G16_mul2_G256_inv0_0;
  _Bool m16_ql0_G16_mul2_G256_inv0_1;
  _Bool m16_ql0_G16_mul2_G256_inv0_2;
  _Bool m16_ql1_G16_mul2_G256_inv0_0;
  _Bool m16_ql1_G16_mul2_G256_inv0_1;
  _Bool m16_ql1_G16_mul2_G256_inv0_2;
  _Bool m4_ab_G4_mul0_G16_mul2_G256_inv0_0;
  _Bool m4_ab_G4_mul0_G16_mul2_G256_inv0_1;
  _Bool m4_ab_G4_mul0_G16_mul2_G256_inv0_2;
  _Bool m4_cd_G4_mul0_G16_mul2_G256_inv0_0;
  _Bool m4_cd_G4_mul0_G16_mul2_G256_inv0_1;
  _Bool m4_cd_G4_mul0_G16_mul2_G256_inv0_2;
  _Bool m4_e_G4_mul0_G16_mul2_G256_inv0_0;
  _Bool m4_e_G4_mul0_G16_mul2_G256_inv0_1;
  _Bool m4_e_G4_mul0_G16_mul2_G256_inv0_2;
  _Bool temp_var_0_G4_mul0_G16_mul2_G256_inv0_0;
  _Bool temp_var_0_G4_mul0_G16_mul2_G256_inv0_1;
  _Bool temp_var_0_G4_mul0_G16_mul2_G256_inv0_2;
  _Bool temp_var_1_G4_mul0_G16_mul2_G256_inv0_0;
  _Bool temp_var_1_G4_mul0_G16_mul2_G256_inv0_1;
  _Bool temp_var_1_G4_mul0_G16_mul2_G256_inv0_2;
  _Bool m4_ab_G4_mul1_G16_mul2_G256_inv0_0;
  _Bool m4_ab_G4_mul1_G16_mul2_G256_inv0_1;
  _Bool m4_ab_G4_mul1_G16_mul2_G256_inv0_2;
  _Bool m4_cd_G4_mul1_G16_mul2_G256_inv0_0;
  _Bool m4_cd_G4_mul1_G16_mul2_G256_inv0_1;
  _Bool m4_cd_G4_mul1_G16_mul2_G256_inv0_2;
  _Bool m4_e_G4_mul1_G16_mul2_G256_inv0_0;
  _Bool m4_e_G4_mul1_G16_mul2_G256_inv0_1;
  _Bool m4_e_G4_mul1_G16_mul2_G256_inv0_2;
  _Bool temp_var_0_G4_mul1_G16_mul2_G256_inv0_0;
  _Bool temp_var_0_G4_mul1_G16_mul2_G256_inv0_1;
  _Bool temp_var_0_G4_mul1_G16_mul2_G256_inv0_2;
  _Bool temp_var_1_G4_mul1_G16_mul2_G256_inv0_0;
  _Bool temp_var_1_G4_mul1_G16_mul2_G256_inv0_1;
  _Bool temp_var_1_G4_mul1_G16_mul2_G256_inv0_2;
  _Bool m4_ab_G4_mul2_G16_mul2_G256_inv0_0;
  _Bool m4_ab_G4_mul2_G16_mul2_G256_inv0_1;
  _Bool m4_ab_G4_mul2_G16_mul2_G256_inv0_2;
  _Bool m4_cd_G4_mul2_G16_mul2_G256_inv0_0;
  _Bool m4_cd_G4_mul2_G16_mul2_G256_inv0_1;
  _Bool m4_cd_G4_mul2_G16_mul2_G256_inv0_2;
  _Bool m4_e_G4_mul2_G16_mul2_G256_inv0_0;
  _Bool m4_e_G4_mul2_G16_mul2_G256_inv0_1;
  _Bool m4_e_G4_mul2_G16_mul2_G256_inv0_2;
  _Bool temp_var_0_G4_mul2_G16_mul2_G256_inv0_0;
  _Bool temp_var_0_G4_mul2_G16_mul2_G256_inv0_1;
  _Bool temp_var_0_G4_mul2_G16_mul2_G256_inv0_2;
  _Bool temp_var_1_G4_mul2_G16_mul2_G256_inv0_0;
  _Bool temp_var_1_G4_mul2_G16_mul2_G256_inv0_1;
  _Bool temp_var_1_G4_mul2_G16_mul2_G256_inv0_2;
  i256_tx0_G256_inv0_0 = sb_y4_0 ^ sb_y0_0;
  i256_tx0_G256_inv0_1 = sb_y4_1 ^ sb_y0_1;
  i256_tx0_G256_inv0_2 = sb_y4_2 ^ sb_y0_2;
  i256_tx1_G256_inv0_0 = sb_y5_0 ^ sb_y1_0;
  i256_tx1_G256_inv0_1 = sb_y5_1 ^ sb_y1_1;
  i256_tx1_G256_inv0_2 = sb_y5_2 ^ sb_y1_2;
  i256_tx2_G256_inv0_0 = sb_y6_0 ^ sb_y2_0;
  i256_tx2_G256_inv0_1 = sb_y6_1 ^ sb_y2_1;
  i256_tx2_G256_inv0_2 = sb_y6_2 ^ sb_y2_2;
  i256_tx3_G256_inv0_0 = sb_y7_0 ^ sb_y3_0;
  i256_tx3_G256_inv0_1 = sb_y7_1 ^ sb_y3_1;
  i256_tx3_G256_inv0_2 = sb_y7_2 ^ sb_y3_2;
  ss16_tx0_G16_sq_scl0_G256_inv0_0 = i256_tx2_G256_inv0_0 ^ i256_tx0_G256_inv0_0;
  ss16_tx0_G16_sq_scl0_G256_inv0_1 = i256_tx2_G256_inv0_1 ^ i256_tx0_G256_inv0_1;
  ss16_tx0_G16_sq_scl0_G256_inv0_2 = i256_tx2_G256_inv0_2 ^ i256_tx0_G256_inv0_2;
  ss16_tx1_G16_sq_scl0_G256_inv0_0 = i256_tx3_G256_inv0_0 ^ i256_tx1_G256_inv0_0;
  ss16_tx1_G16_sq_scl0_G256_inv0_1 = i256_tx3_G256_inv0_1 ^ i256_tx1_G256_inv0_1;
  ss16_tx1_G16_sq_scl0_G256_inv0_2 = i256_tx3_G256_inv0_2 ^ i256_tx1_G256_inv0_2;
  ss16_ph1_G16_sq_scl0_G256_inv0_0 = ss16_tx0_G16_sq_scl0_G256_inv0_0;
  ss16_ph1_G16_sq_scl0_G256_inv0_1 = ss16_tx0_G16_sq_scl0_G256_inv0_1;
  ss16_ph1_G16_sq_scl0_G256_inv0_2 = ss16_tx0_G16_sq_scl0_G256_inv0_2;
  ss16_ph0_G16_sq_scl0_G256_inv0_0 = ss16_tx1_G16_sq_scl0_G256_inv0_0;
  ss16_ph0_G16_sq_scl0_G256_inv0_1 = ss16_tx1_G16_sq_scl0_G256_inv0_1;
  ss16_ph0_G16_sq_scl0_G256_inv0_2 = ss16_tx1_G16_sq_scl0_G256_inv0_2;
  ss16_ql1_s1_G16_sq_scl0_G256_inv0_0 = i256_tx0_G256_inv0_0;
  ss16_ql1_s1_G16_sq_scl0_G256_inv0_1 = i256_tx0_G256_inv0_1;
  ss16_ql1_s1_G16_sq_scl0_G256_inv0_2 = i256_tx0_G256_inv0_2;
  ss16_ql0_s1_G16_sq_scl0_G256_inv0_0 = i256_tx1_G256_inv0_0;
  ss16_ql0_s1_G16_sq_scl0_G256_inv0_1 = i256_tx1_G256_inv0_1;
  ss16_ql0_s1_G16_sq_scl0_G256_inv0_2 = i256_tx1_G256_inv0_2;
  ss16_ql1_s2_G16_sq_scl0_G256_inv0_0 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_0 ^ ss16_ql0_s1_G16_sq_scl0_G256_inv0_0;
  ss16_ql1_s2_G16_sq_scl0_G256_inv0_1 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_1 ^ ss16_ql0_s1_G16_sq_scl0_G256_inv0_1;
  ss16_ql1_s2_G16_sq_scl0_G256_inv0_2 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_2 ^ ss16_ql0_s1_G16_sq_scl0_G256_inv0_2;
  ss16_ql0_s2_G16_sq_scl0_G256_inv0_0 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_0;
  ss16_ql0_s2_G16_sq_scl0_G256_inv0_1 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_1;
  ss16_ql0_s2_G16_sq_scl0_G256_inv0_2 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_2;
  i256_c3_G256_inv0_0 = ss16_ph1_G16_sq_scl0_G256_inv0_0;
  i256_c3_G256_inv0_1 = ss16_ph1_G16_sq_scl0_G256_inv0_1;
  i256_c3_G256_inv0_2 = ss16_ph1_G16_sq_scl0_G256_inv0_2;
  i256_c2_G256_inv0_0 = ss16_ph0_G16_sq_scl0_G256_inv0_0;
  i256_c2_G256_inv0_1 = ss16_ph0_G16_sq_scl0_G256_inv0_1;
  i256_c2_G256_inv0_2 = ss16_ph0_G16_sq_scl0_G256_inv0_2;
  i256_c1_G256_inv0_0 = ss16_ql1_s2_G16_sq_scl0_G256_inv0_0;
  i256_c1_G256_inv0_1 = ss16_ql1_s2_G16_sq_scl0_G256_inv0_1;
  i256_c1_G256_inv0_2 = ss16_ql1_s2_G16_sq_scl0_G256_inv0_2;
  i256_c0_G256_inv0_0 = ss16_ql0_s2_G16_sq_scl0_G256_inv0_0;
  i256_c0_G256_inv0_1 = ss16_ql0_s2_G16_sq_scl0_G256_inv0_1;
  i256_c0_G256_inv0_2 = ss16_ql0_s2_G16_sq_scl0_G256_inv0_2;
  m16_tx0_G16_mul0_G256_inv0_0 = sb_y6_0 ^ sb_y4_0;
  m16_tx0_G16_mul0_G256_inv0_1 = sb_y6_1 ^ sb_y4_1;
  m16_tx0_G16_mul0_G256_inv0_2 = sb_y6_2 ^ sb_y4_2;
  m16_tx1_G16_mul0_G256_inv0_0 = sb_y7_0 ^ sb_y5_0;
  m16_tx1_G16_mul0_G256_inv0_1 = sb_y7_1 ^ sb_y5_1;
  m16_tx1_G16_mul0_G256_inv0_2 = sb_y7_2 ^ sb_y5_2;
  m16_ty0_G16_mul0_G256_inv0_0 = sb_y2_0 ^ sb_y0_0;
  m16_ty0_G16_mul0_G256_inv0_1 = sb_y2_1 ^ sb_y0_1;
  m16_ty0_G16_mul0_G256_inv0_2 = sb_y2_2 ^ sb_y0_2;
  m16_ty1_G16_mul0_G256_inv0_0 = sb_y3_0 ^ sb_y1_0;
  m16_ty1_G16_mul0_G256_inv0_1 = sb_y3_1 ^ sb_y1_1;
  m16_ty1_G16_mul0_G256_inv0_2 = sb_y3_2 ^ sb_y1_2;
  m4_ab_G4_mul0_G16_mul0_G256_inv0_0 = m16_tx1_G16_mul0_G256_inv0_0 ^ m16_tx0_G16_mul0_G256_inv0_0;
  m4_ab_G4_mul0_G16_mul0_G256_inv0_1 = m16_tx1_G16_mul0_G256_inv0_1 ^ m16_tx0_G16_mul0_G256_inv0_1;
  m4_ab_G4_mul0_G16_mul0_G256_inv0_2 = m16_tx1_G16_mul0_G256_inv0_2 ^ m16_tx0_G16_mul0_G256_inv0_2;
  m4_cd_G4_mul0_G16_mul0_G256_inv0_0 = m16_ty1_G16_mul0_G256_inv0_0 ^ m16_ty0_G16_mul0_G256_inv0_0;
  m4_cd_G4_mul0_G16_mul0_G256_inv0_1 = m16_ty1_G16_mul0_G256_inv0_1 ^ m16_ty0_G16_mul0_G256_inv0_1;
  m4_cd_G4_mul0_G16_mul0_G256_inv0_2 = m16_ty1_G16_mul0_G256_inv0_2 ^ m16_ty0_G16_mul0_G256_inv0_2;
  HPC3(m4_ab_G4_mul0_G16_mul0_G256_inv0_0, m4_ab_G4_mul0_G16_mul0_G256_inv0_1, m4_ab_G4_mul0_G16_mul0_G256_inv0_2, m4_cd_G4_mul0_G16_mul0_G256_inv0_0, m4_cd_G4_mul0_G16_mul0_G256_inv0_1, m4_cd_G4_mul0_G16_mul0_G256_inv0_2, &m4_e_G4_mul0_G16_mul0_G256_inv0_0, &m4_e_G4_mul0_G16_mul0_G256_inv0_1, &m4_e_G4_mul0_G16_mul0_G256_inv0_2, rand_1, rand_2, rand_3, rand_4, rand_5, rand_6);
  HPC3(m16_tx1_G16_mul0_G256_inv0_0, m16_tx1_G16_mul0_G256_inv0_1, m16_tx1_G16_mul0_G256_inv0_2, m16_ty1_G16_mul0_G256_inv0_0, m16_ty1_G16_mul0_G256_inv0_1, m16_ty1_G16_mul0_G256_inv0_2, &temp_var_0_G4_mul0_G16_mul0_G256_inv0_0, &temp_var_0_G4_mul0_G16_mul0_G256_inv0_1, &temp_var_0_G4_mul0_G16_mul0_G256_inv0_2, rand_7, rand_8, rand_9, rand_10, rand_11, rand_12);
  m16_e1_s1_G16_mul0_G256_inv0_0 = temp_var_0_G4_mul0_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_0;
  m16_e1_s1_G16_mul0_G256_inv0_1 = temp_var_0_G4_mul0_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_1;
  m16_e1_s1_G16_mul0_G256_inv0_2 = temp_var_0_G4_mul0_G16_mul0_G256_inv0_2 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_2;
  HPC3(m16_tx0_G16_mul0_G256_inv0_0, m16_tx0_G16_mul0_G256_inv0_1, m16_tx0_G16_mul0_G256_inv0_2, m16_ty0_G16_mul0_G256_inv0_0, m16_ty0_G16_mul0_G256_inv0_1, m16_ty0_G16_mul0_G256_inv0_2, &temp_var_1_G4_mul0_G16_mul0_G256_inv0_0, &temp_var_1_G4_mul0_G16_mul0_G256_inv0_1, &temp_var_1_G4_mul0_G16_mul0_G256_inv0_2, rand_13, rand_14, rand_15, rand_16, rand_17, rand_18);
  m16_e0_s1_G16_mul0_G256_inv0_0 = temp_var_1_G4_mul0_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_0;
  m16_e0_s1_G16_mul0_G256_inv0_1 = temp_var_1_G4_mul0_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_1;
  m16_e0_s1_G16_mul0_G256_inv0_2 = temp_var_1_G4_mul0_G16_mul0_G256_inv0_2 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_2;
  m16_e1_s2_G16_mul0_G256_inv0_0 = m16_e0_s1_G16_mul0_G256_inv0_0;
  m16_e1_s2_G16_mul0_G256_inv0_1 = m16_e0_s1_G16_mul0_G256_inv0_1;
  m16_e1_s2_G16_mul0_G256_inv0_2 = m16_e0_s1_G16_mul0_G256_inv0_2;
  m16_e0_s2_G16_mul0_G256_inv0_0 = m16_e1_s1_G16_mul0_G256_inv0_0 ^ m16_e0_s1_G16_mul0_G256_inv0_0;
  m16_e0_s2_G16_mul0_G256_inv0_1 = m16_e1_s1_G16_mul0_G256_inv0_1 ^ m16_e0_s1_G16_mul0_G256_inv0_1;
  m16_e0_s2_G16_mul0_G256_inv0_2 = m16_e1_s1_G16_mul0_G256_inv0_2 ^ m16_e0_s1_G16_mul0_G256_inv0_2;
  m4_ab_G4_mul1_G16_mul0_G256_inv0_0 = sb_y7_0 ^ sb_y6_0;
  m4_ab_G4_mul1_G16_mul0_G256_inv0_1 = sb_y7_1 ^ sb_y6_1;
  m4_ab_G4_mul1_G16_mul0_G256_inv0_2 = sb_y7_2 ^ sb_y6_2;
  m4_cd_G4_mul1_G16_mul0_G256_inv0_0 = sb_y3_0 ^ sb_y2_0;
  m4_cd_G4_mul1_G16_mul0_G256_inv0_1 = sb_y3_1 ^ sb_y2_1;
  m4_cd_G4_mul1_G16_mul0_G256_inv0_2 = sb_y3_2 ^ sb_y2_2;
  HPC3(m4_ab_G4_mul1_G16_mul0_G256_inv0_0, m4_ab_G4_mul1_G16_mul0_G256_inv0_1, m4_ab_G4_mul1_G16_mul0_G256_inv0_2, m4_cd_G4_mul1_G16_mul0_G256_inv0_0, m4_cd_G4_mul1_G16_mul0_G256_inv0_1, m4_cd_G4_mul1_G16_mul0_G256_inv0_2, &m4_e_G4_mul1_G16_mul0_G256_inv0_0, &m4_e_G4_mul1_G16_mul0_G256_inv0_1, &m4_e_G4_mul1_G16_mul0_G256_inv0_2, rand_19, rand_20, rand_21, rand_22, rand_23, rand_24);
  HPC3(sb_y7_0, sb_y7_1, sb_y7_2, sb_y3_0, sb_y3_1, sb_y3_2, &temp_var_0_G4_mul1_G16_mul0_G256_inv0_0, &temp_var_0_G4_mul1_G16_mul0_G256_inv0_1, &temp_var_0_G4_mul1_G16_mul0_G256_inv0_2, rand_25, rand_26, rand_27, rand_28, rand_29, rand_30);
  m16_ph1_G16_mul0_G256_inv0_0 = temp_var_0_G4_mul1_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_0;
  m16_ph1_G16_mul0_G256_inv0_1 = temp_var_0_G4_mul1_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_1;
  m16_ph1_G16_mul0_G256_inv0_2 = temp_var_0_G4_mul1_G16_mul0_G256_inv0_2 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_2;
  HPC3(sb_y6_0, sb_y6_1, sb_y6_2, sb_y2_0, sb_y2_1, sb_y2_2, &temp_var_1_G4_mul1_G16_mul0_G256_inv0_0, &temp_var_1_G4_mul1_G16_mul0_G256_inv0_1, &temp_var_1_G4_mul1_G16_mul0_G256_inv0_2, rand_31, rand_32, rand_33, rand_34, rand_35, rand_36);
  m16_ph0_G16_mul0_G256_inv0_0 = temp_var_1_G4_mul1_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_0;
  m16_ph0_G16_mul0_G256_inv0_1 = temp_var_1_G4_mul1_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_1;
  m16_ph0_G16_mul0_G256_inv0_2 = temp_var_1_G4_mul1_G16_mul0_G256_inv0_2 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_2;
  m4_ab_G4_mul2_G16_mul0_G256_inv0_0 = sb_y5_0 ^ sb_y4_0;
  m4_ab_G4_mul2_G16_mul0_G256_inv0_1 = sb_y5_1 ^ sb_y4_1;
  m4_ab_G4_mul2_G16_mul0_G256_inv0_2 = sb_y5_2 ^ sb_y4_2;
  m4_cd_G4_mul2_G16_mul0_G256_inv0_0 = sb_y1_0 ^ sb_y0_0;
  m4_cd_G4_mul2_G16_mul0_G256_inv0_1 = sb_y1_1 ^ sb_y0_1;
  m4_cd_G4_mul2_G16_mul0_G256_inv0_2 = sb_y1_2 ^ sb_y0_2;
  HPC3(m4_ab_G4_mul2_G16_mul0_G256_inv0_0, m4_ab_G4_mul2_G16_mul0_G256_inv0_1, m4_ab_G4_mul2_G16_mul0_G256_inv0_2, m4_cd_G4_mul2_G16_mul0_G256_inv0_0, m4_cd_G4_mul2_G16_mul0_G256_inv0_1, m4_cd_G4_mul2_G16_mul0_G256_inv0_2, &m4_e_G4_mul2_G16_mul0_G256_inv0_0, &m4_e_G4_mul2_G16_mul0_G256_inv0_1, &m4_e_G4_mul2_G16_mul0_G256_inv0_2, rand_37, rand_38, rand_39, rand_40, rand_41, rand_42);
  HPC3(sb_y5_0, sb_y5_1, sb_y5_2, sb_y1_0, sb_y1_1, sb_y1_2, &temp_var_0_G4_mul2_G16_mul0_G256_inv0_0, &temp_var_0_G4_mul2_G16_mul0_G256_inv0_1, &temp_var_0_G4_mul2_G16_mul0_G256_inv0_2, rand_43, rand_44, rand_45, rand_46, rand_47, rand_48);
  m16_ql1_G16_mul0_G256_inv0_0 = temp_var_0_G4_mul2_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_0;
  m16_ql1_G16_mul0_G256_inv0_1 = temp_var_0_G4_mul2_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_1;
  m16_ql1_G16_mul0_G256_inv0_2 = temp_var_0_G4_mul2_G16_mul0_G256_inv0_2 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_2;
  HPC3(sb_y4_0, sb_y4_1, sb_y4_2, sb_y0_0, sb_y0_1, sb_y0_2, &temp_var_1_G4_mul2_G16_mul0_G256_inv0_0, &temp_var_1_G4_mul2_G16_mul0_G256_inv0_1, &temp_var_1_G4_mul2_G16_mul0_G256_inv0_2, rand_49, rand_50, rand_51, rand_52, rand_53, rand_54);
  m16_ql0_G16_mul0_G256_inv0_0 = temp_var_1_G4_mul2_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_0;
  m16_ql0_G16_mul0_G256_inv0_1 = temp_var_1_G4_mul2_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_1;
  m16_ql0_G16_mul0_G256_inv0_2 = temp_var_1_G4_mul2_G16_mul0_G256_inv0_2 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_2;
  i256_d3_G256_inv0_0 = m16_ph1_G16_mul0_G256_inv0_0 ^ m16_e1_s2_G16_mul0_G256_inv0_0;
  i256_d3_G256_inv0_1 = m16_ph1_G16_mul0_G256_inv0_1 ^ m16_e1_s2_G16_mul0_G256_inv0_1;
  i256_d3_G256_inv0_2 = m16_ph1_G16_mul0_G256_inv0_2 ^ m16_e1_s2_G16_mul0_G256_inv0_2;
  i256_d2_G256_inv0_0 = m16_ph0_G16_mul0_G256_inv0_0 ^ m16_e0_s2_G16_mul0_G256_inv0_0;
  i256_d2_G256_inv0_1 = m16_ph0_G16_mul0_G256_inv0_1 ^ m16_e0_s2_G16_mul0_G256_inv0_1;
  i256_d2_G256_inv0_2 = m16_ph0_G16_mul0_G256_inv0_2 ^ m16_e0_s2_G16_mul0_G256_inv0_2;
  i256_d1_G256_inv0_0 = m16_ql1_G16_mul0_G256_inv0_0 ^ m16_e1_s2_G16_mul0_G256_inv0_0;
  i256_d1_G256_inv0_1 = m16_ql1_G16_mul0_G256_inv0_1 ^ m16_e1_s2_G16_mul0_G256_inv0_1;
  i256_d1_G256_inv0_2 = m16_ql1_G16_mul0_G256_inv0_2 ^ m16_e1_s2_G16_mul0_G256_inv0_2;
  i256_d0_G256_inv0_0 = m16_ql0_G16_mul0_G256_inv0_0 ^ m16_e0_s2_G16_mul0_G256_inv0_0;
  i256_d0_G256_inv0_1 = m16_ql0_G16_mul0_G256_inv0_1 ^ m16_e0_s2_G16_mul0_G256_inv0_1;
  i256_d0_G256_inv0_2 = m16_ql0_G16_mul0_G256_inv0_2 ^ m16_e0_s2_G16_mul0_G256_inv0_2;
  i256_te0_G256_inv0_0 = i256_c0_G256_inv0_0 ^ i256_d0_G256_inv0_0;
  i256_te0_G256_inv0_1 = i256_c0_G256_inv0_1 ^ i256_d0_G256_inv0_1;
  i256_te0_G256_inv0_2 = i256_c0_G256_inv0_2 ^ i256_d0_G256_inv0_2;
  i256_te1_G256_inv0_0 = i256_c1_G256_inv0_0 ^ i256_d1_G256_inv0_0;
  i256_te1_G256_inv0_1 = i256_c1_G256_inv0_1 ^ i256_d1_G256_inv0_1;
  i256_te1_G256_inv0_2 = i256_c1_G256_inv0_2 ^ i256_d1_G256_inv0_2;
  i256_te2_G256_inv0_0 = i256_c2_G256_inv0_0 ^ i256_d2_G256_inv0_0;
  i256_te2_G256_inv0_1 = i256_c2_G256_inv0_1 ^ i256_d2_G256_inv0_1;
  i256_te2_G256_inv0_2 = i256_c2_G256_inv0_2 ^ i256_d2_G256_inv0_2;
  i256_te3_G256_inv0_0 = i256_c3_G256_inv0_0 ^ i256_d3_G256_inv0_0;
  i256_te3_G256_inv0_1 = i256_c3_G256_inv0_1 ^ i256_d3_G256_inv0_1;
  i256_te3_G256_inv0_2 = i256_c3_G256_inv0_2 ^ i256_d3_G256_inv0_2;
  i16_tx0_G16_inv0_G256_inv0_0 = i256_te2_G256_inv0_0 ^ i256_te0_G256_inv0_0;
  i16_tx0_G16_inv0_G256_inv0_1 = i256_te2_G256_inv0_1 ^ i256_te0_G256_inv0_1;
  i16_tx0_G16_inv0_G256_inv0_2 = i256_te2_G256_inv0_2 ^ i256_te0_G256_inv0_2;
  i16_tx1_G16_inv0_G256_inv0_0 = i256_te3_G256_inv0_0 ^ i256_te1_G256_inv0_0;
  i16_tx1_G16_inv0_G256_inv0_1 = i256_te3_G256_inv0_1 ^ i256_te1_G256_inv0_1;
  i16_tx1_G16_inv0_G256_inv0_2 = i256_te3_G256_inv0_2 ^ i256_te1_G256_inv0_2;
  i16_c1_s1_G16_inv0_G256_inv0_0 = i16_tx0_G16_inv0_G256_inv0_0;
  i16_c1_s1_G16_inv0_G256_inv0_1 = i16_tx0_G16_inv0_G256_inv0_1;
  i16_c1_s1_G16_inv0_G256_inv0_2 = i16_tx0_G16_inv0_G256_inv0_2;
  i16_c0_s1_G16_inv0_G256_inv0_0 = i16_tx1_G16_inv0_G256_inv0_0;
  i16_c0_s1_G16_inv0_G256_inv0_1 = i16_tx1_G16_inv0_G256_inv0_1;
  i16_c0_s1_G16_inv0_G256_inv0_2 = i16_tx1_G16_inv0_G256_inv0_2;
  i16_c1_s2_G16_inv0_G256_inv0_0 = i16_c0_s1_G16_inv0_G256_inv0_0;
  i16_c1_s2_G16_inv0_G256_inv0_1 = i16_c0_s1_G16_inv0_G256_inv0_1;
  i16_c1_s2_G16_inv0_G256_inv0_2 = i16_c0_s1_G16_inv0_G256_inv0_2;
  i16_c0_s2_G16_inv0_G256_inv0_0 = i16_c1_s1_G16_inv0_G256_inv0_0 ^ i16_c0_s1_G16_inv0_G256_inv0_0;
  i16_c0_s2_G16_inv0_G256_inv0_1 = i16_c1_s1_G16_inv0_G256_inv0_1 ^ i16_c0_s1_G16_inv0_G256_inv0_1;
  i16_c0_s2_G16_inv0_G256_inv0_2 = i16_c1_s1_G16_inv0_G256_inv0_2 ^ i16_c0_s1_G16_inv0_G256_inv0_2;
  m4_ab_G4_mul3_G16_inv0_G256_inv0_0 = i256_te3_G256_inv0_0 ^ i256_te2_G256_inv0_0;
  m4_ab_G4_mul3_G16_inv0_G256_inv0_1 = i256_te3_G256_inv0_1 ^ i256_te2_G256_inv0_1;
  m4_ab_G4_mul3_G16_inv0_G256_inv0_2 = i256_te3_G256_inv0_2 ^ i256_te2_G256_inv0_2;
  m4_cd_G4_mul3_G16_inv0_G256_inv0_0 = i256_te1_G256_inv0_0 ^ i256_te0_G256_inv0_0;
  m4_cd_G4_mul3_G16_inv0_G256_inv0_1 = i256_te1_G256_inv0_1 ^ i256_te0_G256_inv0_1;
  m4_cd_G4_mul3_G16_inv0_G256_inv0_2 = i256_te1_G256_inv0_2 ^ i256_te0_G256_inv0_2;
  HPC3(m4_ab_G4_mul3_G16_inv0_G256_inv0_0, m4_ab_G4_mul3_G16_inv0_G256_inv0_1, m4_ab_G4_mul3_G16_inv0_G256_inv0_2, m4_cd_G4_mul3_G16_inv0_G256_inv0_0, m4_cd_G4_mul3_G16_inv0_G256_inv0_1, m4_cd_G4_mul3_G16_inv0_G256_inv0_2, &m4_e_G4_mul3_G16_inv0_G256_inv0_0, &m4_e_G4_mul3_G16_inv0_G256_inv0_1, &m4_e_G4_mul3_G16_inv0_G256_inv0_2, rand_55, rand_56, rand_57, rand_58, rand_59, rand_60);
  HPC3(i256_te3_G256_inv0_0, i256_te3_G256_inv0_1, i256_te3_G256_inv0_2, i256_te1_G256_inv0_0, i256_te1_G256_inv0_1, i256_te1_G256_inv0_2, &temp_var_0_G4_mul3_G16_inv0_G256_inv0_0, &temp_var_0_G4_mul3_G16_inv0_G256_inv0_1, &temp_var_0_G4_mul3_G16_inv0_G256_inv0_2, rand_61, rand_62, rand_63, rand_64, rand_65, rand_66);
  i16_d1_G16_inv0_G256_inv0_0 = temp_var_0_G4_mul3_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_0;
  i16_d1_G16_inv0_G256_inv0_1 = temp_var_0_G4_mul3_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_1;
  i16_d1_G16_inv0_G256_inv0_2 = temp_var_0_G4_mul3_G16_inv0_G256_inv0_2 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_2;
  HPC3(i256_te2_G256_inv0_0, i256_te2_G256_inv0_1, i256_te2_G256_inv0_2, i256_te0_G256_inv0_0, i256_te0_G256_inv0_1, i256_te0_G256_inv0_2, &temp_var_1_G4_mul3_G16_inv0_G256_inv0_0, &temp_var_1_G4_mul3_G16_inv0_G256_inv0_1, &temp_var_1_G4_mul3_G16_inv0_G256_inv0_2, rand_67, rand_68, rand_69, rand_70, rand_71, rand_72);
  i16_d0_G16_inv0_G256_inv0_0 = temp_var_1_G4_mul3_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_0;
  i16_d0_G16_inv0_G256_inv0_1 = temp_var_1_G4_mul3_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_1;
  i16_d0_G16_inv0_G256_inv0_2 = temp_var_1_G4_mul3_G16_inv0_G256_inv0_2 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_2;
  i16_te0_G16_inv0_G256_inv0_0 = i16_c0_s2_G16_inv0_G256_inv0_0 ^ i16_d0_G16_inv0_G256_inv0_0;
  i16_te0_G16_inv0_G256_inv0_1 = i16_c0_s2_G16_inv0_G256_inv0_1 ^ i16_d0_G16_inv0_G256_inv0_1;
  i16_te0_G16_inv0_G256_inv0_2 = i16_c0_s2_G16_inv0_G256_inv0_2 ^ i16_d0_G16_inv0_G256_inv0_2;
  i16_te1_G16_inv0_G256_inv0_0 = i16_c1_s2_G16_inv0_G256_inv0_0 ^ i16_d1_G16_inv0_G256_inv0_0;
  i16_te1_G16_inv0_G256_inv0_1 = i16_c1_s2_G16_inv0_G256_inv0_1 ^ i16_d1_G16_inv0_G256_inv0_1;
  i16_te1_G16_inv0_G256_inv0_2 = i16_c1_s2_G16_inv0_G256_inv0_2 ^ i16_d1_G16_inv0_G256_inv0_2;
  i16_e1_G16_inv0_G256_inv0_0 = i16_te0_G16_inv0_G256_inv0_0;
  i16_e1_G16_inv0_G256_inv0_1 = i16_te0_G16_inv0_G256_inv0_1;
  i16_e1_G16_inv0_G256_inv0_2 = i16_te0_G16_inv0_G256_inv0_2;
  i16_e0_G16_inv0_G256_inv0_0 = i16_te1_G16_inv0_G256_inv0_0;
  i16_e0_G16_inv0_G256_inv0_1 = i16_te1_G16_inv0_G256_inv0_1;
  i16_e0_G16_inv0_G256_inv0_2 = i16_te1_G16_inv0_G256_inv0_2;
  m4_ab_G4_mul4_G16_inv0_G256_inv0_0 = i16_e1_G16_inv0_G256_inv0_0 ^ i16_e0_G16_inv0_G256_inv0_0;
  m4_ab_G4_mul4_G16_inv0_G256_inv0_1 = i16_e1_G16_inv0_G256_inv0_1 ^ i16_e0_G16_inv0_G256_inv0_1;
  m4_ab_G4_mul4_G16_inv0_G256_inv0_2 = i16_e1_G16_inv0_G256_inv0_2 ^ i16_e0_G16_inv0_G256_inv0_2;
  m4_cd_G4_mul4_G16_inv0_G256_inv0_0 = i256_te1_G256_inv0_0 ^ i256_te0_G256_inv0_0;
  m4_cd_G4_mul4_G16_inv0_G256_inv0_1 = i256_te1_G256_inv0_1 ^ i256_te0_G256_inv0_1;
  m4_cd_G4_mul4_G16_inv0_G256_inv0_2 = i256_te1_G256_inv0_2 ^ i256_te0_G256_inv0_2;
  HPC2(m4_ab_G4_mul4_G16_inv0_G256_inv0_0, m4_ab_G4_mul4_G16_inv0_G256_inv0_1, m4_ab_G4_mul4_G16_inv0_G256_inv0_2, m4_cd_G4_mul4_G16_inv0_G256_inv0_0, m4_cd_G4_mul4_G16_inv0_G256_inv0_1, m4_cd_G4_mul4_G16_inv0_G256_inv0_2, &m4_e_G4_mul4_G16_inv0_G256_inv0_0, &m4_e_G4_mul4_G16_inv0_G256_inv0_1, &m4_e_G4_mul4_G16_inv0_G256_inv0_2, rand_73, rand_74, rand_75);
  HPC2(i16_e1_G16_inv0_G256_inv0_0, i16_e1_G16_inv0_G256_inv0_1, i16_e1_G16_inv0_G256_inv0_2, i256_te1_G256_inv0_0, i256_te1_G256_inv0_1, i256_te1_G256_inv0_2, &temp_var_0_G4_mul4_G16_inv0_G256_inv0_0, &temp_var_0_G4_mul4_G16_inv0_G256_inv0_1, &temp_var_0_G4_mul4_G16_inv0_G256_inv0_2, rand_76, rand_77, rand_78);
  i16_ph1_G16_inv0_G256_inv0_0 = temp_var_0_G4_mul4_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_0;
  i16_ph1_G16_inv0_G256_inv0_1 = temp_var_0_G4_mul4_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_1;
  i16_ph1_G16_inv0_G256_inv0_2 = temp_var_0_G4_mul4_G16_inv0_G256_inv0_2 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_2;
  HPC2(i16_e0_G16_inv0_G256_inv0_0, i16_e0_G16_inv0_G256_inv0_1, i16_e0_G16_inv0_G256_inv0_2, i256_te0_G256_inv0_0, i256_te0_G256_inv0_1, i256_te0_G256_inv0_2, &temp_var_1_G4_mul4_G16_inv0_G256_inv0_0, &temp_var_1_G4_mul4_G16_inv0_G256_inv0_1, &temp_var_1_G4_mul4_G16_inv0_G256_inv0_2, rand_79, rand_80, rand_81);
  i16_ph0_G16_inv0_G256_inv0_0 = temp_var_1_G4_mul4_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_0;
  i16_ph0_G16_inv0_G256_inv0_1 = temp_var_1_G4_mul4_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_1;
  i16_ph0_G16_inv0_G256_inv0_2 = temp_var_1_G4_mul4_G16_inv0_G256_inv0_2 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_2;
  m4_ab_G4_mul5_G16_inv0_G256_inv0_0 = i16_e1_G16_inv0_G256_inv0_0 ^ i16_e0_G16_inv0_G256_inv0_0;
  m4_ab_G4_mul5_G16_inv0_G256_inv0_1 = i16_e1_G16_inv0_G256_inv0_1 ^ i16_e0_G16_inv0_G256_inv0_1;
  m4_ab_G4_mul5_G16_inv0_G256_inv0_2 = i16_e1_G16_inv0_G256_inv0_2 ^ i16_e0_G16_inv0_G256_inv0_2;
  m4_cd_G4_mul5_G16_inv0_G256_inv0_0 = i256_te3_G256_inv0_0 ^ i256_te2_G256_inv0_0;
  m4_cd_G4_mul5_G16_inv0_G256_inv0_1 = i256_te3_G256_inv0_1 ^ i256_te2_G256_inv0_1;
  m4_cd_G4_mul5_G16_inv0_G256_inv0_2 = i256_te3_G256_inv0_2 ^ i256_te2_G256_inv0_2;
  HPC2(m4_ab_G4_mul5_G16_inv0_G256_inv0_0, m4_ab_G4_mul5_G16_inv0_G256_inv0_1, m4_ab_G4_mul5_G16_inv0_G256_inv0_2, m4_cd_G4_mul5_G16_inv0_G256_inv0_0, m4_cd_G4_mul5_G16_inv0_G256_inv0_1, m4_cd_G4_mul5_G16_inv0_G256_inv0_2, &m4_e_G4_mul5_G16_inv0_G256_inv0_0, &m4_e_G4_mul5_G16_inv0_G256_inv0_1, &m4_e_G4_mul5_G16_inv0_G256_inv0_2, rand_82, rand_83, rand_84);
  HPC2(i16_e1_G16_inv0_G256_inv0_0, i16_e1_G16_inv0_G256_inv0_1, i16_e1_G16_inv0_G256_inv0_2, i256_te3_G256_inv0_0, i256_te3_G256_inv0_1, i256_te3_G256_inv0_2, &temp_var_0_G4_mul5_G16_inv0_G256_inv0_0, &temp_var_0_G4_mul5_G16_inv0_G256_inv0_1, &temp_var_0_G4_mul5_G16_inv0_G256_inv0_2, rand_85, rand_86, rand_87);
  i16_ql1_G16_inv0_G256_inv0_0 = temp_var_0_G4_mul5_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_0;
  i16_ql1_G16_inv0_G256_inv0_1 = temp_var_0_G4_mul5_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_1;
  i16_ql1_G16_inv0_G256_inv0_2 = temp_var_0_G4_mul5_G16_inv0_G256_inv0_2 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_2;
  HPC2(i16_e0_G16_inv0_G256_inv0_0, i16_e0_G16_inv0_G256_inv0_1, i16_e0_G16_inv0_G256_inv0_2, i256_te2_G256_inv0_0, i256_te2_G256_inv0_1, i256_te2_G256_inv0_2, &temp_var_1_G4_mul5_G16_inv0_G256_inv0_0, &temp_var_1_G4_mul5_G16_inv0_G256_inv0_1, &temp_var_1_G4_mul5_G16_inv0_G256_inv0_2, rand_88, rand_89, rand_90);
  i16_ql0_G16_inv0_G256_inv0_0 = temp_var_1_G4_mul5_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_0;
  i16_ql0_G16_inv0_G256_inv0_1 = temp_var_1_G4_mul5_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_1;
  i16_ql0_G16_inv0_G256_inv0_2 = temp_var_1_G4_mul5_G16_inv0_G256_inv0_2 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_2;
  i256_e3_G256_inv0_0 = i16_ph1_G16_inv0_G256_inv0_0;
  i256_e3_G256_inv0_1 = i16_ph1_G16_inv0_G256_inv0_1;
  i256_e3_G256_inv0_2 = i16_ph1_G16_inv0_G256_inv0_2;
  i256_e2_G256_inv0_0 = i16_ph0_G16_inv0_G256_inv0_0;
  i256_e2_G256_inv0_1 = i16_ph0_G16_inv0_G256_inv0_1;
  i256_e2_G256_inv0_2 = i16_ph0_G16_inv0_G256_inv0_2;
  i256_e1_G256_inv0_0 = i16_ql1_G16_inv0_G256_inv0_0;
  i256_e1_G256_inv0_1 = i16_ql1_G16_inv0_G256_inv0_1;
  i256_e1_G256_inv0_2 = i16_ql1_G16_inv0_G256_inv0_2;
  i256_e0_G256_inv0_0 = i16_ql0_G16_inv0_G256_inv0_0;
  i256_e0_G256_inv0_1 = i16_ql0_G16_inv0_G256_inv0_1;
  i256_e0_G256_inv0_2 = i16_ql0_G16_inv0_G256_inv0_2;
  m16_tx0_G16_mul1_G256_inv0_0 = i256_e2_G256_inv0_0 ^ i256_e0_G256_inv0_0;
  m16_tx0_G16_mul1_G256_inv0_1 = i256_e2_G256_inv0_1 ^ i256_e0_G256_inv0_1;
  m16_tx0_G16_mul1_G256_inv0_2 = i256_e2_G256_inv0_2 ^ i256_e0_G256_inv0_2;
  m16_tx1_G16_mul1_G256_inv0_0 = i256_e3_G256_inv0_0 ^ i256_e1_G256_inv0_0;
  m16_tx1_G16_mul1_G256_inv0_1 = i256_e3_G256_inv0_1 ^ i256_e1_G256_inv0_1;
  m16_tx1_G16_mul1_G256_inv0_2 = i256_e3_G256_inv0_2 ^ i256_e1_G256_inv0_2;
  m16_ty0_G16_mul1_G256_inv0_0 = sb_y2_0 ^ sb_y0_0;
  m16_ty0_G16_mul1_G256_inv0_1 = sb_y2_1 ^ sb_y0_1;
  m16_ty0_G16_mul1_G256_inv0_2 = sb_y2_2 ^ sb_y0_2;
  m16_ty1_G16_mul1_G256_inv0_0 = sb_y3_0 ^ sb_y1_0;
  m16_ty1_G16_mul1_G256_inv0_1 = sb_y3_1 ^ sb_y1_1;
  m16_ty1_G16_mul1_G256_inv0_2 = sb_y3_2 ^ sb_y1_2;
  m4_ab_G4_mul0_G16_mul1_G256_inv0_0 = m16_tx1_G16_mul1_G256_inv0_0 ^ m16_tx0_G16_mul1_G256_inv0_0;
  m4_ab_G4_mul0_G16_mul1_G256_inv0_1 = m16_tx1_G16_mul1_G256_inv0_1 ^ m16_tx0_G16_mul1_G256_inv0_1;
  m4_ab_G4_mul0_G16_mul1_G256_inv0_2 = m16_tx1_G16_mul1_G256_inv0_2 ^ m16_tx0_G16_mul1_G256_inv0_2;
  m4_cd_G4_mul0_G16_mul1_G256_inv0_0 = m16_ty1_G16_mul1_G256_inv0_0 ^ m16_ty0_G16_mul1_G256_inv0_0;
  m4_cd_G4_mul0_G16_mul1_G256_inv0_1 = m16_ty1_G16_mul1_G256_inv0_1 ^ m16_ty0_G16_mul1_G256_inv0_1;
  m4_cd_G4_mul0_G16_mul1_G256_inv0_2 = m16_ty1_G16_mul1_G256_inv0_2 ^ m16_ty0_G16_mul1_G256_inv0_2;
  HPC2(m4_ab_G4_mul0_G16_mul1_G256_inv0_0, m4_ab_G4_mul0_G16_mul1_G256_inv0_1, m4_ab_G4_mul0_G16_mul1_G256_inv0_2, m4_cd_G4_mul0_G16_mul1_G256_inv0_0, m4_cd_G4_mul0_G16_mul1_G256_inv0_1, m4_cd_G4_mul0_G16_mul1_G256_inv0_2, &m4_e_G4_mul0_G16_mul1_G256_inv0_0, &m4_e_G4_mul0_G16_mul1_G256_inv0_1, &m4_e_G4_mul0_G16_mul1_G256_inv0_2, rand_91, rand_92, rand_93);
  HPC2(m16_tx1_G16_mul1_G256_inv0_0, m16_tx1_G16_mul1_G256_inv0_1, m16_tx1_G16_mul1_G256_inv0_2, m16_ty1_G16_mul1_G256_inv0_0, m16_ty1_G16_mul1_G256_inv0_1, m16_ty1_G16_mul1_G256_inv0_2, &temp_var_0_G4_mul0_G16_mul1_G256_inv0_0, &temp_var_0_G4_mul0_G16_mul1_G256_inv0_1, &temp_var_0_G4_mul0_G16_mul1_G256_inv0_2, rand_94, rand_95, rand_96);
  m16_e1_s1_G16_mul1_G256_inv0_0 = temp_var_0_G4_mul0_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_0;
  m16_e1_s1_G16_mul1_G256_inv0_1 = temp_var_0_G4_mul0_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_1;
  m16_e1_s1_G16_mul1_G256_inv0_2 = temp_var_0_G4_mul0_G16_mul1_G256_inv0_2 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_2;
  HPC2(m16_tx0_G16_mul1_G256_inv0_0, m16_tx0_G16_mul1_G256_inv0_1, m16_tx0_G16_mul1_G256_inv0_2, m16_ty0_G16_mul1_G256_inv0_0, m16_ty0_G16_mul1_G256_inv0_1, m16_ty0_G16_mul1_G256_inv0_2, &temp_var_1_G4_mul0_G16_mul1_G256_inv0_0, &temp_var_1_G4_mul0_G16_mul1_G256_inv0_1, &temp_var_1_G4_mul0_G16_mul1_G256_inv0_2, rand_97, rand_98, rand_99);
  m16_e0_s1_G16_mul1_G256_inv0_0 = temp_var_1_G4_mul0_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_0;
  m16_e0_s1_G16_mul1_G256_inv0_1 = temp_var_1_G4_mul0_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_1;
  m16_e0_s1_G16_mul1_G256_inv0_2 = temp_var_1_G4_mul0_G16_mul1_G256_inv0_2 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_2;
  m16_e1_s2_G16_mul1_G256_inv0_0 = m16_e0_s1_G16_mul1_G256_inv0_0;
  m16_e1_s2_G16_mul1_G256_inv0_1 = m16_e0_s1_G16_mul1_G256_inv0_1;
  m16_e1_s2_G16_mul1_G256_inv0_2 = m16_e0_s1_G16_mul1_G256_inv0_2;
  m16_e0_s2_G16_mul1_G256_inv0_0 = m16_e1_s1_G16_mul1_G256_inv0_0 ^ m16_e0_s1_G16_mul1_G256_inv0_0;
  m16_e0_s2_G16_mul1_G256_inv0_1 = m16_e1_s1_G16_mul1_G256_inv0_1 ^ m16_e0_s1_G16_mul1_G256_inv0_1;
  m16_e0_s2_G16_mul1_G256_inv0_2 = m16_e1_s1_G16_mul1_G256_inv0_2 ^ m16_e0_s1_G16_mul1_G256_inv0_2;
  m4_ab_G4_mul1_G16_mul1_G256_inv0_0 = i256_e3_G256_inv0_0 ^ i256_e2_G256_inv0_0;
  m4_ab_G4_mul1_G16_mul1_G256_inv0_1 = i256_e3_G256_inv0_1 ^ i256_e2_G256_inv0_1;
  m4_ab_G4_mul1_G16_mul1_G256_inv0_2 = i256_e3_G256_inv0_2 ^ i256_e2_G256_inv0_2;
  m4_cd_G4_mul1_G16_mul1_G256_inv0_0 = sb_y3_0 ^ sb_y2_0;
  m4_cd_G4_mul1_G16_mul1_G256_inv0_1 = sb_y3_1 ^ sb_y2_1;
  m4_cd_G4_mul1_G16_mul1_G256_inv0_2 = sb_y3_2 ^ sb_y2_2;
  HPC2(m4_ab_G4_mul1_G16_mul1_G256_inv0_0, m4_ab_G4_mul1_G16_mul1_G256_inv0_1, m4_ab_G4_mul1_G16_mul1_G256_inv0_2, m4_cd_G4_mul1_G16_mul1_G256_inv0_0, m4_cd_G4_mul1_G16_mul1_G256_inv0_1, m4_cd_G4_mul1_G16_mul1_G256_inv0_2, &m4_e_G4_mul1_G16_mul1_G256_inv0_0, &m4_e_G4_mul1_G16_mul1_G256_inv0_1, &m4_e_G4_mul1_G16_mul1_G256_inv0_2, rand_100, rand_101, rand_102);
  HPC2(i256_e3_G256_inv0_0, i256_e3_G256_inv0_1, i256_e3_G256_inv0_2, sb_y3_0, sb_y3_1, sb_y3_2, &temp_var_0_G4_mul1_G16_mul1_G256_inv0_0, &temp_var_0_G4_mul1_G16_mul1_G256_inv0_1, &temp_var_0_G4_mul1_G16_mul1_G256_inv0_2, rand_103, rand_104, rand_105);
  m16_ph1_G16_mul1_G256_inv0_0 = temp_var_0_G4_mul1_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_0;
  m16_ph1_G16_mul1_G256_inv0_1 = temp_var_0_G4_mul1_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_1;
  m16_ph1_G16_mul1_G256_inv0_2 = temp_var_0_G4_mul1_G16_mul1_G256_inv0_2 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_2;
  HPC2(i256_e2_G256_inv0_0, i256_e2_G256_inv0_1, i256_e2_G256_inv0_2, sb_y2_0, sb_y2_1, sb_y2_2, &temp_var_1_G4_mul1_G16_mul1_G256_inv0_0, &temp_var_1_G4_mul1_G16_mul1_G256_inv0_1, &temp_var_1_G4_mul1_G16_mul1_G256_inv0_2, rand_106, rand_107, rand_108);
  m16_ph0_G16_mul1_G256_inv0_0 = temp_var_1_G4_mul1_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_0;
  m16_ph0_G16_mul1_G256_inv0_1 = temp_var_1_G4_mul1_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_1;
  m16_ph0_G16_mul1_G256_inv0_2 = temp_var_1_G4_mul1_G16_mul1_G256_inv0_2 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_2;
  m4_ab_G4_mul2_G16_mul1_G256_inv0_0 = i256_e1_G256_inv0_0 ^ i256_e0_G256_inv0_0;
  m4_ab_G4_mul2_G16_mul1_G256_inv0_1 = i256_e1_G256_inv0_1 ^ i256_e0_G256_inv0_1;
  m4_ab_G4_mul2_G16_mul1_G256_inv0_2 = i256_e1_G256_inv0_2 ^ i256_e0_G256_inv0_2;
  m4_cd_G4_mul2_G16_mul1_G256_inv0_0 = sb_y1_0 ^ sb_y0_0;
  m4_cd_G4_mul2_G16_mul1_G256_inv0_1 = sb_y1_1 ^ sb_y0_1;
  m4_cd_G4_mul2_G16_mul1_G256_inv0_2 = sb_y1_2 ^ sb_y0_2;
  HPC2(m4_ab_G4_mul2_G16_mul1_G256_inv0_0, m4_ab_G4_mul2_G16_mul1_G256_inv0_1, m4_ab_G4_mul2_G16_mul1_G256_inv0_2, m4_cd_G4_mul2_G16_mul1_G256_inv0_0, m4_cd_G4_mul2_G16_mul1_G256_inv0_1, m4_cd_G4_mul2_G16_mul1_G256_inv0_2, &m4_e_G4_mul2_G16_mul1_G256_inv0_0, &m4_e_G4_mul2_G16_mul1_G256_inv0_1, &m4_e_G4_mul2_G16_mul1_G256_inv0_2, rand_109, rand_110, rand_111);
  HPC2(i256_e1_G256_inv0_0, i256_e1_G256_inv0_1, i256_e1_G256_inv0_2, sb_y1_0, sb_y1_1, sb_y1_2, &temp_var_0_G4_mul2_G16_mul1_G256_inv0_0, &temp_var_0_G4_mul2_G16_mul1_G256_inv0_1, &temp_var_0_G4_mul2_G16_mul1_G256_inv0_2, rand_112, rand_113, rand_114);
  m16_ql1_G16_mul1_G256_inv0_0 = temp_var_0_G4_mul2_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_0;
  m16_ql1_G16_mul1_G256_inv0_1 = temp_var_0_G4_mul2_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_1;
  m16_ql1_G16_mul1_G256_inv0_2 = temp_var_0_G4_mul2_G16_mul1_G256_inv0_2 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_2;
  HPC2(i256_e0_G256_inv0_0, i256_e0_G256_inv0_1, i256_e0_G256_inv0_2, sb_y0_0, sb_y0_1, sb_y0_2, &temp_var_1_G4_mul2_G16_mul1_G256_inv0_0, &temp_var_1_G4_mul2_G16_mul1_G256_inv0_1, &temp_var_1_G4_mul2_G16_mul1_G256_inv0_2, rand_115, rand_116, rand_117);
  m16_ql0_G16_mul1_G256_inv0_0 = temp_var_1_G4_mul2_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_0;
  m16_ql0_G16_mul1_G256_inv0_1 = temp_var_1_G4_mul2_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_1;
  m16_ql0_G16_mul1_G256_inv0_2 = temp_var_1_G4_mul2_G16_mul1_G256_inv0_2 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_2;
  i256_ph3_G256_inv0_0 = m16_ph1_G16_mul1_G256_inv0_0 ^ m16_e1_s2_G16_mul1_G256_inv0_0;
  i256_ph3_G256_inv0_1 = m16_ph1_G16_mul1_G256_inv0_1 ^ m16_e1_s2_G16_mul1_G256_inv0_1;
  i256_ph3_G256_inv0_2 = m16_ph1_G16_mul1_G256_inv0_2 ^ m16_e1_s2_G16_mul1_G256_inv0_2;
  i256_ph2_G256_inv0_0 = m16_ph0_G16_mul1_G256_inv0_0 ^ m16_e0_s2_G16_mul1_G256_inv0_0;
  i256_ph2_G256_inv0_1 = m16_ph0_G16_mul1_G256_inv0_1 ^ m16_e0_s2_G16_mul1_G256_inv0_1;
  i256_ph2_G256_inv0_2 = m16_ph0_G16_mul1_G256_inv0_2 ^ m16_e0_s2_G16_mul1_G256_inv0_2;
  i256_ph1_G256_inv0_0 = m16_ql1_G16_mul1_G256_inv0_0 ^ m16_e1_s2_G16_mul1_G256_inv0_0;
  i256_ph1_G256_inv0_1 = m16_ql1_G16_mul1_G256_inv0_1 ^ m16_e1_s2_G16_mul1_G256_inv0_1;
  i256_ph1_G256_inv0_2 = m16_ql1_G16_mul1_G256_inv0_2 ^ m16_e1_s2_G16_mul1_G256_inv0_2;
  i256_ph0_G256_inv0_0 = m16_ql0_G16_mul1_G256_inv0_0 ^ m16_e0_s2_G16_mul1_G256_inv0_0;
  i256_ph0_G256_inv0_1 = m16_ql0_G16_mul1_G256_inv0_1 ^ m16_e0_s2_G16_mul1_G256_inv0_1;
  i256_ph0_G256_inv0_2 = m16_ql0_G16_mul1_G256_inv0_2 ^ m16_e0_s2_G16_mul1_G256_inv0_2;
  m16_tx0_G16_mul2_G256_inv0_0 = i256_e2_G256_inv0_0 ^ i256_e0_G256_inv0_0;
  m16_tx0_G16_mul2_G256_inv0_1 = i256_e2_G256_inv0_1 ^ i256_e0_G256_inv0_1;
  m16_tx0_G16_mul2_G256_inv0_2 = i256_e2_G256_inv0_2 ^ i256_e0_G256_inv0_2;
  m16_tx1_G16_mul2_G256_inv0_0 = i256_e3_G256_inv0_0 ^ i256_e1_G256_inv0_0;
  m16_tx1_G16_mul2_G256_inv0_1 = i256_e3_G256_inv0_1 ^ i256_e1_G256_inv0_1;
  m16_tx1_G16_mul2_G256_inv0_2 = i256_e3_G256_inv0_2 ^ i256_e1_G256_inv0_2;
  m16_ty0_G16_mul2_G256_inv0_0 = sb_y6_0 ^ sb_y4_0;
  m16_ty0_G16_mul2_G256_inv0_1 = sb_y6_1 ^ sb_y4_1;
  m16_ty0_G16_mul2_G256_inv0_2 = sb_y6_2 ^ sb_y4_2;
  m16_ty1_G16_mul2_G256_inv0_0 = sb_y7_0 ^ sb_y5_0;
  m16_ty1_G16_mul2_G256_inv0_1 = sb_y7_1 ^ sb_y5_1;
  m16_ty1_G16_mul2_G256_inv0_2 = sb_y7_2 ^ sb_y5_2;
  m4_ab_G4_mul0_G16_mul2_G256_inv0_0 = m16_tx1_G16_mul2_G256_inv0_0 ^ m16_tx0_G16_mul2_G256_inv0_0;
  m4_ab_G4_mul0_G16_mul2_G256_inv0_1 = m16_tx1_G16_mul2_G256_inv0_1 ^ m16_tx0_G16_mul2_G256_inv0_1;
  m4_ab_G4_mul0_G16_mul2_G256_inv0_2 = m16_tx1_G16_mul2_G256_inv0_2 ^ m16_tx0_G16_mul2_G256_inv0_2;
  m4_cd_G4_mul0_G16_mul2_G256_inv0_0 = m16_ty1_G16_mul2_G256_inv0_0 ^ m16_ty0_G16_mul2_G256_inv0_0;
  m4_cd_G4_mul0_G16_mul2_G256_inv0_1 = m16_ty1_G16_mul2_G256_inv0_1 ^ m16_ty0_G16_mul2_G256_inv0_1;
  m4_cd_G4_mul0_G16_mul2_G256_inv0_2 = m16_ty1_G16_mul2_G256_inv0_2 ^ m16_ty0_G16_mul2_G256_inv0_2;
  HPC2(m4_ab_G4_mul0_G16_mul2_G256_inv0_0, m4_ab_G4_mul0_G16_mul2_G256_inv0_1, m4_ab_G4_mul0_G16_mul2_G256_inv0_2, m4_cd_G4_mul0_G16_mul2_G256_inv0_0, m4_cd_G4_mul0_G16_mul2_G256_inv0_1, m4_cd_G4_mul0_G16_mul2_G256_inv0_2, &m4_e_G4_mul0_G16_mul2_G256_inv0_0, &m4_e_G4_mul0_G16_mul2_G256_inv0_1, &m4_e_G4_mul0_G16_mul2_G256_inv0_2, rand_118, rand_119, rand_120);
  HPC2(m16_tx1_G16_mul2_G256_inv0_0, m16_tx1_G16_mul2_G256_inv0_1, m16_tx1_G16_mul2_G256_inv0_2, m16_ty1_G16_mul2_G256_inv0_0, m16_ty1_G16_mul2_G256_inv0_1, m16_ty1_G16_mul2_G256_inv0_2, &temp_var_0_G4_mul0_G16_mul2_G256_inv0_0, &temp_var_0_G4_mul0_G16_mul2_G256_inv0_1, &temp_var_0_G4_mul0_G16_mul2_G256_inv0_2, rand_121, rand_122, rand_123);
  m16_e1_s1_G16_mul2_G256_inv0_0 = temp_var_0_G4_mul0_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_0;
  m16_e1_s1_G16_mul2_G256_inv0_1 = temp_var_0_G4_mul0_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_1;
  m16_e1_s1_G16_mul2_G256_inv0_2 = temp_var_0_G4_mul0_G16_mul2_G256_inv0_2 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_2;
  HPC2(m16_tx0_G16_mul2_G256_inv0_0, m16_tx0_G16_mul2_G256_inv0_1, m16_tx0_G16_mul2_G256_inv0_2, m16_ty0_G16_mul2_G256_inv0_0, m16_ty0_G16_mul2_G256_inv0_1, m16_ty0_G16_mul2_G256_inv0_2, &temp_var_1_G4_mul0_G16_mul2_G256_inv0_0, &temp_var_1_G4_mul0_G16_mul2_G256_inv0_1, &temp_var_1_G4_mul0_G16_mul2_G256_inv0_2, rand_124, rand_125, rand_126);
  m16_e0_s1_G16_mul2_G256_inv0_0 = temp_var_1_G4_mul0_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_0;
  m16_e0_s1_G16_mul2_G256_inv0_1 = temp_var_1_G4_mul0_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_1;
  m16_e0_s1_G16_mul2_G256_inv0_2 = temp_var_1_G4_mul0_G16_mul2_G256_inv0_2 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_2;
  m16_e1_s2_G16_mul2_G256_inv0_0 = m16_e0_s1_G16_mul2_G256_inv0_0;
  m16_e1_s2_G16_mul2_G256_inv0_1 = m16_e0_s1_G16_mul2_G256_inv0_1;
  m16_e1_s2_G16_mul2_G256_inv0_2 = m16_e0_s1_G16_mul2_G256_inv0_2;
  m16_e0_s2_G16_mul2_G256_inv0_0 = m16_e1_s1_G16_mul2_G256_inv0_0 ^ m16_e0_s1_G16_mul2_G256_inv0_0;
  m16_e0_s2_G16_mul2_G256_inv0_1 = m16_e1_s1_G16_mul2_G256_inv0_1 ^ m16_e0_s1_G16_mul2_G256_inv0_1;
  m16_e0_s2_G16_mul2_G256_inv0_2 = m16_e1_s1_G16_mul2_G256_inv0_2 ^ m16_e0_s1_G16_mul2_G256_inv0_2;
  m4_ab_G4_mul1_G16_mul2_G256_inv0_0 = i256_e3_G256_inv0_0 ^ i256_e2_G256_inv0_0;
  m4_ab_G4_mul1_G16_mul2_G256_inv0_1 = i256_e3_G256_inv0_1 ^ i256_e2_G256_inv0_1;
  m4_ab_G4_mul1_G16_mul2_G256_inv0_2 = i256_e3_G256_inv0_2 ^ i256_e2_G256_inv0_2;
  m4_cd_G4_mul1_G16_mul2_G256_inv0_0 = sb_y7_0 ^ sb_y6_0;
  m4_cd_G4_mul1_G16_mul2_G256_inv0_1 = sb_y7_1 ^ sb_y6_1;
  m4_cd_G4_mul1_G16_mul2_G256_inv0_2 = sb_y7_2 ^ sb_y6_2;
  HPC2(m4_ab_G4_mul1_G16_mul2_G256_inv0_0, m4_ab_G4_mul1_G16_mul2_G256_inv0_1, m4_ab_G4_mul1_G16_mul2_G256_inv0_2, m4_cd_G4_mul1_G16_mul2_G256_inv0_0, m4_cd_G4_mul1_G16_mul2_G256_inv0_1, m4_cd_G4_mul1_G16_mul2_G256_inv0_2, &m4_e_G4_mul1_G16_mul2_G256_inv0_0, &m4_e_G4_mul1_G16_mul2_G256_inv0_1, &m4_e_G4_mul1_G16_mul2_G256_inv0_2, rand_127, rand_128, rand_129);
  HPC2(i256_e3_G256_inv0_0, i256_e3_G256_inv0_1, i256_e3_G256_inv0_2, sb_y7_0, sb_y7_1, sb_y7_2, &temp_var_0_G4_mul1_G16_mul2_G256_inv0_0, &temp_var_0_G4_mul1_G16_mul2_G256_inv0_1, &temp_var_0_G4_mul1_G16_mul2_G256_inv0_2, rand_130, rand_131, rand_132);
  m16_ph1_G16_mul2_G256_inv0_0 = temp_var_0_G4_mul1_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_0;
  m16_ph1_G16_mul2_G256_inv0_1 = temp_var_0_G4_mul1_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_1;
  m16_ph1_G16_mul2_G256_inv0_2 = temp_var_0_G4_mul1_G16_mul2_G256_inv0_2 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_2;
  HPC2(i256_e2_G256_inv0_0, i256_e2_G256_inv0_1, i256_e2_G256_inv0_2, sb_y6_0, sb_y6_1, sb_y6_2, &temp_var_1_G4_mul1_G16_mul2_G256_inv0_0, &temp_var_1_G4_mul1_G16_mul2_G256_inv0_1, &temp_var_1_G4_mul1_G16_mul2_G256_inv0_2, rand_133, rand_134, rand_135);
  m16_ph0_G16_mul2_G256_inv0_0 = temp_var_1_G4_mul1_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_0;
  m16_ph0_G16_mul2_G256_inv0_1 = temp_var_1_G4_mul1_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_1;
  m16_ph0_G16_mul2_G256_inv0_2 = temp_var_1_G4_mul1_G16_mul2_G256_inv0_2 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_2;
  m4_ab_G4_mul2_G16_mul2_G256_inv0_0 = i256_e1_G256_inv0_0 ^ i256_e0_G256_inv0_0;
  m4_ab_G4_mul2_G16_mul2_G256_inv0_1 = i256_e1_G256_inv0_1 ^ i256_e0_G256_inv0_1;
  m4_ab_G4_mul2_G16_mul2_G256_inv0_2 = i256_e1_G256_inv0_2 ^ i256_e0_G256_inv0_2;
  m4_cd_G4_mul2_G16_mul2_G256_inv0_0 = sb_y5_0 ^ sb_y4_0;
  m4_cd_G4_mul2_G16_mul2_G256_inv0_1 = sb_y5_1 ^ sb_y4_1;
  m4_cd_G4_mul2_G16_mul2_G256_inv0_2 = sb_y5_2 ^ sb_y4_2;
  HPC2(m4_ab_G4_mul2_G16_mul2_G256_inv0_0, m4_ab_G4_mul2_G16_mul2_G256_inv0_1, m4_ab_G4_mul2_G16_mul2_G256_inv0_2, m4_cd_G4_mul2_G16_mul2_G256_inv0_0, m4_cd_G4_mul2_G16_mul2_G256_inv0_1, m4_cd_G4_mul2_G16_mul2_G256_inv0_2, &m4_e_G4_mul2_G16_mul2_G256_inv0_0, &m4_e_G4_mul2_G16_mul2_G256_inv0_1, &m4_e_G4_mul2_G16_mul2_G256_inv0_2, rand_136, rand_137, rand_138);
  HPC2(i256_e1_G256_inv0_0, i256_e1_G256_inv0_1, i256_e1_G256_inv0_2, sb_y5_0, sb_y5_1, sb_y5_2, &temp_var_0_G4_mul2_G16_mul2_G256_inv0_0, &temp_var_0_G4_mul2_G16_mul2_G256_inv0_1, &temp_var_0_G4_mul2_G16_mul2_G256_inv0_2, rand_139, rand_140, rand_141);
  m16_ql1_G16_mul2_G256_inv0_0 = temp_var_0_G4_mul2_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_0;
  m16_ql1_G16_mul2_G256_inv0_1 = temp_var_0_G4_mul2_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_1;
  m16_ql1_G16_mul2_G256_inv0_2 = temp_var_0_G4_mul2_G16_mul2_G256_inv0_2 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_2;
  HPC2(i256_e0_G256_inv0_0, i256_e0_G256_inv0_1, i256_e0_G256_inv0_2, sb_y4_0, sb_y4_1, sb_y4_2, &temp_var_1_G4_mul2_G16_mul2_G256_inv0_0, &temp_var_1_G4_mul2_G16_mul2_G256_inv0_1, &temp_var_1_G4_mul2_G16_mul2_G256_inv0_2, rand_142, rand_143, rand_144);
  m16_ql0_G16_mul2_G256_inv0_0 = temp_var_1_G4_mul2_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_0;
  m16_ql0_G16_mul2_G256_inv0_1 = temp_var_1_G4_mul2_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_1;
  m16_ql0_G16_mul2_G256_inv0_2 = temp_var_1_G4_mul2_G16_mul2_G256_inv0_2 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_2;
  i256_ql3_G256_inv0_0 = m16_ph1_G16_mul2_G256_inv0_0 ^ m16_e1_s2_G16_mul2_G256_inv0_0;
  i256_ql3_G256_inv0_1 = m16_ph1_G16_mul2_G256_inv0_1 ^ m16_e1_s2_G16_mul2_G256_inv0_1;
  i256_ql3_G256_inv0_2 = m16_ph1_G16_mul2_G256_inv0_2 ^ m16_e1_s2_G16_mul2_G256_inv0_2;
  i256_ql2_G256_inv0_0 = m16_ph0_G16_mul2_G256_inv0_0 ^ m16_e0_s2_G16_mul2_G256_inv0_0;
  i256_ql2_G256_inv0_1 = m16_ph0_G16_mul2_G256_inv0_1 ^ m16_e0_s2_G16_mul2_G256_inv0_1;
  i256_ql2_G256_inv0_2 = m16_ph0_G16_mul2_G256_inv0_2 ^ m16_e0_s2_G16_mul2_G256_inv0_2;
  i256_ql1_G256_inv0_0 = m16_ql1_G16_mul2_G256_inv0_0 ^ m16_e1_s2_G16_mul2_G256_inv0_0;
  i256_ql1_G256_inv0_1 = m16_ql1_G16_mul2_G256_inv0_1 ^ m16_e1_s2_G16_mul2_G256_inv0_1;
  i256_ql1_G256_inv0_2 = m16_ql1_G16_mul2_G256_inv0_2 ^ m16_e1_s2_G16_mul2_G256_inv0_2;
  i256_ql0_G256_inv0_0 = m16_ql0_G16_mul2_G256_inv0_0 ^ m16_e0_s2_G16_mul2_G256_inv0_0;
  i256_ql0_G256_inv0_1 = m16_ql0_G16_mul2_G256_inv0_1 ^ m16_e0_s2_G16_mul2_G256_inv0_1;
  i256_ql0_G256_inv0_2 = m16_ql0_G16_mul2_G256_inv0_2 ^ m16_e0_s2_G16_mul2_G256_inv0_2;
  sb_i7_0 = i256_ph3_G256_inv0_0;
  sb_i7_1 = i256_ph3_G256_inv0_1;
  sb_i7_2 = i256_ph3_G256_inv0_2;
  sb_i6_0 = i256_ph2_G256_inv0_0;
  sb_i6_1 = i256_ph2_G256_inv0_1;
  sb_i6_2 = i256_ph2_G256_inv0_2;
  sb_i5_0 = i256_ph1_G256_inv0_0;
  sb_i5_1 = i256_ph1_G256_inv0_1;
  sb_i5_2 = i256_ph1_G256_inv0_2;
  sb_i4_0 = i256_ph0_G256_inv0_0;
  sb_i4_1 = i256_ph0_G256_inv0_1;
  sb_i4_2 = i256_ph0_G256_inv0_2;
  sb_i3_0 = i256_ql3_G256_inv0_0;
  sb_i3_1 = i256_ql3_G256_inv0_1;
  sb_i3_2 = i256_ql3_G256_inv0_2;
  sb_i2_0 = i256_ql2_G256_inv0_0;
  sb_i2_1 = i256_ql2_G256_inv0_1;
  sb_i2_2 = i256_ql2_G256_inv0_2;
  sb_i1_0 = i256_ql1_G256_inv0_0;
  sb_i1_1 = i256_ql1_G256_inv0_1;
  sb_i1_2 = i256_ql1_G256_inv0_2;
  sb_i0_0 = i256_ql0_G256_inv0_0;
  sb_i0_1 = i256_ql0_G256_inv0_1;
  sb_i0_2 = i256_ql0_G256_inv0_2;
  _Bool temp_var_17_0;
  _Bool temp_var_17_1;
  _Bool temp_var_17_2;
  temp_var_17_0 = sb_i1_0 ^ sb_i4_0;
  temp_var_17_1 = sb_i1_1 ^ sb_i4_1;
  temp_var_17_2 = sb_i1_2 ^ sb_i4_2;
  fy0_0 = temp_var_17_0 ^ sb_i6_0;
  fy0_1 = temp_var_17_1 ^ sb_i6_1;
  fy0_2 = temp_var_17_2 ^ sb_i6_2;
  _Bool temp_var_18_0;
  _Bool temp_var_18_1;
  _Bool temp_var_18_2;
  temp_var_18_0 = sb_i1_0 ^ sb_i4_0;
  temp_var_18_1 = sb_i1_1 ^ sb_i4_1;
  temp_var_18_2 = sb_i1_2 ^ sb_i4_2;
  fy1_0 = temp_var_18_0 ^ sb_i5_0;
  fy1_1 = temp_var_18_1 ^ sb_i5_1;
  fy1_2 = temp_var_18_2 ^ sb_i5_2;
  _Bool temp_var_19_0;
  _Bool temp_var_19_1;
  _Bool temp_var_19_2;
  temp_var_19_0 = sb_i0_0 ^ sb_i2_0;
  temp_var_19_1 = sb_i0_1 ^ sb_i2_1;
  temp_var_19_2 = sb_i0_2 ^ sb_i2_2;
  _Bool temp_var_20_0;
  _Bool temp_var_20_1;
  _Bool temp_var_20_2;
  temp_var_20_0 = temp_var_19_0 ^ sb_i3_0;
  temp_var_20_1 = temp_var_19_1 ^ sb_i3_1;
  temp_var_20_2 = temp_var_19_2 ^ sb_i3_2;
  _Bool temp_var_21_0;
  _Bool temp_var_21_1;
  _Bool temp_var_21_2;
  temp_var_21_0 = temp_var_20_0 ^ sb_i5_0;
  temp_var_21_1 = temp_var_20_1 ^ sb_i5_1;
  temp_var_21_2 = temp_var_20_2 ^ sb_i5_2;
  fy2_0 = temp_var_21_0 ^ sb_i6_0;
  fy2_1 = temp_var_21_1 ^ sb_i6_1;
  fy2_2 = temp_var_21_2 ^ sb_i6_2;
  _Bool temp_var_22_0;
  _Bool temp_var_22_1;
  _Bool temp_var_22_2;
  temp_var_22_0 = sb_i3_0 ^ sb_i4_0;
  temp_var_22_1 = sb_i3_1 ^ sb_i4_1;
  temp_var_22_2 = sb_i3_2 ^ sb_i4_2;
  _Bool temp_var_23_0;
  _Bool temp_var_23_1;
  _Bool temp_var_23_2;
  temp_var_23_0 = temp_var_22_0 ^ sb_i5_0;
  temp_var_23_1 = temp_var_22_1 ^ sb_i5_1;
  temp_var_23_2 = temp_var_22_2 ^ sb_i5_2;
  _Bool temp_var_24_0;
  _Bool temp_var_24_1;
  _Bool temp_var_24_2;
  temp_var_24_0 = temp_var_23_0 ^ sb_i6_0;
  temp_var_24_1 = temp_var_23_1 ^ sb_i6_1;
  temp_var_24_2 = temp_var_23_2 ^ sb_i6_2;
  fy3_0 = temp_var_24_0 ^ sb_i7_0;
  fy3_1 = temp_var_24_1 ^ sb_i7_1;
  fy3_2 = temp_var_24_2 ^ sb_i7_2;
  _Bool temp_var_25_0;
  _Bool temp_var_25_1;
  _Bool temp_var_25_2;
  temp_var_25_0 = sb_i3_0 ^ sb_i5_0;
  temp_var_25_1 = sb_i3_1 ^ sb_i5_1;
  temp_var_25_2 = sb_i3_2 ^ sb_i5_2;
  fy4_0 = temp_var_25_0 ^ sb_i7_0;
  fy4_1 = temp_var_25_1 ^ sb_i7_1;
  fy4_2 = temp_var_25_2 ^ sb_i7_2;
  fy5_0 = sb_i0_0 ^ sb_i6_0;
  fy5_1 = sb_i0_1 ^ sb_i6_1;
  fy5_2 = sb_i0_2 ^ sb_i6_2;
  fy6_0 = sb_i3_0 ^ sb_i7_0;
  fy6_1 = sb_i3_1 ^ sb_i7_1;
  fy6_2 = sb_i3_2 ^ sb_i7_2;
  fy7_0 = sb_i3_0 ^ sb_i5_0;
  fy7_1 = sb_i3_1 ^ sb_i5_1;
  fy7_2 = sb_i3_2 ^ sb_i5_2;
  *sb_o0_0 = fy0_0;
  *sb_o0_1 = fy0_1;
  *sb_o0_2 = !fy0_2;
  *sb_o1_0 = fy1_0;
  *sb_o1_1 = fy1_1;
  *sb_o1_2 = !fy1_2;
  *sb_o2_0 = fy2_0;
  *sb_o2_1 = fy2_1;
  *sb_o2_2 = fy2_2;
  *sb_o3_0 = fy3_0;
  *sb_o3_1 = fy3_1;
  *sb_o3_2 = fy3_2;
  *sb_o4_0 = fy4_0;
  *sb_o4_1 = fy4_1;
  *sb_o4_2 = fy4_2;
  *sb_o5_0 = fy5_0;
  *sb_o5_1 = fy5_1;
  *sb_o5_2 = !fy5_2;
  *sb_o6_0 = fy6_0;
  *sb_o6_1 = fy6_1;
  *sb_o6_2 = !fy6_2;
  *sb_o7_0 = fy7_0;
  *sb_o7_1 = fy7_1;
  *sb_o7_2 = fy7_2;
}

