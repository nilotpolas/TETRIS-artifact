`timescale 1ns/1ps

module verify_tb;

    // ── clock ──────────────────────────────────────────────────────────────
    reg clk = 0;
    always #5 clk = ~clk;

    // ── DUT signals ────────────────────────────────────────────────────────
    reg  tb_in_sb_n0_0;
    reg  tb_in_sb_n0_1;
    reg  tb_in_sb_n1_0;
    reg  tb_in_sb_n1_1;
    reg  tb_in_sb_n2_0;
    reg  tb_in_sb_n2_1;
    reg  tb_in_sb_n3_0;
    reg  tb_in_sb_n3_1;
    reg  tb_in_sb_n4_0;
    reg  tb_in_sb_n4_1;
    reg  tb_in_sb_n5_0;
    reg  tb_in_sb_n5_1;
    reg  tb_in_sb_n6_0;
    reg  tb_in_sb_n6_1;
    reg  tb_in_sb_n7_0;
    reg  tb_in_sb_n7_1;
    wire tb_out_sb_o0_0;
    wire tb_out_sb_o0_1;
    wire tb_out_sb_o1_0;
    wire tb_out_sb_o1_1;
    wire tb_out_sb_o2_0;
    wire tb_out_sb_o2_1;
    wire tb_out_sb_o3_0;
    wire tb_out_sb_o3_1;
    wire tb_out_sb_o4_0;
    wire tb_out_sb_o4_1;
    wire tb_out_sb_o5_0;
    wire tb_out_sb_o5_1;
    wire tb_out_sb_o6_0;
    wire tb_out_sb_o6_1;
    wire tb_out_sb_o7_0;
    wire tb_out_sb_o7_1;
    reg  [48-1:0] rand_bits;

    // ── DUT instantiation ──────────────────────────────────────────────────
    sbox dut (
    .clk(clk),
    .sb_n0_0(tb_in_sb_n0_0),
    .sb_n0_1(tb_in_sb_n0_1),
    .sb_n1_0(tb_in_sb_n1_0),
    .sb_n1_1(tb_in_sb_n1_1),
    .sb_n2_0(tb_in_sb_n2_0),
    .sb_n2_1(tb_in_sb_n2_1),
    .sb_n3_0(tb_in_sb_n3_0),
    .sb_n3_1(tb_in_sb_n3_1),
    .sb_n4_0(tb_in_sb_n4_0),
    .sb_n4_1(tb_in_sb_n4_1),
    .sb_n5_0(tb_in_sb_n5_0),
    .sb_n5_1(tb_in_sb_n5_1),
    .sb_n6_0(tb_in_sb_n6_0),
    .sb_n6_1(tb_in_sb_n6_1),
    .sb_n7_0(tb_in_sb_n7_0),
    .sb_n7_1(tb_in_sb_n7_1),
    .rand_1(rand_bits[0]),
    .rand_2(rand_bits[1]),
    .rand_3(rand_bits[2]),
    .rand_4(rand_bits[3]),
    .rand_5(rand_bits[4]),
    .rand_6(rand_bits[5]),
    .rand_7(rand_bits[6]),
    .rand_8(rand_bits[7]),
    .rand_9(rand_bits[8]),
    .rand_10(rand_bits[9]),
    .rand_11(rand_bits[10]),
    .rand_12(rand_bits[11]),
    .rand_13(rand_bits[12]),
    .rand_14(rand_bits[13]),
    .rand_15(rand_bits[14]),
    .rand_16(rand_bits[15]),
    .rand_17(rand_bits[16]),
    .rand_18(rand_bits[17]),
    .rand_19(rand_bits[18]),
    .rand_20(rand_bits[19]),
    .rand_21(rand_bits[20]),
    .rand_22(rand_bits[21]),
    .rand_23(rand_bits[22]),
    .rand_24(rand_bits[23]),
    .rand_25(rand_bits[24]),
    .rand_26(rand_bits[25]),
    .rand_27(rand_bits[26]),
    .rand_28(rand_bits[27]),
    .rand_29(rand_bits[28]),
    .rand_30(rand_bits[29]),
    .rand_31(rand_bits[30]),
    .rand_32(rand_bits[31]),
    .rand_33(rand_bits[32]),
    .rand_34(rand_bits[33]),
    .rand_35(rand_bits[34]),
    .rand_36(rand_bits[35]),
    .rand_37(rand_bits[36]),
    .rand_38(rand_bits[37]),
    .rand_39(rand_bits[38]),
    .rand_40(rand_bits[39]),
    .rand_41(rand_bits[40]),
    .rand_42(rand_bits[41]),
    .rand_43(rand_bits[42]),
    .rand_44(rand_bits[43]),
    .rand_45(rand_bits[44]),
    .rand_46(rand_bits[45]),
    .rand_47(rand_bits[46]),
    .rand_48(rand_bits[47]),
    .dec_1(1'b1),
    .sb_o0_0(tb_out_sb_o0_0),
    .sb_o0_1(tb_out_sb_o0_1),
    .sb_o1_0(tb_out_sb_o1_0),
    .sb_o1_1(tb_out_sb_o1_1),
    .sb_o2_0(tb_out_sb_o2_0),
    .sb_o2_1(tb_out_sb_o2_1),
    .sb_o3_0(tb_out_sb_o3_0),
    .sb_o3_1(tb_out_sb_o3_1),
    .sb_o4_0(tb_out_sb_o4_0),
    .sb_o4_1(tb_out_sb_o4_1),
    .sb_o5_0(tb_out_sb_o5_0),
    .sb_o5_1(tb_out_sb_o5_1),
    .sb_o6_0(tb_out_sb_o6_0),
    .sb_o6_1(tb_out_sb_o6_1),
    .sb_o7_0(tb_out_sb_o7_0),
    .sb_o7_1(tb_out_sb_o7_1)
    );

    // ── test variables ─────────────────────────────────────────────────────
    integer       x_val, trial, b, pass_cnt, fail_cnt;
    reg [7:0]     input_byte, golden, output_byte;
    reg [8-1:0] mask_bits;

    // Golden S-box (combinational LUT)
    task golden_sbox;
        input  [7:0] in;
        output [7:0] g;
        case (in)
            8'h00: g = 8'h63;
            8'h01: g = 8'h7c;
            8'h02: g = 8'h77;
            8'h03: g = 8'h7b;
            8'h04: g = 8'hf2;
            8'h05: g = 8'h6b;
            8'h06: g = 8'h6f;
            8'h07: g = 8'hc5;
            8'h08: g = 8'h30;
            8'h09: g = 8'h01;
            8'h0a: g = 8'h67;
            8'h0b: g = 8'h2b;
            8'h0c: g = 8'hfe;
            8'h0d: g = 8'hd7;
            8'h0e: g = 8'hab;
            8'h0f: g = 8'h76;
            8'h10: g = 8'hca;
            8'h11: g = 8'h82;
            8'h12: g = 8'hc9;
            8'h13: g = 8'h7d;
            8'h14: g = 8'hfa;
            8'h15: g = 8'h59;
            8'h16: g = 8'h47;
            8'h17: g = 8'hf0;
            8'h18: g = 8'had;
            8'h19: g = 8'hd4;
            8'h1a: g = 8'ha2;
            8'h1b: g = 8'haf;
            8'h1c: g = 8'h9c;
            8'h1d: g = 8'ha4;
            8'h1e: g = 8'h72;
            8'h1f: g = 8'hc0;
            8'h20: g = 8'hb7;
            8'h21: g = 8'hfd;
            8'h22: g = 8'h93;
            8'h23: g = 8'h26;
            8'h24: g = 8'h36;
            8'h25: g = 8'h3f;
            8'h26: g = 8'hf7;
            8'h27: g = 8'hcc;
            8'h28: g = 8'h34;
            8'h29: g = 8'ha5;
            8'h2a: g = 8'he5;
            8'h2b: g = 8'hf1;
            8'h2c: g = 8'h71;
            8'h2d: g = 8'hd8;
            8'h2e: g = 8'h31;
            8'h2f: g = 8'h15;
            8'h30: g = 8'h04;
            8'h31: g = 8'hc7;
            8'h32: g = 8'h23;
            8'h33: g = 8'hc3;
            8'h34: g = 8'h18;
            8'h35: g = 8'h96;
            8'h36: g = 8'h05;
            8'h37: g = 8'h9a;
            8'h38: g = 8'h07;
            8'h39: g = 8'h12;
            8'h3a: g = 8'h80;
            8'h3b: g = 8'he2;
            8'h3c: g = 8'heb;
            8'h3d: g = 8'h27;
            8'h3e: g = 8'hb2;
            8'h3f: g = 8'h75;
            8'h40: g = 8'h09;
            8'h41: g = 8'h83;
            8'h42: g = 8'h2c;
            8'h43: g = 8'h1a;
            8'h44: g = 8'h1b;
            8'h45: g = 8'h6e;
            8'h46: g = 8'h5a;
            8'h47: g = 8'ha0;
            8'h48: g = 8'h52;
            8'h49: g = 8'h3b;
            8'h4a: g = 8'hd6;
            8'h4b: g = 8'hb3;
            8'h4c: g = 8'h29;
            8'h4d: g = 8'he3;
            8'h4e: g = 8'h2f;
            8'h4f: g = 8'h84;
            8'h50: g = 8'h53;
            8'h51: g = 8'hd1;
            8'h52: g = 8'h00;
            8'h53: g = 8'hed;
            8'h54: g = 8'h20;
            8'h55: g = 8'hfc;
            8'h56: g = 8'hb1;
            8'h57: g = 8'h5b;
            8'h58: g = 8'h6a;
            8'h59: g = 8'hcb;
            8'h5a: g = 8'hbe;
            8'h5b: g = 8'h39;
            8'h5c: g = 8'h4a;
            8'h5d: g = 8'h4c;
            8'h5e: g = 8'h58;
            8'h5f: g = 8'hcf;
            8'h60: g = 8'hd0;
            8'h61: g = 8'hef;
            8'h62: g = 8'haa;
            8'h63: g = 8'hfb;
            8'h64: g = 8'h43;
            8'h65: g = 8'h4d;
            8'h66: g = 8'h33;
            8'h67: g = 8'h85;
            8'h68: g = 8'h45;
            8'h69: g = 8'hf9;
            8'h6a: g = 8'h02;
            8'h6b: g = 8'h7f;
            8'h6c: g = 8'h50;
            8'h6d: g = 8'h3c;
            8'h6e: g = 8'h9f;
            8'h6f: g = 8'ha8;
            8'h70: g = 8'h51;
            8'h71: g = 8'ha3;
            8'h72: g = 8'h40;
            8'h73: g = 8'h8f;
            8'h74: g = 8'h92;
            8'h75: g = 8'h9d;
            8'h76: g = 8'h38;
            8'h77: g = 8'hf5;
            8'h78: g = 8'hbc;
            8'h79: g = 8'hb6;
            8'h7a: g = 8'hda;
            8'h7b: g = 8'h21;
            8'h7c: g = 8'h10;
            8'h7d: g = 8'hff;
            8'h7e: g = 8'hf3;
            8'h7f: g = 8'hd2;
            8'h80: g = 8'hcd;
            8'h81: g = 8'h0c;
            8'h82: g = 8'h13;
            8'h83: g = 8'hec;
            8'h84: g = 8'h5f;
            8'h85: g = 8'h97;
            8'h86: g = 8'h44;
            8'h87: g = 8'h17;
            8'h88: g = 8'hc4;
            8'h89: g = 8'ha7;
            8'h8a: g = 8'h7e;
            8'h8b: g = 8'h3d;
            8'h8c: g = 8'h64;
            8'h8d: g = 8'h5d;
            8'h8e: g = 8'h19;
            8'h8f: g = 8'h73;
            8'h90: g = 8'h60;
            8'h91: g = 8'h81;
            8'h92: g = 8'h4f;
            8'h93: g = 8'hdc;
            8'h94: g = 8'h22;
            8'h95: g = 8'h2a;
            8'h96: g = 8'h90;
            8'h97: g = 8'h88;
            8'h98: g = 8'h46;
            8'h99: g = 8'hee;
            8'h9a: g = 8'hb8;
            8'h9b: g = 8'h14;
            8'h9c: g = 8'hde;
            8'h9d: g = 8'h5e;
            8'h9e: g = 8'h0b;
            8'h9f: g = 8'hdb;
            8'ha0: g = 8'he0;
            8'ha1: g = 8'h32;
            8'ha2: g = 8'h3a;
            8'ha3: g = 8'h0a;
            8'ha4: g = 8'h49;
            8'ha5: g = 8'h06;
            8'ha6: g = 8'h24;
            8'ha7: g = 8'h5c;
            8'ha8: g = 8'hc2;
            8'ha9: g = 8'hd3;
            8'haa: g = 8'hac;
            8'hab: g = 8'h62;
            8'hac: g = 8'h91;
            8'had: g = 8'h95;
            8'hae: g = 8'he4;
            8'haf: g = 8'h79;
            8'hb0: g = 8'he7;
            8'hb1: g = 8'hc8;
            8'hb2: g = 8'h37;
            8'hb3: g = 8'h6d;
            8'hb4: g = 8'h8d;
            8'hb5: g = 8'hd5;
            8'hb6: g = 8'h4e;
            8'hb7: g = 8'ha9;
            8'hb8: g = 8'h6c;
            8'hb9: g = 8'h56;
            8'hba: g = 8'hf4;
            8'hbb: g = 8'hea;
            8'hbc: g = 8'h65;
            8'hbd: g = 8'h7a;
            8'hbe: g = 8'hae;
            8'hbf: g = 8'h08;
            8'hc0: g = 8'hba;
            8'hc1: g = 8'h78;
            8'hc2: g = 8'h25;
            8'hc3: g = 8'h2e;
            8'hc4: g = 8'h1c;
            8'hc5: g = 8'ha6;
            8'hc6: g = 8'hb4;
            8'hc7: g = 8'hc6;
            8'hc8: g = 8'he8;
            8'hc9: g = 8'hdd;
            8'hca: g = 8'h74;
            8'hcb: g = 8'h1f;
            8'hcc: g = 8'h4b;
            8'hcd: g = 8'hbd;
            8'hce: g = 8'h8b;
            8'hcf: g = 8'h8a;
            8'hd0: g = 8'h70;
            8'hd1: g = 8'h3e;
            8'hd2: g = 8'hb5;
            8'hd3: g = 8'h66;
            8'hd4: g = 8'h48;
            8'hd5: g = 8'h03;
            8'hd6: g = 8'hf6;
            8'hd7: g = 8'h0e;
            8'hd8: g = 8'h61;
            8'hd9: g = 8'h35;
            8'hda: g = 8'h57;
            8'hdb: g = 8'hb9;
            8'hdc: g = 8'h86;
            8'hdd: g = 8'hc1;
            8'hde: g = 8'h1d;
            8'hdf: g = 8'h9e;
            8'he0: g = 8'he1;
            8'he1: g = 8'hf8;
            8'he2: g = 8'h98;
            8'he3: g = 8'h11;
            8'he4: g = 8'h69;
            8'he5: g = 8'hd9;
            8'he6: g = 8'h8e;
            8'he7: g = 8'h94;
            8'he8: g = 8'h9b;
            8'he9: g = 8'h1e;
            8'hea: g = 8'h87;
            8'heb: g = 8'he9;
            8'hec: g = 8'hce;
            8'hed: g = 8'h55;
            8'hee: g = 8'h28;
            8'hef: g = 8'hdf;
            8'hf0: g = 8'h8c;
            8'hf1: g = 8'ha1;
            8'hf2: g = 8'h89;
            8'hf3: g = 8'h0d;
            8'hf4: g = 8'hbf;
            8'hf5: g = 8'he6;
            8'hf6: g = 8'h42;
            8'hf7: g = 8'h68;
            8'hf8: g = 8'h41;
            8'hf9: g = 8'h99;
            8'hfa: g = 8'h2d;
            8'hfb: g = 8'h0f;
            8'hfc: g = 8'hb0;
            8'hfd: g = 8'h54;
            8'hfe: g = 8'hbb;
            8'hff: g = 8'h16;
            default: g = 8'hxx;
        endcase
    endtask

    initial begin
        pass_cnt  = 0;
        fail_cnt  = 0;
        rand_bits = 0;
        tb_in_sb_n0_0 = 0; tb_in_sb_n0_1 = 0; tb_in_sb_n1_0 = 0; tb_in_sb_n1_1 = 0; tb_in_sb_n2_0 = 0; tb_in_sb_n2_1 = 0; tb_in_sb_n3_0 = 0; tb_in_sb_n3_1 = 0; tb_in_sb_n4_0 = 0; tb_in_sb_n4_1 = 0; tb_in_sb_n5_0 = 0; tb_in_sb_n5_1 = 0; tb_in_sb_n6_0 = 0; tb_in_sb_n6_1 = 0; tb_in_sb_n7_0 = 0; tb_in_sb_n7_1 = 0;

        // flush pipeline before first valid output
        repeat (4 + 2) @(posedge clk);

        for (x_val = 0; x_val < 256; x_val = x_val + 1) begin
            input_byte = x_val[7:0];
            golden_sbox(input_byte, golden);

            for (trial = 0; trial < 16; trial = trial + 1) begin
                // fresh randomness each trial
                mask_bits = $urandom;
                rand_bits = $urandom;

                // apply masked inputs
            tb_in_sb_n0_0 = mask_bits[0];
            tb_in_sb_n0_1 = input_byte[0] ^ (mask_bits[0]);
            tb_in_sb_n1_0 = mask_bits[1];
            tb_in_sb_n1_1 = input_byte[1] ^ (mask_bits[1]);
            tb_in_sb_n2_0 = mask_bits[2];
            tb_in_sb_n2_1 = input_byte[2] ^ (mask_bits[2]);
            tb_in_sb_n3_0 = mask_bits[3];
            tb_in_sb_n3_1 = input_byte[3] ^ (mask_bits[3]);
            tb_in_sb_n4_0 = mask_bits[4];
            tb_in_sb_n4_1 = input_byte[4] ^ (mask_bits[4]);
            tb_in_sb_n5_0 = mask_bits[5];
            tb_in_sb_n5_1 = input_byte[5] ^ (mask_bits[5]);
            tb_in_sb_n6_0 = mask_bits[6];
            tb_in_sb_n6_1 = input_byte[6] ^ (mask_bits[6]);
            tb_in_sb_n7_0 = mask_bits[7];
            tb_in_sb_n7_1 = input_byte[7] ^ (mask_bits[7]);

                // clock in and wait for pipeline output.
                // MaskedHLS latency excludes the final output register, so
                // the output is valid after latency+1 rising edges.
                @(posedge clk);
                repeat (4) @(posedge clk);
                #1;   // small settle after last rising edge

                // recover output
        output_byte[0] = tb_out_sb_o0_0 ^ tb_out_sb_o0_1;
        output_byte[1] = tb_out_sb_o1_0 ^ tb_out_sb_o1_1;
        output_byte[2] = tb_out_sb_o2_0 ^ tb_out_sb_o2_1;
        output_byte[3] = tb_out_sb_o3_0 ^ tb_out_sb_o3_1;
        output_byte[4] = tb_out_sb_o4_0 ^ tb_out_sb_o4_1;
        output_byte[5] = tb_out_sb_o5_0 ^ tb_out_sb_o5_1;
        output_byte[6] = tb_out_sb_o6_0 ^ tb_out_sb_o6_1;
        output_byte[7] = tb_out_sb_o7_0 ^ tb_out_sb_o7_1;

                if (output_byte === golden) begin
                    pass_cnt = pass_cnt + 1;
                end else begin
                    fail_cnt = fail_cnt + 1;
                    if (fail_cnt <= 10)
                        $display("FAIL  input=0x%02x trial=%0d  expected=0x%02x  got=0x%02x",
                                 x_val, trial, golden, output_byte);
                end
            end
        end

        $display("\nRTL RESULT: %0d / 4096 passed", pass_cnt);
        if (fail_cnt == 0)
            $display("ALL TESTS PASSED");
        else
            $display("FAILED: %0d test(s)", fail_cnt);

        $finish;
    end
endmodule
