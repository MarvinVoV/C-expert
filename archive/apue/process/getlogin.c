#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    char *name = getlogin();
    
    printf("login name %s\n", name);

    return 0;
}
