#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void){
    char str[]="hello world";

    printf("sizeof=%ld,strlen=%ld\n",(long)sizeof(str),strlen(str));

    char c='\0';
    if(c){
	printf("cc\n");
    }else{
	printf("zz\n");
    }

    char *p;
    for(p=str;*p;p++);
    printf("len=%ld\n",p-str);
    exit(0);
}
