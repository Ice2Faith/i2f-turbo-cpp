
// 23-��DLL�Ĵ���ע��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "23-��DLL�Ĵ���ע��.h"
#include "23-��DLL�Ĵ���ע��Dlg.h"
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


// CMy23��DLL�Ĵ���ע��Dlg �Ի���



CMy23��DLL�Ĵ���ע��Dlg::CMy23��DLL�Ĵ���ע��Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy23��DLL�Ĵ���ע��Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy23��DLL�Ĵ���ע��Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy23��DLL�Ĵ���ע��Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy23��DLL�Ĵ���ע��Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_INJECT, &CMy23��DLL�Ĵ���ע��Dlg::OnBnClickedButtonInject)
END_MESSAGE_MAP()


// CMy23��DLL�Ĵ���ע��Dlg ��Ϣ�������

BOOL CMy23��DLL�Ĵ���ע��Dlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy23��DLL�Ĵ���ע��Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy23��DLL�Ĵ���ע��Dlg::OnPaint()
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
HCURSOR CMy23��DLL�Ĵ���ע��Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy23��DLL�Ĵ���ע��Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
/*
��Ȼ����ʹ��DLLע�뷽ʽ��ͨ��DLLMainִ�кܶ�����飬����Ҳ���Բ���DLL���ܹ�ʵ�ִ���ע��
��Ȼkernel32.dll��ÿ�������еĵ�ַ����ͬ�ģ����ǲ���������DLL�ĵ�ַҲ����ͬ�ģ�
��˾���Ҫ������������ʹ��LoadLibrary��GetProcAddress�����������Ҫʹ�ýṹ�彫���Ǵ���Զ���߳���ʹ��
����ʹ��Զ���̵߳���һ����Ϣ�򼴿�

*/
#include<TlHelp32.h>

void CMy23��DLL�Ĵ���ע��Dlg::OnBnClickedButtonInject()
{
	TCHAR szProcessName[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_EDIT_PROCESS_NAME, szProcessName, MAX_PATH);
	DWORD dwpid = getProcessID(szProcessName);
	InjectCode(dwpid);

}


DWORD CMy23��DLL�Ĵ���ע��Dlg::getProcessID(TCHAR * szProcessName)
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
		ret = Process32Next(hsnap, &pe32);
	}
	CloseHandle(hsnap);
	return 0;
}
/*
�������ò����Ľṹ�壬
����Ҫʹ�õĺ����ĵ�ַ��Ŀ��DLL�ĵ��������Ϣ
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
	//����ǿת
	PINJECT_DATA pdata = (PINJECT_DATA)lpParam;
	//������ú���ԭ��
	HMODULE(__stdcall * myLoadLibrary)(LPCWSTR);
	FARPROC(__stdcall * myGetProcessAddress)(HMODULE, LPCSTR);
	HMODULE(__stdcall * myGetModuleHandle)(LPCWSTR);
	DWORD(__stdcall * myGetModuleFileName)(HMODULE, LPWSTR, DWORD);
	int(__stdcall * myMessageBox)(HWND, LPCWSTR, LPCWSTR,UINT);
	//��ֵת�����ú�����ַ
	myLoadLibrary = (HMODULE(__stdcall * )(LPCWSTR)) pdata->dwLoadLibrary;
	myGetProcessAddress = (FARPROC(__stdcall *)(HMODULE, LPCSTR))pdata->dwGetProcAddress;
	myGetModuleHandle = (HMODULE(__stdcall * )(LPCWSTR))pdata->dwGetModuleHandle;
	myGetModuleFileName = (DWORD(__stdcall * )(HMODULE, LPWSTR, DWORD))pdata->dwGetModuleFileName;
	//����User32.dll������ȡ�������Ϣ������ַ
	HMODULE hmodule = myLoadLibrary(pdata->User32Dll);
	myMessageBox = (int(__stdcall *)(HWND, LPCWSTR, LPCWSTR, UINT))myGetProcessAddress(hmodule, pdata->messageBox);
	if (!myMessageBox)
	{
		DWORD err = GetLastError();
		return 0;
	}
	//��ȡ����ģ��Ľ�����
	TCHAR szModuleFileName[MAX_PATH] = { 0 };
	myGetModuleFileName(NULL, szModuleFileName, MAX_PATH);
	//������Ϣ�Ի���
	myMessageBox(NULL,pdata->Str,szModuleFileName,MB_OK);
	return 0;
}

void CMy23��DLL�Ĵ���ע��Dlg::InjectCode(DWORD dwpid)
{

	//��Ŀ�����
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwpid);
	if (!hprocess)
		return;
	//���ṹ�庯����ַ
	INJECT_DATA data = { 0 }; 
	HMODULE hmod = GetModuleHandle(_T("kernel32.dll"));
	data.dwLoadLibrary = (DWORD)GetProcAddress(hmod, "LoadLibraryW");
	data.dwGetProcAddress = (DWORD)GetProcAddress(hmod, "GetProcAddress");
	data.dwGetModuleHandle = (DWORD)GetProcAddress(hmod, "GetModuleHandleW");
	data.dwGetModuleFileName = (DWORD)GetProcAddress(hmod, "GetModuleFileNameW");
	//��������Ϣ
	lstrcpy(data.User32Dll, _T("user32.dll"));
	strcpy(data.messageBox, "MessageBoxW");
	lstrcpy(data.Str, _T("Inject Code!!")); 
	
	//���ṹ������д��Ŀ�����
	LPVOID lpData = VirtualAllocEx(hprocess, NULL, sizeof(data), MEM_COMMIT|MEM_RESERVE , PAGE_READWRITE);
	if (!lpData)
	{
		DWORD err = GetLastError();
		return;
	}
	DWORD dwWritedSize = 0;
	WriteProcessMemory(hprocess, lpData, &data, sizeof(data), &dwWritedSize);
	//�����ú���д��Ŀ�����
	DWORD dwFuncSize = 0x4000;
	LPVOID lpCode = VirtualAllocEx(hprocess, NULL, dwFuncSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(hprocess, lpCode, &RemoteThreadProc, dwFuncSize, &dwWritedSize);
	//����Զ���̲߳��ȴ�����
	HANDLE hThread = CreateRemoteThread(hprocess, NULL, 0,
		(LPTHREAD_START_ROUTINE)lpCode,
		lpData, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	//�ͷ���ؾ��
	CloseHandle(hThread);
	CloseHandle(hprocess);
	MessageBox(_T("ע����ɣ���"));
}
