#include <stdio.h>
typedef unsigned char u8;
typedef unsigned int u32;
int main() {
    //printf("%02X ", 0x7c8f8c7e ^ 0xc737a22c);
    u32 a = 0x08090a0b;
    u32 b = 0xbbb82e52;
    printf("%08X = ", (a + b) & 0xffffffff);

    u8 x[4] = { 0x08, 0x09, 0x0a, 0x0b };
    u8 y[4] = { 0xbb, 0xb8, 0x2e, 0x52 };

    for(int i = 0 ; i < 4; i++) {
        printf("%02X", (x[i] + y[i]) & 0xff);
    }
    puts("\n");
    a = 0x00000090;
    b = 0x00000070;
    u8 c = (a + b) & 0xff;
    printf("%02X\n", c);
    printf("%02X\n", (c - b) & 0xff);
} 