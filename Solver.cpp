#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawbox()
{
	int ic;
	gotoxy(13, 5); printf("%c", 201);
	for (ic = 1; ic <= 51; ic++) printf("%c", 205);
	printf("%c", 187);
	for (ic = 6; ic <= 22;) { gotoxy(13, ic++); printf("%c", 186); }
	for (ic = 6; ic <= 22;) { gotoxy(65, ic++); printf("%c", 186); }
	gotoxy(13, 22); printf("%c", 200);
	for (ic = 1; ic <= 51; ic++) printf("%c", 205);
	printf("%c\n", 188);
}

void drawlayout(int startx, int starty)
{
	int ix, iy, a, b, count = 0;
	ix = startx;
	iy = starty;
	for (a = 1; a <= 8; a++)
	{
		for (b = 1; b <= 8; b++)
		{
			if (count % 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
			else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			gotoxy(ix, iy);
			_cprintf("%c%c%c%c%c%c%c", 32, 32, 32, 32, 32, 32, 32);
			gotoxy(ix, iy = iy + 1);
			_cprintf("%c%c%c%c%c%c%c", 32, 32, 32, 32, 32, 32, 32);
			ix = ix + 6, iy = starty;
			count++;
		}
		ix = startx;
		starty = starty + 2;
		iy = starty;
		count++;
	}
}

void fillnumbers(int(*arr)[8])
{
	int ix = 17, iy = 7, a, b, count = 0;
	for (a = 0; a < 8; a++)
	{
		for (b = 0; b < 8; b++)
		{
			if (count % 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			gotoxy(ix, iy);
			if (arr[a][b] == 0) _cprintf("  ");
			if (arr[a][b] == -1) _cprintf(" Q ");
			if (arr[a][b] > 0) _cprintf("  ");
			ix = ix + 6;
			count++;
		}
		ix = 17; iy = iy + 2;
		count++;
	}
}

void setqueen(int(*board)[8], int row, int col)
{
	int i, j;
	board[row][col] = -1;
	for (i = col + 1; i < 8; i++) board[row][i] += 1;
	for (i = col - 1; i >= 0; i--) board[row][i] += 1;
	for (i = row + 1; i < 8; i++) board[i][col] += 1;
	for (i = row - 1; i >= 0; i--) board[i][col] += 1;
	for (i = col + 1, j = row + 1; i < 8 && j < 8; i++, j++) board[j][i] += 1;
	for (i = col + 1, j = row - 1; i < 8 && j >= 0; i++, j--) board[j][i] += 1;
	for (i = col - 1, j = row - 1; i >= 0 && j >= 0; i--, j--) board[j][i] += 1;
	for (i = col - 1, j = row + 1; i >= 0 && j < 8; i--, j++) board[j][i] += 1;
}

void removequeen(int(*board)[8], int row, int col)
{
	int i, j;
	board[row][col] = 0;
	for (i = col + 1; i < 8; i++) board[row][i] -= 1;
	for (i = col - 1; i >= 0; i--) board[row][i] -= 1;
	for (i = row + 1; i < 8; i++) board[i][col] -= 1;
	for (i = row - 1; i >= 0; i--) board[i][col] -= 1;
	for (i = col + 1, j = row + 1; i < 8 && j < 8; i++, j++) board[j][i] -= 1;
	for (i = col + 1, j = row - 1; i < 8 && j >= 0; i++, j--) board[j][i] -= 1;
	for (i = col - 1, j = row - 1; i >= 0 && j >= 0; i--, j--) board[j][i] -= 1;
	for (i = col - 1, j = row + 1; i >= 0 && j < 8; i--, j++) board[j][i] -= 1;
}

int moves = 0;

int findsetup(int(*board)[8], int startcol)
{
	int row = 0, success = 0, placed = 0;
	if (startcol == 8)
	{
		moves++;
		fillnumbers(board);
		gotoxy(1, 24);
		printf("Move Number : %d", moves);
		_getch();
		return 0;
	}
	while (success == 0)
	{
		if (placed == 1)
		{
			removequeen(board, row, startcol);
			row++;
		}
		if (row != 8) while (board[row][startcol] > 0 && row < 8) row++;
		if (row != 8)
		{
			setqueen(board, row, startcol);
			if (placed == 0) placed = 1;
			success = findsetup(board, startcol + 1);
		}
		else return 0;
	}
}

int main()
{
	int board[8][8] = {
			 {0,0,0,0,0,0,0,0},
			 {0,0,0,0,0,0,0,0},
			 {0,0,0,0,0,0,0,0},
			 {0,0,0,0,0,0,0,0},
			 {0,0,0,0,0,0,0,0},
			 {0,0,0,0,0,0,0,0},
			 {0,0,0,0,0,0,0,0},
			 {0,0,0,0,0,0,0,0}
	};
	system("cls");
	printf("*******************************************************************************\n");
	printf("                          THE EIGHT QUEENS' DEMO\n");
	printf("*******************************************************************************");
	drawbox();
	drawlayout(15, 6);
	findsetup(board, 0);
}