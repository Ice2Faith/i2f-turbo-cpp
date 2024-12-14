#ifndef _HIPSIL_H_
#define _HIPSIL_H_
#include<Windows.h>
#include<winsvc.h>
#include<stdio.h>
#include"InlineHook.h"
#define _DLLEXPORTAPI extern "C" __declspec(dllexport)
//DLL����
_DLLEXPORTAPI VOID SetHookOn(HWND hWnd);
_DLLEXPORTAPI VOID SetHookOff();

//���������
#pragma comment(linker,"/.shared,RWS")
//���س�����
#define MANAGER_WINDOW_TITLE TEXT("HIPS��Ϊ��ع���")

#include"HipsGuard.h"

//HOOK�Ŀ��غ���
VOID SetHookOn(HWND hWnd);
VOID SetHookOff();


//HOOK���͵��ܿ��غ���
void OpenHooks(HANDLE hModule);
void CloseHooks();
//��ȡ��Ϣ��HOOK�ص�����û����ʲô��ֻ��Ϊ��ע�����л�����Ϣ���Ƶ�Ӧ�ö�����
LRESULT CALLBACK GetMsgProc(
	int code,
	WPARAM wParam,
	LPARAM lParam);

//��������һЩϵͳAPI������HOOK���������ǵ�ԭ����Ҫ�Ͷ�Ӧ��ϵͳ����һ��
//������Ҫ����ϵͳ�������أ�����Ϣ���͸����س��򣬵ȴ����س������Ȩ�����ϵͳ��API���������򲻵��ã��൱�������˵��ã�
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
	);
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
	);
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
	);
LSTATUS APIENTRY MyRegSetValueExW(
	_In_ HKEY hKey,
	_In_opt_ LPCWSTR lpValueName,
	_Reserved_ DWORD Reserved,
	_In_ DWORD dwType,
	_In_reads_bytes_opt_(cbData) CONST BYTE * lpData,
	_In_ DWORD cbData
	);
LSTATUS APIENTRY MyRegSetValueExA(
	_In_ HKEY hKey,
	_In_opt_ LPCSTR lpValueName,
	_Reserved_ DWORD Reserved,
	_In_ DWORD dwType,
	_In_reads_bytes_opt_(cbData) CONST BYTE * lpData,
	_In_ DWORD cbData
	);
LSTATUS APIENTRY MyRegDeleteValueW(
	_In_ HKEY hKey,
	_In_opt_ LPCWSTR lpValueName
	);
LSTATUS APIENTRY MyRegDeleteValueA(
	_In_ HKEY hKey,
	_In_opt_ LPCSTR lpValueName
	);
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
	);
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
	);
UINT WINAPI MyWinExec(
	_In_ LPCSTR lpCmdLine,
	_In_ UINT uCmdShow
	);
HINSTANCE MyShellExecuteA(
	_In_opt_ HWND hwnd,
	_In_opt_ LPCSTR lpOperation,
	_In_ LPCSTR lpFile,
	_In_opt_ LPCSTR lpParameters,
	_In_opt_ LPCSTR lpDirectory,
	_In_ INT nShowCmd);
HINSTANCE MyShellExecuteW(
	_In_opt_ HWND hwnd,
	_In_opt_ LPCWSTR lpOperation,
	_In_ LPCWSTR lpFile,
	_In_opt_ LPCWSTR lpParameters,
	_In_opt_ LPCWSTR lpDirectory,
	_In_ INT nShowCmd);
BOOL WINAPI MyAdjustTokenPrivileges(
	_In_ HANDLE TokenHandle,
	_In_ BOOL DisableAllPrivileges,
	_In_opt_ PTOKEN_PRIVILEGES NewState,
	_In_ DWORD BufferLength,
	_Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
	_Out_opt_ PDWORD ReturnLength
	);
HANDLE WINAPI MyCreateFileA(
	_In_ LPCSTR lpFileName,
	_In_ DWORD dwDesiredAccess,
	_In_ DWORD dwShareMode,
	_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_In_ DWORD dwCreationDisposition,
	_In_ DWORD dwFlagsAndAttributes,
	_In_opt_ HANDLE hTemplateFile
	);
HANDLE WINAPI MyCreateFileW(
	_In_ LPCWSTR lpFileName,
	_In_ DWORD dwDesiredAccess,
	_In_ DWORD dwShareMode,
	_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_In_ DWORD dwCreationDisposition,
	_In_ DWORD dwFlagsAndAttributes,
	_In_opt_ HANDLE hTemplateFile
	);
BOOL WINAPI MyDeleteFileA(
	_In_ LPCSTR lpFileName
	);
BOOL WINAPI MyDeleteFileW(
	_In_ LPCWSTR lpFileName
	);
BOOL WINAPI MyMoveFileExA(
	_In_     LPCSTR lpExistingFileName,
	_In_opt_ LPCSTR lpNewFileName,
	_In_     DWORD    dwFlags
	);
BOOL WINAPI MyMoveFileExW(
	_In_     LPCWSTR lpExistingFileName,
	_In_opt_ LPCWSTR lpNewFileName,
	_In_     DWORD    dwFlags
	);
BOOL WINAPI MyCopyFileExA(
	_In_        LPCSTR lpExistingFileName,
	_In_        LPCSTR lpNewFileName,
	_In_opt_    LPPROGRESS_ROUTINE lpProgressRoutine,
	_In_opt_    LPVOID lpData,
	_When_(pbCancel != NULL, _Pre_satisfies_(*pbCancel == FALSE))
	_Inout_opt_ LPBOOL pbCancel,
	_In_        DWORD dwCopyFlags
	);
BOOL WINAPI MyCopyFileExW(
	_In_        LPCWSTR lpExistingFileName,
	_In_        LPCWSTR lpNewFileName,
	_In_opt_    LPPROGRESS_ROUTINE lpProgressRoutine,
	_In_opt_    LPVOID lpData,
	_When_(pbCancel != NULL, _Pre_satisfies_(*pbCancel == FALSE))
	_Inout_opt_ LPBOOL pbCancel,
	_In_        DWORD dwCopyFlags
	);
#endif //_HIPSIL_H_