#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*
 * Print the names of the signals in the signal mask of the calling process.
 */
print_mask(const char *str){
    sigset_t sigset;
    if(sigprocmask(0, NULL, &sigset) < 0){
        perror("sigprocmask error");
    }else{
        printf("%s", str);
        if(sigismember(&sigset, SIGINT))
            printf(" SIGINT");
        if(sigismember(&sigset, SIGQUIT))
            printf(" SIGQUIT");
        if(sigismember(&sigset, SIGALRM))
            printf(" SIGALRM");
        /* remaining signals can go here */
        printf("\n");
    }

    
}
