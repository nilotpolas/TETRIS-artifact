#include <stdbool.h>

void G4_mul(_Bool x0, _Bool x1, _Bool y0, _Bool y1, _Bool *p0, _Bool *p1) {
    _Bool e, p, q;
    e = (x1 ^ x0) & (y1 ^ y0);
    p = (x1 & y1) ^ e;
    q = (x0 & y0) ^ e;
    *p0 = q;
    *p1 = p;
}

void G4_scl_N(_Bool x0, _Bool x1, _Bool *p0, _Bool *p1) {
    _Bool q = x1 ^ x0;
    *p0 = q;
    *p1 = x0;
}

void G4_scl_N2(_Bool x0, _Bool x1, _Bool *p0, _Bool *p1) {
    _Bool p = x1 ^ x0;
    *p0 = x1;
    *p1 = p;
}

void G4_sq(_Bool x0, _Bool x1, _Bool *p0, _Bool *p1) {
    *p0 = x1;
    *p1 = x0;
}

void G16_mul(_Bool x0, _Bool x1, _Bool x2, _Bool x3, 
             _Bool y0, _Bool y1, _Bool y2, _Bool y3,
             _Bool *p0, _Bool *p1, _Bool *p2, _Bool *p3) {
    _Bool e0, e1;
    _Bool p_tmp0, p_tmp1, q_tmp0, q_tmp1;
    _Bool e_scl0, e_scl1;
    _Bool temp_p0, temp_p1, temp_q0, temp_q1;

    _Bool ab0 = x2 ^ x0;
    _Bool ab1 = x3 ^ x1;
    _Bool cd0 = y2 ^ y0;
    _Bool cd1 = y3 ^ y1;
    G4_mul(ab0, ab1, cd0, cd1, &e0, &e1);
    G4_scl_N(e0, e1, &e_scl0, &e_scl1);

    G4_mul(x2, x3, y2, y3, &p_tmp0, &p_tmp1);
    G4_mul(x0, x1, y0, y1, &q_tmp0, &q_tmp1);

    temp_p0 = p_tmp0 ^ e_scl0;
    temp_p1 = p_tmp1 ^ e_scl1;
    temp_q0 = q_tmp0 ^ e_scl0;
    temp_q1 = q_tmp1 ^ e_scl1;

    *p0 = temp_q0;
    *p1 = temp_q1;
    *p2 = temp_p0;
    *p3 = temp_p1;
}

void G16_sq_scl(_Bool x0, _Bool x1, _Bool x2, _Bool x3,
                _Bool *p0, _Bool *p1, _Bool *p2, _Bool *p3) {
    _Bool ab0, ab1, p_tmp0, p_tmp1;
    _Bool b_sq0, b_sq1, q_tmp0, q_tmp1;

    ab0 = x2 ^ x0;
    ab1 = x3 ^ x1;
    G4_sq(ab0, ab1, &p_tmp0, &p_tmp1);

    G4_sq(x0, x1, &b_sq0, &b_sq1);
    G4_scl_N2(b_sq0, b_sq1, &q_tmp0, &q_tmp1);

    *p0 = q_tmp0;
    *p1 = q_tmp1;
    *p2 = p_tmp0;
    *p3 = p_tmp1;
}

void G16_inv(_Bool x0, _Bool x1, _Bool x2, _Bool x3,
             _Bool *p0, _Bool *p1, _Bool *p2, _Bool *p3) {
    _Bool ab0, ab1, ab_sq0, ab_sq1, c0, c1, d0, d1, cd0, cd1, e0, e1;
    _Bool p_tmp0, p_tmp1, q_tmp0, q_tmp1;

    ab0 = x2 ^ x0;
    ab1 = x3 ^ x1;
    G4_sq(ab0, ab1, &ab_sq0, &ab_sq1);
    G4_scl_N(ab_sq0, ab_sq1, &c0, &c1);

    G4_mul(x2, x3, x0, x1, &d0, &d1);

    cd0 = c0 ^ d0;
    cd1 = c1 ^ d1;
    G4_sq(cd0, cd1, &e0, &e1);

    G4_mul(e0, e1, x0, x1, &p_tmp0, &p_tmp1);
    G4_mul(e0, e1, x2, x3, &q_tmp0, &q_tmp1);

    *p0 = q_tmp0;
    *p1 = q_tmp1;
    *p2 = p_tmp0;
    *p3 = p_tmp1;
}

