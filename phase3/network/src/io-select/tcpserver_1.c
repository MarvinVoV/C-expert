/*
 * tcpserver_1.c
 *
 *  Created on: Jul 27, 2015
 *      Author: yamorn
 */


#include "../lib/common.h"

#define	MAXLINE	4096

void echo_to_client(int sockfd);

int main_tll(int argc, char *argv[]) {
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	/* initialize variable */
	clilen = sizeof(cliaddr);

	/* initialize servaddr */
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8088);

	/* create listen socket */
	listenfd = sun_socket(AF_INET, SOCK_STREAM, 0);

	sun_bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	sun_listen(listenfd, 5);

	while (1) {
		connfd = sun_accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);

		char ip_str[16];
		sun_inet_ntop(AF_INET, &cliaddr.sin_addr, ip_str, sizeof(ip_str));
		printf("connect to client %s success.\n", ip_str);

		if ((childpid = fork()) == 0) { // child process
			close(listenfd);
			echo_to_client(connfd);
			exit(0);
		}
		close(connfd); // parent close connected socket
	}
	exit(0);

}

void echo_to_client(int sockfd) {
	ssize_t n;
	char buf[MAXLINE];
	again: while ((n = read(sockfd, buf, MAXLINE)) > 0) {
		sun_writen(sockfd, buf, n);
	}
	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		perror("str_echo: read error");
}

