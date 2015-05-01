#include "netcomplex.h"

/* Read "n" bytes from a descriptor */
ssize_t readn(int fd, void *buff, size_t nbytes){ 
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = buff;
    nleft = nbytes;
    while(nleft > 0){
	if((nread = read(fd, ptr, nbytes)) < 0){
	    if(errno == EINTR )
		nread = 0; /* and call read() again */
	    else
		return(-1);
	}else if(nread == 0){
	    break; /* EOF */
	}
	nleft -= nread;
	ptr += nread;
    }
    return (nbytes - nleft);
}


/* Write "n" bytes to a descriptor */
ssize_t writen(int fd, const void *buff, size_t nbytes){ 
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = buff;
    nleft = nbytes;
    while(nleft > 0){
	if((nwritten = write(fd, ptr, nleft)) <= 0){
	    if(nwritten <0 && errno == EINTR)
		nwritten = 0; /* and call write() again */
	    else
		return(-1); /* error */
	}
	nleft -= nwritten;
	ptr += nwritten;
    }
    return (nbytes);
}
