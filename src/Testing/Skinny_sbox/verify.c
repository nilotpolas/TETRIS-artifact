#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// ==========================================
// 1. GOLDEN CODE
// ==========================================
#include <stdbool.h>

void sbox_golden(bool i0, bool i1, bool i2, bool i3, bool i4, bool i5, bool i6, bool i7, bool dec_1,
          bool *o0, bool *o1, bool *o2, bool *o3, bool *o4, bool *o5, bool *o6, bool *o7) {
    
    // Intermediate variables
    bool n1, n2, n3, n6, n7;
    bool t0, t1, t2, t3, t4, t5, t6, t7;
    bool nt0, nt1, nt2, nt3, nt4, nt5;
    bool o0_val, o1_val, o2_val, o3_val, o4_val, o5_val, o6_val, o7_val;

    // Layer 1: Input Inversions
    n1 = i1 ^ dec_1;
    n2 = i2 ^ dec_1;
    n3 = i3 ^ dec_1;
    n6 = i6 ^ dec_1;
    n7 = i7 ^ dec_1;

    // Layer 2: AND operations
    t0 = n6 & n7;
    t1 = n3 & n2;
    t2 = n2 & n1;

    // Layer 3: Inversions
    nt0 = t0 ^ dec_1;
    nt1 = t1 ^ dec_1;
    nt2 = t2 ^ dec_1;

    // Layer 4: AND operations
    t3 = nt0 & nt1;
    t4 = nt1 & n3;

    // Layer 5: Inversions
    nt3 = t3 ^ dec_1;
    
    // Layer 6: AND operations
    t5 = nt2 & nt3;
    
    // Layer 7: Inversions
    nt4 = t4 ^ dec_1;
    nt5 = t5 ^ dec_1;

    // Layer 8: Final AND operations
    t6 = nt3 & nt0;
    t7 = nt4 & nt5;

    // Layer 9: Final XOR with inputs - TAC COMPATIBLE FORMAT
    // First assign to temporary variables
    o6_val = t0 ^ i4;
    o5_val = t1 ^ i0;
    o2_val = t2 ^ i6;
    o7_val = t3 ^ i5;
    o0_val = t7 ^ i2;
    o4_val = t6 ^ i3;
    o1_val = t5 ^ i7;
    o3_val = t4 ^ i1;

    // Then assign temporaries to output pointers
    *o0 = o0_val;
    *o1 = o1_val;
    *o2 = o2_val;
    *o3 = o3_val;
    *o4 = o4_val;
    *o5 = o5_val;
    *o6 = o6_val;
    *o7 = o7_val;
}

// ==========================================
// 2. GADGET DEFINITIONS & MASKED CODE
// ==========================================
int reg(bool x){
    return x;
}

// --- HPC2 Gadget ---
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
    *c0 = (u00 ^ u01) & 1;  // Mask to 1-bit
    *c1 = (u10 ^ u11) & 1;  // Mask to 1-bit
}

// --- HPC3 Gadget ---
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

    *c0 = (u00 ^ u01) & 1;  // Mask to 1-bit
    *c1 = (u10 ^ u11) & 1;  // Mask to 1-bit
}

// --- Masked S-Box (with int instead of _Bool) ---
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


// --- hpc3o ---

void hpc3o_first_half_1_order(int a_share, int b_share, int w_share, int rand, int rand_prime, int *out_share) {
    int xor_br;
    int and_ar;
    int xor_step1;
    int xor_step2;

    xor_br = b_share ^ rand;
    and_ar = a_share & xor_br;
    xor_step1 = w_share ^ and_ar;
    xor_step2 = xor_step1 ^ rand_prime;
    
    *out_share = reg(xor_step2);
}

void hpc3o_v_1_order(int a_share, int b_share, int *v_share, int rand) {
    int xor_br;
    int temp;
    int and_ta;

    xor_br = b_share ^ rand;
    temp = reg(xor_br); // This remains an R register in Algo 7
    
    and_ta = a_share & temp;
    *v_share = and_ta; // Notice: NO outer reg() here for HPC3o!
}

void hpc3o_w_1_order(int a_share, int rand, int rand_prime, int *w_share) {
    int and_ar;
    int xor_step1;

    // Notice: Algo 7 does not negate a_share in the else branch
    and_ar = a_share & rand;
    xor_step1 = and_ar ^ rand_prime;
    
    *w_share = reg(xor_step1);
}

void hpc3o_xor_vw_1_order(int v_share, int w_share, int *u_share) {
    *u_share = v_share ^ w_share;
}
void HPC3o(int a0, int a1, int b0, int b1, int w0, int w1, int * c0, int * c1, int rand_01, int rand_prime_01)
{
	int u01, u10;
	int v01, v10;
	int w01, w10;

	hpc3o_first_half_1_order(a0, b0, w0, rand_01, rand_prime_01, &w01);
	hpc3o_v_1_order(a0, b1, &v01, rand_01);
	hpc3o_xor_vw_1_order(v01, w01, &u01);

	hpc3o_first_half_1_order(a1, b1, w1, rand_01, rand_prime_01, &w10);
	hpc3o_v_1_order(a1, b0, &v10, rand_01);
	hpc3o_xor_vw_1_order(v10, w10, &u10);

	*c0 = u01;
	*c1 = u10;
}

