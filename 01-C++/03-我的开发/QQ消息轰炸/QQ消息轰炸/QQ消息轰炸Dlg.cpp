
// QQ消息轰炸Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ消息轰炸.h"
#include "QQ消息轰炸Dlg.h"
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


// CQQ消息轰炸Dlg 对话框



CQQ消息轰炸Dlg::CQQ消息轰炸Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQQ消息轰炸Dlg::IDD, pParent)
	, m_VWaitTime(0)
	, m_VSendTime(0)
	, m_PreTime(0)
	, m_IsFindWnd(false)
	, m_SdMsgIndex(0)
	, m_israndindex(false)
	, m_isOnlySel(false)
	, m_ck_findpos(FALSE)
	, m_edt_pos(_T(""))
	, m_input_pos(0)
	, m_backup_pos(0)
	, m_isSendForeever(false)
{
	this->m_DrtWnd = NULL;
	srand((unsigned int)time(NULL));
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQQ消息轰炸Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MSGLIST, m_MsgList);
	DDX_Control(pDX, IDC_EDIT_MESSAGE, m_MsgInput);
	DDX_Control(pDX, IDC_COMBO_SENDTIME, m_SendTime);
	DDX_Control(pDX, IDC_COMBO_WAITTIME, m_WaitTime);
	DDX_Control(pDX, IDC_BUTTON_FINDWND, m_FindWndBtn);
	DDX_Control(pDX, IDC_LIST_WNDINFO, m_FindWindLB);
	DDX_Control(pDX, IDC_EDIT_DRTTITLE, m_DrtWndTitleIn);
	DDX_Control(pDX, IDC_COMBO_SENDTYPE, m_SendTypeCB);
	DDX_Control(pDX, IDC_CHECK_FROMCLIPBOARD, m_FromClipBoard);
	DDX_Control(pDX, IDC_CHECK_RANDSEND, m_RandSend);
	DDX_Control(pDX, IDC_CHECK_ONLYSEL, m_OnlyCheck);
	DDX_Check(pDX, IDC_CHECK_INPUTPOS, m_ck_findpos);
	DDX_Text(pDX, IDC_EDIT_INPUTPOS, m_edt_pos);
	DDX_Control(pDX, IDC_BUTTON_INPUTPOS, m_btn_getpos);
}

BEGIN_MESSAGE_MAP(CQQ消息轰炸Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CQQ消息轰炸Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADDMSG, &CQQ消息轰炸Dlg::OnBnClickedButtonAddmsg)
	ON_BN_CLICKED(IDC_BUTTON_RMMSG, &CQQ消息轰炸Dlg::OnBnClickedButtonRmmsg)
	ON_BN_CLICKED(IDC_BUTTON_CLEANMSG, &CQQ消息轰炸Dlg::OnBnClickedButtonCleanmsg)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CQQ消息轰炸Dlg::OnBnClickedButtonRun)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SETWND, &CQQ消息轰炸Dlg::OnBnClickedButtonSetwnd)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CQQ消息轰炸Dlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_CHECK_RANDSEND, &CQQ消息轰炸Dlg::OnBnClickedCheckRandsend)
	ON_BN_CLICKED(IDC_CHECK_ONLYSEL, &CQQ消息轰炸Dlg::OnBnClickedCheckOnlysel)
	ON_BN_CLICKED(IDC_CHECK_INPUTPOS, &CQQ消息轰炸Dlg::OnBnClickedCheckInputpos)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_BN_CLICKED(IDC_CHECK_SEND_FOREEVER, &CQQ消息轰炸Dlg::OnBnClickedCheckSendForeever)
END_MESSAGE_MAP()


// CQQ消息轰炸Dlg 消息处理程序

