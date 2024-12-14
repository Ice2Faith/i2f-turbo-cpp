#include<graphics.h> 
#include<conio.h>
#include<windows.h>
#include<stdio.h>
#include<time.h>
typedef struct
{
	int red;
	int green;
	int blue;
}RGBColor;
RGBColor BrickC1, BrickC2, CircleC, BarC; //inner use
int GX; //横向
int GY; //纵向
int COLS;
int LINES;
int SleepTime = 0;
#define MAXCOLS 256 //列数
#define MAXLINES 256 //行数
int Brick[MAXLINES][MAXCOLS];
int BriWid, BriHei; //brick info
int CircleX, CircleY, CircleR;
int CirMovX, CirMovY; //circle info
int BarX, BarY, BarWid, BarHei; //bar info
int GameState; //0 null 1 success -1 default

int score = 0;

RGBColor tBrickC1, tBrickC2, tCircleC, tBarC; //outer set
void SetConsoleInitial();
void InitState();
void DrawGraph();
void MoveBar();
void MoveCircle();
void MoveCheck();
bool IsDead();
bool IsWin();
void OutHelp();
wchar_t OutTips[200];
void RandDead()
{
	int x, y;
	x = rand() % LINES;
	y = rand() % COLS;
	Brick[x][y] = 1;
}
int main()
{
	SetConsoleInitial();
	srand((unsigned)time(NULL));
	initgraph(GX, GY);
	while (true)
	{

		InitState();
		BeginBatchDraw();
		while (true)
		{

			DrawGraph();
			_itow_s(score, OutTips, 10);
			outtextxy(GX / 2 - 20, GY / 2 + 20, L"Score:");
			outtextxy(GX / 2 - 5, GY / 2 + 40, OutTips);
			MoveBar();
			MoveCircle();
			MoveCheck();
			FlushBatchDraw();
			if (IsWin())
			{
				GameState = 1;
				break;
			}

			if (IsDead())
			{
				GameState = -1;
				break;
			}
			Sleep(SleepTime);

		}
		DrawGraph();
		EndBatchDraw();
		if (GameState == 1)
			outtextxy(GX / 2 - 65, GY / 2 - 40, L"Win!!!");
		if (GameState == -1)
			outtextxy(GX / 2 - 65, GY / 2 - 40, L"Failure!!!");
		outtextxy(GX / 2 - 65, GY / 2 - 20, L"Press * continue,ESC exit");
		while (_getch() != '*')
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
				exit(0);
		}
		cleardevice();
		outtextxy(GX / 2 - 65, GY / 2 - 40, L"Press * start new game, 0/ESC exit");
		outtextxy(GX / 2 - 40, GY - 40, L"Ice2Faith");
		OutHelp();
		char sel = '\0';
		while (sel != '0' && sel != '*')
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
				exit(0);
			sel = _getch();
		}

		if (sel == '0')
			break;
	}
	closegraph();
	return 0;
}
void OutHelp()
{
	outtextxy(GX / 2 - 20, GY / 2 - 160, L"Help:");
	outtextxy(GX / 2 - 80, GY / 2 - 140, L"You can move bar to bounce ball.");
	outtextxy(GX / 2 - 80, GY / 2 - 120, L" Left:Left/A/4 Right:Right/D/6");
	outtextxy(GX / 2 - 80, GY / 2 - 100, L" Esc:exit");
}
void SetConsoleInitial()
{
	system("title HitBrick Dev Ice2Faith");
	system("color 0a");
	tBrickC1.red = 20;
	tBrickC1.green = 200;
	tBrickC1.blue = 120;
	tBrickC2.red = 20;
	tBrickC2.green = 120;
	tBrickC2.blue = 200;
	tCircleC.red = 200;
	tCircleC.green = 120;
	tCircleC.blue = 20;
	tBarC.red = 120;
	tBarC.green = 120;
	tBarC.blue = 20;
	GX = 480;
	GY = 720;
	COLS = 16;
	LINES = 12;
	printf("Input * use user-defined mode,ESC exit,else use default\n>/ ");
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		exit(0);
	if (_getch() != '*')
		return;
	printf("Please input window size(width-height)(px)\n>/ ");
	int wid, hei;
	while (2 != scanf_s("%d-%d", &wid, &hei));
	if (wid < 10)
		wid = 10;
	if (hei < 10)
		hei = 10;
	GX = wid;
	GY = hei;
	printf("Input * to set block size,else use default>/ ");
	if (_getch() != '*')
		return;
	printf("Please input block count(lines-cols)\n>/ ");
	int lin, col;
	while (2 != scanf_s("%d-%d", &lin, &col));
	if (lin < 2)
		lin = 2;
	if (col < 1)
		col = 1;
	if (col>256)
		col = 256;
	if (lin>256)
		lin = 256;
	LINES = lin;
	COLS = col;
	printf("Input * to set color,else use default>/ ");
	if (_getch() != '*')
		return;
	printf("Please input block color first(RGB:(red-green-blue)):\n>/ ");
	while (3 != scanf_s("%d-%d-%d", &tBrickC1.red, &tBrickC1.green, &tBrickC1.blue));
	printf("Please input block color second(RGB:(red-green-blue)):\n>/ ");
	while (3 != scanf_s("%d-%d-%d", &tBrickC2.red, &tBrickC2.green, &tBrickC2.blue));
	printf("Please input ball color (RGB:(red-green-blue)):\n>/ ");
	while (3 != scanf_s("%d-%d-%d", &tCircleC.red, &tCircleC.green, &tCircleC.blue));
	printf("Please input bar color (RGB:(red-green-blue)):\n>/ ");
	while (3 != scanf_s("%d-%d-%d", &tBarC.red, &tBarC.green, &tBarC.blue));
	if (tBrickC1.red<0 || tBrickC1.red>255)
		tBrickC1.red = 20;
	if (tBrickC1.green<0 || tBrickC1.green>255)
		tBrickC1.green = 200;
	if (tBrickC1.blue<0 || tBrickC1.blue>255)
		tBrickC1.blue = 120;
	if (tBrickC2.red<0 || tBrickC2.red>255)
		tBrickC2.red = 20;
	if (tBrickC2.green<0 || tBrickC2.green>255)
		tBrickC2.green = 120;
	if (tBrickC2.blue<0 || tBrickC2.blue>255)
		tBrickC2.blue = 200;
	if (tCircleC.red<0 || tCircleC.red>255)
		tCircleC.red = 200;
	if (tCircleC.green<0 || tCircleC.green>255)
		tCircleC.green = 120;
	if (tCircleC.blue<0 || tCircleC.blue>255)
		tCircleC.blue = 20;
	if (tBarC.red<0 || tBarC.red>255)
		tBarC.red = 120;
	if (tBarC.green<0 || tBarC.green>255)
		tBarC.green = 120;
	if (tBarC.blue<0 || tBarC.blue>255)
		tBarC.blue = 20;
}
bool IsDead()
{
	if (CircleY + CircleR > BarY)
		return true;
	return false;
}
void MoveCheck()
{
	if (CircleY + CircleR >= BarY)
	{
		if (CircleX >= BarX && CircleX <= BarX + BarWid)
			CirMovY *= -1;
		return;
	}
	bool flag = false;
	if (CircleY - CircleR <= LINES*BriHei)
	{
		for (int i = 0; i < LINES; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				if (Brick[i][j] == 0)
				{
					if (CircleY - CircleR <= i*BriHei + BriHei && CircleY - CircleR >= i*BriHei && CircleX - CircleR >= j*BriWid && CircleX - CircleR <= j*BriWid + BriWid)
					{
						Brick[i][j] = 1;
						CirMovY *= -1;
						flag = true;
						score++;
						break;
					}

				}
			}
			if (flag)
				break;
		}
	}
}
bool IsWin()
{
	for (int i = 0; i < LINES; i++)
	for (int j = 0; j < COLS; j++)
	if (Brick[i][j] == 0)
		return false;
	return true;
}
void MoveCircle()
{
	if (CircleX + CirMovX <= CircleR || CircleX + CirMovX >= GX - CircleR)
		CirMovX *= -1;
	if (CircleY + CirMovY <= CircleR || CircleY + CirMovY >= GY - CircleR)
		CirMovY *= -1;
	setfillcolor(BLACK);
	solidcircle(CircleX, CircleY, CircleR);
	CircleX += CirMovX;
	CircleY += CirMovY;
	setfillcolor(RGB(200, 120, 20));
	solidcircle(CircleX, CircleY, CircleR);
}
void MoveBar()
{
	int step = GX * 1 / 160;
	int efficclick = 0;
	int c = 0;
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		exit(0);
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState(VK_NUMPAD6) & 0x8000))
	{
		c |= 1;
		efficclick = 1;
	}

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState(VK_NUMPAD4) & 0x8000))
	{
		c |= 2;
		efficclick = 1;
	}
	if (efficclick == 0)
		return;
	setfillcolor(BLACK);
	solidrectangle(BarX, BarY, BarX + BarWid, BarY + BarHei);
	if (c & 1)
	{
		BarX += step;
	}
	if (c & 2)
	{
		BarX -= step;
	}
	if (BarX < 0)
		BarX = 0;
	if (BarX>GX - BarWid)
		BarX = GX - BarWid;
	setfillcolor(RGB(120, 120, 20));
	solidrectangle(BarX, BarY, BarX + BarWid, BarY + BarHei);

}
void InitState()
{
	for (int i = 0; i < LINES; i++)
	for (int j = 0; j < COLS; j++)
		Brick[i][j] = 0;
	BriWid = GX / COLS;
	BriHei = GY / LINES * 35 / 100;
	CircleR = GX * 2 / 100;
	BarWid = GX * 20 / 100;
	BarHei = GY * 2 / 100;
	int space = rand() % (GX / 2);
	space -= space / 2;
	CircleX = GX / 2 + space;
	CircleY = GY - BarHei - CircleR;
	BarX = GX / 2 - BarWid / 2;
	BarY = GY - BarHei;
	if (rand() % 10 <= 3)
		CirMovX = 1;
	else
		CirMovX = -1;
	CirMovY = -1;
	GameState = 0;
	if (GY<100)
		SleepTime = 30 - GY / 10;
	else if (GY < 400)
		SleepTime = 10 - GY / 100;
	else if (GY<800)
		SleepTime = 5 - GY / 200;
	else if (GY < 1200)
		SleepTime = 3 - GY / 400;
	else
		SleepTime = 0;
	score = 0;
	BrickC1.red = tBrickC1.red;
	BrickC1.green = tBrickC1.green;
	BrickC1.blue = tBrickC1.blue;

	BrickC2.red = tBrickC2.red;
	BrickC2.green = tBrickC2.green;
	BrickC2.blue = tBrickC2.blue;

	CircleC.red = tCircleC.red;
	CircleC.green = tCircleC.green;
	CircleC.blue = tCircleC.blue;

	BarC.red = tBarC.red;
	BarC.green = tBarC.green;
	BarC.blue = tBarC.blue;
}
void DrawGraph()
{
	cleardevice();
	for (int i = 0; i < LINES; i++)
	for (int j = 0; j < COLS; j++)
	if (Brick[i][j] == 0)
	{
		if ((i + j) % 2 == 0)
		{
			setfillcolor(RGB(BrickC1.red, BrickC1.green, BrickC1.blue));
		}
		else
		{
			setfillcolor(RGB(BrickC2.red, BrickC2.green, BrickC2.blue));
		}
		solidrectangle(j*BriWid, i*BriHei, j*BriWid + BriWid, i*BriHei + BriHei);
	}
	else
	{
		setfillcolor(BLACK);
		solidrectangle(j*BriWid, i*BriHei, j*BriWid + BriWid, i*BriHei + BriHei);
	}
	setfillcolor(RGB(CircleC.red, CircleC.green, CircleC.blue));
	solidcircle(CircleX, CircleY, CircleR);
	setfillcolor(RGB(BarC.red, BarC.green, BarC.blue));
	solidrectangle(BarX, BarY, BarX + BarWid, BarY + BarHei);

}