
// 19-���̹�����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "19-���̹�����.h"
#include "19-���̹�����Dlg.h"
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


// CMy19���̹�����Dlg �Ի���



CMy19���̹�����Dlg::CMy19���̹�����Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy19���̹�����Dlg::IDD, pParent)
	, m_create_process_path(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy19���̹�����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROCESSES, m_list_processes);
	DDX_Control(pDX, IDC_LIST_DLLS, m_list_dlls);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_CP_FILE, m_create_process_path);
	DDX_Control(pDX, IDC_CHECK_IMAGEREDIRECT, m_ckbox_image_redirect);
}

BEGIN_MESSAGE_MAP(CMy19���̹�����Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy19���̹�����Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_DLL, &CMy19���̹�����Dlg::OnBnClickedButtonViewDll)
	ON_BN_CLICKED(IDC_BUTTON_WAIT_PROCESS, &CMy19���̹�����Dlg::OnBnClickedButtonWaitProcess)
	ON_BN_CLICKED(IDC_BUTTON_RECOVERY_PROCESS, &CMy19���̹�����Dlg::OnBnClickedButtonRecoveryProcess)
	ON_BN_CLICKED(IDC_BUTTON_STOP_PROCESS, &CMy19���̹�����Dlg::OnBnClickedButtonStopProcess)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_PROCESS, &CMy19���̹�����Dlg::OnBnClickedButtonCreateProcess)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CMy19���̹�����Dlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_CHECK_IMAGEREDIRECT, &CMy19���̹�����Dlg::OnBnClickedCheckImageredirect)
END_MESSAGE_MAP()




void CMy19���̹�����Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy19���̹�����Dlg::OnPaint()
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
HCURSOR CMy19���̹�����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy19���̹�����Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}

// CMy19���̹�����Dlg ��Ϣ�������

BOOL CMy19���̹�����Dlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	UpgradeProcessPrivilege();
	InitListControl();
	UpdateProcesses();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

/*
���̲�ѯ����ͷ�ļ�
*/
#include<TlHelp32.h>

