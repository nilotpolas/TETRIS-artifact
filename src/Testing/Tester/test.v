module test(
    clk,
    a_0,
    a_1,
    b_0,
    b_1,
    c_0,
    c_1,
    d_0,
    d_1,
    rand_2,
    rand_1,
    w_0,
    w_1
);
//INPUTS
    input clk;
    input  [7:0] a_0;
    input  [7:0] a_1;
    input  [7:0] b_0;
    input  [7:0] b_1;
    input  [7:0] c_0;
    input  [7:0] c_1;
    input  [7:0] d_0;
    input  [7:0] d_1;
    input  [7:0] rand_2;
    input  [7:0] rand_1;
//OUTPUTS
    output reg  [7:0] w_0;
    output reg  [7:0] w_1;
//Intermediate values
    wire [7:0] a_0_inp;
    wire [7:0] a_1_inp;
    wire [7:0] b_0_inp;
    wire [7:0] b_1_inp;
    wire [7:0] c_0_inp;
    wire [7:0] c_1_inp;
    wire [7:0] d_0_inp;
    wire [7:0] d_1_inp;
    wire [7:0] rand_2_inp;
    wire [7:0] rand_1_inp;
    wire [7:0] a_inp_0;
    wire [7:0] a_inp_1;
    wire [7:0] b_inp_0;
    wire [7:0] b_inp_1;
    wire [7:0] c_inp_0;
    wire [7:0] c_inp_1;
    wire [7:0] d_inp_0;
    wire [7:0] d_inp_1;
    reg [7:0] b_share_reg_hpc2_same_shares_1_order0_HPC20;
    reg [7:0] a_inp_0_reg;
    wire [7:0] z1_assgn1;
    reg [7:0] u00_HPC20;
    reg [7:0] temp_hpc2_v_1_order0_HPC20;
    wire [7:0] z3_assgn3;
    reg [7:0] v01_HPC20;
    reg [7:0] rand_reg_hpc2_w_1_order0_HPC20;
    wire [7:0] a_neg_hpc2_w_1_order0_HPC20;
    reg [7:0] a_neg_hpc2_w_1_order0_HPC20_reg;
    wire [7:0] z5_assgn5;
    reg [7:0] w01_HPC20;
    wire [7:0] u01_HPC20;
    reg [7:0] temp_hpc2_v_1_order1_HPC20;
    reg [7:0] a_inp_1_reg;
    wire [7:0] z7_assgn7;
    reg [7:0] v10_HPC20;
    reg [7:0] rand_reg_hpc2_w_1_order1_HPC20;
    wire [7:0] a_neg_hpc2_w_1_order1_HPC20;
    reg [7:0] a_neg_hpc2_w_1_order1_HPC20_reg;
    wire [7:0] z9_assgn9;
    reg [7:0] w10_HPC20;
    wire [7:0] u10_HPC20;
    reg [7:0] b_share_reg_hpc2_same_shares_1_order1_HPC20;
    wire [7:0] z11_assgn11;
    reg [7:0] u11_HPC20;
    wire [7:0] x_0;
    wire [7:0] x_1;
    reg [7:0] b_share_reg_hpc2_same_shares_1_order0_HPC21;
    reg [7:0] c_inp_0_reg;
    wire [7:0] z13_assgn13;
    reg [7:0] u00_HPC21;
    reg [7:0] temp_hpc2_v_1_order0_HPC21;
    wire [7:0] z15_assgn15;
    reg [7:0] v01_HPC21;
    reg [7:0] rand_reg_hpc2_w_1_order0_HPC21;
    wire [7:0] a_neg_hpc2_w_1_order0_HPC21;
    reg [7:0] a_neg_hpc2_w_1_order0_HPC21_reg;
    wire [7:0] z17_assgn17;
    reg [7:0] w01_HPC21;
    wire [7:0] u01_HPC21;
    reg [7:0] temp_hpc2_v_1_order1_HPC21;
    reg [7:0] c_inp_1_reg;
    wire [7:0] z19_assgn19;
    reg [7:0] v10_HPC21;
    reg [7:0] rand_reg_hpc2_w_1_order1_HPC21;
    wire [7:0] a_neg_hpc2_w_1_order1_HPC21;
    reg [7:0] a_neg_hpc2_w_1_order1_HPC21_reg;
    wire [7:0] z21_assgn21;
    reg [7:0] w10_HPC21;
    wire [7:0] u10_HPC21;
    reg [7:0] b_share_reg_hpc2_same_shares_1_order1_HPC21;
    wire [7:0] z23_assgn23;
    reg [7:0] u11_HPC21;
    wire [7:0] y_0;
    wire [7:0] y_1;

    assign a_0_inp = a_0;
    assign a_1_inp = a_1;
    assign b_0_inp = b_0;
    assign b_1_inp = b_1;
    assign c_0_inp = c_0;
    assign c_1_inp = c_1;
    assign d_0_inp = d_0;
    assign d_1_inp = d_1;
    assign rand_2_inp = rand_2;
    assign rand_1_inp = rand_1;
    assign a_inp_0 = a_0_inp;
    assign a_inp_1 = a_1_inp;
    assign b_inp_0 = b_0_inp;
    assign b_inp_1 = b_1_inp;
    assign c_inp_0 = c_0_inp;
    assign c_inp_1 = c_1_inp;
    assign d_inp_0 = d_0_inp;
    assign d_inp_1 = d_1_inp;
    assign z1_assgn1 = (a_inp_0_reg & b_share_reg_hpc2_same_shares_1_order0_HPC20);
    assign z3_assgn3 = (temp_hpc2_v_1_order0_HPC20 & a_inp_0_reg);
    assign a_neg_hpc2_w_1_order0_HPC20 = ~a_inp_0;
    assign z5_assgn5 = (a_neg_hpc2_w_1_order0_HPC20_reg & rand_reg_hpc2_w_1_order0_HPC20);
    assign u01_HPC20 = (v01_HPC20 ^ w01_HPC20);
    assign z7_assgn7 = (temp_hpc2_v_1_order1_HPC20 & a_inp_1_reg);
    assign a_neg_hpc2_w_1_order1_HPC20 = ~a_inp_1;
    assign z9_assgn9 = (a_neg_hpc2_w_1_order1_HPC20_reg & rand_reg_hpc2_w_1_order1_HPC20);
    assign u10_HPC20 = (v10_HPC20 ^ w10_HPC20);
    assign z11_assgn11 = (a_inp_1_reg & b_share_reg_hpc2_same_shares_1_order1_HPC20);
    assign x_0 = (u00_HPC20 ^ u01_HPC20);
    assign x_1 = (u10_HPC20 ^ u11_HPC20);
    assign z13_assgn13 = (c_inp_0_reg & b_share_reg_hpc2_same_shares_1_order0_HPC21);
    assign z15_assgn15 = (temp_hpc2_v_1_order0_HPC21 & c_inp_0_reg);
    assign a_neg_hpc2_w_1_order0_HPC21 = ~c_inp_0;
    assign z17_assgn17 = (a_neg_hpc2_w_1_order0_HPC21_reg & rand_reg_hpc2_w_1_order0_HPC21);
    assign u01_HPC21 = (v01_HPC21 ^ w01_HPC21);
    assign z19_assgn19 = (temp_hpc2_v_1_order1_HPC21 & c_inp_1_reg);
    assign a_neg_hpc2_w_1_order1_HPC21 = ~c_inp_1;
    assign z21_assgn21 = (a_neg_hpc2_w_1_order1_HPC21_reg & rand_reg_hpc2_w_1_order1_HPC21);
    assign u10_HPC21 = (v10_HPC21 ^ w10_HPC21);
    assign z23_assgn23 = (c_inp_1_reg & b_share_reg_hpc2_same_shares_1_order1_HPC21);
    assign y_0 = (u00_HPC21 ^ u01_HPC21);
    assign y_1 = (u10_HPC21 ^ u11_HPC21);

    always @(posedge clk) begin
        b_share_reg_hpc2_same_shares_1_order0_HPC20 <= b_inp_0;
        a_inp_0_reg <= a_inp_0;
        u00_HPC20 <= z1_assgn1;
        temp_hpc2_v_1_order0_HPC20 <= (b_inp_1 ^ rand_1_inp);
        v01_HPC20 <= z3_assgn3;
        rand_reg_hpc2_w_1_order0_HPC20 <= rand_1_inp;
        a_neg_hpc2_w_1_order0_HPC20_reg <= a_neg_hpc2_w_1_order0_HPC20;
        w01_HPC20 <= z5_assgn5;
        temp_hpc2_v_1_order1_HPC20 <= (b_inp_0 ^ rand_1_inp);
        a_inp_1_reg <= a_inp_1;
        v10_HPC20 <= z7_assgn7;
        rand_reg_hpc2_w_1_order1_HPC20 <= rand_1_inp;
        a_neg_hpc2_w_1_order1_HPC20_reg <= a_neg_hpc2_w_1_order1_HPC20;
        w10_HPC20 <= z9_assgn9;
        b_share_reg_hpc2_same_shares_1_order1_HPC20 <= b_inp_1;
        u11_HPC20 <= z11_assgn11;
        b_share_reg_hpc2_same_shares_1_order0_HPC21 <= d_inp_0;
        c_inp_0_reg <= c_inp_0;
        u00_HPC21 <= z13_assgn13;
        temp_hpc2_v_1_order0_HPC21 <= (d_inp_1 ^ rand_2_inp);
        v01_HPC21 <= z15_assgn15;
        rand_reg_hpc2_w_1_order0_HPC21 <= rand_2_inp;
        a_neg_hpc2_w_1_order0_HPC21_reg <= a_neg_hpc2_w_1_order0_HPC21;
        w01_HPC21 <= z17_assgn17;
        temp_hpc2_v_1_order1_HPC21 <= (d_inp_0 ^ rand_2_inp);
        c_inp_1_reg <= c_inp_1;
        v10_HPC21 <= z19_assgn19;
        rand_reg_hpc2_w_1_order1_HPC21 <= rand_2_inp;
        a_neg_hpc2_w_1_order1_HPC21_reg <= a_neg_hpc2_w_1_order1_HPC21;
        w10_HPC21 <= z21_assgn21;
        b_share_reg_hpc2_same_shares_1_order1_HPC21 <= d_inp_1;
        u11_HPC21 <= z23_assgn23;
        w_0 <= (x_0 ^ y_0);
        w_1 <= (x_1 ^ y_1);
    end

endmodule

