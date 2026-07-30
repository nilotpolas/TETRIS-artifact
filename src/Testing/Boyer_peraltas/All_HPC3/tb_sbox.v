`timescale 1ns / 1ps

module tb_sbox();

    // ----------------------------------------------------
    // 1. Signals & Variables
    // ----------------------------------------------------
    reg clk;
    reg [7:0] share0, share1;
    reg [67:0] rands; // To drive the 68 random inputs

    // Outputs from DUT
    wire Y0_0, Y0_1, Y1_0, Y1_1, Y2_0, Y2_1, Y3_0, Y3_1;
    wire Y4_0, Y4_1, Y5_0, Y5_1, Y6_0, Y6_1, Y7_0, Y7_1;

    // Unmasked output reconstruction (Y_unmasked = Y_0 ^ Y_1)
    wire [7:0] out_share0 = {Y7_0, Y6_0, Y5_0, Y4_0, Y3_0, Y2_0, Y1_0, Y0_0};
    wire [7:0] out_share1 = {Y7_1, Y6_1, Y5_1, Y4_1, Y3_1, Y2_1, Y1_1, Y0_1};
    wire [7:0] out_unmasked = out_share0 ^ out_share1;

    // Golden Results Array
    reg [7:0] sbox_golden [0:255];

    integer i;
    integer errors = 0;

    // ----------------------------------------------------
    // 2. DUT Instantiation
    // ----------------------------------------------------
    sbox dut (
        .clk(clk),
        
        // Data Inputs (X0 is LSB, X7 is MSB)
        .X0_0(share0[0]), .X0_1(share1[0]), .X1_0(share0[1]), .X1_1(share1[1]),
        .X2_0(share0[2]), .X2_1(share1[2]), .X3_0(share0[3]), .X3_1(share1[3]),
        .X4_0(share0[4]), .X4_1(share1[4]), .X5_0(share0[5]), .X5_1(share1[5]),
        .X6_0(share0[6]), .X6_1(share1[6]), .X7_0(share0[7]), .X7_1(share1[7]),
        
        // dec_1 MUST be tied to 1'b1 for correct XNOR calculation in shared designs
        .dec_1(1'b1), 
        
        // Map 68 random ports to the random vector
        .rand_9(rands[0]),   .rand_11(rands[1]),  .rand_14(rands[2]),  .rand_15(rands[3]),  .rand_59(rands[4]),
        .rand_5(rands[5]),   .rand_2(rands[6]),   .rand_64(rands[7]),  .rand_6(rands[8]),   .rand_35(rands[9]),
        .rand_50(rands[10]), .rand_23(rands[11]), .rand_26(rands[12]), .rand_40(rands[13]), .rand_20(rands[14]),
        .rand_32(rands[15]), .rand_24(rands[16]), .rand_42(rands[17]), .rand_48(rands[18]), .rand_66(rands[19]),
        .rand_28(rands[20]), .rand_16(rands[21]), .rand_38(rands[22]), .rand_61(rands[23]), .rand_60(rands[24]),
        .rand_10(rands[25]), .rand_68(rands[26]), .rand_43(rands[27]), .rand_46(rands[28]), .rand_27(rands[29]),
        .rand_57(rands[30]), .rand_17(rands[31]), .rand_47(rands[32]), .rand_53(rands[33]), .rand_67(rands[34]),
        .rand_7(rands[35]),  .rand_44(rands[36]), .rand_65(rands[37]), .rand_55(rands[38]), .rand_56(rands[39]),
        .rand_34(rands[40]), .rand_39(rands[41]), .rand_54(rands[42]), .rand_3(rands[43]),  .rand_18(rands[44]),
        .rand_19(rands[45]), .rand_29(rands[46]), .rand_62(rands[47]), .rand_1(rands[48]),  .rand_41(rands[49]),
        .rand_4(rands[50]),  .rand_8(rands[51]),  .rand_12(rands[52]), .rand_21(rands[53]), .rand_36(rands[54]),
        .rand_31(rands[55]), .rand_13(rands[56]), .rand_22(rands[57]), .rand_30(rands[58]), .rand_58(rands[59]),
        .rand_33(rands[60]), .rand_37(rands[61]), .rand_63(rands[62]), .rand_49(rands[63]), .rand_51(rands[64]),
        .rand_25(rands[65]), .rand_45(rands[66]), .rand_52(rands[67]),
        
        // Data Outputs
        .Y0_0(Y0_0), .Y0_1(Y0_1), .Y1_0(Y1_0), .Y1_1(Y1_1), .Y2_0(Y2_0), .Y2_1(Y2_1),
        .Y3_0(Y3_0), .Y3_1(Y3_1), .Y4_0(Y4_0), .Y4_1(Y4_1), .Y5_0(Y5_0), .Y5_1(Y5_1),
        .Y6_0(Y6_0), .Y6_1(Y6_1), .Y7_0(Y7_0), .Y7_1(Y7_1)
    );

    // ----------------------------------------------------
    // 3. Clock Generation
    // ----------------------------------------------------
    initial begin
        clk = 0;
        forever #5 clk = ~clk; // 10ns period
    end

    // ----------------------------------------------------
    // 4. Main Verification Logic
    // ----------------------------------------------------
    initial begin
        // Initialize Golden Array
        sbox_golden[0]=8'hC6; sbox_golden[1]=8'hB3; sbox_golden[2]=8'h90; sbox_golden[3]=8'h5D; sbox_golden[4]=8'hED; sbox_golden[5]=8'h07; sbox_golden[6]=8'h0B; sbox_golden[7]=8'h87; sbox_golden[8]=8'h53; sbox_golden[9]=8'h06; sbox_golden[10]=8'hCA; sbox_golden[11]=8'h0E; sbox_golden[12]=8'h20; sbox_golden[13]=8'hE7; sbox_golden[14]=8'h8A; sbox_golden[15]=8'h31; 
        sbox_golden[16]=8'h0C; sbox_golden[17]=8'h23; sbox_golden[18]=8'h4A; sbox_golden[19]=8'h17; sbox_golden[20]=8'h2C; sbox_golden[21]=8'h43; sbox_golden[22]=8'hA2; sbox_golden[23]=8'hD9; sbox_golden[24]=8'hB5; sbox_golden[25]=8'h62; sbox_golden[26]=8'h56; sbox_golden[27]=8'h86; sbox_golden[28]=8'hE0; sbox_golden[29]=8'h36; sbox_golden[30]=8'h3D; sbox_golden[31]=8'h82; 
        sbox_golden[32]=8'h4F; sbox_golden[33]=8'hFA; sbox_golden[34]=8'hD8; sbox_golden[35]=8'h38; sbox_golden[36]=8'h6C; sbox_golden[37]=8'h92; sbox_golden[38]=8'hC2; sbox_golden[39]=8'h96; sbox_golden[40]=8'h5F; sbox_golden[41]=8'h44; sbox_golden[42]=8'h04; sbox_golden[43]=8'h12; sbox_golden[44]=8'h18; sbox_golden[45]=8'hB1; sbox_golden[46]=8'h49; sbox_golden[47]=8'hFD; 
        sbox_golden[48]=8'h7F; sbox_golden[49]=8'h26; sbox_golden[50]=8'h94; sbox_golden[51]=8'hD2; sbox_golden[52]=8'h8E; sbox_golden[53]=8'h89; sbox_golden[54]=8'h0A; sbox_golden[55]=8'h73; sbox_golden[56]=8'h39; sbox_golden[57]=8'h7B; sbox_golden[58]=8'h52; sbox_golden[59]=8'h61; sbox_golden[60]=8'hD7; sbox_golden[61]=8'hA6; sbox_golden[62]=8'h08; sbox_golden[63]=8'h0D; 
        sbox_golden[64]=8'hEE; sbox_golden[65]=8'hC8; sbox_golden[66]=8'h34; sbox_golden[67]=8'hA4; sbox_golden[68]=8'hC9; sbox_golden[69]=8'h5C; sbox_golden[70]=8'h55; sbox_golden[71]=8'h19; sbox_golden[72]=8'h93; sbox_golden[73]=8'hF2; sbox_golden[74]=8'h00; sbox_golden[75]=8'hAD; sbox_golden[76]=8'hC4; sbox_golden[77]=8'hEC; sbox_golden[78]=8'h02; sbox_golden[79]=8'h91; 
        sbox_golden[80]=8'hE6; sbox_golden[81]=8'h7E; sbox_golden[82]=8'h6B; sbox_golden[83]=8'h2E; sbox_golden[84]=8'hA7; sbox_golden[85]=8'h35; sbox_golden[86]=8'h40; sbox_golden[87]=8'hE1; sbox_golden[88]=8'h45; sbox_golden[89]=8'h1D; sbox_golden[90]=8'h7D; sbox_golden[91]=8'hEA; sbox_golden[92]=8'h01; sbox_golden[93]=8'h2F; sbox_golden[94]=8'h5B; sbox_golden[95]=8'hB4; 
        sbox_golden[96]=8'hF6; sbox_golden[97]=8'h22; sbox_golden[98]=8'h5A; sbox_golden[99]=8'h2D; sbox_golden[100]=8'hEF; sbox_golden[101]=8'h24; sbox_golden[102]=8'hCC; sbox_golden[103]=8'h71; sbox_golden[104]=8'hE2; sbox_golden[105]=8'h09; sbox_golden[106]=8'h8D; sbox_golden[107]=8'h6F; sbox_golden[108]=8'hA0; sbox_golden[109]=8'h72; sbox_golden[110]=8'h1C; sbox_golden[111]=8'h42; 
        sbox_golden[112]=8'hD5; sbox_golden[113]=8'h98; sbox_golden[114]=8'hF4; sbox_golden[115]=8'hD1; sbox_golden[116]=8'h8C; sbox_golden[117]=8'h27; sbox_golden[118]=8'hF9; sbox_golden[119]=8'h14; sbox_golden[120]=8'h4E; sbox_golden[121]=8'hD0; sbox_golden[122]=8'h1A; sbox_golden[123]=8'hB8; sbox_golden[124]=8'h4D; sbox_golden[125]=8'h75; sbox_golden[126]=8'hCF; sbox_golden[127]=8'hDD; 
        sbox_golden[128]=8'h3E; sbox_golden[129]=8'h30; sbox_golden[130]=8'hC1; sbox_golden[131]=8'h1E; sbox_golden[132]=8'hBF; sbox_golden[133]=8'h4C; sbox_golden[134]=8'hF7; sbox_golden[135]=8'h1F; sbox_golden[136]=8'h41; sbox_golden[137]=8'h81; sbox_golden[138]=8'h8B; sbox_golden[139]=8'h7C; sbox_golden[140]=8'hE3; sbox_golden[141]=8'h13; sbox_golden[142]=8'hC5; sbox_golden[143]=8'h85; 
        sbox_golden[144]=8'h80; sbox_golden[145]=8'hE5; sbox_golden[146]=8'hDC; sbox_golden[147]=8'hBB; sbox_golden[148]=8'hA5; sbox_golden[149]=8'hCB; sbox_golden[150]=8'h9F; sbox_golden[151]=8'h78; sbox_golden[152]=8'h2B; sbox_golden[153]=8'h77; sbox_golden[154]=8'hD3; sbox_golden[155]=8'hAC; sbox_golden[156]=8'h48; sbox_golden[157]=8'h6A; sbox_golden[158]=8'h6D; sbox_golden[159]=8'h99; 
        sbox_golden[160]=8'hD6; sbox_golden[161]=8'hE9; sbox_golden[162]=8'h76; sbox_golden[163]=8'h65; sbox_golden[164]=8'hFC; sbox_golden[165]=8'h60; sbox_golden[166]=8'hB2; sbox_golden[167]=8'h9B; sbox_golden[168]=8'h9A; sbox_golden[169]=8'h54; sbox_golden[170]=8'h3F; sbox_golden[171]=8'hC0; sbox_golden[172]=8'h69; sbox_golden[173]=8'hAB; sbox_golden[174]=8'hB9; sbox_golden[175]=8'h67; 
        sbox_golden[176]=8'hEB; sbox_golden[177]=8'hBA; sbox_golden[178]=8'hC7; sbox_golden[179]=8'hBD; sbox_golden[180]=8'h1B; sbox_golden[181]=8'hA9; sbox_golden[182]=8'h3C; sbox_golden[183]=8'hAA; sbox_golden[184]=8'h25; sbox_golden[185]=8'h7A; sbox_golden[186]=8'h32; sbox_golden[187]=8'h83; sbox_golden[188]=8'hE4; sbox_golden[189]=8'h5E; sbox_golden[190]=8'hFF; sbox_golden[191]=8'h2A; 
        sbox_golden[192]=8'hDE; sbox_golden[193]=8'h37; sbox_golden[194]=8'h58; sbox_golden[195]=8'h74; sbox_golden[196]=8'h64; sbox_golden[197]=8'h50; sbox_golden[198]=8'hDF; sbox_golden[199]=8'h88; sbox_golden[200]=8'hBE; sbox_golden[201]=8'h3B; sbox_golden[202]=8'hB7; sbox_golden[203]=8'h66; sbox_golden[204]=8'hC3; sbox_golden[205]=8'hB6; sbox_golden[206]=8'hF1; sbox_golden[207]=8'hB0; 
        sbox_golden[208]=8'hD4; sbox_golden[209]=8'hBC; sbox_golden[210]=8'hCD; sbox_golden[211]=8'hF8; sbox_golden[212]=8'h8F; sbox_golden[213]=8'h46; sbox_golden[214]=8'hFE; sbox_golden[215]=8'h97; sbox_golden[216]=8'hF5; sbox_golden[217]=8'h28; sbox_golden[218]=8'h9C; sbox_golden[219]=8'h9D; sbox_golden[220]=8'h47; sbox_golden[221]=8'h57; sbox_golden[222]=8'h84; sbox_golden[223]=8'hF0; 
        sbox_golden[224]=8'hA3; sbox_golden[225]=8'hE8; sbox_golden[226]=8'h05; sbox_golden[227]=8'h63; sbox_golden[228]=8'h33; sbox_golden[229]=8'h3A; sbox_golden[230]=8'hA1; sbox_golden[231]=8'h29; sbox_golden[232]=8'h0F; sbox_golden[233]=8'h11; sbox_golden[234]=8'hDA; sbox_golden[235]=8'h70; sbox_golden[236]=8'h59; sbox_golden[237]=8'h95; sbox_golden[238]=8'hAF; sbox_golden[239]=8'h16; 
        sbox_golden[240]=8'h6E; sbox_golden[241]=8'hCE; sbox_golden[242]=8'h21; sbox_golden[243]=8'h51; sbox_golden[244]=8'hA8; sbox_golden[245]=8'h9E; sbox_golden[246]=8'h15; sbox_golden[247]=8'hFB; sbox_golden[248]=8'h03; sbox_golden[249]=8'hDB; sbox_golden[250]=8'hF3; sbox_golden[251]=8'h79; sbox_golden[252]=8'hAE; sbox_golden[253]=8'h10; sbox_golden[254]=8'h4B; sbox_golden[255]=8'h68;

        #10; // Wait a brief moment before starting

        for (i = 0; i < 256; i = i + 1) begin
            // Split the input into two random shares
            share1 = $random;
            share0 = i ^ share1;
            
            // Randomize all 68 input randomness bits
            rands = {$random, $random, $random};

            // Feed it in and wait for the 2-cycle internal pipeline latency
            @(posedge clk); // Edge 1: Input propagates to u00/temp registers
            @(posedge clk); // Edge 2: Logic propagates to Y registers

            #50; // Wait 40ns after posedge to safely read output signals

            // Compare unmasked result with golden array
            if (out_unmasked !== sbox_golden[i]) begin
                $display("ERROR at Input 0x%02X | Expected: 0x%02X | Got: 0x%02X", i, sbox_golden[i], out_unmasked);
                errors = errors + 1;
            end else begin
                // Optional: Print passing inputs to watch the sim run
                // $display("PASS at Input 0x%02X | Output: 0x%02X", i, out_unmasked);
            end
        end

        // Final Verification Output
        $display("-------------------------------------------");
        if (errors == 0) begin
            $display(">> VERIFICATION SUCCESS: All 256 outputs matched!");
        end else begin
            $display(">> VERIFICATION FAILED: %0d mismatch errors found.", errors);
        end
        $display("-------------------------------------------");

        $finish;
    end

endmodule