#include <stdio.h>
#include "seed.h"

int main() {
    
    u32 a = 0x8e00fe84;
    u32 b = 0xc6085430;
    u32 sm;
    printf("%08X\n", a + b);

    u32 c = 0xfe + 0x54;
    printf("%08X\n", c);
    
}
// 0x10