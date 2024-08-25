#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc,char *argv[]){
	int sockfd,n;
	char recvbuff[1024];
	struct sockaddr_in serv_addr;

	if(argc!=2){
		fprintf(stderr,"%s <ip or server> \n",argv[0]);
		exit(1);
	}

	memset(recvbuff,'\0',sizeof(recvbuff));
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
		perror("Error:Could not create socket \n");
		exit(1);
	}

	memset(&serv_addr,'\0',sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(5000);  // port
	// set ip
	if(inet_aton(argv[1],&serv_addr.sin_addr)<=0){
		perror(" inet_aton error");
		exit(1);
	}
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0){
		perror("Error:Connected failed");
		exit(1);
	}
	while((n=read(sockfd,recvbuff,sizeof(recvbuff)-1))>0){
		recvbuff[n]='\0';
		if(fputs(recvbuff,stdout)==EOF){
			perror("Error:fputs error");
			exit(1);
		}
	}

	if(n<0)
		perror("Read error");

	exit(0);
}
