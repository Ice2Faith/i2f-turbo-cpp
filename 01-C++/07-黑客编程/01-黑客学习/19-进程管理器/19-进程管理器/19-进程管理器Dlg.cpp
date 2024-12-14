
// 19-进程管理器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "19-进程管理器.h"
#include "19-进程管理器Dlg.h"
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


// CMy19进程管理器Dlg 对话框



CMy19进程管理器Dlg::CMy19进程管理器Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy19进程管理器Dlg::IDD, pParent)
	, m_create_process_path(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy19进程管理器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROCESSES, m_list_processes);
	DDX_Control(pDX, IDC_LIST_DLLS, m_list_dlls);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_CP_FILE, m_create_process_path);
	DDX_Control(pDX, IDC_CHECK_IMAGEREDIRECT, m_ckbox_image_redirect);
}

BEGIN_MESSAGE_MAP(CMy19进程管理器Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy19进程管理器Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_DLL, &CMy19进程管理器Dlg::OnBnClickedButtonViewDll)
	ON_BN_CLICKED(IDC_BUTTON_WAIT_PROCESS, &CMy19进程管理器Dlg::OnBnClickedButtonWaitProcess)
	ON_BN_CLICKED(IDC_BUTTON_RECOVERY_PROCESS, &CMy19进程管理器Dlg::OnBnClickedButtonRecoveryProcess)
	ON_BN_CLICKED(IDC_BUTTON_STOP_PROCESS, &CMy19进程管理器Dlg::OnBnClickedButtonStopProcess)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_PROCESS, &CMy19进程管理器Dlg::OnBnClickedButtonCreateProcess)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CMy19进程管理器Dlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_CHECK_IMAGEREDIRECT, &CMy19进程管理器Dlg::OnBnClickedCheckImageredirect)
END_MESSAGE_MAP()




void CMy19进程管理器Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy19进程管理器Dlg::OnPaint()
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
HCURSOR CMy19进程管理器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy19进程管理器Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}

// CMy19进程管理器Dlg 消息处理程序

BOOL CMy19进程管理器Dlg::OnInitDialog()
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
	UpgradeProcessPrivilege();
	InitListControl();
	UpdateProcesses();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

/*
进程查询遍历头文件
*/
#include<TlHelp32.h>

