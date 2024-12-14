#include<Windows.h>
#include"InlineHook.h"
//��ӹ������ݶ�
#pragma data_seg(".shared")
HHOOK g_hHook = NULL;
#pragma data_seg()
//�������ӷ�ʽΪ�����
#pragma comment(linker,"/.shared,RWS")
#define _DLLEXPORT extern "C" __declspec(dllexport)
//���DLL��������
_DLLEXPORT VOID SetHookOn(HWND hWnd);
_DLLEXPORT VOID SetHookOff();
//ȫ�ֱ������������
HWND g_ExeHwnd = NULL;
HINSTANCE g_hInst = NULL;
//HOOK�Ļص�����
LRESULT CALLBACK GetMsgProc(
	int code,
	WPARAM wParam,
	LPARAM lParam)
{
	return CallNextHookEx(g_hHook, code, wParam, lParam);
}
//�������Ļ�����Ϣ���ƵĴ��ھ���DLL����ע��
VOID SetHookOn(HWND hWnd)
{
	g_ExeHwnd = hWnd;
	//����Windows��HOOK���ӣ���GetMessage����HOOK��������ʵ���ˣ��ܹ������л�����Ϣ���Ƶ�Ӧ�õ�HOOK
	SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, g_hInst, 0);
}

VOID SetHookOff()
{	
	//ж��HOOK����
	UnhookWindowsHookEx(g_hHook);
	g_hHook = NULL;
}
//�Զ����滻�Ĵ������̺���������UNICODE�ֽڵģ�������������CSDN�õ�������F12�õ�֮���һ������
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
//����һ�����������̵�HOOK����
CInlineHook CreateProcessWHook;

/*DLL��������������ʱ������ɶ�Ӧ�Ķ���*/
BOOL APIENTRY DllMain(
	HANDLE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
							   //����ʹ�ÿ��ʱ�����HOOK
							   g_hInst = (HINSTANCE)hModule;
							   CreateProcessWHook.Hook(
								   TEXT("kernel32.dll"),
								   "CreateProcessW",
								   (PROC)MyCreateProcessW);
							  
	}
		break;
	case DLL_PROCESS_DETACH:
	{
							   //���̽�����ʱ�����HOOK
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
	//����һ����Ϣ��ʾ�򣬵ȴ��û�ȷ�Ϻ����ϵͳԭ���Ĵ������̺��������򲻵��ã��������൱�ڱ�������
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
	if (MessageBox(NULL,tips,TEXT("���ֳ��Դ������̣��Ƿ���������"),MB_OKCANCEL)==IDOK)
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
