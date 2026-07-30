#include <stdbool.h>

/* --- GF(2^2) --- */
void G4_mul(bool m4_x0, bool m4_x1, bool m4_y0, bool m4_y1, bool *m4_p0, bool *m4_p1) {
    bool m4_ab, m4_cd, m4_e;
    m4_ab = m4_x1 ^ m4_x0;
    m4_cd = m4_y1 ^ m4_y0;
    m4_e = m4_ab & m4_cd;
    *m4_p1 = (m4_x1 & m4_y1) ^ m4_e; 
    *m4_p0 = (m4_x0 & m4_y0) ^ m4_e;
}

void G4_scl_N(bool sn4_x0, bool sn4_x1, bool *sn4_p0, bool *sn4_p1) {
    *sn4_p1 = sn4_x0; 
    *sn4_p0 = sn4_x1 ^ sn4_x0;
}

void G4_scl_N2(bool sn24_x0, bool sn24_x1, bool *sn24_p0, bool *sn24_p1) {
    *sn24_p1 = sn24_x1 ^ sn24_x0; 
    *sn24_p0 = sn24_x1;
}

void G4_sq(bool sq4_x0, bool sq4_x1, bool *sq4_p0, bool *sq4_p1) {
    *sq4_p1 = sq4_x0; 
    *sq4_p0 = sq4_x1;
}

/* --- GF(2^4) --- */
void G16_mul(bool m16_x0, bool m16_x1, bool m16_x2, bool m16_x3, 
             bool m16_y0, bool m16_y1, bool m16_y2, bool m16_y3,
             bool *m16_p0, bool *m16_p1, bool *m16_p2, bool *m16_p3) {
    // Added s1/s2 to differentiate assignment stages
    bool m16_tx0, m16_tx1, m16_ty0, m16_ty1, m16_e0_s1, m16_e1_s1, m16_e0_s2, m16_e1_s2, m16_ph0, m16_ph1, m16_ql0, m16_ql1;
    
    m16_tx0 = m16_x2 ^ m16_x0;
    m16_tx1 = m16_x3 ^ m16_x1;
    m16_ty0 = m16_y2 ^ m16_y0;
    m16_ty1 = m16_y3 ^ m16_y1;
    
    G4_mul(m16_tx0, m16_tx1, m16_ty0, m16_ty1, &m16_e0_s1, &m16_e1_s1);
    G4_scl_N(m16_e0_s1, m16_e1_s1, &m16_e0_s2, &m16_e1_s2); // Unique output variables
    
    G4_mul(m16_x2, m16_x3, m16_y2, m16_y3, &m16_ph0, &m16_ph1);
    G4_mul(m16_x0, m16_x1, m16_y0, m16_y1, &m16_ql0, &m16_ql1);
    
    *m16_p3 = m16_ph1 ^ m16_e1_s2; 
    *m16_p2 = m16_ph0 ^ m16_e0_s2;
    *m16_p1 = m16_ql1 ^ m16_e1_s2; 
    *m16_p0 = m16_ql0 ^ m16_e0_s2;
}

void G16_sq_scl(bool ss16_x0, bool ss16_x1, bool ss16_x2, bool ss16_x3,
                bool *ss16_p0, bool *ss16_p1, bool *ss16_p2, bool *ss16_p3) {
    bool ss16_tx0, ss16_tx1, ss16_ph0, ss16_ph1, ss16_ql0_s1, ss16_ql1_s1, ss16_ql0_s2, ss16_ql1_s2;
    
    ss16_tx0 = ss16_x2 ^ ss16_x0;
    ss16_tx1 = ss16_x3 ^ ss16_x1;
    
    G4_sq(ss16_tx0, ss16_tx1, &ss16_ph0, &ss16_ph1);
    G4_sq(ss16_x0, ss16_x1, &ss16_ql0_s1, &ss16_ql1_s1);
    G4_scl_N2(ss16_ql0_s1, ss16_ql1_s1, &ss16_ql0_s2, &ss16_ql1_s2); // Unique output
    
    *ss16_p3 = ss16_ph1; 
    *ss16_p2 = ss16_ph0;
    *ss16_p1 = ss16_ql1_s2; 
    *ss16_p0 = ss16_ql0_s2;
}

