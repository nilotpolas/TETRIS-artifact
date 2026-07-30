
#include <stdio.h>
#include <stdlib.h>

// --- 1. Golden Model (Unmasked) ---
// // #include <stdio.h>
// #include <stdint.h>
// void sbox_golden (int X0, int X1, int X2, int X3, int X4, int X5, int X6, int X7,int dec_1, int *Y0, int *Y1, int *Y2, int *Y3, int *Y4, int *Y5, int *Y6, int *Y7) {
	

// 	//declare T signals
// 	int T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27;

// 	//declare M signals
// 	int M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,
//     M11, M12, M13, M14, M15, M16, M17, M18, M19, M20,
//     M21, M22, M23, M24, M25, M26, M27, M28, M29, M30,
//     M31, M32, M33, M34, M35, M36, M37, M38, M39, M40,
//     M41, M42, M43, M44, M45, M46, M47, M48, M49, M50,
//     M51, M52, M53, M54, M55, M56, M57, M58, M59, M60,
//     M61, M62, M63;

// 	//declare L signals
// 	int L0, L1, L2, L3, L4, L5, L6, L7, L8, L9,
//     L10, L11, L12, L13, L14, L15, L16, L17, L18, L19,
//     L20, L21, L22, L23, L24, L25, L26, L27, L28, L29;

	
// 	// ----- T signals -----
//     T1  = X0 ^ X3;
//     T2  = X0 ^ X5;
//     T3  = X0 ^ X6;
//     T4  = X3 ^ X5;
//     T5  = X4 ^ X6;
//     T6  = T1 ^ T5;
//     T7  = X1 ^ X2;
//     T8  = X7 ^ T6;
//     T9  = X7 ^ T7;
//     T10 = T6 ^ T7;
//     T11 = X1 ^ X5;
//     T12 = X2 ^ X5;
//     T13 = T3 ^ T4;
//     T14 = T6 ^ T11;
//     T15 = T5 ^ T11;
//     T16 = T5 ^ T12;
//     T17 = T9 ^ T16;
//     T18 = X3 ^ X7;
//     T19 = T7 ^ T18;
//     T20 = T1 ^ T19;
//     T21 = X6 ^ X7;
//     T22 = T7 ^ T21;
//     T23 = T2 ^ T22;
//     T24 = T2 ^ T10;
//     T25 = T20 ^ T17;
//     T26 = T3 ^ T16;
//     T27 = T1 ^ T12;

// 	M1  = T13 & T6;
//     M2  = T23 & T8;
//     M3  = T14 ^ M1;
//     M4  = T19 & X7;
//     M5  = M4 ^ M1;
//     M6  = T3 & T16;
//     M7  = T22 & T9;
//     M8  = T26 ^ M6;
//     M9  = T20 & T17;
//     M10 = M9 ^ M6;
//     M11 = T1 & T15;
//     M12 = T4 & T27;
//     M13 = M12 ^ M11;
//     M14 = T2 & T10;
//     M15 = M14 ^ M11;
//     M16 = M3 ^ M2;
//     M17 = M5 ^ T24;
//     M18 = M8 ^ M7;
//     M19 = M10 ^ M15;
//     M20 = M16 ^ M13;
//     M21 = M17 ^ M15;
//     M22 = M18 ^ M13;
//     M23 = M19 ^ T25;
//     M24 = M22 ^ M23;
//     M25 = M22 & M20;
//     M26 = M21 ^ M25;
//     M27 = M20 ^ M21;
//     M28 = M23 ^ M25;
//     M29 = M28 & M27;
//     M30 = M26 & M24;
//     M31 = M20 & M23;
//     M32 = M27 & M31;
//     M33 = M27 ^ M25;
//     M34 = M21 & M22;
//     M35 = M24 & M34;
//     M36 = M24 ^ M25;
//     M37 = M21 ^ M29;
//     M38 = M32 ^ M33;
//     M39 = M23 ^ M30;
//     M40 = M35 ^ M36;
//     M41 = M38 ^ M40;
//     M42 = M37 ^ M39;
//     M43 = M37 ^ M38;
//     M44 = M39 ^ M40;
//     M45 = M42 ^ M41;
//     M46 = M44 & T6;
//     M47 = M40 & T8;
//     M48 = M39 & X7;
//     M49 = M43 & T16;
//     M50 = M38 & T9;
//     M51 = M37 & T17;
//     M52 = M42 & T15;
//     M53 = M45 & T27;
//     M54 = M41 & T10;
//     M55 = M44 & T13;
//     M56 = M40 & T23;
//     M57 = M39 & T19;
//     M58 = M43 & T3;
//     M59 = M38 & T22;
//     M60 = M37 & T20;
//     M61 = M42 & T1;
//     M62 = M45 & T4;
//     M63 = M41 & T2;

//     // ----- L signals -----
//     L0  = M61 ^ M62;
//     L1  = M50 ^ M56;
//     L2  = M46 ^ M48;
//     L3  = M47 ^ M55;
//     L4  = M54 ^ M58;
//     L5  = M49 ^ M61;
//     L6  = M62 ^ L5;
//     L7  = M46 ^ L3;
//     L8  = M51 ^ M59;
//     L9  = M52 ^ M53;
//     L10 = M53 ^ L4;
//     L11 = M60 ^ L2;
//     L12 = M48 ^ M51;
//     L13 = M50 ^ L0;
//     L14 = M52 ^ M61;
//     L15 = M55 ^ L1;
//     L16 = M56 ^ L0;
//     L17 = M57 ^ L1;
//     L18 = M58 ^ L8;
//     L19 = M63 ^ L4;
//     L20 = L0 ^ L1;
//     L21 = L1 ^ L7;
//     L22 = L3 ^ L12;
//     L23 = L18 ^ L2;
//     L24 = L15 ^ L9;
//     L25 = L6 ^ L10;
//     L26 = L7 ^ L9;
//     L27 = L8 ^ L10;
//     L28 = L11 ^ L14;
//     L29 = L11 ^ L17;

