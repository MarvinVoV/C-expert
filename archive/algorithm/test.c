#include <stdio.h>
#include <stdlib.h>

void foo(int *p){
    *p = 10;
}

int main(void){
    int a = 2;
    foo(&a);
    printf("a = %d \n", a);
    
    exit(0);
}
