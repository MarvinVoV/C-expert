#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){

    char str[6];
    snprintf(str, sizeof(str), "%s", "hello");
    
    int n = strlen(str);
    printf("len = %d, content = %s\n", n, str);
    
    exit(0);
}
