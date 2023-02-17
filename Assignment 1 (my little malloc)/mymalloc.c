#include <stdio.h>
#include "mymalloc.h"

#define MEMSIZE 4096
static char memory[MEMSIZE];

typedef struct node {
    size_t size;
    struct node *link;
} node;

void mymalloc(size_t size, char *file, int line) {
    if(size == 0){
        printf("ERROR: Insufficient memory!");
        return;
    }else if(MEMSIZE - size < 0){
        printf("ERROR: Not enough space!");
        return;
    }
}

void myfree(void *ptr, char *file, int line){
    if(ptr == NULL){
        printf("ERROR: Pointer empty!");
        return;
    }
}
