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

/* Error module */
void err_sys(const char *,...);

void err_msg(const char *,...);


/* Socket module */
int Accept(int, struct sockaddr *, socklen_t *);

void Bind(int, const struct sockaddr *, socklen_t);

void Connect(int, struct sockaddr *, socklen_t);

void Listen(int, int);

int Socket(int, int, int);

ssize_t Recv(int, void *, size_t, int);

void Send(int, const void *ptr, size_t nbytes, int);


/* IO module */
ssize_t readn(int fd, void *buff, size_t nbytes);

ssize_t writen(int fd, void *buff, size_t nbytes);

ssize_t readline(int fd, void *buff, size_t maxlen);
