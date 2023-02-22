#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main(int argc, char **argv)
{
    int x, *p;
    //int test = argc > 1 ? atoi(argv[1]) : 0;
    int test = 1;

    switch (test) {
        default:
            puts("Missing or invalid test number");
            return EXIT_FAILURE;

        case 1:
            free(&x);
            break;
        case 2:
            p = (int *) malloc(sizeof(int) * 10);
            free(p + 1);
            break;

        case 3:
            p = (int *) malloc(sizeof(int) * 10);
            free(p);
            free(p);
            break;
        case 4:
            p = (int *) malloc(50000);
            free(p);
            break;
        case 5:
            p = (int*) malloc(0);
            free(p);
            break;
        case 6:
            p = NULL;
            free(p);
        case 7:
            p = (int*) malloc(sizeof(int) * 20);
            free(p);
    }

    printf("\nit works!");

    return EXIT_SUCCESS;
}
