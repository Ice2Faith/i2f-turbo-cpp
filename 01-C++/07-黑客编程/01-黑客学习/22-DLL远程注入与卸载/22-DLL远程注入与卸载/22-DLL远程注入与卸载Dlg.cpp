
// 22-DLLԶ��ע����ж��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "22-DLLԶ��ע����ж��.h"
#include "22-DLLԶ��ע����ж��Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMy22DLLԶ��ע����ж��Dlg �Ի���



CMy22DLLԶ��ע����ж��Dlg::CMy22DLLԶ��ע����ж��Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy22DLLԶ��ע����ж��Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy22DLLԶ��ע����ж��Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy22DLLԶ��ע����ж��Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy22DLLԶ��ע����ж��Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ENTERDLL, &CMy22DLLԶ��ע����ж��Dlg::OnBnClickedButtonEnterdll)
	ON_BN_CLICKED(IDC_BUTTON_LEAVEDLL, &CMy22DLLԶ��ע����ж��Dlg::OnBnClickedButtonLeavedll)
END_MESSAGE_MAP()


// CMy22DLLԶ��ע����ж��Dlg ��Ϣ�������

BOOL CMy22DLLԶ��ע����ж��Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	//����һ��ͨ�ý���Ȩ������д��
	HANDLE htoken = NULL;
	//�򿪽������ƣ����������̾�������Ʒ���Ȩ�ޣ��������Ʊ�����
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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy22DLLԶ��ע����ж��Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy22DLLԶ��ע����ж��Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy22DLLԶ��ע����ж��Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy22DLLԶ��ע����ж��Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
/*
ע���������Զ�̵ĺ��壬��������������֮�䣬����ָ���������֮�䡣

������������DLL�ļ����ܹ��������е��ص㣬��дΪDLL���Ӷ������Ͳ����Լ����ж��������̣��ﵽһ���̶ȵ���ɱЧ����
����Ϊ����DLL�ļ��ܹ�ִ�У�����Ҫ����DLL�ļ����ڴ�ռ䣬��˾�Ҫ����Զ���߳�ʵ��DLL�ļ�ע��

����Զ���̺߳�����
	HANDLE CreateRemoteThread(//������CreateThread����һ����ֻ�Ƕ��˵�һ��Ŀ����̾��������
		HANDLE hProcess,
		LPSECURITY_ATTRIBUTES lpThreadAttributes,
		SIZE_T dwStackSize,
		LPTHREAD_START_ROUTINE lpStartAddress,
		LPVOID lpParameter,
		DWORD dwCreationFlags,
		LPDWORD lpThreadId
		);
		ʵ����CreateThread���ǽ���CreateRemoteThread��ʵ�ֵģ�����һ������ֵ��ֵΪNtCurrentProcess()���������ʵ��
���ڽ���֮����ڴ��Ƕ����ģ�����´����Ľ��̺����ͺ�����Ҫ�Ĳ���ҲӦ����Ŀ�����֮�У�����������ɵ���

�ԱȺ�����
	HMODULE LoadLibrary(LPCTSTR lpFileName);
	DWORD WINAPI ThreadProc(LPVOID lpParam);
	���Կ�����������ʽ��ͬ�����÷�ʽ��ͬ������stdcall��,����������ͬ����˽�LoadLibrary��Ϊ�����̵߳ĺ�����ַ�ǿ��еġ�

	��һ������Ҫ��LoadLibrary�����ĵ�ַ�ŵ�Ŀ����̿ռ䣬�ú���������ϵͳ��kernel32.dll�У��������DLL���κν����еĵ�ַ������ͬ�ģ�
	���ֻҪ��Ŀ������л���������ַ����

	�ڶ��������ؿ��ļ�����Ҫ���ļ����ļ����ƣ���ô���ļ����Ʒ���Ŀ����̣�����Ҫ���溯���İ����ˡ�

��Ŀ������н���д�ڴ溯����
	BOOL WriteProcessMemory(//��Ŀ������е�lpBaseAddress��ַ��д�볤��ΪnSize������lpBuffer
		HANDLE hProcess,//Ŀ����̾��
		LPVOID lpBaseAddress,//д���Ŀ����̵ĵ�ַ
		LPCVOID lpBuffer,//д���������Դ
		SIZE_T nSize,//д������ݴ�С
		SIZE_T * lpNumberOfBytesWritten//���ڽ���ʵ��д������ݴ�С
		);

���ǣ���Ŀ����̵��Ǹ���ַд�룬һ����˵Ŀ����̲���������һ���ڴ������ṩд�룬�����Ҫ��Ŀ�����������һ���ڴ�

��Ŀ������������������ڴ溯����
	LPVOID VirtualAllocEx(
		HANDLE hProcess,//Ŀ����̾��
		LPVOID lpAddress,//ָ��Ŀ������������ڴ����ʼ��ַ
		SIZE_T dwSize,//ָ����Ŀ������������ڴ�Ĵ�С
		DWORD flAllocationType,//ָ�������ڴ��״̬����
		DWORD flProtect//ָ�������ڴ������
		);
	����ֵ����Ŀ�����������ڴ�ĵ�ַ

ע��DLL֮����Ҫж��

ж�ؿ⺯����
	BOOL FreeLibrary(
		HMODULE hLibModule//Ҫ�ͷŵĿ���
		);

��ʵ��ṹ�壺
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
TCHAR   szModule[MAX_MODULE_NAME32 + 1];//ģ������
TCHAR   szExePath[MAX_PATH];//����ģ��·��
} MODULEENTRY32W;
*/
#include<TlHelp32.h>

