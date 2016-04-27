#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	
	pid_t pid;
	
	if((pid = fork()) < 0){
		perror("fork error");
		exit(-1);
	}else if(pid == 0){ /* child */
		printf("child pid is %d\n", (int)getpid());
		printf("parent pid is %d\n", (int)getppid());
		printf("uid is %d\n", (int)getuid());
		printf("eid is %d\n", (int)geteuid());
		printf("gid is %d\n", (int)getgid());
	    sleep(1); // sleep 1 seconds	
	}else{ /* parent */
		if(waitpid(pid, NULL, 0) < 0){ /* parent */
			perror("waitpid error");
			exit(-1);
		}
		printf("pid is %d\n", (int)getpid());

	}

	exit(0);

}
