#define _CRT_SECURE_NO_WARNINGS 1

#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include <stdio.h>
#include <windows.h>

#endif


//void proBar()
//{
//	const char* p = "|/-\\";
//	int i = 0;
//	char arr[101] = { 0 };
//	memset(arr, '\0', sizeof(arr));
//	while (i <= 100)
//	{
//		printf("[%100s][%d%%][%c]\r", arr, i, p[i % 4]);
//		fflush(stdout);
//		arr[i++] = '#';
//		usleep(80000);
//	}
//	printf("\n");
//}
//
//int main()
//{
//	proBar();
//	return 0;
//}



void proBar()
{
	const char* p = "|/-\\";
	int i = 0;
	char arr[101] = { 0 };
	memset(arr, '\0', sizeof(arr));
	while (i <= 100)
	{
		printf("[%100s][%d%%][%c]\r", arr, i, p[i % 4]);
		arr[i++] = '#';
		Sleep(100);
	}
	printf("\n");
}

//void proBar()
//{
//	char* p = "|/-\\";
//	int i = 0;
//	while (i <= 100)
//	{
//		printf("[%100s]\r", p);
//		/*printf("[%c]\r", p[i % 4]);*/
//		Sleep(100);
//		i++;
//	}
//	printf("ssss");
//	//printf("%d", strlen(p));
//}

int main()
{
	proBar();
	return 0;
}
