
// 01-Win消息示例Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "01-Win消息示例.h"
#include "01-Win消息示例Dlg.h"
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


// CMy01Win消息示例Dlg 对话框



CMy01Win消息示例Dlg::CMy01Win消息示例Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy01Win消息示例Dlg::IDD, pParent)
	, m_title(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy01Win消息示例Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_title);
}

BEGIN_MESSAGE_MAP(CMy01Win消息示例Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CMy01Win消息示例Dlg::OnBnClickedButtonCloseNotepad)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy01Win消息示例Dlg::OnBnClickedButtonOpenNotepad)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy01Win消息示例Dlg::OnBnClickedButtonSetNotepadTitle)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy01Win消息示例Dlg::OnBnClickedButtonGetNotepadTitle)
END_MESSAGE_MAP()


// CMy01Win消息示例Dlg 消息处理程序

BOOL CMy01Win消息示例Dlg::OnInitDialog()
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

void CMy01Win消息示例Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy01Win消息示例Dlg::OnPaint()
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
HCURSOR CMy01Win消息示例Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
Windows程序执行流程：
主程序:
	WinMain入口
	RegisterClassEx注册窗口类名
		loop:
		GetMessage获取消息	| 发送、提取消息从-消息队列
		DispatchMessage分发消息 | 回调、调用-系统程序模块
	WinMain结束

窗口过程：
	系统程序模块分发消息
		判断消息的值
			1.用户自己的消息处理
			2.DefWindowProc系统默认的消息处理
	返回系统程序模块

系统程序模块：
	接受分发的消息
	管理窗口句柄和窗口类地址
	管理窗口类信息

窗口类：
	一个管理满足某个特征的窗口模板
*/


void CMy01Win消息示例Dlg::OnBnClickedButtonCloseNotepad()
{
	//HWND FindWindow(LPCTSTR className,LPCTSTR windowTitle);
	//通过类名、窗口标题查找窗口，当只会用到一个时，另一个参数直接设置为NULL
	//关于查找窗口类名，可以通过VS的Spy++工具进行查找
	HWND hwnd = ::FindWindow(TEXT("Notepad"), NULL);
	//也可以通过窗口句柄在进行查询类名
	TCHAR winClass[512];
	::RealGetWindowClass(hwnd, winClass, 512);
	if (hwnd != NULL)
	{
		//LRESULT SendMessage(HWND targetWnd,UINT msgType,WPARAM wParam.LPARAM lParam);
		//给目标窗口发送一条指定类型带参数的消息，如果消息的附加参数没有设置，则值为0、NULL。
		::SendMessage(hwnd, WM_CLOSE, NULL, NULL);
	}
}


void CMy01Win消息示例Dlg::OnBnClickedButtonOpenNotepad()
{
	WinExec("notepad.exe", SW_SHOW);
}


void CMy01Win消息示例Dlg::OnBnClickedButtonSetNotepadTitle()
{
	HWND hwnd = ::FindWindow(NULL, TEXT("无标题 - 记事本"));
	if (hwnd != NULL)
	{
		UpdateData(TRUE);
		::SendMessage(hwnd, WM_SETTEXT, NULL, (LPARAM)m_title.GetBuffer());
	}
}


void CMy01Win消息示例Dlg::OnBnClickedButtonGetNotepadTitle()
{
	HWND hwnd = ::FindWindow(TEXT("Notepad"), NULL);
	if (hwnd != NULL)
	{
		TCHAR arr[1024];
		::SendMessage(hwnd, WM_GETTEXT, (WPARAM)1024, (LPARAM)arr);
		m_title = arr;
		UpdateData(FALSE);
	}
}
