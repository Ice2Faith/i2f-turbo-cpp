#ifndef _ALGO_WIN_PROCESS_HPP_
#define _ALGO_WIN_PROCESS_HPP_
#include<Windows.h>
#include"AlgoString.hpp"

//URLDownloadToFile “¿¿µ£∫
#include<urlmon.h>
#pragma comment(lib,"urlmon")
//√∂æŸΩ¯≥Ã“¿¿µ
#include<TlHelp32.h>
class AlgoWinProcess
{
public:
	static UINT winExec(const char * cmdLine, UINT nCmdShow = SW_SHOW)
	{
		return WinExec(cmdLine, nCmdShow);
	}
	static UINT winExecHide(const char * cmdLine)
	{
		return WinExec(cmdLine, SW_HIDE);
	}
	static HRESULT urlDownloader(const TCHAR * url, const TCHAR * saveFileName)
	{
		return URLDownloadToFile(NULL, url, saveFileName, 0, NULL);
	}
	static bool createProcess(const TCHAR * lpExecuableFileName, TCHAR * cmdArgument,
		LPVOID lpEnvironmentVal = NULL, const TCHAR * lpCurrentDirectory = NULL,
		LPSTARTUPINFO lpStartUpInfo = NULL, LPPROCESS_INFORMATION lpSaveProcessInfo = NULL,
		BOOL isSupportInheritProccess = FALSE, DWORD createFlag = 0,
		LPSECURITY_ATTRIBUTES lpProcessSecAttr = NULL, LPSECURITY_ATTRIBUTES lpThreadSecAttr = NULL)
	{
		return 0 != CreateProcess(lpExecuableFileName, cmdArgument, lpProcessSecAttr, lpThreadSecAttr, isSupportInheritProccess, createFlag, lpEnvironmentVal, lpCurrentDirectory, lpStartUpInfo, lpSaveProcessInfo);
	}
	static bool directCreateProcess(const TCHAR * lpExecuableFileName, TCHAR * cmdLineArg)
	{
		PROCESS_INFORMATION pi = { 0 };
		STARTUPINFO si = { 0 };
		BOOL ret = CreateProcess(lpExecuableFileName, cmdLineArg, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		return 0 != ret;
	}
	static bool directCreateRedirectProcess(const TCHAR * lpExecuableFileName, TCHAR * cmdLineArg, HANDLE hStdInput, HANDLE hStdOutput, HANDLE hStdError)
	{
		PROCESS_INFORMATION pi = { 0 };
		STARTUPINFO si = { 0 };
		si.hStdInput = hStdInput;
		si.hStdOutput = hStdOutput;
		si.hStdError = hStdError;
		BOOL ret = CreateProcess(lpExecuableFileName, cmdLineArg, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		return 0 != ret;
	}
	static DWORD getThreadProcessIdByWindow(HWND targetWind, LPDWORD saveProcessId)
	{
		return GetWindowThreadProcessId(targetWind, saveProcessId);
	}
	static HANDLE openProcess(DWORD targetProcessId, DWORD needAccessPermission = PROCESS_ALL_ACCESS, BOOL isSupportInherit = FALSE)
	{
		return OpenProcess(needAccessPermission, isSupportInherit, targetProcessId);
	}
	static bool terminateProcess(HANDLE targetProcessHandle, UINT exitCode = 0)
	{
		return 0 != TerminateProcess(targetProcessHandle, exitCode);
	}
	static bool directTerminateWindow(HWND targetHwnd)
	{
		DWORD processId = 0;
		GetWindowThreadProcessId(targetHwnd, &processId);
		HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
		if (processHandle != INVALID_HANDLE_VALUE)
		{
			BOOL ret = TerminateProcess(processHandle, 0);
			CloseHandle(processHandle);
			return ret != 0;
		}
		return false;
	}

	static HANDLE createSnapshot(DWORD enumShapshotFlag, DWORD fromProcessId = 0)
	{
		return CreateToolhelp32Snapshot(enumShapshotFlag, fromProcessId);
	}
	static HANDLE createProcessSnapshot()
	{
		return CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	}
	static HANDLE createThreadSnapshot()
	{
		return CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	}
	static HANDLE createModuleSnapshot(DWORD processId)
	{
		return CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
	}

	static bool findFirstProcess(HANDLE hSnapshot, LPPROCESSENTRY32 lppe)
	{
		return 0 != Process32First(hSnapshot, lppe);
	}
	static bool findNextProcess(HANDLE hSnapshot, LPPROCESSENTRY32 lppe)
	{
		return 0 != Process32Next(hSnapshot, lppe);
	}
	static AlgoArray<PROCESSENTRY32, int>& enumerateAllProcessData(AlgoArray<PROCESSENTRY32, int>& saveArr)
	{
		saveArr.setSize(0);
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hSnap == INVALID_HANDLE_VALUE)
			return saveArr;
		PROCESSENTRY32 pe32 = { 0 };
		pe32.dwSize = sizeof(PROCESSENTRY32);
		int i = 0;
		BOOL ret = Process32First(hSnap, &pe32);
		while (ret)
		{
			saveArr.push(pe32);
			i++;
			pe32.dwSize = sizeof(PROCESSENTRY32);
			ret = Process32Next(hSnap, &pe32);
		}
		CloseHandle(hSnap);
		return saveArr;
	}
	static bool findFirstModule(HANDLE hSnap, LPMODULEENTRY32 lpme)
	{
		return 0 != Module32First(hSnap, lpme);
	}
	static bool findNextModule(HANDLE hSnap, LPMODULEENTRY32 lpme)
	{
		return 0 != Module32Next(hSnap, lpme);
	}
	static AlgoArray<MODULEENTRY32, int>& enumerateAllModuleData(DWORD processId, AlgoArray<MODULEENTRY32, int>& saveArr)
	{
		saveArr.setSize(0);
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
		if (hSnap == INVALID_HANDLE_VALUE)
			return saveArr;
		MODULEENTRY32 me32 = { 0 };
		me32.dwSize = sizeof(MODULEENTRY32);
		int i = 0;
		BOOL ret = Module32First(hSnap, &me32);
		while (ret)
		{
			saveArr.push(me32);
			i++;
			saveArr[i].dwSize = sizeof(MODULEENTRY32);
			ret = Module32Next(hSnap, &me32);
		}
		CloseHandle(hSnap);
		return saveArr;
	}
	static bool findFirstThread(HANDLE hSnap, LPTHREADENTRY32 lpte)
	{
		return 0 != Thread32First(hSnap, lpte);
	}
	static bool findNextThread(HANDLE hSnap, LPTHREADENTRY32 lpte)
	{
		return 0 != Thread32Next(hSnap, lpte);
	}
	static AlgoArray<THREADENTRY32, int>& enumerateAllThreadData(DWORD processId, AlgoArray<THREADENTRY32, int>& saveArr)
	{
		saveArr.setSize(0);
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, processId);
		if (hSnap == INVALID_HANDLE_VALUE)
			return saveArr;
		THREADENTRY32 te32 = { 0 };
		te32.dwSize = sizeof(THREADENTRY32);
		int i = 0;
		BOOL ret = Thread32First(hSnap, &te32);
		while (ret)
		{
			saveArr.push(te32);
			i++;
			saveArr[i].dwSize = sizeof(THREADENTRY32);
			ret = Thread32Next(hSnap, &te32);
		}
		CloseHandle(hSnap);
		return saveArr;
	}
	static bool adjustProcessPermission(HANDLE processHandle, const TCHAR * permissionName = SE_DEBUG_NAME)
	{
		HANDLE hToken = NULL;
		BOOL ret = OpenProcessToken(processHandle, TOKEN_ALL_ACCESS, &hToken);
		if (ret == TRUE)
		{
			TOKEN_PRIVILEGES tp;
			tp.PrivilegeCount = 1;
			LookupPrivilegeValue(NULL, permissionName, &tp.Privileges[0].Luid);
			tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
			CloseHandle(hToken);
			return true;
		}
		return false;
	}

	static bool pauseProcess(DWORD processId)
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, processId);
		if (hSnap == INVALID_HANDLE_VALUE)
			return false;
		THREADENTRY32 te32 = { 0 };
		te32.dwSize = sizeof(THREADENTRY32);
		BOOL ret = Thread32First(hSnap, &te32);
		while (ret)
		{
			if (te32.th32OwnerProcessID == processId)
			{
				HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
				SuspendThread(hThread);
				CloseHandle(hThread);
			}
			ret = Thread32Next(hSnap, &te32);
		}
		CloseHandle(hSnap);
		return true;
	}
	static bool continueProcess(DWORD processId)
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, processId);
		if (hSnap == INVALID_HANDLE_VALUE)
			return false;
		THREADENTRY32 te32 = { 0 };
		te32.dwSize = sizeof(THREADENTRY32);
		BOOL ret = Thread32First(hSnap, &te32);
		while (ret)
		{
			if (te32.th32OwnerProcessID == processId)
			{
				HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
				ResumeThread(hThread);
				CloseHandle(hThread);
			}
			ret = Thread32Next(hSnap, &te32);
		}
		CloseHandle(hSnap);
		return true;
	}

};

#endif // _ALGO_WIN_PROCESS_HPP_