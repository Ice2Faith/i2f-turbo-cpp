// Win32VideoWallpaper.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Win32VideoWallpaper.h"

#define MAX_LOADSTRING 100

#include<stdlib.h>
#include<time.h>
#include"VideoWallpaperHelper.h"
#include"PhysicalReflect.h"
using namespace PhysicalReflect;
using namespace std;
#include<math.h>
#include<deque>

class Ball{
public:
	double x;
	double y;
	double radius;
	COLORREF color;
	double speed;
	double direct;

	Ball(double x, double y, double radius){
		PI = 3.141592653549;
		this->x = x;
		this->y = y;
		this->radius = radius;
		randomArgs();
	}

	void randomArgs() {
		this->color = RGB(rand() % 255, rand() % 255, rand() % 255);
		this->speed = rand() % 19 + 1;
		this->direct = DirectionFromSize(rand() % 360 - 180, rand() % 360 - 180);
	}

	Ball & setArgs(double x, double y, double radius, int color, double speed, double direct){
		this->x = x;
		this->y = y;
		this->radius = radius;
		this->color = color;
		this->speed = speed;
		this->direct = direct;
		return *this;
	}
	static double DirectionFromSize(double height, double width){
		return atan2(width, height);
	}
	double AngleToRadian(double angle){
		return angle / 180.0*PI;
	}
private:
	double PI;
};
deque<Ball> allBalls = deque<Ball>();
int ballCount = 130;
int WinWidth = 1280;
int WinHeight = 720;

void InitAllBalls(){
	allBalls.clear();

	for (int i = 0; i< ballCount; i++){
		Ball ball = Ball(rand() % WinWidth,
			rand() % WinHeight,
			rand() % 45 + 5);
		allBalls.push_back(ball);
	}
}

void DrawAllBalls(HDC hdc){
	for (int i = 0; i< allBalls.size(); i++) {
		HBRUSH brush = CreateSolidBrush(allBalls[i].color);
		HGDIOBJ oldBrush=SelectObject(hdc,brush);
		Ellipse(hdc, allBalls[i].x - allBalls[i].radius, allBalls[i].y - allBalls[i].radius,
			allBalls[i].x + allBalls[i].radius, allBalls[i].y + allBalls[i].radius);

		DeleteObject(oldBrush);
	}
}

void MoveOrBounceBalls(){
	for (int i = 0; i < allBalls.size(); i++) {
		allBalls[i].x += allBalls[i].speed * sin(allBalls[i].direct);
		allBalls[i].y += allBalls[i].speed * cos(allBalls[i].direct);
		if (allBalls[i].x <= 0 || allBalls[i].x >= WinWidth
			|| allBalls[i].y <= 0 || allBalls[i].y >= WinHeight) {
			double faltRadian = 0;
			if (allBalls[i].x<0 || allBalls[i].x >= WinWidth){
				faltRadian = AngleToRadian(90);
			}
			allBalls[i].direct = getReflectRadian(allBalls[i].direct,
				faltRadian);
		}
	}
}

void CaptureMouseBalls(){
	POINT mousePoint = { 0 };
	GetCursorPos(&mousePoint);
	for (int i = 0; i< allBalls.size(); i++) {
		if (rand() % 100<5){
			allBalls[i].direct = (allBalls[i].direct + Ball::DirectionFromSize(mousePoint.y - allBalls[i].y, mousePoint.x - allBalls[i].x)) / 2.0;
		}

	}
}

#define ID_TIMER_FLUSH_DRAW 0x1001

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
	LoadString(hInstance, IDC_WIN32VIDEOWALLPAPER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32VIDEOWALLPAPER));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32VIDEOWALLPAPER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCE(IDC_WIN32VIDEOWALLPAPER);
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
      0, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   UpdateWindow(hWnd);
   HWND wallHwnd = GetDesktopWallpaperWorkerHwnd();
   if (wallHwnd != NULL){
	   SetParent(hWnd,wallHwnd);
   }
   ShowWindow(hWnd, SW_MAXIMIZE);
   RECT rect = {0};
   GetWindowRect(hWnd,&rect);
   WinWidth = rect.right - rect.left;
   WinHeight = rect.bottom - rect.top;


   //�����߿�
   SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) - WS_CAPTION);


   InitAllBalls();
   SetTimer(hWnd, ID_TIMER_FLUSH_DRAW, 30, NULL);
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
		DrawAllBalls(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		MoveOrBounceBalls();
		CaptureMouseBalls();
		InvalidateRect(hWnd,NULL,TRUE);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, ID_TIMER_FLUSH_DRAW);
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
