#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc,char *argv[]){
    pid_t pid;
    int status;

    if(argc!=2){
	fprintf(stderr,"usage: a.out <command>\n");
	exit(1);
    }

    if((pid=fork())<0){
	perror("fork failed\n");
	exit(1);
    }else if(pid==0){
	execl("/bin/sh","sh","-c",argv[1],(char *)0);
	_exit(127);
    }else{
	while(waitpid(pid,&status,0)<0){
	    if(errno!=EINTR){
		status=-1;
		break;
	    }
	}
    }

    printf("status=%d\n",status);
    exit(0);
}