void G256_inv(_Bool x0, _Bool x1, _Bool x2, _Bool x3, _Bool x4, _Bool x5, _Bool x6, _Bool x7,
              _Bool *p0, _Bool *p1, _Bool *p2, _Bool *p3, _Bool *p4, _Bool *p5, _Bool *p6, _Bool *p7) {
    _Bool ab0, ab1, ab2, ab3, c0, c1, c2, c3, d0, d1, d2, d3;
    _Bool cd0, cd1, cd2, cd3, e0, e1, e2, e3;
    _Bool p_tmp0, p_tmp1, p_tmp2, p_tmp3, q_tmp0, q_tmp1, q_tmp2, q_tmp3;

    ab0 = x4 ^ x0; ab1 = x5 ^ x1; ab2 = x6 ^ x2; ab3 = x7 ^ x3;
    G16_sq_scl(ab0, ab1, ab2, ab3, &c0, &c1, &c2, &c3);

    G16_mul(x4, x5, x6, x7, x0, x1, x2, x3, &d0, &d1, &d2, &d3);

    cd0 = c0 ^ d0; cd1 = c1 ^ d1; cd2 = c2 ^ d2; cd3 = c3 ^ d3;
    G16_inv(cd0, cd1, cd2, cd3, &e0, &e1, &e2, &e3);

    G16_mul(e0, e1, e2, e3, x0, x1, x2, x3, &p_tmp0, &p_tmp1, &p_tmp2, &p_tmp3);
    G16_mul(e0, e1, e2, e3, x4, x5, x6, x7, &q_tmp0, &q_tmp1, &q_tmp2, &q_tmp3);

    *p0 = q_tmp0; *p1 = q_tmp1; *p2 = q_tmp2; *p3 = q_tmp3;
    *p4 = p_tmp0; *p5 = p_tmp1; *p6 = p_tmp2; *p7 = p_tmp3;
}


void sbox(_Bool n[8], _Bool out[8]) {
    _Bool t0, t1, t2, t3, t4, t5, t6, t7;
    _Bool inv0, inv1, inv2, inv3, inv4, inv5, inv6, inv7;
    _Bool y0, y1, y2, y3, y4, y5, y6, y7;
    _Bool final0, final1, final2, final3, final4, final5, final6, final7;

    y0 = y1 = y2 = y3 = y4 = y5 = y6 = y7 = 0;
    if (n[0]) { y0^=1; y1^=1; y2^=1; y3^=1; y4^=1; y5^=1; y6^=1; y7^=1; }
    if (n[1]) { y0^=1; y2^=1; y4^=1; y6^=1; }
    if (n[2]) { y0^=1; y7^=1; }
    if (n[3]) { y0^=1; y3^=1; }
    if (n[4]) { y3^=1; y4^=1; y7^=1; }
    if (n[5]) { y1^=1; y2^=1; y3^=1; y6^=1; y7^=1; }
    if (n[6]) { y0^=1; y1^=1; y2^=1; y3^=1; y6^=1; y7^=1; }
    if (n[7]) { y3^=1; y4^=1; y7^=1; }

    t0 = y0; t1 = y1; t2 = y2; t3 = y3; t4 = y4; t5 = y5; t6 = y6; t7 = y7;

    G256_inv(t0, t1, t2, t3, t4, t5, t6, t7, &inv0, &inv1, &inv2, &inv3, &inv4, &inv5, &inv6, &inv7);

    y0 = y1 = y2 = y3 = y4 = y5 = y6 = y7 = 0;
    if (inv0) { y2^=1; y5^=1; }
    if (inv1) { y0^=1; y1^=1; }
    if (inv2) { y2^=1; }
    if (inv3) { y2^=1; y3^=1; y4^=1; y5^=1; y7^=1; }
    if (inv4) { y0^=1; y1^=1; y3^=1; }
    if (inv5) { y1^=1; y2^=1; y3^=1; y4^=1; y7^=1; }
    if (inv6) { y0^=1; y2^=1; y3^=1; y5^=1; }
    if (inv7) { y3^=1; y4^=1; y6^=1; }

    final0 = y0 ^ 1;
    final1 = y1 ^ 1;
    final2 = y2 ^ 0;
    final3 = y3 ^ 0;
    final4 = y4 ^ 0;
    final5 = y5 ^ 1;
    final6 = y6 ^ 1;
    final7 = y7 ^ 0;

    out[0] = final0;
    out[1] = final1;
    out[2] = final2;
    out[3] = final3;
    out[4] = final4;
    out[5] = final5;
    out[6] = final6;
    out[7] = final7;
}


