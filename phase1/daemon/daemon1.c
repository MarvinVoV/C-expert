#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

#define error_handle(en,msg) \
    do{errno=en;perror(msg);exit(EXIT_FAILURE);}while(0)

void daemonize(const char *cmd){
    int i,fd0,fd1,fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    /* Clear file creation mask */
    umask(0);

    /* Get maximum number of file descriptors */
    if(getrlimit(RLIMIT_NOFILE,&rl)<0)
	error_handle(1,"getrlimit error");

    /* Become a session leader to lose controlling TTY. */
    if((pid=fork())<0)
	error_handle(1,"fork error");
    else if(pid!=0) /* parent */
	exit(0);
    setsid();

    /* Ensure future opens won't allocate controlling TTYs. */
    sa.sa_handler=SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=0;
    // SIGHUP is a signal sent to a process when its controlling terminal is closed
    if(sigaction(SIGHUP,&sa,NULL)<0)
	error_handle(1,"SIGHUP error");
    if((pid=fork())<0)
	error_handle(1,"fork error");
    else if(pid!=0) /* parent */
	exit(0);

    /* Change the current working directory to the root so 
       we won't prevent file system from being unmounted. */
    if(chdir("/")<0)
	error_handle(1,"chdir root error");

    /* Close all open file descriptors */
    if(rl.rlim_max==RLIM_INFINITY)
	rl.rlim_max=1024;
    for(i=0;i<rl.rlim_max;i++)
	close(i);

    /* Attach file descriptos 0,1,2 to /dev/null */
    fd0=open("/dev/null",O_RDWR);
    fd1=dup(0);
    fd2=dup(0);
    
    /* Initialize the log file */
    openlog(cmd,LOG_CONS|LOG_PID,LOG_DAEMON|LOG_USER);
    if(fd0!=0||fd1!=1||fd2!=2){
	syslog(LOG_ERR,"unexpected file descriptors %d %d %d\n",fd0,fd1,fd2);
	exit(EXIT_FAILURE);
    }

    time_t cur_t;

    while(1){
	time(&cur_t);
	syslog(LOG_INFO,"current time is %s\n",ctime(&cur_t));
	sleep(3);	
    }

    exit(EXIT_SUCCESS);
}

int main(void){
    daemonize("mydeamon"); 
    exit(0);    
}
