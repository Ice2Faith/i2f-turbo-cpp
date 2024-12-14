#pragma once
/*
创建Win32应用程序，属性选择在共享库中使用MFC，否则编译不通过
*/
#include<afxwin.h>
///////////////////////////////////////////
//应用程序类，CWinApp，派生类子类
class myApp:public CWinApp
{
public:
	virtual BOOL InitInstance();

private:

};
///////////////////////////////////////////
//框架类，CFrameWnd，派生类子类
class myFrame:public CFrameWnd
{
public:
	myFrame();

	afx_msg void OnLButtonDown(UINT, CPoint);
	afx_msg void OnPaint();
	//声明消息映射宏
	DECLARE_MESSAGE_MAP()
private:

};
//定义消息宏
BEGIN_MESSAGE_MAP(myFrame, CFrameWnd)
	ON_WM_LBUTTONDOWN()//和对应的函数原型绑定：afx_msg void OnLButtonDown(UINT, CPoint);
	ON_WM_PAINT()
END_MESSAGE_MAP()