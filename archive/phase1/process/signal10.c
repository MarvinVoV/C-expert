#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define error_handle(en,msg) \
	do{errno=en; perror(msg);exit(EXIT_FAILURE);}while(0)

void sig_handle(int signo);
void printsigset(sigset_t *set){
	int i;
	for(i=0;i<NSIG;i++)
		if(sigismember(set,i))
			putchar('1');
		else
			putchar('0');
	putchar('\n');
}

int main(void){
	sigset_t pset,bset; //pending sigset,block sigset
	sigemptyset(&pset);
	sigemptyset(&bset);

	sigaddset(&bset,SIGINT); // add SIGINT to signal set
	
	if(signal(SIGINT,sig_handle)==SIG_ERR)
		error_handle(1,"signal error");
	if(signal(SIGQUIT,sig_handle)==SIG_ERR)
		error_handle(1,"signal error");

	sigprocmask(SIG_BLOCK,&bset,NULL); // add bset to block sigal set 
	for(;;){
		sigpending(&pset);
		printsigset(&pset);
		sleep(1);
	}
	exit(EXIT_SUCCESS);
}

void sig_handle(int signo){
	if(signo==SIGINT){
		printf("recv a signal %d\n",signo);
	}else if(signo==SIGQUIT){
		sigset_t uset;
		sigemptyset(&uset);
		sigaddset(&uset,SIGINT);
		sigprocmask(SIG_UNBLOCK,&uset,NULL);
	}
}
