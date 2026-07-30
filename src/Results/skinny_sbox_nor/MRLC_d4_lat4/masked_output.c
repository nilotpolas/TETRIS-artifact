// === GADGET DEFINITIONS ===

// --- hpc3 ---

void hpc3_same_shares_4_order(_Bool a_share, _Bool b_share, _Bool * u_share) {
    * u_share  = a_share & b_share;
}

void hpc3_v_4_order(_Bool a_share, _Bool b_share, _Bool * v_share, _Bool rand){
    _Bool temp;
    temp = reg(b_share ^ rand);
    *v_share = temp & a_share;
}

void hpc3_w_4_order(_Bool a_share, _Bool rand, _Bool prand, _Bool * w_share){
    _Bool temp;
    _Bool a_share_neg;
    a_share_neg = !(a_share);
    temp = a_share_neg & rand;
    *w_share = reg(temp ^ prand);
}

void hpc3_xor_vw_4_order(_Bool v_share, _Bool w_share, _Bool * u_share){
    *u_share = v_share ^ w_share;
}

void HPC3(_Bool a0, _Bool a1, _Bool a2, _Bool a3, _Bool a4, _Bool b0, _Bool b1, _Bool b2, _Bool b3, _Bool b4, _Bool* c0, _Bool* c1, _Bool* c2, _Bool* c3, _Bool* c4, _Bool r01, _Bool r02, _Bool r03, _Bool r04, _Bool r12, _Bool r13, _Bool r14, _Bool r23, _Bool r24, _Bool r34, _Bool p01, _Bool p02, _Bool p03, _Bool p04, _Bool p12, _Bool p13, _Bool p14, _Bool p23, _Bool p24, _Bool p34)
{
	_Bool u00, u01, u02, u03, u04, u10, u11, u12, u13, u14, u20, u21, u22, u23, u24, u30, u31, u32, u33, u34, u40, u41, u42, u43, u44;
	_Bool v01, v02, v03, v04, v10, v12, v13, v14, v20, v21, v23, v24, v30, v31, v32, v34, v40, v41, v42, v43;
	_Bool w01, w02, w03, w04, w10, w12, w13, w14, w20, w21, w23, w24, w30, w31, w32, w34, w40, w41, w42, w43;

	hpc3_same_shares_4_order(a0, b0, &u00);

	hpc3_v_4_order(a0, b1, &v01 , r01);
	hpc3_w_4_order(a0, r01, p01, &w01);
	hpc3_xor_vw_4_order(v01, w01, &u01);

	hpc3_v_4_order(a0, b2, &v02 , r02);
	hpc3_w_4_order(a0, r02, p02, &w02);
	hpc3_xor_vw_4_order(v02, w02, &u02);

	hpc3_v_4_order(a0, b3, &v03 , r03);
	hpc3_w_4_order(a0, r03, p03, &w03);
	hpc3_xor_vw_4_order(v03, w03, &u03);

	hpc3_v_4_order(a0, b4, &v04 , r04);
	hpc3_w_4_order(a0, r04, p04, &w04);
	hpc3_xor_vw_4_order(v04, w04, &u04);

	hpc3_v_4_order(a1, b0, &v10 , r01);
	hpc3_w_4_order(a1, r01, p01, &w10);
	hpc3_xor_vw_4_order(v10, w10, &u10);

	hpc3_same_shares_4_order(a1, b1, &u11);

	hpc3_v_4_order(a1, b2, &v12 , r12);
	hpc3_w_4_order(a1, r12, p12, &w12);
	hpc3_xor_vw_4_order(v12, w12, &u12);

	hpc3_v_4_order(a1, b3, &v13 , r13);
	hpc3_w_4_order(a1, r13, p13, &w13);
	hpc3_xor_vw_4_order(v13, w13, &u13);

	hpc3_v_4_order(a1, b4, &v14 , r14);
	hpc3_w_4_order(a1, r14, p14, &w14);
	hpc3_xor_vw_4_order(v14, w14, &u14);

	hpc3_v_4_order(a2, b0, &v20 , r02);
	hpc3_w_4_order(a2, r02, p02, &w20);
	hpc3_xor_vw_4_order(v20, w20, &u20);

	hpc3_v_4_order(a2, b1, &v21 , r12);
	hpc3_w_4_order(a2, r12, p12, &w21);
	hpc3_xor_vw_4_order(v21, w21, &u21);

	hpc3_same_shares_4_order(a2, b2, &u22);

	hpc3_v_4_order(a2, b3, &v23 , r23);
	hpc3_w_4_order(a2, r23, p23, &w23);
	hpc3_xor_vw_4_order(v23, w23, &u23);

	hpc3_v_4_order(a2, b4, &v24 , r24);
	hpc3_w_4_order(a2, r24, p24, &w24);
	hpc3_xor_vw_4_order(v24, w24, &u24);

	hpc3_v_4_order(a3, b0, &v30 , r03);
	hpc3_w_4_order(a3, r03, p03, &w30);
	hpc3_xor_vw_4_order(v30, w30, &u30);

	hpc3_v_4_order(a3, b1, &v31 , r13);
	hpc3_w_4_order(a3, r13, p13, &w31);
	hpc3_xor_vw_4_order(v31, w31, &u31);

	hpc3_v_4_order(a3, b2, &v32 , r23);
	hpc3_w_4_order(a3, r23, p23, &w32);
	hpc3_xor_vw_4_order(v32, w32, &u32);

	hpc3_same_shares_4_order(a3, b3, &u33);

	hpc3_v_4_order(a3, b4, &v34 , r34);
	hpc3_w_4_order(a3, r34, p34, &w34);
	hpc3_xor_vw_4_order(v34, w34, &u34);

	hpc3_v_4_order(a4, b0, &v40 , r04);
	hpc3_w_4_order(a4, r04, p04, &w40);
	hpc3_xor_vw_4_order(v40, w40, &u40);

	hpc3_v_4_order(a4, b1, &v41 , r14);
	hpc3_w_4_order(a4, r14, p14, &w41);
	hpc3_xor_vw_4_order(v41, w41, &u41);

	hpc3_v_4_order(a4, b2, &v42 , r24);
	hpc3_w_4_order(a4, r24, p24, &w42);
	hpc3_xor_vw_4_order(v42, w42, &u42);

	hpc3_v_4_order(a4, b3, &v43 , r34);
	hpc3_w_4_order(a4, r34, p34, &w43);
	hpc3_xor_vw_4_order(v43, w43, &u43);

	hpc3_same_shares_4_order(a4, b4, &u44);

	_Bool t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;
	t1 = u00 ^ u01;
	t2 = t1 ^ u02;
	t3 = t2 ^ u03;
	*c0 = t3 ^ u04;

	t4 = u10 ^ u11;
	t5 = t4 ^ u12;
	t6 = t5 ^ u13;
	*c1 = t6 ^ u14;

	t7 = u20 ^ u21;
	t8 = t7 ^ u22;
	t9 = t8 ^ u23;
	*c2 = t9 ^ u24;

	t10 = u30 ^ u31;
	t11 = t10 ^ u32;
	t12 = t11 ^ u33;
	*c3 = t12 ^ u34;

	t13 = u40 ^ u41;
	t14 = t13 ^ u42;
	t15 = t14 ^ u43;
	*c4 = t15 ^ u44;

}


// --- hpc2_swapped ---

