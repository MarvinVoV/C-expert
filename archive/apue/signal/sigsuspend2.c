#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

/* use sigsuspend to wait for a signal handler to set a global variable */

volatile sig_atomic_t quitflag; /* set nonzero by signal handler */

static void sig_int(int sig){
	if(sig == SIGINT)
		printf("\ninterrupt\n");
	else if(sig == SIGQUIT)
		quitflag = 1; /* set flag for main loop */
}

int main(void){
	sigset_t newmask, oldmask, zeromask;

	struct sigaction sa_int, sa_quit;
	sa_int.sa_handler = sig_int;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	if(sigaction(SIGINT, &sa_int, NULL) < 0){
		perror("sigaction error");
		exit(-1);
	}
    sa_quit.sa_handler = sig_int;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	if(sigaction(SIGQUIT, &sa_quit, NULL) < 0){
		perror("sigaction error");
		exit(-1);
	}	

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
		perror("sigprocmask error");
		exit(-1);
	}
	while(quitflag == 0)
		sigsuspend(&zeromask);
	
	quitflag = 0;

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
		perror("sigprocmask error");
		exit(-1);
	}
	exit(0);
}
