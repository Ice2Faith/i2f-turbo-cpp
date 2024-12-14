
// 04-自定义消息Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "04-自定义消息.h"
#include "04-自定义消息Dlg.h"
#include "afxdialogex.h"
#include"resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_SELFMSG (WM_USER+0x101)

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


// CMy04自定义消息Dlg 对话框



CMy04自定义消息Dlg::CMy04自定义消息Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy04自定义消息Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy04自定义消息Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_recvmsg);
}

BEGIN_MESSAGE_MAP(CMy04自定义消息Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SELFMSG,SelfMsgProc)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy04自定义消息Dlg::OnBnClickedButtonSendSelfMsg)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy04自定义消息Dlg::OnBnClickedButtonSendCopyData)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CMy04自定义消息Dlg 消息处理程序

BOOL CMy04自定义消息Dlg::OnInitDialog()
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

void CMy04自定义消息Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy04自定义消息Dlg::OnPaint()
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
HCURSOR CMy04自定义消息Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*
自定义消息的使用：
	适用于简单数据类型，基本数据类型传递，或者不传递数据参数，不能用于复杂数据类型传递
	1.定义自定义消息
		#define WM_SELFMSG (WM_USER+0x101)
	2.添加响应函数
		afx_msg LRESULT SelfMsgProc(WPARAM wParam, LPARAM lParam);
	3.添加消息映射函数
		ON_MESSAGE(WM_SELFMSG,SelfMsgProc)
	4.实现SelfMsgProc响应函数

系统数据拷贝消息：WM_COPYDATA:
	适用于数据拷贝传输，不限制数据类型和大小
	消息只能用SendMessage发送，不能用PostMessage发送
	发送参数示例：
		SendMessage(Hwnd targetWnd,WM_COPYDATA,(WPARAM)sendHwnd,(LPARAM)COPYDATASTRUCT * lpdata);
	结构体说明：
		typedef struct tagCOPYDATASTRUCT {
		ULONG_PTR dwData;//自定义的数据，有时候用来存放内嵌的自定义消息等，不用时为空（0）即可
		DWORD cbData;//数据的大小字节，用来标识数据指针指向数据的大小
		PVOID lpData;//指向数据的万能指针
		} COPYDATASTRUCT, *PCOPYDATASTRUCT;
	步骤：
		1.发送结构体
		2.实现WM_COPYDATA的消息处理函数（通过类向导直接添加即可）
*/

LRESULT CMy04自定义消息Dlg::SelfMsgProc(WPARAM wParam, LPARAM lParam)
{
	CString str;
	str.Format(TEXT("%d,%d"), (int)wParam, (int)lParam);
	SetDlgItemText(IDC_EDIT1, str);
	return 0;
}

void CMy04自定义消息Dlg::OnBnClickedButtonSendSelfMsg()
{
	int num1 = GetDlgItemInt(IDC_EDIT2, FALSE, FALSE);
	int num2 = GetDlgItemInt(IDC_EDIT3, FALSE, FALSE);
	::SendMessage(this->GetSafeHwnd(), WM_SELFMSG, (WPARAM)num1,(LPARAM)num2);
}


void CMy04自定义消息Dlg::OnBnClickedButtonSendCopyData()
{
	CString str;
	GetDlgItemText(IDC_EDIT4, str);
	COPYDATASTRUCT data;
	data.dwData = 0;//没有附加信息
	data.cbData = str.GetLength()*2+1;//由于是采用Unicode编码，一次真实大小是字符长度的二倍
	data.lpData = str.GetBuffer();//得到字符指针
	::SendMessage(this->GetSafeHwnd(), WM_COPYDATA, (WPARAM)this->GetSafeHwnd(), (LPARAM)&data);
}


BOOL CMy04自定义消息Dlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	CString str;
	str.Format(TEXT("%s"),(TCHAR *) pCopyDataStruct->lpData);
	SetDlgItemText(IDC_EDIT1, str);

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}
