/*
 * tcpcli01.c
 *
 *  Created on: Jul 19, 2015
 *      Author: yamorn
 */
#include "../lib/common.h"
#define	MAXLINE	4096

void str_cli(FILE *fp, int sockfd);

int main_tt(int argc, char *argv[]) {
	int sockfd, res;
	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("sockfd");
		exit(-1);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8088);
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

	res = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if (res == -1) {
		perror("connect");
		exit(-1);
	}
	str_cli(stdin, sockfd);

	exit(0);

}

void str_cli(FILE *fp, int sockfd) {
	char sendline[MAXLINE], recvline[MAXLINE];

	while (fgets(sendline, MAXLINE, fp) != NULL) {
		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0) {
			fprintf(stderr, "str_cli: server terminated prematurely");
			exit(-1);
		}

		fputs(recvline, stdout);
	}
}

