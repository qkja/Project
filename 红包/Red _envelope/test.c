#define _CRT_SECURE_NO_WARNINGS 1

//int setrad( int max1, int min1)
//{
//	return rand() % (max1 - min1) + min1;
//}
//
//void test(double ta, int num, double max, double min)
//{
//	int tatall = (int)(ta * 100);
//	int max1 = (int)(max * 100);
//	int min1 = (int)(min * 100);
//    
//	 //100
//	 // 4
//	 //20
//	 //80
//	int count = 0;
//
//	while (count<num)
//	{
//
//		int ret = setrad(max1, min1);
//		count++;
//		printf("��%d������Ľ��Ϊ %.2f\n", count, ret / 100.0);
//
//		tatall -= ret;
//
//		if(tatall/(num-count)<)
//
//	}
//
//}
//
//void set()
//{
//	while (1)
//	{
//		printf("�������ܽ��: ");
//		double tatall = 0.0;
//		scanf("%lf", &tatall);
//		printf("���������ĸ���: ");
//		int num = 0;
//		scanf("%d", &num);
//		printf("��������߽�� ��");
//		double max = 0.0;
//		scanf("%lf", &max);
//		printf("��������߽�� ��");
//		double min = 0.0;
//		scanf("%lf", &min);
//		
//
//		if (min > (tatall) / num)
//		{
//			printf("��ͽ�����,����������\n");
//		}
//		else
//		{
//			test(tatall,num,max,min);
//			break;
//		}
//	}
//
//	
//}
//
//int main()
//{
//	set();
//	return 0;
//}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input();
int range_random_price(int start_price, int end_price);
void redPackets(double Total, int num, double Min_price, double Max_price);

int maxx = 0, maxx_index = -1;

int main()
{
    input();
    return 0;
}


// ��������
void input()
{
    double total = 0.0;
    int num = 0;
    double min_price = 0.0, max_price = 0.0;

    printf("�������������ݣ�\n");
    printf("����ܽ� ");
    scanf("%lf", &total);
    putchar('\n');
    printf("��������� ");
    scanf("%d", &num);
    putchar('\n');
    printf("�����ͽ� ");
    scanf("%lf", &min_price);
    putchar('\n');
    printf("�����߽� ");
    scanf("%lf", &max_price);
    putchar('\n');
    redPackets(total, num, min_price, max_price);
}

// ����(a, b) ֮��������
int range_random_price(int start_price, int end_price)
{
    return rand() % (end_price - start_price + 1) + start_price;
}

// total ���ܽ�Ԫ�� num���˵ĸ���   min_price max_price :���/��߽��
void redPackets(double Total, int num, double Min_price, double Max_price)
{
    // �տ�ʼ���ȫ������100��ת������������������ٳ���һ�٣�ת��Ϊ������
    int total = (int)Total * 100;
    int min_price = (int)Min_price * 100;
    int max_price = (int)Max_price * 100;

    if ((total * 1.0 / num) - min_price * 1.0 < 1e-9)
    {
        printf("��������ܽ���С���������ĺ���������޶ȹ�������������\n");
        input();
        return;
    }
    printf("�����������£�\n");

    for (int i = 1; i < num; i++)
    {
        int random_price;
        while (1)
        {
            random_price = range_random_price(min_price, max_price);
            //�ж�ʣ�µĽ���Ƿ���������
            if ((total - random_price) * 1.0 / (num - i) - min_price * 1.0 >= 1e-9)
                break;
        }

        if (maxx < random_price)
            maxx = random_price, maxx_index = i;
        total -= random_price;// ʣ����
        printf("�� %d ���������ĺ�����Ϊ %.2f, ���ʣ����Ϊ %.2f\n", i, (double)(random_price / 100.0), (double)(total / 100.0));
    }


    if (maxx < total)
        maxx = total, maxx_index = num;

    // ������һ���˵ĺ�����
    printf("�� %d ���������ĺ�����Ϊ %.2f, ���ʣ����Ϊ 0.00\n", num, (double)(total / 100.0));

    printf("��������  %d  ��\n", maxx_index);
}
