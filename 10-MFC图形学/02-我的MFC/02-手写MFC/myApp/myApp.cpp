#include<afxwin.h>
#include"myApp.h"

myApp app;
BEGIN_MESSAGE_MAP(myWindow, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

BOOL myApp::InitInstance()
{
	this->m_pMainWnd = new myWindow;
	this->m_pMainWnd->ShowWindow(this->m_nCmdShow);
	this->m_pMainWnd->UpdateWindow();
	return CWinApp::InitInstance();
}

myWindow::myWindow() :m_wHei(GetSystemMetrics(SM_CYSCREEN) * 6 / 10), m_wWid(GetSystemMetrics(SM_CXSCREEN) * 6 / 10)
{
	RECT wrect;
	wrect.left = GetSystemMetrics(SM_CXSCREEN)/2-m_wWid/2;
	wrect.top = GetSystemMetrics(SM_CYSCREEN)/2 - m_wHei / 2;
	wrect.right = wrect.left+m_wWid;
	wrect.bottom = wrect.top+m_wHei;
	this->Create(NULL,
		_T("MyApp - Ice2Faith"),
		WS_OVERLAPPEDWINDOW,
		wrect,
		NULL,
		NULL,
		WS_EX_ACCEPTFILES,
		NULL
		);
}
int myWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd:: OnCreate(lpCreateStruct) == -1)
		return -1;
	m_listbox = new myListBox;
	m_listbox->Create(WS_VISIBLE | WS_BORDER, CRect(200, 200, 900, 400), this, 102);
	m_listbox->ShowWindow(SW_SHOWNORMAL);
	m_edit = new myEdit;
	m_edit->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(200, 140, 900, 180), this, 101);
	m_edit->ShowWindow(SW_SHOWNORMAL);
	m_enter = new myButton;
	m_enter->Create(L"确认", WS_CHILD | BS_DEFPUSHBUTTON, CRect(60, 60, 140, 120), this, 100);
	m_enter->ShowWindow(SW_SHOWNORMAL);
	return 0;
}

void myWindow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CFrameWnd::OnPaint()
	CRect rect;
	this->GetClientRect(&rect);
	dc.DrawText(TEXT("Hello"), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}


void myWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case VK_CONTROL:
		MessageBox(L"Control Down", L"KeyDown");
		break;
	default:
		MessageBox(L"Other Key Down", L"KeyDown");
	}
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void myWindow::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int filecount = DragQueryFile(hDropInfo, -1, NULL, 0);
	for (int i = 0; i < filecount; i++)
	{
		wchar_t filename[2048] ={0};
		DragQueryFile(hDropInfo, i, filename, MAX_PATH);
			m_listbox->AddString(filename);
	}
	DragFinish(hDropInfo);
	CFrameWnd::OnDropFiles(hDropInfo);
}
BEGIN_MESSAGE_MAP(myButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &myButton::OnBnClicked)
END_MESSAGE_MAP()
void myButton::OnBnClicked()
{
	// TODO:  在此添加控件通知处理程序代码
		MessageBox(L"Click", L"按钮");

}



BEGIN_MESSAGE_MAP(myListBox, CListBox)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


void myListBox::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int filecount = DragQueryFile(hDropInfo, -1, NULL, 0);
	for (int i = 0; i < filecount; i++)
	{
		wchar_t filename[2048] = { 0 };
		DragQueryFile(hDropInfo, i, filename, MAX_PATH);
		MessageBox(filename, L"List New FIle");
		AddString(filename);
	}
	DragFinish(hDropInfo);
	CListBox::OnDropFiles(hDropInfo);
}
