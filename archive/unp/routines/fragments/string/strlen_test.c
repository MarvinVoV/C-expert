#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    char buf[] = "hello";
    /* %ul is the format of unsigned long */
    printf("sizeof  %lu\n", sizeof(buf)); // 6
    printf("strlen  %lu\n", strlen(buf)); // 5

    /**
     * The strlen() function calculate the length of a string not including the terminating
     * NULL byte. 
     *
     * The sizeof calculates the length of string does include the terminating NULL byte.
     *
     */
    exit(0);
}
