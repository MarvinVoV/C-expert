#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

void *thread_function(void *arg);

int main(){
	int res;
	pthread_t thread;
	void *thread_result;

	res=pthread_create(&thread,NULL,thread_function,NULL);
	if(res!=0){
		perror("thread creation failed.");
		exit(1);
	}

	sleep(3);
	printf("canceling thread...\n");
	res=pthread_cancel(thread);
	if(res!=0){
		perror("thread cancelation failed");
		exit(1);
	}

	printf("waiting for thread to finish...\n");

	res=pthread_join(thread,&thread_result);
	if(res!=0){
		perror("thread join failed.");
		exit(1);
	}
	exit(0);

}

void *thread_function(void *arg){
	int i,res;
	res=pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	if(res!=0){
		perror("thread pthread_setcancelstate failed");
		exit(1);
	}

	res=pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
	if(res!=0){
		perror("thread pthread_setcanceltype failed.");
		exit(1);
	}

	printf("thread_function is running\n");
	for(i=0;i<10;i++){
		printf("Thread is still running (%d)...\n",i);
		sleep(1);
	}
	pthread_exit(0);
}
