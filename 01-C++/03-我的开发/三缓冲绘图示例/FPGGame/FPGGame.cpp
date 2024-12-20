// FPGGame.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "FPGGame.h"
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define DISTANCE(x1,y1,x2,y2) (sqrt((double)((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))))
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

int RoundX=10, RoundY=10,RoundR=10;
int FoodX = rand() % WINDOW_WIDTH, FoodY = rand() % WINDOW_HEIGHT, FoodR = 10;

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void InitGame(HWND hwnd);
void MoveRound(WPARAM wParam);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  在此放置代码。
	srand((unsigned int)time(NULL));
	FoodX = rand() % WINDOW_WIDTH, FoodY = rand() % WINDOW_HEIGHT;
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FPGGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FPGGAME));

	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FPGGAME));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_FPGGAME);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, WINDOW_WIDTH+15, WINDOW_HEIGHT+38, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
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
	InitGame(hWnd);
	switch (message)
	{
	case WM_KEYDOWN:
		MoveRound(wParam);
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
		
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
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

void InitGame(HWND hwnd)
{
	HDC hdc, mdc, bdc;		//三缓冲机制
	hdc = GetDC(hwnd);		//获取显示区绘图设备
	mdc = CreateCompatibleDC(hdc);		//创建与绘图区兼容的内存缓冲
	bdc = CreateCompatibleDC(hdc);
	HBITMAP vcantimg,bgimg;		//创建空位图和背景图片
	vcantimg = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	bgimg = (HBITMAP)LoadImage(NULL, L"bgimg.bmp", IMAGE_BITMAP, WINDOW_WIDTH, WINDOW_HEIGHT,LR_LOADFROMFILE);	//载入背景图片
	SelectObject(mdc, vcantimg);	//初始化mdc
	SetBkMode(bdc, TRANSPARENT);	//bdc文字背景透明化

	SelectObject(bdc, vcantimg);	//初始化bdc
	SelectObject(bdc, bgimg);		//选中位图进bdc
	RECT rect = { 0, 0, 255, 25 };
	DrawText(bdc, L"三缓冲绘图", lstrlenW(L"三缓冲绘图"), &rect, DT_SINGLELINE | DT_LEFT|DT_END_ELLIPSIS);

	Ellipse(bdc, RoundX-RoundR, RoundY-RoundR, RoundX+RoundR, RoundY+RoundR);
	Ellipse(bdc, FoodX - FoodR, FoodY - FoodR, FoodX + FoodR, FoodY + FoodR);
	BitBlt(mdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, bdc, 0, 0, SRCCOPY);		//将bdc,0,0位置的图片选入mdc,0,0处
	
	
	
	
	BitBlt(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, mdc, 0, 0, SRCCOPY);
	DeleteDC(bdc);
	DeleteDC(mdc);
	DeleteDC(hdc);
	ReleaseDC(hwnd,hdc);
	ReleaseDC(NULL, mdc);
	ReleaseDC(NULL, bdc);

}

void MoveRound(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_UP:
		if (RoundY>0+RoundR)
		RoundY-=5;
		break;
	case VK_DOWN:
		if (RoundY<WINDOW_HEIGHT - RoundR)
			RoundY += 5;
		break;
	case VK_LEFT:
		if (RoundX>0 + RoundR)
			RoundX -= 5;
		break;
	case VK_RIGHT:
		if (RoundX<WINDOW_WIDTH - RoundR)
			RoundX += 5;
		break;
	default:
		break;
	}
	if (DISTANCE(RoundX, RoundY, FoodX, FoodY) < RoundR + FoodR)
	{
		FoodX = rand() % WINDOW_WIDTH, FoodY = rand() % WINDOW_HEIGHT;
		if (RoundR<80)
		RoundR += 1;
	}
}