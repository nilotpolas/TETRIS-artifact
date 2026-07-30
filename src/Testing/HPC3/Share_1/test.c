/* HPC3 Function Definition */
#include<stdio.h>


void hpc3_same_shares_1_order(int a_share, int b_share, int * u_share) {
    * u_share  = (a_share & b_share);
}

void hpc3_v_1_order(int a_share, int b_share, int * v_share, int rand){
    int temp;
    temp = (b_share ^ rand);
    int a_share_;
	a_share_ = (a_share);
    *v_share = temp & a_share_;
}

void hpc3_w_1_order(int a_share, int rand, int prand, int * w_share){
    int temp;
    int a_share_neg;
    a_share_neg = ~(a_share);
    int x=a_share & a_share_neg;
    temp = a_share_neg & rand;
    *w_share = (temp ^ prand);
}

void hpc3_xor_vw_1_order(int v_share, int w_share, int * u_share){
    *u_share = v_share ^ w_share;
}


void HPC3(int a0, int a1, int b0, int b1, int* c0, int* c1, int r01, int p01){
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

int main(){
    int a0=182;
    int a1=87;
    int b0=33;
    int b1=94;
    int r01=188;
    int p01=26;
    int c0=0,c1=0;
    HPC3(a0,a1,b0,b1,&c0,&c1,r01,p01);
    int a=a0^a1;
    int b=b0^b1;
    int c=a&b;
    printf("a=%d    b=%d    c=%d\n", a,b,c);
    int cf=c0^c1;
    printf("c0= %d  c1=%d   cf=%d\n",c0,c1,cf);
}