
// 19-滑块Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "19-滑块.h"
#include "19-滑块Dlg.h"
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


// CMy19滑块Dlg 对话框



CMy19滑块Dlg::CMy19滑块Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy19滑块Dlg::IDD, pParent)
	, m_hscor_size(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy19滑块Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_hscor_size);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_scrbar);
}

BEGIN_MESSAGE_MAP(CMy19滑块Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy19滑块Dlg::OnBnClickedOk)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CMy19滑块Dlg 消息处理程序

BOOL CMy19滑块Dlg::OnInitDialog()
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
	m_hscor_size = 50;
	UpdateData(FALSE);
	m_scrbar.SetScrollRange(0,100);
	m_scrbar.SetScrollPos(m_hscor_size);
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy19滑块Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy19滑块Dlg::OnPaint()
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
HCURSOR CMy19滑块Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy19滑块Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}

//水平滑块处理时间，需要在父窗口进行处理
void CMy19滑块Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int pos;
	if (pScrollBar == &m_scrbar)//比较对象
	{
		switch (nSBCode)
		{
		case SB_THUMBPOSITION://滑块上,在滑块上时nPos参数才有用，这是个坑，下面几个要注意
			m_scrbar.SetScrollPos(nPos);
			m_hscor_size = nPos;
			UpdateData(FALSE);
			break;
		case SB_LINELEFT://左箭头
			pos = m_scrbar.GetScrollPos() - 5;
			if (pos < 0)
				pos = 0;
			m_scrbar.SetScrollPos(pos);
			m_hscor_size = pos;
			UpdateData(FALSE);
			break;
		case SB_LINERIGHT://右箭头
			pos = m_scrbar.GetScrollPos() + 5;
			if (pos > 100)
				pos = 100;
			m_scrbar.SetScrollPos(pos);
			m_hscor_size = pos;
			UpdateData(FALSE);
			break;
		case SB_PAGELEFT://滑块左边
			pos = m_scrbar.GetScrollPos() - 5;
			if (pos < 0)
				pos = 0;
			m_scrbar.SetScrollPos(pos);
			m_hscor_size = pos;
			UpdateData(FALSE);
			break;
		case SB_PAGERIGHT://滑块右边
			pos = m_scrbar.GetScrollPos() + 5;
			if (pos >100)
				pos = 100;
			m_scrbar.SetScrollPos(pos);
			m_hscor_size = pos;
			UpdateData(FALSE);
			break;
		}
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
