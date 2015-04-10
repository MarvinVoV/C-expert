#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(){
	char buffer[BUFSIZ+1];
	int chars_read;
	FILE *read_fp;  //read from pipe line

	read_fp=popen("ps ax","r");
	if(read_fp!=NULL){
		while((chars_read=fread(buffer,sizeof(char),BUFSIZ,read_fp))>0){
			//string end with '\0'
			buffer[chars_read-1]='\0';
			printf("Reading %d:-\n%s\n",chars_read,buffer);	
		}
		pclose(read_fp);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