void CMy19进程管理器Dlg::InitListControl()
{
	//设置拓展样式，有网格线和选择一整行
	m_list_processes.SetExtendedStyle(m_list_processes.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//插入列
	m_list_processes.InsertColumn(0, TEXT("进    程    名    称    "));
	m_list_processes.InsertColumn(1, TEXT("进程ID"));
	//设置自动列宽
	m_list_processes.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_list_processes.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	//设置拓展样式，有网格线和选择一整行
	m_list_dlls.SetExtendedStyle(m_list_dlls.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//插入列
	m_list_dlls.InsertColumn(0, TEXT("DLL  名  称"));
	m_list_dlls.InsertColumn(1, TEXT("DLL    路    径    "));
	//设置自动列宽
	m_list_dlls.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_list_dlls.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	m_ckbox_image_redirect.SetCheck(0);
}
/*
头文件：
	#include<TlHelp32.h>
枚举进程函数：
	CreateToolhelp32Snapshot(),Process32First(),Process32Next()
枚举线程函数：
	CreateToolhelp32Snapshot(),Thread32First(),Thread32Next()
枚举模块（DLL）函数：
	CreateToolhelp32Snapshot(),Module32First(),Module32Next()

提供给枚举进程，线程等的主要函数，尤其重要，其他函数都要依靠这个函数：
	HANDLE CreateToolhelp32Snapshot(
		DWORD dwFlags,//指明要建立的快照的类型，可有如下值：TH32CS_SNAPPROCESS、TH32CS_SNAPPTHREAD、TH32CS_SNAPMODULE
		DWORD th32ProcessID//如果是枚举系统中的，为0，如果是指定进程中的，就是进程ID
		);
	返回值：返回一个快照句柄，提供给枚举函数使用
获取第一个枚举进程函数：
	BOOL Process32FirstW(
		HANDLE hSnapshot,//CreateToolhelp32Snapshot创建的快照句柄
		LPPROCESSENTRY32 lppe//指向PROCESSENTRY32结构体的指针
		);
		结构体介绍：
			typedef struct tagPROCESSENTRY32W
			{
			DWORD   dwSize;//使用结构体之前，需要赋值，直接sizeof即可
			DWORD   cntUsage;
			DWORD   th32ProcessID;          // 进程ID
			ULONG_PTR th32DefaultHeapID;
			DWORD   th32ModuleID;           // associated exe
			DWORD   cntThreads;
			DWORD   th32ParentProcessID;    // 父进程ID
			LONG    pcPriClassBase;         // Base priority of process's threads
			DWORD   dwFlags;
			TCHAR   szExeFile[MAX_PATH];    // 可执行文件的文件名
			} PROCESSENTRY32;
查找下一个进程函数：
	BOOL Process32NextW(
		HANDLE hSnapshot,//参数同上
		LPPROCESSENTRY32W lppe
		);
枚举线程、模块Dll的结构体，大体一样
	MODULEENTRT32、THREADENTRY32
*/
void CMy19进程管理器Dlg::UpdateProcesses()
{
	//清空列表控件的所有项目
	m_list_processes.DeleteAllItems();
	//创建进程快照
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hsnap == INVALID_HANDLE_VALUE)
	{
		MessageBox(_T("CreateToolhelp32Snapshot Error!!"));
		return;
	}

	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(PROCESSENTRY32);
	//拿到第一个进程
	BOOL ret = Process32First(hsnap, &pe32);
	int index = 0;
	CString str;
	//遍历进程
	while (ret)
	{
		m_list_processes.InsertItem(index, pe32.szExeFile);
		str.Format(_T("%d"),pe32.th32ProcessID);
		m_list_processes.SetItemText(index, 1, str);
		//获取下一个进程
		index++;
		ret = Process32Next(hsnap, &pe32);
	}
	CloseHandle(hsnap);
}


void CMy19进程管理器Dlg::UpdateModules()
{
	m_list_dlls.DeleteAllItems();

	int pid = GetSelectPID();

	if (pid == 0)
		return;

	MODULEENTRY32 me32 = { 0 };
	me32.dwSize = sizeof(MODULEENTRY32);

	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (hsnap == INVALID_HANDLE_VALUE)
	{
		MessageBox(_T("CreateToolhelp32Snapshot Error!!"));
		return;
	}
	//获取第一个模块句柄
	BOOL ret = Module32First(hsnap, &me32);
	int index = 0;
	//遍历所有进程下的模块
	while (ret)
	{
		m_list_dlls.InsertItem(index, me32.szModule);
		m_list_dlls.SetItemText(index, 1, me32.szExePath);
		//获取下一个模块
		index++;
		ret = Module32Next (hsnap, &me32);
	}
	CloseHandle(hsnap);

}
/*
获取已选中的进程列表的选中进程ID
*/
int CMy19进程管理器Dlg::GetSelectPID()
{
	//获取List Control的选中项下标
	int pid = -1;
	POSITION pos = m_list_processes.GetFirstSelectedItemPosition();
	int selectIndex = -1;
	while (pos)
	{
		selectIndex = m_list_processes.GetNextSelectedItem(pos);
	}
	if (selectIndex == -1)
	{
		MessageBox(_T("请先选中一个进程！！"));
		return -1;
	}
	//获取对应下标下的项目的文本
	TCHAR szpid[20] = { 0 };
	m_list_processes.GetItemText(selectIndex, 1,szpid,20);
	pid = _ttoi(szpid);
	return pid;
}


void CMy19进程管理器Dlg::OnBnClickedButtonViewDll()
{
	UpdateModules();
}
/*
进程权限提升，为了解决进程的权限不足，导致一些操作无法执行的问题，但并不是所有的权限都能提升
在使用CreateToolhelp32Snapshot或者OpenProcess打开系统进程的时候会调用失败，
因此需要提升权限至：SeDebugPrivilege
	该权限可以访问一些受限制的系统资源，远程线程注入也会这样使用

权限提升步骤：
	使用OpenProcessToken()函数打开当前进程的访问令牌
	使用LookupPrivilegeValue()函数获取描述前线的LUID
	使用AdjustTokenPrivileges()函数调整访问令牌的权限
*/

void CMy19进程管理器Dlg::UpgradeProcessPrivilege()
{
	//这是一种通用进程权限提升写法
	HANDLE htoken = NULL;
	//打开进程令牌，参数：进程句柄，令牌访问权限，进程令牌保存句柄
	BOOL ret = OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &htoken);
	if (ret == TRUE)
	{
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(htoken, FALSE, &tp, sizeof(tp), NULL, NULL);
		CloseHandle(htoken);
	}
}
/*
进程的暂停实质上是线程的暂停，有些病毒利用双线程互守保证病毒的运行，就不得不暂停其中一个线程，最终实现杀毒
进程是资源分配的单位，线程时真正运行的单位
打开线程函数：
	HANDLE OpenThread(
		DWORD dwDesiredAccess,//想要打开的线程获取的权限，为了方便，一般取THREAD_ALL_ACCESS
		BOOL bInheritHandle,//是否返回的线程句柄是否允许被继承，一般取FALSE
		DWORD dwThreadId//想要打开的线程ID
		);
暂停线程函数：
	DWORD SuspendThread(
		HANDLE hThread//想要暂停的线程句柄
		);
*/

