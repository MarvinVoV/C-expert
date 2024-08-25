#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_fn(void *arg){
	pid_t pid = getpid();
	pthread_t tid = pthread_self();
	printf("pid %lu tid %lu\n", (unsigned long)pid, (unsigned long)tid);
}

int main(void){
	pthread_t tid;	
	if(pthread_create(&tid, NULL, thr_fn, NULL) != 0){
		perror("pthread create error");
		exit(-1);	
	}	
	sleep(1);
	printf("create thread id %lu 0x(%lx).\n", tid, tid);
	exit(0);
}

