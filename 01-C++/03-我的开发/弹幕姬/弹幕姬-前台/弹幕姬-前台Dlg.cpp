
// 弹幕姬-前台Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "弹幕姬-前台.h"
#include "弹幕姬-前台Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include"FooTextMsg.h"

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


// C弹幕姬前台Dlg 对话框



C弹幕姬前台Dlg::C弹幕姬前台Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C弹幕姬前台Dlg::IDD, pParent)
	, m_strFoText(_T(""))
	, m_bRandomSize(FALSE)
	, m_bRandomColor(FALSE)
	, m_bRandomSpeed(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C弹幕姬前台Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IN_FOTEXT, m_strFoText);
	DDX_Control(pDX, IDC_BUTTON_SHOOT_FT, m_btnShoot);
	DDX_Control(pDX, IDC_EDIT_IN_FOTEXT, m_edt_inMsg);
	DDX_Control(pDX, IDC_BUTTON_OPENMSG, m_btnOpenMsg);
	DDX_Control(pDX, IDC_BUTTON_CLOSEMSG, m_btnCloseMsg);
	DDX_Control(pDX, IDC_BUTTON_CLEARMSG, m_btnClearMsg);
	DDX_Control(pDX, IDC_BUTTON_SHOWMSGWND, m_btnShowMsgWnd);
	DDX_Control(pDX, IDC_BUTTON_HIDEMSGWND, m_btnHideMsgWnd);
	DDX_Check(pDX, IDC_CHECK_RANDOMSIZE, m_bRandomSize);
	DDX_Check(pDX, IDC_CHECK_RANDOMCOLOR, m_bRandomColor);
	DDX_Check(pDX, IDC_CHECK_RANDOMSPEED, m_bRandomSpeed);
	DDX_Control(pDX, IDC_SLIDER_SIZE, m_scSize);
	DDX_Control(pDX, IDC_SLIDER_CRED, m_scCRed);
	DDX_Control(pDX, IDC_SLIDER_CGREEN, m_scCGreen);
	DDX_Control(pDX, IDC_SLIDER_CBLUE, m_scCBlue);
	DDX_Control(pDX, IDC_SLIDER_SPEED, m_scSpeed);
}

BEGIN_MESSAGE_MAP(C弹幕姬前台Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C弹幕姬前台Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SHOOT_FT, &C弹幕姬前台Dlg::OnBnClickedButtonShootFt)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON_EXITBGSERVICE, &C弹幕姬前台Dlg::OnBnClickedButtonExitbgservice)
	ON_BN_CLICKED(IDC_BUTTON_OPENMSG, &C弹幕姬前台Dlg::OnBnClickedButtonOpenmsg)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEMSG, &C弹幕姬前台Dlg::OnBnClickedButtonClosemsg)
	ON_BN_CLICKED(IDC_BUTTON_CLEARMSG, &C弹幕姬前台Dlg::OnBnClickedButtonClearmsg)
	ON_BN_CLICKED(IDC_BUTTON_SHOWMSGWND, &C弹幕姬前台Dlg::OnBnClickedButtonShowmsgwnd)
	ON_BN_CLICKED(IDC_BUTTON_HIDEMSGWND, &C弹幕姬前台Dlg::OnBnClickedButtonHidemsgwnd)
	ON_BN_CLICKED(IDC_CHECK_RANDOMSIZE, &C弹幕姬前台Dlg::OnBnClickedCheckRandomsize)
	ON_BN_CLICKED(IDC_CHECK_RANDOMCOLOR, &C弹幕姬前台Dlg::OnBnClickedCheckRandomcolor)
	ON_BN_CLICKED(IDC_CHECK_RANDOMSPEED, &C弹幕姬前台Dlg::OnBnClickedCheckRandomspeed)
END_MESSAGE_MAP()


// C弹幕姬前台Dlg 消息处理程序

BOOL C弹幕姬前台Dlg::OnInitDialog()
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
	this->m_scSize.SetRange(2,150,TRUE);
	this->m_scSize.SetPos(35);
	this->m_scSpeed.SetRange(1,80);
	this->m_scSpeed.SetPos(5);
	this->m_scCRed.SetRange(0,255);
	this->m_scCRed.SetPos(200);
	this->m_scCGreen.SetRange(0,255);
	this->m_scCGreen.SetPos(80);
	this->m_scCBlue.SetRange(0,255);
	this->m_scCBlue.SetPos(120);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C弹幕姬前台Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C弹幕姬前台Dlg::OnPaint()
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
HCURSOR C弹幕姬前台Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C弹幕姬前台Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void C弹幕姬前台Dlg::OnBnClickedButtonShootFt()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strFoText.GetLength() > 0)
	{
		HWND hWnd = 0;
		hWnd=::FindWindow(L"FooTextServiceClass", NULL);
		if (hWnd)
		{
			MsgBody mb = { 0 };
			lstrcpy(mb.text,m_strFoText.GetBuffer());
			if (this->m_bRandomSize==FALSE)
				mb.size = this->m_scSize.GetPos();
			else
				mb.size = rand() % 150 + 2;
			if (this->m_bRandomSpeed == FALSE)
				mb.speed = this->m_scSpeed.GetPos();
			else
				mb.speed = rand() % 80 + 1;
			int cr=0, cg=0, cb=0;
			if (this->m_bRandomColor == FALSE)
			{
				cr = this->m_scCRed.GetPos();
				cg = this->m_scCGreen.GetPos();
				cb = this->m_scCBlue.GetPos();
			}
			else
			{
				cr = rand() % 255;
				cg = rand() % 255;
				cb = rand() % 255;
			}
			mb.color = RGB(cr,cg,cb);
			COPYDATASTRUCT cdata;
			cdata.dwData = WM_TFM_ADDTEXT;
			cdata.cbData = sizeof(MsgBody);
			cdata.lpData = (LPVOID)&mb;
			::SendMessage(hWnd,WM_COPYDATA ,0,(LPARAM)(LPVOID)&cdata);
			m_strFoText.Empty();
			UpdateData(FALSE);
		}
		else
		{
			MessageBox(L"弹幕姬-后台 程序没有在运行哦！！");
		}
	}
	else
	{
		MessageBox(L"当前还没有输入消息呢！！");
	}
}



