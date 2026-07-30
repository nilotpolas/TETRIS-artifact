void hpc1_same_shares_5_order(int a_share, int b_share, int rand, int * v_share) {
    int b_share_;
    b_share_ = reg(b_share ^ rand);
    *v_share  = a_share & b_share_;
}

void hpc1_cross_domain_5_order(int a_share, int b_share, int * v_share, int rand, int prand){
    int b_share_;
    b_share_ = reg(b_share ^ rand);
    int a_and_b;
    a_and_b = a_share & b_share_;
    *v_share = a_and_b ^ prand;
}

void HPC1(int a0, int a1, int a2, int a3, int a4, int a5, int b0, int b1, int b2, int b3, int b4, int b5, int* c0, int* c1, int* c2, int* c3, int* c4, int* c5, int rand_0, int rand_1, int rand_2, int rand_3, int rand_4, int prand_01, int prand_02, int prand_03, int prand_04, int prand_05, int prand_12, int prand_13, int prand_14, int prand_15, int prand_23, int prand_24, int prand_25, int prand_34, int prand_35, int prand_45){
                int v00, v01, v02, v03, v04, v05, v10, v11, v12, v13, v14, v15, v20, v21, v22, v23, v24, v25, v30, v31, v32, v33, v34, v35, v40, v41, v42, v43, v44, v45, v50, v51, v52, v53, v54, v55;
                int r5 = rand_0 ^ rand_1 ^ rand_2 ^ rand_3 ^ rand_4;
                hpc1_same_shares_5_order(a0, b0, rand_0, &v00);
                hpc1_cross_domain_5_order(a0, b1, &v01, rand_1, prand_01);
                hpc1_cross_domain_5_order(a0, b2, &v02, rand_2, prand_02);
                hpc1_cross_domain_5_order(a0, b3, &v03, rand_3, prand_03);
                hpc1_cross_domain_5_order(a0, b4, &v04, rand_4, prand_04);
                hpc1_cross_domain_5_order(a0, b5, &v05, r5, prand_05);
                hpc1_cross_domain_5_order(a1, b0, &v10, rand_0, prand_01);
                hpc1_same_shares_5_order(a1, b1, rand_1, &v11);
                hpc1_cross_domain_5_order(a1, b2, &v12, rand_2, prand_12);
                hpc1_cross_domain_5_order(a1, b3, &v13, rand_3, prand_13);
                hpc1_cross_domain_5_order(a1, b4, &v14, rand_4, prand_14);
                hpc1_cross_domain_5_order(a1, b5, &v15, r5, prand_15);
                hpc1_cross_domain_5_order(a2, b0, &v20, rand_0, prand_02);
                hpc1_cross_domain_5_order(a2, b1, &v21, rand_1, prand_12);
                hpc1_same_shares_5_order(a2, b2, rand_2, &v22);
                hpc1_cross_domain_5_order(a2, b3, &v23, rand_3, prand_23);
                hpc1_cross_domain_5_order(a2, b4, &v24, rand_4, prand_24);
                hpc1_cross_domain_5_order(a2, b5, &v25, r5, prand_25);
                hpc1_cross_domain_5_order(a3, b0, &v30, rand_0, prand_03);
                hpc1_cross_domain_5_order(a3, b1, &v31, rand_1, prand_13);
                hpc1_cross_domain_5_order(a3, b2, &v32, rand_2, prand_23);
                hpc1_same_shares_5_order(a3, b3, rand_3, &v33);
                hpc1_cross_domain_5_order(a3, b4, &v34, rand_4, prand_34);
                hpc1_cross_domain_5_order(a3, b5, &v35, r5, prand_35);
                hpc1_cross_domain_5_order(a4, b0, &v40, rand_0, prand_04);
                hpc1_cross_domain_5_order(a4, b1, &v41, rand_1, prand_14);
                hpc1_cross_domain_5_order(a4, b2, &v42, rand_2, prand_24);
                hpc1_cross_domain_5_order(a4, b3, &v43, rand_3, prand_34);
                hpc1_same_shares_5_order(a4, b4, rand_4, &v44);
                hpc1_cross_domain_5_order(a4, b5, &v45, r5, prand_45);
                hpc1_cross_domain_5_order(a5, b0, &v50, rand_0, prand_05);
                hpc1_cross_domain_5_order(a5, b1, &v51, rand_1, prand_15);
                hpc1_cross_domain_5_order(a5, b2, &v52, rand_2, prand_25);
                hpc1_cross_domain_5_order(a5, b3, &v53, rand_3, prand_35);
                hpc1_cross_domain_5_order(a5, b4, &v54, rand_4, prand_45);
                hpc1_same_shares_5_order(a5, b5, r5, &v55);

                int t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23;

                t0 = v00 ^ v01;
                t1 = t0 ^ v02;
                t2 = t1 ^ v03;
                t3 = t2 ^ v04;
                *c0 = reg(t3 ^ v05);

                t4 = v10 ^ v11;
                t5 = t4 ^ v12;
                t6 = t5 ^ v13;
                t7 = t6 ^ v14;
                *c1 = reg(t7 ^ v15);

                t8 = v20 ^ v21;
                t9 = t8 ^ v22;
                t10 = t9 ^ v23;
                t11 = t10 ^ v24;
                *c2 = reg(t11 ^ v25);

                t12 = v30 ^ v31;
                t13 = t12 ^ v32;
                t14 = t13 ^ v33;
                t15 = t14 ^ v34;
                *c3 = reg(t15 ^ v35);

                t16 = v40 ^ v41;
                t17 = t16 ^ v42;
                t18 = t17 ^ v43;
                t19 = t18 ^ v44;
                *c4 = reg(t19 ^ v45);

                t20 = v50 ^ v51;
                t21 = t20 ^ v52;
                t22 = t21 ^ v53;
                t23 = t22 ^ v54;
                *c5 = reg(t23 ^ v55);

}