// �����ػ���ͼ����.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "�����ػ���ͼ����.h"
#include<graphics.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#define MAX_LOADSTRING 100
/*
�����򼯳��˻��幦�ܺͲ����ػ����ܡ�
���幦�ܣ����м򵥵Ļ�ͼ�����ƻ�ͼ���򣬿�������Ļ��ʱ��ע��ע��
�����ػ����ܣ����ػ�������£���Ļ���һ�в�������ʧЧ�������̲���������Ч

HOOKǿ���ػ�
����ڳɹ�����������£���ô��ļ��̾ͻ������ˣ�ʲôҲ������
��ʱ����������ѡ��1.ǿ�ƹػ����� 2.����ȡ����ݼ�Ctrl+Shift+Alt+F2
��Ȼ���������ԣ���Win10�����£�Ctrl+Alt+Delete��Ȼ��Ч

����˵����
�󲿷ְ�������ȫ�ּ���������ֻ���ٲ�����Ҫ����ڲ���ʹ�ã�
ȫ�ּ����������������Щ�ӳ٣���ϵͳ�ȼ������ͻ����Ϊ�ǰ�������������ע��Ŀ�ݼ�
Win+Ctrl:����ҳ�棬����Ϊ��ͷ���˽�����Խ��л�ͼ��Ϊ��ͼҳ��
Ctrl+Shift+Alt+F1:��ʾ�����ز˵�
Ctrl+Shift+Alt+F2:�˳��ػ�ģʽ/����ҳ��
Ctrl+Shift+Alt+F3:�����ػ�ģʽ
Ctrl+Shift+Alt+F4:�����������У���Ҫ���´򿪳������ʹ����
Ctrl+����Ҽ�����ջ�ͼ����
Shift+����Ҽ��������λ����������
F6+L:��ջ�ͼ����
F6+C:����
F6+S:�����ͼ
F6+Q:�˳���ͼ
ע�⣺�����ڼ䣬ʹ�þ��λ��ƴ�С���⽫��Ϊ����ͼƬ������
����ʹ���������Ʋ�����Ӱ��
F6+F:��������
F6+M:������
F6+R:�������
F6+P:����͹���
F6+Z:�ȸ跭������Ӣ
F6+E:�ȸ跭��Ӣ����
F6+B:�򿪰ٶ���ҳ
F8+N:��������
F8+C:�ۺ�����
F8+P:�������
F8+F:��Դ����
F8+Shift+S:�����ػ�
F8+Shift+R:��������
F8+Shift+L:��������
F8+Shift+B:�����Ѹ����ı�
�����������ṩ����Զ���CMDָ�ָ�������·��� SELF_MIND_FILE_NAME ������ļ��У�
ÿһ�д���һ���Զ���ָ�����ο�cmdָ��ı�д
F8+Shift+1��
F8+Shift+2��
F8+Shift+3��
������ʾ��
ֻҪ�������У�������涼���Լ���ҳ�棨Win+Ctrl��
ֻ�н��뼤�������ܽ��л�ͼ�������ػ����˵�����/����
ֻ�н����ػ����˳��ػ��Ż���Ч

һ��ʹ�����̣�
����������Win+Ctrl�������
�����ػ����߻�ͼ��
�˳��ػ�����������ʹ��

F8+Shift+W:��󻯵�ǰ����
F8+Shift+D:��С����ǰ����
F8+Shift+X:�رյ�ǰ����
F8+Shift+Q:�ر�������ڣ����ڽض�ĳЩ������򸲸�ȫ�������û��޷�ʹ��

Shift+Cap+A-Z:ֱ�Ӵ�ָ���̷�����
*/
////////////////////////////////////////////////////////////////
#define SELF_MIND_FILE_NAME ".\\DeskDemoAppSelfMind.bat"
bool isCaptureMode = false;

void ClearDrawEnv(HWND hWnd);
RECT wndrect = { 0 };
HDC bdc;
HBITMAP bdimg;
void BuildBackgroundImg();
#define ID_TIMER_SPEED 0x0001
#define TIMER_SLEEP_MILLSEC 30
HMENU menu = NULL;
bool isMasked = true;
COLORREF transBgColor = 0x000000;
int screenx	=240 ;
int screeny	=240 ;
bool isLBtnDown = false;
bool isCtrlDown = false;
bool isShiftDown = false;
bool isAltDown = false;
bool isTabDown = false;
POINT befPoint = { 0 };
enum DrawType{DT_Empty,DT_Point,DT_Line,DT_CirLine,DT_Rectangle,DT_Elipese,DT_Arrow};
DrawType preDrawType = DT_CirLine;
enum ColorType{ CT_Red=0x0000ff, CT_Green=0x00ff00, CT_Blue=0xff0000, CT_Black=0x010101,CT_Weite=0xfefefe };
ColorType prePenColor = CT_Red;
COLORREF preBrushColor = transBgColor;
int prePenSize = 1;
int prePenStyle = PS_SOLID;
COLORREF preTextColor = 0xff7744;
int preTextSize = -50;

VOID CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);
void setBrush(HDC hdc, COLORREF color);
void setPen(HDC hdc,int style, COLORREF color, int width);
void setFont(HDC hdc, int size, COLORREF color);
void ShowMenu(HWND hwnd);
void Masked(HWND hwnd, bool mask);
void KeyDownProc(HWND hWnd, WPARAM wParam);
void KeyUpProc(HWND hWnd, WPARAM wParam);
void LBtnDownProc(HWND hWnd, LPARAM lParam);
void LBtnUpProc(HWND hWnd, LPARAM lParam);
void MouseMoveProc(HWND hWnd, LPARAM lParam);
void RBtnDownProc(HWND hWnd, LPARAM lParam);
BOOL CALLBACK InputBoxProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

IMAGE imgCapture;
RECT captureRect;
void captureScreenProc(HWND hWnd);
void exitCaptureProc(HWND hWnd);
void saveCaptureProc(HWND hWnd);
void copyDisplayImage2ClipbordProc(HWND hWnd);

void startCmdProc(HWND hWnd);
void startControlProc(HWND hWnd);
void startApplicationManageProc(HWND hWnd);
void startTranslateZhtoEnProc(HWND hWnd);
void startTranslateEntoZhProc(HWND hWnd);
void startBrowserSearchProc(HWND hWnd);

void searchNormalCombineProc(HWND hWnd);
void searchSiteCombineProc(HWND hWnd);
void searchProgramCombineProc(HWND hWnd);
void searchResourceCombineProc(HWND hWnd);

void startNowShutdownProc(HWND hWnd);
void startNowRebootProc(HWND hWnd);
void startNowLockScreenProc(HWND hWnd);
void startSearchClipboardProc(HWND hWnd);

void startSelfMindOneProc(HWND hWnd);
void startSelfMindTwoProc(HWND hWnd);
void startSelfMindThreeProc(HWND hWnd);

void startRegEditProc(HWND hWnd);
void startExplorerProc(HWND hWnd);
void startNotepadProc(HWND hWnd);
void startSnaptoolProc(HWND hWnd);

void startMagnifyProc(HWND hWnd);
void startPaintProc(HWND hWnd);
void startComputerAttributeProc(HWND hWnd);
void startUACSettingProc(HWND hWnd);
void startComputerManageProc(HWND hWnd);

