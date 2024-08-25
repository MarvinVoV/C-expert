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
    struct sockaddr_in dst;
    char datagram[PACKET_LEN];
    int yes = 1;

    iphd = (struct iphdr *)datagram;
    tcph = (struct tcphdr *)(datagrm + sizeof(struct iphdr));
    
    memset(datagram, 0 , PACKET_LEN);


    /* Fill in the IP header */
    iphd->ihl = 5;
    iphd->verion = 4;
    iphd->tos = 0;
    iphd->tot_len = sizeof(struct iphdr) + sizeof(struct tcphdr);
    iphd->id = htons(54321);
    iphd->frag_off = htons(16384);
    iphd->ttl = 64;
    iphd->protocol = IPPROTO_TCP;
    iphd->check = 0;  /* Set to 0 before calculating checksum */
    iphd->saddr = inet_addr(argv[1]); /* source ip */
    iphd->daddr = inet_addr(argv[2]); /* dest ip   */
    iphd->check = checksum((unsigned short *)datagram, iphd->tot_len >> 1);

    /* Fill TCP header */
    tcph->source = htons(80);
    tcph->dest = htons(80);
    tcph->seq = htonl(1105024978);
    tcph->ack_seq = 0;
    tcph->doff = sizeof(struct tcphdr) / 4; /* size of tcp header */
    tcph->fin = 0;
    tcph->syn = 1;
    tcph->rst = 0;
    tcph->psh = 0;
    tcph->ack = 0;
    tcph->urg = 0;
    tcph->window = htons(14600); /* maximum allowd window size */
    tcph->urg_ptr = 0;
    tcph->check = 0; /* If you set a checksum to 0, the kernel's IP stack should fill in the correct checksum during transmission */



    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if(sockfd < 0){
        perror(sockfd);
        exit(1);
    }
    /* IP_HDRINCL to tell the kernel that headers are include in the packet */
    if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &yes, sizeof(yes)) < 0){
        perror("setsockopt");
        exit(1);
    }
    
    printf("Starting send packet...\n");


    

    


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
