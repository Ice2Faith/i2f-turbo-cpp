#include<Windows.h>
HWND FindDeskIconWindow()
{
	HWND hwnd = ::FindWindow(TEXT("Progman"), TEXT("Program Manager"));
	DWORD dResult = 0;
	const UINT WM_CREATE_WORKERW_WND = 0x052c;
	SendMessageTimeout(hwnd, WM_CREATE_WORKERW_WND, 0, NULL, SMTO_NORMAL, 1000, &dResult);
	HWND hWork = NULL;
	do
	{
		hWork = ::FindWindowEx(NULL, hWork, TEXT("WorkerW"), NULL);
		if (NULL == hWork)
		{
			continue;
		}
		HWND hView = ::FindWindowEx(hWork, NULL, TEXT("SHELLDLL_DefView"), NULL);
		if (NULL == hView)
		{
			continue;
		}
		HWND hp = ::FindWindowEx(NULL, hWork, TEXT("WorkerW"), NULL);
		while (NULL != hp)
		{
			SendMessage(hp, WM_CLOSE, 0, 0);
			hp = ::FindWindowEx(NULL, hWork, TEXT("WorkerW"), NULL);
		}
		break;
	} while (true);
	return hwnd;
}
void SetWindowToDesktopIconBackgroundFullScreen(HWND mHwnd)
{
	//��ȡ���洰��
	HWND fhwnd = FindDeskIconWindow();
	//����Ϊ�Ӵ���
	SetParent(mHwnd, fhwnd);
	//�������
	ShowWindow(mHwnd, SW_MAXIMIZE);
}