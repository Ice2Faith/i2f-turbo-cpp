// 13-Exe图标更改替换.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "13-Exe图标更改替换.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
// “输入”框的消息处理程序。
INT_PTR CALLBACK InputBox(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL SetExeIcon(char * resFileName, char * destFileName);

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
	LoadString(hInstance, IDC_MY13EXE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY13EXE));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_SELF));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY13EXE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON_SELF));

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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

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
		case ID_ICON_REPLACE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DLG_INPUTBOX), hWnd, InputBox);
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
// “输入”框的消息处理程序。
INT_PTR CALLBACK InputBox(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
					 char srcName[1024] = { 0 };
					 char drtName[1024] = { 0 };
					 GetDlgItemTextA(hDlg, IDC_EDIT_SRCNAME, srcName, 1024);
					 GetDlgItemTextA(hDlg, IDC_EDIT_DETNAME, drtName, 1024);
					 BOOL ret=SetExeIcon(srcName, drtName);
					 if (ret)
						 MessageBoxA(NULL, "图标替换成功！！，可能需要重启Explorer刷新缓存。", "操作提示", MB_OK);
					 else
						 MessageBoxA(NULL, "图标替换失败，请检查已选文件是否是exe文件！", "操作提示", MB_OK);
					 EndDialog(hDlg, LOWORD(wParam));
					 return (INT_PTR)TRUE;
		}
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		}
	}
	return (INT_PTR)FALSE;
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

///////////////////////////////////////////////////////
/*
	图标替换：
		用一个已有程序的图标去替换另一个程序的图标
		函数：BOOL SetExeIcon(char * resFileName, char * destFileName);
		函数具体查看下面的代码实现
	图标制作工具：
		Icofx3
	Shellcode:
		一段可执行的代码（数据），比如：x02 x5c x63 xf4
		也就是直接二进制编写可执行代码
	二进制查看工具：
		WinHex
	获取当前程序路径：
		char modelName[MAX_PATH];
		GetModuleFileName(NULL, modelName, MAX_PATH);
*/
//替换图标
BOOL SetRes(LPTSTR destFileName, LPTSTR szType, LPTSTR szName, LPVOID pdata, DWORD dataSize)
{
	//开始更新资源
	HANDLE handle = BeginUpdateResource(destFileName, FALSE);//TRUE时删除这个资源
	if(handle==NULL)
	{
		return FALSE;
	}
	//更新资源
	int ret = UpdateResource(handle, szType, szName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), pdata, dataSize);
	if (!ret)
		return FALSE;
	//结束更新
	EndUpdateResource(handle, FALSE);//TRUE时不进行任何操作，也就不会保存修改
	return TRUE;
}
//枚举资源回调函数
BOOL CALLBACK EnumResProc(HMODULE hmod, LPCTSTR szType, LPTSTR szName, LONG lParam)
{
	//查找资源
	HRSRC hres = FindResource(hmod, szName, RT_ICON);
	if (hres == NULL)
		return FALSE;
	//加载资源
	HGLOBAL hload = LoadResource(hmod, hres);
	if (hload == NULL)
		return FALSE;
	//锁定资源
	LPVOID pdata = LockResource(hload);
	if (pdata == NULL)
		return FALSE;
	//获取资源大小
	DWORD psize = SizeofResource(hmod, hres);
	//设置资源
	return SetRes((LPTSTR)lParam, RT_ICON, szName, pdata, psize);

}
//用一个程序的图标替换另一个程序的图标
BOOL SetExeIcon(char * resFileName, char * destFileName)
{
	//加载源文件
	HMODULE hmod=LoadLibrary(resFileName);
	if (hmod == NULL)
		return FALSE;
	//枚举资源ICON
	return EnumResourceNames(hmod, RT_ICON, EnumResProc, (long)destFileName);
}