#include "process.h"

int main(void){
    pid_t pid;
    pid_t pgid;
    pid_t sid;
    pid=getpid();
    pgid=getpgid(0);
    sid=getsid(0);
    printf("pid=%ld,pgid=%ld,sid=%ld\n",(long)pid,(long)pgid,(long)sid);

    exit(0);
}
