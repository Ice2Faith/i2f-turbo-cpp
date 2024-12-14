
// 22-DLL远程注入与卸载Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "22-DLL远程注入与卸载.h"
#include "22-DLL远程注入与卸载Dlg.h"
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


// CMy22DLL远程注入与卸载Dlg 对话框



CMy22DLL远程注入与卸载Dlg::CMy22DLL远程注入与卸载Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy22DLL远程注入与卸载Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy22DLL远程注入与卸载Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy22DLL远程注入与卸载Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy22DLL远程注入与卸载Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ENTERDLL, &CMy22DLL远程注入与卸载Dlg::OnBnClickedButtonEnterdll)
	ON_BN_CLICKED(IDC_BUTTON_LEAVEDLL, &CMy22DLL远程注入与卸载Dlg::OnBnClickedButtonLeavedll)
END_MESSAGE_MAP()


// CMy22DLL远程注入与卸载Dlg 消息处理程序

BOOL CMy22DLL远程注入与卸载Dlg::OnInitDialog()
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
	//这是一种通用进程权限提升写法
	HANDLE htoken = NULL;
	//打开进程令牌，参数：进程句柄，令牌访问权限，进程令牌保存句柄
	BOOL pret = OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &htoken);
	if (pret == TRUE)
	{
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(htoken, FALSE, &tp, sizeof(tp), NULL, NULL);
		CloseHandle(htoken);
	}
	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy22DLL远程注入与卸载Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy22DLL远程注入与卸载Dlg::OnPaint()
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
HCURSOR CMy22DLL远程注入与卸载Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy22DLL远程注入与卸载Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}
/*
注意理解这里远程的含义，不是主机与主机之间，而是指进程与进程之间。

病毒可以利用DLL文件不能够独立运行的特点，编写为DLL，从而病毒就不会自己运行而创建进程，达到一定程度的免杀效果，
但是为了让DLL文件能够执行，就需要加载DLL文件到内存空间，因此就要借助远程线程实现DLL文件注入

创建远程线程函数：
	HANDLE CreateRemoteThread(//参数和CreateThread函数一样，只是多了第一个目标进程句柄参数，
		HANDLE hProcess,
		LPSECURITY_ATTRIBUTES lpThreadAttributes,
		SIZE_T dwStackSize,
		LPTHREAD_START_ROUTINE lpStartAddress,
		LPVOID lpParameter,
		DWORD dwCreationFlags,
		LPDWORD lpThreadId
		);
		实际上CreateThread就是借助CreateRemoteThread来实现的，将第一个参数值赋值为NtCurrentProcess()，就完成了实现
由于进程之间的内存是独立的，因此新创建的进程函数和函数需要的参数也应该在目标进程之中，这样才能完成调用

对比函数：
	HMODULE LoadLibrary(LPCTSTR lpFileName);
	DWORD WINAPI ThreadProc(LPVOID lpParam);
	可以看出，函数格式相同，调用方式相同（都是stdcall）,参数个数相同，因此将LoadLibrary作为创建线程的函数地址是可行的。

	第一步：需要将LoadLibrary函数的地址放到目标进程空间，该函数来自于系统库kernel32.dll中，而且这个DLL在任何进程中的地址都是相同的，
	因此只要在目标进程中获得了这个地址即可

	第二部：加载库文件，需要库文件的文件名称，怎么把文件名称放入目标进程，就需要下面函数的帮助了。

在目标进程中进行写内存函数：
	BOOL WriteProcessMemory(//在目标进程中的lpBaseAddress地址处写入长度为nSize的内容lpBuffer
		HANDLE hProcess,//目标进程句柄
		LPVOID lpBaseAddress,//写入的目标进程的地址
		LPCVOID lpBuffer,//写入的数据来源
		SIZE_T nSize,//写入的数据大小
		SIZE_T * lpNumberOfBytesWritten//用于接收实际写入的数据大小
		);

但是，往目标进程的那个地址写入，一般来说目标进程不会有这样一块内存区域提供写入，因此需要在目标进程中申请一块内存

在目标进程中申请内申请内存函数：
	LPVOID VirtualAllocEx(
		HANDLE hProcess,//目标进程句柄
		LPVOID lpAddress,//指定目标进程中申请内存的起始地址
		SIZE_T dwSize,//指定在目标进程中申请内存的大小
		DWORD flAllocationType,//指定申请内存的状态类型
		DWORD flProtect//指定申请内存的属性
		);
	返回值：在目标进程申请的内存的地址

注入DLL之后需要卸载

卸载库函数：
	BOOL FreeLibrary(
		HMODULE hLibModule//要释放的库句柄
		);

库实体结构体：
typedef struct tagMODULEENTRY32W
{
DWORD   dwSize;
DWORD   th32ModuleID;       // This module
DWORD   th32ProcessID;      // owning process
DWORD   GlblcntUsage;       // Global usage count on the module
DWORD   ProccntUsage;       // Module usage count in th32ProcessID's context
BYTE  * modBaseAddr;        // Base address of module in th32ProcessID's context
DWORD   modBaseSize;        // Size in bytes of module starting at modBaseAddr
HMODULE hModule;            // The hModule of this module in th32ProcessID's context
TCHAR   szModule[MAX_MODULE_NAME32 + 1];//模块名称
TCHAR   szExePath[MAX_PATH];//完整模块路径
} MODULEENTRY32W;
*/
#include<TlHelp32.h>

