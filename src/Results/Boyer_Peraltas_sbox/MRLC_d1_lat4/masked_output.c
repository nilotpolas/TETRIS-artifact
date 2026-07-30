// === GADGET DEFINITIONS ===

// --- hpc3 ---

void hpc3_same_shares_1_order(_Bool a_share, _Bool b_share, _Bool * u_share) {
    * u_share  = a_share & b_share;
}

void hpc3_v_1_order(_Bool a_share, _Bool b_share, _Bool * v_share, _Bool rand){
    _Bool temp;
    temp = reg(b_share ^ rand);
    *v_share = temp & a_share;
}

void hpc3_w_1_order(_Bool a_share, _Bool rand, _Bool prand, _Bool * w_share){
    _Bool temp;
    _Bool a_share_neg;
    a_share_neg = !(a_share);
    temp = a_share_neg & rand;
    *w_share = reg(temp ^ prand);
}

void hpc3_xor_vw_1_order(_Bool v_share, _Bool w_share, _Bool * u_share){
    *u_share = v_share ^ w_share;
}

void HPC3(_Bool a0, _Bool a1, _Bool b0, _Bool b1, _Bool* c0, _Bool* c1, _Bool r01, _Bool p01)
{
	_Bool u00, u01, u10, u11;
	_Bool v01, v10;
	_Bool w01, w10;

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


// --- hpc2o ---

void hpc2o_first_half_1_order(_Bool a_share, _Bool b_share, _Bool w_share, _Bool rand, _Bool *out_share) {
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

void hpc2o_v_1_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand) {
    _Bool xor_br;
    _Bool temp;
    _Bool and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br); // This remains an R register in Algo 6
    
    and_ta = temp & a_share;
    *v_share = reg(and_ta);
}

void hpc2o_w_1_order(_Bool a_share, _Bool rand, _Bool *w_share) {
    _Bool a_neg;
    _Bool and_ar;

    a_neg = !a_share;
    
    and_ar = a_neg & rand;
    *w_share = reg(and_ar);
}

void hpc2o_xor_vw_1_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share ^ w_share;
}

void hpc2o_or_vw_1_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share | w_share;
}
void HPC2o(_Bool a0, _Bool a1, _Bool b0, _Bool b1, _Bool w0, _Bool w1, _Bool * c0, _Bool * c1, _Bool rand_01)
{
	_Bool u01, u10;
	_Bool v01, v10;
	_Bool w01, w10;

	hpc2o_first_half_1_order(a0, b0, w0, rand_01, &w01);
	hpc2o_v_1_order(a0, b1, &v01, rand_01);
	hpc2o_xor_vw_1_order(v01, w01, &u01);

	hpc2o_first_half_1_order(a1, b1, w1, rand_01, &w10);
	hpc2o_v_1_order(a1, b0, &v10, rand_01);
	hpc2o_xor_vw_1_order(v10, w10, &u10);

	*c0 = u01;
	*c1 = u10;
}


// --- hpc2o_swapped ---

void hpc2osw_first_half_1_order(_Bool a_share, _Bool b_share, _Bool w_share, _Bool rand, _Bool *out_share) {
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

void hpc2osw_v_1_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand) {
    _Bool xor_br;
    _Bool temp;
    _Bool and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br);

    and_ta = temp & a_share;
    *v_share = reg(and_ta);
}

void hpc2osw_w_1_order(_Bool a_share, _Bool rand, _Bool *w_share) {
    _Bool a_neg;
    _Bool and_ar;

    a_neg = !a_share;

    and_ar = a_neg & rand;
    *w_share = reg(and_ar);
}

void hpc2osw_xor_vw_1_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share ^ w_share;
}

void hpc2osw_or_vw_1_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share | w_share;
}
void HPC2o_swapped(_Bool a0, _Bool a1, _Bool b0, _Bool b1, _Bool w0, _Bool w1, _Bool * c0, _Bool * c1, _Bool rand_01)
{
	_Bool u01, u10;
	_Bool v01, v10;
	_Bool w01, w10;

	hpc2osw_first_half_1_order(b0, a0, w0, rand_01, &w01);
	hpc2osw_v_1_order(b0, a1, &v01, rand_01);
	hpc2osw_xor_vw_1_order(v01, w01, &u01);

	hpc2osw_first_half_1_order(b1, a1, w1, rand_01, &w10);
	hpc2osw_v_1_order(b1, a0, &v10, rand_01);
	hpc2osw_xor_vw_1_order(v10, w10, &u10);

	*c0 = u01;
	*c1 = u10;
}


