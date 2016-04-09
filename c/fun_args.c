#include <stdio.h>

int add(int a, int b){
    return a + b;
}

int multiply(a, b){
    return a * b;
}

void callback(int (*fun)(int,int), int a, int b){
   int r = fun(a, b);
   printf("r is %d\n", r);
}

int main(void){
    callback(add, 1, 2);
    callback(multiply, 3, 4);
    return 0;
}
