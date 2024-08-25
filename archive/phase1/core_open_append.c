#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/** open a file and append a message to it.  **/
int main(){
    int fd=open("foo",O_RDWR|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if(fd==-1){
	printf("open file failed.\n");
	exit(-1);
    }
    
    char msg[]="\tthis is a message appended.";
    if(write(fd,msg,strlen(msg))==-1){
	printf("write failed.\n");
	exit(-1);
    }
    
    if(close(fd)==-1){
	printf("close file failed.\n");
	exit(-1);
    }
    exit(0);
}
