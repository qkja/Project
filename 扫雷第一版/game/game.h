#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#define ROW 9
#define COL 9
#define ROWS ROW + 2
#define COLS COL + 2
#define MINE 10

#include<stdio.h>
#include<stdlib.h>
#include<time.h>


//≥ı ºªØ∆Â≈Ã
extern void Init_board(char board[ROWS][COLS], int rows, int cols, char ch);

//¥Ú”°∆Â≈Ã
extern void Display(char board[ROWS][COLS], int row, int col);


//…Ë÷√¿◊
extern void Setmine(char board[ROWS][COLS]);

//≈≈≤È¿◊
extern void Searchmine(char boardmine[ROWS][COLS], char boardshow[ROWS][COLS], int row, int col);
