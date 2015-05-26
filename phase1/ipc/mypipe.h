#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define error_handle(en,msg) \
	do{errno=en;perror(msg);exit(EXIT_FAILURE);}while(0)