#define MAX_LINE_COUNT 1024
TCHAR inputLineArr[MAX_LINE_COUNT];
char inputLineArrAnsi[MAX_LINE_COUNT];
////////////////////////////////////////////////////////////////
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
	LoadString(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor = LoadCursor(NULL, IDC_SIZEALL);
	LOGBRUSH lb;
	lb.lbColor = transBgColor;
	lb.lbHatch = 0;
	lb.lbStyle = 0;
	HBRUSH brush = CreateBrushIndirect(&lb);
	wcex.hbrBackground = brush;
	wcex.lpszMenuName =  MAKEINTRESOURCE(IDC_MY);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));


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

   screenx = GetSystemMetrics(SM_CXFULLSCREEN);
   screeny = GetSystemMetrics(SM_CYFULLSCREEN);
   hWnd = CreateWindowEx(WS_EX_TOOLWINDOW,
	   szWindowClass,
	   szTitle,
	   WS_OVERLAPPED | WS_THICKFRAME | WS_POPUP,
	   -10, -10,
	   screenx + 20, screeny + 20,
	   NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }
   menu = GetMenu(hWnd);

   ShowWindow(hWnd, SW_MAXIMIZE);
   GetWindowRect(hWnd, &wndrect);
   screenx = wndrect.right - wndrect.left+20;
   screeny = wndrect.bottom - wndrect.top+20;
   ShowWindow(hWnd, nCmdShow);

   UpdateWindow(hWnd);

   BuildBackgroundImg();
   setPen(bdc,prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
   setBrush(bdc, preBrushColor);
   setFont(bdc, preTextSize,preTextColor);
   SetBkMode(bdc, TRANSPARENT);
   //����͸��
   LONG wlong = GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED;
   SetWindowLong(hWnd, GWL_EXSTYLE, wlong);
   //����͸���
   Masked(hWnd, false);

   //������ǰ��
   SetWindowPos(hWnd, HWND_TOPMOST, -10, -10, screenx, screeny, SWP_SHOWWINDOW );

   //�����߿�
   SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) - WS_CAPTION);

   //��ʾ�˵�
   ShowMenu(hWnd);
   
   //���ö�ʱ��
   SetTimer(hWnd, ID_TIMER_SPEED, TIMER_SLEEP_MILLSEC, &TimerProc);
   return TRUE;
}

