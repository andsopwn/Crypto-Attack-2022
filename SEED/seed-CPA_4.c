#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "seed.h"
#define DIR "/Users/louxsoen/Documents/Univ/부채널연구/Traces/SEED/"
#define traceFN "trace.bin"
#define ptFN "plaintext.npy"
#define ctFN "ciphertext.npy"
#define startpt 0
#define endpt 6500

#define TraceLength 24000
#define TraceNum 2000

int main() {
	u8**	PT = NULL;
	//u8**	CT = NULL;
	u8		iv, hw_iv; 
    u8      iv0, iv1, iv2;
	u8		MK[16] = { 0x00, };
	u8   	ivv;
	double	maxCorr; 
	double* corr;	
	double	Sy;	  
	double	Syy, *Sxx;
	double	*Sxy;
	double  *Sx; 
	double	a, b, c;
	float** data;  
	int		key, maxkey;
	int		x, y;
	int		i, j, k;
    int     loc;
	char	buf[256];
	double	cur, all;
	FILE	*rfp, * wfp;
    u32 LK = 0x7c8f8c7e;
    u32 RK = 0xc737a22c;
	u32 KK = 0x58ed0491;
    u32 CC, DD;
    u32 L0, L1, R0, R1;
    u8  P0, P1, P2, P3;
    u32 carry = 0;
    u32 temp;

    u8 MT[16] = { 0x00, };

	sprintf(buf, "%s%s", DIR, traceFN);
	rfp = fopen(buf, "rb");
	if (rfp == NULL)
		printf("%s 파일 읽기 오류", traceFN);
	
	// DATA 동적 할당
	data = (float**)calloc(TraceNum, sizeof(float*));
	for (i = 0 ; i < TraceNum; i++)
		data[i] = (float*)calloc(TraceLength, sizeof(float));
	
	// DATA 
	for (i = 0; i < TraceNum; i++)
		fread(data[i], sizeof(float), TraceLength, rfp);
	fclose(rfp);

	sprintf(buf, "%s%s", DIR, ptFN);
	rfp = fopen(buf, "r");
	if (rfp == NULL)
		printf("%s 파일 읽기 오류", ptFN);

	PT = (u8**)calloc(TraceNum, sizeof(u8*));
	for (i = 0; i < TraceNum; i++)
		PT[i] = (u8*)calloc(16, sizeof(u8));
	
	for (i = 0; i < TraceNum; i++)
		fread(PT[i], sizeof(char), 16, rfp);
	/*
	sprintf(buf, "%s%s", DIR, ctFN);
	rfp = fopen(buf, "r");
	if (rfp == NULL)
		printf("%s 파일 읽기 오류", ctFN);

	CT = (u8**)calloc(TraceNum, sizeof(u8*));
	for (i = 0; i < TraceNum; i++)
		CT[i] = (u8*)calloc(16, sizeof(u8));
	
	for (i = 0; i < TraceNum; i++) {
		fread(CT[i], sizeof(char), 16, rfp);
	}
	*/

	corr = (double*)calloc(TraceLength, sizeof(double));
	Sx = (double*)calloc(TraceLength, sizeof(double));
	Sxx = (double*)calloc(TraceLength, sizeof(double));
	Sxy = (double*)calloc(TraceLength, sizeof(double));

	for (i = 0; i < TraceNum; i++)
	{
		for (j = startpt; j < endpt; j++) {
			Sx[j] += data[i][j];
			Sxx[j] += data[i][j] * data[i][j];
        }
	}
	for (int i = 3 ; i >= 0 ; i--)
	{
		maxCorr = 0;
		maxkey = 0;
		for (key = 0 ; key < 256; key++) {
			Sy = 0;
			Syy = 0;
			memset(Sxy, 0, sizeof(double)*TraceLength);
			for (j = 0 ; j < TraceNum; j++) {
                P0 = PT[j][ 8] ^ PT[j][12];
                P1 = PT[j][ 9] ^ PT[j][13];  
                P2 = PT[j][10] ^ PT[j][14];  
                P3 = PT[j][11] ^ PT[j][15];  

                DD = (P0 << 24) ^ (P1 << 16) ^ (P2 << 8) ^ P3 ^ RK ^ LK;
                DD = G_Function(DD);
                
                CC = (PT[j][8] << 24) ^ (PT[j][9] << 16) ^ (PT[j][10] << 8) ^ PT[j][11] ^ LK;

                CC = (u32)(CC + DD);
                CC = G_Function(CC);

                DD = (u32)(CC + DD);
                DD = G_Function(DD);                
                CC = (u32)(CC + DD);
                    // F FUNCTION EXIT

                MT[ 8] = PT[j][0] ^ (u8)(CC >> 24);
                MT[ 9] = PT[j][1] ^ (u8)(CC >> 16);
                MT[10] = PT[j][2] ^ (u8)(CC >>  8);
                MT[11] = PT[j][3] ^ (u8)(CC);
                MT[12] = PT[j][4] ^ (u8)(DD >> 24);
                MT[13] = PT[j][5] ^ (u8)(DD >> 16);
                MT[14] = PT[j][6] ^ (u8)(DD >>  8);
                MT[15] = PT[j][7] ^ (u8)(DD);


				DD = ((MT[8] ^ MT[12]) << 24) ^ ((MT[9] ^ MT[13]) << 16) ^ ((MT[10] ^ MT[14]) << 8) ^ (MT[11] ^ MT[15]) ^ KK;
				DD = G_Function(DD);

				if(i == 0) {
					iv  = (u8)(CC >> 24);
					ivv = (u8)(DD >> 24);
				}	else if(i == 1) {
					iv 	= (u8)(CC >> 16);
					ivv = (u8)(DD >> 16);
				}	else if(i == 2) {
					iv 	= (u8)(CC >> 8);
					ivv = (u8)(DD >> 8);
				}	else if(i == 3) {
					iv 	= (u8)(CC);
					ivv = (u8)(DD);
				}

				iv = MT[i + 8] ^ key;

				if(i == 3) {
                    iv = (iv + ivv) & 0xff;
                    carry = iv + ivv;
                } else {
                    if(carry > 0xff) {
                        iv = (iv + ivv + 1) & 0xff;
                        carry = iv + ivv + 1;
                    } else {
                        iv = (iv + ivv) & 0xff;
                        carry = iv + ivv;
                    }
                }
				if(i % 2 == 0)
                iv = S[1][iv];
                else
                iv = S[0][iv];

				hw_iv = 0;
				for (k = 0 ; k < 8 ; k++) hw_iv += ((iv >> k) & 1);
			
				Sy += hw_iv;
				Syy += hw_iv * hw_iv;
				
				for (k = startpt; k < endpt; k++)
					Sxy[k] += hw_iv * data[j][k];
			}

			for (j = startpt; j < endpt; j++) { 
				a = (double)TraceNum * Sxy[j] - Sx[j] * Sy;
				b = sqrt((double)TraceNum * Sxx[j] - Sx[j] * Sx[j]);
				c = sqrt((double)TraceNum * Syy - Sy * Sy);

				corr[j] = a / (b * c);
				if (fabs(corr[j]) > maxCorr) {
                    maxkey = key;
                    loc = j;
					maxCorr = fabs(corr[j]);
				}
			}
			fflush(stdout);
            if(key == 255)
			printf("\r  %02dth Block | KEY[%02X] CORR[%lf] loc[%d]                         \n", i, maxkey, maxCorr, loc);
			else    
			printf("\r%02dth Block : %.1lf%% CR[%lf] K[%02X] loc[%d]", i, ((double)key / 255) * 100, maxCorr, maxkey, loc);
			if(key == maxkey) {
				sprintf(buf, "%sct/%02dth_4.ct", DIR, i);
				wfp = fopen(buf, "wb");
				if (wfp == NULL)
					printf("블록 쓰기 에러\n");
				fwrite(corr, sizeof(double), TraceLength, wfp);
				fclose(wfp);
			}
        }
		MK[i] = maxkey;
	}
    puts("");

	free(PT);
	//free(CT);
	free(Sxy);
	free(Sx);
	free(Sxx);
	free(data);
	free(corr);
}