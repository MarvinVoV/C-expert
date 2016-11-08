#include "unp.h"

void str_cli(FILE *fp, int sockfd);

void str_cli_select01(FILE *fp, int sockfd);

void str_cli_select02(FILE *fp, int sockfd);


int main(int argc, char **argv){
    int                 sockfd;
    struct sockaddr_in  servaddr;
    int                 ret;

    if(argc != 2){
        perror("Usage: tcpcli <IPAddress>");
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    
    ret = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if(ret != 0){
        perror("connect error");
        exit(-1);
    }

    // str_cli(stdin, sockfd);
    // str_cli_select01(stdin, sockfd);
    str_cli_select02(stdin, sockfd);

    exit(0);
}

void str_cli(FILE *fp, int sockfd){
    char sendline[BUF_SIZE], recvline[BUF_SIZE];

    while(fgets(sendline, BUF_SIZE, fp) != NULL){
        writen(sockfd, sendline, strlen(sendline));

        if(readline(sockfd, recvline, BUF_SIZE) == 0){
            perror("str_cli: server terminated prematurely");
            exit(-1);
        }

        fputs(recvline, stdout);
    }
}


/**
 *  Using select function, so we are notified as soon as the server process terminates.
 */
void str_cli_select01(FILE *fp, int sockfd){
   int      maxfdp1;
   fd_set   rset;
   char     sendline[BUF_SIZE], recvline[BUF_SIZE];
   int      retval;

   FD_ZERO(&rset);
   for ( ; ; ){
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1; // max file descriptor plus 1 
        retval = select(maxfdp1, &rset, NULL, NULL, NULL);
        if (retval == -1){
            perror("select error");
            exit(-1);
        }

        if (FD_ISSET(sockfd, &rset)) { // socket is readable
            if (readline(sockfd, recvline, BUF_SIZE) == 0){
                perror("str_cli: server terminated prematurely");
                exit(-1);
            }
            fputs(recvline, stdout);
        }
        
        if (FD_ISSET(fileno(fp), &rset)){ // input is readable
            if (fgets(sendline, BUF_SIZE, fp) == NULL)
                return; // all done
            writen(sockfd, sendline, strlen(sendline));
        }
   }
}


void str_cli_select02(FILE *fp, int sockfd){
    int     maxfdp1, stdineof;
    fd_set  rset;
    char    buf[BUF_SIZE];
    int     n;
    int     retval;

    stdineof = 0;
    FD_ZERO(&rset);
    for (; ;) {
        if (stdineof == 0)
            FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        retval = select(maxfdp1, &rset, NULL, NULL, NULL);
        if (retval == -1) {
            perror("select error");
            exit(-1);
        }

        if (FD_ISSET(sockfd, &rset)) { // socket is readable
            if ((n = read(sockfd, buf, BUF_SIZE)) == 0) {
                if (stdineof == 1) {
                    return; // normal termination
                } else {
                    perror("str_cli: server terminated prematurely");
                    exit(-1);
                }
                
            }
            write(fileno(stdout), buf, n);
        }

        if (FD_ISSET(fileno(fp), &rset)) { // input is readable
            if ((n = read(fileno(fp), buf, BUF_SIZE)) == 0) {
                stdineof = 1;
                shutdown(sockfd, SHUT_WR); // send FIN
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            writen(sockfd, buf, n);
        }
    }
}

