library.o: library.c library.h string_tools.h
	gcc -c library.c

string_tools.o: string_tools.c string_tools.h
	gcc -c string_tools.c

main.o: main.c library.h string_tools.h
	gcc -c main.c

main: library.o string_tools.o main.o
	gcc *.o -o main