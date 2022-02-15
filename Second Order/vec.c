#include <stdio.h>
typedef unsigned char u8;
#define MUL2(a) (a<<1)^(a&0x80?0x1b:0)
#define MUL3(a) MUL2(a)^a

int main() {
    u8 m2 = 0x4b;
    u8 m3 = 0x1a;
    u8 m4 = 0x85;
    u8 m5 = 0x91;
    u8 m6 = MUL2(m3) ^ MUL3(m3) ^ m4 ^ m5;
    u8 m7 = m2 ^ MUL2(m3) ^ MUL3(m4) ^ m5;
    u8 m8 = m2 ^ m3 ^ MUL2(m4) ^ MUL3(m5);
    u8 m9 = MUL3(m2) ^ m3 ^ m4 ^ MUL2(m5);

    printf("%02X %02X %02X %02X\n", m6, m7, m8, m9);
}