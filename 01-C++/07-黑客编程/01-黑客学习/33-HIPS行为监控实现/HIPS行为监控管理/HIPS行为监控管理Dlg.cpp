
// HIPS��Ϊ��ع���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HIPS��Ϊ��ع���.h"
#include "HIPS��Ϊ��ع���Dlg.h"
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


// CHIPS��Ϊ��ع���Dlg �Ի���



CHIPS��Ϊ��ع���Dlg::CHIPS��Ϊ��ع���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHIPS��Ϊ��ع���Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHIPS��Ϊ��ع���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SPY_ON, m_btn_spyon);
	DDX_Control(pDX, IDC_BUTTON_SPY_OFF, m_btn_spyoff);
	DDX_Control(pDX, IDC_LIST_ADMIN_LIST_LOG, m_list_hips_log);
}

BEGIN_MESSAGE_MAP(CHIPS��Ϊ��ع���Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CHIPS��Ϊ��ع���Dlg::OnBnClickedOk)
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_BUTTON_SPY_ON, &CHIPS��Ϊ��ع���Dlg::OnBnClickedButtonSpyOn)
	ON_BN_CLICKED(IDC_BUTTON_SPY_OFF, &CHIPS��Ϊ��ع���Dlg::OnBnClickedButtonSpyOff)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_LOG, &CHIPS��Ϊ��ع���Dlg::OnBnClickedButtonClearLog)
END_MESSAGE_MAP()


// CHIPS��Ϊ��ع���Dlg ��Ϣ�������

BOOL CHIPS��Ϊ��ع���Dlg::OnInitDialog()
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
	InitControls();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHIPS��Ϊ��ع���Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHIPS��Ϊ��ع���Dlg::OnPaint()
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
HCURSOR CHIPS��Ϊ��ع���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHIPS��Ϊ��ع���Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
/*
HIPS��Ϊ��أ�
	ͨ��HOOKһЩϵͳ�ؼ���API���������Ƴ��������
	���磬�������߶������
		Ҫʵ����������Ҫ�����޸�ע���ĺ���
		Ҫ���о�Ҫ�������У���Ȼ�еĲ�������ͨ��ע��ķ�ʽ�������˴������̣���������������������
		Ҫʵ��һЩ��̨���񣬾�Ҫ���ô�������ĺ����ȡ�

*/
#include"AdminWnd.h"
#include"HipsGuard.h"
typedef VOID(*SETHOOKON)(HWND);
typedef VOID(*SETHOOKOFF)();

