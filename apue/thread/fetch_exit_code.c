#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thr_fn1(void *arg){
	printf("thread id %lu\n", pthread_self());
	return((void *)1);
}

void *thr_fn2(void *arg){
	printf("thread id %lu\n", pthread_self());
	pthread_exit((void *)2);
}

int main(void){
	pthread_t tid1, tid2;
	void *retval;

	if(pthread_create(&tid1, NULL, thr_fn1, NULL) != 0){
		perror("create thread error");
		exit(-1);
	}

	if(pthread_create(&tid2, NULL, thr_fn2, NULL) != 0){
		perror("create thread error");
		exit(-1);
	}

	if(pthread_join(tid1, &retval) != 0 ){
		perror("pthread join error");
		exit(-1);
	}
	printf("thread %lu exit code %ld\n", tid1, (long)retval);

	if(pthread_join(tid2, &retval) != 0 ){
		perror("pthread join error");
		exit(-1);
	}
	printf("thread %lu exit code %ld\n", tid2, (long)retval);

	exit(0);
}