//     // ----- Outputs -----
//     *Y0 = L6 ^ L24;
// 	int temp1 = L16 ^ L26;
//     *Y1 = temp1 ^ dec_1;  // XNOR
// 	int temp2 = L19 ^ L28;
//     *Y2 = temp2 ^ dec_1;  // XNOR
//     *Y3 = L6 ^ L21;
//     *Y4 = L20 ^ L22;
//     *Y5 = L25 ^ L29;
// 	int temp3 = L13 ^ L27;
//     *Y6 = temp3 ^ dec_1;  // XNOR
// 	int temp4 = L6 ^ L23;
//     *Y7 = temp4 ^ dec_1;   // XNOR
// }
// // #include <stdio.h>
// #include <stdint.h>
// void sbox_golden (int X0, int X1, int X2, int X3, int X4, int X5, int X6, int X7, int *Y0, int *Y1, int *Y2, int *Y3, int *Y4, int *Y5, int *Y6, int *Y7, int dec_1) {
	

// 	//declare T signals
// 	int T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27;

// 	//declare M signals
// 	int M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,
//     M11, M12, M13, M14, M15, M16, M17, M18, M19, M20,
//     M21, M22, M23, M24, M25, M26, M27, M28, M29, M30,
//     M31, M32, M33, M34, M35, M36, M37, M38, M39, M40,
//     M41, M42, M43, M44, M45, M46, M47, M48, M49, M50,
//     M51, M52, M53, M54, M55, M56, M57, M58, M59, M60,
//     M61, M62, M63;

// 	//declare L signals
// 	int L0, L1, L2, L3, L4, L5, L6, L7, L8, L9,
//     L10, L11, L12, L13, L14, L15, L16, L17, L18, L19,
//     L20, L21, L22, L23, L24, L25, L26, L27, L28, L29;

	
// 	// ----- T signals -----
//     T1  = X0 ^ X3;
//     T2  = X0 ^ X5;
//     T3  = X0 ^ X6;
//     T4  = X3 ^ X5;
//     T5  = X4 ^ X6;
//     T6  = T1 ^ T5;
//     T7  = X1 ^ X2;
//     T8  = X7 ^ T6;
//     T9  = X7 ^ T7;
//     T10 = T6 ^ T7;
//     T11 = X1 ^ X5;
//     T12 = X2 ^ X5;
//     T13 = T3 ^ T4;
//     T14 = T6 ^ T11;
//     T15 = T5 ^ T11;
//     T16 = T5 ^ T12;
//     T17 = T9 ^ T16;
//     T18 = X3 ^ X7;
//     T19 = T7 ^ T18;
//     T20 = T1 ^ T19;
//     T21 = X6 ^ X7;
//     T22 = T7 ^ T21;
//     T23 = T2 ^ T22;
//     T24 = T2 ^ T10;
//     T25 = T20 ^ T17;
//     T26 = T3 ^ T16;
//     T27 = T1 ^ T12;

// 	M1  = T13 & T6;
//     M2  = T23 & T8;
//     M3  = T14 ^ M1;
//     M4  = T19 & X7;
//     M5  = M4 ^ M1;
//     M6  = T3 & T16;
//     M7  = T22 & T9;
//     M8  = T26 ^ M6;
//     M9  = T20 & T17;
//     M10 = M9 ^ M6;
//     M11 = T1 & T15;
//     M12 = T4 & T27;
//     M13 = M12 ^ M11;
//     M14 = T2 & T10;
//     M15 = M14 ^ M11;
//     M16 = M3 ^ M2;
//     M17 = M5 ^ T24;
//     M18 = M8 ^ M7;
//     M19 = M10 ^ M15;
//     M20 = M16 ^ M13;
//     M21 = M17 ^ M15;
//     M22 = M18 ^ M13;
//     M23 = M19 ^ T25;
//     M24 = M22 ^ M23;
//     M25 = M22 & M20;
//     M26 = M21 ^ M25;
//     M27 = M20 ^ M21;
//     M28 = M23 ^ M25;
//     M29 = M28 & M27;
//     M30 = M26 & M24;
//     M31 = M20 & M23;
//     M32 = M27 & M31;
//     M33 = M27 ^ M25;
//     M34 = M21 & M22;
//     M35 = M24 & M34;
//     M36 = M24 ^ M25;
//     M37 = M21 ^ M29;
//     M38 = M32 ^ M33;
//     M39 = M23 ^ M30;
//     M40 = M35 ^ M36;
//     M41 = M38 ^ M40;
//     M42 = M37 ^ M39;
//     M43 = M37 ^ M38;
//     M44 = M39 ^ M40;
//     M45 = M42 ^ M41;
//     M46 = M44 & T6;
//     M47 = M40 & T8;
//     M48 = M39 & X7;
//     M49 = M43 & T16;
//     M50 = M38 & T9;
//     M51 = M37 & T17;
//     M52 = M42 & T15;
//     M53 = M45 & T27;
//     M54 = M41 & T10;
//     M55 = M44 & T13;
//     M56 = M40 & T23;
//     M57 = M39 & T19;
//     M58 = M43 & T3;
//     M59 = M38 & T22;
//     M60 = M37 & T20;
//     M61 = M42 & T1;
//     M62 = M45 & T4;
//     M63 = M41 & T2;

