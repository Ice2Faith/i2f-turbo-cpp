#include "stdafx.h"
#include "WinWindow.h"

WinWindow::WinWindow()
{
	mHwnd = NULL;
}
WinWindow::WinWindow(HWND hwnd)
{
	mHwnd = hwnd;
}
WinWindow::~WinWindow()
{
}
BOOL WinWindow::SetPosition(int x, int y)
{
	return SetWindowPos(mHwnd, HWND_NOTOPMOST, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
BOOL WinWindow::SetSize(int Wid, int Hei)
{
	return SetWindowPos(mHwnd, HWND_NOTOPMOST, 0, 0, Wid, Hei, SWP_NOMOVE | SWP_NOZORDER);
}
BOOL WinWindow::SetTopMostZ()
{
	return SetWindowPos(mHwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}
BOOL WinWindow::SetButtomZ()
{
	return SetWindowPos(mHwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}
BOOL WinWindow::SetNoTopMostZ()
{
	return SetWindowPos(mHwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}
BOOL WinWindow::SetShow()
{
	return ShowWindow(mHwnd, SW_SHOW);
}
BOOL WinWindow::SetHide()
{
	return ShowWindow(mHwnd, SW_HIDE);
}
BOOL WinWindow::SetMaximize()
{
	return ShowWindow(mHwnd, SW_MAXIMIZE);
}
BOOL WinWindow::SetMinimize()
{
	return ShowWindow(mHwnd, SW_MINIMIZE);
}
BOOL WinWindow::SetNormal()
{
	return ShowWindow(mHwnd, SW_NORMAL);
}
BOOL WinWindow::SetRestore()
{
	return ShowWindow(mHwnd, SW_RESTORE);
}
LONG WinWindow::SetLong(int nlndex,LONG dwNewLong)
{
	return SetWindowLong(mHwnd, nlndex, dwNewLong);
}
LONG WinWindow::RemoveBorder()
{
	return SetWindowLong(mHwnd, GWL_STYLE, GetWindowLong(mHwnd, GWL_STYLE) - WS_CAPTION);
}
BOOL WinWindow::SetTransParent(float alpha)
{
	LONG wlong = GetWindowLong(mHwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
	SetWindowLong(mHwnd, GWL_EXSTYLE, wlong);
	return SetLayeredWindowAttributes(mHwnd, RGB(0, 0, 0), (BYTE)((100-alpha)*(255.0/100)), LWA_ALPHA);
}
BOOL WinWindow::SetLayeredAttributes(COLORREF clrKey,BYTE alpha,DWORD flag)
{
	return SetLayeredWindowAttributes(mHwnd, clrKey, alpha, flag);
}
BOOL WinWindow::SetForeground()
{
	return SetForegroundWindow(mHwnd);
}
HWND WinWindow::SetActive()
{
	return SetActiveWindow(mHwnd);
}
BOOL WinWindow::SetEnable(BOOL enable)
{
	return EnableWindow(mHwnd,enable);
}
BOOL WinWindow::SetText(LPCTSTR str)
{
	return SetWindowText(mHwnd,str);
}
HWND WinWindow::SetParentWnd(HWND newParent)
{
	return SetParent(mHwnd, newParent);
}
void WinWindow::SetHWND(HWND hwnd)
{
	mHwnd = hwnd;
}
HWND WinWindow::GetHWND()
{
	return mHwnd;
}
HDC WinWindow::GetDC()
{
	return GetWindowDC(mHwnd);
}
BOOL WinWindow::GetInfo(PWINDOWINFO pInfo)
{
	return GetWindowInfo(mHwnd, pInfo);
}
LONG WinWindow::GetLong(int nIndex)
{
	return GetWindowLong(mHwnd, nIndex);
}
BOOL WinWindow::GetRect(LPRECT pRect)
{
	return GetWindowRect(mHwnd, pRect);
}
int WinWindow::GetText(LPTSTR str, int maxCount)
{
	return GetWindowText(mHwnd, str, maxCount);
}
int WinWindow::GetTextLen()
{
	return GetWindowTextLength(mHwnd);
}
DWORD WinWindow::GetThreadProcessId(LPDWORD lpdwProcessld)
{
	return GetWindowThreadProcessId(mHwnd, lpdwProcessld);
}
BOOL WinWindow::GetPlacement(WINDOWPLACEMENT * lpwndpl)
{
	return GetWindowPlacement(mHwnd, lpwndpl);
}
HWND WinWindow::GetOwner()
{
	return GetWindow(mHwnd, GW_OWNER);
}
HWND WinWindow::GetChild()
{
	return GetWindow(mHwnd, GW_CHILD);
}
HWND WinWindow::GetNext()
{
	return GetWindow(mHwnd, GW_HWNDNEXT);
}
int WinWindow::ClassName(LPTSTR str, int maxCount)
{
	return GetClassName(mHwnd, str, maxCount);
}
BOOL WinWindow::IsVisible()
{
	return IsWindowVisible(mHwnd);
}
BOOL WinWindow::IsUnicode()
{
	return IsWindowUnicode(mHwnd);
}
BOOL WinWindow::IsChildWnd(HWND parent)
{
	return IsChild(parent, mHwnd);
}
BOOL WinWindow::IsMinimize()
{
	return IsIconic(mHwnd);
}
BOOL WinWindow::Open()
{
	return OpenIcon(mHwnd);
}
BOOL WinWindow::IsMaximize()
{
	return IsZoomed(mHwnd);
}
HWND WinWindow::GetParentWnd()
{
	return GetParent(mHwnd);
}
HWND WinWindow::GetDesktop()
{
	return GetDesktopWindow();
}
HWND WinWindow::Find(LPCTSTR lpClassName, LPCTSTR lpWindowName)
{
	return FindWindow(lpClassName, lpWindowName);
}
HWND WinWindow::FindChild(HWND child, LPCTSTR lpClassName, LPCTSTR lpWindowName)
{
	return FindWindowEx(mHwnd, child, lpClassName, lpWindowName);
}
HWND WinWindow::FindByPoint(POINT point)
{
	return WindowFromPoint(point);
}
HWND WinWindow::FindByDC(HDC dc)
{
	return WindowFromDC(dc);
}
BOOL WinWindow::Move(int x, int y, int wid, int hei, BOOL isRepaint)
{
	return MoveWindow(mHwnd, x, y, wid, hei, isRepaint);
}
int WinWindow::MsgBox(LPCTSTR Text, LPCTSTR Title, UINT type)
{
	return MessageBox(mHwnd, Text, Title, type);
}
BOOL WinWindow::PostMsg(UINT msg, WPARAM wparam, LPARAM lparam)
{
	return PostMessage(mHwnd, msg, wparam, lparam);
}
BOOL WinWindow::SendMsg(UINT msg, WPARAM wparam, LPARAM lparam)
{
	return SendMessage(mHwnd, msg, wparam, lparam);
}
BOOL WinWindow::QuitMsg()
{
	return PostMsg(WM_QUIT,0,0);
}
BOOL WinWindow::DestoryMsg()
{
	return PostMsg(WM_DESTROY, 0, 0);
}
BOOL WinWindow::CloseMsg()
{
	return PostMsg(WM_CLOSE, 0, 0);
}
BOOL WinWindow::PaintMsg()
{
	return PostMsg(WM_PAINT, 0, 0);
}