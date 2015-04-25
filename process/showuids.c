#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    printf("real uid=%d, effective uid=%d, real groupid=%d, effective groupid=%d\n",\
	    getuid(),geteuid(),getgid(),getegid());
    exit(0);

}
