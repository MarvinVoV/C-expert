#include "unp.h"

void str_echo(int sockfd);

int main(int argc, char **argv){
    int                 listenfd, connfd;
    pid_t               childpid;
    socklen_t           clilen;
    struct sockaddr_in  cliaddr, servaddr;
    int                 ret;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    ret = bind(listenfd,(struct sockaddr *) &servaddr, sizeof(servaddr));
    if(ret != 0)
        perror("bind error\n");

    ret = listen(listenfd, 5);
    if(ret != 0)
        perror("listen error\n");

    for(; ;){
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
        if(connfd <= 0)
            perror("accept error\n");
        
        if((childpid = fork()) == 0){ // child process
            close(listenfd);
            str_echo(connfd); // process the request
            exit(0);
        }
        close(connfd); // parent closes connected socket
    }
}

void str_echo(int sockfd){
    ssize_t n;
    char    buf[BUF_SIZE];
again:
    while((n = read(sockfd, buf, BUF_SIZE)) > 0)
        writen(sockfd, buf, n);
    if(n < 0 && errno == EINTR)
        goto again;
    else if(n < 0)
        perror("str_echo: read error.");
}
