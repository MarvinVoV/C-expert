#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024
int main(int argc, char **argv){
    FILE *fp;
    char buf[BUFSIZE];

    fp = fopen("/etc/hosts", "r");
    while (fgets(buf, BUFSIZE, fp) != NULL){
       fputs(buf, stdout);     
    }

    fclose(fp);
    exit(0);
}
