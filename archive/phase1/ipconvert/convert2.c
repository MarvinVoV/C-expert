#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    struct in_addr addr;
    if(argc != 2){
        fprintf(stderr, "%s <dotted-address>\n", argv[0]);
        exit(1);
    }
    
    addr.s_addr = inet_addr(argv[1]);

    if( addr.s_addr == -1){
        fprintf(stderr, "invalid input\n");
        exit(1);
    }

    printf("%s\n", inet_ntoa(addr));
    
    exit(0);
}
