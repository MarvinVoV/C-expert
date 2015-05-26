#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
	struct stat statbuf;
    if(stat("foo",&statbuf)<0){
		perror("stat foo error\n");
		exit(1);
	}
	printf("before truncate foo length is %ld\n",statbuf.st_size);

	if(truncate("foo",500)<0){
		perror("truncate foo failed \n");
		exit(1);
	}

	if(stat("foo",&statbuf)<0){
		perror("stat foo error\n");
		exit(1);
	}
	printf("after truncate foo length is %ld\n",statbuf.st_size);
	exit(0);
}
