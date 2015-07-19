/*
 * readn.c
 *
 *  Created on: Jul 19, 2015
 *      Author: yamorn
 */
#include "common.h"

/* Read "n" bytes from a descriptor */
ssize_t readn(int fd, void *buff, size_t nbytes) {
	size_t nleft;
	ssize_t nread;
	char *ptr;

	ptr = buff;
	nleft = nbytes;
	while (nleft > 0) {
		if ((nread = read(fd, ptr, nbytes)) < 0) {
			if (errno == EINTR)
				nread = 0; /* and call read() again */
			else
				return (-1);
		} else if (nread == 0) {
			break; /* EOF */
		}
		nleft -= nread;
		ptr += nread;
	}
	return (nbytes - nleft);
}

ssize_t Readn(int fd, void *buff, size_t nbytes) {
	ssize_t n;
	if ((n = readn(fd, buff, nbytes)) < 0)
		perror("readn error");
	return (n);
}