//     // ----- L signals -----
//     L0  = M61 ^ M62;
//     L1  = M50 ^ M56;
//     L2  = M46 ^ M48;
//     L3  = M47 ^ M55;
//     L4  = M54 ^ M58;
//     L5  = M49 ^ M61;
//     L6  = M62 ^ L5;
//     L7  = M46 ^ L3;
//     L8  = M51 ^ M59;
//     L9  = M52 ^ M53;
//     L10 = M53 ^ L4;
//     L11 = M60 ^ L2;
//     L12 = M48 ^ M51;
//     L13 = M50 ^ L0;
//     L14 = M52 ^ M61;
//     L15 = M55 ^ L1;
//     L16 = M56 ^ L0;
//     L17 = M57 ^ L1;
//     L18 = M58 ^ L8;
//     L19 = M63 ^ L4;
//     L20 = L0 ^ L1;
//     L21 = L1 ^ L7;
//     L22 = L3 ^ L12;
//     L23 = L18 ^ L2;
//     L24 = L15 ^ L9;
//     L25 = L6 ^ L10;
//     L26 = L7 ^ L9;
//     L27 = L8 ^ L10;
//     L28 = L11 ^ L14;
//     L29 = L11 ^ L17;

//     // ----- Outputs -----
//     *Y0 = L6 ^ L24;
// 	int temp1 = L16 ^ L26;
//     *Y1 = temp1 ^ dec_1;  // XNOR
// 	int temp2 = L19 ^ L28;
//     *Y2 = temp2 ^ dec_1;  // XNOR
//     *Y3 = L6 ^ L21;
//     *Y4 = L20 ^ L22;
//     *Y5 = L25 ^ L29;
// 	int temp3 = L13 ^ L27;
//     *Y6 = temp3 ^ dec_1;  // XNOR
// 	int temp4 = L6 ^ L23;
//     *Y7 = temp4 ^ dec_1;   // XNOR
// }





#include <stdint.h>

void sbox_golden(
    int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7,
    int *o0, int *o1, int *o2, int *o3, int *o4, int *o5, int *o6, int *o7
) {
    // 1. Declare intermediate variables first
    int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27;
    int m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43, m44, m45, m46, m47, m48, m49, m50, m51, m52, m53, m54, m55, m56, m57, m58, m59, m60, m61, m62, m63;
    int l0, l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15, l16, l17, l18, l19, l20, l21, l22, l23, l24, l25, l26, l27, l28, l29;

    // 2. Top Linear Transform
    t1 = i7 ^ i4;
    t2 = i7 ^ i2;
    t3 = i7 ^ i1;
    t4 = i4 ^ i2;
    t5 = i3 ^ i1;
    t6 = t1 ^ t5;
    t7 = i6 ^ i5;
    t8 = i0 ^ t6;
    t9 = i0 ^ t7;
    t10 = t6 ^ t7;
    t11 = i6 ^ i2;
    t12 = i5 ^ i2;
    t13 = t3 ^ t4;
    t14 = t6 ^ t11;
    t15 = t5 ^ t11;
    t16 = t5 ^ t12;
    t17 = t9 ^ t16;
    t18 = i4 ^ i0;
    t19 = t7 ^ t18;
    t20 = t1 ^ t19;
    t21 = i1 ^ i0;
    t22 = t7 ^ t21;
    t23 = t2 ^ t22;
    t24 = t2 ^ t10;
    t25 = t20 ^ t17;
    t26 = t3 ^ t16;
    t27 = t1 ^ t12;

    // 3. Shared Part
    m1 = t13 & t6;
    m2 = t23 & t8;
    m3 = t14 ^ m1;
    m4 = t19 & i0;
    m5 = m4 ^ m1;
    m6 = t3 & t16;
    m7 = t22 & t9;
    m8 = t26 ^ m6;
    m9 = t20 & t17;
    m10 = m9 ^ m6;
    m11 = t1 & t15;
    m12 = t4 & t27;
    m13 = m12 ^ m11;
    m14 = t2 & t10;
    m15 = m14 ^ m11;
    m16 = m3 ^ m2;
    m17 = m5 ^ t24;
    m18 = m8 ^ m7;
    m19 = m10 ^ m15;
    m20 = m16 ^ m13;
    m21 = m17 ^ m15;
    m22 = m18 ^ m13;
    m23 = m19 ^ t25;
    m24 = m22 ^ m23;
    m25 = m22 & m20;
    m26 = m21 ^ m25;
    m27 = m20 ^ m21;
    m28 = m23 ^ m25;
    m29 = m28 & m27;
    m30 = m26 & m24;
    m31 = m20 & m23;
    m32 = m27 & m31;
    m33 = m27 ^ m25;
    m34 = m21 & m22;
    m35 = m24 & m34;
    m36 = m24 ^ m25;
    m37 = m21 ^ m29;
    m38 = m32 ^ m33;
    m39 = m23 ^ m30;
    m40 = m35 ^ m36;
    m41 = m38 ^ m40;
    m42 = m37 ^ m39;
    m43 = m37 ^ m38;
    m44 = m39 ^ m40;
    m45 = m42 ^ m41;
    m46 = m44 & t6;
    m47 = m40 & t8;
    m48 = m39 & i0;
    m49 = m43 & t16;
    m50 = m38 & t9;
    m51 = m37 & t17;
    m52 = m42 & t15;
    m53 = m45 & t27;
    m54 = m41 & t10;
    m55 = m44 & t13;
    m56 = m40 & t23;
    m57 = m39 & t19;
    m58 = m43 & t3;
    m59 = m38 & t22;
    m60 = m37 & t20;
    m61 = m42 & t1;
    m62 = m45 & t4;
    m63 = m41 & t2;

    // 4. Bottom Linear Transform
    l0 = m61 ^ m62;
    l1 = m50 ^ m56;
    l2 = m46 ^ m48;
    l3 = m47 ^ m55;
    l4 = m54 ^ m58;
    l5 = m49 ^ m61;
    l6 = m62 ^ l5;
    l7 = m46 ^ l3;
    l8 = m51 ^ m59;
    l9 = m52 ^ m53;
    l10 = m53 ^ l4;
    l11 = m60 ^ l2;
    l12 = m48 ^ m51;
    l13 = m50 ^ l0;
    l14 = m52 ^ m61;
    l15 = m55 ^ l1;
    l16 = m56 ^ l0;
    l17 = m57 ^ l1;
    l18 = m58 ^ l8;
    l19 = m63 ^ l4;
    l20 = l0 ^ l1;
    l21 = l1 ^ l7;
    l22 = l3 ^ l12;
    l23 = l18 ^ l2;
    l24 = l15 ^ l9;
    l25 = l6 ^ l10;
    l26 = l7 ^ l9;
    l27 = l8 ^ l10;
    l28 = l11 ^ l14;
    l29 = l11 ^ l17;

    // 5. Outputs (including XNOR logic where # was used)
    *o7 = l6 ^ l24;
    *o6 = !(l16 ^ l26); // XNOR (#)
    *o5 = !(l19 ^ l28); // XNOR (#)
    *o4 = l6 ^ l21;
    *o3 = l20 ^ l22;
    *o2 = l25 ^ l29;
    *o1 = !(l13 ^ l27); // XNOR (#)
    *o0 = !(l6 ^ l23);  // XNOR (#)
}

