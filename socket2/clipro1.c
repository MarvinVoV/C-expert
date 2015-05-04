#include "ptc.h"

void cliprocess(FILE *fp, int sockfd){
	char writebuf[MAXLEN],readbuf[MAXLEN];
	int n;
	while(fgets(writebuf, MAXLEN, fp) != NULL){
		writen(sockfd, writebuf, strlen(writebuf));
		
		if((n = readline(sockfd, readbuf, MAXLEN)) <= 0){
			perror("client: server terminated permaturely");
			exit(1);
		}
		printf("n=%d\n",n);
		write(fileno(stdout), readbuf, n);
		fflush(stdout);	
	}
}
