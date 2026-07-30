module HPC1(
    clk,
    a0,
    a1,
    a2,
    a3,
    a4,
    a5,
    b0,
    b1,
    b2,
    b3,
    b4,
    b5,
    rand_0,
    rand_1,
    rand_2,
    rand_3,
    rand_4,
    prand_01,
    prand_02,
    prand_03,
    prand_04,
    prand_05,
    prand_12,
    prand_13,
    prand_14,
    prand_15,
    prand_23,
    prand_24,
    prand_25,
    prand_34,
    prand_35,
    prand_45,
    c0,
    c1,
    c2,
    c3,
    c4,
    c5
);
//INPUTS
    input clk;
    input  [7:0] a0;
    input  [7:0] a1;
    input  [7:0] a2;
    input  [7:0] a3;
    input  [7:0] a4;
    input  [7:0] a5;
    input  [7:0] b0;
    input  [7:0] b1;
    input  [7:0] b2;
    input  [7:0] b3;
    input  [7:0] b4;
    input  [7:0] b5;
    input  [7:0] rand_0;
    input  [7:0] rand_1;
    input  [7:0] rand_2;
    input  [7:0] rand_3;
    input  [7:0] rand_4;
    input  [7:0] prand_01;
    input  [7:0] prand_02;
    input  [7:0] prand_03;
    input  [7:0] prand_04;
    input  [7:0] prand_05;
    input  [7:0] prand_12;
    input  [7:0] prand_13;
    input  [7:0] prand_14;
    input  [7:0] prand_15;
    input  [7:0] prand_23;
    input  [7:0] prand_24;
    input  [7:0] prand_25;
    input  [7:0] prand_34;
    input  [7:0] prand_35;
    input  [7:0] prand_45;
//OUTPUTS
    output reg  [7:0] c0;
    output reg  [7:0] c1;
    output reg  [7:0] c2;
    output reg  [7:0] c3;
    output reg  [7:0] c4;
    output reg  [7:0] c5;
