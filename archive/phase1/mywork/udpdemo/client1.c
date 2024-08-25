#include "yamorn.h"
#include "udpdemo.h"

int main(int argc, char **argv) {

	int sockfd;
	struct addrinfo *ai;

	/* If services is NULL, the port number of the returned socket address will be left uninitialized */
	ai = Getaddrinfo(SERVER, NULL, AF_UNSPEC, 0);
	((struct sockaddr_in *)ai->ai_addr)->sin_port = htons(PORT);

	sockfd = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


	while (fgets(msg, BUFLEN, stdin) != NULL) {
		Sendto(sockfd, msg, strlen(msg) + 1, 0, ai->ai_addr, ai->ai_addrlen);
		bzero(buf, BUFLEN);
		Recvfrom(sockfd, buf, BUFLEN, 0, ai->ai_addr, &ai->ai_addrlen);
		printf("server reply: %s", buf);
	}
	Close(sockfd);
	exit(0);

}

