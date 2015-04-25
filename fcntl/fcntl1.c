#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int fd=fcntl(STDOUT_FILENO,F_DUPFD,0);
    if(fd<0){
	fprintf(stderr,"fcntl dupfd error %d\n",fd);
	exit(1);
    }
    printf("duplicate fd %d\n",fd);

    exit(0);
}
