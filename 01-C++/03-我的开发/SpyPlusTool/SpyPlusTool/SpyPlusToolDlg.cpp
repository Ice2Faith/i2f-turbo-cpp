
// SpyPlusToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SpyPlusTool.h"
#include "SpyPlusToolDlg.h"
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


// CSpyPlusToolDlg 对话框



CSpyPlusToolDlg::CSpyPlusToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpyPlusToolDlg::IDD, pParent)
	, m_is_FindWindow(false)
	, m_DrtWnd(NULL)
	, m_allow_SetTransparent(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpyPlusToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SPY, m_BTN_Spy);
	DDX_Control(pDX, IDC_EDIT_HAND, m_EDT_Hand);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_EDT_Title);
	DDX_Control(pDX, IDC_EDIT_CLASS, m_EDT_Class);
	DDX_Control(pDX, IDC_EDIT_RECT, m_DET_Rect);
	DDX_Control(pDX, IDC_EDIT_STYLE, m_EDT_Style);
	DDX_Control(pDX, IDC_EDIT_EXSTYLE, m_EDT_ExStyle);
	DDX_Control(pDX, IDC_SLIDER_TRANSPARENT, m_SDC_Transparent);
	DDX_Control(pDX, IDC_EDIT_SIZE, m_EDT_Size);
	DDX_Control(pDX, IDC_BUTTON_SIZE, m_BTN_Size);
	DDX_Control(pDX, IDC_EDIT_POS, m_EDT_Pos);
	DDX_Control(pDX, IDC_BUTTON_POS, m_BTN_Pos);
	DDX_Control(pDX, IDC_BUTTON_HELP, m_BTN_Help);
	DDX_Control(pDX, IDC_BUTTON_COPY, m_BTN_Copy);
	DDX_Control(pDX, IDC_COMBO_EXPOWER, m_CMB_ExPoewr);
	DDX_Control(pDX, IDC_BUTTON_EXPOWER, m_BTN_ExPower);
	DDX_Control(pDX, IDC_CHECK_PMSSETTRANSPARENT, m_CKB_PmsSetTransprt);
	DDX_Control(pDX, IDC_LIST_SPY_HISTORY, m_lst_spyHistory);
}

BEGIN_MESSAGE_MAP(CSpyPlusToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSpyPlusToolDlg::OnBnClickedOk)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TRANSPARENT, &CSpyPlusToolDlg::OnNMCustomdrawSliderTransparent)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SIZE, &CSpyPlusToolDlg::OnBnClickedButtonSize)
	ON_BN_CLICKED(IDC_BUTTON_POS, &CSpyPlusToolDlg::OnBnClickedButtonPos)
	ON_BN_CLICKED(IDC_BUTTON_EXPOWER, &CSpyPlusToolDlg::OnBnClickedButtonExpower)
	ON_BN_CLICKED(IDC_CHECK_PMSSETTRANSPARENT, &CSpyPlusToolDlg::OnBnClickedCheckPmssettransparent)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CSpyPlusToolDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_COPY, &CSpyPlusToolDlg::OnBnClickedButtonCopy)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_SEL, &CSpyPlusToolDlg::OnBnClickedButtonLoadSel)
	ON_BN_CLICKED(IDC_BUTTON_TERMINAL_PROCESS, &CSpyPlusToolDlg::OnBnClickedButtonTerminalProcess)
	ON_BN_CLICKED(IDC_BUTTON_ENUM_WINDOWS, &CSpyPlusToolDlg::OnBnClickedButtonEnumWindows)
	ON_BN_CLICKED(IDC_BUTTON_DESKTOP_WINDOW, &CSpyPlusToolDlg::OnBnClickedButtonDesktopWindow)
END_MESSAGE_MAP()


// CSpyPlusToolDlg 消息处理程序

BOOL CSpyPlusToolDlg::OnInitDialog()
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
	AdjustCurrentProcessPrivaligeToSEDebug();
	InitControls();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSpyPlusToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSpyPlusToolDlg::OnPaint()
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
HCURSOR CSpyPlusToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSpyPlusToolDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}



void CSpyPlusToolDlg::OnNMCustomdrawSliderTransparent(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	if (this->m_allow_SetTransparent == true)
	{
		int pos = this->m_SDC_Transparent.GetPos();
		SetWndTransparent(this->m_DrtWnd->GetSafeHwnd(), 100 - pos);
		UpdateData(FALSE);
	}
	*pResult = 0;
}

