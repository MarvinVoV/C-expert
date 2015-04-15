#include <stdio.h>
#include <stdlib.h>

int Max(int *,int *);

void showmax(int (*max)(int *,int *),int a,int b);

int main(void){
    int a=10,b=20;
    showmax(Max,a,b);
}

void showmax(int (*max)(int *,int *),int a,int b){
   int t=(*max)(&a,&b);
    printf("max=%d\n",t); 
}


int Max(int *a,int *b){
    return *a>*b?*a:*b;
}

