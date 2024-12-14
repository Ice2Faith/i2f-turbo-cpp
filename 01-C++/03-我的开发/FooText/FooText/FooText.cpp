#include<iostream>
#include<windows.h>
#include<graphics.h> 
#include<time.h>
#include<conio.h>
typedef struct
{
	int red;
	int green;
	int blue;
}RGBC;
typedef struct
{
	char text[256];
	int x;
	int y;
	int width;
	int height;
	int speed;
	RGBC color;
}Text;
typedef struct node
{
	Text word;
	struct node * next;
}TextList;

TextList * wordlist;
int haveinput;
int screenx;
int screeny;

void InitialEnvironment();
void EndRun();
int GetText();
void DisplayText();
TextList * CreateNode();
void InseartNode(TextList * p); 
void deleteNode(TextList * p);
void RemoveList();
int _tmain(int argc, _TCHAR * argv[])
{
	InitialEnvironment();
	//窗口最大化
	HWND hwnd = initgraph(screenx, screeny, SHOWCONSOLE);
	//窗口透明
	LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
	SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
	//窗口最前端
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, screenx, screeny, SWP_SHOWWINDOW);
	//消除边框
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	printf("发送弹幕:");
	BeginBatchDraw();
	while (true)
	{
		if (_kbhit())
		if (GetText() == 1)
			break;
		DisplayText();
		FlushBatchDraw();
		Sleep(3);	
		//cleardevice();
	}
	EndBatchDraw();
	RemoveList();
	return 0;
}
void InitialEnvironment()
{
	wordlist = NULL;
	wordlist = CreateNode();
	srand((unsigned)time(NULL));
	screenx = GetSystemMetrics(SM_CXSCREEN);
	screeny = GetSystemMetrics(SM_CYSCREEN);
	haveinput = 0;
	system("title 弹幕发送器 dev Ice2Faith");
	system("color f1");
	system("mode con cols=50");
	system("echo 输入/**/ 可以关闭程序");
}
int GetText()
{
	TextList *  p = CreateNode();
	gets_s(p->word.text);
	p->word.color.red = rand() % 256;
	p->word.color.green = rand() % 256;
	p->word.color.blue = rand() % 256;
	p->word.height = rand() % 100;
	p->word.width = rand() % 100;
	p->word.x = screenx - rand() % 100;
	p->word.y = rand() % screeny;
	haveinput = 1;
	InseartNode(p);
	printf("发送弹幕:");
	int isend = 1;
	char end[] = { "/**/" };
	for (int i = 0; i < 4; i++)
	{
		if (p->word.text[i] != end[i])
		{
			isend = 0;
			break;
		}
	}
	if (isend==1)
		return 1;
	return 0;

}
void DisplayText()
{
	TextList * p = wordlist->next, *father = wordlist;
	while (p)
	{
		settextstyle(p->word.height, p->word.width, "黑体");
		settextcolor(RGB(p->word.color.red, p->word.color.green, p->word.color.blue));
		outtextxy(p->word.x, p->word.y, p->word.text);
		p->word.x--;
		if (p->word.x < 0 - screenx)
			deleteNode(father);
		p = p->next;
		father = father->next;
	}
	
}
//----------------Link List-----------------------------------
void RemoveList()
{
	TextList * p = wordlist,* np;
	wordlist = NULL;
	while (p->next)
	{
		np = p->next;
		delete p;
		p = np;
	}
}
TextList * CreateNode()
{
	TextList * p = new TextList;
	p->next = NULL;
	return p;
}
void InseartNode(TextList * p)
{
	p->next = wordlist->next;
	wordlist->next = p;
}
void deleteNode(TextList * p)
{
	TextList * n = p;
	p->next = p->next->next;
	delete n->next;
}