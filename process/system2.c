#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
    if(argc<2){
	fprintf(stderr,"Usage:a.out filename\n");
	exit(EXIT_FAILURE);
    }

    int status;
    if((status=system(argv[1]))<0){
	perror("system error");
	exit(EXIT_FAILURE);
    }
    printf("system exit status is %d\n",status); 
    exit(0); 
}
