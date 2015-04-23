#include "thread.h"

void *thread_func(void *arg){
	printf("thread running.\n");
	sleep(2);
	pthread_exit((void *)10);
}

int main(void){
	pthread_t tid;
	int err;
	void *res;
	long stacksize;
	pthread_attr_t attr;
	err=pthread_attr_init(&attr);
	if(err!=0)
		handle_error_en(err,"pthread_attr_init");
	pthread_attr_getstacksize(&attr,&stacksize);
	printf("thread stacksize is %ld\n",stacksize);
	/* If set thread state detach, main thread cann't join this thread */
	//err=pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	/* joinable is default */
	err=pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	if(err!=0)
		handle_error_en(err,"pthread_setdetachstate");

	err=pthread_create(&tid,&attr,thread_func,NULL);
	if(err!=0)
		handle_error_en(err,"pthread_create");

	printf("main thread running.\n");
	err=pthread_join(tid,&res);	
	if(err!=0)
		handle_error_en(err,"pthread_join");
	printf("thread return value is %d\n",(int)res);

	pthread_attr_destroy(&attr);
	exit(0);
}
