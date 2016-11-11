#include "unp.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

void daemonize(const char *pname) {
    int                 i, fd0, fd1, fd2;
    pid_t               pid;
    struct rlimit       rl;
    struct sigaction    sa;

    /*
     * Clear file creation mask
     */
    umask(0);

    /*
     * Get maximum number of file descriptors.
     */
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        perror("can't get file limit");
        exit(-1);
    }

    /*
     * Become a session leader to lose controlling TTY
     */
    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(-1);
    } else if (pid != 0) /* parent */
        exit(0);
    setsid();

    /*
     * Ensure future opens won't allocate controlling TTYs.
     */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        perror("can't ignore SIGHUP");
        exit(-1);
    } 
    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(-1);
    } else if (pid != 0) /* parent */
        exit(0);

    

    
}
