/** Name: 上升粒子特效 */
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
using namespace std;
int SX;
int SY;
int Num;
typedef struct node
{
	int x;
	int y;
	int r;
	int g;
	int b;
	bool isch;
	char chs[3];
	int radius;
	float speed;
	bool light;
	int mode;
	struct node * next;
}Particle;
Particle * particle;


Particle * CreateParticle()
{
	Particle * p = (Particle *)malloc(sizeof(Particle));
	p->next = NULL;
	p->x = rand()%SX;
	p->y = SY;
	p->r = rand() % 85 + (255 - 85);
	p->g = rand() % 85 + (255 - 85);
	p->b = rand() % 85 + (255 - 85);
	p->chs[2] = 0;
	p->chs[0] = rand() % 256;
	p->chs[1] = rand() % 256;
	if (p->chs[0] >0)
		p->chs[1] = 0;
	p->radius = rand() % 10 + 1;
	p->isch = rand() % 10<7 ? true : false;
	p->light = rand() % 2 ? true : false;
	if (rand() % 10 < 6)
		p->mode = rand() % 2;
	else
		p->mode = 2;
	if (p->isch)
	{
		p->speed = rand() % 8 + 1;
	}
	else
	{
		if (p->mode != 2)
		{
			p->speed = rand() % 8 + 3;
		}
		else
		{
			p->speed = rand() % 8 + 5;
		}
	}
	return p;
}
void AddParticle()
{
	Particle * p = CreateParticle();
	p->next = particle->next;
	particle->next = p;
}
void ShowParticle()
{
	BeginBatchDraw();
	cleardevice();
	int count = 0;
	Particle * tp = particle->next;
	while (tp)
	{
		int cr = tp->r;
		int cg = tp->g;
		int cb = tp->b;
		if (tp->isch)
		{
			settextcolor(RGB(cr, cg, cb));
			outtextxy(tp->x, tp->y, tp->chs);
		}
		else
		{
			if (!tp->light)
			{
				cr -= 80;
				cg -= 80;
				cb -= 80;
			}
			if (tp->mode != 2)
			{
				putpixel(tp->x, tp->y, RGB(cr, cg, cb));
				for (int i = 0; i < tp->radius; i++)
				{
					if (tp->mode == 0)
					{
						putpixel(tp->x + i, tp->y, RGB(cr - 10 * i, cg - 10 * i, cb - 10 * i));
						putpixel(tp->x - i, tp->y, RGB(cr - 10 * i, cg - 10 * i, cb - 10 * i));
						putpixel(tp->x, tp->y + i, RGB(cr - 10 * i, cg - 10 * i, cb - 10 * i));
						putpixel(tp->x, tp->y - i, RGB(cr - 10 * i, cg - 10 * i, cb - 10 * i));
					}
					else
					{
						putpixel(tp->x - i, tp->y - i, RGB(cr - 10 * i, cg - 10 * i, cb - 10 * i));
						putpixel(tp->x - i, tp->y + i, RGB(cr - 10 * i, cg - 10 * i, cb - 10 * i));
						putpixel(tp->x + i, tp->y + i, RGB(cr - 10 * i, cg - 10 * i, cb - 10 * i));
						putpixel(tp->x + i, tp->y - i, RGB(cr - 10 * i, cg - 10 * i, cb - 10 * i));
					}
				}
			}
			else
			{
				int mapping[21][11] = { 
					{ 0, 0, 0, 4, 3, 2, 3, 4, 0, 0, 0 },
					{ 0, 0, 4, 3, 2, 2, 2, 3, 4, 0, 0 },
					{ 0, 4, 3, 2, 1, 1, 1, 2, 3, 4, 0 },
					{ 4, 3, 2, 1, 1, 1, 1, 1, 2, 3, 4 },
					{ 4, 3, 2, 1, 1, 1, 1, 1, 2, 3, 4 },
					{ 3, 2, 1, 1, 1, 1, 1, 1, 1, 2, 3 },
					{ 5, 4, 2, 1, 1, 1, 1, 1, 2, 4, 5 },
					{ 0, 5, 2, 1, 1, 1, 1, 1, 2, 5, 0 },
					{ 0, 5, 2, 1, 1, 1, 1, 1, 2, 5, 0 },
					{ 0, 0, 5, 2, 1, 1, 1, 2, 5, 0, 0 },
					{ 0, 0, 5, 3, 1, 1, 1, 3, 5, 0, 0 },
					{ 0, 0, 0, 3, 1, 1, 1, 3, 0, 0, 0 },
					{ 0, 0, 0, 3, 1, 1, 1, 3, 0, 0, 0 },
					{ 0, 0, 0, 3, 1, 1, 1, 3, 0, 0, 0 },
					{ 0, 0, 0, 4, 3, 1, 3, 4, 0, 0, 0 },
					{ 0, 0, 0, 0, 3, 1, 3, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 4, 2, 4, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 4, 3, 4, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 5, 4, 5, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0 },
				};
				for (int i = 0; i < 21; i++)
				{
					for (int j = 0; j < 11; j++)
					{
						if (mapping[i][j] != 0)
						{
							putpixel(tp->x + j, tp->y + i, RGB(cr - 20 * (mapping[i][j] - 1), cg - 20 * (mapping[i][j] - 1), cb - 20 * (mapping[i][j] - 1)));
						}
					}
				}
			}

		}
		
		count++;
		tp = tp->next;
	}
	char tips[256] = {0};
	sprintf(tips,"Sum: %6d   Level: %3d",count,Num);
	outtextxy(0, 0, tips);
	EndBatchDraw();
}
void MoveParticle()
{
	Particle * tp = particle->next;
	while (tp)
	{
		tp->y -= tp->speed;
		if (!tp->isch && tp->mode!=2)
			tp->x += rand() % 5 - 2;
		if (rand() % 10<3)
			tp->light = !tp->light;
		tp = tp->next;
	}
}
void RemoveDead()
{
	Particle * ftp = particle;
	Particle * tp = particle->next;
	while (tp)
	{
		if (tp->y < 0)
		{
			ftp->next = tp->next;
			free(tp);
			tp = ftp->next;
		}
		else
		{
			tp = tp->next;
			ftp = ftp->next;
		}
		
	}
}
void InitSoftWare()
{
	SX = GetSystemMetrics(SM_CXSCREEN);
	SY= GetSystemMetrics(SM_CYSCREEN);
	Num = 1;
	srand((unsigned int)time(NULL));
	//创建窗口
	HWND phwnd = initgraph(SX, SY);
	//获取桌面窗口
	HWND fhwnd = GetDesktopWindow();
	//设置为子窗口
	SetParent(phwnd, fhwnd);
	//设置窗口透明
	LONG wlong = GetWindowLong(phwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT;
	SetWindowLong(phwnd, GWL_EXSTYLE, wlong);
	SetLayeredWindowAttributes(phwnd, RGB(0, 0, 0), 254, LWA_COLORKEY);
	//设置窗口最底部
	SetWindowPos(phwnd, HWND_TOPMOST, 0, 0, SX, SY, SWP_SHOWWINDOW);
	//消除窗口边框
	SetWindowLong(phwnd, GWL_STYLE, GetWindowLong(phwnd, GWL_STYLE) - WS_CAPTION);

	particle = CreateParticle();
	setbkmode(TRANSPARENT);
}
int main(int argc, char * argv[])
{
	InitSoftWare();
	long ptime = GetTickCount();
	long btime = ptime;
	while (true)
	{
		ptime = GetTickCount();
		if (ptime - btime > 30)
		{
			for (int i = 0; i < Num;i++)
				AddParticle();
			btime = ptime;
		}
		ShowParticle();
		MoveParticle();
		RemoveDead();
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			Num++;
			if (Num>100)
				Num = 100;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			Num--;
			if (Num<1)
				Num = 1;
		}
		Sleep(10);
	}
	return 0;
}