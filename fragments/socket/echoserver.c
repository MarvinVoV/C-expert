#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERV_PORT 8080

int main(int argc, char **argv){
    int                 listenfd, connfd;
    pid_t               childpid;
    socklen_t           chilen;
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

    



     

    
}
