#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define N 7

int main(void){
    /**
     * Add two bit array to another array.
     *
     * high in the left side, low in the right side.
     */
    int a[N] = {1, 0, 1, 1, 0, 0, 1};
    int b[N] = {0, 1, 1, 0, 1, 0, 0};
    int c[N + 1];
    int i, flag = 0; // carray flag
    bzero(c, sizeof(c));

    for( i = N; i >= 0; i--){
        c[i] = a[i - 1] + b[i - 1] + flag;
        if( c[i] >= 2){
            c[i] = c[i] % 2;
            flag = 1;
        }else{
            flag = 0;
        }
    }
    c[0] = flag;

    
    for(i = 0; i < N + 1; i++){
        printf("%d ", c[i]);
    }
    putchar('\n');

    exit(0);
}
