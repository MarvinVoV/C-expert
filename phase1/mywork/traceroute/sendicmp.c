#include "yamorn.h"

int main(int argc, char **argv[]){

    struct sockaddr_in dst, rcv;
    int sockfd;
    char buf[1500];
    int ttl = 1;
    int size = sizeof(rcv);

    bzero(&buf, sizeof(buf));
    bzero(&dst, sizeof(dst));
    dst.sin_family = AF_INET;
    dst.sin_addr.s_addr = inet_addr("119.75.217.109");
    dst.sin_port = htons(46665);


    sockfd = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    Setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));

    Sendto(sockfd, "hello", 6, 0, (struct sockaddr *)&dst, sizeof(dst));

    for(;;){
    	recvfrom(sockfd, buf, 1500, 0, (struct sockaddr *)&rcv, &size);

    	printf("Received packet from %s:%d\nData: %s\n\n", inet_ntoa(rcv.sin_addr), ntohs(rcv.sin_port), buf);
    }
    Close(sockfd);
    exit(0);

    
    
}