void G16_inv(bool i16_x0, bool i16_x1, bool i16_x2, bool i16_x3,
             bool *i16_p0, bool *i16_p1, bool *i16_p2, bool *i16_p3) {
    bool i16_tx0, i16_tx1, i16_c0_s1, i16_c1_s1, i16_c0_s2, i16_c1_s2, i16_d0, i16_d1, i16_te0, i16_te1, i16_e0, i16_e1, i16_ph0, i16_ph1, i16_ql0, i16_ql1;
    
    i16_tx0 = i16_x2 ^ i16_x0;
    i16_tx1 = i16_x3 ^ i16_x1;
    
    G4_sq(i16_tx0, i16_tx1, &i16_c0_s1, &i16_c1_s1);
    G4_scl_N(i16_c0_s1, i16_c1_s1, &i16_c0_s2, &i16_c1_s2); // Unique output
    G4_mul(i16_x2, i16_x3, i16_x0, i16_x1, &i16_d0, &i16_d1);
    
    i16_te0 = i16_c0_s2 ^ i16_d0;
    i16_te1 = i16_c1_s2 ^ i16_d1;
    
    G4_sq(i16_te0, i16_te1, &i16_e0, &i16_e1);
    G4_mul(i16_e0, i16_e1, i16_x0, i16_x1, &i16_ph0, &i16_ph1);
    G4_mul(i16_e0, i16_e1, i16_x2, i16_x3, &i16_ql0, &i16_ql1);
    
    *i16_p3 = i16_ph1; 
    *i16_p2 = i16_ph0;
    *i16_p1 = i16_ql1; 
    *i16_p0 = i16_ql0;
}

/* --- GF(2^8) Inversion stays the same as it doesn't reuse intermediates --- */
void G256_inv(bool i256_x0, bool i256_x1, bool i256_x2, bool i256_x3, bool i256_x4, bool i256_x5, bool i256_x6, bool i256_x7,
              bool *i256_p0, bool *i256_p1, bool *i256_p2, bool *i256_p3, bool *i256_p4, bool *i256_p5, bool *i256_p6, bool *i256_p7) {
    bool i256_tx0, i256_tx1, i256_tx2, i256_tx3, i256_c0, i256_c1, i256_c2, i256_c3, i256_d0, i256_d1, i256_d2, i256_d3;
    bool i256_te0, i256_te1, i256_te2, i256_te3, i256_e0, i256_e1, i256_e2, i256_e3;
    bool i256_ph0, i256_ph1, i256_ph2, i256_ph3, i256_ql0, i256_ql1, i256_ql2, i256_ql3;
    
    i256_tx0 = i256_x4 ^ i256_x0;
    i256_tx1 = i256_x5 ^ i256_x1;
    i256_tx2 = i256_x6 ^ i256_x2;
    i256_tx3 = i256_x7 ^ i256_x3;
    G16_sq_scl(i256_tx0, i256_tx1, i256_tx2, i256_tx3, &i256_c0, &i256_c1, &i256_c2, &i256_c3);
    G16_mul(i256_x4, i256_x5, i256_x6, i256_x7, i256_x0, i256_x1, i256_x2, i256_x3, &i256_d0, &i256_d1, &i256_d2, &i256_d3);
    i256_te0 = i256_c0 ^ i256_d0;
    i256_te1 = i256_c1 ^ i256_d1;
    i256_te2 = i256_c2 ^ i256_d2;
    i256_te3 = i256_c3 ^ i256_d3;
    G16_inv(i256_te0, i256_te1, i256_te2, i256_te3, &i256_e0, &i256_e1, &i256_e2, &i256_e3);
    G16_mul(i256_e0, i256_e1, i256_e2, i256_e3, i256_x0, i256_x1, i256_x2, i256_x3, &i256_ph0, &i256_ph1, &i256_ph2, &i256_ph3);
    G16_mul(i256_e0, i256_e1, i256_e2, i256_e3, i256_x4, i256_x5, i256_x6, i256_x7, &i256_ql0, &i256_ql1, &i256_ql2, &i256_ql3);
    *i256_p7 = i256_ph3; *i256_p6 = i256_ph2; *i256_p5 = i256_ph1; *i256_p4 = i256_ph0;
    *i256_p3 = i256_ql3; *i256_p2 = i256_ql2; *i256_p1 = i256_ql1; *i256_p0 = i256_ql0;
}

