// // #include <stdio.h>
// #include <stdbool.h>
// void sbox (bool X0, bool X1, bool X2, bool X3, bool X4, bool X5, bool X6, bool X7,bool dec_1, bool *Y0, bool *Y1, bool *Y2, bool *Y3, bool *Y4, bool *Y5, bool *Y6, bool *Y7) {
	

// 	//declare T signals
// 	bool T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27;

// 	//declare M signals
// 	bool M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,
//     M11, M12, M13, M14, M15, M16, M17, M18, M19, M20,
//     M21, M22, M23, M24, M25, M26, M27, M28, M29, M30,
//     M31, M32, M33, M34, M35, M36, M37, M38, M39, M40,
//     M41, M42, M43, M44, M45, M46, M47, M48, M49, M50,
//     M51, M52, M53, M54, M55, M56, M57, M58, M59, M60,
//     M61, M62, M63;

// 	//declare L signals
// 	bool L0, L1, L2, L3, L4, L5, L6, L7, L8, L9,
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
// 	bool temp1 = L16 ^ L26;
//     *Y1 = temp1 ^ dec_1;  // XNOR
// 	bool temp2 = L19 ^ L28;
//     *Y2 = temp2 ^ dec_1;  // XNOR
//     *Y3 = L6 ^ L21;
//     *Y4 = L20 ^ L22;
//     *Y5 = L25 ^ L29;
// 	bool temp3 = L13 ^ L27;
//     *Y6 = temp3 ^ dec_1;  // XNOR
// 	bool temp4 = L6 ^ L23;
//     *Y7 = temp4 ^ dec_1;   // XNOR
// }
// // #include <stdio.h>
// #include <stdbool.h>
// void sbox (bool X0, bool X1, bool X2, bool X3, bool X4, bool X5, bool X6, bool X7, bool *Y0, bool *Y1, bool *Y2, bool *Y3, bool *Y4, bool *Y5, bool *Y6, bool *Y7, bool dec_1) {
	

// 	//declare T signals
// 	bool T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27;

// 	//declare M signals
// 	bool M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,
//     M11, M12, M13, M14, M15, M16, M17, M18, M19, M20,
//     M21, M22, M23, M24, M25, M26, M27, M28, M29, M30,
//     M31, M32, M33, M34, M35, M36, M37, M38, M39, M40,
//     M41, M42, M43, M44, M45, M46, M47, M48, M49, M50,
//     M51, M52, M53, M54, M55, M56, M57, M58, M59, M60,
//     M61, M62, M63;

// 	//declare L signals
// 	bool L0, L1, L2, L3, L4, L5, L6, L7, L8, L9,
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
// 	bool temp1 = L16 ^ L26;
//     *Y1 = temp1 ^ dec_1;  // XNOR
// 	bool temp2 = L19 ^ L28;
//     *Y2 = temp2 ^ dec_1;  // XNOR
//     *Y3 = L6 ^ L21;
//     *Y4 = L20 ^ L22;
//     *Y5 = L25 ^ L29;
// 	bool temp3 = L13 ^ L27;
//     *Y6 = temp3 ^ dec_1;  // XNOR
// 	bool temp4 = L6 ^ L23;
//     *Y7 = temp4 ^ dec_1;   // XNOR
// }





#include <stdbool.h>

void sbox(
    bool i0, bool i1, bool i2, bool i3, bool i4, bool i5, bool i6, bool i7,
    bool *o0, bool *o1, bool *o2, bool *o3, bool *o4, bool *o5, bool *o6, bool *o7
) {
    // 1. Declare intermediate variables first
    bool t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27;
    bool m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43, m44, m45, m46, m47, m48, m49, m50, m51, m52, m53, m54, m55, m56, m57, m58, m59, m60, m61, m62, m63;
    bool l0, l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15, l16, l17, l18, l19, l20, l21, l22, l23, l24, l25, l26, l27, l28, l29;

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