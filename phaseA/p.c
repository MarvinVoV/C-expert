#include <stdio.h>

int main(void){
    int x = 1, y = 2;
    int *p;
    p = &x;
    printf("x is %d\n", *p);
    ++*p;
    printf("x is %d\n", x);
    (*p)++;
    printf("x is %d\n", x);

    return 0;
}
