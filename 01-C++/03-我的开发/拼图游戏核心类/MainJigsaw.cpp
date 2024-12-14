/** Name: Jigsaw Core Test*/
#include<iostream>
#include<graphics.h>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include"Jigsaw.h"
#define BLOCK_SIZE 50
#define SIZE_COL 12
#define SIZE_ROW 15
using namespace std;
void DisplayMap(Jigsaw& mygame);
int GetMove();
using namespace std;

int main(int argc, char * argv[])
{
	HWND hwnd = initgraph(SIZE_COL*BLOCK_SIZE, SIZE_ROW*BLOCK_SIZE);
	setbkmode(TRANSPARENT);
	setbkcolor(RGB(180, 180, 180));
	settextcolor(RGB(0, 180, 80));
	cleardevice();
	while (1)
	{
		Jigsaw mygame(SIZE_ROW, SIZE_COL);
		while (1)
		{
			DisplayMap(mygame);
			/*int mov = GetMove();
			cout << mov << endl;
			if (!mygame.Run(mov))
				break;*/
			if (!mygame.AutoRun())
				break;
			Sleep(200);
		}
		DisplayMap(mygame);
		if (MessageBox(hwnd, "游戏结束，是否重玩？", "Tips", MB_YESNO) == IDNO)
			break;
	}
	return 0;
}
int GetMove()
{
	char move = '\0';
	move = getch();
	if (move == 'w' || move == '8' || move == 'W')
		return MOV_UP;
	if (move == 's' || move == '5' || move == 'S')
		return MOV_DOWN;
	if (move == 'a' || move == '4' || move == 'A')
		return MOV_LEFT;
	if (move == 'd' || move == '6' || move == 'D')
		return MOV_RIGHT;
	if (move == '*')
		return MOV_NULL;
	return 0;
}
void DisplayMap(Jigsaw& mygame)
{
	BeginBatchDraw();
	cleardevice();
	char temp[20] = { 0 };
	system("cls");
	for (int i = 0; i<mygame.GetLines(); i++)
	{
		for (int j = 0; j<mygame.GetCols(); j++)
		{
			cout.width(4);
			cout << mygame.MapAt(i, j);
			int size = mygame.MapAt(i, j);
			int px = size%mygame.GetCols(), py = size/mygame.GetCols();
			sprintf(temp, "%d\0", size);
			if (size == mygame.GetMaxBlock())
			{
				setfillcolor(RGB(0, 0, 0));
				solidcircle(j*BLOCK_SIZE + BLOCK_SIZE / 2, i*BLOCK_SIZE + BLOCK_SIZE / 2, BLOCK_SIZE / 2);
			}
			else
			{
				setfillcolor(RGB(50, 220-px*15, 180-py*10));
				solidcircle(j*BLOCK_SIZE + BLOCK_SIZE / 2, i*BLOCK_SIZE + BLOCK_SIZE / 2, BLOCK_SIZE / 2);
			}
			outtextxy(j*BLOCK_SIZE, i*BLOCK_SIZE, temp);
		}
		printf("\n");
	}
	cout << "-------" << endl;
	sprintf(temp, "Step : %d\0", mygame.GetStep());
	outtextxy(0, 1 * BLOCK_SIZE / 3, temp);

	EndBatchDraw();
}