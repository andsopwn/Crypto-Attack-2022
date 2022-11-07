#include <stdio.h>
typedef unsigned char u8;
typedef unsigned int u32;

u8 GenSbox(u8 a)
{
    u8 r, temp;
    temp = inv(a);
    r = 0;
    if (temp & 0x01)    r ^= 0x1f;
    if (temp & 0x02)    r ^= 0x3e;
    if (temp & 0x04)    r ^= 0x7c;
    if (temp & 0x08)    r ^= 0xf8;
    if (temp & 0x10)    r ^= 0xf1;
    if (temp & 0x20)    r ^= 0xe3;
    if (temp & 0x40)    r ^= 0xc7;
    if (temp & 0x80)    r ^= 0x8f;
    r ^= 0x63;
    return r;
}

int main() {
    u8 a;
    u8 b;
    u32 i;
    
    for(i = 0; i < 256; i++)
    {
        printf("0x%02x, ", GenSbox((u8) i));
        if (i % 16 == 15) printf("\n");
        // 16자리마다 줄바꿈
    }
    return 0;
}