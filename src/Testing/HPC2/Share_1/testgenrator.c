#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 50   // number of rows to generate
#define MAX_VAL 255 // max random value (8-bit numbers)

int main() {
    FILE *fp;
    fp = fopen("test_vectors.csv", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write CSV header
    fprintf(fp, "a0,a1,b0,b1,rand_01,a,b,c\n");

    srand(time(NULL)); // seed RNG

    for (int i = 0; i < ROWS; i++) {
        int a0 = rand() % (MAX_VAL + 1);
        int a1 = rand() % (MAX_VAL + 1);
        int b0 = rand() % (MAX_VAL + 1);
        int b1 = rand() % (MAX_VAL + 1);
        int rand_01 = (rand() % (MAX_VAL + 1));
        // int dec_2 = 2;
        

        int a = a0 ^ a1;
        int b = b0 ^ b1;
        int c = a & b;

        fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d\n",
                a0, a1, b0, b1, rand_01, a, b, c);
    }

    fclose(fp);
    printf("CSV file 'test_vectors.csv' generated successfully!\n");

    return 0;
}
