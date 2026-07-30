`timescale 1ns/1ps

module fun_tb;

    // DUT Inputs
    reg clk;
    reg [7:0] a_0;
    reg [7:0] a_1;
    reg [7:0] d_0;
    reg [7:0] d_1;
    reg [7:0] b_0;
    reg [7:0] b_1;
    reg [7:0] c_0;
    reg [7:0] c_1;
    reg [7:0] rand_1;
    reg [7:0] rand_2;
    reg [7:0] rand_3;
    reg [7:0] rand_4;
    reg [7:0] rand_5;
    reg [7:0] rand_6;
    reg [7:0] rand_7;
    // reg [7:0] rand_8;


    // DUT Outputs
    wire [7:0] r_0;
    wire [7:0] r_1;

    // Testbench Variables
    integer fd, r;
    integer line_num;
    integer a, b, c, d, out,out2, x, timeout_counter;
    reg [8*256:0] header;

    // Instantiate the design under test (DUT)
    fun uut (
        .clk(clk),
        .a_0(a_0), .a_1(a_1),
        .d_0(d_0), .d_1(d_1),
        .b_0(b_0), .b_1(b_1),
        .c_0(c_0), .c_1(c_1),
        .rand_1(rand_1), .rand_2(rand_2), .rand_3(rand_3),
        .rand_4(rand_4), .rand_5(rand_5), .rand_6(rand_6),.rand_7(rand_7),
        .r_0(r_0), .r_1(r_1)
    );

    // Clock Generation (100 MHz)
    initial begin
        clk = 0;
        forever #5 clk = ~clk; // 10ns period
    end

    // Stimulus and Checking Process
    initial begin
        $dumpfile("fun_tb.vcd");
        $dumpvars(0, fun_tb);

        // --- PHASE 1: RESET THE DUT ---
        $display("Starting simulation with reset phase...");
        a_0 = 8'd0; a_1 = 8'd0; d_0 = 8'd0; d_1 = 8'd0;
        b_0 = 8'd0; b_1 = 8'd0; c_0 = 8'd0; c_1 = 8'd0;
        rand_1 = 8'd0; rand_2 = 8'd0; rand_3 = 8'd0;
        rand_4 = 8'd0; rand_5 = 8'd0; rand_6 = 8'd0;
        rand_7 = 8'd0; //rand_8 = 8'd0;
        
        // Hold inputs at 0 for 30 cycles to flush the pipeline
        repeat (30) @(posedge clk);
        $display("Reset phase complete. Starting test vectors...");
        // -----------------------------

        fd = $fopen("test_vectors.csv", "r");
        if (fd == 0) begin
            $display("ERROR: Could not open test_vectors.csv");
            $finish;
        end

        r = $fgets(header, fd);
        line_num = 0;

        // --- PHASE 2: PROCESS TEST VECTORS ---
        while (!$feof(fd)) begin
            line_num = line_num + 1;
            
            r = $fscanf(fd, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                        a_0, a_1, b_0, b_1, c_0, c_1, d_0, d_1,
                        rand_1, rand_2, rand_3, rand_4, rand_5, rand_6,rand_7,
                        a, b, c, d, out,out2);

            // Latch the new inputs on the next clock edge
            @(posedge clk);

            // --- Wait-for-Result Loop with a 200-cycle Timeout ---
            // integer timeout_counter;
            timeout_counter = 0;
            
            while ((r_0 ^ r_1) != out2 && timeout_counter < 2000) begin
                @(posedge clk);
                timeout_counter = timeout_counter + 1;
            end
            // ----------------------------------------------------

            // Capture the final result
            x = (r_0 ^ r_1);

            // Check and display the result
            if (timeout_counter >= 2000) begin
                $display("Line %0d: FAIL (Timeout!) expected=%0d  return=%0d", line_num, out, x);
            end else if (x == out) begin // Use === for safe X/Z checking
                $display("Line %0d: PASS (found in %0d cycles) expected=%0d  return=%0d",
                         line_num, timeout_counter + 1, out, x);
            end else begin
                // This case should not be reached due to the while loop condition
                 $display("Line %0d: FAIL (Logic Error!) expected=%0d  return=%0d", line_num, out, x);
            end
        end

        $fclose(fd);
        $display("All test vectors processed.");
        #20 $finish;
    end

endmodule