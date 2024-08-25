/*
 * gen.h
 *
 *  Created on: May 4, 2015
 *      Author: yamorn
 */

#ifndef GEN_H_
#define GEN_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <syslog.h>
#include <sys/resource.h>

#define SERV_PORT 9877 /* TCP */
#define MAXLEN 4096
#define LISTENQ 128 /* 2nd argument to listen() */

#define max(a,b) ((a) > (b) ? (a) : (b));
#define min(a,b) ((a) < (b) ? (a) : (b));



ssize_t readline(int, void *, size_t);

ssize_t writen(int, const void *, size_t);


int daemonize(const char *, int);


#endif /* GEN_H_ */
