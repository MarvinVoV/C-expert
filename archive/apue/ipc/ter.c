#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void){
	int c;
	while((c = getchar()) != EOF){
		if(isupper(c))
			c = tolower(c);
		if(putchar(c) == EOF){
			perror("putchar error");
			exit(-1);
		}
		if(c == '\n')
			fflush(stdout);
	}
	exit(0);
}