void hpc2sw_same_shares_4_order(_Bool a_share, _Bool b_share, _Bool * u_share) {
    *u_share = a_share & b_share;
}

void hpc2sw_v_4_order(_Bool a_share, _Bool b_share, _Bool * v_share, _Bool rand) {
    _Bool temp;
    temp = reg(b_share ^ rand);
    *v_share = reg(temp & a_share);
}

void hpc2sw_w_4_order(_Bool a_share, _Bool rand, _Bool * w_share) {
    _Bool a_neg;
    a_neg = !(a_share);
    *w_share = reg(a_neg & rand);
}

void hpc2sw_xor_vw_4_order(_Bool v_share, _Bool w_share, _Bool * u_share) {
    *u_share = v_share ^ w_share;
}

void HPC2_swapped(_Bool a0, _Bool a1, _Bool a2, _Bool a3, _Bool a4, _Bool b0, _Bool b1, _Bool b2, _Bool b3, _Bool b4, _Bool * c0, _Bool * c1, _Bool * c2, _Bool * c3, _Bool * c4, _Bool rand_01, _Bool rand_02, _Bool rand_03, _Bool rand_04, _Bool rand_12, _Bool rand_13, _Bool rand_14, _Bool rand_23, _Bool rand_24, _Bool rand_34)
{
	_Bool u00, u01, u02, u03, u04, u10, u11, u12, u13, u14, u20, u21, u22, u23, u24, u30, u31, u32, u33, u34, u40, u41, u42, u43, u44;
	_Bool v01, v02, v03, v04, v10, v12, v13, v14, v20, v21, v23, v24, v30, v31, v32, v34, v40, v41, v42, v43;

	_Bool w01, w02, w03, w04, w10, w12, w13, w14, w20, w21, w23, w24, w30, w31, w32, w34, w40, w41, w42, w43;

	hpc2sw_same_shares_4_order(a0, b0, &u00);
	hpc2sw_v_4_order(b0, a1, &v01, rand_01);
	hpc2sw_w_4_order(b0, rand_01, &w01);
	hpc2sw_xor_vw_4_order(v01, w01, &u01);

	hpc2sw_v_4_order(b0, a2, &v02, rand_02);
	hpc2sw_w_4_order(b0, rand_02, &w02);
	hpc2sw_xor_vw_4_order(v02, w02, &u02);

	hpc2sw_v_4_order(b0, a3, &v03, rand_03);
	hpc2sw_w_4_order(b0, rand_03, &w03);
	hpc2sw_xor_vw_4_order(v03, w03, &u03);

	hpc2sw_v_4_order(b0, a4, &v04, rand_04);
	hpc2sw_w_4_order(b0, rand_04, &w04);
	hpc2sw_xor_vw_4_order(v04, w04, &u04);

	hpc2sw_v_4_order(b1, a0, &v10, rand_01);
	hpc2sw_w_4_order(b1, rand_01, &w10);
	hpc2sw_xor_vw_4_order(v10, w10, &u10);

	hpc2sw_same_shares_4_order(a1, b1, &u11);
	hpc2sw_v_4_order(b1, a2, &v12, rand_12);
	hpc2sw_w_4_order(b1, rand_12, &w12);
	hpc2sw_xor_vw_4_order(v12, w12, &u12);

	hpc2sw_v_4_order(b1, a3, &v13, rand_13);
	hpc2sw_w_4_order(b1, rand_13, &w13);
	hpc2sw_xor_vw_4_order(v13, w13, &u13);

	hpc2sw_v_4_order(b1, a4, &v14, rand_14);
	hpc2sw_w_4_order(b1, rand_14, &w14);
	hpc2sw_xor_vw_4_order(v14, w14, &u14);

	hpc2sw_v_4_order(b2, a0, &v20, rand_02);
	hpc2sw_w_4_order(b2, rand_02, &w20);
	hpc2sw_xor_vw_4_order(v20, w20, &u20);

	hpc2sw_v_4_order(b2, a1, &v21, rand_12);
	hpc2sw_w_4_order(b2, rand_12, &w21);
	hpc2sw_xor_vw_4_order(v21, w21, &u21);

	hpc2sw_same_shares_4_order(a2, b2, &u22);
	hpc2sw_v_4_order(b2, a3, &v23, rand_23);
	hpc2sw_w_4_order(b2, rand_23, &w23);
	hpc2sw_xor_vw_4_order(v23, w23, &u23);

	hpc2sw_v_4_order(b2, a4, &v24, rand_24);
	hpc2sw_w_4_order(b2, rand_24, &w24);
	hpc2sw_xor_vw_4_order(v24, w24, &u24);

	hpc2sw_v_4_order(b3, a0, &v30, rand_03);
	hpc2sw_w_4_order(b3, rand_03, &w30);
	hpc2sw_xor_vw_4_order(v30, w30, &u30);

	hpc2sw_v_4_order(b3, a1, &v31, rand_13);
	hpc2sw_w_4_order(b3, rand_13, &w31);
	hpc2sw_xor_vw_4_order(v31, w31, &u31);

	hpc2sw_v_4_order(b3, a2, &v32, rand_23);
	hpc2sw_w_4_order(b3, rand_23, &w32);
	hpc2sw_xor_vw_4_order(v32, w32, &u32);

	hpc2sw_same_shares_4_order(a3, b3, &u33);
	hpc2sw_v_4_order(b3, a4, &v34, rand_34);
	hpc2sw_w_4_order(b3, rand_34, &w34);
	hpc2sw_xor_vw_4_order(v34, w34, &u34);

	hpc2sw_v_4_order(b4, a0, &v40, rand_04);
	hpc2sw_w_4_order(b4, rand_04, &w40);
	hpc2sw_xor_vw_4_order(v40, w40, &u40);

	hpc2sw_v_4_order(b4, a1, &v41, rand_14);
	hpc2sw_w_4_order(b4, rand_14, &w41);
	hpc2sw_xor_vw_4_order(v41, w41, &u41);

	hpc2sw_v_4_order(b4, a2, &v42, rand_24);
	hpc2sw_w_4_order(b4, rand_24, &w42);
	hpc2sw_xor_vw_4_order(v42, w42, &u42);

	hpc2sw_v_4_order(b4, a3, &v43, rand_34);
	hpc2sw_w_4_order(b4, rand_34, &w43);
	hpc2sw_xor_vw_4_order(v43, w43, &u43);

	hpc2sw_same_shares_4_order(a4, b4, &u44);
	_Bool t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

	t1 = u00 ^ u01;
	t2 = t1 ^ u02;
	t3 = t2 ^ u03;
	*c0 = t3 ^ u04;

	t4 = u10 ^ u11;
	t5 = t4 ^ u12;
	t6 = t5 ^ u13;
	*c1 = t6 ^ u14;

	t7 = u20 ^ u21;
	t8 = t7 ^ u22;
	t9 = t8 ^ u23;
	*c2 = t9 ^ u24;

	t10 = u30 ^ u31;
	t11 = t10 ^ u32;
	t12 = t11 ^ u33;
	*c3 = t12 ^ u34;

	t13 = u40 ^ u41;
	t14 = t13 ^ u42;
	t15 = t14 ^ u43;
	*c4 = t15 ^ u44;

}


// --- hpc2o ---

