#ifndef STACK_H
#define STACK_H

#define MAX_CAPACITY 100
#define MAX_LENGTH 100

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//function declared
void push(char ch);
char pop();
char peek();
bool is_empty();
bool is_full();

#endif