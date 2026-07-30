`timescale 1ns/1ps
module sbox_tb;

    // Inputs
    reg clk;
    reg x0, x1, x2, x3;
    reg dec_1;

    // Outputs
    wire y0, y1, y2, y3;

    // Instantiate the Unit Under Test (UUT)
    sbox uut (
        .clk(clk),
        .x0(x0),
        .x1(x1),
        .x2(x2),
        .x3(x3),
        .dec_1(dec_1),
        .y0(y0),
        .y1(y1),
        .y2(y2),
        .y3(y3)
    );

    // Clock generation (10ns period)
    always #5 clk = ~clk;

    initial begin
        // Initialize inputs
        clk   = 0;
        x0    = 0;
        x1    = 0;
        x2    = 0;
        x3    = 0;
        dec_1 = 0;

        // Monitor signals
        $monitor("Time=%0t | x0=%b x1=%b x2=%b x3=%b dec_1=%b | y0=%b y1=%b y2=%b y3=%b",
                 $time, x0, x1, x2, x3, dec_1, y0, y1, y2, y3);

        // Apply test cases
        #10 {x0, x1, x2, x3, dec_1} = 5'b00000;
        #10 {x0, x1, x2, x3, dec_1} = 5'b00001;
        #10 {x0, x1, x2, x3, dec_1} = 5'b00110;
        #10 {x0, x1, x2, x3, dec_1} = 5'b10101;
        #10 {x0, x1, x2, x3, dec_1} = 5'b11111;
        #10 {x0, x1, x2, x3, dec_1} = 5'b01010;

        // Finish simulation
        #20 $finish;
    end

endmodule
