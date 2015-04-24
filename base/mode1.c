#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	mode_t mode;
	printf("mode_t size=%ld\n",(long)sizeof(mode_t));

	mode=0066;
    mode=umask(mode);
	printf("mode=%o,%d\n",mode,mode);

	printf("%o,%d\n",S_IRUSR,S_IRUSR);

	exit(0);
}
