
// 别点我啦Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "别点我啦.h"
#include "别点我啦Dlg.h"
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


// C别点我啦Dlg 对话框



C别点我啦Dlg::C别点我啦Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C别点我啦Dlg::IDD, pParent)
	, m_count(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C别点我啦Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_mBtn);
	DDX_Control(pDX, IDC_BUTTON3, m_BtnClose);
}

BEGIN_MESSAGE_MAP(C别点我啦Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C别点我啦Dlg::OnBnClickedButton1)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON3, &C别点我啦Dlg::OnBnClickedButton3)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// C别点我啦Dlg 消息处理程序

BOOL C别点我啦Dlg::OnInitDialog()
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

void C别点我啦Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C别点我啦Dlg::OnPaint()
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
HCURSOR C别点我啦Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C别点我啦Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}




void C别点我啦Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	MessageBox(L"诶呀，太疼了");
}


int C别点我啦Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(0x1001, 1000,NULL);
	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | 0x80000L);
	this->SetBackgroundColor(RGB(255,255,255));
	this->SetLayeredWindowAttributes(RGB(255, 255, 255), 120, LWA_COLORKEY);
	this->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	this->ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	return 0;
}


void C别点我啦Dlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (IDYES == MessageBox(L"老实说，是不是tab了？", 0, MB_YESNO))
	{
		MessageBox(L"啊！居然会tab，告辞！");
	}
	else
	{
		MessageBox(L"哼！不理你了。");
	}
	PostMessage(WM_CLOSE);
}


void C别点我啦Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (this->m_count<12)
		this->m_count++;
	if (this->m_count > 10)
		this->m_BtnClose.ShowWindow(SW_SHOW);
	CDialogEx::OnTimer(nIDEvent);
}


void C别点我啦Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL C别点我啦Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (pMsg->hwnd == this->m_BtnClose.GetSafeHwnd())
		{
			CRect frect, srect;
			this->GetWindowRect(&frect);
			this->m_BtnClose.GetWindowRect(&srect);
			int wid = frect.right - srect.right;
			int hei = frect.bottom - srect.bottom - 50;
			this->m_BtnClose.SetWindowPos(0, rand() % wid, rand() % hei + 50, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			return true;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void C别点我啦Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	MessageBox(L"再见！不，再也不见。");
}


HBRUSH C别点我啦Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
