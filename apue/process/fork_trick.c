#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void){
	pid_t pid;
	
	if((pid = fork()) < 0){ /* first fork */
		perror("fork error");
		exit(-1);
	}else if(pid == 0){ /* first child */
		if((pid = fork()) < 0){ 
			perror("fork error");
			exit(-1);
		}else if(pid > 0)
			exit(0); /* Note: the first child process has terminated */
	
		/* We're the second child; our parent becomes init as soon as 
	     * our real parent calls exit() in the statement above.
		 * Here's where we'd continue executing, knowing that when we're
	     * done, init will reap our status.
         */		 
		sleep(2);
		printf("\nsecond child, parent pid = %ld\n", (long)getppid());
		exit(0);
	}

	/* We're the parent(the original process); we continue executing,
	 * knowing that we're not the parent of the second child.
	 */
	if(waitpid(pid, NULL, 0) != pid){ /* wait for first child */
		perror("waitpid error");
		exit(-1);
	}
	exit(0);

}
