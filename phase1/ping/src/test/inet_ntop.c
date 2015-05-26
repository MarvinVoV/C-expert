#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>

int main(void){
	char buf[16];
	const char *ptr;
	struct sockaddr_in saddr;
	struct in_addr addr;

	bzero(&saddr, sizeof(saddr));
	addr.s_addr = 0xb0a80080;
	saddr.sin_family = AF_INET;
	saddr.sin_addr = addr;
	
	if((ptr = inet_ntop(saddr.sin_family, &saddr.sin_addr, buf, sizeof(buf))) == NULL){
		perror("inet_ntop");
		exit(1);
	}

	printf("ip=%s\n", ptr);
	exit(0);
}
