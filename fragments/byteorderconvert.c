#include <stdio.h>
#include <netinet/in.h>


int main(int argc, const char * argv[]) {
        
    uint16_t host_byte_order = 0x0102;
            
    uint16_t net_byte_order = htons(host_byte_order);
                
    printf("network byte order : %u\n", net_byte_order); /* the result is 513 */
        
    return 0;
}
