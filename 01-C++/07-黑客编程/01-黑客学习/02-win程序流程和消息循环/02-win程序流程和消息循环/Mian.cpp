#include"Win32App.h"
int WAWin32Main()
{
	if (FALSE == WADirectCreateWindow(hInstance, L"Win32消息处理", L"Win32MessageProcess", nCmdShow))
		return FALSE;
	return WAMessageLoop();
}