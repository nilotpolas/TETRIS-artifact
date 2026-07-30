#include <stdio.h>
#include <stdbool.h> // Provides the _Bool type and true/false constants

void sbox(_Bool X0, _Bool X1, _Bool X2, _Bool X3, _Bool X4, _Bool X5, _Bool X6, _Bool X7, _Bool dec_1, _Bool *Y0, _Bool *Y1, _Bool *Y2, _Bool *Y3, _Bool *Y4, _Bool *Y5, _Bool *Y6, _Bool *Y7)
{
  _Bool T1;
  _Bool T2;
  _Bool T3;
  _Bool T4;
  _Bool T5;
  _Bool T6;
  _Bool T7;
  _Bool T8;
  _Bool T9;
  _Bool T10;
  _Bool T11;
  _Bool T12;
  _Bool T13;
  _Bool T14;
  _Bool T15;
  _Bool T16;
  _Bool T17;
  _Bool T18;
  _Bool T19;
  _Bool T20;
  _Bool T21;
  _Bool T22;
  _Bool T23;
  _Bool T24;
  _Bool T25;
  _Bool T26;
  _Bool T27;
  _Bool M1;
  _Bool M2;
  _Bool M3;
  _Bool M4;
  _Bool M5;
  _Bool M6;
  _Bool M7;
  _Bool M8;
  _Bool M9;
  _Bool M10;
  _Bool M11;
  _Bool M12;
  _Bool M13;
  _Bool M14;
  _Bool M15;
  _Bool M16;
  _Bool M17;
  _Bool M18;
  _Bool M19;
  _Bool M20;
  _Bool M21;
  _Bool M22;
  _Bool M23;
  _Bool M24;
  _Bool M25;
  _Bool M26;
  _Bool M27;
  _Bool M28;
  _Bool M29;
  _Bool M30;
  _Bool M31;
  _Bool M32;
  _Bool M33;
  _Bool M34;
  _Bool M35;
  _Bool M36;
  _Bool M37;
  _Bool M38;
  _Bool M39;
  _Bool M40;
  _Bool M41;
  _Bool M42;
  _Bool M43;
  _Bool M44;
  _Bool M45;
  _Bool M46;
  _Bool M47;
  _Bool M48;
  _Bool M49;
  _Bool M50;
  _Bool M51;
  _Bool M52;
  _Bool M53;
  _Bool M54;
  _Bool M55;
  _Bool M56;
  _Bool M57;
  _Bool M58;
  _Bool M59;
  _Bool M60;
  _Bool M61;
  _Bool M62;
  _Bool M63;
  _Bool L0;
  _Bool L1;
  _Bool L2;
  _Bool L3;
  _Bool L4;
  _Bool L5;
  _Bool L6;
  _Bool L7;
  _Bool L8;
  _Bool L9;
  _Bool L10;
  _Bool L11;
  _Bool L12;
  _Bool L13;
  _Bool L14;
  _Bool L15;
  _Bool L16;
  _Bool L17;
  _Bool L18;
  _Bool L19;
  _Bool L20;
  _Bool L21;
  _Bool L22;
  _Bool L23;
  _Bool L24;
  _Bool L25;
  _Bool L26;
  _Bool L27;
  _Bool L28;
  _Bool L29;
  T1 = X0 ^ X3;
  T2 = X0 ^ X5;
  T3 = X0 ^ X6;
  T4 = X3 ^ X5;
  T5 = X4 ^ X6;
  T6 = T1 ^ T5;
  T7 = X1 ^ X2;
  T8 = X7 ^ T6;
  T9 = X7 ^ T7;
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
  M1 = T13 & T6;
  M2 = T23 & T8;
  M3 = T14 ^ M1;
  M4 = T19 & X7;
  M5 = M4 ^ M1;
  M6 = T3 & T16;
  M7 = T22 & T9;
  M8 = T26 ^ M6;
  M9 = T20 & T17;
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
  L0 = M61 ^ M62;
  L1 = M50 ^ M56;
  L2 = M46 ^ M48;
  L3 = M47 ^ M55;
  L4 = M54 ^ M58;
  L5 = M49 ^ M61;
  L6 = M62 ^ L5;
  L7 = M46 ^ L3;
  L8 = M51 ^ M59;
  L9 = M52 ^ M53;
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
  *Y0 = L6 ^ L24;
  _Bool temp1;
  temp1 = L16 ^ L26;
  *Y1 = temp1 ^ dec_1;
  _Bool temp2;
  temp2 = L19 ^ L28;
  *Y2 = temp2 ^ dec_1;
  *Y3 = L6 ^ L21;
  *Y4 = L20 ^ L22;
  *Y5 = L25 ^ L29;
  _Bool temp3;
  temp3 = L13 ^ L27;
  *Y6 = temp3 ^ dec_1;
  _Bool temp4;
  temp4 = L6 ^ L23;
  *Y7 = temp4 ^ dec_1;
}


