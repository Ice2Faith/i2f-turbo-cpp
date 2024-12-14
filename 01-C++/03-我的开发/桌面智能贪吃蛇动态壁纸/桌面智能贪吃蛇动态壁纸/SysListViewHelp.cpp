#include"stdafx.h"
#include "SysListViewHelp.h"


BOOL CALLBACK __EnumWindowProcFindWorkerOfShellDefViewWindow(HWND hTop, LPARAM lparam)
{
	HWND * hWorker = (HWND *)lparam;
	// 查找 SHELLDLL_DefView 窗体句柄
	// 存在多个WorkerW窗体，只有底下存在SHELLDLL_DefView的才是
	HWND hTemp = ::FindWindowEx(
		hTop, NULL, TEXT("SHELLDLL_DefView"), NULL);
	if (hTemp == NULL) {
		return TRUE;
	}
	//找到底下包含SHELLDLL_DefView的窗口之后，停止枚举，直接返回
	*hWorker = hTop;
	return FALSE;
}

HWND getSysListView32Window()
{
	HWND hworker = NULL;
	// 查找到 WorkerW 窗口，底下包含SHELLDLL_DefView的那一个Worker
	EnumWindows(__EnumWindowProcFindWorkerOfShellDefViewWindow, (LPARAM)&hworker);
	HWND hshell = FindWindowEx(hworker, NULL, TEXT("SHELLDLL_DefView"), NULL);
	HWND hsyslist = FindWindowEx(hshell, NULL, TEXT("SysListView32"), NULL);
	return hsyslist;
}
//直接控制该控件隐藏、显示即可
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
		//如果使用此方式，将会导致项目删除了，没办法恢复，需要手动F5
		//ret = SendMessage(hwnd, LVM_DELETEALLITEMS, 0, 0);
		ret = ShowWindow(hwnd, SW_HIDE);
	}

	return ret == TRUE;
}