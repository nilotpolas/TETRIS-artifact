module HPC2(
    clk,
    a0,
    a1,
    b0,
    b1,
    rand_01,
    c0,
    c1
);
//INPUTS
    input clk;
    input  [7:0] a0;
    input  [7:0] a1;
    input  [7:0] b0;
    input  [7:0] b1;
    input  [7:0] rand_01;
//OUTPUTS
    output reg  [7:0] c0;
    output reg  [7:0] c1;
//Intermediate values
    wire [7:0] a0_inp;
    wire [7:0] a1_inp;
    wire [7:0] b0_inp;
    wire [7:0] b1_inp;
    wire [7:0] rand_01_inp;
    reg [7:0] b_share_reg_hpc2_same_shares_1_order0;
    reg [7:0] a0_inp_reg;
    wire [7:0] z1_assgn1;
    reg [7:0] u00;
    reg [7:0] temp_hpc2_v_1_order0;
    wire [7:0] z3_assgn3;
    reg [7:0] v01;
    reg [7:0] rand_reg_hpc2_w_1_order0;
    wire [7:0] a_neg_hpc2_w_1_order0;
    reg [7:0] a_neg_hpc2_w_1_order0_reg;
    wire [7:0] z5_assgn5;
    reg [7:0] w01;
    wire [7:0] u01;
    reg [7:0] temp_hpc2_v_1_order1;
    reg [7:0] a1_inp_reg;
    wire [7:0] z7_assgn7;
    reg [7:0] v10;
    reg [7:0] rand_reg_hpc2_w_1_order1;
    wire [7:0] a_neg_hpc2_w_1_order1;
    reg [7:0] a_neg_hpc2_w_1_order1_reg;
    wire [7:0] z9_assgn9;
    reg [7:0] w10;
    wire [7:0] u10;
    reg [7:0] b_share_reg_hpc2_same_shares_1_order1;
    wire [7:0] z11_assgn11;
    reg [7:0] u11;

    assign a0_inp = a0;
    assign a1_inp = a1;
    assign b0_inp = b0;
    assign b1_inp = b1;
    assign rand_01_inp = rand_01;
    assign z1_assgn1 = (a0_inp_reg & b_share_reg_hpc2_same_shares_1_order0);
    assign z3_assgn3 = (temp_hpc2_v_1_order0 & a0_inp_reg);
    assign a_neg_hpc2_w_1_order0 = ~a0_inp;
    assign z5_assgn5 = (a_neg_hpc2_w_1_order0_reg & rand_reg_hpc2_w_1_order0);
    assign u01 = (v01 ^ w01);
    assign z7_assgn7 = (temp_hpc2_v_1_order1 & a1_inp_reg);
    assign a_neg_hpc2_w_1_order1 = ~a1_inp;
    assign z9_assgn9 = (a_neg_hpc2_w_1_order1_reg & rand_reg_hpc2_w_1_order1);
    assign u10 = (v10 ^ w10);
    assign z11_assgn11 = (a1_inp_reg & b_share_reg_hpc2_same_shares_1_order1);

    always @(posedge clk) begin
        b_share_reg_hpc2_same_shares_1_order0 <= b0_inp;
        a0_inp_reg <= a0_inp;
        u00 <= z1_assgn1;
        temp_hpc2_v_1_order0 <= (b1_inp ^ rand_01_inp);
        v01 <= z3_assgn3;
        rand_reg_hpc2_w_1_order0 <= rand_01_inp;
        a_neg_hpc2_w_1_order0_reg <= a_neg_hpc2_w_1_order0;
        w01 <= z5_assgn5;
        temp_hpc2_v_1_order1 <= (b0_inp ^ rand_01_inp);
        a1_inp_reg <= a1_inp;
        v10 <= z7_assgn7;
        rand_reg_hpc2_w_1_order1 <= rand_01_inp;
        a_neg_hpc2_w_1_order1_reg <= a_neg_hpc2_w_1_order1;
        w10 <= z9_assgn9;
        b_share_reg_hpc2_same_shares_1_order1 <= b1_inp;
        u11 <= z11_assgn11;
        c0 <= (u00 ^ u01);
        c1 <= (u10 ^ u11);
    end

endmodule

