#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#define N 11 // ¹ÙµÏÆÇ for¹® Á¶°Ç½Ä¿¡ µé¾î°¥ »ó¼ö
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define victory_y 27
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

void field();

int victory(int arr[13][13], int a, int x, int y);

void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c)
	{
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}
void gotoxy(int x, int y)
{
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}
int main(void)
{
	setcursortype(NOCURSOR);
	int x = 0, y = 0;//Ä¿¼­ À§Ä¡
	int count = 2;//È¦Â¦ ±¸ºÐ
	char ch;
	int px = 0, py = 0; //½Â¸® Á¶°Ç¿¡ ¾µ ¹è¿­ÀÇ Çà°ú ¿­
	int arr[13][13] = { 0 }; //½Â¸® Á¶°Ç¿¡ ¾µ ¹è¿­
	field();// ¹ÙµÏÆÇ ÇÔ¼ö
	gotoxy(x, y);
	if (count == 2)
	{
		printf("b");
	}
	else
	{
		printf("w");
	}
	while (1)
	{
		ch = _getch();

		gotoxy(x, y);
		printf(" ");
		switch (ch)
		{
		case UP:
			if (y > 0)
			{
				y -= 2;
				py--;
			}
			break;
		case DOWN:
			if (y < 24)
			{
				y += 2;
				py++;
			}
			break;
		case LEFT:
			if (x > 0)
			{
				x -= 4;
				px--;
			}
			break;
		case RIGHT:
			if (x < 45)
			{
				x += 4;
				px++;
			}
			break;
		case ' ':
			if (count % 2 == 0)
			{
				if (arr[py][px] == 0) {
					printf("¡Û");
					arr[py][px] = count;
					victory(arr, count, px, py);
					count++;
				}
				else
				{
					continue;
				}
			}
			else 
			{
				if (arr[py][px] == 0)
				{
					printf("¡Ü");
					arr[py][px] = count;
					if (victory(arr, count, px, py) == 1)
					{
						break;
					}
					else
					{
						
					}
					count--;
				}
				else
				{
					continue;
				}
			}
			break;
		}
		gotoxy(x, y);
		if (count == 2)
		{
			printf("b");
		}
		else
		{
			printf("w");
		}
	}
}

void field() //¹ÙµÏÆÇ Ãâ·Â ÇÔ¼ö
{
	int i, j;//for¹® Á¦¾îº¯¼ö
	printf(" ¦£");
	for (i = 0; i < N; i++)
	{
		printf("¦¡¦¡¦¡¦¨");
	}
	printf("¦¡¦¡¦¡¦¤\n");
	printf(" ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢\n");
	for (i = 0; i < N; i++)
	{
		printf(" ¦§");
		for (j = 0; j < N; j++)
		{
			printf("¦¡¦¡¦¡¦«");
		}

		printf("¦¡¦¡¦¡¦©\n");
		printf(" ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢   ¦¢\n");
	}
	printf(" ¦¦");
	for (i = 0; i < N; i++)
	{
		printf("¦¡¦¡¦¡¦ª");
	}
	printf("¦¡¦¡¦¡¦¥\n");
	printf("b´Â Èæ w´Â ¹é ¿À¸¥ÂÊ¿¡ µ¹ÀÌ ³õÀÓ");
	
}//¹ÙµÏÆÇ Ãâ·Â ÇÔ¼ö

int victory(int (*arr)[13], int a, int x, int y)
{
	int i, px = x, py = y;
	for ( i = 0; i < 5; i++)// ¿À¸¥ ÂÊ À§¿¡¼­ ¿ÞÂÊ ¾Æ·¡¹æÇâ Àß ÀÛµ¿ÇÔ
	{
		if (arr[py + 1][px + 1] != a && arr[py][px] == a && arr[py - 1][px - 1] == a && arr[py - 2][px - 2] == a && arr[py - 3][px - 3] == a && arr[py - 4][px - 4] == a && arr[py - 5][px - 5] != a)
		{
			if (a % 2 == 0)
			{
				gotoxy(0, victory_y);
				printf("Èæ ½Â¸®");
				return 1;
			}
			else
			{
				gotoxy(0, victory_y);
				printf("¹é ½Â¸®");
				return 1;
			}
		}
		px++;
		py++;
	}
	for ( i = 0, px = x, py = y; i < 5; i++)
	{
		if (arr[py + 1][px] != a && arr[py][px] == a && arr[py - 1][px] == a && arr[py - 2][px] == a && arr[py - 3][px] == a && arr[py - 4][px] == a && arr[py - 5][px] != a)
		{
			if (a % 2 == 0) 
			{
				gotoxy(0, victory_y);
				printf("Èæ ½Â¸®");
				return 1;
			}
			else
			{
				gotoxy(0, victory_y);
				printf("¹é ½Â¸®");
				return 1;
			}
		}
		py++;
	}
	for (i = 0, px = x, py = y; i < 5; i++)
	{
		if (arr[py][px+1] != a && arr[py][px] == a && arr[py][px-1] == a && arr[py][px-2] == a && arr[py][px-3] == a && arr[py][px-4] == a && arr[py][px - 5] != a)
		{
			if (a % 2 == 0)
			{
				gotoxy(0, victory_y);
				printf("Èæ ½Â¸®");
				return 1;
			}
			else
			{
				gotoxy(0, victory_y);
				printf("¹é ½Â¸®");
				return 1;
			}
		}
		px++;
	}
	for (i = 0, px = x, py = y; i < 5; i++)
	{
		if (arr[py+1][px-1] != a && arr[py][px] == a && arr[py - 1][px + 1] == a && arr[py - 2][px + 2] == a && arr[py - 3][px + 3] == a && arr[py - 4][px + 4] == a && arr[py - 5][px + 5] != a)
		{
			if (a % 2 == 0)
			{
				gotoxy(0, victory_y);
				printf("Èæ ½Â¸®");
				return 1;
			}
			else 
			{
				gotoxy(0, victory_y);
				printf("¹é ½Â¸®");
				return 1;
			}
		}
		py++;
		px--;
	}
	return 0;
}