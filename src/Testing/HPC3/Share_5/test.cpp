#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <functional>

using namespace std; // Use the standard namespace

// Assuming reg() is an identity function for software simulation.
// In hardware, this might represent a clock cycle delay.
int reg(int val) {
    return val;
}

// ===================================================================
// Your Provided HPC3 Gadget Code
// ===================================================================

void hpc3_same_shares_5_order(int a_share, int b_share, int* u_share) {
    *u_share = reg(a_share & b_share);
}

void hpc3_v_5_order(int a_share, int b_share, int* v_share, int rand) {
    int temp;
    temp = reg(b_share ^ rand);
    int a_share_reg;
    a_share_reg = reg(a_share);
    *v_share = temp & a_share_reg;
}

void hpc3_w_5_order(int a_share, int rand, int prand, int* w_share) {
    int temp;
    int a_share_neg;
    a_share_neg = ~(a_share);
    temp = a_share_neg & rand;
    *w_share = reg(temp ^ prand);
}

void hpc3_xor_vw_5_order(int v_share, int w_share, int* u_share) {
    *u_share = v_share ^ w_share;
}

void HPC3(int a0, int a1, int a2, int a3, int a4, int a5, int b0, int b1, int b2, int b3, int b4, int b5, int* c0, int* c1, int* c2, int* c3, int* c4, int* c5, int r01, int r02, int r03, int r04, int r05, int r12, int r13, int r14, int r15, int r23, int r24, int r25, int r34, int r35, int r45, int p01, int p02, int p03, int p04, int p05, int p12, int p13, int p14, int p15, int p23, int p24, int p25, int p34, int p35, int p45) {
    int u00, u01, u02, u03, u04, u05, u10, u11, u12, u13, u14, u15, u20, u21, u22, u23, u24, u25, u30, u31, u32, u33, u34, u35, u40, u41, u42, u43, u44, u45, u50, u51, u52, u53, u54, u55;
    int v01, v02, v03, v04, v05, v10, v12, v13, v14, v15, v20, v21, v23, v24, v25, v30, v31, v32, v34, v35, v40, v41, v42, v43, v45, v50, v51, v52, v53, v54;
    int w01, w02, w03, w04, w05, w10, w12, w13, w14, w15, w20, w21, w23, w24, w25, w30, w31, w32, w34, w35, w40, w41, w42, w43, w45, w50, w51, w52, w53, w54;

    hpc3_same_shares_5_order(a0, b0, &u00);
    hpc3_v_5_order(a0, b1, &v01, r01); hpc3_w_5_order(a0, r01, p01, &w01); hpc3_xor_vw_5_order(v01, w01, &u01);
    hpc3_v_5_order(a0, b2, &v02, r02); hpc3_w_5_order(a0, r02, p02, &w02); hpc3_xor_vw_5_order(v02, w02, &u02);
    hpc3_v_5_order(a0, b3, &v03, r03); hpc3_w_5_order(a0, r03, p03, &w03); hpc3_xor_vw_5_order(v03, w03, &u03);
    hpc3_v_5_order(a0, b4, &v04, r04); hpc3_w_5_order(a0, r04, p04, &w04); hpc3_xor_vw_5_order(v04, w04, &u04);
    hpc3_v_5_order(a0, b5, &v05, r05); hpc3_w_5_order(a0, r05, p05, &w05); hpc3_xor_vw_5_order(v05, w05, &u05);

    hpc3_v_5_order(a1, b0, &v10, r01); hpc3_w_5_order(a1, r01, p01, &w10); hpc3_xor_vw_5_order(v10, w10, &u10);
    hpc3_same_shares_5_order(a1, b1, &u11);
    hpc3_v_5_order(a1, b2, &v12, r12); hpc3_w_5_order(a1, r12, p12, &w12); hpc3_xor_vw_5_order(v12, w12, &u12);
    hpc3_v_5_order(a1, b3, &v13, r13); hpc3_w_5_order(a1, r13, p13, &w13); hpc3_xor_vw_5_order(v13, w13, &u13);
    hpc3_v_5_order(a1, b4, &v14, r14); hpc3_w_5_order(a1, r14, p14, &w14); hpc3_xor_vw_5_order(v14, w14, &u14);
    hpc3_v_5_order(a1, b5, &v15, r15); hpc3_w_5_order(a1, r15, p15, &w15); hpc3_xor_vw_5_order(v15, w15, &u15);

    hpc3_v_5_order(a2, b0, &v20, r02); hpc3_w_5_order(a2, r02, p02, &w20); hpc3_xor_vw_5_order(v20, w20, &u20);
    hpc3_v_5_order(a2, b1, &v21, r12); hpc3_w_5_order(a2, r12, p12, &w21); hpc3_xor_vw_5_order(v21, w21, &u21);
    hpc3_same_shares_5_order(a2, b2, &u22);
    hpc3_v_5_order(a2, b3, &v23, r23); hpc3_w_5_order(a2, r23, p23, &w23); hpc3_xor_vw_5_order(v23, w23, &u23);
    hpc3_v_5_order(a2, b4, &v24, r24); hpc3_w_5_order(a2, r24, p24, &w24); hpc3_xor_vw_5_order(v24, w24, &u24);
    hpc3_v_5_order(a2, b5, &v25, r25); hpc3_w_5_order(a2, r25, p25, &w25); hpc3_xor_vw_5_order(v25, w25, &u25);

    hpc3_v_5_order(a3, b0, &v30, r03); hpc3_w_5_order(a3, r03, p03, &w30); hpc3_xor_vw_5_order(v30, w30, &u30);
    hpc3_v_5_order(a3, b1, &v31, r13); hpc3_w_5_order(a3, r13, p13, &w31); hpc3_xor_vw_5_order(v31, w31, &u31);
    hpc3_v_5_order(a3, b2, &v32, r23); hpc3_w_5_order(a3, r23, p23, &w32); hpc3_xor_vw_5_order(v32, w32, &u32);
    hpc3_same_shares_5_order(a3, b3, &u33);
    hpc3_v_5_order(a3, b4, &v34, r34); hpc3_w_5_order(a3, r34, p34, &w34); hpc3_xor_vw_5_order(v34, w34, &u34);
    hpc3_v_5_order(a3, b5, &v35, r35); hpc3_w_5_order(a3, r35, p35, &w35); hpc3_xor_vw_5_order(v35, w35, &u35);

    hpc3_v_5_order(a4, b0, &v40, r04); hpc3_w_5_order(a4, r04, p04, &w40); hpc3_xor_vw_5_order(v40, w40, &u40);
    hpc3_v_5_order(a4, b1, &v41, r14); hpc3_w_5_order(a4, r14, p14, &w41); hpc3_xor_vw_5_order(v41, w41, &u41);
    hpc3_v_5_order(a4, b2, &v42, r24); hpc3_w_5_order(a4, r24, p24, &w42); hpc3_xor_vw_5_order(v42, w42, &u42);
    hpc3_v_5_order(a4, b3, &v43, r34); hpc3_w_5_order(a4, r34, p34, &w43); hpc3_xor_vw_5_order(v43, w43, &u43);
    hpc3_same_shares_5_order(a4, b4, &u44);
    hpc3_v_5_order(a4, b5, &v45, r45); hpc3_w_5_order(a4, r45, p45, &w45); hpc3_xor_vw_5_order(v45, w45, &u45);

    hpc3_v_5_order(a5, b0, &v50, r05); hpc3_w_5_order(a5, r05, p05, &w50); hpc3_xor_vw_5_order(v50, w50, &u50);
    hpc3_v_5_order(a5, b1, &v51, r15); hpc3_w_5_order(a5, r15, p15, &w51); hpc3_xor_vw_5_order(v51, w51, &u51);
    hpc3_v_5_order(a5, b2, &v52, r25); hpc3_w_5_order(a5, r25, p25, &w52); hpc3_xor_vw_5_order(v52, w52, &u52);
    hpc3_v_5_order(a5, b3, &v53, r35); hpc3_w_5_order(a5, r35, p35, &w53); hpc3_xor_vw_5_order(v53, w53, &u53);
    hpc3_v_5_order(a5, b4, &v54, r45); hpc3_w_5_order(a5, r45, p45, &w54); hpc3_xor_vw_5_order(v54, w54, &u54);
    hpc3_same_shares_5_order(a5, b5, &u55);

    int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24;
    t1 = u00 ^ u01; t2 = t1 ^ u02; t3 = t2 ^ u03; t4 = t3 ^ u04; *c0 = t4 ^ u05;
    t5 = u10 ^ u11; t6 = t5 ^ u12; t7 = t6 ^ u13; t8 = t7 ^ u14; *c1 = t8 ^ u15;
    t9 = u20 ^ u21; t10 = t9 ^ u22; t11 = t10 ^ u23; t12 = t11 ^ u24; *c2 = t12 ^ u25;
    t13 = u30 ^ u31; t14 = t13 ^ u32; t15 = t14 ^ u33; t16 = t15 ^ u34; *c3 = t16 ^ u35;
    t17 = u40 ^ u41; t18 = t17 ^ u42; t19 = t18 ^ u43; t20 = t19 ^ u44; *c4 = t20 ^ u45;
    t21 = u50 ^ u51; t22 = t21 ^ u52; t23 = t22 ^ u53; t24 = t23 ^ u54; *c5 = t24 ^ u55;
}


