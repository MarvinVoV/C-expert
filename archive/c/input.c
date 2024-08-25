#include <stdlib.h>
#include <stdio.h>

int main(void){
	char name[10];
	printf("Enter a name:\n");
	// set the max length of input 
	fgets(name, sizeof(name), stdin);
	printf("name is %s\n", name);
	return 0;
}
