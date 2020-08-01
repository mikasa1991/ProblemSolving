/*
f(str): str번지를 시작으로 하는 문자열의 길이

case1. base case
f(문자열끝) = 0

case2. recursive case
f(str) = 1 + f(str + 1) 
*/

#include <stdio.h>

int func(char* str)
{
	if(*str == '\0') {return 0;}	//base case
	else {return 1 + func(str+1);} 	//recursive case
}

void main()
{
	char name[] = "dongheelee";	//lenth 10
	printf("length: %d\n", func(name));
}