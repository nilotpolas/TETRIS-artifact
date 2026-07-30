#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//======================================================================
// Your Provided AES S-Box Implementation
//======================================================================

static int A2X[8] = {152, 243, 242, 72, 9, 129, 169, 255},
           X2A[8] = {100, 120, 110, 140, 104, 41, 222, 96},
           X2S[8] = {88, 45, 158, 11, 220, 4, 3, 36},
           S2X[8] = {140, 121, 5, 235, 18, 4, 81, 83};


/**
 * @brief Multiplication in the Galois Field GF(2^2).
 */
int G4_mul(int x, int y) {
  int a, b, c, d, e, p, q;

  a = (x & 0x2) >> 1;
  b = (x & 0x1);
  c = (y & 0x2) >> 1;
  d = (y & 0x1);
  e = (a ^ b) & (c ^ d);
  p = (a & c) ^ e;
  q = (b & d) ^ e;
  return ((p << 1) | q);
}

/**
 * @brief Scaling operation in GF(2^2).
 */
int G4_scl_N(int x) {
  int a, b, p, q;

  a = (x & 0x2) >> 1;
  b = (x & 0x1);
  p = b;
  q = a ^ b;
  return ((p << 1) | q);
}

/**
 * @brief Another scaling operation in GF(2^2).
 */
int G4_scl_N2(int x) {
  int a, b, p, q;

  a = (x & 0x2) >> 1;
  b = (x & 0x1);
  p = a ^ b;
  q = a;
  return ((p << 1) | q);
}

/**
 * @brief Squaring operation in GF(2^2).
 */
int G4_sq(int x) {
  int a, b;

  a = (x & 0x2) >> 1;
  b = (x & 0x1);
  return ((b << 1) | a);
}

/**
 * @brief Multiplication in the Galois Field GF(2^4).
 */
int G16_mul(int x, int y) {
  int a, b, c, d, e, p, q;

  a = (x & 0xC) >> 2;
  b = (x & 0x3);
  c = (y & 0xC) >> 2;
  d = (y & 0x3);
  e = G4_mul(a ^ b, c ^ d);
  e = G4_scl_N(e);
  p = G4_mul(a, c) ^ e;
  q = G4_mul(b, d) ^ e;
  return ((p << 2) | q);
}

/**
 * @brief Squaring and scaling operation in GF(2^4).
 */
int G16_sq_scl(int x) {
  int a, b, p, q;

  a = (x & 0xC) >> 2;
  b = (x & 0x3);
  p = G4_sq(a ^ b);
  q = G4_scl_N2(G4_sq(b));
  return ((p << 2) | q);
}

/**
 * @brief Inversion in GF(2^4).
 */
int G16_inv(int x) {
  int a, b, c, d, e, p, q;

  a = (x & 0xC) >> 2;
  b = (x & 0x3);
  c = G4_scl_N(G4_sq(a ^ b));
  d = G4_mul(a, b);
  e = G4_sq(c ^ d);
  p = G4_mul(e, b);
  q = G4_mul(e, a);
  return ((p << 2) | q);
}

/**
 * @brief Inversion in the Galois Field GF(2^8).
 */
int G256_inv(int x) {
  int a, b, c, d, e, p, q;

  a = (x & 0xF0) >> 4;
  b = (x & 0x0F);
  c = G16_sq_scl(a ^ b);
  d = G16_mul(a, b);
  e = G16_inv(c ^ d);
  p = G16_mul(e, b);
  q = G16_mul(e, a);
  return ((p << 4) | q);
}

/**
 * @brief Changes the basis of a polynomial in GF(2^8).
 */
int G256_newbasis(int x, int b[]) {
  int i, y = 0;

  for (i = 7; i >= 0; i--) {
    if (x & 1)
      y ^= b[i];
    x >>= 1;
  }
  return (y);
}

/**
 * @brief The AES S-box function.
 */
int sbox(int n) {
  int t;

  t = G256_newbasis(n, A2X);
  t = G256_inv(t);
  t = G256_newbasis(t, X2S);
  return (t ^ 0x63);
}


//======================================================================
// Main function to generate test vectors
//======================================================================
int main() {
    FILE *fp;
    const char *filename = "sbox_test_vectors.csv";
    int num_vectors = 256; // Test all possible 8-bit inputs

    // Open the CSV file for writing
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write the CSV header
    fprintf(fp, "Input,Output\n");

    printf("Generating %d test vectors for the S-box...\n", num_vectors);

    // Loop through all possible 8-bit inputs
    for (int i = 0; i < num_vectors; i++) {
        int input = i;
        int output = sbox(input);

        // Write the input and output to the file
        // We write in hexadecimal format (e.g., 0x5A) for easier comparison
        // with standard AES S-box tables.
        fprintf(fp, "%d,%d\n", input, output);
    }

    // Close the file
    fclose(fp);

    printf("Successfully generated %d test vectors in '%s'.\n", num_vectors, filename);

    return 0;
}
