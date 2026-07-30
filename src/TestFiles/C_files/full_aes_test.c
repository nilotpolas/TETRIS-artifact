#include <stdio.h>
#include <stdbool.h>

/* --- GF(2^2) Bit-Level Operations --- */

void G4_mul(_Bool x0, _Bool x1, _Bool y0, _Bool y1, _Bool *p0, _Bool *p1) {
    _Bool a, b, c, d, e, p, q;
    
    a = x1; b = x0;
    c = y1; d = y0;
    
    e = (a ^ b) & (c ^ d);
    p = (a & c) ^ e;
    q = (b & d) ^ e;
    
    *p1 = p; *p0 = q;
}

void G4_scl_N(_Bool x0, _Bool x1, _Bool *p0, _Bool *p1) {
    _Bool a, b, p, q;
    
    a = x1; b = x0;
    p = b;
    q = a ^ b;
    
    *p1 = p; *p0 = q;
}

void G4_scl_N2(_Bool x0, _Bool x1, _Bool *p0, _Bool *p1) {
    _Bool a, b, p, q;
    
    a = x1; b = x0;
    p = a ^ b;
    q = a;
    
    *p1 = p; *p0 = q;
}

void G4_sq(_Bool x0, _Bool x1, _Bool *p0, _Bool *p1) {
    _Bool a, b;
    
    a = x1; b = x0;
    
    // return ((b << 1) | a)
    *p1 = b; *p0 = a;
}

/* --- GF(2^4) Bit-Level Operations --- */

void G16_mul(_Bool x0, _Bool x1, _Bool x2, _Bool x3, 
             _Bool y0, _Bool y1, _Bool y2, _Bool y3,
             _Bool *p0, _Bool *p1, _Bool *p2, _Bool *p3) {
    _Bool a0, a1, b0, b1, c0, c1, d0, d1, e0, e1, p_h0, p_h1, q_l0, q_l1;
    
    a1 = x3; a0 = x2;
    b1 = x1; b0 = x0;
    c1 = y3; c0 = y2;
    d1 = y1; d0 = y0;
    
    G4_mul(a0 ^ b0, a1 ^ b1, c0 ^ d0, c1 ^ d1, &e0, &e1);
    G4_scl_N(e0, e1, &e0, &e1);
    
    G4_mul(a0, a1, c0, c1, &p_h0, &p_h1);
    G4_mul(b0, b1, d0, d1, &q_l0, &q_l1);
    
    *p3 = p_h1 ^ e1; *p2 = p_h0 ^ e0;
    *p1 = q_l1 ^ e1; *p0 = q_l0 ^ e0;
}

void G16_sq_scl(_Bool x0, _Bool x1, _Bool x2, _Bool x3,
                _Bool *p0, _Bool *p1, _Bool *p2, _Bool *p3) {
    _Bool a0, a1, b0, b1, p_h0, p_h1, q_l0, q_l1;
    
    a1 = x3; a0 = x2;
    b1 = x1; b0 = x0;
    
    G4_sq(a0 ^ b0, a1 ^ b1, &p_h0, &p_h1);
    G4_sq(b0, b1, &q_l0, &q_l1);
    G4_scl_N2(q_l0, q_l1, &q_l0, &q_l1);
    
    *p3 = p_h1; *p2 = p_h0;
    *p1 = q_l1; *p0 = q_l0;
}

void G16_inv(_Bool x0, _Bool x1, _Bool x2, _Bool x3,
             _Bool *p0, _Bool *p1, _Bool *p2, _Bool *p3) {
    _Bool a0, a1, b0, b1, c0, c1, d0, d1, e0, e1, out_p0, out_p1, out_q0, out_q1;
    
    a1 = x3; a0 = x2;
    b1 = x1; b0 = x0;
    
    G4_sq(a0 ^ b0, a1 ^ b1, &c0, &c1);
    G4_scl_N(c0, c1, &c0, &c1);
    G4_mul(a0, a1, b0, b1, &d0, &d1);
    
    G4_sq(c0 ^ d0, c1 ^ d1, &e0, &e1);
    G4_mul(e0, e1, b0, b1, &out_p0, &out_p1);
    G4_mul(e0, e1, a0, a1, &out_q0, &out_q1);
    
    *p3 = out_p1; *p2 = out_p0;
    *p1 = out_q1; *p0 = out_q0;
}

