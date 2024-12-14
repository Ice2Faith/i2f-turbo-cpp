
// 19-����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "19-����.h"
#include "19-����Dlg.h"
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


// CMy19����Dlg �Ի���



CMy19����Dlg::CMy19����Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy19����Dlg::IDD, pParent)
	, m_hscor_size(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy19����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_hscor_size);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_scrbar);
}

BEGIN_MESSAGE_MAP(CMy19����Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy19����Dlg::OnBnClickedOk)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CMy19����Dlg ��Ϣ�������

BOOL CMy19����Dlg::OnInitDialog()
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
	m_hscor_size = 50;
	UpdateData(FALSE);
	m_scrbar.SetScrollRange(0,100);
	m_scrbar.SetScrollPos(m_hscor_size);
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy19����Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy19����Dlg::OnPaint()
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
HCURSOR CMy19����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy19����Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}

//ˮƽ���鴦��ʱ�䣬��Ҫ�ڸ����ڽ��д���
void CMy19����Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int pos;
	if (pScrollBar == &m_scrbar)//�Ƚ϶���
	{
		switch (nSBCode)
		{
		case SB_THUMBPOSITION://������,�ڻ�����ʱnPos���������ã����Ǹ��ӣ����漸��Ҫע��
			m_scrbar.SetScrollPos(nPos);
			m_hscor_size = nPos;
			UpdateData(FALSE);
			break;
		case SB_LINELEFT://���ͷ
			pos = m_scrbar.GetScrollPos() - 5;
			if (pos < 0)
				pos = 0;
			m_scrbar.SetScrollPos(pos);
			m_hscor_size = pos;
			UpdateData(FALSE);
			break;
		case SB_LINERIGHT://�Ҽ�ͷ
			pos = m_scrbar.GetScrollPos() + 5;
			if (pos > 100)
				pos = 100;
			m_scrbar.SetScrollPos(pos);
			m_hscor_size = pos;
			UpdateData(FALSE);
			break;
		case SB_PAGELEFT://�������
			pos = m_scrbar.GetScrollPos() - 5;
			if (pos < 0)
				pos = 0;
			m_scrbar.SetScrollPos(pos);
			m_hscor_size = pos;
			UpdateData(FALSE);
			break;
		case SB_PAGERIGHT://�����ұ�
			pos = m_scrbar.GetScrollPos() + 5;
			if (pos >100)
				pos = 100;
			m_scrbar.SetScrollPos(pos);
			m_hscor_size = pos;
			UpdateData(FALSE);
			break;
		}
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
