#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	
	mode_t mode=0066;
	umask(mode);

	if(creat("foo",0644)<0)
		perror("create file error");



	exit(0);
}