// --- 2. Masked Model (Generated) ---
void sbox_masked(int i0_0, int i0_1, int i1_0, int i1_1, int i2_0, int i2_1, int i3_0, int i3_1, int i4_0, int i4_1, int i5_0, int i5_1, int i6_0, int i6_1, int i7_0, int i7_1, int *o0_0, int *o0_1, int *o1_0, int *o1_1, int *o2_0, int *o2_1, int *o3_0, int *o3_1, int *o4_0, int *o4_1, int *o5_0, int *o5_1, int *o6_0, int *o6_1, int *o7_0, int *o7_1, int rand_36, int rand_18, int rand_42, int rand_21, int rand_23, int rand_16, int rand_7, int rand_45, int rand_31, int rand_34, int rand_1, int rand_6, int rand_15, int rand_25, int rand_32, int rand_44, int rand_5, int rand_2, int rand_26, int rand_28, int rand_40, int rand_46, int rand_10, int rand_39, int rand_8, int rand_13, int rand_17, int rand_38, int rand_4, int rand_22, int rand_27, int rand_29, int rand_30, int rand_9, int rand_11, int rand_12, int rand_35, int rand_14, int rand_37, int rand_33, int rand_41, int rand_43, int rand_3, int rand_20, int rand_24, int rand_19);

int reg(int x){
    return x;
}
int regPR(int x){
    return x;
}
// === GADGET DEFINITIONS ===

// --- hpc3 ---

// === GADGET DEFINITIONS ===

// --- hpc3 ---

void hpc3_same_shares_1_order(int a_share, int b_share, int * u_share) {
    * u_share  = a_share & b_share;
}

void hpc3_v_1_order(int a_share, int b_share, int * v_share, int rand){
    int temp;
    temp = reg(b_share ^ rand);
    *v_share = temp & a_share;
}

void hpc3_w_1_order(int a_share, int rand, int prand, int * w_share){
    int temp;
    int a_share_neg;
    a_share_neg = ~(a_share);
    temp = a_share_neg & rand;
    *w_share = reg(temp ^ prand);
}

void hpc3_xor_vw_1_order(int v_share, int w_share, int * u_share){
    *u_share = v_share ^ w_share;
}

void HPC3(int a0, int a1, int b0, int b1, int* c0, int* c1, int r01, int p01)
{
	int u00, u01, u10, u11;
	int v01, v10;
	int w01, w10;

	hpc3_same_shares_1_order(a0, b0, &u00);

	hpc3_v_1_order(a0, b1, &v01 , r01);
	hpc3_w_1_order(a0, r01, p01, &w01);
	hpc3_xor_vw_1_order(v01, w01, &u01);

	hpc3_v_1_order(a1, b0, &v10 , r01);
	hpc3_w_1_order(a1, r01, p01, &w10);
	hpc3_xor_vw_1_order(v10, w10, &u10);

	hpc3_same_shares_1_order(a1, b1, &u11);

	*c0 = u00 ^ u01;
	*c1 = u10 ^ u11;
}


// --- hpc2 ---

void hpc2_same_shares_1_order(int a_share, int b_share, int * u_share) {
    * u_share  = a_share & b_share;
}

void hpc2_v_1_order(int a_share, int b_share, int * v_share, int rand){
    int temp; 
    temp = reg(b_share ^ rand);
    *v_share = reg(temp & a_share);
}

void hpc2_w_1_order(int a_share, int rand, int * w_share){
    int a_neg;
    a_neg = ~(a_share);
    *w_share = reg(a_neg & rand);
}

void hpc2_xor_vw_1_order(int v_share, int w_share, int * u_share){
    *u_share = v_share ^ w_share;
}

