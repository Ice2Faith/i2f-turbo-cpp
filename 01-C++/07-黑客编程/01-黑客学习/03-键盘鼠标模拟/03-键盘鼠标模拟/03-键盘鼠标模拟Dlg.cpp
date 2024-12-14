
// 03-键盘鼠标模拟Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "03-键盘鼠标模拟.h"
#include "03-键盘鼠标模拟Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy03键盘鼠标模拟Dlg 对话框



CMy03键盘鼠标模拟Dlg::CMy03键盘鼠标模拟Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy03键盘鼠标模拟Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy03键盘鼠标模拟Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy03键盘鼠标模拟Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy03键盘鼠标模拟Dlg::OnBnClickedButtonPostA)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy03键盘鼠标模拟Dlg::OnBnClickedButtonPostTaskPanel)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy03键盘鼠标模拟Dlg::OnBnClickedButtonFuncShift)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy03键盘鼠标模拟Dlg::OnBnClickedButtonFuncWin)
END_MESSAGE_MAP()


// CMy03键盘鼠标模拟Dlg 消息处理程序

BOOL CMy03键盘鼠标模拟Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy03键盘鼠标模拟Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy03键盘鼠标模拟Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy03键盘鼠标模拟Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*
模拟键盘鼠标：
两种方式：
	发送消息
		SendMessage : 不建议使用，很有可能不会成功
		PostMessage : 推荐使用
	使用模拟函数API
		VOID mouse_event(BYTE bVK,BYTE bScan,DWORD dwFlag,ULONG_PTR dwExtraInfo);
		VOID keybd_event(DWORD dwFlag,DWORD dx,DWORD dy,DWORD dwData,ULONG_PTR dwExtraInfo);

定时器：
	UINT_PTR SetTimer(HWND targetWnd,UINT_PTR nIDEvent,UINT uElapse,TIMERPROC lpTimerCallbackFunc);
	回调函数原型：
		VOID (CALLBACK* TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);
	关闭定时器：
		KillTimer(...)
*/

void CMy03键盘鼠标模拟Dlg::OnBnClickedButtonPostA()
{
	::PostMessage(this->GetSafeHwnd(), WM_KEYDOWN, 'A', 1);
	::PostMessage(this->GetSafeHwnd(), WM_KEYUP, 'A', 1);
}


void CMy03键盘鼠标模拟Dlg::OnBnClickedButtonPostTaskPanel()
{
	::PostMessage(this->GetSafeHwnd(), WM_KEYDOWN, VK_CONTROL, 1);
	::PostMessage(this->GetSafeHwnd(), WM_KEYDOWN, VK_SHIFT, 1);
	::PostMessage(this->GetSafeHwnd(), WM_KEYDOWN, VK_ESCAPE, 1);
	::PostMessage(this->GetSafeHwnd(), WM_KEYUP, VK_ESCAPE, 1);
	::PostMessage(this->GetSafeHwnd(), WM_KEYUP, VK_SHIFT, 1);
	::PostMessage(this->GetSafeHwnd(), WM_KEYUP, VK_CONTROL, 1);
}


void CMy03键盘鼠标模拟Dlg::OnBnClickedButtonFuncShift()
{
	//键盘模拟
	keybd_event(VK_SHIFT, 0, 0, 0);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
}


void CMy03键盘鼠标模拟Dlg::OnBnClickedButtonFuncWin()
{
	//鼠标点击Win图标
	//获得屏幕尺寸
	int wid=GetSystemMetrics(SM_CXSCREEN);
	int hei = GetSystemMetrics(SM_CYSCREEN);
	//移动鼠标到屏幕绝对坐标，如果是窗口坐标的话需要转换为屏幕坐标：BOOL ClientToScreen(HWND targetWnd,LPPOINT point)
	SetCursorPos(10, hei - 10);
	//鼠标按键模拟
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
