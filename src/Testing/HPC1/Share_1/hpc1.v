module HPC1(
    clk,
    a0,
    a1,
    b0,
    b1,
    rand_0,
    prand_01,
    c0,
    c1
);
//INPUTS
    input clk;
    input  [7:0] a0;
    input  [7:0] a1;
    input  [7:0] b0;
    input  [7:0] b1;
    input  [7:0] rand_0;
    input  [7:0] prand_01;
//OUTPUTS
    output reg  [7:0] c0;
    output reg  [7:0] c1;
//Intermediate values
    wire [7:0] a0_inp;
    wire [7:0] a1_inp;
    wire [7:0] b0_inp;
    wire [7:0] b1_inp;
    wire [7:0] rand_0_inp;
    wire [7:0] prand_01_inp;
    reg [7:0] b_share__hpc1_same_shares_1_order0;
    reg [7:0] a0_inp_reg;
    wire [7:0] v00;
    reg [7:0] b_share__hpc1_cross_domain_1_order0;
    wire [7:0] a_and_b_hpc1_cross_domain_1_order0;
    reg [7:0] prand_01_inp_reg;
    wire [7:0] v01;
    reg [7:0] b_share__hpc1_cross_domain_1_order1;
    reg [7:0] a1_inp_reg;
    wire [7:0] a_and_b_hpc1_cross_domain_1_order1;
    wire [7:0] v10;
    reg [7:0] b_share__hpc1_same_shares_1_order1;
    wire [7:0] v11;
    wire [7:0] z69_assgn69;
    wire [7:0] z71_assgn71;

    assign a0_inp = a0;
    assign a1_inp = a1;
    assign b0_inp = b0;
    assign b1_inp = b1;
    assign rand_0_inp = rand_0;
    assign prand_01_inp = prand_01;
    assign v00 = (a0_inp_reg & b_share__hpc1_same_shares_1_order0);
    assign a_and_b_hpc1_cross_domain_1_order0 = (a0_inp_reg & b_share__hpc1_cross_domain_1_order0);
    assign v01 = (a_and_b_hpc1_cross_domain_1_order0 ^ prand_01_inp_reg);
    assign a_and_b_hpc1_cross_domain_1_order1 = (a1_inp_reg & b_share__hpc1_cross_domain_1_order1);
    assign v10 = (a_and_b_hpc1_cross_domain_1_order1 ^ prand_01_inp_reg);
    assign v11 = (a1_inp_reg & b_share__hpc1_same_shares_1_order1);
    assign z69_assgn69 = (v00 ^ v01);
    assign z71_assgn71 = (v10 ^ v11);

    always @(posedge clk) begin
        b_share__hpc1_same_shares_1_order0 <= (b0_inp ^ rand_0_inp);
        a0_inp_reg <= a0_inp;
        b_share__hpc1_cross_domain_1_order0 <= (b1_inp ^ rand_0_inp);
        prand_01_inp_reg <= prand_01_inp;
        b_share__hpc1_cross_domain_1_order1 <= (b0_inp ^ rand_0_inp);
        a1_inp_reg <= a1_inp;
        b_share__hpc1_same_shares_1_order1 <= (b1_inp ^ rand_0_inp);
        c0 <= z69_assgn69;
        c1 <= z71_assgn71;
    end

endmodule

