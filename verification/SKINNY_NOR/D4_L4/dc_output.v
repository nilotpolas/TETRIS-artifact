/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Ultra(TM) in wire load mode
// Version   : O-2018.06-SP1
// Date      : Tue Jun 30 19:12:43 2026
/////////////////////////////////////////////////////////////


module sbox ( clk, i0_0, i0_1, i0_2, i0_3, i1_0, i1_1, i1_2, i1_3, i2_0, i2_1, 
        i2_2, i2_3, i3_0, i3_1, i3_2, i3_3, i4_0, i4_1, i4_2, i4_3, i5_0, i5_1, 
        i5_2, i5_3, i6_0, i6_1, i6_2, i6_3, i7_0, i7_1, i7_2, i7_3, rand_47, 
        rand_1, rand_17, rand_37, rand_48, rand_64, rand_65, rand_2, rand_18, 
        rand_32, rand_33, rand_50, rand_66, rand_3, rand_19, rand_34, rand_51, 
        rand_67, rand_4, rand_20, rand_35, rand_52, rand_68, rand_5, rand_25, 
        rand_36, rand_53, rand_69, rand_6, rand_21, rand_38, rand_54, rand_70, 
        rand_7, rand_22, rand_39, rand_55, rand_71, rand_8, rand_23, rand_40, 
        rand_56, rand_72, rand_13, rand_24, rand_41, rand_57, rand_9, rand_26, 
        rand_42, rand_58, rand_10, rand_27, rand_43, rand_59, rand_11, rand_28, 
        rand_44, rand_60, rand_12, rand_29, rand_49, rand_61, rand_14, rand_30, 
        rand_45, rand_62, rand_15, rand_31, rand_46, rand_63, rand_16, o0_0, 
        o0_1, o0_2, o0_3, o1_0, o1_1, o1_2, o1_3, o2_0, o2_1, o2_2, o2_3, o3_0, 
        o3_1, o3_2, o3_3, o4_0, o4_1, o4_2, o4_3, o5_0, o5_1, o5_2, o5_3, o6_0, 
        o6_1, o6_2, o6_3, o7_0, o7_1, o7_2, o7_3 );
  input clk, i0_0, i0_1, i0_2, i0_3, i1_0, i1_1, i1_2, i1_3, i2_0, i2_1, i2_2,
         i2_3, i3_0, i3_1, i3_2, i3_3, i4_0, i4_1, i4_2, i4_3, i5_0, i5_1,
         i5_2, i5_3, i6_0, i6_1, i6_2, i6_3, i7_0, i7_1, i7_2, i7_3, rand_47,
         rand_1, rand_17, rand_37, rand_48, rand_64, rand_65, rand_2, rand_18,
         rand_32, rand_33, rand_50, rand_66, rand_3, rand_19, rand_34, rand_51,
         rand_67, rand_4, rand_20, rand_35, rand_52, rand_68, rand_5, rand_25,
         rand_36, rand_53, rand_69, rand_6, rand_21, rand_38, rand_54, rand_70,
         rand_7, rand_22, rand_39, rand_55, rand_71, rand_8, rand_23, rand_40,
         rand_56, rand_72, rand_13, rand_24, rand_41, rand_57, rand_9, rand_26,
         rand_42, rand_58, rand_10, rand_27, rand_43, rand_59, rand_11,
         rand_28, rand_44, rand_60, rand_12, rand_29, rand_49, rand_61,
         rand_14, rand_30, rand_45, rand_62, rand_15, rand_31, rand_46,
         rand_63, rand_16;
  output o0_0, o0_1, o0_2, o0_3, o1_0, o1_1, o1_2, o1_3, o2_0, o2_1, o2_2,
         o2_3, o3_0, o3_1, o3_2, o3_3, o4_0, o4_1, o4_2, o4_3, o5_0, o5_1,
         o5_2, o5_3, o6_0, o6_1, o6_2, o6_3, o7_0, o7_1, o7_2, o7_3;
  wire   u00_HPC30, temp_hpc3_v_3_order0_HPC30, n7_0_reg, w01_HPC30,
         temp_hpc3_v_3_order1_HPC30, w02_HPC30, temp_hpc3_v_3_order2_HPC30,
         w03_HPC30, temp_hpc3_v_3_order3_HPC30, n7_1_reg, w10_HPC30, u11_HPC30,
         temp_hpc3_v_3_order4_HPC30, w12_HPC30, temp_hpc3_v_3_order5_HPC30,
         w13_HPC30, temp_hpc3_v_3_order6_HPC30, n7_2_reg, w20_HPC30,
         temp_hpc3_v_3_order7_HPC30, w21_HPC30, u22_HPC30,
         temp_hpc3_v_3_order8_HPC30, w23_HPC30, temp_hpc3_v_3_order9_HPC30,
         n7_3_reg, w30_HPC30, temp_hpc3_v_3_order10_HPC30, w31_HPC30,
         temp_hpc3_v_3_order11_HPC30, w32_HPC30, u33_HPC30, u00_HPC30_reg,
         u11_HPC30_reg, u22_HPC30_reg, u33_HPC30_reg, u00_HPC31,
         temp_hpc3_v_3_order0_HPC31, n2_0_reg, w01_HPC31,
         temp_hpc3_v_3_order1_HPC31, w02_HPC31, temp_hpc3_v_3_order2_HPC31,
         w03_HPC31, temp_hpc3_v_3_order3_HPC31, n2_1_reg, w10_HPC31, u11_HPC31,
         temp_hpc3_v_3_order4_HPC31, w12_HPC31, temp_hpc3_v_3_order5_HPC31,
         w13_HPC31, temp_hpc3_v_3_order6_HPC31, n2_2_reg, w20_HPC31,
         temp_hpc3_v_3_order7_HPC31, w21_HPC31, u22_HPC31,
         temp_hpc3_v_3_order8_HPC31, w23_HPC31, temp_hpc3_v_3_order9_HPC31,
         n2_3_reg, w30_HPC31, temp_hpc3_v_3_order10_HPC31, w31_HPC31,
         temp_hpc3_v_3_order11_HPC31, w32_HPC31, u33_HPC31, u00_HPC31_reg,
         u11_HPC31_reg, u22_HPC31_reg, u33_HPC31_reg, u00_HPC32,
         temp_hpc3_v_3_order0_HPC32, n1_0_reg, w01_HPC32,
         temp_hpc3_v_3_order1_HPC32, w02_HPC32, temp_hpc3_v_3_order2_HPC32,
         w03_HPC32, temp_hpc3_v_3_order3_HPC32, n1_1_reg, w10_HPC32, u11_HPC32,
         temp_hpc3_v_3_order4_HPC32, w12_HPC32, temp_hpc3_v_3_order5_HPC32,
         w13_HPC32, temp_hpc3_v_3_order6_HPC32, n1_2_reg, w20_HPC32,
         temp_hpc3_v_3_order7_HPC32, w21_HPC32, u22_HPC32,
         temp_hpc3_v_3_order8_HPC32, w23_HPC32, temp_hpc3_v_3_order9_HPC32,
         n1_3_reg, w30_HPC32, temp_hpc3_v_3_order10_HPC32, w31_HPC32,
         temp_hpc3_v_3_order11_HPC32, w32_HPC32, u33_HPC32, u00_HPC32_reg,
         u11_HPC32_reg, u22_HPC32_reg, u33_HPC32_reg, u00_HPC33,
         temp_hpc3_v_3_order0_HPC33, nt1_0_reg, w01_HPC33,
         temp_hpc3_v_3_order1_HPC33, w02_HPC33, temp_hpc3_v_3_order2_HPC33,
         w03_HPC33, temp_hpc3_v_3_order3_HPC33, nt1_1_reg, w10_HPC33,
         u11_HPC33, temp_hpc3_v_3_order4_HPC33, w12_HPC33,
         temp_hpc3_v_3_order5_HPC33, w13_HPC33, temp_hpc3_v_3_order6_HPC33,
         nt1_2_reg, w20_HPC33, temp_hpc3_v_3_order7_HPC33, w21_HPC33,
         u22_HPC33, temp_hpc3_v_3_order8_HPC33, w23_HPC33,
         temp_hpc3_v_3_order9_HPC33, nt1_3_reg, w30_HPC33,
         temp_hpc3_v_3_order10_HPC33, w31_HPC33, temp_hpc3_v_3_order11_HPC33,
         w32_HPC33, u33_HPC33, u00_HPC33_reg, u11_HPC33_reg, u22_HPC33_reg,
         u33_HPC33_reg, n3_0_reg, u00_HPC24, v01_HPC24, w01_HPC24, v02_HPC24,
         w02_HPC24, v03_HPC24, w03_HPC24, v10_HPC24, w10_HPC24, n3_1_reg,
         u11_HPC24, v12_HPC24, w12_HPC24, v13_HPC24, w13_HPC24, v20_HPC24,
         w20_HPC24, v21_HPC24, w21_HPC24, n3_2_reg, u22_HPC24, v23_HPC24,
         w23_HPC24, v30_HPC24, w30_HPC24, v31_HPC24, w31_HPC24, v32_HPC24,
         w32_HPC24, n3_3_reg, u33_HPC24, u00_HPC24_reg, u11_HPC24_reg,
         u22_HPC24_reg, u33_HPC24_reg, nt2_0_reg, u00_HPC25, v01_HPC25,
         w01_HPC25, v02_HPC25, w02_HPC25, v03_HPC25, w03_HPC25, v10_HPC25,
         w10_HPC25, nt2_1_reg, u11_HPC25, v12_HPC25, w12_HPC25, v13_HPC25,
         w13_HPC25, v20_HPC25, w20_HPC25, v21_HPC25, w21_HPC25, nt2_2_reg,
         u22_HPC25, v23_HPC25, w23_HPC25, v30_HPC25, w30_HPC25, v31_HPC25,
         w31_HPC25, v32_HPC25, w32_HPC25, nt2_3_reg, u33_HPC25, u00_HPC25_reg,
         u11_HPC25_reg, u22_HPC25_reg, u33_HPC25_reg, nt0_0_reg, u00_HPC26,
         v01_HPC26, w01_HPC26, v02_HPC26, w02_HPC26, v03_HPC26, w03_HPC26,
         v10_HPC26, w10_HPC26, nt0_1_reg, u11_HPC26, v12_HPC26, w12_HPC26,
         v13_HPC26, w13_HPC26, v20_HPC26, w20_HPC26, v21_HPC26, w21_HPC26,
         nt0_2_reg, u22_HPC26, v23_HPC26, w23_HPC26, v30_HPC26, w30_HPC26,
         v31_HPC26, w31_HPC26, v32_HPC26, w32_HPC26, nt0_3_reg, u33_HPC26,
         u00_HPC26_reg, u11_HPC26_reg, u22_HPC26_reg, u33_HPC26_reg, nt4_0_reg,
         u00_HPC27, v01_HPC27, w01_HPC27, v02_HPC27, w02_HPC27, v03_HPC27,
         w03_HPC27, v10_HPC27, w10_HPC27, nt4_1_reg, u11_HPC27, v12_HPC27,
         w12_HPC27, v13_HPC27, w13_HPC27, v20_HPC27, w20_HPC27, v21_HPC27,
         w21_HPC27, nt4_2_reg, u22_HPC27, v23_HPC27, w23_HPC27, v30_HPC27,
         w30_HPC27, v31_HPC27, w31_HPC27, v32_HPC27, w32_HPC27, nt4_3_reg,
         u33_HPC27, u00_HPC27_reg, u11_HPC27_reg, u22_HPC27_reg, u33_HPC27_reg,
         o6_val_0, o6_val_1, o6_val_2, o6_val_3, o5_val_0, o5_val_1, o5_val_2,
         o5_val_3, o2_val_0, o2_val_1, o2_val_2, o2_val_3, o7_val_0, o7_val_1,
         o7_val_2, o7_val_3, o0_val_0, o0_val_1, o0_val_2, o0_val_3, o4_val_0,
         o4_val_1, o4_val_2, o4_val_3, o1_val_0, o1_val_1, o1_val_2, o1_val_3,
         o3_val_0, o3_val_1, o3_val_2, o3_val_3, N0, N1, N2, N3, N4, N5, N6,
         N7, N8, N9, N10, N11, N12, N13, N15, N16, N18, N19, N21, N22, N23,
         N24, N25, N27, N28, N30, N31, N33, N34, N35, N36, N37, N39, N40, N42,
         N43, N45, N46, N47, z3009_assgn30090, z3011_assgn30110,
         z3013_assgn30130, z3015_assgn30150, z3033_assgn30330,
         z3035_assgn30350, z3037_assgn30370, z3039_assgn30390,
         z3041_assgn30410, z3043_assgn30430, z3045_assgn30450,
         z3047_assgn30470, N48, N49, N50, N51, N52, N53, N54, N55, N56, N57,
         N58, N59, N60, N61, N62, N63, N64, N65, N66, N67, N68, N69, N70, N71,
         N72, N73, N74, N75, N76, N77, N78, N79, N80, N81, N82, N83, N84, N85,
         N86, N87, N88, N89, N90, N91, N92, N93, N94, N95, N96, N97, N98, N99,
         N100, N101, N102, N103, N104, N105, N106, N107, N108, N109, N110,
         N111, N112, N113, N114, N115, N116, N117, N118, N119, N120, N121,
         N122, N123, N125, N126, N127, N128, N129, N131, N132, N133, N134,
         N135, N137, N138, N139, N140, N141, N142, N143,
         temp_hpc2_v_3_order0_HPC24, N144, N145, temp_hpc2_v_3_order1_HPC24,
         N146, N147, temp_hpc2_v_3_order2_HPC24, N148, N149,
         temp_hpc2_v_3_order3_HPC24, N150, N151, temp_hpc2_v_3_order4_HPC24,
         N152, N153, temp_hpc2_v_3_order5_HPC24, N154, N155,
         temp_hpc2_v_3_order6_HPC24, N156, N157, temp_hpc2_v_3_order7_HPC24,
         N158, N159, temp_hpc2_v_3_order8_HPC24, N160, N161,
         temp_hpc2_v_3_order9_HPC24, N162, N163, temp_hpc2_v_3_order10_HPC24,
         N164, N165, temp_hpc2_v_3_order11_HPC24, N166, N167,
         temp_hpc2_v_3_order0_HPC25, N168, N169, temp_hpc2_v_3_order1_HPC25,
         N170, N171, temp_hpc2_v_3_order2_HPC25, N172, N173,
         temp_hpc2_v_3_order3_HPC25, N174, N175, temp_hpc2_v_3_order4_HPC25,
         N176, N177, temp_hpc2_v_3_order5_HPC25, N178, N179,
         temp_hpc2_v_3_order6_HPC25, N180, N181, temp_hpc2_v_3_order7_HPC25,
         N182, N183, temp_hpc2_v_3_order8_HPC25, N184, N185,
         temp_hpc2_v_3_order9_HPC25, N186, N187, temp_hpc2_v_3_order10_HPC25,
         N188, N189, temp_hpc2_v_3_order11_HPC25, N190, N191,
         temp_hpc2_v_3_order0_HPC26, N192, N193, temp_hpc2_v_3_order1_HPC26,
         N194, N195, temp_hpc2_v_3_order2_HPC26, N196, N197,
         temp_hpc2_v_3_order3_HPC26, N198, N199, temp_hpc2_v_3_order4_HPC26,
         N200, N201, temp_hpc2_v_3_order5_HPC26, N202, N203,
         temp_hpc2_v_3_order6_HPC26, N204, N205, temp_hpc2_v_3_order7_HPC26,
         N206, N207, temp_hpc2_v_3_order8_HPC26, N208, N209,
         temp_hpc2_v_3_order9_HPC26, N210, N211, temp_hpc2_v_3_order10_HPC26,
         N212, N213, temp_hpc2_v_3_order11_HPC26, N214, N215,
         temp_hpc2_v_3_order0_HPC27, N216, N217, temp_hpc2_v_3_order1_HPC27,
         N218, N219, temp_hpc2_v_3_order2_HPC27, N220, N221,
         temp_hpc2_v_3_order3_HPC27, N222, N223, temp_hpc2_v_3_order4_HPC27,
         N224, N225, temp_hpc2_v_3_order5_HPC27, N226, N227,
         temp_hpc2_v_3_order6_HPC27, N228, N229, temp_hpc2_v_3_order7_HPC27,
         N230, N231, temp_hpc2_v_3_order8_HPC27, N232, N233,
         temp_hpc2_v_3_order9_HPC27, N234, N235, temp_hpc2_v_3_order10_HPC27,
         N236, N237, temp_hpc2_v_3_order11_HPC27, N238, N239, z3009_assgn30091,
         z3011_assgn30111, z3013_assgn30131, z3015_assgn30151,
         z3017_assgn30170, z3019_assgn30190, z3021_assgn30210,
         z3023_assgn30230, z3033_assgn30331, z3035_assgn30351,
         z3037_assgn30371, z3039_assgn30391, z3041_assgn30411,
         z3043_assgn30431, z3045_assgn30451, z3047_assgn30471,
         z3049_assgn30490, z3051_assgn30510, z3053_assgn30530,
         z3055_assgn30550, n603, n604, n605, n606, n607, n608, n609, n610,
         n611, n612, n613, n614, n615, n616, n617, n618, n619, n620, n621,
         n622, n623, n624, n625, n626, n627, n628, n629, n630, n631, n632,
         n633, n634, n635, n636, n637, n638, n639, n640, n641, n642, n643,
         n644, n645, n646, n647, n648, n649, n650, n651, n652, n653, n654,
         n655, n656, n657, n658, n659, n660, n661, n662, n663, n664, n665,
         n666, n667, n668, n669, n670, n671, n672, n673, n674, n675, n676,
         n677, n678, n679, n680, n681, n682, n683, n684, n685, n686, n687,
         n688, n689, n690, n691, n692, n693, n694, n695, n696, n697, n698,
         n699, n700, n701, n702, n703, n704, n705, n706, n707, n708, n709,
         n710, n711, n712, n713, n714, n715, n716, n717, n718, n719, n720,
         n721, n722, n723, n724, n725, n726, n727, n728, n729, n730, n731,
         n732, n733, n734, n735, n736, n737, n738, n739, n740, n741, n742,
         n743, n744, n745, n746, n747, n748, n749, n750, n751, n752, n753,
         n754, n755, n756, n757, n758, n759, n760, n761, n762, n763, n764,
         n765, n766, n767, n768, n769, n770, n771, n772, n773, n774, n775,
         n776, n777, n778, n779, n780, n781, n782, n783, n784, n785, n786,
         n787, n788, n789, n790, n791, n792, n793, n794, n795, n796, n797,
         n798, n799, n800, n801, n802, n803, n804, n805, n806, n807, n808,
         n809, n810, n811, n812, n813, n814, n815, n816, n817, n818, n819,
         n820, n821, n822, n823, n824, n825, n826, n827, n828, n829, n830,
         n831, n832, n833, n834, n835, n836, n837, n838, n839, n840, n841,
         n842, n843, n844, n845, n846, n847, n848, n849, n850, n851, n852,
         n853, n854, n855, n856, n857, n858, n859, n860, n861, n862, n863,
         n864, n865, n866, n867, n868, n869, n870, n871, n872, n873, n874,
         n875, n876, n877, n878, n879, n880, n881, n882, n883, n884, n885,
         n886, n887, n888, n889, n890, n891, n892, n893, n894, n895, n896,
         n897, n898, n899, n900, n901, n902, n903, n904, n905, n906, n907,
         n908, n909, n910, n911, n912, n913, n914;

  DFF_X1 temp_hpc2_v_3_order11_HPC24_reg ( .D(N11), .CK(clk), 
        .Q(temp_hpc2_v_3_order11_HPC24) );
  DFF_X1 temp_hpc2_v_3_order0_HPC24_reg ( .D(N0), .CK(clk), 
        .Q(temp_hpc2_v_3_order0_HPC24) );
  DFF_X1 temp_hpc2_v_3_order1_HPC24_reg ( .D(N1), .CK(clk), 
        .Q(temp_hpc2_v_3_order1_HPC24) );
  DFF_X1 temp_hpc2_v_3_order2_HPC24_reg ( .D(N2), .CK(clk), 
        .Q(temp_hpc2_v_3_order2_HPC24) );
  DFF_X1 temp_hpc2_v_3_order3_HPC24_reg ( .D(N3), .CK(clk), 
        .Q(temp_hpc2_v_3_order3_HPC24) );
  DFF_X1 temp_hpc2_v_3_order6_HPC24_reg ( .D(N6), .CK(clk), 
        .Q(temp_hpc2_v_3_order6_HPC24) );
  DFF_X1 temp_hpc2_v_3_order8_HPC24_reg ( .D(N8), .CK(clk), 
        .Q(temp_hpc2_v_3_order8_HPC24) );
  DFF_X1 temp_hpc2_v_3_order9_HPC24_reg ( .D(N9), .CK(clk), 
        .Q(temp_hpc2_v_3_order9_HPC24) );
  DFF_X1 temp_hpc2_v_3_order7_HPC24_reg ( .D(N7), .CK(clk), 
        .Q(temp_hpc2_v_3_order7_HPC24) );
  DFF_X1 temp_hpc2_v_3_order4_HPC24_reg ( .D(N4), .CK(clk), 
        .Q(temp_hpc2_v_3_order4_HPC24) );
  DFF_X1 temp_hpc2_v_3_order5_HPC24_reg ( .D(N5), .CK(clk), 
        .Q(temp_hpc2_v_3_order5_HPC24) );
  DFF_X1 temp_hpc2_v_3_order10_HPC24_reg ( .D(N10), .CK(clk), 
        .Q(temp_hpc2_v_3_order10_HPC24) );
  DFF_X1 temp_hpc3_v_3_order0_HPC30_reg ( .D(N48), .CK(clk), 
        .Q(temp_hpc3_v_3_order0_HPC30) );
  DFF_X1 n7_0_reg_reg ( .D(n615), .CK(clk), .Q(n7_0_reg) );
  DFF_X1 w01_HPC30_reg ( .D(N49), .CK(clk), .Q(w01_HPC30) );
  DFF_X1 temp_hpc3_v_3_order1_HPC30_reg ( .D(N50), .CK(clk), 
        .Q(temp_hpc3_v_3_order1_HPC30) );
  DFF_X1 w02_HPC30_reg ( .D(N51), .CK(clk), .Q(w02_HPC30) );
  DFF_X1 temp_hpc3_v_3_order2_HPC30_reg ( .D(N52), .CK(clk), 
        .Q(temp_hpc3_v_3_order2_HPC30) );
  DFF_X1 w03_HPC30_reg ( .D(N53), .CK(clk), .Q(w03_HPC30) );
  DFF_X1 temp_hpc3_v_3_order3_HPC30_reg ( .D(N54), .CK(clk), 
        .Q(temp_hpc3_v_3_order3_HPC30) );
  DFF_X1 n7_1_reg_reg ( .D(n616), .CK(clk), .Q(n7_1_reg) );
  DFF_X1 w10_HPC30_reg ( .D(N55), .CK(clk), .Q(w10_HPC30) );
  DFF_X1 temp_hpc3_v_3_order4_HPC30_reg ( .D(N56), .CK(clk), 
        .Q(temp_hpc3_v_3_order4_HPC30) );
  DFF_X1 w12_HPC30_reg ( .D(N57), .CK(clk), .Q(w12_HPC30) );
  DFF_X1 temp_hpc3_v_3_order5_HPC30_reg ( .D(N58), .CK(clk), 
        .Q(temp_hpc3_v_3_order5_HPC30) );
  DFF_X1 w13_HPC30_reg ( .D(N59), .CK(clk), .Q(w13_HPC30) );
  DFF_X1 temp_hpc3_v_3_order6_HPC30_reg ( .D(N60), .CK(clk), 
        .Q(temp_hpc3_v_3_order6_HPC30) );
  DFF_X1 n7_2_reg_reg ( .D(n617), .CK(clk), .Q(n7_2_reg) );
  DFF_X1 w20_HPC30_reg ( .D(N61), .CK(clk), .Q(w20_HPC30) );
  DFF_X1 temp_hpc3_v_3_order7_HPC30_reg ( .D(N62), .CK(clk), 
        .Q(temp_hpc3_v_3_order7_HPC30) );
  DFF_X1 w21_HPC30_reg ( .D(N63), .CK(clk), .Q(w21_HPC30) );
  DFF_X1 temp_hpc3_v_3_order8_HPC30_reg ( .D(N64), .CK(clk), 
        .Q(temp_hpc3_v_3_order8_HPC30) );
  DFF_X1 w23_HPC30_reg ( .D(N65), .CK(clk), .Q(w23_HPC30) );
  DFF_X1 temp_hpc3_v_3_order9_HPC30_reg ( .D(N66), .CK(clk), 
        .Q(temp_hpc3_v_3_order9_HPC30) );
  DFF_X1 n7_3_reg_reg ( .D(n618), .CK(clk), .Q(n7_3_reg) );
  DFF_X1 w30_HPC30_reg ( .D(N67), .CK(clk), .Q(w30_HPC30) );
  DFF_X1 temp_hpc3_v_3_order10_HPC30_reg ( .D(N68), .CK(clk), 
        .Q(temp_hpc3_v_3_order10_HPC30) );
  DFF_X1 w31_HPC30_reg ( .D(N69), .CK(clk), .Q(w31_HPC30) );
  DFF_X1 temp_hpc3_v_3_order11_HPC30_reg ( .D(N70), .CK(clk), 
        .Q(temp_hpc3_v_3_order11_HPC30) );
  DFF_X1 w32_HPC30_reg ( .D(N71), .CK(clk), .Q(w32_HPC30) );
  DFF_X1 u00_HPC30_reg_reg ( .D(u00_HPC30), .CK(clk), .Q(u00_HPC30_reg) );
  DFF_X1 nt0_0_reg_reg ( .D(n637), .CK(clk), .Q(nt0_0_reg) );
  DFF_X1 z3041_assgn30410_reg ( .D(o6_val_0), .CK(clk), .Q(z3041_assgn30410)
         );
  DFF_X1 z3041_assgn30411_reg ( .D(z3041_assgn30410), .CK(clk), 
        .Q(z3041_assgn30411) );
  DFF_X1 o6_0_reg ( .D(z3041_assgn30411), .CK(clk), .Q(o6_0) );
  DFF_X1 temp_hpc2_v_3_order9_HPC26_reg ( .D(N33), .CK(clk), 
        .Q(temp_hpc2_v_3_order9_HPC26) );
  DFF_X1 temp_hpc2_v_3_order6_HPC26_reg ( .D(N30), .CK(clk), 
        .Q(temp_hpc2_v_3_order6_HPC26) );
  DFF_X1 temp_hpc2_v_3_order3_HPC26_reg ( .D(N27), .CK(clk), 
        .Q(temp_hpc2_v_3_order3_HPC26) );
  DFF_X1 u11_HPC30_reg_reg ( .D(u11_HPC30), .CK(clk), .Q(u11_HPC30_reg) );
  DFF_X1 nt0_1_reg_reg ( .D(n636), .CK(clk), .Q(nt0_1_reg) );
  DFF_X1 z3043_assgn30430_reg ( .D(o6_val_1), .CK(clk), .Q(z3043_assgn30430)
         );
  DFF_X1 z3043_assgn30431_reg ( .D(z3043_assgn30430), .CK(clk), 
        .Q(z3043_assgn30431) );
  DFF_X1 o6_1_reg ( .D(z3043_assgn30431), .CK(clk), .Q(o6_1) );
  DFF_X1 temp_hpc2_v_3_order10_HPC26_reg ( .D(N34), .CK(clk), 
        .Q(temp_hpc2_v_3_order10_HPC26) );
  DFF_X1 temp_hpc2_v_3_order7_HPC26_reg ( .D(N31), .CK(clk), 
        .Q(temp_hpc2_v_3_order7_HPC26) );
  DFF_X1 temp_hpc2_v_3_order0_HPC26_reg ( .D(N24), .CK(clk), 
        .Q(temp_hpc2_v_3_order0_HPC26) );
  DFF_X1 u22_HPC30_reg_reg ( .D(u22_HPC30), .CK(clk), .Q(u22_HPC30_reg) );
  DFF_X1 nt0_2_reg_reg ( .D(n635), .CK(clk), .Q(nt0_2_reg) );
  DFF_X1 z3045_assgn30450_reg ( .D(o6_val_2), .CK(clk), .Q(z3045_assgn30450)
         );
  DFF_X1 z3045_assgn30451_reg ( .D(z3045_assgn30450), .CK(clk), 
        .Q(z3045_assgn30451) );
  DFF_X1 o6_2_reg ( .D(z3045_assgn30451), .CK(clk), .Q(o6_2) );
  DFF_X1 temp_hpc2_v_3_order11_HPC26_reg ( .D(N35), .CK(clk), 
        .Q(temp_hpc2_v_3_order11_HPC26) );
  DFF_X1 temp_hpc2_v_3_order4_HPC26_reg ( .D(N28), .CK(clk), 
        .Q(temp_hpc2_v_3_order4_HPC26) );
  DFF_X1 temp_hpc2_v_3_order1_HPC26_reg ( .D(N25), .CK(clk), 
        .Q(temp_hpc2_v_3_order1_HPC26) );
  DFF_X1 u33_HPC30_reg_reg ( .D(u33_HPC30), .CK(clk), .Q(u33_HPC30_reg) );
  DFF_X1 nt0_3_reg_reg ( .D(n631), .CK(clk), .Q(nt0_3_reg) );
  DFF_X1 z3047_assgn30470_reg ( .D(o6_val_3), .CK(clk), .Q(z3047_assgn30470)
         );
  DFF_X1 z3047_assgn30471_reg ( .D(z3047_assgn30470), .CK(clk), 
        .Q(z3047_assgn30471) );
  DFF_X1 o6_3_reg ( .D(z3047_assgn30471), .CK(clk), .Q(o6_3) );
  DFF_X1 temp_hpc2_v_3_order8_HPC26_reg ( .D(n620), .CK(clk), 
        .Q(temp_hpc2_v_3_order8_HPC26) );
  DFF_X1 temp_hpc2_v_3_order5_HPC26_reg ( .D(n619), .CK(clk), 
        .Q(temp_hpc2_v_3_order5_HPC26) );
  DFF_X1 temp_hpc2_v_3_order2_HPC26_reg ( .D(n630), .CK(clk), 
        .Q(temp_hpc2_v_3_order2_HPC26) );
  DFF_X1 temp_hpc3_v_3_order0_HPC31_reg ( .D(N72), .CK(clk), 
        .Q(temp_hpc3_v_3_order0_HPC31) );
  DFF_X1 n2_0_reg_reg ( .D(n607), .CK(clk), .Q(n2_0_reg) );
  DFF_X1 w01_HPC31_reg ( .D(N73), .CK(clk), .Q(w01_HPC31) );
  DFF_X1 temp_hpc3_v_3_order1_HPC31_reg ( .D(N74), .CK(clk), 
        .Q(temp_hpc3_v_3_order1_HPC31) );
  DFF_X1 w02_HPC31_reg ( .D(N75), .CK(clk), .Q(w02_HPC31) );
  DFF_X1 temp_hpc3_v_3_order2_HPC31_reg ( .D(N76), .CK(clk), 
        .Q(temp_hpc3_v_3_order2_HPC31) );
  DFF_X1 w03_HPC31_reg ( .D(N77), .CK(clk), .Q(w03_HPC31) );
  DFF_X1 temp_hpc3_v_3_order3_HPC31_reg ( .D(N78), .CK(clk), 
        .Q(temp_hpc3_v_3_order3_HPC31) );
  DFF_X1 n2_1_reg_reg ( .D(n608), .CK(clk), .Q(n2_1_reg) );
  DFF_X1 w10_HPC31_reg ( .D(N79), .CK(clk), .Q(w10_HPC31) );
  DFF_X1 temp_hpc3_v_3_order4_HPC31_reg ( .D(N80), .CK(clk), 
        .Q(temp_hpc3_v_3_order4_HPC31) );
  DFF_X1 w12_HPC31_reg ( .D(N81), .CK(clk), .Q(w12_HPC31) );
  DFF_X1 temp_hpc3_v_3_order5_HPC31_reg ( .D(N82), .CK(clk), 
        .Q(temp_hpc3_v_3_order5_HPC31) );
  DFF_X1 w13_HPC31_reg ( .D(N83), .CK(clk), .Q(w13_HPC31) );
  DFF_X1 temp_hpc3_v_3_order6_HPC31_reg ( .D(N84), .CK(clk), 
        .Q(temp_hpc3_v_3_order6_HPC31) );
  DFF_X1 n2_2_reg_reg ( .D(n609), .CK(clk), .Q(n2_2_reg) );
  DFF_X1 w20_HPC31_reg ( .D(N85), .CK(clk), .Q(w20_HPC31) );
  DFF_X1 temp_hpc3_v_3_order7_HPC31_reg ( .D(N86), .CK(clk), 
        .Q(temp_hpc3_v_3_order7_HPC31) );
  DFF_X1 w21_HPC31_reg ( .D(N87), .CK(clk), .Q(w21_HPC31) );
  DFF_X1 temp_hpc3_v_3_order8_HPC31_reg ( .D(N88), .CK(clk), 
        .Q(temp_hpc3_v_3_order8_HPC31) );
  DFF_X1 w23_HPC31_reg ( .D(N89), .CK(clk), .Q(w23_HPC31) );
  DFF_X1 temp_hpc3_v_3_order9_HPC31_reg ( .D(N90), .CK(clk), 
        .Q(temp_hpc3_v_3_order9_HPC31) );
  DFF_X1 n2_3_reg_reg ( .D(n610), .CK(clk), .Q(n2_3_reg) );
  DFF_X1 w30_HPC31_reg ( .D(N91), .CK(clk), .Q(w30_HPC31) );
  DFF_X1 temp_hpc3_v_3_order10_HPC31_reg ( .D(N92), .CK(clk), 
        .Q(temp_hpc3_v_3_order10_HPC31) );
  DFF_X1 w31_HPC31_reg ( .D(N93), .CK(clk), .Q(w31_HPC31) );
  DFF_X1 temp_hpc3_v_3_order11_HPC31_reg ( .D(N94), .CK(clk), 
        .Q(temp_hpc3_v_3_order11_HPC31) );
  DFF_X1 w32_HPC31_reg ( .D(N95), .CK(clk), .Q(w32_HPC31) );
  DFF_X1 u00_HPC31_reg_reg ( .D(u00_HPC31), .CK(clk), .Q(u00_HPC31_reg) );
  DFF_X1 z3033_assgn30330_reg ( .D(o5_val_0), .CK(clk), .Q(z3033_assgn30330)
         );
  DFF_X1 z3033_assgn30331_reg ( .D(z3033_assgn30330), .CK(clk), 
        .Q(z3033_assgn30331) );
  DFF_X1 o5_0_reg ( .D(z3033_assgn30331), .CK(clk), .Q(o5_0) );
  DFF_X1 u11_HPC31_reg_reg ( .D(u11_HPC31), .CK(clk), .Q(u11_HPC31_reg) );
  DFF_X1 z3035_assgn30350_reg ( .D(o5_val_1), .CK(clk), .Q(z3035_assgn30350)
         );
  DFF_X1 z3035_assgn30351_reg ( .D(z3035_assgn30350), .CK(clk), 
        .Q(z3035_assgn30351) );
  DFF_X1 o5_1_reg ( .D(z3035_assgn30351), .CK(clk), .Q(o5_1) );
  DFF_X1 u22_HPC31_reg_reg ( .D(u22_HPC31), .CK(clk), .Q(u22_HPC31_reg) );
  DFF_X1 z3037_assgn30370_reg ( .D(o5_val_2), .CK(clk), .Q(z3037_assgn30370)
         );
  DFF_X1 z3037_assgn30371_reg ( .D(z3037_assgn30370), .CK(clk), 
        .Q(z3037_assgn30371) );
  DFF_X1 o5_2_reg ( .D(z3037_assgn30371), .CK(clk), .Q(o5_2) );
  DFF_X1 u33_HPC31_reg_reg ( .D(u33_HPC31), .CK(clk), .Q(u33_HPC31_reg) );
  DFF_X1 z3039_assgn30390_reg ( .D(o5_val_3), .CK(clk), .Q(z3039_assgn30390)
         );
  DFF_X1 z3039_assgn30391_reg ( .D(z3039_assgn30390), .CK(clk), 
        .Q(z3039_assgn30391) );
  DFF_X1 o5_3_reg ( .D(z3039_assgn30391), .CK(clk), .Q(o5_3) );
  DFF_X1 temp_hpc3_v_3_order0_HPC32_reg ( .D(N96), .CK(clk), 
        .Q(temp_hpc3_v_3_order0_HPC32) );
  DFF_X1 n1_0_reg_reg ( .D(n603), .CK(clk), .Q(n1_0_reg) );
  DFF_X1 w01_HPC32_reg ( .D(N97), .CK(clk), .Q(w01_HPC32) );
  DFF_X1 temp_hpc3_v_3_order1_HPC32_reg ( .D(N98), .CK(clk), 
        .Q(temp_hpc3_v_3_order1_HPC32) );
  DFF_X1 w02_HPC32_reg ( .D(N99), .CK(clk), .Q(w02_HPC32) );
  DFF_X1 temp_hpc3_v_3_order2_HPC32_reg ( .D(N100), .CK(clk), 
        .Q(temp_hpc3_v_3_order2_HPC32) );
  DFF_X1 w03_HPC32_reg ( .D(N101), .CK(clk), .Q(w03_HPC32) );
  DFF_X1 temp_hpc3_v_3_order3_HPC32_reg ( .D(N102), .CK(clk), 
        .Q(temp_hpc3_v_3_order3_HPC32) );
  DFF_X1 n1_1_reg_reg ( .D(n604), .CK(clk), .Q(n1_1_reg) );
  DFF_X1 w10_HPC32_reg ( .D(N103), .CK(clk), .Q(w10_HPC32) );
  DFF_X1 temp_hpc3_v_3_order4_HPC32_reg ( .D(N104), .CK(clk), 
        .Q(temp_hpc3_v_3_order4_HPC32) );
  DFF_X1 w12_HPC32_reg ( .D(N105), .CK(clk), .Q(w12_HPC32) );
  DFF_X1 temp_hpc3_v_3_order5_HPC32_reg ( .D(N106), .CK(clk), 
        .Q(temp_hpc3_v_3_order5_HPC32) );
  DFF_X1 w13_HPC32_reg ( .D(N107), .CK(clk), .Q(w13_HPC32) );
  DFF_X1 temp_hpc3_v_3_order6_HPC32_reg ( .D(N108), .CK(clk), 
        .Q(temp_hpc3_v_3_order6_HPC32) );
  DFF_X1 n1_2_reg_reg ( .D(n605), .CK(clk), .Q(n1_2_reg) );
  DFF_X1 w20_HPC32_reg ( .D(N109), .CK(clk), .Q(w20_HPC32) );
  DFF_X1 temp_hpc3_v_3_order7_HPC32_reg ( .D(N110), .CK(clk), 
        .Q(temp_hpc3_v_3_order7_HPC32) );
  DFF_X1 w21_HPC32_reg ( .D(N111), .CK(clk), .Q(w21_HPC32) );
  DFF_X1 temp_hpc3_v_3_order8_HPC32_reg ( .D(N112), .CK(clk), 
        .Q(temp_hpc3_v_3_order8_HPC32) );
  DFF_X1 w23_HPC32_reg ( .D(N113), .CK(clk), .Q(w23_HPC32) );
  DFF_X1 temp_hpc3_v_3_order9_HPC32_reg ( .D(N114), .CK(clk), 
        .Q(temp_hpc3_v_3_order9_HPC32) );
  DFF_X1 n1_3_reg_reg ( .D(n606), .CK(clk), .Q(n1_3_reg) );
  DFF_X1 w30_HPC32_reg ( .D(N115), .CK(clk), .Q(w30_HPC32) );
  DFF_X1 temp_hpc3_v_3_order10_HPC32_reg ( .D(N116), .CK(clk), 
        .Q(temp_hpc3_v_3_order10_HPC32) );
  DFF_X1 w31_HPC32_reg ( .D(N117), .CK(clk), .Q(w31_HPC32) );
  DFF_X1 temp_hpc3_v_3_order11_HPC32_reg ( .D(N118), .CK(clk), 
        .Q(temp_hpc3_v_3_order11_HPC32) );
  DFF_X1 w32_HPC32_reg ( .D(N119), .CK(clk), .Q(w32_HPC32) );
  DFF_X1 u00_HPC32_reg_reg ( .D(u00_HPC32), .CK(clk), .Q(u00_HPC32_reg) );
  DFF_X1 z3009_assgn30090_reg ( .D(o2_val_0), .CK(clk), .Q(z3009_assgn30090)
         );
  DFF_X1 z3009_assgn30091_reg ( .D(z3009_assgn30090), .CK(clk), 
        .Q(z3009_assgn30091) );
  DFF_X1 o2_0_reg ( .D(z3009_assgn30091), .CK(clk), .Q(o2_0) );
  DFF_X1 temp_hpc2_v_3_order9_HPC25_reg ( .D(N21), .CK(clk), 
        .Q(temp_hpc2_v_3_order9_HPC25) );
  DFF_X1 temp_hpc2_v_3_order6_HPC25_reg ( .D(N18), .CK(clk), 
        .Q(temp_hpc2_v_3_order6_HPC25) );
  DFF_X1 temp_hpc2_v_3_order3_HPC25_reg ( .D(N15), .CK(clk), 
        .Q(temp_hpc2_v_3_order3_HPC25) );
  DFF_X1 u11_HPC32_reg_reg ( .D(u11_HPC32), .CK(clk), .Q(u11_HPC32_reg) );
  DFF_X1 z3011_assgn30110_reg ( .D(o2_val_1), .CK(clk), .Q(z3011_assgn30110)
         );
  DFF_X1 z3011_assgn30111_reg ( .D(z3011_assgn30110), .CK(clk), 
        .Q(z3011_assgn30111) );
  DFF_X1 o2_1_reg ( .D(z3011_assgn30111), .CK(clk), .Q(o2_1) );
  DFF_X1 temp_hpc2_v_3_order10_HPC25_reg ( .D(N22), .CK(clk), 
        .Q(temp_hpc2_v_3_order10_HPC25) );
  DFF_X1 temp_hpc2_v_3_order7_HPC25_reg ( .D(N19), .CK(clk), 
        .Q(temp_hpc2_v_3_order7_HPC25) );
  DFF_X1 temp_hpc2_v_3_order0_HPC25_reg ( .D(N12), .CK(clk), 
        .Q(temp_hpc2_v_3_order0_HPC25) );
  DFF_X1 u22_HPC32_reg_reg ( .D(u22_HPC32), .CK(clk), .Q(u22_HPC32_reg) );
  DFF_X1 z3013_assgn30130_reg ( .D(o2_val_2), .CK(clk), .Q(z3013_assgn30130)
         );
  DFF_X1 z3013_assgn30131_reg ( .D(z3013_assgn30130), .CK(clk), 
        .Q(z3013_assgn30131) );
  DFF_X1 o2_2_reg ( .D(z3013_assgn30131), .CK(clk), .Q(o2_2) );
  DFF_X1 temp_hpc2_v_3_order11_HPC25_reg ( .D(N23), .CK(clk), 
        .Q(temp_hpc2_v_3_order11_HPC25) );
  DFF_X1 temp_hpc2_v_3_order4_HPC25_reg ( .D(N16), .CK(clk), 
        .Q(temp_hpc2_v_3_order4_HPC25) );
  DFF_X1 temp_hpc2_v_3_order1_HPC25_reg ( .D(N13), .CK(clk), 
        .Q(temp_hpc2_v_3_order1_HPC25) );
  DFF_X1 u33_HPC32_reg_reg ( .D(u33_HPC32), .CK(clk), .Q(u33_HPC32_reg) );
  DFF_X1 nt2_3_reg_reg ( .D(n633), .CK(clk), .Q(nt2_3_reg) );
  DFF_X1 z3015_assgn30150_reg ( .D(o2_val_3), .CK(clk), .Q(z3015_assgn30150)
         );
  DFF_X1 z3015_assgn30151_reg ( .D(z3015_assgn30150), .CK(clk), 
        .Q(z3015_assgn30151) );
  DFF_X1 o2_3_reg ( .D(z3015_assgn30151), .CK(clk), .Q(o2_3) );
  DFF_X1 temp_hpc2_v_3_order8_HPC25_reg ( .D(n629), .CK(clk), 
        .Q(temp_hpc2_v_3_order8_HPC25) );
  DFF_X1 temp_hpc2_v_3_order5_HPC25_reg ( .D(n628), .CK(clk), 
        .Q(temp_hpc2_v_3_order5_HPC25) );
  DFF_X1 temp_hpc2_v_3_order2_HPC25_reg ( .D(n626), .CK(clk), 
        .Q(temp_hpc2_v_3_order2_HPC25) );
  DFF_X1 temp_hpc3_v_3_order0_HPC33_reg ( .D(N120), .CK(clk), 
        .Q(temp_hpc3_v_3_order0_HPC33) );
  DFF_X1 nt1_0_reg_reg ( .D(n644), .CK(clk), .Q(nt1_0_reg) );
  DFF_X1 w01_HPC33_reg ( .D(N121), .CK(clk), .Q(w01_HPC33) );
  DFF_X1 temp_hpc3_v_3_order1_HPC33_reg ( .D(N122), .CK(clk), 
        .Q(temp_hpc3_v_3_order1_HPC33) );
  DFF_X1 w02_HPC33_reg ( .D(N123), .CK(clk), .Q(w02_HPC33) );
  DFF_X1 temp_hpc3_v_3_order2_HPC33_reg ( .D(n622), .CK(clk), 
        .Q(temp_hpc3_v_3_order2_HPC33) );
  DFF_X1 w03_HPC33_reg ( .D(N125), .CK(clk), .Q(w03_HPC33) );
  DFF_X1 temp_hpc3_v_3_order3_HPC33_reg ( .D(N126), .CK(clk), 
        .Q(temp_hpc3_v_3_order3_HPC33) );
  DFF_X1 nt1_1_reg_reg ( .D(n645), .CK(clk), .Q(nt1_1_reg) );
  DFF_X1 w10_HPC33_reg ( .D(N127), .CK(clk), .Q(w10_HPC33) );
  DFF_X1 temp_hpc3_v_3_order4_HPC33_reg ( .D(N128), .CK(clk), 
        .Q(temp_hpc3_v_3_order4_HPC33) );
  DFF_X1 w12_HPC33_reg ( .D(N129), .CK(clk), .Q(w12_HPC33) );
  DFF_X1 temp_hpc3_v_3_order5_HPC33_reg ( .D(n625), .CK(clk), 
        .Q(temp_hpc3_v_3_order5_HPC33) );
  DFF_X1 w13_HPC33_reg ( .D(N131), .CK(clk), .Q(w13_HPC33) );
  DFF_X1 temp_hpc3_v_3_order6_HPC33_reg ( .D(N132), .CK(clk), 
        .Q(temp_hpc3_v_3_order6_HPC33) );
  DFF_X1 nt1_2_reg_reg ( .D(n646), .CK(clk), .Q(nt1_2_reg) );
  DFF_X1 w20_HPC33_reg ( .D(N133), .CK(clk), .Q(w20_HPC33) );
  DFF_X1 temp_hpc3_v_3_order7_HPC33_reg ( .D(N134), .CK(clk), 
        .Q(temp_hpc3_v_3_order7_HPC33) );
  DFF_X1 w21_HPC33_reg ( .D(N135), .CK(clk), .Q(w21_HPC33) );
  DFF_X1 temp_hpc3_v_3_order8_HPC33_reg ( .D(n627), .CK(clk), 
        .Q(temp_hpc3_v_3_order8_HPC33) );
  DFF_X1 w23_HPC33_reg ( .D(N137), .CK(clk), .Q(w23_HPC33) );
  DFF_X1 temp_hpc3_v_3_order9_HPC33_reg ( .D(N138), .CK(clk), 
        .Q(temp_hpc3_v_3_order9_HPC33) );
  DFF_X1 nt1_3_reg_reg ( .D(n632), .CK(clk), .Q(nt1_3_reg) );
  DFF_X1 w30_HPC33_reg ( .D(N139), .CK(clk), .Q(w30_HPC33) );
  DFF_X1 temp_hpc3_v_3_order10_HPC33_reg ( .D(N140), .CK(clk), 
        .Q(temp_hpc3_v_3_order10_HPC33) );
  DFF_X1 w31_HPC33_reg ( .D(N141), .CK(clk), .Q(w31_HPC33) );
  DFF_X1 temp_hpc3_v_3_order11_HPC33_reg ( .D(N142), .CK(clk), 
        .Q(temp_hpc3_v_3_order11_HPC33) );
  DFF_X1 w32_HPC33_reg ( .D(N143), .CK(clk), .Q(w32_HPC33) );
  DFF_X1 u00_HPC33_reg_reg ( .D(u00_HPC33), .CK(clk), .Q(u00_HPC33_reg) );
  DFF_X1 u00_HPC26_reg_reg ( .D(u00_HPC26), .CK(clk), .Q(u00_HPC26_reg) );
  DFF_X1 z3049_assgn30490_reg ( .D(o7_val_0), .CK(clk), .Q(z3049_assgn30490)
         );
  DFF_X1 o7_0_reg ( .D(z3049_assgn30490), .CK(clk), .Q(o7_0) );
  DFF_X1 w03_HPC26_reg ( .D(N197), .CK(clk), .Q(w03_HPC26) );
  DFF_X1 v03_HPC26_reg ( .D(N196), .CK(clk), .Q(v03_HPC26) );
  DFF_X1 w02_HPC26_reg ( .D(N195), .CK(clk), .Q(w02_HPC26) );
  DFF_X1 v02_HPC26_reg ( .D(N194), .CK(clk), .Q(v02_HPC26) );
  DFF_X1 w01_HPC26_reg ( .D(N193), .CK(clk), .Q(w01_HPC26) );
  DFF_X1 v01_HPC26_reg ( .D(N192), .CK(clk), .Q(v01_HPC26) );
  DFF_X1 o4_0_reg ( .D(o4_val_0), .CK(clk), .Q(o4_0) );
  DFF_X1 u11_HPC33_reg_reg ( .D(u11_HPC33), .CK(clk), .Q(u11_HPC33_reg) );
  DFF_X1 u11_HPC26_reg_reg ( .D(u11_HPC26), .CK(clk), .Q(u11_HPC26_reg) );
  DFF_X1 z3051_assgn30510_reg ( .D(o7_val_1), .CK(clk), .Q(z3051_assgn30510)
         );
  DFF_X1 o7_1_reg ( .D(z3051_assgn30510), .CK(clk), .Q(o7_1) );
  DFF_X1 w13_HPC26_reg ( .D(N203), .CK(clk), .Q(w13_HPC26) );
  DFF_X1 v13_HPC26_reg ( .D(N202), .CK(clk), .Q(v13_HPC26) );
  DFF_X1 w12_HPC26_reg ( .D(N201), .CK(clk), .Q(w12_HPC26) );
  DFF_X1 v12_HPC26_reg ( .D(N200), .CK(clk), .Q(v12_HPC26) );
  DFF_X1 w10_HPC26_reg ( .D(N199), .CK(clk), .Q(w10_HPC26) );
  DFF_X1 v10_HPC26_reg ( .D(N198), .CK(clk), .Q(v10_HPC26) );
  DFF_X1 o4_1_reg ( .D(o4_val_1), .CK(clk), .Q(o4_1) );
  DFF_X1 u22_HPC33_reg_reg ( .D(u22_HPC33), .CK(clk), .Q(u22_HPC33_reg) );
  DFF_X1 u22_HPC26_reg_reg ( .D(u22_HPC26), .CK(clk), .Q(u22_HPC26_reg) );
  DFF_X1 z3053_assgn30530_reg ( .D(o7_val_2), .CK(clk), .Q(z3053_assgn30530)
         );
  DFF_X1 o7_2_reg ( .D(z3053_assgn30530), .CK(clk), .Q(o7_2) );
  DFF_X1 w23_HPC26_reg ( .D(N209), .CK(clk), .Q(w23_HPC26) );
  DFF_X1 v23_HPC26_reg ( .D(N208), .CK(clk), .Q(v23_HPC26) );
  DFF_X1 w21_HPC26_reg ( .D(N207), .CK(clk), .Q(w21_HPC26) );
  DFF_X1 v21_HPC26_reg ( .D(N206), .CK(clk), .Q(v21_HPC26) );
  DFF_X1 w20_HPC26_reg ( .D(N205), .CK(clk), .Q(w20_HPC26) );
  DFF_X1 v20_HPC26_reg ( .D(N204), .CK(clk), .Q(v20_HPC26) );
  DFF_X1 o4_2_reg ( .D(o4_val_2), .CK(clk), .Q(o4_2) );
  DFF_X1 w23_HPC25_reg ( .D(N185), .CK(clk), .Q(w23_HPC25) );
  DFF_X1 u33_HPC33_reg_reg ( .D(u33_HPC33), .CK(clk), .Q(u33_HPC33_reg) );
  DFF_X1 u33_HPC26_reg_reg ( .D(u33_HPC26), .CK(clk), .Q(u33_HPC26_reg) );
  DFF_X1 u33_HPC25_reg_reg ( .D(u33_HPC25), .CK(clk), .Q(u33_HPC25_reg) );
  DFF_X1 z3055_assgn30550_reg ( .D(o7_val_3), .CK(clk), .Q(z3055_assgn30550)
         );
  DFF_X1 o7_3_reg ( .D(z3055_assgn30550), .CK(clk), .Q(o7_3) );
  DFF_X1 w32_HPC26_reg ( .D(N215), .CK(clk), .Q(w32_HPC26) );
  DFF_X1 v32_HPC26_reg ( .D(N214), .CK(clk), .Q(v32_HPC26) );
  DFF_X1 w31_HPC26_reg ( .D(N213), .CK(clk), .Q(w31_HPC26) );
  DFF_X1 v31_HPC26_reg ( .D(N212), .CK(clk), .Q(v31_HPC26) );
  DFF_X1 w30_HPC26_reg ( .D(N211), .CK(clk), .Q(w30_HPC26) );
  DFF_X1 v30_HPC26_reg ( .D(N210), .CK(clk), .Q(v30_HPC26) );
  DFF_X1 o4_3_reg ( .D(o4_val_3), .CK(clk), .Q(o4_3) );
  DFF_X1 w32_HPC25_reg ( .D(N191), .CK(clk), .Q(w32_HPC25) );
  DFF_X1 v32_HPC25_reg ( .D(N190), .CK(clk), .Q(v32_HPC25) );
  DFF_X1 w31_HPC25_reg ( .D(N189), .CK(clk), .Q(w31_HPC25) );
  DFF_X1 v31_HPC25_reg ( .D(N188), .CK(clk), .Q(v31_HPC25) );
  DFF_X1 w30_HPC25_reg ( .D(N187), .CK(clk), .Q(w30_HPC25) );
  DFF_X1 v30_HPC25_reg ( .D(N186), .CK(clk), .Q(v30_HPC25) );
  DFF_X1 o1_3_reg ( .D(o1_val_3), .CK(clk), .Q(o1_3) );
  DFF_X1 w32_HPC27_reg ( .D(N239), .CK(clk), .Q(w32_HPC27) );
  DFF_X1 w31_HPC27_reg ( .D(N237), .CK(clk), .Q(w31_HPC27) );
  DFF_X1 w30_HPC27_reg ( .D(N235), .CK(clk), .Q(w30_HPC27) );
  DFF_X1 n3_0_reg_reg ( .D(n611), .CK(clk), .Q(n3_0_reg) );
  DFF_X1 v01_HPC24_reg ( .D(N144), .CK(clk), .Q(v01_HPC24) );
  DFF_X1 w01_HPC24_reg ( .D(N145), .CK(clk), .Q(w01_HPC24) );
  DFF_X1 v02_HPC24_reg ( .D(N146), .CK(clk), .Q(v02_HPC24) );
  DFF_X1 w02_HPC24_reg ( .D(N147), .CK(clk), .Q(w02_HPC24) );
  DFF_X1 v03_HPC24_reg ( .D(N148), .CK(clk), .Q(v03_HPC24) );
  DFF_X1 w03_HPC24_reg ( .D(N149), .CK(clk), .Q(w03_HPC24) );
  DFF_X1 v10_HPC24_reg ( .D(N150), .CK(clk), .Q(v10_HPC24) );
  DFF_X1 w10_HPC24_reg ( .D(N151), .CK(clk), .Q(w10_HPC24) );
  DFF_X1 n3_1_reg_reg ( .D(n612), .CK(clk), .Q(n3_1_reg) );
  DFF_X1 v12_HPC24_reg ( .D(N152), .CK(clk), .Q(v12_HPC24) );
  DFF_X1 w12_HPC24_reg ( .D(N153), .CK(clk), .Q(w12_HPC24) );
  DFF_X1 v13_HPC24_reg ( .D(N154), .CK(clk), .Q(v13_HPC24) );
  DFF_X1 w13_HPC24_reg ( .D(N155), .CK(clk), .Q(w13_HPC24) );
  DFF_X1 v20_HPC24_reg ( .D(N156), .CK(clk), .Q(v20_HPC24) );
  DFF_X1 w20_HPC24_reg ( .D(N157), .CK(clk), .Q(w20_HPC24) );
  DFF_X1 v21_HPC24_reg ( .D(N158), .CK(clk), .Q(v21_HPC24) );
  DFF_X1 w21_HPC24_reg ( .D(N159), .CK(clk), .Q(w21_HPC24) );
  DFF_X1 n3_2_reg_reg ( .D(n613), .CK(clk), .Q(n3_2_reg) );
  DFF_X1 v23_HPC24_reg ( .D(N160), .CK(clk), .Q(v23_HPC24) );
  DFF_X1 w23_HPC24_reg ( .D(N161), .CK(clk), .Q(w23_HPC24) );
  DFF_X1 v30_HPC24_reg ( .D(N162), .CK(clk), .Q(v30_HPC24) );
  DFF_X1 w30_HPC24_reg ( .D(N163), .CK(clk), .Q(w30_HPC24) );
  DFF_X1 v31_HPC24_reg ( .D(N164), .CK(clk), .Q(v31_HPC24) );
  DFF_X1 w31_HPC24_reg ( .D(N165), .CK(clk), .Q(w31_HPC24) );
  DFF_X1 v32_HPC24_reg ( .D(N166), .CK(clk), .Q(v32_HPC24) );
  DFF_X1 w32_HPC24_reg ( .D(N167), .CK(clk), .Q(w32_HPC24) );
  DFF_X1 n3_3_reg_reg ( .D(n614), .CK(clk), .Q(n3_3_reg) );
  DFF_X1 u00_HPC24_reg_reg ( .D(u00_HPC24), .CK(clk), .Q(u00_HPC24_reg) );
  DFF_X1 nt4_0_reg_reg ( .D(n638), .CK(clk), .Q(nt4_0_reg) );
  DFF_X1 z3017_assgn30170_reg ( .D(o3_val_0), .CK(clk), .Q(z3017_assgn30170)
         );
  DFF_X1 o3_0_reg ( .D(z3017_assgn30170), .CK(clk), .Q(o3_0) );
  DFF_X1 temp_hpc2_v_3_order9_HPC27_reg ( .D(N45), .CK(clk), 
        .Q(temp_hpc2_v_3_order9_HPC27) );
  DFF_X1 v30_HPC27_reg ( .D(N234), .CK(clk), .Q(v30_HPC27) );
  DFF_X1 temp_hpc2_v_3_order6_HPC27_reg ( .D(N42), .CK(clk), 
        .Q(temp_hpc2_v_3_order6_HPC27) );
  DFF_X1 temp_hpc2_v_3_order3_HPC27_reg ( .D(N39), .CK(clk), 
        .Q(temp_hpc2_v_3_order3_HPC27) );
  DFF_X1 u11_HPC24_reg_reg ( .D(u11_HPC24), .CK(clk), .Q(u11_HPC24_reg) );
  DFF_X1 nt4_1_reg_reg ( .D(n643), .CK(clk), .Q(nt4_1_reg) );
  DFF_X1 z3019_assgn30190_reg ( .D(o3_val_1), .CK(clk), .Q(z3019_assgn30190)
         );
  DFF_X1 o3_1_reg ( .D(z3019_assgn30190), .CK(clk), .Q(o3_1) );
  DFF_X1 temp_hpc2_v_3_order10_HPC27_reg ( .D(N46), .CK(clk), 
        .Q(temp_hpc2_v_3_order10_HPC27) );
  DFF_X1 v31_HPC27_reg ( .D(N236), .CK(clk), .Q(v31_HPC27) );
  DFF_X1 temp_hpc2_v_3_order7_HPC27_reg ( .D(N43), .CK(clk), 
        .Q(temp_hpc2_v_3_order7_HPC27) );
  DFF_X1 temp_hpc2_v_3_order0_HPC27_reg ( .D(N36), .CK(clk), 
        .Q(temp_hpc2_v_3_order0_HPC27) );
  DFF_X1 u22_HPC24_reg_reg ( .D(u22_HPC24), .CK(clk), .Q(u22_HPC24_reg) );
  DFF_X1 nt4_2_reg_reg ( .D(n642), .CK(clk), .Q(nt4_2_reg) );
  DFF_X1 z3021_assgn30210_reg ( .D(o3_val_2), .CK(clk), .Q(z3021_assgn30210)
         );
  DFF_X1 o3_2_reg ( .D(z3021_assgn30210), .CK(clk), .Q(o3_2) );
  DFF_X1 temp_hpc2_v_3_order11_HPC27_reg ( .D(N47), .CK(clk), 
        .Q(temp_hpc2_v_3_order11_HPC27) );
  DFF_X1 v32_HPC27_reg ( .D(N238), .CK(clk), .Q(v32_HPC27) );
  DFF_X1 temp_hpc2_v_3_order4_HPC27_reg ( .D(N40), .CK(clk), 
        .Q(temp_hpc2_v_3_order4_HPC27) );
  DFF_X1 temp_hpc2_v_3_order1_HPC27_reg ( .D(N37), .CK(clk), 
        .Q(temp_hpc2_v_3_order1_HPC27) );
  DFF_X1 u33_HPC24_reg_reg ( .D(u33_HPC24), .CK(clk), .Q(u33_HPC24_reg) );
  DFF_X1 nt4_3_reg_reg ( .D(n634), .CK(clk), .Q(nt4_3_reg) );
  DFF_X1 u33_HPC27_reg_reg ( .D(u33_HPC27), .CK(clk), .Q(u33_HPC27_reg) );
  DFF_X1 o0_3_reg ( .D(o0_val_3), .CK(clk), .Q(o0_3) );
  DFF_X1 z3023_assgn30230_reg ( .D(o3_val_3), .CK(clk), .Q(z3023_assgn30230)
         );
  DFF_X1 o3_3_reg ( .D(z3023_assgn30230), .CK(clk), .Q(o3_3) );
  DFF_X1 temp_hpc2_v_3_order8_HPC27_reg ( .D(n624), .CK(clk), 
        .Q(temp_hpc2_v_3_order8_HPC27) );
  DFF_X1 temp_hpc2_v_3_order5_HPC27_reg ( .D(n623), .CK(clk), 
        .Q(temp_hpc2_v_3_order5_HPC27) );
  DFF_X1 temp_hpc2_v_3_order2_HPC27_reg ( .D(n621), .CK(clk), 
        .Q(temp_hpc2_v_3_order2_HPC27) );
  DFF_X1 nt2_0_reg_reg ( .D(n639), .CK(clk), .Q(nt2_0_reg) );
  DFF_X1 u00_HPC25_reg_reg ( .D(u00_HPC25), .CK(clk), .Q(u00_HPC25_reg) );
  DFF_X1 v01_HPC25_reg ( .D(N168), .CK(clk), .Q(v01_HPC25) );
  DFF_X1 w01_HPC25_reg ( .D(N169), .CK(clk), .Q(w01_HPC25) );
  DFF_X1 v02_HPC25_reg ( .D(N170), .CK(clk), .Q(v02_HPC25) );
  DFF_X1 w02_HPC25_reg ( .D(N171), .CK(clk), .Q(w02_HPC25) );
  DFF_X1 v03_HPC25_reg ( .D(N172), .CK(clk), .Q(v03_HPC25) );
  DFF_X1 w03_HPC25_reg ( .D(N173), .CK(clk), .Q(w03_HPC25) );
  DFF_X1 u00_HPC27_reg_reg ( .D(u00_HPC27), .CK(clk), .Q(u00_HPC27_reg) );
  DFF_X1 o1_0_reg ( .D(o1_val_0), .CK(clk), .Q(o1_0) );
  DFF_X1 w03_HPC27_reg ( .D(N221), .CK(clk), .Q(w03_HPC27) );
  DFF_X1 v03_HPC27_reg ( .D(N220), .CK(clk), .Q(v03_HPC27) );
  DFF_X1 w02_HPC27_reg ( .D(N219), .CK(clk), .Q(w02_HPC27) );
  DFF_X1 v02_HPC27_reg ( .D(N218), .CK(clk), .Q(v02_HPC27) );
  DFF_X1 w01_HPC27_reg ( .D(N217), .CK(clk), .Q(w01_HPC27) );
  DFF_X1 v01_HPC27_reg ( .D(N216), .CK(clk), .Q(v01_HPC27) );
  DFF_X1 o0_0_reg ( .D(o0_val_0), .CK(clk), .Q(o0_0) );
  DFF_X1 v10_HPC25_reg ( .D(N174), .CK(clk), .Q(v10_HPC25) );
  DFF_X1 w10_HPC25_reg ( .D(N175), .CK(clk), .Q(w10_HPC25) );
  DFF_X1 nt2_1_reg_reg ( .D(n641), .CK(clk), .Q(nt2_1_reg) );
  DFF_X1 u11_HPC25_reg_reg ( .D(u11_HPC25), .CK(clk), .Q(u11_HPC25_reg) );
  DFF_X1 v12_HPC25_reg ( .D(N176), .CK(clk), .Q(v12_HPC25) );
  DFF_X1 w12_HPC25_reg ( .D(N177), .CK(clk), .Q(w12_HPC25) );
  DFF_X1 v13_HPC25_reg ( .D(N178), .CK(clk), .Q(v13_HPC25) );
  DFF_X1 w13_HPC25_reg ( .D(N179), .CK(clk), .Q(w13_HPC25) );
  DFF_X1 u11_HPC27_reg_reg ( .D(u11_HPC27), .CK(clk), .Q(u11_HPC27_reg) );
  DFF_X1 o1_1_reg ( .D(o1_val_1), .CK(clk), .Q(o1_1) );
  DFF_X1 w13_HPC27_reg ( .D(N227), .CK(clk), .Q(w13_HPC27) );
  DFF_X1 v13_HPC27_reg ( .D(N226), .CK(clk), .Q(v13_HPC27) );
  DFF_X1 w12_HPC27_reg ( .D(N225), .CK(clk), .Q(w12_HPC27) );
  DFF_X1 v12_HPC27_reg ( .D(N224), .CK(clk), .Q(v12_HPC27) );
  DFF_X1 w10_HPC27_reg ( .D(N223), .CK(clk), .Q(w10_HPC27) );
  DFF_X1 v10_HPC27_reg ( .D(N222), .CK(clk), .Q(v10_HPC27) );
  DFF_X1 o0_1_reg ( .D(o0_val_1), .CK(clk), .Q(o0_1) );
  DFF_X1 v20_HPC25_reg ( .D(N180), .CK(clk), .Q(v20_HPC25) );
  DFF_X1 w20_HPC25_reg ( .D(N181), .CK(clk), .Q(w20_HPC25) );
  DFF_X1 v21_HPC25_reg ( .D(N182), .CK(clk), .Q(v21_HPC25) );
  DFF_X1 w21_HPC25_reg ( .D(N183), .CK(clk), .Q(w21_HPC25) );
  DFF_X1 nt2_2_reg_reg ( .D(n640), .CK(clk), .Q(nt2_2_reg) );
  DFF_X1 u22_HPC25_reg_reg ( .D(u22_HPC25), .CK(clk), .Q(u22_HPC25_reg) );
  DFF_X1 v23_HPC25_reg ( .D(N184), .CK(clk), .Q(v23_HPC25) );
  DFF_X1 u22_HPC27_reg_reg ( .D(u22_HPC27), .CK(clk), .Q(u22_HPC27_reg) );
  DFF_X1 o1_2_reg ( .D(o1_val_2), .CK(clk), .Q(o1_2) );
  DFF_X1 w23_HPC27_reg ( .D(N233), .CK(clk), .Q(w23_HPC27) );
  DFF_X1 v23_HPC27_reg ( .D(N232), .CK(clk), .Q(v23_HPC27) );
  DFF_X1 w21_HPC27_reg ( .D(N231), .CK(clk), .Q(w21_HPC27) );
  DFF_X1 v21_HPC27_reg ( .D(N230), .CK(clk), .Q(v21_HPC27) );
  DFF_X1 w20_HPC27_reg ( .D(N229), .CK(clk), .Q(w20_HPC27) );
  DFF_X1 v20_HPC27_reg ( .D(N228), .CK(clk), .Q(v20_HPC27) );
  DFF_X1 o0_2_reg ( .D(o0_val_2), .CK(clk), .Q(o0_2) );
  XOR2_X1 U1254 ( .A(n688), .B(n687), .Z(n632) );
  XNOR2_X1 U1255 ( .A(n664), .B(n663), .ZN(n645) );
  INV_X1 U1256 ( .A(i1_3), .ZN(n606) );
  INV_X1 U1257 ( .A(i3_0), .ZN(n611) );
  INV_X1 U1258 ( .A(i3_1), .ZN(n612) );
  INV_X1 U1259 ( .A(i3_2), .ZN(n613) );
  INV_X1 U1260 ( .A(i3_3), .ZN(n614) );
  INV_X1 U1261 ( .A(i2_3), .ZN(n610) );
  INV_X1 U1262 ( .A(i2_2), .ZN(n609) );
  INV_X1 U1263 ( .A(i2_1), .ZN(n608) );
  INV_X1 U1264 ( .A(i2_0), .ZN(n607) );
  INV_X1 U1265 ( .A(i7_3), .ZN(n618) );
  XOR2_X1 U1266 ( .A(w03_HPC31), .B(w01_HPC31), .Z(n648) );
  XNOR2_X1 U1267 ( .A(u00_HPC31_reg), .B(w02_HPC31), .ZN(n647) );
  XNOR2_X1 U1268 ( .A(n648), .B(n647), .ZN(n652) );
  XNOR2_X1 U1269 ( .A(temp_hpc3_v_3_order2_HPC31), 
        .B(temp_hpc3_v_3_order0_HPC31), .ZN(n649) );
  XNOR2_X1 U1270 ( .A(n649), .B(temp_hpc3_v_3_order1_HPC31), .ZN(n650) );
  NAND2_X1 U1271 ( .A1(n650), .A2(n2_0_reg), .ZN(n651) );
  XNOR2_X1 U1272 ( .A(n652), .B(n651), .ZN(n644) );
  XOR2_X1 U1273 ( .A(u00_HPC30_reg), .B(w03_HPC30), .Z(n654) );
  XNOR2_X1 U1274 ( .A(w02_HPC30), .B(w01_HPC30), .ZN(n653) );
  XNOR2_X1 U1275 ( .A(n654), .B(n653), .ZN(n658) );
  XNOR2_X1 U1276 ( .A(temp_hpc3_v_3_order0_HPC30), 
        .B(temp_hpc3_v_3_order1_HPC30), .ZN(n655) );
  XNOR2_X1 U1277 ( .A(n655), .B(temp_hpc3_v_3_order2_HPC30), .ZN(n656) );
  NAND2_X1 U1278 ( .A1(n656), .A2(n7_0_reg), .ZN(n657) );
  XNOR2_X2 U1279 ( .A(n658), .B(n657), .ZN(n637) );
  AND2_X1 U1280 ( .A1(n644), .A2(n637), .ZN(u00_HPC33) );
  XOR2_X1 U1281 ( .A(w13_HPC31), .B(w10_HPC31), .Z(n660) );
  XNOR2_X1 U1282 ( .A(u11_HPC31_reg), .B(w12_HPC31), .ZN(n659) );
  XNOR2_X1 U1283 ( .A(n660), .B(n659), .ZN(n664) );
  XNOR2_X1 U1284 ( .A(temp_hpc3_v_3_order5_HPC31), 
        .B(temp_hpc3_v_3_order3_HPC31), .ZN(n661) );
  XNOR2_X1 U1285 ( .A(n661), .B(temp_hpc3_v_3_order4_HPC31), .ZN(n662) );
  NAND2_X1 U1286 ( .A1(n662), .A2(n2_1_reg), .ZN(n663) );
  XOR2_X1 U1287 ( .A(w12_HPC30), .B(w10_HPC30), .Z(n666) );
  XNOR2_X1 U1288 ( .A(u11_HPC30_reg), .B(w13_HPC30), .ZN(n665) );
  XNOR2_X1 U1289 ( .A(n666), .B(n665), .ZN(n670) );
  XNOR2_X1 U1290 ( .A(temp_hpc3_v_3_order3_HPC30), 
        .B(temp_hpc3_v_3_order5_HPC30), .ZN(n667) );
  XNOR2_X1 U1291 ( .A(n667), .B(temp_hpc3_v_3_order4_HPC30), .ZN(n668) );
  NAND2_X1 U1292 ( .A1(n668), .A2(n7_1_reg), .ZN(n669) );
  XNOR2_X2 U1293 ( .A(n670), .B(n669), .ZN(n636) );
  AND2_X1 U1294 ( .A1(n645), .A2(n636), .ZN(u11_HPC33) );
  XOR2_X1 U1295 ( .A(w23_HPC31), .B(w20_HPC31), .Z(n672) );
  XNOR2_X1 U1296 ( .A(u22_HPC31_reg), .B(w21_HPC31), .ZN(n671) );
  XNOR2_X1 U1297 ( .A(n672), .B(n671), .ZN(n676) );
  XNOR2_X1 U1298 ( .A(temp_hpc3_v_3_order7_HPC31), 
        .B(temp_hpc3_v_3_order8_HPC31), .ZN(n673) );
  XNOR2_X1 U1299 ( .A(n673), .B(temp_hpc3_v_3_order6_HPC31), .ZN(n674) );
  NAND2_X1 U1300 ( .A1(n674), .A2(n2_2_reg), .ZN(n675) );
  XNOR2_X1 U1301 ( .A(n676), .B(n675), .ZN(n646) );
  XOR2_X1 U1302 ( .A(w21_HPC30), .B(w20_HPC30), .Z(n678) );
  XNOR2_X1 U1303 ( .A(w23_HPC30), .B(u22_HPC30_reg), .ZN(n677) );
  XNOR2_X1 U1304 ( .A(n678), .B(n677), .ZN(n682) );
  XNOR2_X1 U1305 ( .A(temp_hpc3_v_3_order7_HPC30), 
        .B(temp_hpc3_v_3_order8_HPC30), .ZN(n679) );
  XNOR2_X1 U1306 ( .A(n679), .B(temp_hpc3_v_3_order6_HPC30), .ZN(n680) );
  NAND2_X1 U1307 ( .A1(n680), .A2(n7_2_reg), .ZN(n681) );
  XNOR2_X2 U1308 ( .A(n682), .B(n681), .ZN(n635) );
  AND2_X1 U1309 ( .A1(n646), .A2(n635), .ZN(u22_HPC33) );
  INV_X1 U1310 ( .A(i1_1), .ZN(n604) );
  INV_X1 U1311 ( .A(i1_2), .ZN(n605) );
  INV_X1 U1312 ( .A(i1_0), .ZN(n603) );
  INV_X1 U1313 ( .A(i7_0), .ZN(n615) );
  INV_X1 U1314 ( .A(i7_1), .ZN(n616) );
  INV_X1 U1315 ( .A(i7_2), .ZN(n617) );
  XOR2_X1 U1316 ( .A(w31_HPC31), .B(w30_HPC31), .Z(n684) );
  XNOR2_X1 U1317 ( .A(u33_HPC31_reg), .B(w32_HPC31), .ZN(n683) );
  XNOR2_X1 U1318 ( .A(n684), .B(n683), .ZN(n688) );
  XNOR2_X1 U1319 ( .A(temp_hpc3_v_3_order10_HPC31), 
        .B(temp_hpc3_v_3_order11_HPC31), .ZN(n685) );
  XNOR2_X1 U1320 ( .A(n685), .B(temp_hpc3_v_3_order9_HPC31), .ZN(n686) );
  NAND2_X1 U1321 ( .A1(n686), .A2(n2_3_reg), .ZN(n687) );
  XNOR2_X1 U1322 ( .A(temp_hpc3_v_3_order10_HPC30), 
        .B(temp_hpc3_v_3_order9_HPC30), .ZN(n689) );
  XNOR2_X1 U1323 ( .A(n689), .B(temp_hpc3_v_3_order11_HPC30), .ZN(n690) );
  NAND2_X1 U1324 ( .A1(n7_3_reg), .A2(n690), .ZN(n693) );
  XNOR2_X1 U1325 ( .A(u33_HPC30_reg), .B(w30_HPC30), .ZN(n691) );
  XNOR2_X1 U1326 ( .A(n691), .B(w32_HPC30), .ZN(n692) );
  XNOR2_X1 U1327 ( .A(n693), .B(n692), .ZN(n694) );
  XNOR2_X2 U1328 ( .A(w31_HPC30), .B(n694), .ZN(n631) );
  AND2_X1 U1329 ( .A1(n632), .A2(n631), .ZN(u33_HPC33) );
  AND2_X1 U1330 ( .A1(n645), .A2(temp_hpc2_v_3_order3_HPC24), .ZN(N150) );
  AND2_X1 U1331 ( .A1(n646), .A2(n3_2_reg), .ZN(u22_HPC24) );
  AND2_X1 U1332 ( .A1(n646), .A2(temp_hpc2_v_3_order8_HPC24), .ZN(N160) );
  AND2_X1 U1333 ( .A1(n645), .A2(temp_hpc2_v_3_order5_HPC24), .ZN(N154) );
  AND2_X1 U1334 ( .A1(n644), .A2(temp_hpc2_v_3_order1_HPC24), .ZN(N146) );
  AND2_X1 U1335 ( .A1(n645), .A2(n3_1_reg), .ZN(u11_HPC24) );
  AND2_X1 U1336 ( .A1(n645), .A2(temp_hpc2_v_3_order4_HPC24), .ZN(N152) );
  AND2_X1 U1337 ( .A1(n644), .A2(temp_hpc2_v_3_order0_HPC24), .ZN(N144) );
  AND2_X1 U1338 ( .A1(n644), .A2(temp_hpc2_v_3_order2_HPC24), .ZN(N148) );
  AND2_X1 U1339 ( .A1(n646), .A2(temp_hpc2_v_3_order6_HPC24), .ZN(N156) );
  AND2_X1 U1340 ( .A1(n646), .A2(temp_hpc2_v_3_order7_HPC24), .ZN(N158) );
  AND2_X1 U1341 ( .A1(n644), .A2(n3_0_reg), .ZN(u00_HPC24) );
  AND2_X1 U1342 ( .A1(n3_3_reg), .A2(n632), .ZN(u33_HPC24) );
  AND2_X1 U1343 ( .A1(temp_hpc2_v_3_order9_HPC24), .A2(n632), .ZN(N162) );
  AND2_X1 U1344 ( .A1(temp_hpc2_v_3_order10_HPC24), .A2(n632), .ZN(N164) );
  AND2_X1 U1345 ( .A1(temp_hpc2_v_3_order11_HPC24), .A2(n632), .ZN(N166) );
  XOR2_X1 U1346 ( .A(w23_HPC33), .B(w21_HPC33), .Z(n696) );
  XNOR2_X1 U1347 ( .A(u22_HPC33_reg), .B(w20_HPC33), .ZN(n695) );
  XNOR2_X1 U1348 ( .A(n696), .B(n695), .ZN(n700) );
  XNOR2_X1 U1349 ( .A(temp_hpc3_v_3_order6_HPC33), 
        .B(temp_hpc3_v_3_order7_HPC33), .ZN(n697) );
  XNOR2_X1 U1350 ( .A(n697), .B(temp_hpc3_v_3_order8_HPC33), .ZN(n698) );
  NAND2_X1 U1351 ( .A1(n698), .A2(nt1_2_reg), .ZN(n699) );
  XNOR2_X2 U1352 ( .A(n700), .B(n699), .ZN(n908) );
  AND2_X1 U1353 ( .A1(n908), .A2(temp_hpc2_v_3_order6_HPC25), .ZN(N180) );
  XOR2_X1 U1354 ( .A(w02_HPC33), .B(w01_HPC33), .Z(n702) );
  XNOR2_X1 U1355 ( .A(u00_HPC33_reg), .B(w03_HPC33), .ZN(n701) );
  XNOR2_X1 U1356 ( .A(n702), .B(n701), .ZN(n706) );
  XNOR2_X1 U1357 ( .A(temp_hpc3_v_3_order0_HPC33), 
        .B(temp_hpc3_v_3_order1_HPC33), .ZN(n703) );
  XNOR2_X1 U1358 ( .A(n703), .B(temp_hpc3_v_3_order2_HPC33), .ZN(n704) );
  NAND2_X1 U1359 ( .A1(n704), .A2(nt1_0_reg), .ZN(n705) );
  XNOR2_X2 U1360 ( .A(n706), .B(n705), .ZN(n907) );
  AND2_X1 U1361 ( .A1(n907), .A2(temp_hpc2_v_3_order0_HPC25), .ZN(N168) );
  AND2_X1 U1362 ( .A1(n907), .A2(temp_hpc2_v_3_order2_HPC25), .ZN(N172) );
  AND2_X1 U1363 ( .A1(n908), .A2(temp_hpc2_v_3_order7_HPC25), .ZN(N182) );
  AND2_X1 U1364 ( .A1(n907), .A2(temp_hpc2_v_3_order1_HPC25), .ZN(N170) );
  XOR2_X1 U1365 ( .A(w13_HPC33), .B(w10_HPC33), .Z(n708) );
  XNOR2_X1 U1366 ( .A(u11_HPC33_reg), .B(w12_HPC33), .ZN(n707) );
  XNOR2_X1 U1367 ( .A(n708), .B(n707), .ZN(n712) );
  XNOR2_X1 U1368 ( .A(temp_hpc3_v_3_order5_HPC33), 
        .B(temp_hpc3_v_3_order3_HPC33), .ZN(n709) );
  XNOR2_X1 U1369 ( .A(n709), .B(temp_hpc3_v_3_order4_HPC33), .ZN(n710) );
  NAND2_X1 U1370 ( .A1(n710), .A2(nt1_1_reg), .ZN(n711) );
  XNOR2_X2 U1371 ( .A(n712), .B(n711), .ZN(n903) );
  AND2_X1 U1372 ( .A1(n903), .A2(temp_hpc2_v_3_order4_HPC25), .ZN(N176) );
  AND2_X1 U1373 ( .A1(n903), .A2(nt2_1_reg), .ZN(u11_HPC25) );
  AND2_X1 U1374 ( .A1(n903), .A2(temp_hpc2_v_3_order5_HPC26), .ZN(N202) );
  AND2_X1 U1375 ( .A1(n903), .A2(temp_hpc2_v_3_order3_HPC25), .ZN(N174) );
  AND2_X1 U1376 ( .A1(n907), .A2(nt2_0_reg), .ZN(u00_HPC25) );
  AND2_X1 U1377 ( .A1(n908), .A2(nt2_2_reg), .ZN(u22_HPC25) );
  AND2_X1 U1378 ( .A1(n903), .A2(temp_hpc2_v_3_order5_HPC25), .ZN(N178) );
  AND2_X1 U1379 ( .A1(n908), .A2(temp_hpc2_v_3_order8_HPC25), .ZN(N184) );
  AND2_X1 U1380 ( .A1(n908), .A2(nt0_2_reg), .ZN(u22_HPC26) );
  AND2_X1 U1381 ( .A1(n903), .A2(nt0_1_reg), .ZN(u11_HPC26) );
  AND2_X1 U1382 ( .A1(n903), .A2(temp_hpc2_v_3_order4_HPC26), .ZN(N200) );
  AND2_X1 U1383 ( .A1(n907), .A2(temp_hpc2_v_3_order0_HPC26), .ZN(N192) );
  AND2_X1 U1384 ( .A1(n908), .A2(temp_hpc2_v_3_order7_HPC26), .ZN(N206) );
  AND2_X1 U1385 ( .A1(n907), .A2(temp_hpc2_v_3_order1_HPC26), .ZN(N194) );
  AND2_X1 U1386 ( .A1(n908), .A2(temp_hpc2_v_3_order8_HPC26), .ZN(N208) );
  AND2_X1 U1387 ( .A1(n907), .A2(temp_hpc2_v_3_order2_HPC26), .ZN(N196) );
  AND2_X1 U1388 ( .A1(n907), .A2(nt0_0_reg), .ZN(u00_HPC26) );
  AND2_X1 U1389 ( .A1(n903), .A2(temp_hpc2_v_3_order3_HPC26), .ZN(N198) );
  AND2_X1 U1390 ( .A1(n908), .A2(temp_hpc2_v_3_order6_HPC26), .ZN(N204) );
  XOR2_X1 U1391 ( .A(w31_HPC33), .B(w30_HPC33), .Z(n714) );
  XNOR2_X1 U1392 ( .A(w32_HPC33), .B(u33_HPC33_reg), .ZN(n713) );
  XNOR2_X1 U1393 ( .A(n714), .B(n713), .ZN(n718) );
  XNOR2_X1 U1394 ( .A(temp_hpc3_v_3_order11_HPC33), 
        .B(temp_hpc3_v_3_order9_HPC33), .ZN(n715) );
  XNOR2_X1 U1395 ( .A(n715), .B(temp_hpc3_v_3_order10_HPC33), .ZN(n716) );
  NAND2_X1 U1396 ( .A1(n716), .A2(nt1_3_reg), .ZN(n717) );
  XOR2_X2 U1397 ( .A(n718), .B(n717), .Z(n906) );
  AND2_X1 U1398 ( .A1(nt0_3_reg), .A2(n906), .ZN(u33_HPC26) );
  AND2_X1 U1399 ( .A1(temp_hpc2_v_3_order10_HPC25), .A2(n906), .ZN(N188) );
  AND2_X1 U1400 ( .A1(temp_hpc2_v_3_order9_HPC26), .A2(n906), .ZN(N210) );
  AND2_X1 U1401 ( .A1(temp_hpc2_v_3_order10_HPC26), .A2(n906), .ZN(N212) );
  AND2_X1 U1402 ( .A1(nt2_3_reg), .A2(n906), .ZN(u33_HPC25) );
  AND2_X1 U1403 ( .A1(temp_hpc2_v_3_order11_HPC26), .A2(n906), .ZN(N214) );
  AND2_X1 U1404 ( .A1(temp_hpc2_v_3_order11_HPC25), .A2(n906), .ZN(N190) );
  AND2_X1 U1405 ( .A1(temp_hpc2_v_3_order9_HPC25), .A2(n906), .ZN(N186) );
  XOR2_X1 U1406 ( .A(w20_HPC25), .B(u22_HPC25_reg), .Z(n720) );
  XNOR2_X1 U1407 ( .A(w21_HPC25), .B(v21_HPC25), .ZN(n719) );
  XNOR2_X1 U1408 ( .A(n720), .B(n719), .ZN(n721) );
  XOR2_X1 U1409 ( .A(n721), .B(v23_HPC25), .Z(n723) );
  XNOR2_X1 U1410 ( .A(v20_HPC25), .B(w23_HPC25), .ZN(n722) );
  XNOR2_X1 U1411 ( .A(n723), .B(n722), .ZN(n900) );
  AND2_X1 U1412 ( .A1(n900), .A2(nt4_2_reg), .ZN(u22_HPC27) );
  XOR2_X1 U1413 ( .A(v10_HPC25), .B(v13_HPC25), .Z(n725) );
  XNOR2_X1 U1414 ( .A(v12_HPC25), .B(w12_HPC25), .ZN(n724) );
  XNOR2_X1 U1415 ( .A(n725), .B(n724), .ZN(n726) );
  XOR2_X1 U1416 ( .A(n726), .B(w13_HPC25), .Z(n728) );
  XNOR2_X1 U1417 ( .A(w10_HPC25), .B(u11_HPC25_reg), .ZN(n727) );
  XNOR2_X1 U1418 ( .A(n728), .B(n727), .ZN(n909) );
  AND2_X1 U1419 ( .A1(n909), .A2(temp_hpc2_v_3_order3_HPC27), .ZN(N222) );
  AND2_X1 U1420 ( .A1(n900), .A2(temp_hpc2_v_3_order7_HPC27), .ZN(N230) );
  XOR2_X1 U1421 ( .A(v02_HPC25), .B(w02_HPC25), .Z(n730) );
  XNOR2_X1 U1422 ( .A(v03_HPC25), .B(u00_HPC25_reg), .ZN(n729) );
  XNOR2_X1 U1423 ( .A(n730), .B(n729), .ZN(n731) );
  XOR2_X1 U1424 ( .A(n731), .B(v01_HPC25), .Z(n733) );
  XNOR2_X1 U1425 ( .A(w03_HPC25), .B(w01_HPC25), .ZN(n732) );
  XNOR2_X1 U1426 ( .A(n733), .B(n732), .ZN(n901) );
  AND2_X1 U1427 ( .A1(n901), .A2(temp_hpc2_v_3_order0_HPC27), .ZN(N216) );
  AND2_X1 U1428 ( .A1(n909), .A2(temp_hpc2_v_3_order4_HPC27), .ZN(N224) );
  AND2_X1 U1429 ( .A1(n909), .A2(nt4_1_reg), .ZN(u11_HPC27) );
  AND2_X1 U1430 ( .A1(n909), .A2(temp_hpc2_v_3_order5_HPC27), .ZN(N226) );
  AND2_X1 U1431 ( .A1(n901), .A2(temp_hpc2_v_3_order2_HPC27), .ZN(N220) );
  AND2_X1 U1432 ( .A1(n900), .A2(temp_hpc2_v_3_order6_HPC27), .ZN(N228) );
  AND2_X1 U1433 ( .A1(n901), .A2(temp_hpc2_v_3_order1_HPC27), .ZN(N218) );
  AND2_X1 U1434 ( .A1(n901), .A2(nt4_0_reg), .ZN(u00_HPC27) );
  AND2_X1 U1435 ( .A1(n900), .A2(temp_hpc2_v_3_order8_HPC27), .ZN(N232) );
  XOR2_X1 U1436 ( .A(v31_HPC25), .B(u33_HPC25_reg), .Z(n735) );
  XNOR2_X1 U1437 ( .A(w31_HPC25), .B(w30_HPC25), .ZN(n734) );
  XNOR2_X1 U1438 ( .A(n735), .B(n734), .ZN(n736) );
  XOR2_X1 U1439 ( .A(n736), .B(v32_HPC25), .Z(n738) );
  XNOR2_X1 U1440 ( .A(v30_HPC25), .B(w32_HPC25), .ZN(n737) );
  XOR2_X1 U1441 ( .A(n738), .B(n737), .Z(n905) );
  AND2_X1 U1442 ( .A1(temp_hpc2_v_3_order10_HPC27), .A2(n905), .ZN(N236) );
  AND2_X1 U1443 ( .A1(temp_hpc2_v_3_order9_HPC27), .A2(n905), .ZN(N234) );
  AND2_X1 U1444 ( .A1(nt4_3_reg), .A2(n905), .ZN(u33_HPC27) );
  AND2_X1 U1445 ( .A1(temp_hpc2_v_3_order11_HPC27), .A2(n905), .ZN(N238) );
  XOR2_X1 U1446 ( .A(v31_HPC24), .B(v32_HPC24), .Z(n740) );
  XNOR2_X1 U1447 ( .A(v30_HPC24), .B(w32_HPC24), .ZN(n739) );
  XNOR2_X1 U1448 ( .A(n740), .B(n739), .ZN(n743) );
  XNOR2_X1 U1449 ( .A(u33_HPC24_reg), .B(w31_HPC24), .ZN(n741) );
  XNOR2_X1 U1450 ( .A(n741), .B(w30_HPC24), .ZN(n742) );
  XNOR2_X1 U1451 ( .A(n743), .B(n742), .ZN(n634) );
  XNOR2_X1 U1452 ( .A(temp_hpc3_v_3_order3_HPC32), 
        .B(temp_hpc3_v_3_order5_HPC32), .ZN(n744) );
  XNOR2_X1 U1453 ( .A(n744), .B(temp_hpc3_v_3_order4_HPC32), .ZN(n745) );
  NAND2_X1 U1454 ( .A1(n1_1_reg), .A2(n745), .ZN(n749) );
  XOR2_X1 U1455 ( .A(w13_HPC32), .B(u11_HPC32_reg), .Z(n747) );
  XNOR2_X1 U1456 ( .A(w12_HPC32), .B(w10_HPC32), .ZN(n746) );
  XNOR2_X1 U1457 ( .A(n747), .B(n746), .ZN(n748) );
  XNOR2_X1 U1458 ( .A(n749), .B(n748), .ZN(n641) );
  XNOR2_X1 U1459 ( .A(temp_hpc3_v_3_order8_HPC32), 
        .B(temp_hpc3_v_3_order6_HPC32), .ZN(n750) );
  XNOR2_X1 U1460 ( .A(n750), .B(temp_hpc3_v_3_order7_HPC32), .ZN(n751) );
  NAND2_X1 U1461 ( .A1(n1_2_reg), .A2(n751), .ZN(n755) );
  XOR2_X1 U1462 ( .A(w21_HPC32), .B(w20_HPC32), .Z(n753) );
  XNOR2_X1 U1463 ( .A(w23_HPC32), .B(u22_HPC32_reg), .ZN(n752) );
  XNOR2_X1 U1464 ( .A(n753), .B(n752), .ZN(n754) );
  XNOR2_X1 U1465 ( .A(n755), .B(n754), .ZN(n640) );
  XNOR2_X1 U1466 ( .A(temp_hpc3_v_3_order2_HPC32), 
        .B(temp_hpc3_v_3_order0_HPC32), .ZN(n756) );
  XNOR2_X1 U1467 ( .A(n756), .B(temp_hpc3_v_3_order1_HPC32), .ZN(n757) );
  NAND2_X1 U1468 ( .A1(n1_0_reg), .A2(n757), .ZN(n761) );
  XOR2_X1 U1469 ( .A(w03_HPC32), .B(w01_HPC32), .Z(n759) );
  XNOR2_X1 U1470 ( .A(u00_HPC32_reg), .B(w02_HPC32), .ZN(n758) );
  XNOR2_X1 U1471 ( .A(n759), .B(n758), .ZN(n760) );
  XNOR2_X1 U1472 ( .A(n761), .B(n760), .ZN(n639) );
  XOR2_X1 U1473 ( .A(w31_HPC32), .B(w30_HPC32), .Z(n763) );
  XNOR2_X1 U1474 ( .A(w32_HPC32), .B(u33_HPC32_reg), .ZN(n762) );
  XNOR2_X1 U1475 ( .A(n763), .B(n762), .ZN(n767) );
  XNOR2_X1 U1476 ( .A(temp_hpc3_v_3_order9_HPC32), 
        .B(temp_hpc3_v_3_order10_HPC32), .ZN(n764) );
  XNOR2_X1 U1477 ( .A(n764), .B(temp_hpc3_v_3_order11_HPC32), .ZN(n765) );
  NAND2_X1 U1478 ( .A1(n1_3_reg), .A2(n765), .ZN(n766) );
  XOR2_X1 U1479 ( .A(n767), .B(n766), .Z(n633) );
  XOR2_X1 U1480 ( .A(w23_HPC24), .B(w21_HPC24), .Z(n769) );
  XNOR2_X1 U1481 ( .A(v20_HPC24), .B(u22_HPC24_reg), .ZN(n768) );
  XNOR2_X1 U1482 ( .A(n769), .B(n768), .ZN(n770) );
  XOR2_X1 U1483 ( .A(n770), .B(v21_HPC24), .Z(n772) );
  XNOR2_X1 U1484 ( .A(v23_HPC24), .B(w20_HPC24), .ZN(n771) );
  XNOR2_X1 U1485 ( .A(n772), .B(n771), .ZN(n642) );
  XOR2_X1 U1486 ( .A(v03_HPC24), .B(w03_HPC24), .Z(n774) );
  XNOR2_X1 U1487 ( .A(v01_HPC24), .B(u00_HPC24_reg), .ZN(n773) );
  XNOR2_X1 U1488 ( .A(n774), .B(n773), .ZN(n775) );
  XOR2_X1 U1489 ( .A(n775), .B(w01_HPC24), .Z(n777) );
  XNOR2_X1 U1490 ( .A(v02_HPC24), .B(w02_HPC24), .ZN(n776) );
  XNOR2_X1 U1491 ( .A(n777), .B(n776), .ZN(n638) );
  INV_X1 U1492 ( .A(rand_57), .ZN(n780) );
  NOR2_X1 U1493 ( .A1(n906), .A2(n780), .ZN(N187) );
  INV_X1 U1494 ( .A(rand_59), .ZN(n778) );
  NOR2_X1 U1495 ( .A1(n906), .A2(n778), .ZN(N189) );
  INV_X1 U1496 ( .A(rand_60), .ZN(n783) );
  NOR2_X1 U1497 ( .A1(n906), .A2(n783), .ZN(N191) );
  INV_X1 U1498 ( .A(rand_63), .ZN(n789) );
  NOR2_X1 U1499 ( .A1(n906), .A2(n789), .ZN(N211) );
  INV_X1 U1500 ( .A(rand_65), .ZN(n786) );
  NOR2_X1 U1501 ( .A1(n906), .A2(n786), .ZN(N213) );
  INV_X1 U1502 ( .A(rand_66), .ZN(n784) );
  NOR2_X1 U1503 ( .A1(n906), .A2(n784), .ZN(N215) );
  INV_X1 U1504 ( .A(rand_58), .ZN(n779) );
  NOR2_X1 U1505 ( .A1(n908), .A2(n779), .ZN(N183) );
  INV_X1 U1506 ( .A(rand_56), .ZN(n781) );
  NOR2_X1 U1507 ( .A1(n908), .A2(n781), .ZN(N181) );
  NOR2_X1 U1508 ( .A1(n903), .A2(n778), .ZN(N179) );
  NOR2_X1 U1509 ( .A1(n903), .A2(n779), .ZN(N177) );
  INV_X1 U1510 ( .A(rand_55), .ZN(n782) );
  NOR2_X1 U1511 ( .A1(n903), .A2(n782), .ZN(N175) );
  NOR2_X1 U1512 ( .A1(n907), .A2(n780), .ZN(N173) );
  NOR2_X1 U1513 ( .A1(n907), .A2(n781), .ZN(N171) );
  NOR2_X1 U1514 ( .A1(n907), .A2(n782), .ZN(N169) );
  NOR2_X1 U1515 ( .A1(n908), .A2(n783), .ZN(N185) );
  INV_X1 U1516 ( .A(rand_62), .ZN(n788) );
  NOR2_X1 U1517 ( .A1(n908), .A2(n788), .ZN(N205) );
  INV_X1 U1518 ( .A(rand_64), .ZN(n785) );
  NOR2_X1 U1519 ( .A1(n908), .A2(n785), .ZN(N207) );
  NOR2_X1 U1520 ( .A1(n908), .A2(n784), .ZN(N209) );
  INV_X1 U1521 ( .A(rand_61), .ZN(n787) );
  NOR2_X1 U1522 ( .A1(n903), .A2(n787), .ZN(N199) );
  NOR2_X1 U1523 ( .A1(n903), .A2(n785), .ZN(N201) );
  NOR2_X1 U1524 ( .A1(n903), .A2(n786), .ZN(N203) );
  NOR2_X1 U1525 ( .A1(n907), .A2(n787), .ZN(N193) );
  NOR2_X1 U1526 ( .A1(n907), .A2(n788), .ZN(N195) );
  NOR2_X1 U1527 ( .A1(n907), .A2(n789), .ZN(N197) );
  INV_X1 U1528 ( .A(rand_54), .ZN(n790) );
  NOR2_X1 U1529 ( .A1(n632), .A2(n790), .ZN(N167) );
  INV_X1 U1530 ( .A(rand_53), .ZN(n791) );
  NOR2_X1 U1531 ( .A1(n632), .A2(n791), .ZN(N165) );
  INV_X1 U1532 ( .A(rand_51), .ZN(n793) );
  NOR2_X1 U1533 ( .A1(n632), .A2(n793), .ZN(N163) );
  NOR2_X1 U1534 ( .A1(n646), .A2(n790), .ZN(N161) );
  INV_X1 U1535 ( .A(rand_52), .ZN(n792) );
  NOR2_X1 U1536 ( .A1(n646), .A2(n792), .ZN(N159) );
  INV_X1 U1537 ( .A(rand_50), .ZN(n794) );
  NOR2_X1 U1538 ( .A1(n646), .A2(n794), .ZN(N157) );
  NOR2_X1 U1539 ( .A1(n645), .A2(n791), .ZN(N155) );
  NOR2_X1 U1540 ( .A1(n645), .A2(n792), .ZN(N153) );
  INV_X1 U1541 ( .A(rand_49), .ZN(n795) );
  NOR2_X1 U1542 ( .A1(n645), .A2(n795), .ZN(N151) );
  NOR2_X1 U1543 ( .A1(n644), .A2(n793), .ZN(N149) );
  NOR2_X1 U1544 ( .A1(n644), .A2(n794), .ZN(N147) );
  NOR2_X1 U1545 ( .A1(n644), .A2(n795), .ZN(N145) );
  INV_X1 U1546 ( .A(rand_69), .ZN(n801) );
  NOR2_X1 U1547 ( .A1(n905), .A2(n801), .ZN(N235) );
  INV_X1 U1548 ( .A(rand_71), .ZN(n798) );
  NOR2_X1 U1549 ( .A1(n905), .A2(n798), .ZN(N237) );
  INV_X1 U1550 ( .A(rand_72), .ZN(n796) );
  NOR2_X1 U1551 ( .A1(n905), .A2(n796), .ZN(N239) );
  INV_X1 U1552 ( .A(rand_68), .ZN(n800) );
  NOR2_X1 U1553 ( .A1(n900), .A2(n800), .ZN(N229) );
  INV_X1 U1554 ( .A(rand_70), .ZN(n797) );
  NOR2_X1 U1555 ( .A1(n900), .A2(n797), .ZN(N231) );
  NOR2_X1 U1556 ( .A1(n900), .A2(n796), .ZN(N233) );
  INV_X1 U1557 ( .A(rand_67), .ZN(n799) );
  NOR2_X1 U1558 ( .A1(n909), .A2(n799), .ZN(N223) );
  NOR2_X1 U1559 ( .A1(n909), .A2(n797), .ZN(N225) );
  NOR2_X1 U1560 ( .A1(n909), .A2(n798), .ZN(N227) );
  NOR2_X1 U1561 ( .A1(n901), .A2(n799), .ZN(N217) );
  NOR2_X1 U1562 ( .A1(n901), .A2(n800), .ZN(N219) );
  NOR2_X1 U1563 ( .A1(n901), .A2(n801), .ZN(N221) );
  INV_X1 U1564 ( .A(n632), .ZN(n804) );
  NAND2_X1 U1565 ( .A1(rand_42), .A2(n804), .ZN(n802) );
  XNOR2_X1 U1566 ( .A(rand_48), .B(n802), .ZN(N143) );
  NAND2_X1 U1567 ( .A1(rand_41), .A2(n804), .ZN(n803) );
  XNOR2_X1 U1568 ( .A(n803), .B(rand_47), .ZN(N141) );
  NAND2_X1 U1569 ( .A1(rand_39), .A2(n804), .ZN(n805) );
  XNOR2_X1 U1570 ( .A(n805), .B(rand_45), .ZN(N139) );
  INV_X1 U1571 ( .A(n646), .ZN(n899) );
  NAND2_X1 U1572 ( .A1(rand_42), .A2(n899), .ZN(n806) );
  XNOR2_X1 U1573 ( .A(rand_48), .B(n806), .ZN(N137) );
  NAND2_X1 U1574 ( .A1(n899), .A2(rand_40), .ZN(n807) );
  XNOR2_X1 U1575 ( .A(n807), .B(rand_46), .ZN(N135) );
  NAND2_X1 U1576 ( .A1(n899), .A2(rand_38), .ZN(n808) );
  XNOR2_X1 U1577 ( .A(n808), .B(rand_44), .ZN(N133) );
  INV_X1 U1578 ( .A(n645), .ZN(n902) );
  NAND2_X1 U1579 ( .A1(rand_41), .A2(n902), .ZN(n809) );
  XNOR2_X1 U1580 ( .A(rand_47), .B(n809), .ZN(N131) );
  NAND2_X1 U1581 ( .A1(n902), .A2(rand_40), .ZN(n810) );
  XNOR2_X1 U1582 ( .A(n810), .B(rand_46), .ZN(N129) );
  NAND2_X1 U1583 ( .A1(n902), .A2(rand_37), .ZN(n811) );
  XNOR2_X1 U1584 ( .A(n811), .B(rand_43), .ZN(N127) );
  INV_X1 U1585 ( .A(n644), .ZN(n904) );
  NAND2_X1 U1586 ( .A1(rand_39), .A2(n904), .ZN(n812) );
  XNOR2_X1 U1587 ( .A(rand_45), .B(n812), .ZN(N125) );
  NAND2_X1 U1588 ( .A1(n904), .A2(rand_38), .ZN(n813) );
  XNOR2_X1 U1589 ( .A(n813), .B(rand_44), .ZN(N123) );
  NAND2_X1 U1590 ( .A1(n904), .A2(rand_37), .ZN(n814) );
  XNOR2_X1 U1591 ( .A(n814), .B(rand_43), .ZN(N121) );
  XOR2_X1 U1592 ( .A(v20_HPC27), .B(v21_HPC27), .Z(n816) );
  XNOR2_X1 U1593 ( .A(u22_HPC27_reg), .B(v23_HPC27), .ZN(n815) );
  XNOR2_X1 U1594 ( .A(n816), .B(n815), .ZN(n820) );
  XOR2_X1 U1595 ( .A(w20_HPC27), .B(w23_HPC27), .Z(n818) );
  XNOR2_X1 U1596 ( .A(i2_2), .B(w21_HPC27), .ZN(n817) );
  XNOR2_X1 U1597 ( .A(n818), .B(n817), .ZN(n819) );
  XOR2_X1 U1598 ( .A(n820), .B(n819), .Z(o0_val_2) );
  XOR2_X1 U1599 ( .A(v10_HPC27), .B(v12_HPC27), .Z(n822) );
  XNOR2_X1 U1600 ( .A(u11_HPC27_reg), .B(v13_HPC27), .ZN(n821) );
  XNOR2_X1 U1601 ( .A(n822), .B(n821), .ZN(n826) );
  XOR2_X1 U1602 ( .A(w10_HPC27), .B(w13_HPC27), .Z(n824) );
  XNOR2_X1 U1603 ( .A(i2_1), .B(w12_HPC27), .ZN(n823) );
  XNOR2_X1 U1604 ( .A(n824), .B(n823), .ZN(n825) );
  XOR2_X1 U1605 ( .A(n826), .B(n825), .Z(o0_val_1) );
  XOR2_X1 U1606 ( .A(v01_HPC27), .B(v02_HPC27), .Z(n828) );
  XNOR2_X1 U1607 ( .A(u00_HPC27_reg), .B(v03_HPC27), .ZN(n827) );
  XNOR2_X1 U1608 ( .A(n828), .B(n827), .ZN(n832) );
  XOR2_X1 U1609 ( .A(w01_HPC27), .B(w03_HPC27), .Z(n830) );
  XNOR2_X1 U1610 ( .A(i2_0), .B(w02_HPC27), .ZN(n829) );
  XNOR2_X1 U1611 ( .A(n830), .B(n829), .ZN(n831) );
  XOR2_X1 U1612 ( .A(n832), .B(n831), .Z(o0_val_0) );
  XOR2_X1 U1613 ( .A(v30_HPC27), .B(v31_HPC27), .Z(n834) );
  XNOR2_X1 U1614 ( .A(u33_HPC27_reg), .B(v32_HPC27), .ZN(n833) );
  XNOR2_X1 U1615 ( .A(n834), .B(n833), .ZN(n838) );
  XOR2_X1 U1616 ( .A(w30_HPC27), .B(w32_HPC27), .Z(n836) );
  XNOR2_X1 U1617 ( .A(i2_3), .B(w31_HPC27), .ZN(n835) );
  XNOR2_X1 U1618 ( .A(n836), .B(n835), .ZN(n837) );
  XOR2_X1 U1619 ( .A(n838), .B(n837), .Z(o0_val_3) );
  XOR2_X1 U1620 ( .A(v30_HPC26), .B(v31_HPC26), .Z(n840) );
  XNOR2_X1 U1621 ( .A(u33_HPC26_reg), .B(v32_HPC26), .ZN(n839) );
  XNOR2_X1 U1622 ( .A(n840), .B(n839), .ZN(n844) );
  XOR2_X1 U1623 ( .A(w30_HPC26), .B(w32_HPC26), .Z(n842) );
  XNOR2_X1 U1624 ( .A(i3_3), .B(w31_HPC26), .ZN(n841) );
  XNOR2_X1 U1625 ( .A(n842), .B(n841), .ZN(n843) );
  XOR2_X1 U1626 ( .A(n844), .B(n843), .Z(o4_val_3) );
  XOR2_X1 U1627 ( .A(v20_HPC26), .B(v21_HPC26), .Z(n846) );
  XNOR2_X1 U1628 ( .A(u22_HPC26_reg), .B(v23_HPC26), .ZN(n845) );
  XNOR2_X1 U1629 ( .A(n846), .B(n845), .ZN(n850) );
  XOR2_X1 U1630 ( .A(w20_HPC26), .B(w23_HPC26), .Z(n848) );
  XNOR2_X1 U1631 ( .A(i3_2), .B(w21_HPC26), .ZN(n847) );
  XNOR2_X1 U1632 ( .A(n848), .B(n847), .ZN(n849) );
  XOR2_X1 U1633 ( .A(n850), .B(n849), .Z(o4_val_2) );
  XOR2_X1 U1634 ( .A(v10_HPC26), .B(v12_HPC26), .Z(n852) );
  XNOR2_X1 U1635 ( .A(u11_HPC26_reg), .B(v13_HPC26), .ZN(n851) );
  XNOR2_X1 U1636 ( .A(n852), .B(n851), .ZN(n856) );
  XOR2_X1 U1637 ( .A(w10_HPC26), .B(w13_HPC26), .Z(n854) );
  XNOR2_X1 U1638 ( .A(i3_1), .B(w12_HPC26), .ZN(n853) );
  XNOR2_X1 U1639 ( .A(n854), .B(n853), .ZN(n855) );
  XOR2_X1 U1640 ( .A(n856), .B(n855), .Z(o4_val_1) );
  XOR2_X1 U1641 ( .A(v01_HPC26), .B(v02_HPC26), .Z(n858) );
  XNOR2_X1 U1642 ( .A(u00_HPC26_reg), .B(v03_HPC26), .ZN(n857) );
  XNOR2_X1 U1643 ( .A(n858), .B(n857), .ZN(n862) );
  XOR2_X1 U1644 ( .A(w01_HPC26), .B(w03_HPC26), .Z(n860) );
  XNOR2_X1 U1645 ( .A(i3_0), .B(w02_HPC26), .ZN(n859) );
  XNOR2_X1 U1646 ( .A(n860), .B(n859), .ZN(n861) );
  XOR2_X1 U1647 ( .A(n862), .B(n861), .Z(o4_val_0) );
  XNOR2_X1 U1648 ( .A(rand_53), .B(i3_1), .ZN(N10) );
  XNOR2_X1 U1649 ( .A(rand_53), .B(i3_3), .ZN(N5) );
  XNOR2_X1 U1650 ( .A(rand_52), .B(i3_2), .ZN(N4) );
  XNOR2_X1 U1651 ( .A(rand_52), .B(i3_1), .ZN(N7) );
  XNOR2_X1 U1652 ( .A(rand_51), .B(i3_0), .ZN(N9) );
  XNOR2_X1 U1653 ( .A(rand_54), .B(i3_3), .ZN(N8) );
  XNOR2_X1 U1654 ( .A(rand_50), .B(i3_0), .ZN(N6) );
  XNOR2_X1 U1655 ( .A(rand_49), .B(i3_0), .ZN(N3) );
  XNOR2_X1 U1656 ( .A(rand_51), .B(i3_3), .ZN(N2) );
  XNOR2_X1 U1657 ( .A(rand_50), .B(i3_2), .ZN(N1) );
  XNOR2_X1 U1658 ( .A(rand_49), .B(i3_1), .ZN(N0) );
  XNOR2_X1 U1659 ( .A(rand_54), .B(i3_2), .ZN(N11) );
  XNOR2_X1 U1660 ( .A(i2_2), .B(rand_30), .ZN(N118) );
  XNOR2_X1 U1661 ( .A(i2_1), .B(rand_29), .ZN(N116) );
  XNOR2_X1 U1662 ( .A(i2_0), .B(rand_27), .ZN(N114) );
  XNOR2_X1 U1663 ( .A(i2_3), .B(rand_30), .ZN(N112) );
  XNOR2_X1 U1664 ( .A(i2_1), .B(rand_28), .ZN(N110) );
  XNOR2_X1 U1665 ( .A(i2_0), .B(rand_26), .ZN(N108) );
  XNOR2_X1 U1666 ( .A(i2_3), .B(rand_29), .ZN(N106) );
  XNOR2_X1 U1667 ( .A(i2_2), .B(rand_28), .ZN(N104) );
  XNOR2_X1 U1668 ( .A(i2_0), .B(rand_25), .ZN(N102) );
  XNOR2_X1 U1669 ( .A(i2_3), .B(rand_27), .ZN(N100) );
  XNOR2_X1 U1670 ( .A(i2_2), .B(rand_26), .ZN(N98) );
  XNOR2_X1 U1671 ( .A(i2_1), .B(rand_25), .ZN(N96) );
  XNOR2_X1 U1672 ( .A(i3_2), .B(rand_18), .ZN(N94) );
  XNOR2_X1 U1673 ( .A(i3_1), .B(rand_17), .ZN(N92) );
  XNOR2_X1 U1674 ( .A(i3_0), .B(rand_15), .ZN(N90) );
  XNOR2_X1 U1675 ( .A(i3_3), .B(rand_18), .ZN(N88) );
  XNOR2_X1 U1676 ( .A(i3_1), .B(rand_16), .ZN(N86) );
  XNOR2_X1 U1677 ( .A(i3_0), .B(rand_14), .ZN(N84) );
  XNOR2_X1 U1678 ( .A(i3_3), .B(rand_17), .ZN(N82) );
  XNOR2_X1 U1679 ( .A(i3_2), .B(rand_16), .ZN(N80) );
  XNOR2_X1 U1680 ( .A(i3_0), .B(rand_13), .ZN(N78) );
  XNOR2_X1 U1681 ( .A(i3_3), .B(rand_15), .ZN(N76) );
  XNOR2_X1 U1682 ( .A(i3_2), .B(rand_14), .ZN(N74) );
  XNOR2_X1 U1683 ( .A(i3_1), .B(rand_13), .ZN(N72) );
  NAND2_X1 U1684 ( .A1(rand_30), .A2(i1_3), .ZN(n863) );
  XNOR2_X1 U1685 ( .A(n863), .B(rand_36), .ZN(N119) );
  NAND2_X1 U1686 ( .A1(rand_29), .A2(i1_3), .ZN(n864) );
  XNOR2_X1 U1687 ( .A(n864), .B(rand_35), .ZN(N117) );
  NAND2_X1 U1688 ( .A1(rand_27), .A2(i1_3), .ZN(n865) );
  XNOR2_X1 U1689 ( .A(n865), .B(rand_33), .ZN(N115) );
  NAND2_X1 U1690 ( .A1(rand_30), .A2(i1_2), .ZN(n866) );
  XNOR2_X1 U1691 ( .A(n866), .B(rand_36), .ZN(N113) );
  NAND2_X1 U1692 ( .A1(rand_28), .A2(i1_2), .ZN(n867) );
  XNOR2_X1 U1693 ( .A(n867), .B(rand_34), .ZN(N111) );
  NAND2_X1 U1694 ( .A1(rand_26), .A2(i1_2), .ZN(n868) );
  XNOR2_X1 U1695 ( .A(n868), .B(rand_32), .ZN(N109) );
  NAND2_X1 U1696 ( .A1(rand_29), .A2(i1_1), .ZN(n869) );
  XNOR2_X1 U1697 ( .A(n869), .B(rand_35), .ZN(N107) );
  NAND2_X1 U1698 ( .A1(rand_28), .A2(i1_1), .ZN(n870) );
  XNOR2_X1 U1699 ( .A(n870), .B(rand_34), .ZN(N105) );
  NAND2_X1 U1700 ( .A1(rand_25), .A2(i1_1), .ZN(n871) );
  XNOR2_X1 U1701 ( .A(n871), .B(rand_31), .ZN(N103) );
  NAND2_X1 U1702 ( .A1(rand_27), .A2(i1_0), .ZN(n872) );
  XNOR2_X1 U1703 ( .A(n872), .B(rand_33), .ZN(N101) );
  NAND2_X1 U1704 ( .A1(rand_26), .A2(i1_0), .ZN(n873) );
  XNOR2_X1 U1705 ( .A(n873), .B(rand_32), .ZN(N99) );
  NAND2_X1 U1706 ( .A1(rand_25), .A2(i1_0), .ZN(n874) );
  XNOR2_X1 U1707 ( .A(n874), .B(rand_31), .ZN(N97) );
  NAND2_X1 U1708 ( .A1(rand_18), .A2(i2_3), .ZN(n875) );
  XNOR2_X1 U1709 ( .A(n875), .B(rand_24), .ZN(N95) );
  NAND2_X1 U1710 ( .A1(rand_17), .A2(i2_3), .ZN(n876) );
  XNOR2_X1 U1711 ( .A(n876), .B(rand_23), .ZN(N93) );
  NAND2_X1 U1712 ( .A1(rand_15), .A2(i2_3), .ZN(n877) );
  XNOR2_X1 U1713 ( .A(n877), .B(rand_21), .ZN(N91) );
  NAND2_X1 U1714 ( .A1(rand_18), .A2(i2_2), .ZN(n878) );
  XNOR2_X1 U1715 ( .A(n878), .B(rand_24), .ZN(N89) );
  NAND2_X1 U1716 ( .A1(rand_16), .A2(i2_2), .ZN(n879) );
  XNOR2_X1 U1717 ( .A(n879), .B(rand_22), .ZN(N87) );
  NAND2_X1 U1718 ( .A1(rand_14), .A2(i2_2), .ZN(n880) );
  XNOR2_X1 U1719 ( .A(n880), .B(rand_20), .ZN(N85) );
  NAND2_X1 U1720 ( .A1(rand_17), .A2(i2_1), .ZN(n881) );
  XNOR2_X1 U1721 ( .A(n881), .B(rand_23), .ZN(N83) );
  NAND2_X1 U1722 ( .A1(rand_16), .A2(i2_1), .ZN(n882) );
  XNOR2_X1 U1723 ( .A(n882), .B(rand_22), .ZN(N81) );
  NAND2_X1 U1724 ( .A1(rand_13), .A2(i2_1), .ZN(n883) );
  XNOR2_X1 U1725 ( .A(n883), .B(rand_19), .ZN(N79) );
  NAND2_X1 U1726 ( .A1(rand_15), .A2(i2_0), .ZN(n884) );
  XNOR2_X1 U1727 ( .A(n884), .B(rand_21), .ZN(N77) );
  NAND2_X1 U1728 ( .A1(rand_14), .A2(i2_0), .ZN(n885) );
  XNOR2_X1 U1729 ( .A(n885), .B(rand_20), .ZN(N75) );
  NAND2_X1 U1730 ( .A1(rand_13), .A2(i2_0), .ZN(n886) );
  XNOR2_X1 U1731 ( .A(n886), .B(rand_19), .ZN(N73) );
  NAND2_X1 U1732 ( .A1(rand_6), .A2(i7_3), .ZN(n887) );
  XNOR2_X1 U1733 ( .A(n887), .B(rand_12), .ZN(N71) );
  XNOR2_X1 U1734 ( .A(i6_2), .B(rand_6), .ZN(N70) );
  NAND2_X1 U1735 ( .A1(rand_5), .A2(i7_3), .ZN(n888) );
  XNOR2_X1 U1736 ( .A(n888), .B(rand_11), .ZN(N69) );
  XNOR2_X1 U1737 ( .A(i6_1), .B(rand_5), .ZN(N68) );
  NAND2_X1 U1738 ( .A1(rand_3), .A2(i7_3), .ZN(n889) );
  XNOR2_X1 U1739 ( .A(n889), .B(rand_9), .ZN(N67) );
  XNOR2_X1 U1740 ( .A(i6_0), .B(rand_3), .ZN(N66) );
  NAND2_X1 U1741 ( .A1(rand_6), .A2(i7_2), .ZN(n890) );
  XNOR2_X1 U1742 ( .A(n890), .B(rand_12), .ZN(N65) );
  XNOR2_X1 U1743 ( .A(i6_3), .B(rand_6), .ZN(N64) );
  NAND2_X1 U1744 ( .A1(rand_4), .A2(i7_2), .ZN(n891) );
  XNOR2_X1 U1745 ( .A(n891), .B(rand_10), .ZN(N63) );
  XNOR2_X1 U1746 ( .A(i6_1), .B(rand_4), .ZN(N62) );
  NAND2_X1 U1747 ( .A1(rand_2), .A2(i7_2), .ZN(n892) );
  XNOR2_X1 U1748 ( .A(n892), .B(rand_8), .ZN(N61) );
  XNOR2_X1 U1749 ( .A(i6_0), .B(rand_2), .ZN(N60) );
  NAND2_X1 U1750 ( .A1(rand_5), .A2(i7_1), .ZN(n893) );
  XNOR2_X1 U1751 ( .A(n893), .B(rand_11), .ZN(N59) );
  XNOR2_X1 U1752 ( .A(i6_3), .B(rand_5), .ZN(N58) );
  NAND2_X1 U1753 ( .A1(rand_4), .A2(i7_1), .ZN(n894) );
  XNOR2_X1 U1754 ( .A(n894), .B(rand_10), .ZN(N57) );
  XNOR2_X1 U1755 ( .A(i6_2), .B(rand_4), .ZN(N56) );
  NAND2_X1 U1756 ( .A1(rand_1), .A2(i7_1), .ZN(n895) );
  XNOR2_X1 U1757 ( .A(n895), .B(rand_7), .ZN(N55) );
  XNOR2_X1 U1758 ( .A(i6_0), .B(rand_1), .ZN(N54) );
  NAND2_X1 U1759 ( .A1(rand_3), .A2(i7_0), .ZN(n896) );
  XNOR2_X1 U1760 ( .A(n896), .B(rand_9), .ZN(N53) );
  XNOR2_X1 U1761 ( .A(i6_3), .B(rand_3), .ZN(N52) );
  NAND2_X1 U1762 ( .A1(rand_2), .A2(i7_0), .ZN(n897) );
  XNOR2_X1 U1763 ( .A(n897), .B(rand_8), .ZN(N51) );
  XNOR2_X1 U1764 ( .A(i6_2), .B(rand_2), .ZN(N50) );
  NAND2_X1 U1765 ( .A1(rand_1), .A2(i7_0), .ZN(n898) );
  XNOR2_X1 U1766 ( .A(n898), .B(rand_7), .ZN(N49) );
  XNOR2_X1 U1767 ( .A(i6_1), .B(rand_1), .ZN(N48) );
  NOR2_X1 U1768 ( .A1(i1_3), .A2(i2_3), .ZN(u33_HPC32) );
  NOR2_X1 U1769 ( .A1(i1_2), .A2(i2_2), .ZN(u22_HPC32) );
  NOR2_X1 U1770 ( .A1(i1_1), .A2(i2_1), .ZN(u11_HPC32) );
  NOR2_X1 U1771 ( .A1(i1_0), .A2(i2_0), .ZN(u00_HPC32) );
  NOR2_X1 U1772 ( .A1(i2_3), .A2(i3_3), .ZN(u33_HPC31) );
  NOR2_X1 U1773 ( .A1(i2_2), .A2(i3_2), .ZN(u22_HPC31) );
  NOR2_X1 U1774 ( .A1(i2_1), .A2(i3_1), .ZN(u11_HPC31) );
  NOR2_X1 U1775 ( .A1(i2_0), .A2(i3_0), .ZN(u00_HPC31) );
  NOR2_X1 U1776 ( .A1(i6_3), .A2(i7_3), .ZN(u33_HPC30) );
  NOR2_X1 U1777 ( .A1(i6_2), .A2(i7_2), .ZN(u22_HPC30) );
  NOR2_X1 U1778 ( .A1(i6_1), .A2(i7_1), .ZN(u11_HPC30) );
  NOR2_X1 U1779 ( .A1(i6_0), .A2(i7_0), .ZN(u00_HPC30) );
  XNOR2_X1 U1780 ( .A(i0_2), .B(n899), .ZN(o5_val_2) );
  XNOR2_X1 U1781 ( .A(n900), .B(n617), .ZN(o1_val_2) );
  XNOR2_X1 U1782 ( .A(n901), .B(n615), .ZN(o1_val_0) );
  XNOR2_X1 U1783 ( .A(i0_1), .B(n902), .ZN(o5_val_1) );
  XOR2_X1 U1784 ( .A(i5_1), .B(n903), .Z(o7_val_1) );
  XNOR2_X1 U1785 ( .A(i0_0), .B(n904), .ZN(o5_val_0) );
  XNOR2_X1 U1786 ( .A(n905), .B(i7_3), .ZN(o1_val_3) );
  XNOR2_X1 U1787 ( .A(i0_3), .B(n632), .ZN(o5_val_3) );
  XNOR2_X1 U1788 ( .A(i5_3), .B(n906), .ZN(o7_val_3) );
  XOR2_X1 U1789 ( .A(i5_0), .B(n907), .Z(o7_val_0) );
  XOR2_X1 U1790 ( .A(i5_2), .B(n908), .Z(o7_val_2) );
  XNOR2_X1 U1791 ( .A(n909), .B(n616), .ZN(o1_val_1) );
  XNOR2_X1 U1792 ( .A(i6_3), .B(n633), .ZN(o2_val_3) );
  XOR2_X1 U1793 ( .A(w10_HPC24), .B(u11_HPC24_reg), .Z(n911) );
  XNOR2_X1 U1794 ( .A(w12_HPC24), .B(v12_HPC24), .ZN(n910) );
  XNOR2_X1 U1795 ( .A(n911), .B(n910), .ZN(n912) );
  XOR2_X1 U1796 ( .A(n912), .B(v13_HPC24), .Z(n914) );
  XNOR2_X1 U1797 ( .A(v10_HPC24), .B(w13_HPC24), .ZN(n913) );
  XNOR2_X1 U1798 ( .A(n914), .B(n913), .ZN(n643) );
  XNOR2_X1 U1799 ( .A(n643), .B(n604), .ZN(o3_val_1) );
  XOR2_X1 U1800 ( .A(n643), .B(rand_71), .Z(N46) );
  XOR2_X1 U1801 ( .A(n643), .B(rand_70), .Z(N43) );
  XOR2_X1 U1802 ( .A(n643), .B(rand_67), .Z(N36) );
  XNOR2_X1 U1803 ( .A(n642), .B(n605), .ZN(o3_val_2) );
  XOR2_X1 U1804 ( .A(n642), .B(rand_72), .Z(N47) );
  XOR2_X1 U1805 ( .A(rand_70), .B(n642), .Z(N40) );
  XOR2_X1 U1806 ( .A(n642), .B(rand_68), .Z(N37) );
  XOR2_X1 U1807 ( .A(n641), .B(i6_1), .Z(o2_val_1) );
  XOR2_X1 U1808 ( .A(n641), .B(rand_59), .Z(N22) );
  XOR2_X1 U1809 ( .A(n641), .B(rand_58), .Z(N19) );
  XOR2_X1 U1810 ( .A(n641), .B(rand_55), .Z(N12) );
  XOR2_X1 U1811 ( .A(n640), .B(i6_2), .Z(o2_val_2) );
  XOR2_X1 U1812 ( .A(n640), .B(rand_60), .Z(N23) );
  XOR2_X1 U1813 ( .A(rand_58), .B(n640), .Z(N16) );
  XOR2_X1 U1814 ( .A(n640), .B(rand_56), .Z(N13) );
  XNOR2_X1 U1815 ( .A(i1_3), .B(n634), .ZN(o3_val_3) );
  XOR2_X1 U1816 ( .A(n639), .B(i6_0), .Z(o2_val_0) );
  XOR2_X1 U1817 ( .A(n639), .B(rand_57), .Z(N21) );
  XOR2_X1 U1818 ( .A(rand_56), .B(n639), .Z(N18) );
  XOR2_X1 U1819 ( .A(rand_55), .B(n639), .Z(N15) );
  XNOR2_X1 U1820 ( .A(n638), .B(n603), .ZN(o3_val_0) );
  XOR2_X1 U1821 ( .A(n638), .B(rand_69), .Z(N45) );
  XOR2_X1 U1822 ( .A(rand_68), .B(n638), .Z(N42) );
  XOR2_X1 U1823 ( .A(rand_67), .B(n638), .Z(N39) );
  XOR2_X1 U1824 ( .A(n637), .B(i4_0), .Z(o6_val_0) );
  XOR2_X1 U1825 ( .A(n637), .B(rand_63), .Z(N33) );
  XOR2_X1 U1826 ( .A(n637), .B(rand_62), .Z(N30) );
  XOR2_X1 U1827 ( .A(n637), .B(rand_61), .Z(N27) );
  XOR2_X1 U1828 ( .A(rand_37), .B(n637), .Z(N126) );
  XOR2_X1 U1829 ( .A(rand_38), .B(n637), .Z(N132) );
  XOR2_X1 U1830 ( .A(rand_39), .B(n637), .Z(N138) );
  XOR2_X1 U1831 ( .A(n636), .B(i4_1), .Z(o6_val_1) );
  XOR2_X1 U1832 ( .A(n636), .B(rand_65), .Z(N34) );
  XOR2_X1 U1833 ( .A(n636), .B(rand_64), .Z(N31) );
  XOR2_X1 U1834 ( .A(rand_61), .B(n636), .Z(N24) );
  XOR2_X1 U1835 ( .A(rand_37), .B(n636), .Z(N120) );
  XOR2_X1 U1836 ( .A(rand_40), .B(n636), .Z(N134) );
  XOR2_X1 U1837 ( .A(rand_41), .B(n636), .Z(N140) );
  XOR2_X1 U1838 ( .A(n635), .B(i4_2), .Z(o6_val_2) );
  XOR2_X1 U1839 ( .A(n635), .B(rand_66), .Z(N35) );
  XOR2_X1 U1840 ( .A(rand_64), .B(n635), .Z(N28) );
  XOR2_X1 U1841 ( .A(rand_62), .B(n635), .Z(N25) );
  XOR2_X1 U1842 ( .A(rand_38), .B(n635), .Z(N122) );
  XOR2_X1 U1843 ( .A(rand_40), .B(n635), .Z(N128) );
  XOR2_X1 U1844 ( .A(rand_42), .B(n635), .Z(N142) );
  XNOR2_X1 U1845 ( .A(i4_3), .B(n631), .ZN(o6_val_3) );
  XOR2_X1 U1846 ( .A(rand_63), .B(n631), .Z(n630) );
  XOR2_X1 U1847 ( .A(rand_60), .B(n633), .Z(n629) );
  XOR2_X1 U1848 ( .A(rand_59), .B(n633), .Z(n628) );
  XOR2_X1 U1849 ( .A(rand_42), .B(n631), .Z(n627) );
  XOR2_X1 U1850 ( .A(rand_57), .B(n633), .Z(n626) );
  XOR2_X1 U1851 ( .A(rand_41), .B(n631), .Z(n625) );
  XOR2_X1 U1852 ( .A(rand_72), .B(n634), .Z(n624) );
  XOR2_X1 U1853 ( .A(rand_71), .B(n634), .Z(n623) );
  XOR2_X1 U1854 ( .A(rand_39), .B(n631), .Z(n622) );
  XOR2_X1 U1855 ( .A(rand_69), .B(n634), .Z(n621) );
  XOR2_X1 U1856 ( .A(rand_66), .B(n631), .Z(n620) );
  XOR2_X1 U1857 ( .A(rand_65), .B(n631), .Z(n619) );
endmodule
