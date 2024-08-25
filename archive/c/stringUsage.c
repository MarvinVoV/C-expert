#include <stdio.h>
#include <string.h>

int main(void){
	char s[] = "greatfully";
	char a[] = "full";
	char *p;
	p = strstr(s, a);
	printf("result is %s\n", p);	

	printf("The length of s is %ld\n", strlen(s));
	printf("The length of p is %ld\n", strlen(p));
	
	size_t sz = strlen("hello");
	printf("length of sz is %ld\n", sz);
	
	char cp[strlen(s)];
	strcpy(cp, s);
	printf("cp %s\n", cp);

    char *ss = "this will be copied on the heap\n";
    char *sscp = strdup(ss);
    printf("address of ss is %p\n", &ss);
    printf("address of sscp is %p\n", &sscp);
	
    free(sscp);
	return 0;
}
