#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
	pid_t pid, w_pid;
	int status; /* child process exit status */

	if((pid = fork()) < 0){
		perror("fork error");
		exit(-1);
	}else if(pid == 0){ /* child */
		printf("child process id %d\n", (int)getpid());
		exit(2); /* child process exit status */
	}else{ /* parent */
		printf("parent process id %d\n", (int)getpid());
		sleep(2); /* delay two seconds */
		w_pid = wait(&status);
		if(w_pid < 0){
			perror("wait error");
			exit(-1);
		}else{
			printf("terminal process id %d, child exit status %d\n", (int)w_pid, status);
		}
	}
}
