#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define NUM_VECTORS 50   // Defines how many random test vectors to generate

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_Bool reg(_Bool x){
    return x;
}

void hpc2_same_shares_1_order(_Bool a_share, _Bool b_share, _Bool *u_share)
{
  _Bool b_share_reg;
  b_share_reg = reg(b_share);
  *u_share = reg(a_share & b_share_reg);
}

void hpc2_v_1_order(_Bool a_share, _Bool b_share, _Bool *v_share, _Bool rand)
{
  _Bool temp;
  temp = reg(b_share ^ rand);
  *v_share = reg(temp & a_share);
}

void hpc2_w_1_order(_Bool a_share, _Bool rand, _Bool *w_share)
{
  _Bool rand_reg;
  rand_reg = reg(rand);
  _Bool a_neg;
  a_neg = !a_share;
  *w_share = reg(a_neg & rand_reg);
}

void hpc2_xor_vw_1_order(_Bool v_share, _Bool w_share, _Bool *u_share)
{
  *u_share = v_share ^ w_share;
}

void HPC2(_Bool a0, _Bool a1, _Bool b0, _Bool b1, _Bool *c0, _Bool *c1, _Bool rand_01)
{
  _Bool u00;
  _Bool u01;
  _Bool u10;
  _Bool u11;
  _Bool v01;
  _Bool v10;
  _Bool w01;
  _Bool w10;
  hpc2_same_shares_1_order(a0, b0, &u00);
  hpc2_v_1_order(a0, b1, &v01, rand_01);
  hpc2_w_1_order(a0, rand_01, &w01);
  hpc2_xor_vw_1_order(v01, w01, &u01);
  hpc2_v_1_order(a1, b0, &v10, rand_01);
  hpc2_w_1_order(a1, rand_01, &w10);
  hpc2_xor_vw_1_order(v10, w10, &u10);
  hpc2_same_shares_1_order(a1, b1, &u11);
  *c0 = u00 ^ u01;
  *c1 = u10 ^ u11;
}

