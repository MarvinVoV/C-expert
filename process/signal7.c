#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

static void sig_chld(int);

int main(){
    pid_t pid;

    if(signal(SIGCHLD,sig_chld)==SIG_ERR)
	perror("signal error");
    if((pid=fork())<0){
	perror("fork error");
    }else if(pid==0){ /* child */
	sleep(2);
	_exit(0);
    }

    pause();
    exit(0);
}

static void sig_chld(int signo){
    pid_t pid;
    int status;

    printf("SIGCHLD received\n");

    if((pid=wait(&status))<0) /* fetch child status */
	perror("wait error");

    printf("pid=%ld,status=%d\n",(long)getpid(),status);
}
