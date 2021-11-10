#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 3
#define COL 3


//初始化棋盘
extern void Init_board(char board[ROW][COL], int row, int col);

//打印棋盘
extern void Show_board(char board[ROW][COL], int row, int col);

//玩家走
extern void PlayerMove(char board[ROW][COL], int row, int col);

//电脑走
extern void ComputerMove(char board[ROW][COL], int row, int col);

//判断输赢
extern char Is_win(char board[ROW][COL], int row, int col);