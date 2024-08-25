#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int status;
	if(argc < 2){
		fprintf(stderr, "command-line argument required");
		exit(-1);
	}

	if((status = system(argv[1])) < 0){
		perror("system error");
		exit(-1);
	}

	return status;
}
