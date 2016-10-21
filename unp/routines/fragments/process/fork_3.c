#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>


void sig_chld(int signo){
    printf("catch SIGCHLD\n");
}

void pr_exit(int status){
    if(WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d\n", WTERMSIG(status));
    else if(WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}
int main(int argc, char **argv){
    pid_t pid, wpid;
    struct sigaction act, oact;
    int stat;

    act.sa_handler = sig_chld;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if(sigaction(SIGCHLD, &act, &oact) < 0){
        perror("sigaction error\n");
        exit(-1);
    }

    if((pid = fork()) == -1){
        perror("fork error");
        exit(-1);
    }else if(pid == 0){ // child 
        printf("child process run\n");
        sleep(5);
    }else{ // parent 
        printf("parent run\n");
        wpid = wait(&stat);
        printf("wpid=%d\n", wpid);
        pr_exit(stat);
    }

    exit(0);
}
