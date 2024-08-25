#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void){
    printf("the storage of sigset_t is %ld\n", sizeof(sigset_t));
    sigset_t sigset;
        
    sigemptyset(&sigset);


    return 0;
}
