#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 50   // number of rows to generate
#define MAX_VAL 254 // max random value (8-bit numbers)
int reg(int x){
    return x;
}
// void hpc2_same_shares_1_order(int a_share, int b_share, int *u_share)
// {
//   int b_share_reg;
//   b_share_reg = reg(b_share);
//   *u_share = reg(a_share & b_share_reg);
// }

// void hpc2_v_1_order(int a_share, int b_share, int *v_share, int rand)
// {
//   int temp;
//   temp = reg(b_share ^ rand);
//   *v_share = reg(temp & a_share);
// }

// void hpc2_w_1_order(int a_share, int rand, int *w_share)
// {
//   int rand_reg;
//   rand_reg = reg(rand);
//   int a_neg;
//   a_neg = ~a_share;
//   *w_share = reg(a_neg & rand_reg);
// }

// void hpc2_xor_vw_1_order(int v_share, int w_share, int *u_share)
// {
//   *u_share = v_share ^ w_share;
// }

// void HPC2(int a0, int a1, int b0, int b1, int *c0, int *c1, int rand_01)
// {
//   int u00;
//   int u01;
//   int u10;
//   int u11;
//   int v01;
//   int v10;
//   int w01;
//   int w10;
//   hpc2_same_shares_1_order(a0, b0, &u00);
//   hpc2_v_1_order(a0, b1, &v01, rand_01);
//   hpc2_w_1_order(a0, rand_01, &w01);
//   hpc2_xor_vw_1_order(v01, w01, &u01);
//   hpc2_v_1_order(a1, b0, &v10, rand_01);
//   hpc2_w_1_order(a1, rand_01, &w10);
//   hpc2_xor_vw_1_order(v10, w10, &u10);
//   hpc2_same_shares_1_order(a1, b1, &u11);
//   *c0 = u00 ^ u01;
//   *c1 = u10 ^ u11;
// }

// void test(int a_0, int a_1, int b_0, int b_1, int c_0, int c_1, int d_0, int d_1, int *w_0, int *w_1, int rand_2, int rand_1)
// {
//   int a_inp_0;
//   int a_inp_1;
//   int b_inp_0;
//   int b_inp_1;
//   int c_inp_0;
//   int c_inp_1;
//   int d_inp_0;
//   int d_inp_1;
//   a_inp_0 = a_0;
//   a_inp_1 = a_1;
//   b_inp_0 = b_0;
//   b_inp_1 = b_1;
//   c_inp_0 = c_0;
//   c_inp_1 = c_1;
//   d_inp_0 = d_0;
//   d_inp_1 = d_1;
//   int x_0;
//   int x_1;
//   int y_0;
//   int y_1;
//   HPC2(a_inp_0, a_inp_1, b_inp_0, b_inp_1, &x_0, &x_1, rand_1);
//   HPC2(c_inp_0, c_inp_1, d_inp_0, d_inp_1, &y_0, &y_1, rand_2);
//   *w_0 = x_0 ^ y_0;
//   *w_1 = x_1 ^ y_1;
// }

