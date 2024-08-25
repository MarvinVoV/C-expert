#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(void){
    sigset_t sigset;
    if(sigprocmask(0, NULL, &sigset) < 0){
        perror("sigprocmask error");
    }else{
        if(sigismember(&sigset, SIGKILL))
            printf("SIGKILL\n");
        if(sigismember(&sigset, SIGSTOP))
            printf("SIGSTOP\n");
    }

    return 0;
}
