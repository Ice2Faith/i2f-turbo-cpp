
// ��ʷ���а�Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ʷ���а�.h"
#include "��ʷ���а�Dlg.h"
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


// C��ʷ���а�Dlg �Ի���



C��ʷ���а�Dlg::C��ʷ���а�Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C��ʷ���а�Dlg::IDD, pParent)
	, m_isTransparent(false)
	, m_isTopMost(false)
	, m_isBanPower(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C��ʷ���а�Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	DDX_Control(pDX, IDC_CHECK1, m_BtnTransparent);
	DDX_Control(pDX, IDC_CHECK2, m_BtnTopMost);
	DDX_Control(pDX, IDC_CHECK3, m_BtnBanPower);
}

BEGIN_MESSAGE_MAP(C��ʷ���а�Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C��ʷ���а�Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C��ʷ���а�Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, &C��ʷ���а�Dlg::OnBnClickedCheckTransparent)
	ON_BN_CLICKED(IDC_CHECK2, &C��ʷ���а�Dlg::OnBnClickedCheckTopWindow)
	ON_BN_CLICKED(IDC_CHECK3, &C��ʷ���а�Dlg::OnBnClickedCheckBanPower)
	ON_BN_CLICKED(IDC_BUTTON1, &C��ʷ���а�Dlg::OnBnClickedButtonClearAll)
	ON_BN_CLICKED(IDC_BUTTON2, &C��ʷ���а�Dlg::OnBnClickedButtonCopyItem)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON3, &C��ʷ���а�Dlg::OnBnClickedButtonRemoveItem)
	ON_BN_CLICKED(IDC_BUTTON4, &C��ʷ���а�Dlg::OnBnClickedHideWindow)
END_MESSAGE_MAP()


// C��ʷ���а�Dlg ��Ϣ�������

BOOL C��ʷ���а�Dlg::OnInitDialog()
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
	m_listbox.SetHorizontalExtent(2000);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C��ʷ���а�Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C��ʷ���а�Dlg::OnPaint()
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
HCURSOR C��ʷ���а�Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C��ʷ���а�Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void C��ʷ���а�Dlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void C��ʷ���а�Dlg::OnBnClickedCheckTransparent()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (this->m_BtnTransparent.GetCheck() == 1)
	{
		this->m_isTransparent = true;
		HWND hwnd=this->GetSafeHwnd();
		LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
		SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
		SetLayeredWindowAttributes(RGB(0, 0, 0), 255 * ((100 - 30) / 100.0), LWA_ALPHA);
	}
	else
	{
		this->m_isTransparent = false;
		HWND hwnd = this->GetSafeHwnd();
		LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
		SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
		SetLayeredWindowAttributes(RGB(0, 0, 0), 255 * ((100 - 1) / 100.0), LWA_ALPHA);
	}
}


void C��ʷ���а�Dlg::OnBnClickedCheckTopWindow()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (this->m_BtnTopMost.GetCheck() == 1)
	{
		this->m_isTopMost = true;
		::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	else
	{
		this->m_isTopMost = false;
		::SetWindowPos(this->m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
}


void C��ʷ���а�Dlg::OnBnClickedCheckBanPower()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (this->m_BtnBanPower.GetCheck() == 1)
	{
		this->m_isBanPower = true;
	}
	else
	{
		this->m_isBanPower = false;
	}
}


void C��ʷ���а�Dlg::OnBnClickedButtonClearAll()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	this->m_listbox.ResetContent();
}


void C��ʷ���а�Dlg::OnBnClickedButtonCopyItem()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (this->m_listbox.GetCurSel() != LB_ERR)
	{
		CopyItemNToClipboard(this->m_listbox.GetCurSel());
	}
}


int C��ʷ���а�Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetTimer(ID_SPYCLIPBOARD, SPY_TIME_MILSEC,NULL);
	return 0;
}


