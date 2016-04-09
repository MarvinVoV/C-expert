#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct island{
    char *name;
    int num;
    struct island *next;
} island;

island *create(const char *name){
    island *i = malloc(sizeof(island));
    i->name = strdup(name);
    i->next = NULL;
    return i;
}

void release(island *start){
    island *i = start;
    island *next = NULL;
    for(; i != NULL; i = next){
        next = i->next;
        free(i->name);
        free(i);
    }
}
void display(island *i){
    printf("name is %s\n", i->name);
}

int main(void){
    island *start = NULL;
    island *i = NULL;
    island *next = NULL;
    char name[5];
    for(; fgets(name, 5, stdin) != NULL; i = next){
        next = create(name);
        if(start == NULL)
            start = next;
        if(i != NULL)
            i->next = next;
    }
    display(start);
    release(start);    
    return 0;
}
