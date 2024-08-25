#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
    pid_t pid;

    printf("before fork.\n");

   if((pid=fork())==-1){
       perror("fork error\n");
       exit(1);
   }else if(pid==0){ 
       printf("child process running... pid=%ld\n",(long)getpid());
       sleep(5);
       printf("child process wake up. pid=%ld\n",(long)getpid());
   }else{
       printf("parent process finished.\n");
   }
    
   printf("current process pid=%ld\n",(long)getpid());
   exit(0);
   

}
