#ifndef _GAMEKEYTOOL_H_
#define _GAMEKEYTOOL_H_
/*Using on Vs code and EasyX*/
#if 1
#define SRAND srand((unsigned)time(NULL))	/*Quick set up seed*/
#define RAND(NUM) (rand() % NUM)	/*Get a random num between (0)-(NUM-1)*/
#define RANDBETWEEN(A,B) (rand()%(B-A+1)+A)	/*Get a random num between (A)-(B)*/
#endif 1

#if 1
#define UntilGet(A)	while(_getch()!=A)	/*until get a char is A to cotinue*/
#endif 1

#if 1
#define USESTD using namespace std		/*Quick set up namespace for c++*/
#define Percent(NUM) (NUM/100.0)	/*Quick calculated percent*/
#define CMAIN int main(int argc,char * argv[])	/*Quick set up std ascii c main*/
#define UMAIN int wmain(int argc, wchar_t *argv[]) /*Quick set up unicode c main*/
#define BETWEEN(C,A,B) (C>=A&&C<=B)	/*C is Between A to B*/
#endif 1

#if 1
void Wchar_t2Char(wchar_t Wchar[], char Char[])
{
	int size = WideCharToMultiByte(CP_ACP, 0, Wchar, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, Wchar, -1, Char, size, NULL, NULL);
}
void Char2Wchar_t(char Char[], wchar_t Wchar[])
{
	int size = MultiByteToWideChar(CP_ACP, 0, Char, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, Char, -1, Wchar, size);
}
#endif 1

#if 0
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib");
	mciSendString("open bgm.mp3",0,0,0);
	mciSendString("play bgm.mp3", 0, 0, 0);
#endif 0
/**
*	this function will get keybord and mouse info
*	usually using on game dev
*	seed out by key and msg
*	using such as:
*		int m_direct = 0;
*		MOUSEMSG m_msg;
*		GetDirectCheckInfo(&m_direct,&m_msg);
*		if (m_direct&CMD_UP)
*		{	
*			//do sth when click up	
*		}
*		if (m_direct&CMD_DOWN)
*		//....
*/
#if 1
#define GPrint(X,Y,Z) outtextxy(X,Y,Z)	/*Z is a string*/
#define IsKeyDown(KEY) (GetAsyncKeyState(KEY) & 0x8000)	/*Will return is down of this key*/
enum Direct{ CMD_UP = 1, CMD_LEFT = 2, CMD_DOWN = 4, CMD_RIGHT = 8 };
void GetDirectCheckInfo(int * key, MOUSEMSG * msg)
{
	while (MouseHit())
	{
		*msg = GetMouseMsg();
	}
	*key = 0;
	if (IsKeyDown(VK_UP)	|| IsKeyDown('W')	|| IsKeyDown(VK_NUMPAD8) )
		*key |= CMD_UP;
	if (IsKeyDown(VK_LEFT)	|| IsKeyDown('A')	|| IsKeyDown(VK_NUMPAD4) )
		*key |= CMD_LEFT;
	if (IsKeyDown(VK_DOWN)	|| IsKeyDown('S')	|| IsKeyDown(VK_NUMPAD5) )
		*key |= CMD_DOWN;
	if (IsKeyDown(VK_RIGHT)	|| IsKeyDown('D')	|| IsKeyDown(VK_NUMPAD6) )
		*key |= CMD_RIGHT;
}
#endif 1

#if 0
#include<iostream>
#include<windows.h>
#include<graphics.h> 
#include<time.h>
#include<conio.h>
//最前端半透明
void SetMyWindowStyle(HWND hwnd)
{
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
	SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 180, LWA_ALPHA);
}
//获取屏幕大小
int screenx = GetSystemMetrics(SM_CXSCREEN);
int screeny = GetSystemMetrics(SM_CYSCREEN);

//窗口最大化
HWND hwnd = initgraph(screenx, screeny, SHOWCONSOLE);

//窗口透明
LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
//穿透点击
SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
//不穿透点击
SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 1, LWA_ALPHA);

//窗口最前端
SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, screenx, screeny, SWP_SHOWWINDOW);

//消除边框
SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);

#endif 0

#if 0
	DWORD ms=GetTickCount();

	BeginBatchDraw();
	FlushBatchDraw();
	EndBatchDraw();

	outtextxy(point.x,point.y,"");
	//row is y,column is x
	initgraph(width, height, [SHOWCONSOLE]);
	closegraph();
#endif 0

#endif _GAMEKEYTOOL_H_