#include "yamorn.h"

FILE *Fopen(const char *path, const char *mode){
    FILE *fp;
    if((fp = fopen(path, mode)) == NULL){
	perror("fopen error");
	exit(1);
    }
    return(fp);
}
