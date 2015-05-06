/*
 * main.c
 *
 *  Created on: May 6, 2015
 *      Author: louis
 */

#include "yamorn.h"
#include "ping.h"

struct proto proto_v4 = { proc_v4, send_v4, NULL, NULL, NULL, 0, IPPROTO_ICMP };
#ifdef IPV6
struct proto proto_v6= {proc_v6,send_v6,init_v6,NULL,NULL,0,IPPROTO_ICMPV6};
#endif

int datalen = 56; /* data that goes with ICMP echo request */

int main(int argc, char **argv) {
	int c;
	struct addrinfo *ai;
	char *h;
	while ((c = getopt(argc, argv, "vh:")) != -1) {
		switch (c) {
		case 'v':
			verbose++;
			break;
		case 'h':
			host = optarg;
			break;
		case '?':
			fprintf(stderr, "unrecognized option: %c\n", c);
			exit(1);
		}
	}

	pid = getpid() & 0xfffff; /* ICMP identifier field is 16 bits */

	Signal(SIGALRM, sig_alrm);

	ai = Getaddrinfo(host, NULL, 0, 0);

	h = Inet_ntop(ai->ai_addr, ai->ai_addrlen);
	printf("PING %s (%s): %d data bytes\n",
			ai->ai_canonname ? ai->ai_canonname : h, h, datalen);

	/* initialize according to protocol */
	if (ai->ai_family == AF_INET) {
		pr = &proto_v4;
#ifdef IPV6
	} else if(ai->ai_family==AF_INET6) {
		pr=&proto_v6;
		if (IN6_IS_ADDR_V4MAPPED(&(((struct sockaddr_in6 *)ai->ai_addr)->sin6_addr))) {
			perror("cannot ping IPv4-mapped IPv6 address");
			exit(1);
		}
#endif
	} else {
		fprintf(stderr, "unknown address family %d", ai->ai_family);
		exit(1);
	}

	pr->sasend = ai->ai_addr;
	pr->sarecv = Calloc(1, ai->ai_addrlen);
	pr->salen = ai->ai_addrlen;
	readloop();

	exit(0);
}

void readloop(void) {
	int size;
	char recvbuf[BUFSIZE];
	char controlbuf[BUFSIZE];
	struct msghdr msg;
	struct iovec iov;
	ssize_t n;
	struct timeval tval;

	sockfd = socket(pr->sasend->sa_family, SOCK_RAW, pr->icmpproto);
	setuid(getuid()); /* don’t need special permissions any more */
	if (pr->finit) {
		(*pr->finit)();
	}

	size = 60 * 1024; /* OK if setsockopt fails */
	setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
	sig_alrm(SIGALRM); /* send first packet */

	iov.iov_base = recvbuf;
	iov.iov_len = sizeof(recvbuf);
	msg.msg_name = pr->sarecv;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = controlbuf;
	for (;;) {
		msg.msg_namelen = pr->salen;
		msg.msg_controllen = sizeof(controlbuf);
		n = recvmsg(sockfd, &msg, 0);
		if (n < 0) {
			if (errno == EINTR)
				continue;
			else {
				perror("recvmsg error");
				exit(1);
			}
		}
		Gettimeofday(&tval, NULL);
		(*pr->fproc)(recvbuf, n, &msg, &tval);
	}
}

void tv_sub(struct timeval *out, struct timeval *in) {
	if ((out->tv_usec -= in->tv_usec) < 0) {
		--out->tv_sec;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}

void proc_v4(char *ptr, ssize_t len, struct msghdr *msg, struct timeval *tvrecv) {
	int hlen1, icmplen;
	double rtt;
	struct ip *ip;
	struct icmp *icmp;
	struct timeval *tvsend;

	ip = (struct ip *) ptr; /* start of IP header */
	hlen1 = ip->ip_hl << 2; /* length of IP header */
	if (ip->ip_p != IPPROTO_ICMP)
		return; /* not ICMP */

	icmp = (struct icmp *) (ptr + hlen1); /* start of ICMP header */
	if ((icmplen = len - hlen1) < 8)
		return; /* malformed packet */

	if (icmp->icmp_type == ICMP_ECHOREPLY) {
		if (icmp->icmp_id != pid)
			return; /* not a response to our ECHO_REQUEST */
		if (icmplen < 16)
			return; /* not enough data to use */

		tvsend = (struct timeval *) icmp->icmp_data;
		tv_sub(tvrecv, tvsend);
		rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;

		printf("%d bytes from %s: seq=%u, ttl=%d, rtt=%.3f ms\n", icmplen,
				Sock_ntop_host(pr->sarecv, pr->salen), icmp->icmp_seq,
				ip->ip_ttl, rtt);

	} else if (verbose) {
		printf("  %d bytes from %s: type = %d, code = %d\n", icmplen,
				Sock_ntop_host(pr->sarecv, pr->salen), icmp->icmp_type,
				icmp->icmp_code);
	}
}

void proc_v6(char *ptr, ssize_t len, struct msghdr *msg, struct timeval* tvrecv) {
#ifdef	IPV6
	double rtt;
	struct icmp6_hdr *icmp6;
	struct timeval *tvsend;
	struct cmsghdr *cmsg;
	int hlim;

	icmp6 = (struct icmp6_hdr *) ptr;
	if (len < 8)
	return; /* malformed packet */

	if (icmp6->icmp6_type == ICMP6_ECHO_REPLY) {
		if (icmp6->icmp6_id != pid)
		return; /* not a response to our ECHO_REQUEST */
		if (len < 16)
		return; /* not enough data to use */

		tvsend = (struct timeval *) (icmp6 + 1);
		tv_sub(tvrecv, tvsend);
		rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;

		hlim = -1;
		for (cmsg = CMSG_FIRSTHDR(msg); cmsg != NULL; cmsg = CMSG_NXTHDR(msg, cmsg)) {
			if (cmsg->cmsg_level == IPPROTO_IPV6 &&
					cmsg->cmsg_type == IPV6_HOPLIMIT) {
				hlim = *(u_int32_t *)CMSG_DATA(cmsg);
				break;
			}
		}
		printf("%d bytes from %s: seq=%u, hlim=",
				len, Sock_ntop_host(pr->sarecv, pr->salen),
				icmp6->icmp6_seq);
		if (hlim == -1)
		printf("???"); /* ancillary data missing */
		else
		printf("%d", hlim);
		printf(", rtt=%.3f ms\n", rtt);
	} else if (verbose) {
		printf("  %d bytes from %s: type = %d, code = %d\n",
				len, Sock_ntop_host(pr->sarecv, pr->salen),
				icmp6->icmp6_type, icmp6->icmp6_code);
	}
#endif	/* IPV6 */
}
