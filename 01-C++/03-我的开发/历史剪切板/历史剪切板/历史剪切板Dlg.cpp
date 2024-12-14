
// 历史剪切板Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "历史剪切板.h"
#include "历史剪切板Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// C历史剪切板Dlg 对话框



C历史剪切板Dlg::C历史剪切板Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C历史剪切板Dlg::IDD, pParent)
	, m_isTransparent(false)
	, m_isTopMost(false)
	, m_isBanPower(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C历史剪切板Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	DDX_Control(pDX, IDC_CHECK1, m_BtnTransparent);
	DDX_Control(pDX, IDC_CHECK2, m_BtnTopMost);
	DDX_Control(pDX, IDC_CHECK3, m_BtnBanPower);
}

BEGIN_MESSAGE_MAP(C历史剪切板Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C历史剪切板Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C历史剪切板Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, &C历史剪切板Dlg::OnBnClickedCheckTransparent)
	ON_BN_CLICKED(IDC_CHECK2, &C历史剪切板Dlg::OnBnClickedCheckTopWindow)
	ON_BN_CLICKED(IDC_CHECK3, &C历史剪切板Dlg::OnBnClickedCheckBanPower)
	ON_BN_CLICKED(IDC_BUTTON1, &C历史剪切板Dlg::OnBnClickedButtonClearAll)
	ON_BN_CLICKED(IDC_BUTTON2, &C历史剪切板Dlg::OnBnClickedButtonCopyItem)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON3, &C历史剪切板Dlg::OnBnClickedButtonRemoveItem)
	ON_BN_CLICKED(IDC_BUTTON4, &C历史剪切板Dlg::OnBnClickedHideWindow)
END_MESSAGE_MAP()


// C历史剪切板Dlg 消息处理程序

BOOL C历史剪切板Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_listbox.SetHorizontalExtent(2000);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C历史剪切板Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C历史剪切板Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C历史剪切板Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C历史剪切板Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void C历史剪切板Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void C历史剪切板Dlg::OnBnClickedCheckTransparent()
{
	// TODO:  在此添加控件通知处理程序代码
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


void C历史剪切板Dlg::OnBnClickedCheckTopWindow()
{
	// TODO:  在此添加控件通知处理程序代码
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


void C历史剪切板Dlg::OnBnClickedCheckBanPower()
{
	// TODO:  在此添加控件通知处理程序代码
	if (this->m_BtnBanPower.GetCheck() == 1)
	{
		this->m_isBanPower = true;
	}
	else
	{
		this->m_isBanPower = false;
	}
}


void C历史剪切板Dlg::OnBnClickedButtonClearAll()
{
	// TODO:  在此添加控件通知处理程序代码
	
	this->m_listbox.ResetContent();
}


void C历史剪切板Dlg::OnBnClickedButtonCopyItem()
{
	// TODO:  在此添加控件通知处理程序代码
	if (this->m_listbox.GetCurSel() != LB_ERR)
	{
		CopyItemNToClipboard(this->m_listbox.GetCurSel());
	}
}


int C历史剪切板Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(ID_SPYCLIPBOARD, SPY_TIME_MILSEC,NULL);
	return 0;
}


void C历史剪切板Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == ID_SPYCLIPBOARD)
	{

		//打开剪贴板
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

void C历史剪切板Dlg::CopyItemNToClipboard(int n){
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


void C历史剪切板Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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


void C历史剪切板Dlg::OnBnClickedButtonRemoveItem()
{
	// TODO:  在此添加控件通知处理程序代码
	if (this->m_listbox.GetCurSel() != LB_ERR)
	{
		this->m_listbox.DeleteString(this->m_listbox.GetCurSel());
	}
}


void C历史剪切板Dlg::OnBnClickedHideWindow()
{
	this->ShowWindow(SW_HIDE);
}