void sbox_masked(_Bool i0_0, _Bool i0_1, _Bool i1_0, _Bool i1_1, _Bool i2_0, _Bool i2_1, _Bool i3_0, _Bool i3_1, _Bool i4_0, _Bool i4_1, _Bool i5_0, _Bool i5_1, _Bool i6_0, _Bool i6_1, _Bool i7_0, _Bool i7_1, _Bool dec_1, _Bool *o0_0, _Bool *o0_1, _Bool *o1_0, _Bool *o1_1, _Bool *o2_0, _Bool *o2_1, _Bool *o3_0, _Bool *o3_1, _Bool *o4_0, _Bool *o4_1, _Bool *o5_0, _Bool *o5_1, _Bool *o6_0, _Bool *o6_1, _Bool *o7_0, _Bool *o7_1, int rand_3, int rand_7, int rand_11, int rand_15, int rand_10, int rand_14, int rand_2, int rand_6, int rand_12, int rand_16, int rand_5, int rand_1, int rand_8, int rand_9, int rand_13, int rand_4)
{
  _Bool n1_0;
  _Bool n1_1;
  _Bool n2_0;
  _Bool n2_1;
  _Bool n3_0;
  _Bool n3_1;
  _Bool n6_0;
  _Bool n6_1;
  _Bool n7_0;
  _Bool n7_1;
  _Bool t0_0;
  _Bool t0_1;
  _Bool t1_0;
  _Bool t1_1;
  _Bool t2_0;
  _Bool t2_1;
  _Bool t3_0;
  _Bool t3_1;
  _Bool t4_0;
  _Bool t4_1;
  _Bool t5_0;
  _Bool t5_1;
  _Bool t6_0;
  _Bool t6_1;
  _Bool t7_0;
  _Bool t7_1;
  _Bool nt0_0;
  _Bool nt0_1;
  _Bool nt1_0;
  _Bool nt1_1;
  _Bool nt2_0;
  _Bool nt2_1;
  _Bool nt3_0;
  _Bool nt3_1;
  _Bool nt4_0;
  _Bool nt4_1;
  _Bool nt5_0;
  _Bool nt5_1;
  _Bool o0_val_0;
  _Bool o0_val_1;
  _Bool o1_val_0;
  _Bool o1_val_1;
  _Bool o2_val_0;
  _Bool o2_val_1;
  _Bool o3_val_0;
  _Bool o3_val_1;
  _Bool o4_val_0;
  _Bool o4_val_1;
  _Bool o5_val_0;
  _Bool o5_val_1;
  _Bool o6_val_0;
  _Bool o6_val_1;
  _Bool o7_val_0;
  _Bool o7_val_1;
  n1_0 = i1_0;
  n1_1 = ~i1_1;
  n2_0 = i2_0;
  n2_1 = ~i2_1;
  n3_0 = i3_0;
  n3_1 = ~i3_1;
  n6_0 = i6_0;
  n6_1 = ~i6_1;
  n7_0 = i7_0;
  n7_1 = ~i7_1;
  HPC3(n7_0, n7_1, n6_0, n6_1, &t0_0, &t0_1, rand_1, rand_2);
  HPC3(n2_0, n2_1, n3_0, n3_1, &t1_0, &t1_1, rand_3, rand_4);
  HPC3(n1_0, n1_1, n2_0, n2_1, &t2_0, &t2_1, rand_5, rand_6);
  nt0_0 = t0_0;
  nt0_1 = ~t0_1;
  nt1_0 = t1_0;
  nt1_1 = ~t1_1;
  nt2_0 = t2_0;
  nt2_1 = ~t2_1;
  HPC3(nt1_0, nt1_1, nt0_0, nt0_1, &t3_0, &t3_1, rand_7, rand_8);
  HPC3(n3_0, n3_1, nt1_0, nt1_1, &t4_0, &t4_1, rand_9, rand_10);
  nt3_0 = t3_0;
  nt3_1 = ~t3_1;
  HPC3(nt3_0, nt3_1, nt2_0, nt2_1, &t5_0, &t5_1, rand_11, rand_12);
  nt4_0 = t4_0;
  nt4_1 = ~t4_1;
  nt5_0 = t5_0;
  nt5_1 = ~t5_1;
  HPC3o(nt0_0, nt0_1, nt3_0, nt3_1, o4_val_0, o4_val_1, &t6_0, &t6_1, rand_13, rand_14);
  HPC3o(nt5_0, nt5_1, nt4_0, nt4_1, o0_val_0, o0_val_1, &t7_0, &t7_1, rand_15, rand_16);
  o6_val_0 = t0_0 ^ i4_0;
  o6_val_1 = t0_1 ^ i4_1;
  o5_val_0 = t1_0 ^ i0_0;
  o5_val_1 = t1_1 ^ i0_1;
  o2_val_0 = t2_0 ^ i6_0;
  o2_val_1 = t2_1 ^ i6_1;
  o7_val_0 = t3_0 ^ i5_0;
  o7_val_1 = t3_1 ^ i5_1;
  o0_val_0 = t7_0 ^ i2_0;
  o0_val_1 = t7_1 ^ i2_1;
  o4_val_0 = t6_0 ^ i3_0;
  o4_val_1 = t6_1 ^ i3_1;
  o1_val_0 = t5_0 ^ i7_0;
  o1_val_1 = t5_1 ^ i7_1;
  o3_val_0 = t4_0 ^ i1_0;
  o3_val_1 = t4_1 ^ i1_1;
  *o0_0 = o0_val_0;
  *o0_1 = o0_val_1;
  *o1_0 = o1_val_0;
  *o1_1 = o1_val_1;
  *o2_0 = o2_val_0;
  *o2_1 = o2_val_1;
  *o3_0 = o3_val_0;
  *o3_1 = o3_val_1;
  *o4_0 = o4_val_0;
  *o4_1 = o4_val_1;
  *o5_0 = o5_val_0;
  *o5_1 = o5_val_1;
  *o6_0 = o6_val_0;
  *o6_1 = o6_val_1;
  *o7_0 = o7_val_0;
  *o7_1 = o7_val_1;
}




