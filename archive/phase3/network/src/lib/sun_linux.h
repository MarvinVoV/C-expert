/*
 * sun_linux.h
 *
 *  Created on: Jul 26, 2015
 *      Author: yamorn
 */

#ifndef LIB_SUN_LINUX_H_
#define LIB_SUN_LINUX_H_

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


void sun_close(int fd);

pid_t sun_fork(void);

void *sun_malloc(size_t size);

int sun_open(const char *pathname, int oflag, mode_t mode);

ssize_t sun_read(int fd, void *ptr, size_t nbytes);

void sun_write(int fd, void *ptr, size_t nbytes);

#endif /* LIB_SUN_LINUX_H_ */
