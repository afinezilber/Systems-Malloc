COMPILER = gcc
CFLAGS = -Wall -g

all: mymalloc

mymalloc.o: mymalloc.c mymalloc.h
	$(COMPILER) $(CFLAG) -c mymalloc.c

main.o: main.c mymalloc.h
	$(COMPILER) $(CFLAGS) -c main.c
	
mymalloc: mymalloc.o main.o
	$(COMPILER) $(CFLAGS) -o mymalloc main.o mymalloc.o
	
clean:
	rm -f *.o mymalloc
