#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "header.h"
StackType check(char ch, StackType *s)
{
	int p; // pop�� ���� �־��ֱ� ���� ����
	char a;
	s->enter = 0;     // ���� �������� �ʱ�ȭ
	switch (ch)
	{
	case '\n':        // \n�� ������ ����ġ ���� ����
		s->count++;
		break;
	case '"':
		push(s, ch);    // " �� �����ϸ� ���� push
		if (s->stack[s->top - 1] == '"')   // top-1�� "�̸� ���� "�� ���� ���̱� ������ pop�� �ι��ؼ� �����
		{
			a = pop(s);
			a = pop(s);
		}
		break;
	case '(': case '{': case '[': case '<':
		if (s->stack[s->top] == '"') {} //������ top���� "�̸� "�� ���۵� ���̱� ������ ����
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
					printf("error!(���ð��鿡��)");
				ORIGINAL
					p = pop(s);
				s->enter = 1;
			}
			else
			{
				s->enter = print(s, ch); // print�� ��ȣ ��Ī�� �Ǵ��� �Ǻ� ���ִµ� ��Ī �ȵ� �� enter�� 1 ��ȯ ��Ī �� �� 0 ��ȯ
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
	{   // /**/���� ä������ �����
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
	case '*': // �ּ��� ���۵Ǵ� ��쳪 ���۵��ִ� ��쿡�� 
		if (s->stack[s->top] == '/')
			push(s, ch);
		else
			if (s->stack[s->top - 1] == '/'&&s->stack[s->top] == '*')
				push(s, ch);
		break;
	case '\n': // //�� �ּ��� ����ϱ� ����
		if (s->stack[s->top] == '/')
		{
			s->stack[s->top] = NULL;
			init(s);
		}
		break;
	}

	return *s;
}
int print(StackType *s, char ch) // ������ ��ȣ�� ������ ������ �Ǻ��Ͽ� ��� ���ϰ��� ���ñ���ü���� ��Ī ���θ� Ȯ�� ������
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