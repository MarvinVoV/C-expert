#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(){
	char *buf;
	int len=64;
	buf=(char *)malloc(sizeof(char)*len);
	if(gethostname(buf,len)!=0){
		perror("gethostname error\n");
		exit(1);
	}

	printf("hostname is %s\n",buf);
	free(buf);
	exit(0);
}
