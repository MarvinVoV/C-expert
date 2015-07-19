/*
 * abortsignal.c
 *
 *  Created on: Jul 19, 2015
 *      Author: yamorn
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void termination_handler(int signum){
	fprintf(stdout, "receive interrupte signal");
	exit(0);
}

int main(int argc, char *argv[]){

	int res;
	struct sigaction act, oact;
	act.sa_handler = termination_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	res = sigaction(SIGINT, &act, &oact);
	if(res == -1){
		perror("sigaction");
		exit(-1);
	}

	pause(); /* wait for signal interruption */
	printf("exit\n");
	return 0;
}

