#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc,char *argv[]){
	if(argc!=2){
		fprintf(stderr,"usage:<dotted-address>\n");
		exit(1);
	}

	struct in_addr addr;
	if(inet_aton(argv[1],&addr)<=0){
		perror("inet_aton invalidate");
		exit(1);
	}

	printf("%s\n",inet_ntoa(addr));
	exit(0);
}
