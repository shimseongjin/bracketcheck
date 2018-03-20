#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "header.h"
StackType check(char ch, StackType *s);
StackType check2(char ch, StackType *s);
int main()
{
	int error_row[50];            // 오류난 곳의 줄위치를 저장하기위한 배열, 마지막에 일괄적으로 출력
	int sel;                      // 메뉴선택
	char *source, fname[100], ch; // 불러온 소스를 저장, 불러올 파일명, 읽어들이는 문자
	long fsize;                   // 파일의 사이즈
	int i, k = 0;                 // 반복문을 위한 변수
	FILE *fp = NULL;
	StackType s, s2;              // s는 오류를 판별하기위한 구조체, s2는 주석문을 구별하기위한 구조체
	init(&s);
	init(&s2);
	display();
	scanf("%d", &sel);
	while (1)
	{
		if (sel == 1)
		{
			while (1)
			{
				printf("파일명 입력 (돌아가기 0) : ");
				browse(fname);
				if (fname[0] == '0')
				{
					display();
					break;
				}
				fp = fopen(fname, "rb");
				if (fp == NULL)
				{
					printf("파일명을 다시 확인하세요!\n");
				}
				else
				{
					fsize = GetFilesize(fp);        // 파일의 크기구함
					source = (char*)malloc(fsize);  // 파일의 크기만큼 동적할당
					fread(source, 1, fsize, fp);    // 파일을 복사
					fclose(fp);
					printf("불러오기 성공!\n");
					display();
					break;
				}
			}
		}
		else if (sel == 2)
		{
			while (1)
			{
				if (fp == NULL)
				{
					printf("파일을 먼저 불러오세요!\n");
					display();
					break;
				}
				else
				{
					printf("1. 전체 소스코드 확인 2. 오류 확인\n");
				}
				while (1)
				{
					scanf("%d", &sel);
					if (sel == 1)   // 1을 선택하면 소스 전체 출력
					{
						for (i = 0; i < fsize; i++)
						{
							ch = source[i];
							printf("%c", ch);
						}
						break;
					}
					else if (sel == 2)  // 2를 선택하면 소스를 출력하면서 오류가 발견되면 error 출력(check로 판별)
					{
						k = 0;
						init(&s);
						init(&s2);
						init2(&s);
						for (i = 0; i < fsize; i++)
						{
							ch = source[i];
							printf("%c", ch); // 소스 출력
							if (s.stack[s.top] == '"'&&s.stack[s.top - 1] != '"') {} // 따옴표 안의 문장이면 검사 x
							else
							{
								s2 = check2(ch, &s2);  // 따옴표 안의 문장이 아니면 check2(주석판별) 호출
							}
							if (s2.stack[s2.top] == '*' || ((s2.stack[s2.top] == '/') && (s2.stack[s2.top - 1] == '/'))) // 주석이 시작 되었으면 검사 x
							{
							}
							else // 주석이 아니라면 검사
							{
								s = check(ch, &s);   // 오류가 있는지 검사
								if (s.enter == 0) {} // 오류가 발견되지 않았으면 
								else                 // 오류가 발견 되었으면 오류의 줄위치 배열에 줄위치 저장
								{
									error_row[k++] = s.count;
								}
							}
						}
						printf("\n오류 줄 위치 : ");
						for (i = 0; i < k; i++)      // 오류의 줄위치 출력
						{
							printf("%d ", error_row[i]);
						}
						init(&s2);
						break;
					}
					else
					{
						printf("다시 입력하세요.\n");
					}
				}
				printf("\n");
				if (!is_empty(&s) && sel == 2)       // 오류검사가 끝났는데도 스택에 남아있으면 에러
				{
					printf("여는 괄호와 닫는 괄호의 수가 다릅니다.\n");
				}
				display();
				break;
			}
		}
		else if (sel == 3)
		{
			printf("프로그램이 종료되었습니다.\n");
			exit(1);
		}
		else
		{
			printf("다시 입력하세요.\n");
			display();
		}
		scanf("%d", &sel);
	}
	free(source);
	return 0;
}