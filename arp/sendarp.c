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



}


