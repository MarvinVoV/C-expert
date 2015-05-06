/*
 * ping.h
 *
 *  Created on: May 6, 2015
 *      Author: louis
 */

#ifndef PING_H_
#define PING_H_

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
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#ifdef IPV6
#include <netinet/ip6.h>
#include <netinet/icmp6.h>
#endif

#define BUFSIZE 1500
char sendbuf[BUFSIZE];
int verbose;
char *host;
pid_t pid;
int sockfd;
int nsent; 		/* add 1 for each sendto() */

/* function prototypes */
void init_v6(void);
void proc_v4(char *, ssize_t, struct msghdr *, struct timeval *);
void proc_v6(char *, ssize_t, struct msghdr *, struct timeval *);
void send_v4(void);
void send_v6(void);
void readloop(void);
void sig_alrm(int);
void tv_sub(struct timeval *, struct timeval *);

struct proto {
	void (*fproc)(char *, ssize_t, struct msghdr *, struct timeval *);
	void (*fsend)(void);
	void (*finit)(void);
	struct sockaddr *sasend;
	struct sockaddr *sarecv;
	socklen_t salen;
	int icmpproto; /* IPPROTO_XXX value */
}*pr;

#endif /* PING_H_ */
