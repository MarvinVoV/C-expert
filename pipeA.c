#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/* Write to pipe line parent process pid.*/
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
			sprintf(buffer,"%d",file_pipes[0]);
			printf("length=%ld,content=%s\n",strlen(buffer),buffer);
			//replace parent process
			// (char *)0 , paramerters terminate 
			(void)execl("pipeB","pipeB",buffer,(char *)0);
			exit(EXIT_FAILURE);	
		}else{  // parent process
			//sleep(3);
			data_processed=write(file_pipes[1],some_data,strlen(some_data));
			printf("%d - Wrote %d bytes\n",getpid(),data_processed);
		}
	}
	exit(EXIT_SUCCESS);
}
