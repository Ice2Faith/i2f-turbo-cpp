#ifndef _ALGO_WIN_REGISTER_HPP_
#define _ALGO_WIN_REGISTER_HPP_
#include<iostream>
using namespace std;
#include<stdio.h>

#include<Windows.h>
#include"AlgoString.hpp"
class AlgoRegValueData
{
public:
	AlgoString<TCHAR, int> valName;
	DWORD valType;
	AlgoArray<BYTE, int> valData;
	AlgoRegValueData()
	{
		valName[300] = 0;
		valName.zeroMemory();
		valType = 0;
		valData[2048] = 0;
		valData.memorySet(0);
	}
	AlgoRegValueData& operator=(const AlgoRegValueData & data)
	{
		this->valName = data.valName;
		this->valType = data.valType;
		this->valData = data.valData;
		return *this;
	}
};
class AlgoWinRegister
{
public:
	static bool openKey(HKEY hKey, const TCHAR * openSubKeyName, PHKEY saveResultKey, REGSAM needHaveAccessPermission = KEY_ALL_ACCESS, DWORD ulOptions = 0)
	{
		return ERROR_SUCCESS == RegOpenKeyEx(hKey, openSubKeyName, ulOptions, needHaveAccessPermission, saveResultKey);
	}
	static bool closeKey(HKEY hKey)
	{
		return ERROR_SUCCESS == RegCloseKey(hKey);
	}
	//已存在时，其实就是打开
	static bool createKey(HKEY hKey, const TCHAR * subKeyName, PHKEY saveResultKey, REGSAM needAccessPermission = KEY_ALL_ACCESS
		, DWORD dwOptions = REG_OPTION_NON_VOLATILE, TCHAR * subKeyClassName = NULL
		, LPSECURITY_ATTRIBUTES lpSecurityAttr = NULL, LPDWORD lpdwDisposition = NULL, DWORD reserved = 0)
	{
		return ERROR_SUCCESS == RegCreateKeyEx(hKey, subKeyName, reserved, subKeyClassName, dwOptions, needAccessPermission, lpSecurityAttr, saveResultKey, lpdwDisposition);
	}
	static bool deleteKey(HKEY hKey, const TCHAR * deleteKeyName)
	{
		return ERROR_SUCCESS == RegDeleteKey(hKey, deleteKeyName);
	}
	static bool queryValue(HKEY hKey, const TCHAR * valueName, LPBYTE lpSaveData, LPDWORD ioBufSizeAndReturnSize, LPDWORD lpReturnValueType = NULL, LPDWORD lpReserved = NULL)
	{
		return ERROR_SUCCESS == RegQueryValueEx(hKey, valueName, lpReserved, lpReturnValueType, lpSaveData, ioBufSizeAndReturnSize);
	}
	static bool setValue(HKEY hKey, const TCHAR * valueName, DWORD dwValueType, const BYTE * lpData, DWORD dataSize, DWORD reserved = 0)
	{
		return ERROR_SUCCESS == RegSetValueEx(hKey, valueName, reserved, dwValueType, lpData, dataSize);
	}
	static bool deleteValue(HKEY hKey, const TCHAR * valueName)
	{
		return ERROR_SUCCESS == RegDeleteValue(hKey, valueName);
	}
	static LONG enumerateKey(HKEY hKey, DWORD dwIndexRequire, TCHAR * saveKeyName, LPDWORD saveKeyNameSizeAndReturnSize, PFILETIME lpLastWriteTime = NULL, TCHAR * lpClassName = NULL, LPDWORD lpClassSizeAndReturn = NULL, LPDWORD lpReserved = NULL)
	{
		FILETIME ft = { 0 };
		LONG ret = RegEnumKeyEx(hKey, dwIndexRequire, saveKeyName, saveKeyNameSizeAndReturnSize, lpReserved, lpClassName, lpClassSizeAndReturn, &ft);
		if (lpLastWriteTime != NULL)
			*lpLastWriteTime = ft;
		return ret;
	}
	static LONG enumerateValue(HKEY hKey, DWORD dwIndexRequire, TCHAR * saveValueName, LPDWORD saveValueNameSizeAndReturnSize, LPDWORD lpValueType, LPBYTE lpSaveData, LPDWORD lpSaveDataSizeAndReturnSize, LPDWORD lpReserved = NULL)
	{
		return RegEnumValue(hKey, dwIndexRequire, saveValueName, saveValueNameSizeAndReturnSize, lpReserved, lpValueType, lpSaveData, lpSaveDataSizeAndReturnSize);
	}
	static AlgoArray<AlgoString<TCHAR, int>, int> & getKeyList(HKEY hKey, AlgoArray<AlgoString<TCHAR, int>, int> & saveArr)
	{
		saveArr.setSize(0);
		AlgoString<TCHAR, int> buf;
		buf[2048] = 0;
		int i = 0;
		DWORD ssize = buf.getCapital();
		while (true)
		{
			LONG ret = enumerateKey(hKey, i, buf.getData(), &ssize);
			if (ret == ERROR_NO_MORE_ITEMS)
			{
				break;
			}
			saveArr.push(buf);
			buf.zeroMemory();
			buf.clear();
			ssize = buf.getCapital();
			i++;
		}
		return saveArr;
	}
	static AlgoArray<AlgoString<TCHAR, int>, int> & getValueNameList(HKEY hKey, AlgoArray<AlgoString<TCHAR, int>, int> & saveArr)
	{
		saveArr.setSize(0);
		AlgoString<TCHAR, int> buf;
		AlgoString<BYTE, int> vbuf;
		vbuf[2048] = 0;
		buf[2048] = 0;
		int i = 0;
		DWORD ssize = buf.getCapital();
		DWORD vsize = vbuf.getCapital();
		DWORD type = 0;
		while (true)
		{
			LONG ret = enumerateValue(hKey, i, buf.getData(), &ssize, &type, vbuf.getData(), &vsize);
			if (ret == ERROR_NO_MORE_ITEMS)
			{
				break;
			}
			saveArr.push(buf);
			buf.zeroMemory();
			buf.clear();
			ssize = buf.getCapital();
			vsize = vbuf.getCapital();
			i++;
		}
		return saveArr;
	}
	static AlgoArray<AlgoRegValueData, int> & getValueList(HKEY hKey, AlgoArray<AlgoRegValueData, int> & saveValue)
	{
		saveValue.setSize(0);

		int i = 0;
		
		while (true)
		{
			DWORD nameSize = saveValue[i].valName.getCapital();
			DWORD dataSize = saveValue[i].valData.capital();
			saveValue[i].valType = 0;

			LONG ret = enumerateValue(hKey, i, saveValue[i].valName.getData(), &nameSize, &saveValue[i].valType, saveValue[i].valData.getData(), &dataSize);
			if (ret == ERROR_NO_MORE_ITEMS)
			{
				break;
			}
			saveValue[i].valData.setSize(dataSize);
			saveValue.setSize(i+1);
			
			i++;
		}
		return saveValue;
	}

};

#endif // _ALGO_WIN_REGISTER_HPP_