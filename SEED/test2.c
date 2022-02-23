#include <stdio.h>
#include "seed.h"

int main() {
    u8 P0, P1, P2, P3;
    u32 L0, L1, R0, R1, CC, DD;
    u32 LK = 0xff276cdb;
    u32 RK = 0xa7ca684a;
    u8 PT[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    P0 = PT[ 8] ^ PT[12];
    P1 = PT[ 9] ^ PT[13];  
    P2 = PT[10] ^ PT[14];  
    P3 = PT[11] ^ PT[15];  

    DD = (P0 << 24) ^ (P1 << 16) ^ (P2 << 8) ^ P3 ^ RK ^ LK;
    DD = G_Function(DD);
    
    CC = (PT[8] << 24) ^ (PT[9] << 16) ^ (PT[10] << 8) ^ PT[11] ^ LK;

    CC = (u32)(CC + DD);
    CC = G_Function(CC);

    DD = (u32)(CC + DD);
    DD = G_Function(DD);                
    CC = (u32)(CC + DD);
        // F FUNCTION EXIT

    L0 = (PT[8] << 24) ^ (PT[9] << 16) ^ (PT[10] << 8) ^ PT[11];
    L1 = (PT[12] << 24) ^ (PT[13] << 16) ^ (PT[14] << 8) ^ PT[15];

    

    P0 = PT[0] ^ (u8)(CC >> 24);
    P1 = PT[1] ^ (u8)(CC >> 16);
    P2 = PT[2] ^ (u8)(CC >>  8);
    P3 = PT[3] ^ (u8)(CC);
    R0 = (P0 << 24) ^ (P1 << 16) ^ (P2 << 8) ^ P3;

    P0 = PT[4] ^ (u8)(DD >> 24);
    P1 = PT[5] ^ (u8)(DD >> 16);
    P2 = PT[6] ^ (u8)(DD >>  8);
    P3 = PT[7] ^ (u8)(DD);
    R1 = (P0 << 24) ^ (P1 << 16) ^ (P2 << 8) ^ P3;

    P0 = (u8)(R0 >> 24) ^ (u8)(R1 >> 24);
    P1 = (u8)(R0 >> 16) ^ (u8)(R1 >> 16);
    P2 = (u8)(R0 >>  8) ^ (u8)(R1 >>  8);
    P3 = (u8)(R0) ^ (u8)(R1);
    


}