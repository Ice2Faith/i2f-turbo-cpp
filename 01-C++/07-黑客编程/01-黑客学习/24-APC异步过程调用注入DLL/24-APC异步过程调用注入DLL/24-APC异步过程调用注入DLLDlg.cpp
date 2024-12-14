
// 24-APC异步过程调用注入DLLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "24-APC异步过程调用注入DLL.h"
#include "24-APC异步过程调用注入DLLDlg.h"
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


// CMy24APC异步过程调用注入DLLDlg 对话框



CMy24APC异步过程调用注入DLLDlg::CMy24APC异步过程调用注入DLLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy24APC异步过程调用注入DLLDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy24APC异步过程调用注入DLLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy24APC异步过程调用注入DLLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy24APC异步过程调用注入DLLDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_INJECT, &CMy24APC异步过程调用注入DLLDlg::OnBnClickedButtonInject)
END_MESSAGE_MAP()


// CMy24APC异步过程调用注入DLLDlg 消息处理程序

BOOL CMy24APC异步过程调用注入DLLDlg::OnInitDialog()
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

void CMy24APC异步过程调用注入DLLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy24APC异步过程调用注入DLLDlg::OnPaint()
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
HCURSOR CMy24APC异步过程调用注入DLLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy24APC异步过程调用注入DLLDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}
/*
APC是异步过程调用，
在Windows中，每个线程在可被唤醒时，在其APC链中的函数将有机会被执行，每个线程都有一个APC链，那么只要在APC中添加一个APC，就可以完成DLL注入

APC注入大致流程：
	将目标DLL的名称写入目标进程内存空间
	获得LoadLibraryA或者LoadLibraryW的地址
	枚举目标进程中的所有线程，给每个线程添加一个APC函数（增加被运行的可能，因为某些线程可能不会被调用）

关键函数介绍：

在APC链中添加一个APC函数：
	DWORD QueueUserAPC(
		PAPCFUNC pfnAPC,//指向一个APC函数的地址
		HANDLE hThread,//目标线程的句柄
		ULONG_PTR dwData//传递给指向APC函数的参数,可以是指针
		);
	相比较CreateRemoteThread()简单了不少
	APC函数原型（同样也因为这个原型和LoadLibrary有着相似的结构）：
	VOID CALLBACK APCProc(ULONG_PTR dwParam);
*/
#include<TlHelp32.h>
void CMy24APC异步过程调用注入DLLDlg::OnBnClickedButtonInject()
{
	//获取输入信息
	char szDllName[MAX_PATH] = { 0 };
	TCHAR szProcessName[MAX_PATH] = { 0 };
	GetDlgItemTextA(this->GetSafeHwnd(), IDC_EDIT_DLL_NAME, szDllName, MAX_PATH);
	GetDlgItemText(IDC_EDIT_PROCESS_NAME, szProcessName, MAX_PATH);
	//获取进程ID并进行DLL注入
	DWORD dwpid = GetProcessId(szProcessName);
	InjectDLL(dwpid, szDllName);
}


DWORD CMy24APC异步过程调用注入DLLDlg::GetProcessId(TCHAR * szProcessName)
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
		ret = Process32Next(hsnap, &pe32);
	}
	CloseHandle(hsnap);
	return 0;
}


void CMy24APC异步过程调用注入DLLDlg::InjectDLL(DWORD dwpid, char * szDllName)
{
	if (dwpid == 0 || strlen(szDllName) == 0)
		return;
	//计算DLL文件名长度
	int dllLen = strlen(szDllName)+sizeof(char);
	//打开进程
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwpid);
	if (!hprocess)
		return;
	//申请目标进程内存
	PVOID pDllAddr = VirtualAllocEx(hprocess, NULL, dllLen, MEM_COMMIT, PAGE_READWRITE);
	if (!pDllAddr)
	{
		CloseHandle(hprocess);
		return;
	}
	//存放DLL名称进目标进程内存
	DWORD dwWritedSize=0;
	WriteProcessMemory(hprocess, pDllAddr, szDllName, dllLen, &dwWritedSize);
	//关闭进程句柄
	CloseHandle(hprocess);
	//得到线程快照
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,0);
	if (hsnap == INVALID_HANDLE_VALUE)
		return;
	//获取加载库函数地址
	char * pFuncName = "LoadLibraryA";
	FARPROC pFuncAddr = GetProcAddress(GetModuleHandle(_T("kernel32.dll")), pFuncName);
	//遍历系统线程
	THREADENTRY32 te32;
	te32.dwSize = sizeof(THREADENTRY32);
	DWORD ret = 0;
	if (Thread32First(hsnap, &te32))
	{
		do
		{
			//找到目标线程
			if (te32.th32OwnerProcessID == dwpid)
			{
				//打开线程
				HANDLE hthread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
				if (hthread)
				{
					//向线程中插入APC异步过程调用
					ret = QueueUserAPC((PAPCFUNC)pFuncAddr, hthread, (ULONG_PTR)pDllAddr);
					CloseHandle(hthread);
				}
			}
		} while (Thread32Next(hsnap,&te32));
	}
	CloseHandle(hsnap);
	MessageBox(_T("APC注入完成！！"));
}
