#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

int main(void){
	char *host="127.0.0.1";
	char str[INET_ADDRSTRLEN];
	struct sockaddr_in addr;
	bzero(addr,sizeof(addr));

	inet_pton(AF_INET,host,&addr.sin_addr);

	if(inet_ntop(AF_INET,(void *)&addr.sin_addr,str,sizeof(addr.sin_addr))==NULL){
		perror("inet_ntop");
	}
	
	printf("addr=%s\n",str);
	return(0);

}