void CMy22DLL远程注入与卸载Dlg::OnBnClickedButtonEnterdll()
{
	//获取输入信息
	char szDllName[MAX_PATH] = { 0 };
	TCHAR szProcessName[MAX_PATH] = { 0 };
	GetDlgItemTextA(this->GetSafeHwnd(),IDC_EDIT_DLLNAME, szDllName, MAX_PATH);
	GetDlgItemText(IDC_EDIT_PROCESSNAME,szProcessName,MAX_PATH);
	//获取进程ID并进行DLL注入
	DWORD dwpid = GetProcessId(szProcessName);
	InjectDLL(dwpid, szDllName);

}


void CMy22DLL远程注入与卸载Dlg::OnBnClickedButtonLeavedll()
{
	//获取输入信息
	TCHAR szDllName[MAX_PATH] = { 0 };
	TCHAR szProcessName[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_EDIT_DLLNAME, szDllName, MAX_PATH);
	GetDlgItemText(IDC_EDIT_PROCESSNAME, szProcessName, MAX_PATH);
	//获取进程ID并进行卸载DLL注入
	DWORD dwpid = GetProcessId(szProcessName);
	UnInjectDll(dwpid, szDllName);
}


DWORD CMy22DLL远程注入与卸载Dlg::GetProcessId(TCHAR * szProcessName)
{
	//打开进程快照
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	//遍历匹配进程名称是否相等
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	BOOL ret = Process32First(hsnap, &pe32);
	while (ret)
	{
		if (lstrcmp(_wcsupr(pe32.szExeFile), _wcsupr(szProcessName)) == 0)
		{
			CloseHandle(hsnap);
			return pe32.th32ProcessID;
		}
		ret = Process32Next(hsnap,&pe32);
	}
	CloseHandle(hsnap);
	return 0;
}

VOID CMy22DLL远程注入与卸载Dlg::InjectDLL(DWORD dwpid, char * szDllName)
{
	//DLL注入对于系统操作时需要进行权限提升，Win8以上版本需要管理员运行
	if (dwpid == 0 || strlen(szDllName) == 0)
	{
		return;
	}
	//打开目标进程
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,dwpid);
	if (!hprocess)
		return;
	//计算并申请要注入的DLL完整路径长度
	int dllLen = strlen(szDllName) + sizeof(char);
	PVOID pDllAddr = VirtualAllocEx(hprocess, NULL, dllLen, MEM_COMMIT, PAGE_READWRITE);
	if (!pDllAddr)
	{
		CloseHandle(hprocess);
		return;
	}
	//将DLL文件路径写入目标内存空间
	DWORD dwWriteNum = 0;
	BOOL ret=WriteProcessMemory(hprocess, pDllAddr, szDllName, dllLen, &dwWriteNum);
	//获取LoadLibraryA的地址，库里面没有LoadLibrary，只有对应的ASCII版本和UNICODE版本
	char * pFuncName = "LoadLibraryA";
	FARPROC pFunAddr = GetProcAddress(GetModuleHandle(_T("kernel32.dll")), pFuncName);
	//创建远程线程（其实创建线程的底层就是通过创建远程线程实现的）
	HANDLE hThread = CreateRemoteThread(hprocess,
		NULL, 0,
		(LPTHREAD_START_ROUTINE)pFunAddr,
		pDllAddr, 0, NULL);
	if (!hThread)
	{
		return;
	}
		
	//等待线程结束并关闭相关句柄
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hprocess);
	MessageBox(_T("注入成功"));
}


void CMy22DLL远程注入与卸载Dlg::UnInjectDll(DWORD dwpid, TCHAR * szDLLName)
{
	if (dwpid == 0 || lstrlen(szDLLName) == 0)
	{
		return;
	}
	//查找目标进程，包含使用了目标DLL的进程
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwpid);
	MODULEENTRY32 me32;
	me32.dwSize = sizeof(MODULEENTRY32);
	BOOL ret = Module32First(hsnap, &me32);
	while (ret)
	{
		if (lstrcmp(_wcsupr(me32.szExePath), _wcsupr(szDLLName)) == 0)
		{
			break;
		}
		ret = Module32Next(hsnap,&me32);
	}
	CloseHandle(hsnap);
	//打开进程
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwpid);
	if (!hprocess)
		return;
	//获得释放DLL库的函数地址
	char * pFuncName = "FreeLibrary";
	FARPROC pFuncAddr = GetProcAddress(GetModuleHandle(_T("kernel32.dll")), pFuncName);
	//创建远程线程释放DLL库，等待完成并释放句柄
	HANDLE hThread = CreateRemoteThread(hprocess,
		NULL, 0,
		(LPTHREAD_START_ROUTINE)pFuncAddr,
		me32.hModule, 0, NULL);
	if (!hThread)
		return;
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hprocess);
	MessageBox(_T("卸载成功"));
}
