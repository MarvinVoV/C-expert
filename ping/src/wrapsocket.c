/*
 * wrapsocket.c
 *
 *  Created on: May 6, 2015
 *      Author: louis
 */

#include "yamorn.h"

void Sendto(int fd, const void *ptr, size_t nbytes, int flags,
		const struct sockaddr *sa, socklen_t salen) {
	if (sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t) nbytes){
		perror("Sendto");
		exit(1);
	}
}

