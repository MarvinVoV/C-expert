#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#define A_MEGABYTE (1024*1024)
int main(){
    char *some_memory;
    int exit_code=EXIT_FAILURE;
    
   some_memory=(char *)malloc(A_MEGABYTE);
  if(some_memory!=NULL){
    sprintf(some_memory,"Hello world\n");
    printf("%s",some_memory);
    free(some_memory);
    exit_code=EXIT_SUCCESS;

  } 
  exit(exit_code);
}
