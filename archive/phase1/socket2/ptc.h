#ifndef __PTC_H
#define __PTC_H

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

#define SERV_PORT 9877 /* TCP */
#define LISTENQ 1024 /* 2nd argument to listen() */
#define MAXLEN 4096

#define max(a,b) ((a) > (b) ? (a) : (b));
#define min(a,b) ((a) < (b) ? (a) : (b));


void servprocess(int); /* server process interface */

void cliprocess(FILE *, int); /* client process interface */

/* general method */
ssize_t readline(int fd, void *buf, size_t maxlen);

ssize_t writen(int, const void *, size_t);

#endif
