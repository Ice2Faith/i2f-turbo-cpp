#include"HipsIL.h"
//共享数据段
#pragma data_seg(".shared")
HHOOK g_hHook = NULL;
#pragma data_seg()
//全局变量
HWND g_ExeHwnd = NULL;
HINSTANCE g_hInst = NULL;

VOID SetHookOn(HWND hWnd)
{
	g_ExeHwnd = hWnd;
	g_hHook=SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, g_hInst, 0);
}
VOID SetHookOff()
{
	UnhookWindowsHookEx(g_hHook);
	g_hHook = NULL;
}
//全局Hook控制对象
CInlineHook HookCreateProcessW;
CInlineHook HookCreateProcessA;
CInlineHook HookRegSetValueExW;
CInlineHook HookRegSetValueExA;
CInlineHook HookRegDeleteValueW;
CInlineHook HookRegDeleteValueA;
CInlineHook HookCreateServiceA;
CInlineHook HookCreateServiceW;
CInlineHook HookWinExec;
CInlineHook HookShellExecuteA;
CInlineHook HookShellExecuteW;
CInlineHook HookAdjustTokenPrivileges;
CInlineHook HookRegCreateKeyExA;
CInlineHook HookRegCreateKeyExW;
CInlineHook HookCreateFileA;
CInlineHook HookCreateFileW;
CInlineHook HookDeleteFileA;
CInlineHook HookDeleteFileW;
CInlineHook HookMoveFileExA;
CInlineHook HookMoveFileExW;
CInlineHook HookCopyFileExA;
CInlineHook HookCopyFileExW;

