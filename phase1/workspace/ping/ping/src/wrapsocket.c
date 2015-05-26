/*
 * wrapsocket.c
 *
 *  Created on: May 6, 2015
 *      Author: louis
 */

#include "yamorn.h"

void Sendto(int fd, const void *ptr, size_t nbytes, int flags,
		const struct sockaddr *sa, socklen_t salen) {
	if (sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t) nbytes) {
		perror("Sendto");
		exit(1);
	}
}

struct addrinfo *Getaddrinfo(const char *host, const char *serv, int family,
		int socktype) {
	int n;
	struct addrinfo hints, *res;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_CANONNAME; /* always return canonical name */
	hints.ai_family = family; /* 0, AF_INET, AF_INET6, etc. */
	hints.ai_socktype = socktype; /* 0, SOCK_STREAM, SOCK_DGRAM, etc. */

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0) {
		fprintf(stderr, "host_serv error for %s, %s: %s",
				(host == NULL) ? "(no hostname)" : host,
				(serv == NULL) ? "(no service name)" : serv, gai_strerror(n));
		exit(1);
	}
	return (res); /* return pointer to first on linked list */
}


static char *__inet_ntop(const struct sockaddr *sa, socklen_t salen) {
	static char str[128]; /* unix domain is largest */
	switch (sa->sa_family) {
	case AF_INET: {
		struct sockaddr_in *sin = (struct sockaddr_in *) sa;
		if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
			return (NULL);
		return (str);
	}
	case AF_INET6: {
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) sa;
		if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL)
			return (NULL);
		return (str);
	}
	default:
		snprintf(str, sizeof(str), "sock_ntop_host: unknown AF_xxx: %d, len %d",
				sa->sa_family, salen);
		return (str);
	}
	return (NULL);
}

char *Inet_ntop(const struct sockaddr *sa, socklen_t salen) {
	char *ptr;
	if ((ptr = __inet_ntop(sa, salen)) == NULL) {
		perror("Inet_ntop");
		exit(1);
	}
	return (ptr);
}
