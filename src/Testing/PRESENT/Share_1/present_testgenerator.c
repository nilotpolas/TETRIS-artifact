#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define NUM_VECTORS 50   // Defines how many random test vectors to generate

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    fprintf(fp, "x0_0,x0_1,x1_0,x1_1,x2_0,x2_1,x3_0,x3_1,dec_1,dec_0"
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
        bool dec_0 = 0;

        bool rands[23];
        for(int j=0; j<23; j++) {
            rands[j] = rand() % 2;
        }

        bool y0, y1, y2, y3;
        sbox(x0, x1, x2, x3, &y0, &y1, &y2, &y3);

        // _Bool x0_0, x0_1, x1_0, x1_1, x2_0, x2_1, x3_0, x3_1;
        _Bool y0_0, y0_1, y1_0, y1_1, y2_0, y2_1, y3_0, y3_1;
    //     sbox2(
    //     x0_0, x0_1, x1_0, x1_1, x2_0, x2_1, x3_0, x3_1,
    //     &y0_0, &y0_1, &y1_0, &y1_1, &y2_0, &y2_1, &y3_0, &y3_1,
    //     dec_1,dec_0, rands[0], rands[1], rands[2], rands[3], rands[4], rands[5], rands[6], rands[7],
    //             rands[8], rands[9], rands[10], rands[11], rands[12], rands[13], rands[14],
    //             rands[15], rands[16], rands[17], rands[18], rands[19], rands[20], rands[21], rands[22]
    // );


        // Write 40 columns of data to the CSV file
        fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,"
                    "%d,%d,%d,%d,%d,%d,%d,%d,"
                    "%d,%d,%d,%d,%d,%d,%d,"
                    "%d,%d,%d,%d,%d,%d,%d,%d,"
                    "%d,%d,%d,%d,%d,%d,%d,%d\n",
                x0_0, x0_1, x1_0, x1_1, x2_0, x2_1, x3_0, x3_1, dec_1,dec_0,
                rands[0], rands[1], rands[2], rands[3], rands[4], rands[5], rands[6], rands[7],
                rands[8], rands[9], rands[10], rands[11], rands[12], rands[13], rands[14],
                rands[15], rands[16], rands[17], rands[18], rands[19], rands[20], rands[21], rands[22],
                y0, y1, y2, y3,
                y0,y1,y2,y3
        );
    }

    fclose(fp);
    printf("CSV file 'test_vectors.csv' with %d vectors (36 columns) generated successfully!\n", NUM_VECTORS);

    return 0;
}