module Domand(
    clk,
    a0,
    a1,
    a2,
    a3,
    b0,
    b1,
    b2,
    b3,
    r01,
    r02,
    r03,
    r12,
    r13,
    r23,
    dec_0,
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
    input  [7:0] r01;
    input  [7:0] r02;
    input  [7:0] r03;
    input  [7:0] r12;
    input  [7:0] r13;
    input  [7:0] r23;
    input  [7:0] dec_0;
//OUTPUTS
    output reg  [7:0] c0;
    output reg  [7:0] c1;
    output reg  [7:0] c2;
    output reg  [7:0] c3;
//Intermediate values
    wire [7:0] dec_0_inp;
    reg [7:0] z1_assgn1;
    wire [7:0] a0_inp;
    wire [7:0] a1_inp;
    wire [7:0] a2_inp;
    wire [7:0] a3_inp;
    wire [7:0] b0_inp;
    wire [7:0] b1_inp;
    wire [7:0] b2_inp;
    wire [7:0] b3_inp;
    wire [7:0] r01_inp;
    wire [7:0] r02_inp;
    wire [7:0] r03_inp;
    wire [7:0] r12_inp;
    wire [7:0] r13_inp;
    wire [7:0] r23_inp;
    wire [7:0] t0;
    wire [7:0] t1;
    wire [7:0] i0;
    wire [7:0] t2;
    wire [7:0] i1;
    wire [7:0] t3;
    wire [7:0] i2;
    wire [7:0] t4;
    wire [7:0] i3;
    wire [7:0] t5;
    wire [7:0] t6;
    wire [7:0] i4;
    wire [7:0] t7;
    wire [7:0] i5;
    wire [7:0] t8;
    wire [7:0] i6;
    wire [7:0] t9;
    wire [7:0] i7;
    wire [7:0] t10;
    wire [7:0] t11;
    wire [7:0] i8;
    wire [7:0] t12;
    wire [7:0] i9;
    wire [7:0] t13;
    wire [7:0] i10;
    wire [7:0] t14;
    wire [7:0] i11;
    wire [7:0] t15;
    wire [7:0] t16;
    reg [7:0] i0_reg;
    reg [7:0] i1_reg;
    wire [7:0] t17;
    reg [7:0] i2_reg;
    reg [7:0] t0_reg;
    reg [7:0] i3_reg;
    reg [7:0] i4_reg;
    wire [7:0] t18;
    reg [7:0] i5_reg;
    reg [7:0] t5_reg;
    reg [7:0] i6_reg;
    reg [7:0] i7_reg;
    wire [7:0] t19;
    reg [7:0] i8_reg;
    reg [7:0] t10_reg;
    reg [7:0] i9_reg;
    reg [7:0] i10_reg;
    wire [7:0] t20;
    reg [7:0] i11_reg;
    reg [7:0] t15_reg;

    assign dec_0_inp = dec_0;
    assign a0_inp = a0;
    assign a1_inp = a1;
    assign a2_inp = a2;
    assign a3_inp = a3;
    assign b0_inp = b0;
    assign b1_inp = b1;
    assign b2_inp = b2;
    assign b3_inp = b3;
    assign r01_inp = r01;
    assign r02_inp = r02;
    assign r03_inp = r03;
    assign r12_inp = r12;
    assign r13_inp = r13;
    assign r23_inp = r23;
    assign t0 = (a0_inp & b0_inp);
    assign t1 = (a0_inp & b1_inp);
    assign i0 = (t1 ^ r01_inp);
    assign t2 = (a0_inp & b2_inp);
    assign i1 = (t2 ^ r02_inp);
    assign t3 = (a0_inp & b3_inp);
    assign i2 = (t3 ^ r03_inp);
    assign t4 = (a1_inp & b0_inp);
    assign i3 = (t4 ^ r01_inp);
    assign t5 = (a1_inp & b1_inp);
    assign t6 = (a1_inp & b2_inp);
    assign i4 = (t6 ^ r12_inp);
    assign t7 = (a1_inp & b3_inp);
    assign i5 = (t7 ^ r13_inp);
    assign t8 = (a2_inp & b0_inp);
    assign i6 = (t8 ^ r02_inp);
    assign t9 = (a2_inp & b1_inp);
    assign i7 = (t9 ^ r12_inp);
    assign t10 = (a2_inp & b2_inp);
    assign t11 = (a2_inp & b3_inp);
    assign i8 = (t11 ^ r23_inp);
    assign t12 = (a3_inp & b0_inp);
    assign i9 = (t12 ^ r03_inp);
    assign t13 = (a3_inp & b1_inp);
    assign i10 = (t13 ^ r13_inp);
    assign t14 = (a3_inp & b2_inp);
    assign i11 = (t14 ^ r23_inp);
    assign t15 = (a3_inp & b3_inp);
    assign t16 = (i0_reg ^ i1_reg);
    assign t17 = (i3_reg ^ i4_reg);
    assign t18 = (i6_reg ^ i7_reg);
    assign t19 = (i9_reg ^ i10_reg);
    assign t20 = (t19 ^ i11_reg);

    always @(posedge clk) begin
        z1_assgn1 <= dec_0_inp;
        i0_reg <= i0;
        i1_reg <= i1;
        i2_reg <= i2;
        t0_reg <= t0;
        c0 <= (t16 ^ t0_reg);
        i3_reg <= i3;
        i4_reg <= i4;
        i5_reg <= i5;
        t5_reg <= t5;
        c1 <= (t17 ^ t5_reg);
        i6_reg <= i6;
        i7_reg <= i7;
        i8_reg <= i8;
        t10_reg <= t10;
        c2 <= (t18 ^ t10_reg);
        i9_reg <= i9;
        i10_reg <= i10;
        i11_reg <= i11;
        t15_reg <= t15;
        c3 <= (t19 ^ t15_reg);
    end

endmodule

