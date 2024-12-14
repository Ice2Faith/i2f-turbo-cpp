#include"mymfc.h"
//有且只有一个全局对象
myApp mApp;

////////////////////////////////////////////
//myApp 实现
//程序的入口地址
BOOL myApp::InitInstance()
{
	//创建框架类
	myFrame * frame = new myFrame();
	//显示窗口
	frame->ShowWindow(SW_SHOWNORMAL);
	//更新窗口
	frame->UpdateWindow();
	//保存框架类指针
	m_pMainWnd = frame;
	return TRUE;
}

///////////////////////////////////////////
//myFrame 实现
myFrame::myFrame()
{
	//CWnd类的成员函数 CWnd::Create

	//CFrameWnd继承于CWnd
	Create(NULL,L"MFC");

}
void myFrame::OnLButtonDown(UINT uint, CPoint cpint)
{
	MessageBox(L"LBUTTONDOWN",L"Tips",MB_OK);
}
void myFrame::OnPaint()
{
	CPaintDC cdc(this);
	cdc.TextOutW(0, 0, L"Hello,Win32App");
}