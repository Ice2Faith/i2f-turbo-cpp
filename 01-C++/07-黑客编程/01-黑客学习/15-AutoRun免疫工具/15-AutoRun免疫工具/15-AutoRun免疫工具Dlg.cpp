
// 15-AutoRun免疫工具Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "15-AutoRun免疫工具.h"
#include "15-AutoRun免疫工具Dlg.h"
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


// CMy15AutoRun免疫工具Dlg 对话框



CMy15AutoRun免疫工具Dlg::CMy15AutoRun免疫工具Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy15AutoRun免疫工具Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy15AutoRun免疫工具Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DRIVES, m_combox_drives);
}

BEGIN_MESSAGE_MAP(CMy15AutoRun免疫工具Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy15AutoRun免疫工具Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMy15AutoRun免疫工具Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_IMMUNE, &CMy15AutoRun免疫工具Dlg::OnBnClickedButtonImmune)
	ON_BN_CLICKED(IDC_BUTTON_ANTIIMMUNE, &CMy15AutoRun免疫工具Dlg::OnBnClickedButtonAntiimmune)
	ON_BN_CLICKED(IDC_BUTTON_CREATEDIR, &CMy15AutoRun免疫工具Dlg::OnBnClickedButtonCreatedir)
	ON_BN_CLICKED(IDC_BUTTON_DELETEDIR, &CMy15AutoRun免疫工具Dlg::OnBnClickedButtonDeletedir)
END_MESSAGE_MAP()


// CMy15AutoRun免疫工具Dlg 消息处理程序

BOOL CMy15AutoRun免疫工具Dlg::OnInitDialog()
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
	InitComboxDrives();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy15AutoRun免疫工具Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy15AutoRun免疫工具Dlg::OnPaint()
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
HCURSOR CMy15AutoRun免疫工具Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy15AutoRun免疫工具Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CMy15AutoRun免疫工具Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
//获取磁盘列表到列表框中
void CMy15AutoRun免疫工具Dlg::InitComboxDrives()
{
	SetDlgItemText(IDC_COMBO_DRIVES, TEXT("请选择磁盘："));

	TCHAR drivers[MAXBYTE] = { 0 };
	GetLogicalDriveStrings(MAXBYTE, drivers);

	TCHAR * tp = drivers;
	while (*tp)
	{
		m_combox_drives.AddString(tp);
		tp += 4;
	}
}
//免疫已选择的磁盘,如果存在autorun.inf文件，则移动到免疫之后的autorun.inf文件夹
//如果存在autorun.inf文件夹，将尝试删除后进行免疫
void CMy15AutoRun免疫工具Dlg::OnBnClickedButtonImmune()
{
	//获取已选择磁盘
	TCHAR drive[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_COMBO_DRIVES, drive, MAX_PATH);
	//创建临时目录
	TCHAR tempDir[MAX_PATH] = { 0 };
	lstrcpy(tempDir, drive);
	lstrcat(tempDir,TEXT("temprature...\\"));
	BOOL ret = CreateDirectory(tempDir, NULL);
	if (!ret)
	{
		MessageBox(TEXT("无法免疫改磁盘，请选择磁盘是否可读写"), TEXT("免疫出错"));
		return;
	}
	//新创建的免疫文件夹
	lstrcat(drive, TEXT("autorun.inf"));
	//移动autorun.inf文件到临时文件夹
	TCHAR tempAuto[MAX_PATH] = { 0 };
	lstrcpy(tempAuto, tempDir);
	lstrcat(tempAuto, TEXT("\\autorun.inf"));
	MoveFile(drive, tempAuto);
	//尝试移除autorun.inf文件夹
	RemoveDirectory(drive);
	//创建免疫文件父路径并设置隐藏
	ret = CreateDirectory(drive, NULL);
	if (!ret)
	{
		MessageBox(TEXT("无法免疫改磁盘，请选择磁盘或者检查磁盘是否已存在autorun.inf文件（夹）"), TEXT("免疫出错"));
		return;
	}
	SetFileAttributes(drive, FILE_ATTRIBUTE_HIDDEN);
	//将备份的源autorun.inf文件移动到免疫父路径
	TCHAR tempTrueAuto[MAX_PATH] = { 0 };
	lstrcpy(tempTrueAuto, drive);
	lstrcat(tempTrueAuto, TEXT("\\autorun.inf"));
	MoveFile(tempAuto, tempTrueAuto);
	//删除临时目录
	RemoveDirectory(tempDir);
	//创建免疫子目录
	lstrcat(drive, TEXT("\\immune...\\"));
	ret = CreateDirectory(drive, NULL);
	if (!ret)
	{
		MessageBox(TEXT("无法免疫改磁盘，请选择磁盘或者检查磁盘是否已存在immune...文件（夹）"), TEXT("免疫出错"));
		return;
	}
	MessageBox(TEXT("免疫成功"), TEXT("免疫提示"));
}


void CMy15AutoRun免疫工具Dlg::OnBnClickedButtonAntiimmune()
{
	//删除免疫子目录
	TCHAR drive[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_COMBO_DRIVES, drive, MAX_PATH);
	lstrcat(drive, TEXT("autorun.inf\\immune...\\"));
	RemoveDirectory(drive);
	//删除免疫父目录
	ZeroMemory(drive, sizeof(drive));
	GetDlgItemText(IDC_COMBO_DRIVES, drive, MAX_PATH);
	lstrcat(drive, TEXT("autorun.inf"));
	RemoveDirectory(drive);
	MessageBox(TEXT("取消免疫成功"), TEXT("免疫提示"));
}


void CMy15AutoRun免疫工具Dlg::OnBnClickedButtonCreatedir()
{
	TCHAR path[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_EDIT_DIRPATH, path, MAX_PATH);
	CreateDirectory(path, NULL);
}


void CMy15AutoRun免疫工具Dlg::OnBnClickedButtonDeletedir()
{
	TCHAR path[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_EDIT_DIRPATH, path, MAX_PATH);
	RemoveDirectory(path);
}
