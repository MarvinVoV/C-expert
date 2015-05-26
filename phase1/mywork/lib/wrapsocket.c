/*
 * wrapsocket.c
 *
 *  Created on: May 6, 2015
 *      Author: louis
 */

#include "yamorn.h"

#ifdef HAVE_SOCKADDR_DL_STRUCT
#include <net/if_dl.h>
#endif

int Socket(int family, int type, int protocol){
    int n;
    if((n = socket(family, type, protocol)) < 0){
    	perror("socket");
    	exit(1);
    }
    return(n);
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen){
    if(bind(fd, sa, salen) < 0){
    	perror("bind");
    	exit(1);
    }
}

void Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen){
    if(setsockopt(sockfd, level, optname, optval, optlen) < 0){
    	perror("setsockopt");
    	exit(1);
    }
}

void setSockPort(struct sockaddr *sa, int port){
    switch(sa->sa_family){
	case AF_INET:{
	    	struct sockaddr_in *sin = (struct sockaddr_in *) sa;
	    	sin->sin_port = port;
	    return;
	    }
    #ifdef IPV6
	case AF_INET6:{
	    	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
	    	sin6->sin6_port = port;
	    return;
	    }
    #endif
    }
}

void Sendto(int fd, const void *ptr, size_t nbytes, int flags,
		const struct sockaddr *sa, socklen_t salen) {
	if (sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t) nbytes) {
		perror("Sendto");
		exit(1);
	}
}

ssize_t Recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen){
    ssize_t n;
    if((n = recvfrom(sockfd, buf, len, flags, src_addr, addrlen)) < 0){
    	perror("recvfrom");
    	exit(1);
    }
    return(n);
}

struct addrinfo *Getaddrinfo(const char *host, const char *serv, int family,
		int socktype) {
	int n;
	struct addrinfo hints, *res;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_CANONNAME; /* always return canonical name */
	hints.ai_family = family; /* AF_UNSPEC, AF_INET, AF_INET6, etc. */
	hints.ai_socktype = socktype; /* 0 (any type)  , SOCK_STREAM, SOCK_DGRAM, etc. */

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0) {
		fprintf(stderr, "Getaddrinfo error for %s, %s: %s",
				(host == NULL) ? "(no hostname)" : host,
				(serv == NULL) ? "(no service name)" : serv, gai_strerror(n));
		exit(1);
	}
	return (res); /* return pointer to first on linked list */
}


static char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen) {
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

char *Sock_ntop_host(const struct sockaddr *sa, socklen_t salen) {
	char *ptr;
	if ((ptr = sock_ntop_host(sa, salen)) == NULL) {
		perror("Inet_ntop");
		exit(1);
	}
	return (ptr);
}

int cmpSockAddr(const struct sockaddr *sa1, const struct sockaddr *sa2, socklen_t salen){
	if (sa1->sa_family != sa2->sa_family)
		return(-1);

	switch (sa1->sa_family) {
	case AF_INET:
		return(memcmp( &((struct sockaddr_in *) sa1)->sin_addr,
					   &((struct sockaddr_in *) sa2)->sin_addr,
					   sizeof(struct in_addr)));
#ifdef	IPV6
	case AF_INET6:
		return(memcmp( &((struct sockaddr_in6 *) sa1)->sin6_addr,
					   &((struct sockaddr_in6 *) sa2)->sin6_addr,
					   sizeof(struct in6_addr)));
#endif
	}
    return (-1);
}

void Inet_aton(const char *cp, struct in_addr *inp){
	if(inet_aton(cp, inp) == 0){
		perror("inet_atop");
		exit(1);
	}
}

