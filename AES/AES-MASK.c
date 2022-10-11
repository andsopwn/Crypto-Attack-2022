#include <stdio.h>
#include <stdlib.h>
#define MUL2(a) (a<<1)^(a&0x80?0x1b:0)
#define MUL3(a) MUL2(a)^a
#define MUL4(a) MUL2((MUL2(a)))
#define MUL8(a) MUL2((MUL2((MUL2(a)))))
#define MUL9(a) (MUL8(a))^(a)
#define MULB(a) (MUL8(a))^(MUL2(a))^(a)
#define MULD(a) (MUL8(a))^(MUL4(a))^(a)
#define MULE(a) (MUL8(a))^(MUL4(a))^(MUL2(a))
#define ptFN "plaintext.txt"
#define ctFN "ciphertext.txt"
#define OS 1
#define RotWord(x) ((x<<8) | (x>>24))
#define SubWord(x)  \
    ((u32)Sbox[(u8)(x >> 24)] << 24) \
    | ((u32)Sbox[(u8)((x >> 16) & 0xFF)] << 16) \
    | ((u32)Sbox[(u8)((x >> 8) & 0xFF)] << 8) \
    | ((u32)Sbox[(u8)(x & 0xff)]) \
// 0 : Windows, 1 : MAC, 2 : VM Linux
#if OS == 0
    #define DIR "C:\\Users\\louxsoen\\Documents\\부채널연구\\AES CPA\\"
    #define txtSize 33
#else
    #define DIR "/Users/louxsoen/Documents/Univ/부채널연구/파형정렬/"
    #define textSize 34 
#endif
typedef unsigned char u8;
typedef unsigned int u32;
u8      M[10];
u8      MSbox[256];
u8      Rcon[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };
u8      Sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 
    };

void prt(u8 *S)
{
    for(int i = 0 ; i < 16 ; i++)
    printf("%02X ", S[i]);
    puts("");
}

void Mask_RK_Update(unsigned char* out, unsigned char* in, int i)
{
   unsigned char tmp[4];

   tmp[0] = in[13] ^ M[7];
   tmp[1] = in[14] ^ M[8];
   tmp[2] = in[15] ^ M[9];
   tmp[3] = in[12] ^ M[6];

   tmp[0] = MSbox[tmp[0]] ^ Rcon[i];
   tmp[1] = MSbox[tmp[1]];
   tmp[2] = MSbox[tmp[2]];
   tmp[3] = MSbox[tmp[3]];

   // 첫번째 블록 
   out[0] = in[0] ^ tmp[0] ^ M[1];
   out[1] = in[1] ^ tmp[1] ^ M[1];
   out[2] = in[2] ^ tmp[2] ^ M[1];
   out[3] = in[3] ^ tmp[3] ^ M[1];
   // 두번째 블록
   out[4] = in[4] ^ M[0] ^ out[0] ^ M[6];
   out[5] = in[5] ^ M[0] ^ out[1] ^ M[7];
   out[6] = in[6] ^ M[0] ^ out[2] ^ M[8];
   out[7] = in[7] ^ M[0] ^ out[3] ^ M[9];
   // 세번째 블록
   out[8] = in[8] ^ M[0] ^ out[4] ^ M[6];
   out[9] = in[9] ^ M[0] ^ out[5] ^ M[7];
   out[10] = in[10] ^ M[0] ^ out[6] ^ M[8];
   out[11] = in[11] ^ M[0] ^ out[7] ^ M[9];
   // 네번째 블록
   out[12] = in[12] ^ M[6] ^ out[8] ^ M[0];
   out[13] = in[13] ^ M[7] ^ out[9] ^ M[0];
   out[14] = in[14] ^ M[8] ^ out[10] ^ M[0];
   out[15] = in[15] ^ M[9] ^ out[11] ^ M[0];
}
void RK_Update(unsigned char* out, unsigned char* in, int i)
{
   unsigned char tmp[4];

   unsigned Rcon[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };


   tmp[0] = in[13]; tmp[1] = in[14]; tmp[2] = in[15]; tmp[3] = in[12];

   tmp[0] = Sbox[tmp[0]] ^ Rcon[i];
   tmp[1] = Sbox[tmp[1]];
   tmp[2] = Sbox[tmp[2]];
   tmp[3] = Sbox[tmp[3]];

   out[0] = in[0] ^ tmp[0]; out[1] = in[1] ^ tmp[1]; out[2] = in[2] ^ tmp[2]; out[3] = in[3] ^ tmp[3];
   out[4] = in[4] ^ out[0]; out[5] = in[5] ^ out[1]; out[6] = in[6] ^ out[2]; out[7] = in[7] ^ out[3];
   out[8] = in[8] ^ out[4]; out[9] = in[9] ^ out[5]; out[10] = in[10] ^ out[6]; out[11] = in[11] ^ out[7];
   out[12] = in[12] ^ out[8]; out[13] = in[13] ^ out[9]; out[14] = in[14] ^ out[10]; out[15] = in[15] ^ out[11];
}