BOOL CQQ消息轰炸Dlg::OnInitDialog()
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
	this->m_MsgList.SetHorizontalExtent(1000);
	this->m_FindWindLB.SetHorizontalExtent(512);
	this->m_FromClipBoard.SetCheck(0);

	this->m_SendTime.AddString(L"1");
	this->m_SendTime.AddString(L"3");
	this->m_SendTime.AddString(L"5");
	this->m_SendTime.AddString(L"10");
	this->m_SendTime.AddString(L"15");
	this->m_SendTime.AddString(L"30");
	this->m_SendTime.AddString(L"70");
	this->m_SendTime.AddString(L"100");
	this->m_SendTime.AddString(L"200");
	this->m_SendTime.AddString(L"500");
	this->m_SendTime.AddString(L"1000");
	this->m_SendTime.SetCurSel(0);

	this->m_WaitTime.AddString(L"30ms");
	this->m_WaitTime.AddString(L"90ms");
	this->m_WaitTime.AddString(L"300ms");
	this->m_WaitTime.AddString(L"700ms");
	this->m_WaitTime.AddString(L"1s");
	this->m_WaitTime.AddString(L"3s");
	this->m_WaitTime.AddString(L"5s");
	this->m_WaitTime.AddString(L"10s");
	this->m_WaitTime.AddString(L"30s");
	this->m_WaitTime.AddString(L"60s");
	this->m_WaitTime.SetCurSel(0);

	this->m_SendTypeCB.AddString(L"Ctrl+Enter");
	this->m_SendTypeCB.AddString(L"Enter");
	this->m_SendTypeCB.AddString(L"Alt+Enter");
	this->m_SendTypeCB.AddString(L"Space");
	this->m_SendTypeCB.AddString(L"Tab");
	this->m_SendTypeCB.AddString(L"无");
	this->m_SendTypeCB.SetCurSel(0);

	this->m_RandSend.SetCheck(0);
	this->m_OnlyCheck.SetCheck(0);

	this->m_ck_findpos = FALSE;
	this->m_btn_getpos.EnableWindow(FALSE);
	this->m_edt_pos=(L"pos:0,0");

	RegisterHotKey(this->GetSafeHwnd(), ID_STOP_LOOP_ACCE, MOD_CONTROL | MOD_SHIFT, 'F');
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQQ消息轰炸Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CQQ消息轰炸Dlg::OnPaint()
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
HCURSOR CQQ消息轰炸Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQQ消息轰炸Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CQQ消息轰炸Dlg::OnBnClickedButtonAddmsg()
{
	// TODO:  在此添加控件通知处理程序代码
	CString msg;
	this->m_MsgInput.GetWindowText(msg);
	if (msg.GetLength() != 0)
	{
		this->m_MsgList.AddString(msg);
		this->m_MsgInput.SetWindowText(L"");
		this->m_MsgList.SetCurSel(0);
	}	
}


void CQQ消息轰炸Dlg::OnBnClickedButtonRmmsg()
{
	// TODO:  在此添加控件通知处理程序代码
	int index = this->m_MsgList.GetCurSel();
	if (index != -1)
	{
		this->m_MsgList.DeleteString(index);
	}
}


void CQQ消息轰炸Dlg::OnBnClickedButtonCleanmsg()
{
	// TODO:  在此添加控件通知处理程序代码
	this->m_MsgList.ResetContent();
}


