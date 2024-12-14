
// 26-驱动的装载程序Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "26-驱动的装载程序.h"
#include "26-驱动的装载程序Dlg.h"
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


// CMy26驱动的装载程序Dlg 对话框



CMy26驱动的装载程序Dlg::CMy26驱动的装载程序Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy26驱动的装载程序Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy26驱动的装载程序Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy26驱动的装载程序Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy26驱动的装载程序Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_INSTALL, &CMy26驱动的装载程序Dlg::OnBnClickedButtonInstall)
	ON_BN_CLICKED(IDC_BUTTON_UNINSTALL, &CMy26驱动的装载程序Dlg::OnBnClickedButtonUninstall)
END_MESSAGE_MAP()


// CMy26驱动的装载程序Dlg 消息处理程序

BOOL CMy26驱动的装载程序Dlg::OnInitDialog()
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

void CMy26驱动的装载程序Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy26驱动的装载程序Dlg::OnPaint()
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
HCURSOR CMy26驱动的装载程序Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy26驱动的装载程序Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}
/*
常见的驱动程序分成两类：
	NT式驱动程序：不支持即插即用，基于服务，需要手动安装
	WDM式驱动程序：支持即插即用的，需要INF文件进行自动安装
*/
#include<winsvc.h>
void CMy26驱动的装载程序Dlg::OnBnClickedButtonInstall()
{
	//获取输入框数据
	TCHAR szDrivePath[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_MFCEDITBROWSE_DRIVE_NAME,szDrivePath,MAX_PATH);
	if (lstrlen(szDrivePath) == 0)
		return;
	//获取文件名
	TCHAR szFileName[MAX_PATH] = { 0 };
	::_tsplitpath(szDrivePath,NULL,NULL,szFileName,NULL);
	//打开服务管理器
	SC_HANDLE hScm;
	hScm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hScm == INVALID_HANDLE_VALUE)
		return;
	//创建服务
	SC_HANDLE hService;
	hService = CreateService(hScm, szFileName, szFileName,
		SERVICE_ALL_ACCESS,
		SERVICE_KERNEL_DRIVER,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_IGNORE,
		szDrivePath, NULL, NULL,
		NULL, NULL, NULL);
	if (hService == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hScm);
		return;
	}
	//启动服务
	BOOL ret=StartService(hService, NULL, NULL);
	CloseHandle(hService);
	CloseHandle(hScm);	
	if (ret)
	{
		MessageBox(_T("驱动安装成功，并已经启动！！"));
	}
}


void CMy26驱动的装载程序Dlg::OnBnClickedButtonUninstall()
{

	//获取输入框数据
	TCHAR szDrivePath[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_MFCEDITBROWSE_DRIVE_NAME, szDrivePath, MAX_PATH);
	if (lstrlen(szDrivePath) == 0)
		return;
	//获取文件名
	TCHAR szFileName[MAX_PATH] = { 0 };
	::_tsplitpath(szDrivePath, NULL, NULL, szFileName, NULL);
	//打开服务管理器
	SC_HANDLE hScm;
	hScm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hScm == INVALID_HANDLE_VALUE)
		return;
	//打开服务
	SC_HANDLE hService;
	hService = OpenService(hScm, szFileName, SERVICE_ALL_ACCESS);
	if (hService == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hScm);
		return;
	}
	//停止服务
	SERVICE_STATUS status = { 0 };
	BOOL ret=ControlService(hService, SERVICE_CONTROL_STOP, &status);
	if (ret == false)
	{
		CloseHandle(hService);
		CloseHandle(hScm);
		return;
	}
	//删除服务
	ret=DeleteService(hService);
	CloseHandle(hService);
	CloseHandle(hScm);
	if (ret)
	{
		MessageBox(_T("驱动已停止并卸载完毕！！"));
	}
}
