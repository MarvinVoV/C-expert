#include "signal.h"

void sig_handle(int signo){
	if(signo==SIGINT){
		printf("recv SIGINT signal %d\n",signo);
		sleep(5);
	}
	if(signo==SIGQUIT)
		printf("recv SIGQUIT signal %d\n",signo);
}

int main(void){
	struct sigaction act;
	act.sa_handler=sig_handle;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGUSR1);
	sigaddset(&act.sa_mask,SIGQUIT);
	act.sa_flags=0;

	if(sigaction(SIGINT,&act,NULL)<0)
		error_handle(1,"sigaction error");
	struct sigaction act2;
	act2.sa_handler=sig_handle;
	sigemptyset(&act2.sa_mask);
	act2.sa_flags=0;
	if(sigaction(SIGQUIT,&act2,NULL)<0)
		error_handle(1,"sigaction error");

	int i;
	sigset_t pset;
	sigemptyset(&pset);
	sigpending(&pset);
	for(;;){
		pause();
		for(i=1;i<NSIG;i++){
			if(sigismember(&pset,i))
				psignal(i,"pending signal");
		}
	}
	exit(0);
}
