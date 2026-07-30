/**
 * @file sbox_tb.v
 * @brief Testbench for the pipelined S-box module.
 *
 * This testbench reads input vectors and expected outputs from a CSV file,
 * applies them to the sbox module (DUT), and verifies the results.
 * It is designed to handle the latency of the pipelined DUT by waiting
 * a fixed number of clock cycles before checking the output.
 */

`timescale 1ns / 1ps

module sbox_tb;

    // Testbench Parameters
    localparam CLK_PERIOD = 10; // Clock period in ns (100 MHz)
    localparam PIPELINE_DELAY = 50; // Latency of the DUT in clock cycles. ADJUST AS NEEDED.

    // --- Inputs to DUT (Device Under Test) ---
    reg clk;
    reg [7:0] x0_0, x0_1, x1_0, x1_1, x2_0, x2_1, x3_0, x3_1;
    reg [7:0] dec_1, dec_0, dec_2, dec_3;
    reg [7:0] rand_1, rand_2, rand_3, rand_4;

    // --- Outputs from DUT ---
    wire [7:0] output_0, output_1;

    // --- Testbench Internal Variables ---
    integer file_handle, scan_status, error_count, vector_count;
    
    // Variables to hold values read from the CSV file. Names match CSV header.
    reg [7:0] csv_x00, csv_x01, csv_x10, csv_x11;
    reg [7:0] csv_x20, csv_x21, csv_x30, csv_x31;
    reg [7:0] csv_const_in1, csv_const_in2, csv_const_in3, csv_const_in4;
    reg [7:0] csv_rand_in2, csv_rand_in3, csv_rand_in1, csv_rand_in4;
    reg [7:0] csv_expected_output;
    
    reg [7:0] actual_output;
    
    // **FIX**: Declare a dummy variable to hold the CSV header.
    reg [1023:0] header_dummy;

    // Instantiate the Device Under Test (DUT)
    sbox dut (
        .clk(clk),
        .x0_0(x0_0), .x0_1(x0_1), .x1_0(x1_0), .x1_1(x1_1),
        .x2_0(x2_0), .x2_1(x2_1), .x3_0(x3_0), .x3_1(x3_1),
        .dec_1(dec_1), .dec_0(dec_0), .dec_2(dec_2), .dec_3(dec_3),
        .rand_1(rand_1), .rand_2(rand_2), .rand_3(rand_3), .rand_4(rand_4),
        .output_0(output_0), .output_1(output_1)
    );

    // 1. Clock Generator
    initial begin
        clk = 0;
        forever #(CLK_PERIOD / 2) clk = ~clk;
    end

    // 2. Main Test Sequence
    initial begin
        $display("--------------------------------------------------");
        $display("--- Starting S-Box Testbench Simulation ---");
        $display("--------------------------------------------------");

        error_count = 0;
        vector_count = 0;
        
        file_handle = $fopen("sbox_test_vectors.csv", "r");
        if (file_handle == 0) begin
            $display("ERROR: Could not open 'sbox_test_vectors.csv'.");
            $finish;
        end

        // **FIX**: Read and discard the CSV header line into the dummy variable.
        scan_status = $fscanf(file_handle, "%s\n", header_dummy); 

        // Loop through each data line in the CSV
        while (!$feof(file_handle)) begin
            scan_status = $fscanf(file_handle, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                csv_x00, csv_x01, csv_x10, csv_x11,
                csv_x20, csv_x21, csv_x30, csv_x31,
                csv_const_in1, csv_const_in2, csv_const_in3, csv_const_in4,
                csv_rand_in2, csv_rand_in3, csv_rand_in1, csv_rand_in4,
                csv_expected_output);

            @(posedge clk);
            x0_0 <= csv_x00; x0_1 <= csv_x01;
            x1_0 <= csv_x10; x1_1 <= csv_x11;
            x2_0 <= csv_x20; x2_1 <= csv_x21;
            x3_0 <= csv_x30; x3_1 <= csv_x31;
            dec_1 <= csv_const_in1; dec_0 <= csv_const_in2;
            dec_2 <= csv_const_in3; dec_3 <= csv_const_in4;
            rand_2 <= csv_rand_in2; rand_3 <= csv_rand_in3;
            rand_1 <= csv_rand_in1; rand_4 <= csv_rand_in4;
            vector_count = vector_count + 1;

            // Wait for the pipeline to process the data
            repeat (PIPELINE_DELAY) @(posedge clk);

            // --- Verification ---
            actual_output = output_0 ^ output_1;
            
            if (actual_output === csv_expected_output) begin
                $display("Vector %0d: [PASS] - Input (unshared): %x -> Output: %x (Expected: %x)",
                         vector_count, (csv_x30^csv_x31)*8 + (csv_x20^csv_x21)*4 + (csv_x10^csv_x11)*2 + (csv_x00^csv_x01),
                         actual_output, csv_expected_output);
            end else begin
                $display("Vector %0d: [FAIL] - Input (unshared): %x -> Output: %x (Expected: %x)",
                         vector_count, (csv_x30^csv_x31)*8 + (csv_x20^csv_x21)*4 + (csv_x10^csv_x11)*2 + (csv_x00^csv_x01),
                         actual_output, csv_expected_output);
                error_count = error_count + 1;
            end
        end

        // --- Simulation Summary ---
        $display("--------------------------------------------------");
        if (error_count == 0) begin
            $display("--- ✅ All %0d tests passed! ---", vector_count);
        end else begin
            $display("--- ❌ Simulation finished with %0d error(s). ---", error_count);
        end
        $display("--------------------------------------------------");

        $fclose(file_handle);
        $finish;
    end

endmodule