//Intermediate values
    wire [7:0] a0_inp;
    wire [7:0] a1_inp;
    wire [7:0] a2_inp;
    wire [7:0] a3_inp;
    wire [7:0] a4_inp;
    wire [7:0] a5_inp;
    wire [7:0] b0_inp;
    wire [7:0] b1_inp;
    wire [7:0] b2_inp;
    wire [7:0] b3_inp;
    wire [7:0] b4_inp;
    wire [7:0] b5_inp;
    wire [7:0] rand_0_inp;
    wire [7:0] rand_1_inp;
    wire [7:0] rand_2_inp;
    wire [7:0] rand_3_inp;
    wire [7:0] rand_4_inp;
    wire [7:0] prand_01_inp;
    wire [7:0] prand_02_inp;
    wire [7:0] prand_03_inp;
    wire [7:0] prand_04_inp;
    wire [7:0] prand_05_inp;
    wire [7:0] prand_12_inp;
    wire [7:0] prand_13_inp;
    wire [7:0] prand_14_inp;
    wire [7:0] prand_15_inp;
    wire [7:0] prand_23_inp;
    wire [7:0] prand_24_inp;
    wire [7:0] prand_25_inp;
    wire [7:0] prand_34_inp;
    wire [7:0] prand_35_inp;
    wire [7:0] prand_45_inp;
    wire [7:0] r5;
    reg [7:0] b_share__hpc1_same_shares_5_order0;
    reg [7:0] a0_inp_reg;
    wire [7:0] v00;
    reg [7:0] b_share__hpc1_cross_domain_5_order0;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order0;
    reg [7:0] prand_01_inp_reg;
    wire [7:0] v01;
    reg [7:0] b_share__hpc1_cross_domain_5_order1;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order1;
    reg [7:0] prand_02_inp_reg;
    wire [7:0] v02;
    reg [7:0] b_share__hpc1_cross_domain_5_order2;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order2;
    reg [7:0] prand_03_inp_reg;
    wire [7:0] v03;
    reg [7:0] b_share__hpc1_cross_domain_5_order3;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order3;
    reg [7:0] prand_04_inp_reg;
    wire [7:0] v04;
    reg [7:0] b_share__hpc1_cross_domain_5_order4;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order4;
    reg [7:0] prand_05_inp_reg;
    wire [7:0] v05;
    reg [7:0] b_share__hpc1_cross_domain_5_order5;
    reg [7:0] a1_inp_reg;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order5;
    wire [7:0] v10;
    reg [7:0] b_share__hpc1_same_shares_5_order1;
    wire [7:0] v11;
    reg [7:0] b_share__hpc1_cross_domain_5_order6;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order6;
    reg [7:0] prand_12_inp_reg;
    wire [7:0] v12;
    reg [7:0] b_share__hpc1_cross_domain_5_order7;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order7;
    reg [7:0] prand_13_inp_reg;
    wire [7:0] v13;
    reg [7:0] b_share__hpc1_cross_domain_5_order8;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order8;
    reg [7:0] prand_14_inp_reg;
    wire [7:0] v14;
    reg [7:0] b_share__hpc1_cross_domain_5_order9;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order9;
    reg [7:0] prand_15_inp_reg;
    wire [7:0] v15;
    reg [7:0] b_share__hpc1_cross_domain_5_order10;
    reg [7:0] a2_inp_reg;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order10;
    wire [7:0] v20;
    reg [7:0] b_share__hpc1_cross_domain_5_order11;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order11;
    wire [7:0] v21;
    reg [7:0] b_share__hpc1_same_shares_5_order2;
    wire [7:0] v22;
    reg [7:0] b_share__hpc1_cross_domain_5_order12;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order12;
    reg [7:0] prand_23_inp_reg;
    wire [7:0] v23;
    reg [7:0] b_share__hpc1_cross_domain_5_order13;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order13;
    reg [7:0] prand_24_inp_reg;
    wire [7:0] v24;
    reg [7:0] b_share__hpc1_cross_domain_5_order14;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order14;
    reg [7:0] prand_25_inp_reg;
    wire [7:0] v25;
    reg [7:0] b_share__hpc1_cross_domain_5_order15;
    reg [7:0] a3_inp_reg;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order15;
    wire [7:0] v30;
    reg [7:0] b_share__hpc1_cross_domain_5_order16;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order16;
    wire [7:0] v31;
    reg [7:0] b_share__hpc1_cross_domain_5_order17;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order17;
    wire [7:0] v32;
    reg [7:0] b_share__hpc1_same_shares_5_order3;
    wire [7:0] v33;
    reg [7:0] b_share__hpc1_cross_domain_5_order18;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order18;
    reg [7:0] prand_34_inp_reg;
    wire [7:0] v34;
    reg [7:0] b_share__hpc1_cross_domain_5_order19;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order19;
    reg [7:0] prand_35_inp_reg;
    wire [7:0] v35;
    reg [7:0] b_share__hpc1_cross_domain_5_order20;
    reg [7:0] a4_inp_reg;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order20;
    wire [7:0] v40;
    reg [7:0] b_share__hpc1_cross_domain_5_order21;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order21;
    wire [7:0] v41;
    reg [7:0] b_share__hpc1_cross_domain_5_order22;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order22;
    wire [7:0] v42;
    reg [7:0] b_share__hpc1_cross_domain_5_order23;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order23;
    wire [7:0] v43;
    reg [7:0] b_share__hpc1_same_shares_5_order4;
    wire [7:0] v44;
    reg [7:0] b_share__hpc1_cross_domain_5_order24;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order24;
    reg [7:0] prand_45_inp_reg;
    wire [7:0] v45;
    reg [7:0] b_share__hpc1_cross_domain_5_order25;
    reg [7:0] a5_inp_reg;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order25;
    wire [7:0] v50;
    reg [7:0] b_share__hpc1_cross_domain_5_order26;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order26;
    wire [7:0] v51;
    reg [7:0] b_share__hpc1_cross_domain_5_order27;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order27;
    wire [7:0] v52;
    reg [7:0] b_share__hpc1_cross_domain_5_order28;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order28;
    wire [7:0] v53;
    reg [7:0] b_share__hpc1_cross_domain_5_order29;
    wire [7:0] a_and_b_hpc1_cross_domain_5_order29;
    wire [7:0] v54;
    reg [7:0] b_share__hpc1_same_shares_5_order5;
    wire [7:0] v55;
    wire [7:0] t0;
    wire [7:0] t1;
    wire [7:0] t2;
    wire [7:0] t3;
    wire [7:0] z605_assgn605;
    wire [7:0] t4;
    wire [7:0] t5;
    wire [7:0] t6;
    wire [7:0] t7;
    wire [7:0] z615_assgn615;
    wire [7:0] t8;
    wire [7:0] t9;
    wire [7:0] t10;
    wire [7:0] t11;
    wire [7:0] z625_assgn625;
    wire [7:0] t12;
    wire [7:0] t13;
    wire [7:0] t14;
    wire [7:0] t15;
    wire [7:0] z635_assgn635;
    wire [7:0] t16;
    wire [7:0] t17;
    wire [7:0] t18;
    wire [7:0] t19;
    wire [7:0] z645_assgn645;
    wire [7:0] t20;
    wire [7:0] t21;
    wire [7:0] t22;
    wire [7:0] t23;
    wire [7:0] z655_assgn655;

    assign a0_inp = a0;
    assign a1_inp = a1;
    assign a2_inp = a2;
    assign a3_inp = a3;
    assign a4_inp = a4;
    assign a5_inp = a5;
    assign b0_inp = b0;
    assign b1_inp = b1;
    assign b2_inp = b2;
    assign b3_inp = b3;
    assign b4_inp = b4;
    assign b5_inp = b5;
    assign rand_0_inp = rand_0;
    assign rand_1_inp = rand_1;
    assign rand_2_inp = rand_2;
    assign rand_3_inp = rand_3;
    assign rand_4_inp = rand_4;
    assign prand_01_inp = prand_01;
    assign prand_02_inp = prand_02;
    assign prand_03_inp = prand_03;
    assign prand_04_inp = prand_04;
    assign prand_05_inp = prand_05;
    assign prand_12_inp = prand_12;
    assign prand_13_inp = prand_13;
    assign prand_14_inp = prand_14;
    assign prand_15_inp = prand_15;
    assign prand_23_inp = prand_23;
    assign prand_24_inp = prand_24;
    assign prand_25_inp = prand_25;
    assign prand_34_inp = prand_34;
    assign prand_35_inp = prand_35;
    assign prand_45_inp = prand_45;
    assign r5 = ((((rand_0 ^ rand_1) ^ rand_2) ^ rand_3) ^ rand_4);
    assign v00 = (a0_inp_reg & b_share__hpc1_same_shares_5_order0);
    assign a_and_b_hpc1_cross_domain_5_order0 = (a0_inp_reg & b_share__hpc1_cross_domain_5_order0);
    assign v01 = (a_and_b_hpc1_cross_domain_5_order0 ^ prand_01_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order1 = (a0_inp_reg & b_share__hpc1_cross_domain_5_order1);
    assign v02 = (a_and_b_hpc1_cross_domain_5_order1 ^ prand_02_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order2 = (a0_inp_reg & b_share__hpc1_cross_domain_5_order2);
    assign v03 = (a_and_b_hpc1_cross_domain_5_order2 ^ prand_03_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order3 = (a0_inp_reg & b_share__hpc1_cross_domain_5_order3);
    assign v04 = (a_and_b_hpc1_cross_domain_5_order3 ^ prand_04_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order4 = (a0_inp_reg & b_share__hpc1_cross_domain_5_order4);
    assign v05 = (a_and_b_hpc1_cross_domain_5_order4 ^ prand_05_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order5 = (a1_inp_reg & b_share__hpc1_cross_domain_5_order5);
    assign v10 = (a_and_b_hpc1_cross_domain_5_order5 ^ prand_01_inp_reg);
    assign v11 = (a1_inp_reg & b_share__hpc1_same_shares_5_order1);
    assign a_and_b_hpc1_cross_domain_5_order6 = (a1_inp_reg & b_share__hpc1_cross_domain_5_order6);
    assign v12 = (a_and_b_hpc1_cross_domain_5_order6 ^ prand_12_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order7 = (a1_inp_reg & b_share__hpc1_cross_domain_5_order7);
    assign v13 = (a_and_b_hpc1_cross_domain_5_order7 ^ prand_13_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order8 = (a1_inp_reg & b_share__hpc1_cross_domain_5_order8);
    assign v14 = (a_and_b_hpc1_cross_domain_5_order8 ^ prand_14_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order9 = (a1_inp_reg & b_share__hpc1_cross_domain_5_order9);
    assign v15 = (a_and_b_hpc1_cross_domain_5_order9 ^ prand_15_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order10 = (a2_inp_reg & b_share__hpc1_cross_domain_5_order10);
    assign v20 = (a_and_b_hpc1_cross_domain_5_order10 ^ prand_02_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order11 = (a2_inp_reg & b_share__hpc1_cross_domain_5_order11);
    assign v21 = (a_and_b_hpc1_cross_domain_5_order11 ^ prand_12_inp_reg);
    assign v22 = (a2_inp_reg & b_share__hpc1_same_shares_5_order2);
    assign a_and_b_hpc1_cross_domain_5_order12 = (a2_inp_reg & b_share__hpc1_cross_domain_5_order12);
    assign v23 = (a_and_b_hpc1_cross_domain_5_order12 ^ prand_23_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order13 = (a2_inp_reg & b_share__hpc1_cross_domain_5_order13);
    assign v24 = (a_and_b_hpc1_cross_domain_5_order13 ^ prand_24_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order14 = (a2_inp_reg & b_share__hpc1_cross_domain_5_order14);
    assign v25 = (a_and_b_hpc1_cross_domain_5_order14 ^ prand_25_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order15 = (a3_inp_reg & b_share__hpc1_cross_domain_5_order15);
    assign v30 = (a_and_b_hpc1_cross_domain_5_order15 ^ prand_03_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order16 = (a3_inp_reg & b_share__hpc1_cross_domain_5_order16);
    assign v31 = (a_and_b_hpc1_cross_domain_5_order16 ^ prand_13_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order17 = (a3_inp_reg & b_share__hpc1_cross_domain_5_order17);
    assign v32 = (a_and_b_hpc1_cross_domain_5_order17 ^ prand_23_inp_reg);
    assign v33 = (a3_inp_reg & b_share__hpc1_same_shares_5_order3);
    assign a_and_b_hpc1_cross_domain_5_order18 = (a3_inp_reg & b_share__hpc1_cross_domain_5_order18);
    assign v34 = (a_and_b_hpc1_cross_domain_5_order18 ^ prand_34_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order19 = (a3_inp_reg & b_share__hpc1_cross_domain_5_order19);
    assign v35 = (a_and_b_hpc1_cross_domain_5_order19 ^ prand_35_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order20 = (a4_inp_reg & b_share__hpc1_cross_domain_5_order20);
    assign v40 = (a_and_b_hpc1_cross_domain_5_order20 ^ prand_04_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order21 = (a4_inp_reg & b_share__hpc1_cross_domain_5_order21);
    assign v41 = (a_and_b_hpc1_cross_domain_5_order21 ^ prand_14_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order22 = (a4_inp_reg & b_share__hpc1_cross_domain_5_order22);
    assign v42 = (a_and_b_hpc1_cross_domain_5_order22 ^ prand_24_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order23 = (a4_inp_reg & b_share__hpc1_cross_domain_5_order23);
    assign v43 = (a_and_b_hpc1_cross_domain_5_order23 ^ prand_34_inp_reg);
    assign v44 = (a4_inp_reg & b_share__hpc1_same_shares_5_order4);
    assign a_and_b_hpc1_cross_domain_5_order24 = (a4_inp_reg & b_share__hpc1_cross_domain_5_order24);
    assign v45 = (a_and_b_hpc1_cross_domain_5_order24 ^ prand_45_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order25 = (a5_inp_reg & b_share__hpc1_cross_domain_5_order25);
    assign v50 = (a_and_b_hpc1_cross_domain_5_order25 ^ prand_05_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order26 = (a5_inp_reg & b_share__hpc1_cross_domain_5_order26);
    assign v51 = (a_and_b_hpc1_cross_domain_5_order26 ^ prand_15_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order27 = (a5_inp_reg & b_share__hpc1_cross_domain_5_order27);
    assign v52 = (a_and_b_hpc1_cross_domain_5_order27 ^ prand_25_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order28 = (a5_inp_reg & b_share__hpc1_cross_domain_5_order28);
    assign v53 = (a_and_b_hpc1_cross_domain_5_order28 ^ prand_35_inp_reg);
    assign a_and_b_hpc1_cross_domain_5_order29 = (a5_inp_reg & b_share__hpc1_cross_domain_5_order29);
    assign v54 = (a_and_b_hpc1_cross_domain_5_order29 ^ prand_45_inp_reg);
    assign v55 = (a5_inp_reg & b_share__hpc1_same_shares_5_order5);
    assign t0 = (v00 ^ v01);
    assign t1 = (t0 ^ v02);
    assign t2 = (t1 ^ v03);
    assign t3 = (t2 ^ v04);
    assign z605_assgn605 = (t3 ^ v05);
    assign t4 = (v10 ^ v11);
    assign t5 = (t4 ^ v12);
    assign t6 = (t5 ^ v13);
    assign t7 = (t6 ^ v14);
    assign z615_assgn615 = (t7 ^ v15);
    assign t8 = (v20 ^ v21);
    assign t9 = (t8 ^ v22);
    assign t10 = (t9 ^ v23);
    assign t11 = (t10 ^ v24);
    assign z625_assgn625 = (t11 ^ v25);
    assign t12 = (v30 ^ v31);
    assign t13 = (t12 ^ v32);
    assign t14 = (t13 ^ v33);
    assign t15 = (t14 ^ v34);
    assign z635_assgn635 = (t15 ^ v35);
    assign t16 = (v40 ^ v41);
    assign t17 = (t16 ^ v42);
    assign t18 = (t17 ^ v43);
    assign t19 = (t18 ^ v44);
    assign z645_assgn645 = (t19 ^ v45);
    assign t20 = (v50 ^ v51);
    assign t21 = (t20 ^ v52);
    assign t22 = (t21 ^ v53);
    assign t23 = (t22 ^ v54);
    assign z655_assgn655 = (t23 ^ v55);

    always @(posedge clk) begin
        b_share__hpc1_same_shares_5_order0 <= (b0_inp ^ rand_0_inp);
        a0_inp_reg <= a0_inp;
        b_share__hpc1_cross_domain_5_order0 <= (b1_inp ^ rand_1_inp);
        prand_01_inp_reg <= prand_01_inp;
        b_share__hpc1_cross_domain_5_order1 <= (b2_inp ^ rand_2_inp);
        prand_02_inp_reg <= prand_02_inp;
        b_share__hpc1_cross_domain_5_order2 <= (b3_inp ^ rand_3_inp);
        prand_03_inp_reg <= prand_03_inp;
        b_share__hpc1_cross_domain_5_order3 <= (b4_inp ^ rand_4_inp);
        prand_04_inp_reg <= prand_04_inp;
        b_share__hpc1_cross_domain_5_order4 <= (b5_inp ^ r5);
        prand_05_inp_reg <= prand_05_inp;
        b_share__hpc1_cross_domain_5_order5 <= (b0_inp ^ rand_0_inp);
        a1_inp_reg <= a1_inp;
        b_share__hpc1_same_shares_5_order1 <= (b1_inp ^ rand_1_inp);
        b_share__hpc1_cross_domain_5_order6 <= (b2_inp ^ rand_2_inp);
        prand_12_inp_reg <= prand_12_inp;
        b_share__hpc1_cross_domain_5_order7 <= (b3_inp ^ rand_3_inp);
        prand_13_inp_reg <= prand_13_inp;
        b_share__hpc1_cross_domain_5_order8 <= (b4_inp ^ rand_4_inp);
        prand_14_inp_reg <= prand_14_inp;
        b_share__hpc1_cross_domain_5_order9 <= (b5_inp ^ r5);
        prand_15_inp_reg <= prand_15_inp;
        b_share__hpc1_cross_domain_5_order10 <= (b0_inp ^ rand_0_inp);
        a2_inp_reg <= a2_inp;
        b_share__hpc1_cross_domain_5_order11 <= (b1_inp ^ rand_1_inp);
        b_share__hpc1_same_shares_5_order2 <= (b2_inp ^ rand_2_inp);
        b_share__hpc1_cross_domain_5_order12 <= (b3_inp ^ rand_3_inp);
        prand_23_inp_reg <= prand_23_inp;
        b_share__hpc1_cross_domain_5_order13 <= (b4_inp ^ rand_4_inp);
        prand_24_inp_reg <= prand_24_inp;
        b_share__hpc1_cross_domain_5_order14 <= (b5_inp ^ r5);
        prand_25_inp_reg <= prand_25_inp;
        b_share__hpc1_cross_domain_5_order15 <= (b0_inp ^ rand_0_inp);
        a3_inp_reg <= a3_inp;
        b_share__hpc1_cross_domain_5_order16 <= (b1_inp ^ rand_1_inp);
        b_share__hpc1_cross_domain_5_order17 <= (b2_inp ^ rand_2_inp);
        b_share__hpc1_same_shares_5_order3 <= (b3_inp ^ rand_3_inp);
        b_share__hpc1_cross_domain_5_order18 <= (b4_inp ^ rand_4_inp);
        prand_34_inp_reg <= prand_34_inp;
        b_share__hpc1_cross_domain_5_order19 <= (b5_inp ^ r5);
        prand_35_inp_reg <= prand_35_inp;
        b_share__hpc1_cross_domain_5_order20 <= (b0_inp ^ rand_0_inp);
        a4_inp_reg <= a4_inp;
        b_share__hpc1_cross_domain_5_order21 <= (b1_inp ^ rand_1_inp);
        b_share__hpc1_cross_domain_5_order22 <= (b2_inp ^ rand_2_inp);
        b_share__hpc1_cross_domain_5_order23 <= (b3_inp ^ rand_3_inp);
        b_share__hpc1_same_shares_5_order4 <= (b4_inp ^ rand_4_inp);
        b_share__hpc1_cross_domain_5_order24 <= (b5_inp ^ r5);
        prand_45_inp_reg <= prand_45_inp;
        b_share__hpc1_cross_domain_5_order25 <= (b0_inp ^ rand_0_inp);
        a5_inp_reg <= a5_inp;
        b_share__hpc1_cross_domain_5_order26 <= (b1_inp ^ rand_1_inp);
        b_share__hpc1_cross_domain_5_order27 <= (b2_inp ^ rand_2_inp);
        b_share__hpc1_cross_domain_5_order28 <= (b3_inp ^ rand_3_inp);
        b_share__hpc1_cross_domain_5_order29 <= (b4_inp ^ rand_4_inp);
        b_share__hpc1_same_shares_5_order5 <= (b5_inp ^ r5);
        c0 <= z605_assgn605;
        c1 <= z615_assgn615;
        c2 <= z625_assgn625;
        c3 <= z635_assgn635;
        c4 <= z645_assgn645;
        c5 <= z655_assgn655;
    end

endmodule

