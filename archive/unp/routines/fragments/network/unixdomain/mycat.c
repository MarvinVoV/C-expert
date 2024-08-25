#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define BUF_SIZE 1024 * 2

int my_open(const char *, int);

int main(int argc, char **argv){
    int fd, n;
    char buf[BUF_SIZE];

    if (argc != 2) {
        printf("usage: mycat <pathname>\n");
        exit(-1);
    }

    if ((fd = my_open(argv[1], O_RDONLY)) < 0) {
        printf("cann't open %s\n", argv[1]);
        exit(-1);
    }

    while ((n = read(fd, buf, BUF_SIZ)) > 0) {
        write(STDOUT_FILENO, buf, n);
    }

    exit(0);
}

int my_open(const char *pathname, int mode) {
    int     fd, sockfd[2], status;
    pid_t   childpid;
    char    c, argsockfd[10], argmode[10];

    if (socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd) != 0) {
        perror("socketpair error");
        exit(-1);
    }

    if ((childpid = fork()) == 0) { // child process
        close(sockfd[0]);
        snprintf(argsockfd, sizeof(argsockfd), "%d", sockfd[1]);
        snprintf(argmode, sizeof(argmode), "%d", mode);
        execl("./openfile", "openfile", argsockfd, pathname, argmode, (char *) NULL);
        perror("execl error");
    }

    // parent process - wait for the child to terminate
    close(sockfd[1]);
    waitpid(childpid, &status, 0);
    if (WIFEXITED(status) == 0) {
        perror("child did not terminate.");
        exit(-1);
    }
    if ((status == WEXITSTATUS(status)) == 0)
        read_fd(sockfd[0], &c, 1, &fd);
     else {
        errno = status;
        fd = -1;
    }
    close(sockfd[0]);
    return (fd);
}