void OpenHooks(HANDLE hModule)
{
	g_hInst = (HINSTANCE)hModule;
	/*拿到对应DLL的地址，替换为自己的HOOK函数地址，开始HOOK*/
	HookCreateProcessW.Hook(
		TEXT("kernel32.dll"),
		"CreateProcessW",
		(PROC)MyCreateProcessW);
	HookCreateProcessA.Hook(
		TEXT("kernel32.dll"),
		"CreateProcessA",
		(PROC)MyCreateProcessA);
	HookShellExecuteA.Hook(
		TEXT("shell32.dll"),
		"ShellExecuteA",
		(PROC)MyShellExecuteA);
	HookShellExecuteW.Hook(
		TEXT("shell32.dll"),
		"ShellExecuteW",
		(PROC)MyShellExecuteW);
	HookWinExec.Hook(
		TEXT("kernel32.dll"),
		"WinExec",
		(PROC)MyWinExec);
	HookCreateServiceA.Hook(
		TEXT("advapi32.dll"),
		"CreateServiceA",
		(PROC)MyCreateServiceA);
	HookCreateServiceW.Hook(
		TEXT("advapi32.dll"),
		"CreateServiceW",
		(PROC)MyCreateServiceW);
	HookAdjustTokenPrivileges.Hook(
		TEXT("advapi32.dll"),
		"AdjustTokenPrivileges",
		(PROC)MyAdjustTokenPrivileges);
	HookCreateFileA.Hook(
		TEXT("kernel32.dll"),
		"CreateFileA",
		(PROC)MyCreateFileA);
	HookCreateFileW.Hook(
		TEXT("kernel32.dll"),
		"CreateFileW",
		(PROC)MyCreateFileW);
	HookDeleteFileA.Hook(
		TEXT("kernel32.dll"),
		"DeleteFileA",
		(PROC)MyDeleteFileA);
	HookDeleteFileW.Hook(
		TEXT("kernel32.dll"),
		"DeleteFileW",
		(PROC)MyDeleteFileW);
	HookMoveFileExA.Hook(
		TEXT("kernel32.dll"),
		"MoveFileExA",
		(PROC)MyMoveFileExA);
	HookMoveFileExW.Hook(
		TEXT("kernel32.dll"),
		"MoveFileExW",
		(PROC)MyMoveFileExW);
	HookCopyFileExA.Hook(
		TEXT("kernel32.dll"),
		"CopyFileExA",
		(PROC)MyCopyFileExA);
	HookCopyFileExA.Hook(
		TEXT("kernel32.dll"),
		"CopyFileExA",
		(PROC)MyCopyFileExA);

	HookRegSetValueExW.Hook(
		TEXT("advapi32.dll"),
		"RegSetValueExW",
		(PROC)MyRegSetValueExW);
	HookRegDeleteValueW.Hook(
		TEXT("advapi32.dll"),
		"RegDeleteValueW",
		(PROC)MyRegDeleteValueW);
	HookRegCreateKeyExA.Hook(
		TEXT("advapi32.dll"),
		"RegCreateKeyExA",
		(PROC)MyRegCreateKeyExA);
	HookRegCreateKeyExW.Hook(
		TEXT("advapi32.dll"),
		"RegCreateKeyExW",
		(PROC)MyRegCreateKeyExW);
}
void CloseHooks()
{
	HookCreateProcessW.UnHook();
	HookCreateProcessA.UnHook();
	HookShellExecuteA.UnHook();
	HookShellExecuteW.UnHook();
	HookWinExec.UnHook();
	HookCreateServiceA.UnHook();
	HookCreateServiceW.UnHook();
	HookAdjustTokenPrivileges.UnHook();
	HookCreateFileA.UnHook();
	HookCreateFileW.UnHook();
	HookDeleteFileA.UnHook();
	HookMoveFileExA.UnHook();
	HookMoveFileExW.UnHook();
	HookCopyFileExA.UnHook();
	HookCopyFileExW.UnHook();

	HookRegSetValueExW.UnHook();
	HookRegDeleteValueW.UnHook();
	HookRegCreateKeyExA.UnHook();
	HookRegCreateKeyExW.UnHook();

	if (g_hHook != NULL)
	{
		SetHookOff();
	}
}
LRESULT CALLBACK GetMsgProc(
	int code,
	WPARAM wParam,
	LPARAM lParam)
{
	return CallNextHookEx(g_hHook, code, wParam, lParam);
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
	//创建封包信息
	HIPS_INFO hips = { 0 };
	//判断是否是通过命令行传递的启动参数
	if (wcslen(lpCommandLine) != 0)
	{
		wsprintf(hips.wszHipsInfo, L"尝试创建进程：%s", lpCommandLine);
	}
	else
	{
		wsprintf(hips.wszHipsInfo, L"尝试创建进程：%s", lpApplicationName);
	}
	//给出请求类型
	hips.dwHipsClass = HIPS_CLASS_CREATE_PROCESSW;
	//给出字符串编码类型
	hips.bisAsciiInfo = FALSE;
	//封装好后发送封包信息给主控程序，等待回应
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	//返回值，和系统的API函数返回值保持一致
	BOOL bret = FALSE;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		//如果授权成功，就暂时取消HOOK，调用系统函数进行处理，系统函数处理完之后重新HOOK
		HookCreateProcessW.UnHook();
		bret = CreateProcessW(
			lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes,
			bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory,
			lpStartupInfo, lpProcessInformation);
		HookCreateProcessW.ReHook();
	}
	return bret;
}
BOOL WINAPI MyCreateProcessA(
	_In_opt_ LPCSTR lpApplicationName,
	_Inout_opt_ LPSTR lpCommandLine,
	_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
	_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
	_In_ BOOL bInheritHandles,
	_In_ DWORD dwCreationFlags,
	_In_opt_ LPVOID lpEnvironment,
	_In_opt_ LPCSTR lpCurrentDirectory,
	_In_ LPSTARTUPINFOA lpStartupInfo,
	_Out_ LPPROCESS_INFORMATION lpProcessInformation
	)
{
	HIPS_INFO hips = { 0 };
	if (strlen(lpCommandLine) != 0)
	{
		sprintf((char *)hips.wszHipsInfo, "尝试创建进程：%s", lpCommandLine);
	}
	else
	{
		sprintf((char *)hips.wszHipsInfo, "尝试创建进程：%s", lpApplicationName);
	}
	hips.dwHipsClass = HIPS_CLASS_CREATE_PROCESSA;
	hips.bisAsciiInfo = TRUE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	BOOL bret = FALSE;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookCreateProcessA.UnHook();
		bret = CreateProcessA(
			lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes,
			bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory,
			lpStartupInfo, lpProcessInformation);
		HookCreateProcessA.ReHook();
	}
	return bret;
}
LSTATUS APIENTRY MyRegCreateKeyExA(
	_In_ HKEY hKey,
	_In_ LPCSTR lpSubKey,
	_Reserved_ DWORD Reserved,
	_In_opt_ LPSTR lpClass,
	_In_ DWORD dwOptions,
	_In_ REGSAM samDesired,
	_In_opt_ CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_Out_ PHKEY phkResult,
	_Out_opt_ LPDWORD lpdwDisposition
	)
{
	HIPS_INFO hips = { 0 };
	sprintf((char *)hips.wszHipsInfo, "创建注册表子键:subKey=%s class=%s", lpSubKey, lpClass);
	hips.dwHipsClass = HIPS_CLASS_REG_CREATE_KEYEXA;
	hips.bisAsciiInfo = TRUE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	LSTATUS ret = 0;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookRegCreateKeyExA.UnHook();
		ret = RegCreateKeyExA(hKey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
		HookRegCreateKeyExA.ReHook();
	}
	return ret;
}

