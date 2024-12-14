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
int DDerec[4][2] =
{
	{ 0, 1 }, //right
	{ 1, 0 }, //down
	{ 0, -1 }, //left
	{ -1, 0 }, //up
};
typedef struct
{
	int value;
	int find;
	int derec;	//reference for DDerec
} HelpMap;
int Map[LINES][COLS] =
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 1, 0, 1, 1 },
	{ 1, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 1, 0, 1, 0, 1 },
	{ 1, 1, 1, 0, 0, 0, 0, 1, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};
HelpMap Hmap[LINES][COLS];
Point Cur = { 1, 1 }, Test = { 1, 1 }, End = { 8, 8 };
void InitEnveronment();
void DisplayMap();
void AutoRouter();
void TestMove(Point Test);

typedef struct node
{
	Point point;
	struct node * next;
} STEP;
STEP * Head = NULL;
void OverturnStack();
int StackIsEmpty();
void GetTop(Point * point);
void Pop(Point * point);
void Push(Point point);
void DisplayRoute();

int size = (GetSystemMetrics(SM_CYSCREEN)>GetSystemMetrics(SM_CXSCREEN) ? GetSystemMetrics(SM_CXSCREEN) : GetSystemMetrics(SM_CYSCREEN)) / 12;
IMAGE bgimage, wall, people,step,route,end;
void initialapp();
void SetMap();
HWND hwnd;
int _tmain(int argc, _TCHAR * argv[])
{
	hwnd=initgraph(LINES*size, COLS*size);
	initialapp();
	Head = (STEP *)malloc(sizeof(STEP));
	Head->next = NULL;
	srand((unsigned)time(NULL));
	InitEnveronment();
	AutoRouter();
	return 0;
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
}
void SetMap()
{
	putimage(0, 0, &bgimage);
	settextcolor(RGB(0, 255, 255));
	settextstyle(LINES*size * 3 / 100, LINES*size * 3 / 100, "黑体");
	outtextxy(LINES*size * 20 / 100, COLS*size * 10 / 100, "深度寻路展示");
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
	for (int i = 0; i<LINES; i++)
	{
		for (int j = 0; j<COLS; j++)
		{
			if (i == Cur.x&&j == Cur.y)
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
			 Cur.x = temp.x / size;
			 Cur.y = temp.y / size;
		 }
		 if (set == '4')
		 {
			 End.x = temp.x / size;
			 End.y = temp.y / size;
		 }
		
		BeginBatchDraw();
		putimage(0, 0, &bgimage);
		for (int i = 0; i<LINES; i++)
		{
			for (int j = 0; j<COLS; j++)
			{
				if (i == Cur.x&&j == Cur.y)
					putimage(j*size, i*size, &people);
				else if (i==End.x&&j==End.y)
					putimage(j*size, i*size, &end);
				else if (Map[i][j] == 1)
					putimage(j*size, i*size, &wall);
			}
		}
		EndBatchDraw();
	}
}

