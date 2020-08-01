#include "polynomial.h"

polynomial* polys[MAX_POLYS];
int n = 0;	//the count of polynomials

term* create_term_instance()	//allocate and initialize
{
	term* t = (term*)malloc(sizeof(term));
	t->coef = 0;
	t->expo = 0;
	return t;
}

polynomial* create_polynomial_instance(char name)	//allocate and initialize
{
	polynomial* ptr_poly = (polynomial*)malloc(sizeof(polynomial));
	ptr_poly->name = name;
	ptr_poly->size = 0;
	ptr_poly->first = NULL;
	return ptr_poly;
}

/*
c: coefficient
e: expotential
*/
void add_term(int c, int e, polynomial* poly)
{
	if(c == 0) return;		//if coefficient is zero, it means that add_term not exist.
	term* p = poly->first;
	term* q = NULL;

	//conference: pic02
	//추가되는 항이 내림차순으로 배열될 수 있도록 포인터를 조정하기 위함
	while( (p != NULL) && (p->expo > e) )
	{
		//q is always behind p.
		q = p;
		p = p->next;
	}

	//case1: if same expo of p exists
	//need to delete p, so q(prev) is important
	if( p != NULL && p->expo == e)
	{
		p->coef = p->coef + c;
		if(p->coef == 0)			//if coef is zero, p must be removed.
		{
			if(q == NULL) { poly->first = p->next; }	//if p is first term
			else 		  { q->next = p->next; }		//if p isn't first term
			poly->size --;								//term size downcounting
			free(p);									//free p(heap)
		}
		return;
	}

	//case2: if the expo isn't same with the expo of another term
	//need to insert new node(term), so q(prev) is important.
	term* term = create_term_instance();
	term->coef = c;
	term->expo = e;

	if(q == NULL)	//add_term_front
	{
		term->next = poly->first;
		poly->first = term;
	}
	else			//add_term_between_q_and_p
	{
		term->next = p;
		q->next = term;
	}
	poly->size++;	//term size upcounting
}

int eval_poly(polynomial* poly, int x)
{
	int result = 0;
	term* t = poly->first;

	//traverse
	while(t != NULL)
	{
		result = result + eval_term(t, x);
		t = t->next;
	}
	return result;
}

int eval_term(term* term, int x)
{
	int result = term->coef;
	for(int i = 0; i < term->expo; i++)
	{
		result = result * x;
	}
	return result;
}

void printf_poly(polynomial* p)
{
	printf("%c=", p->name);
	term* t = p->first;
	while(t != NULL) //traverse
	{
		print_term(t);
		t = t->next;
		if(t != NULL && t->coef > 0) printf("+");
	}
	puts(" ");
}

void print_term(term* pterm)
{
	if(pterm->expo == 0)
	{
		printf("%d", pterm->coef);
	}
	else if(pterm->expo == 1)
	{
		if(pterm->coef == 1)  printf("x");
		else 				  printf("%dx", pterm->coef);
	}
	else
	{	if(pterm->coef == 1) printf("x^%d", pterm->expo);
		else 				 printf("%dx^%d", pterm->coef, pterm->expo);
	}
}

polynomial* create_by_parse_polynomial(char name, char* body)
{
	polynomial* ptr_poly = create_polynomial_instance(name);
	int i = 0;
	int begin_term = 0;

	//3x^2+2x-3
	//any term is from begin_term to i. [begin_term, i)
	//conference: pic03
	while( i < strlen(body) )
	{
		if(body[i] == '+' || body[i] == '-') i++;
		while(i < strlen(body) && (body[i] != '+') && (body[i] != '-')) i++;
		int result = parse_and_add_term(body, begin_term, i, ptr_poly);
		if(result == 0)	//error
		{
			destroy_polynomial(ptr_poly);
			return NULL;
		}
		begin_term = i;
	}
	return ptr_poly;
}

int parse_and_add_term(char* expr, int begin, int end, polynomial* p_poly)
{
	int i = begin;
	int sign_coef = 1;
	int coef = 0;
	int expo = 1;

	//sign write
	if     (expr[i] == '+') i++;
	else if(expr[i] == '-')
	{
		sign_coef = -1;
		i++;
	}

	//coef write
	while(i < end && expr[i] >= '0' && expr[i] <= '9')
	{
		coef = coef*10 + (int)(expr[i] - '0');
		i++;
	}

	if(coef == 0) coef = sign_coef;			//if coef +x^n or -x^n
	else 		  coef = coef * sign_coef;

	//case1. constant term
	//after writing coef, if i >= end is True, it is constant term
	if(i >= end)
	{
		add_term(coef, 0, p_poly);
		return 1;
	}

	//상수 다음에 x가 아니라면 잘못된 입력이므로
	if(expr[i] != 'x') return 0;	//error
	i++;

	//case2. x(^1) term
	if(i >= end) //if it is x(^1) term
	{
		add_term(coef, 1, p_poly);
		return 1;
	}

	//x 다음에 ^가 아니라면 잘못된 입력이므로
	if(expr[i] != '^') return 0;	//error
	i++;
	
	//case3.x(over ^1) term
	expo = 0;
	while(i < end && expr[i] >= '0' && expr[i] <= '9')	//write expo
	{
		expo = expo*10 +(int)(expr[i] - '0');
		i++;
	}
	add_term(coef, expo, p_poly);
	return 1;
}

void destroy_polynomial(polynomial* ptr_poly)
{
	if(ptr_poly == NULL) return;
	
	term* t = ptr_poly->first;
	term* tmp;
	while(t != NULL)
	{
		tmp = t;
		t = t->next;
		free(tmp);
	}
	free(ptr_poly);
}

void insert_polynomial(polynomial* ptr_poly)
{
	//case1.같은 함수명이 존재할 때,
	for(int i = 0; i < n; i++)
	{
		if(polys[i]->name == ptr_poly->name)	//if same function name exists
		{
			destroy_polynomial(polys[i]);
			polys[i] = ptr_poly;
			return;
		}
	}

	//case2.같은 함수명이 존재하지 않을 때,
	polys[n++] = ptr_poly;
}

polynomial* create_by_add_two_polynomials(char name, char f, char g)
{
	polynomial* ptr_poly = create_polynomial_instance(name);
	term* t;

	for(int i = 0; i < n; i++)
	{
		if((polys[i]->name == f) || (polys[i]->name == g))
		{
			t = polys[i]->first;
			while(t != NULL)
			{
				add_term(t->coef, t->expo, ptr_poly);
				t = t->next;
			}
			//printf_poly(ptr_poly);	//for debug
		}
	}
	return ptr_poly;
}