void maxmForegroundWindow(HWND hWnd)
{
	HWND fw = GetForegroundWindow();
	HWND dkw = GetDesktopWindow();
	if (hWnd == fw || fw==dkw)
		return;
	ShowWindow(fw, SW_NORMAL);
	::SendMessage(fw, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
}
void minForegroundWindow(HWND hWnd)
{
	HWND fw = GetForegroundWindow();
	HWND dkw = GetDesktopWindow();
	if (hWnd == fw || fw == dkw)
		return;
	ShowWindow(fw, SW_MINIMIZE);
	::SendMessage(fw, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}
void closeForceWindow(HWND fw){
	PostMessage(fw, WM_CLOSE, 0, 0);
	PostMessage(fw, WM_DESTROY, 0, 0);
	::SendMessage(fw, WM_SYSCOMMAND, SC_CLOSE, 0);
	DWORD pid = -1;
	GetWindowThreadProcessId(fw, &pid);
	HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (phandle != INVALID_HANDLE_VALUE){
		TerminateProcess(phandle, 0);
		CloseHandle(phandle);
	}
}
void closeForegroundWindow(HWND hWnd)
{
	HWND fw = GetForegroundWindow();
	HWND dkw = GetDesktopWindow();
	if (hWnd == fw || fw == dkw)
		return;
	closeForceWindow(fw);
	
}
void closeTopWindow(HWND hWnd)
{
	HWND dkw = GetDesktopWindow();
	HWND curWnd = GetNextWindow(GetDesktopWindow(), GW_CHILD);
	while (curWnd)
	{
		if (hWnd == curWnd || curWnd == dkw){
			curWnd = GetNextWindow(curWnd, GW_HWNDNEXT);
			continue;
		}
		if (IsIconic(curWnd) || !IsWindowVisible(curWnd)){ //��С�����߲��ɼ����ڣ�����
			curWnd = GetNextWindow(curWnd, GW_HWNDNEXT);
			continue;
		}
		if (IsZoomed(curWnd)){ //��󻯴���,�ݲ�����
			
		}
		if (GetWindowLong(curWnd, GWL_EXSTYLE) & WS_EX_TOPMOST){ //�ö����ڣ�ֱ�ӹرգ���Ч��ֹ�ö����ڵ�ס����
			closeForceWindow(curWnd);
			break;
		}
		curWnd = GetNextWindow(curWnd, GW_HWNDNEXT);
	}
}

//HOOKǿ���ػ�ģʽ
bool g_isMaskState = false;
HWND g_hwnd = NULL;
HHOOK g_keyHook = NULL;
LRESULT CALLBACK keyHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT * pkbhs = (KBDLLHOOKSTRUCT *)lParam;
	if (nCode == HC_ACTION) 
	{
		int vkCode = pkbhs->vkCode;
		///////////////////////////////////////////////////////////////
		
		{
			HWND hWnd = g_hwnd;
			if (vkCode==VK_F6 && WM_KEYDOWN==wParam)
			{
				if ((GetAsyncKeyState('L') & 0x8000))
				{
					preDrawType = DT_Line;
				}
				if ((GetAsyncKeyState('A') & 0x8000))
				{
					preDrawType = DT_Arrow;
				}
				if ((GetAsyncKeyState('F') & 0x8000))
				{
					preDrawType = DT_CirLine;
				}
				if ((GetAsyncKeyState('D') & 0x8000))
				{
					ClearDrawEnv(hWnd);
				}
				if ((GetAsyncKeyState('C') & 0x8000))
				{
					captureScreenProc(hWnd);
				}
				if ((GetAsyncKeyState('S') & 0x8000))
				{
					saveCaptureProc(hWnd);
				}
				if ((GetAsyncKeyState('Q') & 0x8000))
				{
					exitCaptureProc(hWnd);
				}
				if ((GetAsyncKeyState('M') & 0x8000))
				{
					startCmdProc(hWnd);
				}
				if ((GetAsyncKeyState('R') & 0x8000))
				{
					startControlProc(hWnd);
				}
				if ((GetAsyncKeyState('P') & 0x8000))
				{
					startApplicationManageProc(hWnd);
				}
				if ((GetAsyncKeyState('Z') & 0x8000))
				{
					startTranslateEntoZhProc(hWnd);
				}
				if ((GetAsyncKeyState('E') & 0x8000))
				{
					startTranslateZhtoEnProc(hWnd);
				}
				if ((GetAsyncKeyState('B') & 0x8000))
				{
					startBrowserSearchProc(hWnd);
				}
				////////////////////
				if ((GetAsyncKeyState('G') & 0x8000))
				{
					startRegEditProc(hWnd);
				}
				if ((GetAsyncKeyState('X') & 0x8000))
				{
					startExplorerProc(hWnd);
				}
				if ((GetAsyncKeyState('T') & 0x8000))
				{
					startNotepadProc(hWnd);
				}
				if ((GetAsyncKeyState('A') & 0x8000))
				{
					startSnaptoolProc(hWnd);
				}
				if ((GetAsyncKeyState('V') & 0x8000))
				{
					startMagnifyProc(hWnd);
				}
				if ((GetAsyncKeyState('D') & 0x8000))
				{
					startPaintProc(hWnd);
				}
				if ((GetAsyncKeyState('I') & 0x8000))
				{
					startComputerAttributeProc(hWnd);
				}
				if ((GetAsyncKeyState('U') & 0x8000))
				{
					startUACSettingProc(hWnd);
				}
				if ((GetAsyncKeyState('K') & 0x8000))
				{
					startComputerManageProc(hWnd);
				}
				if ((GetAsyncKeyState('W') & 0x8000))
				{
					copyDisplayImage2ClipbordProc(hWnd);
				}
				if ((GetAsyncKeyState(VK_TAB) & 0x8000))
				{
					preDrawType = DT_Rectangle;
				}
				if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
				{
					preDrawType = DT_Empty;
				}
			}
			if (vkCode == VK_F8 && WM_KEYDOWN == wParam)
			{
				if ((GetAsyncKeyState('N') & 0x8000))
				{
					searchNormalCombineProc(hWnd);
				}
				if ((GetAsyncKeyState('C') & 0x8000))
				{
					searchSiteCombineProc(hWnd);
				}
				if ((GetAsyncKeyState('P') & 0x8000))
				{
					searchProgramCombineProc(hWnd);
				}
				if ((GetAsyncKeyState('F') & 0x8000))
				{
					searchResourceCombineProc(hWnd);
				}

				if ((GetAsyncKeyState(VK_SHIFT) & 0x8000))
				{
					if ((GetAsyncKeyState('S') & 0x8000))
					{
						startNowShutdownProc(hWnd);
					}
					if ((GetAsyncKeyState('R') & 0x8000))
					{
						startNowRebootProc(hWnd);
					}
					if ((GetAsyncKeyState('L') & 0x8000))
					{
						startNowLockScreenProc(hWnd);
					}
					if ((GetAsyncKeyState('B') & 0x8000))
					{
						startSearchClipboardProc(hWnd);
					}
					if ((GetAsyncKeyState('1') & 0x8000) || (GetAsyncKeyState(VK_NUMPAD1) & 0x8000))
					{
						startSelfMindOneProc(hWnd);
					}
					if ((GetAsyncKeyState('2') & 0x8000) || (GetAsyncKeyState(VK_NUMPAD2) & 0x8000))
					{
						startSelfMindTwoProc(hWnd);
					}
					if ((GetAsyncKeyState('3') & 0x8000) || (GetAsyncKeyState(VK_NUMPAD3) & 0x8000))
					{
						startSelfMindThreeProc(hWnd);
					}
					//////////////////////////////////////
					//���ڹ���==��󻯡���С�����ر�
					if ((GetAsyncKeyState('W') & 0x8000))
					{
						maxmForegroundWindow(hWnd);
					}
					if ((GetAsyncKeyState('D') & 0x8000))
					{
						minForegroundWindow(hWnd);
					}
					if ((GetAsyncKeyState('X') & 0x8000))
					{
						closeForegroundWindow(hWnd);
					}
					if ((GetAsyncKeyState('Q') & 0x8000))
					{
						closeTopWindow(hWnd);
					}
					
				}
			}
			if (vkCode == VK_CAPITAL && WM_KEYDOWN == wParam)
			{
				for (int i = 0; i < 26; i++){
					if ((GetAsyncKeyState('A'+i) & 0x8000))
					{
						char buf[1024] = { 0 };
						sprintf(buf, "explorer %c:\\\0", (char)('A' + i));
						WinExec(buf, SW_SHOW);
						break;
					}
				}
				
			}
			
			//if (GetActiveWindow() != hWnd)
			{
				if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_SHIFT) & 0x8000) && (GetAsyncKeyState(VK_MENU) & 0x8000))
				{
					if (vkCode==VK_F1 && WM_KEYDOWN==wParam)
					{
						ShowMenu(hWnd);
					}
					if ((GetAsyncKeyState(VK_F2) & 0x8000))
					{
						if (isCaptureMode){
							exitCaptureProc(hWnd);
						}
						g_isMaskState = false;
						Masked(hWnd, false);
					}
					if ((GetAsyncKeyState(VK_F3) & 0x8000))
					{
						if (isCaptureMode){
							exitCaptureProc(hWnd);
						}
						g_isMaskState = true;
						Masked(hWnd, true);
					}

				}
			}
		}
		/////////////////////////////////////////////////////////////
		if (g_isMaskState)
		{
			if (vkCode == VK_DELETE)
			{
				if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_MENU) & 0x8000))
				{
					MessageBeep(MB_ICONERROR);
					//Control+Alt+Delete
					return TRUE;//return TRUE to avoid transfrom
				}
			}
			else if (vkCode == VK_ESCAPE)
			{
				if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_SHIFT) & 0x8000))
				{
					MessageBeep(MB_ICONERROR);
					//Shift+Alt+Esc
					return TRUE;//return TRUE to avoid transfrom
				}
			}
			else if (vkCode == VK_F4)
			{
				if ((GetAsyncKeyState(VK_MENU) & 0x8000))
				{
					MessageBeep(MB_ICONERROR);
					//Alt+F4
					return TRUE;//return TRUE to avoid transfrom
				}
			}
			else if (vkCode == VK_TAB )
			{
				if ((GetAsyncKeyState(VK_MENU) & 0x8000))
				{
					MessageBeep(MB_ICONERROR);
					//Alt+Tab
					return TRUE;//return TRUE to avoid transfrom
				}
			}
			else if (vkCode == VK_LWIN || vkCode==VK_RWIN)
			{

					MessageBeep(MB_ICONERROR);
					//Win
					return TRUE;//return TRUE to avoid transfrom
			}
			else if (vkCode == VK_LBUTTON || vkCode == VK_RBUTTON || vkCode == VK_MBUTTON)
			{
				MessageBeep(MB_ICONERROR);
				//mouse keys
				return TRUE;//return TRUE to avoid transfrom
			}
			else if (vkCode == VK_ESCAPE || vkCode == VK_CAPITAL || vkCode == VK_BACK || vkCode == VK_DELETE || vkCode == VK_RETURN || vkCode == VK_SPACE
				|| vkCode == VK_PRINT || vkCode == VK_SCROLL || vkCode == VK_PAUSE || vkCode == VK_NUMLOCK || vkCode==VK_SNAPSHOT
				|| vkCode==VK_MEDIA_PLAY_PAUSE || vkCode==VK_MEDIA_STOP || vkCode==VK_MEDIA_PREV_TRACK || vkCode==VK_MEDIA_NEXT_TRACK
				|| vkCode==VK_VOLUME_MUTE || vkCode==VK_VOLUME_DOWN || vkCode==VK_VOLUME_UP
				||vkCode==VK_F9 ||vkCode==VK_F10 ||vkCode==VK_F11||vkCode==VK_F12
				)
			{

				MessageBeep(MB_ICONERROR);
				//some normal control keys
				return TRUE;//return TRUE to avoid transfrom
			}

		}
		
	}
	return CallNextHookEx(g_keyHook, nCode, wParam, lParam);
}
void initKeyHook()
{
	if (g_keyHook==NULL)
	{
		g_keyHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyHookProc, 0, 0);
		if (g_keyHook == NULL)
		{
			MessageBox(g_hwnd, TEXT("ǿ��HOOK�ػ��������������⣬�����ػ������½�������Ȼ�ܹ�Ӧ��"), TEXT("�ػ���ʾ"), MB_OK | MB_ICONWARNING);
		}
	}
}
void destoryKeyHook()
{
	if (g_keyHook)
	{
		UnhookWindowsHookEx(g_keyHook);
		g_keyHook = NULL;
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
	case WM_CREATE:
		g_hwnd = hWnd;
		initKeyHook();
		break;
	case WM_SYSKEYDOWN:
	{
		//�����򲻴���Alt+F4����ֹAlt+F4�رձ�����
		int vkeyCode = LOWORD(wParam);
		if ( vkeyCode== VK_F4)
			return TRUE;
	}
		break;
	case WM_KEYDOWN:
		KeyDownProc(hWnd, wParam);
		return TRUE;
		break;
	case WM_KEYUP:
		KeyUpProc(hWnd,wParam);
		break;
	case WM_LBUTTONDOWN:
		 LBtnDownProc(hWnd, lParam);
		break;
	case WM_LBUTTONUP:
		LBtnUpProc( hWnd, lParam);
		break;
	case WM_MOUSEMOVE:
		MouseMoveProc( hWnd, lParam);
		break;
	case WM_RBUTTONDOWN:
		RBtnDownProc(hWnd, lParam);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case ID_DRAW_EMPTY:
			preDrawType = DT_Empty;
			break;
		case ID_DRAW_POINT:
			preDrawType = DT_Point;
			break;
		case ID_DRAW_ARROW:
			preDrawType = DT_Arrow;
			break;
		case ID_DRAW_LINE:
			preDrawType = DT_Line;
			break;
		case ID_DRAW_CIRLINE:
			preDrawType = DT_CirLine;
			break;
		case ID_DRAW_RECT:
			preDrawType = DT_Rectangle;
			break;
		case ID_DRAW_ELIPSE:
			preDrawType = DT_Elipese;
			break;
		case ID_DRAW_CLEAR:
			ClearDrawEnv(hWnd);
			break;
		case ID_COPY_VIEW:
			copyDisplayImage2ClipbordProc(hWnd);
			break;
		case ID_COLOR_PEN_RED:
			prePenColor = CT_Red;
			setPen(bdc,prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_COLOR_PEN_GREEN:
			prePenColor = CT_Green;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_COLOR_PEN_BLUE:
			prePenColor = CT_Blue;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_COLOR_PEN_BLACK:
			prePenColor = CT_Black;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_COLOR_PEN_WEITE:
			prePenColor = CT_Weite;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_COLOR_PEN_BG:
			setPen(bdc, prePenStyle, transBgColor, prePenSize);
			break;
		case ID_COLOR_PEN_BLUEGREEN:
			setPen(bdc, prePenStyle, 0xffff00, prePenSize);
			break;
		case ID_COLOR_BRUSH_RED:
			preBrushColor = (COLORREF)(int)CT_Red;
			setBrush(bdc, preBrushColor);
			break;
		case ID_COLOR_BRUSH_GREEN:
			preBrushColor = (COLORREF)(int)CT_Green;
			setBrush(bdc, preBrushColor);
			break;
		case ID_COLOR_BRUSH_BLUE:
			preBrushColor = (COLORREF)(int)CT_Blue;
			setBrush(bdc, preBrushColor);
			break;
		case ID_COLOR_BRUSH_BLACK:
			preBrushColor = (COLORREF)(int)CT_Black;
			setBrush(bdc, preBrushColor);
			break;
		case ID_COLOR_BRUSH_WEITE:
			preBrushColor = (COLORREF)(int)CT_Weite;
			setBrush(bdc, preBrushColor);
			break;
		case ID_COLOR_BRUSH_BG:
			preBrushColor = transBgColor;
			setBrush(bdc, preBrushColor);
			break;
		case ID_COLOR_BRUSH_BLUEGREEN:
			preBrushColor = 0xffff00;
			setBrush(bdc, preBrushColor);
			break;
		case ID_PEN_STYLE_SOLID:
			prePenStyle = PS_SOLID;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_PEN_STYLE_DASH:
			prePenStyle = PS_DASH;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_PEN_STYLE_DOT:
			prePenStyle = PS_DOT;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_PEN_SIZE_1:
			prePenSize = 1;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_PEN_SIZE_3:
			prePenSize = 3;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
		case ID_PEN_SIZE_5:
			prePenSize = 5;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_PEN_SIZE_8:
			prePenSize = 8;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_PEN_SIZE_13:
			prePenSize = 13;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_PEN_SIZE_24:
			prePenSize = 24;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_PEN_SIZE_36:
			prePenSize = 36;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_PEN_SIZE_54:
			prePenSize = 54;
			setPen(bdc, prePenStyle, (COLORREF)(int)prePenColor, prePenSize);
			break;
		case ID_COLOR_FONT_RED:
			preTextColor = 0x2233ff;
			setFont(bdc, preTextSize, preTextColor);
			break;
		case ID_COLOR_FONT_YELLOW:
			preTextColor = 0x22ffff;
			setFont(bdc, preTextSize, preTextColor);
			break;
		case ID_COLOR_FONT_GREEN:
			preTextColor = 0x22ff33;
			setFont(bdc, preTextSize, preTextColor);
			break;
		case ID_COLOR_FONT_BLUE:
			preTextColor = 0xff2233;
			setFont(bdc, preTextSize, preTextColor);
			break;
		case ID_COLOR_FONT_BLACK:
			preTextColor = 0x111111;
			setFont(bdc, preTextSize, preTextColor);
			break;
		case ID_FONT_SIZE_14:
			preTextSize = -14;
			setFont(bdc, preTextSize, preTextColor);
			break;
		case ID_FONT_SIZE_24:
			preTextSize = -24;
			setFont(bdc, preTextSize, preTextColor);
			break;
		case ID_FONT_SIZE_36:
			preTextSize = -36;
			setFont(bdc, preTextSize, preTextColor);
			break;
		case ID_FONT_SIZE_50:
			preTextSize = -50;
			setFont(bdc, preTextSize, preTextColor);
			break;
		case ID_FONT_SIZE_80:
			preTextSize = -80;
			setFont(bdc, preTextSize, preTextColor);
			break;
		case ID_CAPTURE_SCREEN:
			captureScreenProc(hWnd);
			break;
		case ID_SAVE_CAPTURE:
			saveCaptureProc(hWnd);
			break;
		case ID_EXIT_CAPTURE:
			exitCaptureProc(hWnd);
			break;
		case ID_SYS_CMD:
			startCmdProc(hWnd);
			break;
		case ID_SYS_CONTROL:
			startControlProc(hWnd);
			break;
		case ID_SYS_APPLICATION:
			startApplicationManageProc(hWnd);
			break;
		case ID_TRANLATE_ZHEN:
			startTranslateZhtoEnProc(hWnd);
			break;
		case ID_TRANSLATE_ENZH:
			startTranslateEntoZhProc(hWnd);
			break;
		case ID_SEARCH_BROWSWE:
			startBrowserSearchProc(hWnd);
			break;
		case ID_SEARCH_NORMALCOMBINE:
			searchNormalCombineProc(hWnd);
			break;
		case ID_SEARCH_SITECOMBINE:
			searchSiteCombineProc(hWnd);
			break;
		case ID_SEARCH_PROGRAMCOMBINE:
			searchProgramCombineProc(hWnd);
			break;
		case ID_SEARCH_RESOURCECOMBINE:
			searchResourceCombineProc(hWnd);
			break;
		case ID_NOW_SHUTDOWN:
			startNowShutdownProc(hWnd);
			break;
		case ID_NOW_REBOOT:
			startNowRebootProc(hWnd);
			break;
		case ID_NOW_LOCKSCREEN:
			startNowLockScreenProc(hWnd);
			break;
		case ID_SEARCH_CLIPBROAD:
			startSearchClipboardProc(hWnd);
			break;
		case ID_SELF_MIND_ONE:
			startSelfMindOneProc(hWnd);
			break;
		case ID_SELF_MIND_TWO:
			startSelfMindTwoProc(hWnd);
			break;
		case ID_SELF_MIND_THREE:
			startSelfMindThreeProc(hWnd);
			break;
		case ID_SYS_REGEDIT:
			startRegEditProc(hWnd);
			break;
		case ID_SYS_EXPLORER:
			startExplorerProc(hWnd);
			break;
		case ID_SYS_NOTEPAD:
			startNotepadProc(hWnd);
			break;
		case ID_SYS_SNAPTOOL:
			startSnaptoolProc(hWnd);
			break;
		case ID_SYS_MAGNIFY:
			startMagnifyProc(hWnd);
			break;
		case ID_SYS_DRAW:
			startPaintProc(hWnd);
			break;
		case ID_SYS_ATTRIBUTE:
			startComputerAttributeProc(hWnd);
			break;
		case ID_SYS_UAC:
			startUACSettingProc(hWnd);
			break;
		case ID_SYS_COMPUTERMANAGE:
			startComputerManageProc(hWnd);
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
		BitBlt(hdc, 0, 0, screenx, screeny, bdc, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		destoryKeyHook();
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
void showSelfMindDeclareMsgBox(HWND hWnd)
{
	char msgbody[] = { "\
�Զ���ָ����������ָ����ļ��У�ÿһ����Ϊһ���Զ���ָ�\n\
��������Զ���ָ��Ҳ��֧��������У�������н�������,\n\
һ��ָ���������Щ��ʽ��\n\
\tcmd /k color f5\n\
\tcmd /k color f2 && cd E:\\ && cd E: && title ����E�̲���\n\
\t#cmd /c explorer \"https://www.baidu.com\"\n\
��˵����\n\
\t cmd /k ��ʾ����������һ��cmd���ڣ�ִ�������֮�󱣳ִ���\n\
\t\t����/c���ʾִ�����֮���Զ��ر�cmd����\n\
\t && ��ʾ���Ӷ���ָ��һ��ִ��\n\
\t explorer �����ϵͳ����Դ�����������������Ϳ���ִ��Ĭ�ϲ���\n\
\t\t���������һ����ַ�����ܵ���Ĭ��������������ַ\n\
\t # ����еĵ�һ���ַ���#����ô����ָ����ں�̨���У�\n\
\t\t����ʾcmd����,��˽���ʹ��/c��Ϊ����������\n\
\t\t���򽫻���cmd����פ��,������������������ҵ�\n\
\t��������Զ���ָ����õ�ʱ��ȥ��ȡ�ļ�����˾��㱾����������\n\
\t\t��Ҳ���Զ�̬���޸��Զ���ָ���ļ�\n\
"};
	MessageBoxA(hWnd, msgbody, SELF_MIND_FILE_NAME, MB_OK);
	
}
void startSelfMindOneProc(HWND hWnd)
{
	FILE * fp = fopen(SELF_MIND_FILE_NAME,"r");
	if (fp == NULL){
		showSelfMindDeclareMsgBox(hWnd);
		return;
	}
	char buffer[2048] = { 0 };
	fgets(buffer, 2048 - 1, fp);
	fclose(fp);

	if (strlen(buffer) > 0)
	{
		if (buffer[0] == '#')
			WinExec(&buffer[1], SW_HIDE);
		else
			WinExec(buffer, SW_SHOW);
	}
}
void startSelfMindTwoProc(HWND hWnd)
{
	FILE * fp = fopen(SELF_MIND_FILE_NAME, "r");
	if (fp == NULL){
		showSelfMindDeclareMsgBox(hWnd);
		return;
	}
	char buffer[2048] = { 0 };
	fgets(buffer, 2048 - 1, fp);
	if (!feof(fp)){
		memset(buffer, 0, sizeof(buffer));
		fgets(buffer, 2048 - 1, fp);
	}
	fclose(fp);

	if (strlen(buffer) > 0)
	{
		if (buffer[0] == '#')
			WinExec(&buffer[1], SW_HIDE);
		else
			WinExec(buffer, SW_SHOW);
	}
}
void startSelfMindThreeProc(HWND hWnd)
{
	FILE * fp = fopen(SELF_MIND_FILE_NAME, "r");
	if (fp == NULL){
		showSelfMindDeclareMsgBox(hWnd);
		return;
	}
	char buffer[2048] = { 0 };
	fgets(buffer, 2048 - 1, fp);
	if (!feof(fp)){
		memset(buffer, 0, sizeof(buffer));
		fgets(buffer, 2048 - 1, fp);
		if (!feof(fp)){
			memset(buffer, 0, sizeof(buffer));
			fgets(buffer, 2048 - 1, fp);
		}
	}
	fclose(fp);

	if (strlen(buffer) > 0)
	{
		if (buffer[0] == '#')
			WinExec(&buffer[1], SW_HIDE);
		else
			WinExec(buffer, SW_SHOW);
	}
}
void startNowShutdownProc(HWND hWnd)
{
	WinExec("cmd /c shutdown -s -f -t 0", SW_HIDE);
}
void startNowRebootProc(HWND hWnd)
{
	WinExec("cmd /c shutdown -r -f -t 0", SW_HIDE);
}
void startNowLockScreenProc(HWND hWnd)
{
	WinExec("cmd /c rundll32 user32.dll,LockWorkStation", SW_HIDE);
}
void startSearchClipboardProc(HWND hWnd)
{
	static char prepared[] = { "cmd /c explorer \"https://www.baidu.com/s?wd=%s\"" };

	if (OpenClipboard(hWnd))
	{
		HANDLE hData = GetClipboardData(CF_TEXT);
		char * buffer = (char*)GlobalLock(hData);

		char cmd[2048] = { 0 };
		sprintf(cmd, prepared, buffer);
		WinExec(cmd, SW_HIDE);

		GlobalUnlock(hData);
		CloseClipboard();
	}
	
}
void startCmdProc(HWND hWnd)
{
	WinExec("cmd",SW_SHOW);
}
void startControlProc(HWND hWnd)
{
	WinExec("control", SW_HIDE);
}
void startApplicationManageProc(HWND hWnd)
{
	WinExec("cmd /c appwiz.cpl", SW_HIDE);
}
void startTranslateZhtoEnProc(HWND hWnd)
{
	WinExec("cmd /c explorer \"https://translate.google.cn/#view=home&op=translate&sl=zh-CN&tl=en\"", SW_HIDE);
}
void startTranslateEntoZhProc(HWND hWnd)
{
	WinExec("cmd /c explorer \"https://translate.google.cn/#view=home&op=translate&sl=en&tl=zh-CN\"", SW_HIDE);
}
void getSearchText(HWND hWnd)
{
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DLG_INPUT), hWnd, InputBoxProc);
}
void startBrowserSearchProc(HWND hWnd)
{
	static char prepared[] = { "cmd /c explorer \"https://www.baidu.com/s?wd=%s\"" };
	getSearchText(hWnd);
	char cmd[2048] = { 0 };
	sprintf(cmd, prepared, inputLineArrAnsi);
	WinExec(cmd, SW_HIDE);
}

void searchNormalCombineProc(HWND hWnd)
{
	getSearchText(hWnd);
	static int len = 3;
	static char preparedUrlCmd[][200] = { 
		"cmd /c explorer \"https://www.baidu.com/s?wd=%s\"" ,
		"cmd /c explorer \"https://cn.bing.com/search?q=%s\"" ,
		"cmd /c explorer \"https://www.google.com/search?q=%s\""
	};
	char cmd[2048] = { 0 };
	for (int i = 0; i < len; i++)
	{
		memset(cmd, 0, 2048);
		sprintf(cmd,preparedUrlCmd[i],inputLineArrAnsi);
		WinExec(cmd, SW_HIDE);
	}
}
void searchSiteCombineProc(HWND hWnd)
{
	WinExec("cmd /c explorer \"http://so.classic023.com/\"", SW_HIDE);
	WinExec("cmd /c explorer \"http://sou.txpeng.com/\"", SW_HIDE);
}
void searchProgramCombineProc(HWND hWnd)
{
	getSearchText(hWnd);
	static int len = 3;
	static char preparedUrlCmd[][200] = {
		"cmd /c explorer \"https://so.csdn.net/so/search/s.do?q=%s\"",
		"cmd /c explorer \"https://stackoverflow.com/search?q=%s\"",
		"cmd /c explorer \"https://github.com/search?q=%s\""
	};
	char cmd[2048] = { 0 };
	for (int i = 0; i < len; i++)
	{
		memset(cmd, 0, 2048);
		sprintf(cmd, preparedUrlCmd[i], inputLineArrAnsi);
		WinExec(cmd, SW_HIDE);
	}
}
void searchResourceCombineProc(HWND hWnd)
{
	getSearchText(hWnd);
	static int len = 4;
	static char preparedUrlCmd[][200] = {
		"cmd /c explorer \"https://www.sobaidupan.com/search.asp?wd=%s\"",
		"cmd /c explorer \"https://www.fastsoso.cn/search?k=%s\"", 
		"cmd /c explorer \"https://www.dalipan.com/search?keyword=%s\"",
		"cmd /c explorer \"https://www.fqsousou.com/s/%s.html\""
	};
	char cmd[2048] = { 0 };
	for (int i = 0; i < len; i++)
	{
		memset(cmd, 0, 2048);
		sprintf(cmd, preparedUrlCmd[i], inputLineArrAnsi);
		WinExec(cmd, SW_HIDE);
	}
}

void startRegEditProc(HWND hWnd)
{
	char cmd[] = {"cmd /c start regedit"};
	WinExec(cmd, SW_HIDE);
}
void startExplorerProc(HWND hWnd)
{
	getSearchText(hWnd);
	char preparedFmt[] = { "cmd /c explorer %s" };
	char cmd[2048] = { 0 };
	sprintf(cmd, preparedFmt, inputLineArrAnsi);
	WinExec(cmd, SW_HIDE);
}
void startNotepadProc(HWND hWnd)
{
	getSearchText(hWnd);
	char preparedFmt[] = { "cmd /c notepad %s" };
	char cmd[2048] = { 0 };
	sprintf(cmd, preparedFmt, inputLineArrAnsi);
	WinExec(cmd, SW_HIDE);
}
void startSnaptoolProc(HWND hWnd)
{
	//����ֱ��ִ������start Snippingtool �������ã����ֱ��ģ�ⰴ��
	char names[] = { "SNIPPINGTOOL" };
	keybd_event(VK_LWIN, 0, 0, NULL);
	keybd_event('R', 0, 0, NULL);
	keybd_event('R', 0, KEYEVENTF_KEYUP, NULL);
	keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, NULL);
	
	Sleep(120);
	int i = 0;
	while (names[i] != 0){
		keybd_event(names[i], 0, 0, NULL);
		keybd_event(names[i], 0, KEYEVENTF_KEYUP, NULL);
		Sleep(10);
		i++;
	}
	Sleep(60);
	keybd_event(VK_SPACE, 0, 0, NULL);
	keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, NULL);
	keybd_event(VK_RETURN, 0, 0, NULL);
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, NULL);
}

