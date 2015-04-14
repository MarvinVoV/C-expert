#include <stdio.h>
#include <stdlib.h>

union tag{
	int age;
	float num;
};

int main(){
	union tag t;
	t.age=10;
	t.num=100.0;
	printf("%ld\n",sizeof(t));
	return 0;
}
