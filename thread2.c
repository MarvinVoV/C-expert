#include<unistd.h>
#include<semaphore.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>

#define WORK_SIZE 1024

void *thread_function(void *);

sem_t bin_sem; //binary semaphore

char work_area[WORK_SIZE];

int main(){
	int res;
	pthread_t thread;
	void *thread_result;

	res=sem_init(&bin_sem,0,0);
	if(res!=0){
		perror("Semaphore initialization failed.");
		exit(EXIT_FAILURE);
	}

	res=pthread_create(&thread,NULL,thread_function,NULL);
	if(res!=0){
		perror("Thread creation failed.");
		exit(EXIT_FAILURE);
	}

	printf("Input some text. Enter 'end' to finish\n");

	while(strncmp("end",work_area,3)!=0){
		fgets(work_area,WORK_SIZE,stdin);
		sem_post(&bin_sem);
	}

	printf("\nWaiting for thread to finish...\n");
	res=pthread_join(thread,&thread_result);
	if(res!=0){
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}

	printf("Thread joined\n");

	sem_destroy(&bin_sem);
	
	exit(EXIT_SUCCESS);

}

// counting input character number from main thread.
void *thread_function(void *arg){
	printf("thread wait for semaphore\n");
	sem_wait(&bin_sem);
	printf("thread run after waiting for semaphore\n");
	while(strncmp("end",work_area,3)!=0){
		printf("You input %ld characters\n",strlen(work_area)-1);
		sem_wait(&bin_sem);
	}
	pthread_exit(NULL);
}

