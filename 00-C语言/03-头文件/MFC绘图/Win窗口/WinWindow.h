#pragma once
/*
聚合大部分WIN API 窗口操作调用
和相关句柄调用
*/
class WinWindow
{
public:
	WinWindow();
	WinWindow(HWND hwnd);
	~WinWindow();
	BOOL SetPosition(int x,int y);
	BOOL SetSize(int Wid,int Hei);
	BOOL SetTopMostZ();
	BOOL SetButtomZ();
	BOOL SetNoTopMostZ();
	BOOL SetShow();
	BOOL SetHide();
	BOOL SetMaximize();
	BOOL SetMinimize();
	BOOL SetNormal();
	BOOL SetRestore();
	LONG SetLong(int nlndex, LONG dwNewLong);
	LONG RemoveBorder();
	BOOL SetTransParent(float alpha);
	BOOL SetLayeredAttributes(COLORREF clrKey, BYTE alpha, DWORD flag);
	BOOL SetForeground();
	HWND SetActive();
	BOOL SetEnable(BOOL enable);
	BOOL SetText(LPCTSTR str);
	HWND SetParentWnd(HWND newParent);
	void SetHWND(HWND hwnd);
	HWND GetHWND();
	HDC GetDC();
	BOOL GetInfo(PWINDOWINFO pInfo);
	LONG GetLong(int nIndex);
	BOOL GetRect(LPRECT pRect);
	int GetText(LPTSTR str, int maxCount);
	int GetTextLen();
	DWORD GetThreadProcessId(LPDWORD lpdwProcessld = NULL);
	BOOL GetPlacement(WINDOWPLACEMENT * lpwndpl);
	HWND GetOwner();
	HWND GetChild();
	HWND GetNext();
	int ClassName(LPTSTR str,int maxCount);
	BOOL IsVisible();
	BOOL IsUnicode();
	BOOL IsChildWnd(HWND parent);
	BOOL IsMinimize();
	BOOL IsMaximize();
	BOOL Open();
	HWND GetParentWnd();
	HWND GetDesktop();
	HWND Find(LPCTSTR lpClassName, LPCTSTR lpWindowName);
	HWND FindChild(HWND child,LPCTSTR lpClassName,LPCTSTR lpWindowName);
	HWND FindByPoint(POINT point);
	HWND FindByDC(HDC dc);
	BOOL Move(int x, int y, int wid, int hei, BOOL isRepaint);
	int MsgBox(LPCTSTR Text,LPCTSTR Title,UINT type);
	BOOL PostMsg(UINT msg, WPARAM wparam, LPARAM lparam);
	BOOL SendMsg(UINT msg, WPARAM wparam, LPARAM lparam);
	BOOL QuitMsg();
	BOOL DestoryMsg();
	BOOL CloseMsg();
	BOOL PaintMsg();
private:
	HWND mHwnd;
};

