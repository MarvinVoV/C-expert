#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

void printids(const char *s){
	pid_t pid;
	pthread_t tid;

	pid=getpid();
	tid=pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n",s,(unsigned long)pid,(unsigned long)tid,(unsigned long)tid);
}

void *thr_fn(void *arg){
	printids("new thread: ");
	sleep(3);
	pthread_exit((void *)2);
}

int main(void){
	int err;
	void *reval;
	pthread_t tid;
	err=pthread_create(&tid,NULL,thr_fn,NULL);
	if(err!=0){
		perror("pthread_create error");
		exit(1);
	}

	printids("main thread: ");
	err=pthread_join(tid,&reval);
	if(err!=0){
		perror("can't join with thread");
	}
	printf("thread return value is %ld\n",(long)reval);
	sleep(1);
	exit(0);
}
