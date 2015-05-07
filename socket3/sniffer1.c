#include "yamorn.h"

#define BUF_SIZ 65536

static struct sockaddr_in src, dst;
static int sockfd;
static FILE *logfile;
static int total;
static int udp;
static int tcp;
static int icmp;
static int igmp;
static int others;

static void processPacket(unsigned char *buffer, int size);
static void printIpHeader(unsigned char *buffer, int size);
static void printTcpPacket(unsigned char *buffer, int size);
static void printUdpPacket(unsigned char *buffer, int size);
static void printIcmpPacket(unsigned char* buffer , int size);
static void printData(unsigned char* data , int size);

int main(void){
    struct sockaddr saddr;
    int data_len;
    socklen_t saddr_len = sizeof(saddr);

    unsigned char *buffer = (unsigned char *)malloc(BUF_SIZ);

    logfile = Fopen("log.txt","w");

    printf("Starting...\n");

    sockfd = Socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

    for(;;){
		data_len = Recvfrom(sockfd, buffer, BUF_SIZ, 0, &saddr, &saddr_len);
		processPacket(buffer, data_len);
    }

    Close(sockfd);
    printf("finished.");
    exit(0);
}

void processPacket(unsigned char *buffer, int size){
    /* Get the IP header part of this packet */
    struct iphdr *iph = (struct iphdr *)buffer;
    ++total;
    switch(iph->protocol){
	case IPPROTO_ICMP:
	    ++icmp;
	    break;
	case IPPROTO_IGMP:
	    ++igmp;
	    break;
	case IPPROTO_TCP:
	    ++tcp;
	    printTcpPacket(buffer, size);
	    break;
	case IPPROTO_UDP:
	    ++udp;
	    printUdpPacket(buffer, size);
	    break;
	default:
	    ++others;
    }
     printf("TCP : %d   UDP : %d   ICMP : %d   IGMP : %d   Others : %d   Total : %d\r",
	     tcp,udp,icmp,igmp,others,total);
}

