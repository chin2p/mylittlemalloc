#include <stdio.h>
#include "mymalloc.h"

#define MEMSIZE 4096
static char memory[MEMSIZE];

typedef struct node {
    size_t size;
    struct node *link;
} node;

void* mymalloc(size_t size, char *file, int line) {

    if (size == 0) {
        printf("ERROR: Requested allocation of size 0 at %s:%d\n", file, line);
        return NULL;
    }

    // Initialize the free list if it hasn't been initialized yet
    if (*(node**)memory == NULL) {
        (*(node**)memory) = (node*)(memory + sizeof(node*));
        (*(node**)memory)->size = MEMSIZE - sizeof(node);
        (*(node**)memory)->link = NULL;
    }

    // Search the free list for a block of the requested size
    node *prev = NULL;
    node *current = (*(node**)memory);
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
                (*(node**)memory) = current->link;
            } else {
                prev->link = current->link;
            }

            // Initialize the node header for the allocated block
            node *allocated_block = current;
            allocated_block->link = NULL;


            return (void*)((char*)allocated_block + sizeof(node));
        }
        prev = current;
        current = current->link;
    }

    printf("ERROR: Insufficient memory to allocate block of size %zu at %s:%d\n", size, file, line);
    return NULL;
}



void myfree(void *ptr, char *file, int line) {
    if (ptr == NULL) {
        printf("ERROR: Trying to free null pointer at %s:%d\n", file, line);
        return;
    }

    // Get a pointer to the node containing the allocated block
    node *block = (node*)((char*)ptr - sizeof(node));

    if (block < (node*)memory || block >= (node*)(memory + MEMSIZE)) {
        printf("ERROR: Trying to free memory outside of malloc at %s:%d\n", file, line);
        return;
    }

    if ((char*)ptr < (char*)block + sizeof(node) || (char*)ptr >= (char*)block + sizeof(node) + block->size) {
        printf("ERROR: Trying to free memory not at the start of the chunk at %s:%d\n", file, line);
        return;
    }

    // Check if the block is already in the free list
    node *current = *(node**)memory;
    while (current != NULL) {
        if (current == block) {
            printf("ERROR: Calling free twice on the same pointer at %s:%d\n", file, line);
            return;
        }
        current = current->link;
    }

    // Find the correct place to insert the freed block in the free list
    node *prev = NULL;
    current = *(node**)memory;
    while (current != NULL && current < block) {
        prev = current;
        current = current->link;
    }

    if (prev == NULL) {
        *(node**)memory = block;
    } else {
        prev->link = block;
    }
    block->link = current;

    // Coalesce adjacent free blocks
    if (current != NULL && (char*)block + block->size + sizeof(node) == (char*)current) {
        block->size += current->size + sizeof(node);
        block->link = current->link;
    }
    if (prev != NULL && (char*)prev + prev->size + sizeof(node) == (char*)block) {
        prev->size += block->size + sizeof(node);
        prev->link = block->link;
        block = prev;
    }
}
