#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>


int main(void){
	struct sockaddr addr;
	printf("%ld\n",sizeof(addr));
	printf("%ld\n",sizeof(short));
    exit(0);
}
