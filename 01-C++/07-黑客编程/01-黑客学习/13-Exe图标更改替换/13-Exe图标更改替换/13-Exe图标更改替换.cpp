// 13-Exeͼ������滻.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "13-Exeͼ������滻.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
// �����롱�����Ϣ�������
INT_PTR CALLBACK InputBox(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL SetExeIcon(char * resFileName, char * destFileName);

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
	LoadString(hInstance, IDC_MY13EXE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY13EXE));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_SELF));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY13EXE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON_SELF));

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
		case ID_ICON_REPLACE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DLG_INPUTBOX), hWnd, InputBox);
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
// �����롱�����Ϣ�������
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
						 MessageBoxA(NULL, "ͼ���滻�ɹ�������������Ҫ����Explorerˢ�»��档", "������ʾ", MB_OK);
					 else
						 MessageBoxA(NULL, "ͼ���滻ʧ�ܣ�������ѡ�ļ��Ƿ���exe�ļ���", "������ʾ", MB_OK);
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

///////////////////////////////////////////////////////
/*
	ͼ���滻��
		��һ�����г����ͼ��ȥ�滻��һ�������ͼ��
		������BOOL SetExeIcon(char * resFileName, char * destFileName);
		��������鿴����Ĵ���ʵ��
	ͼ���������ߣ�
		Icofx3
	Shellcode:
		һ�ο�ִ�еĴ��루���ݣ������磺x02 x5c x63 xf4
		Ҳ����ֱ�Ӷ����Ʊ�д��ִ�д���
	�����Ʋ鿴���ߣ�
		WinHex
	��ȡ��ǰ����·����
		char modelName[MAX_PATH];
		GetModuleFileName(NULL, modelName, MAX_PATH);
*/
//�滻ͼ��
BOOL SetRes(LPTSTR destFileName, LPTSTR szType, LPTSTR szName, LPVOID pdata, DWORD dataSize)
{
	//��ʼ������Դ
	HANDLE handle = BeginUpdateResource(destFileName, FALSE);//TRUEʱɾ�������Դ
	if(handle==NULL)
	{
		return FALSE;
	}
	//������Դ
	int ret = UpdateResource(handle, szType, szName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), pdata, dataSize);
	if (!ret)
		return FALSE;
	//��������
	EndUpdateResource(handle, FALSE);//TRUEʱ�������κβ�����Ҳ�Ͳ��ᱣ���޸�
	return TRUE;
}
//ö����Դ�ص�����
BOOL CALLBACK EnumResProc(HMODULE hmod, LPCTSTR szType, LPTSTR szName, LONG lParam)
{
	//������Դ
	HRSRC hres = FindResource(hmod, szName, RT_ICON);
	if (hres == NULL)
		return FALSE;
	//������Դ
	HGLOBAL hload = LoadResource(hmod, hres);
	if (hload == NULL)
		return FALSE;
	//������Դ
	LPVOID pdata = LockResource(hload);
	if (pdata == NULL)
		return FALSE;
	//��ȡ��Դ��С
	DWORD psize = SizeofResource(hmod, hres);
	//������Դ
	return SetRes((LPTSTR)lParam, RT_ICON, szName, pdata, psize);

}
//��һ�������ͼ���滻��һ�������ͼ��
BOOL SetExeIcon(char * resFileName, char * destFileName)
{
	//����Դ�ļ�
	HMODULE hmod=LoadLibrary(resFileName);
	if (hmod == NULL)
		return FALSE;
	//ö����ԴICON
	return EnumResourceNames(hmod, RT_ICON, EnumResProc, (long)destFileName);
}