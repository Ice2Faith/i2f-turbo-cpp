/** Name: 上升粒子特效 */
#include<iostream>
#include<fstream>
#include<string>
#include<graphics.h>
#include<windows.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
using namespace std;
#define MAXLOAD 2048
const double PI = 3.1414526;
int SX;
int SY;
int Num;
string wordsSum[MAXLOAD];
int wordsLen;
enum RunMode{ RM_Center, RM_Up, RM_Down, RM_Left, RM_Right };
RunMode RunningMode = RM_Up;
typedef struct node
{
	int x;
	int y;
	int r;
	int g;
	int b;
	float speed;
	double direct;
	string str;
	struct node * next;
}Words;
Words * words;


Words * CreateWords()
{
	Words * p = new Words;
	p->next = NULL;
	p->str = wordsSum[rand() % wordsLen];
	switch (RunningMode)
	{
	case RM_Center:
		p->y = SY / 2;
		p->x = SX / 2 - (p->str.length()) / 2;
		break;
	case RM_Up:
		p->x = rand() % SX;
		p->y = SY;
		break;
	case RM_Down:
		p->x = rand() % SX;
		p->y = 0;
		break;
	case RM_Left:
		p->x = SX;
		p->y = rand() % SY;
		break;
	case RM_Right:
		p->x = 0;
		p->y = rand() % SY;
		break;
	}
	p->r = rand() % 155 + 100;
	p -> g = rand() % 155 + 100;
	p->b = rand() % 155 + 100;
	p->direct = atan2(PI*(rand() % 1000) - 500 * PI, PI*(rand() % 1000) - 500*PI);
	p->speed = rand() % 10 + 1;
	return p;
}
void AddWords()
{
	Words * p = CreateWords();
	p->next = words->next;
	words->next = p;
}
void ShowWords()
{
	BeginBatchDraw();
	cleardevice();
	int count = 0;
	Words * tp = words->next;
	while (tp)
	{
		settextcolor(RGB(tp->r,tp->g,tp->b));
		outtextxy(tp->x-(tp->str.length())/2,tp->y,tp->str.c_str());
		count++;
		tp = tp->next;
	}
	char cmode[6][10] = { "RM_Center", "RM_Up", "RM_Down", "RM_Left", "RM_Right" };
	char tips[256] = { 0 };
	sprintf(tips, "Sum: %6d   Level: %3d Mode: %s\0", count, Num,cmode[RunningMode]);
	outtextxy(0, 0, tips);
	EndBatchDraw();
}
void MoveWords()
{
	Words * tp = words->next;
	while (tp)
	{
		switch (RunningMode)
		{
		case RM_Center:
		{
			int bkx = tp->x;
			int bky = tp->y;
			tp->x += tp->speed*(sin(tp->direct));
			tp->y += tp->speed*(cos(tp->direct));
			if (tp->x == bkx && tp->y == bky)
				tp->direct = atan2(PI*(rand() % 1000) - 500 * PI, PI*(rand() % 1000) - 500 * PI);
		}
			break;
		case RM_Up:
			tp->y -= tp->speed;
			break;
		case RM_Down:
			tp->y += tp->speed;
			break;
		case RM_Left:
			tp->x -= tp->speed;
			break;
		case RM_Right:
			tp->x += tp->speed;
			break;
		}
		tp = tp->next;
	}
}
void RemoveDead()
{
	Words * fp = words;
	Words * tp = words->next;
	int cmx = -1000;
	int cmy = -100;
	if (RunningMode == RM_Center)
	{
		cmy = 0;
	}
	while (tp)
	{
		if (tp->x<=cmx || tp->x>=SX ||
			tp->y<=cmy || tp->y>=SY)
		{
			fp->next = tp->next;
			delete tp;
			tp = fp->next;
		}
		else
		{
			fp = fp->next;
			tp = tp->next;
		}
		
	}
}
void RemoveOthSpace(char * str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	if (i>0)
	i--;
	while (str[i] == ' ' || str[i] == '\t')
	{
		i--;
		if (i == -1)
			break;
	}
	str[i + 1] = 0;
	int len = i + 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
	{
		i++;
	}
	int j = 0;
	while (str[i])
	{
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = 0;
}
void GetWords()
{
	string filename("DisplayWords.txt");
	fstream fpath("WordsPath.txt", ios_base::in);
	if (!fpath)
	{
		fpath.open("WordsPath.txt", ios_base::out);
		fpath << endl;
		fpath << endl;
		fpath << "---------------------------------" << endl;
		fpath << "请将词条文件名（路径）放在第一行" << endl;
		fpath << "请将运行模式放到第二行（模式：Center/Up/Down/Right/Left/(缺省：Random)）" << endl;
		fpath << "词条按照行进行分割" << endl;
		fpath.close();
		exit(0);
	}
	char temp[2048] = { 0 };
	fpath.getline(temp, 1024 - 1);
	RemoveOthSpace(temp);
	filename = temp;
	if (filename.length() == 0)
		exit(0);
	string mode;
	fpath.getline(temp, 20);
	RemoveOthSpace(temp);
	mode = temp;
	for (int i = 0; i < mode.length(); i++)
	{
		if (mode[i] >= 'a'&&mode[i] <= 'z')
		{
			mode[i] &= ~32;
		}
	}
	if (mode == "CENTER")
	{
		RunningMode = RM_Center;
	}
	else if (mode == "UP")
	{
		RunningMode = RM_Up;
	}
	else if (mode == "DOWN")
	{
		RunningMode = RM_Down;
	}
	else if (mode == "LEFT")
	{
		RunningMode = RM_Left;
	}
	else if (mode == "RIGHT")
	{
		RunningMode = RM_Right;
	}
	else
	{
		RunningMode = RunMode(rand() % 5);
	}
	fpath.close();
	fstream fin(filename,ios_base::in);
	if (!fin)
	{
		exit(0);
	}
	wordsLen = 0;
	while (true)
	{
		fin.getline(temp, 1024 - 1);
		RemoveOthSpace(temp);
		wordsSum[wordsLen]=temp;
		if (wordsSum[wordsLen].length())
		{
			wordsLen++;
		}
		if (wordsLen == MAXLOAD - 1)
			break;
		if (fin.eof())
			break;
	}
	fin.close();

}
void InitSoftWare()
{
	SX = GetSystemMetrics(SM_CXSCREEN);
	SY = GetSystemMetrics(SM_CYSCREEN);
	Num = 1;
	srand((unsigned int)time(NULL));
	wordsLen = 0;
	GetWords();
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

	words = CreateWords();
	setbkmode(TRANSPARENT);
	settextstyle(0, SY / 100,"宋体");
}
int main(int argc, char * argv[])
{
	InitSoftWare();
	long ptime = GetTickCount();
	long btime = ptime;
	long cbt = ptime;
	long cnt = ptime;
	while (true)
	{
		ptime = GetTickCount();
		cnt = ptime;
		if (ptime - btime > 90)
		{
			for (int i = 0; i < Num; i++)
				AddWords();
			btime = ptime;
		}
		ShowWords();
		MoveWords();
		RemoveDead();
		if (cnt - cbt>100)
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				Num++;
				if (Num > 50)
					Num = 50;
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				Num--;
				if (Num < 1)
					Num = 1;
			}
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				int pmode = RunningMode-1;
				if (pmode == -1)
					pmode = 4;
				RunningMode = (RunMode)pmode;
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				int pmode = RunningMode + 1;
				if (pmode == 5)
					pmode = 0;
				RunningMode = (RunMode)pmode;
			}
			cbt = cnt;
		}
		
		Sleep(10);
	}
	return 0;
}