#include<stdio.h>
#include<stdlib.h>
int main(){
    char buf[512];
    setbuf(stdin,buf);
    printf("hello,world!\n");
    return 0;
}

