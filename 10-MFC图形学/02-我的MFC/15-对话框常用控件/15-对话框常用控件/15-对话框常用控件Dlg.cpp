
// 15-�Ի����ÿؼ�Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "15-�Ի����ÿؼ�.h"
#include "15-�Ի����ÿؼ�Dlg.h"
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


// CMy15�Ի����ÿؼ�Dlg �Ի���



CMy15�Ի����ÿؼ�Dlg::CMy15�Ի����ÿؼ�Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy15�Ի����ÿؼ�Dlg::IDD, pParent)
	, m_str(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy15�Ի����ÿؼ�Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2, m_button);
	DDX_Text(pDX, IDC_EDIT1, m_str);
	DDX_Control(pDX, IDC_BUTTON4, m_Clickme);
}

BEGIN_MESSAGE_MAP(CMy15�Ի����ÿؼ�Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy15�Ի����ÿؼ�Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy15�Ի����ÿؼ�Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMy15�Ի����ÿؼ�Dlg ��Ϣ�������

BOOL CMy15�Ի����ÿؼ�Dlg::OnInitDialog()
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
	this->m_button.SetWindowTextW(TEXT("�㲻��"));
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	//��ȡͼ���С
	BITMAP bm;
	bitmap.GetBitmap(&bm);
	this->m_button.MoveWindow(0, 0, bm.bmWidth, bm.bmHeight);
	//this->m_button.SetBitmap(bitmap);
	//ͨ��·����ȡλͼ�꣬����ָ����С
#define HBMP(filepath,width,height) \
	(HBITMAP)LoadImage(AfxGetInstanceHandle(),filepath,IMAGE_BITMAP,width,height,LR_LOADFROMFILE|LR_CREATEDIBSECTION)
	this->m_button.SetBitmap(HBMP(TEXT("../02.bmp"),100,50));
	//ͨ��·����ȡIcon��
#define HICO(filapath) \
	(HICON)LoadImage(AfxGetInstanceHandle(), filepath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE |LR_DEFAULTSIZE)
	//ͼƬ��С�Ͱ�ť��С����һ��

	//��ֵ��������
	m_str = TEXT("������");
	UpdateData(FALSE);//�������ݽ�����ʾFALSE
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy15�Ի����ÿؼ�Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy15�Ի����ÿؼ�Dlg::OnPaint()
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
HCURSOR CMy15�Ի����ÿؼ�Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//�����ťʱ����
void CMy15�Ի����ÿؼ�Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MessageBox(TEXT("��������"));
}


void CMy15�Ի����ÿؼ�Dlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//���Ի�������ݸ��µ���������TRUE
	MessageBox(m_str);
}
/*����ͼ�����MyButton���̳�CButton�࣬ʵ����Ϣ��������MouseMove,
��������Ӱ�ť��ѡ�а�ť��ѡ����ӱ�����Control��MYbutton���ͼ���*/