void CMy19进程管理器Dlg::OnBnClickedButtonWaitProcess()
{
	//代码注释见下一个函数注释
	int pid = GetSelectPID();
	if (pid == 0)
		return;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,pid);
	if (hsnap == INVALID_HANDLE_VALUE)
	{
		MessageBox(_T("CreateToolhelp32Snapshot Error!!"));
		return;
	}
	THREADENTRY32 te32 = { 0 };
	te32.dwSize = sizeof(THREADENTRY32);
	BOOL ret = Thread32First(hsnap, &te32);
	while (ret)
	{
		if (te32.th32OwnerProcessID == pid)
		{
			HANDLE hthread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
			SuspendThread(hthread);
			CloseHandle(hthread);
		}
		ret = Thread32Next(hsnap, &te32);
	}
	CloseHandle(hsnap);
}

/*
恢复被暂停的线程函数：
	DWORD ResumeThread(
		HANDLE hThread//想要恢复的线程句柄
		);
*/
void CMy19进程管理器Dlg::OnBnClickedButtonRecoveryProcess()
{
	//获取选中的进程ID，无效ID时返回
	int pid = GetSelectPID();
	if (pid == 0)
		return;
	//创建线程快照
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
	if (hsnap == INVALID_HANDLE_VALUE)
	{
		MessageBox(_T("CreateToolhelp32Snapshot Error!!"));
		return;
	}

	THREADENTRY32 te32 = { 0 };
	te32.dwSize = sizeof(THREADENTRY32);
	BOOL ret = Thread32First(hsnap, &te32);
	//遍历线程快照中的每一项
	while (ret)
	{
		//获取进程中的线程
		if (te32.th32OwnerProcessID == pid)
		{
			//打开线程
			HANDLE hthread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
			//恢复线程
			ResumeThread(hthread);
			CloseHandle(hthread);
		}
		//继续获得下一个线程
		ret = Thread32Next(hsnap, &te32);
	}
	CloseHandle(hsnap);
}
/*
终止进程函数：
	BOOL TerminateProcess(
		HANDLE hProcess,//想要结束的进程句柄
		UINT uExitCode//进程退出码，一般为0
		);
获取进程ID函数：
	DWORD GetWindowThreadProcessId(
		HWND hWnd,//窗口句柄
		LPDWORD lpdwProcessId);//返回的进程ID存放地址
打开进程函数：
		HANDLE OpenProcess(
			DWORD dwDesiredAccess,//打开进程想要获取的权限，为了方便，一般使用PROCESS_ALL_ACCESS
			BOOL bInheritHandle,//获取的进程句柄是否可以被继承，一般不允许继承FALSE
			DWORD dwProcessId//想要打开的进程ID号
			);
进程正常结束时，会调用ExitProcess()函数，
这里使用的就是类似强制结束的方式
*/

