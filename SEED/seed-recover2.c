#include <stdio.h>
#include "seed.h"

int main() {    
    u32 A, B, C, D, A_, B_;
    u32 M1, M2, M3, M4;
    u32 TEMP;
    u8 TM;
    A  = 0x00010203;
    B  = 0x04050607;
    C  = 0x08090a0b;
    D  = 0x0c0d0e0f;
    A_ = 0x07000102;
    B_ = 0x03040506;

    M1 = A  + C;
    M2 = A_ + C;
    M3 = B  - D;
    M4 = B_ - D;
    TM = (M2 + M4) >> 24;
    printf("%08X\n", (M1 + M4) & 0x00ffffff);
    printf("%08X\n", (M2 + M3) & 0x00ffffff);
    printf("%08X\n",  B_ & 0x00ffffff);
    printf("%08X\n", (B & 0xffffff00) >> 8);
}
    //printf("%08X\n", (A + B) + B - (A_ + B_));