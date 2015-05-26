/*
 * udpserv.c
 *
 *  Created on: May 5, 2015
 *      Author: louis
 */
#include "gen.h"

void dg_echo(int, struct sockaddr *, socklen_t);

/**
 * udp server: socket --> bind --> recvfrom(block until datagram received from client) --> sendto
 * udp client: socket --> sendto --> recvfrom --> close
 */
int main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0); /* SOCK_DGRAM present UDP */
	if (sockfd == -1) {
		perror("socket error");
		exit(EXIT_FAILURE);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1) {
		perror("bind error");
		exit(EXIT_FAILURE);
	}
	//process echo
	dg_echo(sockfd,(struct sockaddr *)&cliaddr,sizeof(cliaddr));

}

void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen) {
	int n;
	socklen_t len;
	char msg[MAXLEN];
	for (;;) {
		len = clilen;
		n = recvfrom(sockfd, msg, MAXLEN, 0, pcliaddr, &len);
		if (n < 0) {
			perror("recvfrom error");
			exit(EXIT_FAILURE);
		}
		if (sendto(sockfd, msg, n, 0, pcliaddr, len) != n) {
			perror("sendto error");
			continue;
		}
	}
}

