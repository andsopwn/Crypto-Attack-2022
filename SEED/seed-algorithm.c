#include "seed-algorithm.h"
#define G_Function(X) (SS0[(X) & 0xff] ^ SS1[(X >> 8) & 0xff] ^ SS2[(X >> 16) & 0xff] ^ SS3[(X >> 24) & 0xff])

void KeySC(u8 *MK, u32 *RK) {
    u32 K[4];                                                                   // K = L0(A) || L1(B) || R0(C) || R1(D)
    u32 KL[16], KR[16];
    u32 TEMP;
    
    K[0] = (((MK[0] << 24) ^ (MK[1] << 16)) ^ (MK[2] << 8)) ^ MK[3];
    K[1] = (((MK[4] << 24) ^ (MK[5] << 16)) ^ (MK[6] << 8)) ^ MK[7];
    K[2] = (((MK[8] << 24) ^ (MK[9] << 16)) ^ (MK[10] << 8)) ^ MK[11];
    K[3] = (((MK[12] << 24) ^ (MK[13] << 16)) ^ (MK[14] << 8)) ^ MK[15];

    for(int i = 1 ; i <= 16 ; i++) {
        KL[i] = (K[0] + K[2]) - KC[i - 1];
        KR[i] = (K[1] - K[3]) + KC[i - 1];

        KL[i] = G_Function(KL[i]);
        KR[i] = G_Function(KR[i]);

        if(i % 2 == 1) {
            TEMP = K[0];
            K[0] = (K[0] >> 8) ^ (K[1] << 24);
            K[1] = (K[1] >> 8) ^ (TEMP << 24); 
        } 
        else {
            TEMP = K[2];
            K[2] = (K[2] << 8) ^ (K[3] >> 24);
            K[3] = (K[3] << 8) ^ (TEMP >> 24);
        }
        
        RK[(i - 1) * 2] = KL[i];
        RK[(i - 1) * 2 + 1] = KR[i];
        //printf("%02d KL : %08X, KR : %08X\n", i, KL[i], KR[i]);
    }
}

u32 ZIP(u8 *IN) {
    return (IN[0] << 24) | (IN[1] << 16) | (IN[2] << 8) | IN[3];
}

void Encryption(u8 *PT, u32 *RK, u8 *CT) {
    u32 L0 = ZIP(PT);
    u32 L1 = ZIP(PT + 4);
    u32 R0 = ZIP(PT + 8);
    u32 R1 = ZIP(PT + 12);
    u32 C, D;
    u32 T0, T1;
    //printf("         L0       L1       R0       R1\n01R : %08lX %08lX %08lX %08lX\n", L0, L1, R0, R1);
    for(int i = 0 ; i < 15 ; i++) {
        T0 = R0;
        T1 = R1;
        C = R0 ^ RK[i * 2];
        D = R1 ^ RK[i * 2 + 1];
        D ^= C;
        D = G_Function(D);
        C = (C + D) & 0xffffffff;
        C = G_Function(C);
        D = (C + D) & 0xffffffff;
        D = G_Function(D);
        C = (C + D) & 0xffffffff;

        R0 = L0 ^ C;
        R1 = L1 ^ D;

        L0 = T0;
        L1 = T1;
        //printf("%02dR : %08lX %08lX %08lX %08lX\n", i+2, L0, L1, R0, R1);
    }
    
    
}

int main()
{
    u8 MK[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    u8 PT[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    u8 CT[16] = { 0x00, };
    u32 RK[32] = { 0x00, };
    //u8 CT[16] = { 0x5e, 0xba, 0xc6, 0xe0, 0x05, 0x4e, 0x16, 0x68, 0x19, 0xaf, 0xf1, 0xcc, 0x6d, 0x34, 0x6c, 0xdb };
    KeySC(MK, RK);
    Encryption(PT, RK, CT);

}