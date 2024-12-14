// FPGGame.cpp : ����Ӧ�ó������ڵ㡣
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

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

int RoundX=10, RoundY=10,RoundR=10;
int FoodX = rand() % WINDOW_WIDTH, FoodY = rand() % WINDOW_HEIGHT, FoodR = 10;

// �˴���ģ���а����ĺ�����ǰ������: 
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

 	// TODO:  �ڴ˷��ô��롣
	srand((unsigned int)time(NULL));
	FoodX = rand() % WINDOW_WIDTH, FoodY = rand() % WINDOW_HEIGHT;
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FPGGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FPGGAME));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FPGGAME));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_FPGGAME);
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
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
	InitGame(hWnd);
	switch (message)
	{
	case WM_KEYDOWN:
		MoveRound(wParam);
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

void InitGame(HWND hwnd)
{
	HDC hdc, mdc, bdc;		//���������
	hdc = GetDC(hwnd);		//��ȡ��ʾ����ͼ�豸
	mdc = CreateCompatibleDC(hdc);		//�������ͼ�����ݵ��ڴ滺��
	bdc = CreateCompatibleDC(hdc);
	HBITMAP vcantimg,bgimg;		//������λͼ�ͱ���ͼƬ
	vcantimg = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	bgimg = (HBITMAP)LoadImage(NULL, L"bgimg.bmp", IMAGE_BITMAP, WINDOW_WIDTH, WINDOW_HEIGHT,LR_LOADFROMFILE);	//���뱳��ͼƬ
	SelectObject(mdc, vcantimg);	//��ʼ��mdc
	SetBkMode(bdc, TRANSPARENT);	//bdc���ֱ���͸����

	SelectObject(bdc, vcantimg);	//��ʼ��bdc
	SelectObject(bdc, bgimg);		//ѡ��λͼ��bdc
	RECT rect = { 0, 0, 255, 25 };
	DrawText(bdc, L"�������ͼ", lstrlenW(L"�������ͼ"), &rect, DT_SINGLELINE | DT_LEFT|DT_END_ELLIPSIS);

	Ellipse(bdc, RoundX-RoundR, RoundY-RoundR, RoundX+RoundR, RoundY+RoundR);
	Ellipse(bdc, FoodX - FoodR, FoodY - FoodR, FoodX + FoodR, FoodY + FoodR);
	BitBlt(mdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, bdc, 0, 0, SRCCOPY);		//��bdc,0,0λ�õ�ͼƬѡ��mdc,0,0��
	
	
	
	
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