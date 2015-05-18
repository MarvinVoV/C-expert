#include "thread.h"

pthread_t ptid;

void printids(const char *s){
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();
	printf(" %s pid %lu tid %lu (0x%lx)\n", (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}
void *thread_handler(void *arg){
	printids("new thread: ");
	return((void *)0);
}
int main(void){
	int err;

	err = pthread_create(&ptid, NULL, thread_handler, NULL);
	if(err != 0){
		perror("pthread_create");
		exit(1);
	}
	printids("main thread:");
	sleep(1);
	exit(0);
}
