#include <stdio.h>

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

int main(int argc, char** argv)
{   
    float Var = -7.1598176210440337;
    
    printf("%d\n", FloatingPointHW(Var));
    
    /*
    unsigned char* VarToByte = (unsigned char*)&Var;
    unsigned char BinaryStringArray[33];
    int i, hw = 0;
    
    for(int i = 0 ; i < 4 ; i++) printf("%02X ", VarToByte[i]);

    for(int i = 0 ; i < 8 ; i++)
    {
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
    printf("\n\n%d\n", hw);
    */
}

