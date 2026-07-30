/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Ultra(TM) in wire load mode
// Version   : O-2018.06-SP1
// Date      : Tue Jun 30 11:39:43 2026
/////////////////////////////////////////////////////////////


module sbox ( clk, X0_0, X0_1, X1_0, X1_1, X2_0, X2_1, X3_0, X3_1, X4_0, X4_1, 
        X5_0, X5_1, X6_0, X6_1, X7_0, X7_1, rand_22, rand_30, rand_32, rand_8, 
        rand_35, rand_36, rand_23, rand_44, rand_5, rand_6, rand_28, rand_33, 
        rand_39, rand_4, rand_19, rand_16, rand_27, rand_38, rand_7, rand_14, 
        rand_17, rand_20, rand_10, rand_9, rand_45, rand_25, rand_21, rand_34, 
        rand_46, rand_1, rand_31, rand_41, rand_43, rand_15, rand_24, rand_26, 
        rand_12, rand_2, rand_40, rand_13, rand_18, rand_29, rand_3, rand_37, 
        rand_42, rand_11, Y0_0, Y0_1, Y1_0, Y1_1, Y2_0, Y2_1, Y3_0, Y3_1, Y4_0, 
        Y4_1, Y5_0, Y5_1, Y6_0, Y6_1, Y7_0, Y7_1 );
  input clk, X0_0, X0_1, X1_0, X1_1, X2_0, X2_1, X3_0, X3_1, X4_0, X4_1, X5_0,
         X5_1, X6_0, X6_1, X7_0, X7_1, rand_22, rand_30, rand_32, rand_8,
         rand_35, rand_36, rand_23, rand_44, rand_5, rand_6, rand_28, rand_33,
         rand_39, rand_4, rand_19, rand_16, rand_27, rand_38, rand_7, rand_14,
         rand_17, rand_20, rand_10, rand_9, rand_45, rand_25, rand_21, rand_34,
         rand_46, rand_1, rand_31, rand_41, rand_43, rand_15, rand_24, rand_26,
         rand_12, rand_2, rand_40, rand_13, rand_18, rand_29, rand_3, rand_37,
         rand_42, rand_11;
  output Y0_0, Y0_1, Y1_0, Y1_1, Y2_0, Y2_1, Y3_0, Y3_1, Y4_0, Y4_1, Y5_0,
         Y5_1, Y6_0, Y6_1, Y7_0, Y7_1;
  wire   T14_0, T14_1, T24_0, T24_1, T25_0, T25_1, T26_0, T26_1, u00_HPC30,
         temp_hpc3_v_1_order0_HPC30, T13_0_reg, w01_HPC30,
         temp_hpc3_v_1_order1_HPC30, T13_1_reg, w10_HPC30, u11_HPC30,
         u00_HPC30_reg, u11_HPC30_reg,
         xor_step2_hpc3o_first_half_1_order0_HPC3o1,
         xor_br_hpc3o_v_1_order0_HPC3o1, T23_0_reg,
         temp_hpc3o_v_1_order0_HPC3o1, w01_HPC3o1,
         xor_step2_hpc3o_first_half_1_order1_HPC3o1,
         xor_br_hpc3o_v_1_order1_HPC3o1, T23_1_reg,
         temp_hpc3o_v_1_order1_HPC3o1, w10_HPC3o1, T14_0_reg, T14_1_reg,
         xor_step2_hpc3o_first_half_1_order0_HPC3o2,
         xor_br_hpc3o_v_1_order0_HPC3o2, T19_0_reg,
         temp_hpc3o_v_1_order0_HPC3o2, w01_HPC3o2,
         xor_step2_hpc3o_first_half_1_order1_HPC3o2,
         xor_br_hpc3o_v_1_order1_HPC3o2, T19_1_reg,
         temp_hpc3o_v_1_order1_HPC3o2, w10_HPC3o2, u00_HPC33,
         temp_hpc3_v_1_order0_HPC33, T3_0_reg, w01_HPC33,
         temp_hpc3_v_1_order1_HPC33, T3_1_reg, w10_HPC33, u11_HPC33,
         u00_HPC33_reg, u11_HPC33_reg,
         xor_step2_hpc3o_first_half_1_order0_HPC3o4,
         xor_br_hpc3o_v_1_order0_HPC3o4, T22_0_reg,
         temp_hpc3o_v_1_order0_HPC3o4, w01_HPC3o4,
         xor_step2_hpc3o_first_half_1_order1_HPC3o4,
         xor_br_hpc3o_v_1_order1_HPC3o4, T22_1_reg,
         temp_hpc3o_v_1_order1_HPC3o4, w10_HPC3o4, T26_0_reg, T26_1_reg,
         xor_step2_hpc3o_first_half_1_order0_HPC3o5,
         xor_br_hpc3o_v_1_order0_HPC3o5, T20_0_reg,
         temp_hpc3o_v_1_order0_HPC3o5, w01_HPC3o5,
         xor_step2_hpc3o_first_half_1_order1_HPC3o5,
         xor_br_hpc3o_v_1_order1_HPC3o5, T20_1_reg,
         temp_hpc3o_v_1_order1_HPC3o5, w10_HPC3o5, u00_HPC36,
         temp_hpc3_v_1_order0_HPC36, T1_0_reg, w01_HPC36,
         temp_hpc3_v_1_order1_HPC36, T1_1_reg, w10_HPC36, u11_HPC36,
         u00_HPC36_reg, u11_HPC36_reg,
         xor_step2_hpc3o_first_half_1_order0_HPC3o7,
         xor_br_hpc3o_v_1_order0_HPC3o7, T4_0_reg,
         temp_hpc3o_v_1_order0_HPC3o7, w01_HPC3o7,
         xor_step2_hpc3o_first_half_1_order1_HPC3o7,
         xor_br_hpc3o_v_1_order1_HPC3o7, T4_1_reg,
         temp_hpc3o_v_1_order1_HPC3o7, w10_HPC3o7,
         xor_step2_hpc3o_first_half_1_order0_HPC3o8,
         xor_br_hpc3o_v_1_order0_HPC3o8, T2_0_reg,
         temp_hpc3o_v_1_order0_HPC3o8, w01_HPC3o8,
         xor_step2_hpc3o_first_half_1_order1_HPC3o8,
         xor_br_hpc3o_v_1_order1_HPC3o8, T2_1_reg,
         temp_hpc3o_v_1_order1_HPC3o8, w10_HPC3o8, T24_0_reg, T24_1_reg,
         T25_0_reg, T25_1_reg, u00_HPC39, temp_hpc3_v_1_order0_HPC39,
         M22_0_reg, w01_HPC39, temp_hpc3_v_1_order1_HPC39, M22_1_reg,
         w10_HPC39, u11_HPC39, u00_HPC39_reg, u11_HPC39_reg, M21_0_reg,
         M21_1_reg, M27_0_reg, xor_br_hpc2o_v_1_order0_HPC2o10,
         temp_hpc2o_v_1_order0_HPC2o10, and_ta_hpc2o_v_1_order0_HPC2o10,
         v01_HPC2o10, w01_HPC2o10, M27_1_reg, xor_br_hpc2o_v_1_order1_HPC2o10,
         temp_hpc2o_v_1_order1_HPC2o10, and_ta_hpc2o_v_1_order1_HPC2o10,
         v10_HPC2o10, w10_HPC2o10, M24_0_reg, xor_br_hpc2o_v_1_order0_HPC2o11,
         temp_hpc2o_v_1_order0_HPC2o11, and_ta_hpc2o_v_1_order0_HPC2o11,
         v01_HPC2o11, w01_HPC2o11, M24_1_reg, xor_br_hpc2o_v_1_order1_HPC2o11,
         temp_hpc2o_v_1_order1_HPC2o11, and_ta_hpc2o_v_1_order1_HPC2o11,
         v10_HPC2o11, w10_HPC2o11, u00_HPC312, temp_hpc3_v_1_order0_HPC312,
         M20_0_reg, w01_HPC312, temp_hpc3_v_1_order1_HPC312, M20_1_reg,
         w10_HPC312, u11_HPC312, u00_HPC312_reg, u11_HPC312_reg,
         xor_br_hpc2osw_v_1_order0_HPC2o_swapped13,
         temp_hpc2osw_v_1_order0_HPC2o_swapped13,
         and_ta_hpc2osw_v_1_order0_HPC2o_swapped13, v01_HPC2o_swapped13,
         w01_HPC2o_swapped13, xor_br_hpc2osw_v_1_order1_HPC2o_swapped13,
         temp_hpc2osw_v_1_order1_HPC2o_swapped13,
         and_ta_hpc2osw_v_1_order1_HPC2o_swapped13, v10_HPC2o_swapped13,
         w10_HPC2o_swapped13, M33_0, M33_1, u00_HPC314,
         temp_hpc3_v_1_order0_HPC314, w01_HPC314, temp_hpc3_v_1_order1_HPC314,
         w10_HPC314, u11_HPC314, u00_HPC314_reg, u11_HPC314_reg,
         xor_br_hpc2osw_v_1_order0_HPC2o_swapped15,
         temp_hpc2osw_v_1_order0_HPC2o_swapped15,
         and_ta_hpc2osw_v_1_order0_HPC2o_swapped15, v01_HPC2o_swapped15,
         w01_HPC2o_swapped15, xor_br_hpc2osw_v_1_order1_HPC2o_swapped15,
         temp_hpc2osw_v_1_order1_HPC2o_swapped15,
         and_ta_hpc2osw_v_1_order1_HPC2o_swapped15, v10_HPC2o_swapped15,
         w10_HPC2o_swapped15, M36_0, M36_1, z882_assgn882, z884_assgn884,
         M33_0_reg, M33_1_reg, z890_assgn890, z892_assgn892, M36_0_reg,
         M36_1_reg, z917_assgn917, u00_HPC216, z2659_assgn2659, z922_assgn922,
         z1_assgn1, v01_HPC216, w01_HPC216, z2673_assgn2673, z934_assgn934,
         z3_assgn3, v10_HPC216, w10_HPC216, z943_assgn943, u11_HPC216,
         u00_HPC216_reg, u11_HPC216_reg, z949_assgn949,
         xor_br_hpc2o_v_1_order0_HPC2o17, z2711_assgn2711, z966_assgn966,
         and_ta_hpc2o_v_1_order0_HPC2o17, v01_HPC2o17, w01_HPC2o17,
         z971_assgn971, xor_br_hpc2o_v_1_order1_HPC2o17, z2737_assgn2737,
         z988_assgn988, and_ta_hpc2o_v_1_order1_HPC2o17, v10_HPC2o17,
         w10_HPC2o17, u00_HPC218, z2753_assgn2753, z1002_assgn1002, z5_assgn5,
         v01_HPC218, w01_HPC218, z2767_assgn2767, z1014_assgn1014, z7_assgn7,
         v10_HPC218, w10_HPC218, u11_HPC218, u00_HPC218_reg, u11_HPC218_reg,
         z1029_assgn1029, xor_br_hpc2o_v_1_order0_HPC2o19, z2803_assgn2803,
         z1046_assgn1046, and_ta_hpc2o_v_1_order0_HPC2o19, v01_HPC2o19,
         w01_HPC2o19, z1051_assgn1051, xor_br_hpc2o_v_1_order1_HPC2o19,
         z2829_assgn2829, z1068_assgn1068, and_ta_hpc2o_v_1_order1_HPC2o19,
         v10_HPC2o19, w10_HPC2o19, z1077_assgn1077, u00_HPC220,
         z2847_assgn2847, z1082_assgn1082, z9_assgn9, v01_HPC220, w01_HPC220,
         z2861_assgn2861, z1094_assgn1094, z11_assgn11, v10_HPC220, w10_HPC220,
         z1103_assgn1103, u11_HPC220, u00_HPC220_reg, u11_HPC220_reg,
         z1109_assgn1109, u00_HPC221, z2887_assgn2887, z1114_assgn1114,
         z13_assgn13, v01_HPC221, w01_HPC221, z2901_assgn2901, z1126_assgn1126,
         z15_assgn15, v10_HPC221, w10_HPC221, z1135_assgn1135, u11_HPC221,
         u00_HPC221_reg, u11_HPC221_reg, z1141_assgn1141, u00_HPC222,
         z2927_assgn2927, z1146_assgn1146, z17_assgn17, v01_HPC222, w01_HPC222,
         z2941_assgn2941, z1158_assgn1158, z19_assgn19, v10_HPC222, w10_HPC222,
         z1167_assgn1167, u11_HPC222, u00_HPC222_reg, u11_HPC222_reg,
         z1173_assgn1173, u00_HPC223, z2967_assgn2967, z1178_assgn1178,
         z21_assgn21, v01_HPC223, w01_HPC223, z2981_assgn2981, z1190_assgn1190,
         z23_assgn23, v10_HPC223, w10_HPC223, z1199_assgn1199, u11_HPC223,
         u00_HPC223_reg, u11_HPC223_reg, z1205_assgn1205,
         xor_br_hpc2o_v_1_order0_HPC2o24, z3019_assgn3019, z1222_assgn1222,
         and_ta_hpc2o_v_1_order0_HPC2o24, v01_HPC2o24, w01_HPC2o24,
         z1227_assgn1227, xor_br_hpc2o_v_1_order1_HPC2o24, z3045_assgn3045,
         z1244_assgn1244, and_ta_hpc2o_v_1_order1_HPC2o24, v10_HPC2o24,
         w10_HPC2o24, z1253_assgn1253, u00_HPC225, z3063_assgn3063,
         z1258_assgn1258, z25_assgn25, v01_HPC225, w01_HPC225, z3077_assgn3077,
         z1270_assgn1270, z27_assgn27, v10_HPC225, w10_HPC225, z1279_assgn1279,
         u11_HPC225, u00_HPC225_reg, u11_HPC225_reg, z1285_assgn1285,
         u00_HPC226, z3103_assgn3103, z1290_assgn1290, z29_assgn29, v01_HPC226,
         w01_HPC226, z3117_assgn3117, z1302_assgn1302, z31_assgn31, v10_HPC226,
         w10_HPC226, z1311_assgn1311, u11_HPC226, u00_HPC226_reg,
         u11_HPC226_reg, z1317_assgn1317, xor_br_hpc2o_v_1_order0_HPC2o27,
         z3155_assgn3155, z1334_assgn1334, and_ta_hpc2o_v_1_order0_HPC2o27,
         v01_HPC2o27, w01_HPC2o27, z1339_assgn1339,
         xor_br_hpc2o_v_1_order1_HPC2o27, z3181_assgn3181, z1356_assgn1356,
         and_ta_hpc2o_v_1_order1_HPC2o27, v10_HPC2o27, w10_HPC2o27,
         z1365_assgn1365, u00_HPC228, z3199_assgn3199, z1370_assgn1370,
         z33_assgn33, v01_HPC228, w01_HPC228, z3213_assgn3213, z1382_assgn1382,
         z35_assgn35, v10_HPC228, w10_HPC228, z1391_assgn1391, u11_HPC228,
         u00_HPC228_reg, u11_HPC228_reg, z1397_assgn1397,
         xor_br_hpc2o_v_1_order0_HPC2o29, z3251_assgn3251, z1414_assgn1414,
         and_ta_hpc2o_v_1_order0_HPC2o29, v01_HPC2o29, w01_HPC2o29,
         z1419_assgn1419, xor_br_hpc2o_v_1_order1_HPC2o29, z3277_assgn3277,
         z1436_assgn1436, and_ta_hpc2o_v_1_order1_HPC2o29, v10_HPC2o29,
         w10_HPC2o29, z1445_assgn1445, xor_br_hpc2o_v_1_order0_HPC2o30,
         z3307_assgn3307, z1462_assgn1462, and_ta_hpc2o_v_1_order0_HPC2o30,
         v01_HPC2o30, w01_HPC2o30, z1467_assgn1467,
         xor_br_hpc2o_v_1_order1_HPC2o30, z3333_assgn3333, z1484_assgn1484,
         and_ta_hpc2o_v_1_order1_HPC2o30, v10_HPC2o30, w10_HPC2o30,
         z1493_assgn1493, u00_HPC231, z3351_assgn3351, z1498_assgn1498,
         z37_assgn37, v01_HPC231, w01_HPC231, z3365_assgn3365, z1510_assgn1510,
         z39_assgn39, v10_HPC231, w10_HPC231, z1519_assgn1519, u11_HPC231,
         u00_HPC231_reg, u11_HPC231_reg, z1525_assgn1525, u00_HPC232,
         z3391_assgn3391, z1530_assgn1530, z41_assgn41, v01_HPC232, w01_HPC232,
         z3405_assgn3405, z1542_assgn1542, z43_assgn43, v10_HPC232, w10_HPC232,
         z1551_assgn1551, u11_HPC232, u00_HPC232_reg, u11_HPC232_reg,
         z1557_assgn1557, xor_br_hpc2o_v_1_order0_HPC2o33, z3443_assgn3443,
         z1574_assgn1574, and_ta_hpc2o_v_1_order0_HPC2o33, v01_HPC2o33,
         w01_HPC2o33, z1579_assgn1579, xor_br_hpc2o_v_1_order1_HPC2o33,
         z3469_assgn3469, z1596_assgn1596, and_ta_hpc2o_v_1_order1_HPC2o33,
         v10_HPC2o33, w10_HPC2o33, temp1_0, temp2_0, temp3_0, temp4_0,
         z2653_assgn26530, z2685_assgn26850, z2693_assgn26930,
         z2719_assgn27190, z2785_assgn27850, z2811_assgn28110,
         z2841_assgn28410, z2873_assgn28730, z2881_assgn28810,
         z2913_assgn29130, z2921_assgn29210, z2953_assgn29530,
         z2961_assgn29610, z2993_assgn29930, z3001_assgn30010,
         z3027_assgn30270, N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, N10, N11,
         N12, N13, N14, N15, N16, N17, N18, N19, N20, N21, N22, N23,
         z2621_assgn26210, z2625_assgn26250, z2653_assgn26531, N24,
         z2659_assgn26590, N25, N26, z2673_assgn26730, N27, z2685_assgn26851,
         z2693_assgn26931, z2711_assgn27110, z2719_assgn27191,
         z2737_assgn27370, N28, z2753_assgn27530, N29, N30, z2767_assgn27670,
         N31, z2785_assgn27851, z2803_assgn28030, z2811_assgn28111,
         z2829_assgn28290, z2841_assgn28411, N32, z2847_assgn28470, N33, N34,
         z2861_assgn28610, N35, z2873_assgn28731, z2881_assgn28811, N36,
         z2887_assgn28870, N37, N38, z2901_assgn29010, N39, z2913_assgn29131,
         z2921_assgn29211, N40, z2927_assgn29270, N41, N42, z2941_assgn29410,
         N43, z2953_assgn29531, z2961_assgn29611, N44, z2967_assgn29670, N45,
         N46, z2981_assgn29810, N47, z2993_assgn29931, z3001_assgn30011,
         z3019_assgn30190, z3027_assgn30271, z3045_assgn30450,
         z3057_assgn30571, N48, z3063_assgn30630, N49, N50, z3077_assgn30770,
         N51, z3089_assgn30891, z3097_assgn30971, N52, z3103_assgn31030, N53,
         N54, z3117_assgn31170, N55, z3129_assgn31291, z3137_assgn31371,
         z3155_assgn31550, z3163_assgn31631, z3181_assgn31810,
         z3193_assgn31931, N56, z3199_assgn31990, N57, N58, z3213_assgn32130,
         N59, z3225_assgn32251, z3233_assgn32331, z3251_assgn32510,
         z3259_assgn32591, z3277_assgn32770, z3289_assgn32891,
         z3307_assgn33070, z3315_assgn33151, z3333_assgn33330,
         z3345_assgn33451, N60, z3351_assgn33510, N61, N62, z3365_assgn33650,
         N63, z3377_assgn33771, z3385_assgn33851, N64, z3391_assgn33910, N65,
         N66, z3405_assgn34050, N67, z3417_assgn34171, z3425_assgn34251,
         z3443_assgn34430, z3451_assgn34511, z3469_assgn34690, N68, N69, N72,
         N73, N74, N75, N76, N77, n825, n826, n827, n828, n829, n830, n831,
         n832, n833, n834, n835, n836, n837, n838, n839, n840, n841, n842,
         n843, n844, n845, n846, n847, n848, n849, n850, n851, n852, n853,
         n854, n855, n856, n857, n858, n859, n860, n861, n862, n863, n864,
         n865, n866, n867, n868, n869, n870, n871, n872, n873, n874, n875,
         n876, n877, n878, n879, n880, n881, n882, n883, n884, n885, n886,
         n887, n888, n889, n890, n891, n892, n893, n894, n895, n896, n897,
         n898, n899, n900, n901, n902, n903, n904, n905, n906, n907, n908,
         n909, n910, n911, n912, n913, n914, n915, n916, n917, n918, n919,
         n920, n921, n922, n923, n924, n925, n926, n927, n928, n929, n930,
         n931, n932, n933, n934, n935, n936, n937, n938, n939, n940, n941,
         n942, n943, n944, n945, n946, n947, n948, n949, n950, n951, n952,
         n953, n954, n955, n956, n957, n958, n959, n960, n961, n962, n963,
         n964, n965, n966, n967, n968, n969, n970, n971, n972, n973, n974,
         n975, n976, n977, n978, n979, n980, n981, n982, n983, n984, n985,
         n986, n987, n988, n989, n990, n991, n992, n993, n994, n995, n996,
         n997, n998, n999, n1000, n1001, n1002, n1003, n1004, n1005, n1006,
         n1007, n1008, n1009, n1010, n1011, n1012, n1013, n1014, n1015, n1016,
         n1017, n1018, n1019, n1020, n1021, n1022, n1023, n1024, n1025, n1026,
         n1027, n1028, n1029, n1030, n1031, n1032, n1033, n1034, n1035, n1036,
         n1037, n1038, n1039, n1040, n1041, n1042, n1043, n1044, n1045, n1046,
         n1047, n1048, n1049, n1050, n1051, n1052, n1053, n1054, n1055, n1056,
         n1057, n1058, n1059, n1060, n1061, n1062, n1063, n1064, n1065, n1066,
         n1067, n1068, n1069, n1070, n1071, n1072, n1073, n1074, n1075, n1076,
         n1077, n1078, n1079, n1080, n1081, n1082, n1083, n1084, n1085, n1086,
         n1087, n1088, n1089, n1090, n1091, n1092, n1093, n1094, n1095, n1096,
         n1097, n1098, n1099, n1100, n1101, n1102, n1103, n1104, n1105, n1106,
         n1107, n1108, n1109, n1110, n1111, n1112, n1113, n1114, n1115, n1116,
         n1117, n1118, n1119, n1120, n1121, n1122, n1123, n1124, n1125, n1126,
         n1127, n1128, n1129, n1130, n1131, n1132, n1133, n1134, n1135, n1136,
         n1137, n1138, n1139, n1140, n1141, n1142, n1143, n1144, n1145, n1146,
         n1147, n1148, n1149, n1150, n1151, n1152, n1153, n1154, n1155, n1156,
         n1157, n1158, n1159, n1160, n1161, n1162, n1163, n1164, n1165, n1166,
         n1167, n1168, n1169, n1170, n1171, n1172, n1173, n1174, n1175, n1176,
         n1177, n1178, n1179, n1180, n1181, n1182, n1183, n1184, n1185, n1186,
         n1187, n1188, n1189, n1190, n1191, n1192, n1193, n1194, n1195, n1196,
         n1197, n1198, n1199, n1200, n1201, n1202, n1203, n1204, n1205, n1206,
         n1207, n1208, n1209, n1210, n1211, n1212, n1213, n1214, n1215, n1216,
         n1217, n1218, n1219, n1220, n1221, n1222, n1223, n1224, n1225, n1226,
         n1227, n1228, n1229, n1230, n1231, n1232, n1233, n1234, n1235, n1236,
         n1237, n1238, n1239, n1240, n1241, n1242, n1243, n1244, n1245, n1246,
         n1247, n1248, n1249, n1250, n1251, n1252, n1253, n1254, n1255, n1256,
         n1257, n1258, n1259, n1260, n1261, n1262, n1263, n1264, n1265, n1266,
         n1267, n1268, n1269, n1270, n1271, n1272, n1273, n1274, n1275, n1276,
         n1277, n1278, n1279, n1280, n1281, n1282, n1283, n1284, n1285, n1286,
         n1287, n1288, n1289, n1290, n1291, n1292, n1293, n1294;

  DFF_X1 z2785_assgn27850_reg ( .D(n864), .CK(clk), .Q(z2785_assgn27850) );
  DFF_X1 z2785_assgn27851_reg ( .D(z2785_assgn27850), .CK(clk), 
        .Q(z2785_assgn27851) );
  DFF_X1 z2873_assgn28730_reg ( .D(n856), .CK(clk), .Q(z2873_assgn28730) );
  DFF_X1 z2873_assgn28731_reg ( .D(z2873_assgn28730), .CK(clk), 
        .Q(z2873_assgn28731) );
  DFF_X1 z2913_assgn29130_reg ( .D(n869), .CK(clk), .Q(z2913_assgn29130) );
  DFF_X1 z2913_assgn29131_reg ( .D(z2913_assgn29130), .CK(clk), 
        .Q(z2913_assgn29131) );
  DFF_X1 z2841_assgn28410_reg ( .D(n855), .CK(clk), .Q(z2841_assgn28410) );
  DFF_X1 z2653_assgn26530_reg ( .D(n857), .CK(clk), .Q(z2653_assgn26530) );
  DFF_X1 z2653_assgn26531_reg ( .D(z2653_assgn26530), .CK(clk), 
        .Q(z2653_assgn26531) );
  DFF_X1 z2841_assgn28411_reg ( .D(z2841_assgn28410), .CK(clk), 
        .Q(z2841_assgn28411) );
  DFF_X1 z2953_assgn29530_reg ( .D(n859), .CK(clk), .Q(z2953_assgn29530) );
  DFF_X1 z2953_assgn29531_reg ( .D(z2953_assgn29530), .CK(clk), 
        .Q(z2953_assgn29531) );
  DFF_X1 z2685_assgn26850_reg ( .D(n858), .CK(clk), .Q(z2685_assgn26850) );
  DFF_X1 z2685_assgn26851_reg ( .D(z2685_assgn26850), .CK(clk), 
        .Q(z2685_assgn26851) );
  DFF_X1 z2693_assgn26930_reg ( .D(n870), .CK(clk), .Q(z2693_assgn26930) );
  DFF_X1 z2693_assgn26931_reg ( .D(z2693_assgn26930), .CK(clk), 
        .Q(z2693_assgn26931) );
  DFF_X1 z2719_assgn27190_reg ( .D(n868), .CK(clk), .Q(z2719_assgn27190) );
  DFF_X1 z2719_assgn27191_reg ( .D(z2719_assgn27190), .CK(clk), 
        .Q(z2719_assgn27191) );
  DFF_X1 temp_hpc2_v_1_order1_HPC231_reg ( .D(N62), .CK(clk), 
        .Q(z3365_assgn3365) );
  DFF_X1 temp_hpc2_v_1_order0_HPC232_reg ( .D(N64), .CK(clk), 
        .Q(z3391_assgn3391) );
  DFF_X1 temp_hpc2_v_1_order1_HPC232_reg ( .D(N66), .CK(clk), 
        .Q(z3405_assgn3405) );
  DFF_X1 z2811_assgn28110_reg ( .D(n865), .CK(clk), .Q(z2811_assgn28110) );
  DFF_X1 temp_hpc2o_v_1_order0_HPC2o33_reg ( 
        .D(xor_br_hpc2o_v_1_order0_HPC2o33), .CK(clk), .Q(z3443_assgn3443) );
  DFF_X1 z2811_assgn28111_reg ( .D(z2811_assgn28110), .CK(clk), 
        .Q(z2811_assgn28111) );
  DFF_X1 temp_hpc2o_v_1_order1_HPC2o33_reg ( 
        .D(xor_br_hpc2o_v_1_order1_HPC2o33), .CK(clk), .Q(z3469_assgn3469) );
  DFF_X1 z3469_assgn34690_reg ( .D(z3469_assgn3469), .CK(clk), 
        .Q(z3469_assgn34690) );
  DFF_X1 z1596_assgn1596_reg ( .D(z3469_assgn34690), .CK(clk), 
        .Q(z1596_assgn1596) );
  DFF_X1 z3451_assgn34511_reg ( .D(T2_1_reg), .CK(clk), .Q(z3451_assgn34511)
         );
  DFF_X1 z1579_assgn1579_reg ( .D(z3451_assgn34511), .CK(clk), 
        .Q(z1579_assgn1579) );
  DFF_X1 z3443_assgn34430_reg ( .D(z3443_assgn3443), .CK(clk), 
        .Q(z3443_assgn34430) );
  DFF_X1 z1574_assgn1574_reg ( .D(z3443_assgn34430), .CK(clk), 
        .Q(z1574_assgn1574) );
  DFF_X1 z3425_assgn34251_reg ( .D(T2_0_reg), .CK(clk), .Q(z3425_assgn34251)
         );
  DFF_X1 z1557_assgn1557_reg ( .D(z3425_assgn34251), .CK(clk), 
        .Q(z1557_assgn1557) );
  DFF_X1 z3417_assgn34171_reg ( .D(T4_1_reg), .CK(clk), .Q(z3417_assgn34171)
         );
  DFF_X1 z1551_assgn1551_reg ( .D(z3417_assgn34171), .CK(clk), 
        .Q(z1551_assgn1551) );
  DFF_X1 z3405_assgn34050_reg ( .D(z3405_assgn3405), .CK(clk), 
        .Q(z3405_assgn34050) );
  DFF_X1 z1542_assgn1542_reg ( .D(z3405_assgn34050), .CK(clk), 
        .Q(z1542_assgn1542) );
  DFF_X1 z3391_assgn33910_reg ( .D(z3391_assgn3391), .CK(clk), 
        .Q(z3391_assgn33910) );
  DFF_X1 z1530_assgn1530_reg ( .D(z3391_assgn33910), .CK(clk), 
        .Q(z1530_assgn1530) );
  DFF_X1 z2881_assgn28810_reg ( .D(n871), .CK(clk), .Q(z2881_assgn28810) );
  DFF_X1 z2881_assgn28811_reg ( .D(z2881_assgn28810), .CK(clk), 
        .Q(z2881_assgn28811) );
  DFF_X1 z3385_assgn33851_reg ( .D(T4_0_reg), .CK(clk), .Q(z3385_assgn33851)
         );
  DFF_X1 z1525_assgn1525_reg ( .D(z3385_assgn33851), .CK(clk), 
        .Q(z1525_assgn1525) );
  DFF_X1 z3377_assgn33771_reg ( .D(T1_1_reg), .CK(clk), .Q(z3377_assgn33771)
         );
  DFF_X1 z1519_assgn1519_reg ( .D(z3377_assgn33771), .CK(clk), 
        .Q(z1519_assgn1519) );
  DFF_X1 z3365_assgn33650_reg ( .D(z3365_assgn3365), .CK(clk), 
        .Q(z3365_assgn33650) );
  DFF_X1 z1510_assgn1510_reg ( .D(z3365_assgn33650), .CK(clk), 
        .Q(z1510_assgn1510) );
  DFF_X1 z3345_assgn33451_reg ( .D(T1_0_reg), .CK(clk), .Q(z3345_assgn33451)
         );
  DFF_X1 z3315_assgn33151_reg ( .D(T20_1_reg), .CK(clk), .Q(z3315_assgn33151)
         );
  DFF_X1 z3289_assgn32891_reg ( .D(T20_0_reg), .CK(clk), .Q(z3289_assgn32891)
         );
  DFF_X1 z3259_assgn32591_reg ( .D(T22_1_reg), .CK(clk), .Q(z3259_assgn32591)
         );
  DFF_X1 z2921_assgn29210_reg ( .D(n860), .CK(clk), .Q(z2921_assgn29210) );
  DFF_X1 z2921_assgn29211_reg ( .D(z2921_assgn29210), .CK(clk), 
        .Q(z2921_assgn29211) );
  DFF_X1 z3233_assgn32331_reg ( .D(T22_0_reg), .CK(clk), .Q(z3233_assgn32331)
         );
  DFF_X1 z3225_assgn32251_reg ( .D(T3_1_reg), .CK(clk), .Q(z3225_assgn32251)
         );
  DFF_X1 z3193_assgn31931_reg ( .D(T3_0_reg), .CK(clk), .Q(z3193_assgn31931)
         );
  DFF_X1 z3163_assgn31631_reg ( .D(T19_1_reg), .CK(clk), .Q(z3163_assgn31631)
         );
  DFF_X1 z3137_assgn31371_reg ( .D(T19_0_reg), .CK(clk), .Q(z3137_assgn31371)
         );
  DFF_X1 z3129_assgn31291_reg ( .D(T23_1_reg), .CK(clk), .Q(z3129_assgn31291)
         );
  DFF_X1 z3097_assgn30971_reg ( .D(T23_0_reg), .CK(clk), .Q(z3097_assgn30971)
         );
  DFF_X1 z3089_assgn30891_reg ( .D(T13_1_reg), .CK(clk), .Q(z3089_assgn30891)
         );
  DFF_X1 z2961_assgn29610_reg ( .D(n875), .CK(clk), .Q(z2961_assgn29610) );
  DFF_X1 z3057_assgn30571_reg ( .D(T13_0_reg), .CK(clk), .Q(z3057_assgn30571)
         );
  DFF_X1 z3027_assgn30270_reg ( .D(n867), .CK(clk), .Q(z3027_assgn30270) );
  DFF_X1 z3027_assgn30271_reg ( .D(z3027_assgn30270), .CK(clk), 
        .Q(z3027_assgn30271) );
  DFF_X1 z3001_assgn30010_reg ( .D(n873), .CK(clk), .Q(z3001_assgn30010) );
  DFF_X1 z3001_assgn30011_reg ( .D(z3001_assgn30010), .CK(clk), 
        .Q(z3001_assgn30011) );
  DFF_X1 z2993_assgn29930_reg ( .D(n874), .CK(clk), .Q(z2993_assgn29930) );
  DFF_X1 z2993_assgn29931_reg ( .D(z2993_assgn29930), .CK(clk), 
        .Q(z2993_assgn29931) );
  DFF_X1 z2961_assgn29611_reg ( .D(z2961_assgn29610), .CK(clk), 
        .Q(z2961_assgn29611) );
  DFF_X1 temp_hpc3_v_1_order0_HPC30_reg ( .D(N0), .CK(clk), 
        .Q(temp_hpc3_v_1_order0_HPC30) );
  DFF_X1 T13_0_reg_reg ( .D(n896), .CK(clk), .Q(T13_0_reg) );
  DFF_X1 w01_HPC30_reg ( .D(N1), .CK(clk), .Q(w01_HPC30) );
  DFF_X1 temp_hpc3_v_1_order1_HPC30_reg ( .D(N2), .CK(clk), 
        .Q(temp_hpc3_v_1_order1_HPC30) );
  DFF_X1 T13_1_reg_reg ( .D(n881), .CK(clk), .Q(T13_1_reg) );
  DFF_X1 w10_HPC30_reg ( .D(N3), .CK(clk), .Q(w10_HPC30) );
  DFF_X1 u00_HPC30_reg_reg ( .D(u00_HPC30), .CK(clk), .Q(u00_HPC30_reg) );
  DFF_X1 u11_HPC30_reg_reg ( .D(u11_HPC30), .CK(clk), .Q(u11_HPC30_reg) );
  DFF_X1 temp_hpc3o_v_1_order0_HPC3o1_reg ( .D(xor_br_hpc3o_v_1_order0_HPC3o1), 
        .CK(clk), .Q(temp_hpc3o_v_1_order0_HPC3o1) );
  DFF_X1 T23_0_reg_reg ( .D(n882), .CK(clk), .Q(T23_0_reg) );
  DFF_X1 temp_hpc3o_v_1_order1_HPC3o1_reg ( .D(xor_br_hpc3o_v_1_order1_HPC3o1), 
        .CK(clk), .Q(temp_hpc3o_v_1_order1_HPC3o1) );
  DFF_X1 T23_1_reg_reg ( .D(n889), .CK(clk), .Q(T23_1_reg) );
  DFF_X1 T14_0_reg_reg ( .D(T14_0), .CK(clk), .Q(T14_0_reg) );
  DFF_X1 w01_HPC3o1_reg ( .D(xor_step2_hpc3o_first_half_1_order0_HPC3o1), 
        .CK(clk), .Q(w01_HPC3o1) );
  DFF_X1 T14_1_reg_reg ( .D(T14_1), .CK(clk), .Q(T14_1_reg) );
  DFF_X1 w10_HPC3o1_reg ( .D(xor_step2_hpc3o_first_half_1_order1_HPC3o1), 
        .CK(clk), .Q(w10_HPC3o1) );
  DFF_X1 temp_hpc3o_v_1_order0_HPC3o2_reg ( .D(xor_br_hpc3o_v_1_order0_HPC3o2), 
        .CK(clk), .Q(temp_hpc3o_v_1_order0_HPC3o2) );
  DFF_X1 T19_0_reg_reg ( .D(n892), .CK(clk), .Q(T19_0_reg) );
  DFF_X1 w01_HPC3o2_reg ( .D(xor_step2_hpc3o_first_half_1_order0_HPC3o2), 
        .CK(clk), .Q(w01_HPC3o2) );
  DFF_X1 temp_hpc3o_v_1_order1_HPC3o2_reg ( .D(xor_br_hpc3o_v_1_order1_HPC3o2), 
        .CK(clk), .Q(temp_hpc3o_v_1_order1_HPC3o2) );
  DFF_X1 T19_1_reg_reg ( .D(n891), .CK(clk), .Q(T19_1_reg) );
  DFF_X1 w10_HPC3o2_reg ( .D(xor_step2_hpc3o_first_half_1_order1_HPC3o2), 
        .CK(clk), .Q(w10_HPC3o2) );
  DFF_X1 temp_hpc3_v_1_order0_HPC33_reg ( .D(N4), .CK(clk), 
        .Q(temp_hpc3_v_1_order0_HPC33) );
  DFF_X1 T3_0_reg_reg ( .D(n895), .CK(clk), .Q(T3_0_reg) );
  DFF_X1 w01_HPC33_reg ( .D(N5), .CK(clk), .Q(w01_HPC33) );
  DFF_X1 temp_hpc3_v_1_order1_HPC33_reg ( .D(N6), .CK(clk), 
        .Q(temp_hpc3_v_1_order1_HPC33) );
  DFF_X1 T3_1_reg_reg ( .D(n880), .CK(clk), .Q(T3_1_reg) );
  DFF_X1 w10_HPC33_reg ( .D(N7), .CK(clk), .Q(w10_HPC33) );
  DFF_X1 u00_HPC33_reg_reg ( .D(u00_HPC33), .CK(clk), .Q(u00_HPC33_reg) );
  DFF_X1 u11_HPC33_reg_reg ( .D(u11_HPC33), .CK(clk), .Q(u11_HPC33_reg) );
  DFF_X1 temp_hpc3o_v_1_order0_HPC3o4_reg ( .D(xor_br_hpc3o_v_1_order0_HPC3o4), 
        .CK(clk), .Q(temp_hpc3o_v_1_order0_HPC3o4) );
  DFF_X1 T22_0_reg_reg ( .D(n866), .CK(clk), .Q(T22_0_reg) );
  DFF_X1 temp_hpc3o_v_1_order1_HPC3o4_reg ( .D(xor_br_hpc3o_v_1_order1_HPC3o4), 
        .CK(clk), .Q(temp_hpc3o_v_1_order1_HPC3o4) );
  DFF_X1 T22_1_reg_reg ( .D(n863), .CK(clk), .Q(T22_1_reg) );
  DFF_X1 T26_0_reg_reg ( .D(T26_0), .CK(clk), .Q(T26_0_reg) );
  DFF_X1 w01_HPC3o4_reg ( .D(xor_step2_hpc3o_first_half_1_order0_HPC3o4), 
        .CK(clk), .Q(w01_HPC3o4) );
  DFF_X1 T26_1_reg_reg ( .D(T26_1), .CK(clk), .Q(T26_1_reg) );
  DFF_X1 w10_HPC3o4_reg ( .D(xor_step2_hpc3o_first_half_1_order1_HPC3o4), 
        .CK(clk), .Q(w10_HPC3o4) );
  DFF_X1 temp_hpc3o_v_1_order0_HPC3o5_reg ( .D(xor_br_hpc3o_v_1_order0_HPC3o5), 
        .CK(clk), .Q(temp_hpc3o_v_1_order0_HPC3o5) );
  DFF_X1 T20_0_reg_reg ( .D(n890), .CK(clk), .Q(T20_0_reg) );
  DFF_X1 w01_HPC3o5_reg ( .D(xor_step2_hpc3o_first_half_1_order0_HPC3o5), 
        .CK(clk), .Q(w01_HPC3o5) );
  DFF_X1 temp_hpc3o_v_1_order1_HPC3o5_reg ( .D(xor_br_hpc3o_v_1_order1_HPC3o5), 
        .CK(clk), .Q(temp_hpc3o_v_1_order1_HPC3o5) );
  DFF_X1 T20_1_reg_reg ( .D(n893), .CK(clk), .Q(T20_1_reg) );
  DFF_X1 w10_HPC3o5_reg ( .D(xor_step2_hpc3o_first_half_1_order1_HPC3o5), 
        .CK(clk), .Q(w10_HPC3o5) );
  DFF_X1 temp_hpc3_v_1_order0_HPC36_reg ( .D(N8), .CK(clk), 
        .Q(temp_hpc3_v_1_order0_HPC36) );
  DFF_X1 T1_0_reg_reg ( .D(n853), .CK(clk), .Q(T1_0_reg) );
  DFF_X1 w01_HPC36_reg ( .D(N9), .CK(clk), .Q(w01_HPC36) );
  DFF_X1 temp_hpc3_v_1_order1_HPC36_reg ( .D(N10), .CK(clk), 
        .Q(temp_hpc3_v_1_order1_HPC36) );
  DFF_X1 T1_1_reg_reg ( .D(n854), .CK(clk), .Q(T1_1_reg) );
  DFF_X1 w10_HPC36_reg ( .D(N11), .CK(clk), .Q(w10_HPC36) );
  DFF_X1 u00_HPC36_reg_reg ( .D(u00_HPC36), .CK(clk), .Q(u00_HPC36_reg) );
  DFF_X1 u11_HPC36_reg_reg ( .D(u11_HPC36), .CK(clk), .Q(u11_HPC36_reg) );
  DFF_X1 temp_hpc3o_v_1_order0_HPC3o7_reg ( .D(xor_br_hpc3o_v_1_order0_HPC3o7), 
        .CK(clk), .Q(temp_hpc3o_v_1_order0_HPC3o7) );
  DFF_X1 T4_0_reg_reg ( .D(n885), .CK(clk), .Q(T4_0_reg) );
  DFF_X1 w01_HPC3o7_reg ( .D(xor_step2_hpc3o_first_half_1_order0_HPC3o7), 
        .CK(clk), .Q(w01_HPC3o7) );
  DFF_X1 temp_hpc3o_v_1_order1_HPC3o7_reg ( .D(xor_br_hpc3o_v_1_order1_HPC3o7), 
        .CK(clk), .Q(temp_hpc3o_v_1_order1_HPC3o7) );
  DFF_X1 T4_1_reg_reg ( .D(n879), .CK(clk), .Q(T4_1_reg) );
  DFF_X1 w10_HPC3o7_reg ( .D(xor_step2_hpc3o_first_half_1_order1_HPC3o7), 
        .CK(clk), .Q(w10_HPC3o7) );
  DFF_X1 temp_hpc3o_v_1_order0_HPC3o8_reg ( .D(xor_br_hpc3o_v_1_order0_HPC3o8), 
        .CK(clk), .Q(temp_hpc3o_v_1_order0_HPC3o8) );
  DFF_X1 T2_0_reg_reg ( .D(n862), .CK(clk), .Q(T2_0_reg) );
  DFF_X1 w01_HPC3o8_reg ( .D(xor_step2_hpc3o_first_half_1_order0_HPC3o8), 
        .CK(clk), .Q(w01_HPC3o8) );
  DFF_X1 temp_hpc3o_v_1_order1_HPC3o8_reg ( .D(xor_br_hpc3o_v_1_order1_HPC3o8), 
        .CK(clk), .Q(temp_hpc3o_v_1_order1_HPC3o8) );
  DFF_X1 T2_1_reg_reg ( .D(n861), .CK(clk), .Q(T2_1_reg) );
  DFF_X1 w10_HPC3o8_reg ( .D(xor_step2_hpc3o_first_half_1_order1_HPC3o8), 
        .CK(clk), .Q(w10_HPC3o8) );
  DFF_X1 T24_0_reg_reg ( .D(T24_0), .CK(clk), .Q(T24_0_reg) );
  DFF_X1 T24_1_reg_reg ( .D(T24_1), .CK(clk), .Q(T24_1_reg) );
  DFF_X1 T25_0_reg_reg ( .D(T25_0), .CK(clk), .Q(T25_0_reg) );
  DFF_X1 z2621_assgn26210_reg ( .D(n894), .CK(clk), .Q(z2621_assgn26210) );
  DFF_X1 T25_1_reg_reg ( .D(T25_1), .CK(clk), .Q(T25_1_reg) );
  DFF_X1 z2625_assgn26250_reg ( .D(n886), .CK(clk), .Q(z2625_assgn26250) );
  DFF_X1 temp_hpc3_v_1_order0_HPC39_reg ( .D(N12), .CK(clk), 
        .Q(temp_hpc3_v_1_order0_HPC39) );
  DFF_X1 M22_0_reg_reg ( .D(n888), .CK(clk), .Q(M22_0_reg) );
  DFF_X1 w01_HPC39_reg ( .D(N13), .CK(clk), .Q(w01_HPC39) );
  DFF_X1 temp_hpc3_v_1_order1_HPC39_reg ( .D(N14), .CK(clk), 
        .Q(temp_hpc3_v_1_order1_HPC39) );
  DFF_X1 M22_1_reg_reg ( .D(n884), .CK(clk), .Q(M22_1_reg) );
  DFF_X1 w10_HPC39_reg ( .D(N15), .CK(clk), .Q(w10_HPC39) );
  DFF_X1 u00_HPC39_reg_reg ( .D(u00_HPC39), .CK(clk), .Q(u00_HPC39_reg) );
  DFF_X1 u11_HPC39_reg_reg ( .D(u11_HPC39), .CK(clk), .Q(u11_HPC39_reg) );
  DFF_X1 M21_0_reg_reg ( .D(n851), .CK(clk), .Q(M21_0_reg) );
  DFF_X1 M21_1_reg_reg ( .D(n852), .CK(clk), .Q(M21_1_reg) );
  DFF_X1 M27_0_reg_reg ( .D(n876), .CK(clk), .Q(M27_0_reg) );
  DFF_X1 temp_hpc2o_v_1_order0_HPC2o10_reg ( 
        .D(xor_br_hpc2o_v_1_order0_HPC2o10), .CK(clk), 
        .Q(temp_hpc2o_v_1_order0_HPC2o10) );
  DFF_X1 v01_HPC2o10_reg ( .D(and_ta_hpc2o_v_1_order0_HPC2o10), .CK(clk), 
        .Q(v01_HPC2o10) );
  DFF_X1 M27_1_reg_reg ( .D(n877), .CK(clk), .Q(M27_1_reg) );
  DFF_X1 temp_hpc2o_v_1_order1_HPC2o10_reg ( 
        .D(xor_br_hpc2o_v_1_order1_HPC2o10), .CK(clk), 
        .Q(temp_hpc2o_v_1_order1_HPC2o10) );
  DFF_X1 v10_HPC2o10_reg ( .D(and_ta_hpc2o_v_1_order1_HPC2o10), .CK(clk), 
        .Q(v10_HPC2o10) );
  DFF_X1 M24_0_reg_reg ( .D(n872), .CK(clk), .Q(M24_0_reg) );
  DFF_X1 temp_hpc2o_v_1_order0_HPC2o11_reg ( 
        .D(xor_br_hpc2o_v_1_order0_HPC2o11), .CK(clk), 
        .Q(temp_hpc2o_v_1_order0_HPC2o11) );
  DFF_X1 v01_HPC2o11_reg ( .D(and_ta_hpc2o_v_1_order0_HPC2o11), .CK(clk), 
        .Q(v01_HPC2o11) );
  DFF_X1 M24_1_reg_reg ( .D(n878), .CK(clk), .Q(M24_1_reg) );
  DFF_X1 temp_hpc2o_v_1_order1_HPC2o11_reg ( 
        .D(xor_br_hpc2o_v_1_order1_HPC2o11), .CK(clk), 
        .Q(temp_hpc2o_v_1_order1_HPC2o11) );
  DFF_X1 v10_HPC2o11_reg ( .D(and_ta_hpc2o_v_1_order1_HPC2o11), .CK(clk), 
        .Q(v10_HPC2o11) );
  DFF_X1 temp_hpc3_v_1_order0_HPC312_reg ( .D(N16), .CK(clk), 
        .Q(temp_hpc3_v_1_order0_HPC312) );
  DFF_X1 M20_0_reg_reg ( .D(n887), .CK(clk), .Q(M20_0_reg) );
  DFF_X1 w01_HPC312_reg ( .D(N17), .CK(clk), .Q(w01_HPC312) );
  DFF_X1 temp_hpc3_v_1_order1_HPC312_reg ( .D(N18), .CK(clk), 
        .Q(temp_hpc3_v_1_order1_HPC312) );
  DFF_X1 M20_1_reg_reg ( .D(n883), .CK(clk), .Q(M20_1_reg) );
  DFF_X1 w10_HPC312_reg ( .D(N19), .CK(clk), .Q(w10_HPC312) );
  DFF_X1 u00_HPC312_reg_reg ( .D(u00_HPC312), .CK(clk), .Q(u00_HPC312_reg) );
  DFF_X1 u11_HPC312_reg_reg ( .D(u11_HPC312), .CK(clk), .Q(u11_HPC312_reg) );
  DFF_X1 temp_hpc2osw_v_1_order0_HPC2o_swapped13_reg ( 
        .D(xor_br_hpc2osw_v_1_order0_HPC2o_swapped13), .CK(clk), 
        .Q(temp_hpc2osw_v_1_order0_HPC2o_swapped13) );
  DFF_X1 v01_HPC2o_swapped13_reg ( 
        .D(and_ta_hpc2osw_v_1_order0_HPC2o_swapped13), .CK(clk), 
        .Q(v01_HPC2o_swapped13) );
  DFF_X1 temp_hpc2osw_v_1_order1_HPC2o_swapped13_reg ( 
        .D(xor_br_hpc2osw_v_1_order1_HPC2o_swapped13), .CK(clk), 
        .Q(temp_hpc2osw_v_1_order1_HPC2o_swapped13) );
  DFF_X1 v10_HPC2o_swapped13_reg ( 
        .D(and_ta_hpc2osw_v_1_order1_HPC2o_swapped13), .CK(clk), 
        .Q(v10_HPC2o_swapped13) );
  DFF_X1 temp_hpc3_v_1_order0_HPC314_reg ( .D(N20), .CK(clk), 
        .Q(temp_hpc3_v_1_order0_HPC314) );
  DFF_X1 w01_HPC314_reg ( .D(N21), .CK(clk), .Q(w01_HPC314) );
  DFF_X1 temp_hpc3_v_1_order1_HPC314_reg ( .D(N22), .CK(clk), 
        .Q(temp_hpc3_v_1_order1_HPC314) );
  DFF_X1 w10_HPC314_reg ( .D(N23), .CK(clk), .Q(w10_HPC314) );
  DFF_X1 u00_HPC314_reg_reg ( .D(u00_HPC314), .CK(clk), .Q(u00_HPC314_reg) );
  DFF_X1 u11_HPC314_reg_reg ( .D(u11_HPC314), .CK(clk), .Q(u11_HPC314_reg) );
  DFF_X1 temp_hpc2osw_v_1_order0_HPC2o_swapped15_reg ( 
        .D(xor_br_hpc2osw_v_1_order0_HPC2o_swapped15), .CK(clk), 
        .Q(temp_hpc2osw_v_1_order0_HPC2o_swapped15) );
  DFF_X1 v01_HPC2o_swapped15_reg ( 
        .D(and_ta_hpc2osw_v_1_order0_HPC2o_swapped15), .CK(clk), 
        .Q(v01_HPC2o_swapped15) );
  DFF_X1 temp_hpc2osw_v_1_order1_HPC2o_swapped15_reg ( 
        .D(xor_br_hpc2osw_v_1_order1_HPC2o_swapped15), .CK(clk), 
        .Q(temp_hpc2osw_v_1_order1_HPC2o_swapped15) );
  DFF_X1 v10_HPC2o_swapped15_reg ( 
        .D(and_ta_hpc2osw_v_1_order1_HPC2o_swapped15), .CK(clk), 
        .Q(v10_HPC2o_swapped15) );
  DFF_X1 z882_assgn882_reg ( .D(M21_0_reg), .CK(clk), .Q(z882_assgn882) );
  DFF_X1 w01_HPC2o10_reg ( .D(n835), .CK(clk), .Q(w01_HPC2o10) );
  DFF_X1 z884_assgn884_reg ( .D(M21_1_reg), .CK(clk), .Q(z884_assgn884) );
  DFF_X1 w10_HPC2o10_reg ( .D(n836), .CK(clk), .Q(w10_HPC2o10) );
  DFF_X1 M33_0_reg_reg ( .D(M33_0), .CK(clk), .Q(M33_0_reg) );
  DFF_X1 w01_HPC2o_swapped13_reg ( .D(n834), .CK(clk), .Q(w01_HPC2o_swapped13)
         );
  DFF_X1 M33_1_reg_reg ( .D(M33_1), .CK(clk), .Q(M33_1_reg) );
  DFF_X1 w10_HPC2o_swapped13_reg ( .D(n833), .CK(clk), .Q(w10_HPC2o_swapped13)
         );
  DFF_X1 z890_assgn890_reg ( .D(z2621_assgn26210), .CK(clk), .Q(z890_assgn890)
         );
  DFF_X1 w01_HPC2o11_reg ( .D(n825), .CK(clk), .Q(w01_HPC2o11) );
  DFF_X1 z892_assgn892_reg ( .D(z2625_assgn26250), .CK(clk), .Q(z892_assgn892)
         );
  DFF_X1 w10_HPC2o11_reg ( .D(n826), .CK(clk), .Q(w10_HPC2o11) );
  DFF_X1 v10_HPC231_reg ( .D(z39_assgn39), .CK(clk), .Q(v10_HPC231) );
  DFF_X1 u11_HPC231_reg_reg ( .D(u11_HPC231), .CK(clk), .Q(u11_HPC231_reg) );
  DFF_X1 w10_HPC231_reg ( .D(N63), .CK(clk), .Q(w10_HPC231) );
  DFF_X1 M36_0_reg_reg ( .D(M36_0), .CK(clk), .Q(M36_0_reg) );
  DFF_X1 w01_HPC2o_swapped15_reg ( .D(n832), .CK(clk), .Q(w01_HPC2o_swapped15)
         );
  DFF_X1 v01_HPC232_reg ( .D(z41_assgn41), .CK(clk), .Q(v01_HPC232) );
  DFF_X1 u00_HPC232_reg_reg ( .D(u00_HPC232), .CK(clk), .Q(u00_HPC232_reg) );
  DFF_X1 w01_HPC232_reg ( .D(N65), .CK(clk), .Q(w01_HPC232) );
  DFF_X1 v01_HPC2o33_reg ( .D(and_ta_hpc2o_v_1_order0_HPC2o33), .CK(clk), 
        .Q(v01_HPC2o33) );
  DFF_X1 M36_1_reg_reg ( .D(M36_1), .CK(clk), .Q(M36_1_reg) );
  DFF_X1 w10_HPC2o_swapped15_reg ( .D(n831), .CK(clk), .Q(w10_HPC2o_swapped15)
         );
  DFF_X1 v10_HPC2o33_reg ( .D(and_ta_hpc2o_v_1_order1_HPC2o33), .CK(clk), 
        .Q(v10_HPC2o33) );
  DFF_X1 v10_HPC232_reg ( .D(z43_assgn43), .CK(clk), .Q(v10_HPC232) );
  DFF_X1 u11_HPC232_reg_reg ( .D(u11_HPC232), .CK(clk), .Q(u11_HPC232_reg) );
  DFF_X1 w10_HPC232_reg ( .D(N67), .CK(clk), .Q(w10_HPC232) );
  DFF_X1 z917_assgn917_reg ( .D(z2653_assgn26531), .CK(clk), .Q(z917_assgn917)
         );
  DFF_X1 temp_hpc2_v_1_order0_HPC216_reg ( .D(N24), .CK(clk), 
        .Q(z2659_assgn2659) );
  DFF_X1 z2659_assgn26590_reg ( .D(z2659_assgn2659), .CK(clk), 
        .Q(z2659_assgn26590) );
  DFF_X1 z922_assgn922_reg ( .D(z2659_assgn26590), .CK(clk), .Q(z922_assgn922)
         );
  DFF_X1 v01_HPC216_reg ( .D(z1_assgn1), .CK(clk), .Q(v01_HPC216) );
  DFF_X1 w01_HPC216_reg ( .D(N25), .CK(clk), .Q(w01_HPC216) );
  DFF_X1 temp_hpc2_v_1_order1_HPC216_reg ( .D(N26), .CK(clk), 
        .Q(z2673_assgn2673) );
  DFF_X1 z2673_assgn26730_reg ( .D(z2673_assgn2673), .CK(clk), 
        .Q(z2673_assgn26730) );
  DFF_X1 z934_assgn934_reg ( .D(z2673_assgn26730), .CK(clk), .Q(z934_assgn934)
         );
  DFF_X1 v10_HPC216_reg ( .D(z3_assgn3), .CK(clk), .Q(v10_HPC216) );
  DFF_X1 w10_HPC216_reg ( .D(N27), .CK(clk), .Q(w10_HPC216) );
  DFF_X1 z943_assgn943_reg ( .D(z2685_assgn26851), .CK(clk), .Q(z943_assgn943)
         );
  DFF_X1 u00_HPC216_reg_reg ( .D(u00_HPC216), .CK(clk), .Q(u00_HPC216_reg) );
  DFF_X1 u11_HPC216_reg_reg ( .D(u11_HPC216), .CK(clk), .Q(u11_HPC216_reg) );
  DFF_X1 z949_assgn949_reg ( .D(z2693_assgn26931), .CK(clk), .Q(z949_assgn949)
         );
  DFF_X1 temp_hpc2o_v_1_order0_HPC2o17_reg ( 
        .D(xor_br_hpc2o_v_1_order0_HPC2o17), .CK(clk), .Q(z2711_assgn2711) );
  DFF_X1 z2711_assgn27110_reg ( .D(z2711_assgn2711), .CK(clk), 
        .Q(z2711_assgn27110) );
  DFF_X1 z966_assgn966_reg ( .D(z2711_assgn27110), .CK(clk), .Q(z966_assgn966)
         );
  DFF_X1 v01_HPC2o17_reg ( .D(and_ta_hpc2o_v_1_order0_HPC2o17), .CK(clk), 
        .Q(v01_HPC2o17) );
  DFF_X1 z971_assgn971_reg ( .D(z2719_assgn27191), .CK(clk), .Q(z971_assgn971)
         );
  DFF_X1 temp_hpc2o_v_1_order1_HPC2o17_reg ( 
        .D(xor_br_hpc2o_v_1_order1_HPC2o17), .CK(clk), .Q(z2737_assgn2737) );
  DFF_X1 z2737_assgn27370_reg ( .D(z2737_assgn2737), .CK(clk), 
        .Q(z2737_assgn27370) );
  DFF_X1 z988_assgn988_reg ( .D(z2737_assgn27370), .CK(clk), .Q(z988_assgn988)
         );
  DFF_X1 v10_HPC2o17_reg ( .D(and_ta_hpc2o_v_1_order1_HPC2o17), .CK(clk), 
        .Q(v10_HPC2o17) );
  DFF_X1 temp_hpc2_v_1_order0_HPC218_reg ( .D(N28), .CK(clk), 
        .Q(z2753_assgn2753) );
  DFF_X1 z2753_assgn27530_reg ( .D(z2753_assgn2753), .CK(clk), 
        .Q(z2753_assgn27530) );
  DFF_X1 z1002_assgn1002_reg ( .D(z2753_assgn27530), .CK(clk), 
        .Q(z1002_assgn1002) );
  DFF_X1 v01_HPC218_reg ( .D(z5_assgn5), .CK(clk), .Q(v01_HPC218) );
  DFF_X1 w01_HPC218_reg ( .D(N29), .CK(clk), .Q(w01_HPC218) );
  DFF_X1 temp_hpc2_v_1_order1_HPC218_reg ( .D(N30), .CK(clk), 
        .Q(z2767_assgn2767) );
  DFF_X1 z2767_assgn27670_reg ( .D(z2767_assgn2767), .CK(clk), 
        .Q(z2767_assgn27670) );
  DFF_X1 z1014_assgn1014_reg ( .D(z2767_assgn27670), .CK(clk), 
        .Q(z1014_assgn1014) );
  DFF_X1 v10_HPC218_reg ( .D(z7_assgn7), .CK(clk), .Q(v10_HPC218) );
  DFF_X1 w10_HPC218_reg ( .D(N31), .CK(clk), .Q(w10_HPC218) );
  DFF_X1 u00_HPC218_reg_reg ( .D(u00_HPC218), .CK(clk), .Q(u00_HPC218_reg) );
  DFF_X1 u11_HPC218_reg_reg ( .D(u11_HPC218), .CK(clk), .Q(u11_HPC218_reg) );
  DFF_X1 z1029_assgn1029_reg ( .D(z2785_assgn27851), .CK(clk), 
        .Q(z1029_assgn1029) );
  DFF_X1 temp_hpc2o_v_1_order0_HPC2o19_reg ( 
        .D(xor_br_hpc2o_v_1_order0_HPC2o19), .CK(clk), .Q(z2803_assgn2803) );
  DFF_X1 z2803_assgn28030_reg ( .D(z2803_assgn2803), .CK(clk), 
        .Q(z2803_assgn28030) );
  DFF_X1 z1046_assgn1046_reg ( .D(z2803_assgn28030), .CK(clk), 
        .Q(z1046_assgn1046) );
  DFF_X1 v01_HPC2o19_reg ( .D(and_ta_hpc2o_v_1_order0_HPC2o19), .CK(clk), 
        .Q(v01_HPC2o19) );
  DFF_X1 z1051_assgn1051_reg ( .D(z2811_assgn28111), .CK(clk), 
        .Q(z1051_assgn1051) );
  DFF_X1 temp_hpc2o_v_1_order1_HPC2o19_reg ( 
        .D(xor_br_hpc2o_v_1_order1_HPC2o19), .CK(clk), .Q(z2829_assgn2829) );
  DFF_X1 z2829_assgn28290_reg ( .D(z2829_assgn2829), .CK(clk), 
        .Q(z2829_assgn28290) );
  DFF_X1 z1068_assgn1068_reg ( .D(z2829_assgn28290), .CK(clk), 
        .Q(z1068_assgn1068) );
  DFF_X1 v10_HPC2o19_reg ( .D(and_ta_hpc2o_v_1_order1_HPC2o19), .CK(clk), 
        .Q(v10_HPC2o19) );
  DFF_X1 w10_HPC2o19_reg ( .D(n829), .CK(clk), .Q(w10_HPC2o19) );
  DFF_X1 z1077_assgn1077_reg ( .D(z2841_assgn28411), .CK(clk), 
        .Q(z1077_assgn1077) );
  DFF_X1 temp_hpc2_v_1_order0_HPC220_reg ( .D(N32), .CK(clk), 
        .Q(z2847_assgn2847) );
  DFF_X1 z2847_assgn28470_reg ( .D(z2847_assgn2847), .CK(clk), 
        .Q(z2847_assgn28470) );
  DFF_X1 z1082_assgn1082_reg ( .D(z2847_assgn28470), .CK(clk), 
        .Q(z1082_assgn1082) );
  DFF_X1 v01_HPC220_reg ( .D(z9_assgn9), .CK(clk), .Q(v01_HPC220) );
  DFF_X1 w01_HPC220_reg ( .D(N33), .CK(clk), .Q(w01_HPC220) );
  DFF_X1 temp_hpc2_v_1_order1_HPC220_reg ( .D(N34), .CK(clk), 
        .Q(z2861_assgn2861) );
  DFF_X1 z2861_assgn28610_reg ( .D(z2861_assgn2861), .CK(clk), 
        .Q(z2861_assgn28610) );
  DFF_X1 z1094_assgn1094_reg ( .D(z2861_assgn28610), .CK(clk), 
        .Q(z1094_assgn1094) );
  DFF_X1 v10_HPC220_reg ( .D(z11_assgn11), .CK(clk), .Q(v10_HPC220) );
  DFF_X1 w10_HPC220_reg ( .D(N35), .CK(clk), .Q(w10_HPC220) );
  DFF_X1 z1103_assgn1103_reg ( .D(z2873_assgn28731), .CK(clk), 
        .Q(z1103_assgn1103) );
  DFF_X1 u00_HPC220_reg_reg ( .D(u00_HPC220), .CK(clk), .Q(u00_HPC220_reg) );
  DFF_X1 u11_HPC220_reg_reg ( .D(u11_HPC220), .CK(clk), .Q(u11_HPC220_reg) );
  DFF_X1 z1109_assgn1109_reg ( .D(z2881_assgn28811), .CK(clk), 
        .Q(z1109_assgn1109) );
  DFF_X1 temp_hpc2_v_1_order0_HPC221_reg ( .D(N36), .CK(clk), 
        .Q(z2887_assgn2887) );
  DFF_X1 z2887_assgn28870_reg ( .D(z2887_assgn2887), .CK(clk), 
        .Q(z2887_assgn28870) );
  DFF_X1 z1114_assgn1114_reg ( .D(z2887_assgn28870), .CK(clk), 
        .Q(z1114_assgn1114) );
  DFF_X1 v01_HPC221_reg ( .D(z13_assgn13), .CK(clk), .Q(v01_HPC221) );
  DFF_X1 w01_HPC221_reg ( .D(N37), .CK(clk), .Q(w01_HPC221) );
  DFF_X1 temp_hpc2_v_1_order1_HPC221_reg ( .D(N38), .CK(clk), 
        .Q(z2901_assgn2901) );
  DFF_X1 z2901_assgn29010_reg ( .D(z2901_assgn2901), .CK(clk), 
        .Q(z2901_assgn29010) );
  DFF_X1 z1126_assgn1126_reg ( .D(z2901_assgn29010), .CK(clk), 
        .Q(z1126_assgn1126) );
  DFF_X1 v10_HPC221_reg ( .D(z15_assgn15), .CK(clk), .Q(v10_HPC221) );
  DFF_X1 w10_HPC221_reg ( .D(N39), .CK(clk), .Q(w10_HPC221) );
  DFF_X1 z1135_assgn1135_reg ( .D(z2913_assgn29131), .CK(clk), 
        .Q(z1135_assgn1135) );
  DFF_X1 u00_HPC221_reg_reg ( .D(u00_HPC221), .CK(clk), .Q(u00_HPC221_reg) );
  DFF_X1 u11_HPC221_reg_reg ( .D(u11_HPC221), .CK(clk), .Q(u11_HPC221_reg) );
  DFF_X1 z1141_assgn1141_reg ( .D(z2921_assgn29211), .CK(clk), 
        .Q(z1141_assgn1141) );
  DFF_X1 temp_hpc2_v_1_order0_HPC222_reg ( .D(N40), .CK(clk), 
        .Q(z2927_assgn2927) );
  DFF_X1 z2927_assgn29270_reg ( .D(z2927_assgn2927), .CK(clk), 
        .Q(z2927_assgn29270) );
  DFF_X1 z1146_assgn1146_reg ( .D(z2927_assgn29270), .CK(clk), 
        .Q(z1146_assgn1146) );
  DFF_X1 v01_HPC222_reg ( .D(z17_assgn17), .CK(clk), .Q(v01_HPC222) );
  DFF_X1 w01_HPC222_reg ( .D(N41), .CK(clk), .Q(w01_HPC222) );
  DFF_X1 temp_hpc2_v_1_order1_HPC222_reg ( .D(N42), .CK(clk), 
        .Q(z2941_assgn2941) );
  DFF_X1 z2941_assgn29410_reg ( .D(z2941_assgn2941), .CK(clk), 
        .Q(z2941_assgn29410) );
  DFF_X1 z1158_assgn1158_reg ( .D(z2941_assgn29410), .CK(clk), 
        .Q(z1158_assgn1158) );
  DFF_X1 v10_HPC222_reg ( .D(z19_assgn19), .CK(clk), .Q(v10_HPC222) );
  DFF_X1 w10_HPC222_reg ( .D(N43), .CK(clk), .Q(w10_HPC222) );
  DFF_X1 z1167_assgn1167_reg ( .D(z2953_assgn29531), .CK(clk), 
        .Q(z1167_assgn1167) );
  DFF_X1 u00_HPC222_reg_reg ( .D(u00_HPC222), .CK(clk), .Q(u00_HPC222_reg) );
  DFF_X1 u11_HPC222_reg_reg ( .D(u11_HPC222), .CK(clk), .Q(u11_HPC222_reg) );
  DFF_X1 z1173_assgn1173_reg ( .D(z2961_assgn29611), .CK(clk), 
        .Q(z1173_assgn1173) );
  DFF_X1 temp_hpc2_v_1_order0_HPC223_reg ( .D(N44), .CK(clk), 
        .Q(z2967_assgn2967) );
  DFF_X1 z2967_assgn29670_reg ( .D(z2967_assgn2967), .CK(clk), 
        .Q(z2967_assgn29670) );
  DFF_X1 z1178_assgn1178_reg ( .D(z2967_assgn29670), .CK(clk), 
        .Q(z1178_assgn1178) );
  DFF_X1 v01_HPC223_reg ( .D(z21_assgn21), .CK(clk), .Q(v01_HPC223) );
  DFF_X1 w01_HPC223_reg ( .D(N45), .CK(clk), .Q(w01_HPC223) );
  DFF_X1 temp_hpc2_v_1_order1_HPC223_reg ( .D(N46), .CK(clk), 
        .Q(z2981_assgn2981) );
  DFF_X1 z2981_assgn29810_reg ( .D(z2981_assgn2981), .CK(clk), 
        .Q(z2981_assgn29810) );
  DFF_X1 z1190_assgn1190_reg ( .D(z2981_assgn29810), .CK(clk), 
        .Q(z1190_assgn1190) );
  DFF_X1 v10_HPC223_reg ( .D(z23_assgn23), .CK(clk), .Q(v10_HPC223) );
  DFF_X1 w10_HPC223_reg ( .D(N47), .CK(clk), .Q(w10_HPC223) );
  DFF_X1 z1199_assgn1199_reg ( .D(z2993_assgn29931), .CK(clk), 
        .Q(z1199_assgn1199) );
  DFF_X1 u00_HPC223_reg_reg ( .D(u00_HPC223), .CK(clk), .Q(u00_HPC223_reg) );
  DFF_X1 u11_HPC223_reg_reg ( .D(u11_HPC223), .CK(clk), .Q(u11_HPC223_reg) );
  DFF_X1 z1205_assgn1205_reg ( .D(z3001_assgn30011), .CK(clk), 
        .Q(z1205_assgn1205) );
  DFF_X1 temp_hpc2o_v_1_order0_HPC2o24_reg ( 
        .D(xor_br_hpc2o_v_1_order0_HPC2o24), .CK(clk), .Q(z3019_assgn3019) );
  DFF_X1 z3019_assgn30190_reg ( .D(z3019_assgn3019), .CK(clk), 
        .Q(z3019_assgn30190) );
  DFF_X1 z1222_assgn1222_reg ( .D(z3019_assgn30190), .CK(clk), 
        .Q(z1222_assgn1222) );
  DFF_X1 v01_HPC2o24_reg ( .D(and_ta_hpc2o_v_1_order0_HPC2o24), .CK(clk), 
        .Q(v01_HPC2o24) );
  DFF_X1 z1227_assgn1227_reg ( .D(z3027_assgn30271), .CK(clk), 
        .Q(z1227_assgn1227) );
  DFF_X1 temp_hpc2o_v_1_order1_HPC2o24_reg ( 
        .D(xor_br_hpc2o_v_1_order1_HPC2o24), .CK(clk), .Q(z3045_assgn3045) );
  DFF_X1 z3045_assgn30450_reg ( .D(z3045_assgn3045), .CK(clk), 
        .Q(z3045_assgn30450) );
  DFF_X1 z1244_assgn1244_reg ( .D(z3045_assgn30450), .CK(clk), 
        .Q(z1244_assgn1244) );
  DFF_X1 v10_HPC2o24_reg ( .D(and_ta_hpc2o_v_1_order1_HPC2o24), .CK(clk), 
        .Q(v10_HPC2o24) );
  DFF_X1 z1253_assgn1253_reg ( .D(z3057_assgn30571), .CK(clk), 
        .Q(z1253_assgn1253) );
  DFF_X1 temp_hpc2_v_1_order0_HPC225_reg ( .D(N48), .CK(clk), 
        .Q(z3063_assgn3063) );
  DFF_X1 z3063_assgn30630_reg ( .D(z3063_assgn3063), .CK(clk), 
        .Q(z3063_assgn30630) );
  DFF_X1 z1258_assgn1258_reg ( .D(z3063_assgn30630), .CK(clk), 
        .Q(z1258_assgn1258) );
  DFF_X1 v01_HPC225_reg ( .D(z25_assgn25), .CK(clk), .Q(v01_HPC225) );
  DFF_X1 w01_HPC225_reg ( .D(N49), .CK(clk), .Q(w01_HPC225) );
  DFF_X1 temp_hpc2_v_1_order1_HPC225_reg ( .D(N50), .CK(clk), 
        .Q(z3077_assgn3077) );
  DFF_X1 z3077_assgn30770_reg ( .D(z3077_assgn3077), .CK(clk), 
        .Q(z3077_assgn30770) );
  DFF_X1 z1270_assgn1270_reg ( .D(z3077_assgn30770), .CK(clk), 
        .Q(z1270_assgn1270) );
  DFF_X1 v10_HPC225_reg ( .D(z27_assgn27), .CK(clk), .Q(v10_HPC225) );
  DFF_X1 w10_HPC225_reg ( .D(N51), .CK(clk), .Q(w10_HPC225) );
  DFF_X1 z1279_assgn1279_reg ( .D(z3089_assgn30891), .CK(clk), 
        .Q(z1279_assgn1279) );
  DFF_X1 u00_HPC225_reg_reg ( .D(u00_HPC225), .CK(clk), .Q(u00_HPC225_reg) );
  DFF_X1 w01_HPC2o17_reg ( .D(n827), .CK(clk), .Q(w01_HPC2o17) );
  DFF_X1 u11_HPC225_reg_reg ( .D(u11_HPC225), .CK(clk), .Q(u11_HPC225_reg) );
  DFF_X1 w10_HPC2o17_reg ( .D(n828), .CK(clk), .Q(w10_HPC2o17) );
  DFF_X1 z1285_assgn1285_reg ( .D(z3097_assgn30971), .CK(clk), 
        .Q(z1285_assgn1285) );
  DFF_X1 temp_hpc2_v_1_order0_HPC226_reg ( .D(N52), .CK(clk), 
        .Q(z3103_assgn3103) );
  DFF_X1 z3103_assgn31030_reg ( .D(z3103_assgn3103), .CK(clk), 
        .Q(z3103_assgn31030) );
  DFF_X1 z1290_assgn1290_reg ( .D(z3103_assgn31030), .CK(clk), 
        .Q(z1290_assgn1290) );
  DFF_X1 v01_HPC226_reg ( .D(z29_assgn29), .CK(clk), .Q(v01_HPC226) );
  DFF_X1 w01_HPC226_reg ( .D(N53), .CK(clk), .Q(w01_HPC226) );
  DFF_X1 temp_hpc2_v_1_order1_HPC226_reg ( .D(N54), .CK(clk), 
        .Q(z3117_assgn3117) );
  DFF_X1 z3117_assgn31170_reg ( .D(z3117_assgn3117), .CK(clk), 
        .Q(z3117_assgn31170) );
  DFF_X1 z1302_assgn1302_reg ( .D(z3117_assgn31170), .CK(clk), 
        .Q(z1302_assgn1302) );
  DFF_X1 v10_HPC226_reg ( .D(z31_assgn31), .CK(clk), .Q(v10_HPC226) );
  DFF_X1 w10_HPC226_reg ( .D(N55), .CK(clk), .Q(w10_HPC226) );
  DFF_X1 z1311_assgn1311_reg ( .D(z3129_assgn31291), .CK(clk), 
        .Q(z1311_assgn1311) );
  DFF_X1 u00_HPC226_reg_reg ( .D(u00_HPC226), .CK(clk), .Q(u00_HPC226_reg) );
  DFF_X1 u11_HPC226_reg_reg ( .D(u11_HPC226), .CK(clk), .Q(u11_HPC226_reg) );
  DFF_X1 Y1_1_reg ( .D(n847), .CK(clk), .Q(Y1_1) );
  DFF_X1 Y4_1_reg ( .D(N75), .CK(clk), .Q(Y4_1) );
  DFF_X1 Y3_1_reg ( .D(N73), .CK(clk), .Q(Y3_1) );
  DFF_X1 Y0_1_reg ( .D(N69), .CK(clk), .Q(Y0_1) );
  DFF_X1 z1317_assgn1317_reg ( .D(z3137_assgn31371), .CK(clk), 
        .Q(z1317_assgn1317) );
  DFF_X1 temp_hpc2o_v_1_order0_HPC2o27_reg ( 
        .D(xor_br_hpc2o_v_1_order0_HPC2o27), .CK(clk), .Q(z3155_assgn3155) );
  DFF_X1 z3155_assgn31550_reg ( .D(z3155_assgn3155), .CK(clk), 
        .Q(z3155_assgn31550) );
  DFF_X1 z1334_assgn1334_reg ( .D(z3155_assgn31550), .CK(clk), 
        .Q(z1334_assgn1334) );
  DFF_X1 v01_HPC2o27_reg ( .D(and_ta_hpc2o_v_1_order0_HPC2o27), .CK(clk), 
        .Q(v01_HPC2o27) );
  DFF_X1 w01_HPC2o27_reg ( .D(n842), .CK(clk), .Q(w01_HPC2o27) );
  DFF_X1 z1339_assgn1339_reg ( .D(z3163_assgn31631), .CK(clk), 
        .Q(z1339_assgn1339) );
  DFF_X1 temp_hpc2o_v_1_order1_HPC2o27_reg ( 
        .D(xor_br_hpc2o_v_1_order1_HPC2o27), .CK(clk), .Q(z3181_assgn3181) );
  DFF_X1 z3181_assgn31810_reg ( .D(z3181_assgn3181), .CK(clk), 
        .Q(z3181_assgn31810) );
  DFF_X1 z1356_assgn1356_reg ( .D(z3181_assgn31810), .CK(clk), 
        .Q(z1356_assgn1356) );
  DFF_X1 v10_HPC2o27_reg ( .D(and_ta_hpc2o_v_1_order1_HPC2o27), .CK(clk), 
        .Q(v10_HPC2o27) );
  DFF_X1 w10_HPC2o27_reg ( .D(n841), .CK(clk), .Q(w10_HPC2o27) );
  DFF_X1 z1365_assgn1365_reg ( .D(z3193_assgn31931), .CK(clk), 
        .Q(z1365_assgn1365) );
  DFF_X1 temp_hpc2_v_1_order0_HPC228_reg ( .D(N56), .CK(clk), 
        .Q(z3199_assgn3199) );
  DFF_X1 z3199_assgn31990_reg ( .D(z3199_assgn3199), .CK(clk), 
        .Q(z3199_assgn31990) );
  DFF_X1 z1370_assgn1370_reg ( .D(z3199_assgn31990), .CK(clk), 
        .Q(z1370_assgn1370) );
  DFF_X1 v01_HPC228_reg ( .D(z33_assgn33), .CK(clk), .Q(v01_HPC228) );
  DFF_X1 w01_HPC228_reg ( .D(N57), .CK(clk), .Q(w01_HPC228) );
  DFF_X1 temp_hpc2_v_1_order1_HPC228_reg ( .D(N58), .CK(clk), 
        .Q(z3213_assgn3213) );
  DFF_X1 z3213_assgn32130_reg ( .D(z3213_assgn3213), .CK(clk), 
        .Q(z3213_assgn32130) );
  DFF_X1 z1382_assgn1382_reg ( .D(z3213_assgn32130), .CK(clk), 
        .Q(z1382_assgn1382) );
  DFF_X1 v10_HPC228_reg ( .D(z35_assgn35), .CK(clk), .Q(v10_HPC228) );
  DFF_X1 w10_HPC228_reg ( .D(N59), .CK(clk), .Q(w10_HPC228) );
  DFF_X1 z1391_assgn1391_reg ( .D(z3225_assgn32251), .CK(clk), 
        .Q(z1391_assgn1391) );
  DFF_X1 u00_HPC228_reg_reg ( .D(u00_HPC228), .CK(clk), .Q(u00_HPC228_reg) );
  DFF_X1 w01_HPC2o24_reg ( .D(n843), .CK(clk), .Q(w01_HPC2o24) );
  DFF_X1 w01_HPC2o33_reg ( .D(n837), .CK(clk), .Q(w01_HPC2o33) );
  DFF_X1 u11_HPC228_reg_reg ( .D(u11_HPC228), .CK(clk), .Q(u11_HPC228_reg) );
  DFF_X1 w10_HPC2o24_reg ( .D(n844), .CK(clk), .Q(w10_HPC2o24) );
  DFF_X1 w10_HPC2o33_reg ( .D(n838), .CK(clk), .Q(w10_HPC2o33) );
  DFF_X1 z1397_assgn1397_reg ( .D(z3233_assgn32331), .CK(clk), 
        .Q(z1397_assgn1397) );
  DFF_X1 temp_hpc2o_v_1_order0_HPC2o29_reg ( 
        .D(xor_br_hpc2o_v_1_order0_HPC2o29), .CK(clk), .Q(z3251_assgn3251) );
  DFF_X1 z3251_assgn32510_reg ( .D(z3251_assgn3251), .CK(clk), 
        .Q(z3251_assgn32510) );
  DFF_X1 z1414_assgn1414_reg ( .D(z3251_assgn32510), .CK(clk), 
        .Q(z1414_assgn1414) );
  DFF_X1 v01_HPC2o29_reg ( .D(and_ta_hpc2o_v_1_order0_HPC2o29), .CK(clk), 
        .Q(v01_HPC2o29) );
  DFF_X1 w01_HPC2o29_reg ( .D(n846), .CK(clk), .Q(w01_HPC2o29) );
  DFF_X1 z1419_assgn1419_reg ( .D(z3259_assgn32591), .CK(clk), 
        .Q(z1419_assgn1419) );
  DFF_X1 temp_hpc2o_v_1_order1_HPC2o29_reg ( 
        .D(xor_br_hpc2o_v_1_order1_HPC2o29), .CK(clk), .Q(z3277_assgn3277) );
  DFF_X1 z3277_assgn32770_reg ( .D(z3277_assgn3277), .CK(clk), 
        .Q(z3277_assgn32770) );
  DFF_X1 z1436_assgn1436_reg ( .D(z3277_assgn32770), .CK(clk), 
        .Q(z1436_assgn1436) );
  DFF_X1 v10_HPC2o29_reg ( .D(and_ta_hpc2o_v_1_order1_HPC2o29), .CK(clk), 
        .Q(v10_HPC2o29) );
  DFF_X1 w10_HPC2o29_reg ( .D(n845), .CK(clk), .Q(w10_HPC2o29) );
  DFF_X1 Y7_1_reg ( .D(n849), .CK(clk), .Q(Y7_1) );
  DFF_X1 Y6_1_reg ( .D(n848), .CK(clk), .Q(Y6_1) );
  DFF_X1 z1445_assgn1445_reg ( .D(z3289_assgn32891), .CK(clk), 
        .Q(z1445_assgn1445) );
  DFF_X1 temp_hpc2o_v_1_order0_HPC2o30_reg ( 
        .D(xor_br_hpc2o_v_1_order0_HPC2o30), .CK(clk), .Q(z3307_assgn3307) );
  DFF_X1 z3307_assgn33070_reg ( .D(z3307_assgn3307), .CK(clk), 
        .Q(z3307_assgn33070) );
  DFF_X1 z1462_assgn1462_reg ( .D(z3307_assgn33070), .CK(clk), 
        .Q(z1462_assgn1462) );
  DFF_X1 v01_HPC2o30_reg ( .D(and_ta_hpc2o_v_1_order0_HPC2o30), .CK(clk), 
        .Q(v01_HPC2o30) );
  DFF_X1 w01_HPC2o30_reg ( .D(n840), .CK(clk), .Q(w01_HPC2o30) );
  DFF_X1 z1467_assgn1467_reg ( .D(z3315_assgn33151), .CK(clk), 
        .Q(z1467_assgn1467) );
  DFF_X1 temp_hpc2o_v_1_order1_HPC2o30_reg ( 
        .D(xor_br_hpc2o_v_1_order1_HPC2o30), .CK(clk), .Q(z3333_assgn3333) );
  DFF_X1 z3333_assgn33330_reg ( .D(z3333_assgn3333), .CK(clk), 
        .Q(z3333_assgn33330) );
  DFF_X1 z1484_assgn1484_reg ( .D(z3333_assgn33330), .CK(clk), 
        .Q(z1484_assgn1484) );
  DFF_X1 v10_HPC2o30_reg ( .D(and_ta_hpc2o_v_1_order1_HPC2o30), .CK(clk), 
        .Q(v10_HPC2o30) );
  DFF_X1 w10_HPC2o30_reg ( .D(n839), .CK(clk), .Q(w10_HPC2o30) );
  DFF_X1 Y2_1_reg ( .D(n850), .CK(clk), .Q(Y2_1) );
  DFF_X1 Y5_1_reg ( .D(N77), .CK(clk), .Q(Y5_1) );
  DFF_X1 z1493_assgn1493_reg ( .D(z3345_assgn33451), .CK(clk), 
        .Q(z1493_assgn1493) );
  DFF_X1 u00_HPC231_reg_reg ( .D(u00_HPC231), .CK(clk), .Q(u00_HPC231_reg) );
  DFF_X1 temp_hpc2_v_1_order0_HPC231_reg ( .D(N60), .CK(clk), 
        .Q(z3351_assgn3351) );
  DFF_X1 z3351_assgn33510_reg ( .D(z3351_assgn3351), .CK(clk), 
        .Q(z3351_assgn33510) );
  DFF_X1 z1498_assgn1498_reg ( .D(z3351_assgn33510), .CK(clk), 
        .Q(z1498_assgn1498) );
  DFF_X1 v01_HPC231_reg ( .D(z37_assgn37), .CK(clk), .Q(v01_HPC231) );
  DFF_X1 w01_HPC231_reg ( .D(N61), .CK(clk), .Q(w01_HPC231) );
  DFF_X1 w01_HPC2o19_reg ( .D(n830), .CK(clk), .Q(w01_HPC2o19) );
  DFF_X1 Y2_0_reg ( .D(temp2_0), .CK(clk), .Q(Y2_0) );
  DFF_X1 Y7_0_reg ( .D(temp4_0), .CK(clk), .Q(Y7_0) );
  DFF_X1 Y1_0_reg ( .D(temp1_0), .CK(clk), .Q(Y1_0) );
  DFF_X1 Y6_0_reg ( .D(temp3_0), .CK(clk), .Q(Y6_0) );
  DFF_X1 Y4_0_reg ( .D(N74), .CK(clk), .Q(Y4_0) );
  DFF_X1 Y5_0_reg ( .D(N76), .CK(clk), .Q(Y5_0) );
  DFF_X1 Y3_0_reg ( .D(N72), .CK(clk), .Q(Y3_0) );
  DFF_X1 Y0_0_reg ( .D(N68), .CK(clk), .Q(Y0_0) );
  XOR2_X1 U1389 ( .A(n948), .B(w10_HPC2o_swapped15), .Z(n1271) );
  XOR2_X1 U1390 ( .A(n947), .B(w01_HPC2o_swapped15), .Z(n1277) );
  XNOR2_X1 U1391 ( .A(X0_1), .B(X3_1), .ZN(n1131) );
  XNOR2_X1 U1392 ( .A(X0_0), .B(X3_0), .ZN(n1137) );
  XOR2_X1 U1393 ( .A(X0_1), .B(X5_1), .Z(n861) );
  XOR2_X1 U1394 ( .A(X4_1), .B(X6_1), .Z(n898) );
  XNOR2_X1 U1395 ( .A(n898), .B(X5_1), .ZN(n1133) );
  XNOR2_X1 U1396 ( .A(X2_1), .B(n1133), .ZN(n865) );
  XNOR2_X1 U1397 ( .A(X0_1), .B(X6_1), .ZN(n979) );
  INV_X1 U1398 ( .A(n979), .ZN(n880) );
  AND2_X1 U1399 ( .A1(n865), .A2(n880), .ZN(u11_HPC33) );
  XOR2_X1 U1400 ( .A(X4_0), .B(X6_0), .Z(n897) );
  XNOR2_X1 U1401 ( .A(n897), .B(X5_0), .ZN(n1139) );
  XNOR2_X1 U1402 ( .A(X2_0), .B(n1139), .ZN(n864) );
  XNOR2_X1 U1403 ( .A(X0_0), .B(X6_0), .ZN(n978) );
  INV_X1 U1404 ( .A(n978), .ZN(n895) );
  AND2_X1 U1405 ( .A1(n864), .A2(n895), .ZN(u00_HPC33) );
  INV_X1 U1406 ( .A(n1137), .ZN(n853) );
  INV_X1 U1407 ( .A(n1131), .ZN(n854) );
  XOR2_X1 U1408 ( .A(X5_1), .B(n1131), .Z(n1096) );
  XOR2_X1 U1409 ( .A(X6_1), .B(n1096), .Z(n1127) );
  INV_X1 U1410 ( .A(n1127), .ZN(n881) );
  XOR2_X1 U1411 ( .A(X5_0), .B(n1137), .Z(n1110) );
  XOR2_X1 U1412 ( .A(X6_0), .B(n1110), .Z(n1129) );
  INV_X1 U1413 ( .A(n1129), .ZN(n896) );
  XOR2_X1 U1414 ( .A(X1_1), .B(n1133), .Z(n1136) );
  INV_X1 U1415 ( .A(n1136), .ZN(n859) );
  XOR2_X1 U1416 ( .A(n897), .B(n1137), .Z(n1142) );
  INV_X1 U1417 ( .A(n1142), .ZN(n857) );
  XOR2_X1 U1418 ( .A(X1_0), .B(n1139), .Z(n1144) );
  INV_X1 U1419 ( .A(n1144), .ZN(n860) );
  XOR2_X1 U1420 ( .A(n898), .B(n1131), .Z(n1135) );
  INV_X1 U1421 ( .A(n1135), .ZN(n858) );
  XOR2_X1 U1422 ( .A(v10_HPC2o11), .B(w10_HPC2o11), .Z(n899) );
  XOR2_X1 U1423 ( .A(z892_assgn892), .B(n899), .Z(n1287) );
  AND2_X1 U1424 ( .A1(X7_1), .A2(n1287), .ZN(u11_HPC218) );
  XOR2_X1 U1425 ( .A(v01_HPC2o11), .B(w01_HPC2o11), .Z(n900) );
  XOR2_X1 U1426 ( .A(z890_assgn890), .B(n900), .Z(n1293) );
  AND2_X1 U1427 ( .A1(X7_0), .A2(n1293), .ZN(u00_HPC218) );
  XOR2_X1 U1428 ( .A(X0_0), .B(X5_0), .Z(n862) );
  XOR2_X1 U1429 ( .A(u11_HPC36_reg), .B(w10_HPC36), .Z(n902) );
  NAND2_X1 U1430 ( .A1(temp_hpc3_v_1_order1_HPC36), .A2(T1_1_reg), .ZN(n901)
         );
  XNOR2_X1 U1431 ( .A(n902), .B(n901), .ZN(n911) );
  NAND2_X1 U1432 ( .A1(temp_hpc3o_v_1_order1_HPC3o7), .A2(T4_1_reg), .ZN(n903)
         );
  XOR2_X1 U1433 ( .A(w10_HPC3o7), .B(n903), .Z(n1102) );
  XNOR2_X1 U1434 ( .A(n911), .B(n1102), .ZN(n1097) );
  XOR2_X1 U1435 ( .A(u11_HPC30_reg), .B(w10_HPC30), .Z(n905) );
  NAND2_X1 U1436 ( .A1(temp_hpc3_v_1_order1_HPC30), .A2(T13_1_reg), .ZN(n904)
         );
  XNOR2_X1 U1437 ( .A(n905), .B(n904), .ZN(n983) );
  XOR2_X1 U1438 ( .A(T14_1_reg), .B(w10_HPC3o1), .Z(n907) );
  NAND2_X1 U1439 ( .A1(temp_hpc3o_v_1_order1_HPC3o1), .A2(T23_1_reg), 
        .ZN(n906) );
  XNOR2_X1 U1440 ( .A(n907), .B(n906), .ZN(n1100) );
  XNOR2_X1 U1441 ( .A(n983), .B(n1100), .ZN(n995) );
  XOR2_X1 U1442 ( .A(n1097), .B(n995), .Z(n966) );
  INV_X1 U1443 ( .A(n966), .ZN(n883) );
  XOR2_X1 U1444 ( .A(u11_HPC33_reg), .B(w10_HPC33), .Z(n909) );
  NAND2_X1 U1445 ( .A1(temp_hpc3_v_1_order1_HPC33), .A2(T3_1_reg), .ZN(n908)
         );
  XNOR2_X1 U1446 ( .A(n909), .B(n908), .ZN(n1012) );
  NAND2_X1 U1447 ( .A1(temp_hpc3o_v_1_order1_HPC3o8), .A2(T2_1_reg), .ZN(n910)
         );
  XOR2_X1 U1448 ( .A(w10_HPC3o8), .B(n910), .Z(n1103) );
  XNOR2_X1 U1449 ( .A(n911), .B(n1103), .ZN(n1090) );
  XNOR2_X1 U1450 ( .A(n1012), .B(n1090), .ZN(n913) );
  NAND2_X1 U1451 ( .A1(temp_hpc3o_v_1_order1_HPC3o5), .A2(T20_1_reg), 
        .ZN(n912) );
  XNOR2_X1 U1452 ( .A(n912), .B(w10_HPC3o5), .ZN(n1013) );
  XOR2_X1 U1453 ( .A(n1013), .B(T25_1_reg), .Z(n1105) );
  XNOR2_X1 U1454 ( .A(n913), .B(n1105), .ZN(n886) );
  AND2_X1 U1455 ( .A1(n883), .A2(n886), .ZN(u11_HPC312) );
  XOR2_X1 U1456 ( .A(u00_HPC36_reg), .B(w01_HPC36), .Z(n915) );
  NAND2_X1 U1457 ( .A1(temp_hpc3_v_1_order0_HPC36), .A2(T1_0_reg), .ZN(n914)
         );
  XNOR2_X1 U1458 ( .A(n915), .B(n914), .ZN(n924) );
  NAND2_X1 U1459 ( .A1(temp_hpc3o_v_1_order0_HPC3o7), .A2(T4_0_reg), .ZN(n916)
         );
  XOR2_X1 U1460 ( .A(w01_HPC3o7), .B(n916), .Z(n1116) );
  XNOR2_X1 U1461 ( .A(n924), .B(n1116), .ZN(n1111) );
  XOR2_X1 U1462 ( .A(u00_HPC30_reg), .B(w01_HPC30), .Z(n918) );
  NAND2_X1 U1463 ( .A1(temp_hpc3_v_1_order0_HPC30), .A2(T13_0_reg), .ZN(n917)
         );
  XNOR2_X1 U1464 ( .A(n918), .B(n917), .ZN(n988) );
  XOR2_X1 U1465 ( .A(T14_0_reg), .B(w01_HPC3o1), .Z(n920) );
  NAND2_X1 U1466 ( .A1(temp_hpc3o_v_1_order0_HPC3o1), .A2(T23_0_reg), 
        .ZN(n919) );
  XNOR2_X1 U1467 ( .A(n920), .B(n919), .ZN(n1114) );
  XNOR2_X1 U1468 ( .A(n988), .B(n1114), .ZN(n998) );
  XOR2_X1 U1469 ( .A(n1111), .B(n998), .Z(n968) );
  INV_X1 U1470 ( .A(n968), .ZN(n887) );
  XOR2_X1 U1471 ( .A(u00_HPC33_reg), .B(w01_HPC33), .Z(n922) );
  NAND2_X1 U1472 ( .A1(temp_hpc3_v_1_order0_HPC33), .A2(T3_0_reg), .ZN(n921)
         );
  XNOR2_X1 U1473 ( .A(n922), .B(n921), .ZN(n1004) );
  NAND2_X1 U1474 ( .A1(temp_hpc3o_v_1_order0_HPC3o8), .A2(T2_0_reg), .ZN(n923)
         );
  XOR2_X1 U1475 ( .A(w01_HPC3o8), .B(n923), .Z(n1117) );
  XNOR2_X1 U1476 ( .A(n924), .B(n1117), .ZN(n1093) );
  XNOR2_X1 U1477 ( .A(n1004), .B(n1093), .ZN(n926) );
  NAND2_X1 U1478 ( .A1(temp_hpc3o_v_1_order0_HPC3o5), .A2(T20_0_reg), 
        .ZN(n925) );
  XOR2_X1 U1479 ( .A(w01_HPC3o5), .B(n925), .Z(n1008) );
  XNOR2_X1 U1480 ( .A(T25_0_reg), .B(n1008), .ZN(n1119) );
  XNOR2_X1 U1481 ( .A(n926), .B(n1119), .ZN(n894) );
  AND2_X1 U1482 ( .A1(n887), .A2(n894), .ZN(u00_HPC312) );
  NAND2_X1 U1483 ( .A1(temp_hpc3o_v_1_order0_HPC3o2), .A2(T19_0_reg), 
        .ZN(n927) );
  XOR2_X1 U1484 ( .A(w01_HPC3o2), .B(n927), .Z(n991) );
  XNOR2_X1 U1485 ( .A(T24_0_reg), .B(n991), .ZN(n1115) );
  XNOR2_X1 U1486 ( .A(n1115), .B(n988), .ZN(n928) );
  XNOR2_X1 U1487 ( .A(n928), .B(n1093), .ZN(n851) );
  XOR2_X1 U1488 ( .A(T26_0_reg), .B(w01_HPC3o4), .Z(n930) );
  NAND2_X1 U1489 ( .A1(temp_hpc3o_v_1_order0_HPC3o4), .A2(T22_0_reg), 
        .ZN(n929) );
  XNOR2_X1 U1490 ( .A(n930), .B(n929), .ZN(n1120) );
  XNOR2_X1 U1491 ( .A(n1004), .B(n1120), .ZN(n1001) );
  XOR2_X1 U1492 ( .A(n1111), .B(n1001), .Z(n1123) );
  INV_X1 U1493 ( .A(n1123), .ZN(n888) );
  AND2_X1 U1494 ( .A1(n851), .A2(n888), .ZN(u00_HPC314) );
  NAND2_X1 U1495 ( .A1(temp_hpc3o_v_1_order1_HPC3o2), .A2(T19_1_reg), 
        .ZN(n931) );
  XOR2_X1 U1496 ( .A(w10_HPC3o2), .B(n931), .Z(n986) );
  XNOR2_X1 U1497 ( .A(T24_1_reg), .B(n986), .ZN(n1101) );
  XNOR2_X1 U1498 ( .A(n1101), .B(n983), .ZN(n932) );
  XNOR2_X1 U1499 ( .A(n932), .B(n1090), .ZN(n852) );
  XOR2_X1 U1500 ( .A(T26_1_reg), .B(w10_HPC3o4), .Z(n934) );
  NAND2_X1 U1501 ( .A1(temp_hpc3o_v_1_order1_HPC3o4), .A2(T22_1_reg), 
        .ZN(n933) );
  XNOR2_X1 U1502 ( .A(n934), .B(n933), .ZN(n1106) );
  XNOR2_X1 U1503 ( .A(n1012), .B(n1106), .ZN(n1009) );
  XOR2_X1 U1504 ( .A(n1097), .B(n1009), .Z(n1109) );
  INV_X1 U1505 ( .A(n1109), .ZN(n884) );
  AND2_X1 U1506 ( .A1(n852), .A2(n884), .ZN(u11_HPC314) );
  XOR2_X1 U1507 ( .A(u00_HPC312_reg), .B(w01_HPC312), .Z(n936) );
  NAND2_X1 U1508 ( .A1(M20_0_reg), .A2(temp_hpc3_v_1_order0_HPC312), .ZN(n935)
         );
  XOR2_X1 U1509 ( .A(n936), .B(n935), .Z(n1233) );
  INV_X1 U1510 ( .A(n1233), .ZN(n1234) );
  AND2_X1 U1511 ( .A1(n1234), .A2(temp_hpc2osw_v_1_order0_HPC2o_swapped13), 
        .ZN(and_ta_hpc2osw_v_1_order0_HPC2o_swapped13) );
  XOR2_X1 U1512 ( .A(u11_HPC312_reg), .B(w10_HPC312), .Z(n938) );
  NAND2_X1 U1513 ( .A1(M20_1_reg), .A2(temp_hpc3_v_1_order1_HPC312), .ZN(n937)
         );
  XOR2_X1 U1514 ( .A(n938), .B(n937), .Z(n1239) );
  INV_X1 U1515 ( .A(n1239), .ZN(n1240) );
  AND2_X1 U1516 ( .A1(n1240), .A2(temp_hpc2osw_v_1_order1_HPC2o_swapped13), 
        .ZN(and_ta_hpc2osw_v_1_order1_HPC2o_swapped13) );
  NAND2_X1 U1517 ( .A1(temp_hpc3_v_1_order1_HPC314), .A2(M21_1_reg), .ZN(n939)
         );
  XNOR2_X1 U1518 ( .A(n939), .B(w10_HPC314), .ZN(n940) );
  XOR2_X1 U1519 ( .A(u11_HPC314_reg), .B(n940), .Z(n1251) );
  AND2_X1 U1520 ( .A1(n1251), .A2(temp_hpc2osw_v_1_order1_HPC2o_swapped15), 
        .ZN(and_ta_hpc2osw_v_1_order1_HPC2o_swapped15) );
  NAND2_X1 U1521 ( .A1(temp_hpc3_v_1_order0_HPC314), .A2(M21_0_reg), .ZN(n941)
         );
  XNOR2_X1 U1522 ( .A(n941), .B(w01_HPC314), .ZN(n942) );
  XOR2_X1 U1523 ( .A(u00_HPC314_reg), .B(n942), .Z(n1246) );
  AND2_X1 U1524 ( .A1(n1246), .A2(temp_hpc2osw_v_1_order0_HPC2o_swapped15), 
        .ZN(and_ta_hpc2osw_v_1_order0_HPC2o_swapped15) );
  AND2_X1 U1525 ( .A1(n1287), .A2(z1014_assgn1014), .ZN(z7_assgn7) );
  AND2_X1 U1526 ( .A1(n1293), .A2(z1002_assgn1002), .ZN(z5_assgn5) );
  AND2_X1 U1527 ( .A1(n1287), .A2(z1356_assgn1356), 
        .ZN(and_ta_hpc2o_v_1_order1_HPC2o27) );
  AND2_X1 U1528 ( .A1(n1293), .A2(z1334_assgn1334), 
        .ZN(and_ta_hpc2o_v_1_order0_HPC2o27) );
  XOR2_X1 U1529 ( .A(M33_0_reg), .B(v01_HPC2o_swapped13), .Z(n943) );
  XOR2_X1 U1530 ( .A(w01_HPC2o_swapped13), .B(n943), .Z(n1237) );
  AND2_X1 U1531 ( .A1(n1237), .A2(z1082_assgn1082), .ZN(z9_assgn9) );
  XOR2_X1 U1532 ( .A(M33_1_reg), .B(v10_HPC2o_swapped13), .Z(n944) );
  XOR2_X1 U1533 ( .A(w10_HPC2o_swapped13), .B(n944), .Z(n1243) );
  AND2_X1 U1534 ( .A1(n1243), .A2(z1094_assgn1094), .ZN(z11_assgn11) );
  AND2_X1 U1535 ( .A1(n1237), .A2(z1077_assgn1077), .ZN(u00_HPC220) );
  AND2_X1 U1536 ( .A1(n1237), .A2(z1414_assgn1414), 
        .ZN(and_ta_hpc2o_v_1_order0_HPC2o29) );
  AND2_X1 U1537 ( .A1(n1243), .A2(z1103_assgn1103), .ZN(u11_HPC220) );
  AND2_X1 U1538 ( .A1(n1243), .A2(z1436_assgn1436), 
        .ZN(and_ta_hpc2o_v_1_order1_HPC2o29) );
  XOR2_X1 U1539 ( .A(z882_assgn882), .B(v01_HPC2o10), .Z(n945) );
  XOR2_X1 U1540 ( .A(w01_HPC2o10), .B(n945), .Z(n1231) );
  AND2_X1 U1541 ( .A1(n1231), .A2(z1109_assgn1109), .ZN(u00_HPC221) );
  XOR2_X1 U1542 ( .A(z884_assgn884), .B(v10_HPC2o10), .Z(n946) );
  XOR2_X1 U1543 ( .A(w10_HPC2o10), .B(n946), .Z(n1225) );
  AND2_X1 U1544 ( .A1(n1225), .A2(z1126_assgn1126), .ZN(z15_assgn15) );
  AND2_X1 U1545 ( .A1(n1225), .A2(z1484_assgn1484), 
        .ZN(and_ta_hpc2o_v_1_order1_HPC2o30) );
  AND2_X1 U1546 ( .A1(n1231), .A2(z1462_assgn1462), 
        .ZN(and_ta_hpc2o_v_1_order0_HPC2o30) );
  AND2_X1 U1547 ( .A1(n1231), .A2(z1114_assgn1114), .ZN(z13_assgn13) );
  AND2_X1 U1548 ( .A1(n1225), .A2(z1135_assgn1135), .ZN(u11_HPC221) );
  XNOR2_X1 U1549 ( .A(M36_0_reg), .B(v01_HPC2o_swapped15), .ZN(n947) );
  INV_X1 U1550 ( .A(n1277), .ZN(n1278) );
  AND2_X1 U1551 ( .A1(n1278), .A2(z1285_assgn1285), .ZN(u00_HPC226) );
  XNOR2_X1 U1552 ( .A(M36_1_reg), .B(v10_HPC2o_swapped15), .ZN(n948) );
  INV_X1 U1553 ( .A(n1271), .ZN(n1272) );
  AND2_X1 U1554 ( .A1(n1272), .A2(z1302_assgn1302), .ZN(z31_assgn31) );
  AND2_X1 U1555 ( .A1(n1272), .A2(z1311_assgn1311), .ZN(u11_HPC226) );
  AND2_X1 U1556 ( .A1(n1278), .A2(z1290_assgn1290), .ZN(z29_assgn29) );
  AND2_X1 U1557 ( .A1(n1272), .A2(z988_assgn988), 
        .ZN(and_ta_hpc2o_v_1_order1_HPC2o17) );
  AND2_X1 U1558 ( .A1(n1278), .A2(z966_assgn966), 
        .ZN(and_ta_hpc2o_v_1_order0_HPC2o17) );
  XOR2_X1 U1559 ( .A(u00_HPC39_reg), .B(w01_HPC39), .Z(n950) );
  NAND2_X1 U1560 ( .A1(M22_0_reg), .A2(temp_hpc3_v_1_order0_HPC39), .ZN(n949)
         );
  XNOR2_X1 U1561 ( .A(n950), .B(n949), .ZN(n981) );
  XOR2_X1 U1562 ( .A(n981), .B(M21_0_reg), .Z(n1290) );
  AND2_X1 U1563 ( .A1(n1290), .A2(temp_hpc2o_v_1_order0_HPC2o11), 
        .ZN(and_ta_hpc2o_v_1_order0_HPC2o11) );
  XOR2_X1 U1564 ( .A(u11_HPC39_reg), .B(w10_HPC39), .Z(n952) );
  NAND2_X1 U1565 ( .A1(M22_1_reg), .A2(temp_hpc3_v_1_order1_HPC39), .ZN(n951)
         );
  XNOR2_X1 U1566 ( .A(n952), .B(n951), .ZN(n982) );
  XOR2_X1 U1567 ( .A(n982), .B(z2625_assgn26250), .Z(n1222) );
  AND2_X1 U1568 ( .A1(n1222), .A2(temp_hpc2o_v_1_order1_HPC2o10), 
        .ZN(and_ta_hpc2o_v_1_order1_HPC2o10) );
  XOR2_X1 U1569 ( .A(n981), .B(z2621_assgn26210), .Z(n1228) );
  AND2_X1 U1570 ( .A1(n1228), .A2(temp_hpc2o_v_1_order0_HPC2o10), 
        .ZN(and_ta_hpc2o_v_1_order0_HPC2o10) );
  XOR2_X1 U1571 ( .A(n982), .B(M21_1_reg), .Z(n1284) );
  AND2_X1 U1572 ( .A1(n1284), .A2(temp_hpc2o_v_1_order1_HPC2o11), 
        .ZN(and_ta_hpc2o_v_1_order1_HPC2o11) );
  XNOR2_X1 U1573 ( .A(n1277), .B(n1237), .ZN(n1216) );
  AND2_X1 U1574 ( .A1(n1216), .A2(z1574_assgn1574), 
        .ZN(and_ta_hpc2o_v_1_order0_HPC2o33) );
  AND2_X1 U1575 ( .A1(n1216), .A2(z1222_assgn1222), 
        .ZN(and_ta_hpc2o_v_1_order0_HPC2o24) );
  XNOR2_X1 U1576 ( .A(n1271), .B(n1243), .ZN(n1209) );
  AND2_X1 U1577 ( .A1(n1209), .A2(z1596_assgn1596), 
        .ZN(and_ta_hpc2o_v_1_order1_HPC2o33) );
  AND2_X1 U1578 ( .A1(n1209), .A2(z1244_assgn1244), 
        .ZN(and_ta_hpc2o_v_1_order1_HPC2o24) );
  XNOR2_X1 U1579 ( .A(n1243), .B(n1225), .ZN(n1263) );
  INV_X1 U1580 ( .A(n1263), .ZN(n1264) );
  AND2_X1 U1581 ( .A1(n1264), .A2(z1068_assgn1068), 
        .ZN(and_ta_hpc2o_v_1_order1_HPC2o19) );
  XNOR2_X1 U1582 ( .A(n1237), .B(n1231), .ZN(n1256) );
  INV_X1 U1583 ( .A(n1256), .ZN(n1255) );
  AND2_X1 U1584 ( .A1(n1255), .A2(z1046_assgn1046), 
        .ZN(and_ta_hpc2o_v_1_order0_HPC2o19) );
  AND2_X1 U1585 ( .A1(n1264), .A2(z1382_assgn1382), .ZN(z35_assgn35) );
  AND2_X1 U1586 ( .A1(n1255), .A2(z1365_assgn1365), .ZN(u00_HPC228) );
  AND2_X1 U1587 ( .A1(n1255), .A2(z1370_assgn1370), .ZN(z33_assgn33) );
  AND2_X1 U1588 ( .A1(n1264), .A2(z1391_assgn1391), .ZN(u11_HPC228) );
  INV_X1 U1589 ( .A(n1225), .ZN(n1204) );
  INV_X1 U1590 ( .A(n1287), .ZN(n1192) );
  XOR2_X1 U1591 ( .A(n1204), .B(n1192), .Z(n962) );
  AND2_X1 U1592 ( .A1(n962), .A2(z1167_assgn1167), .ZN(u11_HPC222) );
  INV_X1 U1593 ( .A(n1231), .ZN(n1199) );
  INV_X1 U1594 ( .A(n1293), .ZN(n1183) );
  XOR2_X1 U1595 ( .A(n1199), .B(n1183), .Z(n955) );
  AND2_X1 U1596 ( .A1(n955), .A2(z1493_assgn1493), .ZN(u00_HPC231) );
  AND2_X1 U1597 ( .A1(n962), .A2(z1519_assgn1519), .ZN(u11_HPC231) );
  AND2_X1 U1598 ( .A1(n962), .A2(z1510_assgn1510), .ZN(z39_assgn39) );
  AND2_X1 U1599 ( .A1(n955), .A2(z1141_assgn1141), .ZN(u00_HPC222) );
  AND2_X1 U1600 ( .A1(n955), .A2(z1146_assgn1146), .ZN(z17_assgn17) );
  AND2_X1 U1601 ( .A1(n962), .A2(z1158_assgn1158), .ZN(z19_assgn19) );
  AND2_X1 U1602 ( .A1(n955), .A2(z1498_assgn1498), .ZN(z37_assgn37) );
  XNOR2_X1 U1603 ( .A(n1277), .B(n1183), .ZN(n953) );
  INV_X1 U1604 ( .A(n953), .ZN(n963) );
  AND2_X1 U1605 ( .A1(n963), .A2(z922_assgn922), .ZN(z1_assgn1) );
  AND2_X1 U1606 ( .A1(n963), .A2(z1253_assgn1253), .ZN(u00_HPC225) );
  XNOR2_X1 U1607 ( .A(n1271), .B(n1192), .ZN(n954) );
  INV_X1 U1608 ( .A(n954), .ZN(n956) );
  AND2_X1 U1609 ( .A1(n956), .A2(z1270_assgn1270), .ZN(z27_assgn27) );
  AND2_X1 U1610 ( .A1(n956), .A2(z934_assgn934), .ZN(z3_assgn3) );
  AND2_X1 U1611 ( .A1(n963), .A2(z1258_assgn1258), .ZN(z25_assgn25) );
  AND2_X1 U1612 ( .A1(n956), .A2(z1279_assgn1279), .ZN(u11_HPC225) );
  AND2_X1 U1613 ( .A1(n963), .A2(z917_assgn917), .ZN(u00_HPC216) );
  AND2_X1 U1614 ( .A1(n956), .A2(z943_assgn943), .ZN(u11_HPC216) );
  XOR2_X1 U1615 ( .A(n1256), .B(n953), .Z(n960) );
  AND2_X1 U1616 ( .A1(n960), .A2(z1525_assgn1525), .ZN(u00_HPC232) );
  XOR2_X1 U1617 ( .A(n1263), .B(n954), .Z(n958) );
  AND2_X1 U1618 ( .A1(n958), .A2(z1190_assgn1190), .ZN(z23_assgn23) );
  AND2_X1 U1619 ( .A1(n958), .A2(z1551_assgn1551), .ZN(u11_HPC232) );
  AND2_X1 U1620 ( .A1(n958), .A2(z1199_assgn1199), .ZN(u11_HPC223) );
  AND2_X1 U1621 ( .A1(n960), .A2(z1173_assgn1173), .ZN(u00_HPC223) );
  AND2_X1 U1622 ( .A1(n960), .A2(z1178_assgn1178), .ZN(z21_assgn21) );
  AND2_X1 U1623 ( .A1(n958), .A2(z1542_assgn1542), .ZN(z43_assgn43) );
  AND2_X1 U1624 ( .A1(n960), .A2(z1530_assgn1530), .ZN(z41_assgn41) );
  XNOR2_X1 U1625 ( .A(X1_0), .B(X2_0), .ZN(n1138) );
  XNOR2_X1 U1626 ( .A(X7_0), .B(n1138), .ZN(n855) );
  XNOR2_X1 U1627 ( .A(X1_1), .B(X2_1), .ZN(n1132) );
  XNOR2_X1 U1628 ( .A(X7_1), .B(n1132), .ZN(n856) );
  NOR2_X1 U1629 ( .A1(n1109), .A2(n966), .ZN(u11_HPC39) );
  NOR2_X1 U1630 ( .A1(n1123), .A2(n968), .ZN(u00_HPC39) );
  INV_X1 U1631 ( .A(rand_44), .ZN(n1128) );
  NOR2_X1 U1632 ( .A1(n955), .A2(n1128), .ZN(N61) );
  INV_X1 U1633 ( .A(rand_38), .ZN(n1130) );
  NOR2_X1 U1634 ( .A1(n956), .A2(n1130), .ZN(N51) );
  INV_X1 U1635 ( .A(rand_35), .ZN(n1145) );
  NOR2_X1 U1636 ( .A1(n955), .A2(n1145), .ZN(N41) );
  INV_X1 U1637 ( .A(rand_29), .ZN(n1141) );
  NOR2_X1 U1638 ( .A1(n956), .A2(n1141), .ZN(N27) );
  INV_X1 U1639 ( .A(rand_36), .ZN(n957) );
  NOR2_X1 U1640 ( .A1(n960), .A2(n957), .ZN(N45) );
  NOR2_X1 U1641 ( .A1(n958), .A2(n957), .ZN(N47) );
  INV_X1 U1642 ( .A(rand_45), .ZN(n959) );
  NOR2_X1 U1643 ( .A1(n958), .A2(n959), .ZN(N67) );
  INV_X1 U1644 ( .A(rand_41), .ZN(n980) );
  NOR2_X1 U1645 ( .A1(n1255), .A2(n980), .ZN(N57) );
  NOR2_X1 U1646 ( .A1(n1264), .A2(n980), .ZN(N59) );
  NOR2_X1 U1647 ( .A1(n960), .A2(n959), .ZN(N65) );
  INV_X1 U1648 ( .A(rand_31), .ZN(n961) );
  NOR2_X1 U1649 ( .A1(n1287), .A2(n961), .ZN(N31) );
  NOR2_X1 U1650 ( .A1(n1293), .A2(n961), .ZN(N29) );
  NOR2_X1 U1651 ( .A1(n962), .A2(n1145), .ZN(N43) );
  NOR2_X1 U1652 ( .A1(n962), .A2(n1128), .ZN(N63) );
  INV_X1 U1653 ( .A(rand_39), .ZN(n1126) );
  NOR2_X1 U1654 ( .A1(n1272), .A2(n1126), .ZN(N55) );
  INV_X1 U1655 ( .A(rand_34), .ZN(n1143) );
  NOR2_X1 U1656 ( .A1(n1231), .A2(n1143), .ZN(N37) );
  NOR2_X1 U1657 ( .A1(n963), .A2(n1141), .ZN(N25) );
  NOR2_X1 U1658 ( .A1(n963), .A2(n1130), .ZN(N49) );
  INV_X1 U1659 ( .A(rand_33), .ZN(n1125) );
  NOR2_X1 U1660 ( .A1(n1243), .A2(n1125), .ZN(N35) );
  NOR2_X1 U1661 ( .A1(n1278), .A2(n1126), .ZN(N53) );
  NOR2_X1 U1662 ( .A1(n1237), .A2(n1125), .ZN(N33) );
  NOR2_X1 U1663 ( .A1(n1225), .A2(n1143), .ZN(N39) );
  NOR2_X1 U1664 ( .A1(n1136), .A2(n1131), .ZN(u11_HPC36) );
  NOR2_X1 U1665 ( .A1(n1144), .A2(n1137), .ZN(u00_HPC36) );
  NOR2_X1 U1666 ( .A1(n1135), .A2(n1127), .ZN(u11_HPC30) );
  NOR2_X1 U1667 ( .A1(n1142), .A2(n1129), .ZN(u00_HPC30) );
  NAND2_X1 U1668 ( .A1(n1109), .A2(rand_19), .ZN(n964) );
  XNOR2_X1 U1669 ( .A(n964), .B(rand_20), .ZN(N15) );
  NAND2_X1 U1670 ( .A1(n1123), .A2(rand_19), .ZN(n965) );
  XNOR2_X1 U1671 ( .A(n965), .B(rand_20), .ZN(N13) );
  NAND2_X1 U1672 ( .A1(n966), .A2(rand_23), .ZN(n967) );
  XNOR2_X1 U1673 ( .A(n967), .B(rand_24), .ZN(N19) );
  NAND2_X1 U1674 ( .A1(n968), .A2(rand_23), .ZN(n969) );
  XNOR2_X1 U1675 ( .A(n969), .B(rand_24), .ZN(N17) );
  INV_X1 U1676 ( .A(rand_26), .ZN(n1124) );
  NOR2_X1 U1677 ( .A1(n852), .A2(n1124), .ZN(n970) );
  XOR2_X1 U1678 ( .A(rand_27), .B(n970), .Z(N23) );
  NOR2_X1 U1679 ( .A1(n851), .A2(n1124), .ZN(n971) );
  XOR2_X1 U1680 ( .A(rand_27), .B(n971), .Z(N21) );
  NAND2_X1 U1681 ( .A1(n1131), .A2(rand_13), .ZN(n972) );
  XNOR2_X1 U1682 ( .A(n972), .B(rand_14), .ZN(N11) );
  NAND2_X1 U1683 ( .A1(n1137), .A2(rand_13), .ZN(n973) );
  XNOR2_X1 U1684 ( .A(n973), .B(rand_14), .ZN(N9) );
  XOR2_X1 U1685 ( .A(X7_0), .B(rand_31), .Z(N30) );
  XOR2_X1 U1686 ( .A(X7_1), .B(rand_31), .Z(N28) );
  NAND2_X1 U1687 ( .A1(n979), .A2(rand_7), .ZN(n974) );
  XNOR2_X1 U1688 ( .A(n974), .B(rand_8), .ZN(N7) );
  NAND2_X1 U1689 ( .A1(n978), .A2(rand_7), .ZN(n975) );
  XNOR2_X1 U1690 ( .A(n975), .B(rand_8), .ZN(N5) );
  NAND2_X1 U1691 ( .A1(n1127), .A2(rand_1), .ZN(n976) );
  XNOR2_X1 U1692 ( .A(n976), .B(rand_2), .ZN(N3) );
  NAND2_X1 U1693 ( .A1(n1129), .A2(rand_1), .ZN(n977) );
  XNOR2_X1 U1694 ( .A(n977), .B(rand_2), .ZN(N1) );
  XOR2_X1 U1695 ( .A(n980), .B(n978), .Z(N58) );
  XOR2_X1 U1696 ( .A(X5_0), .B(X3_0), .Z(n885) );
  XOR2_X1 U1697 ( .A(n885), .B(rand_45), .Z(N66) );
  XOR2_X1 U1698 ( .A(n980), .B(n979), .Z(N56) );
  XOR2_X1 U1699 ( .A(X5_1), .B(X3_1), .Z(n879) );
  XOR2_X1 U1700 ( .A(n879), .B(rand_45), .Z(N64) );
  XOR2_X1 U1701 ( .A(n981), .B(M27_0_reg), .Z(M33_0) );
  XOR2_X1 U1702 ( .A(n981), .B(M24_0_reg), .Z(M36_0) );
  XOR2_X1 U1703 ( .A(n982), .B(M27_1_reg), .Z(M33_1) );
  XOR2_X1 U1704 ( .A(n982), .B(M24_1_reg), .Z(M36_1) );
  XOR2_X1 U1705 ( .A(X7_1), .B(rand_5), .Z(xor_br_hpc3o_v_1_order0_HPC3o2) );
  XOR2_X1 U1706 ( .A(n856), .B(X3_1), .Z(n891) );
  XOR2_X1 U1707 ( .A(n983), .B(rand_6), .Z(n985) );
  NAND2_X1 U1708 ( .A1(xor_br_hpc3o_v_1_order0_HPC3o2), .A2(n891), .ZN(n984)
         );
  XNOR2_X1 U1709 ( .A(n985), .B(n984), .ZN(n987) );
  XNOR2_X1 U1710 ( .A(n987), .B(n986), 
        .ZN(xor_step2_hpc3o_first_half_1_order1_HPC3o2) );
  XOR2_X1 U1711 ( .A(X7_0), .B(rand_5), .Z(xor_br_hpc3o_v_1_order1_HPC3o2) );
  XOR2_X1 U1712 ( .A(n855), .B(X3_0), .Z(n892) );
  XOR2_X1 U1713 ( .A(n988), .B(rand_6), .Z(n990) );
  NAND2_X1 U1714 ( .A1(xor_br_hpc3o_v_1_order1_HPC3o2), .A2(n892), .ZN(n989)
         );
  XNOR2_X1 U1715 ( .A(n990), .B(n989), .ZN(n992) );
  XNOR2_X1 U1716 ( .A(n992), .B(n991), 
        .ZN(xor_step2_hpc3o_first_half_1_order0_HPC3o2) );
  XOR2_X1 U1717 ( .A(n862), .B(rand_46), .Z(xor_br_hpc2o_v_1_order1_HPC2o33)
         );
  XNOR2_X1 U1718 ( .A(X2_0), .B(X4_0), .ZN(n993) );
  XNOR2_X1 U1719 ( .A(n993), .B(n862), .ZN(T26_0) );
  XOR2_X1 U1720 ( .A(n861), .B(rand_46), .Z(xor_br_hpc2o_v_1_order0_HPC2o33)
         );
  XNOR2_X1 U1721 ( .A(X2_1), .B(X4_1), .ZN(n994) );
  XNOR2_X1 U1722 ( .A(n994), .B(n861), .ZN(T26_1) );
  XNOR2_X1 U1723 ( .A(X7_1), .B(n1135), .ZN(n868) );
  XOR2_X1 U1724 ( .A(n868), .B(rand_3), .Z(xor_br_hpc3o_v_1_order0_HPC3o1) );
  XOR2_X1 U1725 ( .A(n856), .B(X6_1), .Z(n863) );
  XOR2_X1 U1726 ( .A(n863), .B(n861), .Z(n889) );
  XNOR2_X1 U1727 ( .A(n995), .B(rand_4), .ZN(n997) );
  NAND2_X1 U1728 ( .A1(xor_br_hpc3o_v_1_order0_HPC3o1), .A2(n889), .ZN(n996)
         );
  XNOR2_X1 U1729 ( .A(n997), .B(n996), 
        .ZN(xor_step2_hpc3o_first_half_1_order1_HPC3o1) );
  XNOR2_X1 U1730 ( .A(X7_0), .B(n1142), .ZN(n870) );
  XOR2_X1 U1731 ( .A(rand_3), .B(n870), .Z(xor_br_hpc3o_v_1_order1_HPC3o1) );
  XOR2_X1 U1732 ( .A(n855), .B(X6_0), .Z(n866) );
  XOR2_X1 U1733 ( .A(n866), .B(n862), .Z(n882) );
  XNOR2_X1 U1734 ( .A(n998), .B(rand_4), .ZN(n1000) );
  NAND2_X1 U1735 ( .A1(xor_br_hpc3o_v_1_order1_HPC3o1), .A2(n882), .ZN(n999)
         );
  XNOR2_X1 U1736 ( .A(n1000), .B(n999), 
        .ZN(xor_step2_hpc3o_first_half_1_order0_HPC3o1) );
  XOR2_X1 U1737 ( .A(n855), .B(rand_9), .Z(xor_br_hpc3o_v_1_order1_HPC3o4) );
  XNOR2_X1 U1738 ( .A(n1001), .B(rand_10), .ZN(n1003) );
  NAND2_X1 U1739 ( .A1(xor_br_hpc3o_v_1_order1_HPC3o4), .A2(n866), .ZN(n1002)
         );
  XNOR2_X1 U1740 ( .A(n1003), .B(n1002), 
        .ZN(xor_step2_hpc3o_first_half_1_order0_HPC3o4) );
  XNOR2_X1 U1741 ( .A(X7_0), .B(n1144), .ZN(n871) );
  XOR2_X1 U1742 ( .A(n871), .B(rand_11), .Z(xor_br_hpc3o_v_1_order1_HPC3o5) );
  XOR2_X1 U1743 ( .A(X0_0), .B(n855), .Z(n890) );
  XOR2_X1 U1744 ( .A(n1004), .B(rand_12), .Z(n1006) );
  NAND2_X1 U1745 ( .A1(xor_br_hpc3o_v_1_order1_HPC3o5), .A2(n890), .ZN(n1005)
         );
  XNOR2_X1 U1746 ( .A(n1006), .B(n1005), .ZN(n1007) );
  XNOR2_X1 U1747 ( .A(n1008), .B(n1007), 
        .ZN(xor_step2_hpc3o_first_half_1_order0_HPC3o5) );
  XOR2_X1 U1748 ( .A(n856), .B(rand_9), .Z(xor_br_hpc3o_v_1_order0_HPC3o4) );
  XNOR2_X1 U1749 ( .A(n1009), .B(rand_10), .ZN(n1011) );
  NAND2_X1 U1750 ( .A1(xor_br_hpc3o_v_1_order0_HPC3o4), .A2(n863), .ZN(n1010)
         );
  XNOR2_X1 U1751 ( .A(n1011), .B(n1010), 
        .ZN(xor_step2_hpc3o_first_half_1_order1_HPC3o4) );
  XNOR2_X1 U1752 ( .A(X7_1), .B(n1136), .ZN(n869) );
  XOR2_X1 U1753 ( .A(rand_11), .B(n869), .Z(xor_br_hpc3o_v_1_order0_HPC3o5) );
  XOR2_X1 U1754 ( .A(X0_1), .B(n856), .Z(n893) );
  XOR2_X1 U1755 ( .A(n1013), .B(n1012), .Z(n1015) );
  NAND2_X1 U1756 ( .A1(xor_br_hpc3o_v_1_order0_HPC3o5), .A2(n893), .ZN(n1014)
         );
  XNOR2_X1 U1757 ( .A(n1015), .B(n1014), .ZN(n1016) );
  XOR2_X1 U1758 ( .A(rand_12), .B(n1016), 
        .Z(xor_step2_hpc3o_first_half_1_order1_HPC3o5) );
  XNOR2_X1 U1759 ( .A(v10_HPC231), .B(w10_HPC231), .ZN(n1017) );
  XNOR2_X1 U1760 ( .A(n1017), .B(u11_HPC231_reg), .ZN(n1270) );
  XOR2_X1 U1761 ( .A(w10_HPC232), .B(v10_HPC232), .Z(n1018) );
  XNOR2_X1 U1762 ( .A(u11_HPC232_reg), .B(n1018), .ZN(n1019) );
  XNOR2_X1 U1763 ( .A(n1270), .B(n1019), .ZN(n1150) );
  XNOR2_X1 U1764 ( .A(v10_HPC226), .B(w10_HPC226), .ZN(n1020) );
  XNOR2_X1 U1765 ( .A(n1020), .B(u11_HPC226_reg), .ZN(n1162) );
  XNOR2_X1 U1766 ( .A(u11_HPC220_reg), .B(v10_HPC220), .ZN(n1021) );
  XNOR2_X1 U1767 ( .A(n1021), .B(w10_HPC220), .ZN(n1158) );
  XNOR2_X1 U1768 ( .A(n1162), .B(n1158), .ZN(n1195) );
  XNOR2_X1 U1769 ( .A(n1150), .B(n1195), .ZN(n1028) );
  XNOR2_X1 U1770 ( .A(u11_HPC218_reg), .B(v10_HPC218), .ZN(n1022) );
  XNOR2_X1 U1771 ( .A(n1022), .B(w10_HPC218), .ZN(n1041) );
  XNOR2_X1 U1772 ( .A(u11_HPC225_reg), .B(v10_HPC225), .ZN(n1023) );
  XNOR2_X1 U1773 ( .A(n1023), .B(w10_HPC225), .ZN(n1031) );
  XNOR2_X1 U1774 ( .A(n1031), .B(v10_HPC2o17), .ZN(n1024) );
  XNOR2_X1 U1775 ( .A(n1024), .B(w10_HPC2o17), .ZN(n1276) );
  XNOR2_X1 U1776 ( .A(n1041), .B(n1276), .ZN(n1026) );
  XOR2_X1 U1777 ( .A(u11_HPC221_reg), .B(v10_HPC221), .Z(n1025) );
  XNOR2_X1 U1778 ( .A(w10_HPC221), .B(n1025), .ZN(n1152) );
  XNOR2_X1 U1779 ( .A(n1026), .B(n1152), .ZN(n1027) );
  XNOR2_X1 U1780 ( .A(n1028), .B(n1027), .ZN(N75) );
  XOR2_X1 U1781 ( .A(v10_HPC2o19), .B(w10_HPC2o19), .Z(n1267) );
  XNOR2_X1 U1782 ( .A(n1267), .B(n1195), .ZN(n1039) );
  XNOR2_X1 U1783 ( .A(n1150), .B(n1039), .ZN(n1030) );
  XOR2_X1 U1784 ( .A(u11_HPC216_reg), .B(v10_HPC216), .Z(n1029) );
  XNOR2_X1 U1785 ( .A(w10_HPC216), .B(n1029), .ZN(n1040) );
  XNOR2_X1 U1786 ( .A(n1276), .B(n1040), .ZN(n1161) );
  XNOR2_X1 U1787 ( .A(n1030), .B(n1161), .ZN(N73) );
  XNOR2_X1 U1788 ( .A(n1039), .B(n1031), .ZN(n1035) );
  XOR2_X1 U1789 ( .A(v10_HPC223), .B(u11_HPC223_reg), .Z(n1033) );
  XNOR2_X1 U1790 ( .A(n1150), .B(w10_HPC223), .ZN(n1032) );
  XNOR2_X1 U1791 ( .A(n1033), .B(n1032), .ZN(n1038) );
  XOR2_X1 U1792 ( .A(u11_HPC222_reg), .B(v10_HPC222), .Z(n1034) );
  XNOR2_X1 U1793 ( .A(w10_HPC222), .B(n1034), .ZN(n1146) );
  XNOR2_X1 U1794 ( .A(n1038), .B(n1146), .ZN(n1164) );
  XNOR2_X1 U1795 ( .A(n1035), .B(n1164), .ZN(N69) );
  XNOR2_X1 U1796 ( .A(w10_HPC2o24), .B(v10_HPC2o24), .ZN(n1037) );
  XOR2_X1 U1797 ( .A(u11_HPC228_reg), .B(v10_HPC228), .Z(n1036) );
  XNOR2_X1 U1798 ( .A(w10_HPC228), .B(n1036), .ZN(n1154) );
  XNOR2_X1 U1799 ( .A(n1037), .B(n1154), .ZN(n1177) );
  XNOR2_X1 U1800 ( .A(n1038), .B(n1177), .ZN(n1159) );
  XOR2_X1 U1801 ( .A(n1039), .B(n1159), .Z(n1044) );
  XNOR2_X1 U1802 ( .A(n1041), .B(n1040), .ZN(n1151) );
  XNOR2_X1 U1803 ( .A(n1151), .B(v10_HPC2o30), .ZN(n1042) );
  XNOR2_X1 U1804 ( .A(n1042), .B(w10_HPC2o30), .ZN(n1208) );
  XOR2_X1 U1805 ( .A(v10_HPC2o27), .B(w10_HPC2o27), .Z(n1198) );
  XNOR2_X1 U1806 ( .A(n1208), .B(n1198), .ZN(n1043) );
  XNOR2_X1 U1807 ( .A(n1044), .B(n1043), .ZN(N77) );
  XNOR2_X1 U1808 ( .A(u00_HPC228_reg), .B(v01_HPC228), .ZN(n1045) );
  XNOR2_X1 U1809 ( .A(n1045), .B(w01_HPC228), .ZN(n1057) );
  XNOR2_X1 U1810 ( .A(n1057), .B(w01_HPC2o24), .ZN(n1046) );
  XNOR2_X1 U1811 ( .A(n1046), .B(v01_HPC2o24), .ZN(n1182) );
  XNOR2_X1 U1812 ( .A(n1182), .B(w01_HPC2o33), .ZN(n1047) );
  XNOR2_X1 U1813 ( .A(n1047), .B(v01_HPC2o33), .ZN(n1220) );
  XNOR2_X1 U1814 ( .A(u00_HPC222_reg), .B(v01_HPC222), .ZN(n1048) );
  XNOR2_X1 U1815 ( .A(n1048), .B(w01_HPC222), .ZN(n1069) );
  XOR2_X1 U1816 ( .A(n1220), .B(n1069), .Z(n1054) );
  XNOR2_X1 U1817 ( .A(u00_HPC216_reg), .B(v01_HPC216), .ZN(n1049) );
  XNOR2_X1 U1818 ( .A(n1049), .B(w01_HPC216), .ZN(n1067) );
  XOR2_X1 U1819 ( .A(v01_HPC218), .B(w01_HPC218), .Z(n1050) );
  XNOR2_X1 U1820 ( .A(u00_HPC218_reg), .B(n1050), .ZN(n1079) );
  XNOR2_X1 U1821 ( .A(n1067), .B(n1079), .ZN(n1058) );
  XNOR2_X1 U1822 ( .A(n1058), .B(v01_HPC2o30), .ZN(n1051) );
  XNOR2_X1 U1823 ( .A(n1051), .B(w01_HPC2o30), .ZN(n1203) );
  XNOR2_X1 U1824 ( .A(v01_HPC231), .B(w01_HPC231), .ZN(n1052) );
  XNOR2_X1 U1825 ( .A(n1052), .B(u00_HPC231_reg), .ZN(n1259) );
  XNOR2_X1 U1826 ( .A(n1203), .B(n1259), .ZN(n1053) );
  XNOR2_X1 U1827 ( .A(n1054), .B(n1053), .ZN(temp2_0) );
  XNOR2_X1 U1828 ( .A(u00_HPC221_reg), .B(v01_HPC221), .ZN(n1055) );
  XNOR2_X1 U1829 ( .A(n1055), .B(w01_HPC221), .ZN(n1077) );
  XNOR2_X1 U1830 ( .A(n1077), .B(w01_HPC2o29), .ZN(n1056) );
  XNOR2_X1 U1831 ( .A(n1056), .B(v01_HPC2o29), .ZN(n1169) );
  XOR2_X1 U1832 ( .A(n1169), .B(n1057), .Z(n1060) );
  XOR2_X1 U1833 ( .A(v01_HPC2o19), .B(w01_HPC2o19), .Z(n1262) );
  XNOR2_X1 U1834 ( .A(n1058), .B(n1262), .ZN(n1059) );
  XNOR2_X1 U1835 ( .A(n1060), .B(n1059), .ZN(n1063) );
  XNOR2_X1 U1836 ( .A(w01_HPC232), .B(v01_HPC232), .ZN(n1061) );
  XNOR2_X1 U1837 ( .A(n1061), .B(u00_HPC232_reg), .ZN(n1062) );
  XNOR2_X1 U1838 ( .A(n1259), .B(n1062), .ZN(n1073) );
  XNOR2_X1 U1839 ( .A(n1063), .B(n1073), .ZN(temp4_0) );
  XNOR2_X1 U1840 ( .A(v01_HPC226), .B(w01_HPC226), .ZN(n1064) );
  XNOR2_X1 U1841 ( .A(n1064), .B(u00_HPC226_reg), .ZN(n1188) );
  XNOR2_X1 U1842 ( .A(v01_HPC225), .B(w01_HPC225), .ZN(n1065) );
  XNOR2_X1 U1843 ( .A(n1065), .B(u00_HPC225_reg), .ZN(n1086) );
  XNOR2_X1 U1844 ( .A(n1086), .B(w01_HPC2o17), .ZN(n1066) );
  XNOR2_X1 U1845 ( .A(n1066), .B(v01_HPC2o17), .ZN(n1282) );
  XNOR2_X1 U1846 ( .A(n1067), .B(n1282), .ZN(n1085) );
  XOR2_X1 U1847 ( .A(u00_HPC223_reg), .B(v01_HPC223), .Z(n1068) );
  XNOR2_X1 U1848 ( .A(w01_HPC223), .B(n1068), .ZN(n1074) );
  XNOR2_X1 U1849 ( .A(n1069), .B(n1074), .ZN(n1088) );
  XOR2_X1 U1850 ( .A(n1088), .B(n1073), .Z(n1070) );
  XNOR2_X1 U1851 ( .A(n1085), .B(n1070), .ZN(n1071) );
  XNOR2_X1 U1852 ( .A(n1188), .B(n1071), .ZN(temp1_0) );
  XNOR2_X1 U1853 ( .A(u00_HPC220_reg), .B(v01_HPC220), .ZN(n1072) );
  XNOR2_X1 U1854 ( .A(n1072), .B(w01_HPC220), .ZN(n1186) );
  XNOR2_X1 U1855 ( .A(n1186), .B(n1073), .ZN(n1076) );
  XNOR2_X1 U1856 ( .A(n1182), .B(n1074), .ZN(n1082) );
  XNOR2_X1 U1857 ( .A(n1076), .B(n1082), .ZN(n1075) );
  XNOR2_X1 U1858 ( .A(n1075), .B(n1169), .ZN(temp3_0) );
  XNOR2_X1 U1859 ( .A(n1188), .B(n1076), .ZN(n1081) );
  XOR2_X1 U1860 ( .A(n1282), .B(n1077), .Z(n1078) );
  XNOR2_X1 U1861 ( .A(n1081), .B(n1078), .ZN(n1080) );
  XNOR2_X1 U1862 ( .A(n1080), .B(n1079), .ZN(N74) );
  XNOR2_X1 U1863 ( .A(n1262), .B(n1081), .ZN(n1087) );
  XOR2_X1 U1864 ( .A(n1082), .B(n1087), .Z(n1084) );
  XOR2_X1 U1865 ( .A(v01_HPC2o27), .B(w01_HPC2o27), .Z(n1189) );
  XNOR2_X1 U1866 ( .A(n1203), .B(n1189), .ZN(n1083) );
  XNOR2_X1 U1867 ( .A(n1084), .B(n1083), .ZN(N76) );
  XNOR2_X1 U1868 ( .A(n1087), .B(n1085), .ZN(N72) );
  XNOR2_X1 U1869 ( .A(n1087), .B(n1086), .ZN(n1089) );
  XNOR2_X1 U1870 ( .A(n1089), .B(n1088), .ZN(N68) );
  XOR2_X1 U1871 ( .A(n1135), .B(n1132), .Z(n867) );
  XOR2_X1 U1872 ( .A(n867), .B(rand_17), .Z(xor_br_hpc3o_v_1_order0_HPC3o8) );
  XOR2_X1 U1873 ( .A(rand_18), .B(n1090), .Z(n1092) );
  NAND2_X1 U1874 ( .A1(xor_br_hpc3o_v_1_order0_HPC3o8), .A2(n861), .ZN(n1091)
         );
  XNOR2_X1 U1875 ( .A(n1092), .B(n1091), 
        .ZN(xor_step2_hpc3o_first_half_1_order1_HPC3o8) );
  XOR2_X1 U1876 ( .A(rand_23), .B(n886), .Z(N16) );
  XOR2_X1 U1877 ( .A(n1142), .B(n1138), .Z(n873) );
  XOR2_X1 U1878 ( .A(rand_17), .B(n873), .Z(xor_br_hpc3o_v_1_order1_HPC3o8) );
  XOR2_X1 U1879 ( .A(rand_18), .B(n1093), .Z(n1095) );
  NAND2_X1 U1880 ( .A1(xor_br_hpc3o_v_1_order1_HPC3o8), .A2(n862), .ZN(n1094)
         );
  XNOR2_X1 U1881 ( .A(n1095), .B(n1094), 
        .ZN(xor_step2_hpc3o_first_half_1_order0_HPC3o8) );
  XOR2_X1 U1882 ( .A(rand_23), .B(n894), .Z(N18) );
  XNOR2_X1 U1883 ( .A(X2_1), .B(n1096), .ZN(n874) );
  XOR2_X1 U1884 ( .A(n874), .B(rand_15), .Z(xor_br_hpc3o_v_1_order0_HPC3o7) );
  XOR2_X1 U1885 ( .A(n1097), .B(rand_16), .Z(n1099) );
  NAND2_X1 U1886 ( .A1(n879), .A2(xor_br_hpc3o_v_1_order0_HPC3o7), .ZN(n1098)
         );
  XNOR2_X1 U1887 ( .A(n1099), .B(n1098), 
        .ZN(xor_step2_hpc3o_first_half_1_order1_HPC3o7) );
  XOR2_X1 U1888 ( .A(rand_19), .B(n883), .Z(N12) );
  XNOR2_X1 U1889 ( .A(n1101), .B(n1100), .ZN(n1104) );
  XOR2_X1 U1890 ( .A(n1103), .B(n1102), .Z(n1107) );
  XNOR2_X1 U1891 ( .A(n1104), .B(n1107), .ZN(n877) );
  XOR2_X1 U1892 ( .A(rand_21), .B(n877), .Z(xor_br_hpc2o_v_1_order0_HPC2o10)
         );
  XNOR2_X1 U1893 ( .A(n1106), .B(n1105), .ZN(n1108) );
  XNOR2_X1 U1894 ( .A(n1108), .B(n1107), .ZN(n878) );
  XOR2_X1 U1895 ( .A(rand_22), .B(n878), .Z(xor_br_hpc2o_v_1_order0_HPC2o11)
         );
  XOR2_X1 U1896 ( .A(n877), .B(rand_25), 
        .Z(xor_br_hpc2osw_v_1_order0_HPC2o_swapped13) );
  XOR2_X1 U1897 ( .A(n1124), .B(n1109), .Z(N20) );
  XOR2_X1 U1898 ( .A(n878), .B(rand_28), 
        .Z(xor_br_hpc2osw_v_1_order0_HPC2o_swapped15) );
  XNOR2_X1 U1899 ( .A(X2_0), .B(n1110), .ZN(n875) );
  XOR2_X1 U1900 ( .A(rand_15), .B(n875), .Z(xor_br_hpc3o_v_1_order1_HPC3o7) );
  XOR2_X1 U1901 ( .A(n1111), .B(rand_16), .Z(n1113) );
  NAND2_X1 U1902 ( .A1(n885), .A2(xor_br_hpc3o_v_1_order1_HPC3o7), .ZN(n1112)
         );
  XNOR2_X1 U1903 ( .A(n1113), .B(n1112), 
        .ZN(xor_step2_hpc3o_first_half_1_order0_HPC3o7) );
  XOR2_X1 U1904 ( .A(rand_19), .B(n887), .Z(N14) );
  XNOR2_X1 U1905 ( .A(n1115), .B(n1114), .ZN(n1118) );
  XOR2_X1 U1906 ( .A(n1117), .B(n1116), .Z(n1121) );
  XNOR2_X1 U1907 ( .A(n1118), .B(n1121), .ZN(n876) );
  XOR2_X1 U1908 ( .A(rand_21), .B(n876), .Z(xor_br_hpc2o_v_1_order1_HPC2o10)
         );
  XNOR2_X1 U1909 ( .A(n1120), .B(n1119), .ZN(n1122) );
  XNOR2_X1 U1910 ( .A(n1122), .B(n1121), .ZN(n872) );
  XOR2_X1 U1911 ( .A(rand_22), .B(n872), .Z(xor_br_hpc2o_v_1_order1_HPC2o11)
         );
  XOR2_X1 U1912 ( .A(rand_25), .B(n876), 
        .Z(xor_br_hpc2osw_v_1_order1_HPC2o_swapped13) );
  XOR2_X1 U1913 ( .A(n1124), .B(n1123), .Z(N22) );
  XOR2_X1 U1914 ( .A(rand_28), .B(n872), 
        .Z(xor_br_hpc2osw_v_1_order1_HPC2o_swapped15) );
  XNOR2_X1 U1915 ( .A(n855), .B(n1125), .ZN(N34) );
  XNOR2_X1 U1916 ( .A(n882), .B(n1126), .ZN(N54) );
  XOR2_X1 U1917 ( .A(rand_40), .B(n892), .Z(xor_br_hpc2o_v_1_order1_HPC2o27)
         );
  XOR2_X1 U1918 ( .A(n866), .B(rand_42), .Z(xor_br_hpc2o_v_1_order1_HPC2o29)
         );
  XOR2_X1 U1919 ( .A(n890), .B(rand_43), .Z(xor_br_hpc2o_v_1_order1_HPC2o30)
         );
  XNOR2_X1 U1920 ( .A(n856), .B(n1125), .ZN(N32) );
  XNOR2_X1 U1921 ( .A(n889), .B(n1126), .ZN(N52) );
  XOR2_X1 U1922 ( .A(rand_40), .B(n891), .Z(xor_br_hpc2o_v_1_order0_HPC2o27)
         );
  XOR2_X1 U1923 ( .A(n863), .B(rand_42), .Z(xor_br_hpc2o_v_1_order0_HPC2o29)
         );
  XOR2_X1 U1924 ( .A(n893), .B(rand_43), .Z(xor_br_hpc2o_v_1_order0_HPC2o30)
         );
  XOR2_X1 U1925 ( .A(n874), .B(rand_36), .Z(N44) );
  XOR2_X1 U1926 ( .A(n1130), .B(n1127), .Z(N48) );
  XOR2_X1 U1927 ( .A(n1131), .B(n1128), .Z(N60) );
  XOR2_X1 U1928 ( .A(n1137), .B(n1128), .Z(N62) );
  XOR2_X1 U1929 ( .A(n875), .B(rand_36), .Z(N46) );
  XOR2_X1 U1930 ( .A(n1130), .B(n1129), .Z(N50) );
  XOR2_X1 U1931 ( .A(rand_1), .B(n858), .Z(N0) );
  XOR2_X1 U1932 ( .A(n1136), .B(n1131), .Z(T14_1) );
  XOR2_X1 U1933 ( .A(rand_7), .B(n865), .Z(N4) );
  XOR2_X1 U1934 ( .A(rand_13), .B(n859), .Z(N8) );
  XNOR2_X1 U1935 ( .A(X3_1), .B(n1132), .ZN(n1134) );
  XNOR2_X1 U1936 ( .A(n1134), .B(n1133), .ZN(T24_1) );
  XOR2_X1 U1937 ( .A(X0_1), .B(n865), .Z(T25_1) );
  XOR2_X1 U1938 ( .A(n1135), .B(n1141), .Z(N24) );
  XOR2_X1 U1939 ( .A(n868), .B(rand_30), .Z(xor_br_hpc2o_v_1_order0_HPC2o17)
         );
  XOR2_X1 U1940 ( .A(rand_32), .B(n865), .Z(xor_br_hpc2o_v_1_order0_HPC2o19)
         );
  XNOR2_X1 U1941 ( .A(n869), .B(n1143), .ZN(N36) );
  XOR2_X1 U1942 ( .A(n1145), .B(n1136), .Z(N40) );
  XOR2_X1 U1943 ( .A(n867), .B(rand_37), .Z(xor_br_hpc2o_v_1_order0_HPC2o24)
         );
  XOR2_X1 U1944 ( .A(rand_1), .B(n857), .Z(N2) );
  XOR2_X1 U1945 ( .A(n1144), .B(n1137), .Z(T14_0) );
  XOR2_X1 U1946 ( .A(rand_7), .B(n864), .Z(N6) );
  XOR2_X1 U1947 ( .A(rand_13), .B(n860), .Z(N10) );
  XNOR2_X1 U1948 ( .A(X3_0), .B(n1138), .ZN(n1140) );
  XNOR2_X1 U1949 ( .A(n1140), .B(n1139), .ZN(T24_0) );
  XOR2_X1 U1950 ( .A(X0_0), .B(n864), .Z(T25_0) );
  XOR2_X1 U1951 ( .A(n1142), .B(n1141), .Z(N26) );
  XOR2_X1 U1952 ( .A(n870), .B(rand_30), .Z(xor_br_hpc2o_v_1_order1_HPC2o17)
         );
  XOR2_X1 U1953 ( .A(rand_32), .B(n864), .Z(xor_br_hpc2o_v_1_order1_HPC2o19)
         );
  XNOR2_X1 U1954 ( .A(n871), .B(n1143), .ZN(N38) );
  XOR2_X1 U1955 ( .A(n1145), .B(n1144), .Z(N42) );
  XOR2_X1 U1956 ( .A(n873), .B(rand_37), .Z(xor_br_hpc2o_v_1_order1_HPC2o24)
         );
  XNOR2_X1 U1957 ( .A(n1270), .B(n1146), .ZN(n1148) );
  XNOR2_X1 U1958 ( .A(w10_HPC2o33), .B(v10_HPC2o33), .ZN(n1147) );
  XNOR2_X1 U1959 ( .A(n1147), .B(n1177), .ZN(n1213) );
  XNOR2_X1 U1960 ( .A(n1148), .B(n1213), .ZN(n1149) );
  XNOR2_X1 U1961 ( .A(n1208), .B(n1149), .ZN(n850) );
  XNOR2_X1 U1962 ( .A(n1151), .B(n1150), .ZN(n1157) );
  XNOR2_X1 U1963 ( .A(v10_HPC2o29), .B(w10_HPC2o29), .ZN(n1153) );
  XNOR2_X1 U1964 ( .A(n1153), .B(n1152), .ZN(n1173) );
  XOR2_X1 U1965 ( .A(n1267), .B(n1154), .Z(n1155) );
  XNOR2_X1 U1966 ( .A(n1173), .B(n1155), .ZN(n1156) );
  XNOR2_X1 U1967 ( .A(n1157), .B(n1156), .ZN(n849) );
  XNOR2_X1 U1968 ( .A(n1159), .B(n1158), .ZN(n1160) );
  XNOR2_X1 U1969 ( .A(n1160), .B(n1173), .ZN(n848) );
  XOR2_X1 U1970 ( .A(n1162), .B(n1161), .Z(n1163) );
  XNOR2_X1 U1971 ( .A(n1164), .B(n1163), .ZN(n847) );
  INV_X1 U1972 ( .A(n1237), .ZN(n1165) );
  NAND2_X1 U1973 ( .A1(rand_42), .A2(n1165), .ZN(n1167) );
  NAND2_X1 U1974 ( .A1(n1237), .A2(z1397_assgn1397), .ZN(n1166) );
  NAND2_X1 U1975 ( .A1(n1167), .A2(n1166), .ZN(n1168) );
  XOR2_X1 U1976 ( .A(n1169), .B(n1168), .Z(n846) );
  INV_X1 U1977 ( .A(n1243), .ZN(n1170) );
  NAND2_X1 U1978 ( .A1(rand_42), .A2(n1170), .ZN(n1172) );
  NAND2_X1 U1979 ( .A1(n1243), .A2(z1419_assgn1419), .ZN(n1171) );
  NAND2_X1 U1980 ( .A1(n1172), .A2(n1171), .ZN(n1174) );
  XNOR2_X1 U1981 ( .A(n1174), .B(n1173), .ZN(n845) );
  NAND2_X1 U1982 ( .A1(z1227_assgn1227), .A2(n1209), .ZN(n1176) );
  INV_X1 U1983 ( .A(n1209), .ZN(n1210) );
  NAND2_X1 U1984 ( .A1(rand_37), .A2(n1210), .ZN(n1175) );
  NAND2_X1 U1985 ( .A1(n1176), .A2(n1175), .ZN(n1178) );
  XNOR2_X1 U1986 ( .A(n1178), .B(n1177), .ZN(n844) );
  INV_X1 U1987 ( .A(n1216), .ZN(n1215) );
  NAND2_X1 U1988 ( .A1(rand_37), .A2(n1215), .ZN(n1180) );
  NAND2_X1 U1989 ( .A1(n1216), .A2(z1205_assgn1205), .ZN(n1179) );
  NAND2_X1 U1990 ( .A1(n1180), .A2(n1179), .ZN(n1181) );
  XOR2_X1 U1991 ( .A(n1182), .B(n1181), .Z(n843) );
  NAND2_X1 U1992 ( .A1(n1293), .A2(z1317_assgn1317), .ZN(n1185) );
  NAND2_X1 U1993 ( .A1(rand_40), .A2(n1183), .ZN(n1184) );
  NAND2_X1 U1994 ( .A1(n1185), .A2(n1184), .ZN(n1187) );
  XNOR2_X1 U1995 ( .A(n1187), .B(n1186), .ZN(n1191) );
  XOR2_X1 U1996 ( .A(n1189), .B(n1188), .Z(n1190) );
  XNOR2_X1 U1997 ( .A(n1191), .B(n1190), .ZN(n842) );
  NAND2_X1 U1998 ( .A1(rand_40), .A2(n1192), .ZN(n1194) );
  NAND2_X1 U1999 ( .A1(n1287), .A2(z1339_assgn1339), .ZN(n1193) );
  NAND2_X1 U2000 ( .A1(n1194), .A2(n1193), .ZN(n1196) );
  XNOR2_X1 U2001 ( .A(n1196), .B(n1195), .ZN(n1197) );
  XOR2_X1 U2002 ( .A(n1198), .B(n1197), .Z(n841) );
  NAND2_X1 U2003 ( .A1(rand_43), .A2(n1199), .ZN(n1201) );
  NAND2_X1 U2004 ( .A1(n1231), .A2(z1445_assgn1445), .ZN(n1200) );
  NAND2_X1 U2005 ( .A1(n1201), .A2(n1200), .ZN(n1202) );
  XOR2_X1 U2006 ( .A(n1203), .B(n1202), .Z(n840) );
  NAND2_X1 U2007 ( .A1(rand_43), .A2(n1204), .ZN(n1206) );
  NAND2_X1 U2008 ( .A1(n1225), .A2(z1467_assgn1467), .ZN(n1205) );
  NAND2_X1 U2009 ( .A1(n1206), .A2(n1205), .ZN(n1207) );
  XOR2_X1 U2010 ( .A(n1208), .B(n1207), .Z(n839) );
  NAND2_X1 U2011 ( .A1(z1579_assgn1579), .A2(n1209), .ZN(n1212) );
  NAND2_X1 U2012 ( .A1(rand_46), .A2(n1210), .ZN(n1211) );
  NAND2_X1 U2013 ( .A1(n1212), .A2(n1211), .ZN(n1214) );
  XNOR2_X1 U2014 ( .A(n1214), .B(n1213), .ZN(n838) );
  NAND2_X1 U2015 ( .A1(rand_46), .A2(n1215), .ZN(n1218) );
  NAND2_X1 U2016 ( .A1(n1216), .A2(z1557_assgn1557), .ZN(n1217) );
  NAND2_X1 U2017 ( .A1(n1218), .A2(n1217), .ZN(n1219) );
  XOR2_X1 U2018 ( .A(n1220), .B(n1219), .Z(n837) );
  INV_X1 U2019 ( .A(n1222), .ZN(n1221) );
  NAND2_X1 U2020 ( .A1(rand_21), .A2(n1221), .ZN(n1224) );
  NAND2_X1 U2021 ( .A1(n1222), .A2(M27_1_reg), .ZN(n1223) );
  NAND2_X1 U2022 ( .A1(n1224), .A2(n1223), .ZN(n1226) );
  XOR2_X1 U2023 ( .A(n1226), .B(n1225), .Z(n836) );
  INV_X1 U2024 ( .A(n1228), .ZN(n1227) );
  NAND2_X1 U2025 ( .A1(rand_21), .A2(n1227), .ZN(n1230) );
  NAND2_X1 U2026 ( .A1(n1228), .A2(M27_0_reg), .ZN(n1229) );
  NAND2_X1 U2027 ( .A1(n1230), .A2(n1229), .ZN(n1232) );
  XOR2_X1 U2028 ( .A(n1232), .B(n1231), .Z(n835) );
  NAND2_X1 U2029 ( .A1(rand_25), .A2(n1233), .ZN(n1236) );
  NAND2_X1 U2030 ( .A1(M27_0_reg), .A2(n1234), .ZN(n1235) );
  NAND2_X1 U2031 ( .A1(n1236), .A2(n1235), .ZN(n1238) );
  XOR2_X1 U2032 ( .A(n1238), .B(n1237), .Z(n834) );
  NAND2_X1 U2033 ( .A1(rand_25), .A2(n1239), .ZN(n1242) );
  NAND2_X1 U2034 ( .A1(M27_1_reg), .A2(n1240), .ZN(n1241) );
  NAND2_X1 U2035 ( .A1(n1242), .A2(n1241), .ZN(n1244) );
  XOR2_X1 U2036 ( .A(n1244), .B(n1243), .Z(n833) );
  INV_X1 U2037 ( .A(n1246), .ZN(n1245) );
  NAND2_X1 U2038 ( .A1(rand_28), .A2(n1245), .ZN(n1248) );
  NAND2_X1 U2039 ( .A1(M24_0_reg), .A2(n1246), .ZN(n1247) );
  NAND2_X1 U2040 ( .A1(n1248), .A2(n1247), .ZN(n1249) );
  XNOR2_X1 U2041 ( .A(n1277), .B(n1249), .ZN(n832) );
  INV_X1 U2042 ( .A(n1251), .ZN(n1250) );
  NAND2_X1 U2043 ( .A1(rand_28), .A2(n1250), .ZN(n1253) );
  NAND2_X1 U2044 ( .A1(M24_1_reg), .A2(n1251), .ZN(n1252) );
  NAND2_X1 U2045 ( .A1(n1253), .A2(n1252), .ZN(n1254) );
  XNOR2_X1 U2046 ( .A(n1271), .B(n1254), .ZN(n831) );
  NAND2_X1 U2047 ( .A1(z1029_assgn1029), .A2(n1255), .ZN(n1258) );
  NAND2_X1 U2048 ( .A1(rand_32), .A2(n1256), .ZN(n1257) );
  NAND2_X1 U2049 ( .A1(n1258), .A2(n1257), .ZN(n1260) );
  XNOR2_X1 U2050 ( .A(n1260), .B(n1259), .ZN(n1261) );
  XNOR2_X1 U2051 ( .A(n1262), .B(n1261), .ZN(n830) );
  NAND2_X1 U2052 ( .A1(rand_32), .A2(n1263), .ZN(n1266) );
  NAND2_X1 U2053 ( .A1(z1051_assgn1051), .A2(n1264), .ZN(n1265) );
  NAND2_X1 U2054 ( .A1(n1266), .A2(n1265), .ZN(n1268) );
  XNOR2_X1 U2055 ( .A(n1268), .B(n1267), .ZN(n1269) );
  XNOR2_X1 U2056 ( .A(n1270), .B(n1269), .ZN(n829) );
  NAND2_X1 U2057 ( .A1(rand_30), .A2(n1271), .ZN(n1274) );
  NAND2_X1 U2058 ( .A1(n1272), .A2(z971_assgn971), .ZN(n1273) );
  NAND2_X1 U2059 ( .A1(n1274), .A2(n1273), .ZN(n1275) );
  XOR2_X1 U2060 ( .A(n1276), .B(n1275), .Z(n828) );
  NAND2_X1 U2061 ( .A1(rand_30), .A2(n1277), .ZN(n1280) );
  NAND2_X1 U2062 ( .A1(n1278), .A2(z949_assgn949), .ZN(n1279) );
  NAND2_X1 U2063 ( .A1(n1280), .A2(n1279), .ZN(n1281) );
  XOR2_X1 U2064 ( .A(n1282), .B(n1281), .Z(n827) );
  INV_X1 U2065 ( .A(n1284), .ZN(n1283) );
  NAND2_X1 U2066 ( .A1(rand_22), .A2(n1283), .ZN(n1286) );
  NAND2_X1 U2067 ( .A1(n1284), .A2(M24_1_reg), .ZN(n1285) );
  NAND2_X1 U2068 ( .A1(n1286), .A2(n1285), .ZN(n1288) );
  XOR2_X1 U2069 ( .A(n1288), .B(n1287), .Z(n826) );
  INV_X1 U2070 ( .A(n1290), .ZN(n1289) );
  NAND2_X1 U2071 ( .A1(rand_22), .A2(n1289), .ZN(n1292) );
  NAND2_X1 U2072 ( .A1(n1290), .A2(M24_0_reg), .ZN(n1291) );
  NAND2_X1 U2073 ( .A1(n1292), .A2(n1291), .ZN(n1294) );
  XOR2_X1 U2074 ( .A(n1294), .B(n1293), .Z(n825) );
endmodule
