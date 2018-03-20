#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "header.h"
void init(StackType *s)
{
	s->top = -1;
}
void init2(StackType *s)
{
	s->count = 1;
}
int is_empty(StackType *s)
{
	return (s->top == -1);
}
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
void push(StackType *s, int item)
{
	if (is_full(s))
	{
		printf("���� ��ȭ ����\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
int pop(StackType *s)
{
	if (is_empty(s))
	{
		return;
	}
	else return s->stack[(s->top)--];
}
int peek(StackType *s)
{
	if (is_empty(s))
	{
		printf("���� ���� ����\n");
		exit(1);
	}
	else return s->stack[s->top];
}
void browse(char fname[])
{
	scanf("%s", fname);
}
void display()
{
	printf("------------------------------------------\n");
	printf("����� �����Ͻʽÿ�. \n1. �ҷ����� 2. �������� 3. ���α׷� ���� : ");
}
long GetFilesize(FILE *fp)
{
	long fsize, fpos;
	fpos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	fseek(fp, fpos, SEEK_SET);
	return fsize;
}