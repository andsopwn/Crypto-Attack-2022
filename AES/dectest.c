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
    u32 s0, s1, s2, s3, t0, t1, t2, t3;

    //0 round
    s0 = u4byte_in(PT) ^ W[0];
    s1 = u4byte_in(PT + 4) ^ W[1];
    s2 = u4byte_in(PT + 8) ^ W[2];
    s3 = u4byte_in(PT + 12) ^ W[3];

    //1 round
    t0 = Te0[s0 >> 24] ^ Te1[(s1 >> 16) & 0xff] ^ Te2[(s2 >> 8) & 0xff] ^ Te3[s3 & 0xff] ^ W[4];
    t1 = Te0[s1 >> 24] ^ Te1[(s2 >> 16) & 0xff] ^ Te2[(s3 >> 8) & 0xff] ^ Te3[s0 & 0xff] ^ W[5];
    t2 = Te0[s2 >> 24] ^ Te1[(s3 >> 16) & 0xff] ^ Te2[(s0 >> 8) & 0xff] ^ Te3[s1 & 0xff] ^ W[6];
    t3 = Te0[s3 >> 24] ^ Te1[(s0 >> 16) & 0xff] ^ Te2[(s1 >> 8) & 0xff] ^ Te3[s2 & 0xff] ^ W[7];

    //2 round
    s0 = Te0[t0 >> 24] ^ Te1[(t1 >> 16) & 0xff] ^ Te2[(t2 >> 8) & 0xff] ^ Te3[t3 & 0xff] ^ W[8];
    s1 = Te0[t1 >> 24] ^ Te1[(t2 >> 16) & 0xff] ^ Te2[(t3 >> 8) & 0xff] ^ Te3[t0 & 0xff] ^ W[9];
    s2 = Te0[t2 >> 24] ^ Te1[(t3 >> 16) & 0xff] ^ Te2[(t0 >> 8) & 0xff] ^ Te3[t1 & 0xff] ^ W[10];
    s3 = Te0[t3 >> 24] ^ Te1[(t0 >> 16) & 0xff] ^ Te2[(t1 >> 8) & 0xff] ^ Te3[t2 & 0xff] ^ W[11];

    //3 round
    t0 = Te0[s0 >> 24] ^ Te1[(s1 >> 16) & 0xff] ^ Te2[(s2 >> 8) & 0xff] ^ Te3[s3 & 0xff] ^ W[12];
    t1 = Te0[s1 >> 24] ^ Te1[(s2 >> 16) & 0xff] ^ Te2[(s3 >> 8) & 0xff] ^ Te3[s0 & 0xff] ^ W[13];
    t2 = Te0[s2 >> 24] ^ Te1[(s3 >> 16) & 0xff] ^ Te2[(s0 >> 8) & 0xff] ^ Te3[s1 & 0xff] ^ W[14];
    t3 = Te0[s3 >> 24] ^ Te1[(s0 >> 16) & 0xff] ^ Te2[(s1 >> 8) & 0xff] ^ Te3[s2 & 0xff] ^ W[15];

    //4 round
    s0 = Te0[t0 >> 24] ^ Te1[(t1 >> 16) & 0xff] ^ Te2[(t2 >> 8) & 0xff] ^ Te3[t3 & 0xff] ^ W[16];
    s1 = Te0[t1 >> 24] ^ Te1[(t2 >> 16) & 0xff] ^ Te2[(t3 >> 8) & 0xff] ^ Te3[t0 & 0xff] ^ W[17];
    s2 = Te0[t2 >> 24] ^ Te1[(t3 >> 16) & 0xff] ^ Te2[(t0 >> 8) & 0xff] ^ Te3[t1 & 0xff] ^ W[18];
    s3 = Te0[t3 >> 24] ^ Te1[(t0 >> 16) & 0xff] ^ Te2[(t1 >> 8) & 0xff] ^ Te3[t2 & 0xff] ^ W[19];

    //5 round
    t0 = Te0[s0 >> 24] ^ Te1[(s1 >> 16) & 0xff] ^ Te2[(s2 >> 8) & 0xff] ^ Te3[s3 & 0xff] ^ W[20];
    t1 = Te0[s1 >> 24] ^ Te1[(s2 >> 16) & 0xff] ^ Te2[(s3 >> 8) & 0xff] ^ Te3[s0 & 0xff] ^ W[21];
    t2 = Te0[s2 >> 24] ^ Te1[(s3 >> 16) & 0xff] ^ Te2[(s0 >> 8) & 0xff] ^ Te3[s1 & 0xff] ^ W[22];
    t3 = Te0[s3 >> 24] ^ Te1[(s0 >> 16) & 0xff] ^ Te2[(s1 >> 8) & 0xff] ^ Te3[s2 & 0xff] ^ W[23];

    //6 round
    s0 = Te0[t0 >> 24] ^ Te1[(t1 >> 16) & 0xff] ^ Te2[(t2 >> 8) & 0xff] ^ Te3[t3 & 0xff] ^ W[24];
    s1 = Te0[t1 >> 24] ^ Te1[(t2 >> 16) & 0xff] ^ Te2[(t3 >> 8) & 0xff] ^ Te3[t0 & 0xff] ^ W[25];
    s2 = Te0[t2 >> 24] ^ Te1[(t3 >> 16) & 0xff] ^ Te2[(t0 >> 8) & 0xff] ^ Te3[t1 & 0xff] ^ W[26];
    s3 = Te0[t3 >> 24] ^ Te1[(t0 >> 16) & 0xff] ^ Te2[(t1 >> 8) & 0xff] ^ Te3[t2 & 0xff] ^ W[27];

    //7 round
    t0 = Te0[s0 >> 24] ^ Te1[(s1 >> 16) & 0xff] ^ Te2[(s2 >> 8) & 0xff] ^ Te3[s3 & 0xff] ^ W[28];
    t1 = Te0[s1 >> 24] ^ Te1[(s2 >> 16) & 0xff] ^ Te2[(s3 >> 8) & 0xff] ^ Te3[s0 & 0xff] ^ W[29];
    t2 = Te0[s2 >> 24] ^ Te1[(s3 >> 16) & 0xff] ^ Te2[(s0 >> 8) & 0xff] ^ Te3[s1 & 0xff] ^ W[30];
    t3 = Te0[s3 >> 24] ^ Te1[(s0 >> 16) & 0xff] ^ Te2[(s1 >> 8) & 0xff] ^ Te3[s2 & 0xff] ^ W[31];

    //8 round
    s0 = Te0[t0 >> 24] ^ Te1[(t1 >> 16) & 0xff] ^ Te2[(t2 >> 8) & 0xff] ^ Te3[t3 & 0xff] ^ W[32];
    s1 = Te0[t1 >> 24] ^ Te1[(t2 >> 16) & 0xff] ^ Te2[(t3 >> 8) & 0xff] ^ Te3[t0 & 0xff] ^ W[33];
    s2 = Te0[t2 >> 24] ^ Te1[(t3 >> 16) & 0xff] ^ Te2[(t0 >> 8) & 0xff] ^ Te3[t1 & 0xff] ^ W[34];
    s3 = Te0[t3 >> 24] ^ Te1[(t0 >> 16) & 0xff] ^ Te2[(t1 >> 8) & 0xff] ^ Te3[t2 & 0xff] ^ W[35];

    if (Nr == 10)
    {
        //9 round
        t0 = Te0[s0 >> 24] ^ Te1[(s1 >> 16) & 0xff] ^ Te2[(s2 >> 8) & 0xff] ^ Te3[s3 & 0xff] ^ W[36];
        t1 = Te0[s1 >> 24] ^ Te1[(s2 >> 16) & 0xff] ^ Te2[(s3 >> 8) & 0xff] ^ Te3[s0 & 0xff] ^ W[37];
        t2 = Te0[s2 >> 24] ^ Te1[(s3 >> 16) & 0xff] ^ Te2[(s0 >> 8) & 0xff] ^ Te3[s1 & 0xff] ^ W[38];
        t3 = Te0[s3 >> 24] ^ Te1[(s0 >> 16) & 0xff] ^ Te2[(s1 >> 8) & 0xff] ^ Te3[s2 & 0xff] ^ W[39];

        //10 round
        s0 = (Te2[(t0 >> 24)] & 0xff000000) ^ (Te3[(t1 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(t2 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[t3 & 0xff] & 0x000000ff) ^ W[40];
        s1 = (Te2[(t1 >> 24)] & 0xff000000) ^ (Te3[(t2 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(t3 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[t0 & 0xff] & 0x000000ff) ^ W[41];
        s2 = (Te2[(t2 >> 24)] & 0xff000000) ^ (Te3[(t3 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(t0 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[t1 & 0xff] & 0x000000ff) ^ W[42];
        s3 = (Te2[(t3 >> 24)] & 0xff000000) ^ (Te3[(t0 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(t1 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[t2 & 0xff] & 0x000000ff) ^ W[43];
    }
    else if (Nr == 12) {
        //9 round
        t0 = Te0[s0 >> 24] ^ Te1[(s1 >> 16) & 0xff] ^ Te2[(s2 >> 8) & 0xff] ^ Te3[s3 & 0xff] ^ W[36];
        t1 = Te0[s1 >> 24] ^ Te1[(s2 >> 16) & 0xff] ^ Te2[(s3 >> 8) & 0xff] ^ Te3[s0 & 0xff] ^ W[37];
        t2 = Te0[s2 >> 24] ^ Te1[(s3 >> 16) & 0xff] ^ Te2[(s0 >> 8) & 0xff] ^ Te3[s1 & 0xff] ^ W[38];
        t3 = Te0[s3 >> 24] ^ Te1[(s0 >> 16) & 0xff] ^ Te2[(s1 >> 8) & 0xff] ^ Te3[s2 & 0xff] ^ W[39];

        //10 round
        s0 = Te0[t0 >> 24] ^ Te1[(t1 >> 16) & 0xff] ^ Te2[(t2 >> 8) & 0xff] ^ Te3[t3 & 0xff] ^ W[40];
        s1 = Te0[t1 >> 24] ^ Te1[(t2 >> 16) & 0xff] ^ Te2[(t3 >> 8) & 0xff] ^ Te3[t0 & 0xff] ^ W[41];
        s2 = Te0[t2 >> 24] ^ Te1[(t3 >> 16) & 0xff] ^ Te2[(t0 >> 8) & 0xff] ^ Te3[t1 & 0xff] ^ W[42];
        s3 = Te0[t3 >> 24] ^ Te1[(t0 >> 16) & 0xff] ^ Te2[(t1 >> 8) & 0xff] ^ Te3[t2 & 0xff] ^ W[43];

        //11 round
        t0 = Te0[s0 >> 24] ^ Te1[(s1 >> 16) & 0xff] ^ Te2[(s2 >> 8) & 0xff] ^ Te3[s3 & 0xff] ^ W[44];
        t1 = Te0[s1 >> 24] ^ Te1[(s2 >> 16) & 0xff] ^ Te2[(s3 >> 8) & 0xff] ^ Te3[s0 & 0xff] ^ W[45];
        t2 = Te0[s2 >> 24] ^ Te1[(s3 >> 16) & 0xff] ^ Te2[(s0 >> 8) & 0xff] ^ Te3[s1 & 0xff] ^ W[46];
        t3 = Te0[s3 >> 24] ^ Te1[(s0 >> 16) & 0xff] ^ Te2[(s1 >> 8) & 0xff] ^ Te3[s2 & 0xff] ^ W[47];

        //12 round
        s0 = (Te2[(t0 >> 24)] & 0xff000000) ^ (Te3[(t1 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(t2 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[t3 & 0xff] & 0x000000ff) ^ W[48];
        s1 = (Te2[(t1 >> 24)] & 0xff000000) ^ (Te3[(t2 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(t3 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[t0 & 0xff] & 0x000000ff) ^ W[49];
        s2 = (Te2[(t2 >> 24)] & 0xff000000) ^ (Te3[(t3 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(t0 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[t1 & 0xff] & 0x000000ff) ^ W[50];
        s3 = (Te2[(t3 >> 24)] & 0xff000000) ^ (Te3[(t0 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(t1 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[t2 & 0xff] & 0x000000ff) ^ W[51];
    }
    else if (Nr == 14) {
        //9 round
        t0 = Te0[s0 >> 24] ^ Te1[(s1 >> 16) & 0xff] ^ Te2[(s2 >> 8) & 0xff] ^ Te3[s3 & 0xff] ^ W[36];
        t1 = Te0[s1 >> 24] ^ Te1[(s2 >> 16) & 0xff] ^ Te2[(s3 >> 8) & 0xff] ^ Te3[s0 & 0xff] ^ W[37];
        t2 = Te0[s2 >> 24] ^ Te1[(s3 >> 16) & 0xff] ^ Te2[(s0 >> 8) & 0xff] ^ Te3[s1 & 0xff] ^ W[38];
        t3 = Te0[s3 >> 24] ^ Te1[(s0 >> 16) & 0xff] ^ Te2[(s1 >> 8) & 0xff] ^ Te3[s2 & 0xff] ^ W[39];

        //10 round
        s0 = Te0[t0 >> 24] ^ Te1[(t1 >> 16) & 0xff] ^ Te2[(t2 >> 8) & 0xff] ^ Te3[t3 & 0xff] ^ W[40];
        s1 = Te0[t1 >> 24] ^ Te1[(t2 >> 16) & 0xff] ^ Te2[(t3 >> 8) & 0xff] ^ Te3[t0 & 0xff] ^ W[41];
        s2 = Te0[t2 >> 24] ^ Te1[(t3 >> 16) & 0xff] ^ Te2[(t0 >> 8) & 0xff] ^ Te3[t1 & 0xff] ^ W[42];
        s3 = Te0[t3 >> 24] ^ Te1[(t0 >> 16) & 0xff] ^ Te2[(t1 >> 8) & 0xff] ^ Te3[t2 & 0xff] ^ W[43];

        //11 round
        t0 = Te0[s0 >> 24] ^ Te1[(s1 >> 16) & 0xff] ^ Te2[(s2 >> 8) & 0xff] ^ Te3[s3 & 0xff] ^ W[44];
        t1 = Te0[s1 >> 24] ^ Te1[(s2 >> 16) & 0xff] ^ Te2[(s3 >> 8) & 0xff] ^ Te3[s0 & 0xff] ^ W[45];
        t2 = Te0[s2 >> 24] ^ Te1[(s3 >> 16) & 0xff] ^ Te2[(s0 >> 8) & 0xff] ^ Te3[s1 & 0xff] ^ W[46];
        t3 = Te0[s3 >> 24] ^ Te1[(s0 >> 16) & 0xff] ^ Te2[(s1 >> 8) & 0xff] ^ Te3[s2 & 0xff] ^ W[47];

        //12 round
        s0 = Te0[t0 >> 24] ^ Te1[(t1 >> 16) & 0xff] ^ Te2[(t2 >> 8) & 0xff] ^ Te3[t3 & 0xff] ^ W[48];
        s1 = Te0[t1 >> 24] ^ Te1[(t2 >> 16) & 0xff] ^ Te2[(t3 >> 8) & 0xff] ^ Te3[t0 & 0xff] ^ W[49];
        s2 = Te0[t2 >> 24] ^ Te1[(t3 >> 16) & 0xff] ^ Te2[(t0 >> 8) & 0xff] ^ Te3[t1 & 0xff] ^ W[50];
        s3 = Te0[t3 >> 24] ^ Te1[(t0 >> 16) & 0xff] ^ Te2[(t1 >> 8) & 0xff] ^ Te3[t2 & 0xff] ^ W[51];

        //13 round
        t0 = Te0[s0 >> 24] ^ Te1[(s1 >> 16) & 0xff] ^ Te2[(s2 >> 8) & 0xff] ^ Te3[s3 & 0xff] ^ W[52];
        t1 = Te0[s1 >> 24] ^ Te1[(s2 >> 16) & 0xff] ^ Te2[(s3 >> 8) & 0xff] ^ Te3[s0 & 0xff] ^ W[53];
        t2 = Te0[s2 >> 24] ^ Te1[(s3 >> 16) & 0xff] ^ Te2[(s0 >> 8) & 0xff] ^ Te3[s1 & 0xff] ^ W[54];
        t3 = Te0[s3 >> 24] ^ Te1[(s0 >> 16) & 0xff] ^ Te2[(s1 >> 8) & 0xff] ^ Te3[s2 & 0xff] ^ W[55];

        //14 round
        s0 = (Te2[(t0 >> 24)] & 0xff000000) ^ (Te3[(t1 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(t2 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[t3 & 0xff] & 0x000000ff) ^ W[56];
        s1 = (Te2[(t1 >> 24)] & 0xff000000) ^ (Te3[(t2 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(t3 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[t0 & 0xff] & 0x000000ff) ^ W[57];
        s2 = (Te2[(t2 >> 24)] & 0xff000000) ^ (Te3[(t3 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(t0 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[t1 & 0xff] & 0x000000ff) ^ W[58];
        s3 = (Te2[(t3 >> 24)] & 0xff000000) ^ (Te3[(t0 >> 16) & 0xff] & 0x00ff0000) ^ (Te0[(t1 >> 8) & 0xff] & 0x0000ff00) ^ (Te1[t2 & 0xff] & 0x000000ff) ^ W[59];
    }

    u4byte_out(CT, s0);
    u4byte_out(CT + 4, s1);
    u4byte_out(CT + 8, s2);
    u4byte_out(CT + 12, s3);
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

   u4byte_out(PT, S0);
   u4byte_out(PT + 4, S1);
   u4byte_out(PT + 8, S2);
   u4byte_out(PT + 12, S3);
}

void AES_KeyWordToByte(u32 W[], u8 RK[]) {
   for(int i = 0 ; i < 44 ; i++)
      u4byte_out(RK + 4 * i, W[i]);
}
void W_MixColumns(u32 *W) {
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

int main() {
   u8      PT[16] = { 0x3c, 0x4a, 0x8b, 0xec, 0x82, 0x40, 0x8a, 0x82, 0x94, 0x68, 0xc7, 0xe5, 0x0a, 0x91, 0xce, 0x95 };
   u8      CT[16] = { 0x7D, 0xF7, 0x6B, 0x0C, 0x1A, 0xB8, 0x99, 0xB3, 0x3E, 0x42, 0xF0, 0x47, 0xB9, 0x1B, 0x54, 0x6F };
   u8      OT[16] = { 0x00, };
   u8      OO[16] = { 0x82, 0x2F, 0x94, 0xED, 0x16, 0x86, 0xDC, 0xCB, 0x57, 0x24, 0xF0, 0x47, 0xF4, 0x56, 0x54, 0x45 };
   u8      MK[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
   u32     W[44] = { 0x00, };

   AES_KeySchedule_Optimization(MK, W, 128);

   for(int i = 0 ; i < 16 ; i++) printf("%02X ", PT[i]); puts("");
    
   //AES_ENC_Optimization(PT, CT, W, 128);   

   
   //AES_DEC_Optimization(OT, CT, W, 128);
   for(int i = 0 ; i < 16 ; i++) printf("%02X ", CT[i]); puts("");
   for(int i = 0 ; i < 16 ; i++) printf("%02X ", OT[i]); puts("");
   for(int i = 0 ; i < 16 ; i++) printf("%02X ", OO[i] ^ CT[i]); puts("");
}