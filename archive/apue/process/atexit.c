#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void bye(void){
	printf("That was all folks\n");
}

int main(){
	int i; 
	i = atexit(bye);
	if(i){
		fprintf(stderr, "cannot exit function\n");
		exit(-1);
	}
	exit(0);
}
