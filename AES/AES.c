#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;
typedef unsigned int u32;

u8 Sbox[256] =
{
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

/*
u8 invSbox[256] =
{

};*/

#define xtime(a) (((a)<<1)^((a)&0x80? 0x1b:0))
#define mul3(a) (xtime((a))^(a))
#define mul4(a) (xtime(xtime((a))))
#define mul8(a) (xtime(mul4((a))))
#define mul9(a) (mul8((a))^(a))
#define mulB(a) (mul8((a))^xtime((a))^(a))
#define mulD(a) (mul8((a))^mul4((a))^(a))
#define mulE(a) (mul8((a))^mul4((a))^xtime((a)))

u8 mul(u8 a, u8 b)
{
	u8 c = 0;
	c ^= (a & 0x01) ? b : 0;
	b = xtime(b);
	c ^= (a & 0x02) ? b : 0;
	b = xtime(b);
	c ^= (a & 0x04) ? b : 0;
	b = xtime(b);
	c ^= (a & 0x08) ? b : 0;
	b = xtime(b);
	c ^= (a & 0x10) ? b : 0;
	b = xtime(b);
	c ^= (a & 0x20) ? b : 0;
	b = xtime(b);
	c ^= (a & 0x40) ? b : 0;
	b = xtime(b);
	c ^= (a & 0x80) ? b : 0;
	return c;
}

u8 inv(u8 a)
{
	u8 r;
	r = a;
	r = mul(r, r);
	r = mul(r, a);
	r = mul(r, r);
	r = mul(r, a);
	r = mul(r, r);
	r = mul(r, a);
	r = mul(r, r);
	r = mul(r, a);
	r = mul(r, r);
	r = mul(r, a);
	r = mul(r, r);
	r = mul(r, a);
	r = mul(r, r);
	return r;
}

u8 GenSbox(u8 a)
{
	u8 r, temp;
	temp = inv(a);
	r = 0;
	if (temp & 0x01) r ^= 0x1f;
	if (temp & 0x02) r ^= 0x3e;
	if (temp & 0x04) r ^= 0x7c;
	if (temp & 0x08) r ^= 0xf8;
	if (temp & 0x10) r ^= 0xf1;
	if (temp & 0x20) r ^= 0xe3;
	if (temp & 0x40) r ^= 0xc7;
	if (temp & 0x80) r ^= 0x8f;
	r ^= 0x63;
	return r;
}

void AddRoundKey(u8 *temp, u8 *key)
{
	temp[0] ^= key[0];		temp[1] ^= key[1];		temp[2] ^= key[2];		temp[3] ^= key[3];
	temp[4] ^= key[4];      temp[5] ^= key[5];		temp[6] ^= key[6];		temp[7] ^= key[7];
	temp[8] ^= key[8];		temp[9] ^= key[9];		temp[10] ^= key[10];	temp[11] ^= key[11];
	temp[12] ^= key[12];	temp[13] ^= key[13];	temp[14] ^= key[14];	temp[15] ^= key[15];
}

void SubBytes(u8* temp)
{
	temp[0] = Sbox[temp[0]];	temp[1] = Sbox[temp[1]];	temp[2] = Sbox[temp[2]];	temp[3] = Sbox[temp[3]];
	temp[4] = Sbox[temp[4]];	temp[5] = Sbox[temp[5]];	temp[6] = Sbox[temp[6]];	temp[7] = Sbox[temp[7]];
	temp[8] = Sbox[temp[8]];	temp[9] = Sbox[temp[9]];	temp[10] = Sbox[temp[10]];	temp[11] = Sbox[temp[11]];
	temp[12] = Sbox[temp[12]];	temp[13] = Sbox[temp[13]];	temp[14] = Sbox[temp[14]];	temp[15] = Sbox[temp[15]];
}

void ShiftRows(u8* temp)
{
	u8 du;
	// 1 5 9 13 --> 5 9 13 1
	// 2 6 10 14 --> 10 14 2 6
	// 3 7 11 15 --> 15 3 7 11
	du = temp[ 1]; temp[ 1] = temp[ 5];	temp[ 5] = temp[ 9]; temp[ 9] = temp[13];	temp[13] = du;
	du = temp[ 2]; temp[ 2] = temp[10]; temp[10] = du; du = temp[ 6]; temp[ 6] = temp[14]; temp[14] = du;
	du = temp[15]; temp[15] = temp[11]; temp[11] = temp[ 7]; temp[ 7] = temp[ 3];   temp[ 3] = du;
}

void MixColumns(u8* temp)
{
	u8 r[16];
	u32 i;

	r[ 0] = temp[ 0];	r[ 1] = temp[ 1];	r[ 2] = temp[ 2];   r[ 3] = temp[ 3];
	r[ 4] = temp[ 4];	r[ 5] = temp[ 5];	r[ 6] = temp[ 6];   r[ 7] = temp[ 7];
	r[ 8] = temp[ 8];	r[ 9] = temp[ 9];	r[10] = temp[10];	r[11] = temp[11];
	r[12] = temp[12];	r[13] = temp[13];	r[14] = temp[14];	r[15] = temp[15];

	for (i = 0; i < 16; i += 4) {
		temp[i] = xtime(r[i]) ^ mul3(r[i + 1]) ^ r[i + 2] ^ r[i + 3];
		temp[i + 1] = r[i] ^ xtime(r[i + 1]) ^ mul3(r[i + 2]) ^ r[i + 3];
		temp[i + 2] = r[i] ^ r[i + 1] ^ xtime(r[i + 2]) ^ mul3(r[i + 3]);
		temp[i + 3] = mul3(r[i]) ^ r[i + 1] ^ r[i + 2] ^ xtime(r[i + 3]);
	}

}

u8 Rcons[14] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d };