void Mask_RK_Update2(unsigned char* out, unsigned char* in)
{
   unsigned char tmp[4];

   tmp[0] = in[13] ^ M[7];
   tmp[1] = in[14] ^ M[8];
   tmp[2] = in[15] ^ M[9];
   tmp[3] = in[12] ^ M[6];

   tmp[0] = MSbox[tmp[0]] ^ Rcon[9];
   tmp[1] = MSbox[tmp[1]];
   tmp[2] = MSbox[tmp[2]];
   tmp[3] = MSbox[tmp[3]];

   // 첫번째 블록
   out[0] = in[0] ^ tmp[0];
   out[1] = in[1] ^ tmp[1];
   out[2] = in[2] ^ tmp[2];
   out[3] = in[3] ^ tmp[3];
   // 두번째 블록
   out[4] = in[4] ^ out[0];
   out[5] = in[5] ^ out[1];
   out[6] = in[6] ^ out[2];
   out[7] = in[7] ^ out[3];
   // 세번째 블록
   out[8] = in[8] ^ M[6] ^ out[4];
   out[9] = in[9] ^ M[7] ^ out[5];
   out[10] = in[10] ^ M[8] ^ out[6];
   out[11] = in[11] ^ M[9] ^ out[7];
   // 네번째 블록
   out[12] = in[12] ^ M[6] ^ out[8];
   out[13] = in[13] ^ M[7] ^ out[9];
   out[14] = in[14] ^ M[8] ^ out[10];
   out[15] = in[15] ^ M[9] ^ out[11];

   // 마스크 옳바르게 바꾸기 
   out[0] = out[0] ^ M[6] ^ M[0];
   out[1] = out[1] ^ M[7] ^ M[0];
   out[2] = out[2] ^ M[8] ^ M[0];
   out[3] = out[3] ^ M[9] ^ M[0];

   out[8] = out[8] ^ M[0];
   out[9] = out[9] ^ M[0];
   out[10] = out[10] ^ M[0];
   out[11] = out[11] ^ M[0];
}


