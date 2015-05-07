/*
 * yamorn.h
 *
 *  Created on: May 6, 2015
 *      Author: louis
 */

#ifndef YAMORN_H_
#define YAMORN_H_
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#define	max(a,b)	((a) > (b) ? (a) : (b))
#define	min(a,b)	((a) < (b) ? (a) : (b))

typedef	void Sigfunc(int);	/* for signal handlers */

char *Inet_ntop(const struct sockaddr *, socklen_t);

struct addrinfo *Getaddrinfo(const char *, const char *, int, int);

Sigfunc *Signal(int, Sigfunc *);

void *Calloc(size_t, size_t);

void Gettimeofday(struct timeval *, void *);

void Sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);

uint16_t in_cksum(uint16_t *, int);
#endif /* YAMORN_H_ */
