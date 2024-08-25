#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/** create a file and write a message to it.  **/
int main(){
    int fd=open("foo",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if(fd==-1){
	printf("create file failed.\n");
	exit(-1);
    }
    
    char msg[]="hello world";
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
