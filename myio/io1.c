#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* append a message to a file. If the file doesn't exist. Create it */

#define BUF 1023

int main(int argc,char *argv[]){
    int fd;
    const char *message="hello world\n";
    
    if(argc!=2){
	fprintf(stderr,"Usage:%s <filename>\n",argv[0]);
	exit(0);
    }

    fd=open(argv[1],O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
    if(fd==-1){
	perror("open file failed\n");
	exit(0);
    }
  
    ssize_t num=write(fd,message,strlen(message)); 
    if(num==-1){
	perror("write message failed.\n");
	exit(1);
    }

    fprintf(stdout,"append %ld bytes to %s\n",num,argv[1]);
    

    /* rewind file offset */
    lseek(fd,0,SEEK_SET);

    /*Read this file content and write to standard output */    
    
    printf("File content as follows:\n");
    char buf[BUF+1];
    memset(buf,'\0',BUF);
    int n;
    while((n=read(fd,buf,BUF))>0){
	write(STDOUT_FILENO,buf,n);
    }	
   
    close(fd);
    exit(0);
} 
    

    
