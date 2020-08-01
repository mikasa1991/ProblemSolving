stackADT.o: stackADT.c stackADT.h
	gcc -c stackADT.c
main.o: main.c stackADT.h
	gcc -c main.c
main: stackADT.o main.o
	gcc *.o -o main