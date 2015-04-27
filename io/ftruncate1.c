#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(void){
	int fd;
	struct stat statbuf; 
	if((fd=open("foo",O_RDWR))<0){
		perror("open error");
		exit(1);
	}
	if(fstat(fd,&statbuf)<0){
		perror("fstat error");
		exit(1);
	}
	printf("before truncate,file size is %ld\n",statbuf.st_size);

	if(ftruncate(fd,2048)<0){
		perror("ftruncate error");
		exit(1);
	}

	if(fstat(fd,&statbuf)<0){
		perror("fstat error");
		exit(1);
	}
	printf("after truncate,file size is %ld\n",statbuf.st_size);

	close(fd);

	exit(0);

}
