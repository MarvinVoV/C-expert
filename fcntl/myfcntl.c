#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

#define error_handle(en,msg) \
    do{errno=en;perror(msg);exit(EXIT_FAILURE);}while(0)

int lockfile(int fd){
    struct flock fl;

    fl.l_type=F_WRLCK;
    fl.l_start=0;
    fl.l_whence=SEEK_SET;
    fl.l_len=0;
    return(fcntl(fd,F_SETLK,&fl));
}




