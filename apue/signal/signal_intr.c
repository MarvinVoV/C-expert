#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void ouch(int sig){
    printf("OUCH! - I got signal %d\n", sig);
}

int main(void){
    struct sigaction act;
    
    act.sa_handler = ouch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGINT, &act, 0);

    pause();

}
