#include <stdio.h>
typedef unsigned char u8;
int main() {
    printf("%02X ", 0xc7 ^ 0x7c);
    printf("%02X ", 0x8f ^ 0x37);
    printf("%02X ", 0xff ^ 0xa7);
}