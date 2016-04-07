#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_reverse(char *s);

int main(void){
	char s[] = "hello world";
	print_reverse(s);	
	return 0;
}

void print_reverse(char *s){
	char *p = s + strlen(s);
	while(--p >= s)
	   printf("%c", *p);
	puts("");	
}
