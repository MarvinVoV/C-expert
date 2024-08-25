#include <stdio.h>
#include <stdlib.h>

int main(){
	char *name = "TestName";
	char *value = "TestValue";
	int rewrite = 1;
	int r;
	
	r = setenv(name, value, rewrite);
	if(r == -1){
		fprintf(stderr, "cannot set environment\n");
		exit(-1);
	}
	printf("%s=%s\n", name, getenv(name));
	exit(0);
}
	