void xtime(bool x[8], bool y[8]) {
    bool b7 = x[7];
    bool xshifted[8];
    xshifted[0] = false;
    for (int b = 1; b < 8; b++) xshifted[b] = x[b-1];

    bool cst_0x1b[8] = {true, true, false, true, true, false, false, false};
    for (int b = 0; b < 8; b++) y[b] = xshifted[b] ^ (b7 & cst_0x1b[b]);
}

void MC_mul(bool v[8], bool vx2[8], bool vx3[8]) {
    xtime(v, vx2);
    for (int b = 0; b < 8; b++) vx3[b] = vx2[b] ^ v[b];
}

void MC_single_column(bool *in0, bool *in1, bool *in2, bool *in3,
                      bool *out0, bool *out1, bool *out2, bool *out3) {
    bool vx2_0[8], vx3_0[8];
    bool vx2_1[8], vx3_1[8];
    bool vx2_2[8], vx3_2[8];
    bool vx2_3[8], vx3_3[8];

    MC_mul(in0, vx2_0, vx3_0);
    MC_mul(in1, vx2_1, vx3_1);
    MC_mul(in2, vx2_2, vx3_2);
    MC_mul(in3, vx2_3, vx3_3);

    for (int b = 0; b < 8; b++) {
        out0[b] = vx2_0[b] ^ vx3_1[b] ^ in2[b] ^ in3[b];
        out1[b] = in0[b] ^ vx2_1[b] ^ vx3_2[b] ^ in3[b];
        out2[b] = in0[b] ^ in1[b] ^ vx2_2[b] ^ vx3_3[b];
        out3[b] = vx3_0[b] ^ in1[b] ^ in2[b] ^ vx2_3[b];
    }
}

void MC_umsk(bool state_in[128], bool state_out[128]) {
    bool state_bytes[128];
    for (int i = 0; i < 128; i++) state_bytes[i] = state_in[i];

    bool state_out_bytes[128];

    for (int col = 0; col < 4; col++) {
        bool *in0  = &state_bytes[8 * (4*col + 0)];
        bool *in1  = &state_bytes[8 * (4*col + 1)];
        bool *in2  = &state_bytes[8 * (4*col + 2)];
        bool *in3  = &state_bytes[8 * (4*col + 3)];
        bool *out0 = &state_out_bytes[8 * (4*col + 0)];
        bool *out1 = &state_out_bytes[8 * (4*col + 1)];
        bool *out2 = &state_out_bytes[8 * (4*col + 2)];
        bool *out3 = &state_out_bytes[8 * (4*col + 3)];

        MC_single_column(in0, in1, in2, in3, out0, out1, out2, out3);
    }

    for (int i = 0; i < 128; i++) state_out[i] = state_out_bytes[i];
}