void printIpHeader(unsigned char *buffer, int size){
    unsigned short iphdrlen;
    struct iphdr *iph = (struct iphdr *)buffer;
    iphdrlen = iph->ihl * 4;

    memset(&src, 0 , sizeof(src));
    src.sin_addr.s_addr = iph->saddr;

    memset(&dst, 0, sizeof(src));
    dst.sin_addr.s_addr = iph->daddr;

    fprintf(logfile, "\n");
    fprintf(logfile, "IP Header\n");
    fprintf(logfile, "\t|-IP Version	    : %d\n", (unsigned int)iph->version);
    fprintf(logfile, "\t|-IP Header length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl, ((unsigned int)(iph->ihl)) * 4);
    fprintf(logfile, "\t|-Type Of Service   : %d\n",(unsigned int)iph->tos);
    fprintf(logfile, "\t|-IP Total Length   : %d  Bytes(size of Packet)\n",ntohs(iph->tot_len));
    fprintf(logfile, "\t|-Identification    : %d\n",ntohs(iph->id));
    fprintf(logfile, "\t|-TTL      	    : %d\n",(unsigned int)iph->ttl);
    fprintf(logfile, "\t|-Protocol          : %d\n",(unsigned int)iph->protocol);
    fprintf(logfile, "\t|-Checksum          : %d\n",ntohs(iph->check));
    fprintf(logfile, "\t|-Source IP         : %s\n",inet_ntoa(src.sin_addr));
    fprintf(logfile, "\t|-Destination IP    : %s\n",inet_ntoa(dst.sin_addr));
    
}


void printTcpPacket(unsigned char *buffer, int size){
	unsigned short iphdrlen;
	struct iphdr *iph = (struct iphdr *)buffer;
	iphdrlen = iph->ihl * 4;
	struct tcphdr *tcph = (struct tcphdr *)(buffer + iphdrlen);
	fprintf(logfile,"\n\n***********************TCP Packet*************************\n");   
	
	printIpHeader(buffer, size);
	         
	fprintf(logfile,"\n");
    fprintf(logfile,"TCP Header\n");
    fprintf(logfile,"   |-Source Port      		: %u\n",ntohs(tcph->source));
    fprintf(logfile,"   |-Destination Port      : %u\n",ntohs(tcph->dest));
    fprintf(logfile,"   |-Sequence Number       : %u\n",ntohl(tcph->seq));
    fprintf(logfile,"   |-Acknowledge Number    : %u\n",ntohl(tcph->ack_seq));
    fprintf(logfile,"   |-Header Length         : %d DWORDS or %d BYTES\n" ,(unsigned int)tcph->doff,(unsigned int)tcph->doff*4);
    fprintf(logfile,"   |-Urgent Flag           : %d\n",(unsigned int)tcph->urg);
    fprintf(logfile,"   |-Acknowledgement Flag  : %d\n",(unsigned int)tcph->ack);
    fprintf(logfile,"   |-Push Flag             : %d\n",(unsigned int)tcph->psh);
    fprintf(logfile,"   |-Reset Flag            : %d\n",(unsigned int)tcph->rst);
    fprintf(logfile,"   |-Synchronise Flag      : %d\n",(unsigned int)tcph->syn);
    fprintf(logfile,"   |-Finish Flag           : %d\n",(unsigned int)tcph->fin);
    fprintf(logfile,"   |-Window                : %d\n",ntohs(tcph->window));
    fprintf(logfile,"   |-Checksum              : %d\n",ntohs(tcph->check));
    fprintf(logfile,"   |-Urgent Pointer        : %d\n",tcph->urg_ptr);
    fprintf(logfile,"\n");
    fprintf(logfile,"                        DATA Dump                         ");
    fprintf(logfile,"\n");
         
    fprintf(logfile, "IP Header\n");
    printData(buffer, iphdrlen);
    
    fprintf(logfile, "TCP Header\n");
    printData(buffer + iphdrlen + tcph->doff*4, (size - tcph->doff * 4 - iph->ihl * 4));
    fprintf(logfile, "\n###########################################################");
}

void printUdpPacket(unsigned char *buffer , int size){ 
    unsigned short iphdrlen;   
    struct iphdr *iph = (struct iphdr *)buffer;
    iphdrlen = iph->ihl * 4;
     
    struct udphdr *udph = (struct udphdr*)(buffer + iphdrlen);
     
    fprintf(logfile, "\n\n***********************UDP Packet*************************\n");
     
    printIpHeader(buffer, size);      
     
    fprintf(logfile, "\nUDP Header\n");
    fprintf(logfile, "   |-Source Port      : %d\n" , ntohs(udph->source));
    fprintf(logfile, "   |-Destination Port : %d\n" , ntohs(udph->dest));
    fprintf(logfile, "   |-UDP Length       : %d\n" , ntohs(udph->len));
    fprintf(logfile, "   |-UDP Checksum     : %d\n" , ntohs(udph->check));
     
    fprintf(logfile, "\n");
    fprintf(logfile, "IP Header\n");
    printData(buffer , iphdrlen);
         
    fprintf(logfile,"UDP Header\n");
    printData(buffer + iphdrlen , sizeof udph);
         
    fprintf(logfile, "Data Payload\n");  
    printData(buffer + iphdrlen + sizeof udph ,( size - sizeof udph - iph->ihl * 4 ));
     
    fprintf(logfile, "\n###########################################################");
}

void printIcmpPacket(unsigned char* buffer , int size){
    unsigned short iphdrlen;
     
    struct iphdr *iph = (struct iphdr *)buffer;
    iphdrlen = iph->ihl * 4;
     
    struct icmphdr *icmph = (struct icmphdr *)(buffer + iphdrlen);
             
    fprintf(logfile, "\n\n***********************ICMP Packet*************************\n");   
     
    printIpHeader(buffer, size);      
             
    fprintf(logfile, "\n");
         
    fprintf(logfile, "ICMP Header\n");
    fprintf(logfile, "   |-Type : %d",(unsigned int)(icmph->type));
             
    if((unsigned int)(icmph->type) == 11) 
        fprintf(logfile, "  (TTL Expired)\n");
    else if((unsigned int)(icmph->type) == ICMP_ECHOREPLY) 
        fprintf(logfile, "  (ICMP Echo Reply)\n");
    fprintf(logfile, "   |-Code : %d\n", (unsigned int)(icmph->code));
    fprintf(logfile, "   |-Checksum : %d\n", ntohs(icmph->checksum));
    fprintf(logfile, "\n");
 
    fprintf(logfile, "IP Header\n");
    printData(buffer, iphdrlen);
         
    fprintf(logfile, "UDP Header\n");
    printData(buffer + iphdrlen , sizeof icmph);
         
    fprintf(logfile,"Data Payload\n");  
    printData(buffer + iphdrlen + sizeof icmph , (size - sizeof icmph - iph->ihl * 4));
     
    fprintf(logfile, "\n###########################################################");
}

void printData(unsigned char* data , int size){
    int i, j;
    for(i = 0 ; i < size ; i++){
        if( i != 0 && i % 16 == 0){   //if one line of hex printing is complete...     
            fprintf(logfile,"         ");
            for(j = i-16 ; j<i ; j++){   
                if(data[j] >= 32 && data[j] <= 128)
                    fprintf(logfile, "%c", (unsigned char)data[j]); //if it is a number or alphabet
                else 
                	fprintf(logfile, "."); //otherwise print a dot
            }
            fprintf(logfile, "\n");
        } 
         
        if(i%16==0) 
        	fprintf(logfile,"   ");
        fprintf(logfile, " %02X", (unsigned int)data[i]);
                 
        if( i == size-1){  //print the last spaces
            for(j = 0; j< 15 - i % 16; j++) 
            	fprintf(logfile, "   "); //extra spaces
            	
            fprintf(logfile,"         ");
             
            for(j = i-i % 16 ; j <= i; j++){
                if(data[j] >= 32 && data[j] <= 128) 
                	fprintf(logfile, "%c", (unsigned char)data[j]);
                else 
                	fprintf(logfile, ".");
            }
            fprintf(logfile, "\n");
        }
    }
}

















