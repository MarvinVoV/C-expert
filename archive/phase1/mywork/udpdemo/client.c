#include "yamorn.h"
#include "udpdemo.h"

int main(int argc, char **argv) {
	struct sockaddr_in saserv;
	socklen_t saddrlen = sizeof(saserv);
	int sockfd;

	sockfd = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	bzero(&saserv, saddrlen);
	saserv.sin_family = AF_INET;
	saserv.sin_port = htons(PORT);
	Inet_aton(SERVER, &saserv.sin_addr);

	while (fgets(msg, BUFLEN, stdin) != NULL) {
		Sendto(sockfd, msg, strlen(msg) + 1, 0, (struct sockaddr *) &saserv,
				sizeof(saserv));
		bzero(buf, BUFLEN);
		Recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr *) &saserv,
				&saddrlen);
		printf("server reply: %s", buf);
	}
	Close(sockfd);
	exit(0);

}

