#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

#define NUM_THREADS 6

void *thread_function(void *arg);

int main(){
	int res;
	pthread_t threads[NUM_THREADS];
	void *thread_result;
	int num; //current threads number

	for(num=0;num<NUM_THREADS;num++){
		res=pthread_create(&(threads[num]),NULL,thread_function,(void *)&num);
		if(res!=0){
			perror("thread creation failed.");
			exit(1);
		}
		sleep(1);
	}
	printf("waiting for threads to finish...\n");

	int i;
	for(i=0;i<num;i++){
		res=pthread_join(threads[i],&thread_result);
		if(res==0){
			perror("Picked up a thread \n");
		}else{
			perror("pthread_join failed.");
		}
	}
	printf("All done\n");
	exit(0);	
}

void *thread_function(void *arg){
	int num=*(int *)arg;
	int rand_num;

	printf("thread function is running .Argument is %d\n",num);
	rand_num=1+(int)(9.0*rand()/(RAND_MAX+1.0));
	printf("Bye from %d\n",rand_num);
	pthread_exit(NULL);
}
