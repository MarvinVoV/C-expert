#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void){
	pid_t pid;

	if((pid = fork()) < 0){
		perror("fork error");
		exit(-1);
	}else if(pid == 0){ /* child */
		if(execl("/bin/echo", "echo", "hello world", (char *)0) < 0){
			perror("execl error");
			exit(-1);
		}
	}

	if(waitpid(pid, NULL, 0) < 0){
		perror("waitpid error");
		exit(-1);
	}
	printf("main process done.\n");
	exit(0);
}
