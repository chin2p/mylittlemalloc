My little malloc()

Names - Hamad Naveed (hn197), Chirantan Patel (csp126)

Test plan -
a. What properties your library must have for you to consider it correct
b. How you intend to check that your code has these properties
c. The specific methods you will use to check each property

The goal of this project is to make our own version of malloc and free in C. We will detect common usage errors and report them as well.
Project files are -
memgrind.c (this includes all the test cases and performance testing)
mymalloc.c (this includes our own malloc and free)
mymalloc.h (this includes all the header files, containing function prototypes, other definitions)
Makefile
and this readme.txt file

Our implementations for malloc and free (We are using linked list for these methods)

malloc()
- Our malloc() takes three arguments: size, file and line. Firstly our function checks if size for the malloc call is zero. If it is zero then
it prints an error message and returns NULL. After that we check if the linked list of free memory blocks is empty. We named this head, if it is empty
then we initialize the linked list with entire memory block of size MEMSIZE. After we initialize the free list, we find a free memory block that is
large enough to hold requested amount of memory. Then it divides it into two parts, one is the requested memory and other is the free memory. This
returns a pointer to the start of block that holds requested memory. If there is not enough memory to allocate then it prints an error message and returns NULL


Test cases - 
All the testcases are in memgrind.c
Test case 1 - calls free() with an address not obtained from malloc()
Test case 2 - calls free() with an address not at the start of a chunk
Test case 3 - calls free() a second time on the same pointer
Test case 4 - calls malloc() with a size greater than MEMSIZE(4096)
Test case 5 - calls malloc() with a size of 0
Test case 6 - calls free() on pointer = NULL
Test case 7 - tests malloc() and free() with user inputs
Test case 8 - calls malloc() with size 4096
Test case 9 - calls malloc() and immediately free() a 1-byte chunk, 120 times
Test case 10 - Use malloc() to get 120 1-byte chunks, storing the pointers in an array, then use free() to deallocate the chunks.
Test case 11 - Randomly choose between:
                . Allocating a 1-byte chunk and storing the pointer in an array.
                . Deallocating one of the chunks in the array (if any)
               Repeat until you have called malloc() 120 times, then free all remaining allocated chunks.
Test case 12 - 
Test case 13 -
