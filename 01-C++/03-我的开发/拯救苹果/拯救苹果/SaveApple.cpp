#include<graphics.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
long long Score;
IMAGE apple, bgimage, apple_mask, sword, sword_mask;
int WX, WY;
int FontWid, FontHei;
int AppleSize;
typedef struct node
{
	int x, y;
	char ch;
	int life;
	bool live;
	struct node * next;
}Apple;
Apple * apps = NULL;
bool mode;
int speed;
Apple * AddNode()
{
	Apple * p = (Apple *)malloc(sizeof(Apple));
	p->next = NULL;
	if (!mode)
	{
		p->ch = rand() % 10 + '0';
	}
	else
	{
		p->ch = rand() % 26 + 'A';
	}
	p->x = rand() % (WX - AppleSize);
	p->y = 0;
	p->live = true;
	p->life = 10;
	return p;
}
void CreateApple()
{
	Apple *p = apps;
	while (p->next)
	{
		p = p->next;
	}
	p->next = AddNode();
}

void InitGame()
{
	srand((unsigned int)time(NULL));
	WX = GetSystemMetrics(SM_CXSCREEN) * 6 / 10;
	WY = GetSystemMetrics(SM_CYSCREEN) * 6 / 10;
	AppleSize = WX * 10 / 100;
	loadimage(&apple, "apple.jpg", AppleSize, AppleSize);
	loadimage(&apple_mask, "apple_mask.jpg", AppleSize, AppleSize);
	loadimage(&sword, "sword.jpg", AppleSize, AppleSize);
	loadimage(&sword_mask, "sword_mask.jpg", AppleSize, AppleSize);
	loadimage(&bgimage, "bgimage.jpg", WX, WY);
	HWND hwnd = initgraph(WX, WY);
	//窗口透明
	LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
	SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
	//不穿透点击
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 200, LWA_ALPHA);
	apps = AddNode();
	FontWid = AppleSize * 3 / 10;
	FontHei = FontWid * 3 / 2;
	settextstyle(FontHei, FontWid, "黑体");
	setbkmode(TRANSPARENT);
	Score = 5;
	mode = false;
	speed = 1;
}
void DrawView()
{
	BeginBatchDraw();
	putimage(0, 0, &bgimage);
	Apple * p = apps->next;
	settextcolor(RGB(255, 255, 255));
	while (p)
	{
		putimage(p->x, p->y, &apple_mask, SRCPAINT);
		putimage(p->x, p->y, &apple, SRCAND);
		outtextxy(p->x + (AppleSize - FontWid) / 2, p->y + (AppleSize - FontHei) * 2 / 3, p->ch);
		if (!p->live)
		{
			putimage(p->x, p->y, &sword_mask, SRCPAINT);
			putimage(p->x, p->y, &sword, SRCAND);
			p->life--;
		}

		p = p->next;
	}
	char DScore[256] = { 0 };
	sprintf(DScore, "Score : %d\0", Score);
	settextcolor(RGB(0, 0, 0));
	outtextxy(WX * 3 / 10, WY - FontHei, DScore);
	EndBatchDraw();
}
void DropApple()
{
	Apple * p = apps->next;
	while (p)
	{
		p->y += speed;
		p->x += rand() % 3 - 1;
		p = p->next;
	}

}
void CleanApple()
{
	Apple * father = apps;
	Apple * child = father->next;
	while (child)
	{
		if (child->y > WY || child->life <= 0)
		{
			if (child->y > WY && child->live)
				Score--;
			father->next = father->next->next;
			free(child);
			child = father->next;
		}
		else
		{
			child = child->next;
			father = father->next;
		}

	}

}

void SaveApple(char save)
{
	if (save >= 'a'&&save <= 'z')save &= ~32;
	Apple * father = apps;
	Apple * child = father->next;
	while (child)
	{
		if (child->live && child->ch == save)
		{
			child->live = false;
			Score++;
			break;
		}
		else
		{
			child = child->next;
			father = father->next;
		}

	}
}
void PlayBGM()
{
	while (1)
	{
		mciSendString("open bgmusic.mp3", NULL, NULL, NULL);
		mciSendString("play bgmusic.mp3", NULL, NULL, NULL);
		Sleep(3 * 60 * 1000);
		mciSendString("close bgmusic.mp3", NULL, NULL, NULL);
	}

}
void Welcome()
{
	putimage(0, 0, &bgimage);
	settextcolor(RGB(0, 0, 0));
	outtextxy(WX * 1 / 3, WY * 1 / 10, "拯救苹果");
	outtextxy(WX * 1 / 5, WY * 4 / 10, "空格：切换数字字母模式");
	outtextxy(WX * 1 / 5, WY * 5 / 10, "上下：变换掉落速度");
	outtextxy(WX * 1 / 5, WY * 6 / 10, "+：使用5次道具清除苹果");
	outtextxy(WX * 1 / 5, WY * 7 / 10, "道具：70%成功率，损失20分数");
	outtextxy(WX * 1 / 5, WY * 8 / 10, "按任意键开始游戏");
	getch();
}
int main()
{
	InitGame();
	long beftime, nowtime;
	beftime = nowtime = GetTickCount();
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)PlayBGM, NULL, NULL, NULL);
	Welcome();
	while (true){
		DrawView();
		DropApple();
		CleanApple();
		char save = 0;

		if (kbhit())
		{
			save = getch();
			if (save == '+')
			{
				if (Score > 20)
				{
					Score -= 20;
					for (int k = 0; k < 5; k++)
					{
						if (rand() % 100 < 30)
							continue;
						Apple * tp = apps->next;
						if (tp)
						{
							while (tp)
							{
								if (tp->live)
									break;
								tp = tp->next;
							}
							if (tp)
							{
								save = tp->ch;
								SaveApple(save);
							}

						}
					}
				}

			}
			if (save == ' ')
				mode = !mode;
			else
				SaveApple(save);
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			speed += 1;
			if (speed > 20)
				speed = 20;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			speed -= 1;
			if (speed < 1)
				speed = 1;
		}
		nowtime = GetTickCount();
		if (nowtime - beftime > 1200)
		{
			CreateApple();
			beftime = nowtime;
		}

		Sleep(30);
		if (Score < 0 || GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break;
	}
	outtextxy(WX * 1 / 5, WY * 8 / 10, "按任意键退出游戏");
	fflush(stdin);
	getch();
	return 0;
}