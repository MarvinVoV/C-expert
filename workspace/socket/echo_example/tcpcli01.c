#include "echo.h"

void str_cli(FILE *fp, int sockfd);

int main(int argc, char **argv){
    int                 sockfd;
    struct sockaddr_in  servaddr;
    int                 ret;

    if(argc != 2){
        perror("Usage: tcpcli <IPAddress>");
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    
    ret = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if(ret != 0){
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
