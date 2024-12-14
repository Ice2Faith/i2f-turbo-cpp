
// 17-服务相关编程-服务管理器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "17-服务相关编程-服务管理器.h"
#include "17-服务相关编程-服务管理器Dlg.h"
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


// CMy17服务相关编程服务管理器Dlg 对话框



CMy17服务相关编程服务管理器Dlg::CMy17服务相关编程服务管理器Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy17服务相关编程服务管理器Dlg::IDD, pParent)
	, m_display_type(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy17服务相关编程服务管理器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SERVICE, m_list_service);
}

BEGIN_MESSAGE_MAP(CMy17服务相关编程服务管理器Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CMy17服务相关编程服务管理器Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CMy17服务相关编程服务管理器Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_WINAPP, &CMy17服务相关编程服务管理器Dlg::OnBnClickedRadioWinapp)
	ON_BN_CLICKED(IDC_RADIO_DRIVE, &CMy17服务相关编程服务管理器Dlg::OnBnClickedRadioDrive)
	ON_BN_CLICKED(IDC_BUTTON_START, &CMy17服务相关编程服务管理器Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_BAN, &CMy17服务相关编程服务管理器Dlg::OnBnClickedButtonBan)
	ON_BN_CLICKED(IDC_RADIO_ALLSVC, &CMy17服务相关编程服务管理器Dlg::OnBnClickedRadioAllsvc)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_SERVICE, &CMy17服务相关编程服务管理器Dlg::OnLvnColumnclickListService)
END_MESSAGE_MAP()


// CMy17服务相关编程服务管理器Dlg 消息处理程序

BOOL CMy17服务相关编程服务管理器Dlg::OnInitDialog()
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
	InitView();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy17服务相关编程服务管理器Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy17服务相关编程服务管理器Dlg::OnPaint()
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
HCURSOR CMy17服务相关编程服务管理器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*
	特别的引入头文件：
		#include<winnt.h>//NT 系统支持
		#include<winsvc.h>//service 支持
	枚举服务类型：
		SERVICE_DRIVE:驱动服务类型
		SERVICE_WIN32:Win32应用服务类型
		SERVICE_TYPE_ALL:所有服务类型

	打开和关闭服务管理器：
		打开服务管理器函数：SC_HANDLE OpenSCManager(
			LPCTSTR lpMachineName,//想要打开的服务控制管理器数据库的主机名，本机为NULL
			LPCTSTR lpDataBaseName,//指向目标主机SCM数据库名字的字符串
			DWORD dwDesiredAccess);//指定对SCM数据库的访问权限
		返回值：成功返回句柄，失败返回NULL

		关闭服务句柄函数：BOOL CloseServiceHandle(SC_HANDLE hscobj);
		作用：用来关闭OpenSCManager和OpenService打开的句柄

	服务的枚举：
		枚举函数：BOOL EnumServicesStatus(
			SC_HANDLE hscManager,//服务管理器句柄
			DWORD dwServiceType,//指定枚举的服务类型
			DWORD dwServiceState,//枚举指定状态的服务
			LPENUM_SERVICE_STATUS lpServiceBuffer,//结构指针
			DWORD cbBufferSize,//缓冲区大小
			LPDWORD pcbBytesNeeded,//返回实际使用的缓冲区大小
			LPDWORD lpServiceCountReturned,//返回枚举的服务的个数
			LPDWORD lpResumeHandle);//返回枚举是否成功

		结构定义：
			typedef struct _ENUM_SERVICE_STATUSW {
			LPTSTR            lpServiceName;
			LPTSTR            lpDisplayName;
			SERVICE_STATUS    ServiceStatus;
			} ENUM_SERVICE_STATUS, *LPENUM_SERVICE_STATUS;

			typedef struct _SERVICE_STATUS {
			DWORD   dwServiceType;
			DWORD   dwCurrentState;
			DWORD   dwControlsAccepted;
			DWORD   dwWin32ExitCode;
			DWORD   dwServiceSpecificExitCode;
			DWORD   dwCheckPoint;
			DWORD   dwWaitHint;
			} SERVICE_STATUS, *LPSERVICE_STATUS;

	服务的启动和停止：
		打开服务函数：SC_HANDLE OpenService(
			SC_HANDLE hscManager,//服务管理器句柄
			LPCTSTR lpServiceName,//要打开的服务名字符串
			DWORD dwDesiredAccess);//要打开的服务的访问权限，为了方便，一般：SC_MANAGER_ALL_ACCESS
		返回值：失败NULL，成功打开的服务句柄

		启动服务函数：BOOL StartService(
			SC_HANDLE hService,//已经打开的服务句柄
			DWORD dwNUmServiceArgs,//指向启动服务所需的参数个数
			LPCTSTR * lpServiceArgVectors);//参数向量

		停止服务函数：BOOL ControlService(
			SC_HANDLE hservice,//已经打开的服务句柄
			DWORD dwControl,//要发送的控制码
			LPSERVICE_STATUS lpServiceStatus);//返回服务的状态
			停止服务的控制码：SERVICE_CONTROL_STOP
			注意，没有StopService