void CMy22DLLԶ��ע����ж��Dlg::OnBnClickedButtonEnterdll()
{
	//��ȡ������Ϣ
	char szDllName[MAX_PATH] = { 0 };
	TCHAR szProcessName[MAX_PATH] = { 0 };
	GetDlgItemTextA(this->GetSafeHwnd(),IDC_EDIT_DLLNAME, szDllName, MAX_PATH);
	GetDlgItemText(IDC_EDIT_PROCESSNAME,szProcessName,MAX_PATH);
	//��ȡ����ID������DLLע��
	DWORD dwpid = GetProcessId(szProcessName);
	InjectDLL(dwpid, szDllName);

}


void CMy22DLLԶ��ע����ж��Dlg::OnBnClickedButtonLeavedll()
{
	//��ȡ������Ϣ
	TCHAR szDllName[MAX_PATH] = { 0 };
	TCHAR szProcessName[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_EDIT_DLLNAME, szDllName, MAX_PATH);
	GetDlgItemText(IDC_EDIT_PROCESSNAME, szProcessName, MAX_PATH);
	//��ȡ����ID������ж��DLLע��
	DWORD dwpid = GetProcessId(szProcessName);
	UnInjectDll(dwpid, szDllName);
}


DWORD CMy22DLLԶ��ע����ж��Dlg::GetProcessId(TCHAR * szProcessName)
{
	//�򿪽��̿���
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	//����ƥ����������Ƿ����
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

VOID CMy22DLLԶ��ע����ж��Dlg::InjectDLL(DWORD dwpid, char * szDllName)
{
	//DLLע�����ϵͳ����ʱ��Ҫ����Ȩ��������Win8���ϰ汾��Ҫ����Ա����
	if (dwpid == 0 || strlen(szDllName) == 0)
	{
		return;
	}
	//��Ŀ�����
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,dwpid);
	if (!hprocess)
		return;
	//���㲢����Ҫע���DLL����·������
	int dllLen = strlen(szDllName) + sizeof(char);
	PVOID pDllAddr = VirtualAllocEx(hprocess, NULL, dllLen, MEM_COMMIT, PAGE_READWRITE);
	if (!pDllAddr)
	{
		CloseHandle(hprocess);
		return;
	}
	//��DLL�ļ�·��д��Ŀ���ڴ�ռ�
	DWORD dwWriteNum = 0;
	BOOL ret=WriteProcessMemory(hprocess, pDllAddr, szDllName, dllLen, &dwWriteNum);
	//��ȡLoadLibraryA�ĵ�ַ��������û��LoadLibrary��ֻ�ж�Ӧ��ASCII�汾��UNICODE�汾
	char * pFuncName = "LoadLibraryA";
	FARPROC pFunAddr = GetProcAddress(GetModuleHandle(_T("kernel32.dll")), pFuncName);
	//����Զ���̣߳���ʵ�����̵߳ĵײ����ͨ������Զ���߳�ʵ�ֵģ�
	HANDLE hThread = CreateRemoteThread(hprocess,
		NULL, 0,
		(LPTHREAD_START_ROUTINE)pFunAddr,
		pDllAddr, 0, NULL);
	if (!hThread)
	{
		return;
	}
		
	//�ȴ��߳̽������ر���ؾ��
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hprocess);
	MessageBox(_T("ע��ɹ�"));
}


void CMy22DLLԶ��ע����ж��Dlg::UnInjectDll(DWORD dwpid, TCHAR * szDLLName)
{
	if (dwpid == 0 || lstrlen(szDLLName) == 0)
	{
		return;
	}
	//����Ŀ����̣�����ʹ����Ŀ��DLL�Ľ���
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
	//�򿪽���
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwpid);
	if (!hprocess)
		return;
	//����ͷ�DLL��ĺ�����ַ
	char * pFuncName = "FreeLibrary";
	FARPROC pFuncAddr = GetProcAddress(GetModuleHandle(_T("kernel32.dll")), pFuncName);
	//����Զ���߳��ͷ�DLL�⣬�ȴ���ɲ��ͷž��
	HANDLE hThread = CreateRemoteThread(hprocess,
		NULL, 0,
		(LPTHREAD_START_ROUTINE)pFuncAddr,
		me32.hModule, 0, NULL);
	if (!hThread)
		return;
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hprocess);
	MessageBox(_T("ж�سɹ�"));
}
