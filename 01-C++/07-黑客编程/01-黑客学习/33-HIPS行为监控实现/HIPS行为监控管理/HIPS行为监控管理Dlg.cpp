
// HIPS行为监控管理Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HIPS行为监控管理.h"
#include "HIPS行为监控管理Dlg.h"
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


// CHIPS行为监控管理Dlg 对话框



CHIPS行为监控管理Dlg::CHIPS行为监控管理Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHIPS行为监控管理Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHIPS行为监控管理Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SPY_ON, m_btn_spyon);
	DDX_Control(pDX, IDC_BUTTON_SPY_OFF, m_btn_spyoff);
	DDX_Control(pDX, IDC_LIST_ADMIN_LIST_LOG, m_list_hips_log);
}

BEGIN_MESSAGE_MAP(CHIPS行为监控管理Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CHIPS行为监控管理Dlg::OnBnClickedOk)
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_BUTTON_SPY_ON, &CHIPS行为监控管理Dlg::OnBnClickedButtonSpyOn)
	ON_BN_CLICKED(IDC_BUTTON_SPY_OFF, &CHIPS行为监控管理Dlg::OnBnClickedButtonSpyOff)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_LOG, &CHIPS行为监控管理Dlg::OnBnClickedButtonClearLog)
END_MESSAGE_MAP()


// CHIPS行为监控管理Dlg 消息处理程序

BOOL CHIPS行为监控管理Dlg::OnInitDialog()
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
	InitControls();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHIPS行为监控管理Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHIPS行为监控管理Dlg::OnPaint()
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
HCURSOR CHIPS行为监控管理Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHIPS行为监控管理Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}
/*
HIPS行为监控：
	通过HOOK一些系统关键的API函数，控制程序的运行
	比如，病毒或者恶意程序
		要实现自启动就要调用修改注册表的函数
		要运行就要创建进行，当然有的病毒程序通过注入的方式，避免了创建进程，附加在其他进程中运行
		要实现一些后台服务，就要调用创建服务的函数等。

*/
#include"AdminWnd.h"
#include"HipsGuard.h"
typedef VOID(*SETHOOKON)(HWND);
typedef VOID(*SETHOOKOFF)();

BOOL CHIPS行为监控管理Dlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	//强转为结构体
	PHIPS_INFO phips = (PHIPS_INFO)pCopyDataStruct->lpData;
	CString tipsInfo;
	if (phips->bisAsciiInfo == TRUE)
	{
		USES_CONVERSION;
		tipsInfo = A2T((char *)phips->wszHipsInfo);
	}
	else
	{
		tipsInfo = phips->wszHipsInfo;
	}
	//是否需要进行用户授权运行的标识
	BOOL needAdmin = TRUE;
	//由于没有设置黑白名单，因此系统中所有的应用都会频繁的修改注册表，所以这一项就不要用户授权了，避免频繁的弹出授权窗口
	if (IsDlgButtonChecked(IDC_CHECK_ONLYNOTE) == BST_CHECKED||
		phips->dwHipsClass == HIPS_CLASS_REG_SET_VALUE_EXA ||
		phips->dwHipsClass == HIPS_CLASS_REG_SET_VALUE_EXW ||
		phips->dwHipsClass == HIPS_CLASS_CREATE_FILEA ||
		phips->dwHipsClass == HIPS_CLASS_CREATE_FILEW ||
		phips->dwHipsClass == HIPS_CLASS_DELET_FILEA ||
		phips->dwHipsClass == HIPS_CLASS_DELET_FILEW ||
		phips->dwHipsClass == HIPS_CLASS_COPY_FILEEXA ||
		phips->dwHipsClass == HIPS_CLASS_COPY_FILEEXW ||
		phips->dwHipsClass == HIPS_CLASS_MOVE_FILEEXA ||
		phips->dwHipsClass == HIPS_CLASS_MOVE_FILEEXW 
		)
		needAdmin = FALSE;
	
	//显示授权对话框
	CAdminWnd adminWnd;
	
	adminWnd.m_str_tips = tipsInfo;
	adminWnd.m_waitTime = 15 * 1000;
	if (needAdmin)
		adminWnd.DoModal();
	//获取下一次要插入日志列表的下标
	int index = m_list_hips_log.GetItemCount();
	if (index >= 4096)
		m_list_hips_log.DeleteItem(0);
	//写入序号
	CString str;
	str.Format(TEXT("%d"), index);
	m_list_hips_log.InsertItem(index, str);
	//写入当前时间
	SYSTEMTIME stime;
	GetLocalTime(&stime);
	str.Format(TEXT("%04d/%02d/%02d %02d/%02d/%02d"),
		stime.wYear,
		stime.wMonth,
		stime.wDay,
		stime.wHour,
		stime.wMinute,
		stime.wSecond);
	m_list_hips_log.SetItemText(index, 1, str);
	//写入描述信息
	m_list_hips_log.SetItemText(index, 2, tipsInfo);

	//写入操作类型
	switch (phips->dwHipsClass)
	{
	case HIPS_CLASS_WIN_EXEC:
	case HIPS_CLASS_SHELL_EXECUTEA:
	case HIPS_CLASS_SHELL_EXECUTEW:
	case HIPS_CLASS_CREATE_PROCESSA:
	case HIPS_CLASS_CREATE_PROCESSW:
		str = TEXT("创建进程");
		break;
	case HIPS_CLASS_REG_SET_VALUE_EXA:
	case HIPS_CLASS_REG_SET_VALUE_EXW:
		str = TEXT("修改注册表值");
		break;
	case HIPS_CLASS_REG_DELETE_VALUEA:
	case HIPS_CLASS_REG_DELETE_VALUEW:
		str = TEXT("删除注册表值");
		break;
	case HIPS_CLASS_CREATE_SERVICEA:
	case HIPS_CLASS_CREATE_SERVICEW:
		str = TEXT("创建服务项");
		break;
	case HIPS_CLASS_ADJUST_TOKEN_PRIVILEGES:
		str = TEXT("调整进程权限");
		break;
	case HIPS_CLASS_REG_CREATE_KEYEXA:
	case HIPS_CLASS_REG_CREATE_KEYEXW:
		str = TEXT("添加注册表子键");
		break;
	case HIPS_CLASS_CREATE_FILEA:
	case HIPS_CLASS_CREATE_FILEW:
		str = TEXT("创建文件");
		break;
	case HIPS_CLASS_DELET_FILEA:
	case HIPS_CLASS_DELET_FILEW:
		str = TEXT("删除文件");
		break;
	case HIPS_CLASS_COPY_FILEEXA:
	case HIPS_CLASS_COPY_FILEEXW:
		str = TEXT("复制文件");
		break;
	case HIPS_CLASS_MOVE_FILEEXA:
	case HIPS_CLASS_MOVE_FILEEXW:
		str = TEXT("移动文件");
		break;
	}
	m_list_hips_log.SetItemText(index, 3, str);
	//写入操作结果，对于不弹出授权窗口的默认放行
	if (needAdmin)
		str = adminWnd.m_retCode == true ? TEXT("放行") : TEXT("拦截");
	else
		str = TEXT("放行");

	m_list_hips_log.SetItemText(index, 4, str);
	//返回操作结果给DLL
	if (needAdmin)
	{
		if (adminWnd.m_retCode == true)
			return HIPS_AUTH_AGREEN;
		else
			return HIPS_AUTH_REDUCE;
	}
	else
		return HIPS_AUTH_AGREEN;
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}


