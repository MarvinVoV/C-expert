#include "unp.h"

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen);

int main(int argc, char **argv) {
    int                 sockfd;
    struct sockaddr_in  servaddr;

    if (argc != 2) {
        fprintf(stdout, "Usage: echoclient <IPAddress>\n");
        exit(0);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    dg_cli(stdin, sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    exit(0);
}

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen) {
    int     n;
    char    sendline[BUF_SIZE], recvline[BUF_SIZE + 1];

    while (fgets(sendline, BUF_SIZE, fp) != NULL) {
        sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        n = recvfrom(sockfd, recvline, BUF_SIZE, 0, NULL, NULL);

        recvline[n] = 0;    // null terminate
        fputs(recvline, stdout);
    }
}
