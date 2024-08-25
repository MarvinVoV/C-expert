#include<stdlib.h>
#include<stdio.h>
int main(){
    char buffer[1024];
    fgets(buffer,1024,stdin);
    printf("%s\n",buffer);
    exit(0);
}