// ===================================================================
// Testing Framework
// ===================================================================

/**
 * @brief Splits a value into N shares.
 * @param value The secret value to share.
 * @param num_shares The number of shares to create (must be >= 1).
 * @param rand_gen A random number generator function.
 * @return A vector containing the shares.
 */
vector<int> create_shares(int value, int num_shares, function<int()> rand_gen) {
    if (num_shares < 1) return {};
    vector<int> shares(num_shares);
    int xor_sum = 0;
    
    // Generate N-1 random shares
    for (int i = 0; i < num_shares - 1; ++i) {
        shares[i] = rand_gen();
        xor_sum ^= shares[i];
    }
    
    // The last share makes the XOR sum equal to the original value
    shares[num_shares - 1] = xor_sum ^ value;
    
    return shares;
}

/**
 * @brief Reconstructs the original value from its shares.
 * @param shares A vector of shares.
 * @return The reconstructed secret value.
 */
int reconstruct_value(const vector<int>& shares) {
    int value = 0;
    for (int share : shares) {
        value ^= share;
    }
    return value;
}


int main() {
    // Setup for random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib;
    auto rand_gen = [&]() { return distrib(gen); };

    int num_tests = 10000;
    int tests_passed = 0;

    cout << "Running " << num_tests << " random tests...\n";

    for (int i = 0; i < num_tests; ++i) {
        // 1. Generate two original secret values
        int a_original = rand_gen();
        int b_original = rand_gen();
        
        // 2. Create 6 shares for each secret
        vector<int> a_shares = create_shares(a_original, 6, rand_gen);
        vector<int> b_shares = create_shares(b_original, 6, rand_gen);

        // 3. Generate the required random numbers (r's and p's) for the gadget
        int r[15], p[15];
        for(int j=0; j<15; ++j) {
            r[j] = rand_gen();
            p[j] = rand_gen();
        }

        // 4. Call the HPC3 gadget
        vector<int> c_shares(6);
        HPC3(a_shares[0], a_shares[1], a_shares[2], a_shares[3], a_shares[4], a_shares[5],
             b_shares[0], b_shares[1], b_shares[2], b_shares[3], b_shares[4], b_shares[5],
             &c_shares[0], &c_shares[1], &c_shares[2], &c_shares[3], &c_shares[4], &c_shares[5],
             r[0], r[1], r[2], r[3], r[4],        // r01..r05
             r[5], r[6], r[7], r[8],             // r12..r15
             r[9], r[10], r[11],                 // r23..r25
             r[12], r[13],                       // r34..r35
             r[14],                             // r45
             p[0], p[1], p[2], p[3], p[4],        // p01..p05
             p[5], p[6], p[7], p[8],             // p12..p15
             p[9], p[10], p[11],                 // p23..p25
             p[12], p[13],                       // p34..p35
             p[14]                              // p45
             );

        // 5. Reconstruct the result and check for correctness
        int c_reconstructed = reconstruct_value(c_shares);
        int c_expected = a_original & b_original;
        
        if (c_reconstructed == c_expected) {
            tests_passed++;
        } else {
            cerr << "❌ Test Failed!\n";
            cerr << "  a_original: " << a_original << "\n";
            cerr << "  b_original: " << b_original << "\n";
            cerr << "  Expected c (a&b): " << c_expected << "\n";
            cerr << "  Reconstructed c:  " << c_reconstructed << "\n";
            return 1; // Exit on first failure
        }
    }

    cout << "✅ All " << tests_passed << " tests passed successfully!\n";
    return 0;
}