
// 23-无DLL的代码注入Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "23-无DLL的代码注入.h"
#include "23-无DLL的代码注入Dlg.h"
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


// CMy23无DLL的代码注入Dlg 对话框



CMy23无DLL的代码注入Dlg::CMy23无DLL的代码注入Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy23无DLL的代码注入Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy23无DLL的代码注入Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy23无DLL的代码注入Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy23无DLL的代码注入Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_INJECT, &CMy23无DLL的代码注入Dlg::OnBnClickedButtonInject)
END_MESSAGE_MAP()


// CMy23无DLL的代码注入Dlg 消息处理程序

BOOL CMy23无DLL的代码注入Dlg::OnInitDialog()
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

void CMy23无DLL的代码注入Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy23无DLL的代码注入Dlg::OnPaint()
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
HCURSOR CMy23无DLL的代码注入Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy23无DLL的代码注入Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}
/*
虽然可以使用DLL注入方式，通过DLLMain执行很多的事情，但是也可以不用DLL就能够实现代码注入
虽然kernel32.dll在每个进程中的地址是相同的，但是不代表其他DLL的地址也是相同的，
因此就需要在其他进程中使用LoadLibrary和GetProcAddress函数，这就需要使用结构体将他们传给远程线程以使用
这里使用远程线程弹出一个消息框即可

*/
#include<TlHelp32.h>

void CMy23无DLL的代码注入Dlg::OnBnClickedButtonInject()
{
	TCHAR szProcessName[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_EDIT_PROCESS_NAME, szProcessName, MAX_PATH);
	DWORD dwpid = getProcessID(szProcessName);
	InjectCode(dwpid);

}


DWORD CMy23无DLL的代码注入Dlg::getProcessID(TCHAR * szProcessName)
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
/*
函数调用参数的结构体，
包含要使用的函数的地址和目标DLL的调用相关信息
*/
#define M_STRLEN 20
typedef struct _INJECT_DATA
{
	DWORD dwLoadLibrary;
	DWORD dwGetProcAddress;
	DWORD dwGetModuleHandle;
	DWORD dwGetModuleFileName;

	TCHAR User32Dll[M_STRLEN];
	char messageBox[M_STRLEN];
	TCHAR Str[M_STRLEN];
}INJECT_DATA, *PINJECT_DATA;
extern "C" DWORD  WINAPI RemoteThreadProc(LPVOID lpParam);
DWORD  WINAPI RemoteThreadProc(LPVOID lpParam)
{
	//类型强转
	PINJECT_DATA pdata = (PINJECT_DATA)lpParam;
	//定义调用函数原型
	HMODULE(__stdcall * myLoadLibrary)(LPCWSTR);
	FARPROC(__stdcall * myGetProcessAddress)(HMODULE, LPCSTR);
	HMODULE(__stdcall * myGetModuleHandle)(LPCWSTR);
	DWORD(__stdcall * myGetModuleFileName)(HMODULE, LPWSTR, DWORD);
	int(__stdcall * myMessageBox)(HWND, LPCWSTR, LPCWSTR,UINT);
	//赋值转换调用函数地址
	myLoadLibrary = (HMODULE(__stdcall * )(LPCWSTR)) pdata->dwLoadLibrary;
	myGetProcessAddress = (FARPROC(__stdcall *)(HMODULE, LPCSTR))pdata->dwGetProcAddress;
	myGetModuleHandle = (HMODULE(__stdcall * )(LPCWSTR))pdata->dwGetModuleHandle;
	myGetModuleFileName = (DWORD(__stdcall * )(HMODULE, LPWSTR, DWORD))pdata->dwGetModuleFileName;
	//加载User32.dll，并获取里面的消息框函数地址
	HMODULE hmodule = myLoadLibrary(pdata->User32Dll);
	myMessageBox = (int(__stdcall *)(HWND, LPCWSTR, LPCWSTR, UINT))myGetProcessAddress(hmodule, pdata->messageBox);
	if (!myMessageBox)
	{
		DWORD err = GetLastError();
		return 0;
	}
	//获取调用模块的进程名
	TCHAR szModuleFileName[MAX_PATH] = { 0 };
	myGetModuleFileName(NULL, szModuleFileName, MAX_PATH);
	//弹出消息对话框
	myMessageBox(NULL,pdata->Str,szModuleFileName,MB_OK);
	return 0;
}

void CMy23无DLL的代码注入Dlg::InjectCode(DWORD dwpid)
{

	//打开目标进程
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwpid);
	if (!hprocess)
		return;
	//填充结构体函数地址
	INJECT_DATA data = { 0 }; 
	HMODULE hmod = GetModuleHandle(_T("kernel32.dll"));
	data.dwLoadLibrary = (DWORD)GetProcAddress(hmod, "LoadLibraryW");
	data.dwGetProcAddress = (DWORD)GetProcAddress(hmod, "GetProcAddress");
	data.dwGetModuleHandle = (DWORD)GetProcAddress(hmod, "GetModuleHandleW");
	data.dwGetModuleFileName = (DWORD)GetProcAddress(hmod, "GetModuleFileNameW");
	//填充调用信息
	lstrcpy(data.User32Dll, _T("user32.dll"));
	strcpy(data.messageBox, "MessageBoxW");
	lstrcpy(data.Str, _T("Inject Code!!")); 
	
	//将结构体内容写入目标进程
	LPVOID lpData = VirtualAllocEx(hprocess, NULL, sizeof(data), MEM_COMMIT|MEM_RESERVE , PAGE_READWRITE);
	if (!lpData)
	{
		DWORD err = GetLastError();
		return;
	}
	DWORD dwWritedSize = 0;
	WriteProcessMemory(hprocess, lpData, &data, sizeof(data), &dwWritedSize);
	//将调用函数写入目标进程
	DWORD dwFuncSize = 0x4000;
	LPVOID lpCode = VirtualAllocEx(hprocess, NULL, dwFuncSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(hprocess, lpCode, &RemoteThreadProc, dwFuncSize, &dwWritedSize);
	//启动远程线程并等待结束
	HANDLE hThread = CreateRemoteThread(hprocess, NULL, 0,
		(LPTHREAD_START_ROUTINE)lpCode,
		lpData, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	//释放相关句柄
	CloseHandle(hThread);
	CloseHandle(hprocess);
	MessageBox(_T("注入完成！！"));
}