*/
#include<winnt.h>
#include<winsvc.h>
void CMy17服务相关编程服务管理器Dlg::InitView()
{
	//设置list扩展属性网格线选择整行
	m_list_service.SetExtendedStyle(m_list_service.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//插入list列
	m_list_service.InsertColumn(0, TEXT("服务名                "));
	m_list_service.InsertColumn(1, TEXT("显示名                                "));
	m_list_service.InsertColumn(2, TEXT("状态   "));
	//设置list列宽
	m_list_service.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_list_service.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_list_service.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	//默认选中WinAppService
	CheckDlgButton(IDC_RADIO_WINAPP, 1);
	//显示更新list
	m_display_type = SERVICE_WIN32;
	UpdateList(m_display_type);
}
void CMy17服务相关编程服务管理器Dlg::UpdateList(unsigned long serviceType)
{
	m_list_service.DeleteAllItems();

	//打开服务管理器
	SC_HANDLE  hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		return;
	}
	//查询服务数量和数据量大小，使用一些错误参数获取的技巧
	DWORD serviceCount = 0;
	DWORD dwSize = 0;
	BOOL ret = EnumServicesStatus(hSCM, serviceType, SERVICE_STATE_ALL, NULL, 0, &dwSize, &serviceCount, NULL);
	//定义接受数据的指针
	LPENUM_SERVICE_STATUS lpInfo;
	//由于上面的查询，因为没有给定接受缓冲区，调用失败ERROR_MORE_DATA，需要更大的缓冲区
	if (!ret && GetLastError() == ERROR_MORE_DATA)
	{
		//申请匹配空间
		lpInfo = (LPENUM_SERVICE_STATUS)(new BYTE[dwSize]);
		//获取服务数据并保存
		ret = EnumServicesStatus(hSCM, serviceType, SERVICE_STATE_ALL, (LPENUM_SERVICE_STATUS)lpInfo, dwSize, &dwSize, &serviceCount, NULL);
		if (!ret)
		{
			//服务数据获取失败则关闭服务句柄
			CloseServiceHandle(hSCM);
			return;
		}
		//遍历获得的服务，进行填充到列表
		for (DWORD i = 0; i < serviceCount; i++)
		{
			m_list_service.InsertItem(i, lpInfo[i].lpServiceName);
			m_list_service.SetItemText(i, 1, lpInfo[i].lpDisplayName);
			switch (lpInfo[i].ServiceStatus.dwCurrentState)
			{
			case SERVICE_PAUSED:
				m_list_service.SetItemText(i, 2, TEXT("暂停"));
				break;
			case SERVICE_STOPPED:
				m_list_service.SetItemText(i, 2, TEXT("停止"));
				break;
			case SERVICE_RUNNING:
				m_list_service.SetItemText(i, 2, TEXT("运行"));
				break;
			default:
				m_list_service.SetItemText(i, 2, TEXT("其他"));
				break;
			}
		}
		delete lpInfo;
	}
	CloseServiceHandle(hSCM);
}

void CMy17服务相关编程服务管理器Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMy17服务相关编程服务管理器Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CMy17服务相关编程服务管理器Dlg::OnBnClickedRadioWinapp()
{
	if (IsDlgButtonChecked(IDC_RADIO_WINAPP))
	{
		m_display_type = SERVICE_WIN32;
		UpdateList(m_display_type);
	}
}