void hpc2o_first_half_4_order(_Bool a_share, _Bool b_share, _Bool w_share, _Bool rand, _Bool *out_share) {
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

void hpc2o_v_4_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand) {
    _Bool xor_br;
    _Bool temp;
    _Bool and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br); // This remains an R register in Algo 6
    
    and_ta = temp & a_share;
    *v_share = reg(and_ta);
}

void hpc2o_w_4_order(_Bool a_share, _Bool rand, _Bool *w_share) {
    _Bool a_neg;
    _Bool and_ar;

    a_neg = !a_share;
    
    and_ar = a_neg & rand;
    *w_share = reg(and_ar);
}

void hpc2o_xor_vw_4_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share ^ w_share;
}

void hpc2o_or_vw_4_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share | w_share;
}
void HPC2o(_Bool a0, _Bool a1, _Bool a2, _Bool a3, _Bool a4, _Bool b0, _Bool b1, _Bool b2, _Bool b3, _Bool b4, _Bool w0, _Bool w1, _Bool w2, _Bool w3, _Bool w4, _Bool * c0, _Bool * c1, _Bool * c2, _Bool * c3, _Bool * c4, _Bool rand_01, _Bool rand_02, _Bool rand_03, _Bool rand_04, _Bool rand_12, _Bool rand_13, _Bool rand_14, _Bool rand_23, _Bool rand_24, _Bool rand_34)
{
	_Bool u01, u02, u03, u04, u10, u12, u13, u14, u20, u21, u23, u24, u30, u31, u32, u34, u40, u41, u42, u43;
	_Bool v01, v02, v03, v04, v10, v12, v13, v14, v20, v21, v23, v24, v30, v31, v32, v34, v40, v41, v42, v43;
	_Bool w01, w02, w03, w04, w10, w12, w13, w14, w20, w21, w23, w24, w30, w31, w32, w34, w40, w41, w42, w43;
	_Bool t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

	hpc2o_first_half_4_order(a0, b0, w0, rand_01, &w01);
	hpc2o_v_4_order(a0, b1, &v01, rand_01);
	hpc2o_xor_vw_4_order(v01, w01, &u01);

	hpc2o_w_4_order(a0, rand_02, &w02);
	hpc2o_v_4_order(a0, b2, &v02, rand_02);
	hpc2o_or_vw_4_order(v02, w02, &u02);

	hpc2o_w_4_order(a0, rand_03, &w03);
	hpc2o_v_4_order(a0, b3, &v03, rand_03);
	hpc2o_or_vw_4_order(v03, w03, &u03);

	hpc2o_w_4_order(a0, rand_04, &w04);
	hpc2o_v_4_order(a0, b4, &v04, rand_04);
	hpc2o_or_vw_4_order(v04, w04, &u04);

	hpc2o_first_half_4_order(a1, b1, w1, rand_01, &w10);
	hpc2o_v_4_order(a1, b0, &v10, rand_01);
	hpc2o_xor_vw_4_order(v10, w10, &u10);

	hpc2o_w_4_order(a1, rand_12, &w12);
	hpc2o_v_4_order(a1, b2, &v12, rand_12);
	hpc2o_or_vw_4_order(v12, w12, &u12);

	hpc2o_w_4_order(a1, rand_13, &w13);
	hpc2o_v_4_order(a1, b3, &v13, rand_13);
	hpc2o_or_vw_4_order(v13, w13, &u13);

	hpc2o_w_4_order(a1, rand_14, &w14);
	hpc2o_v_4_order(a1, b4, &v14, rand_14);
	hpc2o_or_vw_4_order(v14, w14, &u14);

	hpc2o_first_half_4_order(a2, b2, w2, rand_02, &w20);
	hpc2o_v_4_order(a2, b0, &v20, rand_02);
	hpc2o_xor_vw_4_order(v20, w20, &u20);

	hpc2o_w_4_order(a2, rand_12, &w21);
	hpc2o_v_4_order(a2, b1, &v21, rand_12);
	hpc2o_or_vw_4_order(v21, w21, &u21);

	hpc2o_w_4_order(a2, rand_23, &w23);
	hpc2o_v_4_order(a2, b3, &v23, rand_23);
	hpc2o_or_vw_4_order(v23, w23, &u23);

	hpc2o_w_4_order(a2, rand_24, &w24);
	hpc2o_v_4_order(a2, b4, &v24, rand_24);
	hpc2o_or_vw_4_order(v24, w24, &u24);

	hpc2o_first_half_4_order(a3, b3, w3, rand_03, &w30);
	hpc2o_v_4_order(a3, b0, &v30, rand_03);
	hpc2o_xor_vw_4_order(v30, w30, &u30);

	hpc2o_w_4_order(a3, rand_13, &w31);
	hpc2o_v_4_order(a3, b1, &v31, rand_13);
	hpc2o_or_vw_4_order(v31, w31, &u31);

	hpc2o_w_4_order(a3, rand_23, &w32);
	hpc2o_v_4_order(a3, b2, &v32, rand_23);
	hpc2o_or_vw_4_order(v32, w32, &u32);

	hpc2o_w_4_order(a3, rand_34, &w34);
	hpc2o_v_4_order(a3, b4, &v34, rand_34);
	hpc2o_or_vw_4_order(v34, w34, &u34);

	hpc2o_first_half_4_order(a4, b4, w4, rand_04, &w40);
	hpc2o_v_4_order(a4, b0, &v40, rand_04);
	hpc2o_xor_vw_4_order(v40, w40, &u40);

	hpc2o_w_4_order(a4, rand_14, &w41);
	hpc2o_v_4_order(a4, b1, &v41, rand_14);
	hpc2o_or_vw_4_order(v41, w41, &u41);

	hpc2o_w_4_order(a4, rand_24, &w42);
	hpc2o_v_4_order(a4, b2, &v42, rand_24);
	hpc2o_or_vw_4_order(v42, w42, &u42);

	hpc2o_w_4_order(a4, rand_34, &w43);
	hpc2o_v_4_order(a4, b3, &v43, rand_34);
	hpc2o_or_vw_4_order(v43, w43, &u43);

	t1 = u01 ^ u02;
	t2 = t1 ^ u03;
	*c0 = t2 ^ u04;

	t3 = u10 ^ u12;
	t4 = t3 ^ u13;
	*c1 = t4 ^ u14;

	t5 = u20 ^ u21;
	t6 = t5 ^ u23;
	*c2 = t6 ^ u24;

	t7 = u30 ^ u31;
	t8 = t7 ^ u32;
	*c3 = t8 ^ u34;

	t9 = u40 ^ u41;
	t10 = t9 ^ u42;
	*c4 = t10 ^ u43;

}


// --- hpc2o_swapped ---

void hpc2osw_first_half_4_order(_Bool a_share, _Bool b_share, _Bool w_share, _Bool rand, _Bool *out_share) {
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

void hpc2osw_v_4_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand) {
    _Bool xor_br;
    _Bool temp;
    _Bool and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br);

    and_ta = temp & a_share;
    *v_share = reg(and_ta);
}

void hpc2osw_w_4_order(_Bool a_share, _Bool rand, _Bool *w_share) {
    _Bool a_neg;
    _Bool and_ar;

    a_neg = !a_share;

    and_ar = a_neg & rand;
    *w_share = reg(and_ar);
}

void hpc2osw_xor_vw_4_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share ^ w_share;
}

