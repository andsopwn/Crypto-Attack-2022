#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef unsigned char u8;
#define Aligned "/Users/louxsoen/Documents/Univ/부채널연구/파형정렬/AlignedAES.traces"
#define PlaintextFN "/Users/louxsoen/Documents/Univ/부채널연구/파형정렬/plaintext.txt"
#define CiphertextFN "/Users/louxsoen/Documents/Univ/부채널연구/파형정렬/ciphertext.txt"
#define ddir "/Users/louxsoen/Documents/Univ/부채널연구/파형정렬/"
#define startpoint 22551
#define endpoint 31050
static u8 SBOX[256] = 
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

void CPA()
{
    u8      **plaintext = NULL;     // 2000 * 16 bytes의 평문을 2000 * 16 크기의 배열 저장
    u8      x, y;                   // x : 16바이트 HEX 앞 부분, y : 16바이트 HEX 뒷 부분
    u8      iv, hw_iv;              // 전력소비량, 전력소비량의 해밍웨이트
    float   **data;                 // 정렬된 파형을 한번에 메모리에 올려서 작업
    char    temp[34];               // Plaintext 파일을 34바이트씩 읽어올 변수
    double  *Sx, *Sxx;              // Sx : 전력 값들의 합, 전력 값 제곱들의 합
    double  *Sxy, *corrT;           // Sxy : 해밍웨이트와 전력값을 곱한 값, corrT : 상관계수 값
    double  a, b, c, max;           // (a, b, c) : 상관계수 식 분배, max : 키가 0~255까지 돌 때 상관계수의 최대 값
    double  Sy, Syy;                // Sy : 해밍웨이트를 더한 값, Syy : 해밍웨이트의 제곱을 더한 값
    char    buf[256];               // 파일 입출력에 덮어씌울 임시 버퍼
    int     TraceLength, TraceNum;  // TraceLenghth : 파동의 길이, TraceNum : 파동의 개수
    int     key, maxkey;            // key : 0~255까지 대입할 변수, maxkey : 상관계수가 최대 값일 때 KEY 값
    int     i, j, k;                // 반복문에 쓰이는 조합, j k는 이중 배열 포인터에 쓰임
    FILE    *rfp, *wfp;             // rfp : 읽어 올 파일의 변수, wfp : 덮어씌울 파일의 변수

    // 읽을 파일
    sprintf(buf, "%s" , Aligned); // 해당 경로에 대한 문자열이 버퍼에 들어옴
    rfp = fopen(buf, "rb"); 
    if(rfp == NULL)
        printf("%s 파형을 읽지 못 했습니다.\n", Aligned); 
    
    // 헤더 정보를 읽고 TraceLength, TraceNum에 넣기
    fread(&TraceLength, sizeof(int), 1, rfp);
    fread(&TraceNum, sizeof(int), 1, rfp);
    
    // 데이터 이중 배열 동적할당
    data = (float **)calloc(TraceNum, sizeof(float*));
    for(i = 0 ; i < TraceNum ; i++)
    {
        data[i] = (float*)calloc(TraceLength, sizeof(float));
    }
    // 데이터 배열 읽기
    for(i = 0 ; i < TraceNum ; i++)
    {
        fread(data[i], sizeof(float), TraceLength, rfp);
    }
    fclose(rfp);


    // plaintext.txt는 아스키코드 형태로 되어있는데 글자를 읽고 숫자로 변환해서 저장해야함
    sprintf(buf, "%s", PlaintextFN); // 해당 경로에 대한 문자열이 버퍼에 들어옴
    rfp = fopen(buf, "r"); 
    if(rfp == NULL)
        printf("%s 파일을 읽지 못 했습니다.\n", PlaintextFN); 
    // plaintext 받아오기
    plaintext = (u8**)calloc(TraceNum, sizeof(u8*));
    for(i = 0 ; i < TraceNum ; i++)
    {
        plaintext[i] = (u8*)calloc(16, sizeof(u8));
    }
    // temp에 32 + 2바이트씩 받아오기 (OD OA까지)
    for(i = 0 ; i < TraceNum ; i++)
    {
        fread(temp, sizeof(char), 34, rfp); // 16바이트로 바꿔서 Plaintext[i]에 저장 필요
        for(j = 0 ; j < 16 ; j++)
        {
            x = temp[2 * j];            // 0xxy, 데이터 앞자리
            y = temp[2 * j + 1];        // 0xxy, 데이터 뒷자리
            // temp 배열을 x, y로 가져와서 아스키코드에 있는 숫자를 16진수로 반환
            
            // '0'~'9', 'A'~'F', 'a'~'f'
            if(x >= 'A' && x <= 'Z') x = x - 'A' + 10; 
            else if(x >= 'a' && x <= 'z') x = x - 'a' + 10;
            else if(x >= '0' && x <= '9') x -= '0';
            // '0'~'9', 'A'~'F', 'a'~'f'
            if(y >= 'A' && y <= 'Z') y = y - 'A' + 10; 
            else if(y >= 'a' && y <= 'z') y = y - 'a' + 10;
            else if(y >= '0' && y <= '9') y -= '0';

            plaintext[i][j] = x * 16 + y;
        }
    }

    Sx = (double*)calloc(TraceLength, sizeof(double));
    Sxx = (double*)calloc(TraceLength, sizeof(double));
    Sxy = (double*)calloc(TraceLength, sizeof(double));
    corrT = (double*)calloc(TraceLength, sizeof(double));
    
    for(i = 0 ; i < TraceNum ; i++)
    {
        for(j = startpoint ; j < endpoint ; j++) // 범위지정
        {
            Sx[j] += data[i][j]; // 전력 값들의 합
            Sxx[j] += data[i][j] * data[i][j]; // 전력 값들의 제곱의 합
        }
    }
    // 16바이트에 키 0부터 256까지 대입해서 해밍웨이트를 구하고 대조
    for(i = 0 ; i < 16 ; i++)
    {
        max = 0; // 상관계수의 최대값
        maxkey = 0; // max값을 갖는 키
        for(key = 0; key < 256 ; key++)
        {
            Sy = 0;
            Syy = 0;
            memset(Sxy, 0, sizeof(double)*TraceLength); // 0으로 다 세팅
            for(j = 0 ; j < TraceNum ; j++)
            {
                iv = SBOX[plaintext[j][i]^key]; // plaintext와 우리가 예상하는 키를 sbox에 넣었을 때
                hw_iv = 0; // iv의 해밍웨이트
                for(k = 0 ; k < 8 ; k++)    hw_iv += ((iv >> k) & 1);
                // iv 값을 1부터 8자리까지 쉬프트를 해보면서 1와 and 연산을 했을 때, 1이 반환되는 숫자만 더한다. 그것이 해밍웨이트
                Sy += hw_iv; // 해밍웨이트를 더함
                Syy += hw_iv * hw_iv; // 해밍웨이트를 제곱해서 더함
                //printf("%lf\n",Sy);
                for(k = startpoint ; k < endpoint ; k++)
                {
                    Sxy[k] += hw_iv * data[j][k];
                }
            }

            for(k = startpoint ; k < endpoint ; k++)
            {
                a = ((double)TraceNum * Sxy[k] - Sx[k] * Sy);
                b = sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]));
                c = sqrt(((double)TraceNum * Syy - Sy * Sy));
                corrT[k] = a / (b * c);
                // corrT가 max보다 클 경우 maxkey는 key, max는 상관계수 최대값
                if(fabs(corrT[k]) > max) 
                {
                    maxkey = key;
                    max = fabs(corrT[k]);
                }
            }

            sprintf(buf, "%scorrtrace/%02dth_block_%02d.corrtrace", ddir, i, key);
            wfp = fopen(buf, "wb");
            if(wfp == NULL)
            {
                printf("블록 쓰기 에러\n");
            }
            fwrite(corrT, sizeof(double), TraceLength, wfp);
            fclose(wfp);
            fflush(stdout);
        }
        printf("%02dth_block : maxkey(%02x), maxcorr(%lf)\n", i, maxkey, max);

    }
    free(Sx);
    free(Sxx);
    free(Sxy);
    free(corrT);
    free(data);
    free(plaintext);
}

int main()  
{
    CPA();
}