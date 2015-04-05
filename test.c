#include<stdio.h>
#include<stdlib.h>
int main(){
    char str[1024]; 
    sprintf(str,"hello world\n");
    printf("%*s%s\n",4,"",str);
    exit(0);
}