void print_bool_array(const _Bool arr[8]) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", arr[i]);
    }
}

int main() {
    // MODIFICATION: Set the filename to the latest version
    const char *filename = "sbox_simulation.csv";
    FILE *csv_file = fopen(filename, "r");

    if (csv_file == NULL) {
        perror("Error opening file");
        printf("Please ensure the file '%s' is in the same directory as this program.\n", filename);
        return 1;
    }

    // Read and discard the header line
    char header_buffer[200];
    if (fgets(header_buffer, sizeof(header_buffer), csv_file) == NULL) {
        fprintf(stderr, "Error: Could not read header from CSV file.\n");
        fclose(csv_file);
        return 1;
    }

    int line_count = 0;
    int errors_found = 0;
    const _Bool dec_1 = true;

    printf("--- Starting S-Box Verification ---\n");
    printf("Reading data from '%s'...\n\n", filename);

    // Arrays to hold the 16 values read from each line
    // We read into temporary `int` arrays for robust parsing with fscanf
    int x_vals[8], y_vals[8];

    // MODIFICATION: Updated loop to read 16 binary values per line
    while (fscanf(csv_file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                  &x_vals[7], &x_vals[6], &x_vals[5], &x_vals[4], &x_vals[3], &x_vals[2], &x_vals[1], &x_vals[0],
                  &y_vals[7], &y_vals[6], &y_vals[5], &y_vals[4], &y_vals[3], &y_vals[2], &y_vals[1], &y_vals[0]) == 16)
    {
        line_count++;

        _Bool X_from_csv[8];
        _Bool Y_expected_from_csv[8];
        
        // Convert the read integers into boolean arrays
        for (int j = 0; j < 8; j++) {
            X_from_csv[j] = (_Bool)x_vals[j];
            Y_expected_from_csv[j] = (_Bool)y_vals[j];
        }

        // Call the sbox function with the input bits from the CSV
        _Bool Y_calculated[8];
        sbox(X_from_csv[0], X_from_csv[1], X_from_csv[2], X_from_csv[3], X_from_csv[4], X_from_csv[5], X_from_csv[6], X_from_csv[7],
             dec_1,
             &Y_calculated[0], &Y_calculated[1], &Y_calculated[2], &Y_calculated[3], &Y_calculated[4], &Y_calculated[5], &Y_calculated[6], &Y_calculated[7]);

        // Compare the calculated output with the expected output, bit-by-bit
        bool is_mismatch = false;
        for (int j = 0; j < 8; j++) {
            if (Y_calculated[j] != Y_expected_from_csv[j]) {
                is_mismatch = true;
                break;
            }
        }
        
        // If a mismatch is found, print a detailed error report
        if (is_mismatch) {
            errors_found++;
            printf("❌ VERIFICATION FAILED on data row %d:\n", line_count);
            printf("   Input (x7..x0):        ");
            print_bool_array(X_from_csv);
            printf("\n");
            printf("   Expected Output (y7..y0): ");
            print_bool_array(Y_expected_from_csv);
            printf("\n");
            printf("   Calculated Output(y7..y0): ");
            print_bool_array(Y_calculated);
            printf("\n\n");
        }
    }

    fclose(csv_file);

    // Print a final summary of the verification process
    printf("\n--- Verification Complete ---\n");
    if (errors_found == 0) {
        if (line_count > 0) {
            printf("✅ Success! All %d entries in the CSV were verified correctly.\n", line_count);
        } else {
            printf("⚠️ Warning: No data was found in the CSV file to verify.\n");
        }
    } else {
        printf("❌ Finished with %d error(s). The S-box implementation does not match the CSV data.\n", errors_found);
    }

    return 0;
}