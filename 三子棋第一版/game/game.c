#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"

void Init_board(char board[ROW][COL], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void Show_board(char board[ROW][COL], int row, int col)
{


	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			if (j < col - 1)
				printf("|");
		}

		printf("\n");

		if (i < row - 1)
		{
        for (int j = 0; j < col; j++)
		   {
			  printf("---");

			  if (j < col - 1)
				printf("|");
		   }
		}
		
		printf("\n");
		
	}
}

void PlayerMove(char board[ROW][COL], int row, int col)
{
	int x = 0;
	int y = 0;
	printf("玩家走>\n");
	printf("请输入你的坐标 ：");

	while (1)
	{
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*';
				break;
			}
			else
			{
				printf("该坐标被占用，请重新输入！\n");
				printf("请输入你的坐标 ：");
			}
		}
		else
		{
			printf("坐标非法，请重输入!\n");
			printf("请输入你的坐标 ：");
		}
	}


}

void ComputerMove(char board[ROW][COL], int row, int col)
{
	printf("电脑走>\n");
	int x = 0;
	int y = 0;
	while (1)
	{
		x = rand() % ROW;
		y = rand() % COL;
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
	}
}

int Is_full(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
				return 0;
		}
	}
	return 1;
}

char Is_win(char board[ROW][COL], int row, int col)
{

	int temp = 0;
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		temp = 0;
		for (j = 0; j < col; j++)
		{
			temp+=board[i][j];
		}
		if ((temp == 3 * board[i][0])&&(temp != 3*' '))
		{
			return board[i][0];
		}
	}
	
	for (j = 0; j < col; j++)
	{
		temp = 0;
		for (i = 0; i < row; i++)
		{
			temp+=board[i][j];
		}
		if ((temp == 3 * board[0][j]) && (temp != 3 * ' '))
		{
			return board[0][j];
		}

	}
	//判断对角线
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ')
	{
		return  board[0][0];
	}

	//int i = 0;
	//int j = 0;
	////判断 行
	//for (i = 0; i < row; i++)
	//{
	//	if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
	//	return  board[i][0];

	//}
	////判断列
	//for (j = 0; j < col; j++)
	//{
	//	if (board[0][j] == board[1][j] && board[0][j] == board[2][j] && board[0][j] != ' ')
	//	return  board[0][0];
	//}
	////判断对角线
	//if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ')
	//{
	//	return  board[0][0];
	//}

	//if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
	//{
	//	return  board[1][1];
	//}
	//
	//判断满了没有  满了 1  未满 0
	if (0 == Is_full(board ,row,col))
	{
		return 'C';
	}
	return 'Q';

}
