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
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int,const struct sockaddr *,socklen_t,int);
extern int set_cloexec(int);

void serve(int sockfd){
	int clfd;
	FILE *fp;
	char buf[BUFLEN];

	for(;;){
		if((clfd=accept(sockfd,NULL,NULL))<0){
			fprintf(stderr,"ruptime:accept error: %s",strerror(errno));
			exit(1);
		}
		set_cloexec(clfd);
		if((fp=popen("/usr/bin/uptime","r"))==NULL){
			fprintf(stderr,"error:%s\n",strerror(errno));
			send(clfd,buf,strlen(buf),0);
		}else{
			while(fgets(buf,BUFLEN,fp)!=NULL)
				send(clfd,buf,strlen(buf),0);
			pclose(fp);
		}
	}
}

int main(int argc,char *argv[]){
	struct addrinfo *ailist,*aip;
	struct addrinfo hint;
	int sockfd,err,n;
	char *host;

	if(argc!=1){
		fprintf(stderr,"usage:%s",argv[0]);
		exit(1);
	}
	if((n=sysconf(_SC_HOST_NAME_MAX))<0){
		n=HOST_NAME_MAX; /* best guess */
	}
	if((host=malloc(n))==NULL)
		error_handle(1,"malloc error");
	if(gethostname(host,n)<0)
		error_handle(1,"gethostname error");

	memset(&hint,0,sizeof(hint));
	hint.ai_flags=AI_CANONNAME;
	hint.ai_socktype=SOCK_STREAM;
	hint.ai_canonname=NULL;
	hint.ai_addr=NULL;
	hint.ai_next=NULL;
	if((err=getaddrinfo(host,"ruptime",&hint,&ailist))!=0){
		fprintf(stderr,"getaddrinfo error");
		exit(1);
	}
	for(aip=ailist;aip!=NULL;aip=aip->ai_next){
		if((sockfd=initserver(SOCK_STREAM,aip->ai_addr,aip->ai_addrlen,QLEN))>=0){
			serve(sockfd);
			exit(0);
		}
	}
	exit(1);
}