/* --- GF(2^8) Bit-Level Inversion --- */

void G256_inv(_Bool x0, _Bool x1, _Bool x2, _Bool x3, _Bool x4, _Bool x5, _Bool x6, _Bool x7,
              _Bool *p0, _Bool *p1, _Bool *p2, _Bool *p3, _Bool *p4, _Bool *p5, _Bool *p6, _Bool *p7) {
    _Bool a0, a1, a2, a3, b0, b1, b2, b3, c0, c1, c2, c3, d0, d1, d2, d3, e0, e1, e2, e3;
    _Bool out_p0, out_p1, out_p2, out_p3, out_q0, out_q1, out_q2, out_q3;
    
    a3 = x7; a2 = x6; a1 = x5; a0 = x4;
    b3 = x3; b2 = x2; b1 = x1; b0 = x0;
    
    G16_sq_scl(a0 ^ b0, a1 ^ b1, a2 ^ b2, a3 ^ b3, &c0, &c1, &c2, &c3);
    G16_mul(a0, a1, a2, a3, b0, b1, b2, b3, &d0, &d1, &d2, &d3);
    G16_inv(c0 ^ d0, c1 ^ d1, c2 ^ d2, c3 ^ d3, &e0, &e1, &e2, &e3);
    
    G16_mul(e0, e1, e2, e3, b0, b1, b2, b3, &out_p0, &out_p1, &out_p2, &out_p3);
    G16_mul(e0, e1, e2, e3, a0, a1, a2, a3, &out_q0, &out_q1, &out_q2, &out_q3);
    
    *p7 = out_p3; *p6 = out_p2; *p5 = out_p1; *p4 = out_p0;
    *p3 = out_q3; *p2 = out_q2; *p1 = out_q1; *p0 = out_q0;
}

/* --- Main S-Box Function --- */

void sbox(_Bool n[], _Bool o[7]) {

    _Bool i0, i1, i2, i3, i4, i5, i6, i7;
    _Bool y0, y1, y2, y3, y4, y5, y6, y7;

    // Step 1: Change to Normal Basis (Unrolled G256_newbasis for A2X)
    y0=0; y1=0; y2=0; y3=0; y4=0; y5=0; y6=0; y7=0;
    if (n[0]) { y7^=1; y6^=1; y5^=1; y4^=1; y3^=1; y2^=1; y1^=1; y0^=1; } // 0xFF
    if (n[1]) { y7^=1; y5^=1; y3^=1; y0^=1; } // 0xA9
    if (n[2]) { y7^=1; y0^=1; } // 0x81
    if (n[3]) { y3^=1; y0^=1; } // 0x09
    if (n[4]) { y6^=1; y3^=1; } // 0x48
    if (n[5]) { y7^=1; y6^=1; y5^=1; y4^=1; y1^=1; } // 0xF2
    if (n[6]) { y7^=1; y6^=1; y5^=1; y4^=1; y1^=1; y0^=1; } // 0xF3
    if (n[7]) { y7^=1; y4^=1; y3^=1; } // 0x98

    // Step 2: Inversion
    G256_inv(y0, y1, y2, y3, y4, y5, y6, y7, &i0, &i1, &i2, &i3, &i4, &i5, &i6, &i7);

    // Step 3: Change back to Standard Basis (Unrolled G256_newbasis for X2S)
    y0=0; y1=0; y2=0; y3=0; y4=0; y5=0; y6=0; y7=0;
    if (i0) { y5^=1; y2^=1; } // 0x24
    if (i1) { y1^=1; y0^=1; } // 0x03
    if (i2) { y2^=1; } // 0x04
    if (i3) { y7^=1; y6^=1; y4^=1; y3^=1; y2^=1; } // 0xDC
    if (i4) { y3^=1; y1^=1; y0^=1; } // 0x0B
    if (i5) { y7^=1; y4^=1; y3^=1; y2^=1; y1^=1; } // 0x9E
    if (i6) { y5^=1; y3^=1; y2^=1; y0^=1; } // 0x2D
    if (i7) { y6^=1; y4^=1; y3^=1; } // 0x58
    
    // Step 4: Final Affine XOR 0x63
    o[0] = y0 ^ 1; o[1] = y1 ^ 1; o[2] = y2 ^ 0; o[3] = y3 ^ 0;
    o[4] = y4 ^ 0; o[5] = y5 ^ 1; o[6] = y6 ^ 1; o[7] = y7 ^ 0;
}

