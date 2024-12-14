#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<math.h>
#include<stdio.h>
typedef struct
{
	int x;
	int y;
}Point;

typedef struct node
{
	Point space;
	struct node * next;
}SNACK;
typedef struct
{
	Point space;
	int reward;
	bool normal;
}FOOD;
typedef struct
{
	Point space;
	int radius;
	double direct;
	int speed;
}BOSS;

int WX = GetSystemMetrics(SM_CXSCREEN) * 6 / 10;
int WY = GetSystemMetrics(SM_CYSCREEN) * 6 / 10;
int SnackRadius = 12;
int FoodRadius = 10;
int SnackSpeed = 10;
MOUSEMSG msg = { 0 };
SNACK * snack=NULL;
BOSS boss = { 0 };
double SnackHeadDirect = 0;
FOOD food = { 0 };

int Score = 0;
int Level = 1;
int Count = 0;

double Distance(Point p1, Point p2)
{
	return sqrt(((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y))*1.0);
}
SNACK * CreateNode()
{
	SNACK * p = (SNACK *)malloc(sizeof(SNACK));
	p->next = NULL;
	p->space.x = 0;
	p->space.y = 0;
	return p;
}
void HeadInsertNode(Point p)
{
	SNACK * pnode = CreateNode();
	pnode->space.x = p.x;
	pnode->space.y = p.y;
	pnode->next = snack->next;
	snack->next = pnode;
}
void InitGame()
{
	srand((unsigned int)time(NULL));
	initgraph(WX, WY);
	setbkcolor(RGB(255, 255, 255));
	cleardevice();
	snack = CreateNode();
	Point p = { WX / 2, WY / 2 };
	HeadInsertNode(p);
	food.space.x = rand() % WX;
	food.space.y = rand() % WY;
	food.reward = 1;
	food.normal = false;
	settextcolor(RGB(0, 0, 0));
	setbkmode(TRANSPARENT);
	boss.radius = 8;
	boss.space.x = WX;
	boss.space.y = WY;
	boss.direct = 0;
	boss.speed = 5;
}
void DrawMap()
{
	BeginBatchDraw();
	cleardevice();
	
	SNACK * pnode = snack->next;
	while (pnode)
	{
		if (pnode==snack->next)
			setfillcolor(RGB(255, 0, 0));
		else if (pnode->next==NULL)
			setfillcolor(RGB(0, 0, 255));
		else
			setfillcolor(RGB(0, 255, 255));
		solidcircle(pnode->space.x, pnode->space.y, SnackRadius);
		pnode = pnode->next;
	}
	setfillcolor(RGB(255, 0, 0));
	solidcircle(snack->next->space.x, snack->next->space.y, SnackRadius);
	if (food.normal)
		setfillcolor(RGB(255, 0, 255));
	else
	setfillcolor(RGB(255, 255, 0));
	solidcircle(food.space.x, food.space.y, FoodRadius);

	setfillcolor(RGB(0,0,0));
	solidcircle(boss.space.x, boss.space.y, boss.radius);

	char temp[256] = { 0 };
	sprintf(temp, "Score : %d\0", Score);
	outtextxy(WX * 9 / 10, WY * 1 / 10, temp);
	sprintf(temp, "Level : %d\0", Level);
	outtextxy(WX * 9 / 10, WY * 2 / 10, temp);
	sprintf(temp, "Ate : %d\0", Count);
	outtextxy(WX * 9 / 10, WY * 3 / 10, temp);
	EndBatchDraw();
}
void CreateFood()
{
	Point pfood = { 0 };
	bool badfood = true;
	while (badfood)
	{
		pfood = { rand() % WX, rand() % WY };
		SNACK * pnode = snack->next;
		while (pnode)
		{
			if (Distance(pfood, pnode->space) > SnackRadius + FoodRadius)
			{
				badfood = false;
				break;
			}
			pnode = pnode->next;
		}
	}
	food.space.x = pfood.x;
	food.space.y = pfood.y;
	if (rand() % 100 < 18)
	{
		food.normal = true;
		food.reward = rand() % 10 + 1;
	}
	else
	{
		food.normal = false;
		food.reward =  1;
	}
}
void GetMoveDirect()
{
	while (MouseHit())
	{
		msg = GetMouseMsg();
		SnackHeadDirect = atan2(msg.x - snack->next->space.x*1.0, msg.y - snack->next->space.y*1.0);
	}
	
	boss.direct = atan2(food.space.x - boss.space.x*1.0, food.space.y - boss.space.y*1.0);
}
void MoveSnack()
{
	boss.space.x = boss.space.x + boss.speed*sin(boss.direct);
	boss.space.y = boss.space.y + boss.speed*cos(boss.direct);
	Point p = { 0 };
	p.x = snack->next->space.x + SnackSpeed*sin(SnackHeadDirect);
	p.y = snack->next->space.y + SnackSpeed*cos(SnackHeadDirect);
	HeadInsertNode(p);

	SNACK * fpnode = snack, *pnode = snack->next;
	while (pnode)
	{
		if (pnode->next == NULL)
			break;
		pnode = pnode->next;
		fpnode = fpnode->next;
	}
	free(pnode);
	fpnode->next = NULL;
}
void EatFood()
{
	if (Distance(food.space, boss.space) < boss.radius + FoodRadius)
	{
		boss.radius++;
		if (boss.radius>30)
			boss.radius = 30;
		CreateFood();
	}
	if (Distance(food.space, snack->next->space) < SnackRadius+FoodRadius)
	{
		Score += food.reward;
		Count++;
		Level = Count / 30;
		SnackSpeed = 10 + Level;
		boss.speed = 5 + Level*1.2;
		if (SnackSpeed>24)
			SnackSpeed = 24;
		if (boss.speed > 20)
			boss.speed = 20;
		HeadInsertNode(food.space);
		CreateFood();
	}
}
bool KillCheck()
{
	SNACK * pnode = snack->next;
	if (pnode->space.x<0   || pnode->space.x>WX   || pnode->space.y<0   || pnode->space.y>WY  )
		return true;
	if (Distance(pnode->space, boss.space) < SnackRadius + boss.radius)
		return true;
	if (pnode->next)
	{
		pnode = pnode->next;
		while (pnode)
		{
			if (Distance(pnode->space, boss.space) < SnackRadius + boss.radius)
				boss.radius--;
			if (boss.radius < 8)
				boss.radius = 8;
			pnode = pnode->next;
		}
	}
	
	return false;
}
void welcome()
{
	outtextxy(WX * 2 / 5, WY * 4 / 10, "万向贪吃蛇");
	outtextxy(WX * 2 / 5, WY * 5 / 10, "控制你的蛇吃食物");
	outtextxy(WX * 2 / 5, WY * 6 / 10, "不要被黑刺猬碰到");
	outtextxy(WX * 2 / 5, WY * 7 / 10, "不要撞到墙壁");
	outtextxy(WX * 2 / 5, WY * 8 / 10, "按任意键开始游戏");
	getch();
}
int main()
{
	InitGame();
	welcome();
	while (1)
	{
		DrawMap();
		GetMoveDirect();
		MoveSnack();
		if (KillCheck())
			break;
		EatFood();
		Sleep(30);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break;
	}
	outtextxy(WX * 2 / 5, WY * 4 / 10, "游戏结束，按任意键退出");
	getch();
	return 0;
}