#ifndef _ALGO_WIN_WINDOW_HPP_
#define _ALGO_WIN_WINDOW_HPP_
#include"AlgoString.hpp"
#include<Windows.h>
typedef struct
{
	HWND hWnd;
	AlgoString<TCHAR, int> title;
	AlgoString<TCHAR, int> className;
}ALGO_WINDOWD_INFO;

BOOL CALLBACK __Algo_EnumWindow_Proc(HWND hWnd, LPARAM lParam)
{
	AlgoArray<ALGO_WINDOWD_INFO, int> * psaveArr = (AlgoArray<ALGO_WINDOWD_INFO, int> *)lParam;

	const static int PREPARE_MEMORY = 512;

	ALGO_WINDOWD_INFO info;
	info.title.prepareMemery(PREPARE_MEMORY);
	info.className.prepareMemery(PREPARE_MEMORY);

	info.hWnd = hWnd;
	::GetWindowText(hWnd, info.title.getData(), PREPARE_MEMORY);
	::GetClassName(hWnd, info.className.getData(), PREPARE_MEMORY);
	psaveArr->push(info);

	return TRUE;
}
class AlgoWinWindow
{
public:
	static void getSystemScreenSize(int * width, int * height)
	{
		*width = ::GetSystemMetrics(SM_CXSCREEN);
		*height = ::GetSystemMetrics(SM_CYSCREEN);
	}
	static void getSystemFullScreenSize(int * width, int * height)
	{
		*width = ::GetSystemMetrics(SM_CXFULLSCREEN);
		*height = ::GetSystemMetrics(SM_CYFULLSCREEN);
	}
	static double getScreenScaleFactor()
	{
		HDC hdeskDc = ::GetDC(NULL);
		int sxDpi = ::GetDeviceCaps(hdeskDc, LOGPIXELSX);
		int syDpi = ::GetDeviceCaps(hdeskDc, LOGPIXELSY);
		//normally,sxDpi should equals syDpi
		return sxDpi*1.0 / 96;//scale rate is 100% when dpi is 96
	}
	static void setWindowTransparentColor(HWND hWnd, COLORREF colorKey)
	{
		//窗口透明
		LONG wlong = ::GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED;
		::SetWindowLong(hWnd, GWL_EXSTYLE, wlong);
		//穿透点击
		::SetLayeredWindowAttributes(hWnd, colorKey, 0, LWA_COLORKEY);
	}
	static void setWindowTransparentAlpha(HWND hWnd, double transRate)
	{
		//窗口透明
		LONG wlong = ::GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED;
		::SetWindowLong(hWnd, GWL_EXSTYLE, wlong);
		//不穿透点击
		::SetLayeredWindowAttributes(hWnd, 0x000000, (1.0 - transRate) * 255, LWA_ALPHA);
	}
	static void removeWindowTaskBarIcon(HWND hWnd)
	{
		LONG wlong = ::GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TOOLWINDOW;//添加透明、任务栏不显示图标属性
		::SetWindowLong(hWnd, GWL_EXSTYLE, wlong);
	}
	static void removeWindowBorder(HWND hWnd)
	{
		//消除边框
		::SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) - WS_CAPTION);
	}
	static void setWindowTopMost(HWND hWnd)
	{
		::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	static AlgoArray<ALGO_WINDOWD_INFO, int>& getChilden(AlgoArray<ALGO_WINDOWD_INFO, int>& saveArr, HWND parent = NULL)
	{
		saveArr.setSize(0);
		if (parent == NULL)
			parent = ::GetDesktopWindow();
		HWND curHwnd = ::GetNextWindow(parent, GW_CHILD);

		const static int PREPARE_MEMORY = 512;
		ALGO_WINDOWD_INFO info;
		info.title.prepareMemery(PREPARE_MEMORY);
		info.className.prepareMemery(PREPARE_MEMORY);
		while (curHwnd != NULL)
		{
			
			info.hWnd = curHwnd;
			::GetWindowText(curHwnd, info.title.getData(), PREPARE_MEMORY);
			::GetClassName(curHwnd, info.className.getData(), PREPARE_MEMORY);
			saveArr.push(info);
			curHwnd = ::GetNextWindow(curHwnd, GW_HWNDNEXT);
		}
		return saveArr;
	}
	static AlgoArray<ALGO_WINDOWD_INFO, int>& enumWindow(AlgoArray<ALGO_WINDOWD_INFO, int>& saveArr)
	{
		saveArr.setSize(0);
		EnumWindows(__Algo_EnumWindow_Proc, (LPARAM)&saveArr);
		return saveArr;
	}
	static AlgoArray<ALGO_WINDOWD_INFO, int>& enumChildWindow(AlgoArray<ALGO_WINDOWD_INFO, int>& saveArr,HWND parent)
	{
		saveArr.setSize(0);
		EnumChildWindows(parent, __Algo_EnumWindow_Proc, (LPARAM)&saveArr);
		return saveArr;
	}
	static AlgoArray<ALGO_WINDOWD_INFO, int>& enumThreadWindow(AlgoArray<ALGO_WINDOWD_INFO, int>& saveArr, DWORD threadId)
	{
		saveArr.setSize(0);
		EnumThreadWindows(threadId, __Algo_EnumWindow_Proc, (LPARAM)&saveArr);
		return saveArr;
	}
	static HWND superFindWindow(TCHAR * szTitle, TCHAR * szClassName, HWND parent)
	{
		AlgoString<TCHAR, int> curTitle;
		AlgoString<TCHAR, int> curClassName;
		curTitle.prepareMemery(512);
		curClassName.prepareMemery(512);
		GetWindowText(parent, curTitle.getData(), 512);
		GetClassName(parent, curClassName.getData(), 512);
		if (curTitle.equals(szTitle) && curClassName.equals(szClassName))
			return parent;
		AlgoArray<ALGO_WINDOWD_INFO, int> saveArr;
		enumChildWindow(saveArr, parent);
		for (int i = 0; i < saveArr.size(); i++)
		{
			if (saveArr[i].title.equals(szTitle) && saveArr[i].className.equals(szClassName))
				return saveArr[i].hWnd;
			return superFindWindow(szTitle,szClassName,saveArr[i].hWnd);
		}
		return NULL;
	}
	static void __find__all_window(AlgoArray<ALGO_WINDOWD_INFO, int>* saveArr, TCHAR * szTitle, TCHAR * szClassName, HWND parent, bool onlyFindTreeFirst)
	{
		AlgoArray<ALGO_WINDOWD_INFO, int> temp;
		enumChildWindow(temp,parent);
		for (int i = 0; i < temp.size(); i++)
		{
			if (szTitle && szClassName)
			{
				if (temp[i].title.equals(szTitle) && temp[i].className.equals(szClassName))
					saveArr->push(temp[i]);
			}
			else if (szTitle && !szClassName)
			{
				if (temp[i].title.equals(szTitle))
					saveArr->push(temp[i]);
			}
			else if (!szTitle && szClassName)
			{
				if (temp[i].className.equals(szClassName))
					saveArr->push(temp[i]);
			}
			if (!onlyFindTreeFirst)
				__find__all_window(saveArr, szTitle, szClassName, temp[i].hWnd, onlyFindTreeFirst);
		}
	}
	static AlgoArray<ALGO_WINDOWD_INFO, int>& findAllWindow(AlgoArray<ALGO_WINDOWD_INFO, int>& saveArr,TCHAR * szTitle, TCHAR * szClassName,bool onlyFindTreeFirst=false)
	{
		saveArr.setSize(0);
		AlgoArray<ALGO_WINDOWD_INFO, int> temp;
		enumWindow(temp);
		for (int i = 0; i < temp.size(); i++)
		{
			if (szTitle && szClassName)
			{
				if (temp[i].title.equals(szTitle) && temp[i].className.equals(szClassName))
					saveArr.push(temp[i]);
			}
			else if (szTitle && !szClassName)
			{
				if (temp[i].title.equals(szTitle))
					saveArr.push(temp[i]);
			}
			else if (!szTitle && szClassName)
			{
				if (temp[i].className.equals(szClassName))
					saveArr.push(temp[i]);
			}
			if (!onlyFindTreeFirst)
				__find__all_window(&saveArr,szTitle,szClassName,temp[i].hWnd,onlyFindTreeFirst);
		}
		return saveArr;
	}
public:

	AlgoWinWindow()
	{
		mHwnd = NULL;
	}
	AlgoWinWindow(HWND hwnd)
	{
		mHwnd = hwnd;
	}
	~AlgoWinWindow()
	{
	}
	BOOL SetPosition(int x, int y)
	{
		return ::SetWindowPos(mHwnd, HWND_NOTOPMOST, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	BOOL SetSize(int Wid, int Hei)
	{
		return ::SetWindowPos(mHwnd, HWND_NOTOPMOST, 0, 0, Wid, Hei, SWP_NOMOVE | SWP_NOZORDER);
	}
	BOOL SetTopMostZ()
	{
		return ::SetWindowPos(mHwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
	BOOL SetButtomZ()
	{
		return ::SetWindowPos(mHwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
	BOOL SetNoTopMostZ()
	{
		return ::SetWindowPos(mHwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
	BOOL SetShow()
	{
		return ::ShowWindow(mHwnd, SW_SHOW);
	}
	BOOL SetHide()
	{
		return ::ShowWindow(mHwnd, SW_HIDE);
	}
	BOOL SetMaximize()
	{
		return ::ShowWindow(mHwnd, SW_MAXIMIZE);
	}
	BOOL SetMinimize()
	{
		return ::ShowWindow(mHwnd, SW_MINIMIZE);
	}
	BOOL SetNormal()
	{
		return ::ShowWindow(mHwnd, SW_NORMAL);
	}
	BOOL SetRestore()
	{
		return ::ShowWindow(mHwnd, SW_RESTORE);
	}
	LONG SetLong(int nlndex, LONG dwNewLong)
	{
		return ::SetWindowLong(mHwnd, nlndex, dwNewLong);
	}
	LONG RemoveBorder()
	{
		return ::SetWindowLong(mHwnd, GWL_STYLE, GetWindowLong(mHwnd, GWL_STYLE) - WS_CAPTION);
	}
	BOOL SetTransParent(float alpha)
	{
		LONG wlong = ::GetWindowLong(mHwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
		::SetWindowLong(mHwnd, GWL_EXSTYLE, wlong);
		return ::SetLayeredWindowAttributes(mHwnd, RGB(0, 0, 0), (BYTE)((100 - alpha)*(255.0 / 100)), LWA_ALPHA);
	}
	BOOL SetLayeredAttributes(COLORREF clrKey, BYTE alpha, DWORD flag)
	{
		return ::SetLayeredWindowAttributes(mHwnd, clrKey, alpha, flag);
	}
	BOOL SetForeground()
	{
		return ::SetForegroundWindow(mHwnd);
	}
	HWND SetActive()
	{
		return ::SetActiveWindow(mHwnd);
	}
	BOOL SetEnable(BOOL enable)
	{
		return ::EnableWindow(mHwnd, enable);
	}
	BOOL SetText(LPCTSTR str)
	{
		return ::SetWindowText(mHwnd, str);
	}
	HWND SetParentWnd(HWND newParent)
	{
		return ::SetParent(mHwnd, newParent);
	}
	void SetHWND(HWND hwnd)
	{
		mHwnd = hwnd;
	}
	HWND GetHWND()
	{
		return mHwnd;
	}
	HDC GetDC()
	{
		return ::GetWindowDC(mHwnd);
	}
#if (WINVER >= 0x0500)
	BOOL GetInfo(PWINDOWINFO pInfo)
	{
		return ::GetWindowInfo(mHwnd, pInfo);
	}
#endif
	LONG GetLong(int nIndex)
	{
		return ::GetWindowLong(mHwnd, nIndex);
	}
	BOOL GetRect(LPRECT pRect)
	{
		return ::GetWindowRect(mHwnd, pRect);
	}
	int GetText(LPTSTR str, int maxCount)
	{
		return ::GetWindowText(mHwnd, str, maxCount);
	}
	int GetTextLen()
	{
		return ::GetWindowTextLength(mHwnd);
	}
	DWORD GetThreadProcessId(LPDWORD lpdwProcessld)
	{
		return ::GetWindowThreadProcessId(mHwnd, lpdwProcessld);
	}
	BOOL GetPlacement(WINDOWPLACEMENT * lpwndpl)
	{
		return ::GetWindowPlacement(mHwnd, lpwndpl);
	}
	HWND GetOwner()
	{
		return ::GetWindow(mHwnd, GW_OWNER);
	}
	HWND GetChild()
	{
		return ::GetWindow(mHwnd, GW_CHILD);
	}
	HWND GetNext()
	{
		return ::GetWindow(mHwnd, GW_HWNDNEXT);
	}
	int ClassName(LPTSTR str, int maxCount)
	{
		return ::GetClassName(mHwnd, str, maxCount);
	}
	BOOL IsVisible()
	{
		return ::IsWindowVisible(mHwnd);
	}
	BOOL IsUnicode()
	{
		return ::IsWindowUnicode(mHwnd);
	}
	BOOL IsChildWnd(HWND parent)
	{
		return ::IsChild(parent, mHwnd);
	}
	BOOL IsMinimize()
	{
		return ::IsIconic(mHwnd);
	}
	BOOL Open()
	{
		return ::OpenIcon(mHwnd);
	}
	BOOL IsMaximize()
	{
		return ::IsZoomed(mHwnd);
	}
	HWND GetParentWnd()
	{
		return ::GetParent(mHwnd);
	}
	static HWND GetDesktop()
	{
		return ::GetDesktopWindow();
	}
	static HWND Find(LPCTSTR lpClassName, LPCTSTR lpWindowName)
	{
		return ::FindWindow(lpClassName, lpWindowName);
	}
	HWND FindChild(HWND child, LPCTSTR lpClassName, LPCTSTR lpWindowName)
	{
		return ::FindWindowEx(mHwnd, child, lpClassName, lpWindowName);
	}
	static HWND FindByPoint(POINT point)
	{
		return ::WindowFromPoint(point);
	}
	static HWND getCursorPoint()
	{
		POINT p;
		::GetCursorPos(&p);
		return ::WindowFromPoint(p);
	}
	static HWND getForeground()
	{
		return ::GetForegroundWindow();
	}
	static HWND getActive()
	{
		return ::GetActiveWindow();
	}
	static HWND FindByDC(HDC dc)
	{
		return ::WindowFromDC(dc);
	}
	BOOL Move(int x, int y, int wid, int hei, BOOL isRepaint)
	{
		return ::MoveWindow(mHwnd, x, y, wid, hei, isRepaint);
	}
	int MsgBox(LPCTSTR Text, LPCTSTR Title, UINT type)
	{
		return ::MessageBox(mHwnd, Text, Title, type);
	}
	BOOL PostMsg(UINT msg, WPARAM wparam, LPARAM lparam)
	{
		return ::PostMessage(mHwnd, msg, wparam, lparam);
	}
	BOOL SendMsg(UINT msg, WPARAM wparam, LPARAM lparam)
	{
		return ::SendMessage(mHwnd, msg, wparam, lparam);
	}
	BOOL QuitMsg()
	{
		return PostMsg(WM_QUIT, 0, 0);
	}
	BOOL DestoryMsg()
	{
		return PostMsg(WM_DESTROY, 0, 0);
	}
	BOOL CloseMsg()
	{
		return PostMsg(WM_CLOSE, 0, 0);
	}
	BOOL PaintMsg()
	{
		return PostMsg(WM_PAINT, 0, 0);
	}
private:
	HWND mHwnd;
};
#endif // _ALGO_WIN_WINDOW_HPP_