void hpc2osw_or_vw_4_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share | w_share;
}
void HPC2o_swapped(_Bool a0, _Bool a1, _Bool a2, _Bool a3, _Bool a4, _Bool b0, _Bool b1, _Bool b2, _Bool b3, _Bool b4, _Bool w0, _Bool w1, _Bool w2, _Bool w3, _Bool w4, _Bool * c0, _Bool * c1, _Bool * c2, _Bool * c3, _Bool * c4, _Bool rand_01, _Bool rand_02, _Bool rand_03, _Bool rand_04, _Bool rand_12, _Bool rand_13, _Bool rand_14, _Bool rand_23, _Bool rand_24, _Bool rand_34)
{
	_Bool u01, u02, u03, u04, u10, u12, u13, u14, u20, u21, u23, u24, u30, u31, u32, u34, u40, u41, u42, u43;
	_Bool v01, v02, v03, v04, v10, v12, v13, v14, v20, v21, v23, v24, v30, v31, v32, v34, v40, v41, v42, v43;
	_Bool w01, w02, w03, w04, w10, w12, w13, w14, w20, w21, w23, w24, w30, w31, w32, w34, w40, w41, w42, w43;
	_Bool t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

	hpc2osw_first_half_4_order(b0, a0, w0, rand_01, &w01);
	hpc2osw_v_4_order(b0, a1, &v01, rand_01);
	hpc2osw_xor_vw_4_order(v01, w01, &u01);

	hpc2osw_w_4_order(b0, rand_02, &w02);
	hpc2osw_v_4_order(b0, a2, &v02, rand_02);
	hpc2osw_or_vw_4_order(v02, w02, &u02);

	hpc2osw_w_4_order(b0, rand_03, &w03);
	hpc2osw_v_4_order(b0, a3, &v03, rand_03);
	hpc2osw_or_vw_4_order(v03, w03, &u03);

	hpc2osw_w_4_order(b0, rand_04, &w04);
	hpc2osw_v_4_order(b0, a4, &v04, rand_04);
	hpc2osw_or_vw_4_order(v04, w04, &u04);

	hpc2osw_first_half_4_order(b1, a1, w1, rand_01, &w10);
	hpc2osw_v_4_order(b1, a0, &v10, rand_01);
	hpc2osw_xor_vw_4_order(v10, w10, &u10);

	hpc2osw_w_4_order(b1, rand_12, &w12);
	hpc2osw_v_4_order(b1, a2, &v12, rand_12);
	hpc2osw_or_vw_4_order(v12, w12, &u12);

	hpc2osw_w_4_order(b1, rand_13, &w13);
	hpc2osw_v_4_order(b1, a3, &v13, rand_13);
	hpc2osw_or_vw_4_order(v13, w13, &u13);

	hpc2osw_w_4_order(b1, rand_14, &w14);
	hpc2osw_v_4_order(b1, a4, &v14, rand_14);
	hpc2osw_or_vw_4_order(v14, w14, &u14);

	hpc2osw_first_half_4_order(b2, a2, w2, rand_02, &w20);
	hpc2osw_v_4_order(b2, a0, &v20, rand_02);
	hpc2osw_xor_vw_4_order(v20, w20, &u20);

	hpc2osw_w_4_order(b2, rand_12, &w21);
	hpc2osw_v_4_order(b2, a1, &v21, rand_12);
	hpc2osw_or_vw_4_order(v21, w21, &u21);

	hpc2osw_w_4_order(b2, rand_23, &w23);
	hpc2osw_v_4_order(b2, a3, &v23, rand_23);
	hpc2osw_or_vw_4_order(v23, w23, &u23);

	hpc2osw_w_4_order(b2, rand_24, &w24);
	hpc2osw_v_4_order(b2, a4, &v24, rand_24);
	hpc2osw_or_vw_4_order(v24, w24, &u24);

	hpc2osw_first_half_4_order(b3, a3, w3, rand_03, &w30);
	hpc2osw_v_4_order(b3, a0, &v30, rand_03);
	hpc2osw_xor_vw_4_order(v30, w30, &u30);

	hpc2osw_w_4_order(b3, rand_13, &w31);
	hpc2osw_v_4_order(b3, a1, &v31, rand_13);
	hpc2osw_or_vw_4_order(v31, w31, &u31);

	hpc2osw_w_4_order(b3, rand_23, &w32);
	hpc2osw_v_4_order(b3, a2, &v32, rand_23);
	hpc2osw_or_vw_4_order(v32, w32, &u32);

	hpc2osw_w_4_order(b3, rand_34, &w34);
	hpc2osw_v_4_order(b3, a4, &v34, rand_34);
	hpc2osw_or_vw_4_order(v34, w34, &u34);

	hpc2osw_first_half_4_order(b4, a4, w4, rand_04, &w40);
	hpc2osw_v_4_order(b4, a0, &v40, rand_04);
	hpc2osw_xor_vw_4_order(v40, w40, &u40);

	hpc2osw_w_4_order(b4, rand_14, &w41);
	hpc2osw_v_4_order(b4, a1, &v41, rand_14);
	hpc2osw_or_vw_4_order(v41, w41, &u41);

	hpc2osw_w_4_order(b4, rand_24, &w42);
	hpc2osw_v_4_order(b4, a2, &v42, rand_24);
	hpc2osw_or_vw_4_order(v42, w42, &u42);

	hpc2osw_w_4_order(b4, rand_34, &w43);
	hpc2osw_v_4_order(b4, a3, &v43, rand_34);
	hpc2osw_or_vw_4_order(v43, w43, &u43);

	t1 = u01 ^ u02;
	t2 = t1 ^ u03;
	*c0 = t2 ^ u04;

	t3 = u10 ^ u12;
	t4 = t3 ^ u13;
	*c1 = t4 ^ u14;

	t5 = u20 ^ u21;
	t6 = t5 ^ u23;
	*c2 = t6 ^ u24;

	t7 = u30 ^ u31;
	t8 = t7 ^ u32;
	*c3 = t8 ^ u34;

	t9 = u40 ^ u41;
	t10 = t9 ^ u42;
	*c4 = t10 ^ u43;

}


// --- hpc2 ---

void hpc2_same_shares_4_order(_Bool a_share, _Bool b_share, _Bool * u_share) {
    * u_share  = a_share & b_share;
}

void hpc2_v_4_order(_Bool a_share, _Bool b_share, _Bool * v_share, _Bool rand){
    _Bool temp; 
    temp = reg(b_share ^ rand);
    *v_share = reg(temp & a_share);
}

void hpc2_w_4_order(_Bool a_share, _Bool rand, _Bool * w_share){
    _Bool a_neg;
    a_neg = !(a_share);
    *w_share = reg(a_neg & rand);
}

void hpc2_xor_vw_4_order(_Bool v_share, _Bool w_share, _Bool * u_share){
    *u_share = v_share ^ w_share;
}

