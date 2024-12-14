// 弹幕姬-后台.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "弹幕姬-后台.h"

#define MAX_LOADSTRING 100

#include"FooTextMsg.h"
#include<time.h>
#include<stdlib.h>
#include<vector>
#include<iterator>
using namespace std;
#define ID_TIMER_SPEED 0x101

typedef struct
{
	TCHAR msg[MAXLENGTH];
	LOGFONT font;
	COLORREF color;
	int x;
	int y;
	int speed;
}MsgText;
std::vector<MsgText> MsgVector;
// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  在此放置代码。
	MSG msg;
	HACCEL hAccelTable;
	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CLASSNAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));
	srand((unsigned int)time(NULL));
	
	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		/*if (msg.message == WM_TIMER)
		{
			DispatchMessage(&msg);
		}*/
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	LOGBRUSH lb;
	lb.lbColor = 0x000000;
	lb.lbHatch = 0;
	lb.lbStyle = 0;
	HBRUSH brush = CreateBrushIndirect(&lb);
	wcex.hbrBackground = brush;// (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCE(IDC_MY);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
//定时器回调函数
VOID CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	//MessageBox(NULL,L"定时器",L"Tips",MB_OK);
	if (MsgVector.size() > 0)
	{
		while (MsgVector.size() > 0)
		{
			if (MsgVector[0].x < -1000)
			{
				MsgVector.erase(MsgVector.begin());
			}
			else
				break;
		}
		for (vector<MsgText>::iterator it = MsgVector.begin(); it != MsgVector.end(); it++)
		{
			(*it).x -= (*it).speed;
		}
		InvalidateRect(hWnd, NULL, TRUE);
	}

}
//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中
   //获取屏幕大小
   int screenx = GetSystemMetrics(SM_CXSCREEN);
   int screeny = GetSystemMetrics(SM_CYSCREEN);
   hWnd = CreateWindowEx(WS_EX_TOOLWINDOW,
	   szWindowClass,
	   szTitle, 
	   WS_OVERLAPPED | WS_THICKFRAME | WS_POPUP ,
      0, 0, 
	  screenx, screeny,
	  NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   //窗口透明
   LONG wlong = GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED;
   SetWindowLong(hWnd, GWL_EXSTYLE, wlong);
   //穿透点击
   SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 0, LWA_COLORKEY);

   //窗口最前端
   SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, screenx, screeny, SWP_SHOWWINDOW);

   //消除边框
   SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) - WS_CAPTION);
   
   for (int i = 0; i < 10; i++)
   {
	   MsgText mtext;
	   lstrcpy(mtext.msg, L"弹幕姬-后台 已启动");
	   mtext.x = rand() % screenx/2+screenx/2;
	   mtext.y = rand() % screeny;
	   ZeroMemory(&mtext.font, sizeof(LOGFONT));
	   mtext.font.lfCharSet = GB2312_CHARSET;
	   mtext.font.lfHeight = -rand()%75+5; //设置字体的大小
	   mtext.color = RGB(rand()%255,rand()%255,rand()%255);
	   mtext.speed = 3;
	   MsgVector.push_back(mtext);
   }

   SetTimer(hWnd, ID_TIMER_SPEED, 30, &TimerProc);
   return TRUE;
}
//显示函数
void ShowMessageText(HWND hWnd,HDC hdc)
{
	RECT rect;
	GetClientRect(hWnd,&rect);
	Rectangle(hdc,-2,-2,rect.right-rect.left+2,rect.bottom-rect.top+2);
	for (vector<MsgText>::iterator it = MsgVector.begin(); it != MsgVector.end(); it++)
	{
		HFONT font = CreateFontIndirect(&(*it).font);
		SelectObject(hdc,font);
		SetTextColor(hdc,(*it).color);
		TextOut(hdc, (*it).x, (*it).y, (*it).msg, lstrlen((*it).msg));
		DeleteObject(font);
	}
}
void AddMessageText(HWND hWnd, LPARAM lParam)
{
	PCOPYDATASTRUCT pcp = (PCOPYDATASTRUCT)lParam;
	if (pcp->dwData == WM_TFM_ADDTEXT)
	{

		RECT rect;
		GetClientRect(hWnd, &rect);
		MsgBody* mb=(MsgBody*)pcp->lpData;
		MsgText mtext;
		lstrcpy(mtext.msg, mb->text);
		mtext.x = rect.right - rect.left;
		mtext.y = rand() % (rect.bottom - rect.top);
		ZeroMemory(&mtext.font, sizeof(LOGFONT));
		mtext.font.lfCharSet = GB2312_CHARSET;
		//mtext.font.lfHeight = -rand() % 75 + 5;
		mtext.font.lfHeight = -mb->size;
		
		//mtext.color = RGB(rand() % 255, rand() % 255, rand() % 255);
		mtext.color = mb->color;

		//mtext.speed = 3;
		mtext.speed = mb->speed;
		MsgVector.push_back(mtext);
	}
	
}
//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	
	switch (message)
	{
	case WM_COPYDATA:
		AddMessageText(hWnd,lParam);
		break;
	case WM_TFM_OPEN:
		KillTimer(hWnd, ID_TIMER_SPEED);
		SetTimer(hWnd, ID_TIMER_SPEED, 30, &TimerProc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_TFM_CLOSE:
		KillTimer(hWnd, ID_TIMER_SPEED);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_TFM_CLEAR:
		MsgVector.clear();
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_TFM_SHOW:
		ShowWindow(hWnd,SW_SHOW);
		break;
	case WM_TFM_HIDE:
		ShowWindow(hWnd, SW_HIDE);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  在此添加任意绘图代码...
		SetBkMode(hdc,TRANSPARENT);
		ShowMessageText(hWnd,hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd,ID_TIMER_SPEED);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
