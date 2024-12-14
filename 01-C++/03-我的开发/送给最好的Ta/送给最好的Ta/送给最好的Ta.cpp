// 送给最好的Ta.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "送给最好的Ta.h"
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include"resource.h"

#include<mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>

#define MAX_LOADSTRING 100
HWND hWnd;//全局窗口句柄
bool SetSystemVolum(float volume)
{
	CoInitialize(0);
	HRESULT hr;
	//获取设备枚举器
	IMMDeviceEnumerator* pDeviceEnumerator = 0;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
	if (FAILED(hr)) return false;
	//获取默认播放设备
	IMMDevice* pDevice = 0;
	hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
	if (FAILED(hr)) return false;
	//获取播放器音量
	IAudioEndpointVolume* pAudioEndpointVolume = 0;
	hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pAudioEndpointVolume);
	if (FAILED(hr)) return false;

	//设置系统音量控制
	hr = pAudioEndpointVolume->SetMasterVolumeLevelScalar(volume / 100.0f, &GUID_NULL);
	if (FAILED(hr)) return false;

	//释放资源
	if (pAudioEndpointVolume) pAudioEndpointVolume->Release();
	if (pDevice) pDevice->Release();
	if (pDeviceEnumerator) pDeviceEnumerator->Release();
	CoUninitialize();
	return true;
}
void LoopPlayer()
{
	keybd_event(VK_LMENU, 0, 0, 0);
	keybd_event(VK_TAB, 0, 0, 0);
	keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	srand((unsigned int)time(NULL));
	int MusicID[] = { IDR_WAVE_APOLOGIZE,IDR_WAVE_AREUWITHME, IDR_WAVE_KAWAIISTEP, IDR_WAVE_TIME, IDR_WAVE_VISION, IDR_WAVE_VIVA, IDR_WAVE_SEX };
	PlaySound((LPCTSTR)MusicID[rand() % 6], NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
	float pvolum = 62.8;
	bool addvol = true;
	long beft = GetTickCount();
	int presstimes = 0;
	while (true)
	{
		long nowt = GetTickCount();
		if (nowt - beft > (60+rand()%34-17) * 1000)
		{
			beft = nowt;
			PlaySound((LPCTSTR)MusicID[rand() % 6], NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
		}
		//获取屏幕大小
		int screenx = GetSystemMetrics(SM_CXSCREEN);
		int screeny = GetSystemMetrics(SM_CYSCREEN);

		//固定鼠标
		SetCursorPos(screenx / 2, screeny/2);
		//窗口透明
		LONG wlong = GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED;
		SetWindowLong(hWnd, GWL_EXSTYLE, wlong);
		//不穿透点击
		SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 1, LWA_ALPHA);
		//窗口最前端
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, screenx, screeny, SWP_SHOWWINDOW);
		//消除边框
		SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) - WS_CAPTION);
		////隐藏窗口
		//ShowWindow(hWnd, SW_HIDE);
		SetForegroundWindow(hWnd);
		SetActiveWindow(hWnd);
		SetSystemVolum(pvolum);
		if (addvol == true && pvolum < 87)
			pvolum += (rand()%9+1.0)/10;
		else
			addvol = false;
		if (addvol == false && pvolum > 37)
			pvolum -= (rand() % 9 + 1.0) / 10;
		else
			addvol = true;
		if (presstimes%3 == 0)
		{
			keybd_event(VK_CONTROL, 0, 0, 0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			if (presstimes == 3)
			{
				keybd_event(VK_NUMLOCK, 0, 0, 0);
				keybd_event(VK_NUMLOCK, 0, KEYEVENTF_KEYUP, 0);
			}
			keybd_event(VK_LWIN, 0, 0, 0);
			keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
			if (presstimes == 6)
			{
				keybd_event(VK_CAPITAL, 0, 0, 0);
				keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
			}
			keybd_event(VK_LMENU, 0, 0, 0);
			keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
			if (presstimes == 0)
			{
				keybd_event(VK_SCROLL, 0, 0, 0);
				keybd_event(VK_SCROLL, 0, KEYEVENTF_KEYUP, 0);
			}
		}
		keybd_event(VK_ESCAPE, 0, 0, 0);
		keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
		presstimes = (presstimes + 1) % 9;
		Sleep(30);
	}
	
}

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
	srand((unsigned int)time(NULL));
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TA));
	
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LoopPlayer, NULL, NULL, NULL);
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TA));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_TA);
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


   hInst = hInstance; // 将实例句柄存储在全局变量中

  /* hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);*/

   //窗口风格：无最大化，无最小化，无关闭窗口，大小320*240
   hWnd = CreateWindow(szWindowClass, szTitle, 
	  WS_OVERLAPPED  | WS_THICKFRAME,
	   CW_USEDEFAULT, 0, 320, 240, NULL, NULL, hInstance, NULL);

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
	case WM_KEYDOWN:
	case WM_QUIT:
	case WM_CLOSE:
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
		//PostQuitMessage(0);
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