void startMagnifyProc(HWND hWnd)
{
	char cmd[] = { "cmd /c magnify" };
	WinExec(cmd, SW_HIDE);
}
void startPaintProc(HWND hWnd)
{
	char cmd[] = { "cmd /c mspaint" };
	WinExec(cmd, SW_HIDE);
}
void startComputerAttributeProc(HWND hWnd)
{
	char cmd[] = { "cmd /c sysdm.cpl" };
	WinExec(cmd, SW_HIDE);
}
void startUACSettingProc(HWND hWnd)
{
	char cmd[] = { "cmd /c UserAccountControlSettings" };
	WinExec(cmd, SW_HIDE);
}
void startComputerManageProc(HWND hWnd)
{
	char cmd[] = { "cmd /c compmgmt.msc" };
	WinExec(cmd, SW_HIDE);
}
void captureScreenProc(HWND hWnd)
{
	isCaptureMode = true;
	preDrawType = DT_Rectangle;
	ShowWindow(hWnd,SW_HIDE);

	imgCapture=IMAGE(screenx, screeny);
	HDC ddc = GetDC(NULL);
	HDC mdc = GetImageHDC(&imgCapture);
	//BitBlt(mdc, 0, 0, imgCapture.getwidth(), imgCapture.getheight(), ddc, 0, 0, SRCCOPY);

	HWND hwnd = GetDesktopWindow();
	//��ȡ��ʵ�����С�µ�ͼ�Σ���ʹ��HALFTONE���и߾��ȵ�ͼ������
	SetStretchBltMode(mdc, HALFTONE);
	StretchBlt(mdc, 0, 0, imgCapture.getwidth() , imgCapture.getheight(), ddc, 0, 0, GetDeviceCaps(ddc, DESKTOPHORZRES), GetDeviceCaps(ddc, DESKTOPVERTRES), SRCCOPY);
	ReleaseDC(NULL,ddc);

	captureRect.left = 0;
	captureRect.top = 0;
	captureRect.right = imgCapture.getwidth();
	captureRect.bottom = imgCapture.getheight();
	ShowWindow(hWnd,SW_SHOW);
	ClearDrawEnv(hWnd);
}
void saveCaptureProc(HWND hWnd)
{
	IMAGE img(captureRect.right-captureRect.left,captureRect.bottom-captureRect.top);
	HDC mdc = GetImageHDC(&img);
	HDC ddc = bdc;
	BitBlt(mdc, 0, 0, img.getwidth(), img.getheight(), ddc, captureRect.left, captureRect.top, SRCCOPY);
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DLG_INPUT), hWnd, InputBoxProc);
	saveimage(inputLineArr, &img);
}

