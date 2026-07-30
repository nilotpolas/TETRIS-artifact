/* HPC1 Function Definition */

void hpc1_same_shares_1_order(_Bool a_share, _Bool b_share, _Bool rand, _Bool * v_share) {
    _Bool b_share_;
    b_share_ = reg(b_share ^ rand);
    *v_share  = a_share & b_share_;
}

void hpc1_cross_domain_1_order(_Bool a_share, _Bool b_share, _Bool * v_share, _Bool rand, _Bool prand){
    _Bool b_share_;
    b_share_ = reg(b_share ^ rand);
    _Bool a_and_b;
    a_and_b = a_share & b_share_;
    *v_share = a_and_b ^ prand;
}

void HPC1(_Bool a0, _Bool a1, _Bool b0, _Bool b1, int* c0, int* c1, _Bool rand_0, _Bool prand_01){
		_Bool v00, v01, v10, v11;
		_Bool r1 = rand_0;
		hpc1_same_shares_1_order(a0, b0, rand_0, &v00);
		hpc1_cross_domain_1_order(a0, b1, &v01, r1, prand_01);
		hpc1_cross_domain_1_order(a1, b0, &v10, rand_0, prand_01);
		hpc1_same_shares_1_order(a1, b1, r1, &v11);
		*c0 = reg(v00 ^ v01);
		*c1 = reg(v10 ^ v11);
}