void C��ʷ���а�Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == ID_SPYCLIPBOARD)
	{

		//�򿪼�����
		CString newtext;
		bool excist = false;

		if (this->m_isBanPower == false)
		{
			excist = false;
			if (OpenClipboard())
			{
				HANDLE hData = GetClipboardData(CF_TEXT);
				char * buffer = (char*)GlobalLock(hData);
				newtext = buffer;
				GlobalUnlock(hData);
				CloseClipboard();
				if (newtext.GetLength() == 0)
					return;
				for (int i = 0; i < this->m_listbox.GetCount(); i++)
				{
					CString pcontext;
					this->m_listbox.GetText(i, pcontext);
					if (newtext == pcontext)
					{
						excist = true;
						break;
					}
				}

				if (excist == false)
				{
					this->m_listbox.InsertString(0,newtext);

				}
				if (this->m_listbox.GetCount() > 1024){
					this->m_listbox.DeleteString(1024);
				}
			}

		}

		if (GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState(VK_MENU) & 0x8000){
			if (GetAsyncKeyState('1') & 0x8000 || GetAsyncKeyState(VK_NUMPAD1) & 0x8000){
				CopyItemNToClipboard(1);
			}
			if (GetAsyncKeyState('2') & 0x8000 || GetAsyncKeyState(VK_NUMPAD2) & 0x8000){
				CopyItemNToClipboard(2);
			}
			if (GetAsyncKeyState('3') & 0x8000 || GetAsyncKeyState(VK_NUMPAD3) & 0x8000){
				CopyItemNToClipboard(3);
			}
			if (GetAsyncKeyState('4') & 0x8000 || GetAsyncKeyState(VK_NUMPAD4) & 0x8000){
				CopyItemNToClipboard(4);
			}
			if (GetAsyncKeyState('5') & 0x8000 || GetAsyncKeyState(VK_NUMPAD5) & 0x8000){
				CopyItemNToClipboard(5);
			}
			if (GetAsyncKeyState('0') & 0x8000 || GetAsyncKeyState(VK_NUMPAD0) & 0x8000){
				CopyItemNToClipboard(0);
			}

			if (GetAsyncKeyState('9') & 0x8000 || GetAsyncKeyState(VK_NUMPAD9) & 0x8000){
				this->ShowWindow(SW_NORMAL);
			}
			if (GetAsyncKeyState('8') & 0x8000 || GetAsyncKeyState(VK_NUMPAD8) & 0x8000){
				this->ShowWindow(SW_HIDE);
			}

		}
		
	}
	CDialogEx::OnTimer(nIDEvent);
}

void C��ʷ���а�Dlg::CopyItemNToClipboard(int n){
	if (this->m_listbox.GetCount() <= n){
		return;
	}
	if (OpenClipboard())
	{
		CString scopy;
		this->m_listbox.GetText(n, scopy);
		wchar_t outwtext[8192] = { 0 };
		char outbord[8192 * 2] = { 0 };
		StrCpyW(outwtext, scopy.GetString());
		int size = WideCharToMultiByte(CP_ACP, 0, outwtext, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, outwtext, -1, outbord, size, NULL, NULL);
		EmptyClipboard();
		HGLOBAL clipbuffer;
		char *buffer;
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, strlen(outbord) + 1);
		buffer = (char *)GlobalLock(clipbuffer);
		strcpy(buffer, outbord);
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT, clipbuffer);
		CloseClipboard();
	}
}


void C��ʷ���а�Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	for (int i = 0; i < DragQueryFile(hDropInfo, -1, NULL, 0); i++)
	{
		WCHAR wcStr[MAX_PATH];
		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);
		CString newtext=wcStr;
		bool excist = false;
		for (int i = 0; i < this->m_listbox.GetCount(); i++)
		{
			CString pcontext;
			this->m_listbox.GetText(i, pcontext);
			if (newtext == pcontext)
			{
				excist = true;
				break;
			}
		}
		if (excist==false)
			this->m_listbox.InsertString(0,wcStr);
	}
	CDialogEx::OnDropFiles(hDropInfo);
}


void C��ʷ���а�Dlg::OnBnClickedButtonRemoveItem()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (this->m_listbox.GetCurSel() != LB_ERR)
	{
		this->m_listbox.DeleteString(this->m_listbox.GetCurSel());
	}
}


void C��ʷ���а�Dlg::OnBnClickedHideWindow()
{
	this->ShowWindow(SW_HIDE);
}
