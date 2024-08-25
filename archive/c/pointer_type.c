#include <stdlib.h>
#include <stdio.h>

int main(void){
	char *s = "hello world";
	printf("char is at %p\n", s);
	printf("char + 1 is at %p\n", ++s);	
	printf("here s is at %c\n", *s);
	--s;
	printf("here s is at %c\n", *s);

	return 0;
}
