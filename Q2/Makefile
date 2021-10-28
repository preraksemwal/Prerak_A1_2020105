
all: compile
	./run
	./brun

compile: 
	gcc main.c a.c c.c -o run
	nasm -f elf64 -o b.o b.asm
	ld b.o -o brun 