void CHIPS行为监控管理Dlg::InitControls()
{
	//设置拓展样式，有网格线和选择一整行
	m_list_hips_log.SetExtendedStyle(m_list_hips_log.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//插入列
	m_list_hips_log.InsertColumn(0, TEXT("序号"));
	m_list_hips_log.InsertColumn(1, TEXT("时间"));
	m_list_hips_log.InsertColumn(2, TEXT("行  为  监  控  描  述"));
	m_list_hips_log.InsertColumn(3, TEXT("类 型"));
	m_list_hips_log.InsertColumn(4, TEXT("事 件"));
	//设置自动列宽
	m_list_hips_log.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_list_hips_log.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_list_hips_log.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_list_hips_log.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_list_hips_log.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);

	m_btn_spyon.EnableWindow(TRUE);
	m_btn_spyoff.EnableWindow(FALSE);
}


void CHIPS行为监控管理Dlg::OnBnClickedButtonSpyOn()
{
	//加载DLL
	m_hInst = LoadLibrary(_T("HipsIL.dll"));
	if (m_hInst == NULL)
	{
		DWORD err = GetLastError();
		return;
	}
	//获取HOOK函数地址
	SETHOOKON SetHookOn = (SETHOOKON)GetProcAddress(m_hInst, "SetHookOn");
	//开始HOOK
	SetHookOn(this->GetSafeHwnd());
	FreeLibrary(m_hInst);
	//设置按钮状态
	m_btn_spyon.EnableWindow(FALSE);
	m_btn_spyoff.EnableWindow(TRUE);
}


void CHIPS行为监控管理Dlg::OnBnClickedButtonSpyOff()
{
	m_hInst = LoadLibrary(_T("HipsIL.dll"));
	SETHOOKOFF SetHookOff = (SETHOOKOFF)GetProcAddress(m_hInst, "SetHookOff");
	SetHookOff();
	
	FreeLibrary(m_hInst);
	//CloseHandle(m_hInst);//这一句虽然有说需要写上，但是这里调用会失败
	m_btn_spyon.EnableWindow(TRUE);
	m_btn_spyoff.EnableWindow(FALSE);
}


void CHIPS行为监控管理Dlg::OnBnClickedButtonClearLog()
{
	m_list_hips_log.DeleteAllItems();
}