void HPC2(_Bool a0, _Bool a1, _Bool a2, _Bool a3, _Bool a4, _Bool b0, _Bool b1, _Bool b2, _Bool b3, _Bool b4, _Bool * c0, _Bool * c1, _Bool * c2, _Bool * c3, _Bool * c4, _Bool rand_01, _Bool rand_02, _Bool rand_03, _Bool rand_04, _Bool rand_12, _Bool rand_13, _Bool rand_14, _Bool rand_23, _Bool rand_24, _Bool rand_34)
{
	_Bool u00, u01, u02, u03, u04, u10, u11, u12, u13, u14, u20, u21, u22, u23, u24, u30, u31, u32, u33, u34, u40, u41, u42, u43, u44;
	_Bool v01, v02, v03, v04, v10, v12, v13, v14, v20, v21, v23, v24, v30, v31, v32, v34, v40, v41, v42, v43;

	_Bool w01, w02, w03, w04, w10, w12, w13, w14, w20, w21, w23, w24, w30, w31, w32, w34, w40, w41, w42, w43;

	hpc2_same_shares_4_order(a0, b0, &u00);
	hpc2_v_4_order(a0, b1, &v01 , rand_01);
	hpc2_w_4_order(a0, rand_01, &w01);
	hpc2_xor_vw_4_order(v01, w01, &u01);

	hpc2_v_4_order(a0, b2, &v02 , rand_02);
	hpc2_w_4_order(a0, rand_02, &w02);
	hpc2_xor_vw_4_order(v02, w02, &u02);

	hpc2_v_4_order(a0, b3, &v03 , rand_03);
	hpc2_w_4_order(a0, rand_03, &w03);
	hpc2_xor_vw_4_order(v03, w03, &u03);

	hpc2_v_4_order(a0, b4, &v04 , rand_04);
	hpc2_w_4_order(a0, rand_04, &w04);
	hpc2_xor_vw_4_order(v04, w04, &u04);

	hpc2_v_4_order(a1, b0, &v10 , rand_01);
	hpc2_w_4_order(a1, rand_01, &w10);
	hpc2_xor_vw_4_order(v10, w10, &u10);

	hpc2_same_shares_4_order(a1, b1, &u11);
	hpc2_v_4_order(a1, b2, &v12 , rand_12);
	hpc2_w_4_order(a1, rand_12, &w12);
	hpc2_xor_vw_4_order(v12, w12, &u12);

	hpc2_v_4_order(a1, b3, &v13 , rand_13);
	hpc2_w_4_order(a1, rand_13, &w13);
	hpc2_xor_vw_4_order(v13, w13, &u13);

	hpc2_v_4_order(a1, b4, &v14 , rand_14);
	hpc2_w_4_order(a1, rand_14, &w14);
	hpc2_xor_vw_4_order(v14, w14, &u14);

	hpc2_v_4_order(a2, b0, &v20 , rand_02);
	hpc2_w_4_order(a2, rand_02, &w20);
	hpc2_xor_vw_4_order(v20, w20, &u20);

	hpc2_v_4_order(a2, b1, &v21 , rand_12);
	hpc2_w_4_order(a2, rand_12, &w21);
	hpc2_xor_vw_4_order(v21, w21, &u21);

	hpc2_same_shares_4_order(a2, b2, &u22);
	hpc2_v_4_order(a2, b3, &v23 , rand_23);
	hpc2_w_4_order(a2, rand_23, &w23);
	hpc2_xor_vw_4_order(v23, w23, &u23);

	hpc2_v_4_order(a2, b4, &v24 , rand_24);
	hpc2_w_4_order(a2, rand_24, &w24);
	hpc2_xor_vw_4_order(v24, w24, &u24);

	hpc2_v_4_order(a3, b0, &v30 , rand_03);
	hpc2_w_4_order(a3, rand_03, &w30);
	hpc2_xor_vw_4_order(v30, w30, &u30);

	hpc2_v_4_order(a3, b1, &v31 , rand_13);
	hpc2_w_4_order(a3, rand_13, &w31);
	hpc2_xor_vw_4_order(v31, w31, &u31);

	hpc2_v_4_order(a3, b2, &v32 , rand_23);
	hpc2_w_4_order(a3, rand_23, &w32);
	hpc2_xor_vw_4_order(v32, w32, &u32);

	hpc2_same_shares_4_order(a3, b3, &u33);
	hpc2_v_4_order(a3, b4, &v34 , rand_34);
	hpc2_w_4_order(a3, rand_34, &w34);
	hpc2_xor_vw_4_order(v34, w34, &u34);

	hpc2_v_4_order(a4, b0, &v40 , rand_04);
	hpc2_w_4_order(a4, rand_04, &w40);
	hpc2_xor_vw_4_order(v40, w40, &u40);

	hpc2_v_4_order(a4, b1, &v41 , rand_14);
	hpc2_w_4_order(a4, rand_14, &w41);
	hpc2_xor_vw_4_order(v41, w41, &u41);

	hpc2_v_4_order(a4, b2, &v42 , rand_24);
	hpc2_w_4_order(a4, rand_24, &w42);
	hpc2_xor_vw_4_order(v42, w42, &u42);

	hpc2_v_4_order(a4, b3, &v43 , rand_34);
	hpc2_w_4_order(a4, rand_34, &w43);
	hpc2_xor_vw_4_order(v43, w43, &u43);

	hpc2_same_shares_4_order(a4, b4, &u44);
	_Bool t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

	t1 = u00 ^ u01;
	t2 = t1 ^ u02;
	t3 = t2 ^ u03;
	*c0 = t3 ^ u04;

	t4 = u10 ^ u11;
	t5 = t4 ^ u12;
	t6 = t5 ^ u13;
	*c1 = t6 ^ u14;

	t7 = u20 ^ u21;
	t8 = t7 ^ u22;
	t9 = t8 ^ u23;
	*c2 = t9 ^ u24;

	t10 = u30 ^ u31;
	t11 = t10 ^ u32;
	t12 = t11 ^ u33;
	*c3 = t12 ^ u34;

	t13 = u40 ^ u41;
	t14 = t13 ^ u42;
	t15 = t14 ^ u43;
	*c4 = t15 ^ u44;

}


// --- hpc3o ---

void hpc3o_first_half_4_order(_Bool a_share, _Bool b_share, _Bool w_share, _Bool rand, _Bool rand_prime, _Bool *out_share) {
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

void hpc3o_v_4_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand) {
    _Bool xor_br;
    _Bool temp;
    _Bool and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br); // This remains an R register in Algo 7
    
    and_ta = a_share & temp;
    *v_share = and_ta; // Notice: NO outer reg() here for HPC3o!
}

void hpc3o_w_4_order(_Bool a_share, _Bool rand, _Bool rand_prime, _Bool *w_share) {
    _Bool and_ar;
    _Bool xor_step1;

    // Notice: Algo 7 does not negate a_share in the else branch
    and_ar = a_share & rand;
    xor_step1 = and_ar ^ rand_prime;
    
    *w_share = reg(xor_step1);
}

