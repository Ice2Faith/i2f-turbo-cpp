
// 04-�Զ�����ϢDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "04-�Զ�����Ϣ.h"
#include "04-�Զ�����ϢDlg.h"
#include "afxdialogex.h"
#include"resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_SELFMSG (WM_USER+0x101)

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


// CMy04�Զ�����ϢDlg �Ի���



CMy04�Զ�����ϢDlg::CMy04�Զ�����ϢDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy04�Զ�����ϢDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy04�Զ�����ϢDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_recvmsg);
}

BEGIN_MESSAGE_MAP(CMy04�Զ�����ϢDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SELFMSG,SelfMsgProc)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy04�Զ�����ϢDlg::OnBnClickedButtonSendSelfMsg)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy04�Զ�����ϢDlg::OnBnClickedButtonSendCopyData)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CMy04�Զ�����ϢDlg ��Ϣ�������

BOOL CMy04�Զ�����ϢDlg::OnInitDialog()
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

void CMy04�Զ�����ϢDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy04�Զ�����ϢDlg::OnPaint()
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
HCURSOR CMy04�Զ�����ϢDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*
�Զ�����Ϣ��ʹ�ã�
	�����ڼ��������ͣ������������ʹ��ݣ����߲��������ݲ������������ڸ����������ʹ���
	1.�����Զ�����Ϣ
		#define WM_SELFMSG (WM_USER+0x101)
	2.�����Ӧ����
		afx_msg LRESULT SelfMsgProc(WPARAM wParam, LPARAM lParam);
	3.�����Ϣӳ�亯��
		ON_MESSAGE(WM_SELFMSG,SelfMsgProc)
	4.ʵ��SelfMsgProc��Ӧ����

ϵͳ���ݿ�����Ϣ��WM_COPYDATA:
	���������ݿ������䣬�������������ͺʹ�С
	��Ϣֻ����SendMessage���ͣ�������PostMessage����
	���Ͳ���ʾ����
		SendMessage(Hwnd targetWnd,WM_COPYDATA,(WPARAM)sendHwnd,(LPARAM)COPYDATASTRUCT * lpdata);
	�ṹ��˵����
		typedef struct tagCOPYDATASTRUCT {
		ULONG_PTR dwData;//�Զ�������ݣ���ʱ�����������Ƕ���Զ�����Ϣ�ȣ�����ʱΪ�գ�0������
		DWORD cbData;//���ݵĴ�С�ֽڣ�������ʶ����ָ��ָ�����ݵĴ�С
		PVOID lpData;//ָ�����ݵ�����ָ��
		} COPYDATASTRUCT, *PCOPYDATASTRUCT;
	���裺
		1.���ͽṹ��
		2.ʵ��WM_COPYDATA����Ϣ��������ͨ������ֱ����Ӽ��ɣ�
*/

LRESULT CMy04�Զ�����ϢDlg::SelfMsgProc(WPARAM wParam, LPARAM lParam)
{
	CString str;
	str.Format(TEXT("%d,%d"), (int)wParam, (int)lParam);
	SetDlgItemText(IDC_EDIT1, str);
	return 0;
}

void CMy04�Զ�����ϢDlg::OnBnClickedButtonSendSelfMsg()
{
	int num1 = GetDlgItemInt(IDC_EDIT2, FALSE, FALSE);
	int num2 = GetDlgItemInt(IDC_EDIT3, FALSE, FALSE);
	::SendMessage(this->GetSafeHwnd(), WM_SELFMSG, (WPARAM)num1,(LPARAM)num2);
}


void CMy04�Զ�����ϢDlg::OnBnClickedButtonSendCopyData()
{
	CString str;
	GetDlgItemText(IDC_EDIT4, str);
	COPYDATASTRUCT data;
	data.dwData = 0;//û�и�����Ϣ
	data.cbData = str.GetLength()*2+1;//�����ǲ���Unicode���룬һ����ʵ��С���ַ����ȵĶ���
	data.lpData = str.GetBuffer();//�õ��ַ�ָ��
	::SendMessage(this->GetSafeHwnd(), WM_COPYDATA, (WPARAM)this->GetSafeHwnd(), (LPARAM)&data);
}


BOOL CMy04�Զ�����ϢDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	CString str;
	str.Format(TEXT("%s"),(TCHAR *) pCopyDataStruct->lpData);
	SetDlgItemText(IDC_EDIT1, str);

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}
