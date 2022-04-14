#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void init(int*);
void printPuzzle(int*);
int checkPuzzle(int*);
int inputKey(int*);

int main()
{
	int puzzle[25];
	init(puzzle);
	while (1)
	{
		printPuzzle(puzzle);
		if (checkPuzzle(puzzle))
		{
			printf("퍼즐 맞추기 성공했습니다.\n");
			break;
		}
		if (inputKey(puzzle))
			break;
	}
	printf("프로그램을 종료합니다.\n");
	return 0;
}

void init(int* puzzle)
{
	srand((unsigned int)time(NULL));
	int i;
	int sour, dest;
	int temp;
	for (i = 0; i < 25; i++)
		puzzle[i] = i;
	for (i = 0; i < 100; i++)
	{
		sour = rand() % 25;
		dest = rand() % 25;
		temp = puzzle[sour];
		puzzle[sour] = puzzle[dest];
		puzzle[dest] = temp;
	}
	for (i = 0; i < 25; i++)
		if (puzzle[i] == 0)
		{
			puzzle[i] = puzzle[24];
			puzzle[24] = 0;
			break;
		}
}

void printPuzzle(int* puzzle)
{
	int i;
	system("cls");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 1, 6, 6, 22, 6, 6, 22, 6, 6, 22, 6, 6, 22, 6, 6, 2);
	for (i = 0; i < 25; i++)
	{
		printf("%c%2d", 5, puzzle[i]);
		if ((i + 1) % 5 == 0)
		{
			printf("%c\n", 5);
			if ((i / 5) < 4)
				printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 25, 6, 6, 16, 6, 6, 16, 6, 6, 16, 6, 6, 16, 6, 6, 23);
		}
	}
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"), 3, 6, 6, 21, 6, 6, 21, 6, 6, 21, 6, 6, 21, 6, 6;
}

int checkPuzzle(int* puzzle)
{
	int i;
	int check = 0;
	for (i = 0; i < 25; i++)
		if (puzzle[i] == i + 1)
			check++;
	if (check == 24)
		return 1;
	return 0;
}

int inputKey(int* puzzle)
{
	char key;
	int index;
	for (index = 0; index < 25; index++)
		if (puzzle[index] == 0)
			break;
	while (1)
	{
		printf("입력(0 = 종료) : ");
		key = _getch();
		switch (key)
		{
		case 'w':
			if (index > 4)
			{
				puzzle[index] = puzzle[index - 5];
				puzzle[index - 5] = 0;
			}
			return 0;
		case 'a':
			if ((index % 5) > 0)
			{
				puzzle[index] = puzzle[index - 1];
				puzzle[index - 1] = 0;
			}
			return 0;
		case 's':
			if (index < 20)
			{
				puzzle[index] = puzzle[index + 5];
				puzzle[index + 5] = 0;
			}
			return 0;
		case 'd':
			if ((index % 5) < 4)
			{
				puzzle[index] = puzzle[index + 1];
				puzzle[index + 1] = 0;
			}
			return 0;
		case '0':
			return 1;
		default:
			printf("w, a, s, d 만 입력해주세요\n");
		}
	}
}
