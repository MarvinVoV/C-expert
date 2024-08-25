#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sig_chld(int sig){
	printf("Catch SIGCHLD\n");
}

int main(void){
	pid_t pid;
	struct sigaction sa;

	sa.sa_handler = sig_chld;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGCHLD, &sa, NULL) < 0){
		perror("sigaction error");
		exit(-1);
	}
	
	if((pid = fork()) < 0){
		perror("fork error");
		exit(-1);
	}else if(pid == 0){ /* child */
		printf("child process done.\n");
	}else{ /* parent */
		sleep(2);
		printf("parent process done\n");
	}

	exit(0);
}
