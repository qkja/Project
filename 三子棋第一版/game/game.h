#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 3
#define COL 3


//��ʼ������
extern void Init_board(char board[ROW][COL], int row, int col);

//��ӡ����
extern void Show_board(char board[ROW][COL], int row, int col);

//�����
extern void PlayerMove(char board[ROW][COL], int row, int col);

//������
extern void ComputerMove(char board[ROW][COL], int row, int col);

//�ж���Ӯ
extern char Is_win(char board[ROW][COL], int row, int col);