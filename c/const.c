#include <stdio.h>

void test(const char *s){
    printf("%s\n", s);
}

int main(void){
    char *s = "hello world";
    test(s);
    char a[] = "welcome";
    test(a);

    const char *z;
    z = a;
    z = "zzz";
    printf("%s\n", z);
    // illegal. the content is read only
//    &z='c';
    return 0;
}
