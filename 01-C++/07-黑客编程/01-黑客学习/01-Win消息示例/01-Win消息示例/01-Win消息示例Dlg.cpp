
// 01-Win��Ϣʾ��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "01-Win��Ϣʾ��.h"
#include "01-Win��Ϣʾ��Dlg.h"
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


// CMy01Win��Ϣʾ��Dlg �Ի���



CMy01Win��Ϣʾ��Dlg::CMy01Win��Ϣʾ��Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy01Win��Ϣʾ��Dlg::IDD, pParent)
	, m_title(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy01Win��Ϣʾ��Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_title);
}

BEGIN_MESSAGE_MAP(CMy01Win��Ϣʾ��Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CMy01Win��Ϣʾ��Dlg::OnBnClickedButtonCloseNotepad)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy01Win��Ϣʾ��Dlg::OnBnClickedButtonOpenNotepad)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy01Win��Ϣʾ��Dlg::OnBnClickedButtonSetNotepadTitle)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy01Win��Ϣʾ��Dlg::OnBnClickedButtonGetNotepadTitle)
END_MESSAGE_MAP()


// CMy01Win��Ϣʾ��Dlg ��Ϣ�������

BOOL CMy01Win��Ϣʾ��Dlg::OnInitDialog()
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

void CMy01Win��Ϣʾ��Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy01Win��Ϣʾ��Dlg::OnPaint()
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
HCURSOR CMy01Win��Ϣʾ��Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
Windows����ִ�����̣�
������:
	WinMain���
	RegisterClassExע�ᴰ������
		loop:
		GetMessage��ȡ��Ϣ	| ���͡���ȡ��Ϣ��-��Ϣ����
		DispatchMessage�ַ���Ϣ | �ص�������-ϵͳ����ģ��
	WinMain����

���ڹ��̣�
	ϵͳ����ģ��ַ���Ϣ
		�ж���Ϣ��ֵ
			1.�û��Լ�����Ϣ����
			2.DefWindowProcϵͳĬ�ϵ���Ϣ����
	����ϵͳ����ģ��

ϵͳ����ģ�飺
	���ַܷ�����Ϣ
	�����ھ���ʹ������ַ
	����������Ϣ

�����ࣺ
	һ����������ĳ�������Ĵ���ģ��
*/


void CMy01Win��Ϣʾ��Dlg::OnBnClickedButtonCloseNotepad()
{
	//HWND FindWindow(LPCTSTR className,LPCTSTR windowTitle);
	//ͨ�����������ڱ�����Ҵ��ڣ���ֻ���õ�һ��ʱ����һ������ֱ������ΪNULL
	//���ڲ��Ҵ�������������ͨ��VS��Spy++���߽��в���
	HWND hwnd = ::FindWindow(TEXT("Notepad"), NULL);
	//Ҳ����ͨ�����ھ���ڽ��в�ѯ����
	TCHAR winClass[512];
	::RealGetWindowClass(hwnd, winClass, 512);
	if (hwnd != NULL)
	{
		//LRESULT SendMessage(HWND targetWnd,UINT msgType,WPARAM wParam.LPARAM lParam);
		//��Ŀ�괰�ڷ���һ��ָ�����ʹ���������Ϣ�������Ϣ�ĸ��Ӳ���û�����ã���ֵΪ0��NULL��
		::SendMessage(hwnd, WM_CLOSE, NULL, NULL);
	}
}


void CMy01Win��Ϣʾ��Dlg::OnBnClickedButtonOpenNotepad()
{
	WinExec("notepad.exe", SW_SHOW);
}


void CMy01Win��Ϣʾ��Dlg::OnBnClickedButtonSetNotepadTitle()
{
	HWND hwnd = ::FindWindow(NULL, TEXT("�ޱ��� - ���±�"));
	if (hwnd != NULL)
	{
		UpdateData(TRUE);
		::SendMessage(hwnd, WM_SETTEXT, NULL, (LPARAM)m_title.GetBuffer());
	}
}


void CMy01Win��Ϣʾ��Dlg::OnBnClickedButtonGetNotepadTitle()
{
	HWND hwnd = ::FindWindow(TEXT("Notepad"), NULL);
	if (hwnd != NULL)
	{
		TCHAR arr[1024];
		::SendMessage(hwnd, WM_GETTEXT, (WPARAM)1024, (LPARAM)arr);
		m_title = arr;
		UpdateData(FALSE);
	}
}
