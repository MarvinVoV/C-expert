#include "ptc.h"

void cliprocess(FILE *fp, int sockfd){
	int maxfdp1, stdineof;
	fd_set rset;
	char buf[MAXLEN];
	int n;

	stdineof = 0;
	FD_ZERO(&rset);
	for( ; ; ){
		if(stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		if(select(maxfdp1, &rset, NULL, NULL, NULL) < 0){
			perror("select error");
			exit(1);
		}

		if(FD_ISSET(sockfd, &rset)){ /* socket is readable */
			if((n = read(sockfd, buf, MAXLEN)) == 0){
				if(stdineof == 1)
					return; /* normal ternimation */
				else{
					perror("server terminated prematurely");
					exit(1);
				}
			}	
			write(fileno(stdout), buf, n);
		}

		if(FD_ISSET(fileno(fp), &rset)){ /* input is readable */
			if((n = read(fileno(fp), buf, MAXLEN)) == 0){
				stdineof = 1;
				shutdown(sockfd, SHUT_WR); /* send FIN */
				FD_CLR(fileno(fp), &rset);
				continue;
			}
			writen(sockfd, buf , n);
		}
	}
}