void copyDisplayImage2ClipbordProc(HWND hWnd)
{
	HDC ddc = GetDC(NULL);
	int pwid = GetDeviceCaps(ddc, DESKTOPHORZRES);
	int phei = GetDeviceCaps(ddc, DESKTOPVERTRES);
	int offx = 0;
	int offy = 0;
	HWND wnd = NULL;
	if (isCaptureMode){
		pwid = captureRect.right - captureRect.left;
		phei = captureRect.bottom - captureRect.top;
		offx = captureRect.left;
		offy = captureRect.top;
		wnd = hWnd;
	}

	HDC dc = GetDC(wnd);
	
	HDC memDC = CreateCompatibleDC(dc);

	HBITMAP bm = CreateCompatibleBitmap(dc, pwid, phei);
	
	HBITMAP oldbm = (HBITMAP)SelectObject(memDC, bm);
	
	BitBlt(memDC, 0, 0, pwid, phei, dc, offx, offy, SRCCOPY);


	OpenClipboard(hWnd);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, bm);
	CloseClipboard();

	SelectObject(memDC, oldbm);
}
void exitCaptureProc(HWND hWnd)
{
	isCaptureMode = false;
	SetLayeredWindowAttributes(hWnd, transBgColor, 120, LWA_ALPHA);
	ClearDrawEnv(hWnd);
}
void ClearDrawEnv(HWND hWnd)
{
	if (isCaptureMode)
	{
		captureRect.left = 0;
		captureRect.top = 0;
		captureRect.right = imgCapture.getwidth();
		captureRect.bottom = imgCapture.getheight();

		HDC mdc = GetImageHDC(&imgCapture);
		BitBlt(bdc, 0, 0, imgCapture.getwidth(), imgCapture.getheight(), mdc, 0, 0, SRCCOPY);
		InvalidateRect(hWnd, &wndrect, TRUE);
		return;
	}
	setBrush(bdc, (COLORREF)(int)transBgColor);
	Rectangle(bdc, 0 - 10, 0 - 10, screenx + 10, screeny + 10);
	InvalidateRect(hWnd, &wndrect, TRUE);
}
void setFont(HDC hdc, int size,COLORREF color)
{
	LOGFONT lf = { 0 };
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = size; 
	HFONT font = CreateFontIndirect(&lf);
	HGDIOBJ obj=SelectObject(hdc, font);
	DeleteObject(obj);
	SetTextColor(hdc, color);
}
void setPen(HDC hdc,int style, COLORREF color, int width)
{
	if (style == PS_DASH || style == PS_DOT)
		width = 1;
	HPEN pen = CreatePen(style, width, color);
	HGDIOBJ obj = SelectObject(hdc, pen);
	DeleteObject(obj);
}
void setBrush(HDC hdc, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	HGDIOBJ obj = SelectObject(hdc, brush);
	DeleteObject(obj);
}
void Masked(HWND hwnd, bool mask)
{
	if (mask)
	{
		isMasked = true;
		SetLayeredWindowAttributes(hwnd, transBgColor, 1, LWA_ALPHA);
		//ClearDrawEnv(hwnd);
	}
	else
	{
		isMasked = false;
		SetLayeredWindowAttributes(hwnd, transBgColor, 0, LWA_COLORKEY);
	}

}
void ShowMenu(HWND hwnd)
{
	static bool isHasMenu = false;
	if (isHasMenu)
	{
		SetMenu(hwnd, menu);
	}
	else
	{
		SetMenu(hwnd, NULL);
	}
	isHasMenu = !isHasMenu;
}
//��ʱ���ص�����
VOID CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	static int waitTime = 0;
	if (nTimerid == ID_TIMER_SPEED){
		waitTime += TIMER_SLEEP_MILLSEC;
		//����һ�²���̫Ƶ���Ľ�����Ӧ
		//ÿ5����ʱ��������Ӧһ��
		if (waitTime < TIMER_SLEEP_MILLSEC*2 && g_keyHook==NULL)//����Ƿ���Hookʧ�ܵ����
		{
			if ((GetAsyncKeyState(VK_F6) & 0x8000))
			{
				if ((GetAsyncKeyState('L') & 0x8000))
				{
					preDrawType = DT_Line;
				}
				if ((GetAsyncKeyState('A') & 0x8000))
				{
					preDrawType = DT_Arrow;
				}
				if ((GetAsyncKeyState('F') & 0x8000))
				{
					preDrawType = DT_CirLine;
				}
				if ((GetAsyncKeyState('D') & 0x8000))
				{
					ClearDrawEnv(hWnd);
				}
				if ((GetAsyncKeyState('C') & 0x8000))
				{
					captureScreenProc(hWnd);
				}
				if ((GetAsyncKeyState('S') & 0x8000))
				{
					saveCaptureProc(hWnd);
				}
				if ((GetAsyncKeyState('Q') & 0x8000))
				{
					exitCaptureProc(hWnd);
				}
				if ((GetAsyncKeyState('M') & 0x8000))
				{
					startCmdProc(hWnd);
				}
				if ((GetAsyncKeyState('R') & 0x8000))
				{
					startControlProc(hWnd);
				}
				if ((GetAsyncKeyState('P') & 0x8000))
				{
					startApplicationManageProc(hWnd);
				}
				if ((GetAsyncKeyState('Z') & 0x8000))
				{
					startTranslateEntoZhProc(hWnd);
				}
				if ((GetAsyncKeyState('E') & 0x8000))
				{
					startTranslateZhtoEnProc(hWnd);
				}
				if ((GetAsyncKeyState('B') & 0x8000))
				{
					startBrowserSearchProc(hWnd);
				}
				////////////////////
				if ((GetAsyncKeyState('G') & 0x8000))
				{
					startRegEditProc(hWnd);
				}
				if ((GetAsyncKeyState('X') & 0x8000))
				{
					startExplorerProc(hWnd);
				}
				if ((GetAsyncKeyState('T') & 0x8000))
				{
					startNotepadProc(hWnd);
				}
				if ((GetAsyncKeyState('A') & 0x8000))
				{
					startSnaptoolProc(hWnd);
				}
				if ((GetAsyncKeyState('V') & 0x8000))
				{
					startMagnifyProc(hWnd);
				}
				if ((GetAsyncKeyState('D') & 0x8000))
				{
					startPaintProc(hWnd);
				}
				if ((GetAsyncKeyState('I') & 0x8000))
				{
					startComputerAttributeProc(hWnd);
				}
				if ((GetAsyncKeyState('U') & 0x8000))
				{
					startUACSettingProc(hWnd);
				}
				if ((GetAsyncKeyState('K') & 0x8000))
				{
					startComputerManageProc(hWnd);
				}
				if ((GetAsyncKeyState('W') & 0x8000))
				{
					copyDisplayImage2ClipbordProc(hWnd);
				}
				if ((GetAsyncKeyState(VK_TAB) & 0x8000))
				{
					preDrawType = DT_Rectangle;
				}
				if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
				{
					preDrawType = DT_Empty;
				}
			}
			if ((GetAsyncKeyState(VK_F8) & 0x8000))
			{
				if ((GetAsyncKeyState('N') & 0x8000))
				{
					searchNormalCombineProc(hWnd);
				}
				if ((GetAsyncKeyState('C') & 0x8000))
				{
					searchSiteCombineProc(hWnd);
				}
				if ((GetAsyncKeyState('P') & 0x8000))
				{
					searchProgramCombineProc(hWnd);
				}
				if ((GetAsyncKeyState('F') & 0x8000))
				{
					searchResourceCombineProc(hWnd);
				}

				if ((GetAsyncKeyState(VK_SHIFT) & 0x8000))
				{
					if ((GetAsyncKeyState('S') & 0x8000))
					{
						startNowShutdownProc(hWnd);
					}
					if ((GetAsyncKeyState('R') & 0x8000))
					{
						startNowRebootProc(hWnd);
					}
					if ((GetAsyncKeyState('L') & 0x8000))
					{
						startNowLockScreenProc(hWnd);
					}
					if ((GetAsyncKeyState('B') & 0x8000))
					{
						startSearchClipboardProc(hWnd);
					}
					if ((GetAsyncKeyState('1') & 0x8000) || (GetAsyncKeyState(VK_NUMPAD1) & 0x8000))
					{
						startSelfMindOneProc(hWnd);
					}
					if ((GetAsyncKeyState('2') & 0x8000) || (GetAsyncKeyState(VK_NUMPAD2) & 0x8000))
					{
						startSelfMindTwoProc(hWnd);
					}
					if ((GetAsyncKeyState('3') & 0x8000) || (GetAsyncKeyState(VK_NUMPAD3) & 0x8000))
					{
						startSelfMindThreeProc(hWnd);
					}
					///////////////////
					//���ڹ���==��󻯡���С�����ر�
					if ((GetAsyncKeyState('W') & 0x8000))
					{
						maxmForegroundWindow(hWnd);
					}
					if ((GetAsyncKeyState('D') & 0x8000))
					{
						minForegroundWindow(hWnd);
					}
					if ((GetAsyncKeyState('X') & 0x8000))
					{
						closeForegroundWindow(hWnd);
					}
					if ((GetAsyncKeyState('Q') & 0x8000))
					{
						closeTopWindow(hWnd);
					}
				}
			}
			if ((GetAsyncKeyState(VK_CAPITAL) & 0x8000))
			{
				for (int i = 0; i < 26; i++){
					if ((GetAsyncKeyState('A' + i) & 0x8000))
					{
						char buf[1024] = { 0 };
						sprintf(buf, "explorer %c:\\\0", (char)('A' + i));
						WinExec(buf, SW_SHOW);
						break;
					}
				}
			}
			//if (GetActiveWindow() != hWnd)
			{
				if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_SHIFT) & 0x8000) && (GetAsyncKeyState(VK_MENU) & 0x8000))
				{
					if ((GetAsyncKeyState(VK_F1) & 0x8000))
					{
						ShowMenu(hWnd);
					}
					if ((GetAsyncKeyState(VK_F2) & 0x8000))
					{
						if (isCaptureMode){
							exitCaptureProc(hWnd);
						}
						g_isMaskState = false;
						Masked(hWnd, false);
					}
					if ((GetAsyncKeyState(VK_F3) & 0x8000))
					{
						if (isCaptureMode){
							exitCaptureProc(hWnd);
						}
						g_isMaskState = true;
						Masked(hWnd, true);
					}

				}
			}
		}
		if (waitTime >= TIMER_SLEEP_MILLSEC * 5)
		{
			waitTime = 0;
		}
		
		if (isCaptureMode)
		{
			SetLayeredWindowAttributes(hWnd, preBrushColor, 255, LWA_ALPHA);
			return;
		}
		if (((GetAsyncKeyState(VK_LWIN) & 0x8000) || (GetAsyncKeyState(VK_RWIN) & 0x8000)) && (GetAsyncKeyState(VK_CONTROL) & 0x8000))
		{
			SetLayeredWindowAttributes(hWnd, transBgColor, 120, LWA_ALPHA);
			//��֤���������������г���Ľ���
			SetActiveWindow(hWnd);
			SetForegroundWindow(hWnd);
			SetFocus(hWnd);
			mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0,0,0);
		}
		if (isMasked)
		{
			SetActiveWindow(hWnd);
			SetForegroundWindow(hWnd);
			SetCursorPos(screenx / 2, screeny / 2);
			SetFocus(hWnd);
		}
	}
}
void KeyDownProc(HWND hWnd,WPARAM wParam)
{
	switch (wParam)
	{
	case VK_CONTROL:
		isCtrlDown = true;
		break;
	case VK_SHIFT:
		isShiftDown = true;
		break;
	case VK_MENU:
		isAltDown = true;
		break;
	case VK_F1:
		if (isCtrlDown && isShiftDown && isAltDown)
		{
			ShowMenu(hWnd);
		}
		break;
	case VK_F2:
		if (isCtrlDown && isShiftDown && isAltDown)
			Masked(hWnd, false);
		break;
	case VK_F3:
		if (isCtrlDown && isShiftDown && isAltDown)
			Masked(hWnd, true);
		break;
	case VK_F4:
		if (isCtrlDown && isShiftDown && isAltDown)
			exit(0);
		break;
	}
}

