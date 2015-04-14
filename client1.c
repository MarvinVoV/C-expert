#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc,char *argv[]){
	int sockfd=0,n=0;
	char recvBuff[1024];
	struct sockaddr_in serv_addr;
	if(argc!=2){
		printf("\nUsage: %s <ip of server> \n",argv[0]);
		return 1;
	}
	memset(recvBuff,'0',sizeof(recvBuff));
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
		printf("\nError:Could not create socket\n");
		return 1;
	}

	memset(&serv_addr,'0',sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(5000);
	if(inet_pton(AF_INET,argv[1],&serv_addr.sin_addr)<=0){
		printf("\n Error:Connect Failed\n");
		return 1;
	}

	while((n=read(sockfd,recvBuff,sizeof(recvBuff)-1))>0){
		recvBuff[n]=0;
		if(fputs(recvBuff,stdout)==EOF){
			printf("\n Error:Fputs error\n");
		}
	}
	if(n<0){
		printf("\n Read error\n");
	}
	return 0;
}
