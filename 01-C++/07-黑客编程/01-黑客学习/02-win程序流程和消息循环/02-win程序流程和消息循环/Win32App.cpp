#include"Win32App.h"
ATOM WARegisterWindowClass(HINSTANCE hInstance, LPTSTR className)
{
	WNDCLASSEX wndCls;	//窗口注册类结构
	ZeroMemory(&wndCls, sizeof(WNDCLASSEX));	//结构清零
	wndCls.cbSize = sizeof(WNDCLASSEX);		//结构体大小，用于调用函数时，函数内部区分结构类型
	wndCls.lpfnWndProc = WAWindowProc;		//消息处理函数，回调函数，提供给系统调用
	wndCls.hInstance = hInstance;			//程序实例句柄
	wndCls.lpszClassName = className;		//注册的窗口类名
	wndCls.style = CS_HREDRAW | CS_VREDRAW;	//窗口类的风格样式
	wndCls.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME;	//窗口类的背景色
	wndCls.hCursor = LoadCursor(NULL, IDC_ARROW);		//加载鼠标样式，使用系统自带的
	wndCls.hIcon = LoadIcon(NULL, IDI_APPLICATION);		//加载程序图标，使用系统自带的
	wndCls.cbClsExtra = 0;		//附加信息，不使用
	wndCls.cbWndExtra = 0;
	return RegisterClassEx(&wndCls);		//注册窗口类
}
BOOL WACreateWindowAndShow(HINSTANCE hInstance, int nCmdShow, LPTSTR className, LPTSTR wndName)
{
	HWND hWnd = NULL;		//保存窗口句柄
	hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,			//窗口风格
		className,			//类名，也就是使用的类风格，前面注册过的窗口
		wndName,			//窗口标题，或者窗口名称
		WS_OVERLAPPEDWINDOW,		//窗口分风格
		CW_USEDEFAULT, CW_USEDEFAULT,		//窗口显示坐标
		CW_USEDEFAULT, CW_USEDEFAULT,		//窗口大小
		NULL, NULL, hInstance, NULL);		//父窗口，菜单，实例句柄，一个参数lpParam
	if (hWnd == NULL)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);		//显示窗口
	UpdateWindow(hWnd);		//更新窗口，此处会发出WM_PAINT消息
	return TRUE;
}
BOOL WADirectCreateWindow(HINSTANCE hInstance, LPTSTR wndName, LPTSTR className, int nCmdShow)
{
	if (0 == WARegisterWindowClass(hInstance, className))
		return FALSE;
	if (WACreateWindowAndShow(hInstance, nCmdShow, className, wndName) == FALSE)
		return FALSE;
	return TRUE;
}
WPARAM WAMessageLoop()
{
	MSG msg;
	BOOL bRet;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)//句柄错误或者将要退出
		{
			break;
		}
		else	//翻译和分发消息
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}
LRESULT CALLBACK WAWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (uMsg)		//进行消息处理
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd,&ps);
		WADrawApplication(hWnd,hdc);
		EndPaint(hWnd,&ps);
		break;
	case WM_CLOSE:		//结束窗口生命周期
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return TRUE;
}
void WADrawApplication(HWND hWnd, HDC hdc)
{
	RECT rect;
	GetClientRect(hWnd,&rect);
	DrawText(hdc,L"Hello Win32",lstrlen(L"Hello Win32"),&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}