BOOL C弹幕姬前台Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->hwnd == m_edt_inMsg.GetSafeHwnd())
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			if (pMsg->wParam == VK_RETURN)
			{
				OnBnClickedButtonShootFt();
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void C弹幕姬前台Dlg::OnBnClickedButtonExitbgservice()
{
	// TODO:  在此添加控件通知处理程序代码
	HWND hWnd = 0;
	hWnd = ::FindWindow(L"FooTextServiceClass", NULL);
	if (hWnd)
	{
		::SendMessage(hWnd, WM_CLOSE, 0, 0);
		
	}
	else
	{
		MessageBox(L"弹幕姬-后台 程序没有在运行哦！！");
	}
}


void C弹幕姬前台Dlg::OnBnClickedButtonOpenmsg()
{
	// TODO:  在此添加控件通知处理程序代码
	HWND hWnd = 0;
	hWnd = ::FindWindow(L"FooTextServiceClass", NULL);
	if (hWnd)
	{
		::SendMessage(hWnd, WM_TFM_OPEN, 0, 0);

	}
	else
	{
		MessageBox(L"弹幕姬-后台 程序没有在运行哦！！");
	}
}


void C弹幕姬前台Dlg::OnBnClickedButtonClosemsg()
{
	// TODO:  在此添加控件通知处理程序代码
	HWND hWnd = 0;
	hWnd = ::FindWindow(L"FooTextServiceClass", NULL);
	if (hWnd)
	{
		::SendMessage(hWnd, WM_TFM_CLOSE, 0, 0);

	}
	else
	{
		MessageBox(L"弹幕姬-后台 程序没有在运行哦！！");
	}
}


void C弹幕姬前台Dlg::OnBnClickedButtonClearmsg()
{
	// TODO:  在此添加控件通知处理程序代码
	HWND hWnd = 0;
	hWnd = ::FindWindow(L"FooTextServiceClass", NULL);
	if (hWnd)
	{
		::SendMessage(hWnd, WM_TFM_CLEAR, 0, 0);

	}
	else
	{
		MessageBox(L"弹幕姬-后台 程序没有在运行哦！！");
	}
}


void C弹幕姬前台Dlg::OnBnClickedButtonShowmsgwnd()
{
	// TODO:  在此添加控件通知处理程序代码
	HWND hWnd = 0;
	hWnd = ::FindWindow(L"FooTextServiceClass", NULL);
	if (hWnd)
	{
		::SendMessage(hWnd, WM_TFM_SHOW, 0, 0);

	}
	else
	{
		MessageBox(L"弹幕姬-后台 程序没有在运行哦！！");
	}
}


void C弹幕姬前台Dlg::OnBnClickedButtonHidemsgwnd()
{
	// TODO:  在此添加控件通知处理程序代码
	HWND hWnd = 0;
	hWnd = ::FindWindow(L"FooTextServiceClass", NULL);
	if (hWnd)
	{
		::SendMessage(hWnd, WM_TFM_HIDE, 0, 0);

	}
	else
	{
		MessageBox(L"弹幕姬-后台 程序没有在运行哦！！");
	}
}


void C弹幕姬前台Dlg::OnBnClickedCheckRandomsize()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (this->m_bRandomSize == FALSE)
	{
		this->m_scSize.EnableWindow(TRUE);
	}
	else
	{
		this->m_scSize.EnableWindow(FALSE);
	}
}


void C弹幕姬前台Dlg::OnBnClickedCheckRandomcolor()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (this->m_bRandomColor == FALSE)
	{
		this->m_scCRed.EnableWindow(TRUE);
		this->m_scCGreen.EnableWindow(TRUE);
		this->m_scCBlue.EnableWindow(TRUE);
	}
	else
	{
		this->m_scCRed.EnableWindow(FALSE);
		this->m_scCGreen.EnableWindow(FALSE);
		this->m_scCBlue.EnableWindow(FALSE);
	}
}


void C弹幕姬前台Dlg::OnBnClickedCheckRandomspeed()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (this->m_bRandomSpeed == FALSE)
	{
		this->m_scSpeed.EnableWindow(TRUE);
	}
	else
	{
		this->m_scSpeed.EnableWindow(FALSE);
	}
}
