#include "ptc.h"

void servprocess(int sockfd){
	ssize_t n;
	char buf[MAXLEN];

again:
	while((n = read(sockfd, buf, MAXLEN)) > 0){
		writen(sockfd, buf, n);	
		printf("server: write %ld bytes\n",n);
	}
	if(n < 0 && errno == EINTR)
		goto again;
	else if(n < 0){
		perror("read error");
		exit(1);
	}
}
