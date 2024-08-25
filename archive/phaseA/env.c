#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
    char *p;
    p = getenv("HOME");
    printf("HOME=%s\n", p);
    return 0;
}
