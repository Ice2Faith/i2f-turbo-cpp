#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<graphics.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define LINES 10
#define COLS 10
#define QR_START 0
#define QR_END 1
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
Point Start = { 1, 1 }, End = { 8, 8 }, STest,ETest;
typedef struct node
{
	Point point;
	int direct;
	struct node * father;
	struct node * next;
}RouteNode;
typedef struct
{
	RouteNode * head;
	RouteNode * rear;
	RouteNode * present;
}QRoute;
QRoute QueueRouteStart, QueueRouteEnd;
RouteNode * CreateNode();
void AddNode(Point point, RouteNode * father,int QR_MODE);
void FreeQueue(int QR_MODE);

void initialapp();
void SetMap();

void AStarRouter();
void MoveCheck(Point Test, RouteNode * father, int QR_MODE);
void InitEnveronment();

void DisplayMap();
void DrawRoute();

int size = (GetSystemMetrics(SM_CYSCREEN) > GetSystemMetrics(SM_CXSCREEN) ? GetSystemMetrics(SM_CXSCREEN) : GetSystemMetrics(SM_CYSCREEN)) / 12;
IMAGE bgimage, wall, people, step, route, end;
HWND hwnd;

Point Find;
bool Isfind = false;
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
	Hmap[QueueRouteStart.present->point.x][QueueRouteStart.present->point.y].find = 1;
	Hmap[QueueRouteEnd.present->point.x][QueueRouteEnd.present->point.y].find = 2;
	while (true)
	{
		STest.x = QueueRouteStart.present->point.x;
		STest.y = QueueRouteStart.present->point.y;
		ETest.x = QueueRouteEnd.present->point.x;
		ETest.y = QueueRouteEnd.present->point.y;
		switch (QueueRouteStart.present->direct)
		{
		case 0:
		{
				  QueueRouteStart.present->direct++;
				  STest.x += DDirec[0][0];
				  STest.y += DDirec[0][1];
				  MoveCheck(STest, QueueRouteStart.present,QR_START);

				  QueueRouteEnd.present->direct++;
				  ETest.x += DDirec[0][0];
				  ETest.y += DDirec[0][1];
				  MoveCheck(ETest, QueueRouteEnd.present, QR_END);
				  break;
		}
		case 1:
		{
				  QueueRouteStart.present->direct++;
				  STest.x += DDirec[1][0];
				  STest.y += DDirec[1][1];
				  MoveCheck(STest, QueueRouteStart.present, QR_START);

				  QueueRouteEnd.present->direct++;
				  ETest.x += DDirec[1][0];
				  ETest.y += DDirec[1][1];
				  MoveCheck(ETest, QueueRouteEnd.present, QR_END);
				  break;
		}
		case 2:
		{
				  QueueRouteStart.present->direct++;
				  STest.x += DDirec[2][0];
				  STest.y += DDirec[2][1];
				  MoveCheck(STest, QueueRouteStart.present, QR_START);

				  QueueRouteEnd.present->direct++;
				  ETest.x += DDirec[2][0];
				  ETest.y += DDirec[2][1];
				  MoveCheck(ETest, QueueRouteEnd.present, QR_END);
				  break;
		}
		case 3:
		{
				  STest.x += DDirec[3][0];
				  STest.y += DDirec[3][1];
				  MoveCheck(STest, QueueRouteStart.present, QR_START);
				  QueueRouteStart.present = QueueRouteStart.present->next;

				  ETest.x += DDirec[3][0];
				  ETest.y += DDirec[3][1];
				  MoveCheck(ETest, QueueRouteEnd.present,QR_END);
				  QueueRouteEnd.present = QueueRouteEnd.present->next;
				  break;
		}
		}
		DisplayMap();
		if (QueueRouteStart.present == NULL || QueueRouteEnd.present == NULL)
		{
			settextcolor(RGB(0, 120, 255));
			settextstyle(LINES*size * 5 / 100, LINES*size * 5 / 100, "黑体");
			outtextxy(LINES*size * 20 / 100, COLS*size / 2, "Failure!!");
			break;
		}
		if (Isfind==true)
		{

			DrawRoute();
			settextcolor(RGB(0, 120, 255));
			settextstyle(LINES*size * 5 / 100, LINES*size * 5 / 100, "黑体");
			outtextxy(LINES*size * 20 / 100, COLS*size / 2, "Success!!");
			break;
		}
		Sleep(10);
	}
	FreeQueue(QR_START);
	settextcolor(RGB(0, 255, 255));
	settextstyle(LINES*size * 5 / 100, LINES*size * 5 / 100, "黑体");
	outtextxy(LINES*size * 20 / 100, COLS*size - LINES*size * 5 / 100, "Click 0 exit");
	char sel = '\0';
	while (sel != '0')
		sel = _getch();
}
void MoveCheck(Point Test, RouteNode * father, int QR_MODE)
{
	if (QR_MODE == QR_START)
	{
		if ((Hmap[Test.x][Test.y].find == 0 || Hmap[Test.x][Test.y].find == 2) && Hmap[Test.x][Test.y].value == 0 && (Test.x >= 0 && Test.x < LINES) && (Test.y >= 0 && Test.y < COLS))
		{
			if (Hmap[Test.x][Test.y].find == 2)
			{
				Isfind = true;
				Find.x = Test.x;
				Find.y = Test.y;
			}
			AddNode(Test, father, QR_START);
			Hmap[Test.x][Test.y].find = 1;
		}
	}
	else if (QR_MODE == QR_END)
	{
		if ((Hmap[Test.x][Test.y].find == 0 || Hmap[Test.x][Test.y].find == 1) && Hmap[Test.x][Test.y].value == 0 && (Test.x >= 0 && Test.x < LINES) && (Test.y >= 0 && Test.y < COLS))
		{
			if (Hmap[Test.x][Test.y].find == 1)
			{
				Isfind = true;
				Find.x = Test.x;
				Find.y = Test.y;
			}
			AddNode(Test, father, QR_END);
			Hmap[Test.x][Test.y].find = 2;
		}
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
	Isfind = false;
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
			else if (Hmap[i][j].find == 2)
			{
				putimage(j*size, i*size, &step);
			}
		}
	}
	EndBatchDraw();
}
void DrawRoute()
{
	RouteNode * rear = QueueRouteStart.present;
	rear = QueueRouteStart.head;
	while (rear)
	{
		if (rear->point.x == Find.x && rear->point.y==Find.y)
			break;
		rear = rear->next;
	}
	while (rear)
	{
		Hmap[rear->point.x][rear->point.y].value = 9;
		rear = rear->father;
	}
	rear = QueueRouteEnd.present;
	rear = QueueRouteEnd.head;
	while (rear)
	{
		if (rear->point.x == Find.x && rear->point.y == Find.y)
			break;
		rear = rear->next;
	}
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
	mciSendString("open bgm.mp3",0,0,0);
	mciSendString("play bgm.mp3", 0, 0, 0);
	setbkmode(TRANSPARENT);
	SetMap();
	QueueRouteStart.head = CreateNode();
	QueueRouteStart.head->point.x = Start.x;
	QueueRouteStart.head->point.y = Start.y;
	QueueRouteStart.rear = QueueRouteStart.head;
	QueueRouteStart.present = QueueRouteStart.head;
	QueueRouteEnd.head = CreateNode();
	QueueRouteEnd.head->point.x = End.x;
	QueueRouteEnd.head->point.y = End.y;
	QueueRouteEnd.rear = QueueRouteEnd.head;
	QueueRouteEnd.present = QueueRouteEnd.head;
}
void SetMap()
{
	putimage(0, 0, &bgimage);
	settextcolor(RGB(0, 255, 255));
	settextstyle(LINES*size * 3 / 100, LINES*size * 3 / 100, "黑体");
	outtextxy(LINES*size * 20 / 100, COLS*size * 10 / 100, "双路A*寻路展示");
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
void AddNode(Point point, RouteNode * father, int QR_MODE)
{
	RouteNode * p = CreateNode();
	p->point.x = point.x;
	p->point.y = point.y;
	p->father = father;
	if (QR_MODE == QR_START)
	{
		QueueRouteStart.rear->next = p;
		QueueRouteStart.rear = p;
	}
	else if (QR_MODE == QR_END)
	{
		QueueRouteEnd.rear->next = p;
		QueueRouteEnd.rear = p;
	}
	
}
void FreeQueue( int QR_MODE)
{
	RouteNode * p = NULL, *q=NULL;
	if (QR_MODE==QR_START)
		p=QueueRouteStart.head ;
	else if (QR_MODE==QR_END)
		p = QueueRouteEnd.head;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
	if (QR_MODE == QR_START)
	{
		QueueRouteStart.head = NULL;
		QueueRouteStart.rear = NULL;
		QueueRouteStart.present = NULL;
	}
	else if (QR_MODE == QR_END)
	{
		QueueRouteEnd.head = NULL;
		QueueRouteEnd.rear = NULL;
		QueueRouteEnd.present = NULL;
	}
	
}