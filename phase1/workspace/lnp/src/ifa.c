/*
 * ifa.c
 *
 *  Created on: May 5, 2015
 *      Author: louis
 */

#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <net/if.h>

int main(int argc, char **argv) {
	struct ifaddrs *ifaddr, *ifa;
	int family, s;
	char host[NI_MAXHOST];
	char netmask[NI_MAXHOST];
	char bcast[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs");
		exit(1);
	}
	/* Walk through linked list, maintaining head pointer so we can free list later */
	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;
		family = ifa->ifa_addr->sa_family;

		printf("%s\taddress family:%d%s\n", ifa->ifa_name, family,
				(family == AF_PACKET) ? " (AF_PACKET)" :
				(family == AF_INET) ? " (AF_INET)" :
				(family == AF_INET6) ? " (AF_INET6)" : "");
		/* for an AF_INET* interface address, display the address */
		if (family == AF_INET || family == AF_INET6) {
			s = getnameinfo(ifa->ifa_addr,
					(family == AF_INET) ?
							sizeof(struct sockaddr_in) :
							sizeof(struct sockaddr_in6), host, NI_MAXHOST, NULL,
					0, NI_NUMERICHOST);
			if (s != 0) {
				printf("getnameinfo() failed:%s\n", gai_strerror(s));
				exit(EXIT_FAILURE);
			}
			printf("\taddress:<%s>\n", host);

			s = getnameinfo(ifa->ifa_netmask,
					(family == AF_INET) ?
							sizeof(struct sockaddr_in) :
							sizeof(struct sockaddr_in6), netmask, NI_MAXHOST,
					NULL, 0, NI_NUMERICHOST);
			if (s != 0) {
				printf("getnameinfo() failed:%s\n", gai_strerror(s));
				exit(EXIT_FAILURE);
			}
			if (ifa->ifa_ifu.ifu_broadaddr != NULL) {
				s = getnameinfo(ifa->ifa_ifu.ifu_broadaddr,
						(family == AF_INET) ?
								sizeof(struct sockaddr_in) :
								sizeof(struct sockaddr_in6), bcast, NI_MAXHOST,
						NULL, 0, NI_NUMERICHOST);
				if (s != 0) {
					printf("getnameinfo() failed:%s\n", gai_strerror(s));
					exit(EXIT_FAILURE);
				}
			}
			printf("\tnetmask:<%s>\n\tbcast:<%s>\t", netmask, bcast);
			if (ifa->ifa_flags & IFF_UP)
				printf("UP ");
			if (ifa->ifa_flags & IFF_BROADCAST)
				printf("BCAST ");
			if (ifa->ifa_flags & IFF_MULTICAST)
				printf("MCAST ");
			if (ifa->ifa_flags & IFF_LOOPBACK)
				printf("LOOP ");
			if (ifa->ifa_flags & IFF_POINTOPOINT)
				printf("P2P ");
			if (ifa->ifa_flags & IFF_RUNNING)
				printf("RUNNING ");
			printf("\n");

		}
	}
	freeifaddrs(ifaddr);
	exit(EXIT_SUCCESS);

}
