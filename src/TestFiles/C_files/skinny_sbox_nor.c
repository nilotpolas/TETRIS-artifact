#include <stdbool.h>

void sbox(bool i0, bool i1, bool i2, bool i3, bool i4, bool i5, bool i6, bool i7, bool dec_1,
          bool *o0, bool *o1, bool *o2, bool *o3, bool *o4, bool *o5, bool *o6, bool *o7) {
    
    // Intermediate variables
    bool n1, n2, n3, n6, n7;
    bool t0, t1, t2, t3, t4, t5, t6, t7;
    bool nt0, nt1, nt2, nt3, nt4, nt5;
    bool o0_val, o1_val, o2_val, o3_val, o4_val, o5_val, o6_val, o7_val;

    // Layer 1: Input Inversions
    n1 = !i1;
    n2 = !i2;
    n3 = !i3;
    n6 = !i6;
    n7 = !i7;

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