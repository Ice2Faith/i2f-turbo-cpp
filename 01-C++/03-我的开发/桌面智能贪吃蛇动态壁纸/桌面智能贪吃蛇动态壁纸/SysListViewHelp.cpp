#include"stdafx.h"
#include "SysListViewHelp.h"


BOOL CALLBACK __EnumWindowProcFindWorkerOfShellDefViewWindow(HWND hTop, LPARAM lparam)
{
	HWND * hWorker = (HWND *)lparam;
	// ���� SHELLDLL_DefView ������
	// ���ڶ��WorkerW���壬ֻ�е��´���SHELLDLL_DefView�Ĳ���
	HWND hTemp = ::FindWindowEx(
		hTop, NULL, TEXT("SHELLDLL_DefView"), NULL);
	if (hTemp == NULL) {
		return TRUE;
	}
	//�ҵ����°���SHELLDLL_DefView�Ĵ���֮��ֹͣö�٣�ֱ�ӷ���
	*hWorker = hTop;
	return FALSE;
}

HWND getSysListView32Window()
{
	HWND hworker = NULL;
	// ���ҵ� WorkerW ���ڣ����°���SHELLDLL_DefView����һ��Worker
	EnumWindows(__EnumWindowProcFindWorkerOfShellDefViewWindow, (LPARAM)&hworker);
	HWND hshell = FindWindowEx(hworker, NULL, TEXT("SHELLDLL_DefView"), NULL);
	HWND hsyslist = FindWindowEx(hshell, NULL, TEXT("SysListView32"), NULL);
	return hsyslist;
}
//ֱ�ӿ��Ƹÿؼ����ء���ʾ����
bool setSysListView32ShowState(bool isShow)
{
	HWND hwnd = getSysListView32Window();
	BOOL ret = FALSE;
	if (isShow)
	{
		//ret = SendMessage(hwnd, LVM_REDRAWITEMS, 0, 10000);
		ret = ShowWindow(hwnd, SW_SHOW);
	}
	else
	{
		//���ʹ�ô˷�ʽ�����ᵼ����Ŀɾ���ˣ�û�취�ָ�����Ҫ�ֶ�F5
		//ret = SendMessage(hwnd, LVM_DELETEALLITEMS, 0, 0);
		ret = ShowWindow(hwnd, SW_HIDE);
	}

	return ret == TRUE;
}