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
	// ��ʼ������
	Init_board(mine,ROWS,COLS,'0');
	Init_board(show,ROWS,COLS,'*');

	//��ӡ����
	/*Display(mine, ROW, COL);
	Display(show, ROW, COL);*/

	//������
	Setmine(mine);
	//Display(mine, ROW, COL);
	Display(show, ROW, COL);

	//�Ų���
	Searchmine(mine,show,ROW,COL);

}

void test()
{
	int input = 0;
	srand((unsigned int) time(NULL));

	do
	{

		menu();
		printf("�����룺");
		scanf("%d", &input);
		switch (input)
		{
		case 0:
			printf("���˳�\n");
			break;
		case 1:
			game();
			break;
		default:
			printf("ѡ�����\n");
			break;

		}
	} while (input);
}

int main()
{
	test();
	return 0;
}