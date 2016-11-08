#include "unp.h"

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen);

void dg_cliaddr(FILE *fp, int sockfd, struct sockaddr *pservaddr, socklen_t servlen);

int main(int argc, char **argv) {
    int                 sockfd;
    struct sockaddr_in  servaddr;

    if (argc != 2) {
        fprintf(stdout, "Usage: echoclient <IPAddress>\n");
        exit(0);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    // servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_port = htons(7);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // dg_cli(stdin, sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    dg_cliaddr(stdin, sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

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

void dg_cliaddr(FILE *fp, int sockfd, struct sockaddr *pservaddr, socklen_t servlen) {
    int         n;
    char        sendline[BUF_SIZE], recvline[BUF_SIZE + 1];
    socklen_t   len;
    struct sockaddr *preply_addr;

    preply_addr = malloc(servlen);

    while (fgets(sendline, BUF_SIZE, fp) != NULL) {
        sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
      
        len = servlen;
        n = recvfrom(sockfd, recvline, BUF_SIZE, 0, preply_addr, &len);
        /*
         * memcmp compares every byte of data in the two socket address structure,
         * and the length field is set in the socket address structure that the kernel 
         * returns; so in this case we must set it when constructing the sockaddr
         *
         */
        pservaddr->sa_len = len;
        if (len != servlen || memcmp(pservaddr, preply_addr, len) != 0) {
            printf("reply from %s (ignored) \n", sock_ntop(preply_addr, len));
            continue;
        }
        recvline[n] = 0;    // null terminate
        fputs(recvline, stdout);
    }
}
