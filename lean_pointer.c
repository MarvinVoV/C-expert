#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union u_tag {
    int *int_ptr;
    char *char_ptr;
};

int main(int argc, char *argv[])
{
    int a = 10;
    char b[] = "hello";

    union u_tag u;
    u.int_ptr = &a;
    u.char_ptr = b;

    printf("%d\n", *u.int_ptr);
    printf("%s\n", u.char_ptr);
    


    return EXIT_SUCCESS;
}

