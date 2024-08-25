#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void){
    pid_t pid,w;

    if((pid=fork())<0){
	perror("fork");
	exit(1);
    }else if(pid==0){
	printf("child pid=%ld\n",(long)getpid());
	if(execl("/bin/ls","ls","-a","-l",(char *)0)<0){
	    perror("execl");
	    exit(1);
	}
	printf("after exec\n");
    }else{
	printf("parent pid=%ld\n",(long)getpid());
	w=wait(NULL);
	if(w<0){
	    perror("wait");
	    exit(1);
	}	    
	printf("parent process finished\n");

    }
    printf("done.\n");
    exit(0);
}
