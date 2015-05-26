#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUF_SIZE 128

/** Copy the first 128 bytes of the standard input to the standard output **/
int main(){
    char buffer[BUF_SIZE];
    int nread;

    nread=read(0,buffer,BUF_SIZE);
    if(nread==-1)
	printf("A read error has occurred\n");

    if(write(1,buffer,nread)!=nread)
	printf("A write error has occurred\n");

    exit(0);
}
