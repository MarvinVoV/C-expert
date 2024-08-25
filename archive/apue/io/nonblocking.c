#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

char buf[50000];

void set_flag(int fd, int flags);

void clr_flag(int fd, int flags);

int main(void){

	ssize_t ntowrite, nwrite;
	char *ptr;

	ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
	fprintf(stderr, "read %ld bytes\n", ntowrite);

	set_flag(STDOUT_FILENO, O_NONBLOCK); /* set stdout as nonblocking */

	ptr = buf;

	while(ntowrite > 0){
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, ntowrite);
		fprintf(stderr, "nwrite = %ld, errno = %d\n", nwrite, errno);

		if(nwrite > 0){
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}

	clr_flag(STDOUT_FILENO, O_NONBLOCK); /* clear nonblocking */

	exit(0);
}

void set_flag(int fd, int flags){
	int val;
	
	if((val = fcntl(fd, F_GETFL, 0) < 0) < 0){
		perror("fcntl F_GETFL error");
		exit(-1);
	}

	val |= flags;

	if(fcntl(fd, F_SETFL, val) < 0){
		perror("fcntl F_SETFL error");
		exit(-1);
	}
}

void clr_flag(int fd, int flags){
	int val;

	if((val = fcntl(fd, F_GETFL, 0)) < 0){
		perror("fcntl F_GETFL error");
		exit(-1);
	}

	val &= ~flags;

	if(fcntl(fd, F_SETFL, val) < 0){
		perror("fcntl F_SETFL error");
		exit(-1);
	}
}
