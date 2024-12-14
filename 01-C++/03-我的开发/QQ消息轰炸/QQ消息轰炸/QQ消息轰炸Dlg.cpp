
// QQ��Ϣ��ըDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQ��Ϣ��ը.h"
#include "QQ��Ϣ��ըDlg.h"
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


// CQQ��Ϣ��ըDlg �Ի���



CQQ��Ϣ��ըDlg::CQQ��Ϣ��ըDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQQ��Ϣ��ըDlg::IDD, pParent)
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

void CQQ��Ϣ��ըDlg::DoDataExchange(CDataExchange* pDX)
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

BEGIN_MESSAGE_MAP(CQQ��Ϣ��ըDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CQQ��Ϣ��ըDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADDMSG, &CQQ��Ϣ��ըDlg::OnBnClickedButtonAddmsg)
	ON_BN_CLICKED(IDC_BUTTON_RMMSG, &CQQ��Ϣ��ըDlg::OnBnClickedButtonRmmsg)
	ON_BN_CLICKED(IDC_BUTTON_CLEANMSG, &CQQ��Ϣ��ըDlg::OnBnClickedButtonCleanmsg)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CQQ��Ϣ��ըDlg::OnBnClickedButtonRun)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SETWND, &CQQ��Ϣ��ըDlg::OnBnClickedButtonSetwnd)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CQQ��Ϣ��ըDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_CHECK_RANDSEND, &CQQ��Ϣ��ըDlg::OnBnClickedCheckRandsend)
	ON_BN_CLICKED(IDC_CHECK_ONLYSEL, &CQQ��Ϣ��ըDlg::OnBnClickedCheckOnlysel)
	ON_BN_CLICKED(IDC_CHECK_INPUTPOS, &CQQ��Ϣ��ըDlg::OnBnClickedCheckInputpos)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_BN_CLICKED(IDC_CHECK_SEND_FOREEVER, &CQQ��Ϣ��ըDlg::OnBnClickedCheckSendForeever)
END_MESSAGE_MAP()


// CQQ��Ϣ��ըDlg ��Ϣ�������

BOOL CQQ��Ϣ��ըDlg::OnInitDialog()
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
	this->m_SendTypeCB.AddString(L"��");
	this->m_SendTypeCB.SetCurSel(0);

	this->m_RandSend.SetCheck(0);
	this->m_OnlyCheck.SetCheck(0);

	this->m_ck_findpos = FALSE;
	this->m_btn_getpos.EnableWindow(FALSE);
	this->m_edt_pos=(L"pos:0,0");

	RegisterHotKey(this->GetSafeHwnd(), ID_STOP_LOOP_ACCE, MOD_CONTROL | MOD_SHIFT, 'F');
	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CQQ��Ϣ��ըDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CQQ��Ϣ��ըDlg::OnPaint()
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
HCURSOR CQQ��Ϣ��ըDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQQ��Ϣ��ըDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CQQ��Ϣ��ըDlg::OnBnClickedButtonAddmsg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString msg;
	this->m_MsgInput.GetWindowText(msg);
	if (msg.GetLength() != 0)
	{
		this->m_MsgList.AddString(msg);
		this->m_MsgInput.SetWindowText(L"");
		this->m_MsgList.SetCurSel(0);
	}	
}


void CQQ��Ϣ��ըDlg::OnBnClickedButtonRmmsg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int index = this->m_MsgList.GetCurSel();
	if (index != -1)
	{
		this->m_MsgList.DeleteString(index);
	}
}


void CQQ��Ϣ��ըDlg::OnBnClickedButtonCleanmsg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->m_MsgList.ResetContent();
}


void CQQ��Ϣ��ըDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CQQ��Ϣ��ըDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
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


void CQQ��Ϣ��ըDlg::OnBnClickedButtonRun()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
			MessageBox(L"��ѡ��Ҫ���͵���Ϣ�����������Ϣ", L"��Ϣ���ʹ���", MB_OK);
			return;
		}
	}
	if (this->m_DrtWnd == NULL)
	{
		MessageBox(L"��ѡȡĿ�괰�ڣ��������봰�ڱ���", L"Ŀ�괰�ڴ���", MB_OK);
		return;
	}
	if (this->m_DrtWnd->GetSafeHwnd() == NULL)
	{
		MessageBox(L"��ѡȡĿ�괰�ڣ��������봰�ڱ���", L"Ŀ�괰�ڴ���", MB_OK);
		return;
	}
	GetCursorPos(&m_backup_pos);
	KillTimer(ID_TIMER_NEXT_LOOP);
	SetTimer(ID_TIMER_NEXT_LOOP, this->m_VWaitTime, NULL);
}


