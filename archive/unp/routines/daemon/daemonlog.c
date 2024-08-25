#include "unp.h"

int main(int argc, char **argv){
    printf("change to daemon prococess\n");
    const char *pname = "yamorn-daemon";
    daemonize(pname);

    // wirte log message
    syslog(LOG_INFO, "This is a message for test.\n");
    exit(0);
}