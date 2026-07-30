`timescale 1ns/1ps

module sbox_tb;

    // DUT Inputs (all are single bits)
    reg clk;
    reg x0_0, x0_1;
    reg x1_0, x1_1;
    reg x2_0, x2_1;
    reg x3_0, x3_1;
    reg dec_1;
    // Declare all 23 random inputs
    reg rand_1, rand_2, rand_3, rand_4, rand_5, rand_6, rand_7, rand_8;
    reg rand_9, rand_10, rand_11, rand_12, rand_13, rand_14, rand_15, rand_16;
    reg rand_17, rand_18, rand_19, rand_20, rand_21, rand_22, rand_23;

    // DUT Outputs (all are single bits)
    wire y0_0, y0_1;
    wire y1_0, y1_1;
    wire y2_0, y2_1;
    wire y3_0, y3_1;

    // Testbench Variables
    integer fd, r, line_num;
    // Expected values read from CSV
    integer exp_y0, exp_y1, exp_y2, exp_y3, y0,y1,y2,y3,dec_0;
    reg [8*512:0] header; // Increased size for longer header

    // Instantiate the design under test (DUT)
    sbox uut (
        .clk(clk),
        .x0_0(x0_0), .x0_1(x0_1), .x1_0(x1_0), .x1_1(x1_1),
        .x2_0(x2_0), .x2_1(x2_1), .x3_0(x3_0), .x3_1(x3_1),
        .dec_1(dec_1),
        .rand_1(rand_1), .rand_2(rand_2), .rand_3(rand_3), .rand_4(rand_4),
        .rand_5(rand_5), .rand_6(rand_6), .rand_7(rand_7), .rand_8(rand_8),
        .rand_9(rand_9), .rand_10(rand_10), .rand_11(rand_11), .rand_12(rand_12),
        .rand_13(rand_13), .rand_14(rand_14), .rand_15(rand_15), .rand_16(rand_16),
        .rand_17(rand_17), .rand_18(rand_18), .rand_19(rand_19), .rand_20(rand_20),
        .rand_21(rand_21), .rand_22(rand_22), .rand_23(rand_23),
        .y0_0(y0_0), .y0_1(y0_1), .y1_0(y1_0), .y1_1(y1_1),
        .y2_0(y2_0), .y2_1(y2_1), .y3_0(y3_0), .y3_1(y3_1)
    );

    // Clock Generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    // Stimulus and Checking Process
    initial begin
        $dumpfile("sbox_tb.vcd");
        $dumpvars(0, sbox_tb);

        // --- PHASE 1: FLUSH PIPELINE ---
        {x0_0, x0_1, x1_0, x1_1, x2_0, x2_1, x3_0, x3_1, dec_1, dec_0} = 0;
        {rand_1, rand_2, rand_3, rand_4, rand_5, rand_6, rand_7, rand_8, rand_9, rand_10, rand_11, rand_12, rand_13, rand_14, rand_15, rand_16, rand_17, rand_18, rand_19, rand_20, rand_21, rand_22, rand_23} = 0;
        $display("Starting simulation with a long reset phase...");
        repeat (100) @(posedge clk);
        $display("Reset phase complete.");
        // -----------------------------

        fd = $fopen("test_vectors.csv", "r");
        if (fd == 0) begin
            $display("ERROR: Could not open test_vectors.csv");
            $finish;
        end

        r = $fgets(header, fd); // Skip header
        line_num = 0;

        // --- PHASE 2: PROCESS TEST VECTORS ---
        // $fscanf string now reads 40 columns
        r = $fscanf(fd, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                    x0_0, x0_1, x1_0, x1_1, x2_0, x2_1, x3_0, x3_1, dec_1, dec_0,
                    rand_1, rand_2, rand_3, rand_4, rand_5, rand_6, rand_7, rand_8,
                    rand_9, rand_10, rand_11, rand_12, rand_13, rand_14, rand_15,
                    rand_16, rand_17, rand_18, rand_19, rand_20, rand_21, rand_22, rand_23,
                    exp_y0, exp_y1, exp_y2, exp_y3,y0,y1,y2,y3
                   );
         repeat (100) @(posedge clk);
        // Loop ONLY while the scan is successful (r == 40)
        while (r == 41) begin
            line_num = line_num + 1;
            
            repeat(500) @(posedge clk);

            if ((y0_0 ^ y0_1) == y0 && (y1_0 ^ y1_1) == y1 &&
                (y2_0 ^ y2_1) == y2 && (y3_0 ^ y3_1) == y3) begin
                $display("Line %0d: PASS", line_num);
            end else begin
                $display("Line %0d: FAIL", line_num);
                $display("  -> Expected y0=%d, y1=%d, y2=%d, y3=%d", y0, y1, y2, y3);
                $display("  -> Got      y0=%d, y1=%d, y2=%d, y3=%d", (y0_0 ^ y0_1), (y1_0 ^ y1_1), (y2_0 ^ y2_1), (y3_0 ^ y3_1));
            end
            
            // Read the *next* line for the *next* loop iteration
            r = $fscanf(fd, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                        x0_0, x0_1, x1_0, x1_1, x2_0, x2_1, x3_0, x3_1, dec_1,dec_0,
                        rand_1, rand_2, rand_3, rand_4, rand_5, rand_6, rand_7, rand_8,
                        rand_9, rand_10, rand_11, rand_12, rand_13, rand_14, rand_15,
                        rand_16, rand_17, rand_18, rand_19, rand_20, rand_21, rand_22, rand_23,
                        exp_y0, exp_y1, exp_y2, exp_y3,y0,y1,y2,y3
                       );
        end

        $fclose(fd);
        $display("All test vectors processed.");
        #20 $finish;
    end

endmodule