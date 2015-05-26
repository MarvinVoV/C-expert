#include "mypipe.h"

int main(void){
	int n;
	int fd[2];
	pid_t pid;
	char line[1024];
	char *msg="hello world\n";
	if(pipe(fd)<0)
		error_handle(1,"pipe error");
	if((pid=fork())<0){
		error_handle(1,"fork error");
	}else if(pid>0){ /* parent */
		close(fd[0]);
		write(fd[1],msg,strlen(msg));
	}else{ /* child */
		close(fd[1]);
		n=read(fd[0],line,1024);
		write(STDOUT_FILENO,line,n);
	}
	exit(0);
		
}
