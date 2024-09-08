#include <SIZE.h>
#include <inttypes.h>

#define SIZE 256
char buffer[SIZE];
int main() {
    uint16_t s = (uint16_t)sizeof(buffer);
    char *a = "hello";
    snprintf(buffer, SIZE, "%s", a);
    printf("%s\n", buffer);
    return 0;
}