void CMy17服务相关编程服务管理器Dlg::OnBnClickedRadioDrive()
{
	if (IsDlgButtonChecked(IDC_RADIO_DRIVE))
	{
		m_display_type = SERVICE_DRIVER;
		UpdateList(m_display_type);
	}
}


void CMy17服务相关编程服务管理器Dlg::OnBnClickedRadioAllsvc()
{
	if (IsDlgButtonChecked(IDC_RADIO_ALLSVC))
	{
		m_display_type = SERVICE_DRIVER;
		UpdateList(m_display_type);
	}
}

void CMy17服务相关编程服务管理器Dlg::OnBnClickedButtonStart()
{
	//获取选中项索引
	POSITION pos = m_list_service.GetFirstSelectedItemPosition();
	int selIndex = -1;
	while (pos)
	{
		selIndex = m_list_service.GetNextSelectedItem(pos);
	}
	if (selIndex == -1)
	{
		return;
	}
	//获取选中项的服务名
	TCHAR szServiceName[MAXBYTE] = { 0 };
	m_list_service.GetItemText(selIndex, 0, szServiceName, MAXBYTE);
	//打开服务管理器
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		return;
	}
	//打开选中的服务
	SC_HANDLE hservice = OpenService(hSCM, szServiceName, SERVICE_ALL_ACCESS);
	//启动服务
	BOOL ret = StartService(hservice, 0, NULL);
	if (ret == TRUE)
	{
		m_list_service.SetItemText(selIndex, 2, TEXT("运行"));
	}
	else
	{
		MessageBox(TEXT("服务启动失败！！"), TEXT("服务提示"));
	}
	//关闭服务句柄
	CloseServiceHandle(hservice);
	CloseServiceHandle(hSCM);
}


void CMy17服务相关编程服务管理器Dlg::OnBnClickedButtonBan()
{
	POSITION pos = m_list_service.GetFirstSelectedItemPosition();
	int selIndex = -1;
	while (pos)
	{
		selIndex = m_list_service.GetNextSelectedItem(pos);
	}
	if (selIndex == -1)
	{
		return;
	}
	TCHAR szServiceName[MAXBYTE] = { 0 };
	m_list_service.GetItemText(selIndex, 0, szServiceName, MAXBYTE);
	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		return;
	}
	SC_HANDLE hservice = OpenService(hSCM, szServiceName, SERVICE_ALL_ACCESS);
	SERVICE_STATUS serviceState;
	//停止服务，没有StopService，只有ControlService
	BOOL ret = ControlService(hservice, SERVICE_CONTROL_STOP, &serviceState);
	if (ret == TRUE)
	{
		m_list_service.SetItemText(selIndex, 2, TEXT("停止"));
	}
	else
	{
		MessageBox(TEXT("服务停止失败！！"), TEXT("服务提示"));
	}
	CloseServiceHandle(hservice);
	CloseServiceHandle(hSCM);
}
//list按列排序的参数和回调函数
int sort_column;
bool sort_direct=false;
int CALLBACK CompareListColumn(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl* list = (CListCtrl*)lParamSort;
	//获取排序列的lParam1和lParam2行的第sort_column列字符串
	CString lp1 = list->GetItemText((int)lParam1 , sort_column);
	CString lp2 = list->GetItemText((int)lParam2, sort_column);
	// 直接比较字符串ASCII
	if (sort_direct)
		return lp1.CompareNoCase(lp2);
	else
		return lp2.CompareNoCase(lp1);
}

void CMy17服务相关编程服务管理器Dlg::OnLvnColumnclickListService(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	//转换排序方向
	sort_direct = !sort_direct;
	//点击的列
	sort_column = pNMLV->iSubItem;
	// 设置i行的数据为i索引，这个数据将是排序的比较lParam1和lParam2参数
	int count = m_list_service.GetItemCount();
	for (int i = 0; i<count; i++)
		m_list_service.SetItemData(i, i); 
	//排序列表项，参数|：排序函数，额外参数（排序的lParamSort，这里直接将list地址传过去即可）
	m_list_service.SortItems(CompareListColumn, (DWORD_PTR)&m_list_service);
	*pResult = 0;
}
