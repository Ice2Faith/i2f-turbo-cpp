#ifndef _ALGO_WIN_SERVICE_HPP_
#define _ALGO_WIN_SERVICE_HPP_
#include<Windows.h>

#include<winnt.h>
#include<winsvc.h>
class AlgoWinService
{
public:
	static SC_HANDLE openSvcManager(DWORD needAccessPermission = SC_MANAGER_ALL_ACCESS, const TCHAR * lpComputerName = NULL, const TCHAR * lpDatabaseName = NULL)
	{
		return OpenSCManager(lpComputerName, lpDatabaseName, needAccessPermission);
	}
	static bool closeSvcHandle(SC_HANDLE hScHandle)
	{
		return 0 != CloseServiceHandle(hScHandle);
	}
	static bool enumerateServiceStatus(SC_HANDLE hSvcManager, DWORD needSvcType, DWORD needSvcStatus, LPENUM_SERVICE_STATUS lpSaveSvcBuf, DWORD bufSize, LPDWORD saveNeedBufSize, LPDWORD saveServiceCount, LPDWORD isSucccessEnum)
	{
		return 0 != EnumServicesStatus(hSvcManager, needSvcType, needSvcStatus, lpSaveSvcBuf, bufSize, saveNeedBufSize, saveServiceCount, isSucccessEnum);
	}
	static LPENUM_SERVICE_STATUS enumerateAllTypeServiceActiveStatusData(SC_HANDLE hSvcManager, LPDWORD saveServiceCount)
	{
		return enumerateServiceStatusData(hSvcManager, SERVICE_TYPE_ALL, SERVICE_ACTIVE, saveServiceCount);
	}
	static LPENUM_SERVICE_STATUS enumerateAllTypeServiceAllStatusData(SC_HANDLE hSvcManager, LPDWORD saveServiceCount)
	{
		return enumerateServiceStatusData(hSvcManager, SERVICE_TYPE_ALL, SERVICE_STATE_ALL, saveServiceCount);
	}
	static LPENUM_SERVICE_STATUS enumerateWin32TypeServiceAllStatusData(SC_HANDLE hSvcManager, LPDWORD saveServiceCount)
	{
		return enumerateServiceStatusData(hSvcManager, SERVICE_WIN32, SERVICE_STATE_ALL, saveServiceCount);
	}
	static LPENUM_SERVICE_STATUS enumerateDriverTypeServiceAllStatusData(SC_HANDLE hSvcManager, LPDWORD saveServiceCount)
	{
		return enumerateServiceStatusData(hSvcManager, SERVICE_DRIVER, SERVICE_STATE_ALL, saveServiceCount);
	}
	static LPENUM_SERVICE_STATUS enumerateServiceAllStatusData(SC_HANDLE hSvcManager, DWORD needSvcType, LPDWORD saveServiceCount)
	{
		return enumerateServiceStatusData(hSvcManager, needSvcType, SERVICE_STATE_ALL, saveServiceCount);
	}
	static LPENUM_SERVICE_STATUS enumerateServiceStatusData(SC_HANDLE hSvcManager, DWORD needSvcType, DWORD needSvcStatus, LPDWORD saveServiceCount)
	{
		DWORD haveCount = 0;
		DWORD needSize = 0;
		BOOL ret = EnumServicesStatus(hSvcManager, needSvcType, needSvcStatus, NULL, 0, &needSize, &haveCount, NULL);
		if (!ret && GetLastError() == ERROR_MORE_DATA)
		{
			LPENUM_SERVICE_STATUS lpInfo = (LPENUM_SERVICE_STATUS)(new BYTE[needSize]);
			ret = EnumServicesStatus(hSvcManager, needSvcType, needSvcStatus, lpInfo, needSize, &needSize, &haveCount, NULL);
			*saveServiceCount = haveCount;
			return lpInfo;
		}
		else
		{
			*saveServiceCount = 0;
			return NULL;
		}
	}
	static void freeEnumServiceStatusData(LPENUM_SERVICE_STATUS lpServices)
	{
		if (lpServices != NULL)
			delete[] lpServices;
	}
	static SC_HANDLE openService(SC_HANDLE hSvcManager, const TCHAR * targetServiceName, DWORD needAccessPermission = SC_MANAGER_ALL_ACCESS)
	{
		return OpenService(hSvcManager, targetServiceName, needAccessPermission);
	}
	static bool startService(SC_HANDLE hService, DWORD startSvcArgCount = 0, const TCHAR ** lpstartSvcArg = NULL)
	{
		return 0 != StartService(hService, startSvcArgCount, lpstartSvcArg);
	}
	static bool stopService(SC_HANDLE hService, LPSERVICE_STATUS saveSvcStatus)
	{
		return 0 != ControlService(hService, SERVICE_CONTROL_STOP, saveSvcStatus);
	}
	static bool pauseService(SC_HANDLE hService, LPSERVICE_STATUS saveSvcStatus)
	{
		return 0 != ControlService(hService, SERVICE_CONTROL_PAUSE, saveSvcStatus);
	}
	static bool continueService(SC_HANDLE hService, LPSERVICE_STATUS saveSvcStatus)
	{
		return 0 != ControlService(hService, SERVICE_CONTROL_CONTINUE, saveSvcStatus);
	}
	static bool controlService(SC_HANDLE hService, DWORD controlCode, LPSERVICE_STATUS saveSvcStatus)
	{
		return 0 != ControlService(hService, controlCode, saveSvcStatus);
	}

};

#endif // _ALGO_WIN_SERVICE_HPP_