void CQQ��Ϣ��ըDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		this->m_FindWindLB.AddString(L"���⣺"+wTitle);
		CRuntimeClass * classInfo = this->m_DrtWnd->GetRuntimeClass();
		CString wClass;
		wClass = classInfo->m_lpszClassName;
		this->m_FindWindLB.AddString(L"Class��" + wClass);
	}
	else if (nIDEvent == ID_TIMER_FIND_INPOS)
	{
		GetCursorPos(&m_input_pos);
		this->m_edt_pos.Format(TEXT("pos:%d,%d"), m_input_pos.x, m_input_pos.y);
		UpdateData(FALSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}
void CQQ��Ϣ��ըDlg::SendMsgProc()
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
void CQQ��Ϣ��ըDlg::PressSendKey()
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

void CQQ��Ϣ��ըDlg::OnBnClickedButtonSetwnd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->m_FindWindLB.ResetContent();
	CString title;
	this->m_DrtWndTitleIn.GetWindowText(title);
	this->m_DrtWnd = FindWindow(NULL,title);
	CString wTitle;
	this->m_DrtWnd->GetWindowText(wTitle);
	this->m_FindWindLB.AddString(L"���⣺" + wTitle);
	CRuntimeClass * classInfo = this->m_DrtWnd->GetRuntimeClass();
	CString wClass;
	wClass = classInfo->m_lpszClassName;
	this->m_FindWindLB.AddString(L"Class��" + wClass);
}

void CQQ��Ϣ��ըDlg::OnBnClickedCheckRandsend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (this->m_RandSend.GetCheck() == 1)
	{
		this->m_israndindex = true;
	}
	else
	{
		this->m_israndindex = false;
	}
}

void CQQ��Ϣ��ըDlg::OnBnClickedCheckOnlysel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (this->m_OnlyCheck.GetCheck() == 1)
	{
		this->m_isOnlySel = true;
	}
	else
	{
		this->m_isOnlySel = false;
	}
}

void CQQ��Ϣ��ըDlg::OnBnClickedButtonHelp()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString helpinfo=L"ʹ�ò��裺\n\
\t1.����Ŀ�괰��\n\
\t\t1.1��ʽ1.���봰�ڱ��⣬������ô��ڰ�ť��س�\n\
\t\t1.2��ʽ2.�ڻ�ȡ���ڰ�ť�ϰ�����������\n\
\t\t�ƶ���굽Ŀ�괰�����ɿ�������\n\
\t2.������Ϣ�����������Ϣ��ť��س�\n\
\t2.1�����ѡ�����Լ��а������\n\
\t3.Ĭ�Ϸ��͵�һ����Ϣ����������ѡ��\n\
\t4.Ĭ�Ϸ��ͷ�ʽΪCtrl+Enter��������ѡ��\n\
\t5.Ĭ��ʱ����Ϊ30ms,����������ѡ��\n\
\t6.�����ʼ��ť�����ɿ�ʼ�Զ�����\n\
\t---------------------------------\n\
ע�⣺���ʱ���������п��ܻᷢ��ʧ��\n\
\tCtrl+Shift+Fǿ��ֹͣ����(��)\n\
\t��������������\n\
\tĬ�ϻὫ�б��е���Ŀ��˳����з���\n\
\t���ѭ�򽫻����б���ѡһ������һ�η���\n\
\t��ѡ��ֻ�ᷢ���б���ѡ�е���Ŀ\n\
\t���ڳ����ľ߱������Ľ��涼����Ŷ\n\
��λ������ܣ�\n\
\t�����ڷǳ�������ʱʹ��\n\
\t1.��ѡ��λ�����\n\
\t2.�ڻ�ȡ�����ť�ϰ������\n\
\t3.�ƶ���굽������Ϻ��ʵ�λ�ú��ɿ����\n\
\t��һ����������ǰ�����λ�õ��һ�����\n\
\t��˲����������̫�̣�����ͳ���˫��\n\
\t������Ҫ��λʱ�����ʱ�����300ms\n\
";
	MessageBox(helpinfo,L"Help",MB_OK);
}


void CQQ��Ϣ��ըDlg::OnBnClickedCheckInputpos()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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



void CQQ��Ϣ��ըDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	UnregisterHotKey(this->GetSafeHwnd(), ID_STOP_LOOP_ACCE);
}
LRESULT CQQ��Ϣ��ըDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	if (wParam == ID_STOP_LOOP_ACCE)
	{
		KillTimer(ID_TIMER_NEXT_LOOP);
		SetDlgItemText(IDC_STATIC_NOWTIMES, TEXT("-/-"));
		SetCursorPos(m_backup_pos.x, m_backup_pos.y);
	}
	return 0;
}


void CQQ��Ϣ��ըDlg::OnBnClickedCheckSendForeever()
{
	if (IsDlgButtonChecked(IDC_CHECK_SEND_FOREEVER) == 1)
	{
		m_isSendForeever = true;
		MessageBox(TEXT("���޷���ģʽ��\n\t�����Ҫ��������񰴿�ݼ���\n\tCtrl+Shift+F"), TEXT("����ģʽ��ʾ"));
	}
	else
	{
		m_isSendForeever = false;
	}
}
