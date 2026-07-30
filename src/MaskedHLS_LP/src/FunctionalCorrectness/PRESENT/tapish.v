module sbox(
    clk,
    x0,
    x1,
    x2,
    x3,
    dec_1,
    y0,
    y1,
    y2,
    y3
);
//INPUTS
    input clk;
    input  x0;
    input  x1;
    input  x2;
    input  x3;
    input  dec_1;
//OUTPUTS
    output reg  y0;
    output reg  y1;
    output reg  y2;
    output reg  y3;
//Intermediate values
    wire dec_1_inp;
    wire x0_inp;
    wire x1_inp;
    wire x2_inp;
    wire x3_inp;
    wire temp1_y0;
    wire t2;
    wire t1;
    wire temp_and_30;
    wire temp1_y1;
    wire temp_and_31;
    wire temp2_y1;
    wire temp_and_32;
    wire temp3_y1;
    wire temp4_y1;
    wire temp5_y1;
    wire t12;
    wire t11;
    wire t10;
    wire t9;
    wire t8;
    wire temp_and_33;
    wire temp1_y2;
    wire temp_and_34;
    wire temp2_y2;
    wire temp3_y2;
    wire temp4_y2;
    wire temp5_y2;
    wire t23;
    wire t22;
    wire t21;
    wire t20;
    wire t19;
    wire t18;
    wire temp_and_35;
    wire temp1_y3;
    wire temp_and_36;
    wire temp2_y3;
    wire temp_and_37;
    wire temp3_y3;
    wire temp4_y3;
    wire t33;
    wire t32;
    wire t31;
    wire t30;
    wire t29;
    wire t28;

    assign dec_1_inp = dec_1;
    assign x0_inp = x0;
    assign x1_inp = x1;
    assign x2_inp = x2;
    assign x3_inp = x3;
    assign temp1_y0 = (x1_inp & x2_inp);
    assign t2 = (x2_inp ^ x3_inp);
    assign t1 = (t2 ^ temp1_y0);
    assign temp_and_30 = (x0_inp & x1_inp);
    assign temp1_y1 = (temp_and_30 & x2_inp);
    assign temp_and_31 = (x0_inp & x1_inp);
    assign temp2_y1 = (temp_and_31 & x3_inp);
    assign temp_and_32 = (x0_inp & x2_inp);
    assign temp3_y1 = (temp_and_32 & x3_inp);
    assign temp4_y1 = (x1_inp & x3_inp);
    assign temp5_y1 = (x2_inp & x3_inp);
    assign t12 = (x1_inp ^ x3_inp);
    assign t11 = (t12 ^ temp1_y1);
    assign t10 = (t11 ^ temp2_y1);
    assign t9 = (t10 ^ temp3_y1);
    assign t8 = (t9 ^ temp4_y1);
    assign temp_and_33 = (x0_inp & x1_inp);
    assign temp1_y2 = (temp_and_33 & x3_inp);
    assign temp_and_34 = (x0_inp & x2_inp);
    assign temp2_y2 = (temp_and_34 & x3_inp);
    assign temp3_y2 = (x0_inp & x1_inp);
    assign temp4_y2 = (x0_inp & x3_inp);
    assign temp5_y2 = (x1_inp & x3_inp);
    assign t23 = (temp1_y2 ^ temp2_y2);
    assign t22 = (t23 ^ temp3_y2);
    assign t21 = (t22 ^ temp4_y2);
    assign t20 = (t21 ^ temp5_y2);
    assign t19 = (t20 ^ x2_inp);
    assign t18 = (t19 ^ x3_inp);
    assign temp_and_35 = (x0_inp & x1_inp);
    assign temp1_y3 = (temp_and_35 & x2_inp);
    assign temp_and_36 = (x0_inp & x1_inp);
    assign temp2_y3 = (temp_and_36 & x3_inp);
    assign temp_and_37 = (x0_inp & x2_inp);
    assign temp3_y3 = (temp_and_37 & x3_inp);
    assign temp4_y3 = (x1_inp & x2_inp);
    assign t33 = (temp1_y3 ^ temp2_y3);
    assign t32 = (t33 ^ temp3_y3);
    assign t31 = (t32 ^ temp4_y3);
    assign t30 = (t31 ^ x0_inp);
    assign t29 = (t30 ^ x1_inp);
    assign t28 = (t29 ^ x3_inp);

    always @(posedge clk) begin
        y0 <= (t1 ^ x0_inp);
        y1 <= (t8 ^ temp5_y1);
        y2 <= (t18 ^ dec_1_inp);
        y3 <= (t28 ^ dec_1_inp);
    end

endmodule

