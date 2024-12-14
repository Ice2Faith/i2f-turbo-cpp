/** Name: SweepCoreTest*/
#include<iostream>
#include"Sweep.h"
#include<graphics.h>
#include<Windows.h>
int SIZE_LINE = 10;
int SIZE_COL = 15;
int BLOCK_SIZE = 40;
using namespace std;
void DrawMap(Sweep& mygame);
void GetClick(int *rindex, int * cindex,bool * falg);
int main(int argc, char * argv[])
{
	HWND hwnd = initgraph(SIZE_COL*BLOCK_SIZE,SIZE_LINE*BLOCK_SIZE);
	setbkcolor(RGB(200,200,200));
	setbkmode(TRANSPARENT);
	cleardevice();
	while (1)
	{
		Sweep mygame(SIZE_LINE,SIZE_COL);
		while (1)
		{
			DrawMap(mygame);
			int rindex = 0, cindex = 0;
			bool flag = false;
			//cin >> rindex >> cindex;
			GetClick(&rindex,&cindex,&flag);
			cout << rindex<<"-" << cindex;
			if(!mygame.Click(rindex,cindex,flag))
			{
				DrawMap(mygame);
				break;
			}
			//system("pause");
		}
		char temp[40] = { 0 };
		int score = mygame.GetScore();
		int boom = mygame.GetBoomCount();
		if (score==boom)
			sprintf(temp, "恭喜通关！！\n本局得分：%d/%d\n是否重玩？", score, boom);
		else
			sprintf(temp,"本局得分：%d/%d\n是否重玩？",score,boom);
		if (MessageBox(hwnd, temp, "游戏提示：游戏结束", MB_YESNO) == IDNO)
			break;
	}
	return 0;
}
void GetClick(int *rindex, int * cindex,bool * flag)
{
	MOUSEMSG msg = { 0 };
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			*rindex = msg.y / BLOCK_SIZE;
			*cindex = msg.x / BLOCK_SIZE;
			*flag = false;
			break;
		}
		if (msg.uMsg == WM_RBUTTONDOWN)
		{
			*rindex = msg.y / BLOCK_SIZE;
			*cindex = msg.x / BLOCK_SIZE;
			*flag = true;
			break;
		}
	}
}
void DrawMap(Sweep& mygame)
{
	BeginBatchDraw();
	cleardevice();
	char temp[20] = { 0 };
	system("cls");
	cout.width(4);
	cout << " ";
	for (int j = 0; j < mygame.GetCols(); j++)
	{
		cout.width(4);
		cout << j;
	}
	cout << endl;
	for (int i = 0; i < mygame.GetLines(); i++)
	{
		cout.width(4);
		cout << i;
		for (int j = 0; j < mygame.GetCols(); j++)
		{
			cout.width(4);
			int elem = mygame.MapAt(i, j);
			cout << elem;
			switch (mygame.GetElemType(elem))
			{
			case ELEM_NULL:
			{
							  setfillcolor(RGB(255,255,255));
							  break;
			}
			case ELEM_MASK:
			{
							  setfillcolor(RGB(0, 255, 255));
							  break;
			}
			case ELEM_BOOM:
			{
							  setfillcolor(RGB(255, 0, 0));
							  break;
			}
			case ELEM_NUMBER:
			{
								setfillcolor(RGB(255, 255, 255));
								break;
			}
			case ELEM_FLAG_MASK:
			{
								setfillcolor(RGB(0, 255, 0));
								break;
			}
			case ELEM_FLAG_BOOM:
			{
								   setfillcolor(RGB(255, 255, 0));
								   break;
			}
			}
			solidcircle(j*BLOCK_SIZE+BLOCK_SIZE/2,i*BLOCK_SIZE+BLOCK_SIZE/2,BLOCK_SIZE/2);
			if (mygame.GetElemType(elem) == ELEM_NUMBER)
			{
				
				sprintf(temp,"%d\0",elem);
				settextcolor(RGB(0, elem*30, 0));
				outtextxy(j*BLOCK_SIZE + BLOCK_SIZE / 2, i*BLOCK_SIZE + BLOCK_SIZE / 2, temp);
			}
		}
		cout << endl;
	}
	settextcolor(RGB(0,0,0));
	sprintf(temp, "剩余：%d\0", mygame.GetFlagCount());
	outtextxy(0,0,temp);
	EndBatchDraw();
}