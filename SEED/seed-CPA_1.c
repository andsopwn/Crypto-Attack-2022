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
#define endpt 5000

#define TraceLength 24000
#define TraceNum 2000

int main() {
	u8**	PT = NULL;
	//u8**	CT = NULL;
	u8		iv, hw_iv; 
	u8		MK[16] = { 0x00, };
	int 	val;
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
	char	buf[256];	 
	double	cur, all;
	FILE	*rfp, * wfp;

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

	for (int i = 0; i < 4 ; i++)
	{
		maxCorr = 0;
		maxkey = 0;
		for (key = 0 ; key < 256; key++) {
			Sy = 0;
			Syy = 0;
			memset(Sxy, 0, sizeof(double)*TraceLength);
			for (j = 0; j < TraceNum; j++) { // hw 구하는 곳
                //iv = PT[j][i]; // 평문 cpa
                iv = PT[j][i + 8] ^ PT[j][i + 12] ^ key; // key = k1 + k0

                if(i % 2 == 0)
                iv = S[1][iv];
                else
                iv = S[0][iv];
				hw_iv = 0;
				for (k = 0; k < 8; k++) hw_iv += ((iv >> k) & 1);
			
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
					maxCorr = fabs(corr[j]);
                    val = j;
				}
			}
			fflush(stdout);
            if(key == 255)
			printf("\r  %02dth Block | KEY[%02X] CORR[%lf] POS[%d]                          \n", i, maxkey, maxCorr, val);
			else
			printf("\r%02dth Block : %.1lf%% CR[%lf] K[%02X] POS[%d]", i, ((double)key / 255) * 100, maxCorr, maxkey, val);
            
			if(key == maxkey) {
				sprintf(buf, "%sct/%02dth_1.ct", DIR, i);
				wfp = fopen(buf, "wb");
				if (wfp == NULL)
					printf("블록 쓰기 에러\n");
				fwrite(corr, sizeof(double), TraceLength, wfp);
				fclose(wfp);
			}
        }
		MK[i] = maxkey;
	}
	printf("\n\n");

	printf("MASTER KEY : 0x");
	for (int i = 0; i < 16; i++)	printf("%02X", MK[i]);
	puts("");

	free(PT);
	//free(CT);
	free(Sxy);
	free(Sx);
	free(Sxx);
	free(data);
	free(corr);
}