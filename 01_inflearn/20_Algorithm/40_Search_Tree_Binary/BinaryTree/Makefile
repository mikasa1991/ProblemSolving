binary_tree_traversal.o: binary_tree_traversal.c binary_tree_traversal.h
	gcc -c binary_tree_traversal.c
queue.o: queue.c queue.h binary_tree_traversal.h
	gcc -c queue.c
main.o: main.c queue.h
	gcc -c main.c
main: binary_tree_traversal.o queue.o main.o
	gcc *.o -o main