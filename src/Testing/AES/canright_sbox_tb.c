#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>

void sbox (bool X0, bool X1, bool X2, bool X3, bool X4, bool X5, bool X6, bool X7, bool *Y0, bool *Y1, bool *Y2, bool *Y3, bool *Y4, bool *Y5, bool *Y6, bool *Y7, bool dec_1) {
	

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









/* --- Test Bench --- */

unsigned char aes_sbox_ref[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

int main() {
    int errors = 0;
    for (int i = 0; i < 256; i++) {
        _Bool n0=(i>>0)&1, n1=(i>>1)&1, n2=(i>>2)&1, n3=(i>>3)&1,
              n4=(i>>4)&1, n5=(i>>5)&1, n6=(i>>6)&1, n7=(i>>7)&1;
        _Bool o0, o1, o2, o3, o4, o5, o6, o7;

        sbox(n0, n1, n2, n3, n4, n5, n6, n7, &o0, &o1, &o2, &o3, &o4, &o5, &o6, &o7, 1);

        unsigned char res = (o0<<0)|(o1<<1)|(o2<<2)|(o3<<3)|(o4<<4)|(o5<<5)|(o6<<6)|(o7<<7);

        if (res != aes_sbox_ref[i]) {
            printf("[FAIL] Input 0x%02X: Expected 0x%02X, Got 0x%02X\n", i, aes_sbox_ref[i], res);
            errors++;
        }
        else {
            printf("[PASS] Input 0x%02X: Output 0x%02X\n", i, res);
        }
    }
    if (errors == 0) printf("SUCCESS: All tests passed!\n");
    else printf("FAILURE: %d mismatches.\n", errors);
    return 0;
}