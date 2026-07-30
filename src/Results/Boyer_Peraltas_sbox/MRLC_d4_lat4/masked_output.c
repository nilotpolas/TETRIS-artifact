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
void sbox(_Bool i0_0, _Bool i0_1, _Bool i0_2, _Bool i0_3, _Bool i0_4, _Bool i1_0, _Bool i1_1, _Bool i1_2, _Bool i1_3, _Bool i1_4, _Bool i2_0, _Bool i2_1, _Bool i2_2, _Bool i2_3, _Bool i2_4, _Bool i3_0, _Bool i3_1, _Bool i3_2, _Bool i3_3, _Bool i3_4, _Bool i4_0, _Bool i4_1, _Bool i4_2, _Bool i4_3, _Bool i4_4, _Bool i5_0, _Bool i5_1, _Bool i5_2, _Bool i5_3, _Bool i5_4, _Bool i6_0, _Bool i6_1, _Bool i6_2, _Bool i6_3, _Bool i6_4, _Bool i7_0, _Bool i7_1, _Bool i7_2, _Bool i7_3, _Bool i7_4, _Bool dec_1, _Bool *y0_0, _Bool *y0_1, _Bool *y0_2, _Bool *y0_3, _Bool *y0_4, _Bool *y1_0, _Bool *y1_1, _Bool *y1_2, _Bool *y1_3, _Bool *y1_4, _Bool *y2_0, _Bool *y2_1, _Bool *y2_2, _Bool *y2_3, _Bool *y2_4, _Bool *y3_0, _Bool *y3_1, _Bool *y3_2, _Bool *y3_3, _Bool *y3_4, _Bool *y4_0, _Bool *y4_1, _Bool *y4_2, _Bool *y4_3, _Bool *y4_4, _Bool *y5_0, _Bool *y5_1, _Bool *y5_2, _Bool *y5_3, _Bool *y5_4, _Bool *y6_0, _Bool *y6_1, _Bool *y6_2, _Bool *y6_3, _Bool *y6_4, _Bool *y7_0, _Bool *y7_1, _Bool *y7_2, _Bool *y7_3, _Bool *y7_4, int rand_250, int rand_340, int rand_251, int rand_341, int rand_252, int rand_253, int rand_254, int rand_255, int rand_256, int rand_102, int rand_257, int rand_342, int rand_103, int rand_258, int rand_343, int rand_104, int rand_259, int rand_344, int rand_105, int rand_260, int rand_345, int rand_106, int rand_261, int rand_346, int rand_2, int rand_107, int rand_262, int rand_347, int rand_3, int rand_108, int rand_263, int rand_348, int rand_4, int rand_109, int rand_264, int rand_349, int rand_5, int rand_110, int rand_265, int rand_350, int rand_6, int rand_111, int rand_266, int rand_351, int rand_7, int rand_112, int rand_267, int rand_8, int rand_113, int rand_268, int rand_9, int rand_114, int rand_269, int rand_10, int rand_115, int rand_270, int rand_11, int rand_116, int rand_271, int rand_12, int rand_117, int rand_272, int rand_352, int rand_13, int rand_118, int rand_273, int rand_353, int rand_14, int rand_119, int rand_274, int rand_354, int rand_15, int rand_120, int rand_275, int rand_355, int rand_16, int rand_121, int rand_276, int rand_356, int rand_17, int rand_277, int rand_357, int rand_1, int rand_18, int rand_278, int rand_358, int rand_19, int rand_279, int rand_359, int rand_20, int rand_280, int rand_360, int rand_21, int rand_281, int rand_361, int rand_22, int rand_122, int rand_362, int rand_23, int rand_123, int rand_363, int rand_24, int rand_124, int rand_364, int rand_25, int rand_125, int rand_365, int rand_26, int rand_126, int rand_366, int rand_27, int rand_127, int rand_367, int rand_28, int rand_128, int rand_368, int rand_29, int rand_129, int rand_369, int rand_30, int rand_130, int rand_370, int rand_31, int rand_131, int rand_371, int rand_32, int rand_132, int rand_33, int rand_133, int rand_34, int rand_134, int rand_35, int rand_135, int rand_36, int rand_136, int rand_37, int rand_137, int rand_372, int rand_38, int rand_138, int rand_373, int rand_39, int rand_139, int rand_374, int rand_40, int rand_140, int rand_375, int rand_41, int rand_141, int rand_376, int rand_377, int rand_378, int rand_379, int rand_380, int rand_381, int rand_142, int rand_282, int rand_143, int rand_283, int rand_144, int rand_284, int rand_145, int rand_285, int rand_146, int rand_286, int rand_42, int rand_147, int rand_287, int rand_382, int rand_43, int rand_148, int rand_288, int rand_383, int rand_44, int rand_149, int rand_289, int rand_384, int rand_45, int rand_150, int rand_290, int rand_385, int rand_46, int rand_151, int rand_291, int rand_386, int rand_152, int rand_47, int rand_387, int rand_48, int rand_153, int rand_388, int rand_49, int rand_154, int rand_389, int rand_50, int rand_155, int rand_390, int rand_51, int rand_156, int rand_391, int rand_52, int rand_157, int rand_292, int rand_53, int rand_158, int rand_293, int rand_54, int rand_159, int rand_294, int rand_55, int rand_160, int rand_295, int rand_56, int rand_161, int rand_296, int rand_57, int rand_297, int rand_392, int rand_58, int rand_298, int rand_393, int rand_59, int rand_299, int rand_394, int rand_60, int rand_300, int rand_395, int rand_61, int rand_301, int rand_396, int rand_397, int rand_398, int rand_399, int rand_400, int rand_401, int rand_162, int rand_302, int rand_163, int rand_303, int rand_164, int rand_304, int rand_165, int rand_305, int rand_166, int rand_306, int rand_62, int rand_167, int rand_307, int rand_402, int rand_63, int rand_168, int rand_308, int rand_403, int rand_64, int rand_169, int rand_309, int rand_404, int rand_65, int rand_170, int rand_310, int rand_405, int rand_66, int rand_171, int rand_311, int rand_406, int rand_67, int rand_172, int rand_407, int rand_68, int rand_173, int rand_408, int rand_69, int rand_174, int rand_409, int rand_70, int rand_175, int rand_410, int rand_71, int rand_176, int rand_411, int rand_72, int rand_177, int rand_312, int rand_73, int rand_178, int rand_313, int rand_74, int rand_179, int rand_314, int rand_75, int rand_180, int rand_315, int rand_76, int rand_181, int rand_316, int rand_77, int rand_317, int rand_412, int rand_78, int rand_318, int rand_413, int rand_79, int rand_319, int rand_414, int rand_80, int rand_320, int rand_415, int rand_81, int rand_321, int rand_416, int rand_417, int rand_418, int rand_419, int rand_420, int rand_421, int rand_82, int rand_322, int rand_83, int rand_323, int rand_84, int rand_324, int rand_85, int rand_325, int rand_86, int rand_326, int rand_87, int rand_327, int rand_422, int rand_88, int rand_328, int rand_423, int rand_89, int rand_329, int rand_424, int rand_90, int rand_330, int rand_425, int rand_91, int rand_331, int rand_426, int rand_92, int rand_427, int rand_93, int rand_428, int rand_94, int rand_429, int rand_95, int rand_430, int rand_96, int rand_431, int rand_97, int rand_332, int rand_98, int rand_333, int rand_99, int rand_334, int rand_100, int rand_335, int rand_101, int rand_336, int rand_337, int rand_432, int rand_338, int rand_433, int rand_339, int rand_434, int rand_435, int rand_436, int rand_437, int rand_438, int rand_439, int rand_440, int rand_441, int rand_442, int rand_443, int rand_444, int rand_445, int rand_446, int rand_447, int rand_448, int rand_449, int rand_450, int rand_451, int rand_182, int rand_183, int rand_184, int rand_185, int rand_186, int rand_187, int rand_452, int rand_188, int rand_453, int rand_189, int rand_454, int rand_190, int rand_455, int rand_191, int rand_456, int rand_192, int rand_457, int rand_193, int rand_458, int rand_194, int rand_459, int rand_195, int rand_460, int rand_196, int rand_197, int rand_198, int rand_199, int rand_200, int rand_201, int rand_202, int rand_203, int rand_204, int rand_205, int rand_206, int rand_207, int rand_208, int rand_209, int rand_210, int rand_211, int rand_212, int rand_213, int rand_214, int rand_215, int rand_216, int rand_217, int rand_218, int rand_219, int rand_220, int rand_221, int rand_222, int rand_223, int rand_224, int rand_225, int rand_226, int rand_227, int rand_228, int rand_229, int rand_230, int rand_231, int rand_232, int rand_233, int rand_234, int rand_235, int rand_236, int rand_237, int rand_238, int rand_239, int rand_240, int rand_241, int rand_242, int rand_243, int rand_244, int rand_245, int rand_246, int rand_247, int rand_248, int rand_249)
{
  _Bool t1_0;
  _Bool t1_1;
  _Bool t1_2;
  _Bool t1_3;
  _Bool t1_4;
  t1_0 = i7_0 ^ i4_0;
  t1_1 = i7_1 ^ i4_1;
  t1_2 = i7_2 ^ i4_2;
  t1_3 = i7_3 ^ i4_3;
  t1_4 = i7_4 ^ i4_4;
  _Bool t2_0;
  _Bool t2_1;
  _Bool t2_2;
  _Bool t2_3;
  _Bool t2_4;
  t2_0 = i7_0 ^ i2_0;
  t2_1 = i7_1 ^ i2_1;
  t2_2 = i7_2 ^ i2_2;
  t2_3 = i7_3 ^ i2_3;
  t2_4 = i7_4 ^ i2_4;
  _Bool t3_0;
  _Bool t3_1;
  _Bool t3_2;
  _Bool t3_3;
  _Bool t3_4;
  t3_0 = i7_0 ^ i1_0;
  t3_1 = i7_1 ^ i1_1;
  t3_2 = i7_2 ^ i1_2;
  t3_3 = i7_3 ^ i1_3;
  t3_4 = i7_4 ^ i1_4;
  _Bool t4_0;
  _Bool t4_1;
  _Bool t4_2;
  _Bool t4_3;
  _Bool t4_4;
  t4_0 = i4_0 ^ i2_0;
  t4_1 = i4_1 ^ i2_1;
  t4_2 = i4_2 ^ i2_2;
  t4_3 = i4_3 ^ i2_3;
  t4_4 = i4_4 ^ i2_4;
  _Bool t5_0;
  _Bool t5_1;
  _Bool t5_2;
  _Bool t5_3;
  _Bool t5_4;
  t5_0 = i3_0 ^ i1_0;
  t5_1 = i3_1 ^ i1_1;
  t5_2 = i3_2 ^ i1_2;
  t5_3 = i3_3 ^ i1_3;
  t5_4 = i3_4 ^ i1_4;
  _Bool t6_0;
  _Bool t6_1;
  _Bool t6_2;
  _Bool t6_3;
  _Bool t6_4;
  t6_0 = t1_0 ^ t5_0;
  t6_1 = t1_1 ^ t5_1;
  t6_2 = t1_2 ^ t5_2;
  t6_3 = t1_3 ^ t5_3;
  t6_4 = t1_4 ^ t5_4;
  _Bool t7_0;
  _Bool t7_1;
  _Bool t7_2;
  _Bool t7_3;
  _Bool t7_4;
  t7_0 = i6_0 ^ i5_0;
  t7_1 = i6_1 ^ i5_1;
  t7_2 = i6_2 ^ i5_2;
  t7_3 = i6_3 ^ i5_3;
  t7_4 = i6_4 ^ i5_4;
  _Bool t8_0;
  _Bool t8_1;
  _Bool t8_2;
  _Bool t8_3;
  _Bool t8_4;
  t8_0 = i0_0 ^ t6_0;
  t8_1 = i0_1 ^ t6_1;
  t8_2 = i0_2 ^ t6_2;
  t8_3 = i0_3 ^ t6_3;
  t8_4 = i0_4 ^ t6_4;
  _Bool t9_0;
  _Bool t9_1;
  _Bool t9_2;
  _Bool t9_3;
  _Bool t9_4;
  t9_0 = i0_0 ^ t7_0;
  t9_1 = i0_1 ^ t7_1;
  t9_2 = i0_2 ^ t7_2;
  t9_3 = i0_3 ^ t7_3;
  t9_4 = i0_4 ^ t7_4;
  _Bool t10_0;
  _Bool t10_1;
  _Bool t10_2;
  _Bool t10_3;
  _Bool t10_4;
  t10_0 = t6_0 ^ t7_0;
  t10_1 = t6_1 ^ t7_1;
  t10_2 = t6_2 ^ t7_2;
  t10_3 = t6_3 ^ t7_3;
  t10_4 = t6_4 ^ t7_4;
  _Bool t11_0;
  _Bool t11_1;
  _Bool t11_2;
  _Bool t11_3;
  _Bool t11_4;
  t11_0 = i6_0 ^ i2_0;
  t11_1 = i6_1 ^ i2_1;
  t11_2 = i6_2 ^ i2_2;
  t11_3 = i6_3 ^ i2_3;
  t11_4 = i6_4 ^ i2_4;
  _Bool t12_0;
  _Bool t12_1;
  _Bool t12_2;
  _Bool t12_3;
  _Bool t12_4;
  t12_0 = i5_0 ^ i2_0;
  t12_1 = i5_1 ^ i2_1;
  t12_2 = i5_2 ^ i2_2;
  t12_3 = i5_3 ^ i2_3;
  t12_4 = i5_4 ^ i2_4;
  _Bool t13_0;
  _Bool t13_1;
  _Bool t13_2;
  _Bool t13_3;
  _Bool t13_4;
  t13_0 = t3_0 ^ t4_0;
  t13_1 = t3_1 ^ t4_1;
  t13_2 = t3_2 ^ t4_2;
  t13_3 = t3_3 ^ t4_3;
  t13_4 = t3_4 ^ t4_4;
  _Bool t14_0;
  _Bool t14_1;
  _Bool t14_2;
  _Bool t14_3;
  _Bool t14_4;
  t14_0 = t6_0 ^ t11_0;
  t14_1 = t6_1 ^ t11_1;
  t14_2 = t6_2 ^ t11_2;
  t14_3 = t6_3 ^ t11_3;
  t14_4 = t6_4 ^ t11_4;
  _Bool t15_0;
  _Bool t15_1;
  _Bool t15_2;
  _Bool t15_3;
  _Bool t15_4;
  t15_0 = t5_0 ^ t11_0;
  t15_1 = t5_1 ^ t11_1;
  t15_2 = t5_2 ^ t11_2;
  t15_3 = t5_3 ^ t11_3;
  t15_4 = t5_4 ^ t11_4;
  _Bool t16_0;
  _Bool t16_1;
  _Bool t16_2;
  _Bool t16_3;
  _Bool t16_4;
  t16_0 = t5_0 ^ t12_0;
  t16_1 = t5_1 ^ t12_1;
  t16_2 = t5_2 ^ t12_2;
  t16_3 = t5_3 ^ t12_3;
  t16_4 = t5_4 ^ t12_4;
  _Bool t17_0;
  _Bool t17_1;
  _Bool t17_2;
  _Bool t17_3;
  _Bool t17_4;
  t17_0 = t9_0 ^ t16_0;
  t17_1 = t9_1 ^ t16_1;
  t17_2 = t9_2 ^ t16_2;
  t17_3 = t9_3 ^ t16_3;
  t17_4 = t9_4 ^ t16_4;
  _Bool t18_0;
  _Bool t18_1;
  _Bool t18_2;
  _Bool t18_3;
  _Bool t18_4;
  t18_0 = i4_0 ^ i0_0;
  t18_1 = i4_1 ^ i0_1;
  t18_2 = i4_2 ^ i0_2;
  t18_3 = i4_3 ^ i0_3;
  t18_4 = i4_4 ^ i0_4;
  _Bool t19_0;
  _Bool t19_1;
  _Bool t19_2;
  _Bool t19_3;
  _Bool t19_4;
  t19_0 = t7_0 ^ t18_0;
  t19_1 = t7_1 ^ t18_1;
  t19_2 = t7_2 ^ t18_2;
  t19_3 = t7_3 ^ t18_3;
  t19_4 = t7_4 ^ t18_4;
  _Bool t20_0;
  _Bool t20_1;
  _Bool t20_2;
  _Bool t20_3;
  _Bool t20_4;
  t20_0 = t1_0 ^ t19_0;
  t20_1 = t1_1 ^ t19_1;
  t20_2 = t1_2 ^ t19_2;
  t20_3 = t1_3 ^ t19_3;
  t20_4 = t1_4 ^ t19_4;
  _Bool t21_0;
  _Bool t21_1;
  _Bool t21_2;
  _Bool t21_3;
  _Bool t21_4;
  t21_0 = i1_0 ^ i0_0;
  t21_1 = i1_1 ^ i0_1;
  t21_2 = i1_2 ^ i0_2;
  t21_3 = i1_3 ^ i0_3;
  t21_4 = i1_4 ^ i0_4;
  _Bool t22_0;
  _Bool t22_1;
  _Bool t22_2;
  _Bool t22_3;
  _Bool t22_4;
  t22_0 = t7_0 ^ t21_0;
  t22_1 = t7_1 ^ t21_1;
  t22_2 = t7_2 ^ t21_2;
  t22_3 = t7_3 ^ t21_3;
  t22_4 = t7_4 ^ t21_4;
  _Bool t23_0;
  _Bool t23_1;
  _Bool t23_2;
  _Bool t23_3;
  _Bool t23_4;
  t23_0 = t2_0 ^ t22_0;
  t23_1 = t2_1 ^ t22_1;
  t23_2 = t2_2 ^ t22_2;
  t23_3 = t2_3 ^ t22_3;
  t23_4 = t2_4 ^ t22_4;
  _Bool t24_0;
  _Bool t24_1;
  _Bool t24_2;
  _Bool t24_3;
  _Bool t24_4;
  t24_0 = t2_0 ^ t10_0;
  t24_1 = t2_1 ^ t10_1;
  t24_2 = t2_2 ^ t10_2;
  t24_3 = t2_3 ^ t10_3;
  t24_4 = t2_4 ^ t10_4;
  _Bool t25_0;
  _Bool t25_1;
  _Bool t25_2;
  _Bool t25_3;
  _Bool t25_4;
  t25_0 = t20_0 ^ t17_0;
  t25_1 = t20_1 ^ t17_1;
  t25_2 = t20_2 ^ t17_2;
  t25_3 = t20_3 ^ t17_3;
  t25_4 = t20_4 ^ t17_4;
  _Bool t26_0;
  _Bool t26_1;
  _Bool t26_2;
  _Bool t26_3;
  _Bool t26_4;
  t26_0 = t3_0 ^ t16_0;
  t26_1 = t3_1 ^ t16_1;
  t26_2 = t3_2 ^ t16_2;
  t26_3 = t3_3 ^ t16_3;
  t26_4 = t3_4 ^ t16_4;
  _Bool t27_0;
  _Bool t27_1;
  _Bool t27_2;
  _Bool t27_3;
  _Bool t27_4;
  t27_0 = t1_0 ^ t12_0;
  t27_1 = t1_1 ^ t12_1;
  t27_2 = t1_2 ^ t12_2;
  t27_3 = t1_3 ^ t12_3;
  t27_4 = t1_4 ^ t12_4;
  _Bool m1_0;
  _Bool m1_1;
  _Bool m1_2;
  _Bool m1_3;
  _Bool m1_4;
  HPC3(t13_0, t13_1, t13_2, t13_3, t13_4, t6_0, t6_1, t6_2, t6_3, t6_4, &m1_0, &m1_1, &m1_2, &m1_3, &m1_4, rand_1, rand_2, rand_3, rand_4, rand_5, rand_6, rand_7, rand_8, rand_9, rand_10, rand_11, rand_12, rand_13, rand_14, rand_15, rand_16, rand_17, rand_18, rand_19, rand_20);
  _Bool m2_0;
  _Bool m2_1;
  _Bool m2_2;
  _Bool m2_3;
  _Bool m2_4;
  HPC3(t23_0, t23_1, t23_2, t23_3, t23_4, t8_0, t8_1, t8_2, t8_3, t8_4, &m2_0, &m2_1, &m2_2, &m2_3, &m2_4, rand_21, rand_22, rand_23, rand_24, rand_25, rand_26, rand_27, rand_28, rand_29, rand_30, rand_31, rand_32, rand_33, rand_34, rand_35, rand_36, rand_37, rand_38, rand_39, rand_40);
  _Bool m3_0;
  _Bool m3_1;
  _Bool m3_2;
  _Bool m3_3;
  _Bool m3_4;
  m3_0 = t14_0 ^ m1_0;
  m3_1 = t14_1 ^ m1_1;
  m3_2 = t14_2 ^ m1_2;
  m3_3 = t14_3 ^ m1_3;
  m3_4 = t14_4 ^ m1_4;
  _Bool m4_0;
  _Bool m4_1;
  _Bool m4_2;
  _Bool m4_3;
  _Bool m4_4;
  HPC3(t19_0, t19_1, t19_2, t19_3, t19_4, i0_0, i0_1, i0_2, i0_3, i0_4, &m4_0, &m4_1, &m4_2, &m4_3, &m4_4, rand_41, rand_42, rand_43, rand_44, rand_45, rand_46, rand_47, rand_48, rand_49, rand_50, rand_51, rand_52, rand_53, rand_54, rand_55, rand_56, rand_57, rand_58, rand_59, rand_60);
  _Bool m5_0;
  _Bool m5_1;
  _Bool m5_2;
  _Bool m5_3;
  _Bool m5_4;
  m5_0 = m4_0 ^ m1_0;
  m5_1 = m4_1 ^ m1_1;
  m5_2 = m4_2 ^ m1_2;
  m5_3 = m4_3 ^ m1_3;
  m5_4 = m4_4 ^ m1_4;
  _Bool m6_0;
  _Bool m6_1;
  _Bool m6_2;
  _Bool m6_3;
  _Bool m6_4;
  HPC3(t3_0, t3_1, t3_2, t3_3, t3_4, t16_0, t16_1, t16_2, t16_3, t16_4, &m6_0, &m6_1, &m6_2, &m6_3, &m6_4, rand_61, rand_62, rand_63, rand_64, rand_65, rand_66, rand_67, rand_68, rand_69, rand_70, rand_71, rand_72, rand_73, rand_74, rand_75, rand_76, rand_77, rand_78, rand_79, rand_80);
  _Bool m7_0;
  _Bool m7_1;
  _Bool m7_2;
  _Bool m7_3;
  _Bool m7_4;
  HPC3(t22_0, t22_1, t22_2, t22_3, t22_4, t9_0, t9_1, t9_2, t9_3, t9_4, &m7_0, &m7_1, &m7_2, &m7_3, &m7_4, rand_81, rand_82, rand_83, rand_84, rand_85, rand_86, rand_87, rand_88, rand_89, rand_90, rand_91, rand_92, rand_93, rand_94, rand_95, rand_96, rand_97, rand_98, rand_99, rand_100);
  _Bool m8_0;
  _Bool m8_1;
  _Bool m8_2;
  _Bool m8_3;
  _Bool m8_4;
  m8_0 = t26_0 ^ m6_0;
  m8_1 = t26_1 ^ m6_1;
  m8_2 = t26_2 ^ m6_2;
  m8_3 = t26_3 ^ m6_3;
  m8_4 = t26_4 ^ m6_4;
  _Bool m9_0;
  _Bool m9_1;
  _Bool m9_2;
  _Bool m9_3;
  _Bool m9_4;
  HPC3(t20_0, t20_1, t20_2, t20_3, t20_4, t17_0, t17_1, t17_2, t17_3, t17_4, &m9_0, &m9_1, &m9_2, &m9_3, &m9_4, rand_101, rand_102, rand_103, rand_104, rand_105, rand_106, rand_107, rand_108, rand_109, rand_110, rand_111, rand_112, rand_113, rand_114, rand_115, rand_116, rand_117, rand_118, rand_119, rand_120);
  _Bool m10_0;
  _Bool m10_1;
  _Bool m10_2;
  _Bool m10_3;
  _Bool m10_4;
  m10_0 = m9_0 ^ m6_0;
  m10_1 = m9_1 ^ m6_1;
  m10_2 = m9_2 ^ m6_2;
  m10_3 = m9_3 ^ m6_3;
  m10_4 = m9_4 ^ m6_4;
  _Bool m11_0;
  _Bool m11_1;
  _Bool m11_2;
  _Bool m11_3;
  _Bool m11_4;
  HPC3(t1_0, t1_1, t1_2, t1_3, t1_4, t15_0, t15_1, t15_2, t15_3, t15_4, &m11_0, &m11_1, &m11_2, &m11_3, &m11_4, rand_121, rand_122, rand_123, rand_124, rand_125, rand_126, rand_127, rand_128, rand_129, rand_130, rand_131, rand_132, rand_133, rand_134, rand_135, rand_136, rand_137, rand_138, rand_139, rand_140);
  _Bool m12_0;
  _Bool m12_1;
  _Bool m12_2;
  _Bool m12_3;
  _Bool m12_4;
  HPC3(t4_0, t4_1, t4_2, t4_3, t4_4, t27_0, t27_1, t27_2, t27_3, t27_4, &m12_0, &m12_1, &m12_2, &m12_3, &m12_4, rand_141, rand_142, rand_143, rand_144, rand_145, rand_146, rand_147, rand_148, rand_149, rand_150, rand_151, rand_152, rand_153, rand_154, rand_155, rand_156, rand_157, rand_158, rand_159, rand_160);
  _Bool m13_0;
  _Bool m13_1;
  _Bool m13_2;
  _Bool m13_3;
  _Bool m13_4;
  m13_0 = m12_0 ^ m11_0;
  m13_1 = m12_1 ^ m11_1;
  m13_2 = m12_2 ^ m11_2;
  m13_3 = m12_3 ^ m11_3;
  m13_4 = m12_4 ^ m11_4;
  _Bool m14_0;
  _Bool m14_1;
  _Bool m14_2;
  _Bool m14_3;
  _Bool m14_4;
  HPC3(t2_0, t2_1, t2_2, t2_3, t2_4, t10_0, t10_1, t10_2, t10_3, t10_4, &m14_0, &m14_1, &m14_2, &m14_3, &m14_4, rand_161, rand_162, rand_163, rand_164, rand_165, rand_166, rand_167, rand_168, rand_169, rand_170, rand_171, rand_172, rand_173, rand_174, rand_175, rand_176, rand_177, rand_178, rand_179, rand_180);
  _Bool m15_0;
  _Bool m15_1;
  _Bool m15_2;
  _Bool m15_3;
  _Bool m15_4;
  m15_0 = m14_0 ^ m11_0;
  m15_1 = m14_1 ^ m11_1;
  m15_2 = m14_2 ^ m11_2;
  m15_3 = m14_3 ^ m11_3;
  m15_4 = m14_4 ^ m11_4;
  _Bool m16_0;
  _Bool m16_1;
  _Bool m16_2;
  _Bool m16_3;
  _Bool m16_4;
  m16_0 = m3_0 ^ m2_0;
  m16_1 = m3_1 ^ m2_1;
  m16_2 = m3_2 ^ m2_2;
  m16_3 = m3_3 ^ m2_3;
  m16_4 = m3_4 ^ m2_4;
  _Bool m17_0;
  _Bool m17_1;
  _Bool m17_2;
  _Bool m17_3;
  _Bool m17_4;
  m17_0 = m5_0 ^ t24_0;
  m17_1 = m5_1 ^ t24_1;
  m17_2 = m5_2 ^ t24_2;
  m17_3 = m5_3 ^ t24_3;
  m17_4 = m5_4 ^ t24_4;
  _Bool m18_0;
  _Bool m18_1;
  _Bool m18_2;
  _Bool m18_3;
  _Bool m18_4;
  m18_0 = m7_0 ^ m8_0;
  m18_1 = m7_1 ^ m8_1;
  m18_2 = m7_2 ^ m8_2;
  m18_3 = m7_3 ^ m8_3;
  m18_4 = m7_4 ^ m8_4;
  _Bool m19_0;
  _Bool m19_1;
  _Bool m19_2;
  _Bool m19_3;
  _Bool m19_4;
  m19_0 = m10_0 ^ m15_0;
  m19_1 = m10_1 ^ m15_1;
  m19_2 = m10_2 ^ m15_2;
  m19_3 = m10_3 ^ m15_3;
  m19_4 = m10_4 ^ m15_4;
  _Bool m20_0;
  _Bool m20_1;
  _Bool m20_2;
  _Bool m20_3;
  _Bool m20_4;
  m20_0 = m16_0 ^ m13_0;
  m20_1 = m16_1 ^ m13_1;
  m20_2 = m16_2 ^ m13_2;
  m20_3 = m16_3 ^ m13_3;
  m20_4 = m16_4 ^ m13_4;
  _Bool m21_0;
  _Bool m21_1;
  _Bool m21_2;
  _Bool m21_3;
  _Bool m21_4;
  m21_0 = m17_0 ^ m15_0;
  m21_1 = m17_1 ^ m15_1;
  m21_2 = m17_2 ^ m15_2;
  m21_3 = m17_3 ^ m15_3;
  m21_4 = m17_4 ^ m15_4;
  _Bool m22_0;
  _Bool m22_1;
  _Bool m22_2;
  _Bool m22_3;
  _Bool m22_4;
  m22_0 = m18_0 ^ m13_0;
  m22_1 = m18_1 ^ m13_1;
  m22_2 = m18_2 ^ m13_2;
  m22_3 = m18_3 ^ m13_3;
  m22_4 = m18_4 ^ m13_4;
  _Bool m23_0;
  _Bool m23_1;
  _Bool m23_2;
  _Bool m23_3;
  _Bool m23_4;
  m23_0 = m19_0 ^ t25_0;
  m23_1 = m19_1 ^ t25_1;
  m23_2 = m19_2 ^ t25_2;
  m23_3 = m19_3 ^ t25_3;
  m23_4 = m19_4 ^ t25_4;
  _Bool m24_0;
  _Bool m24_1;
  _Bool m24_2;
  _Bool m24_3;
  _Bool m24_4;
  m24_0 = m22_0 ^ m23_0;
  m24_1 = m22_1 ^ m23_1;
  m24_2 = m22_2 ^ m23_2;
  m24_3 = m22_3 ^ m23_3;
  m24_4 = m22_4 ^ m23_4;
  _Bool m25_0;
  _Bool m25_1;
  _Bool m25_2;
  _Bool m25_3;
  _Bool m25_4;
  HPC3(m22_0, m22_1, m22_2, m22_3, m22_4, m20_0, m20_1, m20_2, m20_3, m20_4, &m25_0, &m25_1, &m25_2, &m25_3, &m25_4, rand_181, rand_182, rand_183, rand_184, rand_185, rand_186, rand_187, rand_188, rand_189, rand_190, rand_191, rand_192, rand_193, rand_194, rand_195, rand_196, rand_197, rand_198, rand_199, rand_200);
  _Bool m26_0;
  _Bool m26_1;
  _Bool m26_2;
  _Bool m26_3;
  _Bool m26_4;
  m26_0 = m21_0 ^ m25_0;
  m26_1 = m21_1 ^ m25_1;
  m26_2 = m21_2 ^ m25_2;
  m26_3 = m21_3 ^ m25_3;
  m26_4 = m21_4 ^ m25_4;
  _Bool m27_0;
  _Bool m27_1;
  _Bool m27_2;
  _Bool m27_3;
  _Bool m27_4;
  m27_0 = m20_0 ^ m21_0;
  m27_1 = m20_1 ^ m21_1;
  m27_2 = m20_2 ^ m21_2;
  m27_3 = m20_3 ^ m21_3;
  m27_4 = m20_4 ^ m21_4;
  _Bool m28_0;
  _Bool m28_1;
  _Bool m28_2;
  _Bool m28_3;
  _Bool m28_4;
  m28_0 = m23_0 ^ m25_0;
  m28_1 = m23_1 ^ m25_1;
  m28_2 = m23_2 ^ m25_2;
  m28_3 = m23_3 ^ m25_3;
  m28_4 = m23_4 ^ m25_4;
  _Bool m29_0;
  _Bool m29_1;
  _Bool m29_2;
  _Bool m29_3;
  _Bool m29_4;
  _Bool m30_0;
  _Bool m30_1;
  _Bool m30_2;
  _Bool m30_3;
  _Bool m30_4;
  _Bool m31_0;
  _Bool m31_1;
  _Bool m31_2;
  _Bool m31_3;
  _Bool m31_4;
  HPC3(m20_0, m20_1, m20_2, m20_3, m20_4, m23_0, m23_1, m23_2, m23_3, m23_4, &m31_0, &m31_1, &m31_2, &m31_3, &m31_4, rand_201, rand_202, rand_203, rand_204, rand_205, rand_206, rand_207, rand_208, rand_209, rand_210, rand_211, rand_212, rand_213, rand_214, rand_215, rand_216, rand_217, rand_218, rand_219, rand_220);
  _Bool m32_0;
  _Bool m32_1;
  _Bool m32_2;
  _Bool m32_3;
  _Bool m32_4;
  _Bool m33_0;
  _Bool m33_1;
  _Bool m33_2;
  _Bool m33_3;
  _Bool m33_4;
  m33_0 = m27_0 ^ m25_0;
  m33_1 = m27_1 ^ m25_1;
  m33_2 = m27_2 ^ m25_2;
  m33_3 = m27_3 ^ m25_3;
  m33_4 = m27_4 ^ m25_4;
  _Bool m34_0;
  _Bool m34_1;
  _Bool m34_2;
  _Bool m34_3;
  _Bool m34_4;
  HPC3(m21_0, m21_1, m21_2, m21_3, m21_4, m22_0, m22_1, m22_2, m22_3, m22_4, &m34_0, &m34_1, &m34_2, &m34_3, &m34_4, rand_221, rand_222, rand_223, rand_224, rand_225, rand_226, rand_227, rand_228, rand_229, rand_230, rand_231, rand_232, rand_233, rand_234, rand_235, rand_236, rand_237, rand_238, rand_239, rand_240);
  _Bool m35_0;
  _Bool m35_1;
  _Bool m35_2;
  _Bool m35_3;
  _Bool m35_4;
  _Bool m36_0;
  _Bool m36_1;
  _Bool m36_2;
  _Bool m36_3;
  _Bool m36_4;
  m36_0 = m24_0 ^ m25_0;
  m36_1 = m24_1 ^ m25_1;
  m36_2 = m24_2 ^ m25_2;
  m36_3 = m24_3 ^ m25_3;
  m36_4 = m24_4 ^ m25_4;
  HPC2o(m28_0, m28_1, m28_2, m28_3, m28_4, m27_0, m27_1, m27_2, m27_3, m27_4, m21_0, m21_1, m21_2, m21_3, m21_4, &m29_0, &m29_1, &m29_2, &m29_3, &m29_4, rand_241, rand_242, rand_243, rand_244, rand_245, rand_246, rand_247, rand_248, rand_249, rand_250);
  HPC2o_swapped(m27_0, m27_1, m27_2, m27_3, m27_4, m31_0, m31_1, m31_2, m31_3, m31_4, m33_0, m33_1, m33_2, m33_3, m33_4, &m32_0, &m32_1, &m32_2, &m32_3, &m32_4, rand_251, rand_252, rand_253, rand_254, rand_255, rand_256, rand_257, rand_258, rand_259, rand_260);
  HPC2o(m26_0, m26_1, m26_2, m26_3, m26_4, m24_0, m24_1, m24_2, m24_3, m24_4, m23_0, m23_1, m23_2, m23_3, m23_4, &m30_0, &m30_1, &m30_2, &m30_3, &m30_4, rand_261, rand_262, rand_263, rand_264, rand_265, rand_266, rand_267, rand_268, rand_269, rand_270);
  HPC2o_swapped(m24_0, m24_1, m24_2, m24_3, m24_4, m34_0, m34_1, m34_2, m34_3, m34_4, m36_0, m36_1, m36_2, m36_3, m36_4, &m35_0, &m35_1, &m35_2, &m35_3, &m35_4, rand_271, rand_272, rand_273, rand_274, rand_275, rand_276, rand_277, rand_278, rand_279, rand_280);
  _Bool m41_0;
  _Bool m41_1;
  _Bool m41_2;
  _Bool m41_3;
  _Bool m41_4;
  m41_0 = m32_0 ^ m35_0;
  m41_1 = m32_1 ^ m35_1;
  m41_2 = m32_2 ^ m35_2;
  m41_3 = m32_3 ^ m35_3;
  m41_4 = m32_4 ^ m35_4;
  _Bool m42_0;
  _Bool m42_1;
  _Bool m42_2;
  _Bool m42_3;
  _Bool m42_4;
  m42_0 = m29_0 ^ m30_0;
  m42_1 = m29_1 ^ m30_1;
  m42_2 = m29_2 ^ m30_2;
  m42_3 = m29_3 ^ m30_3;
  m42_4 = m29_4 ^ m30_4;
  _Bool m43_0;
  _Bool m43_1;
  _Bool m43_2;
  _Bool m43_3;
  _Bool m43_4;
  m43_0 = m29_0 ^ m32_0;
  m43_1 = m29_1 ^ m32_1;
  m43_2 = m29_2 ^ m32_2;
  m43_3 = m29_3 ^ m32_3;
  m43_4 = m29_4 ^ m32_4;
  _Bool m44_0;
  _Bool m44_1;
  _Bool m44_2;
  _Bool m44_3;
  _Bool m44_4;
  m44_0 = m30_0 ^ m35_0;
  m44_1 = m30_1 ^ m35_1;
  m44_2 = m30_2 ^ m35_2;
  m44_3 = m30_3 ^ m35_3;
  m44_4 = m30_4 ^ m35_4;
  _Bool m45_0;
  _Bool m45_1;
  _Bool m45_2;
  _Bool m45_3;
  _Bool m45_4;
  m45_0 = m42_0 ^ m41_0;
  m45_1 = m42_1 ^ m41_1;
  m45_2 = m42_2 ^ m41_2;
  m45_3 = m42_3 ^ m41_3;
  m45_4 = m42_4 ^ m41_4;
  _Bool m46_0;
  _Bool m46_1;
  _Bool m46_2;
  _Bool m46_3;
  _Bool m46_4;
  HPC2(m44_0, m44_1, m44_2, m44_3, m44_4, t6_0, t6_1, t6_2, t6_3, t6_4, &m46_0, &m46_1, &m46_2, &m46_3, &m46_4, rand_281, rand_282, rand_283, rand_284, rand_285, rand_286, rand_287, rand_288, rand_289, rand_290);
  _Bool m47_0;
  _Bool m47_1;
  _Bool m47_2;
  _Bool m47_3;
  _Bool m47_4;
  HPC2(m35_0, m35_1, m35_2, m35_3, m35_4, t8_0, t8_1, t8_2, t8_3, t8_4, &m47_0, &m47_1, &m47_2, &m47_3, &m47_4, rand_291, rand_292, rand_293, rand_294, rand_295, rand_296, rand_297, rand_298, rand_299, rand_300);
  _Bool m48_0;
  _Bool m48_1;
  _Bool m48_2;
  _Bool m48_3;
  _Bool m48_4;
  HPC2(m30_0, m30_1, m30_2, m30_3, m30_4, i0_0, i0_1, i0_2, i0_3, i0_4, &m48_0, &m48_1, &m48_2, &m48_3, &m48_4, rand_301, rand_302, rand_303, rand_304, rand_305, rand_306, rand_307, rand_308, rand_309, rand_310);
  _Bool m49_0;
  _Bool m49_1;
  _Bool m49_2;
  _Bool m49_3;
  _Bool m49_4;
  HPC2(m43_0, m43_1, m43_2, m43_3, m43_4, t16_0, t16_1, t16_2, t16_3, t16_4, &m49_0, &m49_1, &m49_2, &m49_3, &m49_4, rand_311, rand_312, rand_313, rand_314, rand_315, rand_316, rand_317, rand_318, rand_319, rand_320);
  _Bool m50_0;
  _Bool m50_1;
  _Bool m50_2;
  _Bool m50_3;
  _Bool m50_4;
  HPC2(m32_0, m32_1, m32_2, m32_3, m32_4, t9_0, t9_1, t9_2, t9_3, t9_4, &m50_0, &m50_1, &m50_2, &m50_3, &m50_4, rand_321, rand_322, rand_323, rand_324, rand_325, rand_326, rand_327, rand_328, rand_329, rand_330);
  _Bool m51_0;
  _Bool m51_1;
  _Bool m51_2;
  _Bool m51_3;
  _Bool m51_4;
  HPC2(m29_0, m29_1, m29_2, m29_3, m29_4, t17_0, t17_1, t17_2, t17_3, t17_4, &m51_0, &m51_1, &m51_2, &m51_3, &m51_4, rand_331, rand_332, rand_333, rand_334, rand_335, rand_336, rand_337, rand_338, rand_339, rand_340);
  _Bool m52_0;
  _Bool m52_1;
  _Bool m52_2;
  _Bool m52_3;
  _Bool m52_4;
  HPC2(m42_0, m42_1, m42_2, m42_3, m42_4, t15_0, t15_1, t15_2, t15_3, t15_4, &m52_0, &m52_1, &m52_2, &m52_3, &m52_4, rand_341, rand_342, rand_343, rand_344, rand_345, rand_346, rand_347, rand_348, rand_349, rand_350);
  _Bool m53_0;
  _Bool m53_1;
  _Bool m53_2;
  _Bool m53_3;
  _Bool m53_4;
  HPC2(m45_0, m45_1, m45_2, m45_3, m45_4, t27_0, t27_1, t27_2, t27_3, t27_4, &m53_0, &m53_1, &m53_2, &m53_3, &m53_4, rand_351, rand_352, rand_353, rand_354, rand_355, rand_356, rand_357, rand_358, rand_359, rand_360);
  _Bool m54_0;
  _Bool m54_1;
  _Bool m54_2;
  _Bool m54_3;
  _Bool m54_4;
  HPC2(m41_0, m41_1, m41_2, m41_3, m41_4, t10_0, t10_1, t10_2, t10_3, t10_4, &m54_0, &m54_1, &m54_2, &m54_3, &m54_4, rand_361, rand_362, rand_363, rand_364, rand_365, rand_366, rand_367, rand_368, rand_369, rand_370);
  _Bool m55_0;
  _Bool m55_1;
  _Bool m55_2;
  _Bool m55_3;
  _Bool m55_4;
  HPC2(m44_0, m44_1, m44_2, m44_3, m44_4, t13_0, t13_1, t13_2, t13_3, t13_4, &m55_0, &m55_1, &m55_2, &m55_3, &m55_4, rand_371, rand_372, rand_373, rand_374, rand_375, rand_376, rand_377, rand_378, rand_379, rand_380);
  _Bool m56_0;
  _Bool m56_1;
  _Bool m56_2;
  _Bool m56_3;
  _Bool m56_4;
  HPC2(m35_0, m35_1, m35_2, m35_3, m35_4, t23_0, t23_1, t23_2, t23_3, t23_4, &m56_0, &m56_1, &m56_2, &m56_3, &m56_4, rand_381, rand_382, rand_383, rand_384, rand_385, rand_386, rand_387, rand_388, rand_389, rand_390);
  _Bool m57_0;
  _Bool m57_1;
  _Bool m57_2;
  _Bool m57_3;
  _Bool m57_4;
  HPC2(m30_0, m30_1, m30_2, m30_3, m30_4, t19_0, t19_1, t19_2, t19_3, t19_4, &m57_0, &m57_1, &m57_2, &m57_3, &m57_4, rand_391, rand_392, rand_393, rand_394, rand_395, rand_396, rand_397, rand_398, rand_399, rand_400);
  _Bool m58_0;
  _Bool m58_1;
  _Bool m58_2;
  _Bool m58_3;
  _Bool m58_4;
  HPC2(m43_0, m43_1, m43_2, m43_3, m43_4, t3_0, t3_1, t3_2, t3_3, t3_4, &m58_0, &m58_1, &m58_2, &m58_3, &m58_4, rand_401, rand_402, rand_403, rand_404, rand_405, rand_406, rand_407, rand_408, rand_409, rand_410);
  _Bool m59_0;
  _Bool m59_1;
  _Bool m59_2;
  _Bool m59_3;
  _Bool m59_4;
  HPC2(m32_0, m32_1, m32_2, m32_3, m32_4, t22_0, t22_1, t22_2, t22_3, t22_4, &m59_0, &m59_1, &m59_2, &m59_3, &m59_4, rand_411, rand_412, rand_413, rand_414, rand_415, rand_416, rand_417, rand_418, rand_419, rand_420);
  _Bool m60_0;
  _Bool m60_1;
  _Bool m60_2;
  _Bool m60_3;
  _Bool m60_4;
  HPC2(m29_0, m29_1, m29_2, m29_3, m29_4, t20_0, t20_1, t20_2, t20_3, t20_4, &m60_0, &m60_1, &m60_2, &m60_3, &m60_4, rand_421, rand_422, rand_423, rand_424, rand_425, rand_426, rand_427, rand_428, rand_429, rand_430);
  _Bool m61_0;
  _Bool m61_1;
  _Bool m61_2;
  _Bool m61_3;
  _Bool m61_4;
  HPC2(m42_0, m42_1, m42_2, m42_3, m42_4, t1_0, t1_1, t1_2, t1_3, t1_4, &m61_0, &m61_1, &m61_2, &m61_3, &m61_4, rand_431, rand_432, rand_433, rand_434, rand_435, rand_436, rand_437, rand_438, rand_439, rand_440);
  _Bool m62_0;
  _Bool m62_1;
  _Bool m62_2;
  _Bool m62_3;
  _Bool m62_4;
  HPC2(m45_0, m45_1, m45_2, m45_3, m45_4, t4_0, t4_1, t4_2, t4_3, t4_4, &m62_0, &m62_1, &m62_2, &m62_3, &m62_4, rand_441, rand_442, rand_443, rand_444, rand_445, rand_446, rand_447, rand_448, rand_449, rand_450);
  _Bool m63_0;
  _Bool m63_1;
  _Bool m63_2;
  _Bool m63_3;
  _Bool m63_4;
  HPC2(m41_0, m41_1, m41_2, m41_3, m41_4, t2_0, t2_1, t2_2, t2_3, t2_4, &m63_0, &m63_1, &m63_2, &m63_3, &m63_4, rand_451, rand_452, rand_453, rand_454, rand_455, rand_456, rand_457, rand_458, rand_459, rand_460);
  _Bool l0_0;
  _Bool l0_1;
  _Bool l0_2;
  _Bool l0_3;
  _Bool l0_4;
  l0_0 = m61_0 ^ m62_0;
  l0_1 = m61_1 ^ m62_1;
  l0_2 = m61_2 ^ m62_2;
  l0_3 = m61_3 ^ m62_3;
  l0_4 = m61_4 ^ m62_4;
  _Bool l1_0;
  _Bool l1_1;
  _Bool l1_2;
  _Bool l1_3;
  _Bool l1_4;
  l1_0 = m50_0 ^ m56_0;
  l1_1 = m50_1 ^ m56_1;
  l1_2 = m50_2 ^ m56_2;
  l1_3 = m50_3 ^ m56_3;
  l1_4 = m50_4 ^ m56_4;
  _Bool l2_0;
  _Bool l2_1;
  _Bool l2_2;
  _Bool l2_3;
  _Bool l2_4;
  l2_0 = m46_0 ^ m48_0;
  l2_1 = m46_1 ^ m48_1;
  l2_2 = m46_2 ^ m48_2;
  l2_3 = m46_3 ^ m48_3;
  l2_4 = m46_4 ^ m48_4;
  _Bool l3_0;
  _Bool l3_1;
  _Bool l3_2;
  _Bool l3_3;
  _Bool l3_4;
  l3_0 = m47_0 ^ m55_0;
  l3_1 = m47_1 ^ m55_1;
  l3_2 = m47_2 ^ m55_2;
  l3_3 = m47_3 ^ m55_3;
  l3_4 = m47_4 ^ m55_4;
  _Bool l4_0;
  _Bool l4_1;
  _Bool l4_2;
  _Bool l4_3;
  _Bool l4_4;
  l4_0 = m54_0 ^ m58_0;
  l4_1 = m54_1 ^ m58_1;
  l4_2 = m54_2 ^ m58_2;
  l4_3 = m54_3 ^ m58_3;
  l4_4 = m54_4 ^ m58_4;
  _Bool l5_0;
  _Bool l5_1;
  _Bool l5_2;
  _Bool l5_3;
  _Bool l5_4;
  l5_0 = m49_0 ^ m61_0;
  l5_1 = m49_1 ^ m61_1;
  l5_2 = m49_2 ^ m61_2;
  l5_3 = m49_3 ^ m61_3;
  l5_4 = m49_4 ^ m61_4;
  _Bool l6_0;
  _Bool l6_1;
  _Bool l6_2;
  _Bool l6_3;
  _Bool l6_4;
  l6_0 = m62_0 ^ l5_0;
  l6_1 = m62_1 ^ l5_1;
  l6_2 = m62_2 ^ l5_2;
  l6_3 = m62_3 ^ l5_3;
  l6_4 = m62_4 ^ l5_4;
  _Bool l7_0;
  _Bool l7_1;
  _Bool l7_2;
  _Bool l7_3;
  _Bool l7_4;
  l7_0 = m46_0 ^ l3_0;
  l7_1 = m46_1 ^ l3_1;
  l7_2 = m46_2 ^ l3_2;
  l7_3 = m46_3 ^ l3_3;
  l7_4 = m46_4 ^ l3_4;
  _Bool l8_0;
  _Bool l8_1;
  _Bool l8_2;
  _Bool l8_3;
  _Bool l8_4;
  l8_0 = m51_0 ^ m59_0;
  l8_1 = m51_1 ^ m59_1;
  l8_2 = m51_2 ^ m59_2;
  l8_3 = m51_3 ^ m59_3;
  l8_4 = m51_4 ^ m59_4;
  _Bool l9_0;
  _Bool l9_1;
  _Bool l9_2;
  _Bool l9_3;
  _Bool l9_4;
  l9_0 = m52_0 ^ m53_0;
  l9_1 = m52_1 ^ m53_1;
  l9_2 = m52_2 ^ m53_2;
  l9_3 = m52_3 ^ m53_3;
  l9_4 = m52_4 ^ m53_4;
  _Bool l10_0;
  _Bool l10_1;
  _Bool l10_2;
  _Bool l10_3;
  _Bool l10_4;
  l10_0 = m53_0 ^ l4_0;
  l10_1 = m53_1 ^ l4_1;
  l10_2 = m53_2 ^ l4_2;
  l10_3 = m53_3 ^ l4_3;
  l10_4 = m53_4 ^ l4_4;
  _Bool l11_0;
  _Bool l11_1;
  _Bool l11_2;
  _Bool l11_3;
  _Bool l11_4;
  l11_0 = m60_0 ^ l2_0;
  l11_1 = m60_1 ^ l2_1;
  l11_2 = m60_2 ^ l2_2;
  l11_3 = m60_3 ^ l2_3;
  l11_4 = m60_4 ^ l2_4;
  _Bool l12_0;
  _Bool l12_1;
  _Bool l12_2;
  _Bool l12_3;
  _Bool l12_4;
  l12_0 = m48_0 ^ m51_0;
  l12_1 = m48_1 ^ m51_1;
  l12_2 = m48_2 ^ m51_2;
  l12_3 = m48_3 ^ m51_3;
  l12_4 = m48_4 ^ m51_4;
  _Bool l13_0;
  _Bool l13_1;
  _Bool l13_2;
  _Bool l13_3;
  _Bool l13_4;
  l13_0 = m50_0 ^ l0_0;
  l13_1 = m50_1 ^ l0_1;
  l13_2 = m50_2 ^ l0_2;
  l13_3 = m50_3 ^ l0_3;
  l13_4 = m50_4 ^ l0_4;
  _Bool l14_0;
  _Bool l14_1;
  _Bool l14_2;
  _Bool l14_3;
  _Bool l14_4;
  l14_0 = m52_0 ^ m61_0;
  l14_1 = m52_1 ^ m61_1;
  l14_2 = m52_2 ^ m61_2;
  l14_3 = m52_3 ^ m61_3;
  l14_4 = m52_4 ^ m61_4;
  _Bool l15_0;
  _Bool l15_1;
  _Bool l15_2;
  _Bool l15_3;
  _Bool l15_4;
  l15_0 = m55_0 ^ l1_0;
  l15_1 = m55_1 ^ l1_1;
  l15_2 = m55_2 ^ l1_2;
  l15_3 = m55_3 ^ l1_3;
  l15_4 = m55_4 ^ l1_4;
  _Bool l16_0;
  _Bool l16_1;
  _Bool l16_2;
  _Bool l16_3;
  _Bool l16_4;
  l16_0 = m56_0 ^ l0_0;
  l16_1 = m56_1 ^ l0_1;
  l16_2 = m56_2 ^ l0_2;
  l16_3 = m56_3 ^ l0_3;
  l16_4 = m56_4 ^ l0_4;
  _Bool l17_0;
  _Bool l17_1;
  _Bool l17_2;
  _Bool l17_3;
  _Bool l17_4;
  l17_0 = m57_0 ^ l1_0;
  l17_1 = m57_1 ^ l1_1;
  l17_2 = m57_2 ^ l1_2;
  l17_3 = m57_3 ^ l1_3;
  l17_4 = m57_4 ^ l1_4;
  _Bool l18_0;
  _Bool l18_1;
  _Bool l18_2;
  _Bool l18_3;
  _Bool l18_4;
  l18_0 = m58_0 ^ l8_0;
  l18_1 = m58_1 ^ l8_1;
  l18_2 = m58_2 ^ l8_2;
  l18_3 = m58_3 ^ l8_3;
  l18_4 = m58_4 ^ l8_4;
  _Bool l19_0;
  _Bool l19_1;
  _Bool l19_2;
  _Bool l19_3;
  _Bool l19_4;
  l19_0 = m63_0 ^ l4_0;
  l19_1 = m63_1 ^ l4_1;
  l19_2 = m63_2 ^ l4_2;
  l19_3 = m63_3 ^ l4_3;
  l19_4 = m63_4 ^ l4_4;
  _Bool l20_0;
  _Bool l20_1;
  _Bool l20_2;
  _Bool l20_3;
  _Bool l20_4;
  l20_0 = l0_0 ^ l1_0;
  l20_1 = l0_1 ^ l1_1;
  l20_2 = l0_2 ^ l1_2;
  l20_3 = l0_3 ^ l1_3;
  l20_4 = l0_4 ^ l1_4;
  _Bool l21_0;
  _Bool l21_1;
  _Bool l21_2;
  _Bool l21_3;
  _Bool l21_4;
  l21_0 = l1_0 ^ l7_0;
  l21_1 = l1_1 ^ l7_1;
  l21_2 = l1_2 ^ l7_2;
  l21_3 = l1_3 ^ l7_3;
  l21_4 = l1_4 ^ l7_4;
  _Bool l22_0;
  _Bool l22_1;
  _Bool l22_2;
  _Bool l22_3;
  _Bool l22_4;
  l22_0 = l3_0 ^ l12_0;
  l22_1 = l3_1 ^ l12_1;
  l22_2 = l3_2 ^ l12_2;
  l22_3 = l3_3 ^ l12_3;
  l22_4 = l3_4 ^ l12_4;
  _Bool l23_0;
  _Bool l23_1;
  _Bool l23_2;
  _Bool l23_3;
  _Bool l23_4;
  l23_0 = l18_0 ^ l2_0;
  l23_1 = l18_1 ^ l2_1;
  l23_2 = l18_2 ^ l2_2;
  l23_3 = l18_3 ^ l2_3;
  l23_4 = l18_4 ^ l2_4;
  _Bool l24_0;
  _Bool l24_1;
  _Bool l24_2;
  _Bool l24_3;
  _Bool l24_4;
  l24_0 = l15_0 ^ l9_0;
  l24_1 = l15_1 ^ l9_1;
  l24_2 = l15_2 ^ l9_2;
  l24_3 = l15_3 ^ l9_3;
  l24_4 = l15_4 ^ l9_4;
  _Bool l25_0;
  _Bool l25_1;
  _Bool l25_2;
  _Bool l25_3;
  _Bool l25_4;
  l25_0 = l6_0 ^ l10_0;
  l25_1 = l6_1 ^ l10_1;
  l25_2 = l6_2 ^ l10_2;
  l25_3 = l6_3 ^ l10_3;
  l25_4 = l6_4 ^ l10_4;
  _Bool l26_0;
  _Bool l26_1;
  _Bool l26_2;
  _Bool l26_3;
  _Bool l26_4;
  l26_0 = l7_0 ^ l9_0;
  l26_1 = l7_1 ^ l9_1;
  l26_2 = l7_2 ^ l9_2;
  l26_3 = l7_3 ^ l9_3;
  l26_4 = l7_4 ^ l9_4;
  _Bool l27_0;
  _Bool l27_1;
  _Bool l27_2;
  _Bool l27_3;
  _Bool l27_4;
  l27_0 = l8_0 ^ l10_0;
  l27_1 = l8_1 ^ l10_1;
  l27_2 = l8_2 ^ l10_2;
  l27_3 = l8_3 ^ l10_3;
  l27_4 = l8_4 ^ l10_4;
  _Bool l28_0;
  _Bool l28_1;
  _Bool l28_2;
  _Bool l28_3;
  _Bool l28_4;
  l28_0 = l11_0 ^ l14_0;
  l28_1 = l11_1 ^ l14_1;
  l28_2 = l11_2 ^ l14_2;
  l28_3 = l11_3 ^ l14_3;
  l28_4 = l11_4 ^ l14_4;
  _Bool l29_0;
  _Bool l29_1;
  _Bool l29_2;
  _Bool l29_3;
  _Bool l29_4;
  l29_0 = l11_0 ^ l17_0;
  l29_1 = l11_1 ^ l17_1;
  l29_2 = l11_2 ^ l17_2;
  l29_3 = l11_3 ^ l17_3;
  l29_4 = l11_4 ^ l17_4;
  *y7_0 = l6_0 ^ l24_0;
  *y7_1 = l6_1 ^ l24_1;
  *y7_2 = l6_2 ^ l24_2;
  *y7_3 = l6_3 ^ l24_3;
  *y7_4 = l6_4 ^ l24_4;
  _Bool l30_0;
  _Bool l30_1;
  _Bool l30_2;
  _Bool l30_3;
  _Bool l30_4;
  l30_0 = l16_0 ^ l26_0;
  l30_1 = l16_1 ^ l26_1;
  l30_2 = l16_2 ^ l26_2;
  l30_3 = l16_3 ^ l26_3;
  l30_4 = l16_4 ^ l26_4;
  *y6_0 = l30_0;
  *y6_1 = l30_1;
  *y6_2 = l30_2;
  *y6_3 = l30_3;
  *y6_4 = !l30_4;
  _Bool l31_0;
  _Bool l31_1;
  _Bool l31_2;
  _Bool l31_3;
  _Bool l31_4;
  l31_0 = l19_0 ^ l28_0;
  l31_1 = l19_1 ^ l28_1;
  l31_2 = l19_2 ^ l28_2;
  l31_3 = l19_3 ^ l28_3;
  l31_4 = l19_4 ^ l28_4;
  *y5_0 = l31_0;
  *y5_1 = l31_1;
  *y5_2 = l31_2;
  *y5_3 = l31_3;
  *y5_4 = !l31_4;
  *y4_0 = l6_0 ^ l21_0;
  *y4_1 = l6_1 ^ l21_1;
  *y4_2 = l6_2 ^ l21_2;
  *y4_3 = l6_3 ^ l21_3;
  *y4_4 = l6_4 ^ l21_4;
  *y3_0 = l20_0 ^ l22_0;
  *y3_1 = l20_1 ^ l22_1;
  *y3_2 = l20_2 ^ l22_2;
  *y3_3 = l20_3 ^ l22_3;
  *y3_4 = l20_4 ^ l22_4;
  *y2_0 = l25_0 ^ l29_0;
  *y2_1 = l25_1 ^ l29_1;
  *y2_2 = l25_2 ^ l29_2;
  *y2_3 = l25_3 ^ l29_3;
  *y2_4 = l25_4 ^ l29_4;
  _Bool l32_0;
  _Bool l32_1;
  _Bool l32_2;
  _Bool l32_3;
  _Bool l32_4;
  l32_0 = l13_0 ^ l27_0;
  l32_1 = l13_1 ^ l27_1;
  l32_2 = l13_2 ^ l27_2;
  l32_3 = l13_3 ^ l27_3;
  l32_4 = l13_4 ^ l27_4;
  *y1_0 = l32_0;
  *y1_1 = l32_1;
  *y1_2 = l32_2;
  *y1_3 = l32_3;
  *y1_4 = !l32_4;
  _Bool l33_0;
  _Bool l33_1;
  _Bool l33_2;
  _Bool l33_3;
  _Bool l33_4;
  l33_0 = l6_0 ^ l23_0;
  l33_1 = l6_1 ^ l23_1;
  l33_2 = l6_2 ^ l23_2;
  l33_3 = l6_3 ^ l23_3;
  l33_4 = l6_4 ^ l23_4;
  *y0_0 = l33_0;
  *y0_1 = l33_1;
  *y0_2 = l33_2;
  *y0_3 = l33_3;
  *y0_4 = !l33_4;
}

