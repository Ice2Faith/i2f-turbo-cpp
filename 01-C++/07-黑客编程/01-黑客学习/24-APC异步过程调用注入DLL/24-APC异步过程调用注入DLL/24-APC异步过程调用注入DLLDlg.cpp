
// 24-APC�첽���̵���ע��DLLDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "24-APC�첽���̵���ע��DLL.h"
#include "24-APC�첽���̵���ע��DLLDlg.h"
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


// CMy24APC�첽���̵���ע��DLLDlg �Ի���



CMy24APC�첽���̵���ע��DLLDlg::CMy24APC�첽���̵���ע��DLLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy24APC�첽���̵���ע��DLLDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy24APC�첽���̵���ע��DLLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy24APC�첽���̵���ע��DLLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy24APC�첽���̵���ע��DLLDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_INJECT, &CMy24APC�첽���̵���ע��DLLDlg::OnBnClickedButtonInject)
END_MESSAGE_MAP()


// CMy24APC�첽���̵���ע��DLLDlg ��Ϣ�������

BOOL CMy24APC�첽���̵���ע��DLLDlg::OnInitDialog()
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

void CMy24APC�첽���̵���ע��DLLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy24APC�첽���̵���ע��DLLDlg::OnPaint()
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
HCURSOR CMy24APC�첽���̵���ע��DLLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy24APC�첽���̵���ע��DLLDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
/*
APC���첽���̵��ã�
��Windows�У�ÿ���߳��ڿɱ�����ʱ������APC���еĺ������л��ᱻִ�У�ÿ���̶߳���һ��APC������ôֻҪ��APC�����һ��APC���Ϳ������DLLע��

APCע��������̣�
	��Ŀ��DLL������д��Ŀ������ڴ�ռ�
	���LoadLibraryA����LoadLibraryW�ĵ�ַ
	ö��Ŀ������е������̣߳���ÿ���߳����һ��APC���������ӱ����еĿ��ܣ���ΪĳЩ�߳̿��ܲ��ᱻ���ã�

�ؼ��������ܣ�

��APC�������һ��APC������
	DWORD QueueUserAPC(
		PAPCFUNC pfnAPC,//ָ��һ��APC�����ĵ�ַ
		HANDLE hThread,//Ŀ���̵߳ľ��
		ULONG_PTR dwData//���ݸ�ָ��APC�����Ĳ���,������ָ��
		);
	��Ƚ�CreateRemoteThread()���˲���
	APC����ԭ�ͣ�ͬ��Ҳ��Ϊ���ԭ�ͺ�LoadLibrary�������ƵĽṹ����
	VOID CALLBACK APCProc(ULONG_PTR dwParam);
*/
#include<TlHelp32.h>
void CMy24APC�첽���̵���ע��DLLDlg::OnBnClickedButtonInject()
{
	//��ȡ������Ϣ
	char szDllName[MAX_PATH] = { 0 };
	TCHAR szProcessName[MAX_PATH] = { 0 };
	GetDlgItemTextA(this->GetSafeHwnd(), IDC_EDIT_DLL_NAME, szDllName, MAX_PATH);
	GetDlgItemText(IDC_EDIT_PROCESS_NAME, szProcessName, MAX_PATH);
	//��ȡ����ID������DLLע��
	DWORD dwpid = GetProcessId(szProcessName);
	InjectDLL(dwpid, szDllName);
}


DWORD CMy24APC�첽���̵���ע��DLLDlg::GetProcessId(TCHAR * szProcessName)
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


void CMy24APC�첽���̵���ע��DLLDlg::InjectDLL(DWORD dwpid, char * szDllName)
{
	if (dwpid == 0 || strlen(szDllName) == 0)
		return;
	//����DLL�ļ�������
	int dllLen = strlen(szDllName)+sizeof(char);
	//�򿪽���
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwpid);
	if (!hprocess)
		return;
	//����Ŀ������ڴ�
	PVOID pDllAddr = VirtualAllocEx(hprocess, NULL, dllLen, MEM_COMMIT, PAGE_READWRITE);
	if (!pDllAddr)
	{
		CloseHandle(hprocess);
		return;
	}
	//���DLL���ƽ�Ŀ������ڴ�
	DWORD dwWritedSize=0;
	WriteProcessMemory(hprocess, pDllAddr, szDllName, dllLen, &dwWritedSize);
	//�رս��̾��
	CloseHandle(hprocess);
	//�õ��߳̿���
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,0);
	if (hsnap == INVALID_HANDLE_VALUE)
		return;
	//��ȡ���ؿ⺯����ַ
	char * pFuncName = "LoadLibraryA";
	FARPROC pFuncAddr = GetProcAddress(GetModuleHandle(_T("kernel32.dll")), pFuncName);
	//����ϵͳ�߳�
	THREADENTRY32 te32;
	te32.dwSize = sizeof(THREADENTRY32);
	DWORD ret = 0;
	if (Thread32First(hsnap, &te32))
	{
		do
		{
			//�ҵ�Ŀ���߳�
			if (te32.th32OwnerProcessID == dwpid)
			{
				//���߳�
				HANDLE hthread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
				if (hthread)
				{
					//���߳��в���APC�첽���̵���
					ret = QueueUserAPC((PAPCFUNC)pFuncAddr, hthread, (ULONG_PTR)pDllAddr);
					CloseHandle(hthread);
				}
			}
		} while (Thread32Next(hsnap,&te32));
	}
	CloseHandle(hsnap);
	MessageBox(_T("APCע����ɣ���"));
}
