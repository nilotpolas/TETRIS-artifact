// #define TO_UINT4(x) ((int)((x) & 0xF))

int sbox(int Xin) {
    int X = (Xin);

    // Extract bits
    int X0 = (X >> 3) & 1;
    int X1 = (X >> 2) & 1;
    int X2 = (X >> 1) & 1;
    int X3 = (X >> 0) & 1;

    // Intermediate signals
    int Q0 = X0 ^ X1;
    int Q1 = X0 ^ X2;
    int T0 = X3 & Q1;
    int Q2 = Q0 ^ T0;
    int T1 = X0 & Q2;
    int Q4 = ~(X0 ^ X3) & 1;     // XNOR
    int T2 = X3 & Q4;
    int L0 = T1 ^ T2;
    int Q6 = X1 ^ X3;
    int L1 = ~(Q1 ^ Q6) & 1;
    int Q7 = L1 ^ T2;
    int T3 = Q6 & Q7;

    int L2 = X0 ^ X3;
    int Y0 = L0 ^ L2;
    int Y1 = L0 ^ T3;
    int L3 = X1 ^ T0;
    int Y2 = L3 ^ T2;
    int Y3 = X2 ^ T2;

    // Final O computation
    int O0 = Y2;
    int O1 = ~(Y1 ^ Y3) & 1;
    int O2 = ~Y0 & 1;
    int O3 = ~Y1 & 1;

    return ((O0 << 3) | (O1 << 2) | (O2 << 1) | (O3 << 0));
}