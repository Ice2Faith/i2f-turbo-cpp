#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<graphics.h>
#include<time.h>
#define LINES 10
#define COLS 10
typedef struct
{
	int x;
	int y;
} Point;
int DDirec[4][2] =
{
	{ 0, 1 }, //right
	{ 1, 0 }, //down
	{ 0, -1 }, //left
	{ -1, 0 }, //up
};
int Map[LINES][COLS] =
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 0, 0, 1, 1 },
	{ 1, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
	{ 1, 1, 1, 0, 0, 0, 0, 1, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};
typedef struct
{
	int value;
	int find;
} HelpMap;
HelpMap Hmap[LINES][COLS];
Point Start = { 1, 1 }, End = { 8, 8 }, Test;
typedef struct node
{
	Point point;
	int direct;
	struct node * father;
	struct node * next;
}RouteNode;
struct
{
	RouteNode * head;
	RouteNode * rear;
	RouteNode * present;
}QueueRoute;
RouteNode * CreateNode();
void AddNode(Point point, RouteNode * father);
void FreeQueue();

void initialapp();
void SetMap();

void AStarRouter();
void MoveCheck(Point Test, RouteNode * father);
void InitEnveronment();

void DisplayMap();
void DrawRoute();

int size = (GetSystemMetrics(SM_CYSCREEN) > GetSystemMetrics(SM_CXSCREEN) ? GetSystemMetrics(SM_CXSCREEN) : GetSystemMetrics(SM_CYSCREEN)) / 12;
IMAGE bgimage, wall, people, step, route, end;
HWND hwnd;

int _tmain(int argc, _TCHAR * argv[])
{
	hwnd = initgraph(LINES*size, COLS*size);
	initialapp();
	AStarRouter();
	return 0;
}

void AStarRouter()
{
	InitEnveronment();
	Hmap[QueueRoute.present->point.x][QueueRoute.present->point.y].find = 1;
	while (true)
	{
		Test.x = QueueRoute.present->point.x;
		Test.y = QueueRoute.present->point.y;
		switch (QueueRoute.present->direct)
		{
		case 0:
		{
				  QueueRoute.present->direct++;
				  Test.x += DDirec[0][0];
				  Test.y += DDirec[0][1];
				  MoveCheck(Test, QueueRoute.present);
				  break;
		}
		case 1:
		{
				  QueueRoute.present->direct++;
				  Test.x += DDirec[1][0];
				  Test.y += DDirec[1][1];
				  MoveCheck(Test, QueueRoute.present);
				  break;
		}
		case 2:
		{
				  QueueRoute.present->direct++;
				  Test.x += DDirec[2][0];
				  Test.y += DDirec[2][1];
				  MoveCheck(Test, QueueRoute.present);
				  break;
		}
		case 3:
		{
				  Test.x += DDirec[3][0];
				  Test.y += DDirec[3][1];
				  MoveCheck(Test, QueueRoute.present);
				  QueueRoute.present = QueueRoute.present->next;
				  break;
		}
		}
		DisplayMap();
		if (QueueRoute.present == NULL)
		{
			settextcolor(RGB(0, 120, 255));
			settextstyle(LINES*size * 5 / 100, LINES*size * 5 / 100, "黑体");
			outtextxy(LINES*size * 20 / 100, COLS*size / 2, "Failure!!");
			break;
		}
		if (QueueRoute.present->point.x == End.x&&QueueRoute.present->point.y == End.y)
		{
			DrawRoute();
			settextcolor(RGB(0, 120, 255));
			settextstyle(LINES*size * 5 / 100, LINES*size * 5 / 100, "黑体");
			outtextxy(LINES*size * 20 / 100, COLS*size / 2, "Success!!");
			break;
		}
		Sleep(10);
	}
	FreeQueue();
	settextcolor(RGB(0, 255, 255));
	settextstyle(LINES*size * 5 / 100, LINES*size * 5 / 100, "黑体");
	outtextxy(LINES*size * 20 / 100, COLS*size - LINES*size * 5 / 100, "Click 0 exit");
	char sel = '\0';
	while (sel != '0')
		sel = _getch();
}
void MoveCheck(Point Test, RouteNode * father)
{
	if (Hmap[Test.x][Test.y].find == 0 && Hmap[Test.x][Test.y].value == 0 && (Test.x >= 0 && Test.x < LINES) && (Test.y >= 0 && Test.y < COLS))
	{
		AddNode(Test, father);
		Hmap[Test.x][Test.y].find = 1;
	}
}
void InitEnveronment()
{
	for (int i = 0; i < LINES; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			Hmap[i][j].value = Map[i][j];
			Hmap[i][j].find = 0;
		}
	}
}
void DisplayMap()
{
	BeginBatchDraw();
	for (int i = 0; i < LINES; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (i == Start.x&&j == Start.y)
			{
				putimage(j*size, i*size, &people);
			}
			else if (i == End.x&&j == End.y)
			{
				putimage(j*size, i*size, &end);
			}
			else if (Hmap[i][j].value == 9)
			{
				putimage(j*size, i*size, &route);
			}
			else if (Hmap[i][j].value == 1)
			{
				putimage(j*size, i*size, &wall);
			}
			else if (Hmap[i][j].find == 1)
			{
				putimage(j*size, i*size, &step);
			}
		}
	}
	EndBatchDraw();
}
void DrawRoute()
{
	RouteNode * rear = QueueRoute.present;
	while (rear)
	{
		Hmap[rear->point.x][rear->point.y].value = 9;
		rear = rear->father;
	}
	DisplayMap();
}
void initialapp()
{
	loadimage(&bgimage, "src\\bgimage.jpg", COLS*size, LINES*size, true);
	loadimage(&wall, "src\\wall.jpg", size, size, true);
	loadimage(&people, "src\\people.jpg", size, size, true);
	loadimage(&step, "src\\step.jpg", size, size, true);
	loadimage(&route, "src\\route.jpg", size, size, true);
	loadimage(&end, "src\\end.jpg", size, size, true);
	setbkmode(TRANSPARENT);
	SetMap();
	QueueRoute.head = CreateNode();
	QueueRoute.head->point.x = Start.x;
	QueueRoute.head->point.y = Start.y;
	QueueRoute.rear = QueueRoute.head;
	QueueRoute.present = QueueRoute.head;
}
void SetMap()
{
	putimage(0, 0, &bgimage);
	settextcolor(RGB(0, 255, 255));
	settextstyle(LINES*size * 3 / 100, LINES*size * 3 / 100, "黑体");
	outtextxy(LINES*size * 20 / 100, COLS*size * 10 / 100, "单路A*寻路展示");
	outtextxy(LINES*size * 20 / 100, COLS*size * 20 / 100, "1/左键:设置墙壁");
	outtextxy(LINES*size * 20 / 100, COLS*size * 30 / 100, "2/右键:设置空白");
	outtextxy(LINES*size * 20 / 100, COLS*size * 40 / 100, "3:设置出发点");
	outtextxy(LINES*size * 20 / 100, COLS*size * 50 / 100, "4:设置终点");
	outtextxy(LINES*size * 20 / 100, COLS*size * 60 / 100, "*:结束绘制");
	outtextxy(LINES*size * 20 / 100, COLS*size * 80 / 100, "点击任意键开始");
	outtextxy(LINES*size * 20 / 100, COLS*size * 90 / 100, "Dev Ice2Faith");
	_getch();
	BeginBatchDraw();
	putimage(0, 0, &bgimage);
	for (int i = 0; i < LINES; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (i == Start.x&&j == Start.y)
				putimage(j*size, i*size, &people);
			else if (i == End.x&&j == End.y)
				putimage(j*size, i*size, &end);
			else if (Map[i][j] == 1)
				putimage(j*size, i*size, &wall);
		}
	}
	EndBatchDraw();
	MOUSEMSG msg;
	Point temp;
	char set = '\0';
	while (1)
	{
		set = '\0';
		if (_kbhit())
		{
			set = _getch();
			fflush(stdin);
		}

		while (MouseHit())
		{
			msg = GetMouseMsg();
			temp.x = msg.y;
			temp.y = msg.x;
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				Map[temp.x / size][temp.y / size] = 1;
			}
			if (msg.uMsg == WM_RBUTTONDOWN)
			{
				Map[temp.x / size][temp.y / size] = 0;
			}
		}

		if (set == '*')
			break;
		if (set == '1')
		{
			Map[temp.x / size][temp.y / size] = 1;
		}
		if (set == '2')
		{
			Map[temp.x / size][temp.y / size] = 0;
		}
		if (set == '3')
		{
			Start.x = temp.x / size;
			Start.y = temp.y / size;
		}
		if (set == '4')
		{
			End.x = temp.x / size;
			End.y = temp.y / size;
		}

		BeginBatchDraw();
		putimage(0, 0, &bgimage);
		for (int i = 0; i < LINES; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				if (i == Start.x&&j == Start.y)
					putimage(j*size, i*size, &people);
				else if (i == End.x&&j == End.y)
					putimage(j*size, i*size, &end);
				else if (Map[i][j] == 1)
					putimage(j*size, i*size, &wall);
			}
		}
		EndBatchDraw();
	}
}

//------------------------------------------

RouteNode * CreateNode()
{
	RouteNode * p = (RouteNode *)malloc(sizeof(RouteNode));
	p->father = NULL;
	p->next = NULL;
	p->direct = 0;
	return p;
}
void AddNode(Point point, RouteNode * father)
{
	RouteNode * p = CreateNode();
	p->point.x = point.x;
	p->point.y = point.y;
	p->father = father;
	QueueRoute.rear->next = p;
	QueueRoute.rear = p;
}
void FreeQueue()
{
	RouteNode * p = QueueRoute.head, *q;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
	QueueRoute.head = NULL;
	QueueRoute.rear = NULL;
	QueueRoute.present = NULL;
}