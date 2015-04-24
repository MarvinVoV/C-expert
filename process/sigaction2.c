#include "signal.h"
typedef void (*sig_handler)(int);

void handle(int signo);

sig_handler my_signal(int signo,sig_handler handler);

int main(void){
	my_signal(SIGINT,handle);
	for(;;)
		pause();
	exit(0);
}

void handle(int signo){
	psignal(signo,"recv a signal");
}

sig_handler my_signal(int signo,sig_handler handler){
	struct sigaction act;
	struct sigaction oldact;
	act.sa_handler=handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;

	if(sigaction(signo,&act,&oldact)<0)
		error_handle(1,"sigaction error");
	return oldact.sa_handler;
}
