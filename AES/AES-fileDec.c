#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "aes.h"

#define DEBUG 0

void AES_ENC_Optimization(u8 *PT, u8 *CT, u32 *W, int keysize) {
   int   Nr    = keysize / 32 + 6;
   u32   S0, S1, S2, S3, T0, T1, T2, T3;

   //0 round
   S0 = u4byte_in(PT)        ^ W[0];
   S1 = u4byte_in(PT + 4)    ^ W[1];
   S2 = u4byte_in(PT + 8)    ^ W[2];
   S3 = u4byte_in(PT + 12)   ^ W[3];

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

   if (Nr == 10) {
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
   int   Nr    = keysize / 32 + 6; //라운드 수
   u32   S0, S1, S2, S3, T0, T1, T2, T3;

   S0 = u4byte_in(CT)       ^ W[40];
   S1 = u4byte_in(CT + 4)   ^ W[41];
   S2 = u4byte_in(CT + 8)   ^ W[42];
   S3 = u4byte_in(CT + 12)  ^ W[43]; 

   //  10 round
   T0 = Td0[S0 >> 24] ^ Td3[S1 & 0xff] ^ Td2[(S2 >> 8) & 0xff] ^ Td1[(S3 >> 16) & 0xff] ^ W[36];
   T1 = Td0[S1 >> 24] ^ Td3[S2 & 0xff] ^ Td2[(S3 >> 8) & 0xff] ^ Td1[(S0 >> 16) & 0xff] ^ W[37];
   T2 = Td0[S2 >> 24] ^ Td3[S3 & 0xff] ^ Td2[(S0 >> 8) & 0xff] ^ Td1[(S1 >> 16) & 0xff] ^ W[38];
   T3 = Td0[S3 >> 24] ^ Td3[S0 & 0xff] ^ Td2[(S1 >> 8) & 0xff] ^ Td1[(S2 >> 16) & 0xff] ^ W[39];

   // 9 round
   S0 = Td0[T0 >> 24] ^ Td3[T1 & 0xff] ^ Td2[(T2 >> 8) & 0xff] ^ Td1[(T3 >> 16) & 0xff] ^ W[32];
   S1 = Td0[T1 >> 24] ^ Td3[T2 & 0xff] ^ Td2[(T3 >> 8) & 0xff] ^ Td1[(T0 >> 16) & 0xff] ^ W[33];
   S2 = Td0[T2 >> 24] ^ Td3[T3 & 0xff] ^ Td2[(T0 >> 8) & 0xff] ^ Td1[(T1 >> 16) & 0xff] ^ W[34];
   S3 = Td0[T3 >> 24] ^ Td3[T0 & 0xff] ^ Td2[(T1 >> 8) & 0xff] ^ Td1[(T2 >> 16) & 0xff] ^ W[35];

   // 8 round
   T0 = Td0[S0 >> 24] ^ Td3[S1 & 0xff] ^ Td2[(S2 >> 8) & 0xff] ^ Td1[(S3 >> 16) & 0xff] ^ W[28];
   T1 = Td0[S1 >> 24] ^ Td3[S2 & 0xff] ^ Td2[(S3 >> 8) & 0xff] ^ Td1[(S0 >> 16) & 0xff] ^ W[29];
   T2 = Td0[S2 >> 24] ^ Td3[S3 & 0xff] ^ Td2[(S0 >> 8) & 0xff] ^ Td1[(S1 >> 16) & 0xff] ^ W[30];
   T3 = Td0[S3 >> 24] ^ Td3[S0 & 0xff] ^ Td2[(S1 >> 8) & 0xff] ^ Td1[(S2 >> 16) & 0xff] ^ W[31];

   // 7 round
   S0 = Td0[T0 >> 24] ^ Td3[T1 & 0xff] ^ Td2[(T2 >> 8) & 0xff] ^ Td1[(T3 >> 16) & 0xff] ^ W[24];
   S1 = Td0[T1 >> 24] ^ Td3[T2 & 0xff] ^ Td2[(T3 >> 8) & 0xff] ^ Td1[(T0 >> 16) & 0xff] ^ W[25];
   S2 = Td0[T2 >> 24] ^ Td3[T3 & 0xff] ^ Td2[(T0 >> 8) & 0xff] ^ Td1[(T1 >> 16) & 0xff] ^ W[26];
   S3 = Td0[T3 >> 24] ^ Td3[T0 & 0xff] ^ Td2[(T1 >> 8) & 0xff] ^ Td1[(T2 >> 16) & 0xff] ^ W[27];

   // 6 round
   T0 = Td0[S0 >> 24] ^ Td3[S1 & 0xff] ^ Td2[(S2 >> 8) & 0xff] ^ Td1[(S3 >> 16) & 0xff] ^ W[20];
   T1 = Td0[S1 >> 24] ^ Td3[S2 & 0xff] ^ Td2[(S3 >> 8) & 0xff] ^ Td1[(S0 >> 16) & 0xff] ^ W[21];
   T2 = Td0[S2 >> 24] ^ Td3[S3 & 0xff] ^ Td2[(S0 >> 8) & 0xff] ^ Td1[(S1 >> 16) & 0xff] ^ W[22];
   T3 = Td0[S3 >> 24] ^ Td3[S0 & 0xff] ^ Td2[(S1 >> 8) & 0xff] ^ Td1[(S2 >> 16) & 0xff] ^ W[23];

   // 5 round
   S0 = Td0[T0 >> 24] ^ Td3[T1 & 0xff] ^ Td2[(T2 >> 8) & 0xff] ^ Td1[(T3 >> 16) & 0xff] ^ W[16];
   S1 = Td0[T1 >> 24] ^ Td3[T2 & 0xff] ^ Td2[(T3 >> 8) & 0xff] ^ Td1[(T0 >> 16) & 0xff] ^ W[17];
   S2 = Td0[T2 >> 24] ^ Td3[T3 & 0xff] ^ Td2[(T0 >> 8) & 0xff] ^ Td1[(T1 >> 16) & 0xff] ^ W[18];
   S3 = Td0[T3 >> 24] ^ Td3[T0 & 0xff] ^ Td2[(T1 >> 8) & 0xff] ^ Td1[(T2 >> 16) & 0xff] ^ W[19];
   // 4 round
   T0 = Td0[S0 >> 24] ^ Td3[S1 & 0xff] ^ Td2[(S2 >> 8) & 0xff] ^ Td1[(S3 >> 16) & 0xff] ^ W[12];
   T1 = Td0[S1 >> 24] ^ Td3[S2 & 0xff] ^ Td2[(S3 >> 8) & 0xff] ^ Td1[(S0 >> 16) & 0xff] ^ W[13];
   T2 = Td0[S2 >> 24] ^ Td3[S3 & 0xff] ^ Td2[(S0 >> 8) & 0xff] ^ Td1[(S1 >> 16) & 0xff] ^ W[14];
   T3 = Td0[S3 >> 24] ^ Td3[S0 & 0xff] ^ Td2[(S1 >> 8) & 0xff] ^ Td1[(S2 >> 16) & 0xff] ^ W[15];
   // 3 round
   S0 = Td0[T0 >> 24] ^ Td3[T1 & 0xff] ^ Td2[(T2 >> 8) & 0xff] ^ Td1[(T3 >> 16) & 0xff] ^ W[8];
   S1 = Td0[T1 >> 24] ^ Td3[T2 & 0xff] ^ Td2[(T3 >> 8) & 0xff] ^ Td1[(T0 >> 16) & 0xff] ^ W[9];
   S2 = Td0[T2 >> 24] ^ Td3[T3 & 0xff] ^ Td2[(T0 >> 8) & 0xff] ^ Td1[(T1 >> 16) & 0xff] ^ W[10];
   S3 = Td0[T3 >> 24] ^ Td3[T0 & 0xff] ^ Td2[(T1 >> 8) & 0xff] ^ Td1[(T2 >> 16) & 0xff] ^ W[11];

   // 2 round
   T0 = Td0[S0 >> 24] ^ Td3[S1 & 0xff] ^ Td2[(S2 >> 8) & 0xff] ^ Td1[(S3 >> 16) & 0xff] ^ W[4];
   T1 = Td0[S1 >> 24] ^ Td3[S2 & 0xff] ^ Td2[(S3 >> 8) & 0xff] ^ Td1[(S0 >> 16) & 0xff] ^ W[5];
   T2 = Td0[S2 >> 24] ^ Td3[S3 & 0xff] ^ Td2[(S0 >> 8) & 0xff] ^ Td1[(S1 >> 16) & 0xff] ^ W[6];
   T3 = Td0[S3 >> 24] ^ Td3[S0 & 0xff] ^ Td2[(S1 >> 8) & 0xff] ^ Td1[(S2 >> 16) & 0xff] ^ W[7];

   // 1 round
   S0 = ((u32)invSbox[T0 >> 24] << 24) ^ ((u32)invSbox[T1 & 0xff]) ^ ((u32)invSbox[(T2 >> 8) & 0xff] << 8) ^ ((u32)invSbox[(T3 >> 16) & 0xff] << 16) ^ W[0];
   S1 = ((u32)invSbox[T1 >> 24] << 24) ^ ((u32)invSbox[T2 & 0xff]) ^ ((u32)invSbox[(T3 >> 8) & 0xff] << 8) ^ ((u32)invSbox[(T0 >> 16) & 0xff] << 16) ^ W[1];
   S2 = ((u32)invSbox[T2 >> 24] << 24) ^ ((u32)invSbox[T3 & 0xff]) ^ ((u32)invSbox[(T0 >> 8) & 0xff] << 8) ^ ((u32)invSbox[(T1 >> 16) & 0xff] << 16) ^ W[2];
   S3 = ((u32)invSbox[T3 >> 24] << 24) ^ ((u32)invSbox[T0 & 0xff]) ^ ((u32)invSbox[(T1 >> 8) & 0xff] << 8) ^ ((u32)invSbox[(T2 >> 16) & 0xff] << 16) ^ W[3];

   u4byte_out(PT, S0);
   u4byte_out(PT + 4, S1);
   u4byte_out(PT + 8, S2);
   u4byte_out(PT + 12, S3);
}

clock_t AES_DEC_CTR(char* inst, char* outst, u32 *W) {  
   // CTR 복호화이므로 암호화 과정에 패딩이 되어있다고 가정하고 복호화에서는 패딩 제거만 구현했습니다.
   u32      fileSize;         // 파일의 크기를 담을 변수입니다.
   u8       CTR[16]     = { 0x00, };   // Counter Array
   u8       Padding     = 0;  // 패딩 값입니다.
   u8       *encryptedFile;   // 파일의 바이너리 값을 올리기 위한 변수입니다.
   u8       *decryptedFile;   // 복호화된 파일 
   FILE     *RFP, * WFP;      // RFP - read, WFP - Write 파일 입출력
   clock_t  start = 0, finish = 0;
   u32      time = 0;

   if((RFP = fopen(inst, "rb")) == NULL) { puts("파일 스트림 읽기 에러"); return 0; }

   fseek(RFP, 0, SEEK_END);   // 파일크기 읽기
   fileSize = ftell(RFP);     //

   fseek(RFP, 0, SEEK_SET); 
   encryptedFile = calloc(fileSize, sizeof(u8)); 
   decryptedFile = calloc(fileSize, sizeof(u8)); 

   fread(encryptedFile, 1, fileSize, RFP);
   fclose(RFP);

   if((WFP = fopen(outst, "wb")) == NULL) { puts("파일 스트림 쓰기 에러"); return 0; }
   // IV 생성 (비표 = 0 | 블록번호 기입)
   //for(int i = 0 ; i < Block ; i++) printf("%02X ", encryptedFile[i]);
   for(int i = 0 ; i < (int)(fileSize / 16) ; i++) {
      CTR[15] = i & 0xff;
      CTR[14] = (i >> 8) & 0xff;
      CTR[13] = (i >> 16) & 0xff;
      CTR[12] = (i >> 24) & 0xff;
      start = clock();
      AES_ENC_Optimization(CTR, decryptedFile + i * 16, W, 128);
      finish = clock();
      time += (double)(finish - start);
      for(int j = 0 ; j < 16 ; j++) 
         decryptedFile[i * 16 + j] ^= encryptedFile[i * 16 + j];
   }
   // 패딩 검증 및 파일 출력
   Padding = decryptedFile[fileSize - 1]; // 임의로 맨 마지막 한 바이트를 패딩으로 설정한다
   if(Padding > 0x10)   Padding = 0;      // 패딩 예외처리
   fwrite(decryptedFile, sizeof(u8), fileSize - decryptedFile[fileSize - 1], WFP); // 파일 사이즈에서 패딩 값 뺸 만큼 파일출력
   fclose(WFP);

   printf("[%d Blocks]\n", (int)(fileSize / 16));
   free(encryptedFile);
   free(decryptedFile);

   return time;
}

void RoundKeyGeneration128_Optimization(u8 *MK) {
   u32   T[16];
   u32   M[16];
   u8    RK[176];
   // 1바이트짜리 16개 키를 4개의 워드 4바이트 단위 전처리
   W[0] = u4byte_in(MK);      W[1] = u4byte_in(MK + 4);
   W[2] = u4byte_in(MK + 8);  W[3] = u4byte_in(MK + 12);

   // Encryption RoundKey 
   //T = RotWord(T); //T = SubWord(T); //T ^= Rcons[i];
   for(int i = 0 ; i < 10 ; i++) { 
      W[i * 4 + 4] = W[i * 4] ^ (SubWord(RotWord(W[4 * i + 3]))) ^ Rcons[i];
      W[i * 4 + 5] = W[i * 4 + 1] ^ W[i * 4 + 4];
      W[i * 4 + 6] = W[i * 4 + 2] ^ W[i * 4 + 5];
      W[i * 4 + 7] = W[i * 4 + 3] ^ W[i * 4 + 6];
   }

   for(int i = 0 ; i < 44 ; i++) Wd[i] = W[i];  // Encryption Key Schedule -> Decryption Key Schedule 
   // Decryption RoundKey
   
   for(int i = 0 ; i < 44 ; i++) u4byte_out(RK + i * 4, W[i]);
   for(int i = 1 ; i < 10 ; i++) { 
      // 키 스케쥴링에서 Inverse MixCol 해주는 부분
      for(int k = 0; k < 16; k += 4) {
         T[k]     = MULE(RK[i * 16 + k]) ^ MULB(RK[i * 16 + k + 1]) ^ MULD(RK[i * 16 + k + 2]) ^ MUL9(RK[i * 16 + k + 3]);
         T[k + 1] = MUL9(RK[i * 16 + k]) ^ MULE(RK[i * 16 + k + 1]) ^ MULB(RK[i * 16 + k + 2]) ^ MULD(RK[i * 16 + k + 3]);
         T[k + 2] = MULD(RK[i * 16 + k]) ^ MUL9(RK[i * 16 + k + 1]) ^ MULE(RK[i * 16 + k + 2]) ^ MULB(RK[i * 16 + k + 3]);
         T[k + 3] = MULB(RK[i * 16 + k]) ^ MULD(RK[i * 16 + k + 1]) ^ MUL9(RK[i * 16 + k + 2]) ^ MULE(RK[i * 16 + k + 3]);
      }
      for(int k = 0 ; k < 16 ; k++) RK[i * 16 + k] = T[k];
   }  // 출력된 값 모두 Decryption 전용 키로
   for(int i = 0; i < 44; i++)    Wd[i] = u4byte_in(RK + i * 4); // Decryption Key Schedule
}

void AES_KeySchedule_Optimization(u8 *MK, int keysize) {
   if(keysize == 128) RoundKeyGeneration128_Optimization(MK);
   //if(keysize == 192) RoundKeyGeneration192_Optimization(MK, RK);
   //if(keysize == 256) RoundKeyGeneration256_Optimization(MK, RK);
}

int main(int argc, char* argv[]) {
   
   u8       MK[32]      = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
   //u8      MK[32] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
   u8       PT[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
   u8       CT[16] = { 0x00, };
   u8       DE[16] = { 0x00, };
   const u8      CT_REF[16] = { 0x84, 0xD4, 0xC9, 0xC0, 0x8B, 0x4F, 0x48, 0x28, 0x61, 0xE3, 0xA9, 0xC6, 0xC3, 0x5B, 0xC4, 0xD9 };
   int      keysize     = 128;
   clock_t  start = 0, finish = 0, time = 0;


/*
   for(int i = 0 ; i < 44 ; i++) { printf("%08X ", W[i]); if(i % 4 == 3) puts(""); } puts("");
   for(int i = 0 ; i < 44 ; i++) { printf("%08X ", Wd[i]); if(i % 4 == 3) puts(""); } puts("");

   AES_KeySchedule_Optimization(MK, keysize);
   
   printf("[정보]\n");
   printf("Plaintext - "); for(int i = 0 ; i < 16 ; i++)    printf("0x%02X, ", PT[i]); puts("");
   printf("MasterKey - "); for(int i = 0 ; i < 16 ; i++)    printf("0x%02X, ", MK[i]); puts("");

   puts(""); printf("[암호화 전]\n");
   printf("Ciphertext - "); for(int i = 0 ; i < 16 ; i++)    printf("0x%02X, ", CT[i]); puts("");

   start = clock();
   AES_ENC_Optimization(PT, CT, W, keysize);
   finish = clock();

   puts(""); printf("[암호화 후]\n");
   printf("Ciphertext - "); for(int i = 0 ; i < 16 ; i++)    printf("0x%02X, ", CT[i]); puts("");
   printf("연산 소요 시간 - %lf초", (double)(finish - start) / CLOCKS_PER_SEC);
   
   puts("");
   start = clock();
   AES_DEC_Optimization(DE, CT, Wd, keysize);
   finish = clock();
   puts(""); printf("[복호화 후]\n");
   printf("Ciphertext - "); for(int i = 0 ; i < 16 ; i++)    printf("0x%02X, ", DE[i]); puts("");
   printf("연산 소요 시간 - %lf초", (double)(finish - start) / CLOCKS_PER_SEC);
   puts("\n");
   */
   
   if(argc != 4) { puts("Usage : ./Dec {Encrypted File} {New FileName} {Mode}"); return 0; }
   AES_KeySchedule_Optimization(MK, keysize);

   if((strncmp(argv[3], "CTR", 3) == 0) || (strncmp(argv[3], "ctr", 3) == 0)) {
      puts("CTR");
      time = AES_DEC_CTR(argv[1], argv[2], W);
   } /* ECB 모드를 구현하는 것은 과제가 아님
   else if((strncmp(argv[3], "ECB", 3) == 0) || (strncmp(argv[3], "ecb", 3) == 0)) {
      puts("ecb");   
      start = clock();
      AES_DEC_Optimization_ECB(argv[1], argv[2], W);
      finish = clock();
   } */
   else {
      puts("운영모드는 ECB, CTR 중 하나여야 합니다.");
      return 0;
   }

   printf("원본 파일\t%s\n해독 파일\t%s\n운영 모드\t%s\n연산 시간\t%f초\n", argv[1], argv[2], argv[3], (double)time / CLOCKS_PER_SEC);
   

   return 0;
}