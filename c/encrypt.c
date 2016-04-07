#include <stdio.h>
#include <stdlib.h>
#include "encrypt.h"

int main(void){
    char s[] = "hello world";
    encrypt(s);
    printf("encrypt message is %s\n", s);
    encrypt(s);
    printf("message is %s\n", s);
    return 0;
}


