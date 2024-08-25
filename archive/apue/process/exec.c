#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

char *env_init[] = {"USER=unkown", "PATH=/tmp", NULL};

int main(void){
    pid_t pid;
    if((pid = fork()) < 0){
        perror("fork error");
        exit(-1);
    }else if(pid == 0){ /* specify pathname, environment */
        if(execle("/Users/sunyamorn/workspace/github/linux-programming/apue/process/echoall", "echoall", "myarg1", "myarg2", (char *)0, env_init) < 0){
            perror("execle error");
            exit(-1);
        }
    }
    if(waitpid(pid, NULL, 0) < 0){
        perror("wait error");
        exit(-1);
    }

    if((pid = fork()) < 0){
        perror("fork error");
        exit(-1);
    }else if(pid == 0){
        if(execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0){
            perror("execlp error");
            exit(-1);
        }
    }
    exit(0);
}
