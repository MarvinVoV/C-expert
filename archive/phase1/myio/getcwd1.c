#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(void){
	char cwd[1024];
	if(chdir("/usr/local")<0){
		perror("chdir error\n");
		exit(1);
	}
	if(getcwd(cwd,sizeof(cwd))==NULL){
		perror("cwd error\n");
		exit(1);
	}
	printf("current dir=%s\n",cwd);
	exit(0);
}
