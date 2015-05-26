#include "yamorn.h"
#include "traceroute.h"

int main(int argc, char **argv) {
	int c;
	char *hostname;
	struct addrinfo *ai;
	struct sockaddr_in sinaddr;
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
	printf("traceroute to %s (%s): %d hops max, %d data bytes\n",ai->ai_canonname ? ai->ai_canonname : host, hostname, max_ttl, datalen);

	sport = 44445;
	((struct sockaddr_in *)ai->ai_addr)->sin_port = htons(sport);

	recvfd = Socket(ai->ai_family, SOCK_RAW, IPPROTO_ICMP);

	sendfd = Socket(ai->ai_family, SOCK_DGRAM, IPPROTO_UDP);
	int ttl = 5;

	/* only bind port */
	sinaddr.sin_family = ai->ai_family;
	sinaddr.sin_port = 44448;

	Bind(sendfd, (struct sockaddr *)&sinaddr, sizeof(sinaddr));
	Setsockopt (sendfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
	const char *p= "hello";

	setSockPort(ai->ai_addr, 44448);
	Sendto(sendfd, p, 6, 0, ai->ai_addr , ai->ai_addrlen);
	printf("after send\n");
	struct sockaddr addr;
	bzero(&addr, sizeof(addr));
	socklen_t len = sizeof(addr);
//
	for(;;){
		Recvfrom(recvfd, recvbuf, sizeof(recvbuf), 0 , &addr, &len);
		printf("len=%ld\n",strlen(recvbuf));
	}
//
	Close(sendfd);
	Close(recvfd);
}
