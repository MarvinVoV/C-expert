#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    struct in_addr addr;

    if(argc != 2){
        fprintf(stderr, "%s <dotted-address>\n", argv[0]);
        exit(1);
    }

    if(inet_aton(argv[1], &addr) == 0){
        fprintf(stderr, "Invalid address\n");
        exit(1);
    }
    
    printf("%s\n", inet_ntoa(addr));
    exit(0);
}
