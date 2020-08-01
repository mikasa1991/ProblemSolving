pos.o: pos.c pos.h
	gcc -c pos.c
stackADT.o: stackADT.c stackADT.h pos.h
	gcc -c stackADT.c
main.o: main.c stackADT.h pos.h
	gcc -c main.c
main: pos.o stackADT.o main.o
	gcc *.o -o main