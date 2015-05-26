#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <errno.h>

#define PACKET_LEN 4096

char *hostname_to_ip(char *);

int main(int argc, char **argv){
    int sockfd;
    struct iphdr *iphd;
    struct tcphdr *tcph;
    struct sockaddr dst;
    char datagram[PACKET_LEN];

    iphd = (struct iphdr *)datagram;
    tcph = (struct tcphdr *)(datagrm + sizeof(struct iphdr));
    
    memset(datagram, 0 , PACKET_LEN);
    

    


}


/* Get IP from domain name */
char *hostname_to_ip(char *hostname){
    struct hostent *he;
    struct in_addr **addr_list;
    
    if(( he = gethostbyname(hostname)) == NULL){
        perror("gethostname");
        return NULL;
    }


    addr_list = (struct in_addr **)he->h_addr_list;
    while(*addr_list != NULL){
        char *tmp;
        /* Return the first one */
        tmp = inet_ntoa(**addr_list);
        addr_list++;
        return tmp;
    }
    return NULL;
}
