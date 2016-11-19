#include "unp.h"

#define UNIXSTR_PATH "/tmp/unix_socket"

void sig_chld(int);

void str_echo(int);

int main(int argc, char **argv) {
    int         listenfd, connfd;
    pid_t       childpid;
    socklen_t   clilen;
    struct sockaddr_un  cliaddr, servaddr;

    listenfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("listenfd error");
        exit(-1);
    }

    unlink(UNIXSTR_PATH);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);

    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) != 0) {
        perror("bind error");
        exit(-1);
    }
    
    if (listen(listenfd, 5) != 0){
        perror("listen error");
        exit(-1);
    }

    signal(SIGCHLD, sig_chld);

    for (; ;) {
        clilen = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) {
            if (errno == EINTR)
                continue;   
            else {
                perror("accept error");
                exit(-1);
            }
        }
        if ((childpid = fork()) == 0) { // child process
            close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        close(connfd);  // parent closes connected socket
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

void sig_chld(int signo) {
    pid_t pid;
    int stat;

    while ((pid = waitpid(-1, &stat, WNOHANG) > 0))
        printf("child %d terminated \n", pid);
    return;
}