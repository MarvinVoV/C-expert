#ifndef _ECHO_H_
#define _ECHO_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


ssize_t readn(int fd, void *buf, size_t nbytes);

ssize_t writen(int fd, const void *buf, size_t nbytes);

ssize_t readline(int fd, void *buf, size_t maxlen);



#endif
