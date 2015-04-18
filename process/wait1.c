#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
    pid_t pid,w;
    int status;

    pid=fork();
    if(pid==-1){
	perror("fork");
	exit(1);
    }
    if(pid==0){
	printf("child pid is %ld\n",(long)getpid());
	sleep(2);
	exit(1);
    }else{
	printf("parent pid is %ld\n",(long)getpid());
	
	w=wait(&status);
	if(w==-1){
	    perror("wait");
	    exit(1);
	}
	if(WIFEXITED(status)){
	    printf("exited.status=%d\n",WEXITSTATUS(status));
	}else if(WIFSIGNALED(status)){
	    printf("killed by signal %d\n",WTERMSIG(status));
	}else if(WIFSTOPPED(status)){
	    printf("stopped by signal %d\n",WSTOPSIG(status));
	}else if(WIFCONTINUED(status)){
	    printf("continued\n");
	}
    }
    exit(0);
}
