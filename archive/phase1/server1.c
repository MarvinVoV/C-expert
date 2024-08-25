#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main(int argc,char *argv[]){
	int listenfd,connfd;
	struct sockaddr_in serv_addr;
	
	char sendbuf[1025];
	time_t ticks;

	listenfd=socket(AF_INET,SOCK_STREAM,0);
	memset(&serv_addr,'0',sizeof(serv_addr));
	memset(sendbuf,'0',sizeof(sendbuf));

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(5000);

	bind(listenfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

	listen(listenfd,10);

	while(1){
		connfd=accept(listenfd,(struct sockaddr *)NULL,NULL);
		ticks=time(NULL);
		snprintf(sendbuf,sizeof(sendbuf),"%.24s\r\n",ctime(&ticks));
		write(connfd,sendbuf,strlen(sendbuf));
		close(connfd);
		sleep(1);
	}
}