void Mask_KeyExpansion(unsigned char* MK, unsigned char* RK)
{
   int i;

   for (i = 0; i < 16; i += 4)
   {
      RK[i] = MK[i] ^ M[6] ^ M[0];
      RK[i + 1] = MK[i + 1] ^ M[7] ^ M[0];
      RK[i + 2] = MK[i + 2] ^ M[8] ^ M[0];
      RK[i + 3] = MK[i + 3] ^ M[9] ^ M[0];
   }

   for (i = 0; i < 9; i++)
   {
      Mask_RK_Update(RK + 16, RK, i);
      RK += 16;
   }
}
void AddRoundKey(u8 *S, u8 *RK)
{
    S[0] ^= RK[0]; S[1] ^= RK[1]; S[2] ^= RK[2]; S[3] ^= RK[3];
    S[4] ^= RK[4]; S[5] ^= RK[5]; S[6] ^= RK[6]; S[7] ^= RK[7];
    S[8] ^= RK[8]; S[9] ^= RK[9]; S[10] ^= RK[10]; S[11] ^= RK[11];
    S[12] ^= RK[12]; S[13] ^= RK[13]; S[14] ^= RK[14]; S[15] ^= RK[15];
}
void SubBytes(u8 S[16])
{

    S[0] = MSbox[S[0] ^ M[0]]; S[1] = MSbox[S[1] ^ M[0]]; S[2] = MSbox[S[2] ^ M[0]]; S[3] = MSbox[S[3] ^ M[0]];
    S[4] = MSbox[S[4] ^ M[0]]; S[5] = MSbox[S[5] ^ M[0]]; S[6] = MSbox[S[6] ^ M[0]]; S[7] = MSbox[S[7] ^ M[0]];
    S[8] = MSbox[S[8] ^ M[0]]; S[9] = MSbox[S[9] ^ M[0]]; S[10] = MSbox[S[10] ^ M[0]]; S[11] = MSbox[S[11] ^ M[0]];
    S[12] = MSbox[S[12] ^ M[0]]; S[13] = MSbox[S[13] ^ M[0]]; S[14] = MSbox[S[14] ^ M[0]]; S[15] = MSbox[S[15] ^ M[0]];
}
void Shiftrows(u8 *S)
{
    u8 temp;
    temp = S[1]; S[1] = S[5]; S[5] = S[9]; S[9] = S[13]; S[13] = temp;
    temp = S[2]; S[2] = S[10]; S[10] = temp; temp = S[6]; S[6] = S[14]; S[14] = temp;
    temp = S[15]; S[15] = S[11]; S[11] = S[7]; S[7] = S[3]; S[3] = temp;
    for(int i = 0 ; i < 16 ; i++)
        S[i] ^= M[1];
}

void Submix(u8 *in)
{
   unsigned char tmp[4];

   tmp[0] = MUL2(in[0]) ^ MUL3(in[1]) ^ in[2] ^ in[3];
   tmp[1] = in[0] ^ MUL2(in[1]) ^ MUL3(in[2]) ^ in[3];
   tmp[2] = in[0] ^ in[1] ^ MUL2(in[2]) ^ MUL3(in[3]);
   tmp[3] = MUL3(in[0]) ^ in[1] ^ in[2] ^ MUL2(in[3]);

   in[0] = tmp[0]; in[1] = tmp[1]; in[2] = tmp[2]; in[3] = tmp[3];
}

void Mixcolumns(u8 *S)
{
   Submix(S);
   Submix(S + 4);
   Submix(S + 8);
   Submix(S + 12);
}

void KeyZone1(u8 *IN, u8 *OUT, u8 i)
{
    u8 temp[4];

    temp[0] = IN[13] ^ M[7]; // 수정
    temp[1] = IN[14] ^ M[8];
    temp[2] = IN[15] ^ M[9];
    temp[3] = IN[12] ^ M[6];
    
    temp[0] = MSbox[temp[0]] ^ Rcon[i];
    temp[1] = MSbox[temp[1]];
    temp[2] = MSbox[temp[2]];
    temp[3] = MSbox[temp[3]];
    
    OUT[0] = IN[0] ^ temp[0] ^ M[1];
    OUT[1] = IN[1] ^ temp[1] ^ M[1];
    OUT[2] = IN[2] ^ temp[2] ^ M[1];
    OUT[3] = IN[3] ^ temp[3] ^ M[1];
}

u32 u4byte_in(u8 *x)
{
    return (x[0] << 24) | (x[1] << 16) | (x[2] << 8) | x[3];
}

void u4byte_out(u8 *x, u32 y)
{
    x[0] = (y >> 24) & 0xFF;
    x[1] = (y >> 16) & 0xFF;
    x[2] = (y >> 8) & 0xFF;
    x[3] = y & 0xFF;
}

