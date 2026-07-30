`timescale 1ns/1ps

module tb_sbox();

    // Clock and Control
    reg clk;
    reg dec_1;
    
    // S-Box Inputs
    reg sb_n0_0, sb_n0_1;
    reg sb_n1_0, sb_n1_1;
    reg sb_n2_0, sb_n2_1;
    reg sb_n3_0, sb_n3_1;
    reg sb_n4_0, sb_n4_1;
    reg sb_n5_0, sb_n5_1;
    reg sb_n6_0, sb_n6_1;
    reg sb_n7_0, sb_n7_1;
    
    // Random Inputs
    reg rand_1, rand_2, rand_3, rand_4, rand_5, rand_6, rand_7, rand_8;
    reg rand_9, rand_10, rand_11, rand_12, rand_13, rand_14, rand_15, rand_16;
    reg rand_17, rand_18, rand_19, rand_20, rand_21, rand_22, rand_23, rand_24;
    reg rand_25, rand_26, rand_27, rand_28, rand_29, rand_30, rand_31, rand_32;
    reg rand_33, rand_34, rand_35, rand_36, rand_37, rand_38, rand_39, rand_40;
    reg rand_41, rand_42, rand_43, rand_44, rand_45, rand_46, rand_47, rand_48;

    // S-Box Outputs
    wire sb_o0_0, sb_o0_1;
    wire sb_o1_0, sb_o1_1;
    wire sb_o2_0, sb_o2_1;
    wire sb_o3_0, sb_o3_1;
    wire sb_o4_0, sb_o4_1;
    wire sb_o5_0, sb_o5_1;
    wire sb_o6_0, sb_o6_1;
    wire sb_o7_0, sb_o7_1;

    // Instantiate the DUT (Device Under Test)
    sbox dut (
        .clk(clk),
        .sb_n0_0(sb_n0_0), .sb_n0_1(sb_n0_1),
        .sb_n1_0(sb_n1_0), .sb_n1_1(sb_n1_1),
        .sb_n2_0(sb_n2_0), .sb_n2_1(sb_n2_1),
        .sb_n3_0(sb_n3_0), .sb_n3_1(sb_n3_1),
        .sb_n4_0(sb_n4_0), .sb_n4_1(sb_n4_1),
        .sb_n5_0(sb_n5_0), .sb_n5_1(sb_n5_1),
        .sb_n6_0(sb_n6_0), .sb_n6_1(sb_n6_1),
        .sb_n7_0(sb_n7_0), .sb_n7_1(sb_n7_1),
        .dec_1(dec_1),
        .rand_15(rand_15), .rand_30(rand_30), .rand_47(rand_47), .rand_16(rand_16), 
        .rand_32(rand_32), .rand_48(rand_48), .rand_1(rand_1),   .rand_17(rand_17), 
        .rand_33(rand_33), .rand_18(rand_18), .rand_2(rand_2),   .rand_35(rand_35), 
        .rand_3(rand_3),   .rand_19(rand_19), .rand_34(rand_34), .rand_4(rand_4), 
        .rand_26(rand_26), .rand_36(rand_36), .rand_5(rand_5),   .rand_20(rand_20), 
        .rand_37(rand_37), .rand_6(rand_6),   .rand_21(rand_21), .rand_38(rand_38), 
        .rand_8(rand_8),   .rand_22(rand_22), .rand_29(rand_29), .rand_39(rand_39), 
        .rand_46(rand_46), .rand_7(rand_7),   .rand_23(rand_23), .rand_41(rand_41), 
        .rand_9(rand_9),   .rand_24(rand_24), .rand_42(rand_42), .rand_10(rand_10), 
        .rand_31(rand_31), .rand_40(rand_40), .rand_11(rand_11), .rand_25(rand_25), 
        .rand_44(rand_44), .rand_12(rand_12), .rand_27(rand_27), .rand_43(rand_43), 
        .rand_13(rand_13), .rand_28(rand_28), .rand_45(rand_45), .rand_14(rand_14),
        .sb_o0_0(sb_o0_0), .sb_o0_1(sb_o0_1),
        .sb_o1_0(sb_o1_0), .sb_o1_1(sb_o1_1),
        .sb_o2_0(sb_o2_0), .sb_o2_1(sb_o2_1),
        .sb_o3_0(sb_o3_0), .sb_o3_1(sb_o3_1),
        .sb_o4_0(sb_o4_0), .sb_o4_1(sb_o4_1),
        .sb_o5_0(sb_o5_0), .sb_o5_1(sb_o5_1),
        .sb_o6_0(sb_o6_0), .sb_o6_1(sb_o6_1),
        .sb_o7_0(sb_o7_0), .sb_o7_1(sb_o7_1)
    );

    // Standard AES S-Box Reference
    reg [7:0] aes_ref [0:255];
    initial begin
        aes_ref[0] = 8'h63; aes_ref[1] = 8'h7c; aes_ref[2] = 8'h77; aes_ref[3] = 8'h7b; 
        aes_ref[4] = 8'hf2; aes_ref[5] = 8'h6b; aes_ref[6] = 8'h6f; aes_ref[7] = 8'hc5;
        aes_ref[8] = 8'h30; aes_ref[9] = 8'h01; aes_ref[10] = 8'h67; aes_ref[11] = 8'h2b; 
        aes_ref[12] = 8'hfe; aes_ref[13] = 8'hd7; aes_ref[14] = 8'hab; aes_ref[15] = 8'h76;
        aes_ref[16] = 8'hca; aes_ref[17] = 8'h82; aes_ref[18] = 8'hc9; aes_ref[19] = 8'h7d; 
        aes_ref[20] = 8'hfa; aes_ref[21] = 8'h59; aes_ref[22] = 8'h47; aes_ref[23] = 8'hf0;
        aes_ref[24] = 8'had; aes_ref[25] = 8'hd4; aes_ref[26] = 8'ha2; aes_ref[27] = 8'haf; 
        aes_ref[28] = 8'h9c; aes_ref[29] = 8'ha4; aes_ref[30] = 8'h72; aes_ref[31] = 8'hc0;
        aes_ref[32] = 8'hb7; aes_ref[33] = 8'hfd; aes_ref[34] = 8'h93; aes_ref[35] = 8'h26; 
        aes_ref[36] = 8'h36; aes_ref[37] = 8'h3f; aes_ref[38] = 8'hf7; aes_ref[39] = 8'hcc;
        aes_ref[40] = 8'h34; aes_ref[41] = 8'ha5; aes_ref[42] = 8'he5; aes_ref[43] = 8'hf1; 
        aes_ref[44] = 8'h71; aes_ref[45] = 8'hd8; aes_ref[46] = 8'h31; aes_ref[47] = 8'h15;
        aes_ref[48] = 8'h04; aes_ref[49] = 8'hc7; aes_ref[50] = 8'h23; aes_ref[51] = 8'hc3; 
        aes_ref[52] = 8'h18; aes_ref[53] = 8'h96; aes_ref[54] = 8'h05; aes_ref[55] = 8'h9a;
        aes_ref[56] = 8'h07; aes_ref[57] = 8'h12; aes_ref[58] = 8'h80; aes_ref[59] = 8'he2; 
        aes_ref[60] = 8'heb; aes_ref[61] = 8'h27; aes_ref[62] = 8'hb2; aes_ref[63] = 8'h75;
        aes_ref[64] = 8'h09; aes_ref[65] = 8'h83; aes_ref[66] = 8'h2c; aes_ref[67] = 8'h1a; 
        aes_ref[68] = 8'h1b; aes_ref[69] = 8'h6e; aes_ref[70] = 8'h5a; aes_ref[71] = 8'ha0;
        aes_ref[72] = 8'h52; aes_ref[73] = 8'h3b; aes_ref[74] = 8'hd6; aes_ref[75] = 8'hb3; 
        aes_ref[76] = 8'h29; aes_ref[77] = 8'he3; aes_ref[78] = 8'h2f; aes_ref[79] = 8'h84;
        aes_ref[80] = 8'h53; aes_ref[81] = 8'hd1; aes_ref[82] = 8'h00; aes_ref[83] = 8'hed; 
        aes_ref[84] = 8'h20; aes_ref[85] = 8'hfc; aes_ref[86] = 8'hb1; aes_ref[87] = 8'h5b;
        aes_ref[88] = 8'h6a; aes_ref[89] = 8'hcb; aes_ref[90] = 8'hbe; aes_ref[91] = 8'h39; 
        aes_ref[92] = 8'h4a; aes_ref[93] = 8'h4c; aes_ref[94] = 8'h58; aes_ref[95] = 8'hcf;
        aes_ref[96] = 8'hd0; aes_ref[97] = 8'hef; aes_ref[98] = 8'haa; aes_ref[99] = 8'hfb; 
        aes_ref[100] = 8'h43; aes_ref[101] = 8'h4d; aes_ref[102] = 8'h33; aes_ref[103] = 8'h85;
        aes_ref[104] = 8'h45; aes_ref[105] = 8'hf9; aes_ref[106] = 8'h02; aes_ref[107] = 8'h7f; 
        aes_ref[108] = 8'h50; aes_ref[109] = 8'h3c; aes_ref[110] = 8'h9f; aes_ref[111] = 8'ha8;
        aes_ref[112] = 8'h51; aes_ref[113] = 8'ha3; aes_ref[114] = 8'h40; aes_ref[115] = 8'h8f; 
        aes_ref[116] = 8'h92; aes_ref[117] = 8'h9d; aes_ref[118] = 8'h38; aes_ref[119] = 8'hf5;
        aes_ref[120] = 8'hbc; aes_ref[121] = 8'hb6; aes_ref[122] = 8'hda; aes_ref[123] = 8'h21; 
        aes_ref[124] = 8'h10; aes_ref[125] = 8'hff; aes_ref[126] = 8'hf3; aes_ref[127] = 8'hd2;
        aes_ref[128] = 8'hcd; aes_ref[129] = 8'h0c; aes_ref[130] = 8'h13; aes_ref[131] = 8'hec; 
        aes_ref[132] = 8'h5f; aes_ref[133] = 8'h97; aes_ref[134] = 8'h44; aes_ref[135] = 8'h17;
        aes_ref[136] = 8'hc4; aes_ref[137] = 8'ha7; aes_ref[138] = 8'h7e; aes_ref[139] = 8'h3d; 
        aes_ref[140] = 8'h64; aes_ref[141] = 8'h5d; aes_ref[142] = 8'h19; aes_ref[143] = 8'h73;
        aes_ref[144] = 8'h60; aes_ref[145] = 8'h81; aes_ref[146] = 8'h4f; aes_ref[147] = 8'hdc; 
        aes_ref[148] = 8'h22; aes_ref[149] = 8'h2a; aes_ref[150] = 8'h90; aes_ref[151] = 8'h88;
        aes_ref[152] = 8'h46; aes_ref[153] = 8'hee; aes_ref[154] = 8'hb8; aes_ref[155] = 8'h14; 
        aes_ref[156] = 8'hde; aes_ref[157] = 8'h5e; aes_ref[158] = 8'h0b; aes_ref[159] = 8'hdb;
        aes_ref[160] = 8'he0; aes_ref[161] = 8'h32; aes_ref[162] = 8'h3a; aes_ref[163] = 8'h0a; 
        aes_ref[164] = 8'h49; aes_ref[165] = 8'h06; aes_ref[166] = 8'h24; aes_ref[167] = 8'h5c;
        aes_ref[168] = 8'hc2; aes_ref[169] = 8'hd3; aes_ref[170] = 8'hac; aes_ref[171] = 8'h62; 
        aes_ref[172] = 8'h91; aes_ref[173] = 8'h95; aes_ref[174] = 8'he4; aes_ref[175] = 8'h79;
        aes_ref[176] = 8'he7; aes_ref[177] = 8'hc8; aes_ref[178] = 8'h37; aes_ref[179] = 8'h6d; 
        aes_ref[180] = 8'h8d; aes_ref[181] = 8'hd5; aes_ref[182] = 8'h4e; aes_ref[183] = 8'ha9;
        aes_ref[184] = 8'h6c; aes_ref[185] = 8'h56; aes_ref[186] = 8'hf4; aes_ref[187] = 8'hea; 
        aes_ref[188] = 8'h65; aes_ref[189] = 8'h7a; aes_ref[190] = 8'hae; aes_ref[191] = 8'h08;
        aes_ref[192] = 8'hba; aes_ref[193] = 8'h78; aes_ref[194] = 8'h25; aes_ref[195] = 8'h2e; 
        aes_ref[196] = 8'h1c; aes_ref[197] = 8'ha6; aes_ref[198] = 8'hb4; aes_ref[199] = 8'hc6;
        aes_ref[200] = 8'he8; aes_ref[201] = 8'hdd; aes_ref[202] = 8'h74; aes_ref[203] = 8'h1f; 
        aes_ref[204] = 8'h4b; aes_ref[205] = 8'hbd; aes_ref[206] = 8'h8b; aes_ref[207] = 8'h8a;
        aes_ref[208] = 8'h70; aes_ref[209] = 8'h3e; aes_ref[210] = 8'hb5; aes_ref[211] = 8'h66; 
        aes_ref[212] = 8'h48; aes_ref[213] = 8'h03; aes_ref[214] = 8'hf6; aes_ref[215] = 8'h0e;
        aes_ref[216] = 8'h61; aes_ref[217] = 8'h35; aes_ref[218] = 8'h57; aes_ref[219] = 8'hb9; 
        aes_ref[220] = 8'h86; aes_ref[221] = 8'hc1; aes_ref[222] = 8'h1d; aes_ref[223] = 8'h9e;
        aes_ref[224] = 8'he1; aes_ref[225] = 8'hf8; aes_ref[226] = 8'h98; aes_ref[227] = 8'h11; 
        aes_ref[228] = 8'h69; aes_ref[229] = 8'hd9; aes_ref[230] = 8'h8e; aes_ref[231] = 8'h94;
        aes_ref[232] = 8'h9b; aes_ref[233] = 8'h1e; aes_ref[234] = 8'h87; aes_ref[235] = 8'he9; 
        aes_ref[236] = 8'hce; aes_ref[237] = 8'h55; aes_ref[238] = 8'h28; aes_ref[239] = 8'hdf;
        aes_ref[240] = 8'h8c; aes_ref[241] = 8'ha1; aes_ref[242] = 8'h89; aes_ref[243] = 8'h0d; 
        aes_ref[244] = 8'hbf; aes_ref[245] = 8'he6; aes_ref[246] = 8'h42; aes_ref[247] = 8'h68;
        aes_ref[248] = 8'h41; aes_ref[249] = 8'h99; aes_ref[250] = 8'h2d; aes_ref[251] = 8'h0f; 
        aes_ref[252] = 8'hb0; aes_ref[253] = 8'h54; aes_ref[254] = 8'hbb; aes_ref[255] = 8'h16;
    end

    // Generate Clock
    always #5 clk = ~clk;

    // Test Sequence Variables
    integer i, errors;
    reg [7:0] unmasked_in;
    reg [7:0] unmasked_out;

    initial begin
        // Initialize
        $display("Starting Verilog Masked S-Box Correctness Check...");
        clk = 0;
        errors = 0;
        dec_1 = 1; // As per the C testbench arguments
        
        // Let the circuit initialize
        #20;

        for (i = 0; i < 256; i = i + 1) begin
            unmasked_in = i;

            // 1. Assign Random Mask Shares
            sb_n0_1 = $random % 2; sb_n0_0 = unmasked_in[0] ^ sb_n0_1;
            sb_n1_1 = $random % 2; sb_n1_0 = unmasked_in[1] ^ sb_n1_1;
            sb_n2_1 = $random % 2; sb_n2_0 = unmasked_in[2] ^ sb_n2_1;
            sb_n3_1 = $random % 2; sb_n3_0 = unmasked_in[3] ^ sb_n3_1;
            sb_n4_1 = $random % 2; sb_n4_0 = unmasked_in[4] ^ sb_n4_1;
            sb_n5_1 = $random % 2; sb_n5_0 = unmasked_in[5] ^ sb_n5_1;
            sb_n6_1 = $random % 2; sb_n6_0 = unmasked_in[6] ^ sb_n6_1;
            sb_n7_1 = $random % 2; sb_n7_0 = unmasked_in[7] ^ sb_n7_1;

            // 2. Assign Random Output Variables
            rand_1 = $random; rand_2 = $random; rand_3 = $random; rand_4 = $random;
            rand_5 = $random; rand_6 = $random; rand_7 = $random; rand_8 = $random;
            rand_9 = $random; rand_10 = $random; rand_11 = $random; rand_12 = $random;
            rand_13 = $random; rand_14 = $random; rand_15 = $random; rand_16 = $random;
            rand_17 = $random; rand_18 = $random; rand_19 = $random; rand_20 = $random;
            rand_21 = $random; rand_22 = $random; rand_23 = $random; rand_24 = $random;
            rand_25 = $random; rand_26 = $random; rand_27 = $random; rand_28 = $random;
            rand_29 = $random; rand_30 = $random; rand_31 = $random; rand_32 = $random;
            rand_33 = $random; rand_34 = $random; rand_35 = $random; rand_36 = $random;
            rand_37 = $random; rand_38 = $random; rand_39 = $random; rand_40 = $random;
            rand_41 = $random; rand_42 = $random; rand_43 = $random; rand_44 = $random;
            rand_45 = $random; rand_46 = $random; rand_47 = $random; rand_48 = $random;

            // 3. Allow signals to propagate through all register stages of the pipeline
            // The module utilizes sequential logic on 'posedge clk'
            // We wait 10 cycles to ensure deep pipelines fully flush with the steady input
            repeat(10) @(posedge clk);

            // 4. Reconstruct Output
            unmasked_out[0] = sb_o0_0 ^ sb_o0_1;
            unmasked_out[1] = sb_o1_0 ^ sb_o1_1;
            unmasked_out[2] = sb_o2_0 ^ sb_o2_1;
            unmasked_out[3] = sb_o3_0 ^ sb_o3_1;
            unmasked_out[4] = sb_o4_0 ^ sb_o4_1;
            unmasked_out[5] = sb_o5_0 ^ sb_o5_1;
            unmasked_out[6] = sb_o6_0 ^ sb_o6_1;
            unmasked_out[7] = sb_o7_0 ^ sb_o7_1;

            // 5. Compare with verification
            if (unmasked_out !== aes_ref[i]) begin
                $display("[FAIL] Input 0x%02X: Expected 0x%02X, Got 0x%02X", i, aes_ref[i], unmasked_out);
                errors = errors + 1;
            end
            else begin
                $display("[PASS] Input 0x%02X: Output 0x%02X matches reference.", i, unmasked_out);
            end
        end

        // 6. Report 
        if (errors == 0)
            $display("\nSUCCESS: The Verilog masked S-box code is correct!");
        else
            $display("\nFAILURE: %0d mismatches found.", errors);
            
        $finish;
    end

endmodule