void CSpyPlusToolDlg::SetWndTransparent(HWND hwnd, float alpha)
{
	LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
	SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
	::SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), alpha*(255/100.0), LWA_ALPHA);
}
BOOL CSpyPlusToolDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == this->m_BTN_Spy.GetSafeHwnd())
		{
			this->m_is_FindWindow = true;
			SetTimer(ID_TIMER_FINDWINDOW, 30, NULL);
			this->m_lst_spyHistory.DeleteAllItems();
		}
	}
	if (pMsg->message == WM_LBUTTONUP)
	{
		this->m_is_FindWindow = false;
		KillTimer(ID_TIMER_FINDWINDOW);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSpyPlusToolDlg::InitControls()
{

	SetBackgroundColor(RGB(250, 250, 250));
	this->m_SDC_Transparent.SetRange(0, 100);
	this->m_SDC_Transparent.SetTicFreq(1);

	this->m_CMB_ExPoewr.AddString(L"常规");
	this->m_CMB_ExPoewr.AddString(L"最大化");
	this->m_CMB_ExPoewr.AddString(L"最小化");
	this->m_CMB_ExPoewr.AddString(L"隐藏");
	this->m_CMB_ExPoewr.AddString(L"置顶");
	this->m_CMB_ExPoewr.AddString(L"置底");
	this->m_CMB_ExPoewr.AddString(L"无层次");
	this->m_CMB_ExPoewr.AddString(L"关闭");
	this->m_CMB_ExPoewr.SetCurSel(0);

	this->m_CKB_PmsSetTransprt.SetCheck(0);
	this->m_EDT_Size.SetWindowText(L"720-480");
	this->m_EDT_Pos.SetWindowText(L"100-200");

	//设置拓展样式，有网格线和选择一整行
	m_lst_spyHistory.SetExtendedStyle(m_lst_spyHistory.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//插入列
	m_lst_spyHistory.InsertColumn(0, TEXT("  HWND  "));
	m_lst_spyHistory.InsertColumn(1, TEXT("窗    口    标    题"));
	m_lst_spyHistory.InsertColumn(2, TEXT("窗    口    类"));
	//设置自动列宽
	m_lst_spyHistory.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_lst_spyHistory.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_lst_spyHistory.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
}

void CSpyPlusToolDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == ID_TIMER_FINDWINDOW)
	{
		static HWND lastWnd = NULL;
		CPoint point;
		GetCursorPos(&point);
		this->m_DrtWnd = WindowFromPoint(point);
		if (this->m_DrtWnd == NULL)
			return;
		if (this->m_DrtWnd->GetSafeHwnd() == NULL)
			return;
		if (lastWnd == this->m_DrtWnd->GetSafeHwnd())
			return;
		lastWnd = this->m_DrtWnd->GetSafeHwnd();
		
		ShowDrtWindowInfoToView();

		m_lst_spyHistory.InsertItem(0, wHand);
		m_lst_spyHistory.SetItemText(0, 1, wTitle);
		m_lst_spyHistory.SetItemText(0, 2, wClass);
		m_lst_spyHistory.SetItemData(0, (DWORD_PTR)this->m_DrtWnd->GetSafeHwnd());

		


	}
	CDialogEx::OnTimer(nIDEvent);
}


void CSpyPlusToolDlg::OnBnClickedButtonSize()
{
	// TODO:  在此添加控件通知处理程序代码
	if (this->m_DrtWnd == NULL)
		return;
	if (this->m_DrtWnd->GetSafeHwnd() == NULL)
		return;
	CString wsize;
	this->m_EDT_Size.GetWindowText(wsize);
	int hei=240, wid=480;
	if (2 != _stscanf_s(wsize, L"%d-%d", &wid, &hei))
	{
		MessageBox(L"请正确输入，宽度-高度，例如720-480",L"参数错误",MB_OK);
		return;
	}
	::SetWindowPos(this->m_DrtWnd->GetSafeHwnd(),0,0,0,wid,hei,SWP_NOMOVE|SWP_NOZORDER);

}


