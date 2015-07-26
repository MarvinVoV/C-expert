/*
 * sun_socket.c
 *
 *  Created on: Jul 26, 2015
 *      Author: yamorn
 */

#include "sun_socket.h"

int sun_socket(int family, int type, int protocol) {
	int n;

	if ((n = socket(family, type, protocol)) < 0) {
		perror("socket error");
		exit(1);
	}
	return (n);
}

void sun_bind(int fd, const struct sockaddr *sa, socklen_t salen) {
	if (bind(fd, sa, salen) < 0) {
		perror("bind error");
		exit(1);
	}
}

void sun_connect(int fd, const struct sockaddr *sa, socklen_t salen) {
	if (connect(fd, sa, salen) < 0) {
		perror("connect error");
		exit(1);
	}
}

int sun_accept(int fd, struct sockaddr *sa, socklen_t *salenptr) {
	int n;

	again: if ((n = accept(fd, sa, salenptr)) < 0) {
#ifdef	EPROTO
		if (errno == EPROTO || errno == ECONNABORTED)
#else
			if (errno == ECONNABORTED)
#endif
			goto again;
		else
			perror("accept error");
	}
	return (n);
}

void sun_listen(int fd, int backlog) {
	char *ptr;

	/*4can override 2nd argument with environment variable */
	if ((ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);

	if (listen(fd, backlog) < 0)
		perror("listen error");
}

int sun_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
		struct timeval *timeout) {
	int n;

	if ((n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0) {
		perror("select error");
		exit(1);
	}
	return (n); /* can return 0 on timeout */
}

void sun_send(int fd, const void *ptr, size_t nbytes, int flags) {
	if (send(fd, ptr, nbytes, flags) != (ssize_t) nbytes) {
		perror("send");
	}
}

void sun_sendto(int fd, const void *ptr, size_t nbytes, int flags,
		const struct sockaddr *sa, socklen_t salen) {
	if (sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t) nbytes)
		perror("sendto error");
}

void sun_setsockopt(int fd, int level, int optname, const void *optval,
		socklen_t optlen) {
	if (setsockopt(fd, level, optname, optval, optlen) < 0)
		perror("setsockopt error");
}

ssize_t sun_recvmsg(int fd, struct msghdr *msg, int flags) {
	ssize_t n;

	if ((n = recvmsg(fd, msg, flags)) < 0)
		perror("recvmsg error");
	return (n);
}

ssize_t sun_recvfrom(int fd, void *ptr, size_t nbytes, int flags,
		struct sockaddr *sa, socklen_t *salenptr) {
	ssize_t n;

	if ((n = recvfrom(fd, ptr, nbytes, flags, sa, salenptr)) < 0)
		perror("recvfrom error");
	return (n);
}

ssize_t sun_recv(int fd, void *ptr, size_t nbytes, int flags) {
	ssize_t n;

	if ((n = recv(fd, ptr, nbytes, flags)) < 0)
		perror("recv error");
	return (n);
}

const char *sun_inet_ntop(int family, const void *addrptr, char *strptr,
		size_t len) {
	const char *ptr;

	if (strptr == NULL) { /* check for old code */
		perror("NULL 3rd argument to inet_ntop");
		exit(1);
	}
	if ((ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
		perror("inet_ntop error"); /* sets errno */
	return (ptr);
}

void sun_inet_pton(int family, const char *strptr, void *addrptr) {
	int n;

	if ((n = inet_pton(family, strptr, addrptr)) < 0) {
		fprintf(stderr, "inet_pton error for %s", strptr); /* errno set */
		exit(1);
	} else if (n == 0) {
		fprintf(stderr, "inet_pton error for %s", strptr); /* errno not set */
		exit(1);
	}
}

