#include "unp.h"

#define UNIXSTR_PATH "/tmp/unix_socket"
void str_cli(FILE * , int);

int main(int argc, char **argv){
    int     sockfd;
    struct sockaddr_un servaddr;

    sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket error");
        exit(-1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);

    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) != 0) {
        perror("connect error");
        exit(-1);
    }

    str_cli(stdin, sockfd);
    exit(0);
}

void str_cli(FILE *fp, int sockfd){
    char sendline[BUF_SIZE], recvline[BUF_SIZE];

    while(fgets(sendline, BUF_SIZE, fp) != NULL){
        writen(sockfd, sendline, strlen(sendline));

        if(readline(sockfd, recvline, BUF_SIZE) == 0){
            perror("str_cli: server terminated prematurely");
            exit(-1);
        }

        fputs(recvline, stdout);
    }
}