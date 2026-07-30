#include <stdio.h>
#include <stdbool.h>

// The sbox function remains exactly the same as before.
void sbox (bool X7, bool X6, bool X5, bool X4, bool X3, bool X2, bool X1, bool X0, bool dec_1, bool *Y7, bool *Y6, bool *Y5, bool *Y4, bool *Y3, bool *Y2, bool *Y1, bool *Y0) {
	

	//declare T signals
	bool T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27;

	//declare M signals
	bool M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,
    M11, M12, M13, M14, M15, M16, M17, M18, M19, M20,
    M21, M22, M23, M24, M25, M26, M27, M28, M29, M30,
    M31, M32, M33, M34, M35, M36, M37, M38, M39, M40,
    M41, M42, M43, M44, M45, M46, M47, M48, M49, M50,
    M51, M52, M53, M54, M55, M56, M57, M58, M59, M60,
    M61, M62, M63;

	//declare L signals
	bool L0, L1, L2, L3, L4, L5, L6, L7, L8, L9,
    L10, L11, L12, L13, L14, L15, L16, L17, L18, L19,
    L20, L21, L22, L23, L24, L25, L26, L27, L28, L29;

	
	// ----- T signals -----
    T1  = X0 ^ X3;
    T2  = X0 ^ X5;
    T3  = X0 ^ X6;
    T4  = X3 ^ X5;
    T5  = X4 ^ X6;
    T6  = T1 ^ T5;
    T7  = X1 ^ X2;
    T8  = X7 ^ T6;
    T9  = X7 ^ T7;
    T10 = T6 ^ T7;
    T11 = X1 ^ X5;
    T12 = X2 ^ X5;
    T13 = T3 ^ T4;
    T14 = T6 ^ T11;
    T15 = T5 ^ T11;
    T16 = T5 ^ T12;
    T17 = T9 ^ T16;
    T18 = X3 ^ X7;
    T19 = T7 ^ T18;
    T20 = T1 ^ T19;
    T21 = X6 ^ X7;
    T22 = T7 ^ T21;
    T23 = T2 ^ T22;
    T24 = T2 ^ T10;
    T25 = T20 ^ T17;
    T26 = T3 ^ T16;
    T27 = T1 ^ T12;

	M1  = T13 & T6;
    M2  = T23 & T8;
    M3  = T14 ^ M1;
    M4  = T19 & X7;
    M5  = M4 ^ M1;
    M6  = T3 & T16;
    M7  = T22 & T9;
    M8  = T26 ^ M6;
    M9  = T20 & T17;
    M10 = M9 ^ M6;
    M11 = T1 & T15;
    M12 = T4 & T27;
    M13 = M12 ^ M11;
    M14 = T2 & T10;
    M15 = M14 ^ M11;
    M16 = M3 ^ M2;
    M17 = M5 ^ T24;
    M18 = M8 ^ M7;
    M19 = M10 ^ M15;
    M20 = M16 ^ M13;
    M21 = M17 ^ M15;
    M22 = M18 ^ M13;
    M23 = M19 ^ T25;
    M24 = M22 ^ M23;
    M25 = M22 & M20;
    M26 = M21 ^ M25;
    M27 = M20 ^ M21;
    M28 = M23 ^ M25;
    M29 = M28 & M27;
    M30 = M26 & M24;
    M31 = M20 & M23;
    M32 = M27 & M31;
    M33 = M27 ^ M25;
    M34 = M21 & M22;
    M35 = M24 & M34;
    M36 = M24 ^ M25;
    M37 = M21 ^ M29;
    M38 = M32 ^ M33;
    M39 = M23 ^ M30;
    M40 = M35 ^ M36;
    M41 = M38 ^ M40;
    M42 = M37 ^ M39;
    M43 = M37 ^ M38;
    M44 = M39 ^ M40;
    M45 = M42 ^ M41;
    M46 = M44 & T6;
    M47 = M40 & T8;
    M48 = M39 & X7;
    M49 = M43 & T16;
    M50 = M38 & T9;
    M51 = M37 & T17;
    M52 = M42 & T15;
    M53 = M45 & T27;
    M54 = M41 & T10;
    M55 = M44 & T13;
    M56 = M40 & T23;
    M57 = M39 & T19;
    M58 = M43 & T3;
    M59 = M38 & T22;
    M60 = M37 & T20;
    M61 = M42 & T1;
    M62 = M45 & T4;
    M63 = M41 & T2;

    // ----- L signals -----
    L0  = M61 ^ M62;
    L1  = M50 ^ M56;
    L2  = M46 ^ M48;
    L3  = M47 ^ M55;
    L4  = M54 ^ M58;
    L5  = M49 ^ M61;
    L6  = M62 ^ L5;
    L7  = M46 ^ L3;
    L8  = M51 ^ M59;
    L9  = M52 ^ M53;
    L10 = M53 ^ L4;
    L11 = M60 ^ L2;
    L12 = M48 ^ M51;
    L13 = M50 ^ L0;
    L14 = M52 ^ M61;
    L15 = M55 ^ L1;
    L16 = M56 ^ L0;
    L17 = M57 ^ L1;
    L18 = M58 ^ L8;
    L19 = M63 ^ L4;
    L20 = L0 ^ L1;
    L21 = L1 ^ L7;
    L22 = L3 ^ L12;
    L23 = L18 ^ L2;
    L24 = L15 ^ L9;
    L25 = L6 ^ L10;
    L26 = L7 ^ L9;
    L27 = L8 ^ L10;
    L28 = L11 ^ L14;
    L29 = L11 ^ L17;

    // ----- Outputs -----
    *Y0 = L6 ^ L24;
	bool temp1 = L16 ^ L26;
    *Y1 = temp1 ^ dec_1;  // XNOR
	bool temp2 = L19 ^ L28;
    *Y2 = temp2 ^ dec_1;  // XNOR
    *Y3 = L6 ^ L21;
    *Y4 = L20 ^ L22;
    *Y5 = L25 ^ L29;
	bool temp3 = L13 ^ L27;
    *Y6 = temp3 ^ dec_1;  // XNOR
	bool temp4 = L6 ^ L23;
    *Y7 = temp4 ^ dec_1;   // XNOR
}


