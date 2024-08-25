#include <unistd.h>
#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>

void showtime(struct tms *);

int main(void){
    struct tms start,end;

    if(times(&start)==-1){
	perror("times start error");
	exit(1);
    }

    showtime(&start);
    sleep(2);
    if(times(&end)==-1){
	perror("times end error");
	exit(1);
    }
    showtime(&end);

    exit(0);
    
}

void showtime(struct tms *buf){
    printf("user:%ld,sys:%ld\n",buf->tms_utime,buf->tms_stime);
}
