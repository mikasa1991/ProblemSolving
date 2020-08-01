#ifndef POLYNOMIAL_H
#define	POLYNOMIAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_POLYS 10		//polynomials max count
#define BUFFER_LENGTH 100

typedef struct _term term;
typedef struct _polynomial polynomial;

typedef struct _term		//node
{
	int coef;	//coefficient?	
	int expo;	//exponential?
	term* next;
}term;

typedef struct _polynomial 	//head
{
	char name;		//function name
	term* first;	//the head of node
	int size;		//the count of terms
}polynomial;

//variables declared
extern polynomial* polys[MAX_POLYS];
extern int n;	//the count of polynomials

//functions declared
term* create_term_instance();
polynomial* create_polynomial_instance(char name);
void add_term(int c, int e, polynomial* poly);
int eval_poly(polynomial* poly, int x);
int eval_term(term* term, int x);
void printf_poly(polynomial* p);
void print_term(term* pterm);
polynomial* create_by_parse_polynomial(char name, char* body);
int parse_and_add_term(char* expr, int begin, int end, polynomial* p_poly);
void destroy_polynomial(polynomial* ptr_poly);
void insert_polynomial(polynomial* ptr_poly);
polynomial* create_by_add_two_polynomials(char name, char f, char g);

#endif