void KeyUpProc(HWND hWnd, WPARAM wParam)
{
	switch (wParam)
	{
	case VK_CONTROL:
		isCtrlDown = false;
		break;
	case VK_SHIFT:
		isShiftDown = false;
		break;
	case VK_MENU:
		isAltDown = false;
		break;
	}
}

void LBtnDownProc(HWND hWnd, LPARAM lParam)
{
	befPoint.x = LOWORD(lParam);
	befPoint.y = HIWORD(lParam);

	switch (preDrawType)
	{
	case DT_Point:
		if (prePenSize==1)
			SetPixelV(bdc, befPoint.x, befPoint.y, (COLORREF)(int)prePenColor);
		else
		{
			int penr = prePenSize / 2;
			Ellipse(bdc, befPoint.x - penr, befPoint.y - penr, befPoint.x + penr, befPoint.y + penr);
		}
		InvalidateRect(hWnd, &wndrect, TRUE);
		break;
	default:
		break;
	}

	isLBtnDown = true;
}
template<typename T>
double getLineDirection(T x1,T y1,T x2,T y2)
{
	return atan2(y2 - y1*1.0, x2 - x1*1.0);
}
template<typename T>
double AngleToRadian(T angle)
{
	return angle / 180.0*3.141592653549;
}
template<typename T,typename E>
void getEndPoint(T ix, T iy, E length, double direct, T * ox, T * oy)
{
	*ox = ix + length*cos(direct);
	*oy = iy + length*sin(direct);
}
template<typename T>
double getDistance(T x1, T y1, T x2, T y2)
{
	return sqrt(pow(x2-x1,2.0)+pow(y2-y1,2.0));
}

