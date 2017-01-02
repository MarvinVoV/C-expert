#include <stdio.h>
#include <stdlib.h>
#include <string.h>				// strcpy(), memset(), memcpy()
#include <unistd.h>				// close()
#include <stdint.h>				// uint8_t, uint16_6
#include <sys/socket.h>			// socket()
#include <netinet/if_ether.h>	// ETH_P_ARP = 0x0806
#include <netinet/in.h>			// IPPROTO_RAW, INET_ADDRSTRLEN
#include <netinet/ip.h>			// IP_MAXPACKET (which is 65535)
#include <net/if.h>				// struct ifreq, IFNAMSIZ
#include <sys/ioctl.h>			// ioctl
#include <error.h>				// error, perror()


uint8_t *getmacaddr(char *);


int main(int argc, char **argv) {

	char *interface = "ens33";

	struct ether_arp arp;

	int sockfd;

	uint8_t src_mac[6], dst_mac[6];

	getmacaddr(interface, src_mac);



}


uint8_t *getmacaddr(char *iface) {
	int fd;
	struct ifreq ifr;

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, iface, IFNAMSIZ - 1);

	ioctl(fd, SIOCGIFHWADDR, &ifr);

	close(fd);

	macaddr = (uint8_t *) ifr.ifr_hwaddr.sa_data;

	printf("Mac : %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n" , mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	return macaddr;
}


