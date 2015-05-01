#ifndef __netcomplex_h 
#define __netcomplex_h

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

/* Custom constants */
#define MAXLINE 4096 /* max text line length */
#define SERV_PORT 9877 /* TCP and UDP */
#define LISTENQ 1024 /* 2nd argument to listen() */


/* Error module */
void err_sys(const char *,...);

void err_msg(const char *,...);


/* Socket module */
int Accept(int, struct sockaddr *, socklen_t *);

void Bind(int, const struct sockaddr *, socklen_t);

void Connect(int, const struct sockaddr *, socklen_t);

void Listen(int, int);

int Socket(int, int, int);

ssize_t Recv(int, void *, size_t, int);

void Send(int, const void *ptr, size_t nbytes, int);

void Inet_pton(int, const char *, void *);

const char *Inet_ntop(int, const void *addrptr, char *strptr, size_t len);


/* IO module */
ssize_t Readn(int fd, void *buff, size_t nbytes);

void Writen(int fd, void *buff, size_t nbytes);

ssize_t Readline(int fd, void *buff, size_t maxlen);

/* stdio wrap module */
void Fclose(FILE *);

FILE *Fdopen(int , const char *);

char *Fgets(char *, int, FILE *);

FILE *Fopen(const char *, const char *);

void Fputs(const char *, FILE *);


/* Linux API wrap */
void Close(int);

pid_t Fork();


#endif  /* __netcomplex_h */
