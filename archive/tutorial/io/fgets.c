#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    char name[10];
    printf("who are you ? \n");
    fgets(name, 10, stdin);
    printf("Glad to meet you, %s\n", name);
    exit(0);
}
