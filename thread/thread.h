#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define handle_error_en(en,msg) \
    do{ errno=en; perror(msg); exit(EXIT_FAILURE);} while(0)
