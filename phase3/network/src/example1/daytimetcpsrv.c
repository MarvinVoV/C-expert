/*
 * daytimetcpsrv.c
 *
 *  Created on: Jul 19, 2015
 *      Author: yamorn
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAXLINE 30
int main_t7(int argc, char *argv[]){
	int listenfd, connfd, res;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[MAXLINE];
	time_t ticks;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == -1){
		perror("socket");
		exit(-1);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8088);

	res = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(res == -1){
		perror("bind");
		exit(-1);
	}

	res = listen(listenfd, 5);
	if(res == -1){
		perror("listen");
		exit(-1);
	}

	for(;;){
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
		if(connfd < 0){
			perror("accept");
			exit(-1);
		}

		const char *paddr = inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff));
		printf("connection from %s , port %d\n", *paddr, ntohs(cliaddr.sin_port));
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

		write(connfd, buff, sizeof(buff));

		close(connfd);
	}

	return 0;

}