void SR_umsk(bool state_in[128], bool state_out[128]) {
    bool state_bytes[128];
    for (int i = 0; i < 128; i++) state_bytes[i] = state_in[i];

    bool state_bytes_out[128];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int dst = 8 * (4*j + i);
            int src = 8 * ((4*j + i + i*4) % 16);
            for (int b = 0; b < 8; b++) {
                state_bytes_out[dst + b] = state_bytes[src + b];
            }
        }
    }

    for (int i = 0; i < 128; i++) state_out[i] = state_bytes_out[i];
}

void KS_round(bool kin[128], bool kout[128], bool RCON[8]) {
    bool k_bytes[128];
    for (int i = 0; i < 128; i++) k_bytes[i] = kin[i];

    bool lcol_SB0[8], lcol_SB1[8], lcol_SB2[8], lcol_SB3[8];

    sbox(&k_bytes[8*12], lcol_SB3);
    sbox(&k_bytes[8*13], lcol_SB0);
    sbox(&k_bytes[8*14], lcol_SB1);
    sbox(&k_bytes[8*15], lcol_SB2);

    for (int b = 0; b < 8; b++) lcol_SB0[b] ^= RCON[b];

    bool k_bytes_out[128];

    for (int b = 0; b < 8; b++) {
        k_bytes_out[0  + b] = lcol_SB0[b] ^ k_bytes[0  + b];
        k_bytes_out[8  + b] = lcol_SB1[b] ^ k_bytes[8  + b];
        k_bytes_out[16 + b] = lcol_SB2[b] ^ k_bytes[16 + b];
        k_bytes_out[24 + b] = lcol_SB3[b] ^ k_bytes[24 + b];
    }

    for (int i = 1; i < 4; i++) {
        for (int b = 0; b < 8; b++) {
            int base = 32 * i;
            int prev = 32 * (i - 1);
            k_bytes_out[base + 0  + b] = k_bytes_out[prev + 0  + b] ^ k_bytes[base + 0  + b];
            k_bytes_out[base + 8  + b] = k_bytes_out[prev + 8  + b] ^ k_bytes[base + 8  + b];
            k_bytes_out[base + 16 + b] = k_bytes_out[prev + 16 + b] ^ k_bytes[base + 16 + b];
            k_bytes_out[base + 24 + b] = k_bytes_out[prev + 24 + b] ^ k_bytes[base + 24 + b];
        }
    }

    for (int i = 0; i < 128; i++) kout[i] = k_bytes_out[i];
}

void aes_128_encrypt(bool state[128], bool key[128]) {
    bool rcon[10][8] = {
        {1,0,0,0,0,0,0,0}, {0,1,0,0,0,0,0,0}, {0,0,1,0,0,0,0,0}, {0,0,0,1,0,0,0,0},
        {0,0,0,0,1,0,0,0}, {0,0,0,0,0,1,0,0}, {0,0,0,0,0,0,1,0}, {0,0,0,0,0,0,0,1},
        {1,1,0,1,1,0,0,0}, {0,1,1,0,1,1,0,0}
    };
    
    bool current_key[128];
    for(int i = 0; i < 128; i++) current_key[i] = key[i];
    
    for (int b = 0; b < 128; b++) state[b] ^= current_key[b];
    
    for (int r = 0; r < 9; r++) {
        bool next_key[128], postSB[128], postSR[128], postMC[128];
        
        KS_round(current_key, next_key, rcon[r]);
        for (int i = 0; i < 16; i++) sbox(&state[8*i], &postSB[8*i]);
        SR_umsk(postSB, postSR);
        MC_umsk(postSR, postMC);
        
        for (int b = 0; b < 128; b++) {
            state[b] = postMC[b] ^ next_key[b];
            current_key[b] = next_key[b];
        }
    }
    
    bool next_key[128], postSB[128], postSR[128];
    KS_round(current_key, next_key, rcon[9]);
    for (int i = 0; i < 16; i++) sbox(&state[8*i], &postSB[8*i]);
    SR_umsk(postSB, postSR);
    
    for (int b = 0; b < 128; b++) {
        state[b] = postSR[b] ^ next_key[b];
    }
}