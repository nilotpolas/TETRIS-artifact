#include <stdbool.h>

void sbox(bool x0, bool x1, bool x2, bool x3, bool x4, bool x5, bool x6, bool x7,
          bool *o0, bool *o1, bool *o2, bool *o3, bool *o4, bool *o5, bool *o6, bool *o7) {

    
    bool t0, t1, t2, t3, t4, t5, t6, t7;
    bool net_o0, net_o1, net_o2, net_o3, net_o4, net_o5, net_o6, net_o7;

    
    t0 = x6 & x7;
    t1 = x3 & x2;
    t2 = x2 & x1;

    net_o6 = t0 ^ x4;
    net_o5 = t1 ^ x0;
    net_o1 = t2 ^ x6;

    t3 = net_o6 & net_o5;
    t4 = x3 & net_o5;

    net_o7 = x5 ^ t3;
    net_o3 = t4 ^ x1;
    t5 = net_o7 & net_o1;
    net_o2 = t5 ^ x7;

    t6 = net_o7 & net_o6;
    t7 = net_o3 & net_o2;

    net_o0 = t7 ^ x2;
    net_o4 = t6 ^ x3;

    *o7 = net_o2 ^ 1;
    *o6 = net_o1 ^ 1;
    *o5 = net_o7 ^ 1;
    *o4 = net_o6 ^ 1;
    *o3 = net_o4 ^ 1;
    *o2 = net_o0 ^ 1;
    *o1 = net_o3 ^ 1;
    *o0 = net_o5 ^ 1;
}