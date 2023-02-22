#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main(int argc, char **argv)
{
    int x, *p;
    //int test = argc > 1 ? atoi(argv[1]) : 0;
    int test = 5;

    switch (test) {
        default:
            puts("Missing or invalid test number");
            return EXIT_FAILURE;

        case 1: //address not obtained from malloc
            free(&x);
            break;
        case 2: //address not at the start of a chunk
            p = (int *) malloc(sizeof(int) * 10);
            free(p + 1);
            break;

        case 3: //calling free a second time on the same pointer
            p = (int *) malloc(sizeof(int) * 10);
            free(p);
            free(p);
            break;
        case 4: //going over memory limit
            p = (int *) malloc(50000);
            free(p);
            break;
        case 5: //malloc of size 0
            p = (int*) malloc(0);
            free(p);
            break;
        case 6: //calling free on null
            p = NULL;
            free(p);
        case 7: //testing malloc and free
            p = (int*) malloc(sizeof(int) * 20);
            free(p);
    }

    printf("\nit works!");

    return EXIT_SUCCESS;
}
