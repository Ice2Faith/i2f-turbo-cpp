// �͸���õ�Ta.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "�͸���õ�Ta.h"
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
HWND hWnd;//ȫ�ִ��ھ��
bool SetSystemVolum(float volume)
{
	CoInitialize(0);
	HRESULT hr;
	//��ȡ�豸ö����
	IMMDeviceEnumerator* pDeviceEnumerator = 0;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
	if (FAILED(hr)) return false;
	//��ȡĬ�ϲ����豸
	IMMDevice* pDevice = 0;
	hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
	if (FAILED(hr)) return false;
	//��ȡ����������
	IAudioEndpointVolume* pAudioEndpointVolume = 0;
	hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pAudioEndpointVolume);
	if (FAILED(hr)) return false;

	//����ϵͳ��������
	hr = pAudioEndpointVolume->SetMasterVolumeLevelScalar(volume / 100.0f, &GUID_NULL);
	if (FAILED(hr)) return false;

	//�ͷ���Դ
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
		//��ȡ��Ļ��С
		int screenx = GetSystemMetrics(SM_CXSCREEN);
		int screeny = GetSystemMetrics(SM_CYSCREEN);

		//�̶����
		SetCursorPos(screenx / 2, screeny/2);
		//����͸��
		LONG wlong = GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED;
		SetWindowLong(hWnd, GWL_EXSTYLE, wlong);
		//����͸���
		SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 1, LWA_ALPHA);
		//������ǰ��
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, screenx, screeny, SWP_SHOWWINDOW);
		//�����߿�
		SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) - WS_CAPTION);
		////���ش���
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

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������: 
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

 	// TODO:  �ڴ˷��ô��롣
	srand((unsigned int)time(NULL));
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TA));
	
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LoopPlayer, NULL, NULL, NULL);
	// ����Ϣѭ��: 
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
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
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
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{


   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

  /* hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);*/

   //���ڷ������󻯣�����С�����޹رմ��ڣ���С320*240
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
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��: 
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
		// TODO:  �ڴ���������ͼ����...
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

// �����ڡ������Ϣ�������
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