void AutoRouter()
{
	Hmap[Cur.x][Cur.y].find = 1;
	Push(Cur);
	int jmp = 0;
	while (1)
	{
		Test.x = Cur.x;
		Test.y = Cur.y;
		switch (Hmap[Cur.x][Cur.y].derec)
		{
		case 0:
			Hmap[Cur.x][Cur.y].derec++;
			Test.x += DDerec[0][0];
			Test.y += DDerec[0][1];
			TestMove(Test);
			break;
		case 1:
			Hmap[Cur.x][Cur.y].derec++;
			Test.x += DDerec[1][0];
			Test.y += DDerec[1][1];
			TestMove(Test);
			break;
		case 2:
			Hmap[Cur.x][Cur.y].derec++;
			Test.x += DDerec[2][0];
			Test.y += DDerec[2][1];
			TestMove(Test);
			break;
		case 3:
			Test.x += DDerec[3][0];
			Test.y += DDerec[3][1];
			TestMove(Test);
			if (Hmap[Cur.x][Cur.y].derec == 3)
			{
				GetTop(&Cur);
				Pop(&Test);
			}
			break;
		}
		DisplayMap();
		if (Cur.x == End.x&&Cur.y == End.y)
		{
			Push(Cur);
			//printf("Router Success!!\n");
			DisplayRoute();
			settextcolor(RGB(0, 120, 255));
			settextstyle(LINES*size * 5 / 100, LINES*size * 5 / 100, "黑体");
			outtextxy(LINES*size * 20 / 100, COLS*size / 2, "Success!!");
			break;
		}
		if (StackIsEmpty())
		{
			//printf("Router Failure!!\n");
			settextcolor(RGB(255, 120, 0));
			settextstyle(LINES*size * 5 / 100, LINES*size * 5 / 100, "黑体");
			outtextxy(LINES*size * 20 / 100, COLS*size/2, "Failure!!");
			break;
		}

		Sleep(100);
	}
	settextcolor(RGB(0, 255, 255));
	settextstyle(LINES*size*5/100,LINES*size*5/100,"黑体");
	outtextxy(LINES*size *20/100, COLS*size - LINES*size * 5 / 100, "Click 0 exit");
	char sel = '\0';
	while (sel != '0')
		sel = _getch();
}
void TestMove(Point Test)
{
	if (Hmap[Test.x][Test.y].find == 0 && Hmap[Test.x][Test.y].value == 0 && (Test.x >= 0 && Test.x<LINES) && (Test.y >= 0 && Test.y<COLS))
	{
		Push(Cur);
		//Cur入栈
		Hmap[Test.x][Test.y].find = 1;
		Cur.x = Test.x;
		Cur.y = Test.y;
	}
}
void InitEnveronment()
{
	for (int i = 0; i<LINES; i++)
	{
		for (int j = 0; j<COLS; j++)
		{
			Hmap[i][j].value = Map[i][j];
			Hmap[i][j].find = 0;
			Hmap[i][j].derec = 0;
		}
	}
}
void DisplayMap()
{
	BeginBatchDraw();
	putimage(0, 0, &bgimage);
	for (int i = 0; i<LINES; i++)
	{
		for (int j = 0; j<COLS; j++)
		{
			if (i == Cur.x&&j == Cur.y)
				putimage(j*size, i*size, &people);
			else if (i == End.x&&j == End.y)
				putimage(j*size, i*size, &end);
			else if (Hmap[i][j].value == 1)
				putimage(j*size, i*size, &wall);
		}
	}
	EndBatchDraw();
}
void DisplayRoute()
{
	BeginBatchDraw();
	OverturnStack();
	while (!StackIsEmpty())
	{
		Pop(&Test);
		Hmap[Test.x][Test.y].value = 9;
	}
	for (int i = 0; i<LINES; i++)
	{
		for (int j = 0; j<COLS; j++)
		{
			if (i == Cur.x&&j == Cur.y)
				putimage(j*size, i*size, &people);
			else if (Hmap[i][j].value == 9)
				putimage(j*size, i*size, &route);
			else if (Hmap[i][j].find == 1)
				putimage(j*size, i*size, &step);
			else if (Hmap[i][j].value == 1)
				putimage(j*size, i*size, &wall);
		}
	}
	EndBatchDraw();
}
//------------------------------------------
void Push(Point point)
{
	STEP * p = (STEP *)malloc(sizeof(STEP));
	p->next = NULL;
	p->point.x = point.x;
	p->point.y = point.y;
	p->next = Head->next;
	Head->next = p;
}
void Pop(Point * point)
{
	point->x = Head->next->point.x;
	point->y = Head->next->point.y;
	STEP * p = Head->next;
	Head->next = Head->next->next;
	free(p);
}
void GetTop(Point * point)
{
	point->x = Head->next->point.x;
	point->y = Head->next->point.y;
}
int StackIsEmpty()
{
	if (Head->next == NULL)
		return 1;
	return 0;
}
void OverturnStack()
{
	STEP *f = NULL, *p = Head->next;
	Head->next = NULL;
	while (p)
	{
		f = p;
		p = p->next;
		f->next = Head->next;
		Head->next = f;

	}
}
