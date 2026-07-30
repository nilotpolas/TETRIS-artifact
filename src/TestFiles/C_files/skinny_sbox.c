void sbox(int x0, int x1, int x2, int x3 , int *output) {
    
    int X0 = x1 & 1;               
    int X1 = (x0 ^ x2) & 1;        
    int X2 = (x2 ^ x3) & 1;        
    int X3 = (~x2) & 1;           

    // intermediates
    int Q0 = (X0 ^ X1) & 1;
    int Q1 = (X0 ^ X2) & 1;
    int T0 = X3 & Q1;
    int Q2 = (Q0 ^ T0) & 1;
    int T1 = X0 & Q2;
    int Q3 = X0 ^ X3;
    int neg_Q3 = ~Q3;
    int Q4 = neg_Q3 & 1;     
    int T2 = X3 & Q4;
    int L0 = T1 ^ T2;
    int Q6 = X1 ^ X3;
    int L4 = Q1 ^ Q6;
    int neg_L3 = ~L4;
    int L1 = neg_L3 & 1;     
    int Q7 = L1 ^ T2;
    int T3 = Q6 & Q7;

    // outputs Y
    int L2 = X0 ^ X3;
    int Y0 = L0 ^ L2;
    int Y1 = L0 ^ T3;
    int L3 = X1 ^ T0;
    int Y2 = L3 ^ T2;
    int Y3 = X2 ^ T2;

    int O0 = Y1 & 1;
    int O_temp = Y2 ^ Y0;
    int neg_O_temp = ~O_temp;
    int O1 = neg_O_temp & 1;  
    int O2 = (~Y3) & 1;
    int O3 = (~Y2) & 1;
    *output = (O0 << 0) | (O1 << 1) | (O2 << 2) | (O3 << 3);
}
