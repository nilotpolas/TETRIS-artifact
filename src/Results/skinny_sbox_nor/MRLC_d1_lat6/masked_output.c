// === GADGET DEFINITIONS ===

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
void sbox(_Bool i0_0, _Bool i0_1, _Bool i1_0, _Bool i1_1, _Bool i2_0, _Bool i2_1, _Bool i3_0, _Bool i3_1, _Bool i4_0, _Bool i4_1, _Bool i5_0, _Bool i5_1, _Bool i6_0, _Bool i6_1, _Bool i7_0, _Bool i7_1, _Bool dec_1, _Bool *o0_0, _Bool *o0_1, _Bool *o1_0, _Bool *o1_1, _Bool *o2_0, _Bool *o2_1, _Bool *o3_0, _Bool *o3_1, _Bool *o4_0, _Bool *o4_1, _Bool *o5_0, _Bool *o5_1, _Bool *o6_0, _Bool *o6_1, _Bool *o7_0, _Bool *o7_1, int rand_5, int rand_6, int rand_2, int rand_7, int rand_1, int rand_3, int rand_8, int rand_4)
{
  _Bool n1_0;
  _Bool n1_1;
  _Bool n2_0;
  _Bool n2_1;
  _Bool n3_0;
  _Bool n3_1;
  _Bool n6_0;
  _Bool n6_1;
  _Bool n7_0;
  _Bool n7_1;
  _Bool t0_0;
  _Bool t0_1;
  _Bool t1_0;
  _Bool t1_1;
  _Bool t2_0;
  _Bool t2_1;
  _Bool t3_0;
  _Bool t3_1;
  _Bool t4_0;
  _Bool t4_1;
  _Bool t5_0;
  _Bool t5_1;
  _Bool t6_0;
  _Bool t6_1;
  _Bool t7_0;
  _Bool t7_1;
  _Bool nt0_0;
  _Bool nt0_1;
  _Bool nt1_0;
  _Bool nt1_1;
  _Bool nt2_0;
  _Bool nt2_1;
  _Bool nt3_0;
  _Bool nt3_1;
  _Bool nt4_0;
  _Bool nt4_1;
  _Bool nt5_0;
  _Bool nt5_1;
  _Bool o1_val_0;
  _Bool o1_val_1;
  _Bool o2_val_0;
  _Bool o2_val_1;
  _Bool o3_val_0;
  _Bool o3_val_1;
  _Bool o5_val_0;
  _Bool o5_val_1;
  _Bool o6_val_0;
  _Bool o6_val_1;
  _Bool o7_val_0;
  _Bool o7_val_1;
  n1_0 = i1_0;
  n1_1 = !i1_1;
  n2_0 = i2_0;
  n2_1 = !i2_1;
  n3_0 = i3_0;
  n3_1 = !i3_1;
  n6_0 = i6_0;
  n6_1 = !i6_1;
  n7_0 = i7_0;
  n7_1 = !i7_1;
  HPC2(n6_0, n6_1, n7_0, n7_1, &t0_0, &t0_1, rand_1);
  HPC2(n3_0, n3_1, n2_0, n2_1, &t1_0, &t1_1, rand_2);
  HPC2(n2_0, n2_1, n1_0, n1_1, &t2_0, &t2_1, rand_3);
  nt0_0 = t0_0;
  nt0_1 = !t0_1;
  nt1_0 = t1_0;
  nt1_1 = !t1_1;
  nt2_0 = t2_0;
  nt2_1 = !t2_1;
  HPC2(nt0_0, nt0_1, nt1_0, nt1_1, &t3_0, &t3_1, rand_4);
  HPC2(nt1_0, nt1_1, n3_0, n3_1, &t4_0, &t4_1, rand_5);
  nt3_0 = t3_0;
  nt3_1 = !t3_1;
  HPC2_swapped(nt2_0, nt2_1, nt3_0, nt3_1, &t5_0, &t5_1, rand_6);
  nt4_0 = t4_0;
  nt4_1 = !t4_1;
  nt5_0 = t5_0;
  nt5_1 = !t5_1;
  o6_val_0 = t0_0 ^ i4_0;
  o6_val_1 = t0_1 ^ i4_1;
  o5_val_0 = t1_0 ^ i0_0;
  o5_val_1 = t1_1 ^ i0_1;
  o2_val_0 = t2_0 ^ i6_0;
  o2_val_1 = t2_1 ^ i6_1;
  o7_val_0 = t3_0 ^ i5_0;
  o7_val_1 = t3_1 ^ i5_1;
  HPC2o_swapped(nt4_0, nt4_1, nt5_0, nt5_1, i2_0, i2_1, &t7_0, &t7_1, rand_7);
  HPC2o(nt3_0, nt3_1, nt0_0, nt0_1, i3_0, i3_1, &t6_0, &t6_1, rand_8);
  o1_val_0 = t5_0 ^ i7_0;
  o1_val_1 = t5_1 ^ i7_1;
  o3_val_0 = t4_0 ^ i1_0;
  o3_val_1 = t4_1 ^ i1_1;
  *o0_0 = t7_0;
  *o0_1 = t7_1;
  *o1_0 = o1_val_0;
  *o1_1 = o1_val_1;
  *o2_0 = o2_val_0;
  *o2_1 = o2_val_1;
  *o3_0 = o3_val_0;
  *o3_1 = o3_val_1;
  *o4_0 = t6_0;
  *o4_1 = t6_1;
  *o5_0 = o5_val_0;
  *o5_1 = o5_val_1;
  *o6_0 = o6_val_0;
  *o6_1 = o6_val_1;
  *o7_0 = o7_val_0;
  *o7_1 = o7_val_1;
}

