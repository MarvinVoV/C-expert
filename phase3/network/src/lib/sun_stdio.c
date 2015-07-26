/*
 * sun_stdio.c
 *
 *  Created on: Jul 27, 2015
 *      Author: yamorn
 */

#include "sun_stdio.h"

void sun_fclose(FILE *fp) {
	if (fclose(fp) != 0)
		perror("fclose error");
}

FILE * sun_fdopen(int fd, const char *type) {
	FILE *fp;

	if ((fp = fdopen(fd, type)) == NULL)
		perror("fdopen error");

	return (fp);
}

char * sun_fgets(char *ptr, int n, FILE *stream) {
	char *rptr;

	if ((rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
		perror("fgets error");

	return (rptr);
}

FILE * sun_fopen(const char *filename, const char *mode) {
	FILE *fp;

	if ((fp = fopen(filename, mode)) == NULL)
		perror("fopen error");

	return (fp);
}

void sun_fputs(const char *ptr, FILE *stream) {
	if (fputs(ptr, stream) == EOF)
		perror("fputs error");
}
