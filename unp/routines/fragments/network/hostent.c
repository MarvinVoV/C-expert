#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    char    *ptr, **pptr;
    char    str[INET_ADDRSTRLEN];
    struct hostent *hptr;

    while (--argc > 0) {
        ptr = *++argv;
        if ((hptr = gethostbyname(ptr)) == NULL) {
            fprintf(stdout,"gethostbyname error for host:%s\n", ptr);
            continue;
        }
        printf("official name: %s\n", hptr->h_name);

        for (pptr = hptr->h_aliases; *pptr != NULL; pptr++) 
            printf("\taliases: %s\n", *pptr);

        switch (hptr->h_addrtype) {
            case AF_INET:
                pptr = hptr->h_addr_list;
                for (; *pptr != NULL; pptr++)
                    inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str));
                    printf("\taddress: %s\n", str); 
                break;
            default:
                perror("unkown address type");
                break;
        }
    }

    exit(0);
}
