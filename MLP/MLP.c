#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef unsigned char 	u8;
typedef unsigned int	u32;
#define DIR 	"/Users/louxsoen/Documents/Univ/SCA_Experiment/MLP/"
#define traceFN "aligned_220213.bin"
#define inputFN "newinput_220213.bin"

#define TraceLength 24000
#define TraceNum 	10000

#define startpt    	0
#define endpt      	20000

#define bias		127

int FloatingPointHW(float Var) {
    unsigned char* VarToByte = (unsigned char*)&Var;
    unsigned char BinaryStringArray[33];
    int hw = 0;

    for(int i = 0 ; i < 8 ; i++) {
        BinaryStringArray[i]      = VarToByte[3];
        BinaryStringArray[i + 8]  = VarToByte[2];
        BinaryStringArray[i + 16] = VarToByte[1];
        BinaryStringArray[i + 24] = VarToByte[0];

        VarToByte[3] /= 2;
        VarToByte[2] /= 2;
        VarToByte[1] /= 2;
        VarToByte[0] /= 2;
    }
    for(int i = 0 ; i < 32 ; i++) hw += BinaryStringArray[i] & 1;
    
    return hw;
}

int main() {
    float       **data;
    float       **node;
    char        buf[256];
    int         i, j, k;
    FILE        *rfp, *wfp;

/* 	==============================
        stack to heak zone
	============================== 	*/
    sprintf(buf, "%s%s", DIR, traceFN);     rfp = fopen(buf, "rb"); 
    if(rfp == NULL)     printf("%s ERR\n", traceFN);

    data = (float**)calloc(TraceNum, sizeof(float*));
    for(i = 0 ; i < TraceNum ; i++) 
        data[i] = (float*)calloc(TraceLength, sizeof(float));

    for(i = 0 ; i < TraceNum ; i++)
        fread(data[i], sizeof(float), TraceLength, rfp);
    fclose(rfp);

    sprintf(buf, "%s%s", DIR, inputFN);     rfp = fopen(buf, "r");
    if(rfp == NULL)     printf("%s ERR\n", inputFN);
    node = (float**)calloc(TraceNum, sizeof(float*));
    for(i = 0 ; i < TraceNum ; i++)
        node[i] = (float*)calloc(4, sizeof(float));
    
    for(i = 0 ; i < TraceNum ; i++)
        fread(node[i], sizeof(float), 4, rfp);

/* 	==============================
			NODE TEST	
	============================== 	*/
    printf("%.13lf\n", node[0][0]);
    printf("%.13lf\n", node[0][1]);
    printf("%.13lf\n", node[0][2]);
	puts("");

	printf("%.13lf\n", node[1][0]);
    printf("%.13lf\n", node[1][1]);
    printf("%.13lf\n", node[1][2]);
	puts("");

	printf("%.13lf\n", node[2][0]);
    printf("%.13lf\n", node[2][1]);
    printf("%.13lf\n", node[2][2]);


    double *corr = (double*)calloc(TraceLength, sizeof(double));
    double *Sx = (double*)calloc(TraceLength, sizeof(double));
    double *Sxx = (double*)calloc(TraceLength, sizeof(double));
    double *Sxy = (double*)calloc(TraceLength, sizeof(double));

    double      Sy, Syy;
    double      maxCorr;
    double      a, b, c;
    float       weight, maxweight;
    int         loc, hw_iv;
    double      iv, ivv;

    for(i = 0; i < TraceNum; i++) {
		for(j = startpt; j < endpt; j++) {
			Sx[j] += data[i][j];
			Sxx[j] += data[i][j] * data[i][j];
        }
	}

	for (int i = 0; i < 1 ; i++)
	{
		maxCorr = 0;
		maxweight = 0;
		
		for (weight = 0 ; weight < 3 ; weight += 0.01) {

			Sy = 0;
			Syy = 0;
			memset(Sxy, 0, sizeof(double)*TraceLength);
			for (j = 0 ; j < TraceNum; j++) {
				iv = node[j][0] * weight;
				hw_iv = FloatingPointHW(iv);
			
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
					maxweight = weight;
					maxCorr = fabs(corr[j]);
				}

			fflush(stdout);
            if(weight == 255)
			printf("\r  %02dth Block | KEY[%02X] CORR[%lf] loc[%d]                         \n", i, maxweight, maxCorr, loc);
			else    
			printf("\r%02dth Block : %.1lf%% CR[%lf] K[%02X] loc[%d]", i, ((double)weight / 255) * 100, maxCorr, maxweight, loc);
			if(weight == maxweight) {
				sprintf(buf, "%sct/%02dth_4.ct", DIR, i);
				wfp = fopen(buf, "wb");

				if (wfp == NULL)
					printf("블록 쓰기 에러\n");
				fwrite(corr, sizeof(double), TraceLength, wfp);
				fclose(wfp);
			}
        } // for get correlation
		//MK[i] = maxweight;
	} // for weight 0 - 255 
    //puts("");

/*  
        memory allocated free zone
*/

    for(int i = 0 ; i < TraceNum ; i++)
    free(data[i]);  free(data);

    for(int i = 0 ; i < TraceNum ; i++)
    free(node[i]);  free(node);

    free(Sxy);
	free(Sx);
	free(Sxx);
	free(corr);
	}
}