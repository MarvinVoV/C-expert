#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>

// version1:reliable signal will be delivered more time
//#define MYSIGNAL SIGRTMIN+5
// version2:unreliable signal will be delivered only once
#define MYSIGNAL SIGTERM

void sig_handle(int signo){
	psignal(signo,"catch a signal");
}

int main(void){
	sigset_t bset,pset;
	int sig,flag;

	signal(MYSIGNAL,sig_handle);

	// block this signal
	sigemptyset(&bset);
	sigaddset(&bset,MYSIGNAL);
	printf("block signal\n");
	sigprocmask(SIG_BLOCK,&bset,NULL);

	// send twice signal
	int i;
	for(i=0;i<2;i++){
		printf("---> send a signal ---->\n");
		kill(getpid(),MYSIGNAL);
	}
	// check current pending signal
	flag=0;
	sigpending(&pset);
	for(sig=1;sig<NSIG;sig++){
		if(sigismember(&pset,sig)){
			flag=1;
			psignal(sig,"this signal is pending");
		}
	}
	if(flag==0)
		printf("no pending signal\n");

   // unblock this signal
	printf("unblock signal\n");
	sigprocmask(SIG_UNBLOCK,&bset,NULL);

	// check pending signal again
	flag=0;
	sigpending(&pset);
	for(sig=1;sig<NSIG;sig++){
		if(sigismember(&pset,sig)){
			flag=1;
			psignal(sig,"this signal is pending");
		}
	}
	if(flag==0)
		printf("no pending signal\n");

	exit(0);
}

