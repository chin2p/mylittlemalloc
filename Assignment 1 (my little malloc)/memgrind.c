#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mymalloc.h"

int main(int argc, char **argv)
{
    int x, *p, size, *f;

    struct timeval start, end;
    double elapsedTime;
    int i, j;
    void *ptrs[120];
    int num_ptrs = 0;

    //int test = argc > 1 ? atoi(argv[1]) : 0;
    int test = 11;

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

            int *ptr = (int *) malloc(size * sizeof(int));

            if(ptr == NULL){
                break;
            }


            printf("Please Enter all %d integer(s)\n", size);
            for (int i = 0; i < size; i++) {
                printf("(%d) Enter each integer: ", i + 1);
                scanf("%d", ptr + i);
            }

            for (int i = 0; i < size; i++) {
                printf("%d ", *(ptr + i));
            }
            printf("\n");

            free(ptr);
            ptr = NULL;

            break;
        case 8:
            p = (int*) malloc(4096);
            free(p);
            break;
        case 9:
            for (i = 0; i < 50; i++) {
                gettimeofday(&start, NULL);
                for (j = 0; j < 120; j++) {
                    void *ptr = mymalloc(1, __FILE__, __LINE__);
                    myfree(ptr, __FILE__, __LINE__);
                }
                gettimeofday(&end, NULL);
                elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
                elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
                printf("Task 1, iteration %d: %f ms\n", i, elapsedTime);
            }
            break;
        case 10:
            for (i = 0; i < 50; i++) {
                gettimeofday(&start, NULL);
                void *ptrs[120];
                for (j = 0; j < 120; j++) {
                    ptrs[j] = mymalloc(1, __FILE__, __LINE__);
                }
                for (j = 0; j < 120; j++) {
                    myfree(ptrs[j], __FILE__, __LINE__);
                }
                gettimeofday(&end, NULL);
                elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
                elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
                printf("Task 2, iteration %d: %f ms\n", i, elapsedTime);
            }
            break;
        case 11:
            for (i = 0; i < 50; i++) {
                gettimeofday(&start, NULL);
                for (j = 0; j < 120; j++) {
                    int action = rand() % 2;
                    if (action == 0 && num_ptrs < 120) {
                        ptrs[num_ptrs] = mymalloc(1, __FILE__, __LINE__);
                        num_ptrs++;
                    } else if (num_ptrs > 0) {
                        int index = rand() % num_ptrs;
                        myfree(ptrs[index], __FILE__, __LINE__);
                        ptrs[index] = ptrs[num_ptrs - 1];
                        num_ptrs--;
                    }
                }
                for (j = 0; j < num_ptrs; j++) {
                    myfree(ptrs[j], __FILE__, __LINE__);
                }
                gettimeofday(&end, NULL);
                elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
                elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
                printf("Task 3, iteration %d: %f ms\n", i, elapsedTime);
            }
            break;
        case 12:
            break;
    }

    printf("\nit works!");

    return EXIT_SUCCESS;
}
