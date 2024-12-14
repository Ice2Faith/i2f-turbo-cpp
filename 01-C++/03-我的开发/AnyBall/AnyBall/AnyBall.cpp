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
typedef struct
{
	int x;
	int y;
	int r;
	int movx;
	int movy;
	RGBColor color;
} Ball;


int GX = 1280;
int GY = 720;
int MinG;
RGBColor bgcolor = {0,0,0};
int BallCount = GX*GY*1/10000;
int HollowBallCount = GX*GY * 1 / 20000;
int speed = (GX / 10)*(GY / 10);
Ball * SecondaryBall;
Ball * HollowSecondaryBall;
Ball MainBall;

POINT Mouse;
MOUSEMSG msg;

void InitialEnvironment();
void DrawAll();
void MoveBall();
void MoveMainBall();
void CrackCheck();
void GUIMain();
void ConsoleInitial();
int main()
{

	ConsoleInitial();
	GUIMain();
	return 0;
}
void ConsoleInitial()
{
	MainBall.color.red = 220;
	MainBall.color.green = 40;
	MainBall.color.blue = 60;
	MinG = (GX >= GY ? GY : GX);
	bgcolor = { 0, 0, 0 };
	BallCount = GX*GY * 1 / 10000;
	HollowBallCount = GX*GY * 1 / 20000;
	speed = (GX / 10)*(GY / 10);
	printf("Tips: You can exit by click ESC every time.\n");
	printf("Input * into user-defined mode,else use default\n>/ ");
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		exit(0);
	if (_getch() != '*')
		return;

	printf("Input * into set window size,else use default\n>/ ");
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		exit(0);
	if (_getch() == '*')
	{
		printf("Please input window size(width-height(px))\n>/ ");
		while (2 != scanf_s("%d-%d", &GX, &GY));
		if (GX < 10)
			GX = 10;
		if (GY < 10)
			GY = 10;
		MinG = (GX >= GY ? GY : GX);
		speed = (GX / 10)*(GY / 10);
	}

	printf("Input * into set ball number,else use default\n>/ ");
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		exit(0);
	if (_getch() == '*')
	{
		printf("please input ball number(fill-hollow)\n>/ ");
		while (2 != scanf_s("%d-%d", &BallCount, &HollowBallCount));
		if (BallCount < 0)
			BallCount = 0;
		if (HollowBallCount < 0)
			HollowBallCount = 0;
	}

	printf("Input * into set background color,else use default\n>/ ");
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		exit(0);
	if (_getch() == '*')
	{
		printf("please input background color(RGB)(red-green-blue)\n>/ ");
		while (3 != scanf_s("%d-%d-%d", &bgcolor.red, &bgcolor.green, &bgcolor.blue));
		if (bgcolor.red<0 || bgcolor.red>255)
			bgcolor.red = 0;
		if (bgcolor.green<0 || bgcolor.green>255)
			bgcolor.green = 0;
		if (bgcolor.blue<0 || bgcolor.blue>255)
			bgcolor.blue = 0;
	}

	printf("Input * into set main ball color,else use default\n>/ ");
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		exit(0);
	if (_getch() == '*')
	{
		printf("please input main ball color(RGB)(red-green-blue)\n>/ ");
		while (3 != scanf_s("%d-%d-%d", &MainBall.color.red, &MainBall.color.green, &MainBall.color.blue));
		if (MainBall.color.red<0 || MainBall.color.red>255)
			MainBall.color.red = 0;
		if (MainBall.color.green<0 || MainBall.color.green>255)
			MainBall.color.green = 0;
		if (MainBall.color.blue<0 || MainBall.color.blue>255)
			MainBall.color.blue = 0;
	}
}
void GUIMain()
{
	initgraph(GX, GY);
	InitialEnvironment();
	BeginBatchDraw();
	DrawAll();
	while (true)
	{
		MoveBall();
		MoveMainBall();
		CrackCheck();
		FlushBatchDraw();
		if (speed<=8*12)
			Sleep(30);
		else
		if (speed<=16*24)
			Sleep(20);
		else
		if (speed<=32*48)
			Sleep(10);
		else
		if (speed<64*96)
			Sleep(2);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break;
	}
	EndBatchDraw();
	closegraph();
}
void CrackCheck()
{
	for (int i = 0; i < BallCount; i++)
	{
		if (SecondaryBall[i].x + SecondaryBall[i].r >= MainBall.x - MainBall.r && SecondaryBall[i].x - SecondaryBall[i].r <= MainBall.x + MainBall.r)
			SecondaryBall[i].movx *= -1;
		if (SecondaryBall[i].y + SecondaryBall[i].r >= MainBall.y - MainBall.r && SecondaryBall[i].y - SecondaryBall[i].r <= MainBall.y + MainBall.r)
			SecondaryBall[i].movy *= -1;
		
	}
	for (int i = 0; i < HollowBallCount; i++)
	{
		if (HollowSecondaryBall[i].x + HollowSecondaryBall[i].r >= MainBall.x - MainBall.r && HollowSecondaryBall[i].x - HollowSecondaryBall[i].r <= MainBall.x + MainBall.r)
			HollowSecondaryBall[i].movx *= -1;
		if (HollowSecondaryBall[i].y + HollowSecondaryBall[i].r >= MainBall.y - MainBall.r && HollowSecondaryBall[i].y - HollowSecondaryBall[i].r <= MainBall.y + MainBall.r)
			HollowSecondaryBall[i].movy *= -1;
		
	}
}
void InitialEnvironment()
{
	srand((unsigned)time(NULL));
	setfillcolor(RGB(bgcolor.red, bgcolor.green, bgcolor.blue));
	solidrectangle(0, 0, GX, GY);
	while (MouseHit())
	{
		msg = GetMouseMsg();
		Mouse.x = msg.x;
		Mouse.y = msg.y;
	}
	MainBall.x = Mouse.x;
	MainBall.y = Mouse.y;
	MainBall.r = MinG * 5 / 100;
	
	SecondaryBall = (Ball *)malloc(sizeof(Ball)*BallCount);
	for (int i = 0; i < BallCount; i++)
	{
		SecondaryBall[i].x = rand() % GX;
		SecondaryBall[i].y = rand() % GY;
		SecondaryBall[i].movx = (rand() % 2==0?-1:1) ;
		SecondaryBall[i].movy = (rand() % 2 == 0 ? -1 : 1);
		SecondaryBall[i].r = rand() % (MinG * 2 / 100 + 2);
		SecondaryBall[i].color.red = rand() % 256;
		SecondaryBall[i].color.green = rand() % 256;
		SecondaryBall[i].color.blue = rand() % 256;
	}
	HollowSecondaryBall = (Ball *)malloc(sizeof(Ball)*HollowBallCount);
	for (int i = 0; i < HollowBallCount; i++)
	{
		HollowSecondaryBall[i].x = rand() % GX;;
		HollowSecondaryBall[i].y = rand() % GY;
		HollowSecondaryBall[i].movx = (rand() % 2 == 0 ? -1 : 1);
		HollowSecondaryBall[i].movy = (rand() % 2 == 0 ? -1 : 1);
		HollowSecondaryBall[i].r = rand() % (MinG * 2 / 100 + 2);
		HollowSecondaryBall[i].color.red = rand() % 256;
		HollowSecondaryBall[i].color.green = rand() % 256;
		HollowSecondaryBall[i].color.blue = rand() % 256;
	}
}
void DrawAll()
{
	setfillcolor(RGB(MainBall.color.red, MainBall.color.green, MainBall.color.blue));
	solidcircle(MainBall.x, MainBall.y, MainBall.r);
	for (int i = 0; i < BallCount; i++)
	{
		setfillcolor(RGB(SecondaryBall[i].color.red, SecondaryBall[i].color.green, SecondaryBall[i].color.blue));
		solidcircle(SecondaryBall[i].x, SecondaryBall[i].y, SecondaryBall[i].r);
	}
	for (int i = 0; i < HollowBallCount; i++)
	{
		setlinecolor(RGB(HollowSecondaryBall[i].color.red, HollowSecondaryBall[i].color.green, HollowSecondaryBall[i].color.blue));
		circle(HollowSecondaryBall[i].x, HollowSecondaryBall[i].y, HollowSecondaryBall[i].r);
	}
}
void MoveBall()
{
	for (int i = 0; i < BallCount; i++)
	{
		setfillcolor(RGB(bgcolor.red, bgcolor.green, bgcolor.blue));
		solidcircle(SecondaryBall[i].x, SecondaryBall[i].y, SecondaryBall[i].r);
		if (SecondaryBall[i].x + SecondaryBall[i].movx <= SecondaryBall[i].r || SecondaryBall[i].x + SecondaryBall[i].r >= GX - SecondaryBall[i].r)
			SecondaryBall[i].movx *= -1;
		if (SecondaryBall[i].y + SecondaryBall[i].movy <= SecondaryBall[i].r || SecondaryBall[i].y + SecondaryBall[i].r >= GY - SecondaryBall[i].r)
			SecondaryBall[i].movy *= -1;
		SecondaryBall[i].x += SecondaryBall[i].movx;
		SecondaryBall[i].y += SecondaryBall[i].movy;
		setfillcolor(RGB(SecondaryBall[i].color.red, SecondaryBall[i].color.green, SecondaryBall[i].color.blue));
		solidcircle(SecondaryBall[i].x, SecondaryBall[i].y, SecondaryBall[i].r);
	}
	for (int i = 0; i < HollowBallCount; i++)
	{
		setlinecolor(RGB(bgcolor.red, bgcolor.green, bgcolor.blue));
		circle(HollowSecondaryBall[i].x, HollowSecondaryBall[i].y, HollowSecondaryBall[i].r);
		if (HollowSecondaryBall[i].x + HollowSecondaryBall[i].movx <= HollowSecondaryBall[i].r || HollowSecondaryBall[i].x + HollowSecondaryBall[i].r >= GX - HollowSecondaryBall[i].r)
			HollowSecondaryBall[i].movx *= -1;
		if (HollowSecondaryBall[i].y + HollowSecondaryBall[i].movy <= HollowSecondaryBall[i].r || HollowSecondaryBall[i].y + HollowSecondaryBall[i].r >= GY - HollowSecondaryBall[i].r)
			HollowSecondaryBall[i].movy *= -1;
		HollowSecondaryBall[i].x += HollowSecondaryBall[i].movx;
		HollowSecondaryBall[i].y += HollowSecondaryBall[i].movy;
		setlinecolor(RGB(HollowSecondaryBall[i].color.red, HollowSecondaryBall[i].color.green, HollowSecondaryBall[i].color.blue));
		circle(HollowSecondaryBall[i].x, HollowSecondaryBall[i].y, HollowSecondaryBall[i].r);
	}
}
void MoveMainBall()
{

	setfillcolor(RGB(bgcolor.red,bgcolor.green,bgcolor.blue));
	solidcircle(MainBall.x, MainBall.y, MainBall.r);
	while (MouseHit())
	{
		msg = GetMouseMsg();
		MainBall.x = msg.x;
		MainBall.y = msg.y;
	}
	setfillcolor(RGB(MainBall.color.red, MainBall.color.green, MainBall.color.blue));
	solidcircle(MainBall.x, MainBall.y, MainBall.r);


}