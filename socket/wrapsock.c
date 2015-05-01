#include "netcomplex.h"

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr){
	int n;
again:
	if((n = accept(fd, sa, salenptr)) < 0){
		#ifdef EPROTO
		if(errno == EPROTO || errno == ECONNABORTED)
		#else
		if(errno == ECONNABORTED)
		#endif
			goto again;
		else
			err_sys("accept error");
	}
	return(n);
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen){
	if(bind(fd, sa, salen) < 0)
		err_sys("bind error");
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen){
	if(connect(fd, sa, salen) < 0)
		err_sys("connect error");
}

void Listen(int fd, int backlog){
	char *ptr;
	if((ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);
	if(listen(fd, backlog) < 0)
		err_sys("listen error");
}

int Socket(int family, int type, int protocol){
	int n;
	if((n = socket(family, type, protocol)) < 0)
		err_sys("socket error");
	return(n);
}

ssize_t Recv(int fd, void *ptr, size_t nbytes, int flags){
	ssize_t n;
	if((n = recv(fd, ptr, nbytes, flags))<0)
		err_sys("recv error");
	return(n);
}

void Send(int fd, const void *ptr, size_t nbytes, int flags){
	if(send(fd, ptr, nbytes, flags) != (ssize_t)nbytes)
		err_sys("send error");
}


const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len){
    const char *ptr;

    if(strptr == NULL)
	err_sys("NULL arguments to inet_ntop");
    if((ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
	err_sys("inet_ntop error");
    return (ptr);
}

void Inet_pton(int family, const char *strptr, void *addrptr){
    int n;
    if((n = inet_pton(family, strptr, addrptr)) < 0)
	err_sys("inet_pton error");
    else if(n == 0)
	err_sys("inet_pton error for %s",strptr);
}
