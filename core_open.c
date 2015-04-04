#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

#define BUF_SIZE 1024

/** Open a file, read it and write it's content to the standard output **/
int main(){
    int fd=open("/etc/hosts",O_RDONLY);
    if(fd==-1){
	printf("open file failed.\n");
	exit(-1);
    }
    
    char buffer[BUF_SIZE];
    int n=-1;
    while((n=read(fd,buffer,BUF_SIZE))!=0){
	write(1,buffer,n);
    }
    
    if(close(fd)!=0){
	printf("cann't close file.\n");
	exit(-1);
    }

    exit(0);
}