int main() {
    // Open the CSV file for writing
    const char* filename = "sbox_simulation.csv";
    FILE *csv_file = fopen(filename, "w");

    // Check if the file was opened successfully
    if (csv_file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // **MODIFICATION: Write the header with columns in descending order (MSB first)**
    fprintf(csv_file, "x7,x6,x5,x4,x3,x2,x1,x0,y7,y6,y5,y4,y3,y2,y1,y0\n");

    // dec_1 is fixed to true (1) for decryption mode
    const bool dec_1 = true;

    // Loop through all 2^8 = 256 possible inputs
    for (int i = 0; i < 256; i++) {
        bool X[8];
        bool Y[8];

        // Deconstruct the integer 'i' into 8 boolean inputs (X[0] is LSB)
        for (int j = 0; j < 8; j++) {
            X[j] = (i >> j) & 1;
        }

        // Call the sbox function
        sbox(X[0], X[1], X[2], X[3], X[4], X[5], X[6], X[7],
             dec_1,
             &Y[0], &Y[1], &Y[2], &Y[3], &Y[4], &Y[5], &Y[6], &Y[7]);

        // **MODIFICATION: Write data with columns in descending order (MSB first)**
        fprintf(csv_file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                X[7], X[6], X[5], X[4], X[3], X[2], X[1], X[0],
                Y[7], Y[6], Y[5], Y[4], Y[3], Y[2], Y[1], Y[0]);
    }

    // Close the file
    fclose(csv_file);

    printf("Simulation complete. Results written to '%s'.\n", filename);

    return 0;
}


// #include <stdio.h>
// #include <stdbool.h>
// int sbox (bool X0, bool X1, bool X2, bool X3, bool X4, bool X5, bool X6, bool X7, bool *Y0, bool *Y1, bool *Y2, bool *Y3, bool *Y4, bool *Y5, bool *Y6, bool *Y7) {
	

// 	//declare T signals
// 	bool T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27;

// 	//declare M signals
// 	bool M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,
//     M11, M12, M13, M14, M15, M16, M17, M18, M19, M20,
//     M21, M22, M23, M24, M25, M26, M27, M28, M29, M30,
//     M31, M32, M33, M34, M35, M36, M37, M38, M39, M40,
//     M41, M42, M43, M44, M45, M46, M47, M48, M49, M50,
//     M51, M52, M53, M54, M55, M56, M57, M58, M59, M60,
//     M61, M62, M63;

// 	//declare L signals
// 	bool L0, L1, L2, L3, L4, L5, L6, L7, L8, L9,
//     L10, L11, L12, L13, L14, L15, L16, L17, L18, L19,
//     L20, L21, L22, L23, L24, L25, L26, L27, L28, L29;

	
// 	// ----- T signals -----
//     T1  = X0 ^ X3;
//     T2  = X0 ^ X5;
//     T3  = X0 ^ X6;
//     T4  = X3 ^ X5;
//     T5  = X4 ^ X6;
//     T6  = T1 ^ T5;
//     T7  = X1 ^ X2;
//     T8  = X7 ^ T6;
//     T9  = X7 ^ T7;
//     T10 = T6 ^ T7;
//     T11 = X1 ^ X5;
//     T12 = X2 ^ X5;
//     T13 = T3 ^ T4;
//     T14 = T6 ^ T11;
//     T15 = T5 ^ T11;
//     T16 = T5 ^ T12;
//     T17 = T9 ^ T16;
//     T18 = X3 ^ X7;
//     T19 = T7 ^ T18;
//     T20 = T1 ^ T19;
//     T21 = X6 ^ X7;
//     T22 = T7 ^ T21;
//     T23 = T2 ^ T22;
//     T24 = T2 ^ T10;
//     T25 = T20 ^ T17;
//     T26 = T3 ^ T16;
//     T27 = T1 ^ T12;

// 	M1  = T13 & T6;
//     M2  = T23 & T8;
//     M3  = T14 ^ M1;
//     M4  = T19 & X7;
//     M5  = M4 ^ M1;
//     M6  = T3 & T16;
//     M7  = T22 & T9;
//     M8  = T26 ^ M6;
//     M9  = T20 & T17;
//     M10 = M9 ^ M6;
//     M11 = T1 & T15;
//     M12 = T4 & T27;
//     M13 = M12 ^ M11;
//     M14 = T2 & T10;
//     M15 = M14 ^ M11;
//     M16 = M3 ^ M2;
//     M17 = M5 ^ T24;
//     M18 = M8 ^ M7;
//     M19 = M10 ^ M15;
//     M20 = M16 ^ M13;
//     M21 = M17 ^ M15;
//     M22 = M18 ^ M13;
//     M23 = M19 ^ T25;
//     M24 = M22 ^ M23;
//     M25 = M22 & M20;
//     M26 = M21 ^ M25;
//     M27 = M20 ^ M21;
//     M28 = M23 ^ M25;
//     M29 = M28 & M27;
//     M30 = M26 & M24;
//     M31 = M20 & M23;
//     M32 = M27 & M31;
//     M33 = M27 ^ M25;
//     M34 = M21 & M22;
//     M35 = M24 & M34;
//     M36 = M24 ^ M25;
//     M37 = M21 ^ M29;
//     M38 = M32 ^ M33;
//     M39 = M23 ^ M30;
//     M40 = M35 ^ M36;
//     M41 = M38 ^ M40;
//     M42 = M37 ^ M39;
//     M43 = M37 ^ M38;
//     M44 = M39 ^ M40;
//     M45 = M42 ^ M41;
//     M46 = M44 & T6;
//     M47 = M40 & T8;
//     M48 = M39 & X7;
//     M49 = M43 & T16;
//     M50 = M38 & T9;
//     M51 = M37 & T17;
//     M52 = M42 & T15;
//     M53 = M45 & T27;
//     M54 = M41 & T10;
//     M55 = M44 & T13;
//     M56 = M40 & T23;
//     M57 = M39 & T19;
//     M58 = M43 & T3;
//     M59 = M38 & T22;
//     M60 = M37 & T20;
//     M61 = M42 & T1;
//     M62 = M45 & T4;
//     M63 = M41 & T2;

//     // ----- L signals -----
//     L0  = M61 ^ M62;
//     L1  = M50 ^ M56;
//     L2  = M46 ^ M48;
//     L3  = M47 ^ M55;
//     L4  = M54 ^ M58;
//     L5  = M49 ^ M61;
//     L6  = M62 ^ L5;
//     L7  = M46 ^ L3;
//     L8  = M51 ^ M59;
//     L9  = M52 ^ M53;
//     L10 = M53 ^ L4;
//     L11 = M60 ^ L2;
//     L12 = M48 ^ M51;
//     L13 = M50 ^ L0;
//     L14 = M52 ^ M61;
//     L15 = M55 ^ L1;
//     L16 = M56 ^ L0;
//     L17 = M57 ^ L1;
//     L18 = M58 ^ L8;
//     L19 = M63 ^ L4;
//     L20 = L0 ^ L1;
//     L21 = L1 ^ L7;
//     L22 = L3 ^ L12;
//     L23 = L18 ^ L2;
//     L24 = L15 ^ L9;
//     L25 = L6 ^ L10;
//     L26 = L7 ^ L9;
//     L27 = L8 ^ L10;
//     L28 = L11 ^ L14;
//     L29 = L11 ^ L17;

//     // ----- Outputs -----
//     *Y0 = L6 ^ L24;
// 	bool temp1 = L16 ^ L26;
//     *Y1 = temp1 ^ 1;  // XNOR
// 	bool temp2 = L19 ^ L28;
//     *Y2 = temp2 ^ 1;  // XNOR
//     *Y3 = L6 ^ L21;
//     *Y4 = L20 ^ L22;
//     *Y5 = L25 ^ L29;
// 	bool temp3 = L13 ^ L27;
//     *Y6 = temp3 ^ 1;  // XNOR
// 	bool temp4 = L6 ^ L23;
//     *Y7 = temp4 ^ 1;   // XNOR

//     return 0;
// }

// bool main() {
	
// 	bool a, b, c, d, e, f, g, h;
// 	int out = sbox (1, 0, 0, 0, 0, 0, 0, 0, &a, &b, &c, &d, &e, &f, &g, &h);
// 	printf("x: 0; y: %d%d%d%d%d%d%d%d\n", a, b, c, d, e, f, g, h);						
//     return 0;
// }