
// 26-������װ�س���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "26-������װ�س���.h"
#include "26-������װ�س���Dlg.h"
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


// CMy26������װ�س���Dlg �Ի���



CMy26������װ�س���Dlg::CMy26������װ�س���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy26������װ�س���Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy26������װ�س���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy26������װ�س���Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy26������װ�س���Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_INSTALL, &CMy26������װ�س���Dlg::OnBnClickedButtonInstall)
	ON_BN_CLICKED(IDC_BUTTON_UNINSTALL, &CMy26������װ�س���Dlg::OnBnClickedButtonUninstall)
END_MESSAGE_MAP()


// CMy26������װ�س���Dlg ��Ϣ�������

BOOL CMy26������װ�س���Dlg::OnInitDialog()
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

void CMy26������װ�س���Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy26������װ�س���Dlg::OnPaint()
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
HCURSOR CMy26������װ�س���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy26������װ�س���Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
/*
��������������ֳ����ࣺ
	NTʽ�������򣺲�֧�ּ��弴�ã����ڷ�����Ҫ�ֶ���װ
	WDMʽ��������֧�ּ��弴�õģ���ҪINF�ļ������Զ���װ
*/
#include<winsvc.h>
void CMy26������װ�س���Dlg::OnBnClickedButtonInstall()
{
	//��ȡ���������
	TCHAR szDrivePath[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_MFCEDITBROWSE_DRIVE_NAME,szDrivePath,MAX_PATH);
	if (lstrlen(szDrivePath) == 0)
		return;
	//��ȡ�ļ���
	TCHAR szFileName[MAX_PATH] = { 0 };
	::_tsplitpath(szDrivePath,NULL,NULL,szFileName,NULL);
	//�򿪷��������
	SC_HANDLE hScm;
	hScm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hScm == INVALID_HANDLE_VALUE)
		return;
	//��������
	SC_HANDLE hService;
	hService = CreateService(hScm, szFileName, szFileName,
		SERVICE_ALL_ACCESS,
		SERVICE_KERNEL_DRIVER,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_IGNORE,
		szDrivePath, NULL, NULL,
		NULL, NULL, NULL);
	if (hService == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hScm);
		return;
	}
	//��������
	BOOL ret=StartService(hService, NULL, NULL);
	CloseHandle(hService);
	CloseHandle(hScm);	
	if (ret)
	{
		MessageBox(_T("������װ�ɹ������Ѿ���������"));
	}
}


void CMy26������װ�س���Dlg::OnBnClickedButtonUninstall()
{

	//��ȡ���������
	TCHAR szDrivePath[MAX_PATH] = { 0 };
	GetDlgItemText(IDC_MFCEDITBROWSE_DRIVE_NAME, szDrivePath, MAX_PATH);
	if (lstrlen(szDrivePath) == 0)
		return;
	//��ȡ�ļ���
	TCHAR szFileName[MAX_PATH] = { 0 };
	::_tsplitpath(szDrivePath, NULL, NULL, szFileName, NULL);
	//�򿪷��������
	SC_HANDLE hScm;
	hScm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hScm == INVALID_HANDLE_VALUE)
		return;
	//�򿪷���
	SC_HANDLE hService;
	hService = OpenService(hScm, szFileName, SERVICE_ALL_ACCESS);
	if (hService == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hScm);
		return;
	}
	//ֹͣ����
	SERVICE_STATUS status = { 0 };
	BOOL ret=ControlService(hService, SERVICE_CONTROL_STOP, &status);
	if (ret == false)
	{
		CloseHandle(hService);
		CloseHandle(hScm);
		return;
	}
	//ɾ������
	ret=DeleteService(hService);
	CloseHandle(hService);
	CloseHandle(hScm);
	if (ret)
	{
		MessageBox(_T("������ֹͣ��ж����ϣ���"));
	}
}
