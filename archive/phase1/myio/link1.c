#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
	if(link("foo","lfoo")<0){
		perror("link foo file failed\n");
		exit(1);
	}
	exit(0);
}
