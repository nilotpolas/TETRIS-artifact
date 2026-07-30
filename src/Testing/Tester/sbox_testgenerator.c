/**
 * @file generate_vectors.c
 * @brief Generates a CSV file with test vectors for an S-box function.
 *
 * This program creates a CSV file containing a comprehensive set of inputs
 * and the expected unshared output for a given S-box function. It iterates
 * through all 16 possible 4-bit inputs, generates randomized shares for each
 * input bit, and writes these along with other random and constant parameters
 * to the file. This is useful for creating a testbench for hardware or software
 * verification.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define how many random variations to generate for each of the 16 inputs.
// Set to 1 to generate 16 unique vectors, one for each input.
// Increase this to test the S-box with different random shares for the same input.
#define VECTORS_PER_INPUT 1

int main(void) {
    // The ground truth lookup table for the S-box.
    const int sbox_table[16] = {
        0xC, 0x6, 0x9, 0x0, 0x1, 0xA, 0x2, 0xB,
        0x3, 0x8, 0x5, 0xD, 0x4, 0xE, 0x7, 0xF
    };

    // --- File Handling ---
    const char *filename = "sbox_test_vectors.csv";
    FILE *csv_file = fopen(filename, "w");

    if (csv_file == NULL) {
        perror("Error: Could not open file for writing");
        return 1;
    }

    // --- CSV Header ---
    // These columns match the arguments of your sbox function.
    fprintf(csv_file,
            "x00,x01,x10,x11,x20,x21,x30,x31,"
            "const_in1,const_in2,const_in3,const_in4,"
            "rand_in2,rand_in3,rand_in1,rand_in4,"
            "expected_output\n");

    // Seed the random number generator to ensure different shares on each run.
    srand(time(NULL));
    int vectors_generated = 0;

    // --- Main Generation Loop ---
    // Loop through each of the 16 possible 4-bit inputs (0x0 to 0xF).
    for (int input = 0; input < 16; input++) {
        for (int i = 0; i < VECTORS_PER_INPUT; i++) {
            // 1. Decompose the 4-bit input into individual bits.
            int x0 = (input >> 0) & 1;
            int x1 = (input >> 1) & 1;
            int x2 = (input >> 2) & 1;
            int x3 = (input >> 3) & 1;

            // 2. Generate the first random share for each bit.
            // Using modulo 16 to keep values within a 4-bit range.
            int x00 = rand() % 16;
            int x10 = rand() % 16;
            int x20 = rand() % 16;
            int x30 = rand() % 16;

            // 3. Calculate the second share using the original bit (share ^ bit).
            int x01 = x00 ^ x0;
            int x11 = x10 ^ x1;
            int x21 = x20 ^ x2;
            int x31 = x30 ^ x3;

            // 4. Generate the other random inputs required by the function.
            int rand_1 = rand() % 16;
            int rand_2 = rand() % 16;
            int rand_3 = rand() % 16;
            int rand_4 = rand() % 16;

            // 5. Get the expected unshared output from the lookup table.
            int expected = sbox_table[input];

            // 6. Write all the generated values as a single row to the CSV file.
            fprintf(csv_file,
                    "%d,%d,%d,%d,%d,%d,%d,%d," // Input bit shares
                    "1,0,2,3,"                 // Constant inputs
                    "%d,%d,%d,%d,"             // Other random inputs
                    "%d\n",                    // Expected output
                    x00, x01, x10, x11, x20, x21, x30, x31,
                    rand_2, rand_3, rand_1, rand_4,
                    expected);
            vectors_generated++;
        }
    }

    // --- Cleanup ---
    fclose(csv_file);
    printf("✅ Successfully generated %d test vectors in '%s'.\n", vectors_generated, filename);

    return 0;
}