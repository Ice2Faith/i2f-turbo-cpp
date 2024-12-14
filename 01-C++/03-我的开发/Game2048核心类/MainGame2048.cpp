/** Name: Game2048CoreClass*/
#include<iostream>
#include<graphics.h>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include"Game2048.h"
#define BLOCK_SIZE 60
#define SIZE_COL 10
#define SIZE_ROW 10
using namespace std;
void DisplayMap(Game2048& mygame);
int GetMove();
int main(int argc, char * argv[])
{
	HWND hwnd=initgraph(SIZE_COL*BLOCK_SIZE, SIZE_ROW*BLOCK_SIZE);
	setbkmode(TRANSPARENT);
	setbkcolor(RGB(180,180,180));
	settextcolor(RGB(0,180,80));
	cleardevice();
	while (1)
	{
		Game2048 mygame(SIZE_ROW, SIZE_COL);
		while (1)
		{
			DisplayMap(mygame);
			int mov = GetMove();
			cout << mov << endl;
			if (!mygame.Run(mov))
				break;
		}
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
void DisplayMap(Game2048& mygame)
{
	BeginBatchDraw();
	cleardevice();
	char temp[20] = { 0 };
	system("cls");
	cout << mygame.GetScore() << " " << mygame.GetStep() << " " << mygame.GetUsedTime()<<" " << mygame.GetMaxNum() << endl;
	for (int i = 0; i<mygame.GetLines(); i++)
	{
		for (int j = 0; j<mygame.GetCols(); j++)
		{
			cout.width(4);
			cout << mygame.MapAt(i,j);
			if (mygame.MapAt(i, j) == 0)
			{
				setfillcolor(RGB(220,220,220));
				solidcircle(j*BLOCK_SIZE + BLOCK_SIZE / 2, i*BLOCK_SIZE + BLOCK_SIZE / 2, BLOCK_SIZE / 2);
			}
			else
			{
				int size=mygame.MapAt(i, j);
				sprintf(temp, "%d\0",size );
				size /= 2;
				setfillcolor(RGB(200, 255-size*20, 0+size*20));
				solidcircle(j*BLOCK_SIZE + BLOCK_SIZE / 2, i*BLOCK_SIZE + BLOCK_SIZE / 2, BLOCK_SIZE / 2);
				outtextxy(j*BLOCK_SIZE, i*BLOCK_SIZE,temp);
			}

		}
		printf("\n");
	}
	cout << "-------" << endl;
	sprintf(temp,"Score : %d\0",mygame.GetScore());
	outtextxy(0, 1*BLOCK_SIZE/3, temp);
	sprintf(temp, "Step : %d\0", mygame.GetStep());
	outtextxy(0, 2 * BLOCK_SIZE / 3, temp);
	sprintf(temp, "Time : %d\0", mygame.GetUsedTime());
	outtextxy(0, 3 * BLOCK_SIZE / 3, temp);
	sprintf(temp, "MAX : %d\0", mygame.GetMaxNum());
	outtextxy(0, 4 * BLOCK_SIZE / 3, temp);
	EndBatchDraw();
}