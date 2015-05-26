#include <unistd.h>
#include <pwd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void my_alarm(int signo){
	struct passwd *rootptr;
	printf("in signal handler\n");
	if((rootptr=getpwnam("root"))==NULL){
		perror("getpwname(root) error");
		exit(1);
	}
	alarm(1);
}

int main(void){
	struct passwd *ptr;
	signal(SIGALRM,my_alarm);
	alarm(1);
	for(;;){
		if((ptr=getpwnam("louis"))==NULL){
			perror("getpwnam(louis) error");
			exit(1);
		}
		if(strcmp(ptr->pw_name,"louis")!=0){
			printf("return value corrupted!,pw_name=%s\n",ptr->pw_name);
		}
	}
}
