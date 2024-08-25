/*
 * sun_socket.h
 *
 *  Created on: Jul 26, 2015
 *      Author: yamorn
 */

#ifndef LIB_SUN_SOCKET_H_
#define LIB_SUN_SOCKET_H_

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


int sun_socket(int family, int type, int protocol);

void sun_bind(int fd, const struct sockaddr *sa, socklen_t salen);

void sun_connect(int fd, const struct sockaddr *sa, socklen_t salen);

int sun_accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

void sun_listen(int fd, int backlog);

int sun_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
		struct timeval *timeout);

void sun_send(int fd, const void *ptr, size_t nbytes, int flags);

void sun_sendto(int fd, const void *ptr, size_t nbytes, int flags,
		const struct sockaddr *sa, socklen_t salen);

void sun_setsockopt(int fd, int level, int optname, const void *optval,
		socklen_t optlen);

ssize_t sun_recvmsg(int fd, struct msghdr *msg, int flags);

ssize_t sun_recvfrom(int fd, void *ptr, size_t nbytes, int flags,
		struct sockaddr *sa, socklen_t *salenptr);

ssize_t sun_recv(int fd, void *ptr, size_t nbytes, int flags);

const char *sun_inet_ntop(int family, const void *addrptr, char *strptr, size_t len);

void sun_inet_pton(int family, const char *strptr, void *addrptr);

#endif /* LIB_SUN_SOCKET_H_ */
