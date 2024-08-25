#include <stdio.h>
#include <stdlib.h>

int main(void){
    int x = 7;
    int y = 2;
    float z = x / y;
    printf("z = %f\n", z);
    float d = (float)x / y;
    printf("d = %f\n", d);
    return 0;
}

