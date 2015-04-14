#include<stdio.h>
#include<stdlib.h>
void main(){
    const char i='1';
    int r=atoi(&i);
    printf("%d %c\n",r,i);
}