void KeyGen128(u8* MK, u8* RK)
{
	u32 i;

	RK[0] = MK[0]; RK[1] = MK[1]; RK[2] = MK[2]; RK[3] = MK[3];
	RK[4] = MK[4]; RK[5] = MK[5]; RK[6] = MK[6]; RK[7] = MK[7];
	RK[8] = MK[8]; RK[9] = MK[9]; RK[10] = MK[10]; RK[11] = MK[11];
	RK[12] = MK[12]; RK[13] = MK[13]; RK[14] = MK[14]; RK[15] = MK[15];

	for (i = 0; i < 10; i++)
	{
		RK[16 * (i + 1)] = RK[16 * i] ^ Sbox[RK[16 * i + 13]] ^ Rcons[i];
		RK[16 * (i + 1) + 1] = RK[16 * i + 1] ^ Sbox[RK[16 * i + 14]];
		RK[16 * (i + 1) + 2] = RK[16 * i + 2] ^ Sbox[RK[16 * i + 15]];
		RK[16 * (i + 1) + 3] = RK[16 * i + 3] ^ Sbox[RK[16 * i + 12]];

		RK[16 * (i + 1) + 4] = RK[16 * (i + 1)] ^ RK[16 * i + 4];
		RK[16 * (i + 1) + 5] = RK[16 * (i + 1) + 1] ^ RK[16 * i + 5];
		RK[16 * (i + 1) + 6] = RK[16 * (i + 1) + 2] ^ RK[16 * i + 6];
		RK[16 * (i + 1) + 7] = RK[16 * (i + 1) + 3] ^ RK[16 * i + 7];

		RK[16 * (i + 1) + 8] = RK[16 * (i + 1) + 4] ^ RK[16 * i + 8];
		RK[16 * (i + 1) + 9] = RK[16 * (i + 1) + 5] ^ RK[16 * i + 9];
		RK[16 * (i + 1) + 10] = RK[16 * (i + 1) + 6] ^ RK[16 * i + 10];
		RK[16 * (i + 1) + 11] = RK[16 * (i + 1) + 7] ^ RK[16 * i + 11];

		RK[16 * (i + 1) + 12] = RK[16 * (i + 1) + 8] ^ RK[16 * i + 12];
		RK[16 * (i + 1) + 13] = RK[16 * (i + 1) + 9] ^ RK[16 * i + 13];
		RK[16 * (i + 1) + 14] = RK[16 * (i + 1) + 10] ^ RK[16 * i + 14];
		RK[16 * (i + 1) + 15] = RK[16 * (i + 1) + 11] ^ RK[16 * i + 15];
	}
}

void KeyGen192(u8* MK, u8* RK)
{

}

void KeyGen256(u8* MK, u8* RK)
{

}

void AES_KeySchedule(u8* MK, u8* RK, u32 keysize)
{
	if(keysize == 128)         KeyGen128(MK, RK);
	else if(keysize == 192)    KeyGen192(MK, RK);
	else if(keysize == 256)    KeyGen256(MK, RK);
}



