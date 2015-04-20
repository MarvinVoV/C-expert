#include "thread.h"

static int num=30;
struct timespec spec={0,30*1000}; 
void *thread_func1(void *arg){
    while(num>0){
	num--;
	printf("thread_func1(): num is %d\n",num);
	//sleep(1);
	nanosleep(&spec,NULL);
    }
    pthread_exit(NULL);
}

void *thread_func2(void *arg){
    while(num>0){
	num--;
	printf("thread_func2(): num is %d\n",num);
	//sleep(1);
	nanosleep(&spec,NULL);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t tid1,tid2;
    int s;

    s=pthread_create(&tid1,NULL,thread_func1,NULL);
    if(s!=0)
	handle_error_en(s,"pthread_create");

    s=pthread_create(&tid2,NULL,thread_func2,NULL);
    if(s!=0)
	handle_error_en(s,"pthread_create");

    s=pthread_join(tid1,NULL);
    if(s!=0)
	handle_error_en(s,"pthread_join");
    
    s=pthread_join(tid2,NULL);
    if(s!=0)
	handle_error_en(s,"pthread_join");

    exit(EXIT_SUCCESS);
	
}
