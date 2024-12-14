
// 15-对话框常用控件Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "15-对话框常用控件.h"
#include "15-对话框常用控件Dlg.h"
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


// CMy15对话框常用控件Dlg 对话框



CMy15对话框常用控件Dlg::CMy15对话框常用控件Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy15对话框常用控件Dlg::IDD, pParent)
	, m_str(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy15对话框常用控件Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2, m_button);
	DDX_Text(pDX, IDC_EDIT1, m_str);
	DDX_Control(pDX, IDC_BUTTON4, m_Clickme);
}

BEGIN_MESSAGE_MAP(CMy15对话框常用控件Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy15对话框常用控件Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy15对话框常用控件Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMy15对话框常用控件Dlg 消息处理程序

BOOL CMy15对话框常用控件Dlg::OnInitDialog()
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
	this->m_button.SetWindowTextW(TEXT("点不着"));
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	//获取图标大小
	BITMAP bm;
	bitmap.GetBitmap(&bm);
	this->m_button.MoveWindow(0, 0, bm.bmWidth, bm.bmHeight);
	//this->m_button.SetBitmap(bitmap);
	//通过路径获取位图宏，可以指定大小
#define HBMP(filepath,width,height) \
	(HBITMAP)LoadImage(AfxGetInstanceHandle(),filepath,IMAGE_BITMAP,width,height,LR_LOADFROMFILE|LR_CREATEDIBSECTION)
	this->m_button.SetBitmap(HBMP(TEXT("../02.bmp"),100,50));
	//通过路径获取Icon宏
#define HICO(filapath) \
	(HICON)LoadImage(AfxGetInstanceHandle(), filepath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE |LR_DEFAULTSIZE)
	//图片大小和按钮大小设置一致

	//赋值关联变量
	m_str = TEXT("请输入");
	UpdateData(FALSE);//更新数据进行显示FALSE
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy15对话框常用控件Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy15对话框常用控件Dlg::OnPaint()
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
HCURSOR CMy15对话框常用控件Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//点击按钮时调用
void CMy15对话框常用控件Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	MessageBox(TEXT("点中我了"));
}


void CMy15对话框常用控件Dlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);//将对话框的数据更新到关联变量TRUE
	MessageBox(m_str);
}
/*类视图添加类MyButton，继承CButton类，实现消息出来函数MouseMove,
工具箱添加按钮，选中按钮，选择添加变量，Control，MYbutton类型即可*/
