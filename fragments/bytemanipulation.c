
#include <stdio.h>
#include <strings.h>
#include <string.h>

#include <inttypes.h>
int main(int argc, const char * argv[]) {
    
    /*
     *  BSD
     */
    
    uint16_t data = 0x0102;
    bzero(&data, 1);
    printf("%u\n", data); /* Because little-endian byte order, the result is 256 */
    
    char str1[] = "hello";
    char str2[] = "world";
    bcopy(str1, str2, 2);
    printf("str2 = %s\n", str2); /* result is 'herld' */
    
    int is_same = bcmp(&str1, &str2, 2);
    printf("is_same = %s\n", is_same == 0 ? "true" : "false");
    
    
    /*
     *  ANSI C
     */
    data = 0x0102;
    memset(&data, 0, 1);
    printf("%u\n", data);   /* result is 256 */
    
    return 0;
}
