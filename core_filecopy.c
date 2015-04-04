#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define BUF_SIZE 1024
/** simple copy routine **/
int main(int argc,char *argv[]){
    int i;
    if(argc!=3){
	printf("Usage:%s\t source target\n",argv[0]);
	exit(0);
    }
    for(i=1;i<argc;i++){
	printf("argv[%d]=%s\t",i,argv[i]);
    }
    printf("\n");

    int fd;
    char buffer[BUF_SIZE];
    fd=open(argv[1],O_RDONLY);
    if(fd==-1){
	printf("open %s failed.\n",argv[1]);
	exit(-1);
    }
    int fdt;
    fdt=open(argv[2],O_RDWR|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if(fdt==-1){
	printf("open %s failed.\n",argv[2]);
	exit(-1);
    }

    int n=-1;
    while((n=read(fd,buffer,BUF_SIZE))>0){
	write(fdt,buffer,n);	
    }

    close(fd);
    close(fdt);
   
    exit(0); 
}

