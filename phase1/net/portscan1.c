#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>

int main(int argc,char *argv[]){
    if(argc!=4){
	fprintf(stderr,"usage:%s <hostname> <from> <to>\n",argv[0]);
	exit(1);
    }

    int sockfd,i;
    struct hostent *host;
    struct sockaddr_in addr;
    
    int from,to;
    from=atoi(argv[2]);
    to=atoi(argv[3]);

    if((host=gethostbyname((const char *)argv[1]))==NULL){
	perror("bad address");
	exit(1);
    }

    for(i=from;i<=to;i++){
	if((sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1){
	    perror("Can not create socket");
	    exit(1);
	}
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(i);
	if(inet_aton(argv[1],&addr.sin_addr)<=0){
	    perror("inet_aton error");
	    exit(1);
	}
	if(connect(sockfd,(struct sockaddr *)&addr,sizeof(addr))==-1){
	    close(sockfd);
	    continue;
	}
	printf("port %d open\n",i);
	close(sockfd);
    }
    exit(0);
}
