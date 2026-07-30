/* HPC1 Function Definition */

void hpc1_same_shares_1_order(int a_share, int b_share, int rand, int * v_share) {
    int b_share_;
    b_share_ = reg(b_share ^ rand);
    *v_share  = a_share & b_share_;
}

void hpc1_cross_domain_1_order(int a_share, int b_share, int * v_share, int rand, int prand){
    int b_share_;
    b_share_ = reg(b_share ^ rand);
    int a_and_b;
    a_and_b = a_share & b_share_;
    *v_share = a_and_b ^ prand;
}

void HPC1(int a0, int a1, int b0, int b1, int* c0, int* c1, int rand_0, int prand_01){
		int v00, v01, v10, v11;
		hpc1_same_shares_1_order(a0, b0, rand_0, &v00);
		hpc1_cross_domain_1_order(a0, b1, &v01, rand_0, prand_01);
		hpc1_cross_domain_1_order(a1, b0, &v10, rand_0, prand_01);
		hpc1_same_shares_1_order(a1, b1, rand_0, &v11);
		*c0 = reg(v00 ^ v01);
		*c1 = reg(v10 ^ v11);
}


