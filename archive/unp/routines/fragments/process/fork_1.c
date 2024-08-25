#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int globvar = 6;    /* external variable in initialized data */
char buf[]  = "a write to stdout\n";

int main(int argc, char **argv){
    int     var;    /* automatic variable on the stack */
    pid_t   pid;
    
    var = 88;
    unsigned int len = sizeof(buf) - 1;

    if(write(STDOUT_FILENO, buf, len) != len){
        perror("write error");
        exit(-1);
    }

    if((pid = fork()) < 0){
        perror("fork error");
        exit(-1);
    } else if(pid == 0){    // child
        globvar++;
        var++;
    } else {                // parent
        sleep(2);
    }
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);
}
