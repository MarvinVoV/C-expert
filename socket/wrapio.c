#include "netcomplex.h"

/* Read "n" bytes from a descriptor */
static ssize_t readn(int fd, void *buff, size_t nbytes){ 
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
static ssize_t writen(int fd, const void *buff, size_t nbytes){ 
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

/* Painfully slow version --example only */
static ssize_t readline(int fd, void *buff, size_t maxlen){
   ssize_t n, rc;
   char c, *ptr;
   
   ptr=buff;
   for(n=1; n < maxlen; n++){
	again:
       if((rc = read(fd, &c, 1)) == 1){
	   *ptr++ = c;
	   if(c == '\n')
	       break; /* newline is stored, like fgets() */
	}else if(rc == 0){
	    *ptr = 0;
	    return (n-1);
	}else{
	    if(errno == EINTR) 
		goto again;
	    return (-1); /* error, errno set by read() */
	}
   }
   *ptr = 0; /* null terminate like fgets(); */
   return (n);
}

void Writen(int fd, void *buff, size_t nbytes){
    if(writen(fd, buff, nbytes) != nbytes)
	err_sys("writen error");
}

ssize_t Readn(int fd, void *buff, size_t nbytes){
    ssize_t n;
    if((n = readn(fd, buff, nbytes)) < 0)
	err_sys("readn error");
    return (n);
}

ssize_t Readline(int fd, void *buff, size_t maxlen){
    ssize_t n;
    if((n = readline(fd, buff, maxlen)) < 0)
	err_sys("readline error");
    return (n);
}
