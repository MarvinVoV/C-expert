#include <stdio.h>
#include <stdlib.h>

int main(void){
	// string literals can never be updated
	char *s = "hello world";
	for(char c = *s; *s!=0; s++)
		printf("%c ", *s);
	puts("\n");

	
	char *arrayp[] = {"hello", "world", "welcome", "backbone"};
	puts(arrayp[1]);	

	size_t len = sizeof(arrayp)/sizeof(arrayp[0]);
	printf("pointer array length %ld\n", len);

	for(int i = 0; i < len; i++)
		printf("%s\n", arrayp[i]);

	return 0;
}
