#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define handle_error_en(en,msg) \
    do{errno=en; perror(msg); exit(EXIT_FAILURE); }while(0);

static void sig_usr_handle(int); /* user define signal handler*/
static void sig_intr_handle(int); /* overwrite SIGINT default handler */

int main(void){
    if(signal(SIGUSR1,sig_usr_handle)==SIG_ERR)
	handle_error_en(1,"can't catch SIGUSR1");
    
    if(signal(SIGINT,sig_intr_handle)==SIG_ERR)
	handle_error_en(1,"can't catch SIGKILL");

    for(;;)
	pause(); /* Cause calling process to sleep until signal was delivered */
	
}

static void sig_usr_handle(int sig){
    if(sig==SIGUSR1)
	printf("received SIGUSR1\n");
    else
	printf("received signal %d\n",sig);
}

static void sig_intr_handle(int sig){
    if(sig==SIGINT){
	printf("received SIGINT\n");
	exit(EXIT_SUCCESS);
    }else{
	printf("received signal %d\n",sig);
    }
}
