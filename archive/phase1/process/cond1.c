#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void charatatime(char *);

int main(void){
    pid_t pid;
    if((pid=fork())<0){
	perror("fork");
	exit(1);
    }else if(pid==0){
	// wait for parent
	charatatime("output from child\n");
    }else{
	// tell child
	charatatime("output from parent\n");
    }
    exit(0);
}

static void charatatime(char *str){
    char *ptr;
    int c;
    setbuf(stdout,NULL);  /* set unbuffered */
    for(ptr=str;(c=*ptr++)!=0; )
	putc(c,stdout);
}
