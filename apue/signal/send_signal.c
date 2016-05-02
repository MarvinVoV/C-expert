#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int pid = atoi(argv[1]);
    int ret = kill(pid, SIGQUIT);
    printf("ret :%d\n", ret);

    return 0;
}
