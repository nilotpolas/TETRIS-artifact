`timescale 1ns/1ps

module HPC2_tb;

    // Signals
    reg clk;
    reg   [7:0] a0, a1;
    reg   [7:0] b0, b1;
    reg   [7:0] rand_01;
    wire  [7:0] c0, c1;

    integer fd, r;
    integer line_num;
    integer exp_a, exp_b, exp_c;
    reg [8*256:0] header; // to skip header line in CSV

    // Instantiate DUT
    HPC2 uut (
        .clk(clk),
        .a0(a0), .a1(a1),
        .b0(b0), .b1(b1),
        .rand_01(rand_01),
        .c0(c0), .c1(c1)
    );

    // Clock
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    // Stimulus
    initial begin
        // VCD dump
        $dumpfile("hpc2_tb.vcd");
        $dumpvars(0, HPC2_tb);

        // Open CSV file
        fd = $fopen("test_vectors.csv", "r");
        if (fd == 0) begin
            $display("ERROR: Could not open test_vectors.csv");
            $finish;
        end

        // Skip header
        r = $fgets(header, fd);

        line_num = 0;

        // Read lines until EOF
        while (!$feof(fd)) begin
            line_num = line_num + 1;

            r = $fscanf(fd, "%d,%d,%d,%d,%d,%d,%d,%d\n",
                        a0, a1, b0, b1, rand_01,
                        exp_a, exp_b, exp_c);

            @(posedge clk); // wait 1 cycle for DUT to compute
            #30;
            if ((c0 ^ c1) == exp_c)
                $display("Line %0d: PASS (a0=%0d a1=%0d b0=%0d b1=%0d r=%0d) -> c0^c1=%0d expected=%0d",
                         line_num, a0, a1, b0, b1, rand_01, (c0 ^ c1), exp_c);
            else
                $display("Line %0d: FAIL (a0=%0d a1=%0d b0=%0d b1=%0d r=%0d c0=%0d c1=%0d) -> c0^c1=%0d expected=%0d",
                         line_num, a0, a1, b0, b1, rand_01, c0, c1, (c0 ^ c1), exp_c);
        end

        $fclose(fd);
        $display("All test vectors processed.");
        #20 $finish;
    end

endmodule
