#ifndef _ALGO_WIN_DIRECTORY_
#define _ALGO_WIN_DIRECTORY_
#include<Windows.h>
#include"AlgoString.hpp"
class AlgoWinDirectory
{
public:
	static AlgoArray<AlgoString<TCHAR, int>, int>& getAllLogicalDriverPath(AlgoArray<AlgoString<TCHAR, int>, int> & saveArr)
	{
		saveArr.setSize(0);
		DWORD len = GetLogicalDriveStrings(0, NULL);
		AlgoString<TCHAR, int> buf;
		buf[len + 1] = 0;
		len = GetLogicalDriveStrings(len + 1, buf.getData());
		int i = 0;
		AlgoString<TCHAR, int> tp;
		int saveindex = 0;
		while (i < len)
		{
			if (buf[i] == 0)
			{
				if (tp.getLength()>0)
				{
					saveArr.push(tp);
					tp.clear();
					saveindex = 0;
				}
			}
			else
			{
				tp[saveindex] = buf[i];
				tp[saveindex + 1] = 0;
				saveindex++;
			}
			i++;
		}
		return saveArr;
	}
	static UINT getDriverType(const TCHAR * rootPath)
	{
		return GetDriveType(rootPath);
	}
	static bool isLegalDriver(const TCHAR * rootPath)
	{
		return 0 != (DRIVE_NO_ROOT_DIR & GetDriveType(rootPath));
	}
	static bool isRemoveableDriver(const TCHAR * rootPath)
	{
		return 0 != (DRIVE_REMOVABLE & GetDriveType(rootPath));
	}
	static bool isHardDiskDriver(const TCHAR * rootPath)
	{
		return 0 != (DRIVE_FIXED & GetDriveType(rootPath));
	}
	static bool isNetworkDriver(const TCHAR * rootPath)
	{
		return 0 != (DRIVE_REMOTE & GetDriveType(rootPath));
	}
	static bool isCdRomDriver(const TCHAR * rootPath)
	{
		return 0 != (DRIVE_CDROM & GetDriveType(rootPath));
	}
	static bool isVirtualDriver(const TCHAR * rootPath)
	{
		return 0 != (DRIVE_RAMDISK & GetDriveType(rootPath));
	}
	static bool createDirectory(const TCHAR * pathDir, LPSECURITY_ATTRIBUTES lpsecurityAttr = NULL)
	{
		return 0 != CreateDirectory(pathDir, lpsecurityAttr);
	}
	static bool removeDirectory(const TCHAR * path)
	{
		return 0 != RemoveDirectory(path);
	}
};
#endif // _ALGO_WIN_DIRECTORY_