void CMy19���̹�����Dlg::InitListControl()
{
	//������չ��ʽ���������ߺ�ѡ��һ����
	m_list_processes.SetExtendedStyle(m_list_processes.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//������
	m_list_processes.InsertColumn(0, TEXT("��    ��    ��    ��    "));
	m_list_processes.InsertColumn(1, TEXT("����ID"));
	//�����Զ��п�
	m_list_processes.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_list_processes.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	//������չ��ʽ���������ߺ�ѡ��һ����
	m_list_dlls.SetExtendedStyle(m_list_dlls.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//������
	m_list_dlls.InsertColumn(0, TEXT("DLL  ��  ��"));
	m_list_dlls.InsertColumn(1, TEXT("DLL    ·    ��    "));
	//�����Զ��п�
	m_list_dlls.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_list_dlls.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	m_ckbox_image_redirect.SetCheck(0);
}
/*
ͷ�ļ���
	#include<TlHelp32.h>
ö�ٽ��̺�����
	CreateToolhelp32Snapshot(),Process32First(),Process32Next()
ö���̺߳�����
	CreateToolhelp32Snapshot(),Thread32First(),Thread32Next()
ö��ģ�飨DLL��������
	CreateToolhelp32Snapshot(),Module32First(),Module32Next()

�ṩ��ö�ٽ��̣��̵߳ȵ���Ҫ������������Ҫ������������Ҫ�������������
	HANDLE CreateToolhelp32Snapshot(
		DWORD dwFlags,//ָ��Ҫ�����Ŀ��յ����ͣ���������ֵ��TH32CS_SNAPPROCESS��TH32CS_SNAPPTHREAD��TH32CS_SNAPMODULE
		DWORD th32ProcessID//�����ö��ϵͳ�еģ�Ϊ0�������ָ�������еģ����ǽ���ID
		);
	����ֵ������һ�����վ�����ṩ��ö�ٺ���ʹ��
��ȡ��һ��ö�ٽ��̺�����
	BOOL Process32FirstW(
		HANDLE hSnapshot,//CreateToolhelp32Snapshot�����Ŀ��վ��
		LPPROCESSENTRY32 lppe//ָ��PROCESSENTRY32�ṹ���ָ��
		);
		�ṹ����ܣ�
			typedef struct tagPROCESSENTRY32W
			{
			DWORD   dwSize;//ʹ�ýṹ��֮ǰ����Ҫ��ֵ��ֱ��sizeof����
			DWORD   cntUsage;
			DWORD   th32ProcessID;          // ����ID
			ULONG_PTR th32DefaultHeapID;
			DWORD   th32ModuleID;           // associated exe
			DWORD   cntThreads;
			DWORD   th32ParentProcessID;    // ������ID
			LONG    pcPriClassBase;         // Base priority of process's threads
			DWORD   dwFlags;
			TCHAR   szExeFile[MAX_PATH];    // ��ִ���ļ����ļ���
			} PROCESSENTRY32;
������һ�����̺�����
	BOOL Process32NextW(
		HANDLE hSnapshot,//����ͬ��
		LPPROCESSENTRY32W lppe
		);
ö���̡߳�ģ��Dll�Ľṹ�壬����һ��
	MODULEENTRT32��THREADENTRY32
*/
void CMy19���̹�����Dlg::UpdateProcesses()
{
	//����б�ؼ���������Ŀ
	m_list_processes.DeleteAllItems();
	//�������̿���
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hsnap == INVALID_HANDLE_VALUE)
	{
		MessageBox(_T("CreateToolhelp32Snapshot Error!!"));
		return;
	}

	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(PROCESSENTRY32);
	//�õ���һ������
	BOOL ret = Process32First(hsnap, &pe32);
	int index = 0;
	CString str;
	//��������
	while (ret)
	{
		m_list_processes.InsertItem(index, pe32.szExeFile);
		str.Format(_T("%d"),pe32.th32ProcessID);
		m_list_processes.SetItemText(index, 1, str);
		//��ȡ��һ������
		index++;
		ret = Process32Next(hsnap, &pe32);
	}
	CloseHandle(hsnap);
}


void CMy19���̹�����Dlg::UpdateModules()
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
	//��ȡ��һ��ģ����
	BOOL ret = Module32First(hsnap, &me32);
	int index = 0;
	//�������н����µ�ģ��
	while (ret)
	{
		m_list_dlls.InsertItem(index, me32.szModule);
		m_list_dlls.SetItemText(index, 1, me32.szExePath);
		//��ȡ��һ��ģ��
		index++;
		ret = Module32Next (hsnap, &me32);
	}
	CloseHandle(hsnap);

}
/*
��ȡ��ѡ�еĽ����б��ѡ�н���ID
*/
int CMy19���̹�����Dlg::GetSelectPID()
{
	//��ȡList Control��ѡ�����±�
	int pid = -1;
	POSITION pos = m_list_processes.GetFirstSelectedItemPosition();
	int selectIndex = -1;
	while (pos)
	{
		selectIndex = m_list_processes.GetNextSelectedItem(pos);
	}
	if (selectIndex == -1)
	{
		MessageBox(_T("����ѡ��һ�����̣���"));
		return -1;
	}
	//��ȡ��Ӧ�±��µ���Ŀ���ı�
	TCHAR szpid[20] = { 0 };
	m_list_processes.GetItemText(selectIndex, 1,szpid,20);
	pid = _ttoi(szpid);
	return pid;
}


void CMy19���̹�����Dlg::OnBnClickedButtonViewDll()
{
	UpdateModules();
}
/*
����Ȩ��������Ϊ�˽�����̵�Ȩ�޲��㣬����һЩ�����޷�ִ�е����⣬�����������е�Ȩ�޶�������
��ʹ��CreateToolhelp32Snapshot����OpenProcess��ϵͳ���̵�ʱ������ʧ�ܣ�
�����Ҫ����Ȩ������SeDebugPrivilege
	��Ȩ�޿��Է���һЩ�����Ƶ�ϵͳ��Դ��Զ���߳�ע��Ҳ������ʹ��

Ȩ���������裺
	ʹ��OpenProcessToken()�����򿪵�ǰ���̵ķ�������
	ʹ��LookupPrivilegeValue()������ȡ����ǰ�ߵ�LUID
	ʹ��AdjustTokenPrivileges()���������������Ƶ�Ȩ��
*/

