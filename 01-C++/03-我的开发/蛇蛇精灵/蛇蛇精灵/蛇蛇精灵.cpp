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


int WX = GetSystemMetrics(SM_CXSCREEN) ;
int WY = GetSystemMetrics(SM_CYSCREEN) ;
int SnackRadius = 12;
int FoodRadius = 10;
int SnackSpeed = 10;
int SnackLife = 100;
int SleepTime = 30;
struct {
	short red;
	short green;
	short blue;
} SnackColor = { 0, 255, 255 }, FoodColor = {255,255,0};
int ContinueAte = 0;
MOUSEMSG msg = { 0 };
SNACK * snack = NULL;
BOSS boss = { 0 };
BOSS killboss = { 0 };
double SnackHeadDirect = 0;
FOOD food = { 0 };

int Score = 0;
int Level = 1;
int AteSum = 0;

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
	

	//窗口最大化
	HWND hwnd = initgraph(WX, WY);

	//窗口透明
	LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
	SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
	//穿透点击
	SetLayeredWindowAttributes(hwnd, RGB(255, 255, 255), 0, LWA_COLORKEY);

	//窗口最前端
	SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, WX, WY, SWP_SHOWWINDOW);

	//消除边框
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);


	srand((unsigned int)time(NULL));

	setbkcolor(RGB(255, 255, 255));
	cleardevice();
	snack = CreateNode();
	Point p = { WX / 2, WY / 2 };
	HeadInsertNode(p);
	food.space.x = rand() % WX;
	food.space.y = rand() % WY;
	food.reward = 1;
	food.normal = false;
	settextcolor(RGB(120, 240, 120));
	setbkmode(TRANSPARENT);
	boss.radius = 8;
	boss.space.x = WX;
	boss.space.y = WY;
	boss.direct = 0;
	boss.speed = 5;

	killboss.radius = 10;
	killboss.space.x = 0;
	killboss.space.y = WY;
	killboss.direct = 0;
	killboss.speed = 6;
}
void DrawMap()
{
	BeginBatchDraw();
	cleardevice();

	SNACK * pnode = snack->next;
	while (pnode)
	{
		if (pnode == snack->next)
			setfillcolor(RGB(255 , 0 , 0));
		else if (pnode->next == NULL)
			setfillcolor(RGB(0, 0 , 255 ));
		else
			setfillcolor(RGB(SnackColor.red, SnackColor.green, SnackColor.blue));
		solidcircle(pnode->space.x, pnode->space.y, SnackRadius);
		pnode = pnode->next;
	}
	setfillcolor(RGB(255 , 0 , 0));
	solidcircle(snack->next->space.x, snack->next->space.y, SnackRadius);
	if (food.normal)
		setfillcolor(RGB(FoodColor.red, FoodColor.green, FoodColor.blue));
	else
		setfillcolor(RGB(255, 255, 0));
	solidcircle(food.space.x, food.space.y, FoodRadius);

	setfillcolor(RGB(100, 200, 100));
	solidcircle(boss.space.x, boss.space.y, boss.radius);

	setfillcolor(RGB(200, 100, 150));
	solidcircle(killboss.space.x, killboss.space.y, killboss.radius);

	char temp[256] = { 0 };
	sprintf(temp, "Life : %d\0", SnackLife);
	outtextxy(WX * 9 / 10, 0, temp);
	sprintf(temp, "Score : %d\0", Score);
	outtextxy(WX * 9 / 10, WY * 1 / 10, temp);
	sprintf(temp, "Level : %d\0", Level);
	outtextxy(WX * 9 / 10, WY * 2 / 10, temp);
	sprintf(temp, "Ate : %d\0", AteSum);
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
		food.reward = 1;
	}
}
void GetMoveDirect()
{

	boss.direct = atan2(food.space.x - boss.space.x*1.0, food.space.y - boss.space.y*1.0);
	killboss.direct = atan2(snack->next->space.x - killboss.space.x*1.0, snack->next->space.y - killboss.space.y*1.0);
	SnackHeadDirect = atan2(food.space.x - snack->next->space.x*1.0, food.space.y - snack->next->space.y*1.0);
	while (1)
	{
		Point p = { 0 };
		p.x = snack->next->space.x + SnackSpeed*sin(SnackHeadDirect);
		p.y = snack->next->space.y + SnackSpeed*cos(SnackHeadDirect);
		if (Distance(p, boss.space) > SnackRadius + boss.radius && Distance(p, killboss.space) > SnackRadius + killboss.radius)
		{
			break;
		}
		SnackHeadDirect = atan2(rand() % 1000 - 500*1.0, rand() % 1000 - 500*1.0);
	}
}
void MoveSnack()
{
	boss.space.x = boss.space.x + boss.speed*sin(boss.direct);
	boss.space.y = boss.space.y + boss.speed*cos(boss.direct);

	killboss.space.x = killboss.space.x + killboss.speed*sin(killboss.direct);
	killboss.space.y = killboss.space.y + killboss.speed*cos(killboss.direct);
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
		ContinueAte = 0;
		CreateFood();
	}
	if (Distance(food.space, snack->next->space) < SnackRadius + FoodRadius)
	{
		if (food.normal)
		{
			memcpy((void *)&SnackColor, (void *)&FoodColor, sizeof(SnackColor));
			FoodColor.red = rand() % 100 + 155;
			FoodColor.green = rand() % 10 + 155;
			FoodColor.blue = rand() % 100 + 155;
		}
		Score += food.reward;
		AteSum++;
		Level = AteSum / 30;
		SnackSpeed = 10 + Level;
		boss.speed = 5 + Level*1.2;
		if (SnackSpeed>24)
			SnackSpeed = 24;
		if (boss.speed > 20)
			boss.speed = 20;
		killboss.speed = 5 + Level*1.1;
		if (killboss.speed > 18)
			killboss.speed = 18;
		HeadInsertNode(food.space);
		ContinueAte++;
		CreateFood();
	}
	if (ContinueAte > 12)
	{
		if (SnackLife < 99)
			SnackLife++;
		ContinueAte = 0;
	}
}
bool KillCheck()
{
	SNACK * pnode = snack->next;
	if (pnode->space.x<0 || pnode->space.x>WX || pnode->space.y<0 || pnode->space.y>WY)
		return true;
	if (Distance(pnode->space, boss.space) < (SnackRadius + boss.radius)/2)
		return true;
	if (Distance(pnode->space, killboss.space) < (SnackRadius + killboss.radius)/2)
		return true;
	if (AteSum>512)
	{
		boss.radius=30;
	}
	else if (pnode->next)
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
void DeleteBack(int index)
{
	if (index <= 0)
		index = 0;
	SNACK *fnode=snack,*pnode = snack->next,*temp;
	int pindex = 0;
	while (pnode)
	{
		pnode = pnode->next;
		fnode = fnode->next;
		if (pindex >= index)
			break;
		pindex++;
		
	}
	fnode->next = NULL;
	while (pnode)
	{
		temp = pnode;
		pnode = pnode->next;
		free(temp);
	}
}
int main()
{
	InitGame();

	while (1)
	{
		DrawMap();
		GetMoveDirect();
		MoveSnack();
		if (KillCheck())
			SnackLife--;
		if (SnackLife <= 0)
			break;
		EatFood();
		Sleep(SleepTime);
		if (AteSum % 1280 == 1279)
		{
			DeleteBack(1024);
		}
	}
	DeleteBack(0);
	return 0;
}