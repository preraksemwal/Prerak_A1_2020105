CC=gcc  #variable declared


all: compile
	./run1
	./run2

compile: q1_fork.o q1_thread.o
	$(CC) q1_fork.o -o run1
	$(CC) q1_thread.o -o run2 -lpthread



q1_fork.o: q1_fork.c
	$(CC) q1_fork.c

q1_thread.o: q1_thread.c
	$(CC) q1_thread.c

