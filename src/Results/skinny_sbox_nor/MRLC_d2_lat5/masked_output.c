// === GADGET DEFINITIONS ===

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
void sbox(_Bool i0_0, _Bool i0_1, _Bool i0_2, _Bool i1_0, _Bool i1_1, _Bool i1_2, _Bool i2_0, _Bool i2_1, _Bool i2_2, _Bool i3_0, _Bool i3_1, _Bool i3_2, _Bool i4_0, _Bool i4_1, _Bool i4_2, _Bool i5_0, _Bool i5_1, _Bool i5_2, _Bool i6_0, _Bool i6_1, _Bool i6_2, _Bool i7_0, _Bool i7_1, _Bool i7_2, _Bool dec_1, _Bool *o0_0, _Bool *o0_1, _Bool *o0_2, _Bool *o1_0, _Bool *o1_1, _Bool *o1_2, _Bool *o2_0, _Bool *o2_1, _Bool *o2_2, _Bool *o3_0, _Bool *o3_1, _Bool *o3_2, _Bool *o4_0, _Bool *o4_1, _Bool *o4_2, _Bool *o5_0, _Bool *o5_1, _Bool *o5_2, _Bool *o6_0, _Bool *o6_1, _Bool *o6_2, _Bool *o7_0, _Bool *o7_1, _Bool *o7_2, int rand_17, int rand_18, int rand_19, int rand_20, int rand_2, int rand_3, int rand_4, int rand_1, int rand_5, int rand_6, int rand_21, int rand_8, int rand_22, int rand_7, int rand_9, int rand_24, int rand_10, int rand_23, int rand_11, int rand_25, int rand_12, int rand_27, int rand_13, int rand_26, int rand_14, int rand_15, int rand_16)
{
  _Bool n1_0;
  _Bool n1_1;
  _Bool n1_2;
  _Bool n2_0;
  _Bool n2_1;
  _Bool n2_2;
  _Bool n3_0;
  _Bool n3_1;
  _Bool n3_2;
  _Bool n6_0;
  _Bool n6_1;
  _Bool n6_2;
  _Bool n7_0;
  _Bool n7_1;
  _Bool n7_2;
  _Bool t0_0;
  _Bool t0_1;
  _Bool t0_2;
  _Bool t1_0;
  _Bool t1_1;
  _Bool t1_2;
  _Bool t2_0;
  _Bool t2_1;
  _Bool t2_2;
  _Bool t3_0;
  _Bool t3_1;
  _Bool t3_2;
  _Bool t4_0;
  _Bool t4_1;
  _Bool t4_2;
  _Bool t5_0;
  _Bool t5_1;
  _Bool t5_2;
  _Bool t6_0;
  _Bool t6_1;
  _Bool t6_2;
  _Bool t7_0;
  _Bool t7_1;
  _Bool t7_2;
  _Bool nt0_0;
  _Bool nt0_1;
  _Bool nt0_2;
  _Bool nt1_0;
  _Bool nt1_1;
  _Bool nt1_2;
  _Bool nt2_0;
  _Bool nt2_1;
  _Bool nt2_2;
  _Bool nt3_0;
  _Bool nt3_1;
  _Bool nt3_2;
  _Bool nt4_0;
  _Bool nt4_1;
  _Bool nt4_2;
  _Bool nt5_0;
  _Bool nt5_1;
  _Bool nt5_2;
  _Bool o1_val_0;
  _Bool o1_val_1;
  _Bool o1_val_2;
  _Bool o2_val_0;
  _Bool o2_val_1;
  _Bool o2_val_2;
  _Bool o3_val_0;
  _Bool o3_val_1;
  _Bool o3_val_2;
  _Bool o5_val_0;
  _Bool o5_val_1;
  _Bool o5_val_2;
  _Bool o6_val_0;
  _Bool o6_val_1;
  _Bool o6_val_2;
  _Bool o7_val_0;
  _Bool o7_val_1;
  _Bool o7_val_2;
  n1_0 = i1_0;
  n1_1 = i1_1;
  n1_2 = !i1_2;
  n2_0 = i2_0;
  n2_1 = i2_1;
  n2_2 = !i2_2;
  n3_0 = i3_0;
  n3_1 = i3_1;
  n3_2 = !i3_2;
  n6_0 = i6_0;
  n6_1 = i6_1;
  n6_2 = !i6_2;
  n7_0 = i7_0;
  n7_1 = i7_1;
  n7_2 = !i7_2;
  HPC2(n6_0, n6_1, n6_2, n7_0, n7_1, n7_2, &t0_0, &t0_1, &t0_2, rand_1, rand_2, rand_3);
  HPC2(n3_0, n3_1, n3_2, n2_0, n2_1, n2_2, &t1_0, &t1_1, &t1_2, rand_4, rand_5, rand_6);
  HPC2(n2_0, n2_1, n2_2, n1_0, n1_1, n1_2, &t2_0, &t2_1, &t2_2, rand_7, rand_8, rand_9);
  nt0_0 = t0_0;
  nt0_1 = t0_1;
  nt0_2 = !t0_2;
  nt1_0 = t1_0;
  nt1_1 = t1_1;
  nt1_2 = !t1_2;
  nt2_0 = t2_0;
  nt2_1 = t2_1;
  nt2_2 = !t2_2;
  HPC3(nt0_0, nt0_1, nt0_2, nt1_0, nt1_1, nt1_2, &t3_0, &t3_1, &t3_2, rand_10, rand_11, rand_12, rand_13, rand_14, rand_15);
  HPC2(nt1_0, nt1_1, nt1_2, n3_0, n3_1, n3_2, &t4_0, &t4_1, &t4_2, rand_16, rand_17, rand_18);
  nt3_0 = t3_0;
  nt3_1 = t3_1;
  nt3_2 = !t3_2;
  HPC2_swapped(nt2_0, nt2_1, nt2_2, nt3_0, nt3_1, nt3_2, &t5_0, &t5_1, &t5_2, rand_19, rand_20, rand_21);
  nt4_0 = t4_0;
  nt4_1 = t4_1;
  nt4_2 = !t4_2;
  nt5_0 = t5_0;
  nt5_1 = t5_1;
  nt5_2 = !t5_2;
  o6_val_0 = t0_0 ^ i4_0;
  o6_val_1 = t0_1 ^ i4_1;
  o6_val_2 = t0_2 ^ i4_2;
  o5_val_0 = t1_0 ^ i0_0;
  o5_val_1 = t1_1 ^ i0_1;
  o5_val_2 = t1_2 ^ i0_2;
  o2_val_0 = t2_0 ^ i6_0;
  o2_val_1 = t2_1 ^ i6_1;
  o2_val_2 = t2_2 ^ i6_2;
  o7_val_0 = t3_0 ^ i5_0;
  o7_val_1 = t3_1 ^ i5_1;
  o7_val_2 = t3_2 ^ i5_2;
  HPC2o_swapped(nt4_0, nt4_1, nt4_2, nt5_0, nt5_1, nt5_2, i2_0, i2_1, i2_2, &t7_0, &t7_1, &t7_2, rand_22, rand_23, rand_24);
  HPC2o(nt3_0, nt3_1, nt3_2, nt0_0, nt0_1, nt0_2, i3_0, i3_1, i3_2, &t6_0, &t6_1, &t6_2, rand_25, rand_26, rand_27);
  o1_val_0 = t5_0 ^ i7_0;
  o1_val_1 = t5_1 ^ i7_1;
  o1_val_2 = t5_2 ^ i7_2;
  o3_val_0 = t4_0 ^ i1_0;
  o3_val_1 = t4_1 ^ i1_1;
  o3_val_2 = t4_2 ^ i1_2;
  *o0_0 = t7_0;
  *o0_1 = t7_1;
  *o0_2 = t7_2;
  *o1_0 = o1_val_0;
  *o1_1 = o1_val_1;
  *o1_2 = o1_val_2;
  *o2_0 = o2_val_0;
  *o2_1 = o2_val_1;
  *o2_2 = o2_val_2;
  *o3_0 = o3_val_0;
  *o3_1 = o3_val_1;
  *o3_2 = o3_val_2;
  *o4_0 = t6_0;
  *o4_1 = t6_1;
  *o4_2 = t6_2;
  *o5_0 = o5_val_0;
  *o5_1 = o5_val_1;
  *o5_2 = o5_val_2;
  *o6_0 = o6_val_0;
  *o6_1 = o6_val_1;
  *o6_2 = o6_val_2;
  *o7_0 = o7_val_0;
  *o7_1 = o7_val_1;
  *o7_2 = o7_val_2;
}

