#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    char *p;
    p=getlogin();
    printf("login name is %s\n",p);
    exit(0);
}
