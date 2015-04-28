#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>

#define error_handle(en,msg) \
	do{errno=en;perror(msg);exit(EXIT_FAILURE);}while(0)

#define MAXSLEEP 128

int connect_retry(int domain,int type,int protocol,const struct sockaddr *addr,socklen_t alen){
    int numsec,fd;
    /* Try to connect with exponential backoff */
    for(numsec=1; numsec <= MAXSLEEP; numsec <<= 1){
	if((fd = socket(domain, type, protocol)) < 0 )
	    return(-1);
	if(connect(fd, addr, alen) == 0){
	    /* Connection accepted. */
	    return(fd);
	}
	close(fd);
	/* Delay before trying again */
	if(numsec <= MAXSLEEP/2)
	    sleep(numsec);
    }
    return(-1);
}


int initserver(int type,const struct sockaddr *addr,socklen_t alen,int qlen){
    int fd,err;
    int reuse=1;

    if((fd=socket(addr->sa_family,type,0))<0)
	return(-1);
    if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int))<0)
	goto errout;
    if(bind(fd,addr,alen)<0)
	goto errout;
    if(type==SOCK_STREAM || type==SOCK_SEQPACKET)
	if(listen(fd,qlen)<0)
	    goto errout;
    return(fd);
    
errout:
    err=errno;
    close(fd);
    errno=err;
    return(-1);
}

int set_cloexec(int fd){
	int val;
	if((val=fcntl(fd,F_GETFD,0))<0)
		return(-1);
	val |= FD_CLOEXEC; 
	return(fcntl(fd,F_SETFD,val));
}
