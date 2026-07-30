/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Ultra(TM) in wire load mode
// Version   : O-2018.06-SP1
// Date      : Tue Jun 30 16:24:05 2026
/////////////////////////////////////////////////////////////


module sbox ( clk, i0_0, i0_1, i1_0, i1_1, i2_0, i2_1, i3_0, i3_1, i4_0, i4_1, 
        i5_0, i5_1, i6_0, i6_1, i7_0, i7_1, rand_3, rand_7, rand_11, rand_1, 
        rand_4, rand_8, rand_12, rand_5, rand_2, rand_9, rand_10, rand_6, o0_0, 
        o0_1, o1_0, o1_1, o2_0, o2_1, o3_0, o3_1, o4_0, o4_1, o5_0, o5_1, o6_0, 
        o6_1, o7_0, o7_1 );
  input clk, i0_0, i0_1, i1_0, i1_1, i2_0, i2_1, i3_0, i3_1, i4_0, i4_1, i5_0,
         i5_1, i6_0, i6_1, i7_0, i7_1, rand_3, rand_7, rand_11, rand_1, rand_4,
         rand_8, rand_12, rand_5, rand_2, rand_9, rand_10, rand_6;
  output o0_0, o0_1, o1_0, o1_1, o2_0, o2_1, o3_0, o3_1, o4_0, o4_1, o5_0,
         o5_1, o6_0, o6_1, o7_0, o7_1;
  wire   u00_HPC30, temp_hpc3_v_1_order0_HPC30, n7_0_reg, w01_HPC30,
         temp_hpc3_v_1_order1_HPC30, n7_1_reg, w10_HPC30, u11_HPC30,
         u00_HPC30_reg, u11_HPC30_reg, u00_HPC31, temp_hpc3_v_1_order0_HPC31,
         n2_0_reg, w01_HPC31, temp_hpc3_v_1_order1_HPC31, n2_1_reg, w10_HPC31,
         u11_HPC31, u00_HPC31_reg, u11_HPC31_reg, u00_HPC32,
         temp_hpc3_v_1_order0_HPC32, n1_0_reg, w01_HPC32,
         temp_hpc3_v_1_order1_HPC32, n1_1_reg, w10_HPC32, u11_HPC32,
         u00_HPC32_reg, u11_HPC32_reg, u00_HPC33, temp_hpc3_v_1_order0_HPC33,
         nt1_0_reg, w01_HPC33, temp_hpc3_v_1_order1_HPC33, nt1_1_reg,
         w10_HPC33, u11_HPC33, u00_HPC33_reg, u11_HPC33_reg, n3_0_reg,
         u00_HPC24, v01_HPC24, w01_HPC24, v10_HPC24, w10_HPC24, n3_1_reg,
         u11_HPC24, u00_HPC24_reg, u11_HPC24_reg, nt2_0_reg, u00_HPC25,
         v01_HPC25, w01_HPC25, v10_HPC25, w10_HPC25, nt2_1_reg, u11_HPC25,
         u00_HPC25_reg, u11_HPC25_reg, nt0_0_reg, u00_HPC26, v01_HPC26,
         w01_HPC26, v10_HPC26, w10_HPC26, nt0_1_reg, u11_HPC26, u00_HPC26_reg,
         u11_HPC26_reg, nt4_0_reg, u00_HPC27, v01_HPC27, w01_HPC27, v10_HPC27,
         w10_HPC27, nt4_1_reg, u11_HPC27, u00_HPC27_reg, u11_HPC27_reg,
         o6_val_0, o6_val_1, o5_val_0, o5_val_1, o2_val_0, o2_val_1, o7_val_0,
         o7_val_1, o0_val_0, o0_val_1, o4_val_0, o4_val_1, o1_val_0, o1_val_1,
         o3_val_0, o3_val_1, N0, N1, N3, N5, N7, z673_assgn6730,
         z675_assgn6750, z685_assgn6850, z687_assgn6870, z689_assgn6890,
         z691_assgn6910, N8, N9, N10, N11, N12, N13, N14, N15, N16, N17, N18,
         N19, N21, N22, N23, temp_hpc2_v_1_order0_HPC24, N24, N25,
         temp_hpc2_v_1_order1_HPC24, N26, N27, temp_hpc2_v_1_order0_HPC25, N28,
         N29, temp_hpc2_v_1_order1_HPC25, N30, N31, temp_hpc2_v_1_order0_HPC26,
         N32, N33, temp_hpc2_v_1_order1_HPC26, N34, N35,
         temp_hpc2_v_1_order0_HPC27, N36, N37, temp_hpc2_v_1_order1_HPC27, N38,
         N39, z673_assgn6731, z675_assgn6751, z677_assgn6770, z679_assgn6790,
         z685_assgn6851, z687_assgn6871, z689_assgn6891, z691_assgn6911,
         z693_assgn6930, z695_assgn6950, n111, n112, n113, n114, n115, n116,
         n117, n118, n119, n120, n121, n122, n123, n124, n125, n126, n127,
         n128, n129, n130, n131, n132, n133, n134, n135, n136, n137, n138,
         n139, n140, n141, n142, n143, n144, n145, n146, n147, n148, n149,
         n150, n151, n152, n153, n154, n155, n156, n157, n158, n159, n160,
         n161, n162, n163, n164, n165, n166, n167, n168, n169, n170, n171,
         n172, n173, n174, n175, n176;

  DFF_X1 temp_hpc2_v_1_order0_HPC24_reg ( .D(N0), .CK(clk), 
        .Q(temp_hpc2_v_1_order0_HPC24) );
  DFF_X1 temp_hpc2_v_1_order1_HPC24_reg ( .D(N1), .CK(clk), 
        .Q(temp_hpc2_v_1_order1_HPC24) );
  DFF_X1 temp_hpc3_v_1_order0_HPC30_reg ( .D(N8), .CK(clk), 
        .Q(temp_hpc3_v_1_order0_HPC30) );
  DFF_X1 n7_0_reg_reg ( .D(n117), .CK(clk), .Q(n7_0_reg) );
  DFF_X1 w01_HPC30_reg ( .D(N9), .CK(clk), .Q(w01_HPC30) );
  DFF_X1 temp_hpc3_v_1_order1_HPC30_reg ( .D(N10), .CK(clk), 
        .Q(temp_hpc3_v_1_order1_HPC30) );
  DFF_X1 n7_1_reg_reg ( .D(n118), .CK(clk), .Q(n7_1_reg) );
  DFF_X1 w10_HPC30_reg ( .D(N11), .CK(clk), .Q(w10_HPC30) );
  DFF_X1 u00_HPC30_reg_reg ( .D(u00_HPC30), .CK(clk), .Q(u00_HPC30_reg) );
  DFF_X1 z689_assgn6890_reg ( .D(o6_val_0), .CK(clk), .Q(z689_assgn6890) );
  DFF_X1 z689_assgn6891_reg ( .D(z689_assgn6890), .CK(clk), .Q(z689_assgn6891)
         );
  DFF_X1 o6_0_reg ( .D(z689_assgn6891), .CK(clk), .Q(o6_0) );
  DFF_X1 temp_hpc2_v_1_order1_HPC26_reg ( .D(N5), .CK(clk), 
        .Q(temp_hpc2_v_1_order1_HPC26) );
  DFF_X1 u11_HPC30_reg_reg ( .D(u11_HPC30), .CK(clk), .Q(u11_HPC30_reg) );
  DFF_X1 z691_assgn6910_reg ( .D(o6_val_1), .CK(clk), .Q(z691_assgn6910) );
  DFF_X1 z691_assgn6911_reg ( .D(z691_assgn6910), .CK(clk), .Q(z691_assgn6911)
         );
  DFF_X1 o6_1_reg ( .D(z691_assgn6911), .CK(clk), .Q(o6_1) );
  DFF_X1 temp_hpc2_v_1_order0_HPC26_reg ( .D(n120), .CK(clk), 
        .Q(temp_hpc2_v_1_order0_HPC26) );
  DFF_X1 temp_hpc3_v_1_order0_HPC31_reg ( .D(N12), .CK(clk), 
        .Q(temp_hpc3_v_1_order0_HPC31) );
  DFF_X1 n2_0_reg_reg ( .D(n113), .CK(clk), .Q(n2_0_reg) );
  DFF_X1 w01_HPC31_reg ( .D(N13), .CK(clk), .Q(w01_HPC31) );
  DFF_X1 temp_hpc3_v_1_order1_HPC31_reg ( .D(N14), .CK(clk), 
        .Q(temp_hpc3_v_1_order1_HPC31) );
  DFF_X1 n2_1_reg_reg ( .D(n114), .CK(clk), .Q(n2_1_reg) );
  DFF_X1 w10_HPC31_reg ( .D(N15), .CK(clk), .Q(w10_HPC31) );
  DFF_X1 u00_HPC31_reg_reg ( .D(u00_HPC31), .CK(clk), .Q(u00_HPC31_reg) );
  DFF_X1 z685_assgn6850_reg ( .D(o5_val_0), .CK(clk), .Q(z685_assgn6850) );
  DFF_X1 z685_assgn6851_reg ( .D(z685_assgn6850), .CK(clk), .Q(z685_assgn6851)
         );
  DFF_X1 o5_0_reg ( .D(z685_assgn6851), .CK(clk), .Q(o5_0) );
  DFF_X1 u11_HPC31_reg_reg ( .D(u11_HPC31), .CK(clk), .Q(u11_HPC31_reg) );
  DFF_X1 z687_assgn6870_reg ( .D(o5_val_1), .CK(clk), .Q(z687_assgn6870) );
  DFF_X1 z687_assgn6871_reg ( .D(z687_assgn6870), .CK(clk), .Q(z687_assgn6871)
         );
  DFF_X1 o5_1_reg ( .D(z687_assgn6871), .CK(clk), .Q(o5_1) );
  DFF_X1 temp_hpc3_v_1_order0_HPC32_reg ( .D(N16), .CK(clk), 
        .Q(temp_hpc3_v_1_order0_HPC32) );
  DFF_X1 n1_0_reg_reg ( .D(n111), .CK(clk), .Q(n1_0_reg) );
  DFF_X1 w01_HPC32_reg ( .D(N17), .CK(clk), .Q(w01_HPC32) );
  DFF_X1 temp_hpc3_v_1_order1_HPC32_reg ( .D(N18), .CK(clk), 
        .Q(temp_hpc3_v_1_order1_HPC32) );
  DFF_X1 n1_1_reg_reg ( .D(n112), .CK(clk), .Q(n1_1_reg) );
  DFF_X1 w10_HPC32_reg ( .D(N19), .CK(clk), .Q(w10_HPC32) );
  DFF_X1 u00_HPC32_reg_reg ( .D(u00_HPC32), .CK(clk), .Q(u00_HPC32_reg) );
  DFF_X1 z673_assgn6730_reg ( .D(o2_val_0), .CK(clk), .Q(z673_assgn6730) );
  DFF_X1 z673_assgn6731_reg ( .D(z673_assgn6730), .CK(clk), .Q(z673_assgn6731)
         );
  DFF_X1 o2_0_reg ( .D(z673_assgn6731), .CK(clk), .Q(o2_0) );
  DFF_X1 temp_hpc2_v_1_order1_HPC25_reg ( .D(N3), .CK(clk), 
        .Q(temp_hpc2_v_1_order1_HPC25) );
  DFF_X1 u11_HPC32_reg_reg ( .D(u11_HPC32), .CK(clk), .Q(u11_HPC32_reg) );
  DFF_X1 z675_assgn6750_reg ( .D(o2_val_1), .CK(clk), .Q(z675_assgn6750) );
  DFF_X1 z675_assgn6751_reg ( .D(z675_assgn6750), .CK(clk), .Q(z675_assgn6751)
         );
  DFF_X1 o2_1_reg ( .D(z675_assgn6751), .CK(clk), .Q(o2_1) );
  DFF_X1 temp_hpc2_v_1_order0_HPC25_reg ( .D(n122), .CK(clk), 
        .Q(temp_hpc2_v_1_order0_HPC25) );
  DFF_X1 temp_hpc3_v_1_order0_HPC33_reg ( .D(n119), .CK(clk), 
        .Q(temp_hpc3_v_1_order0_HPC33) );
  DFF_X1 nt1_0_reg_reg ( .D(n130), .CK(clk), .Q(nt1_0_reg) );
  DFF_X1 w01_HPC33_reg ( .D(N21), .CK(clk), .Q(w01_HPC33) );
  DFF_X1 temp_hpc3_v_1_order1_HPC33_reg ( .D(N22), .CK(clk), 
        .Q(temp_hpc3_v_1_order1_HPC33) );
  DFF_X1 nt1_1_reg_reg ( .D(n124), .CK(clk), .Q(nt1_1_reg) );
  DFF_X1 w10_HPC33_reg ( .D(N23), .CK(clk), .Q(w10_HPC33) );
  DFF_X1 u00_HPC33_reg_reg ( .D(u00_HPC33), .CK(clk), .Q(u00_HPC33_reg) );
  DFF_X1 z693_assgn6930_reg ( .D(o7_val_0), .CK(clk), .Q(z693_assgn6930) );
  DFF_X1 o7_0_reg ( .D(z693_assgn6930), .CK(clk), .Q(o7_0) );
  DFF_X1 u11_HPC33_reg_reg ( .D(u11_HPC33), .CK(clk), .Q(u11_HPC33_reg) );
  DFF_X1 z695_assgn6950_reg ( .D(o7_val_1), .CK(clk), .Q(z695_assgn6950) );
  DFF_X1 o7_1_reg ( .D(z695_assgn6950), .CK(clk), .Q(o7_1) );
  DFF_X1 n3_0_reg_reg ( .D(n115), .CK(clk), .Q(n3_0_reg) );
  DFF_X1 v01_HPC24_reg ( .D(N24), .CK(clk), .Q(v01_HPC24) );
  DFF_X1 w01_HPC24_reg ( .D(N25), .CK(clk), .Q(w01_HPC24) );
  DFF_X1 v10_HPC24_reg ( .D(N26), .CK(clk), .Q(v10_HPC24) );
  DFF_X1 w10_HPC24_reg ( .D(N27), .CK(clk), .Q(w10_HPC24) );
  DFF_X1 n3_1_reg_reg ( .D(n116), .CK(clk), .Q(n3_1_reg) );
  DFF_X1 u00_HPC24_reg_reg ( .D(u00_HPC24), .CK(clk), .Q(u00_HPC24_reg) );
  DFF_X1 nt4_0_reg_reg ( .D(n128), .CK(clk), .Q(nt4_0_reg) );
  DFF_X1 z677_assgn6770_reg ( .D(o3_val_0), .CK(clk), .Q(z677_assgn6770) );
  DFF_X1 o3_0_reg ( .D(z677_assgn6770), .CK(clk), .Q(o3_0) );
  DFF_X1 temp_hpc2_v_1_order1_HPC27_reg ( .D(N7), .CK(clk), 
        .Q(temp_hpc2_v_1_order1_HPC27) );
  DFF_X1 u11_HPC24_reg_reg ( .D(u11_HPC24), .CK(clk), .Q(u11_HPC24_reg) );
  DFF_X1 nt4_1_reg_reg ( .D(n126), .CK(clk), .Q(nt4_1_reg) );
  DFF_X1 z679_assgn6790_reg ( .D(o3_val_1), .CK(clk), .Q(z679_assgn6790) );
  DFF_X1 o3_1_reg ( .D(z679_assgn6790), .CK(clk), .Q(o3_1) );
  DFF_X1 temp_hpc2_v_1_order0_HPC27_reg ( .D(n121), .CK(clk), 
        .Q(temp_hpc2_v_1_order0_HPC27) );
  DFF_X1 nt2_0_reg_reg ( .D(n129), .CK(clk), .Q(nt2_0_reg) );
  DFF_X1 v01_HPC25_reg ( .D(N28), .CK(clk), .Q(v01_HPC25) );
  DFF_X1 w01_HPC25_reg ( .D(N29), .CK(clk), .Q(w01_HPC25) );
  DFF_X1 v10_HPC25_reg ( .D(N30), .CK(clk), .Q(v10_HPC25) );
  DFF_X1 w10_HPC25_reg ( .D(N31), .CK(clk), .Q(w10_HPC25) );
  DFF_X1 nt2_1_reg_reg ( .D(n125), .CK(clk), .Q(nt2_1_reg) );
  DFF_X1 u00_HPC25_reg_reg ( .D(u00_HPC25), .CK(clk), .Q(u00_HPC25_reg) );
  DFF_X1 u00_HPC27_reg_reg ( .D(u00_HPC27), .CK(clk), .Q(u00_HPC27_reg) );
  DFF_X1 o1_0_reg ( .D(o1_val_0), .CK(clk), .Q(o1_0) );
  DFF_X1 w01_HPC27_reg ( .D(N37), .CK(clk), .Q(w01_HPC27) );
  DFF_X1 v01_HPC27_reg ( .D(N36), .CK(clk), .Q(v01_HPC27) );
  DFF_X1 o0_0_reg ( .D(o0_val_0), .CK(clk), .Q(o0_0) );
  DFF_X1 u11_HPC25_reg_reg ( .D(u11_HPC25), .CK(clk), .Q(u11_HPC25_reg) );
  DFF_X1 u11_HPC27_reg_reg ( .D(u11_HPC27), .CK(clk), .Q(u11_HPC27_reg) );
  DFF_X1 o1_1_reg ( .D(o1_val_1), .CK(clk), .Q(o1_1) );
  DFF_X1 w10_HPC27_reg ( .D(N39), .CK(clk), .Q(w10_HPC27) );
  DFF_X1 v10_HPC27_reg ( .D(N38), .CK(clk), .Q(v10_HPC27) );
  DFF_X1 o0_1_reg ( .D(o0_val_1), .CK(clk), .Q(o0_1) );
  DFF_X1 nt0_0_reg_reg ( .D(n127), .CK(clk), .Q(nt0_0_reg) );
  DFF_X1 u00_HPC26_reg_reg ( .D(u00_HPC26), .CK(clk), .Q(u00_HPC26_reg) );
  DFF_X1 v01_HPC26_reg ( .D(N32), .CK(clk), .Q(v01_HPC26) );
  DFF_X1 w01_HPC26_reg ( .D(N33), .CK(clk), .Q(w01_HPC26) );
  DFF_X1 o4_0_reg ( .D(o4_val_0), .CK(clk), .Q(o4_0) );
  DFF_X1 v10_HPC26_reg ( .D(N34), .CK(clk), .Q(v10_HPC26) );
  DFF_X1 w10_HPC26_reg ( .D(N35), .CK(clk), .Q(w10_HPC26) );
  DFF_X1 nt0_1_reg_reg ( .D(n123), .CK(clk), .Q(nt0_1_reg) );
  DFF_X1 u11_HPC26_reg_reg ( .D(u11_HPC26), .CK(clk), .Q(u11_HPC26_reg) );
  DFF_X1 o4_1_reg ( .D(o4_val_1), .CK(clk), .Q(o4_1) );
  INV_X1 U276 ( .A(i7_0), .ZN(n117) );
  INV_X1 U277 ( .A(i1_0), .ZN(n111) );
  INV_X1 U278 ( .A(i2_1), .ZN(n114) );
  INV_X1 U279 ( .A(i3_1), .ZN(n116) );
  INV_X1 U280 ( .A(i3_0), .ZN(n115) );
  INV_X1 U281 ( .A(i2_0), .ZN(n113) );
  INV_X1 U282 ( .A(i1_1), .ZN(n112) );
  INV_X1 U283 ( .A(i7_1), .ZN(n118) );
  XOR2_X1 U284 ( .A(u00_HPC31_reg), .B(w01_HPC31), .Z(n132) );
  NAND2_X1 U285 ( .A1(n2_0_reg), .A2(temp_hpc3_v_1_order0_HPC31), .ZN(n131) );
  XOR2_X1 U286 ( .A(n132), .B(n131), .Z(n145) );
  INV_X1 U287 ( .A(n145), .ZN(n130) );
  NAND2_X1 U288 ( .A1(n7_0_reg), .A2(temp_hpc3_v_1_order0_HPC30), .ZN(n133) );
  XOR2_X1 U289 ( .A(w01_HPC30), .B(n133), .Z(n134) );
  XNOR2_X1 U290 ( .A(u00_HPC30_reg), .B(n134), .ZN(n127) );
  AND2_X1 U291 ( .A1(n130), .A2(n127), .ZN(u00_HPC33) );
  NAND2_X1 U292 ( .A1(n2_1_reg), .A2(temp_hpc3_v_1_order1_HPC31), .ZN(n135) );
  XNOR2_X1 U293 ( .A(n135), .B(w10_HPC31), .ZN(n136) );
  XOR2_X1 U294 ( .A(u11_HPC31_reg), .B(n136), .Z(n166) );
  INV_X1 U295 ( .A(n166), .ZN(n124) );
  NAND2_X1 U296 ( .A1(n7_1_reg), .A2(temp_hpc3_v_1_order1_HPC30), .ZN(n137) );
  XNOR2_X1 U297 ( .A(n137), .B(w10_HPC30), .ZN(n138) );
  XNOR2_X1 U298 ( .A(u11_HPC30_reg), .B(n138), .ZN(n123) );
  AND2_X1 U299 ( .A1(n124), .A2(n123), .ZN(u11_HPC33) );
  XOR2_X1 U300 ( .A(u11_HPC25_reg), .B(v10_HPC25), .Z(n139) );
  XNOR2_X1 U301 ( .A(w10_HPC25), .B(n139), .ZN(n167) );
  AND2_X1 U302 ( .A1(temp_hpc2_v_1_order1_HPC27), .A2(n167), .ZN(N38) );
  AND2_X1 U303 ( .A1(nt4_1_reg), .A2(n167), .ZN(u11_HPC27) );
  XOR2_X1 U304 ( .A(v01_HPC25), .B(w01_HPC25), .Z(n140) );
  XOR2_X1 U305 ( .A(u00_HPC25_reg), .B(n140), .Z(n163) );
  AND2_X1 U306 ( .A1(n163), .A2(temp_hpc2_v_1_order0_HPC27), .ZN(N36) );
  AND2_X1 U307 ( .A1(n163), .A2(nt4_0_reg), .ZN(u00_HPC27) );
  XOR2_X1 U308 ( .A(u00_HPC33_reg), .B(w01_HPC33), .Z(n142) );
  NAND2_X1 U309 ( .A1(nt1_0_reg), .A2(temp_hpc3_v_1_order0_HPC33), .ZN(n141)
         );
  XNOR2_X1 U310 ( .A(n142), .B(n141), .ZN(n164) );
  AND2_X1 U311 ( .A1(n164), .A2(nt0_0_reg), .ZN(u00_HPC26) );
  AND2_X1 U312 ( .A1(n164), .A2(nt2_0_reg), .ZN(u00_HPC25) );
  AND2_X1 U313 ( .A1(n164), .A2(temp_hpc2_v_1_order0_HPC26), .ZN(N32) );
  AND2_X1 U314 ( .A1(n164), .A2(temp_hpc2_v_1_order0_HPC25), .ZN(N28) );
  AND2_X1 U315 ( .A1(n130), .A2(n3_0_reg), .ZN(u00_HPC24) );
  AND2_X1 U316 ( .A1(n130), .A2(temp_hpc2_v_1_order0_HPC24), .ZN(N24) );
  XOR2_X1 U317 ( .A(u11_HPC33_reg), .B(w10_HPC33), .Z(n144) );
  NAND2_X1 U318 ( .A1(nt1_1_reg), .A2(temp_hpc3_v_1_order1_HPC33), .ZN(n143)
         );
  XOR2_X1 U319 ( .A(n144), .B(n143), .Z(n165) );
  AND2_X1 U320 ( .A1(temp_hpc2_v_1_order1_HPC26), .A2(n165), .ZN(N34) );
  AND2_X1 U321 ( .A1(temp_hpc2_v_1_order1_HPC25), .A2(n165), .ZN(N30) );
  AND2_X1 U322 ( .A1(nt0_1_reg), .A2(n165), .ZN(u11_HPC26) );
  AND2_X1 U323 ( .A1(nt2_1_reg), .A2(n165), .ZN(u11_HPC25) );
  AND2_X1 U324 ( .A1(n3_1_reg), .A2(n124), .ZN(u11_HPC24) );
  AND2_X1 U325 ( .A1(temp_hpc2_v_1_order1_HPC24), .A2(n124), .ZN(N26) );
  INV_X1 U326 ( .A(rand_11), .ZN(n176) );
  NOR2_X1 U327 ( .A1(n165), .A2(n176), .ZN(N35) );
  INV_X1 U328 ( .A(rand_10), .ZN(n174) );
  NOR2_X1 U329 ( .A1(n165), .A2(n174), .ZN(N31) );
  NOR2_X1 U330 ( .A1(n164), .A2(n176), .ZN(N33) );
  NOR2_X1 U331 ( .A1(n164), .A2(n174), .ZN(N29) );
  INV_X1 U332 ( .A(rand_9), .ZN(n156) );
  NOR2_X1 U333 ( .A1(n130), .A2(n156), .ZN(N25) );
  INV_X1 U334 ( .A(rand_12), .ZN(n175) );
  NOR2_X1 U335 ( .A1(n175), .A2(n163), .ZN(N37) );
  NOR2_X1 U336 ( .A1(n167), .A2(n175), .ZN(N39) );
  NOR2_X1 U337 ( .A1(n124), .A2(n156), .ZN(N27) );
  NAND2_X1 U338 ( .A1(rand_7), .A2(n145), .ZN(n146) );
  XNOR2_X1 U339 ( .A(rand_8), .B(n146), .ZN(N21) );
  XOR2_X1 U340 ( .A(v10_HPC26), .B(w10_HPC26), .Z(n148) );
  XOR2_X1 U341 ( .A(n116), .B(u11_HPC26_reg), .Z(n147) );
  XNOR2_X1 U342 ( .A(n148), .B(n147), .ZN(o4_val_1) );
  XOR2_X1 U343 ( .A(v01_HPC26), .B(w01_HPC26), .Z(n150) );
  XOR2_X1 U344 ( .A(n115), .B(u00_HPC26_reg), .Z(n149) );
  XNOR2_X1 U345 ( .A(n150), .B(n149), .ZN(o4_val_0) );
  XOR2_X1 U346 ( .A(v10_HPC27), .B(w10_HPC27), .Z(n152) );
  XOR2_X1 U347 ( .A(n114), .B(u11_HPC27_reg), .Z(n151) );
  XNOR2_X1 U348 ( .A(n152), .B(n151), .ZN(o0_val_1) );
  XOR2_X1 U349 ( .A(v01_HPC27), .B(w01_HPC27), .Z(n154) );
  XOR2_X1 U350 ( .A(n113), .B(u00_HPC27_reg), .Z(n153) );
  XNOR2_X1 U351 ( .A(n154), .B(n153), .ZN(o0_val_0) );
  NAND2_X1 U352 ( .A1(rand_7), .A2(n166), .ZN(n155) );
  XNOR2_X1 U353 ( .A(rand_8), .B(n155), .ZN(N23) );
  XOR2_X1 U354 ( .A(n115), .B(rand_3), .Z(N14) );
  XOR2_X1 U355 ( .A(n116), .B(rand_3), .Z(N12) );
  XOR2_X1 U356 ( .A(n156), .B(i3_0), .Z(N1) );
  XOR2_X1 U357 ( .A(n156), .B(i3_1), .Z(N0) );
  XOR2_X1 U358 ( .A(n113), .B(rand_5), .Z(N18) );
  XOR2_X1 U359 ( .A(n114), .B(rand_5), .Z(N16) );
  NAND2_X1 U360 ( .A1(rand_5), .A2(i1_1), .ZN(n157) );
  XNOR2_X1 U361 ( .A(n157), .B(rand_6), .ZN(N19) );
  NAND2_X1 U362 ( .A1(rand_5), .A2(i1_0), .ZN(n158) );
  XNOR2_X1 U363 ( .A(n158), .B(rand_6), .ZN(N17) );
  NAND2_X1 U364 ( .A1(rand_3), .A2(i2_1), .ZN(n159) );
  XNOR2_X1 U365 ( .A(n159), .B(rand_4), .ZN(N15) );
  NAND2_X1 U366 ( .A1(rand_3), .A2(i2_0), .ZN(n160) );
  XNOR2_X1 U367 ( .A(n160), .B(rand_4), .ZN(N13) );
  NAND2_X1 U368 ( .A1(rand_1), .A2(i7_1), .ZN(n161) );
  XNOR2_X1 U369 ( .A(n161), .B(rand_2), .ZN(N11) );
  XNOR2_X1 U370 ( .A(i6_0), .B(rand_1), .ZN(N10) );
  NAND2_X1 U371 ( .A1(rand_1), .A2(i7_0), .ZN(n162) );
  XNOR2_X1 U372 ( .A(n162), .B(rand_2), .ZN(N9) );
  XNOR2_X1 U373 ( .A(i6_1), .B(rand_1), .ZN(N8) );
  NOR2_X1 U374 ( .A1(i1_1), .A2(i2_1), .ZN(u11_HPC32) );
  NOR2_X1 U375 ( .A1(i1_0), .A2(i2_0), .ZN(u00_HPC32) );
  NOR2_X1 U376 ( .A1(i3_1), .A2(i2_1), .ZN(u11_HPC31) );
  NOR2_X1 U377 ( .A1(i3_0), .A2(i2_0), .ZN(u00_HPC31) );
  NOR2_X1 U378 ( .A1(i7_1), .A2(i6_1), .ZN(u11_HPC30) );
  NOR2_X1 U379 ( .A1(i7_0), .A2(i6_0), .ZN(u00_HPC30) );
  XOR2_X1 U380 ( .A(i7_0), .B(n163), .Z(o1_val_0) );
  XOR2_X1 U381 ( .A(i5_0), .B(n164), .Z(o7_val_0) );
  XOR2_X1 U382 ( .A(i0_0), .B(n130), .Z(o5_val_0) );
  XNOR2_X1 U383 ( .A(i5_1), .B(n165), .ZN(o7_val_1) );
  XOR2_X1 U384 ( .A(i0_1), .B(n166), .Z(o5_val_1) );
  XOR2_X1 U385 ( .A(n118), .B(n167), .Z(o1_val_1) );
  NAND2_X1 U386 ( .A1(n1_1_reg), .A2(temp_hpc3_v_1_order1_HPC32), .ZN(n168) );
  XNOR2_X1 U387 ( .A(n168), .B(w10_HPC32), .ZN(n169) );
  XNOR2_X1 U388 ( .A(u11_HPC32_reg), .B(n169), .ZN(n125) );
  XNOR2_X1 U389 ( .A(i6_1), .B(n125), .ZN(o2_val_1) );
  XOR2_X1 U390 ( .A(u00_HPC32_reg), .B(w01_HPC32), .Z(n171) );
  NAND2_X1 U391 ( .A1(n1_0_reg), .A2(temp_hpc3_v_1_order0_HPC32), .ZN(n170) );
  XNOR2_X1 U392 ( .A(n171), .B(n170), .ZN(n129) );
  XOR2_X1 U393 ( .A(n129), .B(i6_0), .Z(o2_val_0) );
  XNOR2_X1 U394 ( .A(n129), .B(n174), .ZN(N3) );
  XOR2_X1 U395 ( .A(v10_HPC24), .B(w10_HPC24), .Z(n172) );
  XNOR2_X1 U396 ( .A(u11_HPC24_reg), .B(n172), .ZN(n126) );
  XOR2_X1 U397 ( .A(n112), .B(n126), .Z(o3_val_1) );
  XNOR2_X1 U398 ( .A(u00_HPC24_reg), .B(v01_HPC24), .ZN(n173) );
  XNOR2_X1 U399 ( .A(n173), .B(w01_HPC24), .ZN(n128) );
  XOR2_X1 U400 ( .A(n128), .B(i1_0), .Z(o3_val_0) );
  XNOR2_X1 U401 ( .A(n128), .B(n175), .ZN(N7) );
  XOR2_X1 U402 ( .A(n127), .B(i4_0), .Z(o6_val_0) );
  XNOR2_X1 U403 ( .A(n127), .B(n176), .ZN(N5) );
  XOR2_X1 U404 ( .A(rand_7), .B(n127), .Z(N22) );
  XNOR2_X1 U405 ( .A(i4_1), .B(n123), .ZN(o6_val_1) );
  XNOR2_X1 U406 ( .A(n174), .B(n125), .ZN(n122) );
  XNOR2_X1 U407 ( .A(n175), .B(n126), .ZN(n121) );
  XNOR2_X1 U408 ( .A(n176), .B(n123), .ZN(n120) );
  XOR2_X1 U409 ( .A(rand_7), .B(n123), .Z(n119) );
endmodule
