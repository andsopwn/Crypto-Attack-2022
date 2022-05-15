#include <stdio.h>
#include <time.h>
#include <stdlib.h>

float ReLU(float var) {
    if(var <= 0)    return 0;
    else            return var;
}

int main() {
    clock_t     start, end;
    float       timedelay[100] = { };
    float       resultDum;
    int         index       = 0;

    float       startPos    = -2.0;
    float       endPos      = 2.0;
    float       interval    = 0.1;

    unsigned char buf[256];
    FILE *fn;
    sprintf(buf, "time.txt");
    fn = fopen(buf, 'wb');
    
    

    for(float i = startPos ; i < endPos + 0.1 ; i += interval) {
        start = clock(); 
        resultDum = ReLU(i);
        end   = clock();

        timedelay[index] = end - start;
        index++;
    }
    for(int i = 0 ; i < 100 ; i++)
    printf("%2d | %lf\n", i, timedelay[index]);

}