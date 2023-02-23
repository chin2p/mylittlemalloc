$(CC) = gcc -Wall -fsanitize=address,undefined -c

testing: memgrind.o mymalloc.o
	$(CC) memgrind.o mymalloc.o -o testing

memgrind.o: memgrind.c mymalloc.h
	$(CC) -c memgrind.c

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) -c mymalloc.c

clean:
	rm *.o testing
