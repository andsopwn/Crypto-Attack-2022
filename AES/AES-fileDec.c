#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "aes.h"

#define DEBUG 0

void u4byte_out(u8* x, u32 y) {
    x[0] = (y >> 24) & 0xff;
    x[1] = (y >> 16) & 0xff;
    x[2] = (y >> 8) & 0xff;
    x[3] = y & 0xff;
}

u32 u4byte_in(u8* x) { 
return (x[0] << 24) | (x[1] << 16) | (x[2] << 8) | x[3]; // x[0]||x[1]||x[2]||x[3]
}

void AES_ENC_Optimization(u8 *PT, u8 *CT, u32 *W, int keysize)
{
    int Nr = keysize / 32 + 6;
    u32 S0, S1, S2, S3, T0, T1, T2, T3;

    //0 round
    S0 = u4byte_in(PT) ^ W[0];
    S1 = u4byte_in(PT + 4) ^ W[1];
    S2 = u4byte_in(PT + 8) ^ W[2];
    S3 = u4byte_in(PT + 12) ^ W[3];

    //1 round
    T0 = Te0[S0 >> 24] ^ Te1[(S1 >> 16) & 0xff] ^ Te2[(S2 >> 8) & 0xff] ^ Te3[S3 & 0xff] ^ W[4];
    T1 = Te0[S1 >> 24] ^ Te1[(S2 >> 16) & 0xff] ^ Te2[(S3 >> 8) & 0xff] ^ Te3[S0 & 0xff] ^ W[5];
    T2 = Te0[S2 >> 24] ^ Te1[(S3 >> 16) & 0xff] ^ Te2[(S0 >> 8) & 0xff] ^ Te3[S1 & 0xff] ^ W[6];
    T3 = Te0[S3 >> 24] ^ Te1[(S0 >> 16) & 0xff] ^ Te2[(S1 >> 8) & 0xff] ^ Te3[S2 & 0xff] ^ W[7];

    //2 round
    S0 = Te0[T0 >> 24] ^ Te1[(T1 >> 16) & 0xff] ^ Te2[(T2 >> 8) & 0xff] ^ Te3[T3 & 0xff] ^ W[8];
    S1 = Te0[T1 >> 24] ^ Te1[(T2 >> 16) & 0xff] ^ Te2[(T3 >> 8) & 0xff] ^ Te3[T0 & 0xff] ^ W[9];
    S2 = Te0[T2 >> 24] ^ Te1[(T3 >> 16) & 0xff] ^ Te2[(T0 >> 8) & 0xff] ^ Te3[T1 & 0xff] ^ W[10];
    S3 = Te0[T3 >> 24] ^ Te1[(T0 >> 16) & 0xff] ^ Te2[(T1 >> 8) & 0xff] ^ Te3[T2 & 0xff] ^ W[11];

    //3 round
    T0 = Te0[S0 >> 24] ^ Te1[(S1 >> 16) & 0xff] ^ Te2[(S2 >> 8) & 0xff] ^ Te3[S3 & 0xff] ^ W[12];
    T1 = Te0[S1 >> 24] ^ Te1[(S2 >> 16) & 0xff] ^ Te2[(S3 >> 8) & 0xff] ^ Te3[S0 & 0xff] ^ W[13];
    T2 = Te0[S2 >> 24] ^ Te1[(S3 >> 16) & 0xff] ^ Te2[(S0 >> 8) & 0xff] ^ Te3[S1 & 0xff] ^ W[14];
    T3 = Te0[S3 >> 24] ^ Te1[(S0 >> 16) & 0xff] ^ Te2[(S1 >> 8) & 0xff] ^ Te3[S2 & 0xff] ^ W[15];

    //4 round
    S0 = Te0[T0 >> 24] ^ Te1[(T1 >> 16) & 0xff] ^ Te2[(T2 >> 8) & 0xff] ^ Te3[T3 & 0xff] ^ W[16];
    S1 = Te0[T1 >> 24] ^ Te1[(T2 >> 16) & 0xff] ^ Te2[(T3 >> 8) & 0xff] ^ Te3[T0 & 0xff] ^ W[17];
    S2 = Te0[T2 >> 24] ^ Te1[(T3 >> 16) & 0xff] ^ Te2[(T0 >> 8) & 0xff] ^ Te3[T1 & 0xff] ^ W[18];
    S3 = Te0[T3 >> 24] ^ Te1[(T0 >> 16) & 0xff] ^ Te2[(T1 >> 8) & 0xff] ^ Te3[T2 & 0xff] ^ W[19];

    //5 round
    T0 = Te0[S0 >> 24] ^ Te1[(S1 >> 16) & 0xff] ^ Te2[(S2 >> 8) & 0xff] ^ Te3[S3 & 0xff] ^ W[20];
    T1 = Te0[S1 >> 24] ^ Te1[(S2 >> 16) & 0xff] ^ Te2[(S3 >> 8) & 0xff] ^ Te3[S0 & 0xff] ^ W[21];
    T2 = Te0[S2 >> 24] ^ Te1[(S3 >> 16) & 0xff] ^ Te2[(S0 >> 8) & 0xff] ^ Te3[S1 & 0xff] ^ W[22];
    T3 = Te0[S3 >> 24] ^ Te1[(S0 >> 16) & 0xff] ^ Te2[(S1 >> 8) & 0xff] ^ Te3[S2 & 0xff] ^ W[23];

    //6 round
    S0 = Te0[T0 >> 24] ^ Te1[(T1 >> 16) & 0xff] ^ Te2[(T2 >> 8) & 0xff] ^ Te3[T3 & 0xff] ^ W[24];
    S1 = Te0[T1 >> 24] ^ Te1[(T2 >> 16) & 0xff] ^ Te2[(T3 >> 8) & 0xff] ^ Te3[T0 & 0xff] ^ W[25];
    S2 = Te0[T2 >> 24] ^ Te1[(T3 >> 16) & 0xff] ^ Te2[(T0 >> 8) & 0xff] ^ Te3[T1 & 0xff] ^ W[26];
    S3 = Te0[T3 >> 24] ^ Te1[(T0 >> 16) & 0xff] ^ Te2[(T1 >> 8) & 0xff] ^ Te3[T2 & 0xff] ^ W[27];

    //7 round
    T0 = Te0[S0 >> 24] ^ Te1[(S1 >> 16) & 0xff] ^ Te2[(S2 >> 8) & 0xff] ^ Te3[S3 & 0xff] ^ W[28];
    T1 = Te0[S1 >> 24] ^ Te1[(S2 >> 16) & 0xff] ^ Te2[(S3 >> 8) & 0xff] ^ Te3[S0 & 0xff] ^ W[29];
    T2 = Te0[S2 >> 24] ^ Te1[(S3 >> 16) & 0xff] ^ Te2[(S0 >> 8) & 0xff] ^ Te3[S1 & 0xff] ^ W[30];
    T3 = Te0[S3 >> 24] ^ Te1[(S0 >> 16) & 0xff] ^ Te2[(S1 >> 8) & 0xff] ^ Te3[S2 & 0xff] ^ W[31];

    //8 round
    S0 = Te0[T0 >> 24] ^ Te1[(T1 >> 16) & 0xff] ^ Te2[(T2 >> 8) & 0xff] ^ Te3[T3 & 0xff] ^ W[32];
    S1 = Te0[T1 >> 24] ^ Te1[(T2 >> 16) & 0xff] ^ Te2[(T3 >> 8) & 0xff] ^ Te3[T0 & 0xff] ^ W[33];
    S2 = Te0[T2 >> 24] ^ Te1[(T3 >> 16) & 0xff] ^ Te2[(T0 >> 8) & 0xff] ^ Te3[T1 & 0xff] ^ W[34];
    S3 = Te0[T3 >> 24] ^ Te1[(T0 >> 16) & 0xff] ^ Te2[(T1 >> 8) & 0xff] ^ Te3[T2 & 0xff] ^ W[35];

    if (Nr == 10)
    {
        //9 round
        T0 = Te0[S0 >> 24] ^ Te1[(S1 >> 16) & 0xff] ^ Te2[(S2 >> 8) & 0xff] ^ Te3[S3 & 0xff] ^ W[36];
        T1 = Te0[S1 >> 24] ^ Te1[(S2 >> 16) & 0xff] ^ Te2[(S3 >> 8) & 0xff] ^ Te3[S0 & 0xff] ^ W[37];
        T2 = Te0[S2 >> 24] ^ Te1[(S3 >> 16) & 0xff] ^ Te2[(S0 >> 8) & 0xff] ^ Te3[S1 & 0xff] ^ W[38];
        T3 = Te0[S3 >> 24] ^ Te1[(S0 >> 16) & 0xff] ^ Te2[(S1 >> 8) & 0xff] ^ Te3[S2 & 0xff] ^ W[39];

        //10 round
        S0 = (Te2[(T0 >> 24)] & 0xff000000) ^ (Te3[(T1 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(T2 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[T3 & 0xff] & 0x000000ff) ^ W[40];
        S1 = (Te2[(T1 >> 24)] & 0xff000000) ^ (Te3[(T2 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(T3 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[T0 & 0xff] & 0x000000ff) ^ W[41];
        S2 = (Te2[(T2 >> 24)] & 0xff000000) ^ (Te3[(T3 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(T0 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[T1 & 0xff] & 0x000000ff) ^ W[42];
        S3 = (Te2[(T3 >> 24)] & 0xff000000) ^ (Te3[(T0 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(T1 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[T2 & 0xff] & 0x000000ff) ^ W[43];
    }
    else if (Nr == 12) {
        //9 round
        T0 = Te0[S0 >> 24] ^ Te1[(S1 >> 16) & 0xff] ^ Te2[(S2 >> 8) & 0xff] ^ Te3[S3 & 0xff] ^ W[36];
        T1 = Te0[S1 >> 24] ^ Te1[(S2 >> 16) & 0xff] ^ Te2[(S3 >> 8) & 0xff] ^ Te3[S0 & 0xff] ^ W[37];
        T2 = Te0[S2 >> 24] ^ Te1[(S3 >> 16) & 0xff] ^ Te2[(S0 >> 8) & 0xff] ^ Te3[S1 & 0xff] ^ W[38];
        T3 = Te0[S3 >> 24] ^ Te1[(S0 >> 16) & 0xff] ^ Te2[(S1 >> 8) & 0xff] ^ Te3[S2 & 0xff] ^ W[39];

        //10 round
        S0 = Te0[T0 >> 24] ^ Te1[(T1 >> 16) & 0xff] ^ Te2[(T2 >> 8) & 0xff] ^ Te3[T3 & 0xff] ^ W[40];
        S1 = Te0[T1 >> 24] ^ Te1[(T2 >> 16) & 0xff] ^ Te2[(T3 >> 8) & 0xff] ^ Te3[T0 & 0xff] ^ W[41];
        S2 = Te0[T2 >> 24] ^ Te1[(T3 >> 16) & 0xff] ^ Te2[(T0 >> 8) & 0xff] ^ Te3[T1 & 0xff] ^ W[42];
        S3 = Te0[T3 >> 24] ^ Te1[(T0 >> 16) & 0xff] ^ Te2[(T1 >> 8) & 0xff] ^ Te3[T2 & 0xff] ^ W[43];

        //11 round
        T0 = Te0[S0 >> 24] ^ Te1[(S1 >> 16) & 0xff] ^ Te2[(S2 >> 8) & 0xff] ^ Te3[S3 & 0xff] ^ W[44];
        T1 = Te0[S1 >> 24] ^ Te1[(S2 >> 16) & 0xff] ^ Te2[(S3 >> 8) & 0xff] ^ Te3[S0 & 0xff] ^ W[45];
        T2 = Te0[S2 >> 24] ^ Te1[(S3 >> 16) & 0xff] ^ Te2[(S0 >> 8) & 0xff] ^ Te3[S1 & 0xff] ^ W[46];
        T3 = Te0[S3 >> 24] ^ Te1[(S0 >> 16) & 0xff] ^ Te2[(S1 >> 8) & 0xff] ^ Te3[S2 & 0xff] ^ W[47];

        //12 round
        S0 = (Te2[(T0 >> 24)] & 0xff000000) ^ (Te3[(T1 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(T2 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[T3 & 0xff] & 0x000000ff) ^ W[48];
        S1 = (Te2[(T1 >> 24)] & 0xff000000) ^ (Te3[(T2 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(T3 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[T0 & 0xff] & 0x000000ff) ^ W[49];
        S2 = (Te2[(T2 >> 24)] & 0xff000000) ^ (Te3[(T3 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(T0 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[T1 & 0xff] & 0x000000ff) ^ W[50];
        S3 = (Te2[(T3 >> 24)] & 0xff000000) ^ (Te3[(T0 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(T1 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[T2 & 0xff] & 0x000000ff) ^ W[51];
    }
    else if (Nr == 12) {
        //9 round
        T0 = Te0[S0 >> 24] ^ Te1[(S1 >> 16) & 0xff] ^ Te2[(S2 >> 8) & 0xff] ^ Te3[S3 & 0xff] ^ W[36];
        T1 = Te0[S1 >> 24] ^ Te1[(S2 >> 16) & 0xff] ^ Te2[(S3 >> 8) & 0xff] ^ Te3[S0 & 0xff] ^ W[37];
        T2 = Te0[S2 >> 24] ^ Te1[(S3 >> 16) & 0xff] ^ Te2[(S0 >> 8) & 0xff] ^ Te3[S1 & 0xff] ^ W[38];
        T3 = Te0[S3 >> 24] ^ Te1[(S0 >> 16) & 0xff] ^ Te2[(S1 >> 8) & 0xff] ^ Te3[S2 & 0xff] ^ W[39];

        //10 round
        S0 = Te0[T0 >> 24] ^ Te1[(T1 >> 16) & 0xff] ^ Te2[(T2 >> 8) & 0xff] ^ Te3[T3 & 0xff] ^ W[40];
        S1 = Te0[T1 >> 24] ^ Te1[(T2 >> 16) & 0xff] ^ Te2[(T3 >> 8) & 0xff] ^ Te3[T0 & 0xff] ^ W[41];
        S2 = Te0[T2 >> 24] ^ Te1[(T3 >> 16) & 0xff] ^ Te2[(T0 >> 8) & 0xff] ^ Te3[T1 & 0xff] ^ W[42];
        S3 = Te0[T3 >> 24] ^ Te1[(T0 >> 16) & 0xff] ^ Te2[(T1 >> 8) & 0xff] ^ Te3[T2 & 0xff] ^ W[43];

        //11 round
        T0 = Te0[S0 >> 24] ^ Te1[(S1 >> 16) & 0xff] ^ Te2[(S2 >> 8) & 0xff] ^ Te3[S3 & 0xff] ^ W[44];
        T1 = Te0[S1 >> 24] ^ Te1[(S2 >> 16) & 0xff] ^ Te2[(S3 >> 8) & 0xff] ^ Te3[S0 & 0xff] ^ W[45];
        T2 = Te0[S2 >> 24] ^ Te1[(S3 >> 16) & 0xff] ^ Te2[(S0 >> 8) & 0xff] ^ Te3[S1 & 0xff] ^ W[46];
        T3 = Te0[S3 >> 24] ^ Te1[(S0 >> 16) & 0xff] ^ Te2[(S1 >> 8) & 0xff] ^ Te3[S2 & 0xff] ^ W[47];

        //12 round
        S0 = Te0[T0 >> 24] ^ Te1[(T1 >> 16) & 0xff] ^ Te2[(T2 >> 8) & 0xff] ^ Te3[T3 & 0xff] ^ W[48];
        S1 = Te0[T1 >> 24] ^ Te1[(T2 >> 16) & 0xff] ^ Te2[(T3 >> 8) & 0xff] ^ Te3[T0 & 0xff] ^ W[49];
        S2 = Te0[T2 >> 24] ^ Te1[(T3 >> 16) & 0xff] ^ Te2[(T0 >> 8) & 0xff] ^ Te3[T1 & 0xff] ^ W[50];
        S3 = Te0[T3 >> 24] ^ Te1[(T0 >> 16) & 0xff] ^ Te2[(T1 >> 8) & 0xff] ^ Te3[T2 & 0xff] ^ W[51];

        //13 round
        T0 = Te0[S0 >> 24] ^ Te1[(S1 >> 16) & 0xff] ^ Te2[(S2 >> 8) & 0xff] ^ Te3[S3 & 0xff] ^ W[52];
        T1 = Te0[S1 >> 24] ^ Te1[(S2 >> 16) & 0xff] ^ Te2[(S3 >> 8) & 0xff] ^ Te3[S0 & 0xff] ^ W[53];
        T2 = Te0[S2 >> 24] ^ Te1[(S3 >> 16) & 0xff] ^ Te2[(S0 >> 8) & 0xff] ^ Te3[S1 & 0xff] ^ W[54];
        T3 = Te0[S3 >> 24] ^ Te1[(S0 >> 16) & 0xff] ^ Te2[(S1 >> 8) & 0xff] ^ Te3[S2 & 0xff] ^ W[55];

        //14 round
        S0 = (Te2[(T0 >> 24)] & 0xff000000) ^ (Te3[(T1 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(T2 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[T3 & 0xff] & 0x000000ff) ^ W[56];
        S1 = (Te2[(T1 >> 24)] & 0xff000000) ^ (Te3[(T2 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(T3 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[T0 & 0xff] & 0x000000ff) ^ W[57];
        S2 = (Te2[(T2 >> 24)] & 0xff000000) ^ (Te3[(T3 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(T0 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[T1 & 0xff] & 0x000000ff) ^ W[58];
        S3 = (Te2[(T3 >> 24)] & 0xff000000) ^ (Te3[(T0 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(T1 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[T2 & 0xff] & 0x000000ff) ^ W[59];
    }

    u4byte_out(CT, S0);
    u4byte_out(CT + 4, S1);
    u4byte_out(CT + 8, S2);
    u4byte_out(CT + 12, S3);
}

void AES_DEC_Optimization(u8 *PT, u8 *CT, u32 *W, int keysize) {
   u32      S0, S1, S2, S3, T0, T1, T2, T3;

   S0 = u4byte_in(CT) ^ W[40];
   S1 = u4byte_in(CT + 4) ^ W[41];
   S2 = u4byte_in(CT + 8) ^ W[42];
   S3 = u4byte_in(CT + 12) ^ W[43];

   // Round 10
   T0 = Td0[S0 >> 24] ^ Td3[S1 & 0xff] ^ Td2[(S2 >> 8) & 0xff] ^ Td1[(S3 >> 16) & 0xff] ^ W[36];
   T1 = Td0[S1 >> 24] ^ Td3[S2 & 0xff] ^ Td2[(S3 >> 8) & 0xff] ^ Td1[(S0 >> 16) & 0xff] ^ W[37];
   T2 = Td0[S2 >> 24] ^ Td3[S3 & 0xff] ^ Td2[(S0 >> 8) & 0xff] ^ Td1[(S1 >> 16) & 0xff] ^ W[38];
   T3 = Td0[S3 >> 24] ^ Td3[S0 & 0xff] ^ Td2[(S1 >> 8) & 0xff] ^ Td1[(S2 >> 16) & 0xff] ^ W[39];

   // Round 9
   S0 = Td0[T0 >> 24] ^ Td3[T1 & 0xff] ^ Td2[(T2 >> 8) & 0xff] ^ Td1[(T3 >> 16) & 0xff] ^ W[32];
   S1 = Td0[T1 >> 24] ^ Td3[T2 & 0xff] ^ Td2[(T3 >> 8) & 0xff] ^ Td1[(T0 >> 16) & 0xff] ^ W[33];
   S2 = Td0[T2 >> 24] ^ Td3[T3 & 0xff] ^ Td2[(T0 >> 8) & 0xff] ^ Td1[(T1 >> 16) & 0xff] ^ W[34];
   S3 = Td0[T3 >> 24] ^ Td3[T0 & 0xff] ^ Td2[(T1 >> 8) & 0xff] ^ Td1[(T2 >> 16) & 0xff] ^ W[35];

   // Round 8
   T0 = Td0[S0 >> 24] ^ Td3[S1 & 0xff] ^ Td2[(S2 >> 8) & 0xff] ^ Td1[(S3 >> 16) & 0xff] ^ W[28];
   T1 = Td0[S1 >> 24] ^ Td3[S2 & 0xff] ^ Td2[(S3 >> 8) & 0xff] ^ Td1[(S0 >> 16) & 0xff] ^ W[29];
   T2 = Td0[S2 >> 24] ^ Td3[S3 & 0xff] ^ Td2[(S0 >> 8) & 0xff] ^ Td1[(S1 >> 16) & 0xff] ^ W[30];
   T3 = Td0[S3 >> 24] ^ Td3[S0 & 0xff] ^ Td2[(S1 >> 8) & 0xff] ^ Td1[(S2 >> 16) & 0xff] ^ W[31];

   // Round 7
   S0 = Td0[T0 >> 24] ^ Td3[T1 & 0xff] ^ Td2[(T2 >> 8) & 0xff] ^ Td1[(T3 >> 16) & 0xff] ^ W[24];
   S1 = Td0[T1 >> 24] ^ Td3[T2 & 0xff] ^ Td2[(T3 >> 8) & 0xff] ^ Td1[(T0 >> 16) & 0xff] ^ W[25];
   S2 = Td0[T2 >> 24] ^ Td3[T3 & 0xff] ^ Td2[(T0 >> 8) & 0xff] ^ Td1[(T1 >> 16) & 0xff] ^ W[26];
   S3 = Td0[T3 >> 24] ^ Td3[T0 & 0xff] ^ Td2[(T1 >> 8) & 0xff] ^ Td1[(T2 >> 16) & 0xff] ^ W[27];

   // Round 6
   T0 = Td0[S0 >> 24] ^ Td3[S1 & 0xff] ^ Td2[(S2 >> 8) & 0xff] ^ Td1[(S3 >> 16) & 0xff] ^ W[20];
   T1 = Td0[S1 >> 24] ^ Td3[S2 & 0xff] ^ Td2[(S3 >> 8) & 0xff] ^ Td1[(S0 >> 16) & 0xff] ^ W[21];
   T2 = Td0[S2 >> 24] ^ Td3[S3 & 0xff] ^ Td2[(S0 >> 8) & 0xff] ^ Td1[(S1 >> 16) & 0xff] ^ W[22];
   T3 = Td0[S3 >> 24] ^ Td3[S0 & 0xff] ^ Td2[(S1 >> 8) & 0xff] ^ Td1[(S2 >> 16) & 0xff] ^ W[23];

   // Round 5
   S0 = Td0[T0 >> 24] ^ Td3[T1 & 0xff] ^ Td2[(T2 >> 8) & 0xff] ^ Td1[(T3 >> 16) & 0xff] ^ W[16];
   S1 = Td0[T1 >> 24] ^ Td3[T2 & 0xff] ^ Td2[(T3 >> 8) & 0xff] ^ Td1[(T0 >> 16) & 0xff] ^ W[17];
   S2 = Td0[T2 >> 24] ^ Td3[T3 & 0xff] ^ Td2[(T0 >> 8) & 0xff] ^ Td1[(T1 >> 16) & 0xff] ^ W[18];
   S3 = Td0[T3 >> 24] ^ Td3[T0 & 0xff] ^ Td2[(T1 >> 8) & 0xff] ^ Td1[(T2 >> 16) & 0xff] ^ W[19];
   
   // Round 4
   T0 = Td0[S0 >> 24] ^ Td3[S1 & 0xff] ^ Td2[(S2 >> 8) & 0xff] ^ Td1[(S3 >> 16) & 0xff] ^ W[12];
   T1 = Td0[S1 >> 24] ^ Td3[S2 & 0xff] ^ Td2[(S3 >> 8) & 0xff] ^ Td1[(S0 >> 16) & 0xff] ^ W[13];
   T2 = Td0[S2 >> 24] ^ Td3[S3 & 0xff] ^ Td2[(S0 >> 8) & 0xff] ^ Td1[(S1 >> 16) & 0xff] ^ W[14];
   T3 = Td0[S3 >> 24] ^ Td3[S0 & 0xff] ^ Td2[(S1 >> 8) & 0xff] ^ Td1[(S2 >> 16) & 0xff] ^ W[15];

   // Round 3
   S0 = Td0[T0 >> 24] ^ Td3[T1 & 0xff] ^ Td2[(T2 >> 8) & 0xff] ^ Td1[(T3 >> 16) & 0xff] ^ W[8];
   S1 = Td0[T1 >> 24] ^ Td3[T2 & 0xff] ^ Td2[(T3 >> 8) & 0xff] ^ Td1[(T0 >> 16) & 0xff] ^ W[9];
   S2 = Td0[T2 >> 24] ^ Td3[T3 & 0xff] ^ Td2[(T0 >> 8) & 0xff] ^ Td1[(T1 >> 16) & 0xff] ^ W[10];
   S3 = Td0[T3 >> 24] ^ Td3[T0 & 0xff] ^ Td2[(T1 >> 8) & 0xff] ^ Td1[(T2 >> 16) & 0xff] ^ W[11];

   // Round 2
   T0 = Td0[S0 >> 24] ^ Td3[S1 & 0xff] ^ Td2[(S2 >> 8) & 0xff] ^ Td1[(S3 >> 16) & 0xff] ^ W[4];
   T1 = Td0[S1 >> 24] ^ Td3[S2 & 0xff] ^ Td2[(S3 >> 8) & 0xff] ^ Td1[(S0 >> 16) & 0xff] ^ W[5];
   T2 = Td0[S2 >> 24] ^ Td3[S3 & 0xff] ^ Td2[(S0 >> 8) & 0xff] ^ Td1[(S1 >> 16) & 0xff] ^ W[6];
   T3 = Td0[S3 >> 24] ^ Td3[S0 & 0xff] ^ Td2[(S1 >> 8) & 0xff] ^ Td1[(S2 >> 16) & 0xff] ^ W[7];

   // Round 1
   S0 = ((u32)invSbox[T0 >> 24] << 24) ^ ((u32)invSbox[T1 & 0xff]) ^ ((u32)invSbox[(T2 >> 8) & 0xff] << 8) ^ ((u32)invSbox[(T3 >> 16) & 0xff] << 16) ^ W[0];
   S1 = ((u32)invSbox[T1 >> 24] << 24) ^ ((u32)invSbox[T2 & 0xff]) ^ ((u32)invSbox[(T3 >> 8) & 0xff] << 8) ^ ((u32)invSbox[(T0 >> 16) & 0xff] << 16) ^ W[1];
   S2 = ((u32)invSbox[T2 >> 24] << 24) ^ ((u32)invSbox[T3 & 0xff]) ^ ((u32)invSbox[(T0 >> 8) & 0xff] << 8) ^ ((u32)invSbox[(T1 >> 16) & 0xff] << 16) ^ W[2];
   S3 = ((u32)invSbox[T3 >> 24] << 24) ^ ((u32)invSbox[T0 & 0xff]) ^ ((u32)invSbox[(T1 >> 8) & 0xff] << 8) ^ ((u32)invSbox[(T2 >> 16) & 0xff] << 16) ^ W[3];

   // Round 0
   u4byte_out(PT, S0);
   u4byte_out(PT + 4, S1);
   u4byte_out(PT + 8, S2);
   u4byte_out(PT + 12, S3);
}

void AES_KeyWordToByte(u32 W[], u8 RK[]) {
   for(int i = 0 ; i < 44 ; i++)
      u4byte_out(RK + 4 * i, W[i]);
}

void W_MixColumns(u32 *W)
{
   u8 RK[44 * 4];
   u8 temp[16];
   int i,j;
   
   AES_KeyWordToByte(W, RK);

   for (i = 1; i < 10; i++) { // 1~9 RoundKey까지만 MixColumns
      for (j = 0; j < 16; j += 4)
      {
         temp[j] = MULE(RK[16 * i + j]) ^ MULB(RK[16 * i + j + 1]) ^ MULD(RK[16 * i + j + 2]) ^ MUL9(RK[16 * i + j + 3]);
         temp[j + 1] = MUL9(RK[16 * i + j]) ^ MULE(RK[16 * i + j + 1]) ^ MULB(RK[16 * i + j + 2]) ^ MULD(RK[16 * i + j + 3]);
         temp[j + 2] = MULD(RK[16 * i + j]) ^ MUL9(RK[16 * i + j + 1]) ^ MULE(RK[16 * i + j + 2]) ^ MULB(RK[16 * i + j + 3]);
         temp[j + 3] = MULB(RK[16 * i + j]) ^ MULD(RK[16 * i + j + 1]) ^ MUL9(RK[16 * i + j + 2]) ^ MULE(RK[16 * i + j + 3]);
      }
      RK[0 + i * 16] = temp[0]; RK[1 + i * 16] = temp[1]; RK[2 + i * 16] = temp[2]; RK[3 + i * 16] = temp[3];
      RK[4 + i * 16] = temp[4]; RK[5 + i * 16] = temp[5]; RK[6 + i * 16] = temp[6]; RK[7 + i * 16] = temp[7];
      RK[8 + i * 16] = temp[8]; RK[9 + i * 16] = temp[9]; RK[10 + i * 16] = temp[10]; RK[11 + i * 16] = temp[11];
      RK[12 + i * 16] = temp[12]; RK[13 + i * 16] = temp[13]; RK[14 + i * 16] = temp[14]; RK[15 + i * 16] = temp[15];

   }
}

void RoundKeyGeneration128_Optimization(u8 *MK, u32 *W) {
   u32   T;

   W[0] = u4byte_in(MK);
   W[1] = u4byte_in(MK + 4);
   W[2] = u4byte_in(MK + 8);
   W[3] = u4byte_in(MK + 12);

   for (int i = 0;  i < 10 ; i++) {
      //T = G_func(W[4 * i + 3]);
      T = W[4 * i + 3];
      T = RotWord(T);
      T = SubWord(T);
      T ^= Rcons[i];

      W[4 * i + 4] = W[4 * i] ^ T;
      W[4 * i + 5] = W[4 * i + 1] ^ W[4 * i + 4];
      W[4 * i + 6] = W[4 * i + 2] ^ W[4 * i + 5];
      W[4 * i + 7] = W[4 * i + 3] ^ W[4 * i + 6];
   }
   W_MixColumns(W);
}

void AES_KeySchedule_Optimization(u8* MK, u32* W, u32 keysize) {
    if (keysize == 128)      RoundKeyGeneration128_Optimization(MK, W);
}

void AES_DEC_Optimization_ECB(char* inst, char* outst, u32 W[])
{
   FILE     *RFP, * WFP;
   u8       *inStream, *outStream, r;
   u32      lenData;

   if((RFP = fopen(inst, "rb")) == NULL) { puts("파일 스트림 읽기 에러"); return; }

   fseek(RFP, 0, SEEK_END);   // 파일크기 읽기
   lenData = ftell(RFP);      // 

   fseek(RFP, 0, SEEK_SET); 
   inStream    = calloc(lenData, sizeof(u8)); 
   outStream   = calloc(lenData, sizeof(u8));
   fread(inStream, 1, lenData, RFP);
   fclose(RFP);

   for (int i = 0; i < lenData / 16; i++)
      AES_DEC_Optimization(outStream + 16 * i, inStream + 16 * i, W, 128);

   r = outStream[lenData - 1];

   if((WFP = fopen(outst, "wb")) == NULL) { puts("파일 스트림 쓰기 에러"); return; }
   fwrite(outStream, 1, lenData - r, WFP); //outStream 데이터를 wfp에 쓴다.dk
   fclose(WFP);
}

void AES_DEC_Optimization_CTR(char* inst, char* outst, u32 W[])
{  
   // CTR이므로 패딩을 구현하지 않았습니다.
   u32      lenData;
   u32      Block       = 0;
   u8       Padding     = 0;
   u8       *encryptedFile;
   u8       **IV, **CT;
   FILE     *RFP, * WFP;

   if((RFP = fopen(inst, "rb")) == NULL) { puts("파일 스트림 읽기 에러"); return; }

   fseek(RFP, 0, SEEK_END);   // 파일크기 읽기
   lenData = ftell(RFP);      // 

   fseek(RFP, 0, SEEK_SET); 
   encryptedFile = calloc(lenData, sizeof(u8)); 
   
   fread(encryptedFile, 1, lenData, RFP);
   fclose(RFP);

   Block = (int)(lenData / 16);

   IV = (u8**)calloc(Block, sizeof(u8*));
	for(int i = 0; i < Block ; i++)
		IV[i] = (u8*)calloc(16, sizeof(u8));

   CT = (u8**)calloc(Block, sizeof(u8*));
	for(int i = 0; i < Block ; i++)
		CT[i] = (u8*)calloc(16, sizeof(u8));

   if((WFP = fopen(outst, "wb")) == NULL) { puts("파일 스트림 쓰기 에러"); return; }
   // IV 생성 (비표 = 0 | 블록번호 기입)

   for(int i = 0 ; i < Block ; i++)
      printf("%02X ", encryptedFile[i]);

   for(int i = 0 ; i < Block ; i++) {
      IV[i][15] = i & 0xff;
      IV[i][14] = (i >> 8) & 0xff;
      IV[i][13] = (i >> 16) & 0xff;
      IV[i][12] = (i >> 24) & 0xff;
      
      AES_ENC_Optimization(IV[i], CT[i], W, 128);
      for(int j = 0 ; j < 16 ; j++) 
         CT[i][j] ^= encryptedFile[i * 16 + j];

      fwrite(CT[i], sizeof(u8), 16, WFP);
   }
   for(int i = 0 ; i < 16 ; i++) printf("%02X ", CT[0][i]);
   fclose(WFP);
   printf("[%d Blocks]\n", Block);
   for(int i = 0 ; i < Block ; i++) { free(IV[i]); free(CT[i]); }
   free(IV);
   free(CT);
   free(encryptedFile);
}

int main(int argc, char* argv[])
{
   u32      W[44]       = { 0x00, };
   u8       MK[16]      = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
   int      keysize     = 128;
   clock_t  start, finish;

   if(argc != 4) { puts("Usage : ./Dec {Encrypted File} {New FileName} {Mode}"); return 0; }
   AES_KeySchedule_Optimization(MK, W, keysize);

   if((strncmp(argv[3], "ECB", 3) == 0) || (strncmp(argv[3], "ecb", 3) == 0)) {
      puts("ECB");
      start = clock();
      AES_DEC_Optimization_ECB(argv[1], argv[2], W);
      finish = clock();
   }
   else if((strncmp(argv[3], "CTR", 3) == 0) || (strncmp(argv[3], "ctr", 3) == 0)) {
      puts("CTR");
      start = clock();
      AES_DEC_Optimization_CTR(argv[1], argv[2], W);
      finish = clock();
   }
   else {
      puts("운영모드는 ECB, CTR 중 하나여야 합니다.");
      return 0;
   }

   printf("원본 파일\t%s\n해독 파일\t%s\n운영 모드\t%s\n연산 시간\t%f초\n", argv[1], argv[2], argv[3], (double)(finish - start) / CLOCKS_PER_SEC);
   
   return 0;
}
