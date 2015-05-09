#include "yamorn.h"
#include "traceroute.h"

int main(int argc, char **argv) {
	int c;
	char *hostname;
	struct addrinfo *ai;
	struct sockaddr *sasend;
	struct ip *ip;

	while ((c = getopt(argc, argv, "m:h:")) != -1) {
		switch (c) {
		case 'm': {
			if ((max_ttl = atoi(optarg)) <= 1) {
				fprintf(stderr, "invalid -m value.");
				exit(1);
			}
			break;
		}
		case 'h': {
			hostname = optarg;
			break;
		}
		case '?': {
			fprintf(stderr, "Unrecoginized option: %c", c);
			exit(1);
		}
		}
	}

	if (optind > argc) {
		fprintf(stderr, "usage:troute -m <max_ttl> -h hostname\n");
		exit(1);
	}

	ai = Getaddrinfo(hostname, NULL, AF_UNSPEC, 0);
	host = Sock_ntop_host(ai->ai_addr, ai->ai_addrlen);
	printf("traceroute to %s (%s): %d hops max, %d data bytes\n",
			ai->ai_canonname ? ai->ai_canonname : host, hostname, max_ttl,
			datalen);

//	recvfd = Socket(ai->ai_family, SOCK_RAW, IPPROTO_ICMP);

//	printf("protocol=%d\n",ai->ai_family);
	sendfd = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//	sport = (getpid() & 0xffff) | 0x8000; /* UDP port */
//
//	struct sockaddr *sabind;
//	sabind = Calloc(1, ai->ai_addrlen);
//	sabind->sa_family = ai->ai_family;
//	setSockPort(sabind, htons(sport));
//	printf("sizeof(*sabind)=%ld, sizeof(struct sockaddr)=%ld\n",sizeof(*sabind),sizeof(struct sockaddr));
//
//	Bind(sendfd, sabind, sizeof(*sabind));

	int ttl = 1;
//	Setsockopt(sendfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
	printf("%2d ", ttl);
	fflush(stdout);

	struct data *data = (struct data *) sendbuf;
	datalen = sizeof(struct data);
	data->seq = 1;
	data->ttl = 1;
	Gettimeofday(&data->tv, NULL);

	struct sockaddr destaddr;
	printf("\n%d\n",datalen);
	printf("sendfd= %d\n", sendfd);
	Sendto(sendfd, sendbuf, datalen, 0, &destaddr, sizeof(destaddr));
	printf("helo");
	int n;
	struct icmp *icmp;
	int icmplen;
	for (;;) {
		n = recvfrom(recvfd, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
		if (n < 0) {
			if (errno == EINTR) {
				continue;
			} else {
				perror("recvfrom");
				exit(1);
			}
			ip = (struct ip *) recvbuf;
			int hlen = ip->ip_hl << 2;
			icmp = (struct icmp *) (recvbuf + hlen);
			if ((icmplen = n - hlen) < 0)
				continue;
			printf("code = %d \n", icmp->icmp_code);
		}
	}

}
