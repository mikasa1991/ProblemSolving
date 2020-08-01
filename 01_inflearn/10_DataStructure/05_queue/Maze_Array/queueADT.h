#ifndef QUEUEADT_H
#define QUEUEADT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "pos.h"

#define INIT_CAPACITY 100

typedef position item;
typedef struct _queue queue;

typedef struct _queue
{
	item* contents;
	int front;
	int rear;
	int size;		//the count of data
	int capacity;	//the size of array
}queue;

void terminate(const char* msg);
int get_size(queue* q);
queue* create_queue_instance();
item* create_item_instance(queue* q);
void destroy(queue* q);
void make_empty(queue* q);
bool is_empty(queue* q);
bool is_full(queue* q);
void enqueue(queue* q, item i);
item dequeue(queue* q);
item peek(queue* q);
void reallocate(queue* q);

#endif