
// 03-�������ģ��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "03-�������ģ��.h"
#include "03-�������ģ��Dlg.h"
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


// CMy03�������ģ��Dlg �Ի���



CMy03�������ģ��Dlg::CMy03�������ģ��Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy03�������ģ��Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy03�������ģ��Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy03�������ģ��Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy03�������ģ��Dlg::OnBnClickedButtonPostA)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy03�������ģ��Dlg::OnBnClickedButtonPostTaskPanel)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy03�������ģ��Dlg::OnBnClickedButtonFuncShift)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy03�������ģ��Dlg::OnBnClickedButtonFuncWin)
END_MESSAGE_MAP()


// CMy03�������ģ��Dlg ��Ϣ�������

BOOL CMy03�������ģ��Dlg::OnInitDialog()
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

void CMy03�������ģ��Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy03�������ģ��Dlg::OnPaint()
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
HCURSOR CMy03�������ģ��Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*
ģ�������꣺
���ַ�ʽ��
	������Ϣ
		SendMessage : ������ʹ�ã����п��ܲ���ɹ�
		PostMessage : �Ƽ�ʹ��
	ʹ��ģ�⺯��API
		VOID mouse_event(BYTE bVK,BYTE bScan,DWORD dwFlag,ULONG_PTR dwExtraInfo);
		VOID keybd_event(DWORD dwFlag,DWORD dx,DWORD dy,DWORD dwData,ULONG_PTR dwExtraInfo);

��ʱ����
	UINT_PTR SetTimer(HWND targetWnd,UINT_PTR nIDEvent,UINT uElapse,TIMERPROC lpTimerCallbackFunc);
	�ص�����ԭ�ͣ�
		VOID (CALLBACK* TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);
	�رն�ʱ����
		KillTimer(...)
*/

void CMy03�������ģ��Dlg::OnBnClickedButtonPostA()
{
	::PostMessage(this->GetSafeHwnd(), WM_KEYDOWN, 'A', 1);
	::PostMessage(this->GetSafeHwnd(), WM_KEYUP, 'A', 1);
}


void CMy03�������ģ��Dlg::OnBnClickedButtonPostTaskPanel()
{
	::PostMessage(this->GetSafeHwnd(), WM_KEYDOWN, VK_CONTROL, 1);
	::PostMessage(this->GetSafeHwnd(), WM_KEYDOWN, VK_SHIFT, 1);
	::PostMessage(this->GetSafeHwnd(), WM_KEYDOWN, VK_ESCAPE, 1);
	::PostMessage(this->GetSafeHwnd(), WM_KEYUP, VK_ESCAPE, 1);
	::PostMessage(this->GetSafeHwnd(), WM_KEYUP, VK_SHIFT, 1);
	::PostMessage(this->GetSafeHwnd(), WM_KEYUP, VK_CONTROL, 1);
}


void CMy03�������ģ��Dlg::OnBnClickedButtonFuncShift()
{
	//����ģ��
	keybd_event(VK_SHIFT, 0, 0, 0);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
}


void CMy03�������ģ��Dlg::OnBnClickedButtonFuncWin()
{
	//�����Winͼ��
	//�����Ļ�ߴ�
	int wid=GetSystemMetrics(SM_CXSCREEN);
	int hei = GetSystemMetrics(SM_CYSCREEN);
	//�ƶ���굽��Ļ�������꣬����Ǵ�������Ļ���Ҫת��Ϊ��Ļ���꣺BOOL ClientToScreen(HWND targetWnd,LPPOINT point)
	SetCursorPos(10, hei - 10);
	//��갴��ģ��
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
