linkedlist.o: linkedlist.c linkedlist.h
	gcc -c linkedlist.c
main.o: main.c linkedlist.h
	gcc -c main.c
main: linkedlist.o main.o
	gcc *.o -o main