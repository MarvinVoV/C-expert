#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct user{
    char *name;
    int age;
};
int main(void){
    struct user u;
    u.name="louis";
    u.age=30;
    printf("sizeof(u)=%ld\n",(long)sizeof(u));
    printf("u.age=%d\n",u.age);
    memset(&u,0,sizeof(u));
    printf("u.age=%d\n",u.age);
    exit(0);
}