void CQQ消息轰炸Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CQQ消息轰炸Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->hwnd == this->m_MsgInput.GetSafeHwnd())
		{
			if (pMsg->wParam == VK_RETURN)
			{
				OnBnClickedButtonAddmsg();
			}
		}
		if (pMsg->hwnd == this->m_DrtWndTitleIn.GetSafeHwnd())
		{
			if (pMsg->wParam == VK_RETURN)
			{
				OnBnClickedButtonSetwnd();
			}
		}
	}
	else if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == this->m_FindWndBtn.GetSafeHwnd())
		{
			this->m_IsFindWnd = true;
			this->m_FindWindLB.ResetContent();
			SetTimer(ID_TIMER_FIND_WND,30,NULL);
		}
		if (pMsg->hwnd == this->m_btn_getpos.GetSafeHwnd())
		{
			SetTimer(ID_TIMER_FIND_INPOS,30,NULL);
		}
	}
	if (pMsg->message == WM_LBUTTONUP)
	{
		this->m_IsFindWnd = false;
		KillTimer(ID_TIMER_FIND_WND);
		KillTimer(ID_TIMER_FIND_INPOS);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CQQ消息轰炸Dlg::OnBnClickedButtonRun()
{
	// TODO:  在此添加控件通知处理程序代码
	int sendList[] = {1,3,5,10,15,30,70,100,200,500,1000};
	int waitList[] = {30,90,300,700,1000,3000,5000,10*1000,30*1000,60*1000};
	int wtIndex = this->m_WaitTime.GetCurSel();
	int stIndex = this->m_SendTime.GetCurSel();
	this->m_VSendTime = sendList[stIndex];
	this->m_VWaitTime = waitList[wtIndex];
	this->m_PreTime = 0;
	this->m_SdMsgIndex = this->m_MsgList.GetCurSel();
	if (this->m_FromClipBoard.GetCheck() == 0)
	{
		if (this->m_MsgList.GetCurSel() == -1 || this->m_MsgList.GetCount() == 0)
		{
			MessageBox(L"请选中要发送的信息，或者添加信息", L"消息发送错误", MB_OK);
			return;
		}
	}
	if (this->m_DrtWnd == NULL)
	{
		MessageBox(L"请选取目标窗口，或者输入窗口标题", L"目标窗口错误", MB_OK);
		return;
	}
	if (this->m_DrtWnd->GetSafeHwnd() == NULL)
	{
		MessageBox(L"请选取目标窗口，或者输入窗口标题", L"目标窗口错误", MB_OK);
		return;
	}
	GetCursorPos(&m_backup_pos);
	KillTimer(ID_TIMER_NEXT_LOOP);
	SetTimer(ID_TIMER_NEXT_LOOP, this->m_VWaitTime, NULL);
}


void CQQ消息轰炸Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == ID_TIMER_NEXT_LOOP)
	{
		SendMsgProc();
		this->m_PreTime++;
		CString temp;
		temp.Format(TEXT("%d/%d"), m_PreTime, m_VSendTime);
		SetDlgItemText(IDC_STATIC_NOWTIMES, temp);
		if (IsDlgButtonChecked(IDC_CHECK_RANDOM_TIMESEND) == 1)
		{
			KillTimer(ID_TIMER_NEXT_LOOP);
			SetTimer(ID_TIMER_NEXT_LOOP, rand() % (2400 - 300) + 300, NULL);
		}
		if (m_isSendForeever == false)
		{
			if (this->m_PreTime == this->m_VSendTime)
			{
				KillTimer(ID_TIMER_NEXT_LOOP);
				SetDlgItemText(IDC_STATIC_NOWTIMES, TEXT("-/-"));
				SetCursorPos(m_backup_pos.x, m_backup_pos.y);
			}
		}
	}
	else if (nIDEvent == ID_TIMER_FIND_WND)
	{
		CPoint point;
		GetCursorPos(&point);
		this->m_DrtWnd = WindowFromPoint(point);
		this->m_FindWindLB.ResetContent();
		CString wTitle;
		this->m_DrtWnd->GetWindowText(wTitle);
		this->m_FindWindLB.AddString(L"标题："+wTitle);
		CRuntimeClass * classInfo = this->m_DrtWnd->GetRuntimeClass();
		CString wClass;
		wClass = classInfo->m_lpszClassName;
		this->m_FindWindLB.AddString(L"Class：" + wClass);
	}
	else if (nIDEvent == ID_TIMER_FIND_INPOS)
	{
		GetCursorPos(&m_input_pos);
		this->m_edt_pos.Format(TEXT("pos:%d,%d"), m_input_pos.x, m_input_pos.y);
		UpdateData(FALSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}
void CQQ消息轰炸Dlg::SendMsgProc()
{
	m_DrtWnd->SetForegroundWindow();
	m_DrtWnd->SetActiveWindow();
	if (this->m_ck_findpos == TRUE)
	{
		SetCursorPos(m_input_pos.x, m_input_pos.y);
		mouse_event( MOUSEEVENTF_LEFTDOWN ,0,0, 0, 0);
		mouse_event( MOUSEEVENTF_LEFTUP, 0,0, 0, 0);
	}
	if (this->m_FromClipBoard.GetCheck() == 0)
	{
		int sendIndex = this->m_SdMsgIndex;
		if (this->m_israndindex == true)
		{
			sendIndex = rand() % (this->m_MsgList.GetCount());
		}
		if (this->m_isOnlySel == true)
		{
			sendIndex = this->m_MsgList.GetCurSel();
		}
		if (OpenClipboard())
		{
			CString scopy;
			this->m_MsgList.GetText(sendIndex, scopy);
			wchar_t outwtext[10240] = { 0 };
			char outbord[10240 * 2] = { 0 };
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
			PressSendKey();
		}
		this->m_SdMsgIndex = (this->m_SdMsgIndex + 1) % this->m_MsgList.GetCount();
	}
	else
	{
		PressSendKey();
	}

	
}
void CQQ消息轰炸Dlg::PressSendKey()
{
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event('V', 0, 0, 0);
	keybd_event('V', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

	int SType = this->m_SendTypeCB.GetCurSel();
	if (SType == 0)
	{
		keybd_event(VK_CONTROL, 0, 0, 0);
		keybd_event(VK_RETURN, 0, 0, 0);
		keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (SType == 1)
	{
		keybd_event(VK_RETURN, 0, 0, 0);
		keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (SType == 2)
	{
		keybd_event(VK_MENU, 0, 0, 0);
		keybd_event(VK_RETURN, 0, 0, 0);
		keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (SType == 3)
	{
		keybd_event(VK_SPACE, 0, 0, 0);
		keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (SType == 4)
	{
		keybd_event(VK_TAB, 0, 0, 0);
		keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
	}
}

void CQQ消息轰炸Dlg::OnBnClickedButtonSetwnd()
{
	// TODO:  在此添加控件通知处理程序代码
	this->m_FindWindLB.ResetContent();
	CString title;
	this->m_DrtWndTitleIn.GetWindowText(title);
	this->m_DrtWnd = FindWindow(NULL,title);
	CString wTitle;
	this->m_DrtWnd->GetWindowText(wTitle);
	this->m_FindWindLB.AddString(L"标题：" + wTitle);
	CRuntimeClass * classInfo = this->m_DrtWnd->GetRuntimeClass();
	CString wClass;
	wClass = classInfo->m_lpszClassName;
	this->m_FindWindLB.AddString(L"Class：" + wClass);
}

void CQQ消息轰炸Dlg::OnBnClickedCheckRandsend()
{
	// TODO:  在此添加控件通知处理程序代码
	if (this->m_RandSend.GetCheck() == 1)
	{
		this->m_israndindex = true;
	}
	else
	{
		this->m_israndindex = false;
	}
}

void CQQ消息轰炸Dlg::OnBnClickedCheckOnlysel()
{
	// TODO:  在此添加控件通知处理程序代码
	if (this->m_OnlyCheck.GetCheck() == 1)
	{
		this->m_isOnlySel = true;
	}
	else
	{
		this->m_isOnlySel = false;
	}
}

void CQQ消息轰炸Dlg::OnBnClickedButtonHelp()
{
	// TODO:  在此添加控件通知处理程序代码
	CString helpinfo=L"使用步骤：\n\
\t1.输入目标窗口\n\
\t\t1.1方式1.输入窗口标题，点击设置窗口按钮或回车\n\
\t\t1.2方式2.在获取窗口按钮上按下鼠标左键，\n\
\t\t移动鼠标到目标窗口上松开鼠标左键\n\
\t2.输入消息，单击添加消息按钮或回车\n\
\t2.1如果勾选了来自剪切板则忽略\n\
\t3.默认发送第一行消息，其他行请选中\n\
\t4.默认发送方式为Ctrl+Enter，其他请选择\n\
\t5.默认时间间隔为30ms,其他请自行选择\n\
\t6.点击开始按钮，即可开始自动发送\n\
\t---------------------------------\n\
注意：如果时间间隔过短有可能会发送失败\n\
\tCtrl+Shift+F强制停止发送(狂按)\n\
\t这属于正常现象\n\
\t默认会将列表中的条目按顺序进行发送\n\
\t随机循序将会在列表中选一条进行一次发送\n\
\t仅选中只会发送列表中选中的条目\n\
\t对于常见的具备输入框的界面都可以哦\n\
定位输入框功能：\n\
\t适用于非常规输入时使用\n\
\t1.勾选定位输入框\n\
\t2.在获取输入框按钮上按下左键\n\
\t3.移动鼠标到输入框上合适的位置后松开左键\n\
\t这一步是在输入前在这个位置点击一下鼠标\n\
\t因此操作间隔不能太短，否则就成了双击\n\
\t建议需要定位时，间隔时间大于300ms\n\
";
	MessageBox(helpinfo,L"Help",MB_OK);
}


void CQQ消息轰炸Dlg::OnBnClickedCheckInputpos()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (this->m_ck_findpos == TRUE)
	{
		this->m_btn_getpos.EnableWindow(TRUE);
	}
	else
	{
		this->m_btn_getpos.EnableWindow(FALSE);
	}
}



void CQQ消息轰炸Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	UnregisterHotKey(this->GetSafeHwnd(), ID_STOP_LOOP_ACCE);
}
LRESULT CQQ消息轰炸Dlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	if (wParam == ID_STOP_LOOP_ACCE)
	{
		KillTimer(ID_TIMER_NEXT_LOOP);
		SetDlgItemText(IDC_STATIC_NOWTIMES, TEXT("-/-"));
		SetCursorPos(m_backup_pos.x, m_backup_pos.y);
	}
	return 0;
}


void CQQ消息轰炸Dlg::OnBnClickedCheckSendForeever()
{
	if (IsDlgButtonChecked(IDC_CHECK_SEND_FOREEVER) == 1)
	{
		m_isSendForeever = true;
		MessageBox(TEXT("无限发送模式：\n\t如果需要结束，请狂按快捷键：\n\tCtrl+Shift+F"), TEXT("无限模式提示"));
	}
	else
	{
		m_isSendForeever = false;
	}
}
