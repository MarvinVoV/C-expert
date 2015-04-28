#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include "mysocket.h"
#include <string.h>

#define BUFLEN 128
extern int connect_retry(int,int,int,const struct sockaddr *,socklen_t);

void print_uptime(int sockfd){
	int n;
	char buf[BUFLEN];
	
	while((n=recv(sockfd,buf,BUFLEN,0))>0)
		write(STDOUT_FILENO,buf,n);
	if(n<0)
		error_handle(1,"recv error");
}

int main(int argc,char *argv[]){
	struct addrinfo *ailist,*aip;
	struct addrinfo hint;
	int sockfd,err;

	if(argc!=2){
		fprintf(stderr,"usage:%s hostname\n",argv[0]);
		exit(1);
	}
	memset(&hint,0,sizeof(hint));
	hint.ai_socktype=SOCK_STREAM;
	hint.ai_canonname=NULL;
	hint.ai_addr=NULL;
	hint.ai_next=NULL;
	if((err=getaddrinfo(argv[1],"ruptime",&hint,&ailist))!=0)
		error_handle(1,"getaddrinfo error");
	for(aip=ailist;aip!=NULL;aip=aip->ai_next){
		if((sockfd=connect_retry(aip->ai_family,SOCK_STREAM,0,aip->ai_addr,aip->ai_addrlen))<0){
			err=errno;
		}else{
			print_uptime(sockfd);
			exit(0);
		}
	}
	fprintf(stderr,"can't connect to %s\n",argv[1]);
	exit(1);
}
