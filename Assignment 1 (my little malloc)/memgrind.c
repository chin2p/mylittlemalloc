#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mymalloc.h"


int main(int argc, char **argv)
{
    int x, *p, size;

    struct timeval start, end;
    double time;
    void *pA[120];
    int numP = 0;

    int test = argc > 1 ? atoi(argv[1]) : 0;

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
            break;
        case 7:
            printf("Please enter the amount of integers needed: ");
            scanf("%d", &size);

            p = (int *) malloc(size * sizeof(int));

            printf("Please Enter all %d integer(s)\n", size);
            for (int i = 0; i < size; i++) {
                printf("(%d) Enter each integer: ", i+1);
                scanf("%d", p + i);
            }

            for (int i = 0; i < size; i++) {
                printf("%d ", *(p + i));
            }
            printf("\n");

            free(p);
            p = NULL;

            break;
        case 8:
            p = (int*) malloc(4096);
            free(p);
            break;
        case 9: //1
            printf("Performance Test 1:\n\n");
            for (int i = 0; i < 50; i++) {
                gettimeofday(&start, NULL);
                for (int j = 0; j < 120; j++) {
                    p = (int*) malloc(1);
                    free(p);
                }
                gettimeofday(&end, NULL);
                time = (end.tv_sec - start.tv_sec) * 1000.0;
                time += (end.tv_usec - start.tv_usec) / 1000.0;
                printf("Iteration %d: %f ms\n", i+1,time );
            }
            break;
        case 10: //2
            printf("Performance Test 2:\n\n");
            for (int i = 0; i < 50; i++) {
                gettimeofday(&start, NULL);
                for (int j = 0; j < 120; j++) {
                    pA[j] = malloc(1);
                }
                for (int j = 0; j < 120; j++) {
                    free(pA[j]);
                }
                gettimeofday(&end, NULL);
                time = (end.tv_sec - start.tv_sec) * 1000.0;
                time += (end.tv_usec - start.tv_usec) / 1000.0;
                printf("Iteration %d: %f ms\n", i+1,time );
            }
            break;
        case 11: //3
            printf("Performance Test 3:\n\n");

            for (int i = 0; i < 120; i++) {
                gettimeofday(&start, NULL);

                int action = rand() % 2;
                if (action == 0 && numP < pA) {
                    pA[numP] = malloc(1);
                    numP++;
                } else if (numP > 0) {
                    int index = rand() % numP;
                    free(pA[index]);
                    numP--;
                    pA[index] = pA[numP];
                }

                gettimeofday(&end, NULL);
                time = (end.tv_sec - start.tv_sec) * 1000.0;
                time += (end.tv_usec - start.tv_usec) / 1000.0;
                printf("Iteration %d: %f ms\n", i+1, time);
            }

            for (int i = 0; i < numP; i++) {
                free(pA[i]);
            }
            break;
    }
    return EXIT_SUCCESS;
}