// -------------------------
// AES Structural Layers — REWRITTEN WITHOUT ANY 2D ARRAYS
// (only 1D arrays + simple indexing + separate [8] variables)
// -------------------------

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

// MC_single_column rewritten with separate [8] variables (no 2D arrays)
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

// KS_round rewritten with only [8] and [128] arrays (no 2D)
void KS_round(bool kin[128], bool kout[128], bool RCON[8]) {
    bool k_bytes[128];
    for (int i = 0; i < 128; i++) k_bytes[i] = kin[i];

    bool lcol_SB0[8], lcol_SB1[8], lcol_SB2[8], lcol_SB3[8];

    sbox(&k_bytes[8*12], lcol_SB3);
    sbox(&k_bytes[8*13], lcol_SB0);
    sbox(&k_bytes[8*14], lcol_SB1);
    sbox(&k_bytes[8*15], lcol_SB2);

    for (int b = 0; b < 8; b++) {
        lcol_SB0[b] ^= RCON[b];
    }

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

// -------------------------
// Full AES-128 Encryption (unchanged — already flat)
// -------------------------

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

// ======================
// MAIN — NIST TEST VECTOR
// ======================
int main() {
    bool state[128] = {
        0,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0, 0,1,0,0,0,1,0,0, 1,1,0,0,1,1,0,0,
        0,0,1,0,0,0,1,0, 1,0,1,0,1,0,1,0, 0,1,1,0,0,1,1,0, 1,1,1,0,1,1,1,0,
        0,0,0,1,0,0,0,1, 1,0,0,1,1,0,0,1, 0,1,0,1,0,1,0,1, 1,1,0,1,1,1,0,1,
        0,0,1,1,0,0,1,1, 1,0,1,1,1,0,1,1, 0,1,1,1,0,1,1,1, 1,1,1,1,1,1,1,1
    };

    bool key[128] = {
        0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 0,1,0,0,0,0,0,0, 1,1,0,0,0,0,0,0,
        0,0,1,0,0,0,0,0, 1,0,1,0,0,0,0,0, 0,1,1,0,0,0,0,0, 1,1,1,0,0,0,0,0,
        0,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0, 0,1,0,1,0,0,0,0, 1,1,0,1,0,0,0,0,
        0,0,1,1,0,0,0,0, 1,0,1,1,0,0,0,0, 0,1,1,1,0,0,0,0, 1,1,1,1,0,0,0,0
    };

    printf("Plaintext  (hex):  ");
    for (int i = 0; i < 16; i++) {
        unsigned char byte = 0;
        for (int b = 0; b < 8; b++) if (state[8*i + b]) byte |= (1u << b);
        printf("%02x", byte);
    }
    printf("\n");

    aes_128_encrypt(state, key);

    printf("Ciphertext (hex): ");
    for (int i = 0; i < 16; i++) {
        unsigned char byte = 0;
        for (int b = 0; b < 8; b++) if (state[8*i + b]) byte |= (1u << b);
        printf("%02x", byte);
    }
    printf("\n");

    return 0;
}