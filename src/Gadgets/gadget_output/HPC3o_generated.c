/* HPC3O Function Definition */

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