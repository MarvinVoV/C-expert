/*
 * wraplinux.c
 *
 *  Created on: May 6, 2015
 *      Author: louis
 */

#include "yamorn.h"

void *Calloc(size_t n, size_t size) {
	void *ptr;

	if ((ptr = calloc(n, size)) == NULL){
		perror("calloc error");
		exit(1);
	}
	return (ptr);
}

void Gettimeofday(struct timeval *tv, void *foo){
	if (gettimeofday(tv, foo) == -1){
		perror("gettimeofday");
		exit(1);
	}
	return;
}

void Close(int fd){
    if(close(fd) == -1){
	perror("close error");
	exit(1);
    }
}
