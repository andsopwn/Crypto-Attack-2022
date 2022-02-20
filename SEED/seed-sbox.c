#include <stdio.h>


int main() {
    int sbox[256];
    int index;
    int val;

    for(int i = 0 ; i < 256 ; i++) {
        scanf("%d %d", &index, &val);
        sbox[index] = val;
    }

    for(int i = 0 ; i < 256 ; i++) {
        printf("%03d ", sbox[i]);
        if(i % 16 == 15) puts("");
    }
    for(int i = 0 ; i < 256 ; i++) {
        printf("0x%02x, ", sbox[i]);
        if(i % 16 == 15) puts("");
    }

}