LSTATUS APIENTRY MyRegCreateKeyExW(
	_In_ HKEY hKey,
	_In_ LPCWSTR lpSubKey,
	_Reserved_ DWORD Reserved,
	_In_opt_ LPWSTR lpClass,
	_In_ DWORD dwOptions,
	_In_ REGSAM samDesired,
	_In_opt_ CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_Out_ PHKEY phkResult,
	_Out_opt_ LPDWORD lpdwDisposition
	)
{
	HIPS_INFO hips = { 0 };
	wsprintf(hips.wszHipsInfo, L"创建注册表子键:subKey=%s class=%s", lpSubKey, lpClass);
	hips.dwHipsClass = HIPS_CLASS_REG_CREATE_KEYEXW;
	hips.bisAsciiInfo = FALSE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	LSTATUS ret = 0;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookRegCreateKeyExW.UnHook();
		ret = RegCreateKeyExW(hKey,lpSubKey,Reserved,lpClass,dwOptions,samDesired,lpSecurityAttributes,phkResult,lpdwDisposition);
		HookRegCreateKeyExW.ReHook();
	}
	return ret;
}
LSTATUS APIENTRY MyRegSetValueExW(
	_In_ HKEY hKey,
	_In_opt_ LPCWSTR lpValueName,
	_Reserved_ DWORD Reserved,
	_In_ DWORD dwType,
	_In_reads_bytes_opt_(cbData) CONST BYTE * lpData,
	_In_ DWORD cbData
	)
{
	HIPS_INFO hips = { 0 };
	wsprintf(hips.wszHipsInfo, L"修改注册表值:valueName=%s type=%d valueData=%s", lpValueName, dwType, lpData);
	hips.dwHipsClass = HIPS_CLASS_REG_SET_VALUE_EXW;
	hips.bisAsciiInfo = FALSE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	LSTATUS ret = 0;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookRegSetValueExW.UnHook();
		ret = RegSetValueExW(hKey, lpValueName, Reserved, dwType, lpData, cbData);
		HookRegSetValueExW.ReHook();
	}
	return ret;
}
LSTATUS APIENTRY MyRegSetValueExA(
	_In_ HKEY hKey,
	_In_opt_ LPCSTR lpValueName,
	_Reserved_ DWORD Reserved,
	_In_ DWORD dwType,
	_In_reads_bytes_opt_(cbData) CONST BYTE * lpData,
	_In_ DWORD cbData
	)
{
	HIPS_INFO hips = { 0 };
	sprintf((char *)hips.wszHipsInfo, "修改注册表值:valueName=%s type=%d valueData=%s", lpValueName, dwType, lpData);
	hips.dwHipsClass = HIPS_CLASS_REG_SET_VALUE_EXW;
	hips.bisAsciiInfo = TRUE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	LSTATUS ret = 0;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookRegSetValueExA.UnHook();
		ret = RegSetValueExA(hKey, lpValueName, Reserved, dwType, lpData, cbData);
		HookRegSetValueExA.ReHook();
	}
	return ret;
}

