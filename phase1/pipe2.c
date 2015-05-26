#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(){
	const char some_data[]="hello world.";
	int data_processed;
	int file_pipes[2];
	char buffer[BUFSIZ+1];

	pid_t fork_result;
	
	if(pipe(file_pipes)==0){
		fork_result=fork();
		if(fork_result==-1){
			fprintf(stderr,"Fork failure.");
			exit(EXIT_FAILURE);
		}
		if(fork_result==0){ // child process
			data_processed=read(file_pipes[0],buffer,BUFSIZ);
			printf("Read %d bytes:%s\n",data_processed,buffer);
			exit(EXIT_SUCCESS);	
		}else{  // parent process
			//sleep(3);
			data_processed=write(file_pipes[1],some_data,strlen(some_data));
			printf("Wrote %d bytes\n",data_processed);
		}
	}
	exit(EXIT_SUCCESS);
}
