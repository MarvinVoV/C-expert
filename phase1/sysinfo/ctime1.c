#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	time_t t;
	time(&t);
	printf("ctime=%s\n",ctime(&t));	

	struct tm *tmp;
	tmp=localtime(&t);
	char buf[64];
	if(strftime(buf,64,"time and date:%r,%a %b %d,%Y",tmp)==0){
		printf("buf length 64 is too small\n");
	}else{
		printf("%s\n",buf);
	}


	exit(0);

}
