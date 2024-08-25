/*
 * tcpclient_1.c
 *
 *  Created on: Jul 27, 2015
 *      Author: yamorn
 */

#include "../lib/common.h"

#define	MAXLINE	4096

void talk_to_server(FILE *fp, int sockfd);

int main(int argc, char *argv[]) {
	int sockfd;
	struct sockaddr_in servaddr;

	/* initialize servaddr */
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8088);
	sun_inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

	/* create tcp socket */
	sockfd = sun_socket(AF_INET, SOCK_STREAM, 0);

	/* make tcp connection */
	sun_connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	talk_to_server(stdin, sockfd);

	exit(0);

}

void talk_to_server(FILE *fp, int sockfd){
	int maxfdp1;
	fd_set rset;	// read set
	char sendline[MAXLINE], recvline[MAXLINE];

	FD_ZERO(&rset);		// initialize

	while(1){
		/*
		 * select modifies the descriptor sets pointed to by the readset,writeset and exceptset pointers.
		 * These three arguments are value-result arguments. When we call the function, we specify the
		 * values of the descriptors that we are interested in, and on return, the result indicates which
		 * descriptors are ready. Any descriptor that is not ready on return will have its corresponding
		 * bit cleared in the descriptor set. To handle this, we turn on all the bits in which we are
		 * interested in all the descriptor sets each time we call select.
		 */
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = sun_max(fileno(fp), sockfd) + 1;

		sun_select(maxfdp1, &rset, NULL, NULL, NULL);

		if(FD_ISSET(sockfd, &rset)){	// socket is readable
			if(sun_readline(sockfd, recvline, MAXLINE) == 0){
				perror("sun_readline");
				exit(1);
			}
			sun_fputs(recvline, stdout);
		}

		if(FD_ISSET(fileno(fp), &rset)){ 	// input is readable
			if(sun_fgets(sendline, MAXLINE, fp) == NULL){
				return;		// all done
			}
			sun_writen(sockfd, sendline, strlen(sendline));
		}
	}


}