void HPC2(int a0, int a1, int b0, int b1, int * c0, int * c1, int rand_01)
{
	int u00, u01, u10, u11;
	int v01, v10;

	int w01, w10;

	hpc2_same_shares_1_order(a0, b0, &u00);
	hpc2_v_1_order(a0, b1, &v01 , rand_01);
	hpc2_w_1_order(a0, rand_01, &w01);
	hpc2_xor_vw_1_order(v01, w01, &u01);

	hpc2_v_1_order(a1, b0, &v10 , rand_01);
	hpc2_w_1_order(a1, rand_01, &w10);
	hpc2_xor_vw_1_order(v10, w10, &u10);

	hpc2_same_shares_1_order(a1, b1, &u11);
	*c0 = u00 ^ u01;
	*c1 = u10 ^ u11;
}

void sbox_masked(int i0_0, int i0_1, int i1_0, int i1_1, int i2_0, int i2_1, int i3_0, int i3_1, int i4_0, int i4_1, int i5_0, int i5_1, int i6_0, int i6_1, int i7_0, int i7_1, int *o0_0, int *o0_1, int *o1_0, int *o1_1, int *o2_0, int *o2_1, int *o3_0, int *o3_1, int *o4_0, int *o4_1, int *o5_0, int *o5_1, int *o6_0, int *o6_1, int *o7_0, int *o7_1, int rand_36, int rand_18, int rand_42, int rand_21, int rand_23, int rand_16, int rand_7, int rand_45, int rand_31, int rand_34, int rand_1, int rand_6, int rand_15, int rand_25, int rand_32, int rand_44, int rand_5, int rand_2, int rand_26, int rand_28, int rand_40, int rand_46, int rand_10, int rand_39, int rand_8, int rand_13, int rand_17, int rand_38, int rand_4, int rand_22, int rand_27, int rand_29, int rand_30, int rand_9, int rand_11, int rand_12, int rand_35, int rand_14, int rand_37, int rand_33, int rand_41, int rand_43, int rand_3, int rand_20, int rand_24, int rand_19)
{
  int t1_0;
  int t1_1;
  int t2_0;
  int t2_1;
  int t3_0;
  int t3_1;
  int t4_0;
  int t4_1;
  int t5_0;
  int t5_1;
  int t6_0;
  int t6_1;
  int t7_0;
  int t7_1;
  int t8_0;
  int t8_1;
  int t9_0;
  int t9_1;
  int t10_0;
  int t10_1;
  int t11_0;
  int t11_1;
  int t12_0;
  int t12_1;
  int t13_0;
  int t13_1;
  int t14_0;
  int t14_1;
  int t15_0;
  int t15_1;
  int t16_0;
  int t16_1;
  int t17_0;
  int t17_1;
  int t18_0;
  int t18_1;
  int t19_0;
  int t19_1;
  int t20_0;
  int t20_1;
  int t21_0;
  int t21_1;
  int t22_0;
  int t22_1;
  int t23_0;
  int t23_1;
  int t24_0;
  int t24_1;
  int t25_0;
  int t25_1;
  int t26_0;
  int t26_1;
  int t27_0;
  int t27_1;
  int m1_0;
  int m1_1;
  int m2_0;
  int m2_1;
  int m3_0;
  int m3_1;
  int m4_0;
  int m4_1;
  int m5_0;
  int m5_1;
  int m6_0;
  int m6_1;
  int m7_0;
  int m7_1;
  int m8_0;
  int m8_1;
  int m9_0;
  int m9_1;
  int m10_0;
  int m10_1;
  int m11_0;
  int m11_1;
  int m12_0;
  int m12_1;
  int m13_0;
  int m13_1;
  int m14_0;
  int m14_1;
  int m15_0;
  int m15_1;
  int m16_0;
  int m16_1;
  int m17_0;
  int m17_1;
  int m18_0;
  int m18_1;
  int m19_0;
  int m19_1;
  int m20_0;
  int m20_1;
  int m21_0;
  int m21_1;
  int m22_0;
  int m22_1;
  int m23_0;
  int m23_1;
  int m24_0;
  int m24_1;
  int m25_0;
  int m25_1;
  int m26_0;
  int m26_1;
  int m27_0;
  int m27_1;
  int m28_0;
  int m28_1;
  int m29_0;
  int m29_1;
  int m30_0;
  int m30_1;
  int m31_0;
  int m31_1;
  int m32_0;
  int m32_1;
  int m33_0;
  int m33_1;
  int m34_0;
  int m34_1;
  int m35_0;
  int m35_1;
  int m36_0;
  int m36_1;
  int m37_0;
  int m37_1;
  int m38_0;
  int m38_1;
  int m39_0;
  int m39_1;
  int m40_0;
  int m40_1;
  int m41_0;
  int m41_1;
  int m42_0;
  int m42_1;
  int m43_0;
  int m43_1;
  int m44_0;
  int m44_1;
  int m45_0;
  int m45_1;
  int m46_0;
  int m46_1;
  int m47_0;
  int m47_1;
  int m48_0;
  int m48_1;
  int m49_0;
  int m49_1;
  int m50_0;
  int m50_1;
  int m51_0;
  int m51_1;
  int m52_0;
  int m52_1;
  int m53_0;
  int m53_1;
  int m54_0;
  int m54_1;
  int m55_0;
  int m55_1;
  int m56_0;
  int m56_1;
  int m57_0;
  int m57_1;
  int m58_0;
  int m58_1;
  int m59_0;
  int m59_1;
  int m60_0;
  int m60_1;
  int m61_0;
  int m61_1;
  int m62_0;
  int m62_1;
  int m63_0;
  int m63_1;
  int l0_0;
  int l0_1;
  int l1_0;
  int l1_1;
  int l2_0;
  int l2_1;
  int l3_0;
  int l3_1;
  int l4_0;
  int l4_1;
  int l5_0;
  int l5_1;
  int l6_0;
  int l6_1;
  int l7_0;
  int l7_1;
  int l8_0;
  int l8_1;
  int l9_0;
  int l9_1;
  int l10_0;
  int l10_1;
  int l11_0;
  int l11_1;
  int l12_0;
  int l12_1;
  int l13_0;
  int l13_1;
  int l14_0;
  int l14_1;
  int l15_0;
  int l15_1;
  int l16_0;
  int l16_1;
  int l17_0;
  int l17_1;
  int l18_0;
  int l18_1;
  int l19_0;
  int l19_1;
  int l20_0;
  int l20_1;
  int l21_0;
  int l21_1;
  int l22_0;
  int l22_1;
  int l23_0;
  int l23_1;
  int l24_0;
  int l24_1;
  int l25_0;
  int l25_1;
  int l26_0;
  int l26_1;
  int l27_0;
  int l27_1;
  int l28_0;
  int l28_1;
  int l29_0;
  int l29_1;
  t1_0 = i7_0 ^ i4_0;
  t1_1 = i7_1 ^ i4_1;
  t2_0 = i7_0 ^ i2_0;
  t2_1 = i7_1 ^ i2_1;
  t3_0 = i7_0 ^ i1_0;
  t3_1 = i7_1 ^ i1_1;
  t4_0 = i4_0 ^ i2_0;
  t4_1 = i4_1 ^ i2_1;
  t5_0 = i3_0 ^ i1_0;
  t5_1 = i3_1 ^ i1_1;
  t6_0 = t1_0 ^ t5_0;
  t6_1 = t1_1 ^ t5_1;
  t7_0 = i6_0 ^ i5_0;
  t7_1 = i6_1 ^ i5_1;
  t8_0 = i0_0 ^ t6_0;
  t8_1 = i0_1 ^ t6_1;
  t9_0 = i0_0 ^ t7_0;
  t9_1 = i0_1 ^ t7_1;
  t10_0 = t6_0 ^ t7_0;
  t10_1 = t6_1 ^ t7_1;
  t11_0 = i6_0 ^ i2_0;
  t11_1 = i6_1 ^ i2_1;
  t12_0 = i5_0 ^ i2_0;
  t12_1 = i5_1 ^ i2_1;
  t13_0 = t3_0 ^ t4_0;
  t13_1 = t3_1 ^ t4_1;
  t14_0 = t6_0 ^ t11_0;
  t14_1 = t6_1 ^ t11_1;
  t15_0 = t5_0 ^ t11_0;
  t15_1 = t5_1 ^ t11_1;
  t16_0 = t5_0 ^ t12_0;
  t16_1 = t5_1 ^ t12_1;
  t17_0 = t9_0 ^ t16_0;
  t17_1 = t9_1 ^ t16_1;
  t18_0 = i4_0 ^ i0_0;
  t18_1 = i4_1 ^ i0_1;
  t19_0 = t7_0 ^ t18_0;
  t19_1 = t7_1 ^ t18_1;
  t20_0 = t1_0 ^ t19_0;
  t20_1 = t1_1 ^ t19_1;
  t21_0 = i1_0 ^ i0_0;
  t21_1 = i1_1 ^ i0_1;
  t22_0 = t7_0 ^ t21_0;
  t22_1 = t7_1 ^ t21_1;
  t23_0 = t2_0 ^ t22_0;
  t23_1 = t2_1 ^ t22_1;
  t24_0 = t2_0 ^ t10_0;
  t24_1 = t2_1 ^ t10_1;
  t25_0 = t20_0 ^ t17_0;
  t25_1 = t20_1 ^ t17_1;
  t26_0 = t3_0 ^ t16_0;
  t26_1 = t3_1 ^ t16_1;
  t27_0 = t1_0 ^ t12_0;
  t27_1 = t1_1 ^ t12_1;
  HPC3(t6_0, t6_1, t13_0, t13_1, &m1_0, &m1_1, rand_1, rand_2);
  HPC3(t8_0, t8_1, t23_0, t23_1, &m2_0, &m2_1, rand_3, rand_4);
  m3_0 = t14_0 ^ m1_0;
  m3_1 = t14_1 ^ m1_1;
  HPC3(i0_0, i0_1, t19_0, t19_1, &m4_0, &m4_1, rand_5, rand_6);
  m5_0 = m4_0 ^ m1_0;
  m5_1 = m4_1 ^ m1_1;
  HPC3(t16_0, t16_1, t3_0, t3_1, &m6_0, &m6_1, rand_7, rand_8);
  HPC3(t9_0, t9_1, t22_0, t22_1, &m7_0, &m7_1, rand_9, rand_10);
  m8_0 = t26_0 ^ m6_0;
  m8_1 = t26_1 ^ m6_1;
  HPC3(t17_0, t17_1, t20_0, t20_1, &m9_0, &m9_1, rand_11, rand_12);
  m10_0 = m9_0 ^ m6_0;
  m10_1 = m9_1 ^ m6_1;
  HPC3(t15_0, t15_1, t1_0, t1_1, &m11_0, &m11_1, rand_13, rand_14);
  HPC3(t27_0, t27_1, t4_0, t4_1, &m12_0, &m12_1, rand_15, rand_16);
  m13_0 = m12_0 ^ m11_0;
  m13_1 = m12_1 ^ m11_1;
  HPC3(t10_0, t10_1, t2_0, t2_1, &m14_0, &m14_1, rand_17, rand_18);
  m15_0 = m14_0 ^ m11_0;
  m15_1 = m14_1 ^ m11_1;
  m16_0 = m3_0 ^ m2_0;
  m16_1 = m3_1 ^ m2_1;
  m17_0 = m5_0 ^ t24_0;
  m17_1 = m5_1 ^ t24_1;
  m18_0 = m8_0 ^ m7_0;
  m18_1 = m8_1 ^ m7_1;
  m19_0 = m10_0 ^ m15_0;
  m19_1 = m10_1 ^ m15_1;
  m20_0 = m16_0 ^ m13_0;
  m20_1 = m16_1 ^ m13_1;
  m21_0 = m17_0 ^ m15_0;
  m21_1 = m17_1 ^ m15_1;
  m22_0 = m18_0 ^ m13_0;
  m22_1 = m18_1 ^ m13_1;
  m23_0 = m19_0 ^ t25_0;
  m23_1 = m19_1 ^ t25_1;
  m24_0 = m22_0 ^ m23_0;
  m24_1 = m22_1 ^ m23_1;
  HPC3(m20_0, m20_1, m22_0, m22_1, &m25_0, &m25_1, rand_19, rand_20);
  m26_0 = m21_0 ^ m25_0;
  m26_1 = m21_1 ^ m25_1;
  m27_0 = m20_0 ^ m21_0;
  m27_1 = m20_1 ^ m21_1;
  m28_0 = m23_0 ^ m25_0;
  m28_1 = m23_1 ^ m25_1;
  HPC2(m28_0, m28_1, m27_0, m27_1, &m29_0, &m29_1, rand_21);
  HPC2(m26_0, m26_1, m24_0, m24_1, &m30_0, &m30_1, rand_22);
  HPC3(m23_0, m23_1, m20_0, m20_1, &m31_0, &m31_1, rand_23, rand_24);
  HPC2(m27_0, m27_1, m31_0, m31_1, &m32_0, &m32_1, rand_25);
  m33_0 = m27_0 ^ m25_0;
  m33_1 = m27_1 ^ m25_1;
  HPC3(m22_0, m22_1, m21_0, m21_1, &m34_0, &m34_1, rand_26, rand_27);
  HPC2(m24_0, m24_1, m34_0, m34_1, &m35_0, &m35_1, rand_28);
  m36_0 = m24_0 ^ m25_0;
  m36_1 = m24_1 ^ m25_1;
  m37_0 = m21_0 ^ m29_0;
  m37_1 = m21_1 ^ m29_1;
  m38_0 = m32_0 ^ m33_0;
  m38_1 = m32_1 ^ m33_1;
  m39_0 = m23_0 ^ m30_0;
  m39_1 = m23_1 ^ m30_1;
  m40_0 = m35_0 ^ m36_0;
  m40_1 = m35_1 ^ m36_1;
  m41_0 = m38_0 ^ m40_0;
  m41_1 = m38_1 ^ m40_1;
  m42_0 = m37_0 ^ m39_0;
  m42_1 = m37_1 ^ m39_1;
  m43_0 = m37_0 ^ m38_0;
  m43_1 = m37_1 ^ m38_1;
  m44_0 = m39_0 ^ m40_0;
  m44_1 = m39_1 ^ m40_1;
  m45_0 = m42_0 ^ m41_0;
  m45_1 = m42_1 ^ m41_1;
  HPC2(m44_0, m44_1, t6_0, t6_1, &m46_0, &m46_1, rand_29);
  HPC2(m40_0, m40_1, t8_0, t8_1, &m47_0, &m47_1, rand_30);
  HPC2(m39_0, m39_1, i0_0, i0_1, &m48_0, &m48_1, rand_31);
  HPC2(m43_0, m43_1, t16_0, t16_1, &m49_0, &m49_1, rand_32);
  HPC2(m38_0, m38_1, t9_0, t9_1, &m50_0, &m50_1, rand_33);
  HPC2(m37_0, m37_1, t17_0, t17_1, &m51_0, &m51_1, rand_34);
  HPC2(m42_0, m42_1, t15_0, t15_1, &m52_0, &m52_1, rand_35);
  HPC2(m45_0, m45_1, t27_0, t27_1, &m53_0, &m53_1, rand_36);
  HPC2(m41_0, m41_1, t10_0, t10_1, &m54_0, &m54_1, rand_37);
  HPC2(m44_0, m44_1, t13_0, t13_1, &m55_0, &m55_1, rand_38);
  HPC2(m40_0, m40_1, t23_0, t23_1, &m56_0, &m56_1, rand_39);
  HPC2(m39_0, m39_1, t19_0, t19_1, &m57_0, &m57_1, rand_40);
  HPC2(m43_0, m43_1, t3_0, t3_1, &m58_0, &m58_1, rand_41);
  HPC2(m38_0, m38_1, t22_0, t22_1, &m59_0, &m59_1, rand_42);
  HPC2(m37_0, m37_1, t20_0, t20_1, &m60_0, &m60_1, rand_43);
  HPC2(m42_0, m42_1, t1_0, t1_1, &m61_0, &m61_1, rand_44);
  HPC2(m45_0, m45_1, t4_0, t4_1, &m62_0, &m62_1, rand_45);
  HPC2(m41_0, m41_1, t2_0, t2_1, &m63_0, &m63_1, rand_46);
  l0_0 = m61_0 ^ m62_0;
  l0_1 = m61_1 ^ m62_1;
  l1_0 = m50_0 ^ m56_0;
  l1_1 = m50_1 ^ m56_1;
  l2_0 = m46_0 ^ m48_0;
  l2_1 = m46_1 ^ m48_1;
  l3_0 = m47_0 ^ m55_0;
  l3_1 = m47_1 ^ m55_1;
  l4_0 = m54_0 ^ m58_0;
  l4_1 = m54_1 ^ m58_1;
  l5_0 = m49_0 ^ m61_0;
  l5_1 = m49_1 ^ m61_1;
  l6_0 = m62_0 ^ l5_0;
  l6_1 = m62_1 ^ l5_1;
  l7_0 = m46_0 ^ l3_0;
  l7_1 = m46_1 ^ l3_1;
  l8_0 = m51_0 ^ m59_0;
  l8_1 = m51_1 ^ m59_1;
  l9_0 = m52_0 ^ m53_0;
  l9_1 = m52_1 ^ m53_1;
  l10_0 = m53_0 ^ l4_0;
  l10_1 = m53_1 ^ l4_1;
  l11_0 = m60_0 ^ l2_0;
  l11_1 = m60_1 ^ l2_1;
  l12_0 = m48_0 ^ m51_0;
  l12_1 = m48_1 ^ m51_1;
  l13_0 = m50_0 ^ l0_0;
  l13_1 = m50_1 ^ l0_1;
  l14_0 = m52_0 ^ m61_0;
  l14_1 = m52_1 ^ m61_1;
  l15_0 = m55_0 ^ l1_0;
  l15_1 = m55_1 ^ l1_1;
  l16_0 = m56_0 ^ l0_0;
  l16_1 = m56_1 ^ l0_1;
  l17_0 = m57_0 ^ l1_0;
  l17_1 = m57_1 ^ l1_1;
  l18_0 = m58_0 ^ l8_0;
  l18_1 = m58_1 ^ l8_1;
  l19_0 = m63_0 ^ l4_0;
  l19_1 = m63_1 ^ l4_1;
  l20_0 = l0_0 ^ l1_0;
  l20_1 = l0_1 ^ l1_1;
  l21_0 = l1_0 ^ l7_0;
  l21_1 = l1_1 ^ l7_1;
  l22_0 = l3_0 ^ l12_0;
  l22_1 = l3_1 ^ l12_1;
  l23_0 = l18_0 ^ l2_0;
  l23_1 = l18_1 ^ l2_1;
  l24_0 = l15_0 ^ l9_0;
  l24_1 = l15_1 ^ l9_1;
  l25_0 = l6_0 ^ l10_0;
  l25_1 = l6_1 ^ l10_1;
  l26_0 = l7_0 ^ l9_0;
  l26_1 = l7_1 ^ l9_1;
  l27_0 = l8_0 ^ l10_0;
  l27_1 = l8_1 ^ l10_1;
  l28_0 = l11_0 ^ l14_0;
  l28_1 = l11_1 ^ l14_1;
  l29_0 = l11_0 ^ l17_0;
  l29_1 = l11_1 ^ l17_1;
  *o7_0 = l6_0 ^ l24_0;
  *o7_1 = l6_1 ^ l24_1;
  *o6_0 = l16_0 ^ l26_0;
  *o6_1 = !(l16_1 ^ l26_1);
  *o5_0 = l19_0 ^ l28_0;
  *o5_1 = !(l19_1 ^ l28_1);
  *o4_0 = l6_0 ^ l21_0;
  *o4_1 = l6_1 ^ l21_1;
  *o3_0 = l20_0 ^ l22_0;
  *o3_1 = l20_1 ^ l22_1;
  *o2_0 = l25_0 ^ l29_0;
  *o2_1 = l25_1 ^ l29_1;
  *o1_0 = l13_0 ^ l27_0;
  *o1_1 = !(l13_1 ^ l27_1);
  *o0_0 = l6_0 ^ l23_0;
  *o0_1 = !(l6_1 ^ l23_1);
}






