#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>


int main(int argc, char **argv){
    pid_t pid, wpid;
    int stat;

    if((pid = fork()) == -1){
        perror("fork error");
        exit(-1);
    }else if(pid == 0){ // child 
        printf("child process run\n");
        sleep(5);
    }else{ // parent 
       printf("parent run.\n"); 

       wpid = wait(&stat);
       printf("child process terminated, pid=%d\n", wpid);
    }

    printf("process id %d\n", getpid());

    exit(0);
}
