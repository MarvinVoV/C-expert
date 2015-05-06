#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <string.h>

int main(void){
	struct ifreq ifr,*ifrp;
	struct ifconf ifc;
	int sockfd;
	char buf[2048];


	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if(sockfd == -1){
		perror("socket");
		exit(1);
	}

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;
	if(ioctl(sockfd, SIOCGIFCONF, &ifc) == -1){
		perror("ioctl");
		exit(1);
	}
	
	ifrp = ifc.ifc_req;	

	exit(0);
	

	
}
