#include<graphics.h>
#include"GameKeyTool.h"
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib");
#define MAXCOUNT 30
typedef struct
{
	int r;
	bool live;
	double direct;
	Point space;
	RGB color;
}Ball;

RGB bgcolor;
Ball myBall;
int myBallLife = 100;
Ball * otherBall;
int otherLiveCount;
int WindowX;
int WindowY;
int MinWindow;

int Score;
int Level;
int Life;
int Hungry;
IMAGE bgimg;
int Round;

void initGame();
void drawView();
void moveAll();
void EatBall();
void GetMaxOBall(int * MaxOBall,int * MinOBall);
void CreateBall();
void Help();
int main(int argc, char * argv[])
{
	WindowX = GetSystemMetrics(SM_CXSCREEN) * Percent(66);
	WindowY = GetSystemMetrics(SM_CYSCREEN) * Percent(66);
	MinWindow = (WindowX > WindowY ? WindowY : WindowX);
	initgraph(WindowX, WindowY);
	while (true)
	{
		initGame();
		Help();
		while (true)
		{
			drawView();
			moveAll();
			EatBall();
			if (otherLiveCount < 5)
				CreateBall();
			Sleep(20);
			if (Life < 0)
			{
				settextcolor(RGB(255, 0, 0));
				outtextxy(WindowX / 2, WindowY / 2, "Game Over!");
				settextcolor(RGB(0, 255, 255));
				outtextxy(WindowX / 2, WindowY * 3 / 5, "Press 0  Continue");
				while (_getch() != '0');
				break;
			}
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
				break;
		}
		free(otherBall);
		outtextxy(WindowX *1/ 3, WindowY * 4 / 5, "Press Any Key Continue,ESC exit");
		_getch();
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break;
	}
	
	closegraph();
	return 0;
}
void Help()
{
	drawView();
	settextstyle(MinWindow*Percent(8), MinWindow*Percent(6), "黑体");
	settextcolor(RGB(0, 255, 255));
	setbkmode(TRANSPARENT);
	outtextxy(WindowX*Percent(30),WindowY*Percent(10),"Hungry Ball");
	settextcolor(RGB(0, 255, 0));
	settextstyle(MinWindow*Percent(4), MinWindow*Percent(3), "黑体");
	outtextxy(WindowX*Percent(20), WindowY*Percent(20), "移动鼠标控制球球移动");
	outtextxy(WindowX*Percent(20), WindowY*Percent(30), "吃掉小球球提高饥饿");
	outtextxy(WindowX*Percent(20), WindowY*Percent(40), "不要被大球球吃掉哦");
	outtextxy(WindowX*Percent(20), WindowY*Percent(50), "注意自己的生命值");
	outtextxy(WindowX*Percent(20), WindowY*Percent(60), "饥饿低于40%将会损耗生命");
	outtextxy(WindowX*Percent(20), WindowY*Percent(70), "饥饿高于95%有几率恢复生命");
	settextstyle(MinWindow*Percent(6), MinWindow*Percent(4), "黑体");
	settextcolor(RGB(0, 0, 255));
	outtextxy(WindowX * 1 / 5, WindowY * 8 / 10, "Press Any Key Start,ESC exit");
	outtextxy(WindowX * 2 / 5, WindowY * 9/10, "Ice2Faith");
	_getch();
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		exit(0);
}
void CreateBall()
{
	int lefecount = RAND((MAXCOUNT-5))/2;
	int precount = 0;
	for (int i = 0; i < MAXCOUNT; i++)
	{
		if (otherBall[i].live == false)
		{
			if (precount < lefecount)
			{
				otherBall[i].live = true;
				precount++;
				otherLiveCount++;
				if (otherBall[i].r*Percent(120) < MinWindow*Percent(30))
					otherBall[i].r = (myBall.r*(Percent(RANDBETWEEN(60, 120))));
				else
					otherBall[i].r = myBall.r*(Percent(RANDBETWEEN(60,99)));
				otherBall[i].space.x = RAND(WindowX);
				otherBall[i].space.y = RAND(WindowY);
				otherBall[i].color.red = RAND(255);
				otherBall[i].color.green = RAND(255);
				otherBall[i].color.blue = RAND(255);
				otherBall[i].direct = atan2(RANDBETWEEN(-20, 20)*1.0, RANDBETWEEN(-20, 20)*1.0);
			}
		}
		}
}
void GetMaxOBall(int * MaxOBall, int * MinOBall)
{
	int frist = 1;
	for (int i = 0; i < MAXCOUNT; i++)
	{
		if (otherBall[i].live == true)
		{
			if (frist == 1)
			{
				*MaxOBall = otherBall[i].r;
				*MinOBall = otherBall[i].r;
				frist = 0;
			}
			if (otherBall[i].r < *MinOBall)
			{
				*MinOBall = otherBall[i].r;
			}
			if (otherBall[i].r>*MaxOBall)
			{
				*MaxOBall = otherBall[i].r;
			}
		}
	}
}
void EatBall()
{
	int MaxOBall, MinOBall;
	for (int i = 0; i < MAXCOUNT; i++)
	{
		if (otherBall[i].live == true)
		{
			if (pow(otherBall[i].space.x - myBall.space.x, 2.0) + pow(otherBall[i].space.y - myBall.space.y, 2.0) < pow(myBall.r, 2.0))
			{
				if (myBall.r >= otherBall[i].r)
				{

					otherBall[i].live = false;
					otherLiveCount--;
					Score += Level*(Percent(20)*otherBall[i].r)+1;
					Hungry += 10;
					if (Hungry>100)
						Hungry = 100;
					myBall.r += Percent(20)*otherBall[i].r;
					if (myBall.r>MinWindow*Percent(30))
					{
						myBall.r = MinWindow*Percent(4);
						Level++;
					}
				}
				else
				{
					otherBall[i].r += Percent(20)*myBall.r;
					if (otherBall[i].r > MinWindow*Percent(30))
					{
						otherBall[i].r = MinWindow*Percent(4);
					}
					myBall.r *= Percent(60);
					Life -= Percent(2)*otherBall[i].r;
					myBall.color.red = 255 - (Life/100*256);
					myBall.color.green = (Life / 100 * 256);
					myBall.color.blue = (Life / 100 * 256);
					GetMaxOBall(&MaxOBall, &MinOBall);
					if (myBall.r<MinOBall)
					{
						myBall.r = MinOBall*Percent(120);
					}
				}
			}
		}
	}
	if (Round == 40)
	{
		Hungry -= 3;
	}
	if (Hungry < 40)
	{
		myBall.r *= Percent(80);
		GetMaxOBall(&MaxOBall, &MinOBall);
		if (myBall.r<MinOBall)
		{
			myBall.r = MinOBall*Percent(120);
		}
	}
	if (Hungry < 0)
	{
		Life -= 2;
		Hungry = 0;
	}
	if (Hungry >= 95)
	{
		if (RAND(100)<30)
		Life += 1;
		if (Life>100)
			Life = 100;
	}
	Round = (Round + 1) % 41;

}
void moveAll()
{
	int key=0;
	MOUSEMSG msg;
	GetDirectCheckInfo(&key,&msg);
	if (msg.uMsg==WM_MOUSEMOVE)
	{
		myBall.direct = atan2(msg.y*1.0-myBall.space.y,msg.x*1.0-myBall.space.x);
		
	}
	myBall.space.x += (10 - myBall.r/ MinWindow*Percent(4))* cos(myBall.direct);
	myBall.space.y += (10 - myBall.r / MinWindow*Percent(4))* sin(myBall.direct);
	if (myBall.space.x - myBall.r < 0)
		myBall.space.x = myBall.r;
	if (myBall.space.x + myBall.r>WindowX)
		myBall.space.x = WindowX - myBall.r;
	if (myBall.space.y - myBall.r < 0)
		myBall.space.y = myBall.r;
	if (myBall.space.y + myBall.r>WindowY)
		myBall.space.y = WindowY - myBall.r;
	for (int i = 0; i < MAXCOUNT; i++)
	{
		if (otherBall[i].space.x - otherBall[i].r < 0 )
		{
			otherBall[i].direct = atan2(8.0 * sin(otherBall[i].direct), -(8.0*cos(otherBall[i].direct)));
			otherBall[i].space.x = otherBall[i].r;
		}
		if (otherBall[i].space.x + otherBall[i].r>WindowX)
		{
			otherBall[i].direct = atan2(8.0 * sin(otherBall[i].direct), -(8.0*cos(otherBall[i].direct)));
			otherBall[i].space.x = WindowX - otherBall[i].r;
		}
		if (otherBall[i].space.y - otherBall[i].r < 0)
		{
			otherBall[i].direct = atan2(-(8.0 * sin(otherBall[i].direct)), (8.0 * cos(otherBall[i].direct)));
			otherBall[i].space.y = otherBall[i].r;
		}
		if (otherBall[i].space.y + otherBall[i].r>WindowY)
		{
			otherBall[i].direct = atan2(-(8.0 * sin(otherBall[i].direct)), (8.0 * cos(otherBall[i].direct)));
			otherBall[i].space.y = WindowY - otherBall[i].r;
		}
		otherBall[i].space.x += (3+ Level*Percent(30) )* cos(otherBall[i].direct);
		otherBall[i].space.y +=( 3 + Level*Percent(30) )* sin(otherBall[i].direct);
	}
}
void initGame()
{
	SRAND;
	bgcolor.red = RANDBETWEEN(200, 255);
	bgcolor.green = RANDBETWEEN(200, 255);
	bgcolor.blue = RANDBETWEEN(200, 255);
	Score = 0;
	Level = 1;
	Life = 100;
	Hungry = 100;
	Round = 0;
	loadimage(&bgimg, "bgimg.jpg",WindowX,WindowY,true);
	mciSendString("open bgm.mp3", 0, 0, 0);
	mciSendString("play bgm.mp3", 0, 0, 0);
	myBall.space.x = WindowX / 2;
	myBall.space.y = WindowY / 2;
	myBall.live = true;
	myBall.r = MinWindow*Percent(4);
	myBall.direct = atan2(1.0,0);
	myBall.color.red = RAND(15);
	myBall.color.green = RAND(255);
	myBall.color.blue = RAND(255);
	otherBall = (Ball *)malloc(sizeof(Ball)*MAXCOUNT);
	otherLiveCount = RANDBETWEEN(5,MAXCOUNT);
	for (int i = 0; i < MAXCOUNT; i++)
	{
		if (i < otherLiveCount)
		{
			otherBall[i].live = true;
		}
		else
		{
			otherBall[i].live = false;
		}
		otherBall[i].r = MinWindow*Percent(RANDBETWEEN(1, 6));
		otherBall[i].space.x = RAND(WindowX);
		otherBall[i].space.y = RAND(WindowY);
		otherBall[i].color.red = RAND(255);
		otherBall[i].color.green = RAND(255);
		otherBall[i].color.blue = RAND(255);
		otherBall[i].direct = atan2(RANDBETWEEN(-20,20)*1.0, RANDBETWEEN(-20,20)*1.0);
	}

}
void drawView()
{
	BeginBatchDraw();
	setfillcolor(GRGB(bgcolor));
	solidrectangle(0,0,WindowX,WindowY);
	putimage(0,0,&bgimg);
	for (int i = 0; i < MAXCOUNT; i++)
	{
		if (otherBall[i].live == true)
		{
			setfillcolor(GRGB(otherBall[i].color));
			solidcircle(otherBall[i].space.x, otherBall[i].space.y, otherBall[i].r);
		}
	}
	if (myBall.live)
	{
		setfillcolor(GRGB(myBall.color));
		solidcircle(myBall.space.x, myBall.space.y, myBall.r);
	}
	char temp[40] = { 0 };
	settextstyle(MinWindow*Percent(3), MinWindow*Percent(2), "黑体");
	settextcolor(RGB(0, 0, 0));
	setbkmode(TRANSPARENT);
	outtextxy(WindowX*Percent(90), 0, "Life");
	rectangle(WindowX*Percent(90), WindowY*Percent(5), WindowX*Percent(98), WindowY*Percent(5) + WindowY*Percent(3));
	setfillcolor(RGB(255,0,0));
	solidrectangle(WindowX*Percent(90), WindowY*Percent(5), WindowX*Percent(90) + WindowX*Percent(8)*Life / 100, WindowY*Percent(5) + WindowY*Percent(3));

	outtextxy(WindowX*Percent(90),WindowY*Percent(10),"Score");
	sprintf_s(temp, "%d\0", Score);
	outtextxy(WindowX*Percent(90), WindowY*Percent(15), temp);

	outtextxy(WindowX*Percent(90), WindowY*Percent(20), "Level");
	sprintf_s(temp, "%d\0", Level);
	outtextxy(WindowX*Percent(90), WindowY*Percent(25), temp);

	outtextxy(WindowX*Percent(90), WindowY*Percent(30), "Hungry");
	rectangle(WindowX*Percent(90), WindowY*Percent(35), WindowX*Percent(98), WindowY*Percent(35) + WindowY*Percent(3));
	setfillcolor(RGB(0, 0, 255));
	solidrectangle(WindowX*Percent(90), WindowY*Percent(35), WindowX*Percent(90) + WindowX*Percent(8)*Hungry / 100, WindowY*Percent(35) + WindowY*Percent(3));
	EndBatchDraw();
}