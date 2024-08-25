/*
 * recvicmp.c
 *
 *  Created on: May 10, 2015
 *      Author: yamorn
 */
#include "yamorn.h"

#define BUFLEN 1500
int main(int argc, char **argv){
	struct sockaddr_in servaddr;
	char buf[BUFLEN];
	int sockfd;
	socklen_t addrlen;

	sockfd = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

	addrlen = sizeof(servaddr);
	bzero(&servaddr, addrlen);

	ssize_t n;
	struct ip *ip, *ip2;
	struct icmp *icmp;
	struct updhdr *udp;
	int ipHeaderLen, icmpLen , ipHeaderLen2;
	for(;;){
		n = Recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&servaddr, &addrlen);
		printf("n=%ld\n", n);
		if(n < 0){
			if(errno == EINTR){
				continue;
			}else{
				perror("recvfrom");
				break;
			}
		}

		ip = (struct ip *)buf;	/* start of IP header */
		ipHeaderLen =ip->ip_hl << 2;/* length of IP header */
		icmp = (struct icmp *)(buf + ipHeaderLen); /* start of ICMP header */

		if((icmpLen = n - ipHeaderLen) < 8)
			continue;				/* not enough to look at ICMP header */
		if(icmp->icmp_type == ICMP_TIMXCEED && icmp->icmp_code == ICMP_TIMXCEED_INTRANS){
			if(icmpLen < 8 + sizeof(struct ip)){
				continue;			/* not enough data to look up at inner IP */
			}

			ip2 = (struct ip *)(buf + ipHeaderLen + 8);
			ipHeaderLen2 = ip2->ip_hl << 2;
			if(icmpLen < 8 + ipHeaderLen2 + 4)
				continue;				/* not enough to look at UDP port */

			udp = (struct udphdr *)(buf + ipHeaderLen + 8 + ipHeaderLen2);
			if(ip2->ip_p == IPPROTO_UDP){
					break;
			}
		}else if(icmp->icmp_type == ICMP_UNREACH){
			if(icmpLen < 8 + sizeof(struct ip))
				continue;				/* not enough data to look at inner IP */
			ip2 = (struct ip *)(buf + ipHeaderLen + 8);
			ipHeaderLen2 = ip2->ip_hl << 2;
			if(icmpLen < 8 + ipHeaderLen2 + 4)
				continue;				/* not enough to look at UDP port */
			udp = (struct udphdr *)(buf + ipHeaderLen + 8 + ipHeaderLen2);

			if (ip2->ip_p == IPPROTO_UDP)
				break;


		}
		printf(" (from %s: type = %d, code = %d)\n", Sock_ntop_host(&servaddr, sizeof(servaddr)),
				icmp->icmp_type, icmp->icmp_code);


	}

	Close(sockfd);
	exit(0);
}

