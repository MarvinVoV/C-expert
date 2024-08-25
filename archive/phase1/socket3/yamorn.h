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
#include <netinet/udp.h>
#include <netinet/tcp.h>
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

int Socket(int, int, int);

void *Calloc(size_t, size_t);

void Gettimeofday(struct timeval *, void *);

void Sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);

ssize_t Recvfrom(int, void *, size_t, int, struct sockaddr *, socklen_t *);

uint16_t in_cksum(uint16_t *, int);

/* wrap linux */
void Close(int);

/* wrap stdio */
FILE *Fopen(const char *, const char *);

#endif /* YAMORN_H_ */
