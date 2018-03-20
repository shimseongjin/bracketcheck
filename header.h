#include <stdio.h>
#include <string.h>
#include <Windows.h>
#define COL GetStdHandle(STD_OUTPUT_HANDLE)
#define BLUE SetConsoleTextAttribute(COL,0x0009);
#define ORIGINAL SetConsoleTextAttribute(COL,0x0007);
#define MAX_STACK_SIZE 100
typedef struct {
	int stack[MAX_STACK_SIZE];
	int top;
	int count;
	int enter;
}StackType;