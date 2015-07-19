/*
 * tcpserv01.c
 *
 *  Created on: Jul 19, 2015
 *      Author: yamorn
 */

#include "../lib/common.h"
#define	MAXLINE	4096

void str_echo(int sockfd);

int main_t6(int argc, char *argv[]) {
	int listenfd, connfd, res;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd == -1) {
		perror("listenfd");
		exit(-1);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8088);

	res = bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if (res == -1) {
		perror("bind");
		exit(-1);
	}

	res = listen(listenfd, 5);
	if (res == -1) {
		perror("listen");
		exit(-1);
	}

	for (;;) {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
		if (connfd == -1) {
			perror("accept");
			exit(-1);
		}

		if ((childpid = fork()) == 0) { // child process
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd); // parent close connected socket
	}
	exit(0);

}

void str_echo(int sockfd) {
	ssize_t n;
	char buf[MAXLINE];
	again: while ((n = read(sockfd, buf, MAXLINE)) > 0) {
		Writen(sockfd, buf, n);
	}
	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		perror("str_echo: read error");
}

