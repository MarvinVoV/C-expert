#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int gvar=6;
char buf[]="a write to stdout\n";

int main(void){
    int var; /* automatic variable on the stack */
    pid_t pid;

    var=88;

    if(write(STDOUT_FILENO,buf,sizeof(buf))!=sizeof(buf)){
	perror("write stdout error\n"); /* we don't flush stdout */
	exit(1);
    }

    printf("before fork\n"); 

    pid=fork();
    if(pid<0){
	perror("fork error\n");
	exit(1);
    }else if(pid==0){ //child process 
	gvar++;
	var++;
    }else{
	sleep(2); // parent 
    }

    printf("pid=%ld,gvar=%d,var=%d\n",(long)getpid(),gvar,var);
    exit(0);
}
