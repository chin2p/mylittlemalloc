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
        printf("ERROR: insufficient memory at %s:%d\n", file, line);
        return NULL;
    }

    if(head == NULL) {
        head = (node *) memory;
        head->size = MEMSIZE;
        head->link = NULL;
    }

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

            // Initialize the node header for the allocated block
            node *allocated_block = current;
            allocated_block->link = NULL;

            return (void*)(allocated_block + 1);
        }
        prev = current;
        current = current->link;
    }

    printf("ERROR: Not enough memory in heap!\n");
    return NULL;
}

void myfree(void *ptr, char *file, int line) {
    if (ptr == NULL) {
        printf("ERROR: Attempt to free null pointer at %s:%d\n", file, line);
        return;
    }

    // Get a pointer to the node containing the allocated block
    node *block = (node*)((char*)ptr - sizeof(node));

    if (block < (node*)memory || block >= (node*)(memory + MEMSIZE)) {
        printf("ERROR: Attempt to free invalid memory at %s:%d\n", file, line);
        return;
    }

    if ((char*)ptr < (char*)block + sizeof(node) || (char*)ptr >= (char*)block + sizeof(node) + block->size) {
        printf("ERROR: Attempt to free not at the start %s:%d\n", file, line);
        return;
    }

    // Check if the block is in the free list
    node *current = head;
    while (current != NULL) {
        if (current == block) {
            printf("ERROR: Double free of memory at %s:%d\n", file, line);
            return;
        }
        current = current->link;
    }

    // Find the correct place to insert the freed block in the free list
    node *prev = NULL;
    current = head;
    while (current != NULL && current < block) {
        prev = current;
        current = current->link;
    }

    if (prev == NULL) {
        head = block;
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
    }
}
