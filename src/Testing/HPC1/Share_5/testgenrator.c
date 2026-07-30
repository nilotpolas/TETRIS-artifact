#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define D 5         // Security Order
#define SHARES (D + 1) // Number of shares (6)
#define ROWS 1000   // number of rows to generate
#define MAX_VAL 255 // max random value (8-bit numbers)

int main() {
    FILE *fp;
    fp = fopen("test_vectors_d5.csv", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // --- Write CSV header ---
    // a shares
    for (int i = 0; i < SHARES; i++) {
        fprintf(fp, "a%d,", i);
    }
    // b shares
    for (int i = 0; i < SHARES; i++) {
        fprintf(fp, "b%d,", i);
    }
    // rand values (d total)
    for (int i = 0; i < D; i++) {
        fprintf(fp, "rand_%d,", i);
    }
    // prand values
    for (int i = 0; i < D; i++) {
        for (int j = i + 1; j < SHARES; j++) {
            fprintf(fp, "prand_%d%d,", i, j);
        }
    }
    // Final expected values
    fprintf(fp, "a,b,c\n");

    // --- Seed RNG ---
    srand(time(NULL));

    // --- Generate Rows ---
    for (int i = 0; i < ROWS; i++) {
        int a_shares[SHARES];
        int b_shares[SHARES];
        int rands[D];
        // We use a 2D array for convenience. We only care about prands[i][j] where i < j
        int prands[D][SHARES]; 

        int a_unshared = 0;
        int b_unshared = 0;
        int c_expected = 0;

        // Generate a_shares and calculate a_unshared
        for (int j = 0; j < SHARES; j++) {
            a_shares[j] = rand() % (MAX_VAL + 1);
            a_unshared ^= a_shares[j];
            fprintf(fp, "%d,", a_shares[j]);
        }

        // Generate b_shares and calculate b_unshared
        for (int j = 0; j < SHARES; j++) {
            b_shares[j] = rand() % (MAX_VAL + 1);
            b_unshared ^= b_shares[j];
            fprintf(fp, "%d,", b_shares[j]);
        }

        // Generate rands
        for (int j = 0; j < D; j++) {
            rands[j] = rand() % (MAX_VAL + 1);
            fprintf(fp, "%d,", rands[j]);
        }

        // Generate prands
        for (int j = 0; j < D; j++) {
            for (int k = j + 1; k < SHARES; k++) {
                prands[j][k] = rand() % (MAX_VAL + 1);
                fprintf(fp, "%d,", prands[j][k]);
            }
        }

        // Calculate expected c
        c_expected = a_unshared & b_unshared;

        // Write final expected values
        fprintf(fp, "%d,%d,%d\n", a_unshared, b_unshared, c_expected);
    }

    fclose(fp);
    printf("CSV file 'test_vectors_d5.csv' generated successfully!\n");

    return 0;
}
