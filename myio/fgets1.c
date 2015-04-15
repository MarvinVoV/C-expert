#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int main(void){
    char buf[MAX];

    while(fgets(buf,MAX,stdin)!=NULL){
	if(fputs(buf,stdout)==EOF){
	    fprintf(stderr,"output error\n");
	    exit(1);
	}
    }
    if(ferror(stdin)){
	fprintf(stderr,"input error\n");
	exit(1);
    }
    exit(0);
}

   
