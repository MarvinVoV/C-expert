#include <stdio.h>
#include <stdlib.h>

int main(void){
    char buf[50];
    char *p = buf;
    unsigned char mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    int i;
    for(i = 0;i<5;i++,p+=3){
        sprintf(p,"%02x:",mac[i]);
    }
    sprintf(p,"%02x",mac[i]);
    printf("%s\n", buf);
}
