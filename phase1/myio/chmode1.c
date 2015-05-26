#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void){
	struct stat statbuf;
	if(stat("foo",&statbuf)<0){
		perror("stat foo error \n");
		exit(1);
	}
	/* turn on set-group-ID and turn off group-execute */
	if(chmod("foo",(statbuf.st_mode & ~S_IXGRP) | S_ISGID)<0){
		perror("chmod foo error \n");
		exit(1);
	}

	/* set absolute mode to rw-r--r-- */
	if(chmod("bar",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)<0){
		perror("chmod error for bar\n");
		exit(1);
	}

	exit(0);
}
