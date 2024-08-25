#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	printf("The storage size of pid_t is %ld\n", sizeof(pid_t));

	printf("current process id is %d\n", (int)getpid());

	printf("parent process id  is %d\n", (int)getppid());

	printf("the real user id of calling process %d\n", (int)getuid());

	printf("effective user ID of calling process %d\n", (int)geteuid());

	printf("real group id of calling process %d\n", (int)getgid());

	printf("effective group id of calling process %d\n", (int)getegid());

	exit(0);

}
