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
//		printf("第%d个红包的金额为 %.2f\n", count, ret / 100.0);
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
//		printf("请输入总金额: ");
//		double tatall = 0.0;
//		scanf("%lf", &tatall);
//		printf("请输入红包的个数: ");
//		int num = 0;
//		scanf("%d", &num);
//		printf("请输入最高金额 ：");
//		double max = 0.0;
//		scanf("%lf", &max);
//		printf("请输入最高金额 ：");
//		double min = 0.0;
//		scanf("%lf", &min);
//		
//
//		if (min > (tatall) / num)
//		{
//			printf("最低金额过大,请重新输入\n");
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


// 数据输入
void input()
{
    double total = 0.0;
    int num = 0;
    double min_price = 0.0, max_price = 0.0;

    printf("请输入以下数据：\n");
    printf("红包总金额： ");
    scanf("%lf", &total);
    putchar('\n');
    printf("红包数量： ");
    scanf("%d", &num);
    putchar('\n');
    printf("红包最低金额： ");
    scanf("%lf", &min_price);
    putchar('\n');
    printf("红包最高金额： ");
    scanf("%lf", &max_price);
    putchar('\n');
    redPackets(total, num, min_price, max_price);
}

// 生成(a, b) 之间的随机数
int range_random_price(int start_price, int end_price)
{
    return rand() % (end_price - start_price + 1) + start_price;
}

// total ：总金额（元） num：人的个数   min_price max_price :最低/最高金额
void redPackets(double Total, int num, double Min_price, double Max_price)
{
    // 刚开始金额全部扩大100倍转变成整数，最后输出的再除以一百，转变为浮点数
    int total = (int)Total * 100;
    int min_price = (int)Min_price * 100;
    int max_price = (int)Max_price * 100;

    if ((total * 1.0 / num) - min_price * 1.0 < 1e-9)
    {
        printf("您输入的总金额过小，或者抢的红包金额最低限度过大，请重新输入\n");
        input();
        return;
    }
    printf("抢红包结果如下：\n");

    for (int i = 1; i < num; i++)
    {
        int random_price;
        while (1)
        {
            random_price = range_random_price(min_price, max_price);
            //判断剩下的金额是否满足条件
            if ((total - random_price) * 1.0 / (num - i) - min_price * 1.0 >= 1e-9)
                break;
        }

        if (maxx < random_price)
            maxx = random_price, maxx_index = i;
        total -= random_price;// 剩余金额
        printf("第 %d 个人抢到的红包金额为 %.2f, 红包剩余金额为 %.2f\n", i, (double)(random_price / 100.0), (double)(total / 100.0));
    }


    if (maxx < total)
        maxx = total, maxx_index = num;

    // 输出最后一个人的红包金额
    printf("第 %d 个人抢到的红包金额为 %.2f, 红包剩余金额为 0.00\n", num, (double)(total / 100.0));

    printf("运气王是  %d  号\n", maxx_index);
}