BOOL CHIPS��Ϊ��ع���Dlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	//ǿתΪ�ṹ��
	PHIPS_INFO phips = (PHIPS_INFO)pCopyDataStruct->lpData;
	CString tipsInfo;
	if (phips->bisAsciiInfo == TRUE)
	{
		USES_CONVERSION;
		tipsInfo = A2T((char *)phips->wszHipsInfo);
	}
	else
	{
		tipsInfo = phips->wszHipsInfo;
	}
	//�Ƿ���Ҫ�����û���Ȩ���еı�ʶ
	BOOL needAdmin = TRUE;
	//����û�����úڰ����������ϵͳ�����е�Ӧ�ö���Ƶ�����޸�ע���������һ��Ͳ�Ҫ�û���Ȩ�ˣ�����Ƶ���ĵ�����Ȩ����
	if (IsDlgButtonChecked(IDC_CHECK_ONLYNOTE) == BST_CHECKED||
		phips->dwHipsClass == HIPS_CLASS_REG_SET_VALUE_EXA ||
		phips->dwHipsClass == HIPS_CLASS_REG_SET_VALUE_EXW ||
		phips->dwHipsClass == HIPS_CLASS_CREATE_FILEA ||
		phips->dwHipsClass == HIPS_CLASS_CREATE_FILEW ||
		phips->dwHipsClass == HIPS_CLASS_DELET_FILEA ||
		phips->dwHipsClass == HIPS_CLASS_DELET_FILEW ||
		phips->dwHipsClass == HIPS_CLASS_COPY_FILEEXA ||
		phips->dwHipsClass == HIPS_CLASS_COPY_FILEEXW ||
		phips->dwHipsClass == HIPS_CLASS_MOVE_FILEEXA ||
		phips->dwHipsClass == HIPS_CLASS_MOVE_FILEEXW 
		)
		needAdmin = FALSE;
	
	//��ʾ��Ȩ�Ի���
	CAdminWnd adminWnd;
	
	adminWnd.m_str_tips = tipsInfo;
	adminWnd.m_waitTime = 15 * 1000;
	if (needAdmin)
		adminWnd.DoModal();
	//��ȡ��һ��Ҫ������־�б���±�
	int index = m_list_hips_log.GetItemCount();
	if (index >= 4096)
		m_list_hips_log.DeleteItem(0);
	//д�����
	CString str;
	str.Format(TEXT("%d"), index);
	m_list_hips_log.InsertItem(index, str);
	//д�뵱ǰʱ��
	SYSTEMTIME stime;
	GetLocalTime(&stime);
	str.Format(TEXT("%04d/%02d/%02d %02d/%02d/%02d"),
		stime.wYear,
		stime.wMonth,
		stime.wDay,
		stime.wHour,
		stime.wMinute,
		stime.wSecond);
	m_list_hips_log.SetItemText(index, 1, str);
	//д��������Ϣ
	m_list_hips_log.SetItemText(index, 2, tipsInfo);

	//д���������
	switch (phips->dwHipsClass)
	{
	case HIPS_CLASS_WIN_EXEC:
	case HIPS_CLASS_SHELL_EXECUTEA:
	case HIPS_CLASS_SHELL_EXECUTEW:
	case HIPS_CLASS_CREATE_PROCESSA:
	case HIPS_CLASS_CREATE_PROCESSW:
		str = TEXT("��������");
		break;
	case HIPS_CLASS_REG_SET_VALUE_EXA:
	case HIPS_CLASS_REG_SET_VALUE_EXW:
		str = TEXT("�޸�ע���ֵ");
		break;
	case HIPS_CLASS_REG_DELETE_VALUEA:
	case HIPS_CLASS_REG_DELETE_VALUEW:
		str = TEXT("ɾ��ע���ֵ");
		break;
	case HIPS_CLASS_CREATE_SERVICEA:
	case HIPS_CLASS_CREATE_SERVICEW:
		str = TEXT("����������");
		break;
	case HIPS_CLASS_ADJUST_TOKEN_PRIVILEGES:
		str = TEXT("��������Ȩ��");
		break;
	case HIPS_CLASS_REG_CREATE_KEYEXA:
	case HIPS_CLASS_REG_CREATE_KEYEXW:
		str = TEXT("���ע����Ӽ�");
		break;
	case HIPS_CLASS_CREATE_FILEA:
	case HIPS_CLASS_CREATE_FILEW:
		str = TEXT("�����ļ�");
		break;
	case HIPS_CLASS_DELET_FILEA:
	case HIPS_CLASS_DELET_FILEW:
		str = TEXT("ɾ���ļ�");
		break;
	case HIPS_CLASS_COPY_FILEEXA:
	case HIPS_CLASS_COPY_FILEEXW:
		str = TEXT("�����ļ�");
		break;
	case HIPS_CLASS_MOVE_FILEEXA:
	case HIPS_CLASS_MOVE_FILEEXW:
		str = TEXT("�ƶ��ļ�");
		break;
	}
	m_list_hips_log.SetItemText(index, 3, str);
	//д�������������ڲ�������Ȩ���ڵ�Ĭ�Ϸ���
	if (needAdmin)
		str = adminWnd.m_retCode == true ? TEXT("����") : TEXT("����");
	else
		str = TEXT("����");

	m_list_hips_log.SetItemText(index, 4, str);
	//���ز��������DLL
	if (needAdmin)
	{
		if (adminWnd.m_retCode == true)
			return HIPS_AUTH_AGREEN;
		else
			return HIPS_AUTH_REDUCE;
	}
	else
		return HIPS_AUTH_AGREEN;
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}


void CHIPS��Ϊ��ع���Dlg::InitControls()
{
	//������չ��ʽ���������ߺ�ѡ��һ����
	m_list_hips_log.SetExtendedStyle(m_list_hips_log.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//������
	m_list_hips_log.InsertColumn(0, TEXT("���"));
	m_list_hips_log.InsertColumn(1, TEXT("ʱ��"));
	m_list_hips_log.InsertColumn(2, TEXT("��  Ϊ  ��  ��  ��  ��"));
	m_list_hips_log.InsertColumn(3, TEXT("�� ��"));
	m_list_hips_log.InsertColumn(4, TEXT("�� ��"));
	//�����Զ��п�
	m_list_hips_log.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_list_hips_log.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_list_hips_log.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_list_hips_log.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_list_hips_log.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);

	m_btn_spyon.EnableWindow(TRUE);
	m_btn_spyoff.EnableWindow(FALSE);
}


void CHIPS��Ϊ��ع���Dlg::OnBnClickedButtonSpyOn()
{
	//����DLL
	m_hInst = LoadLibrary(_T("HipsIL.dll"));
	if (m_hInst == NULL)
	{
		DWORD err = GetLastError();
		return;
	}
	//��ȡHOOK������ַ
	SETHOOKON SetHookOn = (SETHOOKON)GetProcAddress(m_hInst, "SetHookOn");
	//��ʼHOOK
	SetHookOn(this->GetSafeHwnd());
	FreeLibrary(m_hInst);
	//���ð�ť״̬
	m_btn_spyon.EnableWindow(FALSE);
	m_btn_spyoff.EnableWindow(TRUE);
}


void CHIPS��Ϊ��ع���Dlg::OnBnClickedButtonSpyOff()
{
	m_hInst = LoadLibrary(_T("HipsIL.dll"));
	SETHOOKOFF SetHookOff = (SETHOOKOFF)GetProcAddress(m_hInst, "SetHookOff");
	SetHookOff();
	
	FreeLibrary(m_hInst);
	//CloseHandle(m_hInst);//��һ����Ȼ��˵��Ҫд�ϣ�����������û�ʧ��
	m_btn_spyon.EnableWindow(TRUE);
	m_btn_spyoff.EnableWindow(FALSE);
}


void CHIPS��Ϊ��ع���Dlg::OnBnClickedButtonClearLog()
{
	m_list_hips_log.DeleteAllItems();
}