void drawArrow(POINT pstart,POINT endp)
{
	POINT tp;
	MoveToEx(bdc, endp.x, endp.y, &tp);
	LineTo(bdc, pstart.x, pstart.y);
	double direct = getLineDirection(endp.x, endp.y, pstart.x, pstart.y);
	double factor = AngleToRadian(15);
	double ldirect = direct - factor;
	double rdirect = direct + factor;
	double len = getDistance(endp.x, endp.y, pstart.x, pstart.y)*0.3;
	if (len < 3)len = 3;
	if (len>50)len = 50;
	POINT lend = { 0 };
	getEndPoint(endp.x, endp.y, len, ldirect, &lend.x, &lend.y);
	MoveToEx(bdc, endp.x, endp.y, &tp);
	LineTo(bdc, lend.x, lend.y);
	POINT rend = { 0 };
	getEndPoint(endp.x, endp.y, len, rdirect, &rend.x, &rend.y);
	MoveToEx(bdc, endp.x, endp.y, &tp);
	LineTo(bdc, rend.x, rend.y);
}
void LBtnUpProc(HWND hWnd, LPARAM lParam)
{
	POINT tp;

	switch (preDrawType)
	{
	case DT_Line:
		if (isLBtnDown)
		{
			MoveToEx(bdc, befPoint.x, befPoint.y, &tp);
			LineTo(bdc, LOWORD(lParam), HIWORD(lParam));
			InvalidateRect(hWnd, &wndrect, TRUE);
		}
		break;
	case DT_Arrow:
		{
			POINT endp = { LOWORD(lParam), HIWORD(lParam) };
			drawArrow(befPoint, endp);
			InvalidateRect(hWnd, &wndrect, TRUE);
		}
		break;
	case DT_Rectangle:
		if (isLBtnDown)
		{
			if (isCaptureMode)
			{
				captureRect.left = befPoint.x;
				captureRect.top = befPoint.y;
				captureRect.right = LOWORD(lParam);
				captureRect.bottom = HIWORD(lParam);
				HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
				HGDIOBJ nOldBrush = SelectObject(bdc, brush);
				Rectangle(bdc, befPoint.x, befPoint.y, LOWORD(lParam), HIWORD(lParam));
				InvalidateRect(hWnd, &wndrect, TRUE);
				SelectObject(bdc, nOldBrush);
				break;
			}
			Rectangle(bdc, befPoint.x, befPoint.y, LOWORD(lParam), HIWORD(lParam));
			InvalidateRect(hWnd, &wndrect, TRUE);
		}
		break;
	case DT_Elipese:
		if (isLBtnDown)
		{
			Ellipse(bdc, befPoint.x, befPoint.y, LOWORD(lParam), HIWORD(lParam));
			InvalidateRect(hWnd, &wndrect, TRUE);
		}
		break;
	default:
		break;
	}

	isLBtnDown = false;
}
void MouseMoveProc(HWND hWnd, LPARAM lParam)
{
	POINT tp;
	switch (preDrawType)
	{
	case DT_CirLine:
		if (isLBtnDown)
		{
			MoveToEx(bdc, befPoint.x, befPoint.y, &tp);
			LineTo(bdc, LOWORD(lParam), HIWORD(lParam));
			befPoint.x = LOWORD(lParam);
			befPoint.y = HIWORD(lParam);
			InvalidateRect(hWnd,&wndrect,TRUE);
		}
		break;
	default:
		break;
	}
}
void BuildBackgroundImg()
{
	bdc = CreateCompatibleDC(GetDC(NULL));
	BITMAPINFOHEADER stBmpInfoHeader = { 0 };
	int nBytesPerLine = ((screenx * 32 + 31) & (~31)) >> 3;
	stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	stBmpInfoHeader.biWidth = screenx;
	stBmpInfoHeader.biHeight = screeny;
	stBmpInfoHeader.biPlanes = 1;
	stBmpInfoHeader.biBitCount = 32;
	stBmpInfoHeader.biCompression = BI_RGB;
	stBmpInfoHeader.biClrUsed = 0;
	stBmpInfoHeader.biSizeImage = nBytesPerLine * screeny;
	PVOID pvBits = NULL;
	bdimg = ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, &pvBits, NULL, 0);
	SelectObject(bdc, bdimg);
}



