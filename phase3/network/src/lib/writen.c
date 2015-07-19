/*
 * writen.c
 *
 *  Created on: Jul 19, 2015
 *      Author: yamorn
 */

#include "common.h"

/* Write "n" bytes to a descriptor */
ssize_t writen(int fd, const void *buff, size_t nbytes) {
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;

	ptr = buff;
	nleft = nbytes;
	while (nleft > 0) {
		if ((nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0; /* and call write() again */
			else
				return (-1); /* error */
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return (nbytes);
}

void Writen(int fd, void *buff, size_t nbytes) {
	if (writen(fd, buff, nbytes) != nbytes){
		perror("writen");
	}
}