// --- 3. Verification Logic ---
int main() {
    int error_count = 0;

    printf("Starting verification for 256 inputs (8-bit S-Box)...\n");

    for(int i = 0; i < 256; i++) {
        int x[8];
        for(int b=0; b<8; b++) x[b] = (i >> b) & 1;

        int y_gold[8] = {0};
        sbox_golden(x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], 0, &y_gold[0], &y_gold[1], &y_gold[2], &y_gold[3], &y_gold[4], &y_gold[5], &y_gold[6], &y_gold[7]);

        int x_sh0[8];
        int x_sh1[8];
        for(int b=0; b<8; b++) {
            x_sh0[b] = x[b];
            x_sh1[b] = 0; 
        }

        int y_masked_sh0[8] = {0};
        int y_masked_sh1[8] = {0};
        
        sbox_masked(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        int y_final[8];
        int mismatch = 0;
        for(int b=0; b<8; b++) {
            // Mask with & 1 to safely truncate integers back to 1/0
            y_final[b] = (y_masked_sh0[b] ^ y_masked_sh1[b]) & 1;
            y_gold[b] = y_gold[b] & 1;
            
            if(y_final[b] != y_gold[b]) mismatch = 1;
        }

        if(mismatch) {
            printf("[FAILED] Input: %d (0x%0X) | Expected: ", i, i);
            for(int b=8-1; b>=0; b--) printf("%d", y_gold[b]);
            printf(" | Got: ");
            for(int b=8-1; b>=0; b--) printf("%d", y_final[b]);
            printf("\n");
            error_count++;
        }
    }

    if(error_count == 0) {
        printf("\n[SUCCESS] All 256 inputs matched perfectly! Ground Truth verified.\n");
    } else {
        printf("\n[FAILURE] Total errors: %d\n", error_count);
    }

    return error_count > 0 ? 1 : 0;
}
    