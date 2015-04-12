#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
/*  Read pipe line from pipeA.c */
int main(int argc,char *argv[]){
	int data_processed;
	char buffer[BUFSIZ+1];
	int file_descriptor;

	memset(buffer,'\0',sizeof(buffer));
	printf("args[0]=%s,args[1]=%s\n",argv[0],argv[1]);
	sscanf(argv[1],"%d",&file_descriptor);
	data_processed=read(file_descriptor,buffer,BUFSIZ);

	printf("%d -read %d bytes:%s\n",getpid(),data_processed,buffer);
	exit(EXIT_SUCCESS);
}
