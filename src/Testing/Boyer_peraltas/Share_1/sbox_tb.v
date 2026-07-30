`timescale 1ns / 1ps

module sbox_tb;

    // Testbench parameters
    parameter CLK_PERIOD = 10; // 10ns clock period
    parameter DATA_FILE  = "sbox_simulation.csv";

    // Testbench signals
    reg         clk;
    reg [7:0]   X_shares_0;
    reg [7:0]   X_shares_1;
    reg         dec_1_tb;
    reg [33:0]  rand_inputs;

    wire [7:0]  Y_shares_0;
    wire [7:0]  Y_shares_1;
    
    integer     file_handle;
    integer     scan_status;
    integer     line_count;
    integer     error_count;

    reg [7:0]   x_unshared_from_csv;
    reg [7:0]   y_expected_unshared_from_csv;
    
    reg [7:0]   y_calculated_recombined;

    // Instantiate the Device Under Test (DUT)
    sbox dut (
        .clk(clk),
        .X0_0(X_shares_0[0]), .X0_1(X_shares_1[0]),
        .X1_0(X_shares_0[1]), .X1_1(X_shares_1[1]),
        .X2_0(X_shares_0[2]), .X2_1(X_shares_1[2]),
        .X3_0(X_shares_0[3]), .X3_1(X_shares_1[3]),
        .X4_0(X_shares_0[4]), .X4_1(X_shares_1[4]),
        .X5_0(X_shares_0[5]), .X5_1(X_shares_1[5]),
        .X6_0(X_shares_0[6]), .X6_1(X_shares_1[6]),
        .X7_0(X_shares_0[7]), .X7_1(X_shares_1[7]),
        .dec_1(dec_1_tb),
        .rand_1(rand_inputs[0]),   .rand_2(rand_inputs[1]),   .rand_3(rand_inputs[2]),
        .rand_4(rand_inputs[3]),   .rand_5(rand_inputs[4]),   .rand_6(rand_inputs[5]),
        .rand_7(rand_inputs[6]),   .rand_8(rand_inputs[7]),   .rand_9(rand_inputs[8]),
        .rand_10(rand_inputs[9]),  .rand_11(rand_inputs[10]), .rand_12(rand_inputs[11]),
        .rand_13(rand_inputs[12]), .rand_14(rand_inputs[13]), .rand_15(rand_inputs[14]),
        .rand_16(rand_inputs[15]), .rand_17(rand_inputs[16]), .rand_18(rand_inputs[17]),
        .rand_19(rand_inputs[18]), .rand_20(rand_inputs[19]), .rand_21(rand_inputs[20]),
        .rand_22(rand_inputs[21]), .rand_23(rand_inputs[22]), .rand_24(rand_inputs[23]),
        .rand_25(rand_inputs[24]), .rand_26(rand_inputs[25]), .rand_27(rand_inputs[26]),
        .rand_28(rand_inputs[27]), .rand_29(rand_inputs[28]), .rand_30(rand_inputs[29]),
        .rand_31(rand_inputs[30]), .rand_32(rand_inputs[31]), .rand_33(rand_inputs[32]),
        .rand_34(rand_inputs[33]),
        .Y0_0(Y_shares_0[0]), .Y0_1(Y_shares_1[0]),
        .Y1_0(Y_shares_0[1]), .Y1_1(Y_shares_1[1]),
        .Y2_0(Y_shares_0[2]), .Y2_1(Y_shares_1[2]),
        .Y3_0(Y_shares_0[3]), .Y3_1(Y_shares_1[3]),
        .Y4_0(Y_shares_0[4]), .Y4_1(Y_shares_1[4]),
        .Y5_0(Y_shares_0[5]), .Y5_1(Y_shares_1[5]),
        .Y6_0(Y_shares_0[6]), .Y6_1(Y_shares_1[6]),
        .Y7_0(Y_shares_0[7]), .Y7_1(Y_shares_1[7])
    );

    // Clock Generator
    always #((CLK_PERIOD)/2) clk = ~clk;

    // Main Test Procedure
    initial begin
        integer i;
        reg random_bit;
        // --- CHANGE #1: DECLARE A REGISTER TO HOLD THE HEADER LINE ---
        reg [1023:0] header_buffer; // 1024 * 8 bits, large enough for a line

        $display("--- Starting S-Box Verilog Testbench ---");
        
        clk <= 0;
        X_shares_0 <= 0;
        X_shares_1 <= 0;
        dec_1_tb <= 0;
        rand_inputs <= 0;
        line_count = 0;
        error_count = 0;

        file_handle = $fopen(DATA_FILE, "r");
        if (file_handle == 0) begin
            $display("ERROR: Could not open data file: %s", DATA_FILE);
            $finish;
        end
        
        // --- CHANGE #2: USE $fgets TO READ AND DISCARD THE HEADER ---
        $fgets(header_buffer, file_handle);

        while (!$feof(file_handle)) begin
            line_count = line_count + 1;
            
            scan_status = $fscanf(file_handle, "%b,%b,%b,%b,%b,%b,%b,%b,%b,%b,%b,%b,%b,%b,%b,%b\n",
                x_unshared_from_csv[0], x_unshared_from_csv[1], x_unshared_from_csv[2], x_unshared_from_csv[3], 
                x_unshared_from_csv[4], x_unshared_from_csv[5], x_unshared_from_csv[6], x_unshared_from_csv[7],
                y_expected_unshared_from_csv[0], y_expected_unshared_from_csv[1], y_expected_unshared_from_csv[2], y_expected_unshared_from_csv[3],
                y_expected_unshared_from_csv[4], y_expected_unshared_from_csv[5], y_expected_unshared_from_csv[6], y_expected_unshared_from_csv[7]
            );

            @(posedge clk);

            for (i = 0; i < 8; i = i + 1) begin
                random_bit = $random % 2;
                X_shares_0[i] <= random_bit;
                X_shares_1[i] <= x_unshared_from_csv[i] ^ random_bit;
            end
            
            rand_inputs <= $random;
            rand_inputs[33:32] <= $random % 4;
            dec_1_tb <= 1;

            @(posedge clk);
            #200
            y_calculated_recombined = Y_shares_0 ^ Y_shares_1;

            if (y_calculated_recombined === y_expected_unshared_from_csv) begin
                $display("Test %3d: PASS (Input: %d) --> (Output: %d)", line_count, x_unshared_from_csv, y_calculated_recombined);
            end else begin
                $display("Test %3d: FAIL!", line_count);
                $display("  Input (x7..x0):         %8b", x_unshared_from_csv);
                $display("  Expected Output (y7..y0): %8b", y_expected_unshared_from_csv);
                $display("  Calculated Output(y7..y0): %8b", y_calculated_recombined);
                error_count = error_count + 1;
            end
            
            dec_1_tb <= 0;
        end

        $fclose(file_handle);
        $display("--- Testbench Finished ---");
        if (error_count == 0) begin
            $display("✅ All %d tests passed successfully!", line_count);
        end else begin
            $display("❌ Verification failed with %d error(s).", error_count);
        end
        $finish;
    end

endmodule