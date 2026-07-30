`timescale 1ns / 1ps

module HPC3_tb;

    // Testbench Parameters
    parameter CLK_PERIOD = 10;   // Clock period in ns
    parameter NUM_TESTS  = 100;  // Number of random test vectors to run

    // Testbench Signals (regs for inputs, wires for outputs)
    reg clk;
    reg  [7:0] a[0:5];
    reg  [7:0] b[0:5];
    reg  [7:0] r[0:14]; // r01..r05, r12..r15, r23..r25, r34..r35, r45
    reg  [7:0] p[0:14]; // p01..p05, p12..p15, p23..p25, p34..p35, p45

    wire [7:0] c[0:5];

    // Instantiate the Device Under Test (DUT)
    HPC3 dut (
        .clk(clk),
        .a0(a[0]), .a1(a[1]), .a2(a[2]), .a3(a[3]), .a4(a[4]), .a5(a[5]),
        .b0(b[0]), .b1(b[1]), .b2(b[2]), .b3(b[3]), .b4(b[4]), .b5(b[5]),
        
        .r01(r[0]), .r02(r[1]), .r03(r[2]), .r04(r[3]), .r05(r[4]),
        .r12(r[5]), .r13(r[6]), .r14(r[7]), .r15(r[8]),
        .r23(r[9]), .r24(r[10]), .r25(r[11]),
        .r34(r[12]), .r35(r[13]),
        .r45(r[14]),

        .p01(p[0]), .p02(p[1]), .p03(p[2]), .p04(p[3]), .p05(p[4]),
        .p12(p[5]), .p13(p[6]), .p14(p[7]), .p15(p[8]),
        .p23(p[9]), .p24(p[10]), .p25(p[11]),
        .p34(p[12]), .p35(p[13]),
        .p45(p[14]),

        .c0(c[0]), .c1(c[1]), .c2(c[2]), .c3(c[3]), .c4(c[4]), .c5(c[5])
    );
    
    // Clock Generator
    always #((CLK_PERIOD)/2) clk = ~clk;
    
    // Main Test Logic
    initial begin
        // --- Moved all variable declarations to the top of the block ---
        integer i;
        integer test_num;
        reg  [7:0] a_original, b_original;
        reg  [7:0] c_expected, c_reconstructed;
        integer tests_passed = 0;
        integer tests_failed = 0;

        // Initialize all inputs to 0
        clk = 0;
        for (i = 0; i < 6; i = i + 1) begin
            a[i] = 8'h00;
            b[i] = 8'h00;
        end
        for (i = 0; i < 15; i = i + 1) begin
            r[i] = 8'h00;
            p[i] = 8'h00;
        end
        
        // Setup waveform dumping
        $dumpfile("hpc3_tb.vcd");
        $dumpvars(0, HPC3_tb);
        
        // Start the test after a small delay
        #CLK_PERIOD;
        $display("-------------------------------------------");
        $display("--- Starting HPC3 Module Verification ---");
        $display("-------------------------------------------");
        
        // Loop for multiple random tests
        for (test_num = 0; test_num < NUM_TESTS; test_num = test_num + 1) begin
            // 1. Generate random original values
            a_original = $random;
            b_original = $random;
            
            // 2. Generate random shares for 'a' and 'b'
            a[0] = $random; a[1] = $random; a[2] = $random; a[3] = $random; a[4] = $random;
            a[5] = a_original ^ a[0] ^ a[1] ^ a[2] ^ a[3] ^ a[4];
            
            b[0] = $random; b[1] = $random; b[2] = $random; b[3] = $random; b[4] = $random;
            b[5] = b_original ^ b[0] ^ b[1] ^ b[2] ^ b[3] ^ b[4];
            
            // 3. Generate random values for 'r' and 'p'
            for (i = 0; i < 15; i = i + 1) begin
                r[i] = $random;
                p[i] = $random;
            end
            
            // 4. Wait for a positive clock edge to apply inputs
            @(posedge clk);
            
            // 5. Wait one more cycle for the result to be computed
            @(posedge clk);
            #200
            // 6. Reconstruct the result from output shares
            c_reconstructed = c[0] ^ c[1] ^ c[2] ^ c[3] ^ c[4] ^ c[5];
            
            // 7. Calculate the expected result
            c_expected = a_original & b_original;
            
            // 8. Compare and report
            if (c_reconstructed === c_expected) begin
                tests_passed = tests_passed + 1;
                $display("✅ Test %0d PASSED: a=0x%h, b=0x%h -> c=0x%h", test_num, a_original, b_original, c_reconstructed);
            end else begin
                tests_failed = tests_failed + 1;
                $display("❌ Test %0d FAILED: a=0x%h, b=0x%h", test_num, a_original, b_original);
                $display("   Expected c = 0x%h,  Got c = 0x%h", c_expected, c_reconstructed);
            end
        end
        
        // Final Summary
        $display("-------------------------------------------");
        if (tests_failed == 0) begin
            $display("✅ All %0d tests passed!", tests_passed);
        end else begin
            $display("🚨 Test Summary: %0d Passed, %0d Failed", tests_passed, tests_failed);
        end
        $display("-------------------------------------------");
        
        // End simulation
        $finish;
    end

endmodule