void hpc3o_xor_vw_4_order(_Bool v_share, _Bool w_share, _Bool *u_share) {
    *u_share = v_share ^ w_share;
}
void HPC3o(_Bool a0, _Bool a1, _Bool a2, _Bool a3, _Bool a4, _Bool b0, _Bool b1, _Bool b2, _Bool b3, _Bool b4, _Bool w0, _Bool w1, _Bool w2, _Bool w3, _Bool w4, _Bool * c0, _Bool * c1, _Bool * c2, _Bool * c3, _Bool * c4, _Bool rand_01, _Bool rand_02, _Bool rand_03, _Bool rand_04, _Bool rand_12, _Bool rand_13, _Bool rand_14, _Bool rand_23, _Bool rand_24, _Bool rand_34, _Bool rand_prime_01, _Bool rand_prime_02, _Bool rand_prime_03, _Bool rand_prime_04, _Bool rand_prime_12, _Bool rand_prime_13, _Bool rand_prime_14, _Bool rand_prime_23, _Bool rand_prime_24, _Bool rand_prime_34)
{
	_Bool u01, u02, u03, u04, u10, u12, u13, u14, u20, u21, u23, u24, u30, u31, u32, u34, u40, u41, u42, u43;
	_Bool v01, v02, v03, v04, v10, v12, v13, v14, v20, v21, v23, v24, v30, v31, v32, v34, v40, v41, v42, v43;
	_Bool w01, w02, w03, w04, w10, w12, w13, w14, w20, w21, w23, w24, w30, w31, w32, w34, w40, w41, w42, w43;
	_Bool t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

	hpc3o_first_half_4_order(a0, b0, w0, rand_01, rand_prime_01, &w01);
	hpc3o_v_4_order(a0, b1, &v01, rand_01);
	hpc3o_xor_vw_4_order(v01, w01, &u01);

	hpc3o_w_4_order(a0, rand_02, rand_prime_02, &w02);
	hpc3o_v_4_order(a0, b2, &v02, rand_02);
	hpc3o_xor_vw_4_order(v02, w02, &u02);

	hpc3o_w_4_order(a0, rand_03, rand_prime_03, &w03);
	hpc3o_v_4_order(a0, b3, &v03, rand_03);
	hpc3o_xor_vw_4_order(v03, w03, &u03);

	hpc3o_w_4_order(a0, rand_04, rand_prime_04, &w04);
	hpc3o_v_4_order(a0, b4, &v04, rand_04);
	hpc3o_xor_vw_4_order(v04, w04, &u04);

	hpc3o_first_half_4_order(a1, b1, w1, rand_01, rand_prime_01, &w10);
	hpc3o_v_4_order(a1, b0, &v10, rand_01);
	hpc3o_xor_vw_4_order(v10, w10, &u10);

	hpc3o_w_4_order(a1, rand_12, rand_prime_12, &w12);
	hpc3o_v_4_order(a1, b2, &v12, rand_12);
	hpc3o_xor_vw_4_order(v12, w12, &u12);

	hpc3o_w_4_order(a1, rand_13, rand_prime_13, &w13);
	hpc3o_v_4_order(a1, b3, &v13, rand_13);
	hpc3o_xor_vw_4_order(v13, w13, &u13);

	hpc3o_w_4_order(a1, rand_14, rand_prime_14, &w14);
	hpc3o_v_4_order(a1, b4, &v14, rand_14);
	hpc3o_xor_vw_4_order(v14, w14, &u14);

	hpc3o_first_half_4_order(a2, b2, w2, rand_02, rand_prime_02, &w20);
	hpc3o_v_4_order(a2, b0, &v20, rand_02);
	hpc3o_xor_vw_4_order(v20, w20, &u20);

	hpc3o_w_4_order(a2, rand_12, rand_prime_12, &w21);
	hpc3o_v_4_order(a2, b1, &v21, rand_12);
	hpc3o_xor_vw_4_order(v21, w21, &u21);

	hpc3o_w_4_order(a2, rand_23, rand_prime_23, &w23);
	hpc3o_v_4_order(a2, b3, &v23, rand_23);
	hpc3o_xor_vw_4_order(v23, w23, &u23);

	hpc3o_w_4_order(a2, rand_24, rand_prime_24, &w24);
	hpc3o_v_4_order(a2, b4, &v24, rand_24);
	hpc3o_xor_vw_4_order(v24, w24, &u24);

	hpc3o_first_half_4_order(a3, b3, w3, rand_03, rand_prime_03, &w30);
	hpc3o_v_4_order(a3, b0, &v30, rand_03);
	hpc3o_xor_vw_4_order(v30, w30, &u30);

	hpc3o_w_4_order(a3, rand_13, rand_prime_13, &w31);
	hpc3o_v_4_order(a3, b1, &v31, rand_13);
	hpc3o_xor_vw_4_order(v31, w31, &u31);

	hpc3o_w_4_order(a3, rand_23, rand_prime_23, &w32);
	hpc3o_v_4_order(a3, b2, &v32, rand_23);
	hpc3o_xor_vw_4_order(v32, w32, &u32);

	hpc3o_w_4_order(a3, rand_34, rand_prime_34, &w34);
	hpc3o_v_4_order(a3, b4, &v34, rand_34);
	hpc3o_xor_vw_4_order(v34, w34, &u34);

	hpc3o_first_half_4_order(a4, b4, w4, rand_04, rand_prime_04, &w40);
	hpc3o_v_4_order(a4, b0, &v40, rand_04);
	hpc3o_xor_vw_4_order(v40, w40, &u40);

	hpc3o_w_4_order(a4, rand_14, rand_prime_14, &w41);
	hpc3o_v_4_order(a4, b1, &v41, rand_14);
	hpc3o_xor_vw_4_order(v41, w41, &u41);

	hpc3o_w_4_order(a4, rand_24, rand_prime_24, &w42);
	hpc3o_v_4_order(a4, b2, &v42, rand_24);
	hpc3o_xor_vw_4_order(v42, w42, &u42);

	hpc3o_w_4_order(a4, rand_34, rand_prime_34, &w43);
	hpc3o_v_4_order(a4, b3, &v43, rand_34);
	hpc3o_xor_vw_4_order(v43, w43, &u43);

	t1 = u01 ^ u02;
	t2 = t1 ^ u03;
	*c0 = t2 ^ u04;

	t3 = u10 ^ u12;
	t4 = t3 ^ u13;
	*c1 = t4 ^ u14;

	t5 = u20 ^ u21;
	t6 = t5 ^ u23;
	*c2 = t6 ^ u24;

	t7 = u30 ^ u31;
	t8 = t7 ^ u32;
	*c3 = t8 ^ u34;

	t9 = u40 ^ u41;
	t10 = t9 ^ u42;
	*c4 = t10 ^ u43;

}