// --- hpc2 ---

void hpc2_same_shares_1_order(_Bool a_share, _Bool b_share, _Bool * u_share) {
    * u_share  = a_share & b_share;
}

void hpc2_v_1_order(_Bool a_share, _Bool b_share, _Bool * v_share, _Bool rand){
    _Bool temp; 
    temp = reg(b_share ^ rand);
    *v_share = reg(temp & a_share);
}

void hpc2_w_1_order(_Bool a_share, _Bool rand, _Bool * w_share){
    _Bool a_neg;
    a_neg = !(a_share);
    *w_share = reg(a_neg & rand);
}

void hpc2_xor_vw_1_order(_Bool v_share, _Bool w_share, _Bool * u_share){
    *u_share = v_share ^ w_share;
}

void HPC2(_Bool a0, _Bool a1, _Bool b0, _Bool b1, _Bool * c0, _Bool * c1, _Bool rand_01)
{
	_Bool u00, u01, u10, u11;
	_Bool v01, v10;

	_Bool w01, w10;

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


// --- hpc2_swapped ---

void hpc2sw_same_shares_1_order(_Bool a_share, _Bool b_share, _Bool * u_share) {
    *u_share = a_share & b_share;
}

void hpc2sw_v_1_order(_Bool a_share, _Bool b_share, _Bool * v_share, _Bool rand) {
    _Bool temp;
    temp = reg(b_share ^ rand);
    *v_share = reg(temp & a_share);
}

void hpc2sw_w_1_order(_Bool a_share, _Bool rand, _Bool * w_share) {
    _Bool a_neg;
    a_neg = !(a_share);
    *w_share = reg(a_neg & rand);
}

void hpc2sw_xor_vw_1_order(_Bool v_share, _Bool w_share, _Bool * u_share) {
    *u_share = v_share ^ w_share;
}

void HPC2_swapped(_Bool a0, _Bool a1, _Bool b0, _Bool b1, _Bool * c0, _Bool * c1, _Bool rand_01)
{
	_Bool u00, u01, u10, u11;
	_Bool v01, v10;

	_Bool w01, w10;

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


// --- hpc3o ---

void hpc3o_first_half_1_order(_Bool a_share, _Bool b_share, _Bool w_share, _Bool rand, _Bool rand_prime, _Bool *out_share) {
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

void hpc3o_v_1_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand) {
    _Bool xor_br;
    _Bool temp;
    _Bool and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br); // This remains an R register in Algo 7
    
    and_ta = a_share & temp;
    *v_share = and_ta; // Notice: NO outer reg() here for HPC3o!
}

void hpc3o_w_1_order(_Bool a_share, _Bool rand, _Bool rand_prime, _Bool *w_share) {
    _Bool and_ar;
    _Bool xor_step1;

    // Notice: Algo 7 does not negate a_share in the else branch
    and_ar = a_share & rand;
    xor_step1 = and_ar ^ rand_prime;
    
    *w_share = reg(xor_step1);
}

void hpc3o_xor_vw_1_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share ^ w_share;
}
void HPC3o(_Bool a0, _Bool a1, _Bool b0, _Bool b1, _Bool w0, _Bool w1, _Bool * c0, _Bool * c1, _Bool rand_01, _Bool rand_prime_01)
{
	_Bool u01, u10;
	_Bool v01, v10;
	_Bool w01, w10;

	hpc3o_first_half_1_order(a0, b0, w0, rand_01, rand_prime_01, &w01);
	hpc3o_v_1_order(a0, b1, &v01, rand_01);
	hpc3o_xor_vw_1_order(v01, w01, &u01);

	hpc3o_first_half_1_order(a1, b1, w1, rand_01, rand_prime_01, &w10);
	hpc3o_v_1_order(a1, b0, &v10, rand_01);
	hpc3o_xor_vw_1_order(v10, w10, &u10);

	*c0 = u01;
	*c1 = u10;
}


