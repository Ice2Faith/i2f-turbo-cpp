
// Win10半透明Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Win10半透明.h"
#include "Win10半透明Dlg.h"
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


// CWin10半透明Dlg 对话框



CWin10半透明Dlg::CWin10半透明Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWin10半透明Dlg::IDD, pParent)
	, m_ck_explorer(FALSE)
	, m_ck_ctrlcenter(FALSE)
	, m_ck_startmenu(FALSE)
	, m_ck_winsearch(FALSE)
	, m_ck_notifyicon(FALSE)
	, m_ck_console(FALSE)
	, m_ck_notepad(FALSE)
	, m_ck_win7cal(FALSE)
	, m_ck_run(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWin10半透明Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_EXPLORER, m_ck_explorer);
	DDX_Check(pDX, IDC_CHECK_CTRLCENTER, m_ck_ctrlcenter);
	DDX_Check(pDX, IDC_CHECK_STARTMENU, m_ck_startmenu);
	DDX_Check(pDX, IDC_CHECK_WINSEARCH, m_ck_winsearch);
	DDX_Check(pDX, IDC_CHECK_NOTIFYICON, m_ck_notifyicon);
	DDX_Control(pDX, IDC_CHECK_CKALL, m_ck_all);
	DDX_Check(pDX, IDC_CHECK_CONSOLE, m_ck_console);
	DDX_Check(pDX, IDC_CHECK_NOTEPAD, m_ck_notepad);
	DDX_Check(pDX, IDC_CHECK_WINSVCAL, m_ck_win7cal);
	DDX_Check(pDX, IDC_CHECK_RUN, m_ck_run);
}

BEGIN_MESSAGE_MAP(CWin10半透明Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CWin10半透明Dlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_USE, &CWin10半透明Dlg::OnBnClickedButtonUse)
	ON_BN_CLICKED(IDC_CHECK_CKALL, &CWin10半透明Dlg::OnBnClickedCheckCkall)
END_MESSAGE_MAP()


// CWin10半透明Dlg 消息处理程序

BOOL CWin10半透明Dlg::OnInitDialog()
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
	this->SetBackgroundColor(0xffffff);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWin10半透明Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWin10半透明Dlg::OnPaint()
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
HCURSOR CWin10半透明Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWin10半透明Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}

BOOL CWin10半透明Dlg::SetTransParent(HWND mHwnd,float alpha)
{
	LONG wlong = ::GetWindowLong(mHwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
	::SetWindowLong(mHwnd, GWL_EXSTYLE, wlong);
	return ::SetLayeredWindowAttributes(mHwnd, RGB(0, 0, 0), (BYTE)((100 - alpha)*(255.0 / 100)), LWA_ALPHA);
}

void CWin10半透明Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	HWND hwnd = 0;
	if (nIDEvent == ID_TIMER_LOOP)
	{
		if (m_ck_explorer == TRUE)
		{
			hwnd=::FindWindow(L"CabinetWClass", NULL);
			SetTransParent(hwnd, 20);
		}
		if (m_ck_ctrlcenter == TRUE)
		{
			hwnd = ::FindWindow(NULL, L"操作中心"); 
			SetTransParent(hwnd, 30);
			hwnd = ::FindWindow(L"Windows.UI.Core.CoreWindow", L"操作中心");
			SetTransParent(hwnd, 30);
		}
		if (m_ck_startmenu == TRUE)
		{
			hwnd = ::FindWindow(NULL, L"启动");
			SetTransParent(hwnd, 30);
		}
		if (m_ck_winsearch == TRUE)
		{
			hwnd = ::FindWindow(L"Windows.UI.Core.CoreWindow", NULL); 
			SetTransParent(hwnd, 20);
			hwnd = ::FindWindow(L"Windows.UI.Core.CoreWindow", L"Cortana(小娜)");
			SetTransParent(hwnd, 20);
		}
		if (m_ck_notifyicon == TRUE)
		{
			hwnd = ::FindWindow(L"NotifyIconOverflowWindow", NULL);
			SetTransParent(hwnd, 20);
		}
		if (m_ck_console == TRUE)
		{
			hwnd = ::FindWindow(L"ConsoleWindowClass", NULL);
			SetTransParent(hwnd, 20);
		}
		if (m_ck_notepad == TRUE)
		{
			hwnd = ::FindWindow(L"Notepad", NULL);
			SetTransParent(hwnd, 20);
		}
		if (m_ck_win7cal == TRUE)
		{
			hwnd = ::FindWindow(L"CalcFrame", L"计算器");
			SetTransParent(hwnd, 20);
		}
		if (m_ck_run == TRUE)
		{
			hwnd = ::FindWindow(NULL, L"运行");
			SetTransParent(hwnd, 20);
		}
		
		
	}
	CDialogEx::OnTimer(nIDEvent);
}



void CWin10半透明Dlg::OnBnClickedButtonUse()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	this->ShowWindow(SW_HIDE);
	SetTimer(ID_TIMER_LOOP,60,NULL);
}


void CWin10半透明Dlg::OnBnClickedCheckCkall()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_ck_all.GetCheck() == 1)
	{
		m_ck_ctrlcenter = TRUE;
		m_ck_explorer = TRUE;
		m_ck_notifyicon = TRUE;
		m_ck_startmenu = TRUE;
		m_ck_winsearch = TRUE;
		m_ck_console = TRUE;
		m_ck_notepad = TRUE;
		m_ck_run = TRUE;
	}
	else
	{
		m_ck_ctrlcenter = FALSE;
		m_ck_explorer = FALSE;
		m_ck_notifyicon = FALSE;
		m_ck_startmenu = FALSE;
		m_ck_winsearch = FALSE;
		m_ck_console = FALSE;
		m_ck_notepad = FALSE;
		m_ck_run = FALSE;
	}
	UpdateData(FALSE);
}
