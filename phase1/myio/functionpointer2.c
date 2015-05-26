#include <stdio.h>
#include <stdlib.h>

typedef int Fun(int,int);
Fun max;

void show(Fun *fun,int,int);
int max(int,int);

int main(void){
    int a=10,b=20;
    show(max,a,b);
}

int max(int a,int b){
    return a>b?a:b;
}

void show(Fun *fun,int a,int b){
    printf("max=%d\n",fun(a,b));
}


