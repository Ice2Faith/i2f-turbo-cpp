/** Name: SudokuCoreTest*/
#include<iostream>
#include"Sudoku.h"
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#define BLOCK_SIZE 50
long begintime;
using namespace std;
void DrawMap(Sudoku& mygame);
void GetSetInfo(int *rindex, int *cindex, int *number);
int main(int argc, char * argv[])
{
	HWND hwnd = initgraph(9*BLOCK_SIZE,9*BLOCK_SIZE);
	setbkcolor(RGB(200,200,200));
	setbkmode(TRANSPARENT);
	settextcolor(RGB(0,0,0));
	cleardevice();
	while (1)
	{
		Sudoku mygame;
		begintime = time(NULL);
		while (1)
		{
			DrawMap(mygame);
			int rindex = 0, cindex = 0, number = 0;
			//cin >> rindex >> cindex >> number;
			GetSetInfo(&rindex, &cindex, &number);
			mygame.SetMapAtValue(rindex,cindex,number);
			if (mygame.GetSuccessCount() == mygame.GetSumCount())
				break;
		}
		if (MessageBox(hwnd,"游戏通关！！\n是否再来一局？","数独：游戏提示",MB_YESNO) == IDNO)
			break;
	}
	
	return 0;
}
void GetSetInfo(int *rindex, int *cindex, int *number)
{
	while (1)
	{
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			*rindex = msg.y / BLOCK_SIZE;
			*cindex = msg.x / BLOCK_SIZE;
			setfillcolor(RGB(0, 255, 255));
			solidcircle((*cindex)*BLOCK_SIZE + BLOCK_SIZE / 2, (*rindex)*BLOCK_SIZE + BLOCK_SIZE / 2, BLOCK_SIZE / 2);
			char sel = 0;
			sel = getch();
			if (sel > '0'&&sel <= '9')
			{
				*number = (int)(sel - '0');
				break;
			}

		}
	}
}
void DrawMap(Sudoku& mygame)
{
	BeginBatchDraw();
	cleardevice();
	settextcolor(RGB(0, 0, 0));
	char temp[200] = { 0 };
	system("cls");
	cout <<"Tips : "<< mygame.GetTipsCount()<<"  Success : "<<mygame.GetSuccessCount() <<"  Empty : "<<mygame.GetEmptyCount()<<"  All : "<<mygame.GetSumCount()<< endl;
	for (int i = 0; i < mygame.GetLine(); i++)
	{
		for (int j = 0; j < mygame.GetCol(); j++)
		{
			cout.width(2);
			int elem = mygame.MapAt(i, j);
			cout << elem;
			if (elem == 0)
			{
				setfillcolor(RGB(255,255,255));
			}
			else
			{
				if (mygame.MaskAt(i, j))
				{
					setfillcolor(RGB(255, 255, 0));
				}
				else
				{
					setfillcolor(RGB(0,255,255));
				}
			}
			solidcircle(j*BLOCK_SIZE + BLOCK_SIZE / 2, i*BLOCK_SIZE + BLOCK_SIZE / 2, BLOCK_SIZE / 2);
			if (elem != 0)
			{
				sprintf(temp,"%d\0",elem);
				outtextxy(j*BLOCK_SIZE + BLOCK_SIZE / 2, i*BLOCK_SIZE + BLOCK_SIZE / 2,temp);
			}
			
		}
		cout << endl;
	}
	setlinecolor(RGB(255,0,0));
	for (int i = 0; i < mygame.GetBlockLine(); i++)
	{
		for (int j = 0; j < mygame.GetBlockCol(); j++)
		{
			rectangle(j*BLOCK_SIZE*mygame.GetBlockCol(), i*BLOCK_SIZE*mygame.GetBlockLine(), (j + 1)*BLOCK_SIZE*mygame.GetBlockCol()-1, (i + 1)*BLOCK_SIZE*mygame.GetBlockLine()-1);
		}
	}
	settextcolor(RGB(0, 0, 255));
	long nowtime = time(NULL);
	sprintf(temp,"Success : %d / %d : %d Time : %d\0",mygame.GetSuccessCount(),mygame.GetSumCount(),mygame.GetEmptyCount(),nowtime-begintime);
	outtextxy(0,0,temp);
	EndBatchDraw();
}