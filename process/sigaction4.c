#include "signal.h"

void sig_handler(int signo,siginfo_t *info,void *ctx){
	printf("receive data from siqueue by info->si_int is %d\n",info->si_int);
	printf("receive data from siqueue by info->si_value.sival_int is %d\n",info->si_value.sival_int);
}

int main(void){
	struct sigaction act;
	act.sa_sigaction=sig_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=SA_SIGINFO; //open info bit 
	if(sigaction(SIGINT,&act,NULL)<0)
		error_handle(1,"sigaction error");
	sleep(2);
	union sigval mysigval;
	mysigval.sival_int=10;
	//send action
	if(sigqueue(getpid(),SIGINT,mysigval)==-1)
		error_handle(1,"sigqueue error");

	exit(0);
}
