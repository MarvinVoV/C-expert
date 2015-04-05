#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
    //char *const ps_argv[]={"ps","ax",0};
    //char *const ps_envp[]={"PATH=/bin:/usr/bin","TERM=console",0};
    printf("Running ps with execlp\n");
    execlp("ps","ps","ax",0);//  assumes /bin is in PATH
    //execl("/bin/ps","ps","ax",0);  // assumes ps is in /bin 
    //execle("/bin/ps","ps","ax",0,ps_envp); // passes own environment

    //execv("/bin/ps",ps_argv);
    //execvp("ps",ps_argv);
    //execve("/bin/ps",ps_argv,ps_envp);
    printf("Done.\n");
    exit(0);
}
