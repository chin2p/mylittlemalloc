#include <stdio.h>
#include "mymalloc.h"

#define MEMSIZE 4096
static char memory[MEMSIZE];

void *mymalloc(size_t size, char *file, int line){
    if(size == 0){
        printf("No memory to allocate!");
    }
}

void myfree(void *ptr, char *file, int line){

}
