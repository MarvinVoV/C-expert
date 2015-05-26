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

#define max(a,b)    ((a) > (b) ? (a) : (b))
#define min(a,b)    ((a) < (b) ? (a) : (b));


typedef void Sigfunc(int); /* for signal handlers */

Sigfunc *Signal(int signo, Sigfunc *func); /* for signal() function */

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

int Select(int, fd_set *, fd_set *, fd_set*, struct timeval *);

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


void Sigemptyset(sigset_t *);

void Sigfillset(sigset_t *);

void Sigfillset(sigset_t *);

int Sigismember(const sigset_t *, int);

void Sigaddset(sigset_t *, int);

void Sigdelset(sigset_t *, int);

void Sigpending(sigset_t *);

void Sigprocmask(int, const sigset_t *, sigset_t *);


#endif  /* __netcomplex_h */
