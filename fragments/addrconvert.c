
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, const char * argv[]) { 
    char addr_str[] = "192.168.218.2";
    struct in_addr inet_addr;
    char *addr_convert_str;
    
    // convert string present address to network address
    int result = inet_aton(addr_str, &inet_addr);
    if(result != 1){
        perror("inet_aton");
        exit(-1);
    }
    
    // convert network address to host address
    addr_convert_str = inet_ntoa(inet_addr);
    
    printf("result is %s\n", addr_convert_str);
   
    return 0;
}