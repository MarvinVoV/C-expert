#include "yamorn.h"
#include "udpdemo.h"
int main(void) {
	struct sockaddr_in sacli;
	socklen_t saddrlen = sizeof(sacli);
	struct addrinfo *ai;
	int sockfd;
	sockfd = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	ai = Getaddrinfo(SERVER, NULL, AF_UNSPEC, 0);
	((struct sockaddr_in *)ai->ai_addr)->sin_port = htons(PORT);

	int yes = 1;
	Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	Bind(sockfd, ai->ai_addr, ai->ai_addrlen);

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
