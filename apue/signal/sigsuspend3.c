#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

/* The correct way to protect a critical region of code from a specific signal */

static void sig_int(int sig){
	printf("receive interrupt signal\n");
}

int main(void){

	sigset_t newmask, oldmask;
	struct sigaction sa;
	printf("program start:\n");


	/* set interrupt signal handler */
	sa.sa_handler = sig_int;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
    if(sigaction(SIGINT, &sa, NULL) < 0){
		perror("sigaction error");
		exit(-1);
	}
	
	/* Block SIGINT and save current signal mask */
	sigemptyset(&oldmask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
		perror("sigprocmask error");
		exit(-1);
	}

	/* Critical region of code */
	printf("in critical region:\n");
	raise(SIGINT);
	printf("outof critical region\n");
	
	
	if(sigsuspend(&oldmask) != -1){
		perror("sigsuspend error");
		exit(-1);
	}
	printf("after return from sigsuspend\n");

	/* Reset signal mask which unblocks SIGINT */
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
		perror("sigprocmask error");
		exit(-1);
	}
	printf("restore sigmask and raise SIGINT\n");

	printf("program exit.\n");
	exit(0);
}
