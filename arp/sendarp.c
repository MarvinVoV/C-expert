#include <stdio.h>
#include <stdlib.h>
#include <string.h>				// strcpy(), memset(), memcpy()
#include <unistd.h>
#include <stdint.h>				// uint8_t, uint16_6
#include <sys/socket.h>			// socket()
#include <netinet/if_ether.h>	// ETH_P_ARP = 0x0806
#include <netinet/in.h>			// IPPROTO_RAW, INET_ADDRSTRLEN
#include <netinet/ip.h>			// IP_MAXPACKET (which is 65535)
#include <ifaddrs.h>			// struct ifaddrs
#include <error.h>				// error, perror()


#define INTERFACE "ens33"

int main(int argc, char **argv) {

	char *interface = "ens33";

	struct ether_arp arp;

	int sockfd;

	uint8_t src_mac[6], dst_mac[6];

	getmacaddr(interface, src_mac);



}


void getmacaddr(char *interface, uint8_t *macaddr) {
	struct ifaddr *iflist;
	if (getifaddrs(&iflist) == 0) {
		for (struct ifaddr *cur = iflist; cur; cur = cur->ifa_next) {
			if (cur->ifa_addr->sa_family == AF_LINK && cur->ifa_addr) {
				//struct sockaddr_dl* sdl = (struct sockaddr_dl*)cur->ifa_addr;
				//uint8_t *ptr = (uint8_t *)LLADDR(sdl);
				printf("interface = %s\n", cur->ifa_name);
			}
		}
	}
}


