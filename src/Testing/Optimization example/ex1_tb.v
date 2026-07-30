`timescale 1ns / 1ps

module tb_fun;

    // --- 1. Signal Declaration ---
    reg clk;
    
    // Logic Inputs
    reg a_0, a_1;
    reg b_0, b_1;
    reg c_0, c_1;
    reg d_0, d_1;
    
    // Random Inputs (Masks)
    reg rand_1, rand_2, rand_3, rand_4, rand_5;
    reg rand_6, rand_7, rand_8, rand_9, rand_10;
    reg rand_11, rand_12, rand_13, rand_14;

    // Outputs
    wire r_0;
    wire r_1;

    // Variables for File I/O
    integer file_handle;
    integer scan_result;
    // Buffer for reading the CSV header (Fix for Icarus Verilog)
    reg [8*100:1] header_str; 
    
    integer a_in, b_in, c_in, d_in, r_expected;
    integer pass_count = 0;
    integer fail_count = 0;
    integer r_actual;

    // --- 2. Instantiate the Module ---
    fun uut (
        .clk(clk),
        .a_0(a_0), .a_1(a_1),
        .b_0(b_0), .b_1(b_1),
        .c_0(c_0), .c_1(c_1),
        .d_0(d_0), .d_1(d_1),
        // Connect Random Inputs (Order matches your module definition)
        .rand_2(rand_2), .rand_7(rand_7), .rand_1(rand_1), 
        .rand_5(rand_5), .rand_8(rand_8), .rand_12(rand_12), 
        .rand_11(rand_11), .rand_13(rand_13), .rand_14(rand_14), 
        .rand_4(rand_4), .rand_3(rand_3), .rand_6(rand_6), 
        .rand_10(rand_10), .rand_9(rand_9),
        // Outputs
        .r_0(r_0), .r_1(r_1)
    );

    // --- 3. Clock Generation ---
    initial begin
        clk = 0;
        forever #5 clk = ~clk; // 10ns period
    end

    // --- 4. Main Test Sequence ---
    initial begin
        // Initialize Inputs
        a_0 = 0; a_1 = 0;
        b_0 = 0; b_1 = 0;
        c_0 = 0; c_1 = 0;
        d_0 = 0; d_1 = 0;
        
        // Open CSV
        file_handle = $fopen("expected_outputs.csv", "r");
        if (file_handle == 0) begin
            $display("ERROR: Could not open expected_outputs.csv");
            $finish;
        end

        // Read and discard header line
        scan_result = $fgets(header_str, file_handle);

        $display("==========================================================");
        $display("STARTING VERIFICATION OF MASKED PIPELINE");
        $display("==========================================================");
        $display("Time | A B C D | Exp | Act | Shares(r0,r1) | Result");

        // Loop through file
        while (!$feof(file_handle)) begin
            scan_result = $fscanf(file_handle, "%d,%d,%d,%d,%d\n", a_in, b_in, c_in, d_in, r_expected);
            
            if (scan_result == 5) begin
                // A. Apply Inputs (Boolean masking: S0 = val, S1 = 0)
                a_0 = a_in; a_1 = 0;
                b_0 = b_in; b_1 = 0;
                c_0 = c_in; c_1 = 0;
                d_0 = d_in; d_1 = 0;

                // B. Randomize noise inputs
                rand_1 = $random; rand_2 = $random; rand_3 = $random; 
                rand_4 = $random; rand_5 = $random; rand_6 = $random;
                rand_7 = $random; rand_8 = $random; rand_9 = $random;
                rand_10 = $random; rand_11 = $random; rand_12 = $random;
                rand_13 = $random; rand_14 = $random;

                // C. Wait for Pipeline
                // This pipeline is deep (~6-8 layers of registers). 
                // We wait 50 cycles to ensure output is stable and flushed.
                repeat (50) @(posedge clk);

                // D. Check Result
                r_actual = r_0 ^ r_1; // Reconstruct output
                
                if (r_actual === r_expected) begin
                    $display("%4t | %d %d %d %d |  %d  |  %d  |    (%b,%b)    | PASS", 
                             $time, a_in, b_in, c_in, d_in, r_expected, r_actual, r_0, r_1);
                    pass_count = pass_count + 1;
                end else begin
                    $display("%4t | %d %d %d %d |  %d  |  %d  |    (%b,%b)    | FAIL", 
                             $time, a_in, b_in, c_in, d_in, r_expected, r_actual, r_0, r_1);
                    fail_count = fail_count + 1;
                end
            end
        end

        $fclose(file_handle);
        $display("==========================================================");
        $display("TEST COMPLETE. Passed: %d, Failed: %d", pass_count, fail_count);
        $display("==========================================================");
        $finish;
    end

endmodule