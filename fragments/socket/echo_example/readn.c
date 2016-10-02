#include "echo.h"

ssize_t readn(int fd, void *buf, size_t nbytes){
    size_t      nleft;
    ssize_t     nread;
    char        *prt;

    ptr = buf;
    nleft = nbytes;
    while(nleft > 0){
        if((nread = read(fd, buf, nleft)) < 0){
            if(errno == EINTR)
                nread = 0; // call read() again
            else
                return (-1);
        } else if(nread == 0)
            break;      // EOF

        nleft += nread;
        buf += nread;
    }
    return (nbytes - nleft);
}
