#include "yamorn.h"
#include "udpdemo.h"
int main(void) {
	struct sockaddr_in saserv, sacli;
	socklen_t saddrlen = sizeof(saserv);
	int sockfd;
	sockfd = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	bzero(&saserv, saddrlen);

	saserv.sin_family = AF_INET;
	saserv.sin_port = htons(PORT);
	saserv.sin_addr.s_addr = htonl(INADDR_ANY);

	int yes = 1;
	Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	Bind(sockfd, (struct sockaddr *) &saserv, sizeof(saserv));


	for (;;) {
		printf("Waiting for data ...\n");
		fflush(stdout);

		Recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr *) &sacli, &saddrlen);
		printf("recv from %s:%d\n", inet_ntoa(sacli.sin_addr),
				ntohs(sacli.sin_port));
		printf("recv data: %s\n", buf);
		// reply
		Sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *) &sacli,
				saddrlen);
	}
	Close(sockfd);
	exit(0);
}
