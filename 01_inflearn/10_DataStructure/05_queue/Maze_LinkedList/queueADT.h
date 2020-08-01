#ifndef QUEUEADT_H
#define QUEUEADT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int item;
typedef struct _node node;
typedef struct _queue queue;

typedef struct _node
{
	item data;
	node* next;
}node;

typedef struct _queue
{
	node* front;	//for dequeue
	node* rear;		//for enqueue
	int size;
}queue;

void terminate(const char* msg);
int get_size(queue* q);
queue* create_queue_instance();
node* create_node_instance(item i);
void destroy(queue* q);
void make_empty(queue* q);
bool is_empty(queue* q);
void enqueue(queue* q, item i);
item dequeue(queue* q);
item peek(queue q);

#endif