// === TRANSFORMED CIRCUIT ===
void sbox(_Bool i0_0, _Bool i0_1, _Bool i1_0, _Bool i1_1, _Bool i2_0, _Bool i2_1, _Bool i3_0, _Bool i3_1, _Bool i4_0, _Bool i4_1, _Bool i5_0, _Bool i5_1, _Bool i6_0, _Bool i6_1, _Bool i7_0, _Bool i7_1, _Bool dec_1, _Bool *y0_0, _Bool *y0_1, _Bool *y1_0, _Bool *y1_1, _Bool *y2_0, _Bool *y2_1, _Bool *y3_0, _Bool *y3_1, _Bool *y4_0, _Bool *y4_1, _Bool *y5_0, _Bool *y5_1, _Bool *y6_0, _Bool *y6_1, _Bool *y7_0, _Bool *y7_1, int rand_42, int rand_36, int rand_30, int rand_5, int rand_18, int rand_19, int rand_26, int rand_43, int rand_37, int rand_12, int rand_31, int rand_27, int rand_13, int rand_28, int rand_6, int rand_29, int rand_44, int rand_38, int rand_32, int rand_7, int rand_22, int rand_1, int rand_23, int rand_45, int rand_39, int rand_14, int rand_33, int rand_2, int rand_20, int rand_15, int rand_3, int rand_4, int rand_21, int rand_8, int rand_46, int rand_40, int rand_34, int rand_9, int rand_16, int rand_17, int rand_24, int rand_41, int rand_35, int rand_10, int rand_25, int rand_11)
{
  _Bool t1_0;
  _Bool t1_1;
  t1_0 = i7_0 ^ i4_0;
  t1_1 = i7_1 ^ i4_1;
  _Bool t2_0;
  _Bool t2_1;
  t2_0 = i7_0 ^ i2_0;
  t2_1 = i7_1 ^ i2_1;
  _Bool t3_0;
  _Bool t3_1;
  t3_0 = i7_0 ^ i1_0;
  t3_1 = i7_1 ^ i1_1;
  _Bool t4_0;
  _Bool t4_1;
  t4_0 = i4_0 ^ i2_0;
  t4_1 = i4_1 ^ i2_1;
  _Bool t5_0;
  _Bool t5_1;
  t5_0 = i3_0 ^ i1_0;
  t5_1 = i3_1 ^ i1_1;
  _Bool t6_0;
  _Bool t6_1;
  t6_0 = t1_0 ^ t5_0;
  t6_1 = t1_1 ^ t5_1;
  _Bool t7_0;
  _Bool t7_1;
  t7_0 = i6_0 ^ i5_0;
  t7_1 = i6_1 ^ i5_1;
  _Bool t8_0;
  _Bool t8_1;
  t8_0 = i0_0 ^ t6_0;
  t8_1 = i0_1 ^ t6_1;
  _Bool t9_0;
  _Bool t9_1;
  t9_0 = i0_0 ^ t7_0;
  t9_1 = i0_1 ^ t7_1;
  _Bool t10_0;
  _Bool t10_1;
  t10_0 = t6_0 ^ t7_0;
  t10_1 = t6_1 ^ t7_1;
  _Bool t11_0;
  _Bool t11_1;
  t11_0 = i6_0 ^ i2_0;
  t11_1 = i6_1 ^ i2_1;
  _Bool t12_0;
  _Bool t12_1;
  t12_0 = i5_0 ^ i2_0;
  t12_1 = i5_1 ^ i2_1;
  _Bool t13_0;
  _Bool t13_1;
  t13_0 = t3_0 ^ t4_0;
  t13_1 = t3_1 ^ t4_1;
  _Bool t14_0;
  _Bool t14_1;
  t14_0 = t6_0 ^ t11_0;
  t14_1 = t6_1 ^ t11_1;
  _Bool t15_0;
  _Bool t15_1;
  t15_0 = t5_0 ^ t11_0;
  t15_1 = t5_1 ^ t11_1;
  _Bool t16_0;
  _Bool t16_1;
  t16_0 = t5_0 ^ t12_0;
  t16_1 = t5_1 ^ t12_1;
  _Bool t17_0;
  _Bool t17_1;
  t17_0 = t9_0 ^ t16_0;
  t17_1 = t9_1 ^ t16_1;
  _Bool t18_0;
  _Bool t18_1;
  t18_0 = i4_0 ^ i0_0;
  t18_1 = i4_1 ^ i0_1;
  _Bool t19_0;
  _Bool t19_1;
  t19_0 = t7_0 ^ t18_0;
  t19_1 = t7_1 ^ t18_1;
  _Bool t20_0;
  _Bool t20_1;
  t20_0 = t1_0 ^ t19_0;
  t20_1 = t1_1 ^ t19_1;
  _Bool t21_0;
  _Bool t21_1;
  t21_0 = i1_0 ^ i0_0;
  t21_1 = i1_1 ^ i0_1;
  _Bool t22_0;
  _Bool t22_1;
  t22_0 = t7_0 ^ t21_0;
  t22_1 = t7_1 ^ t21_1;
  _Bool t23_0;
  _Bool t23_1;
  t23_0 = t2_0 ^ t22_0;
  t23_1 = t2_1 ^ t22_1;
  _Bool t24_0;
  _Bool t24_1;
  t24_0 = t2_0 ^ t10_0;
  t24_1 = t2_1 ^ t10_1;
  _Bool t25_0;
  _Bool t25_1;
  t25_0 = t20_0 ^ t17_0;
  t25_1 = t20_1 ^ t17_1;
  _Bool t26_0;
  _Bool t26_1;
  t26_0 = t3_0 ^ t16_0;
  t26_1 = t3_1 ^ t16_1;
  _Bool t27_0;
  _Bool t27_1;
  t27_0 = t1_0 ^ t12_0;
  t27_1 = t1_1 ^ t12_1;
  _Bool m1_0;
  _Bool m1_1;
  HPC3(t13_0, t13_1, t6_0, t6_1, &m1_0, &m1_1, rand_1, rand_2);
  _Bool m2_0;
  _Bool m2_1;
  HPC3(t23_0, t23_1, t8_0, t8_1, &m2_0, &m2_1, rand_3, rand_4);
  _Bool m3_0;
  _Bool m3_1;
  m3_0 = t14_0 ^ m1_0;
  m3_1 = t14_1 ^ m1_1;
  _Bool m4_0;
  _Bool m4_1;
  HPC3(t19_0, t19_1, i0_0, i0_1, &m4_0, &m4_1, rand_5, rand_6);
  _Bool m5_0;
  _Bool m5_1;
  m5_0 = m4_0 ^ m1_0;
  m5_1 = m4_1 ^ m1_1;
  _Bool m6_0;
  _Bool m6_1;
  HPC3(t3_0, t3_1, t16_0, t16_1, &m6_0, &m6_1, rand_7, rand_8);
  _Bool m7_0;
  _Bool m7_1;
  HPC3(t22_0, t22_1, t9_0, t9_1, &m7_0, &m7_1, rand_9, rand_10);
  _Bool m8_0;
  _Bool m8_1;
  m8_0 = t26_0 ^ m6_0;
  m8_1 = t26_1 ^ m6_1;
  _Bool m9_0;
  _Bool m9_1;
  HPC3(t20_0, t20_1, t17_0, t17_1, &m9_0, &m9_1, rand_11, rand_12);
  _Bool m10_0;
  _Bool m10_1;
  m10_0 = m9_0 ^ m6_0;
  m10_1 = m9_1 ^ m6_1;
  _Bool m11_0;
  _Bool m11_1;
  HPC3(t1_0, t1_1, t15_0, t15_1, &m11_0, &m11_1, rand_13, rand_14);
  _Bool m12_0;
  _Bool m12_1;
  HPC3(t4_0, t4_1, t27_0, t27_1, &m12_0, &m12_1, rand_15, rand_16);
  _Bool m13_0;
  _Bool m13_1;
  m13_0 = m12_0 ^ m11_0;
  m13_1 = m12_1 ^ m11_1;
  _Bool m14_0;
  _Bool m14_1;
  HPC3(t2_0, t2_1, t10_0, t10_1, &m14_0, &m14_1, rand_17, rand_18);
  _Bool m15_0;
  _Bool m15_1;
  m15_0 = m14_0 ^ m11_0;
  m15_1 = m14_1 ^ m11_1;
  _Bool m16_0;
  _Bool m16_1;
  m16_0 = m3_0 ^ m2_0;
  m16_1 = m3_1 ^ m2_1;
  _Bool m17_0;
  _Bool m17_1;
  m17_0 = m5_0 ^ t24_0;
  m17_1 = m5_1 ^ t24_1;
  _Bool m18_0;
  _Bool m18_1;
  m18_0 = m7_0 ^ m8_0;
  m18_1 = m7_1 ^ m8_1;
  _Bool m19_0;
  _Bool m19_1;
  m19_0 = m10_0 ^ m15_0;
  m19_1 = m10_1 ^ m15_1;
  _Bool m20_0;
  _Bool m20_1;
  m20_0 = m16_0 ^ m13_0;
  m20_1 = m16_1 ^ m13_1;
  _Bool m21_0;
  _Bool m21_1;
  m21_0 = m17_0 ^ m15_0;
  m21_1 = m17_1 ^ m15_1;
  _Bool m22_0;
  _Bool m22_1;
  m22_0 = m18_0 ^ m13_0;
  m22_1 = m18_1 ^ m13_1;
  _Bool m23_0;
  _Bool m23_1;
  m23_0 = m19_0 ^ t25_0;
  m23_1 = m19_1 ^ t25_1;
  _Bool m24_0;
  _Bool m24_1;
  m24_0 = m22_0 ^ m23_0;
  m24_1 = m22_1 ^ m23_1;
  _Bool m25_0;
  _Bool m25_1;
  HPC3(m22_0, m22_1, m20_0, m20_1, &m25_0, &m25_1, rand_19, rand_20);
  _Bool m26_0;
  _Bool m26_1;
  m26_0 = m21_0 ^ m25_0;
  m26_1 = m21_1 ^ m25_1;
  _Bool m27_0;
  _Bool m27_1;
  m27_0 = m20_0 ^ m21_0;
  m27_1 = m20_1 ^ m21_1;
  _Bool m28_0;
  _Bool m28_1;
  m28_0 = m23_0 ^ m25_0;
  m28_1 = m23_1 ^ m25_1;
  _Bool m29_0;
  _Bool m29_1;
  _Bool m30_0;
  _Bool m30_1;
  _Bool m31_0;
  _Bool m31_1;
  HPC3(m20_0, m20_1, m23_0, m23_1, &m31_0, &m31_1, rand_21, rand_22);
  _Bool m32_0;
  _Bool m32_1;
  _Bool m33_0;
  _Bool m33_1;
  m33_0 = m27_0 ^ m25_0;
  m33_1 = m27_1 ^ m25_1;
  _Bool m34_0;
  _Bool m34_1;
  HPC3(m21_0, m21_1, m22_0, m22_1, &m34_0, &m34_1, rand_23, rand_24);
  _Bool m35_0;
  _Bool m35_1;
  _Bool m36_0;
  _Bool m36_1;
  m36_0 = m24_0 ^ m25_0;
  m36_1 = m24_1 ^ m25_1;
  HPC2o(m28_0, m28_1, m27_0, m27_1, m21_0, m21_1, &m29_0, &m29_1, rand_25);
  HPC2o_swapped(m27_0, m27_1, m31_0, m31_1, m33_0, m33_1, &m32_0, &m32_1, rand_26);
  HPC2o(m26_0, m26_1, m24_0, m24_1, m23_0, m23_1, &m30_0, &m30_1, rand_27);
  HPC2o_swapped(m24_0, m24_1, m34_0, m34_1, m36_0, m36_1, &m35_0, &m35_1, rand_28);
  _Bool m41_0;
  _Bool m41_1;
  m41_0 = m32_0 ^ m35_0;
  m41_1 = m32_1 ^ m35_1;
  _Bool m42_0;
  _Bool m42_1;
  m42_0 = m29_0 ^ m30_0;
  m42_1 = m29_1 ^ m30_1;
  _Bool m43_0;
  _Bool m43_1;
  m43_0 = m29_0 ^ m32_0;
  m43_1 = m29_1 ^ m32_1;
  _Bool m44_0;
  _Bool m44_1;
  m44_0 = m30_0 ^ m35_0;
  m44_1 = m30_1 ^ m35_1;
  _Bool m45_0;
  _Bool m45_1;
  m45_0 = m42_0 ^ m41_0;
  m45_1 = m42_1 ^ m41_1;
  _Bool m46_0;
  _Bool m46_1;
  HPC2(m44_0, m44_1, t6_0, t6_1, &m46_0, &m46_1, rand_29);
  _Bool m47_0;
  _Bool m47_1;
  HPC2(m35_0, m35_1, t8_0, t8_1, &m47_0, &m47_1, rand_30);
  _Bool m48_0;
  _Bool m48_1;
  HPC2(m30_0, m30_1, i0_0, i0_1, &m48_0, &m48_1, rand_31);
  _Bool m49_0;
  _Bool m49_1;
  HPC2(m43_0, m43_1, t16_0, t16_1, &m49_0, &m49_1, rand_32);
  _Bool m50_0;
  _Bool m50_1;
  HPC2(m32_0, m32_1, t9_0, t9_1, &m50_0, &m50_1, rand_33);
  _Bool m51_0;
  _Bool m51_1;
  HPC2(m29_0, m29_1, t17_0, t17_1, &m51_0, &m51_1, rand_34);
  _Bool m52_0;
  _Bool m52_1;
  HPC2(m42_0, m42_1, t15_0, t15_1, &m52_0, &m52_1, rand_35);
  _Bool m53_0;
  _Bool m53_1;
  HPC2(m45_0, m45_1, t27_0, t27_1, &m53_0, &m53_1, rand_36);
  _Bool m54_0;
  _Bool m54_1;
  HPC2(m41_0, m41_1, t10_0, t10_1, &m54_0, &m54_1, rand_37);
  _Bool m55_0;
  _Bool m55_1;
  HPC2(m44_0, m44_1, t13_0, t13_1, &m55_0, &m55_1, rand_38);
  _Bool m56_0;
  _Bool m56_1;
  HPC2(m35_0, m35_1, t23_0, t23_1, &m56_0, &m56_1, rand_39);
  _Bool m57_0;
  _Bool m57_1;
  HPC2(m30_0, m30_1, t19_0, t19_1, &m57_0, &m57_1, rand_40);
  _Bool m58_0;
  _Bool m58_1;
  HPC2(m43_0, m43_1, t3_0, t3_1, &m58_0, &m58_1, rand_41);
  _Bool m59_0;
  _Bool m59_1;
  HPC2(m32_0, m32_1, t22_0, t22_1, &m59_0, &m59_1, rand_42);
  _Bool m60_0;
  _Bool m60_1;
  HPC2(m29_0, m29_1, t20_0, t20_1, &m60_0, &m60_1, rand_43);
  _Bool m61_0;
  _Bool m61_1;
  HPC2(m42_0, m42_1, t1_0, t1_1, &m61_0, &m61_1, rand_44);
  _Bool m62_0;
  _Bool m62_1;
  HPC2(m45_0, m45_1, t4_0, t4_1, &m62_0, &m62_1, rand_45);
  _Bool m63_0;
  _Bool m63_1;
  HPC2(m41_0, m41_1, t2_0, t2_1, &m63_0, &m63_1, rand_46);
  _Bool l0_0;
  _Bool l0_1;
  l0_0 = m61_0 ^ m62_0;
  l0_1 = m61_1 ^ m62_1;
  _Bool l1_0;
  _Bool l1_1;
  l1_0 = m50_0 ^ m56_0;
  l1_1 = m50_1 ^ m56_1;
  _Bool l2_0;
  _Bool l2_1;
  l2_0 = m46_0 ^ m48_0;
  l2_1 = m46_1 ^ m48_1;
  _Bool l3_0;
  _Bool l3_1;
  l3_0 = m47_0 ^ m55_0;
  l3_1 = m47_1 ^ m55_1;
  _Bool l4_0;
  _Bool l4_1;
  l4_0 = m54_0 ^ m58_0;
  l4_1 = m54_1 ^ m58_1;
  _Bool l5_0;
  _Bool l5_1;
  l5_0 = m49_0 ^ m61_0;
  l5_1 = m49_1 ^ m61_1;
  _Bool l6_0;
  _Bool l6_1;
  l6_0 = m62_0 ^ l5_0;
  l6_1 = m62_1 ^ l5_1;
  _Bool l7_0;
  _Bool l7_1;
  l7_0 = m46_0 ^ l3_0;
  l7_1 = m46_1 ^ l3_1;
  _Bool l8_0;
  _Bool l8_1;
  l8_0 = m51_0 ^ m59_0;
  l8_1 = m51_1 ^ m59_1;
  _Bool l9_0;
  _Bool l9_1;
  l9_0 = m52_0 ^ m53_0;
  l9_1 = m52_1 ^ m53_1;
  _Bool l10_0;
  _Bool l10_1;
  l10_0 = m53_0 ^ l4_0;
  l10_1 = m53_1 ^ l4_1;
  _Bool l11_0;
  _Bool l11_1;
  l11_0 = m60_0 ^ l2_0;
  l11_1 = m60_1 ^ l2_1;
  _Bool l12_0;
  _Bool l12_1;
  l12_0 = m48_0 ^ m51_0;
  l12_1 = m48_1 ^ m51_1;
  _Bool l13_0;
  _Bool l13_1;
  l13_0 = m50_0 ^ l0_0;
  l13_1 = m50_1 ^ l0_1;
  _Bool l14_0;
  _Bool l14_1;
  l14_0 = m52_0 ^ m61_0;
  l14_1 = m52_1 ^ m61_1;
  _Bool l15_0;
  _Bool l15_1;
  l15_0 = m55_0 ^ l1_0;
  l15_1 = m55_1 ^ l1_1;
  _Bool l16_0;
  _Bool l16_1;
  l16_0 = m56_0 ^ l0_0;
  l16_1 = m56_1 ^ l0_1;
  _Bool l17_0;
  _Bool l17_1;
  l17_0 = m57_0 ^ l1_0;
  l17_1 = m57_1 ^ l1_1;
  _Bool l18_0;
  _Bool l18_1;
  l18_0 = m58_0 ^ l8_0;
  l18_1 = m58_1 ^ l8_1;
  _Bool l19_0;
  _Bool l19_1;
  l19_0 = m63_0 ^ l4_0;
  l19_1 = m63_1 ^ l4_1;
  _Bool l20_0;
  _Bool l20_1;
  l20_0 = l0_0 ^ l1_0;
  l20_1 = l0_1 ^ l1_1;
  _Bool l21_0;
  _Bool l21_1;
  l21_0 = l1_0 ^ l7_0;
  l21_1 = l1_1 ^ l7_1;
  _Bool l22_0;
  _Bool l22_1;
  l22_0 = l3_0 ^ l12_0;
  l22_1 = l3_1 ^ l12_1;
  _Bool l23_0;
  _Bool l23_1;
  l23_0 = l18_0 ^ l2_0;
  l23_1 = l18_1 ^ l2_1;
  _Bool l24_0;
  _Bool l24_1;
  l24_0 = l15_0 ^ l9_0;
  l24_1 = l15_1 ^ l9_1;
  _Bool l25_0;
  _Bool l25_1;
  l25_0 = l6_0 ^ l10_0;
  l25_1 = l6_1 ^ l10_1;
  _Bool l26_0;
  _Bool l26_1;
  l26_0 = l7_0 ^ l9_0;
  l26_1 = l7_1 ^ l9_1;
  _Bool l27_0;
  _Bool l27_1;
  l27_0 = l8_0 ^ l10_0;
  l27_1 = l8_1 ^ l10_1;
  _Bool l28_0;
  _Bool l28_1;
  l28_0 = l11_0 ^ l14_0;
  l28_1 = l11_1 ^ l14_1;
  _Bool l29_0;
  _Bool l29_1;
  l29_0 = l11_0 ^ l17_0;
  l29_1 = l11_1 ^ l17_1;
  *y7_0 = l6_0 ^ l24_0;
  *y7_1 = l6_1 ^ l24_1;
  _Bool l30_0;
  _Bool l30_1;
  l30_0 = l16_0 ^ l26_0;
  l30_1 = l16_1 ^ l26_1;
  *y6_0 = l30_0;
  *y6_1 = !l30_1;
  _Bool l31_0;
  _Bool l31_1;
  l31_0 = l19_0 ^ l28_0;
  l31_1 = l19_1 ^ l28_1;
  *y5_0 = l31_0;
  *y5_1 = !l31_1;
  *y4_0 = l6_0 ^ l21_0;
  *y4_1 = l6_1 ^ l21_1;
  *y3_0 = l20_0 ^ l22_0;
  *y3_1 = l20_1 ^ l22_1;
  *y2_0 = l25_0 ^ l29_0;
  *y2_1 = l25_1 ^ l29_1;
  _Bool l32_0;
  _Bool l32_1;
  l32_0 = l13_0 ^ l27_0;
  l32_1 = l13_1 ^ l27_1;
  *y1_0 = l32_0;
  *y1_1 = !l32_1;
  _Bool l33_0;
  _Bool l33_1;
  l33_0 = l6_0 ^ l23_0;
  l33_1 = l6_1 ^ l23_1;
  *y0_0 = l33_0;
  *y0_1 = !l33_1;
}

