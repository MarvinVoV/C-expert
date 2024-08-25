/*
 * sun_stdio.h
 *
 *  Created on: Jul 27, 2015
 *      Author: yamorn
 */

#ifndef LIB_SUN_STDIO_H_
#define LIB_SUN_STDIO_H_

#include <stdio.h>
#include <stdlib.h>



void sun_fclose(FILE *fp);

FILE * sun_fdopen(int fd, const char *type);

char * sun_fgets(char *ptr, int n, FILE *stream);

FILE * sun_fopen(const char *filename, const char *mode);

void sun_fputs(const char *ptr, FILE *stream);


#endif /* LIB_SUN_STDIO_H_ */
