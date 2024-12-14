#include"Win32App.h"
ATOM WARegisterWindowClass(HINSTANCE hInstance, LPTSTR className)
{
	WNDCLASSEX wndCls;	//����ע����ṹ
	ZeroMemory(&wndCls, sizeof(WNDCLASSEX));	//�ṹ����
	wndCls.cbSize = sizeof(WNDCLASSEX);		//�ṹ���С�����ڵ��ú���ʱ�������ڲ����ֽṹ����
	wndCls.lpfnWndProc = WAWindowProc;		//��Ϣ���������ص��������ṩ��ϵͳ����
	wndCls.hInstance = hInstance;			//����ʵ�����
	wndCls.lpszClassName = className;		//ע��Ĵ�������
	wndCls.style = CS_HREDRAW | CS_VREDRAW;	//������ķ����ʽ
	wndCls.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME;	//������ı���ɫ
	wndCls.hCursor = LoadCursor(NULL, IDC_ARROW);		//���������ʽ��ʹ��ϵͳ�Դ���
	wndCls.hIcon = LoadIcon(NULL, IDI_APPLICATION);		//���س���ͼ�꣬ʹ��ϵͳ�Դ���
	wndCls.cbClsExtra = 0;		//������Ϣ����ʹ��
	wndCls.cbWndExtra = 0;
	return RegisterClassEx(&wndCls);		//ע�ᴰ����
}
BOOL WACreateWindowAndShow(HINSTANCE hInstance, int nCmdShow, LPTSTR className, LPTSTR wndName)
{
	HWND hWnd = NULL;		//���洰�ھ��
	hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,			//���ڷ��
		className,			//������Ҳ����ʹ�õ�����ǰ��ע����Ĵ���
		wndName,			//���ڱ��⣬���ߴ�������
		WS_OVERLAPPEDWINDOW,		//���ڷַ��
		CW_USEDEFAULT, CW_USEDEFAULT,		//������ʾ����
		CW_USEDEFAULT, CW_USEDEFAULT,		//���ڴ�С
		NULL, NULL, hInstance, NULL);		//�����ڣ��˵���ʵ�������һ������lpParam
	if (hWnd == NULL)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);		//��ʾ����
	UpdateWindow(hWnd);		//���´��ڣ��˴��ᷢ��WM_PAINT��Ϣ
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
		if (bRet == -1)//���������߽�Ҫ�˳�
		{
			break;
		}
		else	//����ͷַ���Ϣ
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
	switch (uMsg)		//������Ϣ����
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd,&ps);
		WADrawApplication(hWnd,hdc);
		EndPaint(hWnd,&ps);
		break;
	case WM_CLOSE:		//����������������
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
