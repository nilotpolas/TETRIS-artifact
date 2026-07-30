#include <stdbool.h>

void sbox(
    bool i0, bool i1, bool i2, bool i3, 
    bool i4, bool i5, bool i6, bool i7, bool dec_1,
    bool *y0, bool *y1, bool *y2, bool *y3, 
    bool *y4, bool *y5, bool *y6, bool *y7) 
{
    // --- Top linear transform ---
    bool t1  = i7 ^ i4;
    bool t2  = i7 ^ i2;
    bool t3  = i7 ^ i1;
    bool t4  = i4 ^ i2;
    bool t5  = i3 ^ i1;
    bool t6  = t1 ^ t5;
    bool t7  = i6 ^ i5;

    bool t8  = i0 ^ t6;
    bool t9  = i0 ^ t7;
    bool t10 = t6 ^ t7;
    bool t11 = i6 ^ i2;
    bool t12 = i5 ^ i2;
    bool t13 = t3 ^ t4;
    bool t14 = t6 ^ t11;

    bool t15 = t5 ^ t11;
    bool t16 = t5 ^ t12;
    bool t17 = t9 ^ t16;
    bool t18 = i4 ^ i0;
    bool t19 = t7 ^ t18;
    bool t20 = t1 ^ t19;
    bool t21 = i1 ^ i0;

    bool t22 = t7 ^ t21;
    bool t23 = t2 ^ t22;
    bool t24 = t2 ^ t10;
    bool t25 = t20 ^ t17;
    bool t26 = t3 ^ t16;
    bool t27 = t1 ^ t12;

    // --- Shared part of the AES S-box ---
    bool m1  = t13 & t6;
    bool m2  = t23 & t8;
    bool m3  = t14 ^ m1;
    bool m4  = t19 & i0;
    bool m5  = m4 ^ m1;
    bool m6  = t3 & t16;
    bool m7  = t22 & t9;
    bool m8  = t26 ^ m6;
    bool m9  = t20 & t17;
    bool m10 = m9 ^ m6;
    bool m11 = t1 & t15;
    bool m12 = t4 & t27;
    bool m13 = m12 ^ m11;
    bool m14 = t2 & t10;
    bool m15 = m14 ^ m11;
    bool m16 = m3 ^ m2;

    bool m17 = m5 ^ t24;
    bool m18 = m7 ^ m8;
    bool m19 = m10 ^ m15;
    bool m20 = m16 ^ m13;
    bool m21 = m17 ^ m15;
    bool m22 = m18 ^ m13;
    bool m23 = m19 ^ t25;
    bool m24 = m22 ^ m23;
    bool m25 = m22 & m20;
    bool m26 = m21 ^ m25;
    bool m27 = m20 ^ m21;
    bool m28 = m23 ^ m25;
    bool m29 = m28 & m27;
    bool m30 = m26 & m24;
    bool m31 = m20 & m23;
    bool m32 = m27 & m31;

    bool m33 = m27 ^ m25;
    bool m34 = m21 & m22;
    bool m35 = m24 & m34;
    bool m36 = m24 ^ m25;
    bool m37 = m21 ^ m29;
    bool m38 = m32 ^ m33;
    bool m39 = m23 ^ m30;
    bool m40 = m35 ^ m36;
    bool m41 = m38 ^ m40;
    bool m42 = m37 ^ m39;
    bool m43 = m37 ^ m38;
    bool m44 = m39 ^ m40;
    bool m45 = m42 ^ m41;
    bool m46 = m44 & t6;
    bool m47 = m40 & t8;
    bool m48 = m39 & i0;

    bool m49 = m43 & t16;
    bool m50 = m38 & t9;
    bool m51 = m37 & t17;
    bool m52 = m42 & t15;
    bool m53 = m45 & t27;
    bool m54 = m41 & t10;
    bool m55 = m44 & t13;
    bool m56 = m40 & t23;
    bool m57 = m39 & t19;
    bool m58 = m43 & t3;
    bool m59 = m38 & t22;
    bool m60 = m37 & t20;
    bool m61 = m42 & t1;
    bool m62 = m45 & t4;
    bool m63 = m41 & t2;

    // --- Bottom linear transform ---
    bool l0  = m61 ^ m62;
    bool l1  = m50 ^ m56;
    bool l2  = m46 ^ m48;
    bool l3  = m47 ^ m55;
    bool l4  = m54 ^ m58;
    bool l5  = m49 ^ m61;
    bool l6  = m62 ^ l5;
    bool l7  = m46 ^ l3;
    bool l8  = m51 ^ m59;
    bool l9  = m52 ^ m53;

    bool l10 = m53 ^ l4;
    bool l11 = m60 ^ l2;
    bool l12 = m48 ^ m51;
    bool l13 = m50 ^ l0;
    bool l14 = m52 ^ m61;
    bool l15 = m55 ^ l1;
    bool l16 = m56 ^ l0;
    bool l17 = m57 ^ l1;
    bool l18 = m58 ^ l8;
    bool l19 = m63 ^ l4;

    bool l20 = l0 ^ l1;
    bool l21 = l1 ^ l7;
    bool l22 = l3 ^ l12;
    bool l23 = l18 ^ l2;
    bool l24 = l15 ^ l9;
    bool l25 = l6 ^ l10;
    bool l26 = l7 ^ l9;
    bool l27 = l8 ^ l10;
    bool l28 = l11 ^ l14;
    bool l29 = l11 ^ l17;

    // --- Outputs ---
    *y7 = l6 ^ l24;
    bool l30 = l16 ^ l26;
    *y6 = l30 ^ dec_1; // XNOR
    bool l31 = l19 ^ l28;
    *y5 = l31 ^ dec_1; // XNOR
    *y4 = l6 ^ l21;
    *y3 = l20 ^ l22;
    *y2 = l25 ^ l29;
    bool l32 = l13 ^ l27;
    *y1 = l32 ^ dec_1; // XNOR
    bool l33 = l6 ^ l23;
    *y0 = l33 ^ dec_1;  // XNOR
}