/* HPC2O Function Definition */

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