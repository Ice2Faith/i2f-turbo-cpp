
// SpyPlusToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SpyPlusTool.h"
#include "SpyPlusToolDlg.h"
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


// CSpyPlusToolDlg �Ի���



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


// CSpyPlusToolDlg ��Ϣ�������

BOOL CSpyPlusToolDlg::OnInitDialog()
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
	AdjustCurrentProcessPrivaligeToSEDebug();
	InitControls();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSpyPlusToolDlg::OnPaint()
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
HCURSOR CSpyPlusToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSpyPlusToolDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}



void CSpyPlusToolDlg::OnNMCustomdrawSliderTransparent(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ����ר�ô����/����û���
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

	this->m_CMB_ExPoewr.AddString(L"����");
	this->m_CMB_ExPoewr.AddString(L"���");
	this->m_CMB_ExPoewr.AddString(L"��С��");
	this->m_CMB_ExPoewr.AddString(L"����");
	this->m_CMB_ExPoewr.AddString(L"�ö�");
	this->m_CMB_ExPoewr.AddString(L"�õ�");
	this->m_CMB_ExPoewr.AddString(L"�޲��");
	this->m_CMB_ExPoewr.AddString(L"�ر�");
	this->m_CMB_ExPoewr.SetCurSel(0);

	this->m_CKB_PmsSetTransprt.SetCheck(0);
	this->m_EDT_Size.SetWindowText(L"720-480");
	this->m_EDT_Pos.SetWindowText(L"100-200");

	//������չ��ʽ���������ߺ�ѡ��һ����
	m_lst_spyHistory.SetExtendedStyle(m_lst_spyHistory.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//������
	m_lst_spyHistory.InsertColumn(0, TEXT("  HWND  "));
	m_lst_spyHistory.InsertColumn(1, TEXT("��    ��    ��    ��"));
	m_lst_spyHistory.InsertColumn(2, TEXT("��    ��    ��"));
	//�����Զ��п�
	m_lst_spyHistory.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_lst_spyHistory.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_lst_spyHistory.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
}

void CSpyPlusToolDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (this->m_DrtWnd == NULL)
		return;
	if (this->m_DrtWnd->GetSafeHwnd() == NULL)
		return;
	CString wsize;
	this->m_EDT_Size.GetWindowText(wsize);
	int hei=240, wid=480;
	if (2 != _stscanf_s(wsize, L"%d-%d", &wid, &hei))
	{
		MessageBox(L"����ȷ���룬���-�߶ȣ�����720-480",L"��������",MB_OK);
		return;
	}
	::SetWindowPos(this->m_DrtWnd->GetSafeHwnd(),0,0,0,wid,hei,SWP_NOMOVE|SWP_NOZORDER);

}


void CSpyPlusToolDlg::OnBnClickedButtonPos()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (this->m_DrtWnd == NULL)
		return;
	if (this->m_DrtWnd->GetSafeHwnd() == NULL)
		return;
	CString wpos;
	this->m_EDT_Pos.GetWindowText(wpos);
	int wx = 0, wy = 0;
	if(2!=_stscanf_s(wpos, L"%d-%d", &wx, &wy))
	{
		MessageBox(L"����ȷ���룬X����-Y���꣬����100-200", L"��������", MB_OK);
		return;
	}
	::SetWindowPos(this->m_DrtWnd->GetSafeHwnd(), 0, wx, wy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}


void CSpyPlusToolDlg::OnBnClickedButtonExpower()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString source = L"�����" + wHand + L"\n" 
		+ L"���⣺" + wTitle + L"\n" 
		+ L"������" + wClass + L"\n" 
		+ L"���Σ�" + wRect + L"\n" 
		+ L"���" + wStyle + L"\n" 
		+ L"��չ���" + wExStyle + L"\n";
	if (OpenClipboard())
	{
		//��ֹ��ASCII���Ը��Ƶ����а�Ϊ����
		int buff_size = source.GetLength();
		CStringW strWide = CStringW(source);
		int nLen = strWide.GetLength();
		//�����а��ÿ�
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString HelpInfo = L"ʹ�ò���\n\
\t��̽�ⰴť�ϰ�����������ʼ̽��\n\
\t�ƶ���Ŀ�괰����֮���ɿ����\n\
\t��̽����ɣ����ɶԴ��ڽ��в���\n\
\tö�ٴ���:\n\
\t����ö�ٳ���ʾ�������µ������Ӵ���\n\
\t�����Ҫö�����д��ڣ������õ����㴰��\n\
\tͬ��������԰��б��еĽ�������\n\
";

	MessageBox(HelpInfo,L"Help",MB_OK|MB_ICONINFORMATION);
}


void CSpyPlusToolDlg::OnBnClickedButtonLoadSel()
{
	//��ȡѡ����
	POSITION pos = m_lst_spyHistory.GetFirstSelectedItemPosition();
	int selIndex = -1;
	while (pos)
	{
		selIndex = m_lst_spyHistory.GetNextSelectedItem(pos);
	}
	//���û��ѡ�����򷵻�
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
	// ǿ����ֹ�������У����������������

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
		str.Format(_T("PID:%d �����ѱ���ֹ��"), pid);
		MessageBox(str,0,MB_ICONINFORMATION);
	}
	else
	{
		::PostMessage(this->m_DrtWnd->GetSafeHwnd(), WM_CLOSE, 0, 0);
		::PostMessage(this->m_DrtWnd->GetSafeHwnd(), WM_DESTROY, 0, 0);
		char cmd[512] = { 0 };
		sprintf_s(cmd,"cmd /c TASKKILL /F /PID %d /T",pid);
		WinExec(cmd, SW_HIDE);
		MessageBox(TEXT("���̿�����ֹʧ�ܣ����޷���ֹ��"), 0, MB_ICONWARNING);
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
