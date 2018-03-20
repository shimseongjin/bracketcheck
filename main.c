#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "header.h"
StackType check(char ch, StackType *s);
StackType check2(char ch, StackType *s);
int main()
{
	int error_row[50];            // ������ ���� ����ġ�� �����ϱ����� �迭, �������� �ϰ������� ���
	int sel;                      // �޴�����
	char *source, fname[100], ch; // �ҷ��� �ҽ��� ����, �ҷ��� ���ϸ�, �о���̴� ����
	long fsize;                   // ������ ������
	int i, k = 0;                 // �ݺ����� ���� ����
	FILE *fp = NULL;
	StackType s, s2;              // s�� ������ �Ǻ��ϱ����� ����ü, s2�� �ּ����� �����ϱ����� ����ü
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
				printf("���ϸ� �Է� (���ư��� 0) : ");
				browse(fname);
				if (fname[0] == '0')
				{
					display();
					break;
				}
				fp = fopen(fname, "rb");
				if (fp == NULL)
				{
					printf("���ϸ��� �ٽ� Ȯ���ϼ���!\n");
				}
				else
				{
					fsize = GetFilesize(fp);        // ������ ũ�ⱸ��
					source = (char*)malloc(fsize);  // ������ ũ�⸸ŭ �����Ҵ�
					fread(source, 1, fsize, fp);    // ������ ����
					fclose(fp);
					printf("�ҷ����� ����!\n");
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
					printf("������ ���� �ҷ�������!\n");
					display();
					break;
				}
				else
				{
					printf("1. ��ü �ҽ��ڵ� Ȯ�� 2. ���� Ȯ��\n");
				}
				while (1)
				{
					scanf("%d", &sel);
					if (sel == 1)   // 1�� �����ϸ� �ҽ� ��ü ���
					{
						for (i = 0; i < fsize; i++)
						{
							ch = source[i];
							printf("%c", ch);
						}
						break;
					}
					else if (sel == 2)  // 2�� �����ϸ� �ҽ��� ����ϸ鼭 ������ �߰ߵǸ� error ���(check�� �Ǻ�)
					{
						k = 0;
						init(&s);
						init(&s2);
						init2(&s);
						for (i = 0; i < fsize; i++)
						{
							ch = source[i];
							printf("%c", ch); // �ҽ� ���
							if (s.stack[s.top] == '"'&&s.stack[s.top - 1] != '"') {} // ����ǥ ���� �����̸� �˻� x
							else
							{
								s2 = check2(ch, &s2);  // ����ǥ ���� ������ �ƴϸ� check2(�ּ��Ǻ�) ȣ��
							}
							if (s2.stack[s2.top] == '*' || ((s2.stack[s2.top] == '/') && (s2.stack[s2.top - 1] == '/'))) // �ּ��� ���� �Ǿ����� �˻� x
							{
							}
							else // �ּ��� �ƴ϶�� �˻�
							{
								s = check(ch, &s);   // ������ �ִ��� �˻�
								if (s.enter == 0) {} // ������ �߰ߵ��� �ʾ����� 
								else                 // ������ �߰� �Ǿ����� ������ ����ġ �迭�� ����ġ ����
								{
									error_row[k++] = s.count;
								}
							}
						}
						printf("\n���� �� ��ġ : ");
						for (i = 0; i < k; i++)      // ������ ����ġ ���
						{
							printf("%d ", error_row[i]);
						}
						init(&s2);
						break;
					}
					else
					{
						printf("�ٽ� �Է��ϼ���.\n");
					}
				}
				printf("\n");
				if (!is_empty(&s) && sel == 2)       // �����˻簡 �����µ��� ���ÿ� ���������� ����
				{
					printf("���� ��ȣ�� �ݴ� ��ȣ�� ���� �ٸ��ϴ�.\n");
				}
				display();
				break;
			}
		}
		else if (sel == 3)
		{
			printf("���α׷��� ����Ǿ����ϴ�.\n");
			exit(1);
		}
		else
		{
			printf("�ٽ� �Է��ϼ���.\n");
			display();
		}
		scanf("%d", &sel);
	}
	free(source);
	return 0;
}