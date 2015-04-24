#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void print_sigset(sigset_t *set);

int main(void){
	sigset_t myset;
	sigemptyset(&myset);
	sigaddset(&myset,SIGINT);
    sigaddset(&myset,SIGUSR1);
	sigaddset(&myset,SIGQUIT);
	sigaddset(&myset,SIGABRT);

	printf("SIGINT=%d,SIGUSR1=%d,SIGQUIT=%d,SIGABRT=%d\n",SIGINT,SIGUSR1,SIGQUIT,SIGABRT);
	print_sigset(&myset);

	exit(0);
}

void print_sigset(sigset_t *set){
	int i;
	for(i=0;i<NSIG;i++){
		if(sigismember(set,i))
			printf("1");
		else
			printf("0");
	}
    putchar('\n');		
}
