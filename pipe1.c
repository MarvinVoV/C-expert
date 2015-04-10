#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(){
	const char some_data[]="hello world.";
	int data_processed;
	int file_pipes[2];
	char buffer[BUFSIZ+1];
	
	if(pipe(file_pipes)==0){
		data_processed=write(file_pipes[1],some_data,strlen(some_data));
		printf("Wrote %d bytes\n",data_processed);
		data_processed=read(file_pipes[0],buffer,data_processed);
		printf("Read %d bytes:%s\n",data_processed,buffer);
		exit(0);
	}
	exit(1);

}
