#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(void){
	if(unlink("lfoo")<0){
		perror("unlink lfoo error\n");
		exit(1);
	}
	exit(0);
}