LSTATUS APIENTRY MyRegDeleteValueW(
	_In_ HKEY hKey,
	_In_opt_ LPCWSTR lpValueName
	)
{
	HIPS_INFO hips = { 0 };
	wsprintf(hips.wszHipsInfo, L"删除注册表值:valueName=%s", lpValueName);
	hips.dwHipsClass = HIPS_CLASS_REG_DELETE_VALUEW;
	hips.bisAsciiInfo = FALSE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	LSTATUS ret = 0;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookRegDeleteValueW.UnHook();
		ret = RegDeleteValueW(hKey, lpValueName);
		HookRegDeleteValueW.ReHook();
	}
	return ret;
}
LSTATUS APIENTRY MyRegDeleteValueA(
	_In_ HKEY hKey,
	_In_opt_ LPCSTR lpValueName
	)
{
	HIPS_INFO hips = { 0 };
	sprintf((char *)hips.wszHipsInfo, "删除注册表值:valueName=%s", lpValueName);
	hips.dwHipsClass = HIPS_CLASS_REG_DELETE_VALUEW;
	hips.bisAsciiInfo = TRUE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	LSTATUS ret = 0;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookRegDeleteValueA.UnHook();
		ret = RegDeleteValueA(hKey, lpValueName);
		HookRegDeleteValueA.ReHook();
	}
	return ret;
}
SC_HANDLE WINAPI MyCreateServiceA(
	_In_        SC_HANDLE    hSCManager,
	_In_        LPCSTR     lpServiceName,
	_In_opt_    LPCSTR     lpDisplayName,
	_In_        DWORD        dwDesiredAccess,
	_In_        DWORD        dwServiceType,
	_In_        DWORD        dwStartType,
	_In_        DWORD        dwErrorControl,
	_In_opt_    LPCSTR     lpBinaryPathName,
	_In_opt_    LPCSTR     lpLoadOrderGroup,
	_Out_opt_   LPDWORD      lpdwTagId,
	_In_opt_    LPCSTR     lpDependencies,
	_In_opt_    LPCSTR     lpServiceStartName,
	_In_opt_    LPCSTR     lpPassword
	)
{
	HIPS_INFO hips = { 0 };
	sprintf((char *)hips.wszHipsInfo, "创建服务:displayName=%s serviceName=%s binaryPathName=%s serviceStartName=%s password=%s", 
		lpDisplayName,lpServiceName,lpBinaryPathName,lpServiceStartName,lpPassword);
	hips.dwHipsClass = HIPS_CLASS_CREATE_SERVICEA;
	hips.bisAsciiInfo = TRUE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	SC_HANDLE ret = NULL;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookCreateServiceA.UnHook();
		ret = CreateServiceA(hSCManager,lpServiceName,lpDisplayName,dwDesiredAccess,dwServiceType,dwStartType,dwErrorControl,
			lpBinaryPathName,lpLoadOrderGroup,lpdwTagId,lpDependencies,lpServiceStartName,lpPassword);
		HookCreateServiceA.ReHook();
	}
	return ret;
}

