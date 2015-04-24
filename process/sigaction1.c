#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define error_handle(en,msg) \
	do{errno=en; perror(msg); exit(EXIT_FAILURE);}while(0)

void sig_handle(int signo);

int main(void){
	struct sigaction sig_act;
	sig_act.sa_handler=sig_handle;
	sigemptyset(&sig_act.sa_mask);
	sig_act.sa_flags=0;

	if(sigaction(SIGINT,&sig_act,NULL)<0)
		error_handle(1,"sigaction error");

	for(;;)
		pause();
	exit(0);
}


void sig_handle(int signo){
	psignal(signo,"recv a signal");
}
