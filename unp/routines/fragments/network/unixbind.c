#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

int main(int argc, char **argv){
    int         sockfd;
    socklen_t   len;
    struct sockaddr_un  addr1, addr2;

    if (argc != 2){
        printf("usage: unixbind <pathname>\n");
        exit(0);
    }
    sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket error");
        exit(-1);
    }
    /* the bind will fail if the pathname already exists in the filesystem */
    unlink(argv[1]);    

    bzero(&addr1, sizeof(addr1));
    addr1.sun_family = AF_LOCAL;
    strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path) - 1);
    if (bind(sockfd, (struct sockaddr *) &addr1, SUN_LEN(&addr1)) != 0) {
        perror("bind error");
        exit(-1);
    }

    len = sizeof(addr2);
    getsockname(sockfd, (struct sockaddr *) &addr2, &len);
    printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);
    exit(0);
}