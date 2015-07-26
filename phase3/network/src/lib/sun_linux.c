/*
 * sun_linux.c
 *
 *  Created on: Jul 26, 2015
 *      Author: yamorn
 */
#include "sun_linux.h"

void sun_close(int fd) {
	if (close(fd) == -1) {
		perror("close error");
	}
}

pid_t sun_fork(void) {
	pid_t pid;

	if ((pid = fork()) == -1) {
		perror("fork error");
		exit(1);
	}
	return (pid);
}

void *sun_malloc(size_t size) {
	void *ptr;

	if ((ptr = malloc(size)) == NULL) {
		perror("malloc error");
		exit(1);
	}
	return (ptr);
}

int sun_open(const char *pathname, int oflag, mode_t mode) {
	int fd;

	if ((fd = open(pathname, oflag, mode)) == -1) {
		fprintf(stderr, "open error for %s", pathname);
		exit(1);
	}
	return (fd);
}

ssize_t sun_read(int fd, void *ptr, size_t nbytes) {
	ssize_t n;

	if ((n = read(fd, ptr, nbytes)) == -1) {
		perror("read error");
		exit(1);
	}
	return (n);
}

void sun_write(int fd, void *ptr, size_t nbytes) {
	if (write(fd, ptr, nbytes) != nbytes){
		perror("write error");
		exit(1);
	}
}

