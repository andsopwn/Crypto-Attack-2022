#include <stdio.h>
#include "seed.h"

int main() {
    u32 KL = 0xC119F584;
    u32 A, B, C, D;
    u32 AP, BP;
    u32 X, Y, Z, W;
    u32 TEMP;
    A = 0x00010203;
    B = 0x04050607;
    C = 0x08090a0b;
    D = 0x0c0d0e0f;

    AP = (A >> 8) ^ (B << 24); // 07000102
    BP = (B >> 8) ^ (A << 24); // 03040506

    X = A + C;      // A + C
    Y = B - D;      // B - D
    Z = AP + C;     // A' + C
    W = BP - D;     // B' - D

    printf("%08X\n", Z - X);

}