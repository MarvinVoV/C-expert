#include "yamorn.h"
#include "traceroute.h"

int main(int argc, char **argv) {
	int c;
	char *hostname;
	struct addrinfo *ai;
	struct sockaddr addr, bindaddr;
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

	ai = Getaddrinfo(hostname, "discard", AF_UNSPEC, SOCK_DGRAM);
	host = Sock_ntop_host(ai->ai_addr, ai->ai_addrlen);
	printf("traceroute to %s (%s): %d hops max, %d data bytes\n",ai->ai_canonname ? ai->ai_canonname : host, hostname, max_ttl, datalen);

	recvfd = Socket(ai->ai_family, SOCK_RAW, IPPROTO_ICMP);

	sendfd = Socket(ai->ai_family, SOCK_DGRAM, IPPROTO_UDP);
	int ttl = 1;

	sport = 23334;

	Bind(sendfd, &bindaddr, sizeof(bindaddr));
	Setsockopt (sendfd, IPPROTO_IP, IP_TTL, (char *)&ttl, sizeof(ttl));
	const char *p= "hello";
	ai->ai_flags = 0;
	ai->ai_next = 0;

	printf("zz=%d\n",((struct sockaddr_in *)ai->ai_addr)->sin_port);
	Sendto(sendfd, p, 6, 0, ai->ai_addr , ai->ai_addrlen);
	printf("hello");

	socklen_t len = sizeof(addr);

	for(;;){
		Recvfrom(recvfd, recvbuf, sizeof(recvbuf), 0 , &addr, &len);
		printf("len=%ld\n",strlen(recvbuf));
	}

	Close(sendfd);
}