SC_HANDLE WINAPI MyCreateServiceW(
	_In_        SC_HANDLE    hSCManager,
	_In_        LPCWSTR     lpServiceName,
	_In_opt_    LPCWSTR     lpDisplayName,
	_In_        DWORD        dwDesiredAccess,
	_In_        DWORD        dwServiceType,
	_In_        DWORD        dwStartType,
	_In_        DWORD        dwErrorControl,
	_In_opt_    LPCWSTR     lpBinaryPathName,
	_In_opt_    LPCWSTR     lpLoadOrderGroup,
	_Out_opt_   LPDWORD      lpdwTagId,
	_In_opt_    LPCWSTR     lpDependencies,
	_In_opt_    LPCWSTR     lpServiceStartName,
	_In_opt_    LPCWSTR     lpPassword
	)
{
	HIPS_INFO hips = { 0 };
	wsprintf(hips.wszHipsInfo, L"创建服务:displayName=%s serviceName=%s binaryPathName=%s serviceStartName=%s password=%s",
		lpDisplayName, lpServiceName, lpBinaryPathName, lpServiceStartName, lpPassword);
	hips.dwHipsClass = HIPS_CLASS_CREATE_SERVICEW;
	hips.bisAsciiInfo = FALSE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	SC_HANDLE ret = NULL;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookCreateServiceW.UnHook();
		ret = CreateServiceW(hSCManager, lpServiceName, lpDisplayName, dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl,
			lpBinaryPathName, lpLoadOrderGroup, lpdwTagId, lpDependencies, lpServiceStartName, lpPassword);
		HookCreateServiceW.ReHook();
	}
	return ret;
}
UINT WINAPI MyWinExec(
	_In_ LPCSTR lpCmdLine,
	_In_ UINT uCmdShow
	)
{
	HIPS_INFO hips = { 0 };
	sprintf((char *)hips.wszHipsInfo, "WinExec创建进程:cmdLine=%s cmdShow=%s",lpCmdLine,uCmdShow);
	hips.dwHipsClass = HIPS_CLASS_WIN_EXEC;
	hips.bisAsciiInfo = TRUE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	UINT ret = 0;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookWinExec.UnHook();
		ret = WinExec(lpCmdLine,uCmdShow);
		HookWinExec.ReHook();
	}
	return ret;
}
HINSTANCE MyShellExecuteA(
	_In_opt_ HWND hwnd,
	_In_opt_ LPCSTR lpOperation,
	_In_ LPCSTR lpFile,
	_In_opt_ LPCSTR lpParameters,
	_In_opt_ LPCSTR lpDirectory,
	_In_ INT nShowCmd)
{
	HIPS_INFO hips = { 0 };
	sprintf((char *)hips.wszHipsInfo, "ShellExcute创建进程:operation=%s file=%s parameters=%s directory=%s showCmd=%d", 
		lpOperation,lpFile,lpParameters,lpDirectory,nShowCmd);
	hips.dwHipsClass = HIPS_CLASS_SHELL_EXECUTEA;
	hips.bisAsciiInfo = TRUE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	HINSTANCE ret = NULL;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookShellExecuteA.UnHook();
		ret = ShellExecuteA(hwnd,lpOperation,lpFile,lpParameters,lpDirectory,nShowCmd);
		HookShellExecuteA.ReHook();
	}
	return ret;
}
HINSTANCE MyShellExecuteW(
	_In_opt_ HWND hwnd,
	_In_opt_ LPCWSTR lpOperation,
	_In_ LPCWSTR lpFile,
	_In_opt_ LPCWSTR lpParameters,
	_In_opt_ LPCWSTR lpDirectory,
	_In_ INT nShowCmd)
{
	HIPS_INFO hips = { 0 };
	wsprintf(hips.wszHipsInfo, L"ShellExcute创建进程:operation=%s file=%s parameters=%s directory=%s showCmd=%d",
		lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd);
	hips.dwHipsClass = HIPS_CLASS_SHELL_EXECUTEW;
	hips.bisAsciiInfo = FALSE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	HINSTANCE ret = NULL;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookShellExecuteW.UnHook();
		ret = ShellExecuteW(hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd);
		HookShellExecuteW.ReHook();
	}
	return ret;
}
BOOL WINAPI MyAdjustTokenPrivileges(
	_In_ HANDLE TokenHandle,
	_In_ BOOL DisableAllPrivileges,
	_In_opt_ PTOKEN_PRIVILEGES NewState,
	_In_ DWORD BufferLength,
	_Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
	_Out_opt_ PDWORD ReturnLength
	)
{
	HIPS_INFO hips = { 0 };
	wsprintf(hips.wszHipsInfo, L"调整进程权限:Handle=%08x DisableAllPrivaleges=%d PrivalegeCount=%d Privaleges=%d",
		(DWORD)TokenHandle,DisableAllPrivileges,NewState->PrivilegeCount,NewState->Privileges[0]);
	hips.dwHipsClass = HIPS_CLASS_ADJUST_TOKEN_PRIVILEGES;
	hips.bisAsciiInfo = FALSE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	BOOL ret = FALSE;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookAdjustTokenPrivileges.UnHook();
		ret = AdjustTokenPrivileges(TokenHandle,DisableAllPrivileges,NewState,BufferLength,PreviousState,ReturnLength);
		HookAdjustTokenPrivileges.ReHook();
	}
	return ret;
}
HANDLE WINAPI MyCreateFileA(
	_In_ LPCSTR lpFileName,
	_In_ DWORD dwDesiredAccess,
	_In_ DWORD dwShareMode,
	_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_In_ DWORD dwCreationDisposition,
	_In_ DWORD dwFlagsAndAttributes,
	_In_opt_ HANDLE hTemplateFile
	)
{
	HIPS_INFO hips = { 0 };
	sprintf((char *)hips.wszHipsInfo, "%s文件:fileName=%s", 
		(dwCreationDisposition==CREATE_NEW || dwCreationDisposition==CREATE_ALWAYS?TEXT("创建"):
		(dwCreationDisposition == OPEN_ALWAYS || dwCreationDisposition == OPEN_EXISTING)?TEXT("打开"):TEXT("截断")),
		lpFileName);
	hips.dwHipsClass = HIPS_CLASS_CREATE_FILEA;
	hips.bisAsciiInfo = TRUE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	HANDLE ret = INVALID_HANDLE_VALUE;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookCreateFileA.UnHook();
		ret = CreateFileA(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,
			dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile);
		HookCreateFileA.ReHook();
	}
	return ret;
}

