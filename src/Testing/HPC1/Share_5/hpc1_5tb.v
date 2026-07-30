/*
 * Verilog Testbench for HPC1 Gadget (d=5)
 * Reads test vectors from "test_vectors_d5.csv"
 */

`timescale 1ns/1ps

module HPC1_tb;

    // Signals
    reg clk;
    
    // d=5 (6 shares)
    reg  [7:0] a0, a1, a2, a3, a4, a5;
    reg  [7:0] b0, b1, b2, b3, b4, b5;
    wire [7:0] c0, c1, c2, c3, c4, c5;

    // d=5 rand inputs
    // 5 rand_i signals
    reg  [7:0] rand_0, rand_1, rand_2, rand_3, rand_4;
    // 15 prand_ij signals
    reg  [7:0] prand_01, prand_02, prand_03, prand_04, prand_05;
    reg  [7:0] prand_12, prand_13, prand_14, prand_15;
    reg  [7:0] prand_23, prand_24, prand_25;
    reg  [7:0] prand_34, prand_35;
    reg  [7:0] prand_45;


    integer fd, r;
    integer line_num;
    integer exp_a, exp_b, exp_c, c_unshared;
    reg [8*1024:0] header; // to skip header line in CSV (increased size)

    // Instantiate DUT (Device Under Test)
    // Make sure your HPC1 module definition matches this port order
    HPC1 uut (
        .clk(clk),
        
        // a shares
        .a0(a0), .a1(a1), .a2(a2), .a3(a3), .a4(a4), .a5(a5),
        
        // b shares
        .b0(b0), .b1(b1), .b2(b2), .b3(b3), .b4(b4), .b5(b5),
        
        // c shares
        .c0(c0), .c1(c1), .c2(c2), .c3(c3), .c4(c4), .c5(c5),

        // rand signals
        .rand_0(rand_0), .rand_1(rand_1), .rand_2(rand_2), .rand_3(rand_3), .rand_4(rand_4),
        
        // prand signals
        .prand_01(prand_01), .prand_02(prand_02), .prand_03(prand_03), .prand_04(prand_04), .prand_05(prand_05),
        .prand_12(prand_12), .prand_13(prand_13), .prand_14(prand_14), .prand_15(prand_15),
        .prand_23(prand_23), .prand_24(prand_24), .prand_25(prand_25),
        .prand_34(prand_34), .prand_35(prand_35),
        .prand_45(prand_45)
    );

    // Clock
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    // Stimulus
    initial begin
        // VCD dump
        $dumpfile("HPC1_tb_d5.vcd");
        $dumpvars(0, HPC1_tb);

        // Open CSV file
        fd = $fopen("test_vectors_d5.csv", "r");
        if (fd == 0) begin
            $display("ERROR: Could not open test_vectors_d5.csv");
            $finish;
        end

        // Skip header
        r = $fgets(header, fd);

        line_num = 0;

        // Read lines until EOF
        while (!$feof(fd)) begin
            line_num = line_num + 1;

            // Read all 35 columns from the CSV
            r = $fscanf(fd, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                        // a shares (6)
                        a0, a1, a2, a3, a4, a5,
                        // b shares (6)
                        b0, b1, b2, b3, b4, b5,
                        // rand (5)
                        rand_0, rand_1, rand_2, rand_3, rand_4,
                        // prand (15)
                        prand_01, prand_02, prand_03, prand_04, prand_05,
                        prand_12, prand_13, prand_14, prand_15,
                        prand_23, prand_24, prand_25,
                        prand_34, prand_35,
                        prand_45,
                        // expected (3)
                        exp_a, exp_b, exp_c);
            
            // Check if fscanf read all items. If r=0, it's likely end of file.
            // if (r == 0) continue; 
            
            @(posedge clk); // wait 1 cycle for inputs to propagate
            #400; // Wait for DUT to compute (adjust as needed)

            // Check logic for d=5
            c_unshared = c0 ^ c1 ^ c2 ^ c3 ^ c4 ^ c5;
            
            if (c_unshared === exp_c)
                $display("Line %0d: PASS -> c_unshared=%0d expected=%0d",
                         line_num, c_unshared, exp_c);
            else
                $display("Line %0d: FAIL -> c_unshared=%0d expected=%0d",
                         line_num, c_unshared, exp_c);
        end

        $fclose(fd);
        $display("All test vectors processed.");
        #20 $finish;
    end

endmodule
