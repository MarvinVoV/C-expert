#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void my_alarm(int signo){
    printf("received signal %d \n",signo);
    alarm(1);
   
    /* If here cost five seconds */
   // time-consuming operation

    printf("after set alarm clock in signal handle\n");
}

int main(void){
    if(signal(SIGALRM,my_alarm)==SIG_ERR){
	fprintf(stderr,"can't signal\n");
	exit(EXIT_FAILURE);
    }
    alarm(1); /* send SIGALRM to calling process after 1 seconds */
    for(;;)
	pause();
}
