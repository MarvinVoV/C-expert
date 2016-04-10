#include <stdio.h>

int main(void){

    int a[5] = {1,2,3,4,5};
    int *p;
    p = a;
    printf("a[0]=%d\n", *p);
    printf("a[1]=%d\n", *(p + 1));

    return 0;
}
