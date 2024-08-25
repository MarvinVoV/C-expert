#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char **argv){
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
    
    if(argc != 2){
        fprintf(stderr, "%s <hostname>\n", argv[0]);
        exit(1);
    }

    if( (he = gethostbyname(argv[1])) == NULL){
        perror("gethostbyname");
        exit(1);
    }

    printf("hostname is %s\n", he->h_name);

    addr_list = (struct in_addr **) he->h_addr_list;
    while( *addr_list != NULL ){
        printf("host ip is %s\n", inet_ntoa(**addr_list));
        addr_list++;
    }
    
    //for(i = 0; addr_list[i] != NULL; i++){
     //   printf("host ip is %s\n", inet_ntoa(*addr_list[i]));
    //}
    exit(0);
    
}
