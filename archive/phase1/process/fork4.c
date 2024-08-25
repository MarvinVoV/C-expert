#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
    pid_t pid;
    if((pid=fork())<0){
	perror("fork error");
    }else if(pid==0){ /* child */
	sleep(2);
	printf("child process pid=%ld\n",(long)getpid());
    }else if(pid>0){ /* parent */
	printf("parent process pid=%ld\n",(long)getpid());
    }
    printf("main(): pid=%ld\n",(long)getpid());
    exit(0);
}
