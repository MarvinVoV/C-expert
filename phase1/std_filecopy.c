#include<stdlib.h>
#include<stdio.h>

/** Use standard library to copy file **/
int main(int argc,char *argv[]){
    if(argc!=3){
	printf("Usage: <source> <target>\n");
	exit(EXIT_FAILURE);
    }
    int c;
    FILE *in,*out;
    in=fopen(argv[1],"r");
    out=fopen(argv[2],"w+");
    
    while((c=fgetc(in))!=EOF)
	fputc(c,out);

    exit(0);
    
}
