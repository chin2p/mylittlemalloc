#include <stdio.h>
#include "mymalloc.h"

#define MEMSIZE 4096
static char memory[MEMSIZE];

typedef struct node {
    size_t size;
    struct node *link;
} node;

static node *head = NULL;

void* mymalloc(size_t size, char *file, int line) {


    if(size == 0){
        printf("ERROR: insufficient memory!\n");
        return NULL;
    }

    head = (node*)memory;
    head->size = MEMSIZE - sizeof(node);
    head->link = NULL;

    // Search the free list for a block of the requested size
    node *prev = NULL;
    node *current = head;
    while (current != NULL) {
        if (current->size >= size) {
            // We found a block of the requested size
            if (current->size - size >= sizeof(node)) {
                // Split the block into an allocated block and a free block
                node *new_node = (node*)((char*)current + sizeof(node) + size);
                new_node->size = current->size - size - sizeof(node);
                new_node->link = current->link;
                current->size = size;
                current->link = new_node;
            }
            if (prev == NULL) {
                head = current->link;
            } else {
                prev->link = current->link;
            }
            return (void*)(current + 1);
        }
        prev = current;
        current = current->link;
    }

    printf("ERROR: Not enough memory in heap!\n");
    return NULL;
}

void myfree(void *ptr, char *file, int line) {
    if (ptr == NULL) {
        printf("ERROR: Empty pointer!\n");
        return;
    }
    // Check if the pointer is within the range of addresses managed by mymalloc
    if (ptr < (void*)memory || ptr >= (void*)(memory + MEMSIZE)) {
        printf("ERROR: Address is not obtained from malloc!");
        return;
    }


    // Get the node that corresponds to the allocated block
    node *current = (node*)ptr - 1;


    // Add the block to the free list
    node *prev = NULL;
    node *free_node = (node*)memory;
    while (free_node != NULL && free_node < current) {
        prev = free_node;
        free_node = free_node->link;
    }
    if (prev == NULL) {
        head = current;
    } else {
        prev->link = current;
    }
    current->link = free_node;


    // Coalesce adjacent free blocks
    if (current->link != NULL && (char*)current + current->size + sizeof(node) == (char*)current->link) {
        current->size += current->link->size + sizeof(node);
        current->link = current->link->link;
    }
    if (prev != NULL && (char*)prev + prev->size + sizeof(node) == (char*)current) {
        prev->size += current->size + sizeof(node);
        prev->link = current->link;
        current = prev;
    }
}
