/*
f(str): str번지를 시작으로 하는 문자열의 출력문

case1. base case
f(문자열끝) = 0

case2. recursive case
f(str) = print "str번지 문자" + f(str + 1) 
*/

#include <stdio.h>

void func(char* str)
{
	if(*str == '\0') {return;}	//base case
	else						//recursive case 
	{
		printf("%c", *str);
		func(str + 1);
	}
}

void main()
{
	char name[] = "dongheelee";	//lenth 10
	func(name);
	puts(" ");
}