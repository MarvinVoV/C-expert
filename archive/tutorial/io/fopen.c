#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    FILE *file;
    int  c;
    file = fopen("/etc/hosts", "r");
    if(file){
        while((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    }

    exit(0);
}
