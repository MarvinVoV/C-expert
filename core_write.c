#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
/** Write a string to the standard output **/
int main(){
    char str[]="Here is some data\n";
    char msg[]="A write error has ocurred on file descriptor 1\n"; 
    int len=strlen(str); 

    int n=write(1,str,len);
    if(n!=len)
	write(2,msg,strlen(msg));
    exit(0);
}