void CMy19���̹�����Dlg::UpgradeProcessPrivilege()
{
	//����һ��ͨ�ý���Ȩ������д��
	HANDLE htoken = NULL;
	//�򿪽������ƣ����������̾�������Ʒ���Ȩ�ޣ��������Ʊ�����
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
���̵���ͣʵ�������̵߳���ͣ����Щ��������˫�̻߳��ر�֤���������У��Ͳ��ò���ͣ����һ���̣߳�����ʵ��ɱ��
��������Դ����ĵ�λ���߳�ʱ�������еĵ�λ
���̺߳�����
	HANDLE OpenThread(
		DWORD dwDesiredAccess,//��Ҫ�򿪵��̻߳�ȡ��Ȩ�ޣ�Ϊ�˷��㣬һ��ȡTHREAD_ALL_ACCESS
		BOOL bInheritHandle,//�Ƿ񷵻ص��߳̾���Ƿ������̳У�һ��ȡFALSE
		DWORD dwThreadId//��Ҫ�򿪵��߳�ID
		);
��ͣ�̺߳�����
	DWORD SuspendThread(
		HANDLE hThread//��Ҫ��ͣ���߳̾��
		);
*/

void CMy19���̹�����Dlg::OnBnClickedButtonWaitProcess()
{
	//����ע�ͼ���һ������ע��
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
�ָ�����ͣ���̺߳�����
	DWORD ResumeThread(
		HANDLE hThread//��Ҫ�ָ����߳̾��
		);
*/
void CMy19���̹�����Dlg::OnBnClickedButtonRecoveryProcess()
{
	//��ȡѡ�еĽ���ID����ЧIDʱ����
	int pid = GetSelectPID();
	if (pid == 0)
		return;
	//�����߳̿���
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
	if (hsnap == INVALID_HANDLE_VALUE)
	{
		MessageBox(_T("CreateToolhelp32Snapshot Error!!"));
		return;
	}

	THREADENTRY32 te32 = { 0 };
	te32.dwSize = sizeof(THREADENTRY32);
	BOOL ret = Thread32First(hsnap, &te32);
	//�����߳̿����е�ÿһ��
	while (ret)
	{
		//��ȡ�����е��߳�
		if (te32.th32OwnerProcessID == pid)
		{
			//���߳�
			HANDLE hthread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
			//�ָ��߳�
			ResumeThread(hthread);
			CloseHandle(hthread);
		}
		//���������һ���߳�
		ret = Thread32Next(hsnap, &te32);
	}
	CloseHandle(hsnap);
}
/*
��ֹ���̺�����
	BOOL TerminateProcess(
		HANDLE hProcess,//��Ҫ�����Ľ��̾��
		UINT uExitCode//�����˳��룬һ��Ϊ0
		);
��ȡ����ID������
	DWORD GetWindowThreadProcessId(
		HWND hWnd,//���ھ��
		LPDWORD lpdwProcessId);//���صĽ���ID��ŵ�ַ
�򿪽��̺�����
		HANDLE OpenProcess(
			DWORD dwDesiredAccess,//�򿪽�����Ҫ��ȡ��Ȩ�ޣ�Ϊ�˷��㣬һ��ʹ��PROCESS_ALL_ACCESS
			BOOL bInheritHandle,//��ȡ�Ľ��̾���Ƿ���Ա��̳У�һ�㲻����̳�FALSE
			DWORD dwProcessId//��Ҫ�򿪵Ľ���ID��
			);
������������ʱ�������ExitProcess()������
����ʹ�õľ�������ǿ�ƽ����ķ�ʽ
*/

void CMy19���̹�����Dlg::OnBnClickedButtonStopProcess()
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
		str.Format(_T("PID:%d �����ѱ�ֹͣ��"),pid);
		MessageBox(str);
	}
}
/*
�򵥴������̺�����
	UINT WinExec(LPCTSTR lpExecFileName,UINT uCmdShow);
	��ShellExec�����ڽ��н���
�������̺�����
	BOOL CreateProcess(
		LPCTSTR lpApplicationName,//��ִ���ļ����ļ���
		LPTSTR lpCommandLine,//�½��̵������в���
		LPSECURITY_ATTRIBUTES lpProcessAttributes,//���̰�ȫ���ԣ�ͨ��ΪNULL
		LPSECURITY_ATTRIBUTES lpThreadAttributes,//�̰߳�ȫ���ԣ�ͨ��ΪNULL
		BOOL bInheritHandles,//ָ���Ƿ������½��̼̳�
		DWORD dwCreationFlags,//�½��̵����ȼ�������������־
		LPVOID lpEnvironment,//�½��̵Ļ���������ͨ��ΪNULL
		LPCTSTR lpCurrentDirectory,//ָ���½��̵ĵ�ǰ·��
		LPSTARTUPINFO lpStartupInfo,//�½��̵�������Ϣ�ṹ�壬�����˽�������״̬
		LPPROCESS_INFORMATION lpProcessInformation);//���ڷ����½��̺����̵߳������Ϣ

		�����ṹ���˵�����£�
		typedef struct _STARTUPINFOW {
		DWORD   cb;//ʹ�øýṹ��֮ǰ��Ҫ�Ը�ֵ���и�ֵ������ṹ��Ĵ�С��һ��sizeof���㼴��
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
		HANDLE  hStdInput;//��׼�������������ض���������õ��Ļ�
		HANDLE  hStdOutput;
		HANDLE  hStdError;
		} STARTUPINFO;

		typedef struct _PROCESS_INFORMATION {
		HANDLE hProcess;//�ýṹ�屣���´������̺��̵߳ľ����ID��ʹ��֮����Ҫע��رվ��
		HANDLE hThread;
		DWORD dwProcessId;
		DWORD dwThreadId;
		} PROCESS_INFORMATION;
*/