// ==========================================
// 3. TESTBENCH
// ==========================================
int main() {
    int mismatches = 0;
    bool dec_1 = 0;

    printf("======================================================================\n");
    printf("Starting Equivalence Check...\n");
    printf("======================================================================\n\n");

    for(int i = 0; i < 256; i++) {
        // Extract bits from counter
        bool in[8];
        for(int b=0; b<8; b++) {
            in[b] = (i >> b) & 1;
        }

        // Golden Outputs
        bool g0, g1, g2, g3, g4, g5, g6, g7;
        
        // Masked Outputs (Shares 0 and 1) - use int, not _Bool
        int m0_0, m0_1, m1_0, m1_1, m2_0, m2_1, m3_0, m3_1;
        int m4_0, m4_1, m5_0, m5_1, m6_0, m6_1, m7_0, m7_1;

        // Run Golden Code
        sbox_golden(in[0], in[1], in[2], in[3], in[4], in[5], in[6], in[7], dec_1,
                    &g0, &g1, &g2, &g3, &g4, &g5, &g6, &g7);

        // Run Masked Code (Share 1 and Randomness set to 0)
        sbox_masked(in[0], 0, in[1], 0, in[2], 0, in[3], 0, 
                    in[4], 0, in[5], 0, in[6], 0, in[7], 0,
                    dec_1, 
                    &m0_0, &m0_1, &m1_0, &m1_1, &m2_0, &m2_1, &m3_0, &m3_1, 
                    &m4_0, &m4_1, &m5_0, &m5_1, &m6_0, &m6_1, &m7_0, &m7_1, 
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 , 1 , 1, 1);

        // Decode Masked Outputs (o_unmasked = share0 ^ share1)
        int u0 = m0_0 ^ m0_1;
        int u1 = m1_0 ^ m1_1;
        int u2 = m2_0 ^ m2_1;
        int u3 = m3_0 ^ m3_1;
        int u4 = m4_0 ^ m4_1;
        int u5 = m5_0 ^ m5_1;
        int u6 = m6_0 ^ m6_1;
        int u7 = m7_0 ^ m7_1;

        // Check for Equivalence
        if(g0 != u0 || g1 != u1 || g2 != u2 || g3 != u3 || 
           g4 != u4 || g5 != u5 || g6 != u6 || g7 != u7) {
            
            if(mismatches < 10) {  // Print first 10 mismatches
                printf("[MISMATCH] Input: 0x%02X (binary %d%d%d%d%d%d%d%d)\n", i,
                       in[7],in[6],in[5],in[4],in[3],in[2],in[1],in[0]);
                printf("  Golden  output: %d%d%d%d%d%d%d%d\n", g7,g6,g5,g4,g3,g2,g1,g0);
                printf("  Masked  output: %d%d%d%d%d%d%d%d\n\n", u7,u6,u5,u4,u3,u2,u1,u0);
            }
            mismatches++;
        }
    }

    printf("======================================================================\n");
    if(mismatches == 0) {
        printf("✓ SUCCESS: All 256 inputs are functionally equivalent!\n");
    } else {
        printf("✗ FAILURE: %d out of 256 inputs produced non-equivalent outputs.\n", mismatches);
    }
    printf("======================================================================\n\n");

    return mismatches > 0 ? 1 : 0;
}