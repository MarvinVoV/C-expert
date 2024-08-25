/*
 * sun_io.h
 *
 *  Created on: Jul 26, 2015
 *      Author: yamorn
 */

#ifndef LIB_SUN_IO_H_
#define LIB_SUN_IO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <math.h>
#include <time.h>
#include <errno.h>


ssize_t sun_readn(int fd, void* buff, size_t nbytes);

void sun_writen(int fd, void *ptr, size_t nbytes);

/*
 * Deprecated
 */
ssize_t sun_readline(int fd, void *buff, size_t maxlen);

#endif /* LIB_SUN_IO_H_ */
