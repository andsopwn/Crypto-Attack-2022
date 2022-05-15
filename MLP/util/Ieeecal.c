#include <stdio.h>
#include <math.h>

typedef union   u_fltp
{
    float      storage;    // 직접 값을 받아오는 변수
    struct {
        unsigned long int mant :23;
        unsigned int  expt :8;
        unsigned int  sign :1;
    }           bit;
}               fltp;

int main()
{   
    fltp aa;

    float Var = -1.6702;
    unsigned char* VarToByte = (unsigned char*)&Var;
    unsigned char BinaryStringArray[33];

    int* test = (int*)&Var;

    for(int i = 0 ; i < 32 ; i++)
    printf("%c", test[i]);
    puts("");

    unsigned char bExpo = 0x00;
    unsigned int  bMant = 0x00;

    for(int i = 7 ; i >= 0 ; i--) {
        BinaryStringArray[i]      = VarToByte[3] % 2 + '0';
        BinaryStringArray[i + 8]  = VarToByte[2] % 2 + '0';
        BinaryStringArray[i + 16] = VarToByte[1] % 2 + '0';
        BinaryStringArray[i + 24] = VarToByte[0] % 2 + '0';

        VarToByte[3] /=2;
        VarToByte[2] /=2;
        VarToByte[1] /=2;
        VarToByte[0] /=2;
    }
    
    for(int i = 0 ; i < 32 ; i++)
    BinaryStringArray[i] -= 48;

    for(int i = 0 ; i < 32 ; i++)
    printf("%d", BinaryStringArray[i]);
    puts("");

    for(int i = 0 ; i < 8 ; i++) {
        if(BinaryStringArray[i + 1] == 1) bExpo++;
        if(i != 7) bExpo <<= 1;
    }
    for(int i = 0 ; i < 23 ; i++) {
        if(BinaryStringArray[i + 9] == 1) bMant++;
        if(i != 22) bMant <<= 1;
    }
    printf("%d\n", bExpo);
    printf("%d\n", bMant);
}