void CSpyPlusToolDlg::OnBnClickedButtonPos()
{
	// TODO:  在此添加控件通知处理程序代码
	if (this->m_DrtWnd == NULL)
		return;
	if (this->m_DrtWnd->GetSafeHwnd() == NULL)
		return;
	CString wpos;
	this->m_EDT_Pos.GetWindowText(wpos);
	int wx = 0, wy = 0;
	if(2!=_stscanf_s(wpos, L"%d-%d", &wx, &wy))
	{
		MessageBox(L"请正确输入，X坐标-Y坐标，例如100-200", L"参数错误", MB_OK);
		return;
	}
	::SetWindowPos(this->m_DrtWnd->GetSafeHwnd(), 0, wx, wy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}


void CSpyPlusToolDlg::OnBnClickedButtonExpower()
{
	// TODO:  在此添加控件通知处理程序代码
	if (this->m_DrtWnd == NULL)
		return;
	if (this->m_DrtWnd->GetSafeHwnd() == NULL)
		return;
	int ExIndex = this->m_CMB_ExPoewr.GetCurSel();
	if (ExIndex == 0)
	{
		this->m_DrtWnd->SetParent(NULL);
		this->m_DrtWnd->ShowWindow(SW_NORMAL);
	}
	else if (ExIndex == 1)
	{
		this->m_DrtWnd->ShowWindow(SW_MAXIMIZE);
	}
	else if (ExIndex == 2)
	{
		this->m_DrtWnd->ShowWindow(SW_MINIMIZE);
	}
	else if (ExIndex == 3)
	{
		this->m_DrtWnd->ShowWindow(SW_HIDE);
	}
	else if (ExIndex == 4)
	{
		this->m_DrtWnd->SetParent(NULL);
		::SetWindowPos(this->m_DrtWnd->GetSafeHwnd(),HWND_TOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	}
	else if (ExIndex == 5)
	{
		::SetWindowPos(this->m_DrtWnd->GetSafeHwnd(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		HWND hDesktop = ::FindWindow(_T("Progman"), L"Program Manager");
		hDesktop = ::GetWindow(hDesktop, GW_CHILD);
		CWnd* pWndDesktop = CWnd::FromHandle(hDesktop);
		this->m_DrtWnd->SetParent(pWndDesktop);
	}
	else if (ExIndex == 6)
	{
		this->m_DrtWnd->SetParent(NULL);
		::SetWindowPos(this->m_DrtWnd->GetSafeHwnd(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		::SetWindowPos(this->m_DrtWnd->GetSafeHwnd(), HWND_DESKTOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
	else if (ExIndex == 7)
	{
		::PostMessage(this->m_DrtWnd->GetSafeHwnd(), WM_DESTROY, 0, 0);
	}
}

void CSpyPlusToolDlg::OnBnClickedCheckPmssettransparent()
{
	// TODO:  在此添加控件通知处理程序代码
	if (this->m_CKB_PmsSetTransprt.GetCheck() == 1)
	{
		this->m_allow_SetTransparent = true;
	}else
	{
		this->m_allow_SetTransparent = false;
	}
}
void CSpyPlusToolDlg::OnBnClickedButtonCopy()
{
	// TODO:  在此添加控件通知处理程序代码

	CString source = L"句柄：" + wHand + L"\n" 
		+ L"标题：" + wTitle + L"\n" 
		+ L"类名：" + wClass + L"\n" 
		+ L"矩形：" + wRect + L"\n" 
		+ L"风格：" + wStyle + L"\n" 
		+ L"拓展风格：" + wExStyle + L"\n";
	if (OpenClipboard())
	{
		//防止非ASCII语言复制到剪切板为乱码
		int buff_size = source.GetLength();
		CStringW strWide = CStringW(source);
		int nLen = strWide.GetLength();
		//将剪切板置空
		::EmptyClipboard();
		HANDLE clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, (nLen + 1) * 2);
		if (!clipbuffer)
		{
			::CloseClipboard();
			return;
		}
		char* buffer = (char*)::GlobalLock(clipbuffer);
		memset(buffer, 0, (nLen + 1) * 2);
		memcpy_s(buffer, nLen * 2, strWide.GetBuffer(0), nLen * 2);
		strWide.ReleaseBuffer();
		::GlobalUnlock(clipbuffer);
		::SetClipboardData(CF_UNICODETEXT, clipbuffer);
		::CloseClipboard();
	}
}

void CSpyPlusToolDlg::OnBnClickedButtonHelp()
{
	// TODO:  在此添加控件通知处理程序代码
	CString HelpInfo = L"使用步骤\n\
\t在探测按钮上按下鼠标左键开始探测\n\
\t移动到目标窗口上之后松开左键\n\
\t即探测完成，即可对窗口进行操作\n\
\t枚举窗口:\n\
\t将会枚举出显示区窗口下的所有子窗口\n\
\t如果你要枚举所有窗口，请先拿到顶层窗口\n\
\t同样，你可以把列表中的进行载入\n\
";

	MessageBox(HelpInfo,L"Help",MB_OK|MB_ICONINFORMATION);
}


void CSpyPlusToolDlg::OnBnClickedButtonLoadSel()
{
	//获取选中项
	POSITION pos = m_lst_spyHistory.GetFirstSelectedItemPosition();
	int selIndex = -1;
	while (pos)
	{
		selIndex = m_lst_spyHistory.GetNextSelectedItem(pos);
	}
	//如果没有选中项则返回
	if (selIndex == -1)
	{
		return;
	}
	HWND hwnd=(HWND)m_lst_spyHistory.GetItemData(selIndex);
	this->m_DrtWnd = CWnd::FromHandle(hwnd);

	ShowDrtWindowInfoToView();
}

void CSpyPlusToolDlg::OnBnClickedButtonTerminalProcess()
{
	// 强制终止程序运行，类任务管理器能力

	DWORD pid = 0;
	GetWindowThreadProcessId(this->m_DrtWnd->GetSafeHwnd(), &pid);

	if (pid == 0)
		return;
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (handle == INVALID_HANDLE_VALUE)
	{
		return;
	}
	
	BOOL ret = TerminateProcess(handle, 0);
	CloseHandle(handle);
	if (ret == TRUE)
	{
		CString str;
		str.Format(_T("PID:%d 进程已被终止！"), pid);
		MessageBox(str,0,MB_ICONINFORMATION);
	}
	else
	{
		::PostMessage(this->m_DrtWnd->GetSafeHwnd(), WM_CLOSE, 0, 0);
		::PostMessage(this->m_DrtWnd->GetSafeHwnd(), WM_DESTROY, 0, 0);
		char cmd[512] = { 0 };
		sprintf_s(cmd,"cmd /c TASKKILL /F /PID %d /T",pid);
		WinExec(cmd, SW_HIDE);
		MessageBox(TEXT("进程可能终止失败，或无法终止！"), 0, MB_ICONWARNING);
	}
}


void CSpyPlusToolDlg::OnBnClickedButtonEnumWindows()
{
	m_lst_spyHistory.DeleteAllItems();

	HWND curHwnd = ::GetNextWindow(m_DrtWnd->GetSafeHwnd(), GW_CHILD);
	TCHAR buf[1024] = {0};
	while (curHwnd != NULL)
	{
		wHand.Format(TEXT("0x%08x"), curHwnd);

		::GetWindowText(curHwnd, buf, 1024 - 1);
		wTitle = buf;

		::GetClassName(curHwnd, buf, 1024 - 1);
		wClass = buf;

		m_lst_spyHistory.InsertItem(0, wHand);
		m_lst_spyHistory.SetItemText(0, 1, wTitle);
		m_lst_spyHistory.SetItemText(0, 2, wClass);
		m_lst_spyHistory.SetItemData(0, (DWORD_PTR)curHwnd);

		curHwnd = ::GetNextWindow(curHwnd, GW_HWNDNEXT);
	}
}


void CSpyPlusToolDlg::OnBnClickedButtonDesktopWindow()
{
	// TODO:  在此添加控件通知处理程序代码
	m_DrtWnd = CWnd::FromHandle(::GetDesktopWindow());
	ShowDrtWindowInfoToView();
}


void CSpyPlusToolDlg::ShowDrtWindowInfoToView()
{
	wHand.Format(TEXT("0x%08x"), this->m_DrtWnd->GetSafeHwnd());
	this->m_EDT_Hand.SetWindowText(wHand);

	TCHAR buf[1024] = { 0 };
	::GetWindowText(this->m_DrtWnd->GetSafeHwnd(), buf, 1024 - 1);
	wTitle = buf;
	this->m_EDT_Title.SetWindowText(wTitle);

	::GetClassName(this->m_DrtWnd->GetSafeHwnd(), buf, 1024 - 1);
	wClass = buf;
	this->m_EDT_Class.SetWindowText(wClass);

	CRect rect;
	this->m_DrtWnd->GetWindowRect(rect);
	wRect.Format(TEXT("%d,%d,%d,%d"), rect.left, rect.top, rect.right, rect.bottom);
	this->m_DET_Rect.SetWindowText(wRect);

	WINDOWINFO winfo;
	this->m_DrtWnd->GetWindowInfo(&winfo);
	wStyle.Format(TEXT("0x%08x"), winfo.dwStyle);
	this->m_EDT_Style.SetWindowText(wStyle);

	wExStyle.Format(TEXT("0x%08x"), winfo.dwExStyle);
	this->m_EDT_ExStyle.SetWindowText(wExStyle);
}


bool CSpyPlusToolDlg::AdjustCurrentProcessPrivaligeToSEDebug()
{
	HANDLE hToken = NULL;
	BOOL ret = OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);
	if (ret == TRUE)
	{
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
		CloseHandle(hToken);
		return true;
	}
}
