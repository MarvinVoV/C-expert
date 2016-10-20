/*
 * unp.h
 *
 *  Created on: Oct 7, 2016
 *      Author: yamorn
 */

#ifndef HEADER_UNP_H_
#define HEADER_UNP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define SERV_PORT 8080
#define BUF_SIZE  2048 * 10

typedef void sigfunc(int);


ssize_t readn(int fd, void *buf, size_t nbytes);

ssize_t writen(int fd, const void *buf, size_t nbytes);

ssize_t readline(int fd, void *buf, size_t maxlen);


sigfunc *signal(int signo, sigfunc *func);



#endif /* HEADER_UNP_H_ */
