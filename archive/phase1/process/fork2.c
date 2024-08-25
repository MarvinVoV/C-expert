#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(void){
    pid_t pid;
    int fd;

    fd=open("foo",O_RDWR);
    if(fd==-1){
	perror("open file error\n");
	exit(1);
    }

    pid=fork();
    if(pid==-1){
	perror("fork error\n");
	exit(1);
    }else if(pid==0){
	/* child process. write something */
	printf("child process fd=%d\n",fd);
	char buf[]="I am child process.\n";
	if(write(fd,buf,sizeof(buf))!=sizeof(buf)){
	    perror("child process write error\n");	
	    exit(0);
	}	    
	printf("child process write finished\n");
    }else{
	char buf[]="I am parent process.\n";
	if(write(fd,buf,sizeof(buf))!=sizeof(buf)){
	    perror("parent process write error\n");
	    exit(1);
	}
	printf("parent process write finished.\n");
	
    }
    int r;
    r=close(fd);
    printf("r=%d,pid=%ld\n",r,(long)getpid());
    exit(0);
}
