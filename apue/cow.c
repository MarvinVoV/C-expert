#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/**
  * fork function. copy-on-write
  */

int globvar = 6; /* external variable in initialized data */
char buf[] = "a write to stdout\n";

int main(void){
	int var = 88; /* automatic variable on the stack */	
	pid_t pid;

	if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1){
		perror("write error");
		exit(-1);
	}

	printf("before fork\n");

	if((pid = fork()) < 0){
		perror("fork error");
		exit(-1);
	}else if(pid == 0){ // child
		printf("parent process id is %d\n", (int)getppid());
		globvar++;
		var++;
	}else{ // parent 
		sleep(2);
	}
	printf("pid=%ld, glob=%d, var=%d\n", (long)getpid(), globvar, var);
	exit(0);
}
