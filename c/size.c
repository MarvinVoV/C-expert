#include <stdio.h>
#include <stdlib.h>

int main(void){
	int *p;
	int a = 10;
	char s[] = "How big is it";
	char *t = s;
	printf("point size is %ld\n", sizeof(p));
	printf("address of a is %p\n", &a);
	printf("the address of pointer p is %p, to number %ld\n", &p, (long)p);
	printf("Storage size for short int %ld\n", sizeof(short int));
	printf("Storage size for int %ld\n", sizeof(int));
	printf("Storage size for short %ld\n", sizeof(short));
	printf("Storage size for long %ld\n", sizeof(long));
	printf("Storage size for long long %ld\n", sizeof(long long));
	printf("Storage size for array s %ld\n", sizeof(s));
	printf("Storage size for array pointer t %ld\n", sizeof(t));
	printf("%d\n", t == s);
	printf("The address of s %p\n", &s);
	printf("The address of &s %p\n", s);
	printf("The address of pointer t %p\n", &t);
	printf("Storage size for size_t %ld\n", sizeof(size_t));
    short x = 10000;
    // %hi is the proper code to format a short value
    printf("The value of x = %hi\n", x);
	return 0;
}
