#include"Win32App.h"
int WAWin32Main()
{
	if (FALSE == WADirectCreateWindow(hInstance, L"Win32��Ϣ����", L"Win32MessageProcess", nCmdShow))
		return FALSE;
	return WAMessageLoop();
}