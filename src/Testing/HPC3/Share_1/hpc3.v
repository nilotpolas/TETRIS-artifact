module HPC3(
    clk,
    a0,
    a1,
    b0,
    b1,
    r01,
    p01,
    c0,
    c1
);
//INPUTS
    input clk;
    input  [7:0] a0;
    input  [7:0] a1;
    input  [7:0] b0;
    input  [7:0] b1;
    input  [7:0] r01;
    input  [7:0] p01;
//OUTPUTS
    output reg  [7:0] c0;
    output reg  [7:0] c1;
//Intermediate values
    wire [7:0] a0_inp;
    wire [7:0] a1_inp;
    wire [7:0] b0_inp;
    wire [7:0] b1_inp;
    wire [7:0] r01_inp;
    wire [7:0] p01_inp;
    reg [7:0] u00;
    reg [7:0] temp_hpc3_v_1_order0;
    reg [7:0] a_share_reg_hpc3_v_1_order0;
    wire [7:0] v01;
    wire [7:0] a_share_neg_hpc3_w_1_order0;
    wire [7:0] temp_hpc3_w_1_order0;
    reg [7:0] w01;
    wire [7:0] u01;
    reg [7:0] temp_hpc3_v_1_order1;
    reg [7:0] a_share_reg_hpc3_v_1_order1;
    wire [7:0] v10;
    wire [7:0] a_share_neg_hpc3_w_1_order1;
    wire [7:0] temp_hpc3_w_1_order1;
    reg [7:0] w10;
    wire [7:0] u10;
    reg [7:0] u11;

    assign a0_inp = a0;
    assign a1_inp = a1;
    assign b0_inp = b0;
    assign b1_inp = b1;
    assign r01_inp = r01;
    assign p01_inp = p01;
    assign v01 = (temp_hpc3_v_1_order0 & a_share_reg_hpc3_v_1_order0);
    assign a_share_neg_hpc3_w_1_order0 = ~a0_inp;
    assign temp_hpc3_w_1_order0 = (a_share_neg_hpc3_w_1_order0 & r01_inp);
    assign u01 = (v01 ^ w01);
    assign v10 = (temp_hpc3_v_1_order1 & a_share_reg_hpc3_v_1_order1);
    assign a_share_neg_hpc3_w_1_order1 = ~a1_inp;
    assign temp_hpc3_w_1_order1 = (a_share_neg_hpc3_w_1_order1 & r01_inp);
    assign u10 = (v10 ^ w10);

    always @(posedge clk) begin
        u00 <= (a0_inp & b0_inp);
        temp_hpc3_v_1_order0 <= (b1_inp ^ r01_inp);
        a_share_reg_hpc3_v_1_order0 <= a0_inp;
        w01 <= (temp_hpc3_w_1_order0 ^ p01_inp);
        temp_hpc3_v_1_order1 <= (b0_inp ^ r01_inp);
        a_share_reg_hpc3_v_1_order1 <= a1_inp;
        w10 <= (temp_hpc3_w_1_order1 ^ p01_inp);
        u11 <= (a1_inp & b1_inp);
        c0 <= (u00 ^ u01);
        c1 <= (u10 ^ u11);
    end

endmodule

