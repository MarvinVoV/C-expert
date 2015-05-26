#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>

void dec(const unsigned long long int x){
	if(x/2>0){
		dec(x/2);
		printf("%d",x%2);
	}else{
		printf("%d",x);
	}
}
int main(void){
	int a=5;
	dec(a);
	putchar('\n');
    exit(0);
}
