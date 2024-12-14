
// �������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�������.h"
#include "�������Dlg.h"
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


// C�������Dlg �Ի���



C�������Dlg::C�������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C�������Dlg::IDD, pParent)
	, m_count(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C�������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_mBtn);
	DDX_Control(pDX, IDC_BUTTON3, m_BtnClose);
}

BEGIN_MESSAGE_MAP(C�������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C�������Dlg::OnBnClickedButton1)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON3, &C�������Dlg::OnBnClickedButton3)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// C�������Dlg ��Ϣ�������

BOOL C�������Dlg::OnInitDialog()
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

void C�������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C�������Dlg::OnPaint()
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
HCURSOR C�������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C�������Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}




void C�������Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MessageBox(L"��ѽ��̫����");
}


int C�������Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetTimer(0x1001, 1000,NULL);
	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | 0x80000L);
	this->SetBackgroundColor(RGB(255,255,255));
	this->SetLayeredWindowAttributes(RGB(255, 255, 255), 120, LWA_COLORKEY);
	this->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	this->ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	return 0;
}


void C�������Dlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (IDYES == MessageBox(L"��ʵ˵���ǲ���tab�ˣ�", 0, MB_YESNO))
	{
		MessageBox(L"������Ȼ��tab����ǣ�");
	}
	else
	{
		MessageBox(L"�ߣ��������ˡ�");
	}
	PostMessage(WM_CLOSE);
}


void C�������Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (this->m_count<12)
		this->m_count++;
	if (this->m_count > 10)
		this->m_BtnClose.ShowWindow(SW_SHOW);
	CDialogEx::OnTimer(nIDEvent);
}


void C�������Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL C�������Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (pMsg->hwnd == this->m_BtnClose.GetSafeHwnd())
		{
			CRect frect, srect;
			this->GetWindowRect(&frect);
			this->m_BtnClose.GetWindowRect(&srect);
			int wid = frect.right - srect.right;
			int hei = frect.bottom - srect.bottom - 50;
			this->m_BtnClose.SetWindowPos(0, rand() % wid, rand() % hei + 50, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			return true;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void C�������Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	MessageBox(L"�ټ���������Ҳ������");
}


HBRUSH C�������Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