void AES_KeyWordToByte(u32 W[], u8 RK[])
{
    int i;
    for(i = 0 ; i < 44 ; i++)
    u4byte_out(RK + 4 * i, W[i]); 
}

u32 Rcons[10] = { 0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000 };

void RoundkeyGeneration128(u8 MK[], u8 RK[])
{
    u32 W[44];
    int i;
    u32 T;

    W[0] = u4byte_in(MK); // W[0] = MK[0] || MK[1] || MK[2] || MK[3]
    W[1] = u4byte_in(MK + 4);
    W[2] = u4byte_in(MK + 8);
    W[3] = u4byte_in(MK + 12);

    for(i = 0 ; i < 10 ; i++)
    {
        //T = G_func(W[4 * i + 3])
        T = W[4 * i + 3];
        T = RotWord(T);
        T = SubWord(T);
        T ^= Rcons[i];

        W[4 * i + 4] = W[4 * i] ^ T;
        W[4 * i + 5] = W[4 * i + 1] ^ W[4 * i + 4];
        W[4 * i + 6] = W[4 * i + 2] ^ W[4 * i + 5];
        W[4 * i + 7] = W[4 * i + 3] ^ W[4 * i + 6];
    }
    AES_KeyWordToByte(W, RK);
}

void AES_KeySchedule(u8 MK[], u8 RK[], int keysize)
{
    if(keysize == 128)    RoundkeyGeneration128(MK, RK);
    //if(keysize == 192)    RoundkeyGeneration192(MK, RK);
    //if(keysize == 256)    RoundkeyGeneration256(MK, RK);
}

void AddMasking(u8 *S, u8 *M)
{
    S[ 0] ^= M[6]; S[ 1] ^= M[7]; S[ 2] ^= M[8]; S[ 3] ^= M[9];
    S[ 4] ^= M[6]; S[ 5] ^= M[7]; S[ 6] ^= M[8]; S[ 8] ^= M[9];
    S[ 8] ^= M[6]; S[ 9] ^= M[7]; S[10] ^= M[8]; S[11] ^= M[9];
    S[12] ^= M[6]; S[13] ^= M[7]; S[14] ^= M[8]; S[15] ^= M[9];
}

int main()
{
    u8      PT[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    u8      MK[16] = { 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
    u8      CT[16] = { 0x00, };
    u8      RK[176] = { 0x00, };
    int     keysize = 128;
    int     Nr = keysize / 32 + 6;
    int     i;
    M[0] = rand();
    M[1] = rand();
    M[2] = rand();
    M[3] = rand();
    M[4] = rand();
    M[5] = rand();
    M[6] = MUL2(M[2]) ^ MUL3(M[3]) ^ M[4] ^ M[5];
    M[7] = M[2] ^ MUL2(M[3]) ^ MUL3(M[4]) ^ M[5];
    M[8] = M[2] ^ M[3] ^ MUL2(M[4]) ^ MUL3(M[5]);
    M[9] = MUL3(M[2]) ^ M[3] ^ M[4] ^ MUL2(M[5]);
    // MaskedSBOX[i ^ M0] = SBOX[i] ^ M1
    for(int i = 0 ; i < 256 ; i++) 
        MSbox[i ^ M[0]] = Sbox[i] ^ M[1];

    AES_KeySchedule(MK, RK, keysize);
    
    for(i = 0 ; i < 16 ; i++)
        CT[i] = PT[i];
    AddMasking(CT, M);
    AddRoundKey(CT, RK);
    AddMasking(CT, M);
    for(int i = 0 ; i < Nr - 1 ; i++)
    {  
        SubBytes(CT);
        Shiftrows(CT);
        Mixcolumns(CT);
        AddRoundKey(CT, RK + 16 * (i + 1));
    }
    SubBytes(CT);
    Shiftrows(CT);
    AddRoundKey(CT, RK + 16 * 10); 
    prt(CT);
}