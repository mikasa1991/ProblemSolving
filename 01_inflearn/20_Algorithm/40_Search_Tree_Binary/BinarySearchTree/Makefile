binary_search_tree.o: binary_search_tree.c binary_search_tree.h
	gcc -c binary_search_tree.c
main.o: main.c binary_search_tree.h
	gcc -c main.c
main: binary_search_tree.o main.o
	gcc *.o -o main