void CMy19���̹�����Dlg::OnBnClickedButtonCreateProcess()
{
	//��ȡ�����ϵ��ַ���
	UpdateData(TRUE);
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof(STARTUPINFO);
	//��������
	BOOL ret = CreateProcess(m_create_process_path,
		NULL, NULL, NULL, FALSE,
		NULL, NULL, NULL, &si, &pi);
	//�������·���Ի���
	m_create_process_path = _T("");
	UpdateData(FALSE);
	if (ret == FALSE)
		return;
	//��Ҫ�ر��Ѿ��������̺߳ͽ��̾��
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}


void CMy19���̹�����Dlg::OnBnClickedButtonRefresh()
{
	UpdateProcesses();
}

/*
ӳ��ٳּ�����飺
	ͨ��ע����滻ϵͳ�еľ������ʵ�־���ٳ�
	�˴��Խٳ�ϵͳ�����������Ϊ����
	ϵͳ�������������
		HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\taskmgr.exe\debugger
	��ֵ����Ϊ�滻�ĳ���·������
		���磺notepad.exe
	ȥ��ӳ��ٳ֣�ֻ��Ҫɾ�����debugger������
*/
void CMy19���̹�����Dlg::OnBnClickedCheckImageredirect()
{
	//ע������
	//���常��
	const TCHAR imageTaskMgr[] = { _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\taskmgr.exe") };
	//��ȡ���������·��
	TCHAR selfpath[1024] = { 0 };
	GetModuleFileName(NULL, selfpath, 1024);

	if (IsDlgButtonChecked(IDC_CHECK_IMAGEREDIRECT))
	{
		//д���滻�ļ�ֵ
		HKEY hkey = NULL;
		long ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, imageTaskMgr, 0, KEY_ALL_ACCESS, &hkey);
		if (ret != ERROR_SUCCESS)
		{
			MessageBox(_T("�ٳ����������ӳ��ʧ�ܣ���"));
			return;
		}

		RegSetValueEx(hkey, _T("debugger"), 0, REG_SZ, (unsigned char *)selfpath, lstrlen(selfpath)*2+1);
		RegCloseKey(hkey);
	}
	else
	{
		//ɾ���Ѿ��滻�ļ�ֵ
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
