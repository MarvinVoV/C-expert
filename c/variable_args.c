#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void print_args(int argc, ...) {
    va_list ap;
    va_start(ap, argc);
    for (int i = 0; i < argc; i++) {
        printf("%d\n", va_arg(ap, int));
    }
    va_end(ap);
}

int main(void) {
    print_args(3, 1, 20, 32); 
    return 0;
}