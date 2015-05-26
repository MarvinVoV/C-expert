#include <stdio.h>
#include <stdlib.h>

int main(void){
	int a=3;
	void *v=&a;
	printf("%d\n",*((int *)v));
	exit(0);
}
