queueADT.o: queueADT.c queueADT.h pos.h
	gcc -c queueADT.c
pos.o: pos.c pos.h
	gcc -c pos.c
main.o: main.c queueADT.h pos.h
	gcc -c main.c
main: queueADT.o pos.o main.o
	gcc *.o -o main