// === TRANSFORMED CIRCUIT ===
void sbox(_Bool i0_0, _Bool i0_1, _Bool i0_2, _Bool i0_3, _Bool i0_4, _Bool i1_0, _Bool i1_1, _Bool i1_2, _Bool i1_3, _Bool i1_4, _Bool i2_0, _Bool i2_1, _Bool i2_2, _Bool i2_3, _Bool i2_4, _Bool i3_0, _Bool i3_1, _Bool i3_2, _Bool i3_3, _Bool i3_4, _Bool i4_0, _Bool i4_1, _Bool i4_2, _Bool i4_3, _Bool i4_4, _Bool i5_0, _Bool i5_1, _Bool i5_2, _Bool i5_3, _Bool i5_4, _Bool i6_0, _Bool i6_1, _Bool i6_2, _Bool i6_3, _Bool i6_4, _Bool i7_0, _Bool i7_1, _Bool i7_2, _Bool i7_3, _Bool i7_4, _Bool dec_1, _Bool *o0_0, _Bool *o0_1, _Bool *o0_2, _Bool *o0_3, _Bool *o0_4, _Bool *o1_0, _Bool *o1_1, _Bool *o1_2, _Bool *o1_3, _Bool *o1_4, _Bool *o2_0, _Bool *o2_1, _Bool *o2_2, _Bool *o2_3, _Bool *o2_4, _Bool *o3_0, _Bool *o3_1, _Bool *o3_2, _Bool *o3_3, _Bool *o3_4, _Bool *o4_0, _Bool *o4_1, _Bool *o4_2, _Bool *o4_3, _Bool *o4_4, _Bool *o5_0, _Bool *o5_1, _Bool *o5_2, _Bool *o5_3, _Bool *o5_4, _Bool *o6_0, _Bool *o6_1, _Bool *o6_2, _Bool *o6_3, _Bool *o6_4, _Bool *o7_0, _Bool *o7_1, _Bool *o7_2, _Bool *o7_3, _Bool *o7_4, int rand_60, int rand_61, int rand_62, int rand_63, int rand_64, int rand_65, int rand_66, int rand_67, int rand_68, int rand_69, int rand_70, int rand_71, int rand_72, int rand_73, int rand_2, int rand_74, int rand_3, int rand_75, int rand_4, int rand_76, int rand_5, int rand_77, int rand_6, int rand_78, int rand_7, int rand_79, int rand_8, int rand_80, int rand_9, int rand_81, int rand_10, int rand_82, int rand_11, int rand_83, int rand_12, int rand_84, int rand_13, int rand_85, int rand_14, int rand_86, int rand_15, int rand_87, int rand_16, int rand_88, int rand_17, int rand_89, int rand_18, int rand_90, int rand_19, int rand_91, int rand_20, int rand_92, int rand_21, int rand_93, int rand_22, int rand_94, int rand_23, int rand_95, int rand_24, int rand_96, int rand_25, int rand_97, int rand_26, int rand_98, int rand_27, int rand_99, int rand_28, int rand_100, int rand_29, int rand_101, int rand_30, int rand_102, int rand_31, int rand_1, int rand_103, int rand_32, int rand_104, int rand_33, int rand_105, int rand_34, int rand_106, int rand_35, int rand_107, int rand_36, int rand_108, int rand_37, int rand_109, int rand_38, int rand_110, int rand_39, int rand_111, int rand_40, int rand_112, int rand_41, int rand_113, int rand_42, int rand_114, int rand_43, int rand_115, int rand_44, int rand_116, int rand_45, int rand_117, int rand_46, int rand_118, int rand_47, int rand_119, int rand_48, int rand_120, int rand_49, int rand_50, int rand_51, int rand_52, int rand_53, int rand_54, int rand_55, int rand_56, int rand_57, int rand_58, int rand_59)
{
  _Bool n1_0;
  _Bool n1_1;
  _Bool n1_2;
  _Bool n1_3;
  _Bool n1_4;
  _Bool n2_0;
  _Bool n2_1;
  _Bool n2_2;
  _Bool n2_3;
  _Bool n2_4;
  _Bool n3_0;
  _Bool n3_1;
  _Bool n3_2;
  _Bool n3_3;
  _Bool n3_4;
  _Bool n6_0;
  _Bool n6_1;
  _Bool n6_2;
  _Bool n6_3;
  _Bool n6_4;
  _Bool n7_0;
  _Bool n7_1;
  _Bool n7_2;
  _Bool n7_3;
  _Bool n7_4;
  _Bool t0_0;
  _Bool t0_1;
  _Bool t0_2;
  _Bool t0_3;
  _Bool t0_4;
  _Bool t1_0;
  _Bool t1_1;
  _Bool t1_2;
  _Bool t1_3;
  _Bool t1_4;
  _Bool t2_0;
  _Bool t2_1;
  _Bool t2_2;
  _Bool t2_3;
  _Bool t2_4;
  _Bool t3_0;
  _Bool t3_1;
  _Bool t3_2;
  _Bool t3_3;
  _Bool t3_4;
  _Bool t4_0;
  _Bool t4_1;
  _Bool t4_2;
  _Bool t4_3;
  _Bool t4_4;
  _Bool t5_0;
  _Bool t5_1;
  _Bool t5_2;
  _Bool t5_3;
  _Bool t5_4;
  _Bool t6_0;
  _Bool t6_1;
  _Bool t6_2;
  _Bool t6_3;
  _Bool t6_4;
  _Bool t7_0;
  _Bool t7_1;
  _Bool t7_2;
  _Bool t7_3;
  _Bool t7_4;
  _Bool nt0_0;
  _Bool nt0_1;
  _Bool nt0_2;
  _Bool nt0_3;
  _Bool nt0_4;
  _Bool nt1_0;
  _Bool nt1_1;
  _Bool nt1_2;
  _Bool nt1_3;
  _Bool nt1_4;
  _Bool nt2_0;
  _Bool nt2_1;
  _Bool nt2_2;
  _Bool nt2_3;
  _Bool nt2_4;
  _Bool nt3_0;
  _Bool nt3_1;
  _Bool nt3_2;
  _Bool nt3_3;
  _Bool nt3_4;
  _Bool nt4_0;
  _Bool nt4_1;
  _Bool nt4_2;
  _Bool nt4_3;
  _Bool nt4_4;
  _Bool nt5_0;
  _Bool nt5_1;
  _Bool nt5_2;
  _Bool nt5_3;
  _Bool nt5_4;
  _Bool o1_val_0;
  _Bool o1_val_1;
  _Bool o1_val_2;
  _Bool o1_val_3;
  _Bool o1_val_4;
  _Bool o2_val_0;
  _Bool o2_val_1;
  _Bool o2_val_2;
  _Bool o2_val_3;
  _Bool o2_val_4;
  _Bool o3_val_0;
  _Bool o3_val_1;
  _Bool o3_val_2;
  _Bool o3_val_3;
  _Bool o3_val_4;
  _Bool o5_val_0;
  _Bool o5_val_1;
  _Bool o5_val_2;
  _Bool o5_val_3;
  _Bool o5_val_4;
  _Bool o6_val_0;
  _Bool o6_val_1;
  _Bool o6_val_2;
  _Bool o6_val_3;
  _Bool o6_val_4;
  _Bool o7_val_0;
  _Bool o7_val_1;
  _Bool o7_val_2;
  _Bool o7_val_3;
  _Bool o7_val_4;
  n1_0 = i1_0;
  n1_1 = i1_1;
  n1_2 = i1_2;
  n1_3 = i1_3;
  n1_4 = !i1_4;
  n2_0 = i2_0;
  n2_1 = i2_1;
  n2_2 = i2_2;
  n2_3 = i2_3;
  n2_4 = !i2_4;
  n3_0 = i3_0;
  n3_1 = i3_1;
  n3_2 = i3_2;
  n3_3 = i3_3;
  n3_4 = !i3_4;
  n6_0 = i6_0;
  n6_1 = i6_1;
  n6_2 = i6_2;
  n6_3 = i6_3;
  n6_4 = !i6_4;
  n7_0 = i7_0;
  n7_1 = i7_1;
  n7_2 = i7_2;
  n7_3 = i7_3;
  n7_4 = !i7_4;
  HPC3(n6_0, n6_1, n6_2, n6_3, n6_4, n7_0, n7_1, n7_2, n7_3, n7_4, &t0_0, &t0_1, &t0_2, &t0_3, &t0_4, rand_1, rand_2, rand_3, rand_4, rand_5, rand_6, rand_7, rand_8, rand_9, rand_10, rand_11, rand_12, rand_13, rand_14, rand_15, rand_16, rand_17, rand_18, rand_19, rand_20);
  HPC3(n3_0, n3_1, n3_2, n3_3, n3_4, n2_0, n2_1, n2_2, n2_3, n2_4, &t1_0, &t1_1, &t1_2, &t1_3, &t1_4, rand_21, rand_22, rand_23, rand_24, rand_25, rand_26, rand_27, rand_28, rand_29, rand_30, rand_31, rand_32, rand_33, rand_34, rand_35, rand_36, rand_37, rand_38, rand_39, rand_40);
  HPC3(n2_0, n2_1, n2_2, n2_3, n2_4, n1_0, n1_1, n1_2, n1_3, n1_4, &t2_0, &t2_1, &t2_2, &t2_3, &t2_4, rand_41, rand_42, rand_43, rand_44, rand_45, rand_46, rand_47, rand_48, rand_49, rand_50, rand_51, rand_52, rand_53, rand_54, rand_55, rand_56, rand_57, rand_58, rand_59, rand_60);
  nt0_0 = t0_0;
  nt0_1 = t0_1;
  nt0_2 = t0_2;
  nt0_3 = t0_3;
  nt0_4 = !t0_4;
  nt1_0 = t1_0;
  nt1_1 = t1_1;
  nt1_2 = t1_2;
  nt1_3 = t1_3;
  nt1_4 = !t1_4;
  nt2_0 = t2_0;
  nt2_1 = t2_1;
  nt2_2 = t2_2;
  nt2_3 = t2_3;
  nt2_4 = !t2_4;
  HPC3(nt0_0, nt0_1, nt0_2, nt0_3, nt0_4, nt1_0, nt1_1, nt1_2, nt1_3, nt1_4, &t3_0, &t3_1, &t3_2, &t3_3, &t3_4, rand_61, rand_62, rand_63, rand_64, rand_65, rand_66, rand_67, rand_68, rand_69, rand_70, rand_71, rand_72, rand_73, rand_74, rand_75, rand_76, rand_77, rand_78, rand_79, rand_80);
  HPC2(nt1_0, nt1_1, nt1_2, nt1_3, nt1_4, n3_0, n3_1, n3_2, n3_3, n3_4, &t4_0, &t4_1, &t4_2, &t4_3, &t4_4, rand_81, rand_82, rand_83, rand_84, rand_85, rand_86, rand_87, rand_88, rand_89, rand_90);
  nt3_0 = t3_0;
  nt3_1 = t3_1;
  nt3_2 = t3_2;
  nt3_3 = t3_3;
  nt3_4 = !t3_4;
  HPC2_swapped(nt2_0, nt2_1, nt2_2, nt2_3, nt2_4, nt3_0, nt3_1, nt3_2, nt3_3, nt3_4, &t5_0, &t5_1, &t5_2, &t5_3, &t5_4, rand_91, rand_92, rand_93, rand_94, rand_95, rand_96, rand_97, rand_98, rand_99, rand_100);
  nt4_0 = t4_0;
  nt4_1 = t4_1;
  nt4_2 = t4_2;
  nt4_3 = t4_3;
  nt4_4 = !t4_4;
  nt5_0 = t5_0;
  nt5_1 = t5_1;
  nt5_2 = t5_2;
  nt5_3 = t5_3;
  nt5_4 = !t5_4;
  o6_val_0 = t0_0 ^ i4_0;
  o6_val_1 = t0_1 ^ i4_1;
  o6_val_2 = t0_2 ^ i4_2;
  o6_val_3 = t0_3 ^ i4_3;
  o6_val_4 = t0_4 ^ i4_4;
  o5_val_0 = t1_0 ^ i0_0;
  o5_val_1 = t1_1 ^ i0_1;
  o5_val_2 = t1_2 ^ i0_2;
  o5_val_3 = t1_3 ^ i0_3;
  o5_val_4 = t1_4 ^ i0_4;
  o2_val_0 = t2_0 ^ i6_0;
  o2_val_1 = t2_1 ^ i6_1;
  o2_val_2 = t2_2 ^ i6_2;
  o2_val_3 = t2_3 ^ i6_3;
  o2_val_4 = t2_4 ^ i6_4;
  o7_val_0 = t3_0 ^ i5_0;
  o7_val_1 = t3_1 ^ i5_1;
  o7_val_2 = t3_2 ^ i5_2;
  o7_val_3 = t3_3 ^ i5_3;
  o7_val_4 = t3_4 ^ i5_4;
  HPC2o_swapped(nt4_0, nt4_1, nt4_2, nt4_3, nt4_4, nt5_0, nt5_1, nt5_2, nt5_3, nt5_4, i2_0, i2_1, i2_2, i2_3, i2_4, &t7_0, &t7_1, &t7_2, &t7_3, &t7_4, rand_101, rand_102, rand_103, rand_104, rand_105, rand_106, rand_107, rand_108, rand_109, rand_110);
  HPC2o(nt3_0, nt3_1, nt3_2, nt3_3, nt3_4, nt0_0, nt0_1, nt0_2, nt0_3, nt0_4, i3_0, i3_1, i3_2, i3_3, i3_4, &t6_0, &t6_1, &t6_2, &t6_3, &t6_4, rand_111, rand_112, rand_113, rand_114, rand_115, rand_116, rand_117, rand_118, rand_119, rand_120);
  o1_val_0 = t5_0 ^ i7_0;
  o1_val_1 = t5_1 ^ i7_1;
  o1_val_2 = t5_2 ^ i7_2;
  o1_val_3 = t5_3 ^ i7_3;
  o1_val_4 = t5_4 ^ i7_4;
  o3_val_0 = t4_0 ^ i1_0;
  o3_val_1 = t4_1 ^ i1_1;
  o3_val_2 = t4_2 ^ i1_2;
  o3_val_3 = t4_3 ^ i1_3;
  o3_val_4 = t4_4 ^ i1_4;
  *o0_0 = t7_0;
  *o0_1 = t7_1;
  *o0_2 = t7_2;
  *o0_3 = t7_3;
  *o0_4 = t7_4;
  *o1_0 = o1_val_0;
  *o1_1 = o1_val_1;
  *o1_2 = o1_val_2;
  *o1_3 = o1_val_3;
  *o1_4 = o1_val_4;
  *o2_0 = o2_val_0;
  *o2_1 = o2_val_1;
  *o2_2 = o2_val_2;
  *o2_3 = o2_val_3;
  *o2_4 = o2_val_4;
  *o3_0 = o3_val_0;
  *o3_1 = o3_val_1;
  *o3_2 = o3_val_2;
  *o3_3 = o3_val_3;
  *o3_4 = o3_val_4;
  *o4_0 = t6_0;
  *o4_1 = t6_1;
  *o4_2 = t6_2;
  *o4_3 = t6_3;
  *o4_4 = t6_4;
  *o5_0 = o5_val_0;
  *o5_1 = o5_val_1;
  *o5_2 = o5_val_2;
  *o5_3 = o5_val_3;
  *o5_4 = o5_val_4;
  *o6_0 = o6_val_0;
  *o6_1 = o6_val_1;
  *o6_2 = o6_val_2;
  *o6_3 = o6_val_3;
  *o6_4 = o6_val_4;
  *o7_0 = o7_val_0;
  *o7_1 = o7_val_1;
  *o7_2 = o7_val_2;
  *o7_3 = o7_val_3;
  *o7_4 = o7_val_4;
}