/* --- Main S-Box Function --- */

void sbox(bool sb_n0, bool sb_n1, bool sb_n2, bool sb_n3, bool sb_n4, bool sb_n5, bool sb_n6, bool sb_n7,
          bool *sb_o0, bool *sb_o1, bool *sb_o2, bool *sb_o3, bool *sb_o4, bool *sb_o5, bool *sb_o6, bool *sb_o7) {
    
    // Declare all intermediate variables first
    bool sb_y0, sb_y1, sb_y2, sb_y3, sb_y4, sb_y5, sb_y6, sb_y7;
    bool sb_i0, sb_i1, sb_i2, sb_i3, sb_i4, sb_i5, sb_i6, sb_i7;
    bool fy0, fy1, fy2, fy3, fy4, fy5, fy6, fy7;

    // --- Step 1: Normal Basis Transformation (Unrolled A2X) ---
    // Instead of 'if', we use XOR. Each y bit is a linear combination of input bits.
    sb_y0 = sb_n0 ^ sb_n1 ^ sb_n2 ^ sb_n3 ^ sb_n6;
    sb_y1 = sb_n0 ^ sb_n5 ^ sb_n6;
    sb_y2 = sb_n0;
    sb_y3 = sb_n0 ^ sb_n1 ^ sb_n3 ^ sb_n4 ^ sb_n7;
    sb_y4 = sb_n0 ^ sb_n5 ^ sb_n6 ^ sb_n7;
    sb_y5 = sb_n0 ^ sb_n1 ^ sb_n5 ^ sb_n6;
    sb_y6 = sb_n0 ^ sb_n4 ^ sb_n5 ^ sb_n6;
    sb_y7 = sb_n0 ^ sb_n1 ^ sb_n2 ^ sb_n5 ^ sb_n6 ^ sb_n7;

    // --- Step 2: Core Inversion ---
    G256_inv(sb_y0, sb_y1, sb_y2, sb_y3, sb_y4, sb_y5, sb_y6, sb_y7, 
             &sb_i0, &sb_i1, &sb_i2, &sb_i3, &sb_i4, &sb_i5, &sb_i6, &sb_i7);

    // --- Step 3: Standard Basis Transformation (Unrolled X2S) ---
    // Mapping the results of inversion back to standard basis shares.
    fy0 = sb_i1 ^ sb_i4 ^ sb_i6;
    fy1 = sb_i1 ^ sb_i4 ^ sb_i5;
    fy2 = sb_i0 ^ sb_i2 ^ sb_i3 ^ sb_i5 ^ sb_i6;
    fy3 = sb_i3 ^ sb_i4 ^ sb_i5 ^ sb_i6 ^ sb_i7;
    fy4 = sb_i3 ^ sb_i5 ^ sb_i7;
    fy5 = sb_i0 ^ sb_i6;
    fy6 = sb_i3 ^ sb_i7;
    fy7 = sb_i3 ^ sb_i5;

    // --- Step 4: Final Affine XOR (0x63 = 0110 0011) ---
    *sb_o0 = fy0 ^ 1;
    *sb_o1 = fy1 ^ 1;
    *sb_o2 = fy2 ;
    *sb_o3 = fy3 ;
    *sb_o4 = fy4 ;
    *sb_o5 = fy5 ^ 1;
    *sb_o6 = fy6 ^ 1;
    *sb_o7 = fy7 ;
}