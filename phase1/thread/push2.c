#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>

void cleanup(void *arg){
    printf("cleanup:%s\n",(char *)arg);
}

void thr_fu1(void *arg){
    printf("thread 1 start\n");
    /* pthread_cleanup_push and pthread_cleanup_pop defined as macro */
    pthread_cleanup_push(cleanup,"thread 1 first handle");
    

    pthread_cleanup_pop(0);
}

int main(int argc, char *argv[]){

}
