/*
 * net.h
 *
 *  Created on: Jul 19, 2015
 *      Author: yamorn
 */

#ifndef LIB_COMMON_H_
#define LIB_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>
#include <time.h>
#include <errno.h>

void Writen(int fd, void *buff, size_t nbytes);
ssize_t Readn(int fd, void *buff, size_t nbytes);
ssize_t Readline(int fd, void *buff, size_t maxlen);

#endif /* LIB_COMMON_H_ */
