#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void sig_intr(int sig){
    printf("caught SIGINT \n");
}

int main(void){
    struct sigaction new_act, old_act;

    new_act.sa_handler = sig_intr;
    new_act.sa_flags = 0;
    sigemptyset(&new_act.sa_mask);

    if(sigaction(SIGINT, &new_act, &old_act) < 0){
        perror("sigaction error");
        exit(-1);
    }

    /*
     * Block SIGINT and save current signal mask.
     */
    sigset_t newmask, oldmask, pendmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
        perror("sigprocmask error\n");
        exit(-1);
    }
    
    sleep(3);
    
    raise(SIGINT); // send SIGINT to it's self.  this signal would be pended

    if(sigpending(&pendmask) < 0)
        perror("sigpending error");
    if(sigismember(&pendmask, SIGINT))
        printf("SIGINT pending\n");

    /*
     * Restore signal mask which unblocks SIGINT
     */
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("sigprocmask error");
    printf("SIGINT unblocked\n");
    sleep(2);

    return 0;
}
