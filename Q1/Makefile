
CC=gcc  #variable declared
CFLAGS=-c -Wall

all: compile
	./run1
	./run2

compile: Q3_a.o Q3_b.o Q4.o
	$(CC) Q3_a.o -o run1
	$(CC) Q3_b.o -o run2
	$(CC) Q4.o -o run3

    


Q3_a.o: Q3_a.c
	$(CC) $(CFLAGS) Q3_a.c

Q3_b.o: Q3_b.c
	$(CC) $(CFLAGS) Q3_b.c
    
Q4.o: Q4.c
	$(CC) $(CFLAGS) Q4.c



