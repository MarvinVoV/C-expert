#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
int main(void){
    struct sockaddr_in serv;
    printf("%ld\n", (long)sizeof(serv));
	printf("%ld\n",(long)sizeof(unsigned short));
    printf("int=%ld\n", (long)sizeof(int));
    printf("unsigned int=%ld\n", (long)sizeof(unsigned int));

	exit(0);
}
