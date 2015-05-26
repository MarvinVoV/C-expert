#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void sig_chld(int signo){
	printf("received SIGCHLD %d \n",signo);
}

int main(){
	pid_t pid;
	int status;

	if(signal(SIGCHLD,sig_chld)==SIG_ERR){
		perror("signal error");
		exit(1);
	}

	if((pid=fork())<0){
		perror("fork error");
		exit(1);
	}else if(pid==0){  /* child */
		printf("child process pid %ld\n",(long)getpid());
		sleep(2);
		printf("child process finished\n");
	}else{
		printf("parent process pid %ld\n",(long)getpid());
		if(wait(&status)<0){
			perror("wait error");
			exit(1);
		}
		printf("status is %d\n",status);
	}

	exit(0);
}
