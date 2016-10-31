#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){
    char str[] = "2 3 hello";
    int a, b, res;
    res = sscanf(str, "%d %d", &a, &b);
    printf("res = %d, a = %d, b = %d\n", res, a, b);
    exit(0);
}