void test(int a_0, int a_1, int b_0, int b_1, int c_0, int c_1, int d_0, int d_1, int *w_0, int *w_1, int rand_2, int rand_1)
{
  int a_0_inp;
  int a_1_inp;
  int b_0_inp;
  int b_1_inp;
  int c_0_inp;
  int c_1_inp;
  int d_0_inp;
  int d_1_inp;
  int rand_2_inp;
  int rand_1_inp;
  a_0_inp = a_0;
  a_1_inp = a_1;
  b_0_inp = b_0;
  b_1_inp = b_1;
  c_0_inp = c_0;
  c_1_inp = c_1;
  d_0_inp = d_0;
  d_1_inp = d_1;
  rand_2_inp = rand_2;
  rand_1_inp = rand_1;
  int a_inp_0;
  int a_inp_1;
  int b_inp_0;
  int b_inp_1;
  int c_inp_0;
  int c_inp_1;
  int d_inp_0;
  int d_inp_1;
  a_inp_0 = a_0_inp;
  a_inp_1 = a_1_inp;
  b_inp_0 = b_0_inp;
  b_inp_1 = b_1_inp;
  c_inp_0 = c_0_inp;
  c_inp_1 = c_1_inp;
  d_inp_0 = d_0_inp;
  d_inp_1 = d_1_inp;
  int x_0;
  int x_1;
  int y_0;
  int y_1;
  int u00_HPC20;
  int u01_HPC20;
  int u10_HPC20;
  int u11_HPC20;
  int v01_HPC20;
  int v10_HPC20;
  int w01_HPC20;
  int w10_HPC20;
  int b_share_reg_hpc2_same_shares_1_order0_HPC20;
  int temp_hpc2_v_1_order0_HPC20;
  int rand_reg_hpc2_w_1_order0_HPC20;
  int a_neg_hpc2_w_1_order0_HPC20;
  int temp_hpc2_v_1_order1_HPC20;
  int rand_reg_hpc2_w_1_order1_HPC20;
  int a_neg_hpc2_w_1_order1_HPC20;
  int b_share_reg_hpc2_same_shares_1_order1_HPC20;
  b_share_reg_hpc2_same_shares_1_order0_HPC20 = reg(b_inp_0);
  u00_HPC20 = reg(reg(a_inp_0) & b_share_reg_hpc2_same_shares_1_order0_HPC20);
  temp_hpc2_v_1_order0_HPC20 = reg(b_inp_1 ^ rand_1_inp);
  v01_HPC20 = reg(temp_hpc2_v_1_order0_HPC20 & reg(a_inp_0));
  rand_reg_hpc2_w_1_order0_HPC20 = reg(rand_1_inp);
  a_neg_hpc2_w_1_order0_HPC20 = ~a_inp_0;
  w01_HPC20 = reg(reg(a_neg_hpc2_w_1_order0_HPC20) & rand_reg_hpc2_w_1_order0_HPC20);
  u01_HPC20 = v01_HPC20 ^ w01_HPC20;
  temp_hpc2_v_1_order1_HPC20 = reg(b_inp_0 ^ rand_1_inp);
  v10_HPC20 = reg(temp_hpc2_v_1_order1_HPC20 & reg(a_inp_1));
  rand_reg_hpc2_w_1_order1_HPC20 = reg(rand_1_inp);
  a_neg_hpc2_w_1_order1_HPC20 = ~a_inp_1;
  w10_HPC20 = reg(reg(a_neg_hpc2_w_1_order1_HPC20) & rand_reg_hpc2_w_1_order1_HPC20);
  u10_HPC20 = v10_HPC20 ^ w10_HPC20;
  b_share_reg_hpc2_same_shares_1_order1_HPC20 = reg(b_inp_1);
  u11_HPC20 = reg(reg(a_inp_1) & b_share_reg_hpc2_same_shares_1_order1_HPC20);
  x_0 = u00_HPC20 ^ u01_HPC20;
  x_1 = u10_HPC20 ^ u11_HPC20;
  int u00_HPC21;
  int u01_HPC21;
  int u10_HPC21;
  int u11_HPC21;
  int v01_HPC21;
  int v10_HPC21;
  int w01_HPC21;
  int w10_HPC21;
  int b_share_reg_hpc2_same_shares_1_order0_HPC21;
  int temp_hpc2_v_1_order0_HPC21;
  int rand_reg_hpc2_w_1_order0_HPC21;
  int a_neg_hpc2_w_1_order0_HPC21;
  int temp_hpc2_v_1_order1_HPC21;
  int rand_reg_hpc2_w_1_order1_HPC21;
  int a_neg_hpc2_w_1_order1_HPC21;
  int b_share_reg_hpc2_same_shares_1_order1_HPC21;
  b_share_reg_hpc2_same_shares_1_order0_HPC21 = reg(d_inp_0);
  u00_HPC21 = reg(reg(c_inp_0) & b_share_reg_hpc2_same_shares_1_order0_HPC21);
  temp_hpc2_v_1_order0_HPC21 = reg(d_inp_1 ^ rand_2_inp);
  v01_HPC21 = reg(temp_hpc2_v_1_order0_HPC21 & reg(c_inp_0));
  rand_reg_hpc2_w_1_order0_HPC21 = reg(rand_2_inp);
  a_neg_hpc2_w_1_order0_HPC21 = ~c_inp_0;
  w01_HPC21 = reg(reg(a_neg_hpc2_w_1_order0_HPC21) & rand_reg_hpc2_w_1_order0_HPC21);
  u01_HPC21 = v01_HPC21 ^ w01_HPC21;
  temp_hpc2_v_1_order1_HPC21 = reg(d_inp_0 ^ rand_2_inp);
  v10_HPC21 = reg(temp_hpc2_v_1_order1_HPC21 & reg(c_inp_1));
  rand_reg_hpc2_w_1_order1_HPC21 = reg(rand_2_inp);
  a_neg_hpc2_w_1_order1_HPC21 = ~c_inp_1;
  w10_HPC21 = reg(reg(a_neg_hpc2_w_1_order1_HPC21) & rand_reg_hpc2_w_1_order1_HPC21);
  u10_HPC21 = v10_HPC21 ^ w10_HPC21;
  b_share_reg_hpc2_same_shares_1_order1_HPC21 = reg(d_inp_1);
  u11_HPC21 = reg(reg(c_inp_1) & b_share_reg_hpc2_same_shares_1_order1_HPC21);
  y_0 = u00_HPC21 ^ u01_HPC21;
  y_1 = u10_HPC21 ^ u11_HPC21;
  *w_0 = x_0 ^ y_0;
  *w_1 = x_1 ^ y_1;
}





