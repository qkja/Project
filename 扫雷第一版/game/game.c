#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"

void Init_board(char board[ROWS][COLS], int rows, int cols, char ch)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			board[i][j] = ch;
		}
	}
}

void Display(char board[ROWS][COLS], int row, int col)
{
	for (int i = 0; i <= col; i++)
	{
		printf("%d ", i);
	}
	printf("\n");

	for (int i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (int j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}

		printf("\n");
	}

}

void Setmine(char board[ROWS][COLS])
{
	int x = 0;
	int y = 0;
	int count = 0;

   
	while (count < MINE)
	{

		x = rand() % ROW + 1;
		y = rand() % COL + 1;

		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count++;
		}
	}


}

int Findmine(char boardmine[ROWS][COLS], int x, int y)
{
	return  boardmine[x - 1][y] + boardmine[x + 1][y] + boardmine[x - 1][y - 1] + boardmine[x - 1][y + 1] +
		boardmine[x][y - 1] + boardmine[x][y + 1] + boardmine[x + 1][y - 1] + boardmine[x + 1][y + 1] - 8 * '0';
}

void Searchmine(char boardmine[ROWS][COLS], char boardshow[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int count = 0;

	while (count < ROW*COL-MINE)
	{
		printf("请输入你的坐标：");
		scanf("%d %d", &x, &y);

		if (x >= 1 && x <= row && y >= 1 && y < col)
		{
			if (boardmine[x][y] == '1')
			{
				printf("很遗憾你被炸死了\n");
				break;

			}
			else
			{
				int ret = Findmine(boardmine,x,y);
				boardshow[x][y] = ret + '0';
				Display(boardshow, ROW, COL);
				count++;
			}
		
		}
		else
		{
			printf("输入坐标错误,请重新输入\n");
		}
	}//endofwhile

	if (count == ROW * COL - MINE)
	{
		printf("你赢了!!!\n");
	}
}