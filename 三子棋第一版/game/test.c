#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"

void menu()
{
	printf("********************\n");
	printf("*****  1.paly  *****\n");
	printf("*****  0.exit  *****\n");
	printf("********************\n");
}
//��� *
//���� #
//ƽ�� Q
//���� C

void PlayGame(void)
{
	char ret = 0;
	char board[ROW][COL] = { 0 };

	Init_board(board, ROW, COL);

	Show_board(board, ROW, COL);

	while (1)
	{
		//printf("�����>\n");
		PlayerMove(board, ROW, COL);

		Show_board(board, ROW, COL);
		ret = Is_win(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}

	   // printf("������>\n");
		ComputerMove(board, ROW, COL);
	
		Show_board(board, ROW, COL);
		ret = Is_win(board, ROW, COL);

		if (ret != 'C')
		{
			break;
		}
	}
	if (ret == '*')
	{
		printf("���Ӯ\n");
	}
	else if (ret == '#')
	{
		printf("����Ӯ\n");
	}
	else
	{
		printf("ƽ��\n");
	}

}

void test(void)
{
	srand((unsigned int)time(NULL));

	int input = 0;
	do
	{

		menu();
		printf("��ѡ��>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("����\n");
			PlayGame();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("ѡ�����������ѡ��\n");
			break;
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}