void test1(int a, int b,int c,int d, int * r)
{
    int  x, y;
    x = a&b;
    y = c&d;
    * r = x ^ y;
}


int main() {
    FILE *fp;
    fp = fopen("test_vectors.csv", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write CSV header
    fprintf(fp, "a_0,a_1,b_0,b_1,c_0,c_1,d_0,d_1,rand_2,rand_1,a,b,c,d,out,out2\n");

    srand(time(NULL)); // seed RNG

    for (int i = 0; i < ROWS; i++) {
        int a_0 = rand() % (MAX_VAL + 1);
        int a_1 = rand() % (MAX_VAL + 1);
        int b_0 = rand() % (MAX_VAL + 1);
        int b_1 = rand() % (MAX_VAL + 1);
        int c_0 = rand() % (MAX_VAL + 1);
        int c_1 = rand() % (MAX_VAL + 1);
        int d_0 = rand() % (MAX_VAL + 1);
        int d_1 = rand() % (MAX_VAL + 1);

        int rand_1 = rand() % (MAX_VAL + 1);
        int rand_2 = rand() % (MAX_VAL + 1);
        // int rand_3 = rand() % (MAX_VAL + 1);
        // int rand_4 = rand() % (MAX_VAL + 1);
        // int rand_5 = rand() % (MAX_VAL + 1);
        // int rand_6 = rand() % (MAX_VAL + 1);
        // int rand_7 = rand() % (MAX_VAL + 1);
        // int rand_8 = rand() % (MAX_VAL + 1);

        int w_0;
        int w_1;

        test(a_0, a_1, b_0, b_1, c_0, c_1, d_0, d_1, &w_0, &w_1, rand_2, rand_1);

        int a = a_0 ^ a_1;
        int b = b_0 ^ b_1;
        int c = c_0 ^ c_1;
        int d = d_0 ^ d_1;
        int out=w_0^w_1;
        int out2;
        test1(a,b,c,d,&out2);
        fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                a_0, a_1, b_0, b_1, c_0, c_1, d_0, d_1, rand_2, rand_1, a, b, c, d, out,out2);
    }

    fclose(fp);
    printf("CSV file 'test_vectors.csv' generated successfully!\n");

    return 0;
}
