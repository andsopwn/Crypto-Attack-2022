#include <stdio.h>

int main() {
	unsigned char a = 255;

    printf("%d\n", a << 1); 
    
    a <<= 1;
	printf("%d\n", a);
}

