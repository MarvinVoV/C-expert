#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	printf("arguments number is %d\n", argc);
	printf("program name is %s\n", argv[0]);

	printf("print all the arguments\n");
	for(int i = 0; i < argc; i++)
		printf("arg[%d] %s\n", i, argv[i]);	

	return 0;
}
