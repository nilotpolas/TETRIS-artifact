#include <stdbool.h>

void sbox(bool X0, bool X1, bool X2, bool X3, bool X4, bool X5, bool X6, bool X7,bool dec_1, bool *Y0, bool *Y1, bool *Y2, bool *Y3, bool *Y4, bool *Y5, bool *Y6, bool *Y7) {
    
    // 1. Declare ALL intermediate variables first
    bool n1, n2, n3, n6, n7;
    bool t0, t1, t2, t3, t4, t5, t6, t7;
    bool nt0, nt1, nt2, nt3, nt4, nt5;

    // 2. Input Inversions
    n1 = !X1;
    n2 = !X2;
    n3 = !X3;
    n6 = !X6;
    n7 = !X7;

    // 3. Layer 1 (NOR logic via De Morgan's)
    t0 = n6 & n7;
    t1 = n3 & n2;
    t2 = n2 & n1;

    // Inversions of Layer 1
    nt0 = !t0;
    nt1 = !t1;
    nt2 = !t2;

    // 4. Layer 2
    t3 = nt0 & nt1;
    t4 = nt1 & n3;

    // Inversions for Layer 3
    nt3 = !t3;
    
    // 5. Layer 3
    t5 = nt2 & nt3;
    
    // Inversions for Layer 4
    nt4 = !t4;
    nt5 = !t5;

    // 6. Layer 4
    t6 = nt3 & nt0;
    t7 = nt4 & nt5;

    // 7. Output Assignments (Dereferencing pointers)
    *Y6 = t0 ^ X4;
    *Y5 = t1 ^ X0;
    *Y2 = t2 ^ X6;
    *Y7 = t3 ^ X5;

    *Y0 = t7 ^ X2;
    *Y4 = t6 ^ X3;
    *Y1 = t5 ^ X7;
    *Y3 = t4 ^ X1;
}