#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mymalloc.h"

int main(int argc, char **argv)
{
    int x, *p,*h, size;

    struct timeval start, end;
    double time;

    void *pA[120];
    int numP = 0;

    void* ptr1;
    void* ptr2;


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
            //*************************************************CORRECTNESS TESTING****************************************************
        case 4:                             //checks if you can call free one after the other (on different pointers of course).
            p = (int *) malloc(2500);
            h = (int *) malloc(1500);
            free(p);
            free(h);
            printf("Works perfectly!");
            break;
        case 5:                             //checks error message if size is 0
            p = (int*) malloc(0);
            break;
        case 6:                             //checks error message if pointer is NULL
            p = NULL;
            free(p);
            break;
        case 7:                             //proof that malloc() reserves unallocated memory, frees and coalesces.
            printf("\nAs you can see after freeing the original pointers it starts allocating from the "
                   "beginning and since we had two pointers this proves that malloc also coalesces freed blocks!\n\n");

            ptr1 = malloc(20);
            ptr2 = malloc(20);
            printf("ptr1: %p\n", ptr1);
            printf("ptr2: %p\n", ptr2);
            free(ptr1);
            free(ptr2);
            ptr1 = NULL;
            ptr2 = NULL;

            // Allocated another a block after free
            void *ptr3 = malloc(30);
            printf("ptr3: %p\n", ptr3);
            free(ptr3);
            ptr3 = NULL;

            printf("\nNow if we dont free any of the pointers till the end, "
                   "malloc allocates ptr3 after the ptr2 address which is what we want\n");

            ptr1 = malloc(10);
            ptr2 = malloc(20);
            ptr3 = malloc(30);
            printf("ptr1: %p\n", ptr1);
            printf("ptr2: %p\n", ptr2);
            printf("ptr3: %p\n", ptr3);
            free(ptr1);
            free(ptr2);
            free(ptr3);
            ptr1 = NULL;
            ptr2 = NULL;
            ptr3 = NULL;
            printf("\nNow if we only free ptr1 and keep ptr2, ptr3 will allocate after ptr2 because there is not "
                   "enough space where ptr1 was initially\n\n");

            ptr1 = malloc(10);
            ptr2 = malloc(20);
            ptr3 = malloc(30);
            free(ptr1);
            ptr1 = NULL;
            printf("ptr1: %p\n", ptr1);
            printf("ptr2: %p\n", ptr2);
            printf("ptr3: %p\n", ptr3);

            break;
        case 8:                                //Checks if malloc stores data and prints
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
            //******************************************************PERFORMANCE TESTING******************************************************
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
            for(int j = 0; j < 50; j++) {
                int n = 0;
                void* a[120];

                printf("\n\n***TASK ITERATION %d***\n\n", j+1);
                for (int i = 0; i < 120; i++) {
                    struct timeval start, end;
                    gettimeofday(&start, NULL);

                    int action = rand() % 2;
                    if (action == 0 && n < 120) {
                        pA[n] = malloc(1);
                        n++;
                    } else if (n > 0) {
                        int index = rand() % n;
                        free(pA[index]);
                        n--;
                        pA[index] = pA[n];
                    }

                    gettimeofday(&end, NULL);
                    double time = (end.tv_sec - start.tv_sec) * 1000.0;
                    time += (end.tv_usec - start.tv_usec) / 1000.0;
                    printf("Iteration %d: %f ms\n", i + 1, time);
                }

                for (int i = 0; i < n; i++) {
                    free(pA[i]);
                }
            }
            break;
    }
    return EXIT_SUCCESS;
}
