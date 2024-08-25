#include<stdio.h>

int main() {

    // Using a character array
    char a[6] = {'H','e','l','l','o','\0'};
    printf("%s\n",a);

    // Using a string literal
    char b[] = "hello";
    printf("%s\n",b);

    // Using pointer
    char *str = "Hello, World!";
    printf("%s\n",str);


    // 先取str的值，然后递增指针
    char f = *str++;
    printf("%c,%s\n",f, str);


    char r = *--str;
    printf("%c,%s\n",r, str);
    return 0;
}