// ��Ļ��-��̨.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "��Ļ��-��̨.h"

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
	MSG msg;
	HACCEL hAccelTable;
	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CLASSNAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));
	srand((unsigned int)time(NULL));
	
	// ����Ϣѭ��: 
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
//��ʱ���ص�����
VOID CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	//MessageBox(NULL,L"��ʱ��",L"Tips",MB_OK);
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
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
   //��ȡ��Ļ��С
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
   //����͸��
   LONG wlong = GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED;
   SetWindowLong(hWnd, GWL_EXSTYLE, wlong);
   //��͸���
   SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 0, LWA_COLORKEY);

   //������ǰ��
   SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, screenx, screeny, SWP_SHOWWINDOW);

   //�����߿�
   SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) - WS_CAPTION);
   
   for (int i = 0; i < 10; i++)
   {
	   MsgText mtext;
	   lstrcpy(mtext.msg, L"��Ļ��-��̨ ������");
	   mtext.x = rand() % screenx/2+screenx/2;
	   mtext.y = rand() % screeny;
	   ZeroMemory(&mtext.font, sizeof(LOGFONT));
	   mtext.font.lfCharSet = GB2312_CHARSET;
	   mtext.font.lfHeight = -rand()%75+5; //��������Ĵ�С
	   mtext.color = RGB(rand()%255,rand()%255,rand()%255);
	   mtext.speed = 3;
	   MsgVector.push_back(mtext);
   }

   SetTimer(hWnd, ID_TIMER_SPEED, 30, &TimerProc);
   return TRUE;
}
//��ʾ����
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
