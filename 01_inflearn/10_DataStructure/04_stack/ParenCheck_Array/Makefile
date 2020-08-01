stack.o: stack.c stack.h
	gcc -c stack.c
main.o: main.c stack.h
	gcc -c main.c
main: main.o stack.o
	gcc *.o -o main