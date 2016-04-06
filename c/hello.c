#include <stdio.h>
#include <stdlib.h>

int main(void){
	char name[3];
	puts("Enter a name with with two characters\n");
	scanf("%2s", name);
	printf("name is %s\n", name);

	for(int i=0; i<10; i++){
		printf("%d\n", i);
	}
	int x = 0, y = 0;
	x = y = 4;
	printf("x=%d y=%d\n", x, y);
	printf("the address of x is %p\n", &x);
	printf("'hello' length is %ld\n", sizeof("hello"));
	int arr[2] = {1,2};
	printf("arr address start at %p\n", arr);
	return 0;
}
