polynomial.o: polynomial.c polynomial.h
	gcc -c polynomial.c

string_tools.o: string_tools.c string_tools.h
	gcc -c string_tools.c

main.o: main.c string_tools.h polynomial.h
	gcc -c main.c

main: polynomial.o string_tools.o main.o
	gcc *.o -o main