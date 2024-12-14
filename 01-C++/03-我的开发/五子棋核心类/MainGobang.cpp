#include"Gobang.h"
#include<graphics.h>
#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace::std;
int WIDTH = 30;
int SIZELEN = 25;
void DrawMap(Gobang mygb);
void DrawWinLine(Gobang mygb);
void GetClick(int * color, int * row, int * col);
int main(int argc, char * argv[])
{
	HWND hwnd=initgraph(SIZELEN * WIDTH, SIZELEN * WIDTH);
	setbkcolor(RGB(200, 200, 200));
	while (1)
	{
		Gobang mygb(SIZELEN, SIZELEN);
		int downcolor;
		int downrow;
		int downcol;
		DrawMap(mygb);
		while (1)
		{
			GetClick(&downcolor, &downrow, &downcol);
			cout << downcolor << " " << downrow << " " << downcol << endl;
			if (mygb.BlockDown(downcolor, downrow, downcol) == true)
				DrawMap(mygb);
			if (mygb.IsWin())
			{
				DrawWinLine(mygb);
				cout << "Game Over!" << endl;
				for (int i = 0; i < 5; i++)
				{
					cout << "(" << mygb.winsort[i][0] << "," << mygb.winsort[i][1] << ")-";
				}
				cout << endl;
				break;
			}
			if (kbhit())
			{
				if (getch() == ' ')
				{
					mygb.Undo();
					DrawMap(mygb);
				}
					
			}
			Sleep(500);
		}
		if (MessageBox(hwnd, "游戏结束,再来一局？", "Tips", MB_YESNO) == IDNO)
			break;
	}
	return 0;
}
void GetClick(int * color, int * row, int * col)
{
	*color = 0;
	MOUSEMSG msg;
	char sel = 0;
	if (kbhit())
	{
		sel = getch();
		fflush(stdin);
	}
	while (MouseHit())
	{
		msg = GetMouseMsg();
		*row = msg.y / WIDTH;
		*col = msg.x / WIDTH;
		if (sel == '1' || msg.uMsg == WM_LBUTTONDOWN)
			*color = 1;
		if (sel == '2' || msg.uMsg == WM_RBUTTONDOWN)
			*color = -1;
	}
}
void DrawWinLine(Gobang mygb)
{
	BeginBatchDraw();
	for (int i = 0; i < 5; i++)
	{
		setfillcolor(RGB(0, 255, 255));
		solidcircle((mygb.winsort[i][1])*WIDTH + WIDTH / 2, (mygb.winsort[i][0]) * WIDTH + WIDTH / 2, WIDTH / 3);
	}
	EndBatchDraw();
}
void DrawMap(Gobang mygb)
{
	BeginBatchDraw();
	cleardevice();
	//system("cls");
	for (int i = 0; i < mygb.GetSizeRow(); i++)
	{
		for (int j = 0; j < mygb.GetSizeCol(); j++)
		{
			cout.width(4);
			if ((mygb.AtIndex(i, j)) == 0)
			{
				setfillcolor(RGB(180, 180, 180));
				solidcircle(j*WIDTH + WIDTH / 2, i * WIDTH + WIDTH / 2, WIDTH / 2);
				cout.width(4);
				cout << ".";
			}
			else if ((mygb.AtIndex(i, j)) == 1)
			{
				setfillcolor(RGB(255, 255, 255));
				solidcircle(j*WIDTH + WIDTH / 2, i * WIDTH + WIDTH / 2, WIDTH / 2);
				cout.width(4);
				cout << "O";
			}
			else if ((mygb.AtIndex(i, j)) == -1)
			{
				setfillcolor(RGB(0, 0, 0));
				solidcircle(j * WIDTH + WIDTH / 2, i * WIDTH + WIDTH / 2, WIDTH / 2);
				cout.width(4);
				cout << "@";
			}
		}
		cout << endl;
	}
	EndBatchDraw();
}