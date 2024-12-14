#ifndef _ALGO_WIN_FILE_HPP_
#define _ALGO_WIN_FILE_HPP_
#include<Windows.h>
#include"AlgoString.hpp"

class AlgoWinFile
{
public:
	static HANDLE openExist(const TCHAR * filePath)
	{
		return  CreateFile(filePath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	}
	static HANDLE openExistOrCreate(const TCHAR * filePath)
	{
		return  CreateFile(filePath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	}
	static HANDLE openReadOnly(const TCHAR * filePath)
	{
		return  CreateFile(filePath,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	}
	static HANDLE openWriteOnly(const TCHAR * filePath)
	{
		return  CreateFile(filePath,
			GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	}
	static bool close(HANDLE hFile)
	{
		return 0 != CloseHandle(hFile);
	}
	static bool flush(HANDLE hFile)
	{
		return 0 != FlushFileBuffers(hFile);
	}
	static bool write(HANDLE hFile, LPCVOID writeBuf, DWORD bufSize, LPDWORD lpReturnWrittenSize = NULL, LPOVERLAPPED lpOverlapped = NULL)
	{
		DWORD returnSize = 0;
		BOOL ret = WriteFile(hFile, writeBuf, bufSize, &returnSize, lpOverlapped);
		if (lpReturnWrittenSize != NULL)
			*lpReturnWrittenSize = returnSize;
		return 0 != ret;
	}
	static bool read(HANDLE hFile, LPVOID saveBuf, DWORD needReadSize, LPDWORD lpReturnReadedSize = NULL, LPOVERLAPPED lpOverlapped = NULL)
	{
		DWORD returnSize = 0;
		BOOL ret = ReadFile(hFile, saveBuf, needReadSize, &returnSize, lpOverlapped);
		if (lpReturnReadedSize != NULL)
			*lpReturnReadedSize = returnSize;
		return 0 != ret;
	}
	static bool isFile(const TCHAR * filePath)
	{
		WIN32_FILE_ATTRIBUTE_DATA fileData;
		BOOL ret = ::GetFileAttributesEx(filePath, GetFileExInfoStandard, &fileData);
		if (ret == 0)
			return false;
		return fileData.dwFileAttributes && (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
	}
	static bool isDirectory(const TCHAR * filePath)
	{
		WIN32_FILE_ATTRIBUTE_DATA fileData;
		BOOL ret = ::GetFileAttributesEx(filePath, GetFileExInfoStandard, &fileData);
		if (ret == 0)
			return false;
		return 0 != (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	}
	static bool isHide(const TCHAR * filePath)
	{
		WIN32_FILE_ATTRIBUTE_DATA fileData;
		BOOL ret = ::GetFileAttributesEx(filePath, GetFileExInfoStandard, &fileData);
		if (ret == 0)
			return false;
		return 0 != (fileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN);
	}
	static bool isSystem(const TCHAR * filePath)
	{
		WIN32_FILE_ATTRIBUTE_DATA fileData;
		BOOL ret = ::GetFileAttributesEx(filePath, GetFileExInfoStandard, &fileData);
		if (ret == 0)
			return false;
		return 0 != (fileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM);
	}
	static bool isReadOnly(const TCHAR * filePath)
	{
		WIN32_FILE_ATTRIBUTE_DATA fileData;
		BOOL ret = ::GetFileAttributesEx(filePath, GetFileExInfoStandard, &fileData);
		if (ret == 0)
			return false;
		return 0 != (fileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY);
	}
	static bool isDevice(const TCHAR * filePath)
	{
		WIN32_FILE_ATTRIBUTE_DATA fileData;
		BOOL ret = ::GetFileAttributesEx(filePath, GetFileExInfoStandard, &fileData);
		if (ret == 0)
			return false;
		return 0 != (fileData.dwFileAttributes & FILE_ATTRIBUTE_DEVICE);
	}
	static bool getAttributes(const TCHAR * filePath, WIN32_FILE_ATTRIBUTE_DATA * fileData)
	{
		BOOL ret = ::GetFileAttributesEx(filePath, GetFileExInfoStandard, fileData);
		return ret != 0;
	}

	static bool getAttributes(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInfo)
	{
		BOOL ret = ::GetFileInformationByHandle(hFile, lpFileInfo);
		return ret != 0;
	}
	static bool getSize(HANDLE hFile, PLARGE_INTEGER lpSize)
	{
		BOOL ret = ::GetFileSizeEx(hFile, lpSize);
		return ret != 0;
	}
	static bool getSize(HANDLE hFile, LPFILETIME lpCreateTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime)
	{
		BOOL ret = ::GetFileTime(hFile, lpCreateTime, lpLastAccessTime, lpLastWriteTime);
		return ret != 0;
	}
	static short getTitle(TCHAR * filePath, TCHAR * titleSave, WORD saveSize)
	{
		return ::GetFileTitle(filePath, titleSave, saveSize);
	}
	static DWORD getType(HANDLE hFile)
	{
		return ::GetFileType(hFile);
	}
	static bool getOpenName(LPOPENFILENAME lpOpenFileName)
	{
		BOOL ret = ::GetOpenFileName(lpOpenFileName);
		return ret != 0;
	}
	static bool getSaveName(LPOPENFILENAME lpOpenFileName)
	{
		BOOL ret = ::GetSaveFileName(lpOpenFileName);
		return ret != 0;
	}
	static bool setAttributes(const TCHAR * filePath, DWORD dwFileAttr)
	{
		BOOL ret = ::SetFileAttributes(filePath, dwFileAttr);
		return ret != 0;
	}
	static bool setPointerReferenceBegin(HANDLE hFile, LARGE_INTEGER liMoveDistance)
	{
		BOOL ret = ::SetFilePointerEx(hFile, liMoveDistance, NULL, FILE_BEGIN);
		return ret != 0;
	}
	static bool setPointerReferenceCurrent(HANDLE hFile, LARGE_INTEGER liMoveDistance)
	{
		BOOL ret = ::SetFilePointerEx(hFile, liMoveDistance, NULL, FILE_CURRENT);
		return ret != 0;
	}
	static bool setPointerReferenceEnd(HANDLE hFile, LARGE_INTEGER liMoveDistance)
	{
		BOOL ret = ::SetFilePointerEx(hFile, liMoveDistance, NULL, FILE_END);
		return ret != 0;
	}
	static bool setPointer(HANDLE hFile, LARGE_INTEGER liMoveDistance, DWORD dwMoveMethod = FILE_CURRENT, PLARGE_INTEGER lpNewPointerHeight = NULL)
	{
		BOOL ret = ::SetFilePointerEx(hFile, liMoveDistance, lpNewPointerHeight, dwMoveMethod);
		return ret != 0;
	}
	static bool setTime(HANDLE hFile, const LPFILETIME lpCreateTime, const LPFILETIME lpLastAccessTime, const LPFILETIME lpLastWriteTime)
	{
		BOOL ret = ::SetFileTime(hFile, lpCreateTime, lpLastAccessTime, lpLastWriteTime);
		return ret != 0;
	}
	static HANDLE findFirst(const TCHAR * filePath, LPWIN32_FIND_DATA lpFindData)
	{
		return ::FindFirstFile(filePath, lpFindData);
	}
	static bool findNext(HANDLE hFindFile, LPWIN32_FIND_DATA lpFindData)
	{
		return ::FindNextFile(hFindFile, lpFindData) != 0;
	}
	static bool remove(const TCHAR * filePath)
	{
		return ::DeleteFile(filePath) != 0;
	}

	static AlgoArray<AlgoString<TCHAR, int>, int>& getFileList(const TCHAR * filePath, AlgoArray<AlgoString<TCHAR, int>, int>& saveArr)
	{
		saveArr.setSize(0);
		WIN32_FIND_DATA FindFileData;
		HANDLE hListFile;
		AlgoString<TCHAR, int> dir(filePath);
		bool hasDirSplit = false;
		if (dir.endWith(TEXT("\\")))
		{
			dir += TEXT("*");
			hasDirSplit = true;
		}
		else
		{
			dir += TEXT("\\*");
		}
		hListFile = ::FindFirstFile(dir.getData(), &FindFileData);
		if (hListFile == INVALID_HANDLE_VALUE)
		{
			return saveArr;
		}
		do
		{
			if (!lstrcmp(FindFileData.cFileName, TEXT(".")) == 0 &&
				!lstrcmp(FindFileData.cFileName, TEXT("..")) == 0)
			{
				//是否是文件夹
				if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					AlgoString<TCHAR, int> pst(filePath);
					if (!hasDirSplit)
						pst += TEXT("\\");
					pst += FindFileData.cFileName;
					saveArr.push(pst);
				}
				else
				{
					AlgoString<TCHAR, int> pst(filePath);
					if (!hasDirSplit)
						pst += TEXT("\\");
					pst += FindFileData.cFileName;
					saveArr.push(pst);
				}
			}

		} while (::FindNextFile(hListFile, &FindFileData));

		return saveArr;
	}
};

#endif // _ALGO_WIN_FILE_HPP_