BOOL CALLBACK InputBoxProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_PAINT:
	{
					 //���ÿؼ���ý�����Ҫ�ؼ�����ʾ��������Ч�����������ѡ��PAINT��������CREATE����CREATE�н�����Ч
					 SetForegroundWindow(hwndDlg);
					 SetActiveWindow(hwndDlg);
					 POINT posCur = { 0 };
					 GetCursorPos(&posCur);
					 RECT rect = { 0 };
					 GetWindowRect(hwndDlg, &rect);
					 SetWindowPos(hwndDlg, NULL, posCur.x-(rect.right-rect.left)/2, posCur.y-(rect.bottom-rect.top)/2, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
					 HWND hEdit = GetDlgItem(hwndDlg, IDC_EDIT_TEXT);
					 SetFocus(hEdit);

	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hwndDlg, IDC_EDIT_TEXT, inputLineArr, MAX_LINE_COUNT);
			GetDlgItemTextA(hwndDlg, IDC_EDIT_TEXT, inputLineArrAnsi, MAX_LINE_COUNT);
			EndDialog(hwndDlg, IDOK);
			break;
		}
	}
	return FALSE;
}
void RBtnDownProc(HWND hWnd, LPARAM lParam)
{
	if (isCtrlDown)
		ClearDrawEnv(hWnd);
	if (isShiftDown)
	{
		isShiftDown = false;
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DLG_INPUT), hWnd, InputBoxProc);
		int pcount = lstrlen(inputLineArr);
		if (pcount > 0)
		{
			TextOut(bdc, LOWORD(lParam), HIWORD(lParam), inputLineArr, pcount);
		}
		else
		{
			SYSTEMTIME sysTime = { 0 };
			GetLocalTime(&sysTime);
			TCHAR tpTime[1024] = { 0 };
			TCHAR weeks[][5] = { TEXT("��"), TEXT("һ"), TEXT("��"), TEXT("��"), TEXT("��"), TEXT("��"), TEXT("��") };
			_stprintf(tpTime, TEXT("%04d-%02d-%02d %02d:%02d:%02d %s"), sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, weeks[sysTime.wDayOfWeek]);
			TextOut(bdc, LOWORD(lParam), HIWORD(lParam), tpTime, lstrlen(tpTime));
		}
		InvalidateRect(hWnd, &wndrect, TRUE);
	}
}
