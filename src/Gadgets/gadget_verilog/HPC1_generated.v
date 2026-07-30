module HPC1(
    clk,
    a0,
    a1,
    a2,
    a3,
    b0,
    b1,
    b2,
    b3,
    r0,
    r1,
    r2,
    p01,
    p02,
    p03,
    p12,
    p13,
    p23,
    c0,
    c1,
    c2,
    c3
);
//INPUTS
    input clk;
    input  [7:0] a0;
    input  [7:0] a1;
    input  [7:0] a2;
    input  [7:0] a3;
    input  [7:0] b0;
    input  [7:0] b1;
    input  [7:0] b2;
    input  [7:0] b3;
    input  [7:0] r0;
    input  [7:0] r1;
    input  [7:0] r2;
    input  [7:0] p01;
    input  [7:0] p02;
    input  [7:0] p03;
    input  [7:0] p12;
    input  [7:0] p13;
    input  [7:0] p23;
//OUTPUTS
    output reg  [7:0] c0;
    output reg  [7:0] c1;
    output reg  [7:0] c2;
    output reg  [7:0] c3;
//Intermediate values
    wire [7:0] a0_inp;
    wire [7:0] a1_inp;
    wire [7:0] a2_inp;
    wire [7:0] a3_inp;
    wire [7:0] b0_inp;
    wire [7:0] b1_inp;
    wire [7:0] b2_inp;
    wire [7:0] b3_inp;
    wire [7:0] r0_inp;
    wire [7:0] r1_inp;
    wire [7:0] r2_inp;
    wire [7:0] p01_inp;
    wire [7:0] p02_inp;
    wire [7:0] p03_inp;
    wire [7:0] p12_inp;
    wire [7:0] p13_inp;
    wire [7:0] p23_inp;
    wire [7:0] t0;
    wire [7:0] r3;
    reg [7:0] b_share__hpc1_same_shares_3_order0;
    reg [7:0] a0_inp_reg;
    wire [7:0] v00;
    reg [7:0] b_share__hpc1_cross_domain_3_order0;
    wire [7:0] a_and_b_hpc1_cross_domain_3_order0;
    reg [7:0] p01_inp_reg;
    wire [7:0] v01;
    reg [7:0] b_share__hpc1_cross_domain_3_order1;
    wire [7:0] a_and_b_hpc1_cross_domain_3_order1;
    reg [7:0] p02_inp_reg;
    wire [7:0] v02;
    reg [7:0] b_share__hpc1_cross_domain_3_order2;
    wire [7:0] a_and_b_hpc1_cross_domain_3_order2;
    reg [7:0] p03_inp_reg;
    wire [7:0] v03;
    reg [7:0] b_share__hpc1_cross_domain_3_order3;
    reg [7:0] a1_inp_reg;
    wire [7:0] a_and_b_hpc1_cross_domain_3_order3;
    wire [7:0] v10;
    reg [7:0] b_share__hpc1_same_shares_3_order1;
    wire [7:0] v11;
    reg [7:0] b_share__hpc1_cross_domain_3_order4;
    wire [7:0] a_and_b_hpc1_cross_domain_3_order4;
    reg [7:0] p12_inp_reg;
    wire [7:0] v12;
    reg [7:0] b_share__hpc1_cross_domain_3_order5;
    wire [7:0] a_and_b_hpc1_cross_domain_3_order5;
    reg [7:0] p13_inp_reg;
    wire [7:0] v13;
    reg [7:0] b_share__hpc1_cross_domain_3_order6;
    reg [7:0] a2_inp_reg;
    wire [7:0] a_and_b_hpc1_cross_domain_3_order6;
    wire [7:0] v20;
    reg [7:0] b_share__hpc1_cross_domain_3_order7;
    wire [7:0] a_and_b_hpc1_cross_domain_3_order7;
    wire [7:0] v21;
    reg [7:0] b_share__hpc1_same_shares_3_order2;
    wire [7:0] v22;
    reg [7:0] b_share__hpc1_cross_domain_3_order8;
    wire [7:0] a_and_b_hpc1_cross_domain_3_order8;
    reg [7:0] p23_inp_reg;
    wire [7:0] v23;
    reg [7:0] b_share__hpc1_cross_domain_3_order9;
    reg [7:0] a3_inp_reg;
    wire [7:0] a_and_b_hpc1_cross_domain_3_order9;
    wire [7:0] v30;
    reg [7:0] b_share__hpc1_cross_domain_3_order10;
    wire [7:0] a_and_b_hpc1_cross_domain_3_order10;
    wire [7:0] v31;
    reg [7:0] b_share__hpc1_cross_domain_3_order11;
    wire [7:0] a_and_b_hpc1_cross_domain_3_order11;
    wire [7:0] v32;
    reg [7:0] b_share__hpc1_same_shares_3_order3;
    wire [7:0] v33;
    wire [7:0] t1;
    wire [7:0] t2;
    wire [7:0] z281_assgn281;
    wire [7:0] t3;
    wire [7:0] t4;
    wire [7:0] z287_assgn287;
    wire [7:0] t5;
    wire [7:0] t6;
    wire [7:0] z293_assgn293;
    wire [7:0] t7;
    wire [7:0] t8;
    wire [7:0] z299_assgn299;

    assign a0_inp = a0;
    assign a1_inp = a1;
    assign a2_inp = a2;
    assign a3_inp = a3;
    assign b0_inp = b0;
    assign b1_inp = b1;
    assign b2_inp = b2;
    assign b3_inp = b3;
    assign r0_inp = r0;
    assign r1_inp = r1;
    assign r2_inp = r2;
    assign p01_inp = p01;
    assign p02_inp = p02;
    assign p03_inp = p03;
    assign p12_inp = p12;
    assign p13_inp = p13;
    assign p23_inp = p23;
    assign t0 = (r0_inp ^ r1_inp);
    assign r3 = (t0 ^ r2_inp);
    assign v00 = (a0_inp_reg & b_share__hpc1_same_shares_3_order0);
    assign a_and_b_hpc1_cross_domain_3_order0 = (a0_inp_reg & b_share__hpc1_cross_domain_3_order0);
    assign v01 = (a_and_b_hpc1_cross_domain_3_order0 ^ p01_inp_reg);
    assign a_and_b_hpc1_cross_domain_3_order1 = (a0_inp_reg & b_share__hpc1_cross_domain_3_order1);
    assign v02 = (a_and_b_hpc1_cross_domain_3_order1 ^ p02_inp_reg);
    assign a_and_b_hpc1_cross_domain_3_order2 = (a0_inp_reg & b_share__hpc1_cross_domain_3_order2);
    assign v03 = (a_and_b_hpc1_cross_domain_3_order2 ^ p03_inp_reg);
    assign a_and_b_hpc1_cross_domain_3_order3 = (a1_inp_reg & b_share__hpc1_cross_domain_3_order3);
    assign v10 = (a_and_b_hpc1_cross_domain_3_order3 ^ p01_inp_reg);
    assign v11 = (a1_inp_reg & b_share__hpc1_same_shares_3_order1);
    assign a_and_b_hpc1_cross_domain_3_order4 = (a1_inp_reg & b_share__hpc1_cross_domain_3_order4);
    assign v12 = (a_and_b_hpc1_cross_domain_3_order4 ^ p12_inp_reg);
    assign a_and_b_hpc1_cross_domain_3_order5 = (a1_inp_reg & b_share__hpc1_cross_domain_3_order5);
    assign v13 = (a_and_b_hpc1_cross_domain_3_order5 ^ p13_inp_reg);
    assign a_and_b_hpc1_cross_domain_3_order6 = (a2_inp_reg & b_share__hpc1_cross_domain_3_order6);
    assign v20 = (a_and_b_hpc1_cross_domain_3_order6 ^ p02_inp_reg);
    assign a_and_b_hpc1_cross_domain_3_order7 = (a2_inp_reg & b_share__hpc1_cross_domain_3_order7);
    assign v21 = (a_and_b_hpc1_cross_domain_3_order7 ^ p12_inp_reg);
    assign v22 = (a2_inp_reg & b_share__hpc1_same_shares_3_order2);
    assign a_and_b_hpc1_cross_domain_3_order8 = (a2_inp_reg & b_share__hpc1_cross_domain_3_order8);
    assign v23 = (a_and_b_hpc1_cross_domain_3_order8 ^ p23_inp_reg);
    assign a_and_b_hpc1_cross_domain_3_order9 = (a3_inp_reg & b_share__hpc1_cross_domain_3_order9);
    assign v30 = (a_and_b_hpc1_cross_domain_3_order9 ^ p03_inp_reg);
    assign a_and_b_hpc1_cross_domain_3_order10 = (a3_inp_reg & b_share__hpc1_cross_domain_3_order10);
    assign v31 = (a_and_b_hpc1_cross_domain_3_order10 ^ p13_inp_reg);
    assign a_and_b_hpc1_cross_domain_3_order11 = (a3_inp_reg & b_share__hpc1_cross_domain_3_order11);
    assign v32 = (a_and_b_hpc1_cross_domain_3_order11 ^ p23_inp_reg);
    assign v33 = (a3_inp_reg & b_share__hpc1_same_shares_3_order3);
    assign t1 = (v00 ^ v01);
    assign t2 = (t1 ^ v02);
    assign z281_assgn281 = (t2 ^ v03);
    assign t3 = (v10 ^ v11);
    assign t4 = (t3 ^ v12);
    assign z287_assgn287 = (t4 ^ v13);
    assign t5 = (v20 ^ v21);
    assign t6 = (t5 ^ v22);
    assign z293_assgn293 = (t6 ^ v23);
    assign t7 = (v30 ^ v31);
    assign t8 = (t7 ^ v32);
    assign z299_assgn299 = (t8 ^ v33);

    always @(posedge clk) begin
        b_share__hpc1_same_shares_3_order0 <= (b0_inp ^ r0_inp);
        a0_inp_reg <= a0_inp;
        b_share__hpc1_cross_domain_3_order0 <= (b1_inp ^ r1_inp);
        p01_inp_reg <= p01_inp;
        b_share__hpc1_cross_domain_3_order1 <= (b2_inp ^ r2_inp);
        p02_inp_reg <= p02_inp;
        b_share__hpc1_cross_domain_3_order2 <= (b3_inp ^ r3);
        p03_inp_reg <= p03_inp;
        b_share__hpc1_cross_domain_3_order3 <= (b0_inp ^ r0_inp);
        a1_inp_reg <= a1_inp;
        b_share__hpc1_same_shares_3_order1 <= (b1_inp ^ r1_inp);
        b_share__hpc1_cross_domain_3_order4 <= (b2_inp ^ r2_inp);
        p12_inp_reg <= p12_inp;
        b_share__hpc1_cross_domain_3_order5 <= (b3_inp ^ r3);
        p13_inp_reg <= p13_inp;
        b_share__hpc1_cross_domain_3_order6 <= (b0_inp ^ r0_inp);
        a2_inp_reg <= a2_inp;
        b_share__hpc1_cross_domain_3_order7 <= (b1_inp ^ r1_inp);
        b_share__hpc1_same_shares_3_order2 <= (b2_inp ^ r2_inp);
        b_share__hpc1_cross_domain_3_order8 <= (b3_inp ^ r3);
        p23_inp_reg <= p23_inp;
        b_share__hpc1_cross_domain_3_order9 <= (b0_inp ^ r0_inp);
        a3_inp_reg <= a3_inp;
        b_share__hpc1_cross_domain_3_order10 <= (b1_inp ^ r1_inp);
        b_share__hpc1_cross_domain_3_order11 <= (b2_inp ^ r2_inp);
        b_share__hpc1_same_shares_3_order3 <= (b3_inp ^ r3);
        c0 <= z281_assgn281;
        c1 <= z287_assgn287;
        c2 <= z293_assgn293;
        c3 <= z299_assgn299;
    end

endmodule