void CMy19进程管理器Dlg::OnBnClickedButtonStopProcess()
{
	int pid = GetSelectPID();
	if (pid == 0)
		return;
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (handle == INVALID_HANDLE_VALUE)
	{
		return;
	}
	BOOL ret = TerminateProcess(handle,0);
	CloseHandle(handle);
	if (ret == TRUE)
	{
		CString str;
		str.Format(_T("PID:%d 进程已被停止！"),pid);
		MessageBox(str);
	}
}
/*
简单穿件进程函数：
	UINT WinExec(LPCTSTR lpExecFileName,UINT uCmdShow);
	和ShellExec，不在进行介绍
创建进程函数：
	BOOL CreateProcess(
		LPCTSTR lpApplicationName,//可执行文件的文件名
		LPTSTR lpCommandLine,//新进程的命令行参数
		LPSECURITY_ATTRIBUTES lpProcessAttributes,//进程安全属性，通常为NULL
		LPSECURITY_ATTRIBUTES lpThreadAttributes,//线程安全属性，通常为NULL
		BOOL bInheritHandles,//指定是否允许新进程继承
		DWORD dwCreationFlags,//新进程的优先级和其他创建标志
		LPVOID lpEnvironment,//新进程的环境变量，通常为NULL
		LPCTSTR lpCurrentDirectory,//指定新进程的当前路径
		LPSTARTUPINFO lpStartupInfo,//新进程的启动信息结构体，决定了进程启动状态
		LPPROCESS_INFORMATION lpProcessInformation);//用于返回新进程和主线程的相关信息

		两个结构体的说明如下：
		typedef struct _STARTUPINFOW {
		DWORD   cb;//使用该结构体之前需要对该值进行赋值，保存结构体的大小，一般sizeof计算即可
		LPTSTR  lpReserved;
		LPTSTR  lpDesktop;
		LPTSTR  lpTitle;
		DWORD   dwX;
		DWORD   dwY;
		DWORD   dwXSize;
		DWORD   dwYSize;
		DWORD   dwXCountChars;
		DWORD   dwYCountChars;
		DWORD   dwFillAttribute;
		DWORD   dwFlags;
		WORD    wShowWindow;
		WORD    cbReserved2;
		LPBYTE  lpReserved2;
		HANDLE  hStdInput;//标准输入输出错误的重定向，如果有用到的话
		HANDLE  hStdOutput;
		HANDLE  hStdError;
		} STARTUPINFO;

		typedef struct _PROCESS_INFORMATION {
		HANDLE hProcess;//该结构体保存新创建进程和线程的句柄和ID，使用之后，需要注意关闭句柄
		HANDLE hThread;
		DWORD dwProcessId;
		DWORD dwThreadId;
		} PROCESS_INFORMATION;
*/

void CMy19进程管理器Dlg::OnBnClickedButtonCreateProcess()
{
	//获取界面上的字符串
	UpdateData(TRUE);
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof(STARTUPINFO);
	//创建进程
	BOOL ret = CreateProcess(m_create_process_path,
		NULL, NULL, NULL, FALSE,
		NULL, NULL, NULL, &si, &pi);
	//清除进程路径对话框
	m_create_process_path = _T("");
	UpdateData(FALSE);
	if (ret == FALSE)
		return;
	//需要关闭已经创建的线程和进程句柄
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}


void CMy19进程管理器Dlg::OnBnClickedButtonRefresh()
{
	UpdateProcesses();
}

/*
映像劫持技术简介：
	通过注册表替换系统中的镜像程序，实现镜像劫持
	此处以劫持系统的任务管理器为例：
	系统任务管理器键：
		HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\taskmgr.exe\debugger
	其值设置为替换的程序路径即可
		比如：notepad.exe
	去除映像劫持，只需要删除这个debugger键即可
*/
void CMy19进程管理器Dlg::OnBnClickedCheckImageredirect()
{
	//注册表操作
	//定义父键
	const TCHAR imageTaskMgr[] = { _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\taskmgr.exe") };
	//获取程序自身的路径
	TCHAR selfpath[1024] = { 0 };
	GetModuleFileName(NULL, selfpath, 1024);

	if (IsDlgButtonChecked(IDC_CHECK_IMAGEREDIRECT))
	{
		//写入替换的键值
		HKEY hkey = NULL;
		long ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, imageTaskMgr, 0, KEY_ALL_ACCESS, &hkey);
		if (ret != ERROR_SUCCESS)
		{
			MessageBox(_T("劫持任务管理器映像失败！！"));
			return;
		}

		RegSetValueEx(hkey, _T("debugger"), 0, REG_SZ, (unsigned char *)selfpath, lstrlen(selfpath)*2+1);
		RegCloseKey(hkey);
	}
	else
	{
		//删除已经替换的键值
		HKEY hkey = NULL;
		long ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, imageTaskMgr, 0, KEY_ALL_ACCESS, &hkey);
		if (ret != ERROR_SUCCESS)
		{
			MessageBeep(MB_ICONERROR);
			return;
		}
		RegDeleteValue(hkey, _T("debugger"));
		RegCloseKey(hkey);
	}
}
