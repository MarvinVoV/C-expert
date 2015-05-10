/*
 * sendarp.c
 *
 *  Created on: May 10, 2015
 *      Author: yamorn
 */

#include "yamorn.h"

#define BUF_SIZ 42
#define DEVICE "eth0"

int sockfd;
unsigned char buf[BUF_SIZ];
unsigned char src_mac[6]; /* source mac */

struct arp_packet {
	struct ether_header eh;
	struct ether_arp arp;
};

void sigint(int);

int main(int argc, char **argv) {

	/**
	 * Ethernet frame structure
	 *
	 **|** mac destination **|** mac source ***|** ethertype **|** payload **|** frame check seq**|
	 **|------ 6 bytes-------|---- 6 bytes ----|------ 2 ------|- 46 ~ 1500 -|------- 4 bytes ----|
	 **|*********************|*****************|***************|*************|********************|
	 **|--------------------- Ethernet header -----------------|---- ARP ----|--------------------|
	 */

	struct ethhdr *ehr = (struct ethhdr *) buf;
	struct arphdr *arphr = buf + sizeof(struct ethhdr);

	struct ifreq ifrq;
	struct sockaddr_ll slladdr;
	int ifindex; /* Ethernet Interface index */
	int yes = 1;
	int i;
	int sent;
	int length;	/* length of receive packet */

	sockfd = Socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP)); /* completely link-layer packet */
	Setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));

	strncpy(ifrq.ifr_name, DEVICE, strlen(DEVICE) + 1);
	if (ioctl(sockfd, SIOCGIFINDEX, &ifrq) < 0) { /* retrieve Ethernet interface index */
		perror("ioctl");
		exit(1);
	}
	ifindex = ifrq.ifr_ifindex;

	if (ioctl(sockfd, SIOCGIFHWADDR, &ifrq) < 0) { /* retrieve corresponding mac */
		perror("ioctl");
		exit(1);
	}
	for (i = 0; i < 6; i++) {
		src_mac[i] = ifrq.ifr_hwaddr.sa_data[i];
	}

	printf("Got source MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n",
			src_mac[0], src_mac[1], src_mac[2], src_mac[3], src_mac[4],
			src_mac[5]);


	slladdr.sll_family = AF_PACKET;				/* initialize sockaddr_ll */
	slladdr.sll_protocol = htons(ETH_P_ARP);
	slladdr.sll_ifindex = ifindex;
	slladdr.sll_hatype = htons(ARPHRD_ETHER);
	slladdr.sll_pkttype = 0;	// PACKET_OTHERHOST
	slladdr.sll_halen = 0;
	slladdr.sll_addr[6] = 0x00;
	slladdr.sll_addr[7] = 0x00;

	while(1){
		length = Recvfrom(sockfd, buf, BUF_SIZ, 0, NULL, NULL);
		if(htons(ehr->h_proto) ==  ETH_P_ARP){
            unsigned char buf_arp_dha[6];
            unsigned char buf_arp_dpa[4];

            if(htons(arphr->ar_op) !=  ARPOP_REQUEST)
            	continue;
            printf("buffer is---------------- %s \n",(char*)arphr);
		}
		sent = sendto(sockfd, buf, BUF_SIZ, 0, (struct sockaddr *)&slladdr, sizeof(slladdr));
	}



	Close(sockfd);

}

void sigint(int signo){
	/* clean up */
	struct ifreq ifrq;
	if(sockfd == -1)
		return;
	strncpy(ifrq.ifr_name, DEVICE, strlen(DEVICE) + 1);
	if(ioctl(sockfd, SIOCGIFFLAGS, &ifrq) < 0){
		perror("ioctl");
		exit(1);
	}
	 ifrq.ifr_flags &= ~IFF_PROMISC;
	 if(ioctl(sockfd, SIOCSIFFLAGS, &ifrq) < 0){
		perror("ioctl");
		exit(1);
	 }
	 close(sockfd);
	 printf("Server terminating....\n");
	 exit(0);
}
