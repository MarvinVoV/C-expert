#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char *argv[]){
    int val;
    if(argc!=2){
	fprintf(stderr,"usage: a.out <descriptor>\n");
	exit(1);
    }

    if((val=fcntl(atoi(argv[1]),F_GETFL,0))<0){
	perror("fcntl failed\n");
	exit(1);
    }

    switch(val & O_ACCMODE){
	case O_RDONLY:
	    printf("read only");
	    break;
	case O_WRONLY:
	    printf("write only");
	    break;
	case O_RDWR:
	    printf("read write");
	    break;
	default:
	    perror("unkown access mode\n");
	    exit(1);
    }
    if(val & O_APPEND)
	printf(",append");
    if(val & O_NONBLOCK)
	printf(",nonblock");
    if(val & O_SYNC)
	printf(",synchronous write");

    putchar('\n');
    exit(0);
}
