#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sig_handler(int signo){
    switch(signo){
        case SIGTSTP:
            printf("TSTP\n");
            fflush(stdout);
            break;
    }
}

int main(void){
    struct sigaction new_action, old_action;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;
    new_action.sa_handler = sig_handler;

    sigaction(SIGTSTP, &new_action, &old_action);

    pause();
    return 0;
}