HANDLE WINAPI MyCreateFileW(
	_In_ LPCWSTR lpFileName,
	_In_ DWORD dwDesiredAccess,
	_In_ DWORD dwShareMode,
	_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_In_ DWORD dwCreationDisposition,
	_In_ DWORD dwFlagsAndAttributes,
	_In_opt_ HANDLE hTemplateFile
	)
{
	HIPS_INFO hips = { 0 };
	wsprintf(hips.wszHipsInfo, L"%s文件:fileName=%s",
		(dwCreationDisposition == CREATE_NEW || dwCreationDisposition == CREATE_ALWAYS ? TEXT("创建") :
		(dwCreationDisposition == OPEN_ALWAYS || dwCreationDisposition == OPEN_EXISTING) ? TEXT("打开") : TEXT("截断")),
		lpFileName);
	hips.dwHipsClass = HIPS_CLASS_CREATE_FILEW;
	hips.bisAsciiInfo = FALSE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	HANDLE ret = INVALID_HANDLE_VALUE;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookCreateFileW.UnHook();
		ret = CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
			dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
		HookCreateFileW.ReHook();
	}
	return ret;
}
BOOL WINAPI MyDeleteFileA(
	_In_ LPCSTR lpFileName
	)
{
	HIPS_INFO hips = { 0 };
	sprintf((char *)hips.wszHipsInfo, "删除文件:fileName=%s",
		lpFileName);
	hips.dwHipsClass = HIPS_CLASS_DELET_FILEA;
	hips.bisAsciiInfo = TRUE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	BOOL ret = FALSE;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookDeleteFileA.UnHook();
		ret = DeleteFileA(lpFileName);
		HookDeleteFileA.ReHook();
	}
	return ret;
}

