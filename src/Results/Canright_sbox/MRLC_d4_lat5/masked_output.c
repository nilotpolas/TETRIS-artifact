// === GADGET DEFINITIONS ===

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
void sbox(_Bool sb_n0_0, _Bool sb_n0_1, _Bool sb_n0_2, _Bool sb_n0_3, _Bool sb_n0_4, _Bool sb_n1_0, _Bool sb_n1_1, _Bool sb_n1_2, _Bool sb_n1_3, _Bool sb_n1_4, _Bool sb_n2_0, _Bool sb_n2_1, _Bool sb_n2_2, _Bool sb_n2_3, _Bool sb_n2_4, _Bool sb_n3_0, _Bool sb_n3_1, _Bool sb_n3_2, _Bool sb_n3_3, _Bool sb_n3_4, _Bool sb_n4_0, _Bool sb_n4_1, _Bool sb_n4_2, _Bool sb_n4_3, _Bool sb_n4_4, _Bool sb_n5_0, _Bool sb_n5_1, _Bool sb_n5_2, _Bool sb_n5_3, _Bool sb_n5_4, _Bool sb_n6_0, _Bool sb_n6_1, _Bool sb_n6_2, _Bool sb_n6_3, _Bool sb_n6_4, _Bool sb_n7_0, _Bool sb_n7_1, _Bool sb_n7_2, _Bool sb_n7_3, _Bool sb_n7_4, _Bool *sb_o0_0, _Bool *sb_o0_1, _Bool *sb_o0_2, _Bool *sb_o0_3, _Bool *sb_o0_4, _Bool *sb_o1_0, _Bool *sb_o1_1, _Bool *sb_o1_2, _Bool *sb_o1_3, _Bool *sb_o1_4, _Bool *sb_o2_0, _Bool *sb_o2_1, _Bool *sb_o2_2, _Bool *sb_o2_3, _Bool *sb_o2_4, _Bool *sb_o3_0, _Bool *sb_o3_1, _Bool *sb_o3_2, _Bool *sb_o3_3, _Bool *sb_o3_4, _Bool *sb_o4_0, _Bool *sb_o4_1, _Bool *sb_o4_2, _Bool *sb_o4_3, _Bool *sb_o4_4, _Bool *sb_o5_0, _Bool *sb_o5_1, _Bool *sb_o5_2, _Bool *sb_o5_3, _Bool *sb_o5_4, _Bool *sb_o6_0, _Bool *sb_o6_1, _Bool *sb_o6_2, _Bool *sb_o6_3, _Bool *sb_o6_4, _Bool *sb_o7_0, _Bool *sb_o7_1, _Bool *sb_o7_2, _Bool *sb_o7_3, _Bool *sb_o7_4, int dec_1, int rand_34, int rand_35, int rand_36, int rand_37, int rand_38, int rand_39, int rand_40, int rand_61, int rand_41, int rand_42, int rand_43, int rand_44, int rand_45, int rand_46, int rand_47, int rand_48, int rand_49, int rand_50, int rand_51, int rand_52, int rand_53, int rand_54, int rand_55, int rand_56, int rand_57, int rand_58, int rand_59, int rand_60, int rand_62, int rand_63, int rand_64, int rand_65, int rand_66, int rand_67, int rand_68, int rand_69, int rand_70, int rand_1, int rand_92, int rand_71, int rand_72, int rand_73, int rand_74, int rand_75, int rand_76, int rand_77, int rand_78, int rand_79, int rand_80, int rand_81, int rand_82, int rand_83, int rand_84, int rand_85, int rand_86, int rand_87, int rand_88, int rand_89, int rand_90, int rand_91, int rand_93, int rand_94, int rand_95, int rand_96, int rand_97, int rand_98, int rand_99, int rand_100, int rand_101, int rand_102, int rand_103, int rand_104, int rand_105, int rand_106, int rand_107, int rand_108, int rand_109, int rand_110, int rand_111, int rand_112, int rand_113, int rand_114, int rand_115, int rand_116, int rand_386, int rand_117, int rand_332, int rand_118, int rand_387, int rand_119, int rand_389, int rand_120, int rand_388, int rand_121, int rand_390, int rand_122, int rand_123, int rand_124, int rand_330, int rand_125, int rand_331, int rand_126, int rand_333, int rand_127, int rand_334, int rand_128, int rand_335, int rand_129, int rand_336, int rand_130, int rand_337, int rand_131, int rand_338, int rand_132, int rand_339, int rand_133, int rand_340, int rand_134, int rand_341, int rand_135, int rand_342, int rand_136, int rand_343, int rand_137, int rand_344, int rand_138, int rand_345, int rand_139, int rand_346, int rand_140, int rand_347, int rand_141, int rand_348, int rand_142, int rand_349, int rand_143, int rand_350, int rand_144, int rand_351, int rand_145, int rand_352, int rand_146, int rand_353, int rand_2, int rand_147, int rand_354, int rand_3, int rand_148, int rand_355, int rand_4, int rand_149, int rand_356, int rand_5, int rand_150, int rand_357, int rand_6, int rand_151, int rand_358, int rand_7, int rand_152, int rand_359, int rand_8, int rand_153, int rand_360, int rand_9, int rand_154, int rand_362, int rand_10, int rand_155, int rand_361, int rand_11, int rand_156, int rand_363, int rand_12, int rand_157, int rand_364, int rand_13, int rand_158, int rand_365, int rand_14, int rand_159, int rand_366, int rand_15, int rand_160, int rand_367, int rand_16, int rand_161, int rand_368, int rand_17, int rand_162, int rand_369, int rand_18, int rand_163, int rand_370, int rand_19, int rand_164, int rand_371, int rand_20, int rand_165, int rand_372, int rand_21, int rand_166, int rand_373, int rand_22, int rand_167, int rand_374, int rand_23, int rand_168, int rand_375, int rand_24, int rand_169, int rand_376, int rand_25, int rand_170, int rand_377, int rand_26, int rand_171, int rand_378, int rand_27, int rand_172, int rand_379, int rand_28, int rand_173, int rand_380, int rand_29, int rand_174, int rand_381, int rand_30, int rand_175, int rand_382, int rand_32, int rand_176, int rand_383, int rand_31, int rand_177, int rand_384, int rand_33, int rand_178, int rand_385, int rand_179, int rand_315, int rand_180, int rand_316, int rand_181, int rand_317, int rand_182, int rand_318, int rand_183, int rand_319, int rand_184, int rand_320, int rand_185, int rand_321, int rand_186, int rand_322, int rand_187, int rand_323, int rand_188, int rand_324, int rand_189, int rand_325, int rand_190, int rand_326, int rand_191, int rand_327, int rand_192, int rand_328, int rand_193, int rand_329, int rand_194, int rand_314, int rand_195, int rand_196, int rand_197, int rand_198, int rand_199, int rand_200, int rand_201, int rand_202, int rand_203, int rand_204, int rand_205, int rand_206, int rand_207, int rand_208, int rand_209, int rand_210, int rand_211, int rand_212, int rand_213, int rand_214, int rand_215, int rand_216, int rand_217, int rand_218, int rand_219, int rand_220, int rand_221, int rand_222, int rand_223, int rand_224, int rand_225, int rand_226, int rand_227, int rand_228, int rand_229, int rand_230, int rand_231, int rand_232, int rand_233, int rand_234, int rand_235, int rand_236, int rand_237, int rand_238, int rand_239, int rand_240, int rand_242, int rand_241, int rand_243, int rand_244, int rand_245, int rand_246, int rand_247, int rand_248, int rand_249, int rand_250, int rand_251, int rand_252, int rand_253, int rand_254, int rand_255, int rand_256, int rand_257, int rand_258, int rand_259, int rand_260, int rand_261, int rand_262, int rand_263, int rand_264, int rand_265, int rand_266, int rand_267, int rand_268, int rand_269, int rand_270, int rand_271, int rand_272, int rand_273, int rand_274, int rand_275, int rand_276, int rand_277, int rand_278, int rand_279, int rand_280, int rand_281, int rand_282, int rand_312, int rand_283, int rand_284, int rand_285, int rand_313, int rand_286, int rand_287, int rand_288, int rand_289, int rand_290, int rand_291, int rand_292, int rand_293, int rand_294, int rand_295, int rand_296, int rand_297, int rand_298, int rand_299, int rand_300, int rand_301, int rand_302, int rand_303, int rand_304, int rand_305, int rand_306, int rand_311, int rand_307, int rand_308, int rand_309, int rand_310)
{
  _Bool sb_y0_0;
  _Bool sb_y0_1;
  _Bool sb_y0_2;
  _Bool sb_y0_3;
  _Bool sb_y0_4;
  _Bool sb_y1_0;
  _Bool sb_y1_1;
  _Bool sb_y1_2;
  _Bool sb_y1_3;
  _Bool sb_y1_4;
  _Bool sb_y2_0;
  _Bool sb_y2_1;
  _Bool sb_y2_2;
  _Bool sb_y2_3;
  _Bool sb_y2_4;
  _Bool sb_y3_0;
  _Bool sb_y3_1;
  _Bool sb_y3_2;
  _Bool sb_y3_3;
  _Bool sb_y3_4;
  _Bool sb_y4_0;
  _Bool sb_y4_1;
  _Bool sb_y4_2;
  _Bool sb_y4_3;
  _Bool sb_y4_4;
  _Bool sb_y5_0;
  _Bool sb_y5_1;
  _Bool sb_y5_2;
  _Bool sb_y5_3;
  _Bool sb_y5_4;
  _Bool sb_y6_0;
  _Bool sb_y6_1;
  _Bool sb_y6_2;
  _Bool sb_y6_3;
  _Bool sb_y6_4;
  _Bool sb_y7_0;
  _Bool sb_y7_1;
  _Bool sb_y7_2;
  _Bool sb_y7_3;
  _Bool sb_y7_4;
  _Bool sb_i0_0;
  _Bool sb_i0_1;
  _Bool sb_i0_2;
  _Bool sb_i0_3;
  _Bool sb_i0_4;
  _Bool sb_i1_0;
  _Bool sb_i1_1;
  _Bool sb_i1_2;
  _Bool sb_i1_3;
  _Bool sb_i1_4;
  _Bool sb_i2_0;
  _Bool sb_i2_1;
  _Bool sb_i2_2;
  _Bool sb_i2_3;
  _Bool sb_i2_4;
  _Bool sb_i3_0;
  _Bool sb_i3_1;
  _Bool sb_i3_2;
  _Bool sb_i3_3;
  _Bool sb_i3_4;
  _Bool sb_i4_0;
  _Bool sb_i4_1;
  _Bool sb_i4_2;
  _Bool sb_i4_3;
  _Bool sb_i4_4;
  _Bool sb_i5_0;
  _Bool sb_i5_1;
  _Bool sb_i5_2;
  _Bool sb_i5_3;
  _Bool sb_i5_4;
  _Bool sb_i6_0;
  _Bool sb_i6_1;
  _Bool sb_i6_2;
  _Bool sb_i6_3;
  _Bool sb_i6_4;
  _Bool sb_i7_0;
  _Bool sb_i7_1;
  _Bool sb_i7_2;
  _Bool sb_i7_3;
  _Bool sb_i7_4;
  _Bool fy0_0;
  _Bool fy0_1;
  _Bool fy0_2;
  _Bool fy0_3;
  _Bool fy0_4;
  _Bool fy1_0;
  _Bool fy1_1;
  _Bool fy1_2;
  _Bool fy1_3;
  _Bool fy1_4;
  _Bool fy2_0;
  _Bool fy2_1;
  _Bool fy2_2;
  _Bool fy2_3;
  _Bool fy2_4;
  _Bool fy3_0;
  _Bool fy3_1;
  _Bool fy3_2;
  _Bool fy3_3;
  _Bool fy3_4;
  _Bool fy4_0;
  _Bool fy4_1;
  _Bool fy4_2;
  _Bool fy4_3;
  _Bool fy4_4;
  _Bool fy5_0;
  _Bool fy5_1;
  _Bool fy5_2;
  _Bool fy5_3;
  _Bool fy5_4;
  _Bool fy6_0;
  _Bool fy6_1;
  _Bool fy6_2;
  _Bool fy6_3;
  _Bool fy6_4;
  _Bool fy7_0;
  _Bool fy7_1;
  _Bool fy7_2;
  _Bool fy7_3;
  _Bool fy7_4;
  _Bool temp_var_0_0;
  _Bool temp_var_0_1;
  _Bool temp_var_0_2;
  _Bool temp_var_0_3;
  _Bool temp_var_0_4;
  temp_var_0_0 = sb_n0_0 ^ sb_n1_0;
  temp_var_0_1 = sb_n0_1 ^ sb_n1_1;
  temp_var_0_2 = sb_n0_2 ^ sb_n1_2;
  temp_var_0_3 = sb_n0_3 ^ sb_n1_3;
  temp_var_0_4 = sb_n0_4 ^ sb_n1_4;
  _Bool temp_var_1_0;
  _Bool temp_var_1_1;
  _Bool temp_var_1_2;
  _Bool temp_var_1_3;
  _Bool temp_var_1_4;
  temp_var_1_0 = temp_var_0_0 ^ sb_n2_0;
  temp_var_1_1 = temp_var_0_1 ^ sb_n2_1;
  temp_var_1_2 = temp_var_0_2 ^ sb_n2_2;
  temp_var_1_3 = temp_var_0_3 ^ sb_n2_3;
  temp_var_1_4 = temp_var_0_4 ^ sb_n2_4;
  _Bool temp_var_2_0;
  _Bool temp_var_2_1;
  _Bool temp_var_2_2;
  _Bool temp_var_2_3;
  _Bool temp_var_2_4;
  temp_var_2_0 = temp_var_1_0 ^ sb_n3_0;
  temp_var_2_1 = temp_var_1_1 ^ sb_n3_1;
  temp_var_2_2 = temp_var_1_2 ^ sb_n3_2;
  temp_var_2_3 = temp_var_1_3 ^ sb_n3_3;
  temp_var_2_4 = temp_var_1_4 ^ sb_n3_4;
  sb_y0_0 = temp_var_2_0 ^ sb_n6_0;
  sb_y0_1 = temp_var_2_1 ^ sb_n6_1;
  sb_y0_2 = temp_var_2_2 ^ sb_n6_2;
  sb_y0_3 = temp_var_2_3 ^ sb_n6_3;
  sb_y0_4 = temp_var_2_4 ^ sb_n6_4;
  _Bool temp_var_3_0;
  _Bool temp_var_3_1;
  _Bool temp_var_3_2;
  _Bool temp_var_3_3;
  _Bool temp_var_3_4;
  temp_var_3_0 = sb_n0_0 ^ sb_n5_0;
  temp_var_3_1 = sb_n0_1 ^ sb_n5_1;
  temp_var_3_2 = sb_n0_2 ^ sb_n5_2;
  temp_var_3_3 = sb_n0_3 ^ sb_n5_3;
  temp_var_3_4 = sb_n0_4 ^ sb_n5_4;
  sb_y1_0 = temp_var_3_0 ^ sb_n6_0;
  sb_y1_1 = temp_var_3_1 ^ sb_n6_1;
  sb_y1_2 = temp_var_3_2 ^ sb_n6_2;
  sb_y1_3 = temp_var_3_3 ^ sb_n6_3;
  sb_y1_4 = temp_var_3_4 ^ sb_n6_4;
  sb_y2_0 = sb_n0_0;
  sb_y2_1 = sb_n0_1;
  sb_y2_2 = sb_n0_2;
  sb_y2_3 = sb_n0_3;
  sb_y2_4 = sb_n0_4;
  _Bool temp_var_4_0;
  _Bool temp_var_4_1;
  _Bool temp_var_4_2;
  _Bool temp_var_4_3;
  _Bool temp_var_4_4;
  temp_var_4_0 = sb_n0_0 ^ sb_n1_0;
  temp_var_4_1 = sb_n0_1 ^ sb_n1_1;
  temp_var_4_2 = sb_n0_2 ^ sb_n1_2;
  temp_var_4_3 = sb_n0_3 ^ sb_n1_3;
  temp_var_4_4 = sb_n0_4 ^ sb_n1_4;
  _Bool temp_var_5_0;
  _Bool temp_var_5_1;
  _Bool temp_var_5_2;
  _Bool temp_var_5_3;
  _Bool temp_var_5_4;
  temp_var_5_0 = temp_var_4_0 ^ sb_n3_0;
  temp_var_5_1 = temp_var_4_1 ^ sb_n3_1;
  temp_var_5_2 = temp_var_4_2 ^ sb_n3_2;
  temp_var_5_3 = temp_var_4_3 ^ sb_n3_3;
  temp_var_5_4 = temp_var_4_4 ^ sb_n3_4;
  _Bool temp_var_6_0;
  _Bool temp_var_6_1;
  _Bool temp_var_6_2;
  _Bool temp_var_6_3;
  _Bool temp_var_6_4;
  temp_var_6_0 = temp_var_5_0 ^ sb_n4_0;
  temp_var_6_1 = temp_var_5_1 ^ sb_n4_1;
  temp_var_6_2 = temp_var_5_2 ^ sb_n4_2;
  temp_var_6_3 = temp_var_5_3 ^ sb_n4_3;
  temp_var_6_4 = temp_var_5_4 ^ sb_n4_4;
  sb_y3_0 = temp_var_6_0 ^ sb_n7_0;
  sb_y3_1 = temp_var_6_1 ^ sb_n7_1;
  sb_y3_2 = temp_var_6_2 ^ sb_n7_2;
  sb_y3_3 = temp_var_6_3 ^ sb_n7_3;
  sb_y3_4 = temp_var_6_4 ^ sb_n7_4;
  _Bool temp_var_7_0;
  _Bool temp_var_7_1;
  _Bool temp_var_7_2;
  _Bool temp_var_7_3;
  _Bool temp_var_7_4;
  temp_var_7_0 = sb_n0_0 ^ sb_n5_0;
  temp_var_7_1 = sb_n0_1 ^ sb_n5_1;
  temp_var_7_2 = sb_n0_2 ^ sb_n5_2;
  temp_var_7_3 = sb_n0_3 ^ sb_n5_3;
  temp_var_7_4 = sb_n0_4 ^ sb_n5_4;
  _Bool temp_var_8_0;
  _Bool temp_var_8_1;
  _Bool temp_var_8_2;
  _Bool temp_var_8_3;
  _Bool temp_var_8_4;
  temp_var_8_0 = temp_var_7_0 ^ sb_n6_0;
  temp_var_8_1 = temp_var_7_1 ^ sb_n6_1;
  temp_var_8_2 = temp_var_7_2 ^ sb_n6_2;
  temp_var_8_3 = temp_var_7_3 ^ sb_n6_3;
  temp_var_8_4 = temp_var_7_4 ^ sb_n6_4;
  sb_y4_0 = temp_var_8_0 ^ sb_n7_0;
  sb_y4_1 = temp_var_8_1 ^ sb_n7_1;
  sb_y4_2 = temp_var_8_2 ^ sb_n7_2;
  sb_y4_3 = temp_var_8_3 ^ sb_n7_3;
  sb_y4_4 = temp_var_8_4 ^ sb_n7_4;
  _Bool temp_var_9_0;
  _Bool temp_var_9_1;
  _Bool temp_var_9_2;
  _Bool temp_var_9_3;
  _Bool temp_var_9_4;
  temp_var_9_0 = sb_n0_0 ^ sb_n1_0;
  temp_var_9_1 = sb_n0_1 ^ sb_n1_1;
  temp_var_9_2 = sb_n0_2 ^ sb_n1_2;
  temp_var_9_3 = sb_n0_3 ^ sb_n1_3;
  temp_var_9_4 = sb_n0_4 ^ sb_n1_4;
  _Bool temp_var_10_0;
  _Bool temp_var_10_1;
  _Bool temp_var_10_2;
  _Bool temp_var_10_3;
  _Bool temp_var_10_4;
  temp_var_10_0 = temp_var_9_0 ^ sb_n5_0;
  temp_var_10_1 = temp_var_9_1 ^ sb_n5_1;
  temp_var_10_2 = temp_var_9_2 ^ sb_n5_2;
  temp_var_10_3 = temp_var_9_3 ^ sb_n5_3;
  temp_var_10_4 = temp_var_9_4 ^ sb_n5_4;
  sb_y5_0 = temp_var_10_0 ^ sb_n6_0;
  sb_y5_1 = temp_var_10_1 ^ sb_n6_1;
  sb_y5_2 = temp_var_10_2 ^ sb_n6_2;
  sb_y5_3 = temp_var_10_3 ^ sb_n6_3;
  sb_y5_4 = temp_var_10_4 ^ sb_n6_4;
  _Bool temp_var_11_0;
  _Bool temp_var_11_1;
  _Bool temp_var_11_2;
  _Bool temp_var_11_3;
  _Bool temp_var_11_4;
  temp_var_11_0 = sb_n0_0 ^ sb_n4_0;
  temp_var_11_1 = sb_n0_1 ^ sb_n4_1;
  temp_var_11_2 = sb_n0_2 ^ sb_n4_2;
  temp_var_11_3 = sb_n0_3 ^ sb_n4_3;
  temp_var_11_4 = sb_n0_4 ^ sb_n4_4;
  _Bool temp_var_12_0;
  _Bool temp_var_12_1;
  _Bool temp_var_12_2;
  _Bool temp_var_12_3;
  _Bool temp_var_12_4;
  temp_var_12_0 = temp_var_11_0 ^ sb_n5_0;
  temp_var_12_1 = temp_var_11_1 ^ sb_n5_1;
  temp_var_12_2 = temp_var_11_2 ^ sb_n5_2;
  temp_var_12_3 = temp_var_11_3 ^ sb_n5_3;
  temp_var_12_4 = temp_var_11_4 ^ sb_n5_4;
  sb_y6_0 = temp_var_12_0 ^ sb_n6_0;
  sb_y6_1 = temp_var_12_1 ^ sb_n6_1;
  sb_y6_2 = temp_var_12_2 ^ sb_n6_2;
  sb_y6_3 = temp_var_12_3 ^ sb_n6_3;
  sb_y6_4 = temp_var_12_4 ^ sb_n6_4;
  _Bool temp_var_13_0;
  _Bool temp_var_13_1;
  _Bool temp_var_13_2;
  _Bool temp_var_13_3;
  _Bool temp_var_13_4;
  temp_var_13_0 = sb_n0_0 ^ sb_n1_0;
  temp_var_13_1 = sb_n0_1 ^ sb_n1_1;
  temp_var_13_2 = sb_n0_2 ^ sb_n1_2;
  temp_var_13_3 = sb_n0_3 ^ sb_n1_3;
  temp_var_13_4 = sb_n0_4 ^ sb_n1_4;
  _Bool temp_var_14_0;
  _Bool temp_var_14_1;
  _Bool temp_var_14_2;
  _Bool temp_var_14_3;
  _Bool temp_var_14_4;
  temp_var_14_0 = temp_var_13_0 ^ sb_n2_0;
  temp_var_14_1 = temp_var_13_1 ^ sb_n2_1;
  temp_var_14_2 = temp_var_13_2 ^ sb_n2_2;
  temp_var_14_3 = temp_var_13_3 ^ sb_n2_3;
  temp_var_14_4 = temp_var_13_4 ^ sb_n2_4;
  _Bool temp_var_15_0;
  _Bool temp_var_15_1;
  _Bool temp_var_15_2;
  _Bool temp_var_15_3;
  _Bool temp_var_15_4;
  temp_var_15_0 = temp_var_14_0 ^ sb_n5_0;
  temp_var_15_1 = temp_var_14_1 ^ sb_n5_1;
  temp_var_15_2 = temp_var_14_2 ^ sb_n5_2;
  temp_var_15_3 = temp_var_14_3 ^ sb_n5_3;
  temp_var_15_4 = temp_var_14_4 ^ sb_n5_4;
  _Bool temp_var_16_0;
  _Bool temp_var_16_1;
  _Bool temp_var_16_2;
  _Bool temp_var_16_3;
  _Bool temp_var_16_4;
  temp_var_16_0 = temp_var_15_0 ^ sb_n6_0;
  temp_var_16_1 = temp_var_15_1 ^ sb_n6_1;
  temp_var_16_2 = temp_var_15_2 ^ sb_n6_2;
  temp_var_16_3 = temp_var_15_3 ^ sb_n6_3;
  temp_var_16_4 = temp_var_15_4 ^ sb_n6_4;
  sb_y7_0 = temp_var_16_0 ^ sb_n7_0;
  sb_y7_1 = temp_var_16_1 ^ sb_n7_1;
  sb_y7_2 = temp_var_16_2 ^ sb_n7_2;
  sb_y7_3 = temp_var_16_3 ^ sb_n7_3;
  sb_y7_4 = temp_var_16_4 ^ sb_n7_4;
  _Bool i256_tx0_G256_inv0_0;
  _Bool i256_tx0_G256_inv0_1;
  _Bool i256_tx0_G256_inv0_2;
  _Bool i256_tx0_G256_inv0_3;
  _Bool i256_tx0_G256_inv0_4;
  _Bool i256_tx1_G256_inv0_0;
  _Bool i256_tx1_G256_inv0_1;
  _Bool i256_tx1_G256_inv0_2;
  _Bool i256_tx1_G256_inv0_3;
  _Bool i256_tx1_G256_inv0_4;
  _Bool i256_tx2_G256_inv0_0;
  _Bool i256_tx2_G256_inv0_1;
  _Bool i256_tx2_G256_inv0_2;
  _Bool i256_tx2_G256_inv0_3;
  _Bool i256_tx2_G256_inv0_4;
  _Bool i256_tx3_G256_inv0_0;
  _Bool i256_tx3_G256_inv0_1;
  _Bool i256_tx3_G256_inv0_2;
  _Bool i256_tx3_G256_inv0_3;
  _Bool i256_tx3_G256_inv0_4;
  _Bool i256_c0_G256_inv0_0;
  _Bool i256_c0_G256_inv0_1;
  _Bool i256_c0_G256_inv0_2;
  _Bool i256_c0_G256_inv0_3;
  _Bool i256_c0_G256_inv0_4;
  _Bool i256_c1_G256_inv0_0;
  _Bool i256_c1_G256_inv0_1;
  _Bool i256_c1_G256_inv0_2;
  _Bool i256_c1_G256_inv0_3;
  _Bool i256_c1_G256_inv0_4;
  _Bool i256_c2_G256_inv0_0;
  _Bool i256_c2_G256_inv0_1;
  _Bool i256_c2_G256_inv0_2;
  _Bool i256_c2_G256_inv0_3;
  _Bool i256_c2_G256_inv0_4;
  _Bool i256_c3_G256_inv0_0;
  _Bool i256_c3_G256_inv0_1;
  _Bool i256_c3_G256_inv0_2;
  _Bool i256_c3_G256_inv0_3;
  _Bool i256_c3_G256_inv0_4;
  _Bool i256_d0_G256_inv0_0;
  _Bool i256_d0_G256_inv0_1;
  _Bool i256_d0_G256_inv0_2;
  _Bool i256_d0_G256_inv0_3;
  _Bool i256_d0_G256_inv0_4;
  _Bool i256_d1_G256_inv0_0;
  _Bool i256_d1_G256_inv0_1;
  _Bool i256_d1_G256_inv0_2;
  _Bool i256_d1_G256_inv0_3;
  _Bool i256_d1_G256_inv0_4;
  _Bool i256_d2_G256_inv0_0;
  _Bool i256_d2_G256_inv0_1;
  _Bool i256_d2_G256_inv0_2;
  _Bool i256_d2_G256_inv0_3;
  _Bool i256_d2_G256_inv0_4;
  _Bool i256_d3_G256_inv0_0;
  _Bool i256_d3_G256_inv0_1;
  _Bool i256_d3_G256_inv0_2;
  _Bool i256_d3_G256_inv0_3;
  _Bool i256_d3_G256_inv0_4;
  _Bool i256_te0_G256_inv0_0;
  _Bool i256_te0_G256_inv0_1;
  _Bool i256_te0_G256_inv0_2;
  _Bool i256_te0_G256_inv0_3;
  _Bool i256_te0_G256_inv0_4;
  _Bool i256_te1_G256_inv0_0;
  _Bool i256_te1_G256_inv0_1;
  _Bool i256_te1_G256_inv0_2;
  _Bool i256_te1_G256_inv0_3;
  _Bool i256_te1_G256_inv0_4;
  _Bool i256_te2_G256_inv0_0;
  _Bool i256_te2_G256_inv0_1;
  _Bool i256_te2_G256_inv0_2;
  _Bool i256_te2_G256_inv0_3;
  _Bool i256_te2_G256_inv0_4;
  _Bool i256_te3_G256_inv0_0;
  _Bool i256_te3_G256_inv0_1;
  _Bool i256_te3_G256_inv0_2;
  _Bool i256_te3_G256_inv0_3;
  _Bool i256_te3_G256_inv0_4;
  _Bool i256_e0_G256_inv0_0;
  _Bool i256_e0_G256_inv0_1;
  _Bool i256_e0_G256_inv0_2;
  _Bool i256_e0_G256_inv0_3;
  _Bool i256_e0_G256_inv0_4;
  _Bool i256_e1_G256_inv0_0;
  _Bool i256_e1_G256_inv0_1;
  _Bool i256_e1_G256_inv0_2;
  _Bool i256_e1_G256_inv0_3;
  _Bool i256_e1_G256_inv0_4;
  _Bool i256_e2_G256_inv0_0;
  _Bool i256_e2_G256_inv0_1;
  _Bool i256_e2_G256_inv0_2;
  _Bool i256_e2_G256_inv0_3;
  _Bool i256_e2_G256_inv0_4;
  _Bool i256_e3_G256_inv0_0;
  _Bool i256_e3_G256_inv0_1;
  _Bool i256_e3_G256_inv0_2;
  _Bool i256_e3_G256_inv0_3;
  _Bool i256_e3_G256_inv0_4;
  _Bool i256_ph0_G256_inv0_0;
  _Bool i256_ph0_G256_inv0_1;
  _Bool i256_ph0_G256_inv0_2;
  _Bool i256_ph0_G256_inv0_3;
  _Bool i256_ph0_G256_inv0_4;
  _Bool i256_ph1_G256_inv0_0;
  _Bool i256_ph1_G256_inv0_1;
  _Bool i256_ph1_G256_inv0_2;
  _Bool i256_ph1_G256_inv0_3;
  _Bool i256_ph1_G256_inv0_4;
  _Bool i256_ph2_G256_inv0_0;
  _Bool i256_ph2_G256_inv0_1;
  _Bool i256_ph2_G256_inv0_2;
  _Bool i256_ph2_G256_inv0_3;
  _Bool i256_ph2_G256_inv0_4;
  _Bool i256_ph3_G256_inv0_0;
  _Bool i256_ph3_G256_inv0_1;
  _Bool i256_ph3_G256_inv0_2;
  _Bool i256_ph3_G256_inv0_3;
  _Bool i256_ph3_G256_inv0_4;
  _Bool i256_ql0_G256_inv0_0;
  _Bool i256_ql0_G256_inv0_1;
  _Bool i256_ql0_G256_inv0_2;
  _Bool i256_ql0_G256_inv0_3;
  _Bool i256_ql0_G256_inv0_4;
  _Bool i256_ql1_G256_inv0_0;
  _Bool i256_ql1_G256_inv0_1;
  _Bool i256_ql1_G256_inv0_2;
  _Bool i256_ql1_G256_inv0_3;
  _Bool i256_ql1_G256_inv0_4;
  _Bool i256_ql2_G256_inv0_0;
  _Bool i256_ql2_G256_inv0_1;
  _Bool i256_ql2_G256_inv0_2;
  _Bool i256_ql2_G256_inv0_3;
  _Bool i256_ql2_G256_inv0_4;
  _Bool i256_ql3_G256_inv0_0;
  _Bool i256_ql3_G256_inv0_1;
  _Bool i256_ql3_G256_inv0_2;
  _Bool i256_ql3_G256_inv0_3;
  _Bool i256_ql3_G256_inv0_4;
  _Bool ss16_tx0_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_tx0_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_tx0_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_tx0_G16_sq_scl0_G256_inv0_3;
  _Bool ss16_tx0_G16_sq_scl0_G256_inv0_4;
  _Bool ss16_tx1_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_tx1_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_tx1_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_tx1_G16_sq_scl0_G256_inv0_3;
  _Bool ss16_tx1_G16_sq_scl0_G256_inv0_4;
  _Bool ss16_ph0_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_ph0_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_ph0_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_ph0_G16_sq_scl0_G256_inv0_3;
  _Bool ss16_ph0_G16_sq_scl0_G256_inv0_4;
  _Bool ss16_ph1_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_ph1_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_ph1_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_ph1_G16_sq_scl0_G256_inv0_3;
  _Bool ss16_ph1_G16_sq_scl0_G256_inv0_4;
  _Bool ss16_ql0_s1_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_ql0_s1_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_ql0_s1_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_ql0_s1_G16_sq_scl0_G256_inv0_3;
  _Bool ss16_ql0_s1_G16_sq_scl0_G256_inv0_4;
  _Bool ss16_ql1_s1_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_ql1_s1_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_ql1_s1_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_ql1_s1_G16_sq_scl0_G256_inv0_3;
  _Bool ss16_ql1_s1_G16_sq_scl0_G256_inv0_4;
  _Bool ss16_ql0_s2_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_ql0_s2_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_ql0_s2_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_ql0_s2_G16_sq_scl0_G256_inv0_3;
  _Bool ss16_ql0_s2_G16_sq_scl0_G256_inv0_4;
  _Bool ss16_ql1_s2_G16_sq_scl0_G256_inv0_0;
  _Bool ss16_ql1_s2_G16_sq_scl0_G256_inv0_1;
  _Bool ss16_ql1_s2_G16_sq_scl0_G256_inv0_2;
  _Bool ss16_ql1_s2_G16_sq_scl0_G256_inv0_3;
  _Bool ss16_ql1_s2_G16_sq_scl0_G256_inv0_4;
  _Bool m16_tx0_G16_mul0_G256_inv0_0;
  _Bool m16_tx0_G16_mul0_G256_inv0_1;
  _Bool m16_tx0_G16_mul0_G256_inv0_2;
  _Bool m16_tx0_G16_mul0_G256_inv0_3;
  _Bool m16_tx0_G16_mul0_G256_inv0_4;
  _Bool m16_tx1_G16_mul0_G256_inv0_0;
  _Bool m16_tx1_G16_mul0_G256_inv0_1;
  _Bool m16_tx1_G16_mul0_G256_inv0_2;
  _Bool m16_tx1_G16_mul0_G256_inv0_3;
  _Bool m16_tx1_G16_mul0_G256_inv0_4;
  _Bool m16_ty0_G16_mul0_G256_inv0_0;
  _Bool m16_ty0_G16_mul0_G256_inv0_1;
  _Bool m16_ty0_G16_mul0_G256_inv0_2;
  _Bool m16_ty0_G16_mul0_G256_inv0_3;
  _Bool m16_ty0_G16_mul0_G256_inv0_4;
  _Bool m16_ty1_G16_mul0_G256_inv0_0;
  _Bool m16_ty1_G16_mul0_G256_inv0_1;
  _Bool m16_ty1_G16_mul0_G256_inv0_2;
  _Bool m16_ty1_G16_mul0_G256_inv0_3;
  _Bool m16_ty1_G16_mul0_G256_inv0_4;
  _Bool m16_e0_s1_G16_mul0_G256_inv0_0;
  _Bool m16_e0_s1_G16_mul0_G256_inv0_1;
  _Bool m16_e0_s1_G16_mul0_G256_inv0_2;
  _Bool m16_e0_s1_G16_mul0_G256_inv0_3;
  _Bool m16_e0_s1_G16_mul0_G256_inv0_4;
  _Bool m16_e1_s1_G16_mul0_G256_inv0_0;
  _Bool m16_e1_s1_G16_mul0_G256_inv0_1;
  _Bool m16_e1_s1_G16_mul0_G256_inv0_2;
  _Bool m16_e1_s1_G16_mul0_G256_inv0_3;
  _Bool m16_e1_s1_G16_mul0_G256_inv0_4;
  _Bool m16_e0_s2_G16_mul0_G256_inv0_0;
  _Bool m16_e0_s2_G16_mul0_G256_inv0_1;
  _Bool m16_e0_s2_G16_mul0_G256_inv0_2;
  _Bool m16_e0_s2_G16_mul0_G256_inv0_3;
  _Bool m16_e0_s2_G16_mul0_G256_inv0_4;
  _Bool m16_e1_s2_G16_mul0_G256_inv0_0;
  _Bool m16_e1_s2_G16_mul0_G256_inv0_1;
  _Bool m16_e1_s2_G16_mul0_G256_inv0_2;
  _Bool m16_e1_s2_G16_mul0_G256_inv0_3;
  _Bool m16_e1_s2_G16_mul0_G256_inv0_4;
  _Bool m16_ph0_G16_mul0_G256_inv0_0;
  _Bool m16_ph0_G16_mul0_G256_inv0_1;
  _Bool m16_ph0_G16_mul0_G256_inv0_2;
  _Bool m16_ph0_G16_mul0_G256_inv0_3;
  _Bool m16_ph0_G16_mul0_G256_inv0_4;
  _Bool m16_ph1_G16_mul0_G256_inv0_0;
  _Bool m16_ph1_G16_mul0_G256_inv0_1;
  _Bool m16_ph1_G16_mul0_G256_inv0_2;
  _Bool m16_ph1_G16_mul0_G256_inv0_3;
  _Bool m16_ph1_G16_mul0_G256_inv0_4;
  _Bool m16_ql0_G16_mul0_G256_inv0_0;
  _Bool m16_ql0_G16_mul0_G256_inv0_1;
  _Bool m16_ql0_G16_mul0_G256_inv0_2;
  _Bool m16_ql0_G16_mul0_G256_inv0_3;
  _Bool m16_ql0_G16_mul0_G256_inv0_4;
  _Bool m16_ql1_G16_mul0_G256_inv0_0;
  _Bool m16_ql1_G16_mul0_G256_inv0_1;
  _Bool m16_ql1_G16_mul0_G256_inv0_2;
  _Bool m16_ql1_G16_mul0_G256_inv0_3;
  _Bool m16_ql1_G16_mul0_G256_inv0_4;
  _Bool m4_ab_G4_mul0_G16_mul0_G256_inv0_0;
  _Bool m4_ab_G4_mul0_G16_mul0_G256_inv0_1;
  _Bool m4_ab_G4_mul0_G16_mul0_G256_inv0_2;
  _Bool m4_ab_G4_mul0_G16_mul0_G256_inv0_3;
  _Bool m4_ab_G4_mul0_G16_mul0_G256_inv0_4;
  _Bool m4_cd_G4_mul0_G16_mul0_G256_inv0_0;
  _Bool m4_cd_G4_mul0_G16_mul0_G256_inv0_1;
  _Bool m4_cd_G4_mul0_G16_mul0_G256_inv0_2;
  _Bool m4_cd_G4_mul0_G16_mul0_G256_inv0_3;
  _Bool m4_cd_G4_mul0_G16_mul0_G256_inv0_4;
  _Bool m4_e_G4_mul0_G16_mul0_G256_inv0_0;
  _Bool m4_e_G4_mul0_G16_mul0_G256_inv0_1;
  _Bool m4_e_G4_mul0_G16_mul0_G256_inv0_2;
  _Bool m4_e_G4_mul0_G16_mul0_G256_inv0_3;
  _Bool m4_e_G4_mul0_G16_mul0_G256_inv0_4;
  _Bool temp_var_0_G4_mul0_G16_mul0_G256_inv0_0;
  _Bool temp_var_0_G4_mul0_G16_mul0_G256_inv0_1;
  _Bool temp_var_0_G4_mul0_G16_mul0_G256_inv0_2;
  _Bool temp_var_0_G4_mul0_G16_mul0_G256_inv0_3;
  _Bool temp_var_0_G4_mul0_G16_mul0_G256_inv0_4;
  _Bool temp_var_1_G4_mul0_G16_mul0_G256_inv0_0;
  _Bool temp_var_1_G4_mul0_G16_mul0_G256_inv0_1;
  _Bool temp_var_1_G4_mul0_G16_mul0_G256_inv0_2;
  _Bool temp_var_1_G4_mul0_G16_mul0_G256_inv0_3;
  _Bool temp_var_1_G4_mul0_G16_mul0_G256_inv0_4;
  _Bool m4_ab_G4_mul1_G16_mul0_G256_inv0_0;
  _Bool m4_ab_G4_mul1_G16_mul0_G256_inv0_1;
  _Bool m4_ab_G4_mul1_G16_mul0_G256_inv0_2;
  _Bool m4_ab_G4_mul1_G16_mul0_G256_inv0_3;
  _Bool m4_ab_G4_mul1_G16_mul0_G256_inv0_4;
  _Bool m4_cd_G4_mul1_G16_mul0_G256_inv0_0;
  _Bool m4_cd_G4_mul1_G16_mul0_G256_inv0_1;
  _Bool m4_cd_G4_mul1_G16_mul0_G256_inv0_2;
  _Bool m4_cd_G4_mul1_G16_mul0_G256_inv0_3;
  _Bool m4_cd_G4_mul1_G16_mul0_G256_inv0_4;
  _Bool m4_e_G4_mul1_G16_mul0_G256_inv0_0;
  _Bool m4_e_G4_mul1_G16_mul0_G256_inv0_1;
  _Bool m4_e_G4_mul1_G16_mul0_G256_inv0_2;
  _Bool m4_e_G4_mul1_G16_mul0_G256_inv0_3;
  _Bool m4_e_G4_mul1_G16_mul0_G256_inv0_4;
  _Bool temp_var_0_G4_mul1_G16_mul0_G256_inv0_0;
  _Bool temp_var_0_G4_mul1_G16_mul0_G256_inv0_1;
  _Bool temp_var_0_G4_mul1_G16_mul0_G256_inv0_2;
  _Bool temp_var_0_G4_mul1_G16_mul0_G256_inv0_3;
  _Bool temp_var_0_G4_mul1_G16_mul0_G256_inv0_4;
  _Bool temp_var_1_G4_mul1_G16_mul0_G256_inv0_0;
  _Bool temp_var_1_G4_mul1_G16_mul0_G256_inv0_1;
  _Bool temp_var_1_G4_mul1_G16_mul0_G256_inv0_2;
  _Bool temp_var_1_G4_mul1_G16_mul0_G256_inv0_3;
  _Bool temp_var_1_G4_mul1_G16_mul0_G256_inv0_4;
  _Bool m4_ab_G4_mul2_G16_mul0_G256_inv0_0;
  _Bool m4_ab_G4_mul2_G16_mul0_G256_inv0_1;
  _Bool m4_ab_G4_mul2_G16_mul0_G256_inv0_2;
  _Bool m4_ab_G4_mul2_G16_mul0_G256_inv0_3;
  _Bool m4_ab_G4_mul2_G16_mul0_G256_inv0_4;
  _Bool m4_cd_G4_mul2_G16_mul0_G256_inv0_0;
  _Bool m4_cd_G4_mul2_G16_mul0_G256_inv0_1;
  _Bool m4_cd_G4_mul2_G16_mul0_G256_inv0_2;
  _Bool m4_cd_G4_mul2_G16_mul0_G256_inv0_3;
  _Bool m4_cd_G4_mul2_G16_mul0_G256_inv0_4;
  _Bool m4_e_G4_mul2_G16_mul0_G256_inv0_0;
  _Bool m4_e_G4_mul2_G16_mul0_G256_inv0_1;
  _Bool m4_e_G4_mul2_G16_mul0_G256_inv0_2;
  _Bool m4_e_G4_mul2_G16_mul0_G256_inv0_3;
  _Bool m4_e_G4_mul2_G16_mul0_G256_inv0_4;
  _Bool temp_var_0_G4_mul2_G16_mul0_G256_inv0_0;
  _Bool temp_var_0_G4_mul2_G16_mul0_G256_inv0_1;
  _Bool temp_var_0_G4_mul2_G16_mul0_G256_inv0_2;
  _Bool temp_var_0_G4_mul2_G16_mul0_G256_inv0_3;
  _Bool temp_var_0_G4_mul2_G16_mul0_G256_inv0_4;
  _Bool temp_var_1_G4_mul2_G16_mul0_G256_inv0_0;
  _Bool temp_var_1_G4_mul2_G16_mul0_G256_inv0_1;
  _Bool temp_var_1_G4_mul2_G16_mul0_G256_inv0_2;
  _Bool temp_var_1_G4_mul2_G16_mul0_G256_inv0_3;
  _Bool temp_var_1_G4_mul2_G16_mul0_G256_inv0_4;
  _Bool i16_tx0_G16_inv0_G256_inv0_0;
  _Bool i16_tx0_G16_inv0_G256_inv0_1;
  _Bool i16_tx0_G16_inv0_G256_inv0_2;
  _Bool i16_tx0_G16_inv0_G256_inv0_3;
  _Bool i16_tx0_G16_inv0_G256_inv0_4;
  _Bool i16_tx1_G16_inv0_G256_inv0_0;
  _Bool i16_tx1_G16_inv0_G256_inv0_1;
  _Bool i16_tx1_G16_inv0_G256_inv0_2;
  _Bool i16_tx1_G16_inv0_G256_inv0_3;
  _Bool i16_tx1_G16_inv0_G256_inv0_4;
  _Bool i16_c0_s1_G16_inv0_G256_inv0_0;
  _Bool i16_c0_s1_G16_inv0_G256_inv0_1;
  _Bool i16_c0_s1_G16_inv0_G256_inv0_2;
  _Bool i16_c0_s1_G16_inv0_G256_inv0_3;
  _Bool i16_c0_s1_G16_inv0_G256_inv0_4;
  _Bool i16_c1_s1_G16_inv0_G256_inv0_0;
  _Bool i16_c1_s1_G16_inv0_G256_inv0_1;
  _Bool i16_c1_s1_G16_inv0_G256_inv0_2;
  _Bool i16_c1_s1_G16_inv0_G256_inv0_3;
  _Bool i16_c1_s1_G16_inv0_G256_inv0_4;
  _Bool i16_c0_s2_G16_inv0_G256_inv0_0;
  _Bool i16_c0_s2_G16_inv0_G256_inv0_1;
  _Bool i16_c0_s2_G16_inv0_G256_inv0_2;
  _Bool i16_c0_s2_G16_inv0_G256_inv0_3;
  _Bool i16_c0_s2_G16_inv0_G256_inv0_4;
  _Bool i16_c1_s2_G16_inv0_G256_inv0_0;
  _Bool i16_c1_s2_G16_inv0_G256_inv0_1;
  _Bool i16_c1_s2_G16_inv0_G256_inv0_2;
  _Bool i16_c1_s2_G16_inv0_G256_inv0_3;
  _Bool i16_c1_s2_G16_inv0_G256_inv0_4;
  _Bool i16_d0_G16_inv0_G256_inv0_0;
  _Bool i16_d0_G16_inv0_G256_inv0_1;
  _Bool i16_d0_G16_inv0_G256_inv0_2;
  _Bool i16_d0_G16_inv0_G256_inv0_3;
  _Bool i16_d0_G16_inv0_G256_inv0_4;
  _Bool i16_d1_G16_inv0_G256_inv0_0;
  _Bool i16_d1_G16_inv0_G256_inv0_1;
  _Bool i16_d1_G16_inv0_G256_inv0_2;
  _Bool i16_d1_G16_inv0_G256_inv0_3;
  _Bool i16_d1_G16_inv0_G256_inv0_4;
  _Bool i16_te0_G16_inv0_G256_inv0_0;
  _Bool i16_te0_G16_inv0_G256_inv0_1;
  _Bool i16_te0_G16_inv0_G256_inv0_2;
  _Bool i16_te0_G16_inv0_G256_inv0_3;
  _Bool i16_te0_G16_inv0_G256_inv0_4;
  _Bool i16_te1_G16_inv0_G256_inv0_0;
  _Bool i16_te1_G16_inv0_G256_inv0_1;
  _Bool i16_te1_G16_inv0_G256_inv0_2;
  _Bool i16_te1_G16_inv0_G256_inv0_3;
  _Bool i16_te1_G16_inv0_G256_inv0_4;
  _Bool i16_e0_G16_inv0_G256_inv0_0;
  _Bool i16_e0_G16_inv0_G256_inv0_1;
  _Bool i16_e0_G16_inv0_G256_inv0_2;
  _Bool i16_e0_G16_inv0_G256_inv0_3;
  _Bool i16_e0_G16_inv0_G256_inv0_4;
  _Bool i16_e1_G16_inv0_G256_inv0_0;
  _Bool i16_e1_G16_inv0_G256_inv0_1;
  _Bool i16_e1_G16_inv0_G256_inv0_2;
  _Bool i16_e1_G16_inv0_G256_inv0_3;
  _Bool i16_e1_G16_inv0_G256_inv0_4;
  _Bool i16_ph0_G16_inv0_G256_inv0_0;
  _Bool i16_ph0_G16_inv0_G256_inv0_1;
  _Bool i16_ph0_G16_inv0_G256_inv0_2;
  _Bool i16_ph0_G16_inv0_G256_inv0_3;
  _Bool i16_ph0_G16_inv0_G256_inv0_4;
  _Bool i16_ph1_G16_inv0_G256_inv0_0;
  _Bool i16_ph1_G16_inv0_G256_inv0_1;
  _Bool i16_ph1_G16_inv0_G256_inv0_2;
  _Bool i16_ph1_G16_inv0_G256_inv0_3;
  _Bool i16_ph1_G16_inv0_G256_inv0_4;
  _Bool i16_ql0_G16_inv0_G256_inv0_0;
  _Bool i16_ql0_G16_inv0_G256_inv0_1;
  _Bool i16_ql0_G16_inv0_G256_inv0_2;
  _Bool i16_ql0_G16_inv0_G256_inv0_3;
  _Bool i16_ql0_G16_inv0_G256_inv0_4;
  _Bool i16_ql1_G16_inv0_G256_inv0_0;
  _Bool i16_ql1_G16_inv0_G256_inv0_1;
  _Bool i16_ql1_G16_inv0_G256_inv0_2;
  _Bool i16_ql1_G16_inv0_G256_inv0_3;
  _Bool i16_ql1_G16_inv0_G256_inv0_4;
  _Bool m4_ab_G4_mul3_G16_inv0_G256_inv0_0;
  _Bool m4_ab_G4_mul3_G16_inv0_G256_inv0_1;
  _Bool m4_ab_G4_mul3_G16_inv0_G256_inv0_2;
  _Bool m4_ab_G4_mul3_G16_inv0_G256_inv0_3;
  _Bool m4_ab_G4_mul3_G16_inv0_G256_inv0_4;
  _Bool m4_cd_G4_mul3_G16_inv0_G256_inv0_0;
  _Bool m4_cd_G4_mul3_G16_inv0_G256_inv0_1;
  _Bool m4_cd_G4_mul3_G16_inv0_G256_inv0_2;
  _Bool m4_cd_G4_mul3_G16_inv0_G256_inv0_3;
  _Bool m4_cd_G4_mul3_G16_inv0_G256_inv0_4;
  _Bool m4_e_G4_mul3_G16_inv0_G256_inv0_0;
  _Bool m4_e_G4_mul3_G16_inv0_G256_inv0_1;
  _Bool m4_e_G4_mul3_G16_inv0_G256_inv0_2;
  _Bool m4_e_G4_mul3_G16_inv0_G256_inv0_3;
  _Bool m4_e_G4_mul3_G16_inv0_G256_inv0_4;
  _Bool temp_var_0_G4_mul3_G16_inv0_G256_inv0_0;
  _Bool temp_var_0_G4_mul3_G16_inv0_G256_inv0_1;
  _Bool temp_var_0_G4_mul3_G16_inv0_G256_inv0_2;
  _Bool temp_var_0_G4_mul3_G16_inv0_G256_inv0_3;
  _Bool temp_var_0_G4_mul3_G16_inv0_G256_inv0_4;
  _Bool temp_var_1_G4_mul3_G16_inv0_G256_inv0_0;
  _Bool temp_var_1_G4_mul3_G16_inv0_G256_inv0_1;
  _Bool temp_var_1_G4_mul3_G16_inv0_G256_inv0_2;
  _Bool temp_var_1_G4_mul3_G16_inv0_G256_inv0_3;
  _Bool temp_var_1_G4_mul3_G16_inv0_G256_inv0_4;
  _Bool m4_ab_G4_mul4_G16_inv0_G256_inv0_0;
  _Bool m4_ab_G4_mul4_G16_inv0_G256_inv0_1;
  _Bool m4_ab_G4_mul4_G16_inv0_G256_inv0_2;
  _Bool m4_ab_G4_mul4_G16_inv0_G256_inv0_3;
  _Bool m4_ab_G4_mul4_G16_inv0_G256_inv0_4;
  _Bool m4_cd_G4_mul4_G16_inv0_G256_inv0_0;
  _Bool m4_cd_G4_mul4_G16_inv0_G256_inv0_1;
  _Bool m4_cd_G4_mul4_G16_inv0_G256_inv0_2;
  _Bool m4_cd_G4_mul4_G16_inv0_G256_inv0_3;
  _Bool m4_cd_G4_mul4_G16_inv0_G256_inv0_4;
  _Bool m4_e_G4_mul4_G16_inv0_G256_inv0_0;
  _Bool m4_e_G4_mul4_G16_inv0_G256_inv0_1;
  _Bool m4_e_G4_mul4_G16_inv0_G256_inv0_2;
  _Bool m4_e_G4_mul4_G16_inv0_G256_inv0_3;
  _Bool m4_e_G4_mul4_G16_inv0_G256_inv0_4;
  _Bool temp_var_0_G4_mul4_G16_inv0_G256_inv0_0;
  _Bool temp_var_0_G4_mul4_G16_inv0_G256_inv0_1;
  _Bool temp_var_0_G4_mul4_G16_inv0_G256_inv0_2;
  _Bool temp_var_0_G4_mul4_G16_inv0_G256_inv0_3;
  _Bool temp_var_0_G4_mul4_G16_inv0_G256_inv0_4;
  _Bool temp_var_1_G4_mul4_G16_inv0_G256_inv0_0;
  _Bool temp_var_1_G4_mul4_G16_inv0_G256_inv0_1;
  _Bool temp_var_1_G4_mul4_G16_inv0_G256_inv0_2;
  _Bool temp_var_1_G4_mul4_G16_inv0_G256_inv0_3;
  _Bool temp_var_1_G4_mul4_G16_inv0_G256_inv0_4;
  _Bool m4_ab_G4_mul5_G16_inv0_G256_inv0_0;
  _Bool m4_ab_G4_mul5_G16_inv0_G256_inv0_1;
  _Bool m4_ab_G4_mul5_G16_inv0_G256_inv0_2;
  _Bool m4_ab_G4_mul5_G16_inv0_G256_inv0_3;
  _Bool m4_ab_G4_mul5_G16_inv0_G256_inv0_4;
  _Bool m4_cd_G4_mul5_G16_inv0_G256_inv0_0;
  _Bool m4_cd_G4_mul5_G16_inv0_G256_inv0_1;
  _Bool m4_cd_G4_mul5_G16_inv0_G256_inv0_2;
  _Bool m4_cd_G4_mul5_G16_inv0_G256_inv0_3;
  _Bool m4_cd_G4_mul5_G16_inv0_G256_inv0_4;
  _Bool m4_e_G4_mul5_G16_inv0_G256_inv0_0;
  _Bool m4_e_G4_mul5_G16_inv0_G256_inv0_1;
  _Bool m4_e_G4_mul5_G16_inv0_G256_inv0_2;
  _Bool m4_e_G4_mul5_G16_inv0_G256_inv0_3;
  _Bool m4_e_G4_mul5_G16_inv0_G256_inv0_4;
  _Bool temp_var_0_G4_mul5_G16_inv0_G256_inv0_0;
  _Bool temp_var_0_G4_mul5_G16_inv0_G256_inv0_1;
  _Bool temp_var_0_G4_mul5_G16_inv0_G256_inv0_2;
  _Bool temp_var_0_G4_mul5_G16_inv0_G256_inv0_3;
  _Bool temp_var_0_G4_mul5_G16_inv0_G256_inv0_4;
  _Bool temp_var_1_G4_mul5_G16_inv0_G256_inv0_0;
  _Bool temp_var_1_G4_mul5_G16_inv0_G256_inv0_1;
  _Bool temp_var_1_G4_mul5_G16_inv0_G256_inv0_2;
  _Bool temp_var_1_G4_mul5_G16_inv0_G256_inv0_3;
  _Bool temp_var_1_G4_mul5_G16_inv0_G256_inv0_4;
  _Bool m16_tx0_G16_mul1_G256_inv0_0;
  _Bool m16_tx0_G16_mul1_G256_inv0_1;
  _Bool m16_tx0_G16_mul1_G256_inv0_2;
  _Bool m16_tx0_G16_mul1_G256_inv0_3;
  _Bool m16_tx0_G16_mul1_G256_inv0_4;
  _Bool m16_tx1_G16_mul1_G256_inv0_0;
  _Bool m16_tx1_G16_mul1_G256_inv0_1;
  _Bool m16_tx1_G16_mul1_G256_inv0_2;
  _Bool m16_tx1_G16_mul1_G256_inv0_3;
  _Bool m16_tx1_G16_mul1_G256_inv0_4;
  _Bool m16_ty0_G16_mul1_G256_inv0_0;
  _Bool m16_ty0_G16_mul1_G256_inv0_1;
  _Bool m16_ty0_G16_mul1_G256_inv0_2;
  _Bool m16_ty0_G16_mul1_G256_inv0_3;
  _Bool m16_ty0_G16_mul1_G256_inv0_4;
  _Bool m16_ty1_G16_mul1_G256_inv0_0;
  _Bool m16_ty1_G16_mul1_G256_inv0_1;
  _Bool m16_ty1_G16_mul1_G256_inv0_2;
  _Bool m16_ty1_G16_mul1_G256_inv0_3;
  _Bool m16_ty1_G16_mul1_G256_inv0_4;
  _Bool m16_e0_s1_G16_mul1_G256_inv0_0;
  _Bool m16_e0_s1_G16_mul1_G256_inv0_1;
  _Bool m16_e0_s1_G16_mul1_G256_inv0_2;
  _Bool m16_e0_s1_G16_mul1_G256_inv0_3;
  _Bool m16_e0_s1_G16_mul1_G256_inv0_4;
  _Bool m16_e1_s1_G16_mul1_G256_inv0_0;
  _Bool m16_e1_s1_G16_mul1_G256_inv0_1;
  _Bool m16_e1_s1_G16_mul1_G256_inv0_2;
  _Bool m16_e1_s1_G16_mul1_G256_inv0_3;
  _Bool m16_e1_s1_G16_mul1_G256_inv0_4;
  _Bool m16_e0_s2_G16_mul1_G256_inv0_0;
  _Bool m16_e0_s2_G16_mul1_G256_inv0_1;
  _Bool m16_e0_s2_G16_mul1_G256_inv0_2;
  _Bool m16_e0_s2_G16_mul1_G256_inv0_3;
  _Bool m16_e0_s2_G16_mul1_G256_inv0_4;
  _Bool m16_e1_s2_G16_mul1_G256_inv0_0;
  _Bool m16_e1_s2_G16_mul1_G256_inv0_1;
  _Bool m16_e1_s2_G16_mul1_G256_inv0_2;
  _Bool m16_e1_s2_G16_mul1_G256_inv0_3;
  _Bool m16_e1_s2_G16_mul1_G256_inv0_4;
  _Bool m16_ph0_G16_mul1_G256_inv0_0;
  _Bool m16_ph0_G16_mul1_G256_inv0_1;
  _Bool m16_ph0_G16_mul1_G256_inv0_2;
  _Bool m16_ph0_G16_mul1_G256_inv0_3;
  _Bool m16_ph0_G16_mul1_G256_inv0_4;
  _Bool m16_ph1_G16_mul1_G256_inv0_0;
  _Bool m16_ph1_G16_mul1_G256_inv0_1;
  _Bool m16_ph1_G16_mul1_G256_inv0_2;
  _Bool m16_ph1_G16_mul1_G256_inv0_3;
  _Bool m16_ph1_G16_mul1_G256_inv0_4;
  _Bool m16_ql0_G16_mul1_G256_inv0_0;
  _Bool m16_ql0_G16_mul1_G256_inv0_1;
  _Bool m16_ql0_G16_mul1_G256_inv0_2;
  _Bool m16_ql0_G16_mul1_G256_inv0_3;
  _Bool m16_ql0_G16_mul1_G256_inv0_4;
  _Bool m16_ql1_G16_mul1_G256_inv0_0;
  _Bool m16_ql1_G16_mul1_G256_inv0_1;
  _Bool m16_ql1_G16_mul1_G256_inv0_2;
  _Bool m16_ql1_G16_mul1_G256_inv0_3;
  _Bool m16_ql1_G16_mul1_G256_inv0_4;
  _Bool m4_ab_G4_mul0_G16_mul1_G256_inv0_0;
  _Bool m4_ab_G4_mul0_G16_mul1_G256_inv0_1;
  _Bool m4_ab_G4_mul0_G16_mul1_G256_inv0_2;
  _Bool m4_ab_G4_mul0_G16_mul1_G256_inv0_3;
  _Bool m4_ab_G4_mul0_G16_mul1_G256_inv0_4;
  _Bool m4_cd_G4_mul0_G16_mul1_G256_inv0_0;
  _Bool m4_cd_G4_mul0_G16_mul1_G256_inv0_1;
  _Bool m4_cd_G4_mul0_G16_mul1_G256_inv0_2;
  _Bool m4_cd_G4_mul0_G16_mul1_G256_inv0_3;
  _Bool m4_cd_G4_mul0_G16_mul1_G256_inv0_4;
  _Bool m4_e_G4_mul0_G16_mul1_G256_inv0_0;
  _Bool m4_e_G4_mul0_G16_mul1_G256_inv0_1;
  _Bool m4_e_G4_mul0_G16_mul1_G256_inv0_2;
  _Bool m4_e_G4_mul0_G16_mul1_G256_inv0_3;
  _Bool m4_e_G4_mul0_G16_mul1_G256_inv0_4;
  _Bool temp_var_0_G4_mul0_G16_mul1_G256_inv0_0;
  _Bool temp_var_0_G4_mul0_G16_mul1_G256_inv0_1;
  _Bool temp_var_0_G4_mul0_G16_mul1_G256_inv0_2;
  _Bool temp_var_0_G4_mul0_G16_mul1_G256_inv0_3;
  _Bool temp_var_0_G4_mul0_G16_mul1_G256_inv0_4;
  _Bool temp_var_1_G4_mul0_G16_mul1_G256_inv0_0;
  _Bool temp_var_1_G4_mul0_G16_mul1_G256_inv0_1;
  _Bool temp_var_1_G4_mul0_G16_mul1_G256_inv0_2;
  _Bool temp_var_1_G4_mul0_G16_mul1_G256_inv0_3;
  _Bool temp_var_1_G4_mul0_G16_mul1_G256_inv0_4;
  _Bool m4_ab_G4_mul1_G16_mul1_G256_inv0_0;
  _Bool m4_ab_G4_mul1_G16_mul1_G256_inv0_1;
  _Bool m4_ab_G4_mul1_G16_mul1_G256_inv0_2;
  _Bool m4_ab_G4_mul1_G16_mul1_G256_inv0_3;
  _Bool m4_ab_G4_mul1_G16_mul1_G256_inv0_4;
  _Bool m4_cd_G4_mul1_G16_mul1_G256_inv0_0;
  _Bool m4_cd_G4_mul1_G16_mul1_G256_inv0_1;
  _Bool m4_cd_G4_mul1_G16_mul1_G256_inv0_2;
  _Bool m4_cd_G4_mul1_G16_mul1_G256_inv0_3;
  _Bool m4_cd_G4_mul1_G16_mul1_G256_inv0_4;
  _Bool m4_e_G4_mul1_G16_mul1_G256_inv0_0;
  _Bool m4_e_G4_mul1_G16_mul1_G256_inv0_1;
  _Bool m4_e_G4_mul1_G16_mul1_G256_inv0_2;
  _Bool m4_e_G4_mul1_G16_mul1_G256_inv0_3;
  _Bool m4_e_G4_mul1_G16_mul1_G256_inv0_4;
  _Bool temp_var_0_G4_mul1_G16_mul1_G256_inv0_0;
  _Bool temp_var_0_G4_mul1_G16_mul1_G256_inv0_1;
  _Bool temp_var_0_G4_mul1_G16_mul1_G256_inv0_2;
  _Bool temp_var_0_G4_mul1_G16_mul1_G256_inv0_3;
  _Bool temp_var_0_G4_mul1_G16_mul1_G256_inv0_4;
  _Bool temp_var_1_G4_mul1_G16_mul1_G256_inv0_0;
  _Bool temp_var_1_G4_mul1_G16_mul1_G256_inv0_1;
  _Bool temp_var_1_G4_mul1_G16_mul1_G256_inv0_2;
  _Bool temp_var_1_G4_mul1_G16_mul1_G256_inv0_3;
  _Bool temp_var_1_G4_mul1_G16_mul1_G256_inv0_4;
  _Bool m4_ab_G4_mul2_G16_mul1_G256_inv0_0;
  _Bool m4_ab_G4_mul2_G16_mul1_G256_inv0_1;
  _Bool m4_ab_G4_mul2_G16_mul1_G256_inv0_2;
  _Bool m4_ab_G4_mul2_G16_mul1_G256_inv0_3;
  _Bool m4_ab_G4_mul2_G16_mul1_G256_inv0_4;
  _Bool m4_cd_G4_mul2_G16_mul1_G256_inv0_0;
  _Bool m4_cd_G4_mul2_G16_mul1_G256_inv0_1;
  _Bool m4_cd_G4_mul2_G16_mul1_G256_inv0_2;
  _Bool m4_cd_G4_mul2_G16_mul1_G256_inv0_3;
  _Bool m4_cd_G4_mul2_G16_mul1_G256_inv0_4;
  _Bool m4_e_G4_mul2_G16_mul1_G256_inv0_0;
  _Bool m4_e_G4_mul2_G16_mul1_G256_inv0_1;
  _Bool m4_e_G4_mul2_G16_mul1_G256_inv0_2;
  _Bool m4_e_G4_mul2_G16_mul1_G256_inv0_3;
  _Bool m4_e_G4_mul2_G16_mul1_G256_inv0_4;
  _Bool temp_var_0_G4_mul2_G16_mul1_G256_inv0_0;
  _Bool temp_var_0_G4_mul2_G16_mul1_G256_inv0_1;
  _Bool temp_var_0_G4_mul2_G16_mul1_G256_inv0_2;
  _Bool temp_var_0_G4_mul2_G16_mul1_G256_inv0_3;
  _Bool temp_var_0_G4_mul2_G16_mul1_G256_inv0_4;
  _Bool temp_var_1_G4_mul2_G16_mul1_G256_inv0_0;
  _Bool temp_var_1_G4_mul2_G16_mul1_G256_inv0_1;
  _Bool temp_var_1_G4_mul2_G16_mul1_G256_inv0_2;
  _Bool temp_var_1_G4_mul2_G16_mul1_G256_inv0_3;
  _Bool temp_var_1_G4_mul2_G16_mul1_G256_inv0_4;
  _Bool m16_tx0_G16_mul2_G256_inv0_0;
  _Bool m16_tx0_G16_mul2_G256_inv0_1;
  _Bool m16_tx0_G16_mul2_G256_inv0_2;
  _Bool m16_tx0_G16_mul2_G256_inv0_3;
  _Bool m16_tx0_G16_mul2_G256_inv0_4;
  _Bool m16_tx1_G16_mul2_G256_inv0_0;
  _Bool m16_tx1_G16_mul2_G256_inv0_1;
  _Bool m16_tx1_G16_mul2_G256_inv0_2;
  _Bool m16_tx1_G16_mul2_G256_inv0_3;
  _Bool m16_tx1_G16_mul2_G256_inv0_4;
  _Bool m16_ty0_G16_mul2_G256_inv0_0;
  _Bool m16_ty0_G16_mul2_G256_inv0_1;
  _Bool m16_ty0_G16_mul2_G256_inv0_2;
  _Bool m16_ty0_G16_mul2_G256_inv0_3;
  _Bool m16_ty0_G16_mul2_G256_inv0_4;
  _Bool m16_ty1_G16_mul2_G256_inv0_0;
  _Bool m16_ty1_G16_mul2_G256_inv0_1;
  _Bool m16_ty1_G16_mul2_G256_inv0_2;
  _Bool m16_ty1_G16_mul2_G256_inv0_3;
  _Bool m16_ty1_G16_mul2_G256_inv0_4;
  _Bool m16_e0_s1_G16_mul2_G256_inv0_0;
  _Bool m16_e0_s1_G16_mul2_G256_inv0_1;
  _Bool m16_e0_s1_G16_mul2_G256_inv0_2;
  _Bool m16_e0_s1_G16_mul2_G256_inv0_3;
  _Bool m16_e0_s1_G16_mul2_G256_inv0_4;
  _Bool m16_e1_s1_G16_mul2_G256_inv0_0;
  _Bool m16_e1_s1_G16_mul2_G256_inv0_1;
  _Bool m16_e1_s1_G16_mul2_G256_inv0_2;
  _Bool m16_e1_s1_G16_mul2_G256_inv0_3;
  _Bool m16_e1_s1_G16_mul2_G256_inv0_4;
  _Bool m16_e0_s2_G16_mul2_G256_inv0_0;
  _Bool m16_e0_s2_G16_mul2_G256_inv0_1;
  _Bool m16_e0_s2_G16_mul2_G256_inv0_2;
  _Bool m16_e0_s2_G16_mul2_G256_inv0_3;
  _Bool m16_e0_s2_G16_mul2_G256_inv0_4;
  _Bool m16_e1_s2_G16_mul2_G256_inv0_0;
  _Bool m16_e1_s2_G16_mul2_G256_inv0_1;
  _Bool m16_e1_s2_G16_mul2_G256_inv0_2;
  _Bool m16_e1_s2_G16_mul2_G256_inv0_3;
  _Bool m16_e1_s2_G16_mul2_G256_inv0_4;
  _Bool m16_ph0_G16_mul2_G256_inv0_0;
  _Bool m16_ph0_G16_mul2_G256_inv0_1;
  _Bool m16_ph0_G16_mul2_G256_inv0_2;
  _Bool m16_ph0_G16_mul2_G256_inv0_3;
  _Bool m16_ph0_G16_mul2_G256_inv0_4;
  _Bool m16_ph1_G16_mul2_G256_inv0_0;
  _Bool m16_ph1_G16_mul2_G256_inv0_1;
  _Bool m16_ph1_G16_mul2_G256_inv0_2;
  _Bool m16_ph1_G16_mul2_G256_inv0_3;
  _Bool m16_ph1_G16_mul2_G256_inv0_4;
  _Bool m16_ql0_G16_mul2_G256_inv0_0;
  _Bool m16_ql0_G16_mul2_G256_inv0_1;
  _Bool m16_ql0_G16_mul2_G256_inv0_2;
  _Bool m16_ql0_G16_mul2_G256_inv0_3;
  _Bool m16_ql0_G16_mul2_G256_inv0_4;
  _Bool m16_ql1_G16_mul2_G256_inv0_0;
  _Bool m16_ql1_G16_mul2_G256_inv0_1;
  _Bool m16_ql1_G16_mul2_G256_inv0_2;
  _Bool m16_ql1_G16_mul2_G256_inv0_3;
  _Bool m16_ql1_G16_mul2_G256_inv0_4;
  _Bool m4_ab_G4_mul0_G16_mul2_G256_inv0_0;
  _Bool m4_ab_G4_mul0_G16_mul2_G256_inv0_1;
  _Bool m4_ab_G4_mul0_G16_mul2_G256_inv0_2;
  _Bool m4_ab_G4_mul0_G16_mul2_G256_inv0_3;
  _Bool m4_ab_G4_mul0_G16_mul2_G256_inv0_4;
  _Bool m4_cd_G4_mul0_G16_mul2_G256_inv0_0;
  _Bool m4_cd_G4_mul0_G16_mul2_G256_inv0_1;
  _Bool m4_cd_G4_mul0_G16_mul2_G256_inv0_2;
  _Bool m4_cd_G4_mul0_G16_mul2_G256_inv0_3;
  _Bool m4_cd_G4_mul0_G16_mul2_G256_inv0_4;
  _Bool m4_e_G4_mul0_G16_mul2_G256_inv0_0;
  _Bool m4_e_G4_mul0_G16_mul2_G256_inv0_1;
  _Bool m4_e_G4_mul0_G16_mul2_G256_inv0_2;
  _Bool m4_e_G4_mul0_G16_mul2_G256_inv0_3;
  _Bool m4_e_G4_mul0_G16_mul2_G256_inv0_4;
  _Bool temp_var_0_G4_mul0_G16_mul2_G256_inv0_0;
  _Bool temp_var_0_G4_mul0_G16_mul2_G256_inv0_1;
  _Bool temp_var_0_G4_mul0_G16_mul2_G256_inv0_2;
  _Bool temp_var_0_G4_mul0_G16_mul2_G256_inv0_3;
  _Bool temp_var_0_G4_mul0_G16_mul2_G256_inv0_4;
  _Bool temp_var_1_G4_mul0_G16_mul2_G256_inv0_0;
  _Bool temp_var_1_G4_mul0_G16_mul2_G256_inv0_1;
  _Bool temp_var_1_G4_mul0_G16_mul2_G256_inv0_2;
  _Bool temp_var_1_G4_mul0_G16_mul2_G256_inv0_3;
  _Bool temp_var_1_G4_mul0_G16_mul2_G256_inv0_4;
  _Bool m4_ab_G4_mul1_G16_mul2_G256_inv0_0;
  _Bool m4_ab_G4_mul1_G16_mul2_G256_inv0_1;
  _Bool m4_ab_G4_mul1_G16_mul2_G256_inv0_2;
  _Bool m4_ab_G4_mul1_G16_mul2_G256_inv0_3;
  _Bool m4_ab_G4_mul1_G16_mul2_G256_inv0_4;
  _Bool m4_cd_G4_mul1_G16_mul2_G256_inv0_0;
  _Bool m4_cd_G4_mul1_G16_mul2_G256_inv0_1;
  _Bool m4_cd_G4_mul1_G16_mul2_G256_inv0_2;
  _Bool m4_cd_G4_mul1_G16_mul2_G256_inv0_3;
  _Bool m4_cd_G4_mul1_G16_mul2_G256_inv0_4;
  _Bool m4_e_G4_mul1_G16_mul2_G256_inv0_0;
  _Bool m4_e_G4_mul1_G16_mul2_G256_inv0_1;
  _Bool m4_e_G4_mul1_G16_mul2_G256_inv0_2;
  _Bool m4_e_G4_mul1_G16_mul2_G256_inv0_3;
  _Bool m4_e_G4_mul1_G16_mul2_G256_inv0_4;
  _Bool temp_var_0_G4_mul1_G16_mul2_G256_inv0_0;
  _Bool temp_var_0_G4_mul1_G16_mul2_G256_inv0_1;
  _Bool temp_var_0_G4_mul1_G16_mul2_G256_inv0_2;
  _Bool temp_var_0_G4_mul1_G16_mul2_G256_inv0_3;
  _Bool temp_var_0_G4_mul1_G16_mul2_G256_inv0_4;
  _Bool temp_var_1_G4_mul1_G16_mul2_G256_inv0_0;
  _Bool temp_var_1_G4_mul1_G16_mul2_G256_inv0_1;
  _Bool temp_var_1_G4_mul1_G16_mul2_G256_inv0_2;
  _Bool temp_var_1_G4_mul1_G16_mul2_G256_inv0_3;
  _Bool temp_var_1_G4_mul1_G16_mul2_G256_inv0_4;
  _Bool m4_ab_G4_mul2_G16_mul2_G256_inv0_0;
  _Bool m4_ab_G4_mul2_G16_mul2_G256_inv0_1;
  _Bool m4_ab_G4_mul2_G16_mul2_G256_inv0_2;
  _Bool m4_ab_G4_mul2_G16_mul2_G256_inv0_3;
  _Bool m4_ab_G4_mul2_G16_mul2_G256_inv0_4;
  _Bool m4_cd_G4_mul2_G16_mul2_G256_inv0_0;
  _Bool m4_cd_G4_mul2_G16_mul2_G256_inv0_1;
  _Bool m4_cd_G4_mul2_G16_mul2_G256_inv0_2;
  _Bool m4_cd_G4_mul2_G16_mul2_G256_inv0_3;
  _Bool m4_cd_G4_mul2_G16_mul2_G256_inv0_4;
  _Bool m4_e_G4_mul2_G16_mul2_G256_inv0_0;
  _Bool m4_e_G4_mul2_G16_mul2_G256_inv0_1;
  _Bool m4_e_G4_mul2_G16_mul2_G256_inv0_2;
  _Bool m4_e_G4_mul2_G16_mul2_G256_inv0_3;
  _Bool m4_e_G4_mul2_G16_mul2_G256_inv0_4;
  _Bool temp_var_0_G4_mul2_G16_mul2_G256_inv0_0;
  _Bool temp_var_0_G4_mul2_G16_mul2_G256_inv0_1;
  _Bool temp_var_0_G4_mul2_G16_mul2_G256_inv0_2;
  _Bool temp_var_0_G4_mul2_G16_mul2_G256_inv0_3;
  _Bool temp_var_0_G4_mul2_G16_mul2_G256_inv0_4;
  _Bool temp_var_1_G4_mul2_G16_mul2_G256_inv0_0;
  _Bool temp_var_1_G4_mul2_G16_mul2_G256_inv0_1;
  _Bool temp_var_1_G4_mul2_G16_mul2_G256_inv0_2;
  _Bool temp_var_1_G4_mul2_G16_mul2_G256_inv0_3;
  _Bool temp_var_1_G4_mul2_G16_mul2_G256_inv0_4;
  i256_tx0_G256_inv0_0 = sb_y4_0 ^ sb_y0_0;
  i256_tx0_G256_inv0_1 = sb_y4_1 ^ sb_y0_1;
  i256_tx0_G256_inv0_2 = sb_y4_2 ^ sb_y0_2;
  i256_tx0_G256_inv0_3 = sb_y4_3 ^ sb_y0_3;
  i256_tx0_G256_inv0_4 = sb_y4_4 ^ sb_y0_4;
  i256_tx1_G256_inv0_0 = sb_y5_0 ^ sb_y1_0;
  i256_tx1_G256_inv0_1 = sb_y5_1 ^ sb_y1_1;
  i256_tx1_G256_inv0_2 = sb_y5_2 ^ sb_y1_2;
  i256_tx1_G256_inv0_3 = sb_y5_3 ^ sb_y1_3;
  i256_tx1_G256_inv0_4 = sb_y5_4 ^ sb_y1_4;
  i256_tx2_G256_inv0_0 = sb_y6_0 ^ sb_y2_0;
  i256_tx2_G256_inv0_1 = sb_y6_1 ^ sb_y2_1;
  i256_tx2_G256_inv0_2 = sb_y6_2 ^ sb_y2_2;
  i256_tx2_G256_inv0_3 = sb_y6_3 ^ sb_y2_3;
  i256_tx2_G256_inv0_4 = sb_y6_4 ^ sb_y2_4;
  i256_tx3_G256_inv0_0 = sb_y7_0 ^ sb_y3_0;
  i256_tx3_G256_inv0_1 = sb_y7_1 ^ sb_y3_1;
  i256_tx3_G256_inv0_2 = sb_y7_2 ^ sb_y3_2;
  i256_tx3_G256_inv0_3 = sb_y7_3 ^ sb_y3_3;
  i256_tx3_G256_inv0_4 = sb_y7_4 ^ sb_y3_4;
  ss16_tx0_G16_sq_scl0_G256_inv0_0 = i256_tx2_G256_inv0_0 ^ i256_tx0_G256_inv0_0;
  ss16_tx0_G16_sq_scl0_G256_inv0_1 = i256_tx2_G256_inv0_1 ^ i256_tx0_G256_inv0_1;
  ss16_tx0_G16_sq_scl0_G256_inv0_2 = i256_tx2_G256_inv0_2 ^ i256_tx0_G256_inv0_2;
  ss16_tx0_G16_sq_scl0_G256_inv0_3 = i256_tx2_G256_inv0_3 ^ i256_tx0_G256_inv0_3;
  ss16_tx0_G16_sq_scl0_G256_inv0_4 = i256_tx2_G256_inv0_4 ^ i256_tx0_G256_inv0_4;
  ss16_tx1_G16_sq_scl0_G256_inv0_0 = i256_tx3_G256_inv0_0 ^ i256_tx1_G256_inv0_0;
  ss16_tx1_G16_sq_scl0_G256_inv0_1 = i256_tx3_G256_inv0_1 ^ i256_tx1_G256_inv0_1;
  ss16_tx1_G16_sq_scl0_G256_inv0_2 = i256_tx3_G256_inv0_2 ^ i256_tx1_G256_inv0_2;
  ss16_tx1_G16_sq_scl0_G256_inv0_3 = i256_tx3_G256_inv0_3 ^ i256_tx1_G256_inv0_3;
  ss16_tx1_G16_sq_scl0_G256_inv0_4 = i256_tx3_G256_inv0_4 ^ i256_tx1_G256_inv0_4;
  ss16_ph1_G16_sq_scl0_G256_inv0_0 = ss16_tx0_G16_sq_scl0_G256_inv0_0;
  ss16_ph1_G16_sq_scl0_G256_inv0_1 = ss16_tx0_G16_sq_scl0_G256_inv0_1;
  ss16_ph1_G16_sq_scl0_G256_inv0_2 = ss16_tx0_G16_sq_scl0_G256_inv0_2;
  ss16_ph1_G16_sq_scl0_G256_inv0_3 = ss16_tx0_G16_sq_scl0_G256_inv0_3;
  ss16_ph1_G16_sq_scl0_G256_inv0_4 = ss16_tx0_G16_sq_scl0_G256_inv0_4;
  ss16_ph0_G16_sq_scl0_G256_inv0_0 = ss16_tx1_G16_sq_scl0_G256_inv0_0;
  ss16_ph0_G16_sq_scl0_G256_inv0_1 = ss16_tx1_G16_sq_scl0_G256_inv0_1;
  ss16_ph0_G16_sq_scl0_G256_inv0_2 = ss16_tx1_G16_sq_scl0_G256_inv0_2;
  ss16_ph0_G16_sq_scl0_G256_inv0_3 = ss16_tx1_G16_sq_scl0_G256_inv0_3;
  ss16_ph0_G16_sq_scl0_G256_inv0_4 = ss16_tx1_G16_sq_scl0_G256_inv0_4;
  ss16_ql1_s1_G16_sq_scl0_G256_inv0_0 = i256_tx0_G256_inv0_0;
  ss16_ql1_s1_G16_sq_scl0_G256_inv0_1 = i256_tx0_G256_inv0_1;
  ss16_ql1_s1_G16_sq_scl0_G256_inv0_2 = i256_tx0_G256_inv0_2;
  ss16_ql1_s1_G16_sq_scl0_G256_inv0_3 = i256_tx0_G256_inv0_3;
  ss16_ql1_s1_G16_sq_scl0_G256_inv0_4 = i256_tx0_G256_inv0_4;
  ss16_ql0_s1_G16_sq_scl0_G256_inv0_0 = i256_tx1_G256_inv0_0;
  ss16_ql0_s1_G16_sq_scl0_G256_inv0_1 = i256_tx1_G256_inv0_1;
  ss16_ql0_s1_G16_sq_scl0_G256_inv0_2 = i256_tx1_G256_inv0_2;
  ss16_ql0_s1_G16_sq_scl0_G256_inv0_3 = i256_tx1_G256_inv0_3;
  ss16_ql0_s1_G16_sq_scl0_G256_inv0_4 = i256_tx1_G256_inv0_4;
  ss16_ql1_s2_G16_sq_scl0_G256_inv0_0 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_0 ^ ss16_ql0_s1_G16_sq_scl0_G256_inv0_0;
  ss16_ql1_s2_G16_sq_scl0_G256_inv0_1 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_1 ^ ss16_ql0_s1_G16_sq_scl0_G256_inv0_1;
  ss16_ql1_s2_G16_sq_scl0_G256_inv0_2 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_2 ^ ss16_ql0_s1_G16_sq_scl0_G256_inv0_2;
  ss16_ql1_s2_G16_sq_scl0_G256_inv0_3 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_3 ^ ss16_ql0_s1_G16_sq_scl0_G256_inv0_3;
  ss16_ql1_s2_G16_sq_scl0_G256_inv0_4 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_4 ^ ss16_ql0_s1_G16_sq_scl0_G256_inv0_4;
  ss16_ql0_s2_G16_sq_scl0_G256_inv0_0 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_0;
  ss16_ql0_s2_G16_sq_scl0_G256_inv0_1 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_1;
  ss16_ql0_s2_G16_sq_scl0_G256_inv0_2 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_2;
  ss16_ql0_s2_G16_sq_scl0_G256_inv0_3 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_3;
  ss16_ql0_s2_G16_sq_scl0_G256_inv0_4 = ss16_ql1_s1_G16_sq_scl0_G256_inv0_4;
  i256_c3_G256_inv0_0 = ss16_ph1_G16_sq_scl0_G256_inv0_0;
  i256_c3_G256_inv0_1 = ss16_ph1_G16_sq_scl0_G256_inv0_1;
  i256_c3_G256_inv0_2 = ss16_ph1_G16_sq_scl0_G256_inv0_2;
  i256_c3_G256_inv0_3 = ss16_ph1_G16_sq_scl0_G256_inv0_3;
  i256_c3_G256_inv0_4 = ss16_ph1_G16_sq_scl0_G256_inv0_4;
  i256_c2_G256_inv0_0 = ss16_ph0_G16_sq_scl0_G256_inv0_0;
  i256_c2_G256_inv0_1 = ss16_ph0_G16_sq_scl0_G256_inv0_1;
  i256_c2_G256_inv0_2 = ss16_ph0_G16_sq_scl0_G256_inv0_2;
  i256_c2_G256_inv0_3 = ss16_ph0_G16_sq_scl0_G256_inv0_3;
  i256_c2_G256_inv0_4 = ss16_ph0_G16_sq_scl0_G256_inv0_4;
  i256_c1_G256_inv0_0 = ss16_ql1_s2_G16_sq_scl0_G256_inv0_0;
  i256_c1_G256_inv0_1 = ss16_ql1_s2_G16_sq_scl0_G256_inv0_1;
  i256_c1_G256_inv0_2 = ss16_ql1_s2_G16_sq_scl0_G256_inv0_2;
  i256_c1_G256_inv0_3 = ss16_ql1_s2_G16_sq_scl0_G256_inv0_3;
  i256_c1_G256_inv0_4 = ss16_ql1_s2_G16_sq_scl0_G256_inv0_4;
  i256_c0_G256_inv0_0 = ss16_ql0_s2_G16_sq_scl0_G256_inv0_0;
  i256_c0_G256_inv0_1 = ss16_ql0_s2_G16_sq_scl0_G256_inv0_1;
  i256_c0_G256_inv0_2 = ss16_ql0_s2_G16_sq_scl0_G256_inv0_2;
  i256_c0_G256_inv0_3 = ss16_ql0_s2_G16_sq_scl0_G256_inv0_3;
  i256_c0_G256_inv0_4 = ss16_ql0_s2_G16_sq_scl0_G256_inv0_4;
  m16_tx0_G16_mul0_G256_inv0_0 = sb_y6_0 ^ sb_y4_0;
  m16_tx0_G16_mul0_G256_inv0_1 = sb_y6_1 ^ sb_y4_1;
  m16_tx0_G16_mul0_G256_inv0_2 = sb_y6_2 ^ sb_y4_2;
  m16_tx0_G16_mul0_G256_inv0_3 = sb_y6_3 ^ sb_y4_3;
  m16_tx0_G16_mul0_G256_inv0_4 = sb_y6_4 ^ sb_y4_4;
  m16_tx1_G16_mul0_G256_inv0_0 = sb_y7_0 ^ sb_y5_0;
  m16_tx1_G16_mul0_G256_inv0_1 = sb_y7_1 ^ sb_y5_1;
  m16_tx1_G16_mul0_G256_inv0_2 = sb_y7_2 ^ sb_y5_2;
  m16_tx1_G16_mul0_G256_inv0_3 = sb_y7_3 ^ sb_y5_3;
  m16_tx1_G16_mul0_G256_inv0_4 = sb_y7_4 ^ sb_y5_4;
  m16_ty0_G16_mul0_G256_inv0_0 = sb_y2_0 ^ sb_y0_0;
  m16_ty0_G16_mul0_G256_inv0_1 = sb_y2_1 ^ sb_y0_1;
  m16_ty0_G16_mul0_G256_inv0_2 = sb_y2_2 ^ sb_y0_2;
  m16_ty0_G16_mul0_G256_inv0_3 = sb_y2_3 ^ sb_y0_3;
  m16_ty0_G16_mul0_G256_inv0_4 = sb_y2_4 ^ sb_y0_4;
  m16_ty1_G16_mul0_G256_inv0_0 = sb_y3_0 ^ sb_y1_0;
  m16_ty1_G16_mul0_G256_inv0_1 = sb_y3_1 ^ sb_y1_1;
  m16_ty1_G16_mul0_G256_inv0_2 = sb_y3_2 ^ sb_y1_2;
  m16_ty1_G16_mul0_G256_inv0_3 = sb_y3_3 ^ sb_y1_3;
  m16_ty1_G16_mul0_G256_inv0_4 = sb_y3_4 ^ sb_y1_4;
  m4_ab_G4_mul0_G16_mul0_G256_inv0_0 = m16_tx1_G16_mul0_G256_inv0_0 ^ m16_tx0_G16_mul0_G256_inv0_0;
  m4_ab_G4_mul0_G16_mul0_G256_inv0_1 = m16_tx1_G16_mul0_G256_inv0_1 ^ m16_tx0_G16_mul0_G256_inv0_1;
  m4_ab_G4_mul0_G16_mul0_G256_inv0_2 = m16_tx1_G16_mul0_G256_inv0_2 ^ m16_tx0_G16_mul0_G256_inv0_2;
  m4_ab_G4_mul0_G16_mul0_G256_inv0_3 = m16_tx1_G16_mul0_G256_inv0_3 ^ m16_tx0_G16_mul0_G256_inv0_3;
  m4_ab_G4_mul0_G16_mul0_G256_inv0_4 = m16_tx1_G16_mul0_G256_inv0_4 ^ m16_tx0_G16_mul0_G256_inv0_4;
  m4_cd_G4_mul0_G16_mul0_G256_inv0_0 = m16_ty1_G16_mul0_G256_inv0_0 ^ m16_ty0_G16_mul0_G256_inv0_0;
  m4_cd_G4_mul0_G16_mul0_G256_inv0_1 = m16_ty1_G16_mul0_G256_inv0_1 ^ m16_ty0_G16_mul0_G256_inv0_1;
  m4_cd_G4_mul0_G16_mul0_G256_inv0_2 = m16_ty1_G16_mul0_G256_inv0_2 ^ m16_ty0_G16_mul0_G256_inv0_2;
  m4_cd_G4_mul0_G16_mul0_G256_inv0_3 = m16_ty1_G16_mul0_G256_inv0_3 ^ m16_ty0_G16_mul0_G256_inv0_3;
  m4_cd_G4_mul0_G16_mul0_G256_inv0_4 = m16_ty1_G16_mul0_G256_inv0_4 ^ m16_ty0_G16_mul0_G256_inv0_4;
  HPC2(m4_ab_G4_mul0_G16_mul0_G256_inv0_0, m4_ab_G4_mul0_G16_mul0_G256_inv0_1, m4_ab_G4_mul0_G16_mul0_G256_inv0_2, m4_ab_G4_mul0_G16_mul0_G256_inv0_3, m4_ab_G4_mul0_G16_mul0_G256_inv0_4, m4_cd_G4_mul0_G16_mul0_G256_inv0_0, m4_cd_G4_mul0_G16_mul0_G256_inv0_1, m4_cd_G4_mul0_G16_mul0_G256_inv0_2, m4_cd_G4_mul0_G16_mul0_G256_inv0_3, m4_cd_G4_mul0_G16_mul0_G256_inv0_4, &m4_e_G4_mul0_G16_mul0_G256_inv0_0, &m4_e_G4_mul0_G16_mul0_G256_inv0_1, &m4_e_G4_mul0_G16_mul0_G256_inv0_2, &m4_e_G4_mul0_G16_mul0_G256_inv0_3, &m4_e_G4_mul0_G16_mul0_G256_inv0_4, rand_1, rand_2, rand_3, rand_4, rand_5, rand_6, rand_7, rand_8, rand_9, rand_10);
  HPC2(m16_tx1_G16_mul0_G256_inv0_0, m16_tx1_G16_mul0_G256_inv0_1, m16_tx1_G16_mul0_G256_inv0_2, m16_tx1_G16_mul0_G256_inv0_3, m16_tx1_G16_mul0_G256_inv0_4, m16_ty1_G16_mul0_G256_inv0_0, m16_ty1_G16_mul0_G256_inv0_1, m16_ty1_G16_mul0_G256_inv0_2, m16_ty1_G16_mul0_G256_inv0_3, m16_ty1_G16_mul0_G256_inv0_4, &temp_var_0_G4_mul0_G16_mul0_G256_inv0_0, &temp_var_0_G4_mul0_G16_mul0_G256_inv0_1, &temp_var_0_G4_mul0_G16_mul0_G256_inv0_2, &temp_var_0_G4_mul0_G16_mul0_G256_inv0_3, &temp_var_0_G4_mul0_G16_mul0_G256_inv0_4, rand_11, rand_12, rand_13, rand_14, rand_15, rand_16, rand_17, rand_18, rand_19, rand_20);
  m16_e1_s1_G16_mul0_G256_inv0_0 = temp_var_0_G4_mul0_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_0;
  m16_e1_s1_G16_mul0_G256_inv0_1 = temp_var_0_G4_mul0_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_1;
  m16_e1_s1_G16_mul0_G256_inv0_2 = temp_var_0_G4_mul0_G16_mul0_G256_inv0_2 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_2;
  m16_e1_s1_G16_mul0_G256_inv0_3 = temp_var_0_G4_mul0_G16_mul0_G256_inv0_3 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_3;
  m16_e1_s1_G16_mul0_G256_inv0_4 = temp_var_0_G4_mul0_G16_mul0_G256_inv0_4 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_4;
  HPC2(m16_tx0_G16_mul0_G256_inv0_0, m16_tx0_G16_mul0_G256_inv0_1, m16_tx0_G16_mul0_G256_inv0_2, m16_tx0_G16_mul0_G256_inv0_3, m16_tx0_G16_mul0_G256_inv0_4, m16_ty0_G16_mul0_G256_inv0_0, m16_ty0_G16_mul0_G256_inv0_1, m16_ty0_G16_mul0_G256_inv0_2, m16_ty0_G16_mul0_G256_inv0_3, m16_ty0_G16_mul0_G256_inv0_4, &temp_var_1_G4_mul0_G16_mul0_G256_inv0_0, &temp_var_1_G4_mul0_G16_mul0_G256_inv0_1, &temp_var_1_G4_mul0_G16_mul0_G256_inv0_2, &temp_var_1_G4_mul0_G16_mul0_G256_inv0_3, &temp_var_1_G4_mul0_G16_mul0_G256_inv0_4, rand_21, rand_22, rand_23, rand_24, rand_25, rand_26, rand_27, rand_28, rand_29, rand_30);
  m16_e0_s1_G16_mul0_G256_inv0_0 = temp_var_1_G4_mul0_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_0;
  m16_e0_s1_G16_mul0_G256_inv0_1 = temp_var_1_G4_mul0_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_1;
  m16_e0_s1_G16_mul0_G256_inv0_2 = temp_var_1_G4_mul0_G16_mul0_G256_inv0_2 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_2;
  m16_e0_s1_G16_mul0_G256_inv0_3 = temp_var_1_G4_mul0_G16_mul0_G256_inv0_3 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_3;
  m16_e0_s1_G16_mul0_G256_inv0_4 = temp_var_1_G4_mul0_G16_mul0_G256_inv0_4 ^ m4_e_G4_mul0_G16_mul0_G256_inv0_4;
  m16_e1_s2_G16_mul0_G256_inv0_0 = m16_e0_s1_G16_mul0_G256_inv0_0;
  m16_e1_s2_G16_mul0_G256_inv0_1 = m16_e0_s1_G16_mul0_G256_inv0_1;
  m16_e1_s2_G16_mul0_G256_inv0_2 = m16_e0_s1_G16_mul0_G256_inv0_2;
  m16_e1_s2_G16_mul0_G256_inv0_3 = m16_e0_s1_G16_mul0_G256_inv0_3;
  m16_e1_s2_G16_mul0_G256_inv0_4 = m16_e0_s1_G16_mul0_G256_inv0_4;
  m16_e0_s2_G16_mul0_G256_inv0_0 = m16_e1_s1_G16_mul0_G256_inv0_0 ^ m16_e0_s1_G16_mul0_G256_inv0_0;
  m16_e0_s2_G16_mul0_G256_inv0_1 = m16_e1_s1_G16_mul0_G256_inv0_1 ^ m16_e0_s1_G16_mul0_G256_inv0_1;
  m16_e0_s2_G16_mul0_G256_inv0_2 = m16_e1_s1_G16_mul0_G256_inv0_2 ^ m16_e0_s1_G16_mul0_G256_inv0_2;
  m16_e0_s2_G16_mul0_G256_inv0_3 = m16_e1_s1_G16_mul0_G256_inv0_3 ^ m16_e0_s1_G16_mul0_G256_inv0_3;
  m16_e0_s2_G16_mul0_G256_inv0_4 = m16_e1_s1_G16_mul0_G256_inv0_4 ^ m16_e0_s1_G16_mul0_G256_inv0_4;
  m4_ab_G4_mul1_G16_mul0_G256_inv0_0 = sb_y7_0 ^ sb_y6_0;
  m4_ab_G4_mul1_G16_mul0_G256_inv0_1 = sb_y7_1 ^ sb_y6_1;
  m4_ab_G4_mul1_G16_mul0_G256_inv0_2 = sb_y7_2 ^ sb_y6_2;
  m4_ab_G4_mul1_G16_mul0_G256_inv0_3 = sb_y7_3 ^ sb_y6_3;
  m4_ab_G4_mul1_G16_mul0_G256_inv0_4 = sb_y7_4 ^ sb_y6_4;
  m4_cd_G4_mul1_G16_mul0_G256_inv0_0 = sb_y3_0 ^ sb_y2_0;
  m4_cd_G4_mul1_G16_mul0_G256_inv0_1 = sb_y3_1 ^ sb_y2_1;
  m4_cd_G4_mul1_G16_mul0_G256_inv0_2 = sb_y3_2 ^ sb_y2_2;
  m4_cd_G4_mul1_G16_mul0_G256_inv0_3 = sb_y3_3 ^ sb_y2_3;
  m4_cd_G4_mul1_G16_mul0_G256_inv0_4 = sb_y3_4 ^ sb_y2_4;
  HPC2(m4_ab_G4_mul1_G16_mul0_G256_inv0_0, m4_ab_G4_mul1_G16_mul0_G256_inv0_1, m4_ab_G4_mul1_G16_mul0_G256_inv0_2, m4_ab_G4_mul1_G16_mul0_G256_inv0_3, m4_ab_G4_mul1_G16_mul0_G256_inv0_4, m4_cd_G4_mul1_G16_mul0_G256_inv0_0, m4_cd_G4_mul1_G16_mul0_G256_inv0_1, m4_cd_G4_mul1_G16_mul0_G256_inv0_2, m4_cd_G4_mul1_G16_mul0_G256_inv0_3, m4_cd_G4_mul1_G16_mul0_G256_inv0_4, &m4_e_G4_mul1_G16_mul0_G256_inv0_0, &m4_e_G4_mul1_G16_mul0_G256_inv0_1, &m4_e_G4_mul1_G16_mul0_G256_inv0_2, &m4_e_G4_mul1_G16_mul0_G256_inv0_3, &m4_e_G4_mul1_G16_mul0_G256_inv0_4, rand_31, rand_32, rand_33, rand_34, rand_35, rand_36, rand_37, rand_38, rand_39, rand_40);
  HPC2(sb_y7_0, sb_y7_1, sb_y7_2, sb_y7_3, sb_y7_4, sb_y3_0, sb_y3_1, sb_y3_2, sb_y3_3, sb_y3_4, &temp_var_0_G4_mul1_G16_mul0_G256_inv0_0, &temp_var_0_G4_mul1_G16_mul0_G256_inv0_1, &temp_var_0_G4_mul1_G16_mul0_G256_inv0_2, &temp_var_0_G4_mul1_G16_mul0_G256_inv0_3, &temp_var_0_G4_mul1_G16_mul0_G256_inv0_4, rand_41, rand_42, rand_43, rand_44, rand_45, rand_46, rand_47, rand_48, rand_49, rand_50);
  m16_ph1_G16_mul0_G256_inv0_0 = temp_var_0_G4_mul1_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_0;
  m16_ph1_G16_mul0_G256_inv0_1 = temp_var_0_G4_mul1_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_1;
  m16_ph1_G16_mul0_G256_inv0_2 = temp_var_0_G4_mul1_G16_mul0_G256_inv0_2 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_2;
  m16_ph1_G16_mul0_G256_inv0_3 = temp_var_0_G4_mul1_G16_mul0_G256_inv0_3 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_3;
  m16_ph1_G16_mul0_G256_inv0_4 = temp_var_0_G4_mul1_G16_mul0_G256_inv0_4 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_4;
  HPC2(sb_y6_0, sb_y6_1, sb_y6_2, sb_y6_3, sb_y6_4, sb_y2_0, sb_y2_1, sb_y2_2, sb_y2_3, sb_y2_4, &temp_var_1_G4_mul1_G16_mul0_G256_inv0_0, &temp_var_1_G4_mul1_G16_mul0_G256_inv0_1, &temp_var_1_G4_mul1_G16_mul0_G256_inv0_2, &temp_var_1_G4_mul1_G16_mul0_G256_inv0_3, &temp_var_1_G4_mul1_G16_mul0_G256_inv0_4, rand_51, rand_52, rand_53, rand_54, rand_55, rand_56, rand_57, rand_58, rand_59, rand_60);
  m16_ph0_G16_mul0_G256_inv0_0 = temp_var_1_G4_mul1_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_0;
  m16_ph0_G16_mul0_G256_inv0_1 = temp_var_1_G4_mul1_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_1;
  m16_ph0_G16_mul0_G256_inv0_2 = temp_var_1_G4_mul1_G16_mul0_G256_inv0_2 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_2;
  m16_ph0_G16_mul0_G256_inv0_3 = temp_var_1_G4_mul1_G16_mul0_G256_inv0_3 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_3;
  m16_ph0_G16_mul0_G256_inv0_4 = temp_var_1_G4_mul1_G16_mul0_G256_inv0_4 ^ m4_e_G4_mul1_G16_mul0_G256_inv0_4;
  m4_ab_G4_mul2_G16_mul0_G256_inv0_0 = sb_y5_0 ^ sb_y4_0;
  m4_ab_G4_mul2_G16_mul0_G256_inv0_1 = sb_y5_1 ^ sb_y4_1;
  m4_ab_G4_mul2_G16_mul0_G256_inv0_2 = sb_y5_2 ^ sb_y4_2;
  m4_ab_G4_mul2_G16_mul0_G256_inv0_3 = sb_y5_3 ^ sb_y4_3;
  m4_ab_G4_mul2_G16_mul0_G256_inv0_4 = sb_y5_4 ^ sb_y4_4;
  m4_cd_G4_mul2_G16_mul0_G256_inv0_0 = sb_y1_0 ^ sb_y0_0;
  m4_cd_G4_mul2_G16_mul0_G256_inv0_1 = sb_y1_1 ^ sb_y0_1;
  m4_cd_G4_mul2_G16_mul0_G256_inv0_2 = sb_y1_2 ^ sb_y0_2;
  m4_cd_G4_mul2_G16_mul0_G256_inv0_3 = sb_y1_3 ^ sb_y0_3;
  m4_cd_G4_mul2_G16_mul0_G256_inv0_4 = sb_y1_4 ^ sb_y0_4;
  HPC2(m4_ab_G4_mul2_G16_mul0_G256_inv0_0, m4_ab_G4_mul2_G16_mul0_G256_inv0_1, m4_ab_G4_mul2_G16_mul0_G256_inv0_2, m4_ab_G4_mul2_G16_mul0_G256_inv0_3, m4_ab_G4_mul2_G16_mul0_G256_inv0_4, m4_cd_G4_mul2_G16_mul0_G256_inv0_0, m4_cd_G4_mul2_G16_mul0_G256_inv0_1, m4_cd_G4_mul2_G16_mul0_G256_inv0_2, m4_cd_G4_mul2_G16_mul0_G256_inv0_3, m4_cd_G4_mul2_G16_mul0_G256_inv0_4, &m4_e_G4_mul2_G16_mul0_G256_inv0_0, &m4_e_G4_mul2_G16_mul0_G256_inv0_1, &m4_e_G4_mul2_G16_mul0_G256_inv0_2, &m4_e_G4_mul2_G16_mul0_G256_inv0_3, &m4_e_G4_mul2_G16_mul0_G256_inv0_4, rand_61, rand_62, rand_63, rand_64, rand_65, rand_66, rand_67, rand_68, rand_69, rand_70);
  HPC2(sb_y5_0, sb_y5_1, sb_y5_2, sb_y5_3, sb_y5_4, sb_y1_0, sb_y1_1, sb_y1_2, sb_y1_3, sb_y1_4, &temp_var_0_G4_mul2_G16_mul0_G256_inv0_0, &temp_var_0_G4_mul2_G16_mul0_G256_inv0_1, &temp_var_0_G4_mul2_G16_mul0_G256_inv0_2, &temp_var_0_G4_mul2_G16_mul0_G256_inv0_3, &temp_var_0_G4_mul2_G16_mul0_G256_inv0_4, rand_71, rand_72, rand_73, rand_74, rand_75, rand_76, rand_77, rand_78, rand_79, rand_80);
  m16_ql1_G16_mul0_G256_inv0_0 = temp_var_0_G4_mul2_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_0;
  m16_ql1_G16_mul0_G256_inv0_1 = temp_var_0_G4_mul2_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_1;
  m16_ql1_G16_mul0_G256_inv0_2 = temp_var_0_G4_mul2_G16_mul0_G256_inv0_2 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_2;
  m16_ql1_G16_mul0_G256_inv0_3 = temp_var_0_G4_mul2_G16_mul0_G256_inv0_3 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_3;
  m16_ql1_G16_mul0_G256_inv0_4 = temp_var_0_G4_mul2_G16_mul0_G256_inv0_4 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_4;
  HPC2(sb_y4_0, sb_y4_1, sb_y4_2, sb_y4_3, sb_y4_4, sb_y0_0, sb_y0_1, sb_y0_2, sb_y0_3, sb_y0_4, &temp_var_1_G4_mul2_G16_mul0_G256_inv0_0, &temp_var_1_G4_mul2_G16_mul0_G256_inv0_1, &temp_var_1_G4_mul2_G16_mul0_G256_inv0_2, &temp_var_1_G4_mul2_G16_mul0_G256_inv0_3, &temp_var_1_G4_mul2_G16_mul0_G256_inv0_4, rand_81, rand_82, rand_83, rand_84, rand_85, rand_86, rand_87, rand_88, rand_89, rand_90);
  m16_ql0_G16_mul0_G256_inv0_0 = temp_var_1_G4_mul2_G16_mul0_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_0;
  m16_ql0_G16_mul0_G256_inv0_1 = temp_var_1_G4_mul2_G16_mul0_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_1;
  m16_ql0_G16_mul0_G256_inv0_2 = temp_var_1_G4_mul2_G16_mul0_G256_inv0_2 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_2;
  m16_ql0_G16_mul0_G256_inv0_3 = temp_var_1_G4_mul2_G16_mul0_G256_inv0_3 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_3;
  m16_ql0_G16_mul0_G256_inv0_4 = temp_var_1_G4_mul2_G16_mul0_G256_inv0_4 ^ m4_e_G4_mul2_G16_mul0_G256_inv0_4;
  i256_d3_G256_inv0_0 = m16_ph1_G16_mul0_G256_inv0_0 ^ m16_e1_s2_G16_mul0_G256_inv0_0;
  i256_d3_G256_inv0_1 = m16_ph1_G16_mul0_G256_inv0_1 ^ m16_e1_s2_G16_mul0_G256_inv0_1;
  i256_d3_G256_inv0_2 = m16_ph1_G16_mul0_G256_inv0_2 ^ m16_e1_s2_G16_mul0_G256_inv0_2;
  i256_d3_G256_inv0_3 = m16_ph1_G16_mul0_G256_inv0_3 ^ m16_e1_s2_G16_mul0_G256_inv0_3;
  i256_d3_G256_inv0_4 = m16_ph1_G16_mul0_G256_inv0_4 ^ m16_e1_s2_G16_mul0_G256_inv0_4;
  i256_d2_G256_inv0_0 = m16_ph0_G16_mul0_G256_inv0_0 ^ m16_e0_s2_G16_mul0_G256_inv0_0;
  i256_d2_G256_inv0_1 = m16_ph0_G16_mul0_G256_inv0_1 ^ m16_e0_s2_G16_mul0_G256_inv0_1;
  i256_d2_G256_inv0_2 = m16_ph0_G16_mul0_G256_inv0_2 ^ m16_e0_s2_G16_mul0_G256_inv0_2;
  i256_d2_G256_inv0_3 = m16_ph0_G16_mul0_G256_inv0_3 ^ m16_e0_s2_G16_mul0_G256_inv0_3;
  i256_d2_G256_inv0_4 = m16_ph0_G16_mul0_G256_inv0_4 ^ m16_e0_s2_G16_mul0_G256_inv0_4;
  i256_d1_G256_inv0_0 = m16_ql1_G16_mul0_G256_inv0_0 ^ m16_e1_s2_G16_mul0_G256_inv0_0;
  i256_d1_G256_inv0_1 = m16_ql1_G16_mul0_G256_inv0_1 ^ m16_e1_s2_G16_mul0_G256_inv0_1;
  i256_d1_G256_inv0_2 = m16_ql1_G16_mul0_G256_inv0_2 ^ m16_e1_s2_G16_mul0_G256_inv0_2;
  i256_d1_G256_inv0_3 = m16_ql1_G16_mul0_G256_inv0_3 ^ m16_e1_s2_G16_mul0_G256_inv0_3;
  i256_d1_G256_inv0_4 = m16_ql1_G16_mul0_G256_inv0_4 ^ m16_e1_s2_G16_mul0_G256_inv0_4;
  i256_d0_G256_inv0_0 = m16_ql0_G16_mul0_G256_inv0_0 ^ m16_e0_s2_G16_mul0_G256_inv0_0;
  i256_d0_G256_inv0_1 = m16_ql0_G16_mul0_G256_inv0_1 ^ m16_e0_s2_G16_mul0_G256_inv0_1;
  i256_d0_G256_inv0_2 = m16_ql0_G16_mul0_G256_inv0_2 ^ m16_e0_s2_G16_mul0_G256_inv0_2;
  i256_d0_G256_inv0_3 = m16_ql0_G16_mul0_G256_inv0_3 ^ m16_e0_s2_G16_mul0_G256_inv0_3;
  i256_d0_G256_inv0_4 = m16_ql0_G16_mul0_G256_inv0_4 ^ m16_e0_s2_G16_mul0_G256_inv0_4;
  i256_te0_G256_inv0_0 = i256_c0_G256_inv0_0 ^ i256_d0_G256_inv0_0;
  i256_te0_G256_inv0_1 = i256_c0_G256_inv0_1 ^ i256_d0_G256_inv0_1;
  i256_te0_G256_inv0_2 = i256_c0_G256_inv0_2 ^ i256_d0_G256_inv0_2;
  i256_te0_G256_inv0_3 = i256_c0_G256_inv0_3 ^ i256_d0_G256_inv0_3;
  i256_te0_G256_inv0_4 = i256_c0_G256_inv0_4 ^ i256_d0_G256_inv0_4;
  i256_te1_G256_inv0_0 = i256_c1_G256_inv0_0 ^ i256_d1_G256_inv0_0;
  i256_te1_G256_inv0_1 = i256_c1_G256_inv0_1 ^ i256_d1_G256_inv0_1;
  i256_te1_G256_inv0_2 = i256_c1_G256_inv0_2 ^ i256_d1_G256_inv0_2;
  i256_te1_G256_inv0_3 = i256_c1_G256_inv0_3 ^ i256_d1_G256_inv0_3;
  i256_te1_G256_inv0_4 = i256_c1_G256_inv0_4 ^ i256_d1_G256_inv0_4;
  i256_te2_G256_inv0_0 = i256_c2_G256_inv0_0 ^ i256_d2_G256_inv0_0;
  i256_te2_G256_inv0_1 = i256_c2_G256_inv0_1 ^ i256_d2_G256_inv0_1;
  i256_te2_G256_inv0_2 = i256_c2_G256_inv0_2 ^ i256_d2_G256_inv0_2;
  i256_te2_G256_inv0_3 = i256_c2_G256_inv0_3 ^ i256_d2_G256_inv0_3;
  i256_te2_G256_inv0_4 = i256_c2_G256_inv0_4 ^ i256_d2_G256_inv0_4;
  i256_te3_G256_inv0_0 = i256_c3_G256_inv0_0 ^ i256_d3_G256_inv0_0;
  i256_te3_G256_inv0_1 = i256_c3_G256_inv0_1 ^ i256_d3_G256_inv0_1;
  i256_te3_G256_inv0_2 = i256_c3_G256_inv0_2 ^ i256_d3_G256_inv0_2;
  i256_te3_G256_inv0_3 = i256_c3_G256_inv0_3 ^ i256_d3_G256_inv0_3;
  i256_te3_G256_inv0_4 = i256_c3_G256_inv0_4 ^ i256_d3_G256_inv0_4;
  i16_tx0_G16_inv0_G256_inv0_0 = i256_te2_G256_inv0_0 ^ i256_te0_G256_inv0_0;
  i16_tx0_G16_inv0_G256_inv0_1 = i256_te2_G256_inv0_1 ^ i256_te0_G256_inv0_1;
  i16_tx0_G16_inv0_G256_inv0_2 = i256_te2_G256_inv0_2 ^ i256_te0_G256_inv0_2;
  i16_tx0_G16_inv0_G256_inv0_3 = i256_te2_G256_inv0_3 ^ i256_te0_G256_inv0_3;
  i16_tx0_G16_inv0_G256_inv0_4 = i256_te2_G256_inv0_4 ^ i256_te0_G256_inv0_4;
  i16_tx1_G16_inv0_G256_inv0_0 = i256_te3_G256_inv0_0 ^ i256_te1_G256_inv0_0;
  i16_tx1_G16_inv0_G256_inv0_1 = i256_te3_G256_inv0_1 ^ i256_te1_G256_inv0_1;
  i16_tx1_G16_inv0_G256_inv0_2 = i256_te3_G256_inv0_2 ^ i256_te1_G256_inv0_2;
  i16_tx1_G16_inv0_G256_inv0_3 = i256_te3_G256_inv0_3 ^ i256_te1_G256_inv0_3;
  i16_tx1_G16_inv0_G256_inv0_4 = i256_te3_G256_inv0_4 ^ i256_te1_G256_inv0_4;
  i16_c1_s1_G16_inv0_G256_inv0_0 = i16_tx0_G16_inv0_G256_inv0_0;
  i16_c1_s1_G16_inv0_G256_inv0_1 = i16_tx0_G16_inv0_G256_inv0_1;
  i16_c1_s1_G16_inv0_G256_inv0_2 = i16_tx0_G16_inv0_G256_inv0_2;
  i16_c1_s1_G16_inv0_G256_inv0_3 = i16_tx0_G16_inv0_G256_inv0_3;
  i16_c1_s1_G16_inv0_G256_inv0_4 = i16_tx0_G16_inv0_G256_inv0_4;
  i16_c0_s1_G16_inv0_G256_inv0_0 = i16_tx1_G16_inv0_G256_inv0_0;
  i16_c0_s1_G16_inv0_G256_inv0_1 = i16_tx1_G16_inv0_G256_inv0_1;
  i16_c0_s1_G16_inv0_G256_inv0_2 = i16_tx1_G16_inv0_G256_inv0_2;
  i16_c0_s1_G16_inv0_G256_inv0_3 = i16_tx1_G16_inv0_G256_inv0_3;
  i16_c0_s1_G16_inv0_G256_inv0_4 = i16_tx1_G16_inv0_G256_inv0_4;
  i16_c1_s2_G16_inv0_G256_inv0_0 = i16_c0_s1_G16_inv0_G256_inv0_0;
  i16_c1_s2_G16_inv0_G256_inv0_1 = i16_c0_s1_G16_inv0_G256_inv0_1;
  i16_c1_s2_G16_inv0_G256_inv0_2 = i16_c0_s1_G16_inv0_G256_inv0_2;
  i16_c1_s2_G16_inv0_G256_inv0_3 = i16_c0_s1_G16_inv0_G256_inv0_3;
  i16_c1_s2_G16_inv0_G256_inv0_4 = i16_c0_s1_G16_inv0_G256_inv0_4;
  i16_c0_s2_G16_inv0_G256_inv0_0 = i16_c1_s1_G16_inv0_G256_inv0_0 ^ i16_c0_s1_G16_inv0_G256_inv0_0;
  i16_c0_s2_G16_inv0_G256_inv0_1 = i16_c1_s1_G16_inv0_G256_inv0_1 ^ i16_c0_s1_G16_inv0_G256_inv0_1;
  i16_c0_s2_G16_inv0_G256_inv0_2 = i16_c1_s1_G16_inv0_G256_inv0_2 ^ i16_c0_s1_G16_inv0_G256_inv0_2;
  i16_c0_s2_G16_inv0_G256_inv0_3 = i16_c1_s1_G16_inv0_G256_inv0_3 ^ i16_c0_s1_G16_inv0_G256_inv0_3;
  i16_c0_s2_G16_inv0_G256_inv0_4 = i16_c1_s1_G16_inv0_G256_inv0_4 ^ i16_c0_s1_G16_inv0_G256_inv0_4;
  m4_ab_G4_mul3_G16_inv0_G256_inv0_0 = i256_te3_G256_inv0_0 ^ i256_te2_G256_inv0_0;
  m4_ab_G4_mul3_G16_inv0_G256_inv0_1 = i256_te3_G256_inv0_1 ^ i256_te2_G256_inv0_1;
  m4_ab_G4_mul3_G16_inv0_G256_inv0_2 = i256_te3_G256_inv0_2 ^ i256_te2_G256_inv0_2;
  m4_ab_G4_mul3_G16_inv0_G256_inv0_3 = i256_te3_G256_inv0_3 ^ i256_te2_G256_inv0_3;
  m4_ab_G4_mul3_G16_inv0_G256_inv0_4 = i256_te3_G256_inv0_4 ^ i256_te2_G256_inv0_4;
  m4_cd_G4_mul3_G16_inv0_G256_inv0_0 = i256_te1_G256_inv0_0 ^ i256_te0_G256_inv0_0;
  m4_cd_G4_mul3_G16_inv0_G256_inv0_1 = i256_te1_G256_inv0_1 ^ i256_te0_G256_inv0_1;
  m4_cd_G4_mul3_G16_inv0_G256_inv0_2 = i256_te1_G256_inv0_2 ^ i256_te0_G256_inv0_2;
  m4_cd_G4_mul3_G16_inv0_G256_inv0_3 = i256_te1_G256_inv0_3 ^ i256_te0_G256_inv0_3;
  m4_cd_G4_mul3_G16_inv0_G256_inv0_4 = i256_te1_G256_inv0_4 ^ i256_te0_G256_inv0_4;
  HPC3(m4_ab_G4_mul3_G16_inv0_G256_inv0_0, m4_ab_G4_mul3_G16_inv0_G256_inv0_1, m4_ab_G4_mul3_G16_inv0_G256_inv0_2, m4_ab_G4_mul3_G16_inv0_G256_inv0_3, m4_ab_G4_mul3_G16_inv0_G256_inv0_4, m4_cd_G4_mul3_G16_inv0_G256_inv0_0, m4_cd_G4_mul3_G16_inv0_G256_inv0_1, m4_cd_G4_mul3_G16_inv0_G256_inv0_2, m4_cd_G4_mul3_G16_inv0_G256_inv0_3, m4_cd_G4_mul3_G16_inv0_G256_inv0_4, &m4_e_G4_mul3_G16_inv0_G256_inv0_0, &m4_e_G4_mul3_G16_inv0_G256_inv0_1, &m4_e_G4_mul3_G16_inv0_G256_inv0_2, &m4_e_G4_mul3_G16_inv0_G256_inv0_3, &m4_e_G4_mul3_G16_inv0_G256_inv0_4, rand_91, rand_92, rand_93, rand_94, rand_95, rand_96, rand_97, rand_98, rand_99, rand_100, rand_101, rand_102, rand_103, rand_104, rand_105, rand_106, rand_107, rand_108, rand_109, rand_110);
  HPC3(i256_te3_G256_inv0_0, i256_te3_G256_inv0_1, i256_te3_G256_inv0_2, i256_te3_G256_inv0_3, i256_te3_G256_inv0_4, i256_te1_G256_inv0_0, i256_te1_G256_inv0_1, i256_te1_G256_inv0_2, i256_te1_G256_inv0_3, i256_te1_G256_inv0_4, &temp_var_0_G4_mul3_G16_inv0_G256_inv0_0, &temp_var_0_G4_mul3_G16_inv0_G256_inv0_1, &temp_var_0_G4_mul3_G16_inv0_G256_inv0_2, &temp_var_0_G4_mul3_G16_inv0_G256_inv0_3, &temp_var_0_G4_mul3_G16_inv0_G256_inv0_4, rand_111, rand_112, rand_113, rand_114, rand_115, rand_116, rand_117, rand_118, rand_119, rand_120, rand_121, rand_122, rand_123, rand_124, rand_125, rand_126, rand_127, rand_128, rand_129, rand_130);
  i16_d1_G16_inv0_G256_inv0_0 = temp_var_0_G4_mul3_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_0;
  i16_d1_G16_inv0_G256_inv0_1 = temp_var_0_G4_mul3_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_1;
  i16_d1_G16_inv0_G256_inv0_2 = temp_var_0_G4_mul3_G16_inv0_G256_inv0_2 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_2;
  i16_d1_G16_inv0_G256_inv0_3 = temp_var_0_G4_mul3_G16_inv0_G256_inv0_3 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_3;
  i16_d1_G16_inv0_G256_inv0_4 = temp_var_0_G4_mul3_G16_inv0_G256_inv0_4 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_4;
  HPC3(i256_te2_G256_inv0_0, i256_te2_G256_inv0_1, i256_te2_G256_inv0_2, i256_te2_G256_inv0_3, i256_te2_G256_inv0_4, i256_te0_G256_inv0_0, i256_te0_G256_inv0_1, i256_te0_G256_inv0_2, i256_te0_G256_inv0_3, i256_te0_G256_inv0_4, &temp_var_1_G4_mul3_G16_inv0_G256_inv0_0, &temp_var_1_G4_mul3_G16_inv0_G256_inv0_1, &temp_var_1_G4_mul3_G16_inv0_G256_inv0_2, &temp_var_1_G4_mul3_G16_inv0_G256_inv0_3, &temp_var_1_G4_mul3_G16_inv0_G256_inv0_4, rand_131, rand_132, rand_133, rand_134, rand_135, rand_136, rand_137, rand_138, rand_139, rand_140, rand_141, rand_142, rand_143, rand_144, rand_145, rand_146, rand_147, rand_148, rand_149, rand_150);
  i16_d0_G16_inv0_G256_inv0_0 = temp_var_1_G4_mul3_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_0;
  i16_d0_G16_inv0_G256_inv0_1 = temp_var_1_G4_mul3_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_1;
  i16_d0_G16_inv0_G256_inv0_2 = temp_var_1_G4_mul3_G16_inv0_G256_inv0_2 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_2;
  i16_d0_G16_inv0_G256_inv0_3 = temp_var_1_G4_mul3_G16_inv0_G256_inv0_3 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_3;
  i16_d0_G16_inv0_G256_inv0_4 = temp_var_1_G4_mul3_G16_inv0_G256_inv0_4 ^ m4_e_G4_mul3_G16_inv0_G256_inv0_4;
  i16_te0_G16_inv0_G256_inv0_0 = i16_c0_s2_G16_inv0_G256_inv0_0 ^ i16_d0_G16_inv0_G256_inv0_0;
  i16_te0_G16_inv0_G256_inv0_1 = i16_c0_s2_G16_inv0_G256_inv0_1 ^ i16_d0_G16_inv0_G256_inv0_1;
  i16_te0_G16_inv0_G256_inv0_2 = i16_c0_s2_G16_inv0_G256_inv0_2 ^ i16_d0_G16_inv0_G256_inv0_2;
  i16_te0_G16_inv0_G256_inv0_3 = i16_c0_s2_G16_inv0_G256_inv0_3 ^ i16_d0_G16_inv0_G256_inv0_3;
  i16_te0_G16_inv0_G256_inv0_4 = i16_c0_s2_G16_inv0_G256_inv0_4 ^ i16_d0_G16_inv0_G256_inv0_4;
  i16_te1_G16_inv0_G256_inv0_0 = i16_c1_s2_G16_inv0_G256_inv0_0 ^ i16_d1_G16_inv0_G256_inv0_0;
  i16_te1_G16_inv0_G256_inv0_1 = i16_c1_s2_G16_inv0_G256_inv0_1 ^ i16_d1_G16_inv0_G256_inv0_1;
  i16_te1_G16_inv0_G256_inv0_2 = i16_c1_s2_G16_inv0_G256_inv0_2 ^ i16_d1_G16_inv0_G256_inv0_2;
  i16_te1_G16_inv0_G256_inv0_3 = i16_c1_s2_G16_inv0_G256_inv0_3 ^ i16_d1_G16_inv0_G256_inv0_3;
  i16_te1_G16_inv0_G256_inv0_4 = i16_c1_s2_G16_inv0_G256_inv0_4 ^ i16_d1_G16_inv0_G256_inv0_4;
  i16_e1_G16_inv0_G256_inv0_0 = i16_te0_G16_inv0_G256_inv0_0;
  i16_e1_G16_inv0_G256_inv0_1 = i16_te0_G16_inv0_G256_inv0_1;
  i16_e1_G16_inv0_G256_inv0_2 = i16_te0_G16_inv0_G256_inv0_2;
  i16_e1_G16_inv0_G256_inv0_3 = i16_te0_G16_inv0_G256_inv0_3;
  i16_e1_G16_inv0_G256_inv0_4 = i16_te0_G16_inv0_G256_inv0_4;
  i16_e0_G16_inv0_G256_inv0_0 = i16_te1_G16_inv0_G256_inv0_0;
  i16_e0_G16_inv0_G256_inv0_1 = i16_te1_G16_inv0_G256_inv0_1;
  i16_e0_G16_inv0_G256_inv0_2 = i16_te1_G16_inv0_G256_inv0_2;
  i16_e0_G16_inv0_G256_inv0_3 = i16_te1_G16_inv0_G256_inv0_3;
  i16_e0_G16_inv0_G256_inv0_4 = i16_te1_G16_inv0_G256_inv0_4;
  m4_ab_G4_mul4_G16_inv0_G256_inv0_0 = i16_e1_G16_inv0_G256_inv0_0 ^ i16_e0_G16_inv0_G256_inv0_0;
  m4_ab_G4_mul4_G16_inv0_G256_inv0_1 = i16_e1_G16_inv0_G256_inv0_1 ^ i16_e0_G16_inv0_G256_inv0_1;
  m4_ab_G4_mul4_G16_inv0_G256_inv0_2 = i16_e1_G16_inv0_G256_inv0_2 ^ i16_e0_G16_inv0_G256_inv0_2;
  m4_ab_G4_mul4_G16_inv0_G256_inv0_3 = i16_e1_G16_inv0_G256_inv0_3 ^ i16_e0_G16_inv0_G256_inv0_3;
  m4_ab_G4_mul4_G16_inv0_G256_inv0_4 = i16_e1_G16_inv0_G256_inv0_4 ^ i16_e0_G16_inv0_G256_inv0_4;
  m4_cd_G4_mul4_G16_inv0_G256_inv0_0 = i256_te1_G256_inv0_0 ^ i256_te0_G256_inv0_0;
  m4_cd_G4_mul4_G16_inv0_G256_inv0_1 = i256_te1_G256_inv0_1 ^ i256_te0_G256_inv0_1;
  m4_cd_G4_mul4_G16_inv0_G256_inv0_2 = i256_te1_G256_inv0_2 ^ i256_te0_G256_inv0_2;
  m4_cd_G4_mul4_G16_inv0_G256_inv0_3 = i256_te1_G256_inv0_3 ^ i256_te0_G256_inv0_3;
  m4_cd_G4_mul4_G16_inv0_G256_inv0_4 = i256_te1_G256_inv0_4 ^ i256_te0_G256_inv0_4;
  HPC2(m4_ab_G4_mul4_G16_inv0_G256_inv0_0, m4_ab_G4_mul4_G16_inv0_G256_inv0_1, m4_ab_G4_mul4_G16_inv0_G256_inv0_2, m4_ab_G4_mul4_G16_inv0_G256_inv0_3, m4_ab_G4_mul4_G16_inv0_G256_inv0_4, m4_cd_G4_mul4_G16_inv0_G256_inv0_0, m4_cd_G4_mul4_G16_inv0_G256_inv0_1, m4_cd_G4_mul4_G16_inv0_G256_inv0_2, m4_cd_G4_mul4_G16_inv0_G256_inv0_3, m4_cd_G4_mul4_G16_inv0_G256_inv0_4, &m4_e_G4_mul4_G16_inv0_G256_inv0_0, &m4_e_G4_mul4_G16_inv0_G256_inv0_1, &m4_e_G4_mul4_G16_inv0_G256_inv0_2, &m4_e_G4_mul4_G16_inv0_G256_inv0_3, &m4_e_G4_mul4_G16_inv0_G256_inv0_4, rand_151, rand_152, rand_153, rand_154, rand_155, rand_156, rand_157, rand_158, rand_159, rand_160);
  HPC2(i16_e1_G16_inv0_G256_inv0_0, i16_e1_G16_inv0_G256_inv0_1, i16_e1_G16_inv0_G256_inv0_2, i16_e1_G16_inv0_G256_inv0_3, i16_e1_G16_inv0_G256_inv0_4, i256_te1_G256_inv0_0, i256_te1_G256_inv0_1, i256_te1_G256_inv0_2, i256_te1_G256_inv0_3, i256_te1_G256_inv0_4, &temp_var_0_G4_mul4_G16_inv0_G256_inv0_0, &temp_var_0_G4_mul4_G16_inv0_G256_inv0_1, &temp_var_0_G4_mul4_G16_inv0_G256_inv0_2, &temp_var_0_G4_mul4_G16_inv0_G256_inv0_3, &temp_var_0_G4_mul4_G16_inv0_G256_inv0_4, rand_161, rand_162, rand_163, rand_164, rand_165, rand_166, rand_167, rand_168, rand_169, rand_170);
  i16_ph1_G16_inv0_G256_inv0_0 = temp_var_0_G4_mul4_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_0;
  i16_ph1_G16_inv0_G256_inv0_1 = temp_var_0_G4_mul4_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_1;
  i16_ph1_G16_inv0_G256_inv0_2 = temp_var_0_G4_mul4_G16_inv0_G256_inv0_2 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_2;
  i16_ph1_G16_inv0_G256_inv0_3 = temp_var_0_G4_mul4_G16_inv0_G256_inv0_3 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_3;
  i16_ph1_G16_inv0_G256_inv0_4 = temp_var_0_G4_mul4_G16_inv0_G256_inv0_4 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_4;
  HPC2(i16_e0_G16_inv0_G256_inv0_0, i16_e0_G16_inv0_G256_inv0_1, i16_e0_G16_inv0_G256_inv0_2, i16_e0_G16_inv0_G256_inv0_3, i16_e0_G16_inv0_G256_inv0_4, i256_te0_G256_inv0_0, i256_te0_G256_inv0_1, i256_te0_G256_inv0_2, i256_te0_G256_inv0_3, i256_te0_G256_inv0_4, &temp_var_1_G4_mul4_G16_inv0_G256_inv0_0, &temp_var_1_G4_mul4_G16_inv0_G256_inv0_1, &temp_var_1_G4_mul4_G16_inv0_G256_inv0_2, &temp_var_1_G4_mul4_G16_inv0_G256_inv0_3, &temp_var_1_G4_mul4_G16_inv0_G256_inv0_4, rand_171, rand_172, rand_173, rand_174, rand_175, rand_176, rand_177, rand_178, rand_179, rand_180);
  i16_ph0_G16_inv0_G256_inv0_0 = temp_var_1_G4_mul4_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_0;
  i16_ph0_G16_inv0_G256_inv0_1 = temp_var_1_G4_mul4_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_1;
  i16_ph0_G16_inv0_G256_inv0_2 = temp_var_1_G4_mul4_G16_inv0_G256_inv0_2 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_2;
  i16_ph0_G16_inv0_G256_inv0_3 = temp_var_1_G4_mul4_G16_inv0_G256_inv0_3 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_3;
  i16_ph0_G16_inv0_G256_inv0_4 = temp_var_1_G4_mul4_G16_inv0_G256_inv0_4 ^ m4_e_G4_mul4_G16_inv0_G256_inv0_4;
  m4_ab_G4_mul5_G16_inv0_G256_inv0_0 = i16_e1_G16_inv0_G256_inv0_0 ^ i16_e0_G16_inv0_G256_inv0_0;
  m4_ab_G4_mul5_G16_inv0_G256_inv0_1 = i16_e1_G16_inv0_G256_inv0_1 ^ i16_e0_G16_inv0_G256_inv0_1;
  m4_ab_G4_mul5_G16_inv0_G256_inv0_2 = i16_e1_G16_inv0_G256_inv0_2 ^ i16_e0_G16_inv0_G256_inv0_2;
  m4_ab_G4_mul5_G16_inv0_G256_inv0_3 = i16_e1_G16_inv0_G256_inv0_3 ^ i16_e0_G16_inv0_G256_inv0_3;
  m4_ab_G4_mul5_G16_inv0_G256_inv0_4 = i16_e1_G16_inv0_G256_inv0_4 ^ i16_e0_G16_inv0_G256_inv0_4;
  m4_cd_G4_mul5_G16_inv0_G256_inv0_0 = i256_te3_G256_inv0_0 ^ i256_te2_G256_inv0_0;
  m4_cd_G4_mul5_G16_inv0_G256_inv0_1 = i256_te3_G256_inv0_1 ^ i256_te2_G256_inv0_1;
  m4_cd_G4_mul5_G16_inv0_G256_inv0_2 = i256_te3_G256_inv0_2 ^ i256_te2_G256_inv0_2;
  m4_cd_G4_mul5_G16_inv0_G256_inv0_3 = i256_te3_G256_inv0_3 ^ i256_te2_G256_inv0_3;
  m4_cd_G4_mul5_G16_inv0_G256_inv0_4 = i256_te3_G256_inv0_4 ^ i256_te2_G256_inv0_4;
  HPC2(m4_ab_G4_mul5_G16_inv0_G256_inv0_0, m4_ab_G4_mul5_G16_inv0_G256_inv0_1, m4_ab_G4_mul5_G16_inv0_G256_inv0_2, m4_ab_G4_mul5_G16_inv0_G256_inv0_3, m4_ab_G4_mul5_G16_inv0_G256_inv0_4, m4_cd_G4_mul5_G16_inv0_G256_inv0_0, m4_cd_G4_mul5_G16_inv0_G256_inv0_1, m4_cd_G4_mul5_G16_inv0_G256_inv0_2, m4_cd_G4_mul5_G16_inv0_G256_inv0_3, m4_cd_G4_mul5_G16_inv0_G256_inv0_4, &m4_e_G4_mul5_G16_inv0_G256_inv0_0, &m4_e_G4_mul5_G16_inv0_G256_inv0_1, &m4_e_G4_mul5_G16_inv0_G256_inv0_2, &m4_e_G4_mul5_G16_inv0_G256_inv0_3, &m4_e_G4_mul5_G16_inv0_G256_inv0_4, rand_181, rand_182, rand_183, rand_184, rand_185, rand_186, rand_187, rand_188, rand_189, rand_190);
  HPC2(i16_e1_G16_inv0_G256_inv0_0, i16_e1_G16_inv0_G256_inv0_1, i16_e1_G16_inv0_G256_inv0_2, i16_e1_G16_inv0_G256_inv0_3, i16_e1_G16_inv0_G256_inv0_4, i256_te3_G256_inv0_0, i256_te3_G256_inv0_1, i256_te3_G256_inv0_2, i256_te3_G256_inv0_3, i256_te3_G256_inv0_4, &temp_var_0_G4_mul5_G16_inv0_G256_inv0_0, &temp_var_0_G4_mul5_G16_inv0_G256_inv0_1, &temp_var_0_G4_mul5_G16_inv0_G256_inv0_2, &temp_var_0_G4_mul5_G16_inv0_G256_inv0_3, &temp_var_0_G4_mul5_G16_inv0_G256_inv0_4, rand_191, rand_192, rand_193, rand_194, rand_195, rand_196, rand_197, rand_198, rand_199, rand_200);
  i16_ql1_G16_inv0_G256_inv0_0 = temp_var_0_G4_mul5_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_0;
  i16_ql1_G16_inv0_G256_inv0_1 = temp_var_0_G4_mul5_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_1;
  i16_ql1_G16_inv0_G256_inv0_2 = temp_var_0_G4_mul5_G16_inv0_G256_inv0_2 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_2;
  i16_ql1_G16_inv0_G256_inv0_3 = temp_var_0_G4_mul5_G16_inv0_G256_inv0_3 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_3;
  i16_ql1_G16_inv0_G256_inv0_4 = temp_var_0_G4_mul5_G16_inv0_G256_inv0_4 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_4;
  HPC2(i16_e0_G16_inv0_G256_inv0_0, i16_e0_G16_inv0_G256_inv0_1, i16_e0_G16_inv0_G256_inv0_2, i16_e0_G16_inv0_G256_inv0_3, i16_e0_G16_inv0_G256_inv0_4, i256_te2_G256_inv0_0, i256_te2_G256_inv0_1, i256_te2_G256_inv0_2, i256_te2_G256_inv0_3, i256_te2_G256_inv0_4, &temp_var_1_G4_mul5_G16_inv0_G256_inv0_0, &temp_var_1_G4_mul5_G16_inv0_G256_inv0_1, &temp_var_1_G4_mul5_G16_inv0_G256_inv0_2, &temp_var_1_G4_mul5_G16_inv0_G256_inv0_3, &temp_var_1_G4_mul5_G16_inv0_G256_inv0_4, rand_201, rand_202, rand_203, rand_204, rand_205, rand_206, rand_207, rand_208, rand_209, rand_210);
  i16_ql0_G16_inv0_G256_inv0_0 = temp_var_1_G4_mul5_G16_inv0_G256_inv0_0 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_0;
  i16_ql0_G16_inv0_G256_inv0_1 = temp_var_1_G4_mul5_G16_inv0_G256_inv0_1 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_1;
  i16_ql0_G16_inv0_G256_inv0_2 = temp_var_1_G4_mul5_G16_inv0_G256_inv0_2 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_2;
  i16_ql0_G16_inv0_G256_inv0_3 = temp_var_1_G4_mul5_G16_inv0_G256_inv0_3 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_3;
  i16_ql0_G16_inv0_G256_inv0_4 = temp_var_1_G4_mul5_G16_inv0_G256_inv0_4 ^ m4_e_G4_mul5_G16_inv0_G256_inv0_4;
  i256_e3_G256_inv0_0 = i16_ph1_G16_inv0_G256_inv0_0;
  i256_e3_G256_inv0_1 = i16_ph1_G16_inv0_G256_inv0_1;
  i256_e3_G256_inv0_2 = i16_ph1_G16_inv0_G256_inv0_2;
  i256_e3_G256_inv0_3 = i16_ph1_G16_inv0_G256_inv0_3;
  i256_e3_G256_inv0_4 = i16_ph1_G16_inv0_G256_inv0_4;
  i256_e2_G256_inv0_0 = i16_ph0_G16_inv0_G256_inv0_0;
  i256_e2_G256_inv0_1 = i16_ph0_G16_inv0_G256_inv0_1;
  i256_e2_G256_inv0_2 = i16_ph0_G16_inv0_G256_inv0_2;
  i256_e2_G256_inv0_3 = i16_ph0_G16_inv0_G256_inv0_3;
  i256_e2_G256_inv0_4 = i16_ph0_G16_inv0_G256_inv0_4;
  i256_e1_G256_inv0_0 = i16_ql1_G16_inv0_G256_inv0_0;
  i256_e1_G256_inv0_1 = i16_ql1_G16_inv0_G256_inv0_1;
  i256_e1_G256_inv0_2 = i16_ql1_G16_inv0_G256_inv0_2;
  i256_e1_G256_inv0_3 = i16_ql1_G16_inv0_G256_inv0_3;
  i256_e1_G256_inv0_4 = i16_ql1_G16_inv0_G256_inv0_4;
  i256_e0_G256_inv0_0 = i16_ql0_G16_inv0_G256_inv0_0;
  i256_e0_G256_inv0_1 = i16_ql0_G16_inv0_G256_inv0_1;
  i256_e0_G256_inv0_2 = i16_ql0_G16_inv0_G256_inv0_2;
  i256_e0_G256_inv0_3 = i16_ql0_G16_inv0_G256_inv0_3;
  i256_e0_G256_inv0_4 = i16_ql0_G16_inv0_G256_inv0_4;
  m16_tx0_G16_mul1_G256_inv0_0 = i256_e2_G256_inv0_0 ^ i256_e0_G256_inv0_0;
  m16_tx0_G16_mul1_G256_inv0_1 = i256_e2_G256_inv0_1 ^ i256_e0_G256_inv0_1;
  m16_tx0_G16_mul1_G256_inv0_2 = i256_e2_G256_inv0_2 ^ i256_e0_G256_inv0_2;
  m16_tx0_G16_mul1_G256_inv0_3 = i256_e2_G256_inv0_3 ^ i256_e0_G256_inv0_3;
  m16_tx0_G16_mul1_G256_inv0_4 = i256_e2_G256_inv0_4 ^ i256_e0_G256_inv0_4;
  m16_tx1_G16_mul1_G256_inv0_0 = i256_e3_G256_inv0_0 ^ i256_e1_G256_inv0_0;
  m16_tx1_G16_mul1_G256_inv0_1 = i256_e3_G256_inv0_1 ^ i256_e1_G256_inv0_1;
  m16_tx1_G16_mul1_G256_inv0_2 = i256_e3_G256_inv0_2 ^ i256_e1_G256_inv0_2;
  m16_tx1_G16_mul1_G256_inv0_3 = i256_e3_G256_inv0_3 ^ i256_e1_G256_inv0_3;
  m16_tx1_G16_mul1_G256_inv0_4 = i256_e3_G256_inv0_4 ^ i256_e1_G256_inv0_4;
  m16_ty0_G16_mul1_G256_inv0_0 = sb_y2_0 ^ sb_y0_0;
  m16_ty0_G16_mul1_G256_inv0_1 = sb_y2_1 ^ sb_y0_1;
  m16_ty0_G16_mul1_G256_inv0_2 = sb_y2_2 ^ sb_y0_2;
  m16_ty0_G16_mul1_G256_inv0_3 = sb_y2_3 ^ sb_y0_3;
  m16_ty0_G16_mul1_G256_inv0_4 = sb_y2_4 ^ sb_y0_4;
  m16_ty1_G16_mul1_G256_inv0_0 = sb_y3_0 ^ sb_y1_0;
  m16_ty1_G16_mul1_G256_inv0_1 = sb_y3_1 ^ sb_y1_1;
  m16_ty1_G16_mul1_G256_inv0_2 = sb_y3_2 ^ sb_y1_2;
  m16_ty1_G16_mul1_G256_inv0_3 = sb_y3_3 ^ sb_y1_3;
  m16_ty1_G16_mul1_G256_inv0_4 = sb_y3_4 ^ sb_y1_4;
  m4_ab_G4_mul0_G16_mul1_G256_inv0_0 = m16_tx1_G16_mul1_G256_inv0_0 ^ m16_tx0_G16_mul1_G256_inv0_0;
  m4_ab_G4_mul0_G16_mul1_G256_inv0_1 = m16_tx1_G16_mul1_G256_inv0_1 ^ m16_tx0_G16_mul1_G256_inv0_1;
  m4_ab_G4_mul0_G16_mul1_G256_inv0_2 = m16_tx1_G16_mul1_G256_inv0_2 ^ m16_tx0_G16_mul1_G256_inv0_2;
  m4_ab_G4_mul0_G16_mul1_G256_inv0_3 = m16_tx1_G16_mul1_G256_inv0_3 ^ m16_tx0_G16_mul1_G256_inv0_3;
  m4_ab_G4_mul0_G16_mul1_G256_inv0_4 = m16_tx1_G16_mul1_G256_inv0_4 ^ m16_tx0_G16_mul1_G256_inv0_4;
  m4_cd_G4_mul0_G16_mul1_G256_inv0_0 = m16_ty1_G16_mul1_G256_inv0_0 ^ m16_ty0_G16_mul1_G256_inv0_0;
  m4_cd_G4_mul0_G16_mul1_G256_inv0_1 = m16_ty1_G16_mul1_G256_inv0_1 ^ m16_ty0_G16_mul1_G256_inv0_1;
  m4_cd_G4_mul0_G16_mul1_G256_inv0_2 = m16_ty1_G16_mul1_G256_inv0_2 ^ m16_ty0_G16_mul1_G256_inv0_2;
  m4_cd_G4_mul0_G16_mul1_G256_inv0_3 = m16_ty1_G16_mul1_G256_inv0_3 ^ m16_ty0_G16_mul1_G256_inv0_3;
  m4_cd_G4_mul0_G16_mul1_G256_inv0_4 = m16_ty1_G16_mul1_G256_inv0_4 ^ m16_ty0_G16_mul1_G256_inv0_4;
  HPC2(m4_ab_G4_mul0_G16_mul1_G256_inv0_0, m4_ab_G4_mul0_G16_mul1_G256_inv0_1, m4_ab_G4_mul0_G16_mul1_G256_inv0_2, m4_ab_G4_mul0_G16_mul1_G256_inv0_3, m4_ab_G4_mul0_G16_mul1_G256_inv0_4, m4_cd_G4_mul0_G16_mul1_G256_inv0_0, m4_cd_G4_mul0_G16_mul1_G256_inv0_1, m4_cd_G4_mul0_G16_mul1_G256_inv0_2, m4_cd_G4_mul0_G16_mul1_G256_inv0_3, m4_cd_G4_mul0_G16_mul1_G256_inv0_4, &m4_e_G4_mul0_G16_mul1_G256_inv0_0, &m4_e_G4_mul0_G16_mul1_G256_inv0_1, &m4_e_G4_mul0_G16_mul1_G256_inv0_2, &m4_e_G4_mul0_G16_mul1_G256_inv0_3, &m4_e_G4_mul0_G16_mul1_G256_inv0_4, rand_211, rand_212, rand_213, rand_214, rand_215, rand_216, rand_217, rand_218, rand_219, rand_220);
  HPC2(m16_tx1_G16_mul1_G256_inv0_0, m16_tx1_G16_mul1_G256_inv0_1, m16_tx1_G16_mul1_G256_inv0_2, m16_tx1_G16_mul1_G256_inv0_3, m16_tx1_G16_mul1_G256_inv0_4, m16_ty1_G16_mul1_G256_inv0_0, m16_ty1_G16_mul1_G256_inv0_1, m16_ty1_G16_mul1_G256_inv0_2, m16_ty1_G16_mul1_G256_inv0_3, m16_ty1_G16_mul1_G256_inv0_4, &temp_var_0_G4_mul0_G16_mul1_G256_inv0_0, &temp_var_0_G4_mul0_G16_mul1_G256_inv0_1, &temp_var_0_G4_mul0_G16_mul1_G256_inv0_2, &temp_var_0_G4_mul0_G16_mul1_G256_inv0_3, &temp_var_0_G4_mul0_G16_mul1_G256_inv0_4, rand_221, rand_222, rand_223, rand_224, rand_225, rand_226, rand_227, rand_228, rand_229, rand_230);
  m16_e1_s1_G16_mul1_G256_inv0_0 = temp_var_0_G4_mul0_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_0;
  m16_e1_s1_G16_mul1_G256_inv0_1 = temp_var_0_G4_mul0_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_1;
  m16_e1_s1_G16_mul1_G256_inv0_2 = temp_var_0_G4_mul0_G16_mul1_G256_inv0_2 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_2;
  m16_e1_s1_G16_mul1_G256_inv0_3 = temp_var_0_G4_mul0_G16_mul1_G256_inv0_3 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_3;
  m16_e1_s1_G16_mul1_G256_inv0_4 = temp_var_0_G4_mul0_G16_mul1_G256_inv0_4 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_4;
  HPC2(m16_tx0_G16_mul1_G256_inv0_0, m16_tx0_G16_mul1_G256_inv0_1, m16_tx0_G16_mul1_G256_inv0_2, m16_tx0_G16_mul1_G256_inv0_3, m16_tx0_G16_mul1_G256_inv0_4, m16_ty0_G16_mul1_G256_inv0_0, m16_ty0_G16_mul1_G256_inv0_1, m16_ty0_G16_mul1_G256_inv0_2, m16_ty0_G16_mul1_G256_inv0_3, m16_ty0_G16_mul1_G256_inv0_4, &temp_var_1_G4_mul0_G16_mul1_G256_inv0_0, &temp_var_1_G4_mul0_G16_mul1_G256_inv0_1, &temp_var_1_G4_mul0_G16_mul1_G256_inv0_2, &temp_var_1_G4_mul0_G16_mul1_G256_inv0_3, &temp_var_1_G4_mul0_G16_mul1_G256_inv0_4, rand_231, rand_232, rand_233, rand_234, rand_235, rand_236, rand_237, rand_238, rand_239, rand_240);
  m16_e0_s1_G16_mul1_G256_inv0_0 = temp_var_1_G4_mul0_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_0;
  m16_e0_s1_G16_mul1_G256_inv0_1 = temp_var_1_G4_mul0_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_1;
  m16_e0_s1_G16_mul1_G256_inv0_2 = temp_var_1_G4_mul0_G16_mul1_G256_inv0_2 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_2;
  m16_e0_s1_G16_mul1_G256_inv0_3 = temp_var_1_G4_mul0_G16_mul1_G256_inv0_3 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_3;
  m16_e0_s1_G16_mul1_G256_inv0_4 = temp_var_1_G4_mul0_G16_mul1_G256_inv0_4 ^ m4_e_G4_mul0_G16_mul1_G256_inv0_4;
  m16_e1_s2_G16_mul1_G256_inv0_0 = m16_e0_s1_G16_mul1_G256_inv0_0;
  m16_e1_s2_G16_mul1_G256_inv0_1 = m16_e0_s1_G16_mul1_G256_inv0_1;
  m16_e1_s2_G16_mul1_G256_inv0_2 = m16_e0_s1_G16_mul1_G256_inv0_2;
  m16_e1_s2_G16_mul1_G256_inv0_3 = m16_e0_s1_G16_mul1_G256_inv0_3;
  m16_e1_s2_G16_mul1_G256_inv0_4 = m16_e0_s1_G16_mul1_G256_inv0_4;
  m16_e0_s2_G16_mul1_G256_inv0_0 = m16_e1_s1_G16_mul1_G256_inv0_0 ^ m16_e0_s1_G16_mul1_G256_inv0_0;
  m16_e0_s2_G16_mul1_G256_inv0_1 = m16_e1_s1_G16_mul1_G256_inv0_1 ^ m16_e0_s1_G16_mul1_G256_inv0_1;
  m16_e0_s2_G16_mul1_G256_inv0_2 = m16_e1_s1_G16_mul1_G256_inv0_2 ^ m16_e0_s1_G16_mul1_G256_inv0_2;
  m16_e0_s2_G16_mul1_G256_inv0_3 = m16_e1_s1_G16_mul1_G256_inv0_3 ^ m16_e0_s1_G16_mul1_G256_inv0_3;
  m16_e0_s2_G16_mul1_G256_inv0_4 = m16_e1_s1_G16_mul1_G256_inv0_4 ^ m16_e0_s1_G16_mul1_G256_inv0_4;
  m4_ab_G4_mul1_G16_mul1_G256_inv0_0 = i256_e3_G256_inv0_0 ^ i256_e2_G256_inv0_0;
  m4_ab_G4_mul1_G16_mul1_G256_inv0_1 = i256_e3_G256_inv0_1 ^ i256_e2_G256_inv0_1;
  m4_ab_G4_mul1_G16_mul1_G256_inv0_2 = i256_e3_G256_inv0_2 ^ i256_e2_G256_inv0_2;
  m4_ab_G4_mul1_G16_mul1_G256_inv0_3 = i256_e3_G256_inv0_3 ^ i256_e2_G256_inv0_3;
  m4_ab_G4_mul1_G16_mul1_G256_inv0_4 = i256_e3_G256_inv0_4 ^ i256_e2_G256_inv0_4;
  m4_cd_G4_mul1_G16_mul1_G256_inv0_0 = sb_y3_0 ^ sb_y2_0;
  m4_cd_G4_mul1_G16_mul1_G256_inv0_1 = sb_y3_1 ^ sb_y2_1;
  m4_cd_G4_mul1_G16_mul1_G256_inv0_2 = sb_y3_2 ^ sb_y2_2;
  m4_cd_G4_mul1_G16_mul1_G256_inv0_3 = sb_y3_3 ^ sb_y2_3;
  m4_cd_G4_mul1_G16_mul1_G256_inv0_4 = sb_y3_4 ^ sb_y2_4;
  HPC2(m4_ab_G4_mul1_G16_mul1_G256_inv0_0, m4_ab_G4_mul1_G16_mul1_G256_inv0_1, m4_ab_G4_mul1_G16_mul1_G256_inv0_2, m4_ab_G4_mul1_G16_mul1_G256_inv0_3, m4_ab_G4_mul1_G16_mul1_G256_inv0_4, m4_cd_G4_mul1_G16_mul1_G256_inv0_0, m4_cd_G4_mul1_G16_mul1_G256_inv0_1, m4_cd_G4_mul1_G16_mul1_G256_inv0_2, m4_cd_G4_mul1_G16_mul1_G256_inv0_3, m4_cd_G4_mul1_G16_mul1_G256_inv0_4, &m4_e_G4_mul1_G16_mul1_G256_inv0_0, &m4_e_G4_mul1_G16_mul1_G256_inv0_1, &m4_e_G4_mul1_G16_mul1_G256_inv0_2, &m4_e_G4_mul1_G16_mul1_G256_inv0_3, &m4_e_G4_mul1_G16_mul1_G256_inv0_4, rand_241, rand_242, rand_243, rand_244, rand_245, rand_246, rand_247, rand_248, rand_249, rand_250);
  HPC2(i256_e3_G256_inv0_0, i256_e3_G256_inv0_1, i256_e3_G256_inv0_2, i256_e3_G256_inv0_3, i256_e3_G256_inv0_4, sb_y3_0, sb_y3_1, sb_y3_2, sb_y3_3, sb_y3_4, &temp_var_0_G4_mul1_G16_mul1_G256_inv0_0, &temp_var_0_G4_mul1_G16_mul1_G256_inv0_1, &temp_var_0_G4_mul1_G16_mul1_G256_inv0_2, &temp_var_0_G4_mul1_G16_mul1_G256_inv0_3, &temp_var_0_G4_mul1_G16_mul1_G256_inv0_4, rand_251, rand_252, rand_253, rand_254, rand_255, rand_256, rand_257, rand_258, rand_259, rand_260);
  m16_ph1_G16_mul1_G256_inv0_0 = temp_var_0_G4_mul1_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_0;
  m16_ph1_G16_mul1_G256_inv0_1 = temp_var_0_G4_mul1_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_1;
  m16_ph1_G16_mul1_G256_inv0_2 = temp_var_0_G4_mul1_G16_mul1_G256_inv0_2 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_2;
  m16_ph1_G16_mul1_G256_inv0_3 = temp_var_0_G4_mul1_G16_mul1_G256_inv0_3 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_3;
  m16_ph1_G16_mul1_G256_inv0_4 = temp_var_0_G4_mul1_G16_mul1_G256_inv0_4 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_4;
  HPC2(i256_e2_G256_inv0_0, i256_e2_G256_inv0_1, i256_e2_G256_inv0_2, i256_e2_G256_inv0_3, i256_e2_G256_inv0_4, sb_y2_0, sb_y2_1, sb_y2_2, sb_y2_3, sb_y2_4, &temp_var_1_G4_mul1_G16_mul1_G256_inv0_0, &temp_var_1_G4_mul1_G16_mul1_G256_inv0_1, &temp_var_1_G4_mul1_G16_mul1_G256_inv0_2, &temp_var_1_G4_mul1_G16_mul1_G256_inv0_3, &temp_var_1_G4_mul1_G16_mul1_G256_inv0_4, rand_261, rand_262, rand_263, rand_264, rand_265, rand_266, rand_267, rand_268, rand_269, rand_270);
  m16_ph0_G16_mul1_G256_inv0_0 = temp_var_1_G4_mul1_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_0;
  m16_ph0_G16_mul1_G256_inv0_1 = temp_var_1_G4_mul1_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_1;
  m16_ph0_G16_mul1_G256_inv0_2 = temp_var_1_G4_mul1_G16_mul1_G256_inv0_2 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_2;
  m16_ph0_G16_mul1_G256_inv0_3 = temp_var_1_G4_mul1_G16_mul1_G256_inv0_3 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_3;
  m16_ph0_G16_mul1_G256_inv0_4 = temp_var_1_G4_mul1_G16_mul1_G256_inv0_4 ^ m4_e_G4_mul1_G16_mul1_G256_inv0_4;
  m4_ab_G4_mul2_G16_mul1_G256_inv0_0 = i256_e1_G256_inv0_0 ^ i256_e0_G256_inv0_0;
  m4_ab_G4_mul2_G16_mul1_G256_inv0_1 = i256_e1_G256_inv0_1 ^ i256_e0_G256_inv0_1;
  m4_ab_G4_mul2_G16_mul1_G256_inv0_2 = i256_e1_G256_inv0_2 ^ i256_e0_G256_inv0_2;
  m4_ab_G4_mul2_G16_mul1_G256_inv0_3 = i256_e1_G256_inv0_3 ^ i256_e0_G256_inv0_3;
  m4_ab_G4_mul2_G16_mul1_G256_inv0_4 = i256_e1_G256_inv0_4 ^ i256_e0_G256_inv0_4;
  m4_cd_G4_mul2_G16_mul1_G256_inv0_0 = sb_y1_0 ^ sb_y0_0;
  m4_cd_G4_mul2_G16_mul1_G256_inv0_1 = sb_y1_1 ^ sb_y0_1;
  m4_cd_G4_mul2_G16_mul1_G256_inv0_2 = sb_y1_2 ^ sb_y0_2;
  m4_cd_G4_mul2_G16_mul1_G256_inv0_3 = sb_y1_3 ^ sb_y0_3;
  m4_cd_G4_mul2_G16_mul1_G256_inv0_4 = sb_y1_4 ^ sb_y0_4;
  HPC2(m4_ab_G4_mul2_G16_mul1_G256_inv0_0, m4_ab_G4_mul2_G16_mul1_G256_inv0_1, m4_ab_G4_mul2_G16_mul1_G256_inv0_2, m4_ab_G4_mul2_G16_mul1_G256_inv0_3, m4_ab_G4_mul2_G16_mul1_G256_inv0_4, m4_cd_G4_mul2_G16_mul1_G256_inv0_0, m4_cd_G4_mul2_G16_mul1_G256_inv0_1, m4_cd_G4_mul2_G16_mul1_G256_inv0_2, m4_cd_G4_mul2_G16_mul1_G256_inv0_3, m4_cd_G4_mul2_G16_mul1_G256_inv0_4, &m4_e_G4_mul2_G16_mul1_G256_inv0_0, &m4_e_G4_mul2_G16_mul1_G256_inv0_1, &m4_e_G4_mul2_G16_mul1_G256_inv0_2, &m4_e_G4_mul2_G16_mul1_G256_inv0_3, &m4_e_G4_mul2_G16_mul1_G256_inv0_4, rand_271, rand_272, rand_273, rand_274, rand_275, rand_276, rand_277, rand_278, rand_279, rand_280);
  HPC2(i256_e1_G256_inv0_0, i256_e1_G256_inv0_1, i256_e1_G256_inv0_2, i256_e1_G256_inv0_3, i256_e1_G256_inv0_4, sb_y1_0, sb_y1_1, sb_y1_2, sb_y1_3, sb_y1_4, &temp_var_0_G4_mul2_G16_mul1_G256_inv0_0, &temp_var_0_G4_mul2_G16_mul1_G256_inv0_1, &temp_var_0_G4_mul2_G16_mul1_G256_inv0_2, &temp_var_0_G4_mul2_G16_mul1_G256_inv0_3, &temp_var_0_G4_mul2_G16_mul1_G256_inv0_4, rand_281, rand_282, rand_283, rand_284, rand_285, rand_286, rand_287, rand_288, rand_289, rand_290);
  m16_ql1_G16_mul1_G256_inv0_0 = temp_var_0_G4_mul2_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_0;
  m16_ql1_G16_mul1_G256_inv0_1 = temp_var_0_G4_mul2_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_1;
  m16_ql1_G16_mul1_G256_inv0_2 = temp_var_0_G4_mul2_G16_mul1_G256_inv0_2 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_2;
  m16_ql1_G16_mul1_G256_inv0_3 = temp_var_0_G4_mul2_G16_mul1_G256_inv0_3 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_3;
  m16_ql1_G16_mul1_G256_inv0_4 = temp_var_0_G4_mul2_G16_mul1_G256_inv0_4 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_4;
  HPC2(i256_e0_G256_inv0_0, i256_e0_G256_inv0_1, i256_e0_G256_inv0_2, i256_e0_G256_inv0_3, i256_e0_G256_inv0_4, sb_y0_0, sb_y0_1, sb_y0_2, sb_y0_3, sb_y0_4, &temp_var_1_G4_mul2_G16_mul1_G256_inv0_0, &temp_var_1_G4_mul2_G16_mul1_G256_inv0_1, &temp_var_1_G4_mul2_G16_mul1_G256_inv0_2, &temp_var_1_G4_mul2_G16_mul1_G256_inv0_3, &temp_var_1_G4_mul2_G16_mul1_G256_inv0_4, rand_291, rand_292, rand_293, rand_294, rand_295, rand_296, rand_297, rand_298, rand_299, rand_300);
  m16_ql0_G16_mul1_G256_inv0_0 = temp_var_1_G4_mul2_G16_mul1_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_0;
  m16_ql0_G16_mul1_G256_inv0_1 = temp_var_1_G4_mul2_G16_mul1_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_1;
  m16_ql0_G16_mul1_G256_inv0_2 = temp_var_1_G4_mul2_G16_mul1_G256_inv0_2 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_2;
  m16_ql0_G16_mul1_G256_inv0_3 = temp_var_1_G4_mul2_G16_mul1_G256_inv0_3 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_3;
  m16_ql0_G16_mul1_G256_inv0_4 = temp_var_1_G4_mul2_G16_mul1_G256_inv0_4 ^ m4_e_G4_mul2_G16_mul1_G256_inv0_4;
  i256_ph3_G256_inv0_0 = m16_ph1_G16_mul1_G256_inv0_0 ^ m16_e1_s2_G16_mul1_G256_inv0_0;
  i256_ph3_G256_inv0_1 = m16_ph1_G16_mul1_G256_inv0_1 ^ m16_e1_s2_G16_mul1_G256_inv0_1;
  i256_ph3_G256_inv0_2 = m16_ph1_G16_mul1_G256_inv0_2 ^ m16_e1_s2_G16_mul1_G256_inv0_2;
  i256_ph3_G256_inv0_3 = m16_ph1_G16_mul1_G256_inv0_3 ^ m16_e1_s2_G16_mul1_G256_inv0_3;
  i256_ph3_G256_inv0_4 = m16_ph1_G16_mul1_G256_inv0_4 ^ m16_e1_s2_G16_mul1_G256_inv0_4;
  i256_ph2_G256_inv0_0 = m16_ph0_G16_mul1_G256_inv0_0 ^ m16_e0_s2_G16_mul1_G256_inv0_0;
  i256_ph2_G256_inv0_1 = m16_ph0_G16_mul1_G256_inv0_1 ^ m16_e0_s2_G16_mul1_G256_inv0_1;
  i256_ph2_G256_inv0_2 = m16_ph0_G16_mul1_G256_inv0_2 ^ m16_e0_s2_G16_mul1_G256_inv0_2;
  i256_ph2_G256_inv0_3 = m16_ph0_G16_mul1_G256_inv0_3 ^ m16_e0_s2_G16_mul1_G256_inv0_3;
  i256_ph2_G256_inv0_4 = m16_ph0_G16_mul1_G256_inv0_4 ^ m16_e0_s2_G16_mul1_G256_inv0_4;
  i256_ph1_G256_inv0_0 = m16_ql1_G16_mul1_G256_inv0_0 ^ m16_e1_s2_G16_mul1_G256_inv0_0;
  i256_ph1_G256_inv0_1 = m16_ql1_G16_mul1_G256_inv0_1 ^ m16_e1_s2_G16_mul1_G256_inv0_1;
  i256_ph1_G256_inv0_2 = m16_ql1_G16_mul1_G256_inv0_2 ^ m16_e1_s2_G16_mul1_G256_inv0_2;
  i256_ph1_G256_inv0_3 = m16_ql1_G16_mul1_G256_inv0_3 ^ m16_e1_s2_G16_mul1_G256_inv0_3;
  i256_ph1_G256_inv0_4 = m16_ql1_G16_mul1_G256_inv0_4 ^ m16_e1_s2_G16_mul1_G256_inv0_4;
  i256_ph0_G256_inv0_0 = m16_ql0_G16_mul1_G256_inv0_0 ^ m16_e0_s2_G16_mul1_G256_inv0_0;
  i256_ph0_G256_inv0_1 = m16_ql0_G16_mul1_G256_inv0_1 ^ m16_e0_s2_G16_mul1_G256_inv0_1;
  i256_ph0_G256_inv0_2 = m16_ql0_G16_mul1_G256_inv0_2 ^ m16_e0_s2_G16_mul1_G256_inv0_2;
  i256_ph0_G256_inv0_3 = m16_ql0_G16_mul1_G256_inv0_3 ^ m16_e0_s2_G16_mul1_G256_inv0_3;
  i256_ph0_G256_inv0_4 = m16_ql0_G16_mul1_G256_inv0_4 ^ m16_e0_s2_G16_mul1_G256_inv0_4;
  m16_tx0_G16_mul2_G256_inv0_0 = i256_e2_G256_inv0_0 ^ i256_e0_G256_inv0_0;
  m16_tx0_G16_mul2_G256_inv0_1 = i256_e2_G256_inv0_1 ^ i256_e0_G256_inv0_1;
  m16_tx0_G16_mul2_G256_inv0_2 = i256_e2_G256_inv0_2 ^ i256_e0_G256_inv0_2;
  m16_tx0_G16_mul2_G256_inv0_3 = i256_e2_G256_inv0_3 ^ i256_e0_G256_inv0_3;
  m16_tx0_G16_mul2_G256_inv0_4 = i256_e2_G256_inv0_4 ^ i256_e0_G256_inv0_4;
  m16_tx1_G16_mul2_G256_inv0_0 = i256_e3_G256_inv0_0 ^ i256_e1_G256_inv0_0;
  m16_tx1_G16_mul2_G256_inv0_1 = i256_e3_G256_inv0_1 ^ i256_e1_G256_inv0_1;
  m16_tx1_G16_mul2_G256_inv0_2 = i256_e3_G256_inv0_2 ^ i256_e1_G256_inv0_2;
  m16_tx1_G16_mul2_G256_inv0_3 = i256_e3_G256_inv0_3 ^ i256_e1_G256_inv0_3;
  m16_tx1_G16_mul2_G256_inv0_4 = i256_e3_G256_inv0_4 ^ i256_e1_G256_inv0_4;
  m16_ty0_G16_mul2_G256_inv0_0 = sb_y6_0 ^ sb_y4_0;
  m16_ty0_G16_mul2_G256_inv0_1 = sb_y6_1 ^ sb_y4_1;
  m16_ty0_G16_mul2_G256_inv0_2 = sb_y6_2 ^ sb_y4_2;
  m16_ty0_G16_mul2_G256_inv0_3 = sb_y6_3 ^ sb_y4_3;
  m16_ty0_G16_mul2_G256_inv0_4 = sb_y6_4 ^ sb_y4_4;
  m16_ty1_G16_mul2_G256_inv0_0 = sb_y7_0 ^ sb_y5_0;
  m16_ty1_G16_mul2_G256_inv0_1 = sb_y7_1 ^ sb_y5_1;
  m16_ty1_G16_mul2_G256_inv0_2 = sb_y7_2 ^ sb_y5_2;
  m16_ty1_G16_mul2_G256_inv0_3 = sb_y7_3 ^ sb_y5_3;
  m16_ty1_G16_mul2_G256_inv0_4 = sb_y7_4 ^ sb_y5_4;
  m4_ab_G4_mul0_G16_mul2_G256_inv0_0 = m16_tx1_G16_mul2_G256_inv0_0 ^ m16_tx0_G16_mul2_G256_inv0_0;
  m4_ab_G4_mul0_G16_mul2_G256_inv0_1 = m16_tx1_G16_mul2_G256_inv0_1 ^ m16_tx0_G16_mul2_G256_inv0_1;
  m4_ab_G4_mul0_G16_mul2_G256_inv0_2 = m16_tx1_G16_mul2_G256_inv0_2 ^ m16_tx0_G16_mul2_G256_inv0_2;
  m4_ab_G4_mul0_G16_mul2_G256_inv0_3 = m16_tx1_G16_mul2_G256_inv0_3 ^ m16_tx0_G16_mul2_G256_inv0_3;
  m4_ab_G4_mul0_G16_mul2_G256_inv0_4 = m16_tx1_G16_mul2_G256_inv0_4 ^ m16_tx0_G16_mul2_G256_inv0_4;
  m4_cd_G4_mul0_G16_mul2_G256_inv0_0 = m16_ty1_G16_mul2_G256_inv0_0 ^ m16_ty0_G16_mul2_G256_inv0_0;
  m4_cd_G4_mul0_G16_mul2_G256_inv0_1 = m16_ty1_G16_mul2_G256_inv0_1 ^ m16_ty0_G16_mul2_G256_inv0_1;
  m4_cd_G4_mul0_G16_mul2_G256_inv0_2 = m16_ty1_G16_mul2_G256_inv0_2 ^ m16_ty0_G16_mul2_G256_inv0_2;
  m4_cd_G4_mul0_G16_mul2_G256_inv0_3 = m16_ty1_G16_mul2_G256_inv0_3 ^ m16_ty0_G16_mul2_G256_inv0_3;
  m4_cd_G4_mul0_G16_mul2_G256_inv0_4 = m16_ty1_G16_mul2_G256_inv0_4 ^ m16_ty0_G16_mul2_G256_inv0_4;
  HPC2(m4_ab_G4_mul0_G16_mul2_G256_inv0_0, m4_ab_G4_mul0_G16_mul2_G256_inv0_1, m4_ab_G4_mul0_G16_mul2_G256_inv0_2, m4_ab_G4_mul0_G16_mul2_G256_inv0_3, m4_ab_G4_mul0_G16_mul2_G256_inv0_4, m4_cd_G4_mul0_G16_mul2_G256_inv0_0, m4_cd_G4_mul0_G16_mul2_G256_inv0_1, m4_cd_G4_mul0_G16_mul2_G256_inv0_2, m4_cd_G4_mul0_G16_mul2_G256_inv0_3, m4_cd_G4_mul0_G16_mul2_G256_inv0_4, &m4_e_G4_mul0_G16_mul2_G256_inv0_0, &m4_e_G4_mul0_G16_mul2_G256_inv0_1, &m4_e_G4_mul0_G16_mul2_G256_inv0_2, &m4_e_G4_mul0_G16_mul2_G256_inv0_3, &m4_e_G4_mul0_G16_mul2_G256_inv0_4, rand_301, rand_302, rand_303, rand_304, rand_305, rand_306, rand_307, rand_308, rand_309, rand_310);
  HPC2(m16_tx1_G16_mul2_G256_inv0_0, m16_tx1_G16_mul2_G256_inv0_1, m16_tx1_G16_mul2_G256_inv0_2, m16_tx1_G16_mul2_G256_inv0_3, m16_tx1_G16_mul2_G256_inv0_4, m16_ty1_G16_mul2_G256_inv0_0, m16_ty1_G16_mul2_G256_inv0_1, m16_ty1_G16_mul2_G256_inv0_2, m16_ty1_G16_mul2_G256_inv0_3, m16_ty1_G16_mul2_G256_inv0_4, &temp_var_0_G4_mul0_G16_mul2_G256_inv0_0, &temp_var_0_G4_mul0_G16_mul2_G256_inv0_1, &temp_var_0_G4_mul0_G16_mul2_G256_inv0_2, &temp_var_0_G4_mul0_G16_mul2_G256_inv0_3, &temp_var_0_G4_mul0_G16_mul2_G256_inv0_4, rand_311, rand_312, rand_313, rand_314, rand_315, rand_316, rand_317, rand_318, rand_319, rand_320);
  m16_e1_s1_G16_mul2_G256_inv0_0 = temp_var_0_G4_mul0_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_0;
  m16_e1_s1_G16_mul2_G256_inv0_1 = temp_var_0_G4_mul0_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_1;
  m16_e1_s1_G16_mul2_G256_inv0_2 = temp_var_0_G4_mul0_G16_mul2_G256_inv0_2 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_2;
  m16_e1_s1_G16_mul2_G256_inv0_3 = temp_var_0_G4_mul0_G16_mul2_G256_inv0_3 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_3;
  m16_e1_s1_G16_mul2_G256_inv0_4 = temp_var_0_G4_mul0_G16_mul2_G256_inv0_4 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_4;
  HPC2(m16_tx0_G16_mul2_G256_inv0_0, m16_tx0_G16_mul2_G256_inv0_1, m16_tx0_G16_mul2_G256_inv0_2, m16_tx0_G16_mul2_G256_inv0_3, m16_tx0_G16_mul2_G256_inv0_4, m16_ty0_G16_mul2_G256_inv0_0, m16_ty0_G16_mul2_G256_inv0_1, m16_ty0_G16_mul2_G256_inv0_2, m16_ty0_G16_mul2_G256_inv0_3, m16_ty0_G16_mul2_G256_inv0_4, &temp_var_1_G4_mul0_G16_mul2_G256_inv0_0, &temp_var_1_G4_mul0_G16_mul2_G256_inv0_1, &temp_var_1_G4_mul0_G16_mul2_G256_inv0_2, &temp_var_1_G4_mul0_G16_mul2_G256_inv0_3, &temp_var_1_G4_mul0_G16_mul2_G256_inv0_4, rand_321, rand_322, rand_323, rand_324, rand_325, rand_326, rand_327, rand_328, rand_329, rand_330);
  m16_e0_s1_G16_mul2_G256_inv0_0 = temp_var_1_G4_mul0_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_0;
  m16_e0_s1_G16_mul2_G256_inv0_1 = temp_var_1_G4_mul0_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_1;
  m16_e0_s1_G16_mul2_G256_inv0_2 = temp_var_1_G4_mul0_G16_mul2_G256_inv0_2 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_2;
  m16_e0_s1_G16_mul2_G256_inv0_3 = temp_var_1_G4_mul0_G16_mul2_G256_inv0_3 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_3;
  m16_e0_s1_G16_mul2_G256_inv0_4 = temp_var_1_G4_mul0_G16_mul2_G256_inv0_4 ^ m4_e_G4_mul0_G16_mul2_G256_inv0_4;
  m16_e1_s2_G16_mul2_G256_inv0_0 = m16_e0_s1_G16_mul2_G256_inv0_0;
  m16_e1_s2_G16_mul2_G256_inv0_1 = m16_e0_s1_G16_mul2_G256_inv0_1;
  m16_e1_s2_G16_mul2_G256_inv0_2 = m16_e0_s1_G16_mul2_G256_inv0_2;
  m16_e1_s2_G16_mul2_G256_inv0_3 = m16_e0_s1_G16_mul2_G256_inv0_3;
  m16_e1_s2_G16_mul2_G256_inv0_4 = m16_e0_s1_G16_mul2_G256_inv0_4;
  m16_e0_s2_G16_mul2_G256_inv0_0 = m16_e1_s1_G16_mul2_G256_inv0_0 ^ m16_e0_s1_G16_mul2_G256_inv0_0;
  m16_e0_s2_G16_mul2_G256_inv0_1 = m16_e1_s1_G16_mul2_G256_inv0_1 ^ m16_e0_s1_G16_mul2_G256_inv0_1;
  m16_e0_s2_G16_mul2_G256_inv0_2 = m16_e1_s1_G16_mul2_G256_inv0_2 ^ m16_e0_s1_G16_mul2_G256_inv0_2;
  m16_e0_s2_G16_mul2_G256_inv0_3 = m16_e1_s1_G16_mul2_G256_inv0_3 ^ m16_e0_s1_G16_mul2_G256_inv0_3;
  m16_e0_s2_G16_mul2_G256_inv0_4 = m16_e1_s1_G16_mul2_G256_inv0_4 ^ m16_e0_s1_G16_mul2_G256_inv0_4;
  m4_ab_G4_mul1_G16_mul2_G256_inv0_0 = i256_e3_G256_inv0_0 ^ i256_e2_G256_inv0_0;
  m4_ab_G4_mul1_G16_mul2_G256_inv0_1 = i256_e3_G256_inv0_1 ^ i256_e2_G256_inv0_1;
  m4_ab_G4_mul1_G16_mul2_G256_inv0_2 = i256_e3_G256_inv0_2 ^ i256_e2_G256_inv0_2;
  m4_ab_G4_mul1_G16_mul2_G256_inv0_3 = i256_e3_G256_inv0_3 ^ i256_e2_G256_inv0_3;
  m4_ab_G4_mul1_G16_mul2_G256_inv0_4 = i256_e3_G256_inv0_4 ^ i256_e2_G256_inv0_4;
  m4_cd_G4_mul1_G16_mul2_G256_inv0_0 = sb_y7_0 ^ sb_y6_0;
  m4_cd_G4_mul1_G16_mul2_G256_inv0_1 = sb_y7_1 ^ sb_y6_1;
  m4_cd_G4_mul1_G16_mul2_G256_inv0_2 = sb_y7_2 ^ sb_y6_2;
  m4_cd_G4_mul1_G16_mul2_G256_inv0_3 = sb_y7_3 ^ sb_y6_3;
  m4_cd_G4_mul1_G16_mul2_G256_inv0_4 = sb_y7_4 ^ sb_y6_4;
  HPC2(m4_ab_G4_mul1_G16_mul2_G256_inv0_0, m4_ab_G4_mul1_G16_mul2_G256_inv0_1, m4_ab_G4_mul1_G16_mul2_G256_inv0_2, m4_ab_G4_mul1_G16_mul2_G256_inv0_3, m4_ab_G4_mul1_G16_mul2_G256_inv0_4, m4_cd_G4_mul1_G16_mul2_G256_inv0_0, m4_cd_G4_mul1_G16_mul2_G256_inv0_1, m4_cd_G4_mul1_G16_mul2_G256_inv0_2, m4_cd_G4_mul1_G16_mul2_G256_inv0_3, m4_cd_G4_mul1_G16_mul2_G256_inv0_4, &m4_e_G4_mul1_G16_mul2_G256_inv0_0, &m4_e_G4_mul1_G16_mul2_G256_inv0_1, &m4_e_G4_mul1_G16_mul2_G256_inv0_2, &m4_e_G4_mul1_G16_mul2_G256_inv0_3, &m4_e_G4_mul1_G16_mul2_G256_inv0_4, rand_331, rand_332, rand_333, rand_334, rand_335, rand_336, rand_337, rand_338, rand_339, rand_340);
  HPC2(i256_e3_G256_inv0_0, i256_e3_G256_inv0_1, i256_e3_G256_inv0_2, i256_e3_G256_inv0_3, i256_e3_G256_inv0_4, sb_y7_0, sb_y7_1, sb_y7_2, sb_y7_3, sb_y7_4, &temp_var_0_G4_mul1_G16_mul2_G256_inv0_0, &temp_var_0_G4_mul1_G16_mul2_G256_inv0_1, &temp_var_0_G4_mul1_G16_mul2_G256_inv0_2, &temp_var_0_G4_mul1_G16_mul2_G256_inv0_3, &temp_var_0_G4_mul1_G16_mul2_G256_inv0_4, rand_341, rand_342, rand_343, rand_344, rand_345, rand_346, rand_347, rand_348, rand_349, rand_350);
  m16_ph1_G16_mul2_G256_inv0_0 = temp_var_0_G4_mul1_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_0;
  m16_ph1_G16_mul2_G256_inv0_1 = temp_var_0_G4_mul1_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_1;
  m16_ph1_G16_mul2_G256_inv0_2 = temp_var_0_G4_mul1_G16_mul2_G256_inv0_2 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_2;
  m16_ph1_G16_mul2_G256_inv0_3 = temp_var_0_G4_mul1_G16_mul2_G256_inv0_3 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_3;
  m16_ph1_G16_mul2_G256_inv0_4 = temp_var_0_G4_mul1_G16_mul2_G256_inv0_4 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_4;
  HPC2(i256_e2_G256_inv0_0, i256_e2_G256_inv0_1, i256_e2_G256_inv0_2, i256_e2_G256_inv0_3, i256_e2_G256_inv0_4, sb_y6_0, sb_y6_1, sb_y6_2, sb_y6_3, sb_y6_4, &temp_var_1_G4_mul1_G16_mul2_G256_inv0_0, &temp_var_1_G4_mul1_G16_mul2_G256_inv0_1, &temp_var_1_G4_mul1_G16_mul2_G256_inv0_2, &temp_var_1_G4_mul1_G16_mul2_G256_inv0_3, &temp_var_1_G4_mul1_G16_mul2_G256_inv0_4, rand_351, rand_352, rand_353, rand_354, rand_355, rand_356, rand_357, rand_358, rand_359, rand_360);
  m16_ph0_G16_mul2_G256_inv0_0 = temp_var_1_G4_mul1_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_0;
  m16_ph0_G16_mul2_G256_inv0_1 = temp_var_1_G4_mul1_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_1;
  m16_ph0_G16_mul2_G256_inv0_2 = temp_var_1_G4_mul1_G16_mul2_G256_inv0_2 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_2;
  m16_ph0_G16_mul2_G256_inv0_3 = temp_var_1_G4_mul1_G16_mul2_G256_inv0_3 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_3;
  m16_ph0_G16_mul2_G256_inv0_4 = temp_var_1_G4_mul1_G16_mul2_G256_inv0_4 ^ m4_e_G4_mul1_G16_mul2_G256_inv0_4;
  m4_ab_G4_mul2_G16_mul2_G256_inv0_0 = i256_e1_G256_inv0_0 ^ i256_e0_G256_inv0_0;
  m4_ab_G4_mul2_G16_mul2_G256_inv0_1 = i256_e1_G256_inv0_1 ^ i256_e0_G256_inv0_1;
  m4_ab_G4_mul2_G16_mul2_G256_inv0_2 = i256_e1_G256_inv0_2 ^ i256_e0_G256_inv0_2;
  m4_ab_G4_mul2_G16_mul2_G256_inv0_3 = i256_e1_G256_inv0_3 ^ i256_e0_G256_inv0_3;
  m4_ab_G4_mul2_G16_mul2_G256_inv0_4 = i256_e1_G256_inv0_4 ^ i256_e0_G256_inv0_4;
  m4_cd_G4_mul2_G16_mul2_G256_inv0_0 = sb_y5_0 ^ sb_y4_0;
  m4_cd_G4_mul2_G16_mul2_G256_inv0_1 = sb_y5_1 ^ sb_y4_1;
  m4_cd_G4_mul2_G16_mul2_G256_inv0_2 = sb_y5_2 ^ sb_y4_2;
  m4_cd_G4_mul2_G16_mul2_G256_inv0_3 = sb_y5_3 ^ sb_y4_3;
  m4_cd_G4_mul2_G16_mul2_G256_inv0_4 = sb_y5_4 ^ sb_y4_4;
  HPC2(m4_ab_G4_mul2_G16_mul2_G256_inv0_0, m4_ab_G4_mul2_G16_mul2_G256_inv0_1, m4_ab_G4_mul2_G16_mul2_G256_inv0_2, m4_ab_G4_mul2_G16_mul2_G256_inv0_3, m4_ab_G4_mul2_G16_mul2_G256_inv0_4, m4_cd_G4_mul2_G16_mul2_G256_inv0_0, m4_cd_G4_mul2_G16_mul2_G256_inv0_1, m4_cd_G4_mul2_G16_mul2_G256_inv0_2, m4_cd_G4_mul2_G16_mul2_G256_inv0_3, m4_cd_G4_mul2_G16_mul2_G256_inv0_4, &m4_e_G4_mul2_G16_mul2_G256_inv0_0, &m4_e_G4_mul2_G16_mul2_G256_inv0_1, &m4_e_G4_mul2_G16_mul2_G256_inv0_2, &m4_e_G4_mul2_G16_mul2_G256_inv0_3, &m4_e_G4_mul2_G16_mul2_G256_inv0_4, rand_361, rand_362, rand_363, rand_364, rand_365, rand_366, rand_367, rand_368, rand_369, rand_370);
  HPC2(i256_e1_G256_inv0_0, i256_e1_G256_inv0_1, i256_e1_G256_inv0_2, i256_e1_G256_inv0_3, i256_e1_G256_inv0_4, sb_y5_0, sb_y5_1, sb_y5_2, sb_y5_3, sb_y5_4, &temp_var_0_G4_mul2_G16_mul2_G256_inv0_0, &temp_var_0_G4_mul2_G16_mul2_G256_inv0_1, &temp_var_0_G4_mul2_G16_mul2_G256_inv0_2, &temp_var_0_G4_mul2_G16_mul2_G256_inv0_3, &temp_var_0_G4_mul2_G16_mul2_G256_inv0_4, rand_371, rand_372, rand_373, rand_374, rand_375, rand_376, rand_377, rand_378, rand_379, rand_380);
  m16_ql1_G16_mul2_G256_inv0_0 = temp_var_0_G4_mul2_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_0;
  m16_ql1_G16_mul2_G256_inv0_1 = temp_var_0_G4_mul2_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_1;
  m16_ql1_G16_mul2_G256_inv0_2 = temp_var_0_G4_mul2_G16_mul2_G256_inv0_2 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_2;
  m16_ql1_G16_mul2_G256_inv0_3 = temp_var_0_G4_mul2_G16_mul2_G256_inv0_3 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_3;
  m16_ql1_G16_mul2_G256_inv0_4 = temp_var_0_G4_mul2_G16_mul2_G256_inv0_4 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_4;
  HPC2(i256_e0_G256_inv0_0, i256_e0_G256_inv0_1, i256_e0_G256_inv0_2, i256_e0_G256_inv0_3, i256_e0_G256_inv0_4, sb_y4_0, sb_y4_1, sb_y4_2, sb_y4_3, sb_y4_4, &temp_var_1_G4_mul2_G16_mul2_G256_inv0_0, &temp_var_1_G4_mul2_G16_mul2_G256_inv0_1, &temp_var_1_G4_mul2_G16_mul2_G256_inv0_2, &temp_var_1_G4_mul2_G16_mul2_G256_inv0_3, &temp_var_1_G4_mul2_G16_mul2_G256_inv0_4, rand_381, rand_382, rand_383, rand_384, rand_385, rand_386, rand_387, rand_388, rand_389, rand_390);
  m16_ql0_G16_mul2_G256_inv0_0 = temp_var_1_G4_mul2_G16_mul2_G256_inv0_0 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_0;
  m16_ql0_G16_mul2_G256_inv0_1 = temp_var_1_G4_mul2_G16_mul2_G256_inv0_1 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_1;
  m16_ql0_G16_mul2_G256_inv0_2 = temp_var_1_G4_mul2_G16_mul2_G256_inv0_2 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_2;
  m16_ql0_G16_mul2_G256_inv0_3 = temp_var_1_G4_mul2_G16_mul2_G256_inv0_3 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_3;
  m16_ql0_G16_mul2_G256_inv0_4 = temp_var_1_G4_mul2_G16_mul2_G256_inv0_4 ^ m4_e_G4_mul2_G16_mul2_G256_inv0_4;
  i256_ql3_G256_inv0_0 = m16_ph1_G16_mul2_G256_inv0_0 ^ m16_e1_s2_G16_mul2_G256_inv0_0;
  i256_ql3_G256_inv0_1 = m16_ph1_G16_mul2_G256_inv0_1 ^ m16_e1_s2_G16_mul2_G256_inv0_1;
  i256_ql3_G256_inv0_2 = m16_ph1_G16_mul2_G256_inv0_2 ^ m16_e1_s2_G16_mul2_G256_inv0_2;
  i256_ql3_G256_inv0_3 = m16_ph1_G16_mul2_G256_inv0_3 ^ m16_e1_s2_G16_mul2_G256_inv0_3;
  i256_ql3_G256_inv0_4 = m16_ph1_G16_mul2_G256_inv0_4 ^ m16_e1_s2_G16_mul2_G256_inv0_4;
  i256_ql2_G256_inv0_0 = m16_ph0_G16_mul2_G256_inv0_0 ^ m16_e0_s2_G16_mul2_G256_inv0_0;
  i256_ql2_G256_inv0_1 = m16_ph0_G16_mul2_G256_inv0_1 ^ m16_e0_s2_G16_mul2_G256_inv0_1;
  i256_ql2_G256_inv0_2 = m16_ph0_G16_mul2_G256_inv0_2 ^ m16_e0_s2_G16_mul2_G256_inv0_2;
  i256_ql2_G256_inv0_3 = m16_ph0_G16_mul2_G256_inv0_3 ^ m16_e0_s2_G16_mul2_G256_inv0_3;
  i256_ql2_G256_inv0_4 = m16_ph0_G16_mul2_G256_inv0_4 ^ m16_e0_s2_G16_mul2_G256_inv0_4;
  i256_ql1_G256_inv0_0 = m16_ql1_G16_mul2_G256_inv0_0 ^ m16_e1_s2_G16_mul2_G256_inv0_0;
  i256_ql1_G256_inv0_1 = m16_ql1_G16_mul2_G256_inv0_1 ^ m16_e1_s2_G16_mul2_G256_inv0_1;
  i256_ql1_G256_inv0_2 = m16_ql1_G16_mul2_G256_inv0_2 ^ m16_e1_s2_G16_mul2_G256_inv0_2;
  i256_ql1_G256_inv0_3 = m16_ql1_G16_mul2_G256_inv0_3 ^ m16_e1_s2_G16_mul2_G256_inv0_3;
  i256_ql1_G256_inv0_4 = m16_ql1_G16_mul2_G256_inv0_4 ^ m16_e1_s2_G16_mul2_G256_inv0_4;
  i256_ql0_G256_inv0_0 = m16_ql0_G16_mul2_G256_inv0_0 ^ m16_e0_s2_G16_mul2_G256_inv0_0;
  i256_ql0_G256_inv0_1 = m16_ql0_G16_mul2_G256_inv0_1 ^ m16_e0_s2_G16_mul2_G256_inv0_1;
  i256_ql0_G256_inv0_2 = m16_ql0_G16_mul2_G256_inv0_2 ^ m16_e0_s2_G16_mul2_G256_inv0_2;
  i256_ql0_G256_inv0_3 = m16_ql0_G16_mul2_G256_inv0_3 ^ m16_e0_s2_G16_mul2_G256_inv0_3;
  i256_ql0_G256_inv0_4 = m16_ql0_G16_mul2_G256_inv0_4 ^ m16_e0_s2_G16_mul2_G256_inv0_4;
  sb_i7_0 = i256_ph3_G256_inv0_0;
  sb_i7_1 = i256_ph3_G256_inv0_1;
  sb_i7_2 = i256_ph3_G256_inv0_2;
  sb_i7_3 = i256_ph3_G256_inv0_3;
  sb_i7_4 = i256_ph3_G256_inv0_4;
  sb_i6_0 = i256_ph2_G256_inv0_0;
  sb_i6_1 = i256_ph2_G256_inv0_1;
  sb_i6_2 = i256_ph2_G256_inv0_2;
  sb_i6_3 = i256_ph2_G256_inv0_3;
  sb_i6_4 = i256_ph2_G256_inv0_4;
  sb_i5_0 = i256_ph1_G256_inv0_0;
  sb_i5_1 = i256_ph1_G256_inv0_1;
  sb_i5_2 = i256_ph1_G256_inv0_2;
  sb_i5_3 = i256_ph1_G256_inv0_3;
  sb_i5_4 = i256_ph1_G256_inv0_4;
  sb_i4_0 = i256_ph0_G256_inv0_0;
  sb_i4_1 = i256_ph0_G256_inv0_1;
  sb_i4_2 = i256_ph0_G256_inv0_2;
  sb_i4_3 = i256_ph0_G256_inv0_3;
  sb_i4_4 = i256_ph0_G256_inv0_4;
  sb_i3_0 = i256_ql3_G256_inv0_0;
  sb_i3_1 = i256_ql3_G256_inv0_1;
  sb_i3_2 = i256_ql3_G256_inv0_2;
  sb_i3_3 = i256_ql3_G256_inv0_3;
  sb_i3_4 = i256_ql3_G256_inv0_4;
  sb_i2_0 = i256_ql2_G256_inv0_0;
  sb_i2_1 = i256_ql2_G256_inv0_1;
  sb_i2_2 = i256_ql2_G256_inv0_2;
  sb_i2_3 = i256_ql2_G256_inv0_3;
  sb_i2_4 = i256_ql2_G256_inv0_4;
  sb_i1_0 = i256_ql1_G256_inv0_0;
  sb_i1_1 = i256_ql1_G256_inv0_1;
  sb_i1_2 = i256_ql1_G256_inv0_2;
  sb_i1_3 = i256_ql1_G256_inv0_3;
  sb_i1_4 = i256_ql1_G256_inv0_4;
  sb_i0_0 = i256_ql0_G256_inv0_0;
  sb_i0_1 = i256_ql0_G256_inv0_1;
  sb_i0_2 = i256_ql0_G256_inv0_2;
  sb_i0_3 = i256_ql0_G256_inv0_3;
  sb_i0_4 = i256_ql0_G256_inv0_4;
  _Bool temp_var_17_0;
  _Bool temp_var_17_1;
  _Bool temp_var_17_2;
  _Bool temp_var_17_3;
  _Bool temp_var_17_4;
  temp_var_17_0 = sb_i1_0 ^ sb_i4_0;
  temp_var_17_1 = sb_i1_1 ^ sb_i4_1;
  temp_var_17_2 = sb_i1_2 ^ sb_i4_2;
  temp_var_17_3 = sb_i1_3 ^ sb_i4_3;
  temp_var_17_4 = sb_i1_4 ^ sb_i4_4;
  fy0_0 = temp_var_17_0 ^ sb_i6_0;
  fy0_1 = temp_var_17_1 ^ sb_i6_1;
  fy0_2 = temp_var_17_2 ^ sb_i6_2;
  fy0_3 = temp_var_17_3 ^ sb_i6_3;
  fy0_4 = temp_var_17_4 ^ sb_i6_4;
  _Bool temp_var_18_0;
  _Bool temp_var_18_1;
  _Bool temp_var_18_2;
  _Bool temp_var_18_3;
  _Bool temp_var_18_4;
  temp_var_18_0 = sb_i1_0 ^ sb_i4_0;
  temp_var_18_1 = sb_i1_1 ^ sb_i4_1;
  temp_var_18_2 = sb_i1_2 ^ sb_i4_2;
  temp_var_18_3 = sb_i1_3 ^ sb_i4_3;
  temp_var_18_4 = sb_i1_4 ^ sb_i4_4;
  fy1_0 = temp_var_18_0 ^ sb_i5_0;
  fy1_1 = temp_var_18_1 ^ sb_i5_1;
  fy1_2 = temp_var_18_2 ^ sb_i5_2;
  fy1_3 = temp_var_18_3 ^ sb_i5_3;
  fy1_4 = temp_var_18_4 ^ sb_i5_4;
  _Bool temp_var_19_0;
  _Bool temp_var_19_1;
  _Bool temp_var_19_2;
  _Bool temp_var_19_3;
  _Bool temp_var_19_4;
  temp_var_19_0 = sb_i0_0 ^ sb_i2_0;
  temp_var_19_1 = sb_i0_1 ^ sb_i2_1;
  temp_var_19_2 = sb_i0_2 ^ sb_i2_2;
  temp_var_19_3 = sb_i0_3 ^ sb_i2_3;
  temp_var_19_4 = sb_i0_4 ^ sb_i2_4;
  _Bool temp_var_20_0;
  _Bool temp_var_20_1;
  _Bool temp_var_20_2;
  _Bool temp_var_20_3;
  _Bool temp_var_20_4;
  temp_var_20_0 = temp_var_19_0 ^ sb_i3_0;
  temp_var_20_1 = temp_var_19_1 ^ sb_i3_1;
  temp_var_20_2 = temp_var_19_2 ^ sb_i3_2;
  temp_var_20_3 = temp_var_19_3 ^ sb_i3_3;
  temp_var_20_4 = temp_var_19_4 ^ sb_i3_4;
  _Bool temp_var_21_0;
  _Bool temp_var_21_1;
  _Bool temp_var_21_2;
  _Bool temp_var_21_3;
  _Bool temp_var_21_4;
  temp_var_21_0 = temp_var_20_0 ^ sb_i5_0;
  temp_var_21_1 = temp_var_20_1 ^ sb_i5_1;
  temp_var_21_2 = temp_var_20_2 ^ sb_i5_2;
  temp_var_21_3 = temp_var_20_3 ^ sb_i5_3;
  temp_var_21_4 = temp_var_20_4 ^ sb_i5_4;
  fy2_0 = temp_var_21_0 ^ sb_i6_0;
  fy2_1 = temp_var_21_1 ^ sb_i6_1;
  fy2_2 = temp_var_21_2 ^ sb_i6_2;
  fy2_3 = temp_var_21_3 ^ sb_i6_3;
  fy2_4 = temp_var_21_4 ^ sb_i6_4;
  _Bool temp_var_22_0;
  _Bool temp_var_22_1;
  _Bool temp_var_22_2;
  _Bool temp_var_22_3;
  _Bool temp_var_22_4;
  temp_var_22_0 = sb_i3_0 ^ sb_i4_0;
  temp_var_22_1 = sb_i3_1 ^ sb_i4_1;
  temp_var_22_2 = sb_i3_2 ^ sb_i4_2;
  temp_var_22_3 = sb_i3_3 ^ sb_i4_3;
  temp_var_22_4 = sb_i3_4 ^ sb_i4_4;
  _Bool temp_var_23_0;
  _Bool temp_var_23_1;
  _Bool temp_var_23_2;
  _Bool temp_var_23_3;
  _Bool temp_var_23_4;
  temp_var_23_0 = temp_var_22_0 ^ sb_i5_0;
  temp_var_23_1 = temp_var_22_1 ^ sb_i5_1;
  temp_var_23_2 = temp_var_22_2 ^ sb_i5_2;
  temp_var_23_3 = temp_var_22_3 ^ sb_i5_3;
  temp_var_23_4 = temp_var_22_4 ^ sb_i5_4;
  _Bool temp_var_24_0;
  _Bool temp_var_24_1;
  _Bool temp_var_24_2;
  _Bool temp_var_24_3;
  _Bool temp_var_24_4;
  temp_var_24_0 = temp_var_23_0 ^ sb_i6_0;
  temp_var_24_1 = temp_var_23_1 ^ sb_i6_1;
  temp_var_24_2 = temp_var_23_2 ^ sb_i6_2;
  temp_var_24_3 = temp_var_23_3 ^ sb_i6_3;
  temp_var_24_4 = temp_var_23_4 ^ sb_i6_4;
  fy3_0 = temp_var_24_0 ^ sb_i7_0;
  fy3_1 = temp_var_24_1 ^ sb_i7_1;
  fy3_2 = temp_var_24_2 ^ sb_i7_2;
  fy3_3 = temp_var_24_3 ^ sb_i7_3;
  fy3_4 = temp_var_24_4 ^ sb_i7_4;
  _Bool temp_var_25_0;
  _Bool temp_var_25_1;
  _Bool temp_var_25_2;
  _Bool temp_var_25_3;
  _Bool temp_var_25_4;
  temp_var_25_0 = sb_i3_0 ^ sb_i5_0;
  temp_var_25_1 = sb_i3_1 ^ sb_i5_1;
  temp_var_25_2 = sb_i3_2 ^ sb_i5_2;
  temp_var_25_3 = sb_i3_3 ^ sb_i5_3;
  temp_var_25_4 = sb_i3_4 ^ sb_i5_4;
  fy4_0 = temp_var_25_0 ^ sb_i7_0;
  fy4_1 = temp_var_25_1 ^ sb_i7_1;
  fy4_2 = temp_var_25_2 ^ sb_i7_2;
  fy4_3 = temp_var_25_3 ^ sb_i7_3;
  fy4_4 = temp_var_25_4 ^ sb_i7_4;
  fy5_0 = sb_i0_0 ^ sb_i6_0;
  fy5_1 = sb_i0_1 ^ sb_i6_1;
  fy5_2 = sb_i0_2 ^ sb_i6_2;
  fy5_3 = sb_i0_3 ^ sb_i6_3;
  fy5_4 = sb_i0_4 ^ sb_i6_4;
  fy6_0 = sb_i3_0 ^ sb_i7_0;
  fy6_1 = sb_i3_1 ^ sb_i7_1;
  fy6_2 = sb_i3_2 ^ sb_i7_2;
  fy6_3 = sb_i3_3 ^ sb_i7_3;
  fy6_4 = sb_i3_4 ^ sb_i7_4;
  fy7_0 = sb_i3_0 ^ sb_i5_0;
  fy7_1 = sb_i3_1 ^ sb_i5_1;
  fy7_2 = sb_i3_2 ^ sb_i5_2;
  fy7_3 = sb_i3_3 ^ sb_i5_3;
  fy7_4 = sb_i3_4 ^ sb_i5_4;
  *sb_o0_0 = fy0_0;
  *sb_o0_1 = fy0_1;
  *sb_o0_2 = fy0_2;
  *sb_o0_3 = fy0_3;
  *sb_o0_4 = !fy0_4;
  *sb_o1_0 = fy1_0;
  *sb_o1_1 = fy1_1;
  *sb_o1_2 = fy1_2;
  *sb_o1_3 = fy1_3;
  *sb_o1_4 = !fy1_4;
  *sb_o2_0 = fy2_0;
  *sb_o2_1 = fy2_1;
  *sb_o2_2 = fy2_2;
  *sb_o2_3 = fy2_3;
  *sb_o2_4 = fy2_4;
  *sb_o3_0 = fy3_0;
  *sb_o3_1 = fy3_1;
  *sb_o3_2 = fy3_2;
  *sb_o3_3 = fy3_3;
  *sb_o3_4 = fy3_4;
  *sb_o4_0 = fy4_0;
  *sb_o4_1 = fy4_1;
  *sb_o4_2 = fy4_2;
  *sb_o4_3 = fy4_3;
  *sb_o4_4 = fy4_4;
  *sb_o5_0 = fy5_0;
  *sb_o5_1 = fy5_1;
  *sb_o5_2 = fy5_2;
  *sb_o5_3 = fy5_3;
  *sb_o5_4 = !fy5_4;
  *sb_o6_0 = fy6_0;
  *sb_o6_1 = fy6_1;
  *sb_o6_2 = fy6_2;
  *sb_o6_3 = fy6_3;
  *sb_o6_4 = !fy6_4;
  *sb_o7_0 = fy7_0;
  *sb_o7_1 = fy7_1;
  *sb_o7_2 = fy7_2;
  *sb_o7_3 = fy7_3;
  *sb_o7_4 = fy7_4;
}

