#include<stdbool.h>
void hpc2(int a0, int a1, int b0, int b1, int *y0, int *y1, int r01)
{
   
    int a0_neg, a1_neg;
    int u00, u01,u01_, u10,u10_, u11;
	int v01, v10;
	int w01, w10;
    a0_neg = !a0;
    a1_neg = !a1;
    w01 = a0_neg & r01;
    w10 = a1_neg & r01;
    v01 = b1 ^ r01;
    v10 = b0 ^ r01;
    u00 = a0 & b0;
    u01_ = a0 & v01;
    u01 = u01_ ^ w01;
    *y0 = u00 ^ u01;
    u11 = a1 & b1;
    u10_ = a1 & v10;
    u10 = w10 ^ u10_;
    *y1 = u11 ^ u10;
}