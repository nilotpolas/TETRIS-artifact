#include <stdio.h>
#include <stdbool.h>

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

void sbox(bool x0, bool x1, bool x2, bool x3, bool *y0, bool *y1, bool *y2, bool *y3, bool dec_1)
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
  *y2 = t18 ^ dec_1;

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
  *y3 = t28 ^ dec_1;
}

int main() {
    FILE *fp = fopen("sbox_output.csv", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write CSV Header
    fprintf(fp, "Input (Hex),Output (Hex)\n");

    printf("Generating S-box LUT...\n");

    for (int i = 0; i < 16; i++) {
        // Extract bits from the input integer (i)
        // Assuming x0 is the LSB and x3 is the MSB (or vice versa depending on your design)
        // Here we use: x0 = bit 0, x1 = bit 1, x2 = bit 2, x3 = bit 3
        bool x0 = (i >> 0) & 1;
        bool x1 = (i >> 1) & 1;
        bool x2 = (i >> 2) & 1;
        bool x3 = (i >> 3) & 1;

        bool y0, y1, y2, y3;
        
        // dec_1 is usually a control signal or constant in these implementations
        // I will set it to 0 (false) for standard S-box generation
        sbox(x0, x1, x2, x3, &y0, &y1, &y2, &y3, true);

        // Recombine output bits into a single integer
        int output = (y0 << 0) | (y1 << 1) | (y2 << 2) | (y3 << 3);

        // Log to console and write to CSV
        printf("In: %X -> Out: %X\n", i, output);
        fprintf(fp, "%X,%X\n", i, output);
    }

    fclose(fp);
    printf("Success! Data saved to sbox_output.csv\n");

    return 0;
}