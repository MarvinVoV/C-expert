/*
 * test_alarm.c
 *
 *  Created on: May 7, 2015
 *      Author: louis
 */
#include "yamorn.h"

void alarm_handle(int);

int main(void){
	char buf[1024];
	Signal(SIGALRM,alarm_handle);
	alarm_handle(SIGALRM); /* first trigger */
	for(;;){
		while(fgets(buf,1024,stdin)!=NULL){
			printf("input: %s\n",buf);
		}
	}
}

void alarm_handle(int signo){
	printf("trigger alarm.\n");

	alarm(2); /* trigger every one second */

	return;
}

