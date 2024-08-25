#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#define BUF_SIZE 2048 * 2

int main(int argc, char **argv){
    struct msghdr msg;
    struct iovec iov;
    struct timeval tval;
    char recvbuf[BUF_SIZ];
    size_t sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_ICMP);
    if (sockfd == -1) {
        perror("socket error");
        exit(-1);
    }
    
    iov.iov_base = recvbuf;
    iov.iov_len = sizeof(recvbuf);
    

}