BOOL WINAPI MyDeleteFileW(
	_In_ LPCWSTR lpFileName
	)
{
	HIPS_INFO hips = { 0 };
	wsprintf(hips.wszHipsInfo, L"删除文件:fileName=%s",
		lpFileName);
	hips.dwHipsClass = HIPS_CLASS_DELET_FILEW;
	hips.bisAsciiInfo = FALSE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	BOOL ret = FALSE;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookDeleteFileW.UnHook();
		ret = DeleteFileW(lpFileName);
		HookDeleteFileW.ReHook();
	}
	return ret;
}
BOOL WINAPI MyMoveFileExA(
	_In_     LPCSTR lpExistingFileName,
	_In_opt_ LPCSTR lpNewFileName,
	_In_     DWORD    dwFlags
	)
{
	HIPS_INFO hips = { 0 };
	sprintf((char *)hips.wszHipsInfo, "移动文件:srcFileName=%s dstFileName=%s",
		lpExistingFileName,lpNewFileName);
	hips.dwHipsClass = HIPS_CLASS_MOVE_FILEEXA;
	hips.bisAsciiInfo = TRUE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	BOOL ret = FALSE;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookMoveFileExA.UnHook();
		ret = MoveFileExA(lpExistingFileName,lpNewFileName,dwFlags);
		HookMoveFileExA.ReHook();
	}
	return ret;
}
BOOL WINAPI MyMoveFileExW(
	_In_     LPCWSTR lpExistingFileName,
	_In_opt_ LPCWSTR lpNewFileName,
	_In_     DWORD    dwFlags
	)
{
	HIPS_INFO hips = { 0 };
	wsprintf(hips.wszHipsInfo, L"移动文件:srcFileName=%s dstFileName=%s",
		lpExistingFileName, lpNewFileName);
	hips.dwHipsClass = HIPS_CLASS_MOVE_FILEEXW;
	hips.bisAsciiInfo = FALSE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	BOOL ret = FALSE;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookMoveFileExW.UnHook();
		ret = MoveFileExW(lpExistingFileName, lpNewFileName, dwFlags);
		HookMoveFileExW.ReHook();
	}
	return ret;
}
BOOL WINAPI MyCopyFileExA(
	_In_        LPCSTR lpExistingFileName,
	_In_        LPCSTR lpNewFileName,
	_In_opt_    LPPROGRESS_ROUTINE lpProgressRoutine,
	_In_opt_    LPVOID lpData,
	_When_(pbCancel != NULL, _Pre_satisfies_(*pbCancel == FALSE))
	_Inout_opt_ LPBOOL pbCancel,
	_In_        DWORD dwCopyFlags
	)
{
	HIPS_INFO hips = { 0 };
	sprintf((char *)hips.wszHipsInfo, "复制文件:srcFileName=%s dstFileName=%s",
		lpExistingFileName, lpNewFileName);
	hips.dwHipsClass = HIPS_CLASS_COPY_FILEEXA;
	hips.bisAsciiInfo = TRUE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	BOOL ret = FALSE;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookCopyFileExA.UnHook();
		ret = CopyFileExA(lpExistingFileName, lpNewFileName,lpProgressRoutine,lpData,pbCancel,dwCopyFlags);
		HookCopyFileExA.ReHook();
	}
	return ret;
}
BOOL WINAPI MyCopyFileExW(
	_In_        LPCWSTR lpExistingFileName,
	_In_        LPCWSTR lpNewFileName,
	_In_opt_    LPPROGRESS_ROUTINE lpProgressRoutine,
	_In_opt_    LPVOID lpData,
	_When_(pbCancel != NULL, _Pre_satisfies_(*pbCancel == FALSE))
	_Inout_opt_ LPBOOL pbCancel,
	_In_        DWORD dwCopyFlags
	)
{
	HIPS_INFO hips = { 0 };
	wsprintf(hips.wszHipsInfo, L"复制文件:srcFileName=%s dstFileName=%s",
		lpExistingFileName, lpNewFileName);
	hips.dwHipsClass = HIPS_CLASS_COPY_FILEEXW;
	hips.bisAsciiInfo = FALSE;
	COPYDATASTRUCT cds = { NULL, sizeof(HIPS_INFO), (void*)&hips };
	BOOL ret = FALSE;
	if (SendMessage(FindWindow(NULL, MANAGER_WINDOW_TITLE),
		WM_COPYDATA,
		GetCurrentProcessId(),
		(LPARAM)&cds) == HIPS_AUTH_AGREEN)
	{
		HookCopyFileExW.UnHook();
		ret = CopyFileExW(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, pbCancel, dwCopyFlags);
		HookCopyFileExW.ReHook();
	}
	return ret;
}