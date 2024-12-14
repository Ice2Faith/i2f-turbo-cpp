
// ��¼��֤ģ���ƽ�Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��¼��֤ģ���ƽ�.h"
#include "��¼��֤ģ���ƽ�Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include<stdlib.h>
#include<time.h>
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


// C��¼��֤ģ���ƽ�Dlg �Ի���



C��¼��֤ģ���ƽ�Dlg::C��¼��֤ģ���ƽ�Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C��¼��֤ģ���ƽ�Dlg::IDD, pParent)
	, m_loginInfo(_T(""))
	, m_resultRoll(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C��¼��֤ģ���ƽ�Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_LOGININFO, m_loginInfo);
	DDX_Text(pDX, IDC_STATIC_RESULT, m_resultRoll);
}

BEGIN_MESSAGE_MAP(C��¼��֤ģ���ƽ�Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C��¼��֤ģ���ƽ�Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ROLLONCE, &C��¼��֤ģ���ƽ�Dlg::OnBnClickedButtonRollonce)
END_MESSAGE_MAP()


// C��¼��֤ģ���ƽ�Dlg ��Ϣ�������

BOOL C��¼��֤ģ���ƽ�Dlg::OnInitDialog()
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
	logindlg.DoModal();
	srand((unsigned int)time(NULL));
	m_resultRoll = _T("0  0  0  0  0");
	if (!logindlg.m_isLogined)
	{
		MessageBox(_T("δ��¼��������ʹ�ñ�����������˳�"));
		exit(0);
	}
	m_loginInfo = _T("�û�����")+logindlg.m_account +_T(" ���룺")+ logindlg.m_password;
	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C��¼��֤ģ���ƽ�Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C��¼��֤ģ���ƽ�Dlg::OnPaint()
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
HCURSOR C��¼��֤ģ���ƽ�Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C��¼��֤ģ���ƽ�Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void C��¼��֤ģ���ƽ�Dlg::OnBnClickedButtonRollonce()
{
	m_resultRoll.Format(_T("%d  %d  %d  %d  %d"), rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1);
	UpdateData(FALSE);
}
