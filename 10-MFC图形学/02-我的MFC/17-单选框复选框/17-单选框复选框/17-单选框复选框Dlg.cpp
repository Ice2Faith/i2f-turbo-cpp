
// 17-��ѡ��ѡ��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "17-��ѡ��ѡ��.h"
#include "17-��ѡ��ѡ��Dlg.h"
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


// CMy17��ѡ��ѡ��Dlg �Ի���



CMy17��ѡ��ѡ��Dlg::CMy17��ѡ��ѡ��Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy17��ѡ��ѡ��Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy17��ѡ��ѡ��Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_CKB_01);
}

BEGIN_MESSAGE_MAP(CMy17��ѡ��ѡ��Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy17��ѡ��ѡ��Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy17��ѡ��ѡ��Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy17��ѡ��ѡ��Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMy17��ѡ��ѡ��Dlg ��Ϣ�������

BOOL CMy17��ѡ��ѡ��Dlg::OnInitDialog()
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
	//���õ�ѡ���Ĭ��ѡ�У�������ʼID������ID��ѡ��ID
	//��ѡ��TAB����Ҫ����
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);

	//����ѡ�и�ѡ��
	this->m_CKB_01.SetCheck(1);
	this->m_CKB_01.SetWindowText(L"Ĭ��ѡ��");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy17��ѡ��ѡ��Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy17��ѡ��ѡ��Dlg::OnPaint()
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
HCURSOR CMy17��ѡ��ѡ��Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy17��ѡ��ѡ��Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CMy17��ѡ��ѡ��Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (IsDlgButtonChecked(IDC_RADIO2))
		MessageBox(L"ѡ��Ů");
}


void CMy17��ѡ��ѡ��Dlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tips;
	int IDs[] = { IDC_CHECK1, IDC_CHECK2, IDC_CHECK3, IDC_CHECK4 };
	CString names[] = { L"CK1", L"CK2", L"CK3", L"CK4" };
	for (int i = 0; i < 4; i++)
	{
		if (IsDlgButtonChecked(IDs[i]))
		{
			tips += names[i];
		}
	}
	MessageBox(tips);
}