void sbox1(_Bool x0_0, _Bool x0_1, _Bool x1_0, _Bool x1_1, _Bool x2_0, _Bool x2_1, _Bool x3_0, _Bool x3_1, _Bool *y0_0, _Bool *y0_1, _Bool *y1_0, _Bool *y1_1, _Bool *y2_0, _Bool *y2_1, _Bool *y3_0, _Bool *y3_1, _Bool dec_1, _Bool rand_16, _Bool rand_4, _Bool rand_3, _Bool rand_22, _Bool rand_7, _Bool rand_10, _Bool rand_18, _Bool rand_19, _Bool rand_20, _Bool rand_9, _Bool rand_17, _Bool rand_13, _Bool rand_1, _Bool rand_21, _Bool rand_15, _Bool rand_5, _Bool rand_2, _Bool rand_23, _Bool rand_6, _Bool rand_11, _Bool rand_12, _Bool rand_8, _Bool rand_14)
{
  _Bool temp1_y0_0;
  _Bool temp1_y0_1;
  _Bool temp1_y1_0;
  _Bool temp1_y1_1;
  _Bool temp2_y1_0;
  _Bool temp2_y1_1;
  _Bool temp3_y1_0;
  _Bool temp3_y1_1;
  _Bool temp4_y1_0;
  _Bool temp4_y1_1;
  _Bool temp5_y1_0;
  _Bool temp5_y1_1;
  _Bool temp1_y2_0;
  _Bool temp1_y2_1;
  _Bool temp2_y2_0;
  _Bool temp2_y2_1;
  _Bool temp3_y2_0;
  _Bool temp3_y2_1;
  _Bool temp4_y2_0;
  _Bool temp4_y2_1;
  _Bool temp5_y2_0;
  _Bool temp5_y2_1;
  _Bool temp1_y3_0;
  _Bool temp1_y3_1;
  _Bool temp2_y3_0;
  _Bool temp2_y3_1;
  _Bool temp3_y3_0;
  _Bool temp3_y3_1;
  _Bool temp4_y3_0;
  _Bool temp4_y3_1;
  _Bool t1_0;
  _Bool t1_1;
  _Bool t2_0;
  _Bool t2_1;
  _Bool t8_0;
  _Bool t8_1;
  _Bool t9_0;
  _Bool t9_1;
  _Bool t10_0;
  _Bool t10_1;
  _Bool t11_0;
  _Bool t11_1;
  _Bool t12_0;
  _Bool t12_1;
  _Bool t18_0;
  _Bool t18_1;
  _Bool t19_0;
  _Bool t19_1;
  _Bool t20_0;
  _Bool t20_1;
  _Bool t21_0;
  _Bool t21_1;
  _Bool t22_0;
  _Bool t22_1;
  _Bool t23_0;
  _Bool t23_1;
  _Bool t28_0;
  _Bool t28_1;
  _Bool t29_0;
  _Bool t29_1;
  _Bool t30_0;
  _Bool t30_1;
  _Bool t31_0;
  _Bool t31_1;
  _Bool t32_0;
  _Bool t32_1;
  _Bool t33_0;
  _Bool t33_1;
  HPC2(x1_0, x1_1, x2_0, x2_1, &temp1_y0_0, &temp1_y0_1, rand_1);
  t2_0 = x2_0 ^ x3_0;
  t2_1 = x2_1 ^ x3_1;
  t1_0 = t2_0 ^ temp1_y0_0;
  t1_1 = t2_1 ^ temp1_y0_1;
  *y0_0 = t1_0 ^ x0_0;
  *y0_1 = t1_1 ^ x0_1;
  _Bool temp_and_30_0;
  _Bool temp_and_30_1;
  HPC2(x0_0, x0_1, x1_0, x1_1, &temp_and_30_0, &temp_and_30_1, rand_2);
  HPC2(temp_and_30_0, temp_and_30_1, x2_0, x2_1, &temp1_y1_0, &temp1_y1_1, rand_3);
  _Bool temp_and_31_0;
  _Bool temp_and_31_1;
  HPC2(x0_0, x0_1, x1_0, x1_1, &temp_and_31_0, &temp_and_31_1, rand_4);
  HPC2(temp_and_31_0, temp_and_31_1, x3_0, x3_1, &temp2_y1_0, &temp2_y1_1, rand_5);
  _Bool temp_and_32_0;
  _Bool temp_and_32_1;
  HPC2(x0_0, x0_1, x2_0, x2_1, &temp_and_32_0, &temp_and_32_1, rand_6);
  HPC2(temp_and_32_0, temp_and_32_1, x3_0, x3_1, &temp3_y1_0, &temp3_y1_1, rand_7);
  HPC2(x1_0, x1_1, x3_0, x3_1, &temp4_y1_0, &temp4_y1_1, rand_8);
  HPC2(x2_0, x2_1, x3_0, x3_1, &temp5_y1_0, &temp5_y1_1, rand_9);
  t12_0 = x1_0 ^ x3_0;
  t12_1 = x1_1 ^ x3_1;
  t11_0 = t12_0 ^ temp1_y1_0;
  t11_1 = t12_1 ^ temp1_y1_1;
  t10_0 = t11_0 ^ temp2_y1_0;
  t10_1 = t11_1 ^ temp2_y1_1;
  t9_0 = t10_0 ^ temp3_y1_0;
  t9_1 = t10_1 ^ temp3_y1_1;
  t8_0 = t9_0 ^ temp4_y1_0;
  t8_1 = t9_1 ^ temp4_y1_1;
  *y1_0 = t8_0 ^ temp5_y1_0;
  *y1_1 = t8_1 ^ temp5_y1_1;
  _Bool temp_and_33_0;
  _Bool temp_and_33_1;
  HPC2(x0_0, x0_1, x1_0, x1_1, &temp_and_33_0, &temp_and_33_1, rand_10);
  HPC2(temp_and_33_0, temp_and_33_1, x3_0, x3_1, &temp1_y2_0, &temp1_y2_1, rand_11);
  _Bool temp_and_34_0;
  _Bool temp_and_34_1;
  HPC2(x0_0, x0_1, x2_0, x2_1, &temp_and_34_0, &temp_and_34_1, rand_12);
  HPC2(temp_and_34_0, temp_and_34_1, x3_0, x3_1, &temp2_y2_0, &temp2_y2_1, rand_13);
  HPC2(x0_0, x0_1, x1_0, x1_1, &temp3_y2_0, &temp3_y2_1, rand_14);
  HPC2(x0_0, x0_1, x3_0, x3_1, &temp4_y2_0, &temp4_y2_1, rand_15);
  HPC2(x1_0, x1_1, x3_0, x3_1, &temp5_y2_0, &temp5_y2_1, rand_16);
  t23_0 = temp1_y2_0 ^ temp2_y2_0;
  t23_1 = temp1_y2_1 ^ temp2_y2_1;
  t22_0 = t23_0 ^ temp3_y2_0;
  t22_1 = t23_1 ^ temp3_y2_1;
  t21_0 = t22_0 ^ temp4_y2_0;
  t21_1 = t22_1 ^ temp4_y2_1;
  t20_0 = t21_0 ^ temp5_y2_0;
  t20_1 = t21_1 ^ temp5_y2_1;
  t19_0 = t20_0 ^ x2_0;
  t19_1 = t20_1 ^ x2_1;
  t18_0 = t19_0 ^ x3_0;
  t18_1 = t19_1 ^ x3_1;
  *y2_0 = t18_0 ^ 0;
  *y2_1 = t18_1 ^ dec_1;
  _Bool temp_and_35_0;
  _Bool temp_and_35_1;
  HPC2(x0_0, x0_1, x1_0, x1_1, &temp_and_35_0, &temp_and_35_1, rand_17);
  HPC2(temp_and_35_0, temp_and_35_1, x2_0, x2_1, &temp1_y3_0, &temp1_y3_1, rand_18);
  _Bool temp_and_36_0;
  _Bool temp_and_36_1;
  HPC2(x0_0, x0_1, x1_0, x1_1, &temp_and_36_0, &temp_and_36_1, rand_19);
  HPC2(temp_and_36_0, temp_and_36_1, x3_0, x3_1, &temp2_y3_0, &temp2_y3_1, rand_20);
  _Bool temp_and_37_0;
  _Bool temp_and_37_1;
  HPC2(x0_0, x0_1, x2_0, x2_1, &temp_and_37_0, &temp_and_37_1, rand_21);
  HPC2(temp_and_37_0, temp_and_37_1, x3_0, x3_1, &temp3_y3_0, &temp3_y3_1, rand_22);
  HPC2(x1_0, x1_1, x2_0, x2_1, &temp4_y3_0, &temp4_y3_1, rand_23);
  t33_0 = temp1_y3_0 ^ temp2_y3_0;
  t33_1 = temp1_y3_1 ^ temp2_y3_1;
  t32_0 = t33_0 ^ temp3_y3_0;
  t32_1 = t33_1 ^ temp3_y3_1;
  t31_0 = t32_0 ^ temp4_y3_0;
  t31_1 = t32_1 ^ temp4_y3_1;
  t30_0 = t31_0 ^ x0_0;
  t30_1 = t31_1 ^ x0_1;
  t29_0 = t30_0 ^ x1_0;
  t29_1 = t30_1 ^ x1_1;
  t28_0 = t29_0 ^ x3_0;
  t28_1 = t29_1 ^ x3_1;
  *y3_0 = t28_0 ^ 0;
  *y3_1 = t28_1 ^ dec_1;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void and_2(bool a, bool b, bool *d)
{
  *d = a & b;
}

void and_3(bool a, bool b, bool c, bool * d)
{
  bool temp;
  and_2(a, b, &temp);
  and_2(temp, c, d);
}

void sbox(bool x0, bool x1, bool x2, bool x3, bool *y0, bool *y1, bool *y2, bool *y3)
{
  bool temp1_y0, temp1_y1, temp2_y1, temp3_y1, temp4_y1, temp5_y1, temp1_y2, temp2_y2, temp3_y2, temp4_y2, temp5_y2, temp1_y3, temp2_y3, temp3_y3, temp4_y3;
  bool t1, t2, t8, t9, t10, t11, t12, t18, t19, t20, t21, t22, t23, t28, t29, t30, t31, t32, t33;
  and_2(x1, x2, &temp1_y0);
  
  t2 = x2 ^ x3;
  t1 = t2 ^ temp1_y0;
  *y0 = t1 ^ x0;
  
  and_3(x0, x1, x2, &temp1_y1);
  and_3(x0, x1, x3, &temp2_y1);
  and_3(x0, x2, x3, &temp3_y1);
  and_2(x1, x3, &temp4_y1);
  and_2(x2, x3, &temp5_y1);

  t12 = x1 ^ x3;
  t11 = t12 ^ temp1_y1;
  t10 = t11 ^ temp2_y1;
  t9 = t10 ^ temp3_y1;
  t8 = t9 ^ temp4_y1;
  *y1 = t8 ^ temp5_y1;

  and_3(x0, x1, x3, &temp1_y2);
  and_3(x0, x2, x3, &temp2_y2);
  and_2(x0, x1, &temp3_y2);
  and_2(x0, x3, &temp4_y2);
  and_2(x1, x3, &temp5_y2);

  t23 = temp1_y2 ^ temp2_y2;
  t22 = t23 ^ temp3_y2;
  t21 = t22 ^ temp4_y2;
  t20 = t21 ^ temp5_y2;
  t19 = t20 ^ x2;
  t18 = t19 ^ x3;
  *y2 = t18 ^ 1;

  and_3(x0, x1, x2, &temp1_y3);
  and_3(x0, x1, x3, &temp2_y3);
  and_3(x0, x2, x3, &temp3_y3);
  and_2(x1, x2, &temp4_y3);

  t33 = temp1_y3 ^ temp2_y3;
  t32 = t33 ^ temp3_y3;
  t31 = t32 ^ temp4_y3;
  t30 = t31 ^ x0;
  t29 = t30 ^ x1;
  t28 = t29 ^ x3;
  *y3 = t28 ^ 1;
}

int main() {
    FILE *fp;
    fp = fopen("test_vectors.csv", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write a 40-column CSV header
    fprintf(fp, "x0_0,x0_1,x1_0,x1_1,x2_0,x2_1,x3_0,x3_1,dec_1,"
                "rand_1,rand_2,rand_3,rand_4,rand_5,rand_6,rand_7,rand_8,"
                "rand_9,rand_10,rand_11,rand_12,rand_13,rand_14,rand_15,"
                "rand_16,rand_17,rand_18,rand_19,rand_20,rand_21,rand_22,rand_23,"
                "exp_y0,exp_y1,exp_y2,exp_y3,y0,y1,y2,y3\n");

    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < NUM_VECTORS; i++) {
        bool x0 = rand() % 2; bool x1 = rand() % 2;
        bool x2 = rand() % 2; bool x3 = rand() % 2;

        bool x0_0 = rand() % 2; bool x0_1 = x0_0 ^ x0;
        bool x1_0 = rand() % 2; bool x1_1 = x1_0 ^ x1;
        bool x2_0 = rand() % 2; bool x2_1 = x2_0 ^ x2;
        bool x3_0 = rand() % 2; bool x3_1 = x3_0 ^ x3;
        bool dec_1 = 1;

        bool rands[23];
        for(int j=0; j<23; j++) {
            rands[j] = rand() % 2;
        }

        bool y0, y1, y2, y3;
        sbox(x0, x1, x2, x3, &y0, &y1, &y2, &y3);

        // _Bool x0_0, x0_1, x1_0, x1_1, x2_0, x2_1, x3_0, x3_1;
        _Bool y0_0, y0_1, y1_0, y1_1, y2_0, y2_1, y3_0, y3_1;
        sbox1(
        x0_0, x0_1, x1_0, x1_1, x2_0, x2_1, x3_0, x3_1,
        &y0_0, &y0_1, &y1_0, &y1_1, &y2_0, &y2_1, &y3_0, &y3_1,
        dec_1, rands[0], rands[1], rands[2], rands[3], rands[4], rands[5], rands[6], rands[7],
                rands[8], rands[9], rands[10], rands[11], rands[12], rands[13], rands[14],
                rands[15], rands[16], rands[17], rands[18], rands[19], rands[20], rands[21], rands[22]
    );


        // Write 40 columns of data to the CSV file
        fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,"
                    "%d,%d,%d,%d,%d,%d,%d,%d,"
                    "%d,%d,%d,%d,%d,%d,%d,"
                    "%d,%d,%d,%d,%d,%d,%d,%d,"
                    "%d,%d,%d,%d,%d,%d,%d,%d\n",
                x0_0, x0_1, x1_0, x1_1, x2_0, x2_1, x3_0, x3_1, dec_1,
                rands[0], rands[1], rands[2], rands[3], rands[4], rands[5], rands[6], rands[7],
                rands[8], rands[9], rands[10], rands[11], rands[12], rands[13], rands[14],
                rands[15], rands[16], rands[17], rands[18], rands[19], rands[20], rands[21], rands[22],
                y0, y1, y2, y3,
                y0_0 ^ y0_1, y1_0 ^ y1_1, y2_0 ^ y2_1, y3_0 ^ y3_1
        );
    }

    fclose(fp);
    printf("CSV file 'test_vectors.csv' with %d vectors (36 columns) generated successfully!\n", NUM_VECTORS);

    return 0;
}