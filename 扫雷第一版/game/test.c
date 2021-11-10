#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"

void menu()
{
	printf("***********************\n");
	printf("*****   0.exit    *****\n");
	printf("*****   1.play    *****\n");
	printf("***********************\n");
}

void game()
{
	char mine[ROWS][COLS];
	char show[ROWS][COLS];
	// 初始化棋盘
	Init_board(mine,ROWS,COLS,'0');
	Init_board(show,ROWS,COLS,'*');

	//打印棋盘
	/*Display(mine, ROW, COL);
	Display(show, ROW, COL);*/

	//设置雷
	Setmine(mine);
	//Display(mine, ROW, COL);
	Display(show, ROW, COL);

	//排查雷
	Searchmine(mine,show,ROW,COL);

}

void test()
{
	int input = 0;
	srand((unsigned int) time(NULL));

	do
	{

		menu();
		printf("请输入：");
		scanf("%d", &input);
		switch (input)
		{
		case 0:
			printf("已退出\n");
			break;
		case 1:
			game();
			break;
		default:
			printf("选择错误\n");
			break;

		}
	} while (input);
}

int main()
{
	test();
	return 0;
}