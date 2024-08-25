#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define DEF_PAGER "/bin/more" /* default paper program */
#define BUF_SIZE 500

int main(int argc, char *argv[]){
	char line[BUF_SIZE];
	FILE *fpin, *fpout;

	if(argc != 2){
		fprintf(stderr, "usage: a.out <pathname>\n");
		exit(0);
	}

	if((fpin = fopen(argv[1], "r")) == NULL){
		perror("fopen error");
		exit(-1);
	}

	if((fpout = popen(DEF_PAGER, "w")) == NULL){
		perror("popen error");
		exit(-1);
	}

	/* copy argv[1] to pager */
	while(fgets(line, BUF_SIZE, fpin) != NULL){
		if(fputs(line, fpout) == EOF){
			perror("fputs error");
			break;
		}
	}

	if(ferror(fpin)){
		perror("fgets error");
		exit(-1);
	}
	
	if(pclose(fpout) == -1){
		perror("pclose error");
		exit(-1);
	}
	exit(0);
}
