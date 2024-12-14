/** Name: SnackCoreTest*/
#include"Snack.h"
#include<iostream>
#include<graphics.h>
#include<conio.h>
int MAP_LINE = 30;
int MAP_COL = 40;
int BLOCK_SIZE = 25;
int screenWidth = 480;
int screenHeight = 320;
int FONT_HEIGHT = 5;
int USED_TIME = 0;
using namespace std;
void DrawMap(Snack& mygame);
MOV_DIRECT GetMove();
int main(int argc, char * argv[])
{
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	HWND hwnd = initgraph(BLOCK_SIZE*MAP_COL, BLOCK_SIZE*MAP_LINE);
	setbkcolor(RGB(200,200,200));
	setbkmode(TRANSPARENT);
	settextcolor(RGB(120,220,120));
	LOGFONT font = { 0 };
	gettextstyle(&font);
	FONT_HEIGHT = font.lfHeight;
	cleardevice();
	if (MessageBox(hwnd, "是否默认大小？", "游戏设置：大小设置", MB_YESNO) == IDNO)
	{
		char read[20] = { 0 };
		InputBox(read,20-1,"请输入大小（长*宽）：","大小设置");
		int line = 0, col = 0;
		if (sscanf(read, "%d*%d", &line, &col) == 2)
		{
			MAP_LINE = line;
			MAP_COL = col;
			if (line<25){
				BLOCK_SIZE = (25 - line) / 5 * 10 + 25;
			}
				
			int windowWidth = BLOCK_SIZE*MAP_LINE;
			int windowHeight = BLOCK_SIZE*MAP_COL;
			if (windowHeight>screenHeight || windowWidth > screenWidth)
			{
				double rate = windowWidth*1.0 / windowHeight;
				if (windowWidth>screenWidth)
				{
					double srate = windowWidth*1.0 / screenWidth;
					windowWidth = screenWidth;
					windowHeight = windowWidth / rate;
					BLOCK_SIZE /= srate;
				}
				if (windowHeight > screenHeight)
				{
					double srate = windowHeight*1.0 / screenHeight;
					windowHeight = screenHeight;
					windowWidth = windowHeight*rate;
					BLOCK_SIZE /= srate;
				}
				windowWidth = BLOCK_SIZE*MAP_LINE;
				windowHeight = BLOCK_SIZE*MAP_COL;

				screenHeight *= 0.95;
				screenWidth *= 0.95;
				double hrate = windowWidth*1.0 / screenWidth;
				double vrate = windowHeight*1.0 / screenHeight;
				int hh = windowHeight / hrate;

				if (hh < screenHeight)
				{
					BLOCK_SIZE /= hrate;
					windowWidth = BLOCK_SIZE*MAP_LINE;
					windowHeight = BLOCK_SIZE*MAP_COL;
				}
				else
				{
					BLOCK_SIZE /= vrate;
					windowWidth = BLOCK_SIZE*MAP_LINE;
					windowHeight = BLOCK_SIZE*MAP_COL;
				}
			}
			

			hwnd = initgraph(windowWidth, windowHeight);
			setbkcolor(RGB(220, 230, 220));
			setbkmode(TRANSPARENT);
			settextcolor(RGB(120, 220, 120));
			cleardevice();
		}

	}
	bool Autoplay = true;
	bool Wallopen = false;
	if (MessageBox(hwnd, "是否玩家玩？", "游戏设置：玩家设置", MB_YESNO) == IDYES)
		Autoplay = false;
	else
		Autoplay = true;
	if (MessageBox(hwnd, "是否去除边界？", "游戏设置：边界设置", MB_YESNO) == IDYES)
		Wallopen = false;
	else
		Wallopen = true;

	int autoRefreshTime = 10;
	int autoSingleStep = 1;
	int avgLC = (MAP_COL + MAP_LINE) / 2;
	if ((MAP_COL >= 400 || MAP_LINE >= 400) && avgLC >= 320)
	{
		autoRefreshTime = 0;
		autoSingleStep = 8;
	}
	else if ((MAP_COL >= 300 || MAP_LINE >= 300) && avgLC >= 250)
	{
			autoRefreshTime = 0;
			autoSingleStep = 5;
	}
	else if ((MAP_COL >= 200 || MAP_LINE >= 200) && avgLC >= 180)
	{
		autoRefreshTime = 2;
		autoSingleStep = 3;
	}
	else if ((MAP_COL >= 100 || MAP_LINE >= 100) && avgLC >= 80)
	{
		autoRefreshTime = 5;
		autoSingleStep = 2;
	}
	else if ((MAP_COL >= 50 || MAP_LINE >= 50) && avgLC >= 45)
	{
		autoRefreshTime = 8;
	}
	else if ((MAP_COL >= 20 || MAP_LINE >= 20) && avgLC >= 15)
		autoRefreshTime = 10;
	else
		autoRefreshTime = 15;

	long beginTime = GetTickCount();
	int isDraw = 0;
	while (1)
	{
		Snack mygame(MAP_LINE, MAP_COL, Wallopen);
		while (1)
		{
			USED_TIME = (GetTickCount() - beginTime);
			if (isDraw==0)
				DrawMap(mygame);

			if (!Autoplay)
			{
				MOV_DIRECT direct = GetMove();
				if (!mygame.Run(direct))
					break;
				Sleep(80);
			}
			else
			{
				if (autoRefreshTime <= 5)
				{
					int slen = mygame.GetSnackLen()*0.3;
					if (slen<avgLC*0.3 && slen > autoSingleStep)
						autoSingleStep = slen;
				}
				isDraw = (isDraw + 1) % autoSingleStep;

				if (!mygame.AutoRun())
					break;
				if (autoRefreshTime != 0)
					Sleep(autoRefreshTime);
			}
		}
		if (MessageBox(hwnd, "是否重玩？", "游戏提示：游戏结束", MB_YESNO) == IDNO)
			break;
	}
	return 0;
}
MOV_DIRECT GetMove()
{
	char move = '\0';
	if (kbhit())
	{
		move = getch();
		if (move == 'w' || move == '8' || move == 'W')
			return MOV_UP;
		if (move == 's' || move == '5' || move == 'S')
			return MOV_DOWN;
		if (move == 'a' || move == '4' || move == 'A')
			return MOV_LEFT;
		if (move == 'd' || move == '6' || move == 'D')
			return MOV_RIGHT;
	}
	else
		return MOV_NULL;

}
void DrawMap(Snack& mygame)
{
	BeginBatchDraw();
	cleardevice();
	for (int i = 0; i < mygame.GetLines(); i++)
	{
		for (int j = 0; j < mygame.GetCols(); j++)
		{
			int elem = mygame.MapAt(i, j);
			cout.width(2);
			if (elem == ELEM_VECANT)
			{
				setfillcolor(RGB(255,255,255));
			}
			else if (elem == ELEM_GIFT)
			{
				if(mygame.IsNormalGift())
					setfillcolor(RGB(255, 180, 120));
				else
					setfillcolor(RGB(255, 120, 0));
			}
			else if (elem == ELEM_SNACK)
			{
				setfillcolor(RGB(0, 255, 0));
			}
			else if (elem == ELEM_SNACK_HEAD)
			{
				setfillcolor(RGB(255, 0, 0));
			}
			else if (elem == ELEM_SNACK_TAIL)
			{
				setfillcolor(RGB(100, 100, 100));
			}
			else if (elem==ELEM_WALL)
			{
				setfillcolor(RGB(0,0,0));
			}
			solidcircle(i*BLOCK_SIZE + BLOCK_SIZE / 2, j*BLOCK_SIZE + BLOCK_SIZE / 2, BLOCK_SIZE/2);
		}
	}
	char temp[20] = { 0 };
	sprintf(temp,"Score : %d\0",mygame.GetScore());
	outtextxy(0,FONT_HEIGHT*1,temp);

	sprintf(temp, "Length : %d\0", mygame.GetSnackLen());
	outtextxy(0, 2*FONT_HEIGHT, temp);

	sprintf(temp, "Time : %d\0", USED_TIME/1000);
	outtextxy(0, 3 * FONT_HEIGHT, temp);

	EndBatchDraw();
}