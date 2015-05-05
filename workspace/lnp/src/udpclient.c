/*
 * udpclient.c
 *
 *  Created on: May 5, 2015
 *      Author: louis
 */
#include "gen.h"

void dg_cli(FILE *, int, const struct sockaddr *, socklen_t);

int main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in servaddr;

	if (argc != 2) {
		fprintf(stderr, "usage:%s <ip address>\n", argv[0]);
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		perror("inet_pton error");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		perror("socket error");
		exit(1);
	}
	/* echo process */
	dg_cli(stdin, sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	exit(0);

}

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr,
		socklen_t servlen) {
	ssize_t n;
	char sendbuf[MAXLEN], recvbuf[MAXLEN];
	while (fgets(sendbuf, MAXLEN, fp) != NULL) {
		sendto(sockfd, sendbuf, strlen(sendbuf), 0, pservaddr, servlen);

		n = recvfrom(sockfd, recvbuf, MAXLEN, 0, NULL, NULL);
		printf("recv %ld bytes from server\n", n);
		recvbuf[n] = 0; /* null terminate */
		fputs(recvbuf, stdout);
	}
}

