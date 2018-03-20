#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "header.h"
StackType check(char ch, StackType *s)
{
	int p; // pop의 인자 넣어주기 위한 변수
	char a;
	s->enter = 0;     // 오류 없음으로 초기화
	switch (ch)
	{
	case '\n':        // \n가 나오면 줄위치 변수 증가
		s->count++;
		break;
	case '"':
		push(s, ch);    // " 가 등장하면 먼저 push
		if (s->stack[s->top - 1] == '"')   // top-1이 "이면 닫힌 "가 들어온 것이기 때문에 pop을 두번해서 비워줌
		{
			a = pop(s);
			a = pop(s);
		}
		break;
	case '(': case '{': case '[': case '<':
		if (s->stack[s->top] == '"') {} //스택의 top값이 "이면 "가 시작된 곳이기 때문에 무시
		else
		{
			push(s, ch);
		}
		break;
	case ')': case '}': case ']': case '>':
		if (s->stack[s->top] == '"') {}
		else{
			if (is_empty(s))
			{
				BLUE
					printf("error!(스택공백에러)");
				ORIGINAL
					p = pop(s);
				s->enter = 1;
			}
			else
			{
				s->enter = print(s, ch); // print가 괄호 매칭이 되는지 판별 해주는데 매칭 안될 시 enter값 1 반환 매칭 될 시 0 반환
			}
		}
		break;
	}
	return *s;
}
StackType check2(char ch, StackType *s)
{
	int b;
	if (s->stack[0] == '/'&&s->stack[0] == '*'&&s->stack[s->top - 1] == '*'&&s->stack[s->top] == '/')
	{   // /**/으로 채워지면 비워줌
		b = pop(s);
		b = pop(s);
		b = pop(s);
		b = pop(s);
	}
	switch (ch){
	case '/':
		if (is_empty(s))
		{
			push(s, ch);
		}
		else   // 
			if (s->stack[s->top] == '*')
			{
				push(s, ch);
			}
			else if (s->stack[s->top] == '/')
			{
				push(s, ch);
			}
		break;
	case '*': // 주석이 시작되는 경우나 시작되있는 경우에만 
		if (s->stack[s->top] == '/')
			push(s, ch);
		else
			if (s->stack[s->top - 1] == '/'&&s->stack[s->top] == '*')
				push(s, ch);
		break;
	case '\n': // //의 주석을 사용하기 위함
		if (s->stack[s->top] == '/')
		{
			s->stack[s->top] = NULL;
			init(s);
		}
		break;
	}

	return *s;
}
int print(StackType *s, char ch) // 닫히는 괄호가 들어오면 오류를 판별하여 출력 리턴값은 스택구조체에서 매칭 여부를 확인 시켜줌
{
	char open_ch;

	open_ch = pop(s);
	if (ch == ')'&&open_ch != '(')
	{
		BLUE
			printf("error!");
		ORIGINAL
			return 1;
	}
	if (ch == '}'&&open_ch != '{')
	{
		BLUE
			printf("error!");
		ORIGINAL
			return 1;
	}
	if (ch == ']'&&open_ch != '[')
	{
		BLUE
			printf("error!");
		ORIGINAL
			return 1;
	}
	if (ch == '>'&&open_ch != '<')
	{
		BLUE
			printf("error!");
		ORIGINAL
			return 1;
	}
	else
	{
		return 0;
	}
}