u32 u4byte_in(u8 *x)
{
	return (x[0] << 24) | (x[1] << 16) | (x[2] << 8) | x[3];	//x[0] || x[1] || x[2] || x[3]
}

u32 Rcons32[14] = { 0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000, 0x6c000000, 0xd8000000, 0xab000000, 0x4d000000 };

#define RotWord(x) (((x) << 8) | ((x) >> 24))
#define SubWord(x) ((u32)Sbox[(u8)((x) >> 24)] << 24) | ((u32)Sbox[(u8)((x) >> 16)] << 16) | ((u32)Sbox[(u8)((x) >> 8)] << 8) | ((u32)Sbox[(u8)(x)])

void RoundkeyGeneration128_Optimization(u8* MK, u32* W)
{
	u32 i, T;

	W[0] = u4byte_in(MK);   //W[0] = MK[0] || MK[1] || MK[2] || MK[3]
	W[1] = u4byte_in(MK + 4);
	W[2] = u4byte_in(MK + 8);
	W[3] = u4byte_in(MK + 12);
	for (i = 0; i < 10; i++)
	{
		T = W[4 * i + 3];
		T = RotWord(T);
		T = SubWord(T);
		T ^= Rcons32[i];

		W[4 * i + 4] = W[4 * i] ^ T;
		W[4 * i + 5] = W[4 * i + 1] ^ W[4 * i + 4];
		W[4 * i + 6] = W[4 * i + 2] ^ W[4 * i + 5];
		W[4 * i + 7] = W[4 * i + 3] ^ W[4 * i + 6];
	}

}

void AES_ENC(u8* in, u8* out, u8* RK, u32 keysize)
{
	u32 Nr, i;
	u8 temp[16];

	temp[0] = in[0];	temp[1] = in[1];	temp[2] = in[2];	temp[3] = in[3];
	temp[4] = in[4];	temp[5] = in[5];	temp[6] = in[6];	temp[7] = in[7];
	temp[8] = in[8];	temp[9] = in[9];	temp[10] = in[10];	temp[11] = in[11];
	temp[12] = in[12];	temp[13] = in[13];	temp[14] = in[14];	temp[15] = in[15];

	Nr = keysize / 32 + 6;

	AddRoundKey(temp, RK);

	for (i = 1; i < Nr; i++)
	{
		SubBytes(temp);
		ShiftRows(temp);
		MixColumns(temp);
		AddRoundKey(temp, RK+16*i);
	}
	
	SubBytes(temp);
	ShiftRows(temp);
	AddRoundKey(temp, RK + 16 * Nr);

	out[0] = temp[0];	out[1] = temp[1];	out[2] = temp[2];	out[3] = temp[3];
	out[4] = temp[4];	out[5] = temp[5];	out[6] = temp[6];	out[7] = temp[7];
	out[8] = temp[8];	out[9] = temp[9];	out[10] = temp[10];	out[11] = temp[11];
	out[12] = temp[12];	out[13] = temp[13];	out[14] = temp[14];	out[15] = temp[15];
}

int main()
{
	u8      a, b;
	u8      MK[32] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
	//u8 MK[32] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
	u8      RK[240] = {0, };
	u32     W[60];
	u8      in[16] = { 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 };
	u8      out[16] = { 0, };
	u32     keysize, i;
	clock_t start, finish;
	
	keysize = 128;

	start = clock();    // start
	AES_KeySchedule(MK, RK, keysize);
	RoundkeyGeneration128_Optimization(MK, W);

    // Round Key
	//for(i = 0 ; i < 176 ; i++)   printf("0x%02x, ", RK[i]);  puts(""); 
    // Round Key DWORD
	//for(i = 0 ; i < 44 ; i++)  printf("0x%08x, ", W[i]); puts("");

	
    AES_ENC(in, out, RK, keysize);
	finish = clock();

	printf("Master Key : ");
	for(i = 0 ; i < 16 ; i++)   printf("0x%02x, ", MK[i]); puts("");
	printf("plaintext : ");
	for(i = 0 ; i < 16 ; i++) printf("0x%02x, ", in[i]); puts("");
	printf("Ciphertext : ");
	for(i = 0 ; i < 16 ; i++) printf("0x%02x, ", out[i]); puts("");

	printf("Computation Time : % f seconds \n", (double)(finish - start) / CLOCKS_PER_SEC);

	return 0;
}