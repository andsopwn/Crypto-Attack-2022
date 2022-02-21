#include <stdio.h>

int main() {
    
    int a = 0x55;
    int b = 0x99;
    int c = a & b;
    printf("%02x", c | (0xff - b));
}
// 0x10