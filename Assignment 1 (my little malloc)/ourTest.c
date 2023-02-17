#include <stdio.h>
#include "mymalloc.h"

int main() {
    int size;

    printf("Please enter the amount of integers needed: ");
    scanf("%d", &size);

    int *ptr = (int *) malloc(size * sizeof(int));


    printf("Please Enter all %d integer(s)\n", size);
    for (int i = 0; i < size; i++) {
        printf("(%d) Enter each integer: ", i + 1);
        scanf("%d", ptr + i);
    }

    for (int i = 0; i < size; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");
}
