#include<Windows.h>
#include"InlineHook.h"
//添加共享数据段
#pragma data_seg(".shared")
HHOOK g_hHook = NULL;
#pragma data_seg()
//定义连接方式为共享库
#pragma comment(linker,"/.shared,RWS")
#define _DLLEXPORT extern "C" __declspec(dllexport)
//添加DLL函数导出
_DLLEXPORT VOID SetHookOn(HWND hWnd);
_DLLEXPORT VOID SetHookOff();
//全局变量，方便调用
HWND g_ExeHwnd = NULL;
HINSTANCE g_hInst = NULL;
//HOOK的回调函数
LRESULT CALLBACK GetMsgProc(
	int code,
	WPARAM wParam,
	LPARAM lParam)
{
	return CallNextHookEx(g_hHook, code, wParam, lParam);
}
//对新增的基于消息机制的窗口尽心DLL内联注入
VOID SetHookOn(HWND hWnd)
{
	g_ExeHwnd = hWnd;
	//设置Windows的HOOK钩子，对GetMessage进行HOOK，这样就实现了，能够对所有基于消息机制的应用的HOOK
	SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, g_hInst, 0);
}

VOID SetHookOff()
{	
	//卸载HOOK钩子
	UnhookWindowsHookEx(g_hHook);
	g_hHook = NULL;
}
//自定义替换的创建进程函数，基于UNICODE字节的，这个定义可以在CSDN拿到，或者F12拿到之后改一下名字
BOOL WINAPI MyCreateProcessW(
	_In_opt_ LPCWSTR lpApplicationName,
	_Inout_opt_ LPWSTR lpCommandLine,
	_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
	_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
	_In_ BOOL bInheritHandles,
	_In_ DWORD dwCreationFlags,
	_In_opt_ LPVOID lpEnvironment,
	_In_opt_ LPCWSTR lpCurrentDirectory,
	_In_ LPSTARTUPINFOW lpStartupInfo,
	_Out_ LPPROCESS_INFORMATION lpProcessInformation
	);
//定义一个管理创建进程的HOOK对象
CInlineHook CreateProcessWHook;

/*DLL主函数，检测加载时机，完成对应的动作*/
BOOL APIENTRY DllMain(
	HANDLE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
							   //进程使用库的时候进行HOOK
							   g_hInst = (HINSTANCE)hModule;
							   CreateProcessWHook.Hook(
								   TEXT("kernel32.dll"),
								   "CreateProcessW",
								   (PROC)MyCreateProcessW);
							  
	}
		break;
	case DLL_PROCESS_DETACH:
	{
							   //进程结束的时候结束HOOK
							   CreateProcessWHook.UnHook();
							   if (g_hHook != NULL)
							   {
								   SetHookOff(); 
							   }
							   
	}
		break;
	}
	return TRUE;
}
BOOL WINAPI MyCreateProcessW(
	_In_opt_ LPCWSTR lpApplicationName,
	_Inout_opt_ LPWSTR lpCommandLine,
	_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
	_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
	_In_ BOOL bInheritHandles,
	_In_ DWORD dwCreationFlags,
	_In_opt_ LPVOID lpEnvironment,
	_In_opt_ LPCWSTR lpCurrentDirectory,
	_In_ LPSTARTUPINFOW lpStartupInfo,
	_Out_ LPPROCESS_INFORMATION lpProcessInformation
	)
{
	//构造一个消息提示框，等待用户确认后调用系统原来的创建进程函数，否则不调用，结束，相当于被拦截了
	WCHAR tips[MAXBYTE] = { 0 };
	if (wcslen(lpCommandLine) != 0)
	{
		wcscpy(tips, lpCommandLine);
	}
	else
	{
		wcscpy(tips, lpApplicationName);
	}
	
	BOOL bret = FALSE;
	if (MessageBox(NULL,tips,TEXT("发现尝试创建进程，是否允许创建？"),MB_OKCANCEL)==IDOK)
	{
		CreateProcessWHook.UnHook();
		bret = CreateProcessW(
			lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes,
			bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory,
			lpStartupInfo, lpProcessInformation);
		CreateProcessWHook.